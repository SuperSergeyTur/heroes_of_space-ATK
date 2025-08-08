#ifndef _at24c64
#define _at24c64

#define  _i2c_beg       ( 0x000 )
 //В начальной области оставляем область для служебных переменных в ЭОЗУ
 //размер области определяется в obj_def.h
//номер последней аварии
//#define  Last_Av_addr  _i2c_beg
//Адрес размещения в ЭОЗУ блока последней аварии
//#define  Addr_Av_addr  (_i2c_beg+2)
#define  WinTime_addr   _i2c_beg
#define   FreeSpaceBeg   WinTime_addr+2
#define   NarabSpaceBeg   FreeSpaceBeg

#define  _i2c_end_08k  ((w)0x1FFF)  // Конечный адрес для i2c на 8кб
#define  _i2c_end_32k  ((w)0x7FFF)  // Конечный адрес для i2c на 32кб
#define  _i2c_end_64k  ((w)0xFFFF)  // Конечный адрес для i2c на 64кб
//#define  _i2c_end_512k  (0x7FFFF)  // Конечный адрес для i2c на 512кб


      /*   Аппаратный адрес микросхемы flash-памяти AT24C64.  */
#define    _Adr_AT24C16   0xA0

#ifndef    _Adr_Flash_i2c
  #define  _Adr_Flash_i2c     _Adr_AT24C16
#endif

#ifndef _Page_i2c

 #define _Page_i2c   32

#endif


#define  _I2c_dev   I2C_0



#ifdef  _MAIN_INCLUDE

word i2c_Pi, i2c_Ki, i2c_Ki_max;
word  ax_i2c ,bx_i2c , cx_i2c, time_i2c ;
word  _i2c_end;
word  size_block_rw ; // Размер записываемого блока без выхода из I2C

#else
extern word  ax_i2c ,bx_i2c, cx_i2c ,time_i2c ;
extern word i2c_Pi, i2c_Ki, i2c_Ki_max;
extern word  _i2c_end;
extern word  size_block_rw ;
#endif

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/

word  Save_into_i2c ( word n , byte *from ,  word into , byte c_addr) ;
word  Load_from_i2c ( word n ,  word from , byte *into , byte c_addr) ;
word  xSave_into_i2c ( word n ,byte *from ,  word into , byte c_addr) ;
word  xLoad_from_i2c ( word n , word from , byte *into , byte c_addr) ;
void  Detect_i2c ( void );
void init_i2c(void);

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/

#endif
