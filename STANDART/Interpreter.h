
#ifndef _interpreter_h
#define _interpreter_h

#include "functions.h"

//---------------Коды ошибок----------------------------------

#define   _No_Link          0x01  //нет сязи с i2с
#define   _ErrCtrlCode      0x02  //Контрольная сумма заголока не совпадает с прочитанной
#define   _VarQuantiy       0x03  //Превышение количеством зяавленных переменных максимально возможного количества
#define   _SPQuantiy        0x04  //Превышение количеством зяавленных уставок максимально возможного количества
#define   _LenCode          0x05  //Превышена длина блока программ
#define   _CS_Programm      0x06  //Несовпадение контрольной суммы блока программ
#define   _SP_Max           0x07  //Общее количество уставок превышает максимально допустимое
#define   _CS_SP            0x08  //Несовпадение контрольной суммы блока уставок
#define   _SP_Max_Block     0x09  //Адрес уставки указывает на ячейку, находящуюся за пределами требуемого блока
#define   _SP_No_Type       0x0A  //Неоределенный тип уставки
#define   _ind_No_Type      0x0B  //Неоределенный тип для индикации
#define   _Ind_Max          0x0C  //Указанное число строк переменных для индикации превышает максимально возможное
#define   _CS_Ind           0x0D  //Несовпадение контрольной суммы блока индикации
#define   _Av_msg_max       0x0E  //Превышено число аварийных сообщений
#define   _CS_AvMsg         0x0F  //Несовпадение контрольной суммы блока аварийных сообщений
#define   _Pr_msg_max       0x10  //Превышено число предупредительных сообщений
#define   _CS_PrMsg         0x11  //Несовпадение контрольной суммы блока предупредительных сообщений
#define   _Srv_msg_max      0x12  //Превышено число сервисных сообщений
#define   _CS_SrvMsg        0x13  //Несовпадение контрольной суммы блока сервисных сообщений
#define   _BVarQuantiy      0x14  //Превышение количества возможных базовых переменных
#define   _CS_Base          0x15  //Несовпадение контрольной суммы блока базовых переменных
#define   _Err_Base         0x16  //Указанного имени базовй переменной нет в таблице
#define   _CS               0x17  //Несовпадение контрольной суммы всего загружаемого блока
#define   _Num_Base_func    0x18  //Количество базовых функций больше возможного
#define   _Basef_load_err   0x19  //Ошибка загрузки блока базовых функций
#define   _Err_Basef_Name   0x1A  //Неправильное имя базовой функции
#define   _Err_Basef_nBlock 0x1B  //Превышение количества числа блоков базовых функций
#define   _CS_Basef         0x1C  //Несовпадение контрольной суммы блока базовых функций

#define   _Err_Comm         0x30  //Неверная комманда
#define   _Oveflow          0x31  //Счетчик программ вышел за пределы блока программ
#define   _Goto_Oveflow     0x32  //Указатель перехода указывает на ячейку за пределами блока программ
#define   _AvMsg_Oveflow    0x33  //Номер аварийного сообщения превышает допустимое значение
#define   _PrMsg_Oveflow    0x34  //Номер предупредительного сообщения превышает допустимое значение
#define   _SrvMsg_Oveflow   0x35  //Номер сервисного сообщения превышает допустимое значение
#define   _Err_Oper         0x36  //Ошибка в операндах
#define   _Stack_Oveflow    0x37  //Переплонение стека
#define   _Stack_Underflow  0x38  //Cтек пуст
#define   _Wrong_Base_func  0x39  //Выдан ошибочный номер базовой функции

#define   _End_programm     0xfff //Успешное завершение выполнения программы

//------------------------------------------------------------

#define _MAX_NUM_OPER      16 // Максимальное количество операндов в одной операции
#define _MAX_NUM_BITS      511 // Максимальное колчество байт для битовых переменных
#define _MAX_NUM_BYTE      511 // Максимальное число однобайтовых переменных
#define _MAX_NUM_WORD      511 // Максимальное число двухбайтовых переменных
#define _MAX_NUM_LWORD     511 // Максимальное число четырехбайтовых переменных
#define _MAX_NUM_DOUBLE    511 // Максимальное число переменных с плавающей точкой
#define _MAX_NUM_SP_BYTE   32
#define _MAX_NUM_SP_WORD   32
#define _MAX_NUM_SP_LWORD  32
#define _MAX_NUM_SP_DOUBLE 32
//Общий максимум уставок
#define _MAX_NUM_SETPOINTS   _MAX_NUM_SP_BYTE+_MAX_NUM_SP_WORD+_MAX_NUM_SP_LWORD+_MAX_NUM_SP_DOUBLE

