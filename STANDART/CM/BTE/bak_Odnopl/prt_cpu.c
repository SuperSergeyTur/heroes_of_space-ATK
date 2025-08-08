//#include "iocon.h"
//#include "user.h"
/*-----------------15.08.2012 11:22-----------------
 *
 * --------------------------------------------------*/
void Init_CPU_Ports( void )
{
 // byte i;                                             //  BTE          //KTE
 // P0
    LPC_IOCON->P0_0   = D_RESERV | 0x1;                 // CAN0.RX
    LPC_IOCON->P0_1   = D_RESERV | 0x1;                 // CAN0.TX
    LPC_IOCON->P0_2   = D_RESERV | 0x1;                 // UART0.TX
    LPC_IOCON->P0_3   = D_RESERV | 0x1;                 // UART0.RX

    LPC_IOCON->P0_4   = D_RESERV | 0x2;                 // CAN1.RX
    LPC_IOCON->P0_5   = D_RESERV | 0x2;                 // CAN1.TX
    LPC_IOCON->P0_6   = D_RESERV | D_MODE_PULLUP | 0;   // Не исп.// CS0
    LPC_IOCON->P0_7   = D_RESERV | D_MODE_PULLUP | 0;   // Не исп.// CS1
    LPC_IOCON->P0_8   = D_RESERV | D_MODE_PULLUP | 0;   // Не исп.// CS2
    LPC_IOCON->P0_9   = D_RESERV | D_MODE_PULLUP | 0;   // Не исп.// CS3
    LPC_IOCON->P0_10  = D_RESERV | D_MODE_PULLUP | 0;   // Не исп.// CS4
    LPC_IOCON->P0_11  = D_RESERV | D_MODE_PULLUP | 0;   // Не исп.// CS5
    LPC_IOCON->P0_12  = A_RESERV | A_ADMODE_AM | 0x3;   // ADC6
    LPC_IOCON->P0_13  = A_RESERV | 0;                   // Не исп. //ADC7
    LPC_IOCON->P0_14  = D_RESERV | D_MODE_PULLUP| 0x3;  // USB.CON
    LPC_IOCON->P0_15  = D_RESERV | D_MODE_PULLUP | 0;   // Не исп.
//  LPC_IOCON->P0_16 =  // Emc.c
    LPC_IOCON->P0_17  = D_RESERV | D_HYS_EN | 0;        // Выход БО (60)
    LPC_IOCON->P0_18  = D_RESERV | 0;                   // KAR1
    LPC_IOCON->P0_19  = D_RESERV | 0;                   // KAR2
    LPC_IOCON->P0_20  = D_RESERV | D_MODE_PULLUP | 0;   // Не исп. // INT6
    LPC_IOCON->P0_21  = D_RESERV | D_MODE_PULLUP | 0;   // Не исп. // INT7
    LPC_IOCON->P0_22  = D_RESERV | D_MODE_PULLUP | 0;   // Не исп. // SSP.CS6
    LPC_IOCON->P0_23  = A_RESERV | A_ADMODE_AM | 0x1;   // ADC0
    LPC_IOCON->P0_24  = A_RESERV | A_ADMODE_AM | 0x1;   // ADC1
    LPC_IOCON->P0_25  = A_RESERV | A_ADMODE_AM | 0x1;   // ADC2
    LPC_IOCON->P0_26  = A_RESERV | 0x2;                 // DA0
    LPC_IOCON->P0_27  = I_RESERV | 0;                   // ADC.MUX0
    LPC_IOCON->P0_28  = I_RESERV | 0;                   // ADC.MUX1
    LPC_IOCON->P0_29  = U_RESERV | 0;                   // ADC.MUX2
    LPC_IOCON->P0_30  = U_RESERV | 0;                   // ADC.P04
    LPC_IOCON->P0_31  = U_RESERV | 0x1;                 // USB.DP
    LPC_GPIO0->DIR = _ADC_USR_Msk | 0x000c0000;         // Выходы: KAR1, KAR2

// Настройка USEL
    LPC_IOCON->P1_0  = D_RESERV | 0;                    // LED-CAN1
    LPC_IOCON->P1_1  = D_RESERV | D_MODE_PULLUP | 0; 					// Q1V
    LPC_IOCON->P1_2  = D_RESERV | D_MODE_PULLUP | D_HYS_EN | 0;         // Pi1 (KS)
    LPC_IOCON->P1_3  = D_RESERV | 0;                    // SUM0
    LPC_IOCON->P1_4  = D_RESERV | D_MODE_PULLUP | D_HYS_EN | 0;         // Pi1 (KF)   // Q2V
    LPC_IOCON->P1_5  = D_RESERV | 0;                    // SUM1
    LPC_IOCON->P1_6  = D_RESERV | D_MODE_PULLUP | 0;    // Не исп.
    LPC_IOCON->P1_7  = D_RESERV | D_MODE_PULLUP | 0;    // Не исп.
    LPC_IOCON->P1_8  = D_RESERV | D_MODE_PULLUP | 0;    // Не исп.
    LPC_IOCON->P1_9  = D_RESERV | D_MODE_PULLUP | 0;    // Не исп.
//  LPC_IOCON->P1_10 = D_RESERV | D_HYS_EN | 0x3;       // прописан в Timer.c
    LPC_IOCON->P1_11 = D_RESERV | D_MODE_PULLUP | 0;    // Не исп.
    LPC_IOCON->P1_12 = D_RESERV | D_MODE_PULLUP | 0;    // Не исп.
    LPC_IOCON->P1_13 = D_RESERV | D_MODE_PULLUP | 0;    // Не исп.
    LPC_IOCON->P1_14 = D_RESERV | D_MODE_PULLUP | 0;    // Не исп.
    LPC_IOCON->P1_15 = D_RESERV | D_MODE_PULLUP | 0;    // Не исп.
    LPC_IOCON->P1_16 = D_RESERV | D_MODE_PULLUP | 0;    // Не исп.
//  LPC_IOCON->P1_18 = D_RESERV | D_HYS_EN | 0x3;       // прописан в Timer.c
//  LPC_IOCON->P1_19 = D_RESERV | D_HYS_EN | 0x3;       // прописан в Timer.c
    LPC_IOCON->P1_20 = D_RESERV | D_MODE_PULLUP | 0;    // Не исп.    КТЕ - // | 0x3; // FX0
    LPC_IOCON->P1_21 = D_RESERV | D_MODE_PULLUP | 0;    // Не исп.
    LPC_IOCON->P1_22 = D_RESERV | D_MODE_PULLUP | 0;    // Не исп.
    LPC_IOCON->P1_23 = D_RESERV | D_MODE_PULLUP | 0;    // Не исп.    КТЕ - // | 0x3; // FX1
    LPC_IOCON->P1_24 = D_RESERV | D_MODE_PULLUP | 0;    // Не исп.    КТЕ - // | 0x3; // FZ
    LPC_IOCON->P1_25 = D_RESERV | D_MODE_PULLUP | 0;    // Не исп.
//  LPC_IOCON->P1_26 = D_RESERV | D_HYS_EN | 0x3;       // прописан в Timer.c
    LPC_IOCON->P1_27 = D_RESERV | D_MODE_PULLUP | 0;    // Не исп.
    LPC_IOCON->P1_28 = D_RESERV | D_MODE_PULLUP | 0;    // Не исп.
//  LPC_IOCON->P1_29 = // Emc.c
    LPC_IOCON->P1_30 = A_RESERV | A_ADMODE_AM | 0x3;    // ADC5
    LPC_IOCON->P1_31 = A_RESERV | A_ADMODE_AM | 0x3;    // ADC4

    mCLR_Q1();  // без него отлючается QV1 при старте программы и АПВ "накрывается". Если опустить ниже LPC_GPIO1->DIR все равно остается стробик,
                // который не отключает автомат с катушкой. Оставил в этом месте здесь нет даже стробика
    LPC_GPIO1->DIR |= 0x0000002B;      // Выходы: LED-CAN1, Q1V, SUM0, SUM1


// Настройка Input Port 0
    LPC_IOCON->P2_0   = D_RESERV | D_MODE_PULLUP | 0;   // Не исп.  // PPG4
    LPC_IOCON->P2_1   = D_RESERV | D_MODE_PULLUP | 0;   // Не исп.  // PPG6
    LPC_IOCON->P2_2   = D_RESERV | D_MODE_PULLUP | 0;   // Не исп.  // PPG5 - Если запайка #4:1-2
    LPC_IOCON->P2_3   = D_RESERV | 0;                   // PPG7
    LPC_IOCON->P2_4   = D_RESERV | 0;                   // DA1 (PWM1.5)
    LPC_IOCON->P2_5   = D_RESERV | D_MODE_PULLUP | 0;   // Не исп.
    LPC_IOCON->P2_6   = D_RESERV | 0x4;                 // RS485.RTS (UART2.OE)
    LPC_IOCON->P2_7   = D_RESERV | D_MODE_PULLUP | 0;   // Не исп.
    LPC_IOCON->P2_8   = D_RESERV | 0x2;                 // RS485.TX
    LPC_IOCON->P2_9   = D_RESERV | 0x2;                 // RS485.RX
    LPC_IOCON->P2_10  = D_RESERV | D_HYS_EN | 0x1;      // INT0
    LPC_IOCON->P2_11  = D_RESERV | D_HYS_EN | D_MODE_PULLUP | 0x1;      // INT1
    LPC_IOCON->P2_12  = D_RESERV | D_HYS_EN | D_MODE_PULLUP | 0x1;      // INT2
    LPC_IOCON->P2_13  = D_RESERV | D_HYS_EN | D_MODE_PULLUP | 0x1;      // INT3
//  LPC_IOCON->P2_14  = // Emc.c
    LPC_IOCON->P2_15  = D_RESERV | D_MODE_PULLUP | 0;   // Не исп.  // INT4
    LPC_IOCON->P2_16  = D_RESERV | D_MODE_PULLUP | 0;   // Pi/Po(Изм. назн. выборкой)    // Pi0.0
    LPC_IOCON->P2_17  = D_RESERV | D_MODE_PULLUP | 0;   // Pi/Po(Изм. назн. выборкой)    // Pi0.1
    LPC_IOCON->P2_18  = D_RESERV | D_MODE_PULLUP | 0;   // Pi/Po(Изм. назн. выборкой)    // Pi0.2
    LPC_IOCON->P2_19  = D_RESERV | D_MODE_PULLUP | 0;   // Pi/Po(Изм. назн. выборкой)    // Pi0.3
    LPC_IOCON->P2_20  = D_RESERV | D_MODE_PULLUP | 0;   // Pi/Po(Изм. назн. выборкой)    // Pi0.4
    LPC_IOCON->P2_21  = D_RESERV | D_MODE_PULLUP | 0;   // Pi/Po(Изм. назн. выборкой)    // Pi0.5
    LPC_IOCON->P2_22  = D_RESERV | D_MODE_PULLUP | 0;   // Pi/Po(Изм. назн. выборкой)    // Pi0.6
    LPC_IOCON->P2_23  = D_RESERV | D_MODE_PULLUP | 0;   // Pi/Po(Изм. назн. выборкой)    // Pi0.7
//  LPC_IOCON->P2_24  = D_RESERV | D_MODE_PULLUP | 0;   // J1 перекл. S3 (PIN-STOP)    // Po0.0
    LPC_IOCON->P2_25  = D_RESERV | D_MODE_PULLUP | 0;   // J2 перекл. S3               // Po0.1
    LPC_IOCON->P2_26  = D_RESERV | D_HYS_EN | 0;        // CS0 ()                      // Po0.2
    LPC_IOCON->P2_27  = D_RESERV | D_HYS_EN | 0;        // CS1 ()                      // Po0.3
    LPC_IOCON->P2_28  = D_RESERV | D_HYS_EN | 0;        // CS2 ()                      // Po0.4
    LPC_IOCON->P2_29  = D_RESERV | D_MODE_PULLUP | 0;   // Не исп.                     // Po0.5
    LPC_IOCON->P2_30  = D_RESERV | 0x2;                 // I2C.SDA
    LPC_IOCON->P2_31  = D_RESERV | 0x2;                 // I2C.SCL

    LPC_GPIO2->DIR =  0x1C000018 ;// 0x3F00001F ;
// Набваойкая PINSTOP
    LPC_IOCON->P2_24  = D_RESERV | D_MODE_PULLUP | D_HYS_EN | 0;        // (PIN-STOP)
    LPC_GPIO2->DIR &= ~PINSTOP_Msk;     //

//  LPC_IOCON->P3_0  = // Emc.c
//       . . .
//  LPC_IOCON->P3_15 = // Emc.c
    LPC_IOCON->P3_16  = D_RESERV  | 0;                  // U1 (Prt_drv.h)
    LPC_IOCON->P3_17  = D_RESERV  | 0;                  // U2 (Prt_drv.h)
    LPC_IOCON->P3_18  = D_RESERV  | 0;                  // U3 (Prt_drv.h)
    LPC_IOCON->P3_19  = D_RESERV  | 0;                  // U4 (Prt_drv.h)
    LPC_IOCON->P3_20  = D_RESERV  | 0;                  // U5 (Prt_drv.h)
    LPC_IOCON->P3_21  = D_RESERV  | 0;                  // U6 (Prt_drv.h)
    LPC_IOCON->P3_22  = D_RESERV  | 0;                  // LED-RS485
    LPC_IOCON->P3_23  = D_RESERV  | D_MODE_PULLUP | 0;  // Не исп.
    LPC_IOCON->P3_24  = D_RESERV  | D_MODE_PULLUP | 0;  // Не исп.          //V1
    LPC_IOCON->P3_25  = D_RESERV  | D_MODE_PULLUP | 0;  // J4 перекл. S3    //V2
    LPC_IOCON->P3_26  = D_RESERV  | D_MODE_PULLUP | 0;  // J3 перекл. S3    //V3
    LPC_IOCON->P3_27  = D_RESERV  | 0;                  // LED-CAN0         //V4
    LPC_IOCON->P3_28  = D_RESERV  | D_MODE_PULLUP | 0;  // Не исп.          //V5
    LPC_IOCON->P3_29  = D_RESERV  | D_MODE_PULLUP | 0;  // Не исп.          //V6
    LPC_IOCON->P3_30  = D_RESERV  | D_MODE_PULLUP | 0;  // Не исп.
    LPC_IOCON->P3_31  = D_RESERV  | D_MODE_PULLUP | 0;  // Не исп.          //CS-ADC
    //выходы
    LPC_GPIO3->DIR =  0x087f0000 ;
    LPC_GPIO3->SET =  0x003f0000 ;                      // высокий уровень для импульсов управления


//  LPC_IOCON->P4_0  = // Emc.c
//       . . .
//  LPC_IOCON->P4_19 = // Emc.c
    LPC_IOCON->P4_20  = D_RESERV  | D_MODE_PULLUP | 0 | 0x3; //SCK1
    LPC_IOCON->P4_21  = D_RESERV  | D_MODE_PULLUP | 0 | 0x3; //CS_SPI1
    LPC_IOCON->P4_22  = D_RESERV  | D_MODE_PULLUP | 0 | 0x3; //MISO1
    LPC_IOCON->P4_23  = D_RESERV  | D_MODE_PULLUP | 0 | 0x3; //MOSI1
//  LPC_IOCON->P4_24 = // Emc.c
//       . . .
//  LPC_IOCON->P4_27 = // Emc.c
    LPC_IOCON->P4_28  = D_RESERV  | D_MODE_PULLUP | 0 ; // Не исп.
    LPC_IOCON->P4_29  = D_RESERV  | D_MODE_PULLUP | 0 ; // Не исп.
    LPC_IOCON->P4_30  = D_RESERV  | D_MODE_PULLUP | 0 ; // Не исп.   // Emc.c (EMC.CS0)
//  LPC_IOCON->P4_31 = // Emc.c

    //выходы
    LPC_GPIO4->DIR =  0x00000000 ;



    LPC_IOCON->P5_0 = D_RESERV  | D_MODE_PULLUP | 0 ;   // Не исп.
    LPC_IOCON->P5_1 = D_RESERV  | D_MODE_PULLUP | 0 ;   // Не исп.
    LPC_IOCON->P5_2 = I_RESERV  | 0 ;                   // Не исп.
    LPC_IOCON->P5_3 = I_RESERV  | 0 ;                   // Не исп.
    LPC_IOCON->P5_4 = D_RESERV  | 0 ;                   // USEL
    LPC_GPIO5->DIR =  0x00000010;
}

