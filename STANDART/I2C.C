
//       НАБОР ВСЕХ ПРИМИТИВОВ ДЛЯ ФОРМИРОВАНИЯ АЛГОРИТМОВ
//  РАБОТЫ НА ЛИНИИ IэC В РЕЖИМЕ МАСТЕРА С ПОДЧИНЕННЫМИ АБОНЕНТАМИ.
//--------------------------------------------------

             /* второе имя для тестирования линии SDA на фазе ACK. */
#define    mACK()        mSDA()

             /* значение бита RD/WR в байте адреса при операции записи. */
#define    _WR_i2c        0x00
             /* значение бита RD/WR в байте адреса при операции чтения. */
#define    _RD_i2c        0x01


             /* Фоамиаование гбловип "Start" на линии IэC. */
void   Start_i2c( void )
{
     mSDA_out();
     if ( mSDA() == 0 )    /*  Если линия SDA сброшена, */
       {                   /* ее следует предварительно */
         mSCL_clr()    ;   /* установить, сопроводив,   */
          Delay()      ;   /* нулевым стробом SCL.      */
         mSDA_set()    ;   /*                           */
          Delay()      ;
       }
     mSCL_set()   ;
      Delay()     ;
     mSDA_clr()   ;   /* Формирование условия "Start". */
      Delay()     ;
  return ;
}

             /* Фоамиаование гбловип "Stop" на линии IэC. */
void   Stop_i2c( void )
{
     mSCL_clr()    ;
      Delay()      ;
     mSDA_out()    ;
     mSDA_clr()    ;
       Delay()     ;
     mSCL_set()    ;
      Delay()      ;
     mSDA_set()    ;
       Delay()     ;
  return ;
}


             /*  Установка строба "ACK", как запрос на квитирование
              * от мастера к помощнику. */
void   ACK_set( void )
{
    mSCL_SDA_clr(); //mSCL_clr() 06.02.2015 9:13 чтобы убрать полочку на SDA 0.5мкс обнуляем одновременно SCL и SDA
//  mSDA_out()    ;
   //  Delay() ;// 20.11.03 16:15 Чтобы убрать полочку по ACK: выход на выход.
//  mSDA_set()    ;
     mSDA_in()    ;
      Delay()     ;
    mSCL_set()    ;
     Delay()      ;
  return ;
}


             /*  Сброс строба "ACK", как ответ на квитирование
              * от мастера к помощнику. */
void   ACK_clr( void )
{
      mSCL_clr()    ;
       Delay()      ;
      mSDA_out()    ;
      mSDA_clr()    ;
        Delay()     ;
      mSCL_set()    ;
       Delay()      ;
   //  в следующей по тексту команде переключать 'SDA' на 'in'
  //  следует только после переключения 'SCL' на нуль, чтобы не проскакивало
  // снятие подтверждения 'ACK'.

  return ;
}


             /* Сзивлвание байва б линии IэC. */
byte   Rd_byte_i2c (void)
{
  register  byte al , mask ;
        /* считывание осуществляется от старшего разряда к младшему. */
  for ( al = 0 , mask = 0x80 ; mask != 0 ; mask >>= 1 )
    {
      mSCL_clr()  ;
       Delay()    ;
      mSDA_in()   ;
      mSCL_set()  ;
       Delay()      ;
      if ( mSDA() == 1 ) al |= mask ;
    }
  return al ;
}



             /* Влдаза байва на линио IэC. */
void  Wr_byte_i2c ( byte data )
{
  register  byte al ;
        /* выдача осуществляется от старшего разряда к младшему. */
  for ( al = 8 ; al != 0 ; al-- , data <<= 1 )
    {
      mSCL_clr()  ;
      mSDA_out();  // стоит специально после "mSCL_clr()", чтобы не проскочило
       Delay()    ; // снятие "ACK", если оно было перед этим выставлено.
      if ( (sb)data < (sb)0 )  mSDA_set() ;
      else                     mSDA_clr() ;
       Delay()    ;
      mSCL_set()  ;
       Delay()    ;
    }
  return ;
}


