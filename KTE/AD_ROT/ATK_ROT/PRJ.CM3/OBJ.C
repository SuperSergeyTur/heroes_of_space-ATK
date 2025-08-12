
//     ОБЪЕКТНЫЕ ПРОГРАММЫ.
//
//--------------------------------------------------------
//    Программа считывания кода текущего резерва для
//  перезагрузки уставок у многорезервных агрегатов.
word read_rezerv ( void )
  {
    register word ax ;

    // Для многорезервных агрегатов ОБЯЗАТЕЛЬНО следующее :
    //   1. На каждую область уставок ДОЛЖЕН БЫТЬ отдельный , самостоятельный дискретный вход .
    //   2. КАЖДЫЙ дискретный вход , для каждой области уставок , должен проверяться в условии .
    //   3. Дискретный вход для определения области уставок должен быть "= 1" , именно "1" ,
    // а не "0" , это важно .
    //   4. В типовых уставках установить инверсию дискретных входов "= 1" .
    //   5. Наличие "ax = 0" обязательно , для того , чтобы определять отсуствующий резерв .
    //   6. Для отсутствующего резерва применить либо "else" без проверки дискретных входов
    // (как в примере ниже) , либо проверить дискретные входы для отсуствующего резерва на "= 0" .
    //   7. В каждой области уставок необходимо будет принять и сохранить Типовые Уставки .

    //if      ( bi_KTE_rezerv1 == 1 ) ax = 1 ;
    //else if ( bi_KTE_rezerv2 == 1 ) ax = 2 ;
    //else                            ax = 0 ;

  // Для раздельной работы 12-пульсной схемы :
  #if defined(bi_Vedusch) && defined(bi_Vedom) && defined(bi_Both)
    if      ( bi_Vedusch == 1 && bi_Vedom == 0 && bi_Both == 0 ) ax = 2 ; // ШС1,ШС2
    else if ( bi_Vedusch == 0 && bi_Vedom == 1 && bi_Both == 0 ) ax = 3 ; //           ШС3,ШС4
    else if ( bi_Vedusch == 0 && bi_Vedom == 0 && bi_Both == 1 ) ax = 1 ; // ШС1,ШС2 + ШС3,ШС4
    else                                                         ax = 0 ;
  #else
    ax = 0 ; // если нет резерва
  #endif

    return ax ;
  }
//--------------------------------------------------------


//     ОБЪЕКТНАЯ ПРОГРАММА.

