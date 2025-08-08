#ifndef _sled_h
#define _sled_h

#ifndef      _SizeSledPole
  #ifdef     _Union_FR
    #ifndef  _32K_RAM
       #define  _SizeSledPole       4000
    #else
       #define  _SizeSledPole      32000
    #endif
  #elif _CM3_
       #define  _SizeSledPole      32000
  #else
       #define  _SizeSledPole      2000
  #endif
#endif

#ifndef    _Sled_Vresion
  #define  _Sled_Vresion   0x10
#endif

void Start_Sled ( void ) ;
void Sled ( void )       ;
//void SledPrint ( void )  ;
void SetSledTab ( void ) ;
word  TestSledTab ( void ) ;


        /* Команда пуска-остановки следа. */
        // След пускается только тогда, когда нет ни одной команды остановки.
//  #ifdef  _Link

      #define  bi_SledStop  ( Prg._.Sled == 0 || sl_d.Stop != 0 \
      || L_sts._.off_sled == 1 )

//  #else

//      #define  bi_SledStop  ( Prg._.Sled == 0 || sl_d.Stop != 0 )

//  #endif

  #define  bo_SledStart     Prg._.Sled

        // Признак того, что след остановился после команды остановки.
  #define  bo_SledActiv    sl_d.activ


        /* Максимальное количество ячеек заносимых в след */
  #define  _SledTabSizeMax  ( 24 )

//-----------Одна струутура для следа и журнала-----------------
struct MENU1S
{
  char const *txt; // текст меню
  byte label;      // метка
};

// Структура блока данных для описания отдельной переменной таблицы следа.

#define _NameSize  12

struct Sled_var
{
  char txt[_NameSize] ;  // текстовое наименование переменной
  void *addr ;     // адрес переменной
  union
  {
    word all ;
#ifndef   _Union_FR
    struct
    {
      word  type     : 3 ;  // тип уставки:0-float, 1-char, 2-word,  // VSEV 02.17.2020  3-double
      word  off_sign : 1 ;  // '=1'- беззнаковое
      word print_type: 2 ;  // распечатка: 0,1-hex, 2-dec, 3-bin.
      word  celoe    : 3 ;  // количество цифр целой части
      word  drob     : 2 ;  // количество цифр дробн.части
    } _ ;
#else
    struct
    {
      word  rezerv   : 5 ;  // резерв.
      word  drob     : 2 ;  // количество цифр дробн.части
      word  celoe    : 3 ;  // количество цифр целой части
      word print_type: 2 ;  // распечатка: 0,1-hex, 2-dec, 3-bin.
      word  off_sign : 1 ;  // '=1'- беззнаковое
      word  type     : 3 ;  // тип уставки: 1-char, 2-word
    } _ ;
#endif
  } code;

  word  nom ;  // номинальное значение параметра
               //в программных дискретах
  word *abs_nom;//адрес ячейки номинала в абсолютных
                //единицах
  char txt2[5] ; // текст для отображения физической  //ед.измер. данного парам.
  char rezerv[3] ;// резерв - добиваем до 32-байтной   //кратности размера структуры, для //удобства ее просмотра из монитора.
} ;

                /* задание кода формата отображения переменной для режима  */
               /* редактирования уставок (по вышеописанному битовому полю):  */
               /* type  -  1,2 - тип переменной: 1 - однобайтная, 2 - двухбайтная.  */
               /* off_sign  -  1 - не отображать знак  */
               /* print_type -  распечатка: 0,1-hex, 2-dec, 3-bin.   */
               /* celoe -  1...5 - количество символов до запятой (целая часть)  */
               /* drob  -  0...3 - количество символов после запятой (дробная часть)  */
               /*   Задание "celoe=0" эквивалентно "celoe=3, drob=2" - для  */
               /* совместимости с уже сформированными таблицами переменных.  */
#define  _sl_form(type,off_sign,print_type,celoe,drob)  (( type )|    \
                                                 ( off_sign << 3 )|   \
                                                 ( print_type << 4 )| \
                                                 ( celoe << 6 )|    \
                                                 ( drob << 9 ))
//-----------------------------

     // Текстовая таблица типов данных для сервисной программы.
  struct Sled_var_short
  {
    char txt[_NameSize] ;  // текстовое наименование переменной
  //  byte ptr ; // указатель на соотв. данные в базовой таблице.
    //const struct Sled_var *ptr ;// указатель на соотв. данные в базовой таблице.
  };

//-----------------------------
       //  Рабочая таблица в ОЗУ.
