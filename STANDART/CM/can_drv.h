#ifndef	_CAN_DRV_H
 #define  _CAN_DRV_H

#ifndef  _Num_CAN_Ports
 #define _Num_CAN_Ports  2
#endif
#define  _CAN0_Port 0
#define  _CAN1_Port	1
#define  _CAN_IRQ_PRIORITY  IntPriority(3, 5)

#define  can_reInit(port)  (can_dd[port].Can_reInit)
#define  can_stop(port)    (can_dd[port].Can_stop)
#define  tst_can_stop(port)  ( can_dd[port].Can_stop == 1 || can_setting(port).config._.vkl == 0 )

struct Baud  { byte bt0, bt1 ; } ;

#define   _bt0_100k     0x0f
#define   _bt1_100k     0x16

#define  _CAN_GSR_RBS		0x00000001
#define  _CAN_GSR_DOS 		0x00000002
#define  _CAN_GSR_TBS		0x00000004
#define  _CAN_GSR_TCS 		0x00000008
#define  _CAN_GSR_RS		0x00000010
#define  _CAN_GSR_TS  		0x00000020
#define  _CAN_GSR_ES		0x00000040
#define  _CAN_GSR_BS  		0x00000080
#define  _CAN_GSR_RXERR		0x00FF0000
#define  _CAN_GSR_TXERR		0xFF000000

#define  _CAN_CMR_TR		0x0001
#define  _CAN_CMR_AT		0x0002
#define  _CAN_CMR_RRB		0x0004
#define  _CAN_CMR_CDO		0x0008
#define  _CAN_CMR_SRR		0x0010
#define  _CAN_CMR_STB1		0x0020
#define  _CAN_CMR_STB2		0x0040
#define  _CAN_CMR_STB3		0x0080

#define  _CAN_SR_TBS1		0x00000004
#define  _CAN_SR_TCS1		0x00000008
#define  _CAN_SR_TS1		0x00000020
#define  _CAN_SR_TBS2		0x00000400
#define  _CAN_SR_TCS2		0x00000800
#define  _CAN_SR_TS2		0x00002000
#define  _CAN_SR_TBS3		0x00040000
#define  _CAN_SR_TCS3		0x00080000
#define  _CAN_SR_TS3		0x00200000

struct canMSG_Fuj
{
        lword  id ;
        struct
        {
          word dlen ;
          //byte dir ;
        } cfg ;
        byte data[10];
} ;

     // Блок данных для i-того CAN-порта.
struct CAN_drv_data
{
 byte Error_receive;
 byte Avar;
 byte Error_send ;
 word time_out_send14 , time_out_send13 ;
 word time_out_send[16];
 byte Can_reInit ;
 byte Can_stop ;
};

typedef struct
{
   struct canMSG_Fuj msg;
   byte flag;
} TMailBox;

typedef struct
{
   TMailBox rmsg[3];
   byte mailbox;
} TCAN_FIFO	;

typedef struct
{
   word count;
   word FC[_Num_CAN_Ports];
   word SFF[_Num_CAN_Ports];
   word SFFg[_Num_CAN_Ports];
   word EFF[_Num_CAN_Ports];
   word EFFg[_Num_CAN_Ports];
} TCAN_AFLUT;

#define canMSG_hw canMSG_Fuj
#define  _TimeOut_send      _MkSec(10000)

//----- CANopen ----------------------
typedef struct
{
    byte 	state;
    byte 	can_number;
    byte 	mailbox_number;
    byte 	test_can;
    lword  	mode_reg;
    lword  	acceptance_mask_reg;
    lword  	identifier;
    lword  	data_low_reg;
    lword  	data_high_reg;
    lword  	control_reg;
    word  	mailbox_in_use;
    word  	size;
}TCAN_Transfer;

#define AT91C_TEST_NOK                 0
#define AT91C_TEST_OK                  1

#define CAN_STATUS_SUCCESS             0
#define CAN_STATUS_LOCKED              1
#define CAN_STATUS_ABORTED             2
#define CAN_STATUS_RESET               3

#define CAN_DISABLED       0
#define CAN_HALTED         1
#define CAN_IDLE           2
#define CAN_SENDING        3
#define CAN_RECEIVING      4

// MOT: Mailbox Object Type
#define CAN_MOT_DISABLE    0 // Mailbox is disabled
#define CAN_MOT_RECEPT     1 // Reception Mailbox
#define CAN_MOT_RECEPT_OW  2 // Reception mailbox with overwrite
#define CAN_MOT_TRANSMIT   3 // Transmit mailbox
#define CAN_MOT_CONSUMER   4 // Consumer mailbox
#define CAN_MOT_PRODUCER   5 // Producer mailbox



TCAN_Transfer   cantransfer[16];
TCAN_Transfer *pCANTransfer = NULL;
word can_irq_flag;//[_Num_CAN_Ports];


#define mco_test	can_test
#define CAN_Init        can_config
#define _MCO_CAN_H

//byte CAN_Init( byte port );
byte CAN_SendMsg( TCAN_Transfer *pTransfer );
//void CAN_InitMailboxRegisters( TCAN_Transfer *pTransfer );
void CAN_ResetTransfer( TCAN_Transfer *pTransfer );
void CAN_ResetAllMailbox( byte port );
//byte CAN_Synchronisation( byte port );
//byte CAN_BaudRateCalculate( CANHSTR *base_CAN, lword baudrate );
byte SetRxMailbox( byte port, word ID, byte mb );
byte SetTxMailbox( byte port, word ID, byte mb );

//----------------------------------

TCAN_AFLUT can_aflut;
struct CAN_drv_data   can_dd[ _Num_CAN_Ports] ;

TCAN_FIFO can_fifo[_Num_CAN_Ports];



void CAN_aflut_Init( void );
word can_config( byte port );
word can_test( byte port );
word canSend( byte port, struct canMSG_Fuj *ptr );
word canReceive( byte port, struct canMSG_Fuj *ptr );
extern "C" {
void CAN_IRQHandler(void);
}
void can_deInit( byte port );

#endif //  _CAN_DRV_H

