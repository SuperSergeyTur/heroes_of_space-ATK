#ifndef  _FLASH_H
#define  _FLASH_H

word  Byte_Relock ( word n , lword addr_flash ,  byte* adrr_mem , word Save_m);
word Save_into_i2c(word n,byte *from, lword into, word c_addr);

#define  xSave_into_i2c(n,from,into,c_addr) Byte_Relock(n ,(lw)into, from , 1)

#define  xLoad_from_i2c(n,from,into,c_addr) Byte_Relock(n ,(lw)from ,into , 0)

//#define  Save_into_i2c(n,from,into,c_addr) while (Byte_Relock(n ,(lw)into, from , 1) == 4)
#define  Load_from_i2c(n,from,into,c_addr)  Byte_Relock(n ,(lw)from ,into , 0)

#define  _i2c_beg       ( 0x0 )
 //В начальной области оставляем область для служебных переменных в ЭОЗУ
 //размер области определяется в obj_def.h
//номер последней аварии
//#define  Last_Av_addr  _i2c_beg
//Адрес размещения в ЭОЗУ блока последней аварии
//#define  Addr_Av_addr  (_i2c_beg+2)
#define  WinTime_addr   _i2c_beg
#define  Calibr_addr    WinTime_addr+2

#define  FreeSpaceBeg   Calibr_addr+4 

#define   NarabSpaceBeg   FreeSpaceBeg
//#define  _i2c_end     0x7ffff

#define  _i2c_end_08k  (0x1FFF)  // Конечный адрес для i2c на 8кб
#define  _i2c_end_32k  (0x7FFF)  // Конечный адрес для i2c на 32кб
#define  _i2c_end_64k  (0xFFFF)  // Конечный адрес для i2c на 64кб
#define  _i2c_end_512k  (0x7FFFF)  // Конечный адрес для i2c на 512кб

#define  _flash_beg      (0x90000000)
#define  _flash_end      (0x9007ffff)

#define _Adr_Flash_i2c   0
#define _Adr_Clock_i2c   1

#ifndef  _MaxSaveSled
#define  _MaxSaveSled  4000
#endif
/*
typedef struct
{
  word CtrlCode;
  struct MSG_reg       Msg;
  struct SLED          sled;
  byte Sled_data[_MaxSaveSled];
} Av_Save;
*/
//#define Size_Block_Av_Save  sizeof(Av_Save)
//#define _MaxNumbAv  ((_i2c_av_end  - _i2c_av_beg) / Size_Block_Av_Save )
/* 22.03.2023 09:13 Перенесено в monitor.h
#ifndef   _SaveUst_prompt
  #define  _SaveUst_prompt   "\r\nЗапись уставок:"
  #define  _Agregat_txt      "\r\n Объект:\r\n"
  #define  _SaveYes_txt      "\rЗаписать?-да ."
  #define  _SaveNo_txt       "\rЗаписать?-нет."
  #define  _Saved_txt        "\r\n Записано. "
#endif
*/
__no_init byte Flash_Space[(_flash_end - _flash_beg + 1) ]@_flash_beg;
#define _Flash_size sizeof( Flash_Space )


//void load_obl_ust ( word num )  ;
word Rd_wr_ust (word num_obl)   ;
void   UstRam_in_Flash ( void ) ;
void   Type_ustavki ( void )    ;
word xSave_Ust ( byte code )    ;

#ifdef _FLASH_INCLUDE

lword  _i2c_end;
//word Store_Label, time_Store;
lword ttt[5];
//word dtx;
//word timeRW;
//Av_Save   Asave;
#else

extern lword  _i2c_end;
//extern word Store_Label, time_Store;
extern lword ttt[];
//extern Av_Save   Asave;

//extern word dtx;
//extern word timeRW;
#endif


#endif