struct SLED
{
  byte  type   ;
  lword  save_mem ; // объем памяти фрагмента следа сохраняемый в i2c после аварии.
  word  dt_scan ; //  интервал времени тактирования следа
  word  dt_stop ; //  сколько тактовых интервалов произв.запись после аварии
  word  kratn ;   //  каждый i-й такт на котором производить запись.
  word  t_start;  //  Время автоматического старта
  byte  n_kanal ; //  количество каналов таблицы заносимых в след.
  byte  page_size ; // Количество строк в странице при распечатке следа.
  struct Sled_var_short  tab [  _SledTabSizeMax ] ;
  //struct Sled_var        tabx ;//[ _xSledTabSizeMax ] ;// таблица переменных задаваемых
  byte  check_sum ;                               // адресом.
};
//----------------------------

     // Текстовая таблица типов данных для сервисной программы.
  struct Sled_Types
  {
    char *txt ;
    word code ;
    char txt2 ;
  };

//   В самом начале области следа i2c расположен указатель (word) адреса конца
// данных последней записи фрагмента следа.
         //  Одна страница следа в i2c включает в себя:
         //  регистры авар., предупр., служебн. сообщений;
         //  таблицу адресов следа;
         //  сам след из N последних пульсов.
//  Размер страницы закладываем из условия максимального кол-ва каналов.
#define  _i2c_av_page   ( sizeof(struct MSG_reg) + sizeof(struct SLED) + sled.save_mem )

struct SLED_data
{
  lword index   ; /* Указатель памяти в поле следа */
  lword print_size ;        /* Распечатываемый размер следа. */
  lword index_stop ;
  //word count, count2, time ; 20.10.04 15:10
  word time_out ;
  word count, count2 ;
  byte label, activ, Stop  ; // триггер остановки/запуска следа.
     //  указатель на соотв. данные в базовой таблице.
  byte tab [  _SledTabSizeMax ] ;
};
// ******************************************************************
           // Централизованная вставка для всех 'var_tab.h'

           //      В ТАБЛИЦЕ НИЧЕГО НЕ СДВИГАТЬ И НЕ ПЕРЕСТАВЛЯТЬ - ВИТАЛИК!
           //   В ССТ ИСПОЛЬЗУЕТСЯ ДЛЯ CAN-DLL И В РЭ С ФИКСИРОВАННЫМИ НОМЕРАМИ.

#ifdef _CANOPEN
       // Группа 4  - Еще один набор регистров аварий в 2-х байтном исполнении для ModBus.
#define  _Var_tab_InsertSled  \
  { "Sled"  ,  &SledPole   ,      sizeof(SledPole), _CHAR_array_type,  0,  _READ_access , 0x2100, _ARRAY },  \
  { "SldCom",  &sl_d.Stop  ,                     1, _CHAR_type,  0,  _READ_WRITE_access , 0x2101,   _VAR },  \
  { "SldSts",  &sl_d.activ ,                     1, _CHAR_type,  0,  _READ_WRITE_access , 0x2102,   _VAR },  \
  { "Device", (b*)_Device_Name_, sizeof(_Device_Name_), _CHAR_array_type,  0,  _READ_access , 0x2103, _ARRAY },  \
  { "Date"  ,(b*)__DATETIME__  ,  sizeof(__DATETIME__), _CHAR_array_type,  0,  _READ_access , 0x2104, _ARRAY },  \
  { "UstWr" ,  &Write_ust                      , 1, _CHAR_type,  0,  _READ_WRITE_access , 0x2105,   _VAR },  \
  { "MsgD"  ,  &msg_reg.time                   , 8, _CHAR_array_type,  0,  _READ_access , 0x2106,   _VAR },  \
  { "MsgF"  ,  &msg_reg._.avar_first           , 4, _LONG_type,  0,        _READ_access , 0x2107,   _VAR },  \
  { "MsgA"  ,  &msg_reg._.avar                 , 4, _LONG_type,  0,        _READ_access , 0x2108,   _VAR },  \
  { "MsgP"  ,  &msg_reg._.predupr              , 4, _LONG_type,  0,        _READ_access , 0x2109,   _VAR },  \
  { "MsgS"  ,  &msg_reg._.service              , 4, _LONG_type,  0,        _READ_access , 0x210a,   _VAR },  \
  { "MsgF2" ,  &msg_reg._.avar_first2          , 4, _LONG_type,  0,        _READ_access , 0x210b,   _VAR },  \
  { "MsgA2" ,  &msg_reg._.avar2                , 4, _LONG_type,  0,        _READ_access , 0x210c,   _VAR },  \
  { "MsgP2" ,  &msg_reg._.predupr2             , 4, _LONG_type,  0,        _READ_access , 0x210d,   _VAR },  \
  { "MsgS2" ,  &msg_reg._.service2             , 4, _LONG_type,  0,        _READ_access , 0x210e,   _VAR },  \
