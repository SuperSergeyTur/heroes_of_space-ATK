// Драйвер для работы с резистором MCP4661


//typedef struct
//{
//  uint32_t          sl_addr7bit;				/**< Slave address in 7bit mode */
//  __IO uint8_t*     tx_data;					/**< Pointer to Transmit data - NULL if data transmit
//													  is not used */
//  uint32_t          tx_length;					/**< Transmit data length - 0 if data transmit
//													  is not used*/
// __IO uint32_t     tx_count;					/**< Current Transmit data counter */
//  __IO uint8_t*     rx_data;					/**< Pointer to Receive data - NULL if data receive
//													  is not used */
//  uint32_t          rx_length;					/**< Receive data length - 0 if data receive is
//													   not used */
//  __IO uint32_t     rx_count;					/**< Current Receive data counter */
//  uint32_t          retransmissions_max;		/**< Max Re-Transmission value */
//  uint32_t          retransmissions_count;		/**< Current Re-Transmission counter */
//  __IO uint32_t     status;						/**< Current status of I2C activity */
//  void 				(*callback)(void);			/**< Pointer to Call back function when transmission complete
//													used in interrupt transfer mode */
//} I2C_M_SETUP_Type;


//#ifndef _RES_I2C
//#define _RES_I2C





// Ошибки возвращаемые функциями при работе с цифровым резистором
  // Отсутствие ошибок по I2C
#define MCP4661_RETFUNC_OK					(0x0000)
  // Ошибка по I2C
#define MCP4661_RETFUNC_FAILED                                  (0x0001)

  // EEPROM микросхемы занята для чтения записи
#define MCP4661_RET_EEPROM_BUSY                                 (0x0004)
  // EEPROM микросхемы свободна для чтения записи
#define MCP4661_RET_EEPROM_OK                                   (0x0000)

  // Количество попыток для чтения/записи данных
  // исчерпаны (3-и попытки)
#define MCP4661_RET_CONNECT_OVERFLOW                            (0x0008)

  // Цикл записи по нажатию Enter в меню теста резист. НЕ ЗАкончен
#define MCP4661_RET_RECORD_NO_FINISH                            (0x0010)
  // Цикл записи по нажатию Enter в меню теста резист. ЗАкончен
#define MCP4661_RET_RECORD_FINISH                               (0x0000)

  // При сверке записанных данных чтением из запрошенного адреса выявлено несоответствие
#define MCP4661_RET_DATA_FAILED                                 (0x0040)
  // Все требуемые данные записаны корректно
#define MCP4661_RET_DATA_OK                                     (0x0000)







// Аппаратная данные для работы с I2C :
  // Выбор номера канала I2C контроллера
#define RES_CH_I2C           I2C_2

  // Частота шины
#define RES_CLOCK_FREQ_I2C   100000

  // Адрес микросхемы ( без учета дополнительной (аппаратной) выборки адресов )
#define MCP4661_adr          0x28



// Данные для установки особенностей резистора
  // Максимально допустимое значение записуемое в память резистора
#define _RES_setka_max   (w)(0x0100)
  // Минимально  допустимое значение записуемое в память резистора
#define _RES_setka_min  (sw)( 0 )
  // Номер движка микросхемы согласно схемы
#define _RES_WIPER_NUM0   0
#define _RES_WIPER_NUM1   1
  // Номинальное R резистора
#define _RES_NOM           100000
  // Если резистор подключен через жопу ( Нулевое значение зписанное в резистор соответствует максимальному R на задействованных выводах 
  //   а именно, когда точка common B и Wiper соеденены вместе и подключенны на операционник как 1-ая сорона резистора, а common A подключена как 2-ая сторона резистора)
#define _RES_IND_INVERT






// данные считанные с памяти резистора для последующей их обработки
struct Res_Memory
{
     // Данные считанные из RAM резистора (текущее значение движка резистора)
   word Res_RAM ;
     // Данные считанные из ROM резистора ( при подаче питания значение из ROM должно автоматически лечь в RAM  )
   word Res_ROM ;
     // Счетчик сколько раз менялось сопротивление (значение хранится в одном из адресов EEPROM резистора при старте перекладываем в данную перем.)
   word Count_Save ;
     // значение прошлой установки из ROM резистора (значение хранится в одном из адресов EEPROM резистора при старте перекладываем в данную перем.)
   word Past_Save ;

} ;


  // Константы для работы с резистором
 struct Res_Const
 {
     // Адрес I2C задаваемый распайкой ножек микросхемы
   uint32_t Add_channel ;
     // Номер Wiper канала резистора (два резистора в одной микросхеме канал0, канал1. Согл. схемы принципиальной)
   word     Wiper_Num ;
     // Масштаб для индикации в "Ом" ( прирост для одной дискреты: 100000 (номинал.: Ом) * 256 / 256(max_setka) )
   lword    mashtab ;
     // Максимальное значение в дискретах допустимое для установки резистора (может пригодиться пока оставим)
   word     Wiper_Data_max ;
 };





