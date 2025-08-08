/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/
//    ПРОГРАММА НАСТРОЙКИ ПАРАМЕТРОВ ДЛЯ ПРОГРАММЫ ЦИКЛИЧЕСКИ-
//  СТУПЕНЧАТОГО ФОРМИРОВАНИЯ ЗАДАНИЯ ДЛЯ РАЗЛИЧНЫХ СТРУКТУР РАБОЧИХ
//                       ПРОГРАММ .
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/

#define  _Tnom  300

void   Vybor_Isp ( void )
{
   register byte  bh ;
   register word    ax , bx , cx ;

   // ВНИМАНИЕ! Порядковый номер метки указывается в таблице Vybor Vyb [] в MSG_TABL.H :
   enum { k0, k1, k2,
          k10, k11, k12, k13, k14, k15, k16, k17, // СИФУМ1 , СИФУМ2 , ФП , РНг-рез , СИФУВ-рез , Штатный Режим .
          k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, // Циклы .
          k40, k41 ,                                        // Циклы .
          k50, k51 ,                                        // Циклы .
          k60a, k60, k61, k62, k63, k64, k65, k66 ,         // Автонастройка .
          k67, k68, k69, k70 ,                              // Наработка .
          k71, k72, k73, k74, k75, k76, k77,                // Нуль сельсинов .
          k80, k85, k90, k95                                // РТ1-рез , РТ2-рез для 12-пульсной схемы .
           , k96 // Для функции Фазировка моста в "Наладке" 18.05.2020*/
        } ;


              //  Контроль пароля: Полный запрет входа.

      if ( Password_control ( 2 ) == 0 )  return   ;
              //---


      if ( M_FirstCall == 1 )  /*  Идентификация первого входа для задания  */
        {                      /* начального условия ...                    */
          M_FirstCall = 0 ;
          Label = k0 ;
          return ;
        }

  switch ( Label )
    {
      case k0:
              output_s ( _F2_prompt_txt"\n\r" ) ;
              m_index = F2regim ;
              Label = k1 ;
      case k1:  // Ожидание завершения предыдущего вывода.
              if ( TestCompleted_Output() )
                {
                  output_s ( Vyb[ m_index ].txt ) ;
                  Label = k2 ;
                  break ;
                }
      case k2:  if ( TestData_for_Input() ) // 30.07.2020 Здесь был "while" .
                {
                  mInput_c ( bh ) ;
                  if ( bh == Return )
                    {
                end:  Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                      return ;   // добавить еще какую-то иниц.
                    }
                  else if ( bh == Down ) /* Выбрать номер порта.*/
                    {
                      if ( ++m_index >= _Nvyb ) m_index = 0 ;
                      Label = k1 ;
                    }
                  else if ( bh == Up ) /* Выбрать номер порта.*/
                    {
                      if ( m_index-- == 0 ) m_index = _Nvyb - 1 ;
                      Label = k1 ;
                    }    /* переход к следующей настройке */
                  else if ( bh == Enter )
                    {
                    // Выбор наладочных режимов допускается из "Сб.Готовности" .
                    // В "ЦИКЛЫ" ( порядковый номер метки 11 ) можно входить
                    // в "Работе" , но при условии , что они уже были заданы в
                    // "Сборке Готовности" .
                      if ( Prg._.Gotovn == 0 &&
                          (Vyb[ m_index ].label != 11 || Ckl.all == 0) )
                       {
                     xx: output_s ( _Dostup_Gotovn_txt ) ;
                         Label = k51 ;
                         m_time = Timer1_Ovr ;
                       }
                      else
                       {
                         Label = Vyb[ m_index ].label ;
                         F2regim = (b)m_index ;
                       }
                    }
                  else  Klav_Buff = bh;
                }
              break ;
            //-------------------
            //              СИФУ-Рез , М-Вперёд :
      case k10:
              Isp.all &= _ZI_shunt , Isp._.SIFU_Res = 1 ; //Isp.all = 0 , DAN - Не обнуляем шунтирование ЗИТ и ЗИС .
              Isp._.NumMost = 0 ;  //  S.NumMost = 1 ;
              Label = k50 ;
              m_time = Timer1_Ovr ;
              break ;
            //-------------------
            //              СИФУ-Рез , М-Назад :
      case k11:
              Isp.all &= _ZI_shunt , Isp._.SIFU_Res = 1 ; //Isp.all = 0 , DAN - Не обнуляем шунтирование ЗИТ и ЗИС .
              Isp._.NumMost = 1 ;  //  S.NumMost = 2 ;
              Label = k50 ;
              m_time = Timer1_Ovr ;
              break ;
            //-------------------
            //              РТ-Рез , М-Вперёд :
      case k12:
              Isp.all &= _ZI_shunt , Isp._.RT_Res = 1 ;   //Isp.all = 0 , DAN - Не обнуляем шунтирование ЗИТ и ЗИС .
              Isp._.NumMost = 0 ;  //  S.NumMost = 1 ;
              Label = k50 ;
              m_time = Timer1_Ovr ;
              break ;
            //-------------------
            //              РТ-Рез , М-Назад :
      case k13:
              Isp.all &= _ZI_shunt , Isp._.RT_Res = 1 ;   //Isp.all = 0 , DAN - Не обнуляем шунтирование ЗИТ и ЗИС .
              Isp._.NumMost = 1 ;  //  S.NumMost = 2 ;
              Label = k50 ;
              m_time = Timer1_Ovr ;
              break ;
            //-------------------
            //              РТ1-Рез , М-Вперёд :
      case k80:
              Isp.all &= _ZI_shunt , Isp._.RT1_Res = 1 ;   //Isp.all = 0 , DAN - Не обнуляем шунтирование ЗИТ и ЗИС .
              Isp._.NumMost = 0 ;  //  S.NumMost = 1 ;
              Label = k50 ;
              m_time = Timer1_Ovr ;
              break ;
            //-------------------
            //              РТ1-Рез , М-Назад :
      case k85:
              Isp.all &= _ZI_shunt , Isp._.RT1_Res = 1 ;   //Isp.all = 0 , DAN - Не обнуляем шунтирование ЗИТ и ЗИС .
              Isp._.NumMost = 1 ;  //  S.NumMost = 2 ;
              Label = k50 ;
              m_time = Timer1_Ovr ;
              break ;
            //-------------------
            //              РТ2-Рез , М-Вперёд :
      case k90:
              Isp.all &= _ZI_shunt , Isp._.RT2_Res = 1 ;   //Isp.all = 0 , DAN - Не обнуляем шунтирование ЗИТ и ЗИС .
              Isp._.NumMost = 0 ;  //  S.NumMost = 1 ;
              Label = k50 ;
              m_time = Timer1_Ovr ;
              break ;
            //-------------------
            //              РТ2-Рез , М-Назад :
      case k95:
              Isp.all &= _ZI_shunt , Isp._.RT2_Res = 1 ;   //Isp.all = 0 , DAN - Не обнуляем шунтирование ЗИТ и ЗИС .
              Isp._.NumMost = 1 ;  //  S.NumMost = 2 ;
              Label = k50 ;
              m_time = Timer1_Ovr ;
              break ;
      case k96:
              if( Av._.Ostanov == 1 ) break;  //18.05.2020
              Fazirovka() ;
              break;
            //-------------------
            //              САМОНАСТРОЙКА ФП :
      case k14:
              if ( _r.Sk_str._.TG != 1 && _r.Sk_str._.PDF != 1 )
                {
                  output_s ( _Not_Selected_DS_txt ) ;
                  Label = k51 ;
                }
              else
                {
                  Isp.all &= _ZI_shunt , Isp._.Samonastr = 1 ; //Isp.all = 0 , DAN - Не обнуляем шунтирование ЗИТ и ЗИС .
                    // для последующего контроля в Init_posle_DistSbr.
                  zeds = 0 ;
                  Label = k50 ;
                }
              m_time = Timer1_Ovr ;
              break ;
            //-------------------
            //              РН-Рез , М-Вперёд :
      case k15:
              Isp.all &= _ZI_shunt , Isp._.RN_Res = 1 ;    //Isp.all = 0 , DAN - Не обнуляем шунтирование ЗИТ и ЗИС .
              Isp._.NumMost = 0 ;
              Label = k50 ;
              m_time = Timer1_Ovr ;
              break ;
            //-------------------
            //              СИФУВ-Рез :
      case k16:
              Isp.all &= _ZI_shunt , Isp._.SIFUV_Res = 1 ; //Isp.all = 0 , DAN - Не обнуляем шунтирование ЗИТ и ЗИС .
              Label = k50 ;
              m_time = Timer1_Ovr ;
              break ;
            //-------------------
            //              ШТАТНЫЙ РЕЖИМ :
      case k17:
              // V.flg.all = 0 ; // 18.10.05 08:16 Не нужно обнулять все ,
              // достаточно обнулить отключение функционала :
              V.flg._.otkl_func = 0 ;
              //V.flg._.RT = 1 ;
              Prg._.Cikl = 0 ;//Ckl._.RTV  = 0 ;
              Ckl._.SIFUV = 0 ; // DAN 10.01.2011 15:00 Чтобы включился РТВ в СИФУВ .
              //-----------------------------
              //18.09.2019 - добавил обнуление всех циклов , чтобы поле настройки отдельно РТ1 или РТ2
              Ckl.all = 0 ; // при переходе в штатный режим не блокировался РТ ...
              //-----------------------------
              Isp.all = 0 ;//, Z_sk.ach = &Z_sk_ach ;
              Label = k50 ;
              m_time = Timer1_Ovr ;
              break ;
      //-----------------------------------------------------------
            //              ЦИКЛЫ.
      case k30:
    #ifndef _AD_ROT
         #ifndef _KTEV
           #ifndef _KTE_GD
              if      ( Ckl._.RT2     == 1 )   m_index = 7 /*8*/ ;
              else if ( Ckl._.RT1     == 1 )   m_index = 6 /*7*/ ;
           #else
              if      ( Ckl._.RN      == 1 )   m_index = 6 /*7*/ ;
           #endif
              else if ( Ckl._.RP      == 1 )   m_index = 5 /*6*/ ;
              else if ( Ckl._.SIFU    == 1 )   m_index = 4 /*5*/ ;
//            else if ( Ckl._.Reg_EDS == 1 )   m_index = 4 ; 09.06.2020 15:35
              else if ( Ckl._.SIFUV   == 1 )   m_index = 3 ;
              else if ( Ckl._.RTV     == 1 )   m_index = 2 ;
         #else
                   if ( Ckl._.SIFU    == 1 )   m_index = 2 ;
         #endif
              else if ( Ckl._.RT      == 1 )   m_index = 1 ;
              else if ( Ckl._.RS      == 1 )   m_index = 0 ;
    #else
      #ifdef _UPTF
                   if ( Ckl._.RS      == 1 )   m_index = 1 ;
              else
      #endif
                   if ( Ckl._.SIFU    == 1 )   m_index = 0 ;
    #endif
              else      Ckl.all = 0 ,          m_index = 0 ;
              output_c ( '\n' ) ;
              Label = k31 ;
              break ;
      case k31:
                 // Ожидание завершения предыдущего вывода.
              if ( TestCompleted_Output() )
                {
                  output_s ( _Cikl_Reg_txt ) ;
                  output_s ( Nckl[ m_index ].txt ) ;
                  Label = k32 ;
                  break ;
                }
      case k32: if ( TestData_for_Input() ) // 30.07.2020 Здесь был "while" .
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                    {
                      output_s ("\n\r") ;
                      Label = k0 ;
                      break ;
                    }
                  else if ( m_ch == Down ) /* Выбрать структуру.*/
                    {
                      if ( ++m_index >= _Nck ) m_index = 0 ;
                      Label = k31 ;
                    }
                  else if ( m_ch == Up ) /* Выбрать структуру.*/
                    {
                      if ( m_index-- == 0 ) m_index = _Nck - 1  ;
                      Label = k31 ;
                    }
                  else if ( m_ch == Enter )
                    {
                      //---
                      // Контроль выбора того же контура регулир. в "Работе" ,
                      // какой был определен в "Сб. Готовности" :
    #ifndef _AD_ROT
                      if ( Prg._.Gotovn == 0 && Ckl._.RS      == 1 && m_index != 0 ) goto xx ;
                      if ( Prg._.Gotovn == 0 && Ckl._.RT      == 1 && m_index != 1 ) goto xx ;
                   #ifndef _KTEV
                      if ( Prg._.Gotovn == 0 && Ckl._.RTV     == 1 && m_index != 2 ) goto xx ;
                      if ( Prg._.Gotovn == 0 && Ckl._.SIFUV   == 1 && m_index != 3 ) goto xx ;
// 09.06.2020 15:35   if ( Prg._.Gotovn == 0 && Ckl._.Reg_EDS == 1 && m_index != 4 ) goto xx ;
                      if ( Prg._.Gotovn == 0 && Ckl._.SIFU    == 1 && m_index != 4 /*5*/ ) goto xx ;
                      if ( Prg._.Gotovn == 0 && Ckl._.RP      == 1 && m_index != 5 /*6*/ ) goto xx ;
                    #ifndef _KTE_GD
                      if ( Prg._.Gotovn == 0 && Ckl._.RT1     == 1 && m_index != 6 /*7*/ ) goto xx ;
                      if ( Prg._.Gotovn == 0 && Ckl._.RT2     == 1 && m_index != 7 /*8*/ ) goto xx ;
                    #else
                      if ( Prg._.Gotovn == 0 && Ckl._.RN      == 1 && m_index != 6 /*7*/ ) goto xx ;
                    #endif
                   #else
                      if ( Prg._.Gotovn == 0 && Ckl._.SIFU    == 1 && m_index != 2 ) goto xx ;
                   #endif
    #else
                      if ( Prg._.Gotovn == 0 && Ckl._.SIFU    == 1 && m_index != 0 ) goto xx ;
      #ifdef _UPTF
                      if ( Prg._.Gotovn == 0 && Ckl._.RS      == 1 && m_index != 1 ) goto xx ;
      #endif
    #endif
                      //---
                      Ckl.all = 0 ;
                      switch ( m_index ) {
    #ifndef _AD_ROT
                          case 0 :  // регулятор скорости.
                                    Ckl._.RS  = 1 ;
                            break ;
                          case 1 :  // регулятор тока.
                                    Ckl._.RT  = 1 ;
                            break ;
                   #ifndef _KTEV
                          case 2 :  // регулятор тока возбуждения.
                                    Ckl._.RTV = 1 ;
                            break ;
                          case 3 :  // СИФУВ.
                                    Ckl._.SIFUV = 1 ;
                            break ;
// 09.06.2020 15:35       case 4 :  // регулятор ЭДС.
//                                  Ckl._.Reg_EDS = 1 ;
//                          break ;
                          case 4 /*5*/ :  // СИФУ.
                                    Ckl._.SIFU = 1 ;
                            break ;
                          case 5 /*6*/ :  // регулятор положения.
                                    Ckl._.RP  = 1 ;
                            break ;
                    #ifndef _KTE_GD
                          case 6 /*7*/ :  // регулятор тока 1-го Моста 12-пульсной схемы.
                                    Ckl._.RT1 = 1 ;
                            break ;
                          case 7 /*8*/ :  // регулятор тока 2-го Моста 12-пульсной схемы.
                                    Ckl._.RT2 = 1 ;
                            break ;
                    #else
                          case 6 /*7*/ :  // регулятор напряжения.
                                    Ckl._.RN  = 1 ;
                            break ;
                    #endif
                   #else
                          case 2 :  // СИФУ.
                                    Ckl._.SIFU = 1 ;
                            break ;
                   #endif
    #else
                          case 0 :  // СИФУ.
                                    Ckl._.SIFU = 1 ;
                            break ;
      #ifdef _UPTF
                          case 1 :  // регулятор скорости.
                                    Ckl._.RS  = 1 ;
                            break ;
      #endif
    #endif
                          default:;
                        }
                      Label = k33 ;
                      if( c_index != m_index) Prg.all &= ~_Cikl , OCIKL = 0; //21.01.2021
                    }
                  else  Klav_Buff = m_ch;
                }
              break ;
            /*чччччччччччччччччччччччччччччччччччччччч*/

      case k33: output_c ( '\n' ) ;
              Label = k34 ;
      case k34:
                 // Ожидание завершения предыдущего вывода.
              if  ( TestCompleted_Output() )
                {
                  output_s ("\rT=") ;
                  ax = TCIKL ,  bx = _Tnom ;
                    // приводим содержимое ячейки к его номиналам.
                  cx = ax / bx ;
                        // распечатка целой части
                      output_c ( (b)cx + 0x30 ) ;
                     output_c ( '.' ) ;
                         // распечатка дробной части
                      cx = ax % bx * 100 / bx ;
                      bx = cx / 10u  ;
                      output_c ( (b)bx + 0x30 ) ;
                      cx %= 10 ;
                      output_c ( (b)cx + 0x30 ) ;
                     output_s ( "sec" ) ;

                  Label = k35 ;
                  break ;
                }
     case k35: if ( TestData_for_Input() ) // 30.07.2020 Здесь был "while" .
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )  Label = k30 ;
                  else if ( m_ch == Up )
                    {     // максимальное ограничение масштаба.
                      if ( TCIKL < 2997u ) TCIKL += 3 ; // огранич. до 9.99с .
                      Label = k34 ;
                    }
                  else if ( m_ch == Down )
                    {     // минимальное ограничение масштаба.
                      if ( TCIKL > 3 ) TCIKL -= 3 ;
                      Label = k34 ;
                    }
                  else if ( m_ch == Enter ) Label = k36 ;
                  else  Klav_Buff = m_ch;
                }
              break ;
            /*чччччччччччччччччччччччччччччччччччччччч*/

     case k36: output_c ( '\n' ) ;
                  /*   Подсчет количества заполненных ячеек таблицы:
                   *  признаком последней заполненной ячейки являются
                   *  нули в двух последующих ячейках.
                   */
              m_ext = YKSTc; /* = 1 ;
              while ( CiklTab[ m_ext ] != 0 || CiklTab[ m_ext+1 ] != 0 )
                {
                  m_ext++ ;
                  if ( (sw)m_ext >= _CiklLong - 1 ) break ;
                }  20.01.2021 */
              Label = k37 ;
              break ;
     case k37:
                 // Ожидание завершения предыдущего вывода.
              if  ( TestCompleted_Output() )
                {
                  output_s ("\rN=") ;
                  output_c ( m_ext + 0x30 ) ;
                  Label = k38 ;
                  break ;
                }
     case k38: if ( TestData_for_Input() ) // 30.07.2020 Здесь был "while" .
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )  Label = k33 ;
                  else if ( m_ch == Up )
                    {
                      if ( m_ext < (w)_CiklLong ) m_ext++ ;
                      Label = k37 ;
                    }
                  else if ( m_ch == Down )
                    {
                      if ( m_ext > 1 ) m_ext -- ;
                      Label = k37 ;
                    }
                  else if ( m_ch == Enter )
                    {    /* оформляем конец таблицы циклов */
                      //20.01.2021 for ( ax = m_ext ; ax < _CiklLong ; ax++ ) CiklTab[ax] = 0 ;
                      Label = k39 ;
                    }
                  else  Klav_Buff = m_ch;
                }
              break ;
            /*чччччччччччччччччччччччччччччччччччччччч*/

     case k39: output_c ( '\n' ) ;
              m_time = 0 ;
              Label = k40 ;
     case k40:
                 // Ожидание завершения предыдущего вывода.
              if  ( TestCompleted_Output() )
                {
                  output_s ("\rn") ;
                  output_c ( m_time + 0x31 ) ;
                  output_c ( '=' ) ;

                  //15.01.21 SAP - каждый выбранный цикл должен начинаться с допустимых значений для выбранного режима.
                  //Объявление переменной avar.h. Алгоритм F2_DRV.c .
                  //Для других режимов, начальное заначение, в начале работы будет равно уставке = 32 дискреты
                  //Например после угла при 150 градусов, для регулятора положения значение будет 13652 дискреты
                  //Для изменения начальных условий добавить начальное значение выбранного режима
                  YKSTc = m_ext; // кол-во выбранных циклов.
                  if( c_index != m_index)
                  {
                    //Заполняем все ячейки массива - все ступени цикла
                    for( m_time = 0 ; m_time < _CiklLong ; m_time ++ ){
                      #ifdef _REG_POL
                          if ( Ckl._.RP == 1 )  CiklTab[m_time] = _Grad(0.05) ;
                          else
                      #endif
                          if ( Ckl._.RS == 1 )  CiklTab[m_time] = _Skor_nom( 0.00 ) ;
                          else if ( Ckl._.RT == 1 || Ckl._.RT1 == 1 || Ckl._.RT2 == 1 )
                          {
                      #ifndef _KTE_GD
                            CiklTab[m_time] =  _Id_nom( 0.00 ) ;
                      #else
                            CiklTab[m_time] = _Ig_nom( 0.00 ) ;
                      #endif
                          }
                          else if ( Ckl._.RN   == 1 )     CiklTab[m_time] =  _Id_nom( 0.00 ) ;
                          else if ( Ckl._.SIFU == 1 )     CiklTab[m_time] = _r.S_Alfa_Max ;
                      #ifdef  _Vozb_KTE
                          else if ( Ckl._.SIFUV== 1 )     CiklTab[m_time] = _r.V_Alfa_Max ;
                      #endif
                    }
                    m_time = 0; //После заполнения всего массива возыращаем начальный индекс
                  }
                  c_index = m_index; // индекс выбранного режима
                  //---------------------------------------------------
                  ax = CiklTab[m_time] ;
                  bx = Nckl[m_index].nom ;
                  if ( (sw)ax >= 0 )
                    {
                      output_c ( '+' ) ;
                    }
                  else
                    {
                      output_c ( '-' ) ;
                      ax = ~ax + 1 ;
                    }
                    // приводим содержимое ячейки к его номиналам.
                    cx = ax / bx ;
                        // распечатка целой части
                      output_c ( (b)(cx/100) + 0x30 ) ;
                    cx %= 100 ;
                      output_c ( (b)(cx/10) + 0x30 ) ;
                    cx %= 10 ;
                      output_c ( (b)cx + 0x30 ) ;
                     output_c ( '.' ) ;
                         // распечатка дробной части
                      ax = ax % bx * 10 ;
                      output_c ( (b)(ax/bx) + 0x30 ) ;
                      ax = ax % bx * 10 ;
                      output_c ( (b)(ax/bx) + 0x30 ) ;

                  Label = k41 ;
                  break ;
                }
     case k41: if ( TestData_for_Input() ) // 30.07.2020 Здесь был "while" .
                {
                  ax = CiklTab[m_time] ; // Считывание уставки для ее последующего изменения.
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )  Label = k36 ;
                  else if ( m_ch == Up )
                    {
                      cx = ax ;
                      if ( (sw)(ax += Nckl[m_index].dK ) > (sw)Nckl[m_index].max ) ax = Nckl[m_index].max ;
                            //  chtobi pri perehode cherez null byl chystiy null.
                        if ( (sw)cx < 0 && (sw)ax > 0 ) ax = 0 ;
                      CiklTab[m_time] = ax ;
                      Label = k40 ;
                    }
                  else if ( m_ch == Down )
                    {
                      cx = ax ;
                      if ( (sw)(ax -= Nckl[m_index].dK ) < (sw)Nckl[m_index].min ) ax = Nckl[m_index].min ;
                            //  chtobi pri perehode cherez null byl chystiy null.
                        if ( (sw)cx > 0 && (sw)ax < 0 ) ax = 0 ;
                      CiklTab[m_time] = ax ;
                      Label = k40 ;
                    }
                  else if ( m_ch == Enter )
                    {     /* Закончено ли задание всех ступеней. */
                      if ( m_time < (w)(m_ext - 1)) m_time++ , Label = k40 ;
                      else
                        {
                          Isp.all &= _ZI_shunt , Isp._.Cikl = 1 ; //Isp.all = 0 , DAN - Не обнуляем шунтирование ЗИТ и ЗИС .
                          if ( Prg._.Gotovn == 1 )
                          {
                            // 18.11.2013 DAN - Для циклов , которые выполняются в Сборке Готовности включаем Цикл и След :
                            if ( Ckl._.RTV == 1 || Ckl._.SIFUV == 1 ) Prg.all |= _Sled | _Cikl ;
                          }
                          /* 18.11.2013 DAN - Убрано за ненадобностью , сейчас регуляторы циклов включаются только в
                          // файле UPRAVL.C и выключить отдельные регуляторы нельзя . Оставлять здесь выбор регуляторов
                          // нет смысла , т.к. тогда здесь придётся ещё и контролировать ЛК для ГД ...
                          if ( Ckl._.RTV == 1 )
                            {
                              //V.flg._.otkl_func = 1 ; 02.04.2008 13:26 - не требуется .
                              if ( Prg._.Gotovn == 0 ) Prg.all = (Prg.all & _Sled) | _Cikl ;
                              else                     Prg._.Cikl = 1 ;
                            }
                          else if ( Ckl._.SIFUV == 1 )
                            {
                              //V.flg._.otkl_func = 1 ; 02.04.2008 13:26 - не требуется .
                              if ( Prg._.Gotovn == 0 ) Prg.all = (Prg.all & _Sled) | _Cikl ;
                              else                     Prg._.Cikl = 1 ;
                            }
                          else if ( Prg._.Gotovn == 0 )
                            {
                              if ( Ckl._.RP == 1 )
                                {
                                  Prg.all = (Prg.all & _Sled) | _Cikl | _RegTok | _RegSk | _RP ;
                                }
                              else if ( Ckl._.RS == 1 )
                                {
                                  Prg.all = (Prg.all & _Sled) | _Cikl | _RegTok | _RegSk ;
                                }
                              else if ( Ckl._.Reg_EDS == 1 )
                                {
                                  Prg.all = (Prg.all & _Sled) | _Cikl | _RegTok | _RegSk | _RP ;
                                }
                              else if ( Ckl._.RT == 1 )
                                {
                                  Prg.all =  (Prg.all & _Sled) | _Cikl | _RegTok ;
                                }
                              else if ( Ckl._.RT1 == 1 )
                                {
                                  Prg.all =  (Prg.all & _Sled) | _Cikl | _RegTok ;
                                }
                              else if ( Ckl._.RT2 == 1 )
                                {
                                  Prg.all =  (Prg.all & _Sled) | _Cikl | _RegTok ;
                                }
                              else if ( Ckl._.RN == 1 )
                                {
                                  Prg.all =  (Prg.all & _Sled) | _Cikl | _RN ;
                                }
                              else if ( Ckl._.RTV == 1 )
                                {
                                  Prg.all =  (Prg.all & _Sled) | _Cikl ;
                                }
                              else if ( Ckl._.SIFUV == 1 )
                                {
                                  Prg.all =  (Prg.all & _Sled) | _Cikl ;
                                }
                              else if ( Ckl._.SIFU == 1 )
                                {
                                  Prg.all =  (Prg.all & _Sled) | _Cikl ;
                                }
                            } */
                          Label = k50 ;
                          m_time = Timer1_Ovr ;
                    }   }
                  else  Klav_Buff = m_ch;
                }
              break ;
            /*чччччччччччччччччччччччччччччччччччччччч*/

     case k50: output_s ( "\r\n Ok." ) ;
               Label = k51 ;

     case k51: if ( (u)((w)(Timer1_Ovr-m_time)) > _Sec( 2.0 ) ) goto end ;
              break ;

