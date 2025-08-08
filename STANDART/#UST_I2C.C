   //
   //   Программа сборник системных программ.
   //
#ifndef _CM3_
  #include "system.c"
#endif
//-----------------------------

void    setTypeUst()
{
        mSet_PreduprMsg( _Pr_TipUst ) ;
        _r = _c ; //  временное копирование блока в ОЗУ
        _ar = _ac ;
        _or = _oc ;
        _sr = _sc ;
        sled = c_sled ;
        TabFunc = c_TabFunc ; //  восстановление типовых уставок
#ifdef _JOURNAL
        TabJrn = c_TabJrn;
#endif
        // Взводим признак типовых уставок.
        _r.Begin_Code |= 0x8000 ;

    return;
}

     //   Программа считывания из памяти i2c заданного блока уставок,
     // проверки их контрольной суммы и записи в них типовых значений
     // при ошибке в контрольной сумме.
 void load_obl_ust ( word num )
 {
   /*register*/ word ax, bx, cx = 0;

      if( ( Reg_ServiceMsg & _Srv_NoRead_i2c ) != (lw)r0 ) cx = 1; // проверка, было ли установлено это сообщение в функции
                                                                   // Detect_i2c, чтобы ниже его не сбросить
      adr_obl_ust ( num );

      bx = 0 ;
povt: bx++ ;
      if ( bx <= 3 )
      {
        ax  = Load_from_i2c ( sizeof( struct Blok_Ustavok ) ,   _r_adr_i2c , (b*)&_r, _Adr_Flash_i2c ) ;
        ax += Load_from_i2c ( sizeof( struct ABlok_Ustavok ) , _ar_adr_i2c , (b*)&_ar, _Adr_Flash_i2c  ) ;
        ax += Load_from_i2c ( sizeof( struct oBlok_Ustavok ) , _or_adr_i2c , (b*)&_or, _Adr_Flash_i2c  ) ;
        ax += Load_from_i2c ( sizeof( struct SBlok_Ustavok ) , _sr_adr_i2c , (b*)&_sr, _Adr_Flash_i2c  ) ;
        ax += Load_from_i2c ( sizeof( TabFunc ), _TabFunc_adr_i2c , (b*)&TabFunc, _Adr_Flash_i2c ) ;
        ax += Load_from_i2c ( sizeof( struct SLED ), _TablSled_adr_i2c , (b*)&sled, _Adr_Flash_i2c ) ;
#ifdef _JOURNAL
        ax += Load_from_i2c ( sizeof( struct TAB_JRN ), _TablJrn_adr_i2c , (b*)&TabJrn, _Adr_Flash_i2c ) ;
#endif
        if ( ax != 0 )
        {
          mSet_ServiceMsg( _Srv_NoRead_i2c ) ;
          goto povt ;
        }

           //   В "_r.Begin_Code" старший бит - признак того, что приняты
           // типовые уставки, по которому в "msg.c" взводится соотв. сообщение.
           // здесь на время сравнения исключаем его.
           // Признак сбрасывается при записи уставок.
        if ( (_r.Begin_Code & 0x7fff) != (_c.Begin_Code & 0x7fff) ) goto povt ;
        else
        {     // Подсчет контрольной суммы.
          ax  = Chek_sum ( sizeof( struct Blok_Ustavok ) , (b*)&_r ) ;
          ax += Chek_sum ( sizeof( struct ABlok_Ustavok ), (b*)&_ar) ;
          ax += Chek_sum ( sizeof( struct oBlok_Ustavok ), (b*)&_or) ;
          //ax += Chek_sum ( sizeof( struct SBlok_Ustavok ), (b*)&_sr) ;
          ax += Chek_sum ( sizeof( TabFunc ), (b*)&TabFunc ) ;
          ax += Chek_sum ( sizeof( struct SLED ), (b*)&sled ) ;
#ifdef _JOURNAL
          ax += Chek_sum ( sizeof( struct TAB_JRN ), (b*)&TabJrn ) ;
#endif
          if ( ax != 0 )
          {
            mSet_ServiceMsg( _Srv_NoCheckSum_i2c ) ;
            goto povt ;
          }
        }
        if( cx == 0 ) mClr_ServiceMsg( _Srv_NoRead_i2c ) ; // если в Detect_i2c это сообщение не было установлено
        mClr_ServiceMsg( _Srv_NoCheckSum_i2c ) ;
      }
      else
      {
        setTypeUst();

            // Подсчет контрольной суммы.
   /*   Chek_sum ( sizeof( struct Blok_Ustavok ) , (b*)&_r ) ;
        Chek_sum ( sizeof( struct ABlok_Ustavok ), (b*)&_ar) ;
        Chek_sum ( sizeof( struct oBlok_Ustavok ), (b*)&_or) ;
        Chek_sum ( sizeof( struct SBlok_Ustavok ), (b*)&_sr) ;
        Chek_sum ( sizeof( TabFunc ), (b*)&TabFunc ) ;
        Chek_sum ( sizeof( struct SLED ), (b*)&sled ) ;

            // pusty zapisyvayut vruchnuyu cherez "AE"// перезапись блока из ОЗУ во Flash
        ax  = Save_into_i2c ( sizeof( struct Blok_Ustavok  ) , (b*)&_r ,  _r_adr_i2c, _Adr_Flash_i2c ) ;
        ax += Save_into_i2c ( sizeof( struct ABlok_Ustavok ) , (b*)&_ar,  _ar_adr_i2c, _Adr_Flash_i2c ) ;
        ax += Save_into_i2c ( sizeof( struct oBlok_Ustavok ) , (b*)&_or,  _or_adr_i2c, _Adr_Flash_i2c ) ;
        ax += Save_into_i2c ( sizeof( struct SBlok_Ustavok ) , (b*)&_sr,  _sr_adr_i2c, _Adr_Flash_i2c ) ;
        ax += Save_into_i2c ( sizeof( TabFunc ), (b*)&TabFunc,  _TabFunc_adr_i2c, _Adr_Flash_i2c ) ;
        ax += Save_into_i2c ( sizeof( struct SLED ), (b*)&sled, _TablSled_adr_i2c, _Adr_Flash_i2c ) ;

        if ( ax != 0 )   mSet_ServiceMsg( _Srv_NoWrite_i2c ) ; */
      }
   return ;
 }
