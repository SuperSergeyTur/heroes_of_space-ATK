#ifndef  _UART_H
  #define  _UART_H

#define 	_PULT_			0 // UART0
#define 	_RS485_			2 // UART2


/*********************************************************************//**
 * Macro defines for Macro defines for UART interrupt enable register
 **********************************************************************/
/** RBR Interrupt enable*/
#define UART_IER_RBRINT_EN		((uint32_t)(1<<0))
/** THR Interrupt enable*/
#define UART_IER_THREINT_EN		((uint32_t)(1<<1))
/** RX line status interrupt enable*/
#define UART_IER_RLSINT_EN		((uint32_t)(1<<2))
/** Enables the end of auto-baud interrupt */
#define UART_IER_ABEOINT_EN		((uint32_t)(1<<8))
/** Enables the auto-baud time-out interrupt */
#define UART_IER_ABTOINT_EN		((uint32_t)(1<<9))
/** UART interrupt enable register bit mask */
#define UART_IER_BITMASK		((uint32_t)(0x307))
/** UART1 interrupt enable register bit mask */
#define UART1_IER_BITMASK		((uint32_t)(0x38F))

/*********************************************************************//**
 * Macro defines for Macro defines for UART interrupt identification register
 **********************************************************************/
/** Interrupt Status - Active low */
#define UART_IIR_INTSTAT_PEND	((uint32_t)(1<<0))
/** Interrupt identification: Receive line status*/
#define UART_IIR_INTID_RLS		((uint32_t)(3<<1))
/** Interrupt identification: Receive data available*/
#define UART_IIR_INTID_RDA		((uint32_t)(2<<1))
/** Interrupt identification: Character time-out indicator*/
#define UART_IIR_INTID_CTI		((uint32_t)(6<<1))
/** Interrupt identification: THRE interrupt*/
#define UART_IIR_INTID_THRE		((uint32_t)(1<<1))
/** Interrupt identification: Interrupt ID mask */
#define UART_IIR_INTID_MASK		((uint32_t)(7<<1))
/** These bits are equivalent to UnFCR[0] */
#define UART_IIR_FIFO_EN		((uint32_t)(3<<6))
/** End of auto-baud interrupt */
#define UART_IIR_ABEO_INT		((uint32_t)(1<<8))
/** Auto-baud time-out interrupt */
#define UART_IIR_ABTO_INT		((uint32_t)(1<<9))
/** UART interrupt identification register bit mask */
#define UART_IIR_BITMASK		((uint32_t)(0x3CF))

/*********************************************************************//**
 * Macro defines for Macro defines for UART FIFO control register
 **********************************************************************/
/** UART FIFO enable */
#define UART_FCR_FIFO_EN		((uint8_t)(1<<0))
/** UART FIFO RX reset */
#define UART_FCR_RX_RS			((uint8_t)(1<<1))
/** UART FIFO TX reset */
#define UART_FCR_TX_RS			((uint8_t)(1<<2))
/** UART DMA mode selection */
#define UART_FCR_DMAMODE_SEL 	((uint8_t)(1<<3))
/** UART FIFO trigger level 0: 1 character */
#define UART_FCR_TRG_LEV0		((uint8_t)(0))
/** UART FIFO trigger level 1: 4 character */
#define UART_FCR_TRG_LEV1		((uint8_t)(1<<6))
/** UART FIFO trigger level 2: 8 character */
#define UART_FCR_TRG_LEV2		((uint8_t)(2<<6))
/** UART FIFO trigger level 3: 14 character */
#define UART_FCR_TRG_LEV3		((uint8_t)(3<<6))
/** UART FIFO control bit mask */
#define UART_FCR_BITMASK		((uint8_t)(0xCF))

#define UART_TX_FIFO_SIZE		(16)

/*********************************************************************//**
 * Macro defines for Macro defines for UART line control register
 **********************************************************************/
/** UART 5 bit data mode */
#define UART_LCR_WLEN5     		((uint8_t)(0))
/** UART 6 bit data mode */
#define UART_LCR_WLEN6     		((uint8_t)(1<<0))
/** UART 7 bit data mode */
#define UART_LCR_WLEN7     		((uint8_t)(2<<0))
/** UART 8 bit data mode */
#define UART_LCR_WLEN8     		((uint8_t)(3<<0))
/** UART Two Stop Bits Select */
#define UART_LCR_STOPBIT_SEL	((uint8_t)(1<<2))
/** UART Parity Enable */
#define UART_LCR_PARITY_EN		((uint8_t)(1<<3))
/** UART Odd Parity Select */
#define UART_LCR_PARITY_ODD		((uint8_t)(0))
/** UART Even Parity Select */
#define UART_LCR_PARITY_EVEN	((uint8_t)(1<<4))
/** UART force 1 stick parity */
#define UART_LCR_PARITY_F_1		((uint8_t)(2<<4))
/** UART force 0 stick parity */
#define UART_LCR_PARITY_F_0		((uint8_t)(3<<4))
/** UART Transmission Break enable */
#define UART_LCR_BREAK_EN		((uint8_t)(1<<6))
/** UART Divisor Latches Access bit enable */
#define UART_LCR_DLAB_EN		((uint8_t)(1<<7))
/** UART line control bit mask */
#define UART_LCR_BITMASK		((uint8_t)(0xFF))