#define _MAX_NUM_IND    20   // Максимальное число строк для индикации
#define _SIZE_IND_TAB   1   // Размер таблицы описания одной переменной для индикации в i2c
#define _MAX_SIZE_IND_TAB    _MAX_NUM_IND*_SIZE_IND_TAB
#define _MAX_NUM_ARG    16  //Максимальное число аргументов в функции
//------------------------------------------------------------
// Типы операндов
#define _VALUE       0x00 // Переменная
#define _SETPOINT    0x01 // Уставка
#define _BASE        0x02 // Базовая переменная (из базового ПО)
#define _CONST       0x03 // Константа
#define _ARGUMENT    0x04 // Аргумент функции

// Размерность операнда
#define _1BYTE       0x00 // Целый однобайтный операнд
#define _2BYTE       0x01 // Целый двухбайтный операнд
#define _4BYTE       0x02 // Целый четырехбайтный операнд
#define _FLOAT       0x03 // Четырехбайтный операнд с плавающей точкой
//#define _BIT         0x04 // Битовый операнд
#define _VOID        0x05 // Неопределен (для результатов функции)

#define _STACK_SIZE  1500 //Размер стека в словах
#define _Tmp_Opers_max 64
//----------------------
#define _comp_Date  comp_date[0]
#define _comp_Month comp_date[1]
#define _comp_Year  comp_date[2]
#define _comp_Hour  comp_date[3]
#define _comp_Min   comp_date[4]
#define _comp_Sec   comp_date[5]

//---базовые функции---

//Максимальный размер имени функции

#define _Max_Name_Func   12 //10 символов + 0 + 1 байт выравнивания

struct  Base_func_def
{
  const char*  Name; //Имя функции
  word Numb_blocks;  //Колчиество используемых блоков
};

union Command
{
  word all;
  struct
  {
#ifdef _Union_FR   //переворачиваем байты только для FR

    word Command  : 12; // Код команды
    word Noperand : 4; // Количество операндов
#else
    word Noperand : 4; // Количество операндов
    word Command  : 12; // Код команды
#endif
  }_;
};

/*------------------------------------------------------------
union bwlw
{
   lword  all;
   struct
   {
    word   h;
    word   l;
   }wrd;
   struct
   {
    byte   hh;
    byte   hl;
    byte   lh;
    byte   ll;
   }bt;
};
//------------------------------------------------------------
union str_word_byte
{
   word  all;
   struct
   {
    byte   h;
    byte   l;
   }_;
};*/
//--------------------------------------------------------------
struct Var_quant
{
   word    qByte;
   word    qWord;
   word    qLWord;
   word    qDouble;
};
//--------------------------------------------------------------
union FormatCode
{
  word all;
  struct
  {
#ifdef _Union_FR   //переворачиваем байты только для FR
     word rezerv     : 1;
     word invert     : 1;  // отображение уставок в виде 1/x
     word print_type : 2;  // отображение уставок в 16-ричн виде 0/1 - 10/16-ричный вид
     word zapr       : 1;  // для совместимости с form2()-форматом уставок
     word off_sign   : 1;  // '=1'- отмена распечатки знака
     word celoe      : 4;  // количество цифр целой части
     word drob       : 3;  // количество цифр дробной части
     word type       : 3;  // тип переменной: 0- double, 1-однобайтная, 2-двухбайтная, 4-четырехбайтная, 7 - базовая
#else
     word type       : 3;  // тип переменной: 0- double, 1-однобайтная, 2-двухбайтная, 4-четырехбайтная, 7 - базовая
     word drob       : 3;  // количество цифр дробной части
     word celoe      : 4;  // количество цифр целой части
     word off_sign   : 1;  // '=1'- отмена распечатки знака
     word zapr       : 1;  // для совместимости с form2()-форматом уставок
     word print_type : 2;  // отображение уставок в 16-ричн виде 0/1 - 10/16-ричный вид
     word invert     : 1;  // отображение уставок в виде 1/x
     word rezerv     : 1;
#endif

  }_;
};
//------------------------------------------------------------