/*Программа расчета начального адреса областей  уставок, в зависимости
 от значения num_obl. Карта расположения областей следующая:

           начальный адрес:  уставки аналоговых каналов
             .........................................
                 область 1:  основные уставки
                            ------------------
                             объектные уставки
                            -------------------
                               уставки Ivz
                            -------------------
                             уставки для следа
                            -------------------
                 область 2:  основные уставки
             .........................................
                 область n:  основные уставки
                             -----------------
                             объектные уставки
                            -------------------
                               уставки Ivz
                            -------------------
                             уставки для следа
                            -------------------
 Аналоговые уставки расположены только в одной области I2C по нулевому
 адресу.(для любых значений num_obl)
 Исходя из этого начальный адрес n-ой области расчитывается как сумма объемов
 всех подобластей, умноженная на n-1.
 */

//  KVV_backup  07.2019
//  Добавлена область BackUp-уставок
//  Развернутые комментарии смотри в monitor.h.

//  KVV_backup: Ввел параметр для возможности вызова этой функции для бэкап-ставок

void xadr_obl_ust ( word num_obl, word start_addr_i2c )
  {
     // /*register*/ word ax ;

     if ( num_obl > _kol_obl ) num_obl= _kol_obl;
     else if ( num_obl < 1   ) num_obl= 1;

     //KVV_backup
     //ax=(start_addr_i2c+_v_ar) + _sm_obl_ust*(num_obl-1);
    //Переменные, определяющие начальный адрес каждой из подобластей
    _ar_adr_i2c = start_addr_i2c;
    _r_adr_i2c = (_ar_adr_i2c+_v_ar) + _sm_obl_ust*(num_obl-1); //ax
    _or_adr_i2c  = _r_adr_i2c+_v_r;
    _sr_adr_i2c  = _or_adr_i2c+_v_or;
    _TabFunc_adr_i2c =_sr_adr_i2c+_v_Stat;
    _TablSled_adr_i2c = _TabFunc_adr_i2c+_v_Func;
#ifdef _JOURNAL
    _TablJrn_adr_i2c  = _TablSled_adr_i2c + _v_TablSled;
#endif
#ifdef _INTERPRETER
    _ExtPrg_adr_i2c = _i2c_code_beg + 2; //адрес в i2c блока объектной программы (+2 байта - размер зашивочного файла)
#endif

    return ;
  }

//  KVV_backup: получение области Основных уставок
void adr_obl_ust ( word num_obl)
{
    xadr_obl_ust ( num_obl, _ust_beg_adr_i2c);
}


//  KVV_backup: получение области BackUp-уставок
void adr_obl_ust_backup ( word num_obl)
{
    xadr_obl_ust ( num_obl, _ust_beg_adr_i2c_backup);
}


// *******************************************************************
// *******************************************************************
//
//                  Чтение Уставок
//


// Программа чтения одной из областей уставок из i2c в ОЗУ. При выходе принимает
// следующие значения: 0 - чтение окончено; 1 - ошибка чтения уставок;
// 2-ошибка контрольной суммы;4 - чтение продолжается.

//  KVV_backup: Ввел параметр для возможности вызова этой функции для бэкап-ставок
//  KVV_backup: для совместимости с прежним ПО ввел две функции см. ниже
//  ar_adr_i2c_read - Обход загрузки уставок АЦП чтобы не сбивать автоустановленные нули АЦП
word xRd_wr_ust (word num_obl, word start_addr_i2c, word ar_adr_i2c_IsReading )
  {
   register word ax;
   enum {i0,i1,i2,i3,i4,i5,i6,i7,i8,i9, i10, i11, i12, i13, i14, i15};
   switch ( Wr_label )
   {
    default:
    case i0:
                // задаем адреса, для данной области
                //KVV 07-2019 перенес вниз xadr_obl_ust ( num_obl, start_addr_i2c );

                Wr_label=1;
    case i1:
               if ( Mon.i2c_busy == 1 )
                 {
                   ax = 4 ;
                   break; //  Ждем пока освободится шина.
                 }
               Mon.i2c_busy = 1 ;  // Устанавливаем признак, что теперь шина занята.
                // задаем адреса, для данной области
               xadr_obl_ust ( num_obl, start_addr_i2c );

                  //  Взводим перед чтением в исходное состояние
                 // указатель метки для функции xLoad_from_i2c.
               i2c_label = 0 , Wr_label++ ;
    case i2:

              // Загружаем основной блок в ОЗУ побайтно
              ax= xLoad_from_i2c ( sizeof( struct Blok_Ustavok ) , _r_adr_i2c , (b*)&_r , _Adr_Flash_i2c);
              // Проверка, закончилась-ли запись блока
              if ( ax == 4 ) ;
              // Если закончилась, то переходим на следующую метку
              else if ( ax == 0 )
              {
                    if ( (_r.Begin_Code & 0x7fff) != (_c.Begin_Code & 0x7fff) )
                    {
                        setTypeUst();
                        ax = 1;
                        Wr_label=0;
                        Mon.i2c_busy = 0 ;
                    }
                    else
                    {
                        ++Wr_label;
                        ax = 4;
                    }
              }
              else
              {
               // Все остальные значения ах - чтение из i2c неудачно
                ax = 1;  // Возврат 1 - неудачное чтение из i2c
                Wr_label=0;
                Mon.i2c_busy = 0 ;
                mSet_ServiceMsg( _Srv_NoRead_i2c );
              }
            break;
    case i3:
               // Проверка контрольной суммы уставок, при неудаче - выдает 2
             if ( Chek_sum ( sizeof( struct Blok_Ustavok ) , (b*)&_r ) != 0)
               {
  avar:         mSet_ServiceMsg( _Srv_NoCheckSum_i2c );
            #ifndef  _DisableReloadUst
                setTypeUst();
                ax = 1;
                Wr_label=0;
                Mon.i2c_busy = 0 ;
                return ax;
            #endif
               }
              ax=4;
              i2c_label = 0;
              ++Wr_label;
              break;
    case i4:
              // Чтение объектных уставок
              ax= xLoad_from_i2c ( sizeof( struct oBlok_Ustavok ) , _or_adr_i2c , (b*)&_or, _Adr_Flash_i2c );
              // Проверка, закончилась-ли запись блока
          ch: if ( ax == 4 ) ;
              // Если закончилась, то переходим на следующую метку
              else if ( ax == 0 )
              {
                ++Wr_label;
                ax = 4;
              }
              else
              {
               // Все остальные значения ах - чтение из i2c неудачно
                ax = 1;  // Возврат 1 - неудачное чтение из i2c
                Wr_label=0;
                Mon.i2c_busy = 0 ;
                mSet_ServiceMsg( _Srv_NoRead_i2c );
              }
            break;
    case i5:

              if ( Chek_sum ( sizeof( struct oBlok_Ustavok ) , (b*)&_or ) != 0) goto avar;
              ax=4;
              i2c_label = 0;
              ++Wr_label;
              break;
    case i6:

              // Чтение статичных уставок
              ax= xLoad_from_i2c ( sizeof( struct SBlok_Ustavok ) , _sr_adr_i2c , (b*)&_sr, _Adr_Flash_i2c );
              goto ch;
    case i7:

              if ( Chek_sum ( sizeof( struct SBlok_Ustavok ) , (b*)&_sr ) != 0)  goto avar;
              ax=4;
              i2c_label = 0;
              ++Wr_label;
              break;
    case i8:

              // Чтение таблицы следа.
              ax= xLoad_from_i2c ( sizeof( struct SLED ),  _TablSled_adr_i2c , (b*)&sled, _Adr_Flash_i2c ) ;
              goto ch;
    case i9:

              if ( Chek_sum ( sizeof( struct SLED ), (b*)&sled) != 0 )  goto avar;
              ax=4;
              i2c_label = 0;
              ++Wr_label;
              break;
    case i10:

              // Чтение уставок Ivz
              ax= xLoad_from_i2c ( sizeof(TabFunc ) , _TabFunc_adr_i2c , (b*)&TabFunc , _Adr_Flash_i2c);
              goto ch;
    case i11:

              if (Chek_sum ( sizeof( TabFunc) , (b*)&TabFunc ) != 0)  goto avar;
              ax=4;
              i2c_label = 0;
              ++Wr_label;
              break;
    case i12:
                //KVV_backup - Добавлена ветвь для ручной загрузки уставок из F9
              if ( ar_adr_i2c_IsReading == 0 )
              {       //  Обход загрузки уставок АЦП чтобы не сбивать автоустановленные нули АЦП
                ax=4;
                i2c_label = 0;
                Wr_label+=2;
                break;
              }

              // Чтение уставок АЦП
              ax= xLoad_from_i2c ( sizeof(struct ABlok_Ustavok) , _ar_adr_i2c, (b*)&_ar, _Adr_Flash_i2c);
              goto ch;
    case i13:

              if (Chek_sum ( sizeof(struct ABlok_Ustavok) , (b*)&_ar) != 0)  goto avar;
              ax=4;
              i2c_label = 0;
              ++Wr_label;
              break;
    case i14:
#ifndef _JOURNAL
              //Если все в порядке - освобождаем шину и выдаем 0
              ax = 0;
              Wr_label=0;
              Mon.i2c_busy = 0 ;
              return ax;
#else

              // Чтение уставок журнала
              ax= xLoad_from_i2c ( sizeof( struct TAB_JRN ) , _TablJrn_adr_i2c , (b*)&TabJrn , _Adr_Flash_i2c);
              goto ch;
    case i15:
              //Заключительная проверка контрольной суммы
              if (Chek_sum ( sizeof( struct TAB_JRN ) , (b*)&TabJrn ) != 0) goto avar;

              //Если все в порядке - освобождаем шину и выдаем 0
              ax = 0;
              Wr_label=0;
              Mon.i2c_busy = 0 ;
              return ax;
#endif
   }

   return ax;
  }

