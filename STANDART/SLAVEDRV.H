
#ifndef _slavedrv_h
#define _slavedrv_h


//10.04.03 11:41#ifndef   _CAN_MASTER  //------- IFNDEF -----------
#ifndef _Num_CAN_Ports
  #define  _Num_CAN_Ports  1
#endif


#ifndef  _Extern_names

union CAN_CONFIG
{
  byte all ;
  struct
  {
#ifndef _Union_FR
    unsigned int vkl     : 1 ;  // откл. CAN -  программ и контроллера.
    unsigned int mcovkl  : 1 ;
    unsigned int master  : 1 ;
    unsigned int bt_125k : 1 ;
    unsigned int bt_250k : 1 ;
    unsigned int bt_1M   : 1 ;
    unsigned int bt_20k  : 1 ;
#else
    byte         rez1    : 1 ;
    byte         rez2    : 1 ;
    byte         bt_1M   : 1 ;
    byte         bt_250k : 1 ;
    byte         bt_125k : 1 ;
    byte         master  : 1 ;
    byte         mcovkl  : 1 ;
    byte         vkl     : 1 ;  // откл. CAN -  программ и контроллера.
#endif
  } _;
};
#define   _can_cfg_vkl         0x01
#define   _can_cfg_mcovkl      0x02
#define   _can_cfg_master      0x04
#define   _can_cfg_bt_125k     0x08
#define   _can_cfg_bt_250k     0x10
#define   _can_cfg_bt_1M       0x20


#ifndef _can_MCS_196
      //  Параметры канала CAN и владеющего им мастера (абонента).
   struct CAN_SETTING
   {
       byte   addr ;             // CAN-адрес порта в сети к которой он подкл.
       byte   master_addr_size ; // разрядная сетка адреса мастера - фиксированная.
       union  CAN_CONFIG config ;// не использ-ся
       byte   btime0  ;          // 1-я настройка скорости порта
       byte   btime1  ;          // 2-я настройка скорости порта
      //-------
       word   timeout ;  // дискрета timeout = 1мсек - фиксированна.
       byte   connect ;  // количество отсчитываемых дискрет тайм-аута.
       byte   addr_p ;   // адрес платы - не используется.
       word   rezerv  ;
   }  ;
#else
   struct CAN_SETTING
   {
       byte   addr ;             // CAN-адрес порта в сети к которой он подкл.
       byte   master_addr_size ; // разрядная сетка адреса мастера - фиксированная.
       union  CAN_CONFIG config ;// не использ-ся
       byte   btime0  ;          // 1-я настройка скорости порта
       byte   btime1  ;          // 2-я настройка скорости порта
      //-------
    #ifdef   _CAN_MASTER
       word   timeout ;  // дискрета timeout = 1мсек - фиксированна.
       byte   connect ;  // количество отсчитываемых дискрет тайм-аута.
       byte   addr_p ;   // адрес платы - не используется.
    #endif
   }  ;
#endif
/*10.04.03 11:45struct CAN_SETTING
{
    byte   addr ;
    byte   master_addr_size ;
    union  CAN_CONFIG config ;
    byte   btime0  ;
    byte   btime1  ;
} ; */
//10.04.03 11:41#endif //----- ENDIF ------------
//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД
#endif  //10.04.03 11:42
//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД


    //  Структура описывающая одну переменную.
struct namevar
{
  char *name;         /* имя данных (KOI - 8, OEM) */
  void *addr;         /* адpес данных */
  unsigned int lon;		/* длина данных  в байтах  */
  char type;          /*тип пеpеменной:
                              1-char, 1 байт
                              3-short, 2 байта
                          	  4-long, 4 байта
                              5-float, 4 байта
                              6-double, 8 байт
                              7-unsigned char, 1 байт
                              8-unsigned short, 2 байта
                              9-unsigned long, 4 байта
                              41-массив char,
                              42-массив short,
                              43-массив short,
                              44-массив long,
                              45-массив float,
                              46-массив double,
                              47-массив unsigned char,
                              48-массив unsigned short,
                              49-массив unsigned long,
                              77-битовая переменная (unsigned char)
                  */

  word  nom ;     /* Номинальная величина параметра */

