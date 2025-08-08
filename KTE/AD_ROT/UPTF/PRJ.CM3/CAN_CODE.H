
#define  _canName_max_size   6   // максимальный размер имени переменной

#define __MasterAddr_Size 0x04
#define  _FullAddr_Size     ( 11 )


   //   Структура для преобразования отдельных байт в слово,
   // в длинное слово и наоборот.
union lax_ax_b
{               // Разрешаем для PCL841 обмен переменными типа Float.
  #ifdef   _CAN_FLOAT_VAR
             float flt ;
  #endif
     unsigned long lax ;
     unsigned short ax ;
   //  unsigned char  b[4];
} ;

     //  Коды ошибок возвращаемые контроллером.

#define  _Err_DESCRIPT            0x01  // несуществующий дескриптор.
#define  _Err_NAME                0x04  // несуществующее имя.
#define  _Err_TYPE                0x05  // несуществующий тип.
#define  _Err_DATA_LENGHT         0x06  // ошибка длины сообщения или данных
#define  _Err_WAIT                0x07  // система занята - повторите запрос.
#define  _Err_FirstReading        0x08  // дескриптор ранее не запрашивался.
#define  _Err_COMMAND             0x09  // неизвестная команда.
#define  _Err_ACCESS              0x0A  // переменная недоступна для данной операции
#define  _Err_CONTINUE            0x0B  // команде "продолжение чтения" не предшествовала ком. "начало чтения"
#define  _Err_NAME_SIZE           0x0C  // чрезмерная длина имени

//------------------------------------------
     //  Коды ошибок возвращаемые функциями (см. ниже).

#define   _Err_Send             ( 0x0001 )    //  ошибка посылки.
#define   _Err_Receive          ( 0x0002 )    //  ошибка приема.
#define   _Err_DscrSize         ( 0x0003 )    //  дескрипт. выходит за рамки таблицы переменных.
#define   _Err_DscrNumber       ( 0x0004 )    //  количество заданных дескрипт. не влазит в сообщение.
#define   _Err_DscrDataNumber   ( 0x0005 )    //  данные по заданному количеству дескрипт. не влезут в ответное сообщение.
#define   _Err_AnswLong         ( 0x0006 )    //  размер ответа не равен ожидаемому.
#define   _Err_Type             ( 0x0007 )    //  неизвестный тип данных в таблице.
#define   _Err_NameSize         ( 0x0008 )    //  задана чрезмерная длина имени переменной " более 6 символов"
#define   _Err_UnknownAbonent   ( 0x0009 )    //  неизвестное имя абонента
#define   _Err_Access           ( 0x000A )    //  переменная не доступна для данной операции
#define   _Err_NonCompatiblType ( 0x000B )    //  несовместимость типов данных в одном запросе
#define   _Err_ArraySize        ( 0x000C )    //  несоответсвие передаваемой длины массива его заданной длине
#define   _Err_Wait             ( 0x000D )    //  система длинной записи занята - повторите запрос.
#define   _Err_CAN_controller   ( 0x000E )    //  сбой CAN-контроллера

#define   _NoErr_TimeOut        ( 0x0050 )    //  функция не завершена и ожидает истечение тайм-аута, следует повторять вызовы функции для продолжения данной операции
#define   _NoErr_Continue       ( 0x0055 )    //  операция не завершена, следует повторять вызовы функции для продолжения данной операции


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//typedef struct canMSG_struct canMSG_struct ;

      // Структура для компоновки кода команды с порядковым номером посылки.

union MSG_CMD
{
  unsigned char all ;
  struct
  {
#ifndef _Union_FR
    unsigned int cmd   : 4 ;  // код команды.
    unsigned int rqst  : 1 ;  // бит - "=1-запрос/=0-ответ" .
    unsigned int code  : 3 ;  // порядковый номер посылки.
#else
    unsigned int code  : 3 ;  // порядковый номер посылки.
    unsigned int rqst  : 1 ;  // бит - "=1-запрос/=0-ответ" .
    unsigned int cmd   : 4 ;  // код команды.
#endif
  }_ ;
};

#define  _Continue_OpCode   0   // продолжение записи/чтения по незавершенной команде
#define  _Descript_OpCode   1   // отослать дескриптор соотв. полученному имени
#define  _Read_OpCode       2   // чтение
#define  _Write_OpCode      3   // запись с подтверждающим ответом
#define  _WriteArray_OpCode 4   // запись массива
#define  _Break_OpCode      5   // сброс
  #define  _Break_array     1   // сброс передачи массива.

#define  _Version_OpCode    6   // запрос возможностей
#define  _VarName_OpCode    7   // запрос имени переменной по дескриптору.
#define  _QuickWrite_OpCode 8   // запись без подтверждающего ответа
#define  _Descript_OpCodeL  9   // отослать дескриптор соотв. полученному имени, для значения длины переменной более 65536 байт

#define  _Error_OpCode    0xF   // ответ ошибкой.

#define  _READ_access         1   // 1-только для чтения
#define  _READ_WRITE_access   2   // 3-short, 2 байта

//---------------------------------
#ifndef   _Extern_names
//---------------------------------

#ifndef  _CANOPEN
	#define  _CHAR_type           1   // 1-char, 1 байт
	#define  _INT_type            2   // 2-int, 2 байта
	#define  _SHORT_type          3   // 3-short, 2 байта
	#define  _LONG_type           4   // 4-long, 4 байта
	#define  _FLOAT_type          5   // 5-float, 4 байта
	#define  _DOUBLE_type         6   // 6-double, 8 байт
	#define  _uCHAR_type          7   // 7-unsigned char, 1 байт
	#define  _uSHORT_type         8   // 8-unsigned short, 2 байта
	#define  _uLONG_type          9   // 9-unsigned long, 4 байта
	#define  _CHAR_array_type    41   // 41-массив char,
	#define  _SHORT_array_type   42   // 42-массив short,
	#define  _SHORT2_array_type  43   // 43-массив short,
	#define  _LONG_array_type    44   // 44-массив long,
	#define  _FLOAT_array_type   45   // 45-массив float,
	#define  _DOUBLE_array_type  46   // 46-массив double,
	#define  _uCHAR_array_type   47   // 47-массив unsigned char,
	#define  _uSHORT_array_type  48   // 48-массив unsigned short,
	#define  _uLONG_array_type   49   // 49-массив unsigned long,
	//#define  _BIT_type           77   // 77-битовая переменная (unsigned char)

//----- Классы в CANopen -----
#define  _NULL		0
#define  _DOMAIN	2
#define  _DEFTYPE	5
#define  _DEFSTUCT	6
#define  _VAR		7
#define  _ARRAY		8
#define  _RECORD	9

#endif

//---------------------------------
#endif
//---------------------------------
        //  старший бит накладывается на тип указывая, что данная переменная
        // содержит не данные, а адрес данных указанного типа.
#define  _Indirect_type  0x80

#define  _Descript_tag        1   // признак того, что дескриптор уже запрашивался
//#define  _Long_IO_tag         2   // признак того, что идет длинная запись

//#define  _arrea_bsize         2   // размер в байтах адреса массива
//------------------------------------------