_Var_tab_TRETIY_REG1 \
  { "MsgDa" ,  &msg_av.time                    , 8, _CHAR_array_type,  0,  _READ_access , 0x2113,   _VAR },  \
  { "MsgFa" ,  &msg_av._.avar_first            , 4, _LONG_type,  0,        _READ_access , 0x2114,   _VAR },  \
  { "MsgAa" ,  &msg_av._.avar                  , 4, _LONG_type,  0,        _READ_access , 0x2115,   _VAR },  \
  { "MsgPa" ,  &msg_av._.predupr               , 4, _LONG_type,  0,        _READ_access , 0x2116,   _VAR },  \
  { "MsgSa" ,  &msg_av._.service               , 4, _LONG_type,  0,        _READ_access , 0x2117,   _VAR },  \
  { "MsgF2a",  &msg_av._.avar_first2           , 4, _LONG_type,  0,        _READ_access , 0x2118,   _VAR },  \
  { "MsgA2a",  &msg_av._.avar2                 , 4, _LONG_type,  0,        _READ_access , 0x2119,   _VAR },  \
  { "MsgP2a",  &msg_av._.predupr2              , 4, _LONG_type,  0,        _READ_access , 0x211a,   _VAR },  \
  { "MsgS2a",  &msg_av._.service2              , 4, _LONG_type,  0,        _READ_access , 0x211b,   _VAR },  \
_Var_tab_TRETIY_REG2 \
  { "MsgFh" ,  &msg_reg._.avar_first.w_reg.h   , 2, _SHORT_type, 0,        _READ_access , 0x2120,   _VAR },  \
  { "MsgFl" ,  &msg_reg._.avar_first.w_reg.l   , 2, _SHORT_type, 0,        _READ_access , 0x2121,   _VAR },  \
  { "MsgAh" ,  &msg_reg._.avar.w_reg.h         , 2, _SHORT_type, 0,        _READ_access , 0x2122,   _VAR },  \
  { "MsgAl" ,  &msg_reg._.avar.w_reg.l         , 2, _SHORT_type, 0,        _READ_access , 0x2123,   _VAR },  \
  { "MsgPh" ,  &msg_reg._.predupr.w_reg.h      , 2, _SHORT_type, 0,        _READ_access , 0x2124,   _VAR },  \
  { "MsgPl" ,  &msg_reg._.predupr.w_reg.l      , 2, _SHORT_type, 0,        _READ_access , 0x2125,   _VAR },  \
  { "MsgSh" ,  &msg_reg._.service.w_reg.h      , 2, _SHORT_type, 0,        _READ_access , 0x2126,   _VAR },  \
  { "MsgSl" ,  &msg_reg._.service.w_reg.l      , 2, _SHORT_type, 0,        _READ_access , 0x2127,   _VAR },  \
  { "MsgF2h",  &msg_reg._.avar_first2.w_reg.h  , 2, _SHORT_type, 0,        _READ_access , 0x2128,   _VAR },  \
  { "MsgF2l",  &msg_reg._.avar_first2.w_reg.l  , 2, _SHORT_type, 0,        _READ_access , 0x2129,   _VAR },  \
  { "MsgA2h",  &msg_reg._.avar2.w_reg.h        , 2, _SHORT_type, 0,        _READ_access , 0x212a,   _VAR },  \
  { "MsgA2l",  &msg_reg._.avar2.w_reg.l        , 2, _SHORT_type, 0,        _READ_access , 0x212b,   _VAR },  \
  { "MsgP2h",  &msg_reg._.predupr2.w_reg.h     , 2, _SHORT_type, 0,        _READ_access , 0x212c,   _VAR },  \
  { "MsgP2l",  &msg_reg._.predupr2.w_reg.l     , 2, _SHORT_type, 0,        _READ_access , 0x212d,   _VAR },  \
  { "MsgS2h",  &msg_reg._.service2.w_reg.h     , 2, _SHORT_type, 0,        _READ_access , 0x212e,   _VAR },  \
  { "MsgS2l",  &msg_reg._.service2.w_reg.l     , 2, _SHORT_type, 0,        _READ_access , 0x212f,   _VAR },  \
