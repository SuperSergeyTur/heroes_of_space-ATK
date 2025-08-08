
word Init_ust_EEPROM(void)
{  //word ax;
   EEPROM_Init();
/*  //Заполнение структруры адресов
  EEPROM_addr.r.Page = 0;
  EEPROM_addr.r.Offset = _ust_beg_adr_i2c;

  ax = sizeof(struct Blok_Ustavok)+1+_ust_beg_adr_i2c;

  EEPROM_addr._or.Page = ax/EEPROM_PAGE_SIZE;
  EEPROM_addr._or.Offset = ax%EEPROM_PAGE_SIZE;

  ax += sizeof(struct oBlok_Ustavok)+1;

  EEPROM_addr.ar.Page = ax/EEPROM_PAGE_SIZE;
  EEPROM_addr.ar.Offset = ax%EEPROM_PAGE_SIZE;

  ax += sizeof(struct ABlok_Ustavok)+1;

  EEPROM_addr.sr.Page = ax/EEPROM_PAGE_SIZE;
  EEPROM_addr.sr.Offset = ax%EEPROM_PAGE_SIZE;

  ax += sizeof(struct SBlok_Ustavok)+1;

  EEPROM_addr.sld.Page = ax/EEPROM_PAGE_SIZE;
  EEPROM_addr.sld.Offset = ax%EEPROM_PAGE_SIZE;

  ax += sizeof(struct SLED)+1;
#ifndef _i2c_av_beg
  _i2c_av_beg = ax;

  if ( (ax/EEPROM_PAGE_SIZE) > EEPROM_PAGE_NUM) return 1;

  EEPROM_addr.avar.Page = ax/EEPROM_PAGE_SIZE;
  EEPROM_addr.avar.Offset = ax%EEPROM_PAGE_SIZE;
  //_i2c_end = (EEPROM_PAGE_SIZE*EEPROM_PAGE_NUM)-1;
#endif
   */
  return 0;

}

//  Подсчет контрольной суммы блока ОЗУ размером 'n' начиная с адреса
// 'from'.
//  Контрольная сумма записывается в последний байт заданного блока -
// этот байт должен быть зарезервирован под конрольную сумму.

word Chek_sum ( word n , byte *from )
{
  _register lword ax , bx ;
  word cx ;

  ax = (lw)from, bx = 0 , cx = 0 ;
  while ( ax < ( (lw)from + n - 1 ) )
    {
      bx -= *(b*)ax ;  // Подсчет контрольной суммы для
      ax++;           // всей таблицы кроме последнего байта.
    }
  if ( *(b*)ax != (b)bx )  cx = 1 ;

  *(b*)ax = bx ;  // Запись в последний байт таблицы уставок

   return cx ;
}
/*
void load_obl_ust (  word num )
{
byte bx = 0;
word ax, cx;
cx = num-1;
povt: bx++ ;
   if ( bx <= 3 )
   {
     ax =   EEPROM_Read( EEPROM_addr.r.Offset, EEPROM_addr.r.Page  , &_r , MODE_8_BIT, sizeof (struct Blok_Ustavok));
     ax +=  EEPROM_Read( EEPROM_addr._or.Offset, EEPROM_addr._or.Page, &_or, MODE_8_BIT, sizeof (struct oBlok_Ustavok));
     ax +=  EEPROM_Read( EEPROM_addr.ar.Offset, EEPROM_addr.ar.Page, &_ar, MODE_8_BIT, sizeof (struct ABlok_Ustavok));
     ax +=  EEPROM_Read( EEPROM_addr.sr.Offset, EEPROM_addr.sr.Page, &_sr, MODE_8_BIT, sizeof (struct SBlok_Ustavok));
     ax +=  EEPROM_Read( EEPROM_addr.sld.Offset, EEPROM_addr.sr.Page, &sled, MODE_8_BIT, sizeof (struct SLED));

  	  if ( (_r.Begin_Code & 0x7fff) != (_c.Begin_Code & 0x7fff) ) goto povt ;
      else
      {     // Подсчет контрольной суммы.
         ax  = Chek_sum ( sizeof( struct Blok_Ustavok ) , (b*)&_r ) ;
         ax += Chek_sum ( sizeof( struct ABlok_Ustavok ), (b*)&_ar) ;
         ax += Chek_sum ( sizeof( struct oBlok_Ustavok ), (b*)&_or) ;
         ax += Chek_sum ( sizeof( struct SBlok_Ustavok ), (b*)&_sr) ;
         ax += Chek_sum ( sizeof( struct SLED ), (b*)&sled ) ;

         if ( ax != 0 )
         {
            mSet_ServiceMsg( _Srv_NoCheckSum_i2c ) ;
            goto povt ;
         }
         mClr_ServiceMsg( _Srv_NoCheckSum_i2c ) ;
	  }
   }
   else
   {
        mSet_PreduprMsg( _Pr_TipUst ) ;
        _r = _c ; //  временное копирование блока в ОЗУ
        _ar = _ac ;
        _or = _oc ;
        _sr = _sc ;
        sled = c_sled ;
            // Взводим признак типовых уставок.
        _r.Begin_Code |= 0x8000 ;

   }
   return ;

}

*/
/*------------------------------------------------------------------*/
 /*   Вызов программы осуществляется командой "AE" из режима диспетчера.
 *   После входа в программу пользователю по умолчанию предлагается
 * намерение не записывать уставки.
 *   Назначение активных клавиш следующее:
 * - '+'  - изменить намерение (заданное по умолчанию или перезаданное Вами) ;
 * - 'Enter' - выполнить установленное намерение.
 *   Выход из программы осуществляется нажатием клавиши 'Esc', при этом
 * значения уставок в ПЗУ остаются неизменными.
 */