#ifdef   _AVTONASTR
     case k60a:      output_s ( "\n\rАвтоналагод. " );

     case k60:
                     output_s ( "\n\r" ) ;
                     m_index = 0 ; //Индекс сохраняется в "F2regim".
                     Label = k61 ;

     case k61:
              if ( TestCompleted_Output() )
                {
                  output_s ( AN_RT[ m_index ].txt ) ;
                  Label  = k62 ;
                  break ;
                }

     case k62 :
                if ( TestData_for_Input() ) // 30.07.2020 Здесь был "while" .
                    {
                        mInput_c ( m_ch ) ;
                        if ( m_ch == Return )
                            {
                            output_s ("\n\r") ;
                            m_index = F2regim ;  // Возврат в меню автонастройки
                            Label = k0 ;
                            break ;
                            }
                        else if ( m_ch == Down )
                            {
                            if ( ++m_index >= _Nanastr ) m_index = 0 ;
                            Label = k61 ;
                            }
                        else if ( m_ch == Up )
                            {
                            if ( m_index-- == 0 ) m_index = _Nanastr - 1  ;
                            Label = k61 ;
                            }
                        else if ( m_ch == Enter )
                            {
                              m_ext = m_index;
                              m_index = 0;
                              Label = k63 ;
                            }

                        else  Klav_Buff = m_ch;
                }
            break ;

     case k63 :
                output_s ( "\n" ) ;
                Label = k64 ;

     case k64:
                if ( TestCompleted_Output() )
                 {
                    if ( m_index == 0 ) output_s ( _Fazir_No_txt  ) ;
                    else                output_s ( _Fazir_Yes_txt ) ;
                    Label = k65 ;
                    break ;
                 }

     case k65 :
                if ( TestData_for_Input() ) // 30.07.2020 Здесь был "while" .
                    {
                        mInput_c ( m_ch ) ;
                        if ( m_ch == Return )
                            {
                  back:     m_index = m_ext;  // Возврат в предыдущее меню автонастройки
                            Label = k60a ;
                            break ;
                            }
                        else if ( m_ch == Down )
                            {
                            if ( ++m_index >= 2 ) m_index = 0 ;
                            Label = k64 ;
                            }
                        else if ( m_ch == Up )
                            {
                            if ( m_index-- == 0 ) m_index = 1  ;
                            Label = k64 ;
                            }
                        else if ( m_ch == Enter )
                            {
                              if ( m_index != 0 )
                               {
                                 AnastrRT = AN_RT[m_ext].label ;
                                 Isp.all &= _ZI_shunt ; //Isp.all = 0 , DAN - Не обнуляем шунтирование ЗИТ и ЗИС .
                                 Isp._.AvtoNastr = 1;
                                 AN_Label = k0 ;
                                 //m_index = 0;  // Возврат в предыдущее меню автонастройки
                                 Label = k66 ;
                                 output_s ( "\r\n Ok." ) ;
                                 m_time = Timer1_Ovr ;
                               }
                               else  goto back ;
                               //{
                                 //output_s ("\r") ;
                                 //m_index = 0;  // Возврат в предыдущее меню автонастройки
                                 //Label = k60a ;
                               //}
                            }
                        else  Klav_Buff = m_ch;
                    }
                    break;

     case k66: if ( (u)((w)(Timer1_Ovr-m_time)) > _Sec( 1.0 ) )  Label = k0 ;
               break ;