_Var_tab_TRETIY_REG3 \
  { "MsgTxt",  (void*)&Tabl_Msg,sizeof(Tabl_Msg)  , _CHAR_array_type,  0,  _READ_access , 0x2138, _ARRAY },  \
  { "SlTabU",  &s_tx      ,sizeof(s_tx)      ,_CHAR_array_type,  0,  _READ_WRITE_access , 0x2139, _ARRAY },  \
  { "SlTemp",  &s_short[0],sizeof(s_short[0]),_CHAR_array_type,  0,  _READ_WRITE_access , 0x213a, _ARRAY },  \
  { "SlTem1",  &s_short[1],sizeof(s_short[1]),_CHAR_array_type,  0,  _READ_WRITE_access , 0x213b, _ARRAY },  \
  { "Ver"   ,  (b*)&L_Ver                      , 1, _CHAR_type,  0,        _READ_access , 0x213c,   _VAR },  \
  { "PrTab" ,  &P_Tab.bits.all                 , 1, _CHAR_type,  0,  _READ_WRITE_access , 0x213d,   _VAR },  \
  { "Numb"  ,  &P_Tab.numb                     , 1, _CHAR_type,  0,  _READ_WRITE_access , 0x213e,   _VAR },  \
  { "rez_07",  (w*)&crezerv                    , 2, _SHORT_type, 0,        _READ_access , 0x213f,   _VAR }
  //   32 - строки: больше не добавлять, открывать новое имя.
#else
       // Группа 4  - Еще один набор регистров аварий в 2-х байтном исполнении для ModBus.
//  { "TmSled",  &TmpSled   ,      sizeof(TmpSled), _CHAR_array_type,  0,  _READ_WRITE_access},
#define  _Var_tab_InsertSled \
  { "Sled"  ,  &SledPole   ,      sizeof(SledPole), _CHAR_array_type,  0,  _READ_access },  \
  { "SldCom",  &sl_d.Stop  ,                     1, _CHAR_type,  0,  _READ_WRITE_access },  \
  { "SldSts",  &sl_d.activ ,                     1, _CHAR_type,  0,  _READ_WRITE_access },  \
  { "Device", (b*)_Device_Name_, sizeof(_Device_Name_), _CHAR_array_type,  0,  _READ_access },  \
  { "Date"  , (b*)__DATETIME__  ,  sizeof(__DATETIME__), _CHAR_array_type,  0,  _READ_access },  \
  { "UstWr" ,  &Write_ust                      , 1, _CHAR_type,  0,  _READ_WRITE_access },  \
  { "MsgD"  ,  &msg_reg.time                   , 8, _CHAR_array_type,  0,  _READ_access },  \
  { "MsgR"  ,  &msg_reg._                      , sizeof(msg_reg._), _CHAR_array_type,  0,  _READ_access },  \
  { "MsgF"  ,  &msg_reg._.avar_first           , 4, _LONG_type,  0,        _READ_access },  \
  { "MsgA"  ,  &msg_reg._.avar                 , 4, _LONG_type,  0,        _READ_access },  \
  { "MsgP"  ,  &msg_reg._.predupr              , 4, _LONG_type,  0,        _READ_access },  \
  { "MsgS"  ,  &msg_reg._.service              , 4, _LONG_type,  0,        _READ_access },  \
  { "MsgF2" ,  &msg_reg._.avar_first2          , 4, _LONG_type,  0,        _READ_access },  \
  { "MsgA2" ,  &msg_reg._.avar2                , 4, _LONG_type,  0,        _READ_access },  \
  { "MsgP2" ,  &msg_reg._.predupr2             , 4, _LONG_type,  0,        _READ_access },  \
  { "MsgS2" ,  &msg_reg._.service2             , 4, _LONG_type,  0,        _READ_access },  \
  { "MsgDa" ,  &msg_av.time                    , 8, _CHAR_array_type,  0,  _READ_access },  \
  { "MsgRa" ,  &msg_av._                       , 8, _CHAR_array_type,  0,  _READ_access },  \
  { "MsgFa" ,  &msg_av._.avar_first            , 4, _LONG_type,  0,        _READ_access },  \
  { "MsgAa" ,  &msg_av._.avar                  , 4, _LONG_type,  0,        _READ_access },  \
  { "MsgPa" ,  &msg_av._.predupr               , 4, _LONG_type,  0,        _READ_access },  \
  { "MsgSa" ,  &msg_av._.service               , 4, _LONG_type,  0,        _READ_access },  \
  { "MsgF2a",  &msg_av._.avar_first2           , 4, _LONG_type,  0,        _READ_access },  \
  { "MsgA2a",  &msg_av._.avar2                 , 4, _LONG_type,  0,        _READ_access },  \
  { "MsgP2a",  &msg_av._.predupr2              , 4, _LONG_type,  0,        _READ_access },  \
  { "MsgS2a",  &msg_av._.service2              , 4, _LONG_type,  0,        _READ_access },  \
  { "MsgFh" ,  &msg_reg._.avar_first.w_reg.h   , 2, _SHORT_type, 0,        _READ_access },  \
  { "MsgFl" ,  &msg_reg._.avar_first.w_reg.l   , 2, _SHORT_type, 0,        _READ_access },  \
  { "MsgAh" ,  &msg_reg._.avar.w_reg.h         , 2, _SHORT_type, 0,        _READ_access },  \
  { "MsgAl" ,  &msg_reg._.avar.w_reg.l         , 2, _SHORT_type, 0,        _READ_access },  \
  { "MsgPh" ,  &msg_reg._.predupr.w_reg.h      , 2, _SHORT_type, 0,        _READ_access },  \
  { "MsgPl" ,  &msg_reg._.predupr.w_reg.l      , 2, _SHORT_type, 0,        _READ_access },  \
  { "MsgSh" ,  &msg_reg._.service.w_reg.h      , 2, _SHORT_type, 0,        _READ_access },  \
  { "MsgSl" ,  &msg_reg._.service.w_reg.l      , 2, _SHORT_type, 0,        _READ_access },  \
  { "MsgF2h",  &msg_reg._.avar_first2.w_reg.h  , 2, _SHORT_type, 0,        _READ_access },  \
  { "MsgF2l",  &msg_reg._.avar_first2.w_reg.l  , 2, _SHORT_type, 0,        _READ_access },  \
  { "MsgA2h",  &msg_reg._.avar2.w_reg.h        , 2, _SHORT_type, 0,        _READ_access },  \
  { "MsgA2l",  &msg_reg._.avar2.w_reg.l        , 2, _SHORT_type, 0,        _READ_access },  \
  { "MsgP2h",  &msg_reg._.predupr2.w_reg.h     , 2, _SHORT_type, 0,        _READ_access },  \
  { "MsgP2l",  &msg_reg._.predupr2.w_reg.l     , 2, _SHORT_type, 0,        _READ_access },  \
  { "MsgS2h",  &msg_reg._.service2.w_reg.h     , 2, _SHORT_type, 0,        _READ_access },  \
  { "MsgS2l",  &msg_reg._.service2.w_reg.l     , 2, _SHORT_type, 0,        _READ_access },  \