word  ObjPrg ( word num )
  {
    word ax;
    lword lax;
    if ( num != _Obj_c_Init && num != _Obj_c_Common_avar ) // Инициализация и Общие Аварии в любом случае .
     {
        // Задано ли объектное управление .
      if ( _r.Cfg._.Obj_prg == 0 || Isp.all != 0 ) return 1 ;
     }
   //----
    switch ( num )
    {    // Стартовая объектная программа для задания начальных условий.
      case _Obj_c_Init :
        TimeFrot = Timer1_fSec;
        SimCounter = 0;
        RT_Str.zad_max = &_r.RTMAX;
        RT_Str.zad_min = &_r.RTMIN;
        RT_Str.kp =  &_r.KRTP;   
        RT_Str.ki =  &_r.KRTNI;   
        RT_Str.zad = &canr.Id_zad;   
        RT_Str.oc  = &IDV;    
        RT_Str.cfg._.enable = 0;                                   
        RT_Str.cfg._.positiv_oc = 1;
        RT_Str.cfg._.pos_out = 1;
        RT_Str.cfg._.positiv_in = 1;    
        
        RT_Str.zi.temp_p_razg = &_r.Temp_RT_P ;
        RT_Str.zi.temp_p_torm = &_r.Temp_RT_M ;
        RT_Str.zi.time = timer1 ;
        trig_Privyazk_TZ = 0 ;
        trig_Priv_TZ = 0;
        Accel = 0;
        DP_buffer[0] = DP_buffer[1] = DP_buffer[2] = 0;
        DP_index = 0;
        DPSimulator.Init(&_or.DeltDPSimulat, &Accel,  _wgL( 200 ) , (w)0x1fff, &Accel ,3);
        Prg.all |= _Sled;
        Trg_Sled = 0;
        Encf = 0;
        //EncDP_old_r =0;
        EncoderDPr = 0;
        bo_Err_Sifu = 0;
        Err_counter[0] = 0;
        Err_counter[1] = 0;
          
        //QueryTimeOvrOk_old = QueryTimeOvrOk  = 0;
        
        //trig_Privyazk_TZ= 1;
        for (ax = 0; ax < _Fil_buf_max_Len; ++ax)
        {
          DP_buffer[ax] = 0;
        }
        Timer3 = (lw*)&LPC_TIM3->TC;
         break;
        //-------
         // Объектная программа для задания начальных условий при переходе
        // из Работы в Сб.Готовности.
      case _Obj_c_DS1_Init :
        break;
        //-------
         // Объектная программа перед всеми защитами , например , для зарядки измерений .
      case _Obj_c_Common_avar :
/*        lax = *Timer3;
       if ((lw)(DP_TZ - lax ) > _Secl(3))
       {
         ++Err_counter[1];
         mOtkl_Imp ( _Sifu_Err_imp) ;
         DP_TZ = lax+_MkSecl(2000);
         _sifu_epa_time ( DP_TZ );
         S.NumInt = 1 ;
         Time_ErrSifu = timer1;
         bo_Err_Sifu = 1;
       }
       
       if (bo_Err_Sifu )
       {
         if((u)((w)(timer1- Time_ErrSifu)) > _MkSec(20000))
         {
           mVkl_Imp(_Sifu_Err_imp);
           bo_Err_Sifu = 0;
         }
       }*/
        if ( canr.Data._.Connect == 0 )
        {
          mSet_ServiceMsg2( _Srv2_NoLinkCAN ) ;
          canr.StatReg2.all = 0 ;
        }
        else
        {
          mClr_ServiceMsg2( _Srv2_NoLinkCAN ) ;
        }

        //------------------------ Выдача дискретных сигналов ---------------------------------

        // реле К8 - состояние ВВ3 вакуумного выключателя статора .
        if ( KTE2_VV1_stator == 1 )
        {
          bo_VV1_stator = 1 ;
        }
        else
        {
          bo_VV1_stator = 0 ;
        }

        // Общие Аварии выполняются даже в наладочных режимах и при отключенном объектном управлении :

        break;
        //-------
         // Объектная программа для Сборки Готовности.
      case _Obj_c_Sborka_Gotovn :
         //    Для контроля задания скорости в Сборке Готовности необходимо прием задания
         // писать ниже , в работе , а здесь , в Сборке Готовности , закоменировать "break" .
        trig_Privyazk_TZ = 0 ;
        trig_Priv_TZ = 0;
        Time_Pusk = Timer1_Ovr;
        break;
        //-------
         // Объектная программа защит, неотключаемая после срабатывания защиты.
      case _Obj_c_Rabota :
        if ( trig_Priv_TZ == 0 )
        {
            trig_Privyazk_TZ = 1 ;

            if (  trig_Privyazk_TZ == 1 && ( (u)((w)(Timer1_Ovr - Time_Pusk)) > _Sec(1.2) )  )
               {
                  trig_Privyazk_TZ = 0 ;
                  trig_Priv_TZ = 1 ;
               }
        }

        break;
        //-------
         // Объектная программа защит, отключаемая после срабатывания защиты.
      case _Obj_c_Avar_Otkl :
        break;
        //-------
    }

    return 0;
  }
/*--------------------------------------------------*/
void SmulatorDP(void)                  // симулятор энкодера
{
    if ( _or.CfgO._.EnSimulat )
     {
       //if ( _or.CfgO._.Inv_Simul == 0 )
       DPSimulator.Run();
     }

     return;
}

