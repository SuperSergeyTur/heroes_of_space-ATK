// ������� ��� ������ � ���������� MCP4661


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





// ������ ������������ ��������� ��� ������ � �������� ����������
  // ���������� ������ �� I2C
#define MCP4661_RETFUNC_OK					(0x0000)
  // ������ �� I2C
#define MCP4661_RETFUNC_FAILED                                  (0x0001)

  // EEPROM ���������� ������ ��� ������ ������
#define MCP4661_RET_EEPROM_BUSY                                 (0x0004)
  // EEPROM ���������� �������� ��� ������ ������
#define MCP4661_RET_EEPROM_OK                                   (0x0000)

  // ���������� ������� ��� ������/������ ������
  // ��������� (3-� �������)
#define MCP4661_RET_CONNECT_OVERFLOW                            (0x0008)

  // ���� ������ �� ������� Enter � ���� ����� ������. �� ��������
#define MCP4661_RET_RECORD_NO_FINISH                            (0x0010)
  // ���� ������ �� ������� Enter � ���� ����� ������. ��������
#define MCP4661_RET_RECORD_FINISH                               (0x0000)

  // ��� ������ ���������� ������ ������� �� ������������ ������ �������� ��������������
#define MCP4661_RET_DATA_FAILED                                 (0x0040)
  // ��� ��������� ������ �������� ���������
#define MCP4661_RET_DATA_OK                                     (0x0000)







// ���������� ������ ��� ������ � I2C :
  // ����� ������ ������ I2C �����������
#define RES_CH_I2C           I2C_2

  // ������� ����
#define RES_CLOCK_FREQ_I2C   100000

  // ����� ���������� ( ��� ����� �������������� (����������) ������� ������� )
#define MCP4661_adr          0x28



// ������ ��� ��������� ������������ ���������
  // ����������� ���������� �������� ���������� � ������ ���������
#define _RES_setka_max   (w)(0x0100)
  // ����������  ���������� �������� ���������� � ������ ���������
#define _RES_setka_min  (sw)( 0 )
  // ����� ������ ���������� �������� �����
#define _RES_WIPER_NUM0   0
#define _RES_WIPER_NUM1   1
  // ����������� R ���������
#define _RES_NOM           100000
  // ���� �������� ��������� ����� ���� ( ������� �������� ��������� � �������� ������������� ������������� R �� ��������������� ������� 
  //   � ������, ����� ����� common B � Wiper ��������� ������ � ����������� �� ������������ ��� 1-�� ������ ���������, � common A ���������� ��� 2-�� ������� ���������)
#define _RES_IND_INVERT






// ������ ��������� � ������ ��������� ��� ����������� �� ���������
struct Res_Memory
{
     // ������ ��������� �� RAM ��������� (������� �������� ������ ���������)
   word Res_RAM ;
     // ������ ��������� �� ROM ��������� ( ��� ������ ������� �������� �� ROM ������ ������������� ���� � RAM  )
   word Res_ROM ;
     // ������� ������� ��� �������� ������������� (�������� �������� � ����� �� ������� EEPROM ��������� ��� ������ ������������� � ������ �����.)
   word Count_Save ;
     // �������� ������� ��������� �� ROM ��������� (�������� �������� � ����� �� ������� EEPROM ��������� ��� ������ ������������� � ������ �����.)
   word Past_Save ;

} ;


  // ��������� ��� ������ � ����������
 struct Res_Const
 {
     // ����� I2C ���������� ��������� ����� ����������
   uint32_t Add_channel ;
     // ����� Wiper ������ ��������� (��� ��������� � ����� ���������� �����0, �����1. ����. ����� ��������������)
   word     Wiper_Num ;
     // ������� ��� ��������� � "��" ( ������� ��� ����� ��������: 100000 (�������.: ��) * 256 / 256(max_setka) )
   lword    mashtab ;
     // ������������ �������� � ��������� ���������� ��� ��������� ��������� (����� ����������� ���� �������)
   word     Wiper_Data_max ;
 };





