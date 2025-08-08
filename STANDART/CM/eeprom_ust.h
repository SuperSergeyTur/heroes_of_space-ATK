#ifndef  _EEPROM_UST_H
#define  _EEPROM_UST_H

//#undef _i2c_av_beg
//#define _i2c_av_beg  saveAv_beg

#define _Adr_Flash_i2c 0
#define _Adr_Clock_i2c 1
#define  _i2c_beg (0)
#define  _i2c_end ((EEPROM_PAGE_SIZE*EEPROM_PAGE_NUM)-1)

#define  WinTime_addr   _i2c_beg


typedef struct  straddrEEPROM
{
    word Page;
    word Offset;
} straddrEEPROM ;
/*
struct  addr_eeprom
{
   straddrEEPROM  r ;
   straddrEEPROM  _or;
   straddrEEPROM  ar;
   straddrEEPROM  sr;
   straddrEEPROM  sld;
   straddrEEPROM  avar;
};

#ifndef   _SaveUst_prompt
  #define  _SaveUst_prompt   "\r\nЗапись уставок:"
  #define  _Agregat_txt      "\r\n Объект:\r\n"
  #define  _SaveYes_txt      "\rЗаписать?-да ."
  #define  _SaveNo_txt       "\rЗаписать?-нет."
  #define  _Saved_txt        "\r\n Записано. "
#endif

#ifndef    _TypeUst_Prompt
  #define  _TypeUst_Prompt   "\r\nТиповые уставки:"
  #define  _RestoreYes_txt   "\rУстановить?-да ."
  #define  _RestoreNo_txt    "\rУстановить?-нет."
  #define  _TypeUst_txt      "\r\nТиповые уставки \r\nустановлены."
#endif
*/

word Init_ust_EEPROM(void);

word  xSave_into_i2c ( word n ,byte *from ,  word into , byte c_addr);
word  xLoad_from_i2c ( word n , word from , byte *into , byte c_addr);
word  Load_from_i2c ( word n , word from , byte *into, byte c_addr );
word  Save_into_i2c ( word n , byte *from , word into, byte c_addr );

void load_obl_ust ( word num )  ;
word Rd_wr_ust (word num_obl)   ;
void   UstRam_in_Flash ( void ) ;
void   Type_ustavki ( void )    ;
word xSave_Ust ( byte code )    ;

/*
#ifdef _EEPROM_INCLUDE

//struct  addr_eeprom EEPROM_addr;
//word saveAv_beg;

#else

extern struct  addr_eeprom EEPROM_addr;
extern word saveAv_beg;

#endif
*/
#endif //  _EEPROM_UST_H