void DPLrotNrot ( void )  // функция вычисления эл. угла поворота ротора, периода(частоты) напряжения ротора и скорости вращения ротора
{
  word ax , bx ;
  lword lax ;
  float fax, fbx;

    // Энкодер 13-разрядный, максимальное число - 8191 дискр.
   // EncoderBinar = GraytoBinarycode( EncoderGray );

    if ( !_or.CfgO._.EnSimulat )
    {
      EncoderBinar = EncoderGray  ;
    }
    else
    {
      EncoderBinar = DPSimulator.GetRes();
    }
     
    //------ Вычисление электрического угла поворота ротора -------

  if ( QueryTimeOk != TimeDP_old  )
    {

       deltTimDP = QueryTimeOk - TimeDP_old ; //delta_T - время между измерениями датчика положения

       deltTDP_old = deltTimDP  ;                                                                                // DAN

         if ( (sw)EncoderBinar > _wgL360 )                                                                       // DAN
          {                                                                                                      // DAN
            EncoderBinar = _wgL360 ;                                                                             // DAN
          }                                                                                                      // DAN

       if ( !_or.CfgO._.EnSimulat )    // в штатном режиме                                                      // DAN
        {                               // если при вращении энкодер выдает обратную пилу то нужно инвертировать // DAN
            if ( _r.Sk_str._.EncodInv == 1 ) EncoderDPr = _wgL360 - (w)EncoderBinar ;                             // DAN
            else                             EncoderDPr =  (w)EncoderBinar;                                       // DAN
        }                                                                                                  // DAN
       else                                  EncoderDPr =  (w)EncoderBinar;                                       // DAN

       
       if (EncoderDPr >= EncDP_old)
       {
         ax =  EncoderDPr - EncDP_old ;  // deltDP - дельта между измерениями датчика положения
       }
       else
       {
         //Переход через ноль 
         if ((EncDP_old - EncoderDPr) > _wgL180)
         {
           ax = _wgL360 - EncDP_old+ EncoderDPr;
           if (_or.CfgO._.Priv_Filt)
           {
             EncoderDPf= EncoderDPr; //Раз в оборот притягиваем фильтрованное значение к реальному
           }
         }
         else
         {
           ax = EncoderDPr - EncDP_old ;
         }
       }
       deltDP_r = ax;
       EncDP_old = EncoderDPr ;
       //      ax &= _wgL360 ;                // обререзаем под формат энкодера

 /*      if ( (ax & 0x1000u) != 0 )       // добавляем знак если надо
         {
            ax |=  0xE000u ;
            
         }
*/       
  
       //ax &= _wgL360 ;                // обререзаем под формат энкодера
      
       if(_or.CfgO._.En_Fil_DP)
       {
         
          DP_buffer[DP_index] = (float)(sw)ax;
          if (++DP_index >= _or.Fil_buf_Len)
          {
            DP_index = 0;
          }
          fax = 0;
          for(bx = 0; bx < _or.Fil_buf_Len; ++bx)
          {
            fax += DP_buffer[bx]; 
          }
          fax /=(float)_or.Fil_buf_Len;
          ax = (w)fax;
          EncoderDPf += ax;
          if (EncoderDPf > _wgL360)
          {
            EncoderDPf %=_wgL360 ;         
          }
          
          if ((sw)EncoderDPf < 0)
          {
            
            bx = (sw)EncoderDPf%_wgL360;              
            
            EncoderDPf = bx +_wgL360 ;         
          }
          
         EncoderDP = EncoderDPf;
       }
       else
       {
         EncoderDPf= EncoderDPr;
         EncoderDP = EncoderDPr;
       }
       
       
       
       deltDP =  ax ;
       deltDPr = deltDP ;
/*
       ax = deltDPr - deltDP ;

       //------ Определение величины скачка дельты -----------------------
     //  if ( (sw)ax <= (sw)_r.DT_ZISk && (sw)ax >= (sw)(~_r.DT_ZISk+1) )
     //  {
         
         excess_delt = 0 ;
     //  }
       


       if ( excess_delt == 0 )       // если нет отклонений
         {*/
           ax = EncoderDP ;
        // }


     //EncDP_old = EncoderDPr ;
       
       wgL_rn_old = wgL_rn ;

        // ограничение
         if ( (sw)ax > _wgL360 )
          {
            ax = _wgL360 ;
          }
         else  if ( (sw)ax < 0 )
          {
            ax = 0 ;
          }

        // введение смещения нуля
        ax += _r.Selsin[0].null ;

      //if (bi_Revers == 1)   ax += _or.KorLnazad ; DAN 21.04.2016 11:35

         if ( (sw)ax > _wgL360 )
          {
            ax -= _wgL360 ;
          }

        DProt = ax ;  // абсолютный угол положения ротора, нуль угла должно приниматься когда значение фазы А ротора наибольшее.

        wgL_rot = Pary_AD * DProt ;

       // if ( wgL_rot > _wgL360 )
       // {
          ax = wgL_rot%_wgL360 ;
          //ax = wgL_rot - ax * _wgL360 ;
      /*  }
        else
        {
          ax = wgL_rot ;
        }
*/

        wgL_dp = ax ;  // угол поворота ДП ротора c учетом смещения

        wgL_rn = wgL_dp * _Kadapt ;   // приведение значения ДП к масштабу электрических градусов

        //----- Вычислуние эл. угла напряжения статора -------
        if ( flgO._.VShunt1)
        {
          flgO._.VShunt1 = 0 ;
        }
        else
        {
          flgO._.VShunt1 = 1 ;
        }
        
        ax = Syn.NS2 ;

        if ( (sw)(ax - QueryTimeOk) > 0 )
        {
          bx = QueryTimeOk - Syn_NS2_old ;
        }
        else  bx = QueryTimeOk - ax ;           //  угол линейного напряжения статора

        lax = bx << 15 ;

        Lsety = lax / Tsyn ;

        if ( Lsety > _Grad( 360 ) )  Lsety -= _Grad( 360 ) ;

        //----- Электрический угол поворота ротора -------
        if ( (w)Lsety >= (w)wgL_rn )

          {
            ax = Lsety - wgL_rn  ;
          }
        else
          {
            ax = Lsety - wgL_rn + _Grad( 360 ) ;
          }
        /*
        if ((Lrot > ax) && ((Lrot -ax) > _Grad(180)))
        {
          Encf = ax;
          DPFiltr_drob = 0;
        }
        

          lax = ((lw)Encf << 16) + (lw)DPFiltr_drob ;
          
          ax  -=  Encf;
          
          lax += (slw)(sw)ax << ( 16 - _or.K_Enc_syn3f ) ;
          
          Encf = (sw)( lax >> 16 ) ;
          
          DPFiltr_drob = (w)lax ;
          
          ax = Encf;
*/

        if (Lrot_dp <= ax)
        {
          dLrot = (float)(ax - Lrot_dp);
        }
        else
        {
          bx = Lrot_dp - ax;
        
          if (bx < _Grad(180))
          {
            ax = Lrot_dp;
          }
          dLrot = (float)(_Grad(360) - Lrot_dp + ax );
        }
        asm_di();
        Time_DLRot = timer1;
        dLdT = dLrot/(float)deltTDP_old;

   Lrot_old = Lrot_dp ;
   Lrot_dp = ax ;   //  разница углов будет составлять угол Uab ротора
//   Lrot =  Lrot_dp;
   asm_ei();
//   if ( _or.CfgO._.Vedushiy )
//   {
//     Lrot = Lrot_dp;
//   }   
   if (Lrot_old > Lrot_dp)
   {
     float fax = (float)(u)((w)(Timer1_fSec - TimeFrot))/(float)_fSec(1);
     TimeFrot = Timer1_fSec;
     F_Lrot = 1/fax;

   }
   
   if (Frotf < Syn.Fsyn)
   {
     if ( CrossoverTEK() )       // был переход через ТЕК Uab
     {
       Define_NS2_rot6();      // определение NS2 для статора при 6-тикратной сихронизации
     }
     
     if ( (w)Lrot_old > (w)Lrot_dp )      // был переход через ноль угла Uab
     {
       Define_NS2_rot();    // определение NS2 для ротора
     }
   }
 /*       if (NS2_rot < NS2_rot_old)
        {
          Trg_Sled = 1;
          
        }
   if (Trg_Sled & Prg._.Sled)
   {
     if ((u)((w)(Timer1_fSec - TimeStopSled)) > _fSec(0.150))
     {
       Prg._.Sled = 0;
       Trg_Sled = 0;
     }
   }
   else
   {
     TimeStopSled = Timer1_fSec;
     Trg_Sled = 0;
   }*/
     //------- Расчет скорости вращения ротора по датчику положения ------

        // Noc = dDatPol / dT  ;

        fax = fabsf((float)(sw)deltDPr) ;
        fax /= (float)deltTDP_old;
        fax *= (float)_Secl(60)/(float)_wgL360;
        if (!isnormal(fax))
        {
          fax = 0;
        }
        //Скорость в оборотах в минуту
        Velos_f = fax;
        //Скорость в дискретах
        fax *= ((float)_Skor_Nom/(float)_sr.NOM.N.fe); 
        //ax = deltDP ;
        /*if ( (sw)ax < 0  )   ax = ~ax+1 ;

        lax = (lw)(w)ax * (lw)(w)_Enc_base_time ;
        ax = lax / deltTDP_old ;  // вычисляем модуль неотмасштабированной скорости . //deltTimDP - DAN: так в Каборге...
        //---

        lax = (lw)60000000 / (lw)(w)_wgL360  ;
        lax *= (lw)(w)_Skor_Nom ;
        lax = (lw)lax / (lw)(w)_sr.NOM.N.fe ;
*/
       //if ( (sw)deltDP < 0  )   ax = ~ax+1 ;
        //Само масштабирование сигнала по частоте
        // где F - неотмасштабированная скорость по частоте импульсов
        Ndpr = (w)fax;//( (lw)lax * (lw)(w)ax ) / (lw)( _Enc_base_time ) ;
      //Ndpr = ( (slw)lax * (slw)(sw)ax ) / (slw)( _Enc_base_time ) ;

        if ( (sw)deltDPr < 0  )   Ndpr = ~Ndpr+1 ;


  //    if ( _r.Sk_str._.EncodInv  == 1 )
  //      {
  //        Ndpr = ~Ndpr + 1 ;
  //      } DAN 09.06.2016 11:11 - Это лишнее, инвертирование сигнала с ДП уже было выше ... 

     //------- Расчет периода(частоты) напряжения ротора  ------

        // Tab_r = Tr * Ts / ( Tr - Ts ) ;  период напряжения ротора.
            //  Tr = dT * 360 / dWrm ;   период вращения ротора.

        // fab_r = fs - fr ;
        //  fr =  dWrm / (dT * 360) ;

        //deltwgL = deltDPr * Pary_AD * _Kadapt ;
       // deltwgL = deltDP * _Polus * _Kadapt ;
        deltwgL = (float)(slw)(sw)(deltDPr * Pary_AD * _Kadapt) ;
        
        fax = fabsf(deltwgL)/(float)_Grad(1);
        
        fbx = (float)deltTDP_old/(float)_Secl(1) ;
        
        fax /= (fbx*360.0);
        
       // ax = deltwgL ;

      //if ( ax != 0 )                                      // DAN: так в Каборге...
        //{                                                  // DAN: так в Каборге...
       //    if ( (sw)ax < 0 )   ax = ~ax+1 ;

            // ( 360UL / 360gr ) - сократили
            // _MkSec(1000) * 1000UL
/*
            lax = 10000UL * (lw)(w)ax ;

            lax =  lax / (lw)(w)deltTDP_old ; //deltTimDP - DAN: так в Каборге...

            lax =  lax  *  100UL ;

            Frot = lax  / (w)_Grad(1) ;
*/
            //----------  Фильтрация: вычисление отклонения текущего измеренного задания

            //fax = (float)Frot/360 ;
        Frot = fax;
            if ( _or.K_f_syn3f != 0 )   // включаем фильтр только при наличии уставки    // DAN: так в Каборге...
              {                                                                          // DAN: так в Каборге...
                //lax = ((lw)Frotf << 16) + (lw)Frotdrob ;

                fax -= Frotf ;
                fax = Frotf+ fax/((float)_or.K_f_syn3f*2);

//                lax += (slw)(sw)ax << ( 16 - _or.K_f_syn3f ) ;
//
//                ax = (sw)( lax >> 16 ) ;
//
//                Frotdrob = (w)lax ;
              }                                                                          // DAN: так в Каборге...
            Frotf = fax ;

            //---------------------------------------
            if (Frotf < Syn.Fsyn)
            {
              //Fsrot = Syn.Fsyn - Frot ;
              Fsrot = Syn.Fsyn - Frotf ;
              
              
              Tpp_f =(1/(2*Fsrot))*1e6;
              //частоту сети ротора переводим в период
             // lax = 1000000UL * 360UL ;
             // lax =  lax / (lw)(w)Fsrot >> 5 ;
              
              //if ( _r.Sk_str._.Po_T_NS2  == 0 )              // DAN: в Каборге такого нет...
              //  {
              Tpp_3syn = (lw)Tpp_f;//lax ;            // пол периода напряжения ротора
              //  }
              T_60gr = Tpp_3syn/3 ;
              
              T_syn = (lw)Tpp_f; 
            }
            //            if ( (sw)deltwgL < 0  ) //  если в режиме "Назад" двигат. поехал вперед
//                {
//                  DAN 16.06.2016 13:46 - Это было нужно при старой синхронизации 2 раза в период .
//                                           При синхронизации 6 раз в период этого не нужно ...
//                   Tpp_3syn =  T_NS2_rot / 2 ; 
//                }
        //}                                                  // DAN: так в Каборге...
        /*else      DAN 09.06.2016 8:38 - С этим при нулевой скорости сбивается ИУ...
          {                               Осталось от старой синхронизации 2 раза в период . Для 6-ти кратной - нужно переделывать ...
            Tpp_3syn = Hw( Syn.lTsyn ) >> 5 ;  // движок стоит - период ротора равен периоду статора
            Tsrot = Hw( Syn.lTsyn ) ;
            Trot = 0 ;
            Frot = 0 ;
            Fsrot = Syn.Fsyn ;
          }*/
          DAC0_output ( 1 ) ;  

         TimeDP_old = QueryTimeOk ;
         //QueryTimeOvrOk_old = QueryTimeOvrOk ;
    }

    return  ;
}