/*
void   UstRam_in_Flash ( void )
{
   register byte    bh ;

      //   Следует следить, чтобы номера меток здесь и далее шли
      //  последовательно по возрастающей.
enum { i00, i0, i1, i001x, i001, i01, i2, i3 };


              //  Контроль пароля: Полный запрет входа.

      if ( Password_control ( 2 ) == 0 )  return   ;
              //---


//     УБРАЛ ВЫБОР ОБЛАСТИ УСТАВОК - К ЕДРЕНЕЙ ФЕНЕ.

      if ( M_FirstCall == 1 )  //  Идентификация первого входа для задания  
        {                      // начального условия ...                    
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
              if ( m_index == 0 ) output_s ( _SaveNo_txt  ) ;
              else                output_s ( _SaveYes_txt ) ;
              Label = i01 ;
              break ;
            }

      case i01:

      if ( TestData_for_Input() )
        {
          mInput_c ( bh ) ;
              if ( bh == Return )  // Выход из этого режима 
                {
             end: Pult_Prog_Addr = _MainPultProg , M_FirstCall = 1 ;
                  return ;   // добавить еще какую-то иниц.
                }
              else if ( bh == Up || bh == Down ) // Изменить выбор. 
                {
                  m_index = ~m_index,  Label = i001 ;
                }
              else if ( bh == Enter )
                {
                  if ( m_index == 0 ) goto end ;
                  output_s( _Waiting_txt ) ;
                  Label = i2 ;
                  Write_ust |= _Pult_Wr_ust ;
                }
              else    Klav_Buff = bh;
        }

          break ;
                    // ожидание завершения записи.
      case i2:
                if ((Write_ust & _Pult_Wr_ust) != 0 ) break ;
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


//   Программа пошагового востановления типовых уставок.

void   Type_ustavki ( void )
{
  register byte bh ;
      //   Следует следить, чтобы номера меток здесь и далее шли
      //  последовательно по возрастающей.
  enum { i0, i1, i2, i3, i4};


              //  Контроль пароля: Полный запрет входа.

      if ( Password_control ( 2 ) == 0 )  return   ;
              //---


      if ( M_FirstCall == 1 )  //  Идентификация первого входа для задания  
        {                      // начального условия ...                    
          output_s ( _TypeUst_Prompt ) ;
          M_FirstCall = 0 ;
          Label = 0 ;
          m_index = 0;
        }

    switch ( Label )
     {
      default:
      case i0: output_s ( "\n" ) ;
               Label = i1 ;
      case i1:
          if ( TestCompleted_Output() )
            {
              if ( m_index == 0 ) output_s ( _RestoreNo_txt  ) ;
              else                output_s ( _RestoreYes_txt ) ;
              Label = i2 ;
              break ;
            }

      case i2:

          if ( TestData_for_Input() )
            {
              mInput_c ( bh ) ;
                  if ( bh == Return )  // Выход из этого режима 
                    {
                 end: Pult_Prog_Addr = _MainPultProg , M_FirstCall = 1 ;
                      return ;   // добавить еще какую-то иниц.
                    }
                  else if ( bh == Up || bh == Down ) // Изменить выбор. 
                    {
                      m_index = ~m_index,  Label = i1 ;
                    }
                  else if ( bh == Enter )
                    {
                      if ( m_index == 0 ) goto end ;
                      Label = i3 ;
                    }
                  else    Klav_Buff = bh;
            }
          break ;

      case i3:
             _r = _c ;
             _ar = _ac ;
             _or = _oc ;
             sled = c_sled ;
             // Взводим признак типовых уставок.
          _r.Begin_Code |= 0x8000 ;

              output_s( _TypeUst_txt ) ;
              m_time = Timer1_Ovr  ;
           Label++ ;
            break ;
      case i4:
              if ( (u)((w)(Timer1_Ovr-m_time)) > _Sec( 2.0 ) ) goto end ;
            break ;
     }
  return ;
}*/
/*
//--------------------------------------
//
//   АВТОНОМНАЯ ПРОГРАММА ЗАПИСИ УСТАВОК.
//

word xSave_Ust ( byte code )
{
  static byte Label_ust , cWrite_ust ;
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
      }
    }
      //-----------

    ch = 4 ;
    switch (  Label_ust )
    {
      case i0:        //  Ожидаем разблокировки записи уставок от программы перезагрузки уставок.
                  _r.Begin_Code &= 0x7fff ;
                  Label_ust = i2 ;
          break ;

      case i2:
                  if ( Mon.i2c_busy == 1 ) break; //  Ждем пока освободится шина.
                  Mon.i2c_busy = 1 ;  // Устанавливаем признак, что теперь шина занята.
                   //  перезапись блока из ОЗУ во Flash
                      // Подсчет контрольной суммы.
                  Chek_sum ( sizeof( struct Blok_Ustavok ) , (b*)&_r ) ;
                  i2c_label = 0,  Label_ust++ ;
          break ;
      case i3:
                bh =   EEPROM_Write( EEPROM_addr.r.Offset, EEPROM_addr.r.Page  , &_r , MODE_8_BIT, sizeof (struct Blok_Ustavok));
          read:
               if ( bh != TRUE )
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
      case i4:
                  Chek_sum ( sizeof( struct oBlok_Ustavok ) , (b*)&_or ) ;
                    Label_ust++ ;
                  break ;
      case i5:
                bh =   EEPROM_Write( EEPROM_addr._or.Offset, EEPROM_addr._or.Page  , &_or , MODE_8_BIT, sizeof (struct oBlok_Ustavok));
               goto read;
               //-----------------
      case i6:
                  Chek_sum ( sizeof( struct SBlok_Ustavok ) , (b*)&_sr ) ;
                  Label_ust++ ;
          break ;
      case i7:
                bh =   EEPROM_Write( EEPROM_addr.sr.Offset, EEPROM_addr.sr.Page  , &_sr , MODE_8_BIT, sizeof (struct SBlok_Ustavok));
               goto read;
               //-----------------
      case i8:
                  Chek_sum ( sizeof( struct ABlok_Ustavok ), (b*)&_ar) ;
                  Label_ust++ ;
          break ;
      case i9:
                bh =   EEPROM_Write( EEPROM_addr.ar.Offset, EEPROM_addr.ar.Page  , &_ar , MODE_8_BIT, sizeof (struct ABlok_Ustavok));
               goto read;
               //-----------------
       case i10:
                  Chek_sum ( sizeof( struct SLED ), (b*)&sled) ;
                  Label_ust++ ;
          break ;
     case i11:
                bh =   EEPROM_Write( EEPROM_addr.sld.Offset, EEPROM_addr.sld.Page  , &sled , MODE_8_BIT, sizeof (struct SLED));
               goto read;
               //-----------------
      case i12:
               ch = 0 ;
         end:  Mon.i2c_busy = 0 ;  // Устанавливаем признак, что теперь шина свободна.
               Label_ust = i0 ;
               Write_ust &= ~cWrite_ust ; // сбрасываем отработанные запросы на запись.
               cWrite_ust = 0 ;
            break ;
               //-----------------
    }

  return ch ;
}
*/

