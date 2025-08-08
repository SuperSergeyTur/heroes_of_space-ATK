#ifndef _ad_drv_h
#define _ad_drv_h
//---------------

struct Channel_AD
{
    word mux;
    word offset;
    word n_Scale;
};

static __INLINE void mAD_Izm( struct Channel_AD ach, word* AddrResult );
void Start_AD( void );

/*********************************************************************
 * Macro defines for ADC  control register
 **********************************************************************/

/**  Selects which of the AD0.0:7 pins (channels) is (are) to be sampled and converted */
#define ADC_CR_CH_SEL(n)	((1UL << n))

/**  The APB clock (PCLK) is divided by (this value plus one)
* to produce the clock for the A/D */
#define ADC_CR_CLKDIV(n)	((n<<8))

/**  Repeated conversions A/D enable bit */
#define ADC_CR_BURST		((1UL<<16))

/**  ADC convert in power down mode; if 0, it's in power down mode; if 1, it's in normal
* operation mode */
#define ADC_CR_PDN			((1UL<<21))

/**  Start mask bits */
#define ADC_CR_START_MASK	((7UL<<24))

/**  Select Start Mode controll the AD Converter in case the Burst bit is 0 (zero) */
#define ADC_CR_START_MODE_SEL(SEL)	((SEL<<24))

/**  Start conversion now */
#define ADC_CR_START_NOW	((1UL<<24))

/**  Start conversion when the edge selected by bit 27 occurs on P2.10/EINT0 */
#define ADC_CR_START_EINT0	((2UL<<24))

/** Start conversion when the edge selected by bit 27 occurs on P1.27/CAP0.1 */
#define ADC_CR_START_CAP01	((3UL<<24))

/**  Start conversion when the edge selected by bit 27 occurs on MAT0.1 */
#define ADC_CR_START_MAT01	((4UL<<24))

/**  Start conversion when the edge selected by bit 27 occurs on MAT0.3 */
#define ADC_CR_START_MAT03	((5UL<<24))

/**  Start conversion when the edge selected by bit 27 occurs on MAT1.0 */
#define ADC_CR_START_MAT10	((6UL<<24))

/**  Start conversion when the edge selected by bit 27 occurs on MAT1.1 */
#define ADC_CR_START_MAT11	((7UL<<24))

/**  Start conversion on a falling edge on the selected CAP/MAT signal */
#define ADC_CR_EDGE			((1UL<<27))

/*********************************************************************//**
 * Macro defines for ADC Global Data register
 **********************************************************************/

/** When DONE is 1, this field contains result value of ADC conversion
* (in 12-bit value) */
#define ADC_GDR_RESULT(n)		(((n>>4)&0xFFF))

/** These bits contain the channel from which the LS bits were converted */
#define ADC_GDR_CH(n)			(((n>>24)&0x7))

/** This bits is used to mask for Channel */
#define ADC_GDR_CH_MASK			((7UL<<24))

/** This bit is 1 in burst mode if the results of one or
 * more conversions was (were) lost */
#define ADC_GDR_OVERRUN_FLAG	((1UL<<30))

/** This bit is set to 1 when an A/D conversion completes */
#define ADC_GDR_DONE_FLAG		((1UL<<31))

/*********************************************************************
 * Macro defines for ADC Interrupt register
 **********************************************************************/

/** These bits allow control over which A/D channels generate
 * interrupts for conversion completion */
#define ADC_INTEN_CH(n)			((1UL<<n))

/** When 1, enables the global DONE flag in ADDR to generate an interrupt */
#define ADC_INTEN_GLOBAL		((1UL<<8))

// Для AD Converter
#define _ADC_CLK         12000000      // в Гц
#define _AD_BUSY         0x8000        // можно задать любой бит старше D11...D0.

#define _AD_MAX          2046
#define _AD_FULL_MAX     4095          // 0x0FFF - 4095 дискрет для 12-разрядного АЦП 2047
#define _AD_VOLT         (_AD_FULL_MAX / 3) // 4095 / 3 Bольта = 1365 дискрет на 1 Bольт
#define _AD_MaxOffset    4092
#define _AD_Delta        1

#define _MaxOffset_ach   100
#define _Default_offset  2048
#define _mAD_Volt( nom )  ((w)(int)( (const d)(nom) * ((const d)_AD_VOLT) ))

#define _Ch0_Numb        0x0000
#define _Ch1_Numb        0x0001
#define _Ch2_Numb        0x0002
#define _Ch3_Numb        0x0003
#define _Ch4_Numb        0x0004
#define _Ch5_Numb        0x0005

#define _Open_AD_BUFFERs
//-------------------------
     /*   АЦП 10-разрядный однополярный. Для измерения двухполярных
      * сигналов сигнал на входе АЦП смещен вверх, примерно, на пол-питания,
      * поэтому после преобразования необходимо вычитать из результата
      * смещение "_r.IzmSmech" равное, примерно, пол-шкалы АЦП.
      *   Вычитание производится таким образом, чтобы получить положитель-
      * ный модуль результата измерения.
      *   В итоге преобразования получаем стандартное знаковое двухбайтное
      * число.
 * * **
 *
 * word  src  - источник: преобразуемый результат измерения в формате
 *                        регистра АЦП "ad_result";
 * word  dest - адресат: ячейка в которую следует поместить результат
 *                       этого преобразования.
 * struct Channel_AD ach - имя структуры данных для канала АЦП по которому
 *              производится измерение; из этой структуры макрос извлечет
 *              смещение для данного канала АЦП.
 */

     // ADCR:-> S10=0 ,ST1=0 ,ST0=1 ,CT1=1 ,CT0=0 ,RES=0 ,D9...D0=0
        /* преобразование со своим смещением в знаковое  */
#define mIzmData_Conversion( src, dest, ach )  dest = (sw)(((slw)( ( (w)(src) & 0xFFF ) - (ach).offset ) * (slw)( _ar.ADC_Scale[ (ach).n_Scale ] ) ) / 10000 )

#define def_ach_scale   10000
#define ach_scale_min   9800
#define ach_scale_max   11000

word dtizm, tx;

//---------------
#endif
