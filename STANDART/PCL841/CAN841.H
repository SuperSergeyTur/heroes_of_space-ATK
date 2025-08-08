#ifndef  can841_h
#define  can841_h

/*****************************************************************************
 *  FILE        : CAN841.H
 *  DATE        : 11-3-95'
 *  Version     : V1.0
 *  Description : Prototype for CAN841x.LIB
 *
 *
 *
 ******************************************************************************/

#define  BYTE  unsigned char
#define  UI    unsigned int
#define  UL    unsigned long

/* define can controller interrupt connect to PC irq number */
#define CAN1_IRQ  0   /* 0 mean polling */
//#define CAN1_IRQ  12   /* 0 mean polling */
#define	CAN2_IRQ  0      /* 0	mean polling */
#define BASE_ADDR 0xDA00

#define	PORT1		0
#define	PORT2		1

#define	FAIL		0
#define	SUCCESS		1


typedef struct {
        BYTE acc_code;
        BYTE acc_mask;
        BYTE bt0;
        BYTE bt1;
}CAN_STRUCT;

typedef struct {
        UI   id;
        BYTE rtr;
        BYTE dlen;
        BYTE data[8];
} MSG_STRUCT;

extern  int can_err_no;

/*===============  functions declaration ==========================*/
/* set can card hardware setting , if successful return 1, else return 0*/
/*----------------------------------------------------------------------
input:
   segment :set memory decode segment value, 0xC000 to 0xDF00
   irq1    : can port#1 irq number
   irq2    : can port#2 irq number
----------------------------------------------------------------------*/


int canInitHW( void ); // UI segment ); //, BYTE irq1, BYTE irq2);

int  canExitHW( void );

/* reset can controller */
int  canReset( BYTE port );

/* initiallize and configure can controller */
int  canConfig( BYTE port, CAN_STRUCT can);

/* change can controller to normal run mode */
int  canNormalRun( BYTE port );

/* send a message */
int canSendMsg( BYTE  port, MSG_STRUCT send_msg);

/* receive a message */
int  canReceiveMsg( BYTE port, MSG_STRUCT *msg_ptr);

void can0w(BYTE addr, BYTE v) ;
BYTE can0r( BYTE addr) ;
void can1w(BYTE addr, BYTE v) ;
BYTE can1r( BYTE addr) ;

             //  CONTROL REGISTER

#define _ResetRequest        ( 0x01 )

             //  COMMAND REGISTER

#define _TxRequest           ( 0x01 )
#define _AbortTx             ( 0x02 )
#define _ReleaseRxBuff       ( 0x04 )
#define _ClearOvrStatus      ( 0x08 )
#define _GotoSleep           ( 0x10 )

             //  STATUS REGISTER

#define _RxBuffStatus        ( 0x01 )
#define _DataOvr             ( 0x02 )
#define _TxBuffAccess        ( 0x04 )
#define _TxCompleteStatus    ( 0x08 )
#define _RxStatus            ( 0x10 )
#define _TxStatus            ( 0x20 )
#define _ErrorStatus         ( 0x40 )
#define _BusStatus           ( 0x80 )

#endif