void  Define_NS2_rot(void)
{
   // word ax , bx ;
   // lword lax ;
    float fax;

    NS2_rot_old = NS2_rot ;
    fax = (float)(QueryTimeOk - TimeDP_old)* (float)(_Grad(360) - Lrot_old );
    fax /=(float)(Lrot_dp - Lrot_old + _Grad( 360 ));
    NS2_f = fax;
    
/*
    ax = (w)(QueryTimeOk - TimeDP_old)  ;
    bx = Lrot_dp - Lrot_old + _Grad( 360 ) ;

    lax = (lw)(w)() *  (lw)(w)ax ; // (lw)(w)bx ;
      ax = ( (lw)lax + (w)TimeDP_old * (lw)(w)bx ) / (lw)(w)bx ;
*/
    //lax = (lw)(w)(_Grad(360) - Lrot_old) *  (lw)(w)ax / (lw)(w)bx ;
    //ax = (w)lax + QueryTimeOvrOk_old ;

     //DAN 21.05.2016 16:36
  //if ( _or.CfgO._.One_NS2 == 0 || ( _or.CfgO._.One_NS2 == 1 && Usb.flg._.NewSyn == 0 ) )  // если СИФУ уже обработал прошлый синхроимпульс
    {
     asm_di();
   // mUSEL_not();
    NS2_rot = TimeDP_old + (lw)fax ;      // вычисленное NS2 по ДП ротора
     //-----------------------------------------------------------
      //TEK_Grs = TEK_Grad = 5 ;     // переход 360гр/0гр  - значит ТЕК превого тиристора
        TEK_Grs = TEK_Grad = 2 ;     // переход 360гр/0гр  - значит ТЕК превого тиристора
    flgO._.NewSyn = 1 ;
    //count_tir = 0 ; DAN 19.05.2016 10:52
     asm_ei();
    }
    dT_f0 = ((float)(NS2_rot - NS2_rot_old))/1e3;
    //T_NS2_rot = NS2_rot - NS2_rot_old ; DAN   Это было для синхронизации раз в период
    T_NS2_rot = (NS2_rot - NS2_rot_old) * 6 ;

    return  ;
}