//  KVV_backup: адаптер для совместимости с прежним ПО
//  KVV_backup: получение Основных уставок
word Rd_wr_ust ( word num_obl)
{
    return xRd_wr_ust (num_obl, _ust_beg_adr_i2c, 0);
}


//KVV_backup
// Для F9:  Считывание Бэкап-уставок текущей области в ОЗУ

word  F9_LoadUst(word start_addr_i2c)
{
  static byte copy_obl ;
  word ax;
  word bx;
  static word count;
  enum  { k0, k1, k10, k20, k25,
#ifdef _JOURNAL
        k26,
#endif
        }  ;
  ax = 4;


        switch ( Backup_label )
        {
          default: Backup_label= k0 ;
                  //----------------
          case k0 :
          case k1 :
                if ( Num_obl == 0 ) break; // ожидаем разблокировки от "АЕ-Зап.Устав"
                copy_obl = Num_obl;
#ifndef Num_obl  //  для агрегатов с несколькми областями
                Num_obl = 0 ; // "0"-блокирует запись уставок по "АЕ-Зап.Устав"
#endif
                Wr_label = 0 ;// на время перезагрузки уставок.
                Backup_label = k20 ;
                count = 0;
           break ;
             //-----------------------

          case k20 :

                // Происходит перезапись уставок из i2c в ОЗУ,
              bx = xRd_wr_ust (copy_obl, start_addr_i2c, 1);  // 08.02.2019 10:16. Уссурийск 5к. Проблемы с перезагрузкой областей
              if( bx == 4 );                       // уставок (проявилось на номиналах).Причина не установлена.
              else if( bx == 0 || count >= 3 )     // Виталик сказал - делаем повторы.
              {
#ifndef Num_obl
                Num_obl = copy_obl; // переключаем рабочую область уставок.
#endif
                Backup_label= k25 ;
              }
              else
              {
                count++;
                Wr_label = 0;
              }
             break ;
              //-----------------------
          case k25 :
                   //   Находим соответствие именам из рабочей таблицы имен
                   // в const-таблице.
              if ( TestSledTab() != 4 )
              {
#ifdef _JOURNAL
                Backup_label= k26 ;
#else
                ax = 0;
#endif
              }
             break ;
              //-----------------------

#ifdef _JOURNAL
          case k26 :
                   //   Находим соответствие именам из рабочей таблицы имен
                   // в const-таблице.
              if ( TestJrnTab ( 0 ) != 4 )
              {
                ax = 0;
              }
             break ;
              //-----------------------
#endif

        }

    return ax;
}



/* 22.05.2020 14:47 Перенесено в Monitor.h
    // Если не заданы внешние тексты сообщений, то задаем свои.
#ifndef    _TypeUst_Prompt
  #define  _TypeUst_Prompt   "\r\nТиповые уставки:"
  //#define  _RestoreNo_txt    "\rУстановить?-Нет "
  //#define  _RestoreYes_txt   "\rУстановить?-Да  "

  //KVV_backup
  #define  _RestoreNo_txt      "\rУстановить?-Нет "
  #define  _RestoreYes_txt     "\rУстан.Типовые   "
  #define  _RestoreWork_txt    "\rУстан.Рабочие   "
  #define  _RestoreBackUp_txt  "\rУстан.Резервныe "
#endif
*/
#ifndef P_CH