// Структура таблицы индикации, загружаемой извне
struct Ind_Table_Cod
{
  byte txt[ 16 ];  // текст для отображения наименования параметров
  word num_var1; // номер параметра 1 в массиве переменных
  word num_var2; // номер параметра 2 в массиве переменных
  word nom1;              // номинальное значение параметра 1
  word nom2;              // номинальное значение параметра 2
  byte unit1[ 4]; // текст единицы измерения параметра 1
  byte unit2[ 4]; // текст единицы измерения параметра 2
  word abs_nom1;          // номинальное значение параметра 1 в абсолютных единицах
  word abs_nom2;          // номинальное значение параметра 2 в абсолютных единицах
  union FormatCode code1;  // формат индикации параметра 1 на пультовом терминале
  union FormatCode code2;  // формат индикации параметра 1 на пультовом терминале
};
      // Структура блока данных для отдельного элемента таблицы параметров.
struct Ind_obj {
             byte  *txt ;      //текст для отображения наименования параметра данного элемента таблицы
             void  *adr[2] ;      // адрес ячейки памяти соответствующей параметру данного элемента таблицы
             word  nom[2] ;       // номинальное значение данного параметра в программных дискретах
             byte  *txt2[2] ;  // текст для отображения физической ед.измер. данного парам.
             word  *abs_nom[2];   //адрес ячейки номинала в абсолютных единицах
             union FormatCode code[2] ;
               } ;

//------------------------------------------------------------

// Шаблон структуры уставки, загруажаемой извне
struct Ust_Tab
{
  double dX;                  // шаг изменения уставки
  double typ;                 // типовое значение
  double min;                 // минимальное значение уставки
  double max;                 // максимальное значение уставки
  word num_var;               // номер переменной в массиве уставок
  word nom;                   // номинальное значение уставки в дискретах
  word abs_nom;               // номинальное значение уставки в абсолютных единицах
  union FormatCode code;
  byte text[ 16 ];            // текст уставки
  byte ch[ 4 ];               // текст единицы измерения уставки
};
//Структура описания уставки для ее отбражения на пультике

struct Obj_STB {
            byte *text ;  // адрес строки текста соответствующего уставке
            void *addr      ;  // адрес уставки; уставка может быть только двухбайтной
            double  min     ;  // минимальное значение вличины в программных единицах
            double  max     ;  // максимальное значение величины в программных единицах
            word  nom       ;  // номинальное значение данной уставки в программных дискретах
            word  *abs_nom  ;  // номинальное значение данной уставки в программных дискретах
            double  dX      ;  //
            byte  mask      ;  // Маска уставки - определяет показывать ее в таблице или нет
            byte *ch        ;  // адрес строки текста соответствующего уставке
            union FormatCode code ;
 //           void * Type_Ust;        //Адрес типового значения
 //           void * Max_Dat;         //Маскимальное значение уставки, исходя из разрешения датчика
 //   _x_far  char * Help_str;        //Адрес первого символа строки Help для уставки
        } ;

//------------------------------------------------------------
//Отчет об ошибке
struct  Err_Rep
{
    word code;                          // код ошибки
    word Comm;                          //код команды в которой произошла ошибка
    word PC;                            //программный счетчик
    word SP;                            //Указатель стека
    word Oper[_Tmp_Opers_max+1];                      //Набор операндов
};
// Структура данных
struct MemoryData
{
 // byte   bitData [ _MAX_NUM_BITS ];
  byte   bData [ _MAX_NUM_BYTE   ];
  word   wData [ _MAX_NUM_WORD   ];
  lword  lwData[ _MAX_NUM_LWORD  ];
  double dData [ _MAX_NUM_DOUBLE ];
};
//данные в уставках
struct SetpointData
{
  byte   bData [ _MAX_NUM_SP_BYTE   ];
  word   wData [ _MAX_NUM_SP_WORD   ];
  lword  lwData[ _MAX_NUM_SP_LWORD  ];
  double dData [ _MAX_NUM_SP_DOUBLE ];
};