void Define_NS2_rot6(void)
{
 // word ax, bx;
 // lword lax;
  float fax, fbx, fcx;
  
    NS2_rot_old = NS2_rot ;
      
  //    ax = (w)(QueryTimeOvrOk - QueryTimeOvrOk_old)  ;

    if (Lrot_dp >= Lrot_old)
    {
      fbx = (float)(Lrot_dp - Lrot_old) ;  //+ _Grad( 360 ) ;
      fcx = (float)(GradTek - Lrot_old) ;
    }
    else
    {
       fbx = (float)(Lrot_dp - Lrot_old + _Grad( 360 )) ;
       fcx = (float)(GradTek - Lrot_old + _Grad( 360 )) ;
    }   

    
    fax = (float)(QueryTimeOk - TimeDP_old)* fcx;
    fax /= fbx;
      NS2_f1 = fax;  
//      lax = (lw)(w)(GradTek - Lrot_old) *  (lw)(w)ax ;
//      ax = ( (lw)lax + (lw)QueryTimeOvrOk_old * (lw)(w)bx ) / (lw)(w)bx ;
      
      //DAN 21.05.2016 16:36
      //if ( _or.CfgO._.One_NS2 == 0 || ( _or.CfgO._.One_NS2 == 1 && Usb.flg._.NewSyn == 0 ) )  // если СИФУ уже обработал прошлый синхроимпульс
      {
        asm_di();
       // mUSEL_not();
        NS2_rot = TimeDP_old + (lw)fax ;      // вычисленное NS2 по ДП ротора
        //-----------------------------------------------------------
        TEK_Grs = TEK_Grad ;
        
        flgO._.NewSyn = 1 ;
        //count_tir++ ;
        asm_ei();
      }
    
    dT_f0 = ((float)(NS2_rot - NS2_rot_old))/1e3;
    T_NS2_rot = (NS2_rot - NS2_rot_old) * 6 ;    

    return  ;
}