//   Программа пошагового востановления типовых уставок.

//KVV_backup
//      Два вида типовых уставок:
//  - Обычная запись уставок
//  - Бэкап запись уставок

void   Type_ustavki ( void )
{
  register byte bh ;

  static word addr_i2c;

      //   Следует следить, чтобы номера меток здесь и далее шли
      //  последовательно по возрастающей.
  enum { i0, i1, i2, i2_1, i2_2, i3, i4, i5, i6,
#ifdef _JOURNAL
         i60,
#endif
#ifdef _INTERPRETER
          i65,
#endif
         i7, i8, i71 };


              //  Контроль пароля: Полный запрет входа.

      if ( Password_control ( 2 ) == 0 )  return   ;
              //---


      if ( M_FirstCall == 1 )  /*  Идентификация первого входа для задания  */
        {                      /* начального условия ...                    */
          output_s ( _TypeUst_Prompt ) ;
          M_FirstCall = 0 ;
          Label = 0 ;
          m_index = 0;
        }

    switch ( Label )
     {
      default:
case i0:
               Label = i1 ;
      case i1:
          if ( TestCompleted_Output() )
            {
              if       ( m_index == 0 ) output_s ( _RestoreNo_txt  ) ;
              else  if ( m_index == 1 ) output_s ( _RestoreYes_txt ) ;
              else  if ( m_index == 2 ) output_s ( _RestoreWork_txt ) ;
              else  if ( m_index == 3 ) output_s ( _RestoreBackUp_txt ) ;
              Label = i2 ;
              break ;
            }
/*-----------------05.07.2019 -----------------
 *

Все закончил кроме пароля на бекап.

Далее зашивать проц и проверять для одноблочных затем для многоблочных
Сначала все меню
Затем сохранение в архив
Затем восстановление из архива
 * --------------------------------------------------*/


      case i2:

          if ( TestData_for_Input() )
            {
              mInput_c ( bh ) ;
                  if ( bh == Return )  /* Выход из этого режима */
                    {
                 end: Pult_Prog_Addr = _MainPultProg , M_FirstCall = 1 ;
                      return ;   // добавить еще какую-то иниц.
                    }
                  else if ( bh == Down ) /* Изменить выбор. */
                    {
                      if(m_index < 3) m_index++,  Label = i1 ;
                    }
                  else if ( bh == Up ) /* Изменить выбор. */
                    {
                      if(m_index > 0) m_index--,  Label = i1 ;
                    }
                  else if ( bh == Enter )
                    {
                      if ( m_index == 1 ) Label = i3 ;
                      else if ( m_index == 2 ) { Label = i2_1 ; addr_i2c = _ust_beg_adr_i2c; }
                      else if ( m_index == 3 ) { Label = i2_1 ; addr_i2c = _ust_beg_adr_i2c_backup; }
                      else goto end ;
                    }
                  else    Klav_Buff = bh;
            }
          break ;
//--------------
          //KVV_backup
          //  Востановление Бэкап-уставок
      case i2_1:  output_s (_Waiting_txt);
                  Backup_label= 0 ;
                  Label = i2_2 ;
      case i2_2:
           if( F9_LoadUst( addr_i2c ) == 4) return;
           Label = i71 ;
           break ;
//--------------

          //  Востановление Типовых-уставок
      case i3:
             _r = _c ;
           Label++ ;
           break ;
      case i4:
             _ar = _ac ;
             _or = _oc ;
           Label++ ;
           break ;
      case i5:
           TabFunc = c_TabFunc ;
           Label++ ;
           break ;
      case i6:
              sled = c_sled ;
           Label++ ;
           break ;
#ifdef _JOURNAL
      case i60:
              TabJrn = c_TabJrn ;
           Label++ ;
           break ;
#endif
#ifdef _INTERPRETER
      case i65:
            if (Cfg_str._.ust != 0)  _or.MemData =  Type_SetPoints;
           Label++ ;
           break ;
#endif
      case i7:
             // Взводим признак типовых уставок.
          _r.Begin_Code |= 0x8000 ;

      case i71:  //KVV_backup
              output_s( _Saved_txt ) ;
              m_time = Timer1_Ovr  ;
           Label = i8;
            break ;
      case i8:
              if ( (u)((w)(Timer1_Ovr-m_time)) > _Sec( 2.0 ) ) goto end ;
            break ;
     }
  return ;
}

#else

//   Программа пошагового востановления типовых уставок.

void   Type_ustavki ( void )
{
      //   Следует следить, чтобы номера меток здесь и далее шли
      //  последовательно по возрастающей.
  enum { i0, i1, i2, i3 ,
#ifdef _JOURNAL
         i30,
#endif
         i4 };


              //  Контроль пароля: Полный запрет входа.

      if ( Password_control ( 2 ) == 0 )  return   ;
              //---


      if ( M_FirstCall == 1 )  //  Идентификация первого входа для задани
        {                      // начального условия ...
          M_FirstCall = 0 ;
          Label = 0 ;
        }

    switch ( Label )
     {
      case i0:
             _r = _c ;
           Label++ ;
           break ;
      case i1:
             _ar = _ac ;
             _or = _oc ;
           Label++ ;
           break ;
      case i2:
             TabFunc = c_TabFunc ;
           Label++ ;
           break ;
      case i3:
           sled = c_sled ;
           Label++ ;
#ifdef _JOURNAL
           break ;
      case i30:
              TabJrn = c_TabJrn ;
           Label++ ;
#endif
          // Взводим признак типовых уставок.
          _r.Begin_Code |= 0x8000 ;
           break ;
      case i4:
              output_s( _TypeUst_prompt ) ;
              Pult_Prog_Addr = _MainPultProg , M_FirstCall = 1 ;
            break ;
     }
  return ;
}

#endif


// *******************************************************************
// *******************************************************************
//
//                  AE-Запись Уставок
//

/*
    case i4:
              // Чтение аналоговых уставок
              ax= xLoad_from_i2c ( sizeof( struct ABlok_Ustavok ) , (b*)_ar_adr_i2c , (b*)&_ar );
              goto ch;
    case i5:
              if ( Chek_sum ( sizeof( struct ABlok_Ustavok ) , (b*)&_ar ) != 0)
              {
                Mon.i2c_busy = 0 ;
                Wr_label=0;
                ax=2;
                break;
              }
              ax=4;
              i2c_label = 0;
              ++Wr_label;
              break;

 */
    // Если не заданы внешние тексты сообщений, то задаем свои.
