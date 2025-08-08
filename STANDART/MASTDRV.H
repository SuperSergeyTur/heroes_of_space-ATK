
#ifndef mastdrv_h
#define mastdrv_h

#ifndef  _Extern_names
/*10.04.03 11:43
union CAN_CONFIG
{
  byte all ;
  struct
  {
    unsigned int vkl     : 1 ;  // откл. CAN -  программ и контроллера.
    unsigned int reInit  : 1 ;  // бит-команда дл€ переинициализации CAN по ходу работы.
  } _;
};

      //  ѕараметры канала CAN и владеющего им мастера (абонента).
   struct CAN_SETTING
   {
       byte   addr ;             // CAN-адрес порта в сети к которой он подкл.
       byte   master_addr_size ; // разр€дна€ сетка адреса мастера - фиксированна€.
       union  CAN_CONFIG config ;// не использ-с€
       byte   btime0  ;          // 1-€ настройка скорости порта
       byte   btime1  ;          // 2-€ настройка скорости порта
      //-------
       word   timeout ;  // дискрета timeout = 1мсек - фиксированна.
       byte   connect ;  // количество отсчитываемых дискрет тайм-аута.
       byte   addr_p ;   // адрес платы - не используетс€.
   }  ;
10.04.03 11:43*/

//ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ
#endif
//ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ

//   Ѕлок длинной записи с адресами счетчиками и прочим дл€
// работы механизма считывани€/записи массивов.
struct Long_IO_blk
{
  char  *addr ;  //   текущий адрес чтени€/записи длинной передачи.
  word  size ;   // "!=0" - оставшийс€ размер передаваемого блока - блок зан€т.
                 // "==0" - блок передан и свободен дл€ сновой операции.
  word  beg_size ; // исходный размер передаваемого блока - дл€ возможности
                 // расчета уже переданного кол-ва байт при обрыве передачи.
  byte dscr ;   //  номер переменной в перечне, котора€ зан€ла блок длинной передачи.
  byte cmd ;     //   команда за которой закреплена передача.
  byte repeat ;  // команда длинной передачи оборвалась - ее следует повторить.
};

      //  –егистраци€ ошибок св€зи с абонентом.
  struct  Abonent_error
  {
    byte send ;
    byte receive ;
  };

//------------------------------------------

struct CAN_MsrRxBuff
  {
    byte new_data  ;        // признак того, что по€вились новые данные.
    struct canMSG_hw msg ;  // буфер дл€ сообщени€.
  } ;

//------------------------------------------

       //  —труктура дл€ инициализации карточек абонентов дл€
      // компил€торов не имеющих инициализации смешанных структур
     //  из константных и неконстантных переменных.
struct  Abon_Init
{
          // адрес рабочей структуры.
        struct Abonent_form  *ab ;
     // адрес const структуры дл€ инициализации рабочей структуры.
  const struct Abonent_form  *c_ab ;
     //  адрес const таблицы переменных дл€ инициализации рабочей
     // таблицы переменных.
  const struct namevar *c_t_ab  ;
};

/*    ‘рагмент инициализации на базе вышеописанной структуры.
    //   —писок всех открытых таблиц абонентов дл€ их
    // систематизированной инициализации.

const struct  Abon_Init  tab_ab[] =
{
  { &ab1, &c_ab1, &c_t_ab1[0] },
  { &ab2, &c_ab2, &c_t_ab2[0] },
  { &ab3, &c_ab3, &c_t_ab3[0] }
};

const byte size_tab_ab =  sizeof(tab_ab) / sizeof(struct  Abon_Init) ;

  for ( bx = 0 ; bx < size_tab_ab ; bx++ )
  {       //  »нициализаци€ карточки абонента.
    *(tab_ab[bx].ab) = *(tab_ab[bx].c_ab) ;
          //  »нициализаци€ его таблицы переменных.
    for ( ax = 0 ; ax < tab_ab[bx].ab->size_var_tab ; ax++ )
                          tab_ab[bx].ab->var_tab[ax] = tab_ab[bx].c_t_ab[ax] ;
  }

 */
//------------------------------------------

#define   _AbCfg_Master  0x01

    //  —труктура описывающа€ одного абонента.
struct Abonent_form
{
    //  ѕользовательское наименование абонента.
  char*  ab_name ;
    //  Ќомер порта абонента.
  byte   port ;
    //  јдрес абонента.
  byte   ab_addr ;

  union  Config_abonent
  {
    byte all ;
    struct
    {
#ifndef _Union_FR
      unsigned int  master :1 ;
      unsigned int  rezerv :7 ;
#else
      byte          rezerv :7 ;
      byte          master :1 ;
#endif
    }_;
  } cfg ;

