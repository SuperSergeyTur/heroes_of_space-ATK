#ifndef  _MCO_CAN_H
  #define  _MCO_CAN_H

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

#define mSetIRQ_Mailbox( port, mailbox )			( port->rier.word |=  ( 1 << mailbox ) )
#define mClrIRQ_Mailbox( port, mailbox )			( port->rier.word &= ~( 1 << mailbox ) )


byte CAN_Init( byte port );
byte CAN_SendMsg( TCAN_Transfer *pTransfer );
void CAN_InitMailboxRegisters( TCAN_Transfer *pTransfer );
void CAN_ResetTransfer( TCAN_Transfer *pTransfer );
void CAN_ResetAllMailbox( byte port );
byte CAN_Synchronisation( byte port );
byte CAN_BaudRateCalculate( CANHSTR *base_CAN, lword baudrate );
byte SetRxMailbox( byte port, word ID, byte mb );
byte SetTxMailbox( byte port, word ID, byte mb );

#ifdef _CANOPEN_INCLUDE

TCAN_Transfer   cantransfer[8];
TCAN_Transfer *pCANTransfer = NULL;
word can_irq_flag;

#else

extern TCAN_Transfer   cantransfer[];
extern TCAN_Transfer *pCANTransfer;
extern word can_irq_flag;

#endif

#endif  // _CAN_H
