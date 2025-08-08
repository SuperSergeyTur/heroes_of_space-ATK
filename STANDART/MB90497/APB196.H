#ifndef _apb196_h
#define _apb196_h

/*   Задаем источник ввода/вывода для пультовых программ.
 *  ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД
 */       //  Родной последов.порт 196-й
#define   _Terminal_196xRS232

//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД

typedef   unsigned char       byte  ;
typedef   unsigned int        word  ;
typedef   unsigned long int  lword  ;

typedef     signed char      sbyte  ;
typedef     signed int       sword  ;
typedef     signed long int slword  ;

typedef   const               c  ;
typedef   double              d  ;
typedef   unsigned char       b  ;
typedef   unsigned int        w  ;
typedef   unsigned long int  lw  ;

typedef     signed char      sb  ;
typedef     signed int       sw  ;
typedef     signed long int slw  ;

//-----------------------------------------------

#ifdef _24_BITS_
//----------------------
typedef   far unsigned char       fbyte  ;
typedef   far unsigned int        fword  ;
typedef   far unsigned long int  flword  ;

typedef   far   signed char      fsbyte  ;
typedef   far   signed int       fsword  ;
typedef   far   signed long int fslword  ;

typedef   far double              fd  ;
typedef   far unsigned char       fb  ;
typedef   far unsigned int        fw  ;
typedef   far unsigned long int  flw  ;

typedef   far   signed char      fsb  ;
typedef   far   signed int       fsw  ;
typedef   far   signed long int fslw  ;
//----------------------
#else
//----------------------
typedef   unsigned char       fbyte  ;
typedef   unsigned int        fword  ;
typedef   unsigned long int  flword  ;

typedef     signed char      fsbyte  ;
typedef     signed int       fsword  ;
typedef     signed long int fslword  ;

typedef   double              fd  ;
typedef   unsigned char       fb  ;
typedef   unsigned int        fw  ;
typedef   unsigned long int  flw  ;

typedef     signed char      fsb  ;
typedef     signed int       fsw  ;
typedef     signed long int fslw  ;
//----------------------
#endif
//-----------------------------------------------

//-------  PTS-блок одиночной пересылки  --------
  struct SingleTrans_PtsCtrlBlock {
                            byte      count;
                            byte      con;
                   volatile byte     *src;
                            byte     *dst;
                          } ;

//-------  PTS-блок для ШИМ на одном ЕПА  --------
  struct PWM_PtsCtrlBlock {
                            byte  unused ; /* не используется */
                            byte      con;
                            word     *ptr;
                            word      t1 ;
                            word      t2 ;
                          } ;


/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/
#ifdef  _MAIN_INCLUDE
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/

  struct  SingleTrans_PtsCtrlBlock  RXD_pts  ;
#pragma locate ( RXD_pts = 0x1F0 )

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/
#else
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/

extern  struct  SingleTrans_PtsCtrlBlock  RXD_pts  ;

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/
#endif


//--------------------------------------------------------
//         НАСТРОЙКИ  ТАЙМЕРОВ

           //    Код задающий время захвата АЦП:
           //  N = ( Tsam*Fxtal - 2 )/8 ;

#define  _AD_SAM_TIME         (7 << 5)

           //    Код задающий время преобразования АЦП:
           //  N = ( Tconv*Fxtal - 3 )/( 2*B ) - 1 ;

#define  _AD_CONV_TIME        (  16  )
//#define  _AD_GO               ( ???0x08 )
#define  _AD_BUSY             ( 0x08 )
//#define  _MASK_MuxAD          ( ???0x8A )

//--------------------------------------------------------
//         НАСТРОЙКИ  ТАЙМЕРОВ
//
#define  COUNT_ENABLE         0x80
#define  COUNT_DISABLE        0x00
#define  COUNT_UP             0x40
#define  COUNT_DOWN           0x00
#define  CLOCK_INTERNAL       0x00
#define  CLOCK_EXTERNAL       0x08
#define  DIRECTION_TXDIR      0x10
#define  CLOCK_T1_OVFL        0x20
#define  DIRECTION_T1_OVFL    0x10
#define  QUADRATURE_CLOCK     0x38

