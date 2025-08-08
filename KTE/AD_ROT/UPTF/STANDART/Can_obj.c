
word can_ConfigReg ( word code )
{
/*register*/ word ax, dx;
#ifndef _F16e

   word  bx;

#endif
  static word time_connect, time2_connect, TimeClrMsg ;
  static byte trigg_connect ;
  dx = 0 ;

      // Задан ли режим управления по CAN.
      // пропускаем инициализацию и измерения аналоговых каналов :
  if ( (code != _CAN_Init) && (code != _CAN_Obmen) )
    {
      if ( _r.Cfg._.CAN_reg == 0 || Isp.all != 0 ) return dx ;
    }

  switch ( code )
  {
            // Начальная инициализация.
    case _CAN_Init :

         canr.Data.all   = 0 ;          // Для сброса после выдержки времени "мигающего" по
         TimeClrMsg      = Timer1_Ovr ; // старту контроля наличия связи с Верхним уровнем .

           //  Инициализация дополнительных переменных.
         Status_KTE = 0 ;
  reinit:
         //---------------------
           // Инициализация переменных управления КТЭ по CAN.

         canr.CfgReg.all &= _creg_Connect ;// чтобы не изменять Connect
           if ( bi_canConnect == 1 ) trigg_connect = 1 ;// при отсутствии связи и не
           else                      trigg_connect = 0 ;// создавать видимость ее появления.
         //---
         canr.StatReg.all= 0 ;
         bo_canConnect   = 1 ;
         canr.Data.all  &= _dreg_ClrMsg ;// 22.04.2008 - чтобы не изменять флаг сброса сообщения .
         canr.S_zad      = 0 ;
         canr.N_zad      = 0 ;

         //vmz_29012019 - как в Ингульце
         //canr.Id_zad     = 0 ;

         ax = _Id_Nom *10;
         canr.Temp_Zad = ax/_r.T_ZISkorP_Razg;
         canr.dId_zad    = 0 ;
         canr.Ug_zad     = 0 ;
#ifndef _KTE_GD
         //vmz_29012019 - как в Ингульце
         //canr.Idz_MaxP = _Id_nom(+3.0), canr.Idz_MaxM = _Id_nom(-3.0) ;
         canr.Idz_MaxP = _Id_nom(+5.0), canr.Idz_MaxM = _Id_nom(-5.0) ;
#else
         canr.Idz_MaxP = _Ig_nom(+3.0), canr.Idz_MaxM = _Ig_nom(-3.0) ;
#endif
         canr.F_zad      = _Fv_Nom ;

         //vmz_31012019 - как в Ингульце
         //canr.L_zad      = _r.S_Alfa_Max,  canr.L_min = _Grad( 0.0 ) ;//_r.S_Alfa_Min ;

         for ( ax = 0 ; ax < _Ai_max ; ax++ )  canr.Ai[ax] = 0 ;
         for ( ax = 0 ; ax < _Ao_max ; ax++ )  canr.Ao[ax] = 0 ;

       break;
         //-------------

            // Переинициализация по дист.сбросу.
    case _CAN_DS1_Init :  // переинициализация если связь оборвалась.
           if ( canr.Data._.Connect == 0 )  goto reinit ;
       break;
         //-------------

           //  Включение/Отключение последнего коммутационного аппарата .
    case _CAN_QK :

//vmz_29012019
/*
         if    ( _r.Cfg._.CAN_QK == 0  ) dx = 0 ; // Нет CAN-управления QK .
         else
          {
            if ( bi_canQK == 1 ) dx = 1 ; // включить QK .
            else
             {
               dx = 2 ; // отключить QK .
               mSet_ServiceMsg( _Srv_NoCAN_QK ) ; // очистка в AVAR.C .
             }
      #ifdef bi_QK1_Mestnoe
            if ( bi_QK1Mestnoe == 1 ) dx = 0 ; // блокировка CAN-Управления QK .
      #endif
          }
*/
            if (bi_canStart ) // Если Ведущий вошел в Работу ( bo_canRabota перекладывается в bi_canStart ) :
            {
              dx = 0;
            }
            else
            {
               dx = 2;
            }

       break;
         //-------------

           //  Задание на положение.
    case _CAN_S_Zad :
        #ifdef _REG_POL
         if ( bi_canS_zad == 1 ) ZUgol = canr.S_zad, dx = 1 ;
        #endif
       break;
         //-------------

           //  Задание на скорость.
    case _CAN_N_Zad :
         if ( bi_canN_zad == 1 ) Z_Skor = canr.N_zad, dx = 1 ;
       break;
         //-------------

            // Задание на скорость после ЗИ.
    case _CAN_N_Zad_R :

       // В случае необходимости , проверить полученное Объектное Задание
       // Скорости на превышение ограничений ( раскоментировать dx ) .
       // dx = 1 ;

       //vmz_29012019
       ZISkor = canr.N_zad;
       dx = 1 ;

       break;
         //-------------

            //  Задание на ток якоря и добавка к заданию.
    case _CAN_Id_Zad :

//vmz_29012019 - как в Ингульце
/*
         if ( bi_canId_zad == 1 )
         {
#ifndef  _WM591
          // if ( canr.Data._.Connect == 1 )
          //{
              OuRegS_dop_kod = canr.Id_zad, dx = 1 ;
          // }
          // else
          // {    // снимаем задание тока якоря. -- заменили на обнуление
            // bi_canId_zad = 0, OuRegS_dop_kod = 0 ; "bi_canStart".
          // }
           OuIchRS = 0 ; // сбрасываем интегратор вышестоящего регулятора.
#else

          if ( canr.Data._.Connect == 1 )
          {
           dx = 1 ;

           bo_Neg_curr = bi_canRecup;

           OuRegS_dop_kod = canr.Id_zad;

           time_razg =  canr.Temp_Zad;
          }
#endif
         }
         //---
              // Коррекция задания на ток
         //OuRegS_dop_kod += canr.dId_zad ; 25.10.06 11:51 перенесено ниже для
               // моталки. Если надо будет и здесь тогда добавим сюда вторую добавку.
*/
       break;
         //-------------

            //  Ограничение тока.
    case _CAN_Id_Zad_Ogr :

//vmz_29012019 - как в Ингульце
/*
           if ( (sw)OuRegS_dop_kod > (sw)canr.Idz_MaxP ) // Ограничение тока
             {
               OuRegS_dop_kod = canr.Idz_MaxP, Prz._.int_p = 1 ;
             }
           else if ( (sw)OuRegS_dop_kod < (sw)canr.Idz_MaxM )
             {
               OuRegS_dop_kod = canr.Idz_MaxM, Prz._.int_m = 1 ;
             }
              // Коррекция задания на ток.  - Vit 25.10.06 11:49
           OuRegS_dop_kod += canr.dId_zad ;// перенесено сюда для моталки: для
                      // нее нужно сначала огр.РС, а затем к огр.добавл.добавку.
*/

       break;
         //-------------

//vmz_29012019
/*            // Выполнение перед реверсом.
    case _CAN_Revers :
       // dх = 1 ; // чтобы не дать среверсироваться.
       break;
         //-------------

            //  Задание на ток возбуждения.
    case _CAN_Iv_Zad :
       break;
*/
        case _CAN_P01  :
            if ( bi_canStart && bi_canP01)
            {
                dx = 1;

            }
        break;
            //-------------

                //  Задание на ток возбуждения.
        case _CAN_P10 :
            if ( bi_canStart && bi_canP10)
            {
                dx = 1;

            }

        break;

         //-------------
            //  Вход/выход из Останова.
    case _CAN_Ostanov :
#ifndef _WM591
           //---
           // При отсуствии меандра CAN-Connect ( связи нет ) :
          if (  canr.Data._.Connect == 0 )  // переинициализацию не делаем для Следа,
          {    // и для Connect, т.к. он обнулится и сист.подумает, что появилась связь.
            bi_canStart = 0 ;  // просто останавливаемся, без Аварии,
            mClr_ServiceMsg( _Srv_NoCAN_Start ) ; // Связи нет - и хватит сообщений .

            //vmz_29012019 - как в Ингульце
            //mSet_ServiceMsg( _Srv_NoCAN_Connect ) ;// чтобы не было неудобств с

            dx = 1 ;     // развалившимися QK при перезапуске верхнего уровня.
          }
           // При наличии меандра CAN-Connect ( связь есть ) :
          else
          {
            // В Сборке Готовности стираем старое сообщение об Отсутствии Связи :
            // В Сборке Готовности НЕ ВЫДАЕМ на всякий случай сообщ. "Нет CAN-Старт".
            if ( Prg._.Gotovn == 1 )
             { // Только если нет CAN-управления ЛК , СТИРАЕМ СТАРОЕ
               // сообщение об Отсутствии Связи , чтобы при пропаже Связи и
               // последующем отключении ЛК было видно , что ЛК пропал из-за
               // обрыва связи :
               if ( _r.Cfg._.CAN_QK == 0 ) mClr_ServiceMsg( _Srv_NoCAN_Connect ) ;
               //---
               // По старту , после выдержки времени , "мигающий" контроль наличия связи с
               // Верхним уровнем должен устаканится - ТОЛЛЬКО тогда сбрасываем сообщение
               // об отсуствии связи . Дальнейшие обрывы связи фиксируем .
               else if ( canr.Data._.ClrMsg == 0 )
                {
                  if ( (u)((w)(Timer1_Ovr - TimeClrMsg)) > _Sec(5.0) )
                   {
                     canr.Data._.ClrMsg = 1 ;
                     mClr_ServiceMsg( _Srv_NoCAN_Connect ) ;
                   }
                }
             }
               // В Работе старое сообщение об Отсутствии Связи не стирается .
            else
             { // В Работе и выдаем и стираем сообщ. "Нет CAN-Старт".
              if ( bi_canStart == 0 )
              {
                mSet_ServiceMsg( _Srv_NoCAN_Start ) ;
                dx = 1 ;
              }
              else mClr_ServiceMsg( _Srv_NoCAN_Start ) ;
             }
          }
#else

          if (  canr.Data._.Connect == 0 )  // переинициализацию не делаем для Следа,
          {    // и для Connect, т.к. он обнулится и сист.подумает, что появилась связь.
            dx = 0;
            mSet_ServiceMsg( _Srv_NoCAN_Connect ) ;// чтобы не было неудобств с
          }              // развалившимися QK при перезапуске верхнего уровня.
          else
          {
            dx = 1 ;
            if ( Prg._.Gotovn == 1 )  mClr_ServiceMsg( _Srv_NoCAN_Connect ) ;
            bo_Start = bi_canStart;
            bo_Stop  = bi_canStop ;
          }

#endif
       break;
         //-------------
         // Управляем мех.торм. по CAN если отключено его упр. от КТЭ.
    case _CAN_MT :

//vmz_29012019 - как в Ингульце
/*
                // Проверяем наличие CAN-команды 'MT'.
            //if ( _r.Cfg._.MT == 0 )
            //{
              // Команда наложить МТ , возвращаем код "1" :
              if ( bi_canMT == 0 ) bo_MT = 0, dx = 1 ;
              else // команда снять МТ :
              {   // связь есть , растормаживаемся , возвращаем код "2" :
                if ( canr.Data._.Connect == 1 )   bo_MT = 1, dx = 2 ;
                  // связи нет , снимаем команду растормаживания , код "1" :
                else  bi_canMT = 0, bo_MT = 0 , dx = 1 ;
              }
            //}
*/
       break;
         //-------------
    case _CAN_Avar :    // Проверяем наличие CAN-команды 'Аварийное отключение'.
            if ( bi_canAvar == 1 )
            {
              mSet_AvarMsg( _Av_CAN_avar ) ;
              dx = 1 ;
            }
            else if ( bi_canPredupr == 1 )
            {
              mSet_PreduprMsg( _Pr_CAN_predupr ) ;
              dx = 2 ;
            }
       break;
         //-------------
    case _CAN_Obmen :
            // ПЕРЕНЕСЕНО ИЗ НАЧАЛА ФУНКЦИИ, ЧТОБЫ НЕ БЫЛО НАКЛАДОК С ВЫЗОВОМ
            // ЭТОЙ ФУНКЦИИ И ИЗ ФОНА И ИЗ ПРЕРЫВАНИЯ СИФУ.
            //   Проверяем наличие связи и запускаем выдержку на снятие задания
            // тока якоря в режиме его задания.
            // Признак наличия связи приходит как меандр 0.5сек.
          if ( trigg_connect != bi_canConnect )
          {
            if ( trigg_connect == 0 )  trigg_connect = 1 ;
            else                       trigg_connect = 0 ;
            time_connect = Timer1_Ovr ;
            canr.Data._.Connect = 1 ;
          }
          if ( (u)((w)(Timer1_Ovr-time_connect)) > _r.T_Connect_cfg )
          {
            canr.Data._.Connect = 0 ;
            canr.N_zad   = 0 ;  // 23.08.06 09:56

            //vmz_29012019 - как в Ингульце
            //canr.Id_zad  = 0 ;

            ax = _Id_Nom *10;
            canr.Temp_Zad = ax/_r.T_ZISkorP_Razg;
            canr.dId_zad = 0 ;
            canr.Ug_zad  = 0 ;
            //vmz_29012019 - как в Ингульце
            //canr.L_zad   = _r.S_Alfa_Max ;
          }
          //-----------
          //     Формирование ответного Connect.
          if ( _r.T_Connect_sts != 0 ) // Штатное формир. ответного Connect ,
          {                            // если задана уставка меандра статуса .
            if ( (u)((w)(Timer1_Ovr-time2_connect)) >= _r.T_Connect_sts )
            {
              bo_canConnect = !bo_canConnect ;
              time2_connect = Timer1_Ovr ;
            }
          }
          else // Для проверки времени сетевого обмена обнулить время меандра :
          {
            if      ( bi_canConnect == 0 ) bo_canConnect = 0 ;
            else if ( bi_canConnect == 1 ) bo_canConnect = 1 ;
          }
          //-----------
         // Считываем заданные аналоговые каналы для выдачи в CAN.
#ifndef _F16e
          for ( ax = 0 ; ax < _Ai_max ; ax++ )
          {
            if ( _or.Ai_CS[ax] != 0xff )
            {
                // ложим в bx , чтобы прерывание не использовало _AD_BUSY как значение
              bx = _AD_BUSY;
                // преобразуем номер канала из десятичного вида в требуемый.
                /*    Измерение  */
              AD_Izm ( *Nstx[_or.Ai_CS[ax]].ach , &bx ) ;
                /*    АЦП запущен, ожидаем...
                 */
              while ( bx == _AD_BUSY );
                //Преобразование измеренного напряжения.
              mIzmData_Conversion ( bx, bx, *Nstx[_or.Ai_CS[ax]].ach ) ;
              canr.Ai[ax] = bx ;
            }
          }
#endif
          //----------------
          // Формирование слова состояния cStsR и Статуса для диагностики :
          if ( bo_Avar == 1 )    bo_canAvar = 1 ;
          else                   bo_canAvar = 0 ;
          if ( bo_Predupr == 1 ) bo_canPredupr = 1 ;
          else                   bo_canPredupr = 0 ;

          //vmz_29012019
          //if ( bo_Gotov == 1 )   bo_canGotovQK = 1 ;
          if ( bo_Gotov == 1 && _r.Cfg._.CAN_reg == 1 && _r.Cfg._.CAN_QK == 1 )
              {
              bo_canGotovQK = 1 ;
              }

          else                   bo_canGotovQK = 0 ;
          //---
          if ( bi_QK1 == 0 )     bo_canStateQK = 0 ;
          else                   bo_canStateQK = 1 ;
          //---
//vmz_29012019 - как в Ингульце
/*
          if ( bo_MT == 0 )      bo_canMT = 0 ;
          else                   bo_canMT = 1 ;
          //---
          if      ( S.NumMost == 1 ) bo_canMost = 0 ;
          else if ( S.NumMost == 2 ) bo_canMost = 1 ;
*/
          //---
          if ( bi_KTE_rezerv != 0 ) // Агрегат Резервный
          {
            ax = _stat_Reserve ;
            bo_canKTE_Rezerv = 1 ;
          }
          else // Агрегат Рабочий
          {
            bo_canKTE_Rezerv = 0 ;
            if ( Prg._.Gotovn == 1 ) // Агрегат в Режиме "Сборка Готовности"
            {
              if ( bo_Gotov == 0 ) ax = _stat_NotReady ;
              else                 ax = _stat_Ready ;
            }
            else // Агрегат в Режиме "Работа"
            {
              if ( bo_Avar  == 1 )     ax = _stat_Avar ;
              else
              {
                if ( bo_Predupr == 0 ) ax = _stat_Work ;
                else                   ax = _stat_Work_Predupr ;
              }
            }
          }
          Status_KTE = ax ;

         //vmz_31012019 - взял из Sts_KTE Ингульца
         if ( Prg._.Gotovn ==  0 &&  bo_Avar == 0 )  bo_canRabota = 1 ;
         else                                        bo_canRabota = 0 ;

         if ( bi_Pusk_0_1)
         {
             bo_canP01  = 1;
         }
         else bo_canP01  = 0;

         if ( bi_Pusk_1_0)
         {
             bo_canP10  = 1;
         }
         else bo_canP10  = 0;

       break;
         //-------------
            //  Ограничение минимального угла управления.
    case _CAN_Alfa_Min :

//vmz_29012019 - как в Ингульце
/*
         if ( S.Alfa < canr.L_min )
           {
             S.Alfa = canr.L_min ;
             S.flg._.Fmin = 1;
           }
*/
       break;
         //-------------
            //  Задание на угол управления.
    case _CAN_Alfa_Zad :

//vmz_29012019 - как в Ингульце
/*
         if ( bi_canL_zad == 1 )
         {
          dx = 1 ;  // ответ для внешнего выключения РТ.
          S.Alfa = canr.L_zad ;
          OuIchRS = 0 ; // сбрасываем интегратор вышестоящего регулятора.
    #ifndef _KTE_GD
          OIRT  = _r.RevU0  ;  // интегратор регулятора тока //
          OIRT1 = _r.RevU0  ;  // интегратор регулятора тока //
        #ifdef _SIFU2_
           OIRT_2_  = _r.RevU0  ;  // интегратор регулятора тока //
           OIRT1_2_ = _r.RevU0  ;  // интегратор регулятора тока //
        #endif
    #else
          OIRT  = 0 ;  // интегратор регулятора тока //
          Integr_rn = 0 ;
          Integr_rn_drob = 0 ;
    #endif
          // Проверка необходимости реверса в реверсе не нужна , иначе угол после реверса
          if ( stop_pointR1 == 1 ) break; // забросит в Lmax , откуда он будет долго выползать ,
          // вместо того , чтобы после смены моста сразу выйти с нужным углом .

              // Проверка необходимости реверса.
          if ((( S.NumMost == 1 ) && ( bi_canMost  == 1 ))
                                  ||
              (( S.NumMost == 2 ) && ( bi_canMost  == 0 )))
              {
                 S.Alfa = _r.S_Alfa_Max ;
                 S.flg._.Revers = 1 ;
              }
          else
              {
                  // признак реверса был, но снялся.
                S.flg._.Revers = 0 ;
                S.flg._.ZapretImp = 0 ;
              }
          }
*/
       break;
         //-------------
            //  Задание на напряжение генератора.
    case _CAN_Ug_Zad :

//vmz_29012019 - как в Ингульце
/*
        if ( bi_canUg_zad == 1 )
        {
          ORT = canr.Ug_zad, dx = 1 ;
          OuIchRS = 0 ; // сбрасываем интегратор вышестоящего регулятора.
    #ifndef _KTE_GD
          OIRT  = _r.RevU0  ;  // интегратор регулятора тока //
          OIRT1 = _r.RevU0  ;  // интегратор регулятора тока //
    #else
          OIRT  = 0 ;  // интегратор регулятора тока //
    #endif
        }
*/
       break;

         //-------------
//vmz_29012019 - как в Ингульце
/*
    case _CAN_DistSbros :    // Проверяем наличие CAN-команды 'Сброс защит'.
            if ( bi_canDistSbros == 1 )
              {
                 Av._.DistSbros = 1 ; // Для совместимости со стандартными программами .
                 dx = 1 ;
              }
       break;
*/
         //-------------
  }

  return dx ;
}
/*
   Status_KTE =:
  - в резерве;
  - в готовности: автомат еще не включен, есть Готовность;
  - в готовности: автомат еще не включен, нет Готовности;
  - в работе: автомат включен, предупреждений нет;
  - в работе: автомат включен, предупреждения есть;
  - в послеаварийном состоянии.
 */