//замена стандартных функций чтения-записи, на функции EEPROM
word  xSave_into_i2c ( word n ,byte *from ,  word into , byte c_addr)
{
  struct  straddrEEPROM intoEEPROM;
  word bh;

  intoEEPROM.Page = into/EEPROM_PAGE_SIZE;
  intoEEPROM.Offset = into%EEPROM_PAGE_SIZE;

  bh = EEPROM_Write( intoEEPROM.Offset, intoEEPROM.Page  , from , MODE_8_BIT, n);
  if ( bh != TRUE) return 1;
  else return 0;
}

word  xLoad_from_i2c ( word n , word from , byte *into , byte c_addr)
{
  struct  straddrEEPROM intoEEPROM;
  word bh;

  intoEEPROM.Page = from/EEPROM_PAGE_SIZE;
  intoEEPROM.Offset = from%EEPROM_PAGE_SIZE;

  bh = EEPROM_Read(intoEEPROM.Offset, intoEEPROM.Page  , into , MODE_8_BIT, n);
  if ( bh != TRUE) return 1;
  else return 0;

}

   //    Функция-переходник для совместимости xSave_into_i2c и
   //  Save_into_i2c для ранее написанных программ.

word  Save_into_i2c ( word n , byte *from , word into, byte c_addr )
{
  register word ax ;

  i2c_label = 0 ;
  do
  {
    ax = xSave_into_i2c ( n , from , into, c_addr ) ;
    if ( ax == 1 )   break;
  } while ( ax == 4 );

  return ax ;
}


   //    Функция-переходник для совместимости xLoad_from_i2c и
   //  Load_from_i2c для ранее написанных программ.

word  Load_from_i2c ( word n , word from , byte *into, byte c_addr )
{
  register word ax ;

  i2c_label = 0 ;
  do
  {
    ax = xLoad_from_i2c ( n , from , into, c_addr ) ;
    if ( ax == 1 )   break;
  } while ( ax == 4 );

  return ax ;
}
/*
//  KVV_backup  07.2019
//  Добавлена область BackUp-уставок
//  Развернутые комментарии смотри в monitor.h.

//  KVV_backup: Ввел параметр для возможности вызова этой функции для бэкап-ставок

void xadr_obl_ust ( word num_obl, word start_addr_i2c )
  {
     // word ax ;

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
   word ax, bx, cx = 0;

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

       }
   return ;
 }
*/