#define  DIVIDE_BY_1          0x00
#define  DIVIDE_BY_2          0x01
#define  DIVIDE_BY_4          0x02
#define  DIVIDE_BY_8          0x03
#define  DIVIDE_BY_16         0x04
#define  DIVIDE_BY_32         0x05
#define  DIVIDE_BY_64         0x06
#define  DIVIDE_BY_STANDART   DIVIDE_BY_4  // ВЫБОР ДЕЛИТЕЛЯ

//--------------------------------------------------------
//
//          Настройка  ЕПА
//
#define   CAPTURE             (byte) 0x00
#define   COMPARE             (byte) 0x40
#define   USE_TIMER1          (byte) 0x00
#define   USE_TIMER2          (byte) 0x80
#define   OVERWRITE_NEW_DATA  (byte) 0x01
#define   IGNORE_NEW_DATA     (byte) 0x00
#define   AUTO_LOAD           (byte) 0x08
#define   NO_AUTO_LOAD        (byte) 0x00
#define   NO_MAP              (word) 0x0000
#define   RE_MAP              (word) 0x0100

           /* тип регистрируемого события */
#define   NEG_EDGE            (byte) 0x10
#define   POS_EDGE            (byte) 0x20
#define   BOTH_EDGE           (byte) 0x30

           /* тип формируемого события */
#define   NO_EVENT            (byte) 0x00
#define   CLR_PIN             (byte) 0x10
#define   SET_PIN             (byte) 0x20
#define   TOGGLE_PIN          (byte) 0x30
#define   RESET_MY_TIMER      (byte) 0x01
#define   RST_ALIEN_TIMER     (byte) 0x02  /* для режима CAPTURE */
#define   RESET_ALIEN_TIMER   (byte) 0x03  /* для режима COMPARE */
#define   EPA_START_AD        (byte) 0x04

/*-------------- INT_MASK  ------------------------*/

#define   EPAX_IntEnable      ( byte )   0x01
#define   EPA3_IntEnable      ( byte )   0x02
#define   EPA2_IntEnable      ( byte )   0x04
#define   EPA1_IntEnable      ( byte )   0x08
#define   EPA0_IntEnable      ( byte )   0x10
#define   AD_IntEnable        ( byte )   0x20

/*-------------- INT_MASK1 ------------------------*/

#define   _SSIO0_IntEnable    ( byte )   0x02
#define   _SSIO1_IntEnable    ( byte )   0x04
#define   TXD_IntEnable       ( byte )   0x08
#define   RXD_IntEnable       ( byte )   0x10
#define   EXTINT_IntEnable    ( byte )   0x40


/*-------------- EPA_MASK  ------------------------*/

#define   EPA4_Enable        ( word )   0x8000
#define   EPA5_Enable        ( word )   0x4000
#define   EPA6_Enable        ( word )   0x2000
#define   EPA7_Enable        ( word )   0x1000
#define   EPA8_Enable        ( word )   0x0800
#define   EPA9_Enable        ( word )   0x0400
#define   OVR0_Enable        ( word )   0x0200
#define   OVR1_Enable        ( word )   0x0100
#define   OVR2_Enable        ( word )   0x0080
#define   OVR3_Enable        ( word )   0x0040
#define   OVR4_Enable        ( word )   0x0020
#define   OVR5_Enable        ( word )   0x0010
#define   OVR6_Enable        ( word )   0x0008
#define   OVR7_Enable        ( word )   0x0004
#define   OVR8_Enable        ( word )   0x0002
#define   OVR9_Enable        ( word )   0x0001

/*-------------- EPA_MASK1 ------------------------*/

#define   _COMP0_IntEnable   ( byte )   0x08
#define   _COMP1_IntEnable   ( byte )   0x04
#define   _OVRTM1_IntEnable  ( byte )   0x02
#define   _OVRTM2_IntEnable  ( byte )   0x01

/*-------------- EPAIPV    ------------------------*/