_Var_tab_TRETIY_REG  \
  { "MsgTxt",  (void*)&Tabl_Msg,sizeof(Tabl_Msg)  , _CHAR_array_type,  0,  _READ_access },  \
  { "SlTabU",  &s_tx      ,sizeof(s_tx)     , _CHAR_array_type,  0,  _READ_WRITE_access },  \
  { "SlTemp",  &s_short[0],sizeof(s_short[0]),_CHAR_array_type,  0,  _READ_WRITE_access },  \
  { "SlTem1",  &s_short[1],sizeof(s_short[1]),_CHAR_array_type,  0,  _READ_WRITE_access },  \
  { "Ver"   ,  (b*)&L_Ver                      , 1, _CHAR_type,  0,        _READ_access },  \
  { "PrTab" ,  &P_Tab.bits.all                 , 1, _CHAR_type,  0,  _READ_WRITE_access },  \
  { "Numb"  ,  &P_Tab.numb                     , 1, _CHAR_type,  0,  _READ_WRITE_access },  \
  { "rez_07",  (w*)&crezerv                    , 2, _SHORT_type, 0,        _READ_access }
  //   32 - строки: больше не добавлять, открывать новое имя.
#endif


#ifndef _TRETIY_REG

  #define  _Var_tab_TRETIY_REG1   \
  { "MsgF3" ,  (w*)&crezerv                    , 4, _LONG_type,  0,        _READ_access , 0x210f,   _VAR },  \
  { "MsgA3" ,  (w*)&crezerv                    , 4, _LONG_type,  0,        _READ_access , 0x2110,   _VAR },  \
  { "MsgP3" ,  (w*)&crezerv                    , 4, _LONG_type,  0,        _READ_access , 0x2111,   _VAR },  \
  { "MsgS3" ,  (w*)&crezerv                    , 4, _LONG_type,  0,        _READ_access , 0x2112,   _VAR },

  #define  _Var_tab_TRETIY_REG2   \
  { "MsgF3a",  (w*)&crezerv                    , 4, _LONG_type,  0,        _READ_access , 0x211c,   _VAR },  \
  { "MsgA3a",  (w*)&crezerv                    , 4, _LONG_type,  0,        _READ_access , 0x211d,   _VAR },  \
  { "MsgP3a",  (w*)&crezerv                    , 4, _LONG_type,  0,        _READ_access , 0x211e,   _VAR },  \
  { "MsgS3a",  (w*)&crezerv                    , 4, _LONG_type,  0,        _READ_access , 0x211f,   _VAR },

  #define  _Var_tab_TRETIY_REG3   \
  { "MsgF3h",  (w*)&crezerv                    , 2, _SHORT_type, 0,        _READ_access , 0x2130,   _VAR },  \
  { "MsgF3l",  (w*)&crezerv                    , 2, _SHORT_type, 0,        _READ_access , 0x2131,   _VAR },  \
  { "MsgA3h",  (w*)&crezerv                    , 2, _SHORT_type, 0,        _READ_access , 0x2132,   _VAR },  \
  { "MsgA3l",  (w*)&crezerv                    , 2, _SHORT_type, 0,        _READ_access , 0x2133,   _VAR },  \
  { "MsgP3h",  (w*)&crezerv                    , 2, _SHORT_type, 0,        _READ_access , 0x2134,   _VAR },  \
  { "MsgP3l",  (w*)&crezerv                    , 2, _SHORT_type, 0,        _READ_access , 0x2135,   _VAR },  \
  { "MsgS3h",  (w*)&crezerv                    , 2, _SHORT_type, 0,        _READ_access , 0x2136,   _VAR },  \
  { "MsgS3l",  (w*)&crezerv                    , 2, _SHORT_type, 0,        _READ_access , 0x2137,   _VAR },

  #define  _Var_tab_TRETIY_REG