word  can_obj ( word code )
{
  code = code ;// чтобы не было предупр. о неиспользовании "code"

  //if ( tst_can_stop(_WorkSlaveCANPort) == 1 )  return 1 ;

  //----------------------------------------------

  return 0 ;
}

/*
//vmz_31012019
void  Sts_KTE ( void )
  {

    if ( Prg._.Gotovn ==  0 &&  bo_Avar == 0 )  bo_canRabota = 1 ;
    else                                        bo_canRabota = 0 ;

    if ( bi_Pusk_0_1)
    {
        bo_canP01  = 1;
    }
    else bo_canP01  = 0;

    if ( bi_Pusk_1_0)
    {
        bo_canP10  = 1;
    }
    else bo_canP10  = 0;

//vmz_31012019 - было для внутренней связи ?
//
//    if ( KTE2_Avar == 0 )    // выдавать в АР1 аварию только если АР1 находится еще в работе
//    {
//     if ( bo_Avar == 1 )    bo_canAvar = 1 ;
//     else                   bo_canAvar = 0 ;
//    }
//
    //if ( bi_KF1 == 0 || bi_KF2 == 0 )  bo_canAvar = 1 ;  //  в сборке готовности тоже выдавать в АР1
    //vmz_31012019 - а может так ? : - это уже есть в Obmen
    // if ( bo_Avar == 1 )    bo_canAvar = 1 ;
    // else                   bo_canAvar = 0 ;

    return ;
  }
*/