// ����� ��������� ��� ���� ����������
 struct Res_Common
 {

     // ��������� �������� ��� ������ � ����������
   _x_far const  struct  Res_Const   ResConst ;

     // ������ ��������� � ������ ���������
   struct  Res_Memory ResMemory ;

     // �������� ���������� �� ������� �� ����� �������������� ������ � ������ ��������� (��������� ���������� ��� ���� ���� ������,
     // ��� ����� � ������� ����� )
   word       Res_data_write ;

     // ��������� ����� ������ ��������
   word       Sts_Reg ;
     // ���������� � ������� ����� ��� ������� ������ �� ����������� ���������� ���������� ������ (����� ����������� return �������)
   uint32_t   Res_Err_Ret ;

 } ;











// ������� ��� ������ � ���������� ( ������� ������ ���� �������� � ����� ����� ������ � ������� �� �������� ��� ������ ���� ��������� )
  // �������� ������
#define RES_COMMAND_WRITE      0x00
  // ��������� ����� �������� �� ������������ ������������� ( ��������� ������ ��� RAM ������ )
#define RES_COMMAND_INCR       0x04
  // ��������� ����� �������� �� ������������ ������������� ( ��������� ������ ��� RAM ������ )
#define RES_COMMAND_DECR       0x08
  // ������ ������
#define RES_COMMAND_READ       0x0c



// ����� �������� ��� ������ ������ �� ��������� � ��������� �������
  // �.�. � ��� ��������� ��������, ����� ������, ��� ��� ����� ��������� � ��������, ����������� ����, ��������� ��� ��������� Wiper0, �
  // ��� ��������� Wiper1  �������������� AddWiper1 = AddWiper0+1 (��� �� ��������� � RES_TCON_REG � RES_STS_REG ������� ������ �� ���� ������� ����� �� 2-� ��������� )

  // ����� RAM ������, � ��� ��������� ������� �������� ������ ���������
#define RES_WIPER_RAM                0x00
  // ����� ROM ������, � ��� �������� �������� ������., ������� ������������ � RAM ��� ������ ������
#define RES_WIPER_ROM              ( 0x02 << 4 )
  // TCON Registr( � ������ �������� �������� �����������/���������� ������� ��������� � �������� "���������" ��������� � ��. )
#define RES_TCON_REG               ( 0x04 << 4 )
// Status Registr (���� ����� ������ � EEPROM �������  +  ��������� WiperLock �����(����� ������ �� ������))
  // ����� Status registra
#define RES_STS_REG                ( 0x05 << 4 )
  // ����� EEPROM ������, ������� ���������� ��� �������� �������� ���������� ����������� WIPER_ROM
#define RES_WIPER_EEP_COUNT_SAVE   ( 0x07 << 4 )
  // ����� EEPROM ������, ������� ���������� ��� �������� �������� ��������� ��������� WIPER_ROM(n-1)
#define RES_WIPER_EEP_PAST_SAVE    ( 0x09 << 4 )
  // �������� � ������ AddWiper0 ��� ��������� � AddWiper1 (AddWiper1 = AddWiper0+1)
#define RES_MEM_ADD_WIPER1         ( 0x01 << 4 )





// Status Registr
  // ������� ��������� ���������� �� ����� ������ � EEPROM (�� ������ ��������� ������� ���� ����������� ������ ������� � RAM ���������)
#define RES_EEPROM_BUSY  0x0008
  // ��� ���� � ����� ������� �����. ����. ����� �� ������ � EEPROM (�� ����� ��� �� 04.16 ������ ������ ������ � ������ ��� ����������� ����������.
  // ��� �� ����� ����� ������� ��������� ����� 0 )
#define RES_LOCK_BIT_SET 0x0007



// TCON Registr
     // ���������� ��������� (��� ������ ������) ���� ����� ���������� ��������� ����������� � �������� TCON