// общая структура для всех резисторов
 struct Res_Common
 {

     // Структура констант для работы с резистором
   _x_far const  struct  Res_Const   ResConst ;

     // Данные считанные с памяти резистора
   struct  Res_Memory ResMemory ;

     // Буферная переменная из которой мы ложим подгодовленные данные в адреса резистора (локальная переменная для того чтоб видеть,
     // что ложим в текущий адрес )
   word       Res_data_write ;

     // Последний опрос статус регистра
   word       Sts_Reg ;
     // Переменная в которую ложим код текущей ошибки не позволившей произвести корректную работу (ложим ВЕРНУВШИЙСЯ return функции)
   uint32_t   Res_Err_Ret ;

 } ;











// Команды для работы с резистором ( команда должна быть передана в одном байте вместе с адресом по которому она должна быть выполнена )
  // Записать данные
#define RES_COMMAND_WRITE      0x00
  // Инкремент одной дискреты от номиналоного сопротивления ( актуальна только для RAM памяти )
#define RES_COMMAND_INCR       0x04
  // Декремент одной дискреты от номиналоного сопротивления ( актуальна только для RAM памяти )
#define RES_COMMAND_DECR       0x08
  // Чтение данных
#define RES_COMMAND_READ       0x0c



// Набор макросов для четния данных из резистора с указанных адресов
  // Т.к. у нас сдвоенный резистор, тогда примим, что все адеса указанные в макросах, приведенные ниже, актуальны для резистора Wiper0, а
  // для резастора Wiper1  соответственно AddWiper1 = AddWiper0+1 (это не относится к RES_TCON_REG и RES_STS_REG адресам данные по этим адресам общие на 2-а резистора )

  // Адрес RAM памяти, в ней находится текущее значение движка резистора
#define RES_WIPER_RAM                0x00
  // Адрес ROM памяти, в ней хранится значение резист., которое переложиться в RAM при подаче питани
#define RES_WIPER_ROM              ( 0x02 << 4 )
  // TCON Registr( в данном регистре задается подключения/отключение выводов резистора к выходным "контактам" резистора и др. )
#define RES_TCON_REG               ( 0x04 << 4 )
// Status Registr (флаг цикла записи в EEPROM активен  +  состояние WiperLock битов(битов защиты от записи))
  // Адрес Status registra
#define RES_STS_REG                ( 0x05 << 4 )
  // Адрес EEPROM памяти, которую используем для хранения счетчика количества перезаписей WIPER_ROM
#define RES_WIPER_EEP_COUNT_SAVE   ( 0x07 << 4 )
  // Адрес EEPROM памяти, которую используем для хранения значения настройки резистора WIPER_ROM(n-1)
#define RES_WIPER_EEP_PAST_SAVE    ( 0x09 << 4 )
  // прибавка к адресу AddWiper0 для обращения к AddWiper1 (AddWiper1 = AddWiper0+1)
#define RES_MEM_ADD_WIPER1         ( 0x01 << 4 )





// Status Registr
  // Занятое состояние микросхемы на время записи в EEPROM (на момент установки данного бита допускаются только команды к RAM регистрам)
#define RES_EEPROM_BUSY  0x0008
  // Три бита в слове статуса соотв. сост. защит от записи в EEPROM (по схеме ВТЕ на 04.16 данную защиту ввести в работы нет возможности соответств.
  // они не могут иметь другого состояния кроме 0 )
#define RES_LOCK_BIT_SET 0x0007



// TCON Registr
     // нармальное заначение (для нашего случая) всех битов управления резистора находящиеся в регистре TCON
#define TCON_NORMAL      0x01ff







///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++///

//  Насторойк параметров резистора
struct Res_Common ResCommon[  ] =
{

  { {0x00, _RES_WIPER_NUM0, (lw)((d)_RES_NOM *256. / (d)_RES_setka_max) , _RES_setka_max }, {0}, 0 },
  { {0x00, _RES_WIPER_NUM1, (lw)((d)_RES_NOM *256. / (d)_RES_setka_max) , _RES_setka_max }, {0,0,0,0}, 0, 0 ,0 },

  { {0x01, _RES_WIPER_NUM0, (lw)((d)_RES_NOM *256. / (d)_RES_setka_max) , _RES_setka_max }, {0}, 0 },
  { {0x01, _RES_WIPER_NUM1, (lw)((d)_RES_NOM *256. / (d)_RES_setka_max) , _RES_setka_max }, {0}, 0 },