  char  access ;  /* код доступа:
                         0-признак конца списка
                         1-только для чтения
                         2-для записи/чтения */
#ifdef _CANOPEN
 #ifdef _Union_FR // возможно только для FR . В 590м - нехватает памяти .
  word index;
  byte objcode;
 #endif
#ifdef _CM3_ // возможно только для FR . В 590м - нехватает памяти .
  word index;
  byte objcode;
 #endif
#endif
  char dscr;      /* Принятый от абонента дескриптор переменной. */
  word tag ;      /* Признак запроса дескриптора сервером. */

#ifdef ULTRALOGIK
  byte far *YesNo ;
//  byte Ok ;
#endif
};

struct SlaveVars   // Список таблиц переменных для n-портов.
{
  word size ;
  _x_far const struct namevar  *tab ;
} ;

           //  Время выдержки на передачу ответа мастеру.
#define  _TimeOut_long_io   _Sec(25.0)


struct LongSlv_IO_blk
{
  byte  *addr ;  //   текущий адрес чтения/записи длинной передачи.
  word  size ;   // "!=0" - оставшийся размер передаваемого блока - блок занят.
                 // "==0" - блок передан и свободен для сновой операции.
  lword id ;     //   адрес мастера, который запросил длинную передачу.
  byte cmd ;     //   команда за которой закреплена передача.
  word  time ;   // время последнего обращения мастера к длинной записи - для
};  // остчета тайм-аута на высвобождение блока, если мастер перестал обращаться так и не закончив запись.

//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД
//10.04.03 11:08#ifdef   _CAN_MASTER     //   Для Master.
//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД

struct CAN_SlvRxBuff
  {
    byte new_data  ;        // признак того, что появились новые данные.
    struct canMSG_hw msg ;  // буфер для сообщения.
  } ;

#define  _CanTxBuffSize     ((w) 0x02)
struct CAN_TxBuff
  {
    byte in, out, num ;
    struct canMSG_hw msg[_CanTxBuffSize] ;  // буфер для сообщения.
  } ;
//-------------------------
         // набор оперативных данных для работы на i-тый порт.
struct CAN_slave_data
{
  struct LongSlv_IO_blk  long_io ;

  byte canNewReceiveSlv , canNewSendSlv ; // признаки того, что появились новые данные.

  struct  canMSG_hw rmsg, smsg ;// SDELATY VREMENNYMI

      // Структура для компоновки кода команды с порядковым номером посылки.
  union MSG_CMD  cmd ;

  char canName_buff[_canName_max_size+1] ;

//10.04.03 11:06#ifdef   _CAN_MASTER     //   Для Master.
  struct CAN_SlvRxBuff  canSlvRxBuff ;
//10.04.03 11:06#endif
  struct CAN_TxBuff     TxBuff ;
};

//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД
//10.04.03 11:08#endif
//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД

extern word  can_init ( byte port ) ;
extern word  can_slv_init ( byte port ) ;
extern lword SetOwn_ID( byte port , byte address) ;
extern lword SetOwn_Mask( byte port ) ;
extern lword SetMasterToSlave_ID( byte port, byte slave_addr ) ;
extern word  can_config ( byte port ) ;
extern word  can_test ( byte port ) ;
extern word seek_index( byte port, char *ptr ) ;
extern word canSlaveDrive( byte port ) ;
extern word  canInTxBuffMsg( byte port, struct canMSG_hw *sptr ) ;
extern word  canFromTxBuffMsg( byte port ) ;

//    Занесение в slave-буфер принятого сообщения (буфер на одно сообщение).
extern word canInSlvBuffReceiveMsg( byte port, struct canMSG_hw *ptr ) ;

//    Извлечение из slave-буфера принятого сообщения для обработки.
extern word canFromSlvBuffReceiveMsg( byte port, struct canMSG_hw *ptr ) ;

extern word can_slave ( byte port ) ;

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/
#ifdef  _FLASH_INCLUDE
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/

struct CAN_slave_data  can_sd[ _Num_CAN_Ports]  ;

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/
#else
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/

extern struct CAN_slave_data  can_sd[]  ;

//extern const struct namevar  var_tab[] ;

         // Список таблиц переменных для n-портов.
//extern const struct SlaveVars  svar[] ;  // 12.08.2015 - перенесено в VAR_TAB.H .

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/
#endif
#endif
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/
