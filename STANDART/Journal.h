
#ifndef _journal
#define _journal
/*ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ*/

// прототипы функций
void Journal ( byte );    // собственно сам журнал
void SetJrnTab ( void );  // настройка журнала
void JrnPrint ( void );   // вывод журнала на пультик
word TestJrnTab ( byte );
word Save_jrn ( void );   // сохранение буфера журнала в i2c

#ifndef    _Journal_Version
  #define  _Journal_Version   0x01
#endif

#ifndef _CM3_

#define  _AdrSize 2

#else

#define  _AdrSize (4)

#endif

#define  _i2c_jrn_page   ( sizeof( struct MSG_JRN ) ) // –азмер страницы журнала

#define _MaxJrnCount 0x7u //размер буфера журнала в ќ«”


        //  оманда пуска-остановки журнала
        // ∆урнал пускаетс€ только тогда, когда нет ни одной команды остановки
        // ≈сли задано 0 переменных - журнал не работает
#define bi_JrnStop  ( ( JrnData.Stop != 0 ) || ( TabJrn.n_kanal == 0 ) ) //|| L_sts._.off_jrn == 1 )


#define _BRV 0x00 // >=
#define _MRV 0x01 // <=
#define _RVN 0x02 // ==
#define _NRV 0x03 // !=
#define _BOL 0x04 // >
#define _MEN 0x05 // <

#define _Gisterezis   5  // гистерезис на 5%
#define _CntrCode     ((w)0x1234)  // контрольный код дл€ различени€ записи журнала от мусора

#define _VarNameSize  15  // 14 - длина имени + 1 - конец строки

// таблица одной переменной
struct TAB_VAR
{
  char name[ _VarNameSize ];  // текстовое наименование переменной
  byte uslovie; // условие занесени€ записи в журнал дл€ аналоговой переменной
  word etalon;  // значение эталона, с которым сравниваетс€ аналогова€ переменна€,
                // или номер бита дл€ дискретной переменной
};

// ћаксимальное количество переменных, заносимых в журнал
#ifndef  _MaxNumVarJrn
  #define  _MaxNumVarJrn  ( 40 )
#endif

// таблица журнала в ќ«” и Ёќ«”
struct TAB_JRN
{
  byte  version;  // верси€ журнала
  byte  n_kanal;  // общее число переменных
  word  dt_scan;  // интервал времени тактировани€
  struct TAB_VAR TabVar[ _MaxNumVarJrn ];
  byte  check_sum; // контрольна€ сумма дл€ Ёќ«”
};

// —оздание шаблона-структуры переменной дл€ журнала
struct VAR_JRN
{
  char name[ _VarNameSize ];    // им€ переменной
  void       *addr;    // адрес переменной
  word       min;      // минимальное значение переменной в программных дискретах дл€ аналоговой переменной или
                       // наименьший номер бита дл€ дискретной переменной
  word       max;      // максимальное значение переменной в программных дискретах дл€ аналоговой переменной или
                       // наибольший номер бита дл€ дискретной переменной
  word       nom;      // номинальное значение переменной в программных дискретах дл€ аналоговой переменной или
                       // номер бита дл€ дискретной переменной или
                       // маска дл€ аналоговой переменной, сформированной битовыми пол€ми
  word       *abs_nom; // адрес €чейки номинала в абсолютных единицах
  word       dX;       // шаг изменени€
  char const *ch;      // текст единиц измерени€ переменной
  union
  {
    word all;
#ifndef   _Union_FR
    struct
    {
      word type     : 2;  // тип переменной: 1-byte, 2-word
      word drob     : 2;  // количество цифр дробн.части
      word celoe    : 3;  // количество цифр целой части
      word off_sign : 1;  // '=1'- беззнаковое

      word ad       : 2;  // 0-аналогова€ переменна€, 1-дискретна€, 2 - сформирована битовыми пол€ми
      word rezerv   : 6;  // резерв
    } _ ;
#else
    struct
    {
      word rezerv   : 6;  // резерв
      word ad       : 2;  // 0-аналогова€ переменна€, 1-дискретна€, 2 - сформирована битовыми пол€ми

      word off_sign : 1;  // '=1'- беззнаковое
      word celoe    : 3;  // количество цифр целой части
      word drob     : 2;  // количество цифр дробн.части
      word type     : 2;  // тип переменной: 1-byte, 2-word
    } _ ;
#endif
  } code;
} ;


// 1. јналогова€ переменна€ может быть только "word" или сформирована битовыми пол€ми.
// 2. ƒискретна€ переменна€ может быть "byte", "word".

// задание кода формата отображени€ переменной
// type  -  1,2 - тип переменной: 1 - однобайтна€, 2 - двухбайтна€
// drob  -  0...3 - количество символов после зап€той (дробна€ часть)
// celoe -  1...5 - количество символов до зап€той (цела€ часть)
// off_sign  -  1 - не отображать знак (переменна€ однопол€рна€) или большие символы дл€ hex
// ad -  0-аналогова€ переменна€, 1-дискретна€, 2 - сформирована битовыми пол€ми
#define  _jrn_form(ad,off_sign,celoe,drob,type)\
                                                (( type )|\
                                                 ( drob << 2 )|\
                                                 ( celoe << 4 )|\
                                                 ( off_sign << 7 )|\
                                                 ( ad << 8 ))

