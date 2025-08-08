
//       НАБОР ВСЕХ ПРИМИТИВОВ ДЛЯ ФОРМИРОВАНИЯ АЛГОРИТМОВ
//  РАБОТЫ НА ЛИНИИ IэC В РЕЖИМЕ МАСТЕРА С ПОДЧИНЕННЫМИ АБОНЕНТАМИ.
//--------------------------------------------------

             /* второе имя для тестирования линии SDA на фазе ACK. */
#define    mACK()        mSDA()

             /* значение бита RD/WR в байте адреса при операции записи. */
#define    _WR_i2c        0x00
             /* значение бита RD/WR в байте адреса при операции чтения. */
#define    _RD_i2c        0x01

void   Start_i2c_bus( void )
{
  ICCR_CS = 0x1c; // 62 кГц
  ICCR_EN = 1;

  return ;
}


             /* Фоамиаование гбловип "Start" на линии IэC. */
void   Start_i2c( void )
{
  IBCR_MSS = 1;
  return ;
}

             /* Фоамиаование гбловип "Stop" на линии IэC. */
void   Stop_i2c( void )
{
  IBCR_MSS = 0;
  return ;
}


             /*  Установка строба "ACK", как запрос на квитирование
              * от мастера к помощнику. */
/*void   ACK_set( void )
{
    mSCL_clr()    ;
     Delay()      ;
    mSDA_set()    ;
      Delay()     ;
    mSCL_set()    ;
     Delay()      ;
  return ;
}


             /*  Сброс строба "ACK", как ответ на квитирование
              * от мастера к помощнику. */
/*void   ACK_clr( void )
{
      mSCL_clr()    ;
       Delay()      ;
      mSDA_clr()    ;
        Delay()     ;
      mSCL_set()    ;
       Delay()      ;
  return ;
}


             /* Сзивлвание байва б линии IэC. */
/*byte   Rd_byte_i2c (void)
{
  register  byte al , mask ;
        /* считывание осуществляется от старшего разряда к младшему. */
/*  for ( al = 0 , mask = 0x80 ; mask != 0 ; mask >>= 1 )
    {
      mSCL_clr()  ;
       Delay()    ;
      mSCL_set()  ;
       Delay()      ;
      if ( mSDA() == 1 ) al |= mask ;
    }
  return al ;
}



             /* Влдаза байва на линио IэC. */
/*void  Wr_byte_i2c ( byte data )
{
  register  byte al ;
        /* выдача осуществляется от старшего разряда к младшему. */
/*  for ( al = 8 ; al != 0 ; al-- , data <<= 1 )
    {
      mSCL_clr()  ;
       Delay()    ;
      if ( (sb)data < (sb)0 )  mSDA_set() ;
      else                     mSDA_clr() ;
       Delay()    ;
      mSCL_set()  ;
       Delay()    ;
    }
  return ;
} */


