
#ifndef mastdrv_h
#define mastdrv_h

#define    _CAN_SHARED  //  CAN-используется и другими программами

        //  Блок параметров для таблицы-перечня микро-мастеров.
struct MICRO_MASTER
{
  byte abonent_num ;
  byte port, obj_r, obj_w ;
  byte *sl_addr ;
  char *r_dscr1, *r_dscr2 ;
  char *w_dscr1, *w_dscr2 ;
};
//------
#include <microtab.h>
//------

         // набор оперативных данных для работы на i-тый порт.
struct CAN_master_data
{
  volatile byte   n_call ;
  volatile byte   read_label ;
  struct
  {
    byte receive ;
    byte send ;
  } err ;
};

  //  Копия оперативных данных функций.
struct Data_mast
{
  byte code ;//, n_call ;
  byte bh , i , tst ;
  struct canMSG_hw smsg ;
  word time ;
  // Структура для компоновки кода команды с порядковым номером посылки.
  union MSG_CMD  scmd ;
};
//***************************

word micro_master_init( word code ) ;
word micro_master( word code ) ;
word micro_master_read( const struct MICRO_MASTER *ptr, byte num_call ) ;
     // Функция записи может быть как с подтверждающим ответом, так и без:
     //   master_xwrite( _Write_OpCode, ... )      - с ответом.
word micro_master_xwrite( char OpCode, const struct MICRO_MASTER *ptr, byte num_call) ;

     //   Имитируем, для совместимости с прежними приложениями,
     // функцию записи с подтверждающим ответом.
#define micro_master_write( ptr, num_call ) \
        micro_master_xwrite( _Write_OpCode, ptr, num_call )

     //   Имитируем функцию записи без подтверждающего ответа.
#define micro_master_qwrite( ptr, num_call ) \
        micro_master_xwrite( _QuickWrite_OpCode, ptr, num_call )

#define  write_label    read_label
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/
#ifdef  _MAIN_INCLUDE
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/

struct CAN_master_data  can_md[ _Num_Micro_Master] ;

struct Data_mast     read_data[ _Num_Micro_Master] ;
//struct Data_mast    write_data[ _Num_CAN_Ports] ;

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/
#else
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/

extern struct CAN_master_data  can_md[] ;

extern struct Data_mast     read_data[] ;
//extern struct Data_mast    write_data[] ;

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/
#endif
#endif