// Код программы
struct CodeData
{
  word Size;  //Размер программного блока.
  word ProgrammCounter;       // Здесь хранится адрес извлекаемого для анализа байта из "Prog"
  word Prog[ _MAX_LEN_CODE/2 ]; // Сюда загружается код программы из i2c  размер задан в байтах,
                                //а массив из слов состоит, по этому делим на 2
};
//Структура, определяющая наличие основных элементов в программе.
union Prg_cfg
{
 word all;
 struct
 {
#ifdef _Union_FR   //переворачиваем байты только для FR

    word res_h    :8;    //резерв

    word res      :1;
    word func     :1;  //служебные функции
    word base     :1;  //стандартные переменные
    word srv_msg  :1;  //сервисные сообщения

    word pr_msg   :1;  //предупредительные сообщения
    word av_msg   :1;  //аварийные сообщения
    word ind      :1;  //наличие переменных для индикации
    word ust      :1;  //наличие уставок
#else

    word ust      :1;  //наличие уставок
    word ind      :1;  //наличие переменных для индикации
    word av_msg   :1;  //аварийные сообщения
    word pr_msg   :1;  //предупредительные сообщения

    word srv_msg  :1;  //сервисные сообщения
    word base     :1;  //стандартные переменные
    word func     :1;  //служебные функции
    word res      :1;

    word res_h    :8;    //резерв

#endif
 }_;
};
//Структура, определяющая количество пременных, сообщений и т.д.
 struct quantity
 {
    word Function;
    word SetPoint;
    word VarInd;
    word VarBase;
    word Av_Msg;
    word Pr_Msg;
    word Srv_Msg;

 };
//Структура описания одтельного типа аргументов
 struct arg_data
 {
   word quant; //Количество аргументов данного типа
   word Arg[_MAX_NUM_ARG]; //куда складываются значения аргументов

 };
 struct  arg_data_full
 {
    struct arg_data   byte_arg     ;  //однобайтные
    struct arg_data   word_arg     ;  //двухбайтные
    struct arg_data   lword_arg    ;  //четырехбайтные
    struct arg_data   double_arg   ;  //double
 };

struct  Stack_str
{
    word Stack_Pointer; //Указатель стека
    union
    {
        word Stack[_STACK_SIZE]; //Стек для  перехода на подпрограммы
        union Operand oStack[_STACK_SIZE]; //стек в виде операндов
    } body;
} ;

union  ObjPrg_Srv_bit
{
   word all;
   struct
   {
      word Avar   :1;
      word InWork :1;
   }_;

};
word Interpreter ( byte code );
double Double_Move( double in) ;


word PUSH(byte*in, word size);
word POP (byte*in, word size);


//byte ExtractFromMemory(union Operand *Operands, union bwlw *Output, byte Counter);
//void LoadToMemory     (union Operand Operands, union bwlw *Input);

#ifdef _INT_MEM_INCLUDE

struct CodeData       ObjPrgData;

#else

extern struct CodeData       ObjPrgData;

#endif

#ifdef _INTERPRETER_INCLUDE

const struct  Base_func_def  Basef_def[] =
{
    "bSin",     _Numb_blocks_bSin,
    "bCos",     _Numb_blocks_bCos,
    "bTan",     _Numb_blocks_bTan,
    "bAsin",    _Numb_blocks_bAsin,
    "bAcos",    _Numb_blocks_bAcos,
    "bAtan",    _Numb_blocks_bAtan,
    "bSqr",     _Numb_blocks_bSqr,
    "bAbs_d",   _Numb_blocks_bAbsD,
    "bAbs_i",   _Numb_blocks_bAbsI,
    "bLim_d",   _Numb_blocks_bLimD,
    "bLim_i",   _Numb_blocks_bLimI,
    "bIZU_d",   _Numb_blocks_bIZUD,
    "bIZU_i",   _Numb_blocks_bIZUI,
    "bZI"  ,    _Numb_blocks_bZI,
    "bInitZi",  _Numb_blocks_bini_ZI,
    "bPI_reg",  _Numb_blocks_bPI_reg,
    "bFiltr",   _Numb_blocks_bFiltr,
    "bAverage", _Numb_blocks_bAverage
};

