//#include "iocon.h"
//#include "user.h"
/*-----------------15.08.2012 11:22-----------------
 *
 * --------------------------------------------------*/

lword INTReg_GPIO_R[3];
lword INTReg_GPIO_F[3];

void Init_CPU_Ports( void )
{
  // P0
    LPC_IOCON->P0_0   = D_RESERV | 0x1;                   // CAN0.RX
    LPC_IOCON->P0_1   = D_RESERV | 0x1;                   // CAN0.TX
    LPC_IOCON->P0_2   = D_RESERV | 0x1;                 // UART0.TX
    LPC_IOCON->P0_3   = D_RESERV | 0x1;                 // UART0.RX

    LPC_IOCON->P0_4   = D_RESERV | D_HYS_EN |0;                 // Mode1
    LPC_IOCON->P0_5   = D_RESERV | D_HYS_EN |0;                 // Mode2
    LPC_IOCON->P0_6   = D_RESERV | D_HYS_EN |0;        // CS0
    LPC_IOCON->P0_7   = W_RESERV | W_HYS_EN |0;        // CS1

    LPC_IOCON->P0_8   = W_RESERV | W_HYS_EN |0;        // CS2
    LPC_IOCON->P0_9   = W_RESERV | W_HYS_EN |0;        // CS3
    LPC_IOCON->P0_10  = D_RESERV | D_HYS_EN |0;        // CS4
    LPC_IOCON->P0_11  = D_RESERV | D_HYS_EN |0;        // int4

//    LPC_IOCON->P0_12  = A_RESERV | A_ADMODE_AM | 0x3;  // ADC6
//    LPC_IOCON->P0_13  = A_RESERV | A_ADMODE_AM | 0x3;  // ADC7
    LPC_IOCON->P0_15  = D_RESERV | D_HYS_EN |0x0;      // SCK

    LPC_IOCON->P0_17  = D_RESERV | D_HYS_EN |0x0;      // MISO
    LPC_IOCON->P0_18  = D_RESERV | D_HYS_EN |0x0;      // MOSI
//    LPC_IOCON->P0_19  = D_RESERV | D_HYS_EN | 0;       // INT5

//    LPC_IOCON->P0_20  = D_RESERV | D_HYS_EN | 0;       // INT6
//    LPC_IOCON->P0_21  = D_RESERV | D_HYS_EN | 0;       // INT7
//    LPC_IOCON->P0_22  = D_RESERV | D_HYS_EN | 0;       // CS6
    LPC_IOCON->P0_23  = A_RESERV | A_ADMODE_AM | 0x1;  // ADC0

    LPC_IOCON->P0_24  = A_RESERV | A_ADMODE_AM | 0x1;  // ADC1
    LPC_IOCON->P0_25  = A_RESERV | A_ADMODE_AM | 0x1;  // ADC2
    LPC_IOCON->P0_26  = A_RESERV | A_ADMODE_AM | 0x1;  // ADC3
//    LPC_IOCON->P0_27  = I_RESERV | 0;                  // ADC.MUX0

//    LPC_IOCON->P0_28  = I_RESERV | 0;                  // ADC.MUX1
//    LPC_IOCON->P0_29  = U_RESERV | 0;                  // ADC.MUX2
//    LPC_IOCON->P0_30  = U_RESERV | 0;                  // ADC.P04

    LPC_GPIO0->DIR = 0x0007c0;

// P1
//  LPC_IOCON->P1_0  = D_RESERV | 0; // In
    LPC_IOCON->P1_1  = D_RESERV | D_HYS_EN | 0; // In KF
//  LPC_IOCON->P1_2  = D_RESERV | 0; // In
//  LPC_IOCON->P1_3  = D_RESERV | 0; // In

    LPC_IOCON->P1_4  = D_RESERV | 0; // Out Green
//  LPC_IOCON->P1_5  = D_RESERV | 0; // In
//  LPC_IOCON->P1_6  = D_RESERV | 0; // In
//  LPC_IOCON->P1_7  = D_RESERV | 0; // In

    LPC_IOCON->P1_8  = D_RESERV | 0; // Out Yellow
    LPC_IOCON->P1_9  = D_RESERV | 0; // Out Red
    LPC_IOCON->P1_10 = D_RESERV | D_HYS_EN| 0; // In SYN
//  LPC_IOCON->P1_11 = D_RESERV | 0; // In

//  LPC_IOCON->P1_12 = D_RESERV | 0; // In
//  LPC_IOCON->P1_13 = D_RESERV | 0; // In
    LPC_IOCON->P1_14 = D_RESERV | 0; // Out DO4
    LPC_IOCON->P1_15 = D_RESERV | 0; // Out DO3

    LPC_IOCON->P1_16 = W_RESERV | W_HYS_EN | 0; // Out DO2
    LPC_IOCON->P1_17 = W_RESERV | W_HYS_EN | 0; // Out DO1
//  LPC_IOCON->P1_18 = D_RESERV | 0; // In
//  LPC_IOCON->P1_19 = D_RESERV | 0; // In

    LPC_IOCON->P1_20 = D_RESERV | 0; // Out QV
//  LPC_IOCON->P1_21 = D_RESERV | 0; // In
    LPC_IOCON->P1_22 = A_RESERV | 0; // Out PPG2
//  LPC_IOCON->P1_23 = D_RESERV | 0; // In

//  LPC_IOCON->P1_24 = D_RESERV | 0; // In
    LPC_IOCON->P1_25 = D_RESERV | 0; // Out F1 (SUM)
//  LPC_IOCON->P1_26 = D_RESERV | 0; // In
//  LPC_IOCON->P1_27 = D_RESERV | 0; // In

    LPC_IOCON->P1_28 = D_RESERV | 0; // Out F2 (SUM)
    LPC_IOCON->P1_29 = D_RESERV | 0; // Out D1
    LPC_IOCON->P1_30 = A_RESERV | A_ADMODE_AM | 0x03; // In AN4 (1P24)
    LPC_IOCON->P1_31 = A_RESERV | A_ADMODE_AM | 0x03; // In AN5 (P5)

    LPC_GPIO1->SET  = 0x0013C000; // Установка сигналов QV, DO1, DO2, DO3, DO4 в 1
    LPC_GPIO1->DIR |= 0x3253C310;

// Набваойкая PINSTOP
//	LPC_IOCON->P5_4  = D_RESERV | D_HYS_EN | 0; 	  // PIN-STOP
//	LPC_GPIO5->DIR &= ~PINSTOP_Msk;     //

//
    LPC_IOCON->P2_0   = D_RESERV | D_OD_EN | 0;       // v1
    LPC_IOCON->P2_1   = D_RESERV | D_OD_EN | 0;       // v2
    LPC_IOCON->P2_2   = D_RESERV | D_OD_EN | 0;       // v3
    LPC_IOCON->P2_3   = D_RESERV | D_OD_EN | 0;       // v4
    LPC_IOCON->P2_4   = D_RESERV | D_OD_EN | 0;       // v5
    LPC_IOCON->P2_5   = D_RESERV | D_OD_EN | 0;       // v6
    LPC_IOCON->P2_6   = D_RESERV | 0x4;               // RS485.RTS (UART2.OE)
    LPC_IOCON->P2_8   = D_RESERV | 0x2;               // RS485.TX
    LPC_IOCON->P2_9   = D_RESERV | 0x2;               // RS485.RX
    LPC_IOCON->P2_10  = D_RESERV | D_HYS_EN | 0x1;    // INT0
    LPC_IOCON->P2_11  = D_RESERV | D_HYS_EN | 0x1;    // INT1
    LPC_IOCON->P2_12  = D_RESERV | D_HYS_EN | 0x1;    // INT2
    LPC_IOCON->P2_13  = D_RESERV | D_HYS_EN | 0x1;    // INT3
/*  LPC_IOCON->P2_15  = D_RESERV | D_HYS_EN | 0;      // INT4
    LPC_IOCON->P2_16  = D_RESERV | D_HYS_EN | 0;      // Pi0.0
    LPC_IOCON->P2_17  = D_RESERV | D_HYS_EN | 0;      // Pi0.1
    LPC_IOCON->P2_18  = D_RESERV | D_HYS_EN | 0;      // Pi0.2
    LPC_IOCON->P2_19  = D_RESERV | D_HYS_EN | 0;      // Pi0.3
    LPC_IOCON->P2_20  = D_RESERV | D_HYS_EN | 0;      // Pi0.4
    LPC_IOCON->P2_21  = D_RESERV | D_HYS_EN | 0;      // Pi0.5
    LPC_IOCON->P2_22  = D_RESERV | D_HYS_EN | 0;      // Pi0.6
    LPC_IOCON->P2_23  = D_RESERV | D_HYS_EN | 0;      // Pi0.7
    LPC_IOCON->P2_24  = D_RESERV | 0;    // Po0.0
    LPC_IOCON->P2_25  = D_RESERV | 0;    // Po0.1
    LPC_IOCON->P2_26  = D_RESERV | 0;    // Po0.2
    LPC_IOCON->P2_27  = D_RESERV | 0;    // Po0.3
    LPC_IOCON->P2_28  = D_RESERV | 0;    // Po0.4
    LPC_IOCON->P2_29  = D_RESERV | 0;    // Po0.5
*/
    LPC_GPIO2->DIR =   0x0000003f ;

/*
    LPC_IOCON->P3_16  = D_RESERV  | 0;
    LPC_IOCON->P3_17  = D_RESERV  | 0;
    LPC_IOCON->P3_18  = D_RESERV  | 0;
    LPC_IOCON->P3_19  = D_RESERV  | 0;
    LPC_IOCON->P3_20  = D_RESERV  | 0;
    LPC_IOCON->P3_21  = D_RESERV  | 0;
    LPC_IOCON->P3_22  = D_RESERV  | 0;
    LPC_IOCON->P3_23  = D_RESERV  | 0;
    LPC_IOCON->P3_24  = D_RESERV  | 0;
    LPC_IOCON->P3_25  = D_RESERV  | 0;
    LPC_IOCON->P3_26  = D_RESERV  | 0;
    LPC_IOCON->P3_27  = D_RESERV  | 0;
    LPC_IOCON->P3_28  = D_RESERV  | 0;
    LPC_IOCON->P3_29  = D_RESERV  | 0;
    LPC_IOCON->P3_30  = D_RESERV  | 0;
    LPC_IOCON->P3_31  = D_RESERV  | D_MODE_PULLUP| 0;//CS-ADC
    //выходы
    LPC_GPIO3->DIR =  0xffff0000 ;
    LPC_GPIO3->SET =  0x7fff0000 ;

    LPC_IOCON->P4_20  = D_RESERV  | D_MODE_PULLUP | 0 | 0x3; //SCK1
    LPC_IOCON->P4_21  = D_RESERV  | D_MODE_PULLUP | 0 | 0x3; //CS_SPI1
    LPC_IOCON->P4_22  = D_RESERV  | D_MODE_PULLUP | 0 | 0x3; //MISO1
    LPC_IOCON->P4_23  = D_RESERV  | D_MODE_PULLUP | 0 | 0x3; //MOSI1
    LPC_IOCON->P4_28  = D_RESERV  | D_MODE_PULLUP | 0 ;
    //выходы
    LPC_GPIO4->DIR =  0x10000000 ;

    LPC_IOCON->P5_0 = D_RESERV  | D_MODE_PULLUP | 0 ;
    LPC_IOCON->P5_1 = D_RESERV  | D_MODE_PULLUP | 0 ;
    LPC_IOCON->P5_2 = I_RESERV  | 0 ;
    LPC_IOCON->P5_3 = I_RESERV  | 0 ;
    LPC_IOCON->P5_4 = D_RESERV  | 0 ; // USEL
    LPC_GPIO5->DIR =  0x00000010;

    INTReg_GPIO_R[0] = 0;
    INTReg_GPIO_R[2] = 0;
    INTReg_GPIO_F[0] = 0;
    INTReg_GPIO_F[2] = 0;
*/
    LPC_IOCON->P5_4 = D_RESERV  | 0 ; // USEL
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
		return (FunctionalState)(((LPC_GPIOINT->IO0IntStatR)>>pinNum)& 0x1);
	else if ((portNum == 2) && (edgeState == 0))
		return (FunctionalState)(((LPC_GPIOINT->IO2IntStatR)>>pinNum)& 0x1);
	else if ((portNum == 0) && (edgeState == 1))//Falling Edge
		return (FunctionalState)(((LPC_GPIOINT->IO0IntStatF)>>pinNum)& 0x1);
	else if ((portNum == 2) && (edgeState == 1))
		return (FunctionalState)(((LPC_GPIOINT->IO2IntStatF)>>pinNum)& 0x1);
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

extern "C" {
void GPIO_IRQHandler (void)
{

#ifdef _Synch_3f
  if (( LPC_GPIOINT->IO0IntStatR & ( 1UL<<_SyncTCA_Bit )) != 0 ) _SyncTCA_time = timer1 ;
  if (( LPC_GPIOINT->IO2IntStatR & ( 1UL<<_SyncTCB_Bit )) != 0 ) _SyncTCB_time = timer1 ;
  if (( LPC_GPIOINT->IO0IntStatR & ( 1UL<<_SyncTCC_Bit )) != 0 ) _SyncTCC_time = timer1 ;
//  itime1 = (u)((w)(timer1-itime_old1));  //  измеряем растояние между ИУ. - КВВ
//  itime_old1 = timer1;

//  LPC_GPIOINT->IO0IntClr = 0xffffffff;
//  LPC_GPIOINT->IO2IntClr = 0xffffffff;
#endif


  INTReg_GPIO_R[0]|= LPC_GPIOINT->IO0IntStatR;
  INTReg_GPIO_R[2]|= LPC_GPIOINT->IO2IntStatR;
  INTReg_GPIO_F[0]|= LPC_GPIOINT->IO0IntStatF;
  INTReg_GPIO_F[2]|= LPC_GPIOINT->IO2IntStatF;



  LPC_GPIOINT->IO0IntClr = LPC_GPIOINT->IO0IntStatR|LPC_GPIOINT->IO0IntStatF;

  LPC_GPIOINT->IO2IntClr = LPC_GPIOINT->IO2IntStatR|LPC_GPIOINT->IO2IntStatF;

  // Старая идея .
  // DAN 24.05.2016 - Это прерывание выполняется по переднему и заднему
  // фронтам ДЗВ (так проинициализировано) . В зависимости от того ,
  // какой уровень является разрешающим , при вызове опроса ДЗВ во
  // время реверса , возвращаем либо "1" , либо "0" .

  /*if (((LPC_GPIOINT->IO0IntStatR)>>_DZVA_Bit)& 0x1) // Rising
  {
    if ( _DZVA_Ok_level == 1 ) dzva1 = 1;  // Разрешение реверса по верхнему уровню сигнала .
    else                       dzva1 = 0;  // Запрет реверса .
  }

  if (((LPC_GPIOINT->IO0IntStatF)>>_DZVA_Bit)& 0x1) // Falling
  {
    if ( _DZVA_Ok_level == 1 ) dzva1 = 0;  // Запрет реверса .
    else                       dzva1 = 1;  // Разрешение реверса по нижнему уровню сигнала .
  }

  if (((LPC_GPIOINT->IO0IntStatR)>>_DZVK_Bit)& 0x1) // Rising
  {
    if ( _DZVK_Ok_level == 1 ) dzvk1 = 1;  // Разрешение реверса по верхнему уровню сигнала .
    else                       dzvk1 = 0;  // Запрет реверса .
  }

  if (((LPC_GPIOINT->IO0IntStatF)>>_DZVK_Bit)& 0x1) // Falling
  {
    if ( _DZVK_Ok_level == 1 ) dzvk1 = 0;  // Запрет реверса .
    else                       dzvk1 = 1;  // Разрешение реверса по нижнему уровню сигнала .
  }

  if (((LPC_GPIOINT->IO2IntStatR)>>_DZVA2_Bit)& 0x1) // Rising
  {
    if ( _DZVA2_Ok_level == 1 ) dzva2 = 1;  // Разрешение реверса по верхнему уровню сигнала .
    else                        dzva2 = 0;  // Запрет реверса .
  }

  if (((LPC_GPIOINT->IO2IntStatF)>>_DZVA2_Bit)& 0x1) // Falling
  {
    if ( _DZVA2_Ok_level == 1 ) dzva2 = 0;  // Запрет реверса .
    else                        dzva2 = 1;  // Разрешение реверса по нижнему уровню сигнала .
  }

  if (((LPC_GPIOINT->IO2IntStatR)>>_DZVK2_Bit)& 0x1) // Rising
  {
    if ( _DZVK2_Ok_level == 1 ) dzvk2 = 1;  // Разрешение реверса по верхнему уровню сигнала .
    else                        dzvk2 = 0;  // Запрет реверса .
  }

  if (((LPC_GPIOINT->IO2IntStatF)>>_DZVK2_Bit)& 0x1) // Falling
  {
    if ( _DZVK2_Ok_level == 1 ) dzvk2 = 0;  // Запрет реверса .
    else                        dzvk2 = 1;  // Разрешение реверса по нижнему уровню сигнала .
  }*/

  // Новая идея .
  // DAN 25.05.2016 - Инициализируем прерывание ДЗВ по переднему фронту , если
  // разрешающим уровнем является верхний , и по заднему фронту , если разрешающим
  // уровнем является нижний .
  // Это значит , что в прерывание будем заходить по заданному фронту и , т.о. отслеживать
  // либо нижний , либо верхний уровень сигналов ДЗВ , что нужно для алгоритма работы ДЗВ .
  //---
  // Кроме того , сбрасываем не всё скопом , а каждый INT по одному .
 /* if ( _DZVA_Ok_level == 1 )
  {
    if (((LPC_GPIOINT->IO0IntStatR)>>_DZVA_Bit)& 0x1) dzva1 = 1 ; // Rising
  }
  else
  {
	if (((LPC_GPIOINT->IO0IntStatF)>>_DZVA_Bit)& 0x1) dzva1 = 1 ; // Falling
  }
  LPC_GPIOINT->IO0IntClr = 0x1<<_DZVA_Bit;

  if ( _DZVK_Ok_level == 1 )
  {
    if (((LPC_GPIOINT->IO0IntStatR)>>_DZVK_Bit)& 0x1) dzvk1 = 1 ; // Rising
  }
  else
  {
	if (((LPC_GPIOINT->IO0IntStatF)>>_DZVK_Bit)& 0x1) dzvk1 = 1 ; // Falling
  }
  LPC_GPIOINT->IO0IntClr = 0x1<<_DZVK_Bit;

  if ( _DZVA2_Ok_level == 1 )
  {
    if (((LPC_GPIOINT->IO2IntStatR)>>_DZVA2_Bit)& 0x1) dzva2 = 1 ; // Rising
  }
  else
  {
	if (((LPC_GPIOINT->IO2IntStatF)>>_DZVA2_Bit)& 0x1) dzva2 = 1 ; // Falling
  }
  LPC_GPIOINT->IO2IntClr = 0x1<<_DZVA2_Bit;

  if ( _DZVK2_Ok_level == 1 )
  {
    if (((LPC_GPIOINT->IO2IntStatR)>>_DZVK2_Bit)& 0x1) dzvk2 = 1 ; // Rising
  }
  else
  {
	if (((LPC_GPIOINT->IO2IntStatF)>>_DZVK2_Bit)& 0x1) dzvk2 = 1 ; // Falling
  }
  LPC_GPIOINT->IO2IntClr = 0x1<<_DZVK2_Bit;

  // mUSEL_not();
  */
}
}//extern "C"