/*********************************************************************//**
 * Macro defines for Macro defines for UART line status register
 **********************************************************************/
/** Line status register: Receive data ready*/
#define UART_LSR_RDR		((uint8_t)(1<<0))
/** Line status register: Overrun error*/
#define UART_LSR_OE			((uint8_t)(1<<1))
/** Line status register: Parity error*/
#define UART_LSR_PE			((uint8_t)(1<<2))
/** Line status register: Framing error*/
#define UART_LSR_FE			((uint8_t)(1<<3))
/** Line status register: Break interrupt*/
#define UART_LSR_BI			((uint8_t)(1<<4))
/** Line status register: Transmit holding register empty*/
#define UART_LSR_THRE		((uint8_t)(1<<5))
/** Line status register: Transmitter empty*/
#define UART_LSR_TEMT		((uint8_t)(1<<6))
/** Error in RX FIFO*/
#define UART_LSR_RXFE		((uint8_t)(1<<7))
/** UART Line status bit mask */
#define UART_LSR_BITMASK	((uint8_t)(0xFF))

/*********************************************************************//**
 * Macro defines for Macro defines for UART Scratch Pad Register
 **********************************************************************/
/** UART Scratch Pad bit mask */
#define UART_SCR_BIMASK		((uint8_t)(0xFF))

/*********************************************************************//**
 * Macro defines for Macro defines for UART Auto baudrate control register
 **********************************************************************/
/** UART Auto-baud start */
#define UART_ACR_START				((uint32_t)(1<<0))
/** UART Auto baudrate Mode 1 */
#define UART_ACR_MODE				((uint32_t)(1<<1))
/** UART Auto baudrate restart */
#define UART_ACR_AUTO_RESTART		((uint32_t)(1<<2))
/** UART End of auto-baud interrupt clear */
#define UART_ACR_ABEOINT_CLR		((uint32_t)(1<<8))
/** UART Auto-baud time-out interrupt clear */
#define UART_ACR_ABTOINT_CLR		((uint32_t)(1<<9))
/** UART Auto Baudrate register bit mask */
#define UART_ACR_BITMASK			((uint32_t)(0x307))

/*********************************************************************//**
 * Macro defines for Macro defines for UART IrDA control register
 **********************************************************************/
/** IrDA mode enable */
#define UART_ICR_IRDAEN			((uint32_t)(1<<0))
/** IrDA serial input inverted */
#define UART_ICR_IRDAINV		((uint32_t)(1<<1))
/** IrDA fixed pulse width mode */
#define UART_ICR_FIXPULSE_EN	((uint32_t)(1<<2))
/** PulseDiv - Configures the pulse when FixPulseEn = 1 */
#define UART_ICR_PULSEDIV(n)	((uint32_t)((n&0x07)<<3))
/** UART IRDA bit mask */
#define UART_ICR_BITMASK		((uint32_t)(0x3F))

/*********************************************************************//**
 * Macro defines for Macro defines for UART Fractional divider register
 **********************************************************************/
/** Baud-rate generation pre-scaler divisor */
#define UART_FDR_DIVADDVAL(n)	((uint32_t)(n&0x0F))
/** Baud-rate pre-scaler multiplier value */
#define UART_FDR_MULVAL(n)		((uint32_t)((n<<4)&0xF0))
/** UART Fractional Divider register bit mask */
#define UART_FDR_BITMASK		((uint32_t)(0xFF))

/*********************************************************************//**
 * Macro defines for Macro defines for UART Tx Enable register
 **********************************************************************/
/** Transmit enable bit */
#define UART_TER_TXEN			((uint8_t)(1<<7))
/** UART Transmit Enable Register bit mask */
#define UART_TER_BITMASK		((uint8_t)(0x80))

/*********************************************************************//**
 * Macro defines for Macro defines for UART FIFO Level register
 **********************************************************************/
/** Reflects the current level of the UART receiver FIFO */
#define UART_FIFOLVL_RXFIFOLVL(n)	((uint32_t)(n&0x0F))
/** Reflects the current level of the UART transmitter FIFO */
#define UART_FIFOLVL_TXFIFOLVL(n)	((uint32_t)((n>>8)&0x0F))
/** UART FIFO Level Register bit mask */
#define UART_FIFOLVL_BITMASK		((uint32_t)(0x0F0F))


/*********************************************************************//**
 * Macro defines for Macro defines for UARTn Divisor Latch LSB register
 **********************************************************************/
/** Macro for loading least significant halfs of divisors */
#define UART_LOAD_DLL(div)	((div) & 0xFF)
/** Divisor latch LSB bit mask */
#define UART_DLL_MASKBIT	((uint8_t)0xFF)