#else

  #define  _Var_tab_TRETIY_REG1  \
  { "MsgF3" ,  &msg_reg._.avar_first3          , 4, _LONG_type,  0,        _READ_access , 0x210f,   _VAR },  \
  { "MsgA3" ,  &msg_reg._.avar3                , 4, _LONG_type,  0,        _READ_access , 0x2110,   _VAR },  \
  { "MsgP3" ,  &msg_reg._.predupr3             , 4, _LONG_type,  0,        _READ_access , 0x2111,   _VAR },  \
  { "MsgS3" ,  &msg_reg._.service3             , 4, _LONG_type,  0,        _READ_access , 0x2112,   _VAR },

  #define  _Var_tab_TRETIY_REG2  \
  { "MsgF3a",  &msg_av._.avar_first3           , 4, _LONG_type,  0,        _READ_access , 0x211c,   _VAR },  \
  { "MsgA3a",  &msg_av._.avar3                 , 4, _LONG_type,  0,        _READ_access , 0x211d,   _VAR },  \
  { "MsgP3a",  &msg_av._.predupr3              , 4, _LONG_type,  0,        _READ_access , 0x211e,   _VAR },  \
  { "MsgS3a",  &msg_av._.service3              , 4, _LONG_type,  0,        _READ_access , 0x211f,   _VAR },

  #define  _Var_tab_TRETIY_REG3  \
  { "MsgF3h",  &msg_reg._.avar_first3.w_reg.h  , 2, _SHORT_type, 0,        _READ_access , 0x2130,   _VAR },  \
  { "MsgF3l",  &msg_reg._.avar_first3.w_reg.l  , 2, _SHORT_type, 0,        _READ_access , 0x2131,   _VAR },  \
  { "MsgA3h",  &msg_reg._.avar3.w_reg.h        , 2, _SHORT_type, 0,        _READ_access , 0x2132,   _VAR },  \
  { "MsgA3l",  &msg_reg._.avar3.w_reg.l        , 2, _SHORT_type, 0,        _READ_access , 0x2133,   _VAR },  \
  { "MsgP3h",  &msg_reg._.predupr3.w_reg.h     , 2, _SHORT_type, 0,        _READ_access , 0x2134,   _VAR },  \
  { "MsgP3l",  &msg_reg._.predupr3.w_reg.l     , 2, _SHORT_type, 0,        _READ_access , 0x2135,   _VAR },  \
  { "MsgS3h",  &msg_reg._.service3.w_reg.h     , 2, _SHORT_type, 0,        _READ_access , 0x2136,   _VAR },  \
  { "MsgS3l",  &msg_reg._.service3.w_reg.l     , 2, _SHORT_type, 0,        _READ_access , 0x2137,   _VAR },

  #define  _Var_tab_TRETIY_REG  \
  { "MsgF3" ,  &msg_reg._.avar_first3          , 4, _LONG_type,  0,        _READ_access },  \
  { "MsgA3" ,  &msg_reg._.avar3                , 4, _LONG_type,  0,        _READ_access },  \
  { "MsgP3" ,  &msg_reg._.predupr3             , 4, _LONG_type,  0,        _READ_access },  \
  { "MsgS3" ,  &msg_reg._.service3             , 4, _LONG_type,  0,        _READ_access },  \
  { "MsgF3a",  &msg_av._.avar_first3           , 4, _LONG_type,  0,        _READ_access },  \
  { "MsgA3a",  &msg_av._.avar3                 , 4, _LONG_type,  0,        _READ_access },  \
  { "MsgP3a",  &msg_av._.predupr3              , 4, _LONG_type,  0,        _READ_access },  \
  { "MsgS3a",  &msg_av._.service3              , 4, _LONG_type,  0,        _READ_access },  \
  { "MsgF3h",  &msg_reg._.avar_first3.w_reg.h  , 2, _SHORT_type, 0,        _READ_access },  \
  { "MsgF3l",  &msg_reg._.avar_first3.w_reg.l  , 2, _SHORT_type, 0,        _READ_access },  \
  { "MsgA3h",  &msg_reg._.avar3.w_reg.h        , 2, _SHORT_type, 0,        _READ_access },  \
  { "MsgA3l",  &msg_reg._.avar3.w_reg.l        , 2, _SHORT_type, 0,        _READ_access },  \
  { "MsgP3h",  &msg_reg._.predupr3.w_reg.h     , 2, _SHORT_type, 0,        _READ_access },  \
  { "MsgP3l",  &msg_reg._.predupr3.w_reg.l     , 2, _SHORT_type, 0,        _READ_access },  \
  { "MsgS3h",  &msg_reg._.service3.w_reg.h     , 2, _SHORT_type, 0,        _READ_access },  \
  { "MsgS3l",  &msg_reg._.service3.w_reg.l     , 2, _SHORT_type, 0,        _READ_access },