#ifndef   _SaveUst_prompt
  #define  _SaveUst_prompt   "\r\nЗапись уставок:"
  #define  _Agregat_txt      "\r\n Объект:\r\n"
  #define  _SaveYes_txt      "\rЗаписать?-да ."
  #define  _SaveNo_txt       "\rЗаписать?-нет."
//KVV_backup
  #define  _SaveBackUp_txt   "\rРезервировать "
#endif

//    ПРОГРАММА  ЗАПИСИ  СКОРРЕКТИРОВАННЫХ  УСТАВОК ИЗ ОЗУ В FLASH-ПЗУ
//  ПОЛЬЗОВАТЕЛЕМ  ПОСРЕДСТВОМ  ПУЛЬТА  ЛИБО  КОМПЬЮТЕРА .

/*------------------------------------------------------------------*/
/*   Программа может быть вызвана только в фазе сборки готовности при
 * несобраной силовой цепи (что определяется по сигналу '1AK').
 *   Вызов программы осуществляется командой "AE" из режима диспетчера.
 *   После входа в программу пользователю по умолчанию предлагаетс
 * намерение не записывать уставки.
 *   Назначение активных клавиш следующее:
 * - '+'  - изменить намерение (заданное по умолчанию или перезаданное Вами) ;
 * - 'Enter' - выполнить установленное намерение.
 *   Выход из программы осуществляется нажатием клавиши 'Esc', при этом
 * значения уставок в ПЗУ остаются неизменными.
 */

//KVV_backup
//      Два вида записи уставок:
//  - Обычная запись уставок
//  - Бэкап запись уставок

void   UstRam_in_Flash ( void )
{
   register byte    bh ;
   static word command;

      //   Следует следить, чтобы номера меток здесь и далее шли
      //  последовательно по возрастающей.
enum { i00, i0, i1, i001x, i001, i01, i2, i3 };


              //  Контроль пароля: Полный запрет входа.

      if ( Password_control ( 2 ) == 0 )  return   ;
              //---


//     УБРАЛ ВЫБОР ОБЛАСТИ УСТАВОК - К ЕДРЕНЕЙ ФЕНЕ.

      if ( M_FirstCall == 1 )  /*  Идентификация первого входа для задания  */
        {                      /* начального условия ...                    */
          output_s ( _SaveUst_prompt ) ;
             //-------------
          M_FirstCall = 0 ;

          Label = i001x;
          m_index = 0;
          return ;
        }

               //---

    switch ( Label )
     {
      default:
      case i001x: output_s ( "\n" ) ;
                  Label = i001 ;
      case i001:
          if ( TestCompleted_Output() )
            {
              if ( m_index == 0 )       output_s ( _SaveNo_txt  ) ;
              else if ( m_index == 1 )  output_s ( _SaveYes_txt ) ;
              else if ( m_index == 2 )  output_s ( _SaveBackUp_txt ) ;
              Label = i01 ;
              break ;
            }

      case i01:

      if ( TestData_for_Input() )
        {
          mInput_c ( bh ) ;
              if ( bh == Return )  /* Выход из этого режима */
                {
             end: Pult_Prog_Addr = _MainPultProg , M_FirstCall = 1 ;
                  return ;   // добавить еще какую-то иниц.
                }
              else if ( bh == Down ) /* Изменить выбор. */
                {
                  if(m_index < 2) m_index++,  Label = i001 ;
                }
              else if ( bh == Up ) /* Изменить выбор. */
                {
                  if(m_index > 0) m_index--,  Label = i001 ;
                }
              else if ( bh == Enter )
                {
                  if ( m_index == 1 )       command = _Pult_Wr_ust;
                  else if ( m_index == 2 )  command = _Pult_BackUp_ust;
                  else goto end ;
                  output_s( _Waiting_txt ) ;
                  Label = i2 ;
                  Write_ust |= command;
                }
              else    Klav_Buff = bh;
        }

          break ;
                    // ожидание завершения записи.
      case i2:
                if ((Write_ust & command) != 0 ) break ;
                else if ((Write_ust & _Error_Wr_ust) == 0 )
                {
                  output_s ( _Saved_txt );
                }
                else  Write_ust &= ~_Error_Wr_ust ;
                m_time = Timer1_Ovr,  Label = i3 ;
           break;
      case i3:
              if ( (u)((w)(Timer1_Ovr-m_time)) > _Sec( 2.0 ) ) goto end;
            break ;

    }
  return ;
}


//--------------------------------------
//
//   АВТОНОМНАЯ ПРОГРАММА ЗАПИСИ УСТАВОК.
//
//KVV_backup
//      Два вида записи уставок:
//  - Обычная запись уставок
//  - Бэкап запись уставок

