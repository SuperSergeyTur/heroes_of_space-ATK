#ifndef _i2c_time_h
#define _i2c_time_h

#define  _clock_i2c_beg       ( 0x0008 )
#define  _clock_i2c_end       ( 0x003f )

      /*   Аппаратный адрес микросхемы часов времени.  */
#define    _Adr_M41T56    0xD0

#ifndef    _Adr_Clock_i2c
  #define  _Adr_Clock_i2c     _Adr_M41T56
#endif

        //  Определения для часов реального времени.

  #define  _Adr_sec     0
  #define  _Adr_min     1
  #define  _Adr_hour    2
  #define  _Adr_day     3
  #define  _Adr_dat     4
  #define  _Adr_mon     5
  #define  _Adr_Contr   7

    struct I2C_time
    {
      byte b[8] ;
 /*                   D7...D4         D3...D0
          time.b[0]:   10 seconds       seconds      00-59
          time.b[1]:   10 minutes       minutes      00-59
          time.b[2]:   10 hours          hours      0-1/00-23
          time.b[3]:                     day         01-07
          time.b[4]:   10 date           date        01-31
          time.b[5]:   10 month          month       01-12
          time.b[6]:   10 years          years       00-99
          time.b[7]:   Control Byte
  */
    };

extern    word    Read_i2c_time( void ) ;
extern    void    PrintTime ( struct I2C_time* ptr ) ;
extern    void    xOvr_Time_Schet(struct I2C_time* ptr);
extern    void    xClock ( struct I2C_time* ptr);
extern    void    xClock_ust ( struct I2C_time* ptr);
        // Делаем подмены для совместимости.
#define   Ovr_Time_Schet()    xOvr_Time_Schet( &c_time )
#define   Clock()             xClock( &c_time )
#define   Clock_ust()         xClock_ust( &c_time )

/*------------------------------------------------*/
#ifdef _MAIN_INCLUDE
/*------------------------------------------------*/
  //Время в двоично-десятичной системе
    struct I2C_time c_time ;
 //Время в обычной системе
    struct I2C_time d_time ;
    byte Time_label;
    word I2C_Time_Ovr;
/*------------------------------------------------*/
#else
/*------------------------------------------------*/

extern struct I2C_time c_time ;
extern struct I2C_time d_time ;
extern byte Time_label;
extern word I2C_Time_Ovr;

/*------------------------------------------------*/

#endif
#endif