byte CrossoverTEK(void)                 // проверка перехода угла через ТЕК
{
   if ( (w)Lrot_old < _Grad( 60 ) &&  (w)Lrot_dp >= _Grad( 60 ))
   {
     GradTek = _Grad( 60 ) ;
     //TEK_Grad = 6 ;
       TEK_Grad = 3 ;
     return 1 ;
   }
   else if ( (w)Lrot_old < _Grad( 120 ) &&  (w)Lrot_dp >= _Grad( 120 ))
   {
     GradTek = _Grad( 120 ) ;
     //TEK_Grad = 1 ;
       TEK_Grad = 4 ;
       
     return 1 ;
   }
   else if ( (w)Lrot_old < _Grad( 180 ) &&  (w)Lrot_dp >= _Grad( 180 ))
   {
     GradTek = _Grad( 180 ) ;
     //TEK_Grad = 2 ;
       TEK_Grad = 5 ;
     return 1 ;
   }
   else if ( (w)Lrot_old < _Grad( 240 ) &&  (w)Lrot_dp >= _Grad( 240 ))
   {
     GradTek = _Grad( 240 ) ;
     //TEK_Grad = 3 ;
       TEK_Grad = 6 ;
     return 1 ;
   }
   else if ( (w)Lrot_old < _Grad( 300 ) &&  (w)Lrot_dp >= _Grad( 300 ))
   {
     GradTek = _Grad( 300 ) ;
     //TEK_Grad = 4 ;
       TEK_Grad = 1 ;
     return 1 ;
   }
   else
   {
     return 0 ;
   }

}