//Таблица с именами используемых базовых функций, используемых в программе
// struct  Base_func_def Basef_block[_Numb_Basef];

//массив для перехода от полученной таблиц базовых функций к внутренней номерации
word Base_func_decoding[_Numb_Basef];

byte comp_date[6];


//struct Tabl_Obj_MSG   TablObjMSG;
//struct MSG_Obj_regs   MSGObjregs;
struct MemoryData     MemData;  // ОЗУ данных интерпретатора
struct Stack_str      Stack;  //Стек
//struct AgrData ObjArgData;      //Структура указателей на аргументы функции
union  Prg_cfg  Cfg_str;
struct quantity Str_quant;
struct Var_quant PVar_quant;
struct Var_quant SVar_quant;

//struct MemoryArgData    MemArgData; //Буфер аргументов подпрограмм
union  ObjPrg_Srv_bit   ObjSrv_bit;
const char CtrlCode[9] = "PComplex";
//word  addr_Ctrl;
byte CtrlTmp[8];
//word fr1,fr2;
lword fr3;
lword fr4;//, fr5;
word *fr5[4];
double fr6, fr7;
//Признак первого оборота программы для начальной инициализации базовых функций
word obj_FirstPrg;
//массив сдвигов по условным переходам
//word Shifts[1000];
const word SizeMemData = sizeof ( struct MemoryData ); // Размер ОЗУ данных интерпретатора

union Operand  Operand_Tmp[_Tmp_Opers_max+1]; //Временное хранилище операндов
//номер стандартной переменной в var_tab
//word   Std_Vars[(size_vartab1/sizeof(struct namevar))] ;
struct Ind_obj  Ind_Obj_Prg[_MAX_NUM_IND];
struct Ind_Table_Cod  Ind_Obj_Load[_MAX_NUM_IND];
struct Ust_Tab        Ust_Obj_Load[_MAX_NUM_SETPOINTS];
struct Obj_STB        Ust_Obj_Prg [_MAX_NUM_SETPOINTS];
union Command  Com;
//union bwlw  long_tmp;
struct  Err_Rep  ErrRep;
byte ObjVarPar[5];
//Типовые значения уставок
struct SetpointData   Type_SetPoints;
//struct SetpointData   _opr;
#else

extern const struct  Base_func_def Basef_def[];

extern byte comp_date[6];

extern word Base_func_decoding[];

//extern struct Tabl_Obj_MSG   TablObjMSG;
//extern struct MSG_Obj_regs   MSGObjregs;
//extern struct AgrData        ObjArgData;
extern union  Prg_cfg  Cfg_str;
extern struct quantity Str_quant;
extern struct Var_quant PVar_quant;
extern struct Var_quant SVar_quant;
extern struct MemoryData     MemData;
//extern struct MemoryArgData    MemArgData;
//extern word   Shifts[1000];
extern struct Stack_str Stack;
extern union  Operand Operand_Tmp[];
extern struct Ind_obj        Ind_Obj_Prg[_MAX_NUM_IND];
extern struct Ind_Table_Cod  Ind_Obj_Load[_MAX_NUM_IND];
extern struct Ust_Tab        Ust_Obj_Load[_MAX_NUM_SETPOINTS];
extern struct Obj_STB        Ust_Obj_Prg [_MAX_NUM_SETPOINTS];
//extern word   Std_Vars[] ;
extern union Command  Com;
//extern union bwlw  long_tmp;
extern const word SizeMemData;
extern union  ObjPrg_Srv_bit   ObjSrv_bit;
extern const char CtrlCode[];
extern word obj_FirstPrg;
//extern word  addr_Ctrl;
extern byte CtrlTmp[8];
extern word fr1, fr2;
extern double fr6, fr7;
extern struct  Err_Rep  ErrRep;
extern byte ObjVarPar[5];
extern struct SetpointData   Type_SetPoints;
//extern struct SetpointData   _opr;

#endif

#endif  // _interpreter_h