  { {0x02, _RES_WIPER_NUM0, (lw)((d)_RES_NOM *256. / (d)_RES_setka_max) , _RES_setka_max }, {0}, 0 },
  { {0x02, _RES_WIPER_NUM1, (lw)((d)_RES_NOM *256. / (d)_RES_setka_max) , _RES_setka_max }, {0}, 0 },

  { {0x03, _RES_WIPER_NUM0, (lw)((d)_RES_NOM *256. / (d)_RES_setka_max) , _RES_setka_max }, {0}, 0 },
  { {0x03, _RES_WIPER_NUM1, (lw)((d)_RES_NOM *256. / (d)_RES_setka_max) , _RES_setka_max }, {0}, 0 },

  { {0x04, _RES_WIPER_NUM0, (lw)((d)_RES_NOM *256. / (d)_RES_setka_max) , _RES_setka_max }, {0}, 0 },
  { {0x04, _RES_WIPER_NUM1, (lw)((d)_RES_NOM *256. / (d)_RES_setka_max) , _RES_setka_max }, {0}, 0 }
} ;

const word   _RES_Ntab = sizeof( ResCommon )/sizeof( struct Res_Common )  ;


struct RES_Data_ach
{
  char const *txt ; // индикация R и настр. переменной
  void  *adr;  // адрес переменной которую выводим на индикацию
  word  nom ; // масштаб
};


struct RES_common_tab
{
  struct RES_output_tab RES_tab ;

  struct RES_Data_ach RES_DataAch ;

};



// данные заносимые по номеру массива данной структуры и номер массива структуры ResCommon[N].ResMemory должены быть идентичны
// соответственно номер массива структур ResCommon[] и константные параметры заданные в нем относятся непосредственно к номеру массива данной структуры
// Если масштаб == 0 в меню "Настр.Рез." вместо числового значения параметра выводится надпись "НеИзм." (не измеряется)
_x_far const struct RES_common_tab RES_com_tab[  ] =
{
  {{ "RES0-Ud       " , &ResCommon[0].ResMemory }, { " Ом  ,  Ud(%) ", &Ud       , _Ud_Nom } },
  {{ "RES0-AR       " , &ResCommon[1].ResMemory }, { " Ом  ,  AR(%) ", &Uinsul   , _Ud_Nom } },

  {{ "RES1-Id_BO    " , &ResCommon[2].ResMemory }, { " Ом  ,Id_BO(%)", &Id_BO.U  , _Ud_Nom } }, 
  {{ "RES1-Id_max   " , &ResCommon[3].ResMemory }, { " Ом  ,Id_max  ", &Id       , _Id_Nom } }, //NULL      ,  0      } },// Id_max (не измеряется в АЦП)

  {{ "RES2-Id       " , &ResCommon[4].ResMemory }, { " Ом  ,  Id(%) ", &Id       , _Id_Nom } },
  {{ "RES2-KS       " , &ResCommon[5].ResMemory }, { " Ом  ,  KS    ", NULL      ,  0      } },// KS- синхронизация (не измеряется в АЦП)

  {{ "RES3-Idz4-20  " , &ResCommon[6].ResMemory }, { " Ом,Idz4-20(%)", &Id_zpch  , _Id_Nom } },
  {{ "RES3-Is       " , &ResCommon[7].ResMemory }, { " Ом  ,  Is(%) ", &Is_p     , _Is_Nom } },

  {{ "RES4-Us       " , &ResCommon[8].ResMemory }, { " Ом  ,  Us(%) ", &Us       , _Us_Nom } },
  {{ "RES4-eIs      " , &ResCommon[9].ResMemory }, { " Ом  ,  eIs(%)", &eIs.Ip   , _Is_Nom } }

};









  // инициализация шины для работы с RES
void MCP4661_Init( void ) ;
  // РЕинициализация шины для работы с RES
void MCP4661_DeInit(void) ;
  // Считать данные начиная с указанного адресса
word GetData_fromAdd ( I2C_M_SETUP_Type *TransferCfg ) ;
  // Функция проверки занятости/свободности EEPROM адресов резистора для считывания и записи в них
uint32_t GetResistorSts( struct Res_Common *Res_chenel_in, uint8_t ResMemAdd_Read ) ;
  // Считать значение с указанного адреса
word GetResistorValue( struct Res_Common *Res_chenel_in, uint8_t ResMemAdd_Read ) ;
  // Записать значение в указанный адрес
word SetResistorValue(struct Res_Common *Res_chenel_in, uint8_t ResMemAdd_write   ) ;
  // Функция реализующая выход из меню настр. резистора по Enter с сохранением данных в память резистора
word SetResVal_Enter(struct Res_Common *Res_chenel_in ) ;
  // Функция реализующая одноразовое считывание данных с резистора при старте
word GetResVal_Start(struct Res_Common *Res_chenel_in, word num ) ;


///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++///








