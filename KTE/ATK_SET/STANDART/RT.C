
//         ПРОГРАММА  РЕГУЛЯТОРА ТОКА ЯКОРЯ .
//----------------------------------------------------------

void RegTok (void)
 {
     word  bx, cx ;
     lword lax ;

   if ( Ckl._.RT2 == 1 || Isp._.RT2_Res == 1 || S.Disable == 1 )
   {
     // Инициализация РТ1 в наладочных режимах , в которых он не используется :
      OIRT_drob = 0 ;
      ZIDN  = 0 ;  /* выход ЗИ-РТ. */
      OIRT  = _r.RevU0  ;  /* интегратор регулятора тока */
     //---
     return ;
   }

     //----  Фрагмент вынесен из концов регуляторов скорости и ЭДС
     //   для того чтобы регулятору тока задавать ток, а он уже
     //   разбирался с реверсом и ограничениями. -------

      OuRegS = OuRegS_dop_kod ;


        if ( (sw)OuRegS >= 0 ) //RegFlg._.OuRS == 0 )
        {
            if ((sw)OuRegS > (sw)_r.OuRSMaxMost1 ) OuRegS = _r.OuRSMaxMost1 , Prz._.int_p = 1 ;
        }
        else
        {
            if ((sw)OuRegS < (sw)_r.OuRSMaxMost2 ) OuRegS = _r.OuRSMaxMost2 , Prz._.int_m = 1 ;
        }

       //---------------  Ограничение задания на ток.
       // Объектные ограничения после штатного :
      can_ConfigReg ( _CAN_Id_Zad_Ogr ) ; // CAN-ограничение задания на ток
      obj_ConfigReg ( _Obj_Id_Zad_Ogr ) ; // Объектное задание перебивает CAN-задание
       //---------------

      if ( (sw)OuRegS < 0 )  // ВыхРС (вхРТ) отриц. - режим торм-я или реверса .
        {
             RegFlg._.OuRS = 1 ;       // Флаг отриц. ВыхРС (вкл. моста "Назад")
             OuRegS = ~OuRegS + 1 ;    // Модуль задания .
        }
      else  RegFlg._.OuRS = 0 ;

      // 1% задания тока , чтобы в канале не появилось отрицательное смещение :
      //16.11.06 if ( OuRegS == 0 )  OuRegS = 0x0002 ;
      //-----------

         // Проверка необходимости реверса.
      if ((( S.flg._.Invertor == 1 ) && ( RegFlg._.OuRS == 1 ))
                              ||
          (( S.flg._.Invertor == 0 ) && ( RegFlg._.OuRS == 0 )))
          {
            OuRegS = 0x0u ;
              // Реверс без сброса тока , с подстановкой нужного интегратора :
              // Процедуру реверса начинаем без сброса тока :
              if       ( S.flg._.Invertor == 1 ) // Переход на отрицательный выход РС :
              {
                  // Подставлять интегратор при этом переходе не нужно , иначе будет удар тока .
                  // KVV вставив за порадою ДДС бо були стуки у редукторі під час нульового струму до 500мсек поки інтегратор вилазив зі 150грд
                  //if( _or.CfgO._.VklOIRT_for_revers == 1 ) OIRT = _or.RevU0_Vypryamitel ; // KVV как ДДС и говорил - долбануло ток до герконов OIRT = OIRT_for_revers ; // Подставляем рассчитанный ранее интегратор .
                  // Zapamyatovuy schob trohy piznishe vstavyty u integrator 
                  // koly vugol AP2 viyde na 120grd - shob ne bulo kydku strumu
                  OIRT_for_revers_vypryamitel = OIRT_for_revers; // KVV- perenis u avar.c  + _Grad( 5.0 ); // 5grd - schob zmenshity Id na 10-15% // KVV - pry perehody u vypryamlyach ne mogna vidrazu vstavlyaty schosy u integrator 
                  bi_canLrv_6g = 0 ;  // KVV - ochischaem chtoby Ap2 prislala svegee,t.k. pri bystroy smene v Ap1 
                  bi_canLrv_120g = 0 ; //  "Vypryam-Invertor-Vypryam" voznikayut broski toka, t/k/ integrator RT initializ mgnovenno bez vydergki
                  S.flg._.Invertor = 0 ;
                  bo_canOuRS = 1 ; // Флаг отриц. ВыхРС - режим торможения .
                  bo_atkOuRS = 1 ; // Флаг отриц. ВыхРС - режим торможения .
              }
              else if  ( S.flg._.Invertor == 0 )
              {
                  OIRT = OIRT_for_revers; // KVV- perenis u avar.c    + _Grad( 20.0 ) ; // 20rd - schob zmenshity Id na 10-15%  KVV // Подставляем рассчитанный ранее интегратор .
                  OIRT_for_revers_vypryamitel = 0;// na vypadok koly regim vypryamlyacha buv korotkiy ta ne vstyglo obnulytysya
                  bi_canLrv_6g = 0 ;  // KVV - ochischaem chtoby Ap2 prislala svegee,t.k. pri bystroy smene v Ap1 
                  bi_canLrv_120g = 0 ; //  "Vypryam-Invertor-Vypryam" voznikayut broski toka, t/k/ integrator RT initializ mgnovenno bez vydergki
                  S.flg._.Invertor = 1 ;
                  bo_canOuRS = 0 ; // Флаг положит. ВыхРС .
                  bo_atkOuRS = 0 ; // Флаг положит. ВыхРС .
              }
          }
      else
         {
   #ifdef _ATK_SET
           // 14.10.2020 - Почему-то иногда бывало , что после классического реверса , КТЭ-шного ,
           //              который в АТК уже не используется , режим Инвертор/Выпрямитель
           //              перекидывался , а bo_canOuRS не изменялся , что приводило к аварии .
           //              Во избежание данной ситуации , приводим эти два бита в соответствие .
           // 25.08.2021 - Все равно оставляем эту припарку , она не помешает , если выполнится лишний раз :
               if ( S.flg._.Invertor == 0 )
               {
                 bo_canOuRS = 1 ; // Флаг отриц. ВыхРС - режим торможения .
                 bo_atkOuRS = 1 ; // Флаг отриц. ВыхРС - режим торможения .
               }
               else
               {
                 bo_canOuRS = 0 ; // Флаг положит. ВыхРС .
                 bo_atkOuRS = 0 ; // Флаг положит. ВыхРС .
               }
   #endif
           S.flg._.ZapretImp = 0 ;
         }
       Get_Regim((ERT_Reg*) &RT_Regim);
      // KVV - Koly AP2 vyyshla povnistyu u invertor = 120grd Подставляем рассчитанный ранее интегратор .
      if( _or.CfgO._.VklOIRT_for_revers == 1 ) 
      { 
        if( bi_canLrv_120g == 1 && OIRT_for_revers_vypryamitel != 0 )
        {
          OIRT = OIRT_for_revers_vypryamitel ;  
          OIRT_for_revers_vypryamitel = 0; // dlya odnorazovosti 
        }
      }
      
     //-----------------

      ZIDN =  OuRegS; // Задание тока однополярное - взят модуль .

      bx = IDV - ZIDN ;

      if ( (sw)bx >= 0 )
        {
          if ( S.flg._.Fmax == 1 )  goto r ;
        }
      else
        {
          if ( S.flg._.Fmin == 1 )  goto r ;
        }
         

   lax = _r_KRTNI;

   if ( lax == 0 )
     {             // инициализация интегратора при Ки = 0 :
       OIRT = _r.RevU0 ;
       OIRT_drob = 0 ;
       goto r ;
     }

   // KVV: Esli rotornoe SIFU nahoditsya v stadii Reversa t.e. perehoda ot 6grd k 120grd ili naoborot
   // to blokiruem narastanie integratora. 
   // Esli Lrv = 6 ili 120 ili >120 (150 avariya ili chtoto drugoe) to razreshaem integrator
   //if ( bi_canLrv_6g_120g == _canLrv_6g_120g )  goto r ;
   if ( bi_canLrv_6g == 0 && bi_canLrv_120g == 0 && (sw)bx < 0)  goto r ; // Zapret v storonu Lmin
   
    //-------------- 01.04.09 -------------------------------------

    // 3.3 мс - такт счёта , раз в пульс .
    // 65535  - основание интегратора и выхода РТ (дробная часть) , в конце происходит сдвиг на 16 разрядов влево .
    // 64     - основание уставки Ти (дробная часть) для возможности задать доли миллисекунды .
    lax = (lw)( (d)_Grad( 1 ) / (d)_Id_nom ( 0.01 ) *  3.3 * 65535. * 64. ) / lax ;
    lax &= 0x7ffffffful ;  //защита от "-" коэфф.

    //--------------------------------------------------
    cx = bx ;                     // ошибка .
    if ( (sw)cx < 0 )  cx = -cx ; // выпрямленная ошибка .
    // Если lax = 0 , то процессор _CM3_ при делении на нуль получает нуль , входит в условие
    // и выдаёт максимальный выход , что есть неправильно . Поэтому проверяем , что lax != 0 :
    if ( ((lw)cx >= (lw)0x7fffffff / lax) && (lax != 0) )    // sravnivaem modul oshibki
     {                                       // s maksimalno dopustimoy
       if ( (sw)bx >= 0 ) lax = 0x7fffffff ; // pri vychislennom 'Ki',
       else               lax = 0x80000000 ; // dlya 32-bit setki oshibkoy.
     }
    else  lax = (slw)lax * (slw)(sw)bx ;     // умножение интегр. коэффициента на ошибку
    //--------------------------------------------------

    // lax = (lw) bx * (lw) KRTI ;
    // if ( lax > 0x4000u ) lax = 0x4000u ;
    if ( (slw)lax >= ((slw)0x4000u << 16) )   lax = (lw)0x4000u << 16 ;  //оставшееся ограничение Шестакова

       //  Подготовка к контролю переполнения (без использ.'asm'):
       // если до сложения/вычитания операнды были одного знака, а результат
       // получился другого знака - значит произошло переполнение.
     cx = 2 ;
     if ( (slw)lax >= 0 ) // запоминаем сочетание знаков операндов.
      {
          if( (sw)OIRT >= 0 ) cx = 0 ; // +/+
      }
     else if( (sw)OIRT <  0 ) cx = 1 ; // -/-

     lax += (slw)(sw)OIRT << 16 ;
     lax += (lw)(w)OIRT_drob ;   // DROB ISN'T SIGNED !

              /* Проверка переполнений. */
                  //  переполнение в плюс?
          if     ( cx == 0 && (slw)lax <  0 ) goto v1 ;
                  //  переполнение в минус?
          else if( cx == 1 && (slw)lax >= 0 ) goto v2 ;
    //--------------------------------------------------

              /* Проверка ограничений. */
          if ( (slw)lax < ((slw)_r.RTMIN << 16) )
            {
    v2:       lax = (lw)_r.RTMIN << 16 ;
            }
          else if ( (slw)lax >= ((slw)_r.RTMAX << 16) )
            {
    v1:       lax = (lw)_r.RTMAX << 16 ;
            }

     OIRT = (slw)lax >> 16 ; // дробная часть уходит, целая записывается .
     OIRT_drob = lax ;       // запись дробной части .

  //-----------------------------------------------------------------------

  r:
        lax = _r_KRTP ;
                                            // "<< 8"-догоняем "Kp*256" до формата
        lax = lax * _Grad( 1 ) / _Id_nom ( 0.01 ) << 8 ;
        lax &= 0x7ffffffful ;  //защита от "-" коэфф.

        //---------- preventive overflow control -----------
        cx = bx ;                     // ошибка .
        if ( (sw)cx < 0 )  cx = -cx ; // выпрямленная ошибка .
        // Если lax = 0 , то процессор _CM3_ при делении на нуль получает нуль , входит в условие
        // и выдаёт максимальный выход , что есть неправильно . Поэтому проверяем , что lax != 0 :
        if ( ((lw)cx >= (lw)0x7fffffff / lax) && (lax != 0) )    // sravnivaem modul oshibki
          {                                       // s maksimalno dopustimoy
            if ( (sw)bx >= 0 ) lax = 0x7fffffff ; // pri vychislennom 'Kp',
            else               lax = 0x80000000 ; // dlya 32-bit setki oshibkoy.
          }
        else  lax = (slw)lax * (slw)(sw)bx ;


        //  Подготовка к контролю переполнения (без использ.'asm'):
        // если до сложения/вычитания операнды были одного знака, а результат
        // получился другого знака - значит произошло переполнение.
        cx = 2 ;
        if ( (slw)lax >= 0 ) // запоминаем сочетание знаков операндов.
          {
             if( (sw)OIRT >= 0 ) cx = 0 ; // +/+
          }
        else if( (sw)OIRT <  0 ) cx = 1 ; // -/-

        lax += (slw)(sw)OIRT << 16 ;
        lax += (lw)(w)OIRT_drob ;   // DROB ISN'T SIGNED !

                  /* Проверка переполнений. */
                      //  переполнение в плюс?
              if     ( cx == 0 && (slw)lax <  0 ) goto p3 ;
                      //  переполнение в минус?
              else if( cx == 1 && (slw)lax >= 0 ) goto p2 ;
                      //  нет переполнения.

                  /* Проверка ограничений. */
              if ( (slw)lax < ((slw)_r.RTMIN << 16) )
                {
       p2:          ORT = (lw)_r.RTMIN ;
                }
              else if ( (slw)lax >= ((slw)_r.RTMAX << 16) )
                {
       p3:          ORT = (lw)_r.RTMAX  ;
                }
              else  ORT = (slw)lax >> 16 ; // дробная часть уходит, целая записывается .


    return;
 }

//------------------------------------
		//Программа линеаризации 

word Linear (word Alfa)
{
   register word  ax , bx , cx ;

  if ( Alfa <= _Ugol_90 )  ax = Alfa ;
  else                    ax = _Ugol_180 - Alfa ;
    bx  = LIN [ ax >> 8 ] ;
    cx  = LIN [(ax >> 8) + 1 ] ;
    cx -= bx ;
    bx += (w)( (lw)cx * (lw)(ax & 0x00FFu) / 0x0100ul ) ;
  if ( Alfa > _Ugol_90 )
  {
    bx = _Ugol_180 - bx ;
  }
return bx;

}