// структура дл€ фиксации сообщений журнала
// Ќа одну запись - 58 байт
struct MSG_JRN
{
  char name[ _VarNameSize ];  // текстовое наименование переменной
  byte uslovie; // условие занесени€ записи в журнал
  word value;   // значение переменной byte, word
  struct MSG_reg time_msg;
  //  struct I2C_time time;      // ¬рем€ регистрации
  //  {                   D7...D4         D3...D0
  //        time.b[0]:   10 seconds       seconds      00-59
  //        time.b[1]:   10 minutes       minutes      00-59
  //        time.b[2]:   10 hours          hours      0-1/00-23
  //        time.b[3]:                     day         01-07
  //        time.b[4]:   10 date           date        01-31
  //        time.b[5]:   10 month          month       01-12
  //        time.b[6]:   10 years          years       00-99
  //        time.b[7]:   Control Byte  - сюда пишем контрольный код дл€ различени€ записи журнала от мусора
  //  },
  //  struct MSG_regs  _ ;    // буфер дл€ сбора текущих сообщений.
  //  {
  //    lword    avar_first;        // –егистр первой аварии
  //    lword    avar;              // –егистр повторных аварий
  //    lword    predupr;           // –егистр предупреждений
  //    lword    service;           // –егистр служебных сообщений
  //------
  //    lword    avar_first2;       // 2-й регистр первой аварии
  //    lword    avar2;             // 2-й регистр повторных аварий
  //    lword    predupr2;          // 2-й регистр предупреждений
  //    lword    service2;          // 2-й регистр служебных сообщений
  //  }
};

struct JRN_DATA
{
  word time;
  byte tab[ _MaxNumVarJrn ];  // указатель на соответствующие данные в базовой таблице
  byte flag[ _MaxNumVarJrn ]; // признак изменени€ переменной
  byte number; // номер переменной, считанной из i2c
  byte label; // метка дл€ программы TestJrnTab()
  byte activ, Stop; // триггер остановки/запуска следа.
};

struct MENU
{
  char const *txt; // текст меню
  byte label;      // метка
};

union BIT_JRN
{
  byte all;
  struct
  {
    word tst_msg_jrn : 2;
    word tst_new_msg : 1;
    word first       : 1;
    word rezerv      : 4;
  }_;
};

/*struct BIT_PORT
{
  char name[ _VarNameSize ];  // им€ порта дискретных сигналов
  void       *addr;    // адрес порта дискретных сигналов
};*/

/*ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ*/
#ifdef _JOURNAL_INCLUDE
/*ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ*/

// таблица журнала в ќ«”
struct TAB_JRN TabJrn;

// буфер журнала в ќ«”
struct MSG_JRN MsgJrn[ _MaxJrnCount + 1 ];

// буфер журнала в ќ«” дл€ считывани€ из i2c и распечатки
struct MSG_JRN MsgJrnPrint;

byte InJrnPtr;  // указатель, указывающий на следующую (пустую) строку журнала
byte OutJrnPtr; // указатель, указывающий на последнюю (записанную в i2c) строку журнала.
                // ¬сегда должен отставать на 1 от InJrnPtr

struct JRN_DATA JrnData;

const struct MENU Menu1[ ] =
{
  { _jrnMultiplicity, 10 },
  { _jrnQuantity    , 20 },
  { _jrnList        , 30 }
};

const word Menu1_size = sizeof( Menu1 )/sizeof( struct MENU );

const struct MENU Menu2[ ] =
{
  { _jrnNewChannel, 40 },
  { _jrnCondition , 50 },
  { _jrnLevel     , 60 }
};

const word Menu2_size = sizeof( Menu2 )/sizeof( struct MENU );

const struct MENU Menu3[ ] =
{
  { " '>='", _BRV },
  { " '<='", _MRV },
  { " '=' ", _RVN },
  { " '!='", _NRV },
  { " '>' ", _BOL },
  { " '<' ", _MEN }
};

const word Menu3_size = sizeof( Menu3 )/sizeof( struct MENU );

_x_far const struct VAR_JRN *dptr;
union BIT_JRN  BitJrn;
byte i2c_jrn_label, *jrn_adr_data;
#ifndef _CM3_

word i2c_jrn_addr;

#else

lword i2c_jrn_addr;

#endif
const char *const DayJrn[ 7 ] = { "ѕн,","¬т,","—р,","„т,","ѕт,","—б,","Ќд," };
word Tjrn, Tckl_jrn;
#ifdef _CM3_

lword j_ext ;

#endif
/*ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ*/
#else
/*ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ*/

extern struct TAB_JRN TabJrn;
extern struct MSG_JRN MsgJrn[];
extern byte InJrnPtr;
extern byte OutJrnPtr;
extern struct JRN_DATA JrnData;
extern const struct MENU Menu1[];
extern const struct MENU Menu2[];
extern const struct MENU Menu3[];
extern const word Menu1_size;
extern const word Menu2_size;
extern const word Menu3_size;
extern _x_far const struct VAR_JRN *dptr;
extern struct MSG_JRN MsgJrnPrint;
extern union BIT_JRN  BitJrn;
extern byte i2c_jrn_label, *jrn_adr_data;
#ifndef _CM3_

extern word i2c_jrn_addr;

#else

extern lword i2c_jrn_addr;

#endif
extern const char *const DayJrn[];
extern word Tjrn, Tckl_jrn;
#ifdef _CM3_

extern lword j_ext ;

#endif

/*ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ*/
#endif
/*ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ*/
#endif