#endif


#ifdef  _Sld_cond

#ifndef _CM3_
 #define  Write_RTC  crezerv
 #define  l_time     crezerv
#endif

#undef    _Sled_Vresion
  #define  _Sled_Vresion   0x22

#ifdef _CANOPEN
#define  _Var_tab_InsertSled2 \
  { "Cnumb" , (w*)&_r.Start_cond.numb          , 2, _SHORT_type, 0,  _READ_WRITE_access , 0x2200,   _VAR },  \
  { "Cnumb1", (w*)&_r.Stop_cond.numb           , 2, _SHORT_type, 0,  _READ_WRITE_access , 0x2201,   _VAR },  \
  { "Cmean" , (w*)&_r.Start_cond.mean          , 2, _SHORT_type, 0,  _READ_WRITE_access , 0x2202,   _VAR },  \
  { "Cmean1", (w*)&_r.Stop_cond.mean           , 2, _SHORT_type, 0,  _READ_WRITE_access , 0x2203,   _VAR },  \
  { "Cbits" , (w*)&_r.Start_cond.bits.all      , 2, _SHORT_type, 0,  _READ_WRITE_access , 0x2204,   _VAR },  \
  { "Cbits1", (w*)&_r.Stop_cond.bits.all       , 2, _SHORT_type, 0,  _READ_WRITE_access , 0x2205,   _VAR },  \
  { "Cdelst", (w*)&_r.DelayTime_Start          , 2, _SHORT_type, 0,  _READ_WRITE_access , 0x2202,   _VAR },  \
  { "Cdelsp", (w*)&_r.DelayTime_Stop           , 2, _SHORT_type, 0,  _READ_WRITE_access , 0x2203,   _VAR },  \
  { "Cfilst", (w*)&_r.FiltrTime_Start          , 2, _SHORT_type, 0,  _READ_WRITE_access , 0x2204,   _VAR },  \
  { "Cfilsp", (w*)&_r.FiltrTime_Stop           , 2, _SHORT_type, 0,  _READ_WRITE_access , 0x2205,   _VAR },  \
  { "WR_RTC", (w*)&Write_RTC                   , 2, _SHORT_type, 0,  _READ_WRITE_access , 0x2206,   _VAR },  \
  { "DateTm", (w*)&l_time         , sizeof(l_time), _CHAR_array_type, 0,  _READ_WRITE_access,0x2207,_VAR }
  { "OsclPt", (w*)&OscPtrs                     , 4, _CHAR_array_type, 0,  _READ_WRITE_access,0x2208,_VAR },  \
  { "OsclVr", (w*)&LanOsclOut, sizeof (LanOsclOut), _CHAR_array_type, 0,  _READ_access      ,0x2209,_VAR },\
  { "MsgTst", (w*)&crezerv,                      2, _SHORT_type, 0,  _READ_access      ,0x220a,_VAR }