word xSave_Ust ( byte code )
{
  static byte Label_ust , cWrite_ust , copy_obl ;
  register byte    bh, ch ;

      //   Следует следить, чтобы номера меток здесь и далее шли
      //  последовательно по возрастающей.
enum { i0, i2, i3, i4, i5, i6, i7, i8, i9,
       i10, i11, i12, i13,
#ifdef _JOURNAL
       i120, i130,
#endif
       i14 };
      //-----------
        //  Перенесено из msg.c т.к. при появлении нового буфера для 'msg'
        // сообщение о типовых.уст. стало выводиться только после
        // второго прохода сообщений.
        //   В "_r.Begin_Code" старший бит - признак того,
        //  что приняты типовые уставки.
    if ( (_r.Begin_Code & 0x8000) != 0 )
          {  mSet_PreduprMsg( _Pr_TipUst ) ; }
    else  {  mClr_PreduprMsg( _Pr_TipUst ) ; }
    //-----

        //для стартовой инициализации.
    if ( code == 0 )
    {
      Write_ust = 0 ;
      cWrite_ust = 0 ;
      Label_ust = 0 ;
      return 0 ;
    }
      //-----------

    if ((Write_ust & ~_Error_Wr_ust) == 0 ) return 0 ;// команды на запись нет.
    else
    {   // Старт записи: разные программы дают запросы на запись разными битами.
      if ( cWrite_ust == 0 )
      {
        cWrite_ust = Write_ust & ~_Error_Wr_ust ; // копируем текущие запросы на запись.

        //  Разделяем на несколько обработок команды Запись и Бэкап
        //  если есть и команда Запись и Бэкап то выполняем первой Запись
//KVV_backup    -  убираем Бэкап запись если есть другие Записи
        if ((cWrite_ust & (~_Pult_BackUp_ust)) != 0 )
                {
                      cWrite_ust &= ~_Pult_BackUp_ust;
                }
      }
    }
      //-----------

    ch = 4 ;
    switch (  Label_ust )
    {
      case i0:        //  Ожидаем разблокировки записи уставок от программы перезагрузки уставок.
                  if ( Num_obl == 0 ) return ch;

                  // KVV 07-2019 перенес вверх перед adr_obl_ust чтобы никому не затереть адреса блоков уставок
                  if ( Mon.i2c_busy == 1 ) break; //  Ждем пока освободится шина.
                  Mon.i2c_busy = 1 ;  // Устанавливаем признак, что теперь шина занята.

//KVV_backup
                  if (cWrite_ust != _Pult_BackUp_ust)   adr_obl_ust ( Num_obl );
                  else                                  adr_obl_ust_backup ( Num_obl );


                  copy_obl = Num_obl ; // сохраняем значение блока уставок
          #ifndef  Num_obl    // если Num_obl задана константой, то нечего ее и проверять - это агрегат без резервов.
                  Num_obl = 0 ; // "0"-блокирует загрузку уставок в многорезервных агрегатах
          #endif
                     // Сбрасываем признак типовых уставок.
                  _r.Begin_Code &= 0x7fff ;
                  Label_ust = i2 ;
          //break ;

      case i2:
                  //if ( Mon.i2c_busy == 1 ) break; //  Ждем пока освободится шина.
                  //Mon.i2c_busy = 1 ;  // Устанавливаем признак, что теперь шина занята.
                   //  перезапись блока из ОЗУ во Flash
                      // Подсчет контрольной суммы.
                  Chek_sum ( sizeof( struct Blok_Ustavok ) , (b*)&_r ) ;
                  i2c_label = 0,  Label_ust++ ;
          break ;
      case i3:
                  bh = xSave_into_i2c ( sizeof( struct Blok_Ustavok ) , (b*)&_r , _r_adr_i2c ,_Adr_Flash_i2c ) ;
               goto read;
               //-----------------
      case i4:
                  Chek_sum ( sizeof( struct oBlok_Ustavok ) , (b*)&_or ) ;
                  i2c_label = 0,  Label_ust++ ;
          break ;
      case i5:
                  bh = xSave_into_i2c ( sizeof( struct oBlok_Ustavok ) , (b*)&_or ,  _or_adr_i2c,_Adr_Flash_i2c  ) ;
               goto read;
               //-----------------
      case i6:
                  Chek_sum ( sizeof( struct SBlok_Ustavok ) , (b*)&_sr ) ;
                  i2c_label = 0,  Label_ust++ ;
          break ;
      case i7:
                  bh = xSave_into_i2c ( sizeof( struct SBlok_Ustavok ) , (b*)&_sr ,  _sr_adr_i2c,_Adr_Flash_i2c  ) ;
               goto read;
               //-----------------
      case i8:
                  Chek_sum ( sizeof( struct ABlok_Ustavok ), (b*)&_ar) ;
                  i2c_label = 0,  Label_ust++ ;
          break ;
      case i9:
                  bh = xSave_into_i2c ( sizeof( struct ABlok_Ustavok ) , (b*)&_ar,  _ar_adr_i2c ,_Adr_Flash_i2c ) ;
               goto read;
               //-----------------
      case i10:
                  Chek_sum ( sizeof(TabFunc  ), (b*)&TabFunc ) ;
                  i2c_label = 0,  Label_ust++ ;
          break ;
      case i11:
                  bh = xSave_into_i2c ( sizeof( TabFunc ), (b*)&TabFunc, _TabFunc_adr_i2c,_Adr_Flash_i2c  ) ;
               goto read;
               //-----------------
      case i12:
                  Chek_sum ( sizeof( struct SLED ), (b*)&sled ) ;
                  i2c_label = 0,  Label_ust++ ;
          break ;
      case i13:
                  bh = xSave_into_i2c ( sizeof( struct SLED ), (b*)&sled,  _TablSled_adr_i2c,_Adr_Flash_i2c  ) ;
               goto read;
               //-----------------
#ifdef _JOURNAL
      case i120:
                  Chek_sum ( sizeof( struct TAB_JRN ), (b*)&TabJrn ) ;
                  i2c_label = 0,  Label_ust++ ;
          break ;
      case i130:
                  bh = xSave_into_i2c ( sizeof( struct TAB_JRN ), (b*)&TabJrn,  _TablJrn_adr_i2c,_Adr_Flash_i2c  ) ;
               goto read;
               //-----------------
#endif
      case i14:
               ch = 0 ;
         end:  Mon.i2c_busy = 0 ;  // Устанавливаем признак, что теперь шина свободна.
          #ifndef Num_obl
                  Num_obl = copy_obl ; // восстанавливаем значение блока уставок
          #endif
               Label_ust = i0 ;
               Write_ust &= ~cWrite_ust ; // сбрасываем отработанные запросы на запись.
               cWrite_ust = 0 ;
            break ;
               //-----------------
          read:
               if ( bh == 4 ) break;  // пока = 4 - продолжаем чтение.
               if ( bh == 1 )
                 {
                   output_s( _Error_i2c_txt ) ;
                   mSet_ServiceMsg( _Srv_NoWrite_i2c ) ;
                   Write_ust |= _Error_Wr_ust ;
                   ch = 1 ;
                   goto end ;
                 }
               else  Label_ust++ ;
               break;
               //-----------------
    }

  return ch ;
}

// Определение объема микросхемы i2c.
// 1. Читаем один байт с нулевого адреса.
// 2. Если на чтение микросхема отвечает - значит она установлена и исправна.
// 3. Считываем по два байта из последних адресов из расчета 8кб, 32кб, 64кб.
// 4. Пишем для каждого последнего адреса из расчета 64кб, 32кб, 8кб свой контрольный код.
//    Последним должен писаться контрольный код для 8кб, т.к. если на самом деле установлена микросхема на 8кб,
//    то этот контрольный код затрёт контрольный код для 32кб и 64кб.
// 5. Считываем два байта из последнего адреса из расчета 64кб.
// 6. Если считанные два байта в п.5 равны контрольному коду для 64кб - то микросхема на 64кб.
// 7. Если считанные два байта в п.5 равны контрольному коду для 32кб - то микросхема на 32кб.
// 8. Если считанные два байта в п.5 равны контрольному коду для 8кб - то микросхема на 8кб.
// 9. Восстанавливаем два байта, считанные в п.3.
// 10. В _i2c_end пишем 0x1fff для 8кб, 0x7fff для 32кб, 0xffff для 64кб.