#endif  // Автонастройка
#ifdef   _NARABOTKA
     case k67:       output_s ( "\n\rОбнул.напрац.?  " );

     case k68:
                     output_s ( "\n\r" ) ;
                     m_index = 0 ; //Индекс сохраняется в "F2regim".
                     Label = k69 ;

      case k69:
          if ( TestCompleted_Output() )
            {
              if ( m_index == 0 ) output_s ( _OstanovNo_txt  ) ;
              else                output_s ( _OstanovYes_txt ) ;
              Label = k70 ;
              break ;
            }

      case k70:

          if ( TestData_for_Input() )
            {
              mInput_c ( bh ) ;
                  if ( bh == Return )  /* Выход из этого режима */
                    {
                end1: output_s ("\n\r") ;
                      Label = k0 ;
                      break ;
                    }
                  else if ( bh == Up || bh == Down ) /* Изменить выбор. */
                    {
                      m_index = ~m_index,  Label = k69 ;
                    }
                  else if ( bh == Enter )
                    {
                      if ( m_index == 0 ) goto end1 ;
                      //----------------------------
                       NARAB.hou = 0 ;
                       NARAB.min = 0 ;
                       NARAB.sec = 0 ;
                       NARAB.ovr = 0 ;
                       narab._.rab_wr  = 1 ;  // Выставляем флаг требования записи .
                      //----------------------------
                      m_time = Timer1_Ovr ;
                      Label = k50 ;
                    }
                  else    Klav_Buff = bh;
            }
          break ;