#else //_CANOPEN
#define  _Var_tab_InsertSled2 \
  { "Cnumb" , (w*)&_r.Start_cond.numb          , 2, _SHORT_type, 0,  _READ_WRITE_access },  \
  { "Cnumb1", (w*)&_r.Stop_cond.numb           , 2, _SHORT_type, 0,  _READ_WRITE_access },  \
  { "Cmean" , (w*)&_r.Start_cond.mean          , 2, _SHORT_type, 0,  _READ_WRITE_access },  \
  { "Cmean1", (w*)&_r.Stop_cond.mean           , 2, _SHORT_type, 0,  _READ_WRITE_access },  \
  { "Cbits" , (w*)&_r.Start_cond.bits.all      , 2, _SHORT_type, 0,  _READ_WRITE_access },  \
  { "Cbits1", (w*)&_r.Stop_cond.bits.all       , 2, _SHORT_type, 0,  _READ_WRITE_access },  \
  { "Cdelst", (w*)&_r.DelayTime_Start          , 2, _SHORT_type, 0,  _READ_WRITE_access },  \
  { "Cdelsp", (w*)&_r.DelayTime_Stop           , 2, _SHORT_type, 0,  _READ_WRITE_access },  \
  { "Cfilst", (w*)&_r.FiltrTime_Start          , 2, _SHORT_type, 0,  _READ_WRITE_access },  \
  { "Cfilsp", (w*)&_r.FiltrTime_Stop           , 2, _SHORT_type, 0,  _READ_WRITE_access },\
  { "WR_RTC", (w*)&Write_RTC                   , 2, _SHORT_type, 0,  _READ_WRITE_access },  \
  { "DateTm", (w*)&l_time         , sizeof(l_time), _CHAR_array_type, 0,  _READ_WRITE_access },\
  { "OsclPt", (w*)&OscPtrs                     , 4, _CHAR_array_type, 0,  _READ_WRITE_access },  \
  { "OsclVr", (w*)&LanOsclOut, sizeof (LanOsclOut), _CHAR_array_type, 0,  _READ_access },\
 // { "MsgTst", (w*)&crezerv,                      2, _SHORT_type, 0,  _READ_access      }
#endif //_CANOPEN
#else //_Sld_cond
Ичьхэшть эюьхЁ тхЁёшш ёыхфр
#define  _Var_tab_InsertSled2

#endif //_Sld_cond
/*------------------------------------------------*/
#ifdef _MAIN_INCLUDE
/*------------------------------------------------*/

        /* Резервирование памяти под след */
  fbyte          SledPole [ _SizeSledPole ] ;

  /* Таблица адресов ячеек, содержимое которых будет заносится в след */
struct SLED   sled ;

struct SLED_data  sl_d ;   /* оперативные данные следа */

  const struct Sled_Types sled_types[] =
  {
    { "byte-hex       ", _sl_form(1,1,1,3,0), 'H' },
    { "byte-signed-dec", _sl_form(1,0,2,3,0), '.'  },
    { "byte-unsign-dec", _sl_form(1,1,2,3,0), '.'  },
    { "word-hex       ", _sl_form(2,1,1,5,0), 'H'  },
    { "word-signed-dec", _sl_form(2,0,2,5,0), '.'  },
    { "word-unsign-dec", _sl_form(2,1,2,5,0), '.'  }
  };

  const word sled_types_size = sizeof(sled_types) / sizeof(struct Sled_Types);

  word  sld_label ;

// Меню для следа. Структура определена Journal.c
const struct MENU1S Menu1S[ ] =
{
  { _sldMultiplicity, 10 },
  { _sldAutoStart   , 20 },
  { _sldQuantity    , 30 },
  { _sldList        , 40 }
};

const word Menu1S_size = sizeof( Menu1S )/sizeof( struct MENU1S );

/*------------------------------------------------*/
#else
/*------------------------------------------------*/

        /* Резервирование памяти под след */
  extern  fbyte  SledPole [_SizeSledPole] ;

        /* Таблица адресов ячеек, содержимое которых будет заносится в след */
  extern struct SLED   sled ;

  extern struct SLED_data  sl_d ;   /* оперативные данные следа */

  extern  const struct Sled_Types sled_types[] ;

  extern  const word sled_types_size ;

  extern  word  sld_label ;

  extern const struct MENU1S Menu1S[];

  extern const word Menu1S_size;

/*------------------------------------------------*/
#endif
#endif