// 06.02.2015 10:20
// п.1 и п.2 исключил и добавил повторы на случай ошибки чтения/записи.
// Ошибка проявилась у VMZ на плате F16K .004-03 0448.01.15 для КТЕ5-ВС-320 (Голиков).
// Иногда (причем после записи уставок) в п.1 при первом чтении 1-го байта функция Load_from_i2c возвращала 1 и
// объем i2c ошибочно принимался равным 8 кб с переходом в ОСТАНОВ.
//23.07.2019 добавлено определение 512кб  ЭОЗУ
/*
void Detect_i2c ( void )
{
  word ax, bx, cx;
  struct
  {
    word copy08k;
    word copy32k;
    word copy64k;
    word cod08k;
    word cod32k;
    word cod64k;
  } Detect;

  Detect.cod08k = 0x1234;
  Detect.cod32k = 0x5678;
  Detect.cod64k = 0xABCD;

  cx = 0;
povt1:
  cx++;
  if( cx <= 3 )
  {
     ax  = Load_from_i2c ( 2, _i2c_end_08k - 1, (b*)&Detect.copy08k, _Adr_Flash_i2c ); // п.3
     ax += Load_from_i2c ( 2, _i2c_end_32k - 1, (b*)&Detect.copy32k, _Adr_Flash_i2c );
     ax += Load_from_i2c ( 2, _i2c_end_64k - 1, (b*)&Detect.copy64k, _Adr_Flash_i2c );
     if ( ax != 0 )
     {
        mSet_ServiceMsg( _Srv_NoRead_i2c ) ;
        goto povt1;
     }
     mClr_ServiceMsg( _Srv_NoRead_i2c ) ;
  }
  else
  {
end:
     _i2c_end = _i2c_end_08k; // на всякий случай оставляем минимум
     return;
  }

  cx = 0;
povt2:
  cx++;
  if( cx <= 3 )
  {
     ax  = Save_into_i2c ( 2 , (b*)&Detect.cod64k, _i2c_end_64k - 1, _Adr_Flash_i2c ); //п.4  обязательно в таком порядке -
     ax += Save_into_i2c ( 2 , (b*)&Detect.cod32k, _i2c_end_32k - 1, _Adr_Flash_i2c ); // сначала в 64кб, потом в 32кб
     ax += Save_into_i2c ( 2 , (b*)&Detect.cod08k, _i2c_end_08k - 1, _Adr_Flash_i2c ); // и последним в 8кб
     if ( ax != 0 )
     {
        mSet_ServiceMsg( _Srv_NoWrite_i2c ) ;
        goto povt2;
     }
     mClr_ServiceMsg( _Srv_NoWrite_i2c ) ;
  }
  else goto end;

  cx = 0;
povt3:
  cx++;
  if( cx <= 3 )
  {
     bx = 0;
     ax = Load_from_i2c ( 2, _i2c_end_64k - 1, (b*)&bx, _Adr_Flash_i2c ); // п.5
     if ( ax != 0 )
     {
        mSet_ServiceMsg( _Srv_NoRead_i2c ) ;
        goto povt3;
     }
     mClr_ServiceMsg( _Srv_NoRead_i2c ) ;
  }
  else goto end;

  cx = 0;
povt4:
  cx++;
  if( cx <= 3 )
  {
     if ( bx == Detect.cod64k ) // п.6
     {
       _i2c_end = _i2c_end_64k;
       //output_s( "\n\r i2c = 64кб " ) ;
       ax  = Save_into_i2c ( 2 , (b*)&Detect.copy64k, _i2c_end_64k - 1, _Adr_Flash_i2c );
       ax += Save_into_i2c ( 2 , (b*)&Detect.copy32k, _i2c_end_32k - 1, _Adr_Flash_i2c );
       ax += Save_into_i2c ( 2 , (b*)&Detect.copy08k, _i2c_end_08k - 1, _Adr_Flash_i2c );
       if ( ax != 0 )
       {
          mSet_ServiceMsg( _Srv_NoWrite_i2c ) ;
          goto povt4;
       }
       else
       {
          mClr_ServiceMsg( _Srv_NoWrite_i2c ) ;
          return;
       }
     }
     else if ( bx == Detect.cod32k )  // п.7
     {
       _i2c_end = _i2c_end_32k;
       //output_s( "\n\r i2c = 32кб " ) ;
       ax  = Save_into_i2c ( 2 , (b*)&Detect.copy32k, _i2c_end_32k - 1, _Adr_Flash_i2c );
       ax += Save_into_i2c ( 2 , (b*)&Detect.copy08k, _i2c_end_08k - 1, _Adr_Flash_i2c );
       if ( ax != 0 )
       {
          mSet_ServiceMsg( _Srv_NoWrite_i2c ) ;
          goto povt4;
       }
       else
       {
          mClr_ServiceMsg( _Srv_NoWrite_i2c ) ;
          return;
       }
     }
     else if ( bx == Detect.cod08k ) // п.8
     {
       _i2c_end = _i2c_end_08k;
       //output_s( "\n\r i2c = 8кб " ) ;
       ax = Save_into_i2c ( 2 , (b*)&Detect.copy08k, _i2c_end_08k - 1, _Adr_Flash_i2c );
       if ( ax != 0 )
       {
          mSet_ServiceMsg( _Srv_NoWrite_i2c ) ;
          goto povt4;
       }
       else
       {
          mClr_ServiceMsg( _Srv_NoWrite_i2c ) ;
          return;
       }
     }
     else goto end;
  }
  else goto end;
}

*/