#define   _OVRTM2_IPV      ( byte )   0x01
#define   _OVRTM1_IPV      ( byte )   0x02
#define   _COMP1_IPV       ( byte )   0x03
#define   _COMP0_IPV       ( byte )   0x04
#define   OVR0_IPV         ( byte )   0x0E
#define   EPA8_IPV         ( byte )   0x10
#define   EPA4_IPV         ( byte )   0x14


/*----------------------------------------------*/
      //  Условная компиляция для того, чтобы можно было задать
     // из конткретного проекта другую частоту кварца.
#ifndef   F_Quarz
#define   F_Quarz         ((lw) 18432000ul )
#endif

/*-------------- SP_BAUD   ------------------------*/

#define   _SP_INTERNAL_CLK       ( w )   0x8000u
#define   _SP_EXTERNAL_CLK       ( w )   0x0000u
#define   _SP_BAUD_1200       (w) ( F_Quarz / 16u / 1200u    - 1u )
#define   _SP_BAUD_9600       (w) ( F_Quarz / 16u / 9600u    - 1u )
#define   _SP_BAUD_19200      (w) ( F_Quarz / 16u / 19200u   - 1u )
#define   _SP_BAUD_57600      (w) ( F_Quarz / 16u / 57600u   - 1u )
#define   _SP_BAUD_115200     (w) ( F_Quarz / 16u / 115200ul - 1u )
#define   _SP_STANDART_BAUD     _SP_BAUD_19200

/*-------------- SP_CON    ------------------------*/

#define   SP_MODE0             ( byte )     0x00
#define   SP_MODE1             ( byte )     0x01
#define   SP_MODE2             ( byte )     0x02
#define   SP_MODE3             ( byte )     0x03
#define   REC_ENABLE           ( byte )     0x08
#define   REC_DISABLE          ( byte )     0x00
#define   EVEN_PARITY          ( byte )     0x04
#define   ODD_PARITY           ( byte )     0x24
#define   NO_PARITY            ( byte )     0x00
#define   ON_PARITY            ( byte )     0x04
#define   SET_BIT_8            ( byte )     0x10

/*-------------- SP_STAT   ------------------------*/

#define   RPE_BIT                ( byte )   0x80
#define   RB8_BIT                ( byte )   0x80
#define   RI_BIT                 ( byte )   0x40
#define   TI_BIT                 ( byte )   0x20
#define   FE_BIT                 ( byte )   0x10
#define   TXE_BIT                ( byte )   0x08
#define   OE_BIT                 ( byte )   0x04

//------------   SSIO  -  Синхронный Порт

#define   _SYNC_BAUD_GEN_ENABLE    ( b )   0x80
#define   _SYNC_BAUD_GEN_DISABLE   ( b )   0x00
#define   _SYNC_BAUD_2304K         ( b )   0x00
#define   _SYNC_BAUD_1152K         ( b )   0x01
#define   _SYNC_BAUD_768K          ( b )   0x02
#define   _SYNC_BAUD_576K          ( b )   0x03
#define   _SYNC_BAUD_460K8         ( b )   0x04

#define   _STANDART_SYNC_BAUD  _SYNC_BAUD_460K8

#define   _SSIO_MASTER             ( b )   0x80
#define   _SSIO_SLAVE              ( b )   0x00
#define   _SSIO_TRANSMITTER        ( b )   0x40
#define   _SSIO_RECEIVER           ( b )   0x00
#define   _SSIO_T_R_BIT_TOGGLE     ( b )   0x20
#define   _SSIO_HANDSHAKE_ENABLE   ( b )   0x10
#define   _SSIO_HANDSHAKE_DISABLE  ( b )   0x00
#define   _SSIO_TRANSFER_ENABLE    ( b )   0x08
#define   _SSIO_AUTO_TRANS_RE_EN   ( b )   0x04
#define   _SSIO_OVERFLOW_FLAG      ( b )   0x02
#define   _SSIO_TRANSCEIVER_STATUS ( b )   0x01

/*------------------------------------------------*/
#endif