/*********************************************************************//**
 * @brief		Enable GPIO interrupt (just used for P0.0-P0.30, P2.0-P2.13)
 * @param[in]	portNum		Port number to read value, should be: 0 or 2
 * @param[in]	bitValue	Value that contains all bits on GPIO to enable,
 * 							in range from 0 to 0xFFFFFFFF.
 * @param[in]	edgeState	state of edge, should be:
 * 							- 0: Rising edge
 * 							- 1: Falling edge
 * @return		None
 **********************************************************************/
void GPIO_IntCmd(uint8_t portNum, uint32_t bitValue, uint8_t edgeState)
{
	if((portNum == 0)&&(edgeState == 0))
        LPC_GPIOINT->IO0IntEnR |= (0x1<<bitValue);
	else if ((portNum == 2)&&(edgeState == 0))
        LPC_GPIOINT->IO2IntEnR |= (0x1<<bitValue);
	else if ((portNum == 0)&&(edgeState == 1))
        LPC_GPIOINT->IO0IntEnF |= (0x1<<bitValue);
	else if ((portNum == 2)&&(edgeState == 1))
        LPC_GPIOINT->IO2IntEnF |= (0x1<<bitValue);
	else
		//Error
		while(1);
}

/*********************************************************************//**
 * @brief		Get GPIO Interrupt Status (just used for P0.0-P0.30, P2.0-P2.13)
 * @param[in]	portNum		Port number to read value, should be: 0 or 2
 * @param[in]	pinNum		Pin number, should be: 0..30(with port 0) and 0..13
 * 							(with port 2)
 * @param[in]	edgeState	state of edge, should be:
 * 							- 0: Rising edge
 * 							- 1: Falling edge
 * @return		Bool	could be:
 * 						- ENABLE: Interrupt has been generated due to a rising
 * 								edge on P0.0
 * 						- DISABLE: A rising edge has not been detected on P0.0
 **********************************************************************/
