
/*  ПРОГРАММА-ДОПОЛНЕНИЕ К ДИСПЕТЧЕРУ ПУЛЬТОВЫХ ПРОГРАММ.  */
/*-------------------------------------------------  */


/*--------------------------------------------  */
/*    Программа-дополнение к диспетчеру: по коду текста введенной  */
/*  команды помещенной диспетчером в двухбайтную ячейку "Pult_Prog_Addr"  */
/*  запускается поставленная в соответствие данному коду (см.ниже) программа,  */
/*  которая подменяет собой диспетчера.  */
/*    При необходимости снова вернуть управление диспетчеру эта вызываемая  */
/*  по коду программа должна записать в ячейку  "Pult_Prog_Addr"  нули и в  */
/*  ячейку "M_FirstCall" ( используемую в вызываемых программах и самом  */
/*  диспетчере, как признак первого входа в п/п, для задания необходимых  */
/*  начальных условий переменным ) единицу.  */

/*    По внешнему "switch" распознается первый символ введенной команды  */
/*  ( хотя он и единственный для односимвольной команды ).  */
/*    По внутреннему "switch" распознается либо второй символ для двухсим-  */
/*  вольной команды, либо нуль - для односимвольной команды ( чему соответст-  */
/*  вует запись - "case 0 :" ).  */

 void Pult_Rabota ( void )
 {
         // Очистка кодов из буфера с выдержкой времени.
      Test_Klav_buff() ;

      switch ( Lb( Pult_Prog_Addr ) )
        {       /* Вызов текущей активной пультовой программы.  */

          case 0 :    Pult_Dispetcher () ;
                      return ;
                    /*----------------------------  */

          case  'A' :
          case  'a' : switch ( Hb( Pult_Prog_Addr ) )
                        {
                          case  0  :
                                      Norton_Drive () ;
                                      return ;
                          case '0' :
                                      Mon.EnableSrvMsg = 0 ;
                                      PrintMessage () ;
                                      return ;
                          case '1' :
                                      Mon.EnableSrvMsg = 1 ;
                                      PrintMessage () ;
                                      return ;
                     /*     case '2' :
                                      Fazirovka_Us () ;  //2080
                                      return ;
                          case '3' :
                                      Fazirovka_Is () ;
                                      return ;*/
                          case '4' :
                                      TstADC_Drive () ;
                                      return ;
                          /*case '5' :                         // Перенесено в "Наладка" 18.05.2020
                                      if( Av._.Ostanov == 1 ) break;
                                      Fazirovka() ;
                                      return ;*/
                          case '6' :
                                      Indicator_Drive () ;
                                      return ;
                          case '7' :
                                      SetabDrive ("",0) ;
                                      return ;
                          case '8' :
                                      Setab_Bit_Drive ("",0) ;
                                      return ;
                          case '9' :
                                      TstDAC_Drive () ;
                                      return ;
                          case 'A' :
                          case 'a' :
                                      TstInputPort_Drive () ;
                                      return ;
                          case 'B' :
                          case 'b' :
                                      TstOutputPort_Drive () ;
                                      return ;
#ifdef _JOURNAL
                          case 'C' :
                          case 'c' :
                                      SetJrnTab () ;
                                      return ;
#endif
                          case 'D' :
                          case 'd' :
                                      Vybor_DAC_tabl () ;
                                      return ;
                          case 'E' :
                          case 'e' :
                                      UstRam_in_Flash ()  ;
                                      return ;
                          case 'F' :
                          case 'f' :
                                      Password_control ( 1 ) ;
                                      return ;

                          default:  break ;
                        }
                      break ;
                    //----------------------------

          case  'f' :
          case  'F' : switch ( Hb( Pult_Prog_Addr ) )
                        {
                          case 0 :
                                    Monitor () ;
                                    return ;
                          case '0' :
                                    SetSledTab () ;
                                    return ;
#ifdef _CombRedact
                          case '1' :
                                    comb_redact () ;
                                    //SledPrint () ;
                                    return ;
#endif
                          case '2' :
                                    Vybor_Isp () ;
                                    return ;
#ifdef  _TEST_RAM_INCLUDE
                          case '3' :
                                    if( Av._.Ostanov == 0 ) break;
                                    Test_RAM () ;
                                    return ;
#endif
                          case '4' :
                                    if( Av._.Ostanov == 0 ) break;
                                    Test_i2c () ;
                                    return ;
                          case '5' :
                                    ReLoad_sled () ;
                                    return ;
                          case '6' :
                                    Clock() ;
                                    return ;
                          case '7' :
                                    Clock_ust() ;
                                    return ;
                          case '8' :
                                    About () ;
                                    return ;
                          case '9' :
                                      /*  Восстановление типовых уставок. */
                                      Type_ustavki () ;
                                      return ;
                          case 'A' : // 19.03.2014 13:27 В ОСТАНОВ входим только по PIN1 из-за "боков" сторожа
                          case 'a' : // 27.05.2020 10:19 ОСТАНОВ вернулся!!!
                                 /* Av._.Ostanov = 1 ;
                                    Pult_Prog_Addr = _MainPultProg  ;
                                    output_s("\r\nOk.\r\n") ;*/
                                    if( Av._.Ostanov == 1 ) break;
                                    FA_Ostanov () ;
                                    return ;
#ifdef _JOURNAL
                          case 'B' :
                          case 'b' :
                                      JrnPrint () ;
                                      return ;
#endif
#ifdef _Sld_cond
                          case 'C' :
                          case 'c' :
                                    Sled_Cond_sel ();
                                    return ;
#endif
#ifdef _NET_IRQ
                          case 'D' :
                          case 'd' :
                                    if( Av._.Ostanov == 0 || TypeNet != _ProfibusDP_)  break; // 19.03.2014 13:16 раскомментировано, чтобы тест был
                                    Test_DP () ; // только в ОСТАНОВЕ, т.к. из-за задержек вывода на пультик срабатывает
                                    return ;     // сторож, а в ОСТАНОВЕ сторож не работает
#endif
                          case 'E' :
                          case 'e' :
                                    Speed_Pult () ;
                                    return ;
                          case 'F' :
                          case 'f' :
                                    if( Av._.Ostanov == 0 ) break;
                                    MWelcome = "\r\nMf>" ;
                                    while ( Pult_Prog_Addr != _MainPultProg )
																			{
					                              Monitor() ;
                                        Sled() ;
																			}
                                    MWelcome = "\r\nMo>" ;
                                   return ;
                         default:  break ;
                        }
                      break ;
                    /*----------------------------  */
          case  'I' : switch ( Hb( Pult_Prog_Addr ) )
                        {
                          case 0 :
                                    Link();
                                    return ;
                          default:  break ;
                        }
                      break ;

          case  'J' : switch ( Hb( Pult_Prog_Addr ) )
                        {
                          case 0 :
                                    ReadWrite_i2c ( _i2c_beg, _i2c_end, _Adr_Flash_i2c );
                                    return ;
                          default:  break ;
                        }
                      break ;

          case  'K' : switch ( Hb( Pult_Prog_Addr ) )
                        {
                          case 0 :
                                    Read_Ust ( ) ;
                                    return ;
                          default:  break ;
                        }
                      break ;
#ifndef _CM3_
          case  'L' : switch ( Hb( Pult_Prog_Addr ) )
                        {
                          case 0 :
                                    ReadWrite_i2c ( _clock_i2c_beg, _clock_i2c_end, _Adr_Clock_i2c );
                                    return ;
                          default:  break ;
                        }
                      break ;
#endif
#ifdef _INTERPRETER
          case  'M' : switch ( Hb( Pult_Prog_Addr ) )
                        {
                          case 0 :
                                    RW_Prog ( _i2c_code_beg, _i2c_code_end, _Adr_Flash_i2c );
                                    return ;
                          default:  break ;
                        }
                      break ;
#endif

                    //----------------------------
#ifdef _NET_IRQ
          case  'B' :
          case  'b' :
                        if ( TypeNet == _NotDefined_ ) break;
                        switch ( Hb( Pult_Prog_Addr ) )
                        {
                          case '6' :
                                      NetIndicator_Drive () ;
                                      return ;
                          case '7' :
                                      NetSetab_Drive ("",0) ;
                                      return ;
                          case '8' :
                                      NetSetabBit_Drive ("",0) ;
                                      return ;
                          default:  break ;
                        }
                      break;
                    //----------------------------
#endif
          default:    break ;
        }

   output_s ( _Disp_ComNotServed ) ;
   Pult_Prog_Addr = _MainPultProg  ;

   return ;
 }