#endif
#ifdef   _SELS_NULL
      case k71:      output_s ( "\n\rВстан.нуля селс." );
                     output_s ( "\n\r" ) ;
                     m_index = 0 ; //Индекс сохраняется в "F2regim".
                     m_ch = 0 ;
                     Label = k72 ;

      case k72:
          if ( TestCompleted_Output() )
            {
              if ( m_index == 0 ) output_s ( "\rCельсин 0" ) ;
              else                output_s ( "\rCельсин 1" ) ;
              Label = k73 ;
              break ;
            }

      case k73:
          if ( TestData_for_Input() )
            {
              mInput_c ( bh ) ;
                  if ( bh == Return )  /* Выход из этого режима */
                    {
                      output_s ("\n\r") ;
                      Label = k0 ;
                      break ;
                    }
                  else if ( bh == Up || bh == Down ) /* Изменить выбор. */
                    {
                      m_index = ~m_index,  Label = k72 ;
                    }
                  else if ( bh == Enter )
                    {
                      Label = k74 ;
                      output_s ("\n\r") ;
                    }
                  else      Klav_Buff = bh;
            }
          break ;

      case k74:
          if ( TestCompleted_Output() )
            {
              if ( m_ch == 0 ) output_s ( _OstanovNo_txt  ) ;
              else             output_s ( _OstanovYes_txt ) ;
              Label = k75 ;
              break ;
            }

      case k75:
          if ( TestData_for_Input() )
            {
              mInput_c ( bh ) ;
                  if ( bh == Return )  /* Выход из этого режима */
                    {
                end2: output_s ("\n\r") ;
                      Label = k71 ;
                      break ;
                    }
                  else if ( bh == Up || bh == Down ) /* Изменить выбор. */
                    {
                      m_ch = ~m_ch,  Label = k74 ;
                    }
                  else if ( bh == Enter )
                    {
                      if ( m_ch == 0 ) goto end2 ;
                      Label = k76 ;
                    }
                  else    Klav_Buff = bh;
            }
          break ;

      case k76:
          if ( m_index == 0 ) Sels_tr._.null0 = 1 ;
          else                Sels_tr._.null1 = 1 ;
          Label = k77 ;
          timerNull = Timer1_Ovr ;
          break ;

      case k77:
          if ((u)((w)(Timer1_Ovr - timerNull)) > _Sec(0.2))
           {
             Sels_tr._.null0 = 0 ;
             Sels_tr._.null1 = 0 ;
             m_time = Timer1_Ovr ;
             Label = k50 ;
           }
          break ;
#endif
    }

  Restart_Output ()  ;

  return ;
}

