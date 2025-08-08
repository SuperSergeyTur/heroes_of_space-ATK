#ifndef _ad_drv_h
#define _ad_drv_h
//---------------
struct Channel_AD {  
                     word mux  ;
                     word offset ; 
                     word *scale; 
                  } ;

static __INLINE void mAD_Izm( struct Channel_AD ach , word* AddrResult );
void Set_MUX(word num);
void Clr_MUX(word num);

#define AdBuffSize            ((b) 0x0f)  /* все мл.разряды в указателе
                                           * размера должны быть запол-
                                           * нены единицами    */
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


extern void  Start_AD ( void ) ;
word SPI_izm (LPC_SSP_TypeDef *SSPx,
#ifdef _ADC_CS
              LPC_GPIO_TypeDef *CS_Chnl,
#endif
              word chnl);

union ADC_SPI
{
  word all;
  struct
  {
     word NC3     :4;

     word coding  :1;
     word range   :1;
     word NC2     :1;
     word shadow  :1;

     word pm      :2;
     word addr    :3;

     word NC1     :1;
     word seq     :1;
     word write   :1;
  }_;
};
union Shadow_chnls
{
  byte all;
  struct
  {
     word N0      :1;
     word N1      :1;
     word N2      :1;
     word N3      :1;

     word N4      :1;
     word N5      :1;
     word N6      :1;
     word N7      :1;
  }_;
};
union ADC_Shadow
{
  word all;
  union Shadow_chnls  s1;
  union Shadow_chnls  s2;
};
//  Для AD Converter

#define    _ADC_IRQ_PRIORITY       ((0x01<<3)|0x01) // 9

#define    _ADC_CLK        ( 12000000 )  // в Гц
//#define  _ADC_CLK        ( 6000000 )   // в Гц

#define    _AD_BUSY        ( 0x8000 )    // можно задать любой бит старше D11...D0.

#define    _AD_MAX         ( 2046 )
#define    _AD_VOLT        ( 1191 )       // 4095 / 3.3V   - дискрет на 1вольт
//#define    _AD_VOLT_DVUPOL ( 1240 )
//#define  _AD_VOLTucc     ( 1241 )      // 4095 / 3.3V - дискрет на 1вольт внутреннего АЦП
//#define    _AD_K33         ( 3 )         // 1241 / 409  - дискрет на 1вольт при 3.3В АЦП и 10В АЦП
#define    _AD_MaxOffset   ( 4092 )
#define    _AD_Delta         4

#define    _MaxOffset_ach  ( 100 )
#define    _Default_offset ( 2048 )


#define  _Ch0_Numb     0x0000
#define  _Ch1_Numb     0x0001
#define  _Ch2_Numb     0x0002
#define  _Ch3_Numb     0x0003
#define  _Ch4_Numb     0x0004
#define  _Ch5_Numb     0x0005
#define  _Ch6_Numb     0x0006
#define  _Ch7_Numb     0x0007
#define  _Ch8_Numb     0x0008
#define  _Ch9_Numb     0x0009
#define  _Ch10_Numb    0x000a
#define  _Ch11_Numb    0x000b
#define  _Ch12_Numb    0x000c
#define  _Ch13_Numb    0x000d
#define  _Ch14_Numb    0x000e
#define  _Ch15_Numb    0x000f

#define  _Open_AD_BUFFERs
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
#define  mIzmData_Conversion( src , dest , ach )  dest = (sw)(((slw)( ( (w)(src) & 0xFFF ) - (ach).offset )*(slw)(*(ach).scale))/10000)
/* конец макроса  */
//#define ADBuffSize  0x0f;
#define mSet_MUX( num ) Set_MUX(num)
#define mClr_MUX( num ) Clr_MUX(num)
struct ADBuffer
{
  struct Channel_AD *Chnl;
  word              *Out;
};

struct AD_Buff
{
   word InCount;
   word OutCount;
   struct ADBuffer Buffer[AdBuffSize+1];
};

#define def_ach_scale   10000
#define ach_scale_min   9800
#define ach_scale_max   11000
 
const lword FltrNumb[3][2] =
 {
 {0,1},
 {2,1},
 {1,2}
 };

/*------------------------------------------------*/
#ifdef   _MAIN_INCLUDE
/*------------------------------------------------*/
    union ADC_SPI adc_sts;
    union ADC_Shadow adc_sreg;
    struct AD_Buff BuffAD;

    word  t_mux ;
    word AD_busy;
    word flt_en;
    word dtizm, tx;
/*------------------------------------------------*/
#else
/*------------------------------------------------*/
//    extern  const lword FltrNumb[][];
    extern  union ADC_SPI adc_sts;
    extern  union ADC_Shadow adc_sreg;
    extern  struct AD_Buff BuffAD;

    extern  word  t_mux ;
    extern  word AD_busy;
    extern  word dtizm,tx;
/*------------------------------------------------*/
#endif

//---------------
#endif