FunctionalState GPIO_GetIntStatus(uint8_t portNum, uint32_t pinNum, uint8_t edgeState)
{
	if((portNum == 0) && (edgeState == 0))//Rising Edge
		return (((LPC_GPIOINT->IO0IntStatR)>>pinNum)& 0x1);
	else if ((portNum == 2) && (edgeState == 0))
		return (((LPC_GPIOINT->IO2IntStatR)>>pinNum)& 0x1);
	else if ((portNum == 0) && (edgeState == 1))//Falling Edge
		return (((LPC_GPIOINT->IO0IntStatF)>>pinNum)& 0x1);
	else if ((portNum == 2) && (edgeState == 1))
		return (((LPC_GPIOINT->IO2IntStatF)>>pinNum)& 0x1);
	else
		//Error
		while(1);
}
/*********************************************************************//**
 * @brief		Clear GPIO interrupt (just used for P0.0-P0.30, P2.0-P2.13)
 * @param[in]	portNum		Port number to read value, should be: 0 or 2
 * @param[in]	bitValue	Value that contains all bits on GPIO to enable,
 * 							in range from 0 to 0xFFFFFFFF.
 * @return		None
 **********************************************************************/
void GPIO_ClearInt(uint8_t portNum, uint32_t bitValue)
{
	if(portNum == 0)
        LPC_GPIOINT->IO0IntClr |= (0x1<<bitValue);
	else if (portNum == 2)
        LPC_GPIOINT->IO2IntClr |= (0x1<<bitValue);
	else
		//Invalid portNum
		while(1);
}

void GPIO_IRQHandler (void)
{
  LPC_GPIOINT->IO0IntClr = 0xffffffff;

  LPC_GPIOINT->IO2IntClr |= 0xffffffff;
  // mUSEL_not();
}

