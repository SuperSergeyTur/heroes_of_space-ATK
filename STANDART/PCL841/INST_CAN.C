

word  install_can ( void )
{
   float buf ;
   word i, ax, bx ;
   word xbtime0, xbtime1 ;
   word maddr, saddr, xmaster_addr_size, xtime_out ;

   FILE *fp ;
   //word  gSegment ;

//*********************************************
//****   Загрузка уставок по умолчанию.  *******
//*********************************************

    /* declare the can card segment address */
   gSegment = BASE_ADDR;

     // Рабочий порт платы PCL-841.
   MASTER_PORT       = _MASTER_canPORT ;
   SLAVE_PORT        = _SLAVE_canPORT ;

   xbtime0           = _CAN_btime0 ;
   xbtime1           = _CAN_btime1 ;
   maddr             = _MASTER_ADDR ;
   saddr             = _SLAVE_ADDR ;
   xmaster_addr_size = __MasterAddr_Size ;
   xtime_out         = __TIME_OUT ;

//*********************************************
//****   Загрузка уставок из файла данных.  *******
//*********************************************

   fp = fopen("can_dat.mp3","r") ;
   if ( fp == NULL )
     {
       //printf ("\n Ошибка открытия файла данных: \"can_dat.mp3\"\n\n") ;
       return 1 ;
     }
   else
     {
       if ( find_in_file( fp, "BASE_ADDR_PCL-841" ))
       {
         i = fscanf(fp,"%x",&ax ) ;
         if ( i != 0 && (int)i != EOF )  gSegment =  ax ;
       }
       if ( find_in_file( fp, "MASTER_PORT_PCL-841" ))
       {
         i = fscanf(fp,"%f",&buf ) ;
         if ( i != 0 && (int)i != EOF )  MASTER_PORT =  (w)(buf-1) ;
       }
       if ( find_in_file( fp, "SLAVE_PORT_PCL-841" ))
       {
         i = fscanf(fp,"%f",&buf ) ;
         if ( i != 0 && (int)i != EOF )  SLAVE_PORT =  (w)(buf-1) ;
       }
       //j = 0 ;
       if ( find_in_file( fp, "bt0" ))
       {
         i = fscanf(fp,"%x",&ax ) ;
         if ( i != 0 && (int)i != EOF )
         {
           if ( find_in_file( fp, "bt1" ))
           {
             i = fscanf(fp,"%x",&bx ) ;
             if ( i != 0 && (int)i != EOF )
              {
               xbtime0 = ax ;
               xbtime1 = bx ;
//               j = 1 ;
         } } }
       }
   //    if ( j == 0 ) printf("\r\n Структура данных в файле \"can_dat.mp3\" неверна.\r\n");

       if ( find_in_file( fp, "MASTER_ADDR" ))
       {
         i = fscanf(fp,"%f",&buf ) ;
         if ( i != 0 && (int)i != EOF ) maddr = buf ;
       }
       if ( find_in_file( fp, "SLAVE_ADDR" ))
       {
         i = fscanf(fp,"%f",&buf ) ;
         if ( i != 0 && (int)i != EOF ) saddr = buf ;
       }
       if ( find_in_file( fp, "MasterAddr_Size" ))
       {
         i = fscanf(fp,"%f",&buf ) ;
         if ( i != 0 && (int)i != EOF ) xmaster_addr_size = buf ;
       }

       if ( find_in_file( fp, "TIME_OUT" ))
       {
         i = fscanf(fp,"%f",&buf ) ;
         if ( i != 0 && (int)i != EOF )  xtime_out =  buf*1000 ;
       }

     }
  fclose( fp ) ;

        // значения скорости по умолчанию.
                   //133kHz=0x03;//100kHz=0x07  ; //0x01-400kHz ;//125kHz=0x43;   /* baud rate 125Kbps    */
                   //133kHz=0x39;//100kHz=0x16  ; //0x16-400    ;//125kHz=0x1c;
#ifdef  _CAN_MASTER    // включить Мастер-опции.
 if ( (sw)MASTER_PORT != ( -1 ) )
 {
   can_setting(MASTER_PORT).btime0 = xbtime0 ;
   can_setting(MASTER_PORT).btime1 = xbtime1 ;

   can_setting(MASTER_PORT).addr = maddr ;
   can_setting(MASTER_PORT).master_addr_size = xmaster_addr_size ;
   can_setting(MASTER_PORT).config._.master = 1 ;

     // Время максимального ожидание чтения из шины CAN.(word)
   mTime_out( MASTER_PORT ) = xtime_out ;
 }
#endif

 if ( (sw)SLAVE_PORT != ( -1 ) )
 {
   if ( SLAVE_PORT != MASTER_PORT )
   {
     can_setting(SLAVE_PORT).btime0 = xbtime0 ;
     can_setting(SLAVE_PORT).btime1 = xbtime1 ;

     can_setting(SLAVE_PORT).addr = saddr ;//ab3PU.ab_addr ;
     can_setting(SLAVE_PORT).master_addr_size = xmaster_addr_size ;
     can_setting(SLAVE_PORT).config._.master = 0 ;
     mTime_out( SLAVE_PORT ) = xtime_out ;
   }
 }
//*********************************************

       //юююююю Инижиализажип аппааавной забви CAN ююююююююю

    if ( canInitHW()== FAIL)
      {
       // clrscr();
       // cprintf("\n\n hardware initial is error ");
        return 2 ;
      }
       // если задали нулевой порт - значит функция "master" не используется.
#ifdef  _CAN_MASTER    // включить Мастер-опции.
   if ( (sw)MASTER_PORT != ( -1 ) )
   {
     if ( can_init ( MASTER_PORT ) != 0 )
     {
       //clrscr();
       //cprintf("\n\n can controller port %d configure is error ", MASTER_PORT);
       return 3 ;
     }
   }
#endif
       // если задали нулевой порт - значит функция "slave" не используется.
   if ( (sw)SLAVE_PORT != ( -1 ) )
   {
     if ( SLAVE_PORT != MASTER_PORT )
     {
       if ( can_init ( SLAVE_PORT ) != 0 )
       {
         //clrscr();
         //cprintf("\n\n can controller port %d configure is error ", SLAVE_PORT);
         return 3 ;
     } }
   }
//----------------------------------------------------
      //   Инициализация таблиц переменных в ОЗУ из константных
      // таблиц в ПЗУ.
 #ifdef  _CAN_MASTER    // включить Мастер-опции.
   init_var_mtab () ;
 #endif
   //-------------

  return 0 ;
}


//  Отключение аппаратной части CAN.

void  uninstall_can ( void )
{
    /*---- reset can controller	*/
    canReset( MASTER_PORT );
    if ( SLAVE_PORT != MASTER_PORT )  canReset( SLAVE_PORT );
    //canReset( 1 );
    //canExitHW(); // только возврат в нормальный режим прерываний.

  return ;
}