/*--------------------------------------------------*/

// Функция фильтра скорости , вызывается независимо от того , включен ли фильтр
// для индикации нефильтрованной и отфильтрованной скоростей .

word Filtr_Sk ( word num )
{
    word ax , dx ;
    sword  cx ;
    slword  lax;

 switch ( num )
  {
   case 0 : // инициализация .
    Kf_Sk = _r.K_fil_sk ;
    if ( Kf_Sk <= 1 )  Kf_Sk = 2 ;
    drob_FSk = 0 ;
    Skor_f = 0 ;
   break ;

   case 1 :
//if ( new_izm_pdf == 1 ) //вызывается раз в 10ms
 //{
    cx = Skor - Skor_f ; //разность скорости между измеренной и отфильтрованной
    dx = cx ;  //сохранение разности

    //смещение на 16 бит влево для получения в дальнейшем числа с дробной частью
    lax = ( (slw)(sw)cx << 16 );

    ax = Kf_Sk ;
    lax /= (slw)(sw)ax ; // деление на текущий коэффициент фильтрации

    // добавление к результату дробной части, оставшейся в прошлом вычислении
    lax += (lw)(w)drob_FSk ;
    drob_FSk = (w)lax ;  //сохранение текущей дробной части для след-го вычисл-ия

    cx = (slw)lax >> 16 ; //смещение на 16 бит вправо для получения челой части
    Skor_f += cx ;    //добавление к выходу фильтра  целой части от деления.


         //---  определение коэффициента фильтрации

    // если разность выше уставочного порога
    if ( (sw)dx >= (sw)_r.porog_fil || (sw)dx <= (sw)( ~_r.porog_fil + 1 ) )
      {
        // если разность на прошлом шаге была другого знака -
        // - коэффициент фильтрации не уменьшается
        cx = Skor - Skor_f ;
        if ( ( (sw)cx < 0 && (sw)Delt_n > 0 )
                          ||
             ( (sw)cx > 0 && (sw)Delt_n < 0 ) )
          {
            dfgg++ ;
            goto sz ;
          }
        ax = ax / 2 ; // деление КF_sk на два.
        if ( ax <= 1 )  ax = 2 ;
      }
    else  // если разность не вылезла за порог
      {
        sz:
        ax = ax * 2 ; // умножение КF_sk на два.
        if ( ax > _r.K_fil_sk )   ax = _r.K_fil_sk ;  // ограничение КF_sk.
      }

    //сохранение данных.
    Kf_Sk = ax ;
    Delt_n = dx ;
 //}

    //Skor = Skor_f ; // 24.01.07 09:45 - если фильтр включен .
   break ;
  }
    return 0 ;
}
void  DAC_pOutput ( void )
{  
  DAC2_output ( 1 ) ;
  DAC3_output ( 1 ) ;
  return   ;
}

//------------------------------------------
//Программа линеаризации

word Linear (word in)
{
  register word  ax , bx , cx ;
  
  if ( in <= _Ugol_90 )  ax = in ;
  else                   ax = _Ugol_180 - in ;
  bx  = LIN [ ax >> 8 ] ;
  cx  = LIN [(ax >> 8) + 1 ] ;
  cx -= bx ;
  bx += (w)( (lw)cx * (lw)(ax & 0x00FFu) / 0x0100ul ) ;
  if ( in <= _Ugol_90 ) return bx;
  else                  return _Ugol_180 - bx ;
  
}