void Detect_i2c ( void )
{
#if !defined( _EEPROM) || defined(_Detect_i2c)
  word ax, bx, cx;
  struct
  {
    word copy08k;
    word copy32k;
    word copy64k;
    word copy512k;
    word cod08k;
    word cod32k;
    word cod64k;
    word cod512k;
  } Detect;

  Detect.cod08k = 0x1234;
  Detect.cod32k = 0x5678;
  Detect.cod64k = 0xABCD;
  Detect.cod512k = 0x4321;

  cx = 0;
povt1:
  cx++;
  if( cx <= 3 )
  {
     i2c_label = 0;
     ax  = Load_from_i2c ( 2, _i2c_end_08k - 1, (b*)&Detect.copy08k, _Adr_Flash_i2c ); // п.3
     ax += Load_from_i2c ( 2, _i2c_end_32k - 1, (b*)&Detect.copy32k, _Adr_Flash_i2c );
     ax += Load_from_i2c ( 2, _i2c_end_64k - 1, (b*)&Detect.copy64k, _Adr_Flash_i2c );
#if defined(_CM3_) & !defined(_Detect_i2c)
     ax += Load_from_i2c ( 2, _i2c_end_512k- 1, (b*)&Detect.copy512k, _Adr_Flash_i2c );
#endif
     if ( ax != 0 )
     {
        mSet_ServiceMsg( _Srv_NoRead_i2c ) ;
        goto povt1;
     }
     mClr_ServiceMsg( _Srv_NoRead_i2c ) ;
  }
  else
  {
end:
     _i2c_end = _i2c_end_08k; // на всякий случай оставляем минимум
     return;
  }

  cx = 0;
povt2:
  cx++;
  if( cx <= 3 )
  {
#ifdef _CM3_
#ifndef _Detect_i2c
     ax  = Save_into_i2c ( 2 , (b*)&Detect.cod512k, _i2c_end_512k - 1, _Adr_Flash_i2c );
#else
     ax = 0;
#endif
     ax += Save_into_i2c ( 2 , (b*)&Detect.cod64k , _i2c_end_64k - 1, _Adr_Flash_i2c ); //п.4  обязательно в таком порядке -
#else
     ax = Save_into_i2c ( 2 , (b*)&Detect.cod64k , _i2c_end_64k - 1, _Adr_Flash_i2c ); //п.4  обязательно в таком порядке -
#endif

     ax += Save_into_i2c ( 2 , (b*)&Detect.cod32k , _i2c_end_32k - 1, _Adr_Flash_i2c ); // сначала в 64кб, потом в 32кб
     ax += Save_into_i2c ( 2 , (b*)&Detect.cod08k , _i2c_end_08k - 1, _Adr_Flash_i2c ); // и последним в 8кб
     if ( ax != 0 )
     {
        mSet_ServiceMsg( _Srv_NoWrite_i2c ) ;
        goto povt2;
     }
     mClr_ServiceMsg( _Srv_NoWrite_i2c ) ;
  }
  else goto end;

  cx = 0;
povt3:
  cx++;
 /* ax = timer1;
  while ((timer1 - ax)< _MkSec());*/
  if( cx <= 3 )
  {
     bx = 0;
#if defined(_CM3_) & !defined(_Detect_i2c)
     ax = Load_from_i2c ( 2, _i2c_end_512k - 1, (b*)&bx, _Adr_Flash_i2c ); // п.5
#else
     ax = Load_from_i2c ( 2, _i2c_end_64k  - 1, (b*)&bx, _Adr_Flash_i2c ); // п.5
#endif
     if ( ax != 0 )
     {
        mSet_ServiceMsg( _Srv_NoRead_i2c ) ;
        goto povt3;
     }
     mClr_ServiceMsg( _Srv_NoRead_i2c ) ;
  }
  else goto end;

  cx = 0;
povt4:
  cx++;
  if( cx <= 3 )
  {
#ifdef _CM3_
     if ( bx == Detect.cod512k ) // п.6
     {
#ifndef _Detect_i2c
       _i2c_end = _i2c_end_512k;

       //output_s( "\n\r i2c = 64кб " ) ;
       ax  = Save_into_i2c ( 2 , (b*)&Detect.copy512k, _i2c_end_512k - 1, _Adr_Flash_i2c );
#else
        _i2c_end = _i2c_end_64k;
        ax = 0;
#endif
       ax += Save_into_i2c ( 2 , (b*)&Detect.copy64k, _i2c_end_64k - 1, _Adr_Flash_i2c );
       ax += Save_into_i2c ( 2 , (b*)&Detect.copy32k, _i2c_end_32k - 1, _Adr_Flash_i2c );
       ax += Save_into_i2c ( 2 , (b*)&Detect.copy08k, _i2c_end_08k - 1, _Adr_Flash_i2c );
       if ( ax != 0 )
       {
          mSet_ServiceMsg( _Srv_NoWrite_i2c ) ;
          goto povt4;
       }
       else
       {
          mClr_ServiceMsg( _Srv_NoWrite_i2c ) ;
          return;
       }
     }
     else if ( bx == Detect.cod64k ) // п.6
#else
          if ( bx == Detect.cod64k ) // п.6
#endif
     {
       _i2c_end = _i2c_end_64k;
       //output_s( "\n\r i2c = 64кб " ) ;
       ax  = Save_into_i2c ( 2 , (b*)&Detect.copy64k, _i2c_end_64k - 1, _Adr_Flash_i2c );
       ax += Save_into_i2c ( 2 , (b*)&Detect.copy32k, _i2c_end_32k - 1, _Adr_Flash_i2c );
       ax += Save_into_i2c ( 2 , (b*)&Detect.copy08k, _i2c_end_08k - 1, _Adr_Flash_i2c );
       if ( ax != 0 )
       {
          mSet_ServiceMsg( _Srv_NoWrite_i2c ) ;
          goto povt4;
       }
       else
       {
          mClr_ServiceMsg( _Srv_NoWrite_i2c ) ;
          return;
       }
     }
     else if ( bx == Detect.cod32k )  // п.7
     {
       _i2c_end = _i2c_end_32k;
       //output_s( "\n\r i2c = 32кб " ) ;
       ax  = Save_into_i2c ( 2 , (b*)&Detect.copy32k, _i2c_end_32k - 1, _Adr_Flash_i2c );
       ax += Save_into_i2c ( 2 , (b*)&Detect.copy08k, _i2c_end_08k - 1, _Adr_Flash_i2c );
       if ( ax != 0 )
       {
          mSet_ServiceMsg( _Srv_NoWrite_i2c ) ;
          goto povt4;
       }
       else
       {
          mClr_ServiceMsg( _Srv_NoWrite_i2c ) ;
          return;
       }
     }
     else if ( bx == Detect.cod08k ) // п.8
     {
       _i2c_end = _i2c_end_08k;
       //output_s( "\n\r i2c = 8кб " ) ;
       ax = Save_into_i2c ( 2 , (b*)&Detect.copy08k, _i2c_end_08k - 1, _Adr_Flash_i2c );
       if ( ax != 0 )
       {
          mSet_ServiceMsg( _Srv_NoWrite_i2c ) ;
          goto povt4;
       }
       else
       {
          mClr_ServiceMsg( _Srv_NoWrite_i2c ) ;
          return;
       }
     }
     else goto end;
  }
  else goto end;
#else //_EEPROM
  return;
#endif //_EEPROM
}