    //   оличество заполненных позиций таблицы набора переменных абонента.
  byte   size_var_tab ;
    //  “аблица описывающа€ набор переменных данного абонента.
  struct namevar *var_tab;
  //struct namevar  var_tab[_MaxVarTabSize];

    //  Ѕлок длинной записи - дл€ каждого абонента один блок, поскольку сам
  // абонент поддерживает одновременную работу только лишь с одним блоком.
  struct Long_IO_blk long_io ;

  struct Abonent_error err ;
};

struct Sleep_data  { word time, n_time ; } ;
         // набор оперативных данных дл€ работы на i-тый порт.
struct CAN_master_data
{
  volatile int  n_call ;
  volatile byte   read_label, dscr_label, varn_label, break_label ;
  //volatile byte   write_label ;

  struct CAN_MsrRxBuff  canMsrRxBuff ;
  struct Sleep_data     slpd ;
};

  //   опи€ оперативных данных функций.
struct Data_mast
{
  byte code ;//, n_call ;
  struct canMSG_hw smsg ;
  word time , bx , tst , ax , i ;
  // —труктура дл€ компоновки кода команды с пор€дковым номером посылки.
  union MSG_CMD  scmd ;
};
//***************************

word Receive_Monitor( byte port ) ;

//    «анесение в мастер-буфер прин€того сообщени€ (буфер на одно сообщение).
word  canInMsrBuffReceiveMsg( byte port, struct canMSG_hw *ptr ) ;

//    »звлечение из мастер-буфера прин€того сообщени€ дл€ обработки.
word canFromMsrBuffReceiveMsg( byte port, struct canMSG_hw *ptr ) ;

lword SetMasterToMaster_ID( byte port, byte master2_addr ) ;

word read_dscr( byte descriptor, struct Abonent_form *ptr, byte num_call ) ;

word can_slave ( byte port ) ;

word     read_var_name( struct Abonent_form *ptr, byte dscr, char *cptr, byte num_call ) ;
word can_read_var_name( struct Abonent_form *ptr, byte dscr, char *cptr, byte num_call ) ;

word master_read( char *descriptor, struct Abonent_form *ptr, byte num_call ) ;
word master_full_read( char *descriptor, struct Abonent_form *ptr ) ;

     // ‘ункци€ записи может быть как с подтверждающим ответом, так и без:
     //   master_xwrite( _Write_OpCode, ... )      - с ответом.
     //   master_xwrite( _QuickWrite_OpCode, ... ) - без ответа.
word master_xwrite( char OpCode, char *descriptor, struct Abonent_form *ptr, byte num_call ) ;

     //   »митируем, дл€ совместимости с прежними приложени€ми,
     // функцию записи с подтверждающим ответом.
#define master_write( descriptor, ptr, num_call ) \
        master_xwrite( _Write_OpCode, descriptor, ptr, num_call )

     //   »митируем функцию записи без подтверждающего ответа.
#define master_qwrite( descriptor, ptr, num_call ) \
        master_xwrite( _QuickWrite_OpCode, descriptor, ptr, num_call )

word master_full_write( char *descriptor, struct Abonent_form *ptr ) ;

word master_break( struct Abonent_form *ptr, byte cmd, byte num_call ) ;

word  can_mast_init ( byte port ) ;

word  can_init ( byte port ) ;

word xSleep( char num, struct Sleep_data *ptr, short Ntime ) ;

#define  write_label    read_label
/*ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ-*/
#ifdef  _MAIN_INCLUDE
/*ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ*/

struct canMSG_hw monitor_rmsg[ _Num_CAN_Ports];

struct CAN_master_data  can_md[ _Num_CAN_Ports] ;

struct Data_mast     read_data[ _Num_CAN_Ports] ;
struct Data_mast    write_data[ _Num_CAN_Ports] ;
struct Data_mast    break_data[ _Num_CAN_Ports] ;
struct Data_mast     dscr_data[ _Num_CAN_Ports] ;
struct Data_mast read_var_data[ _Num_CAN_Ports] ;

/*ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ*/
#else
/*ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ*/

extern struct CAN_master_data  can_md[] ;

extern struct canMSG_hw monitor_rmsg[];

extern struct Data_mast     read_data[] ;
extern struct Data_mast    write_data[] ;
extern struct Data_mast    break_data[] ;
extern struct Data_mast     dscr_data[] ;
extern struct Data_mast read_var_data[] ;

/*ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ*/
#endif
#endif