/*********************************************************************//**
 * Macro defines for Macro defines for UARTn Divisor Latch MSB register
 **********************************************************************/
/** Divisor latch MSB bit mask */
#define UART_DLM_MASKBIT	((uint8_t)0xFF)
/** Macro for loading most significant halfs of divisors */
#define UART_LOAD_DLM(div)  (((div) >> 8) & 0xFF)

/*********************************************************************//**
 * Macro defines for Macro defines for UARTn Receiver Buffer Register
 **********************************************************************/
/** UART Received Buffer mask bit (8 bits) */
#define UART_RBR_MASKBIT   	((uint8_t)0xFF)


#define UART_ACCEPTED_BAUDRATE_ERROR	(3)			/*!< Acceptable UART baudrate error */


#define  mSymbol_in_TXD_port(data) LPC_UART0->THR = data;

//------   Настройка регистра управления UART   ----------------------
typedef enum
{
	UART_DATABIT_5		= 0,     		/*!< UART 5 bit data mode */
	UART_DATABIT_6,		     			/*!< UART 6 bit data mode */
	UART_DATABIT_7,		     			/*!< UART 7 bit data mode */
	UART_DATABIT_8		     			/*!< UART 8 bit data mode */
} TUART_DATABIT;

typedef enum
{
	UART_STOPBIT_1		= (0),   					/*!< UART 1 Stop Bits Select */
	UART_STOPBIT_2,		 							/*!< UART Two Stop Bits Select */
} TUART_STOPBIT;

typedef enum
{
	UART_PARITY_NONE 	= 0,					/*!< No parity */
	UART_PARITY_ODD,	 						/*!< Odd parity */
	UART_PARITY_EVEN, 							/*!< Even parity */
	UART_PARITY_SP_1, 							/*!< Forced "1" stick parity */
	UART_PARITY_SP_0 							/*!< Forced "0" stick parity */
} TUART_PARITY;

typedef enum
{
	UART_FIFO_TRGLEV0 = 0,	/*!< UART FIFO trigger level 0: 1 character */
	UART_FIFO_TRGLEV1, 		/*!< UART FIFO trigger level 1: 4 character */
	UART_FIFO_TRGLEV2,		/*!< UART FIFO trigger level 2: 8 character */
	UART_FIFO_TRGLEV3		/*!< UART FIFO trigger level 3: 14 character */
} TUART_FIFO_LEVEL;
//---------------------------------------------------------------------------------

typedef enum
{
	UART_RS485_DIS		= (0),
	UART_RS484_EN,
} TUART_RS485_ON;

//---------------------------------------------------------------------------------

typedef struct
{
	TUART_RS485_ON	on;
	byte	dly;
} TUART_RS485_Config;

typedef struct
{
  lword 				baudrate;
  TUART_DATABIT			data;
  TUART_PARITY			parity;
  TUART_STOPBIT			stop;
  TUART_RS485_Config	RS485;
} TUART_Config;

/*********************************************************************//**
 * Macro defines for Macro defines for UART RS485 Control register
 **********************************************************************/
/** RS-485/EIA-485 Normal Multi-drop Mode (NMM) is disabled */
#define UART_RS485CTRL_NMM_EN		((lword)(1<<0))
/** The receiver is disabled */
#define UART_RS485CTRL_RX_DIS		((lword)(1<<1))
/** Auto Address Detect (AAD) is enabled */
#define UART_RS485CTRL_AADEN		((lword)(1<<2))
/** If direction control is enabled (bit DCTRL = 1), pin DTR is used for direction control */
#define UART_RS485CTRL_SEL_DTR		((lword)(1<<3))
/** Enable Auto Direction Control */
#define UART_RS485CTRL_DCTRL_EN	((lword)(1<<4))
/** This bit reverses the polarity of the direction control signal on the RTS (or DTR) pin.
The direction control pin will be driven to logic "1" when the transmitter has data to be sent */
#define UART_RS485CTRL_OINV_1		((lword)(1<<5))

/** RS485 control bit-mask value */
#define UART_RS485CTRL_BITMASK		((lword)(0x3F))

/*********************************************************************//**
 * Macro defines for Macro defines for UART1 RS-485 Address Match register
 **********************************************************************/
#define UART_RS485ADRMATCH_BITMASK ((byte)(0xFF)) 	/**< Bit mask value */

/*********************************************************************//**
 * Macro defines for Macro defines for UART1 RS-485 Delay value register
 **********************************************************************/
/* Macro defines for UART1 RS-485 Delay value register */
#define UART_RS485DLY_BITMASK		((byte)(0xFF)) 	/** Bit mask value */

#define UART_BLOCKING_TIMEOUT			(0xFFFFFFFFUL)

extern "C" {
void UART0_IRQHandler( void );
}

void   mRestart_Output( void );
void UART_Init( byte port );





#endif // _UART_H