#define TCON_NORMAL      0x01ff







///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++///

//  ��������� ���������� ���������
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
  char const *txt ; // ��������� R � �����. ����������
  void  *adr;  // ����� ���������� ������� ������� �� ���������
  word  nom ; // �������
};


struct RES_common_tab
{
  struct RES_output_tab RES_tab ;

  struct RES_Data_ach RES_DataAch ;

};



// ������ ��������� �� ������ ������� ������ ��������� � ����� ������� ��������� ResCommon[N].ResMemory ������� ���� ���������
// �������������� ����� ������� �������� ResCommon[] � ����������� ��������� �������� � ��� ��������� ��������������� � ������ ������� ������ ���������
// ���� ������� == 0 � ���� "�����.���." ������ ��������� �������� ��������� ��������� ������� "�����." (�� ����������)
_x_far const struct RES_common_tab RES_com_tab[  ] =
{
  {{ "RES0-Ud       " , &ResCommon[0].ResMemory }, { " ��  ,  Ud(%) ", &Ud       , _Ud_Nom } },
  {{ "RES0-AR       " , &ResCommon[1].ResMemory }, { " ��  ,  AR(%) ", &Uinsul   , _Ud_Nom } },

  {{ "RES1-Id_BO    " , &ResCommon[2].ResMemory }, { " ��  ,Id_BO(%)", &Id_BO.U  , _Ud_Nom } }, 
  {{ "RES1-Id_max   " , &ResCommon[3].ResMemory }, { " ��  ,Id_max  ", &Id       , _Id_Nom } }, //NULL      ,  0      } },// Id_max (�� ���������� � ���)

  {{ "RES2-Id       " , &ResCommon[4].ResMemory }, { " ��  ,  Id(%) ", &Id       , _Id_Nom } },
  {{ "RES2-KS       " , &ResCommon[5].ResMemory }, { " ��  ,  KS    ", NULL      ,  0      } },// KS- ������������� (�� ���������� � ���)

  {{ "RES3-Idz4-20  " , &ResCommon[6].ResMemory }, { " ��,Idz4-20(%)", &Id_zpch  , _Id_Nom } },
  {{ "RES3-Is       " , &ResCommon[7].ResMemory }, { " ��  ,  Is(%) ", &Is_p     , _Is_Nom } },

  {{ "RES4-Us       " , &ResCommon[8].ResMemory }, { " ��  ,  Us(%) ", &Us       , _Us_Nom } },
  {{ "RES4-eIs      " , &ResCommon[9].ResMemory }, { " ��  ,  eIs(%)", &eIs.Ip   , _Is_Nom } }

};









  // ������������� ���� ��� ������ � RES
void MCP4661_Init( void ) ;
  // ��������������� ���� ��� ������ � RES
void MCP4661_DeInit(void) ;
  // ������� ������ ������� � ���������� �������
word GetData_fromAdd ( I2C_M_SETUP_Type *TransferCfg ) ;
  // ������� �������� ���������/����������� EEPROM ������� ��������� ��� ���������� � ������ � ���
uint32_t GetResistorSts( struct Res_Common *Res_chenel_in, uint8_t ResMemAdd_Read ) ;
  // ������� �������� � ���������� ������
word GetResistorValue( struct Res_Common *Res_chenel_in, uint8_t ResMemAdd_Read ) ;
  // �������� �������� � ��������� �����
word SetResistorValue(struct Res_Common *Res_chenel_in, uint8_t ResMemAdd_write   ) ;
  // ������� ����������� ����� �� ���� �����. ��������� �� Enter � ����������� ������ � ������ ���������
word SetResVal_Enter(struct Res_Common *Res_chenel_in ) ;
  // ������� ����������� ����������� ���������� ������ � ��������� ��� ������
word GetResVal_Start(struct Res_Common *Res_chenel_in, word num ) ;


///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++///








