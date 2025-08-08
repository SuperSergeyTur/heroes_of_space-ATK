//#include "iocon.h"
//#include "user.h"
/*-----------------15.08.2012 11:22-----------------
 *   Dir: 0 - input
 *        1 - output
 * --------------------------------------------------*/
void Init_CPU_Ports( void )
{
 // byte i;
 // P0

    LPC_IOCON->P0_0   = D_RESERV | 0x1;                 // CAN1.RX
    LPC_IOCON->P0_1   = D_RESERV | 0x1;                 // CAN1.TX
    LPC_IOCON->P0_2   = D_RESERV | 0x1;                 // UART0.TX
    LPC_IOCON->P0_3   = D_RESERV | 0x1;                 // UART0.RX

    //LPC_IOCON->P0_4   = D_RESERV | 0;                 // Нет таких выводов
    //LPC_IOCON->P0_5   = D_RESERV | 0;                 // Нет таких выводов
    LPC_IOCON->P0_6   = D_RESERV | 0;                   // MUX3
    LPC_IOCON->P0_7   = W_RESERV | 0;                   // MUX2

    LPC_IOCON->P0_8   = W_RESERV | 0;                   // MUX1
    LPC_IOCON->P0_9   = W_RESERV | 0;                   // MUX0
    LPC_IOCON->P0_10  = D_RESERV | 0;
    LPC_IOCON->P0_11  = D_RESERV | 0;

   // LPC_IOCON->P0_12  = A_RESERV | A_ADMODE_AM   | 0x3;  // ADC6
   // LPC_IOCON->P0_13  = A_RESERV | A_ADMODE_AM   | 0x3;  // ADC7
   // LPC_IOCON->P0_14  = D_RESERV | 0;
    LPC_IOCON->P0_15  = D_RESERV | D_MODE_PULLUP |0;       // выход Q1

    LPC_IOCON->P0_16  = D_RESERV | D_MODE_PULLUP |0;       // выход Q2
    LPC_IOCON->P0_17  = D_RESERV | 0;      
    LPC_IOCON->P0_18  = D_RESERV | 0;      
   // LPC_IOCON->P0_19  = D_RESERV | 0;

   // LPC_IOCON->P0_20  = D_RESERV | 0;
   // LPC_IOCON->P0_21  = D_RESERV | 0;
    LPC_IOCON->P0_22  = D_RESERV | 0;
   // LPC_IOCON->P0_23  = A_RESERV | A_ADMODE_AM | 0x1;  // ADC0

   // LPC_IOCON->P0_24  = A_RESERV | A_ADMODE_AM | 0x1;  // ADC1
    LPC_IOCON->P0_25  = A_RESERV | A_ADMODE_AM | 0x1;  // ADC_in
    LPC_IOCON->P0_26  = A_RESERV | A_ADMODE_AM | 0x2;  // DAC
    //LPC_IOCON->P0_27  = I_RESERV | 0;                  //

    //LPC_IOCON->P0_28  = I_RESERV | 0;                  //
    LPC_IOCON->P0_29  = U_RESERV | 0;                  // CAP1
    LPC_IOCON->P0_30  = U_RESERV | 0;                
    LPC_IOCON->P0_31 =  U_RESERV | 0;                  //

    LPC_GPIO0->DIR = 0x040183c0;

    LPC_IOCON->P1_0  = D_RESERV | D_MODE_PULLUP | 0;       // USER
    LPC_IOCON->P1_1  = D_RESERV | D_MODE_PULLUP | 0;       // Predupr
//    LPC_IOCON->P1_2  = D_RESERV | 0;         //
//    LPC_IOCON->P1_3  = D_RESERV | 0;         //
    LPC_IOCON->P1_4  = D_RESERV | D_MODE_PULLUP | 0;       // Avar
//    LPC_IOCON->P1_5  = D_RESERV | 0;         //
//    LPC_IOCON->P1_6  = D_RESERV | 0;         //
//    LPC_IOCON->P1_7  = D_RESERV | 0;         //
    LPC_IOCON->P1_8  = D_RESERV | 0;         // 
    LPC_IOCON->P1_9  = D_RESERV | 0;         //
    LPC_IOCON->P1_10 = D_RESERV | 0;         //
    LPC_IOCON->P1_11 = D_RESERV | 0;         //
    LPC_IOCON->P1_12 = D_RESERV | 0;         //
    LPC_IOCON->P1_13 = D_RESERV | 0;         //
    LPC_IOCON->P1_14 = D_RESERV | 0;         //
    LPC_IOCON->P1_15 = D_RESERV | 0;         //
    LPC_IOCON->P1_16 = D_RESERV | 0;         //
    LPC_IOCON->P1_17 = D_RESERV | 0;         //
    LPC_IOCON->P1_18 = D_RESERV | 0;         //
    LPC_IOCON->P1_19 = D_RESERV | 0;         //
    LPC_IOCON->P1_20 = D_RESERV | 0;         //
    LPC_IOCON->P1_21 = D_RESERV | 0;         //
    LPC_IOCON->P1_22 = D_RESERV | 0;         //
    LPC_IOCON->P1_23 = D_RESERV | 0;         //
    LPC_IOCON->P1_24 = D_RESERV | 0;         //
    LPC_IOCON->P1_25 = D_RESERV | 0;         //
    LPC_IOCON->P1_26 = D_RESERV | 0;         //
    LPC_IOCON->P1_27 = D_RESERV | 0;         //
    LPC_IOCON->P1_28 = D_RESERV | 0;         //
    LPC_IOCON->P1_29 = D_RESERV | 0;         //
    LPC_IOCON->P1_30 = A_RESERV | 0; 	     // 
    LPC_IOCON->P1_31 = A_RESERV | 0; 	     // 

    LPC_GPIO1->DIR = 0x13;     //

    LPC_IOCON->P2_0   = D_RESERV | 0;       // 
    LPC_IOCON->P2_1   = D_RESERV | 0;       // 
    LPC_IOCON->P2_2   = D_RESERV | 0;       // 
    LPC_IOCON->P2_3   = D_RESERV | 0;       // 
    LPC_IOCON->P2_4   = D_RESERV | 0;       // 
    LPC_IOCON->P2_5   = D_RESERV | 0;       // 
    LPC_IOCON->P2_6   = D_RESERV | 0;       //CAP2
    LPC_IOCON->P2_7   = D_RESERV | 0;       //
    LPC_IOCON->P2_8   = D_RESERV | 0;       //
    LPC_IOCON->P2_9   = D_RESERV | 0;
/*    LPC_IOCON->P2_10  = D_RESERV | 0;
    LPC_IOCON->P2_11  = D_RESERV | 0;
    LPC_IOCON->P2_12  = D_RESERV | 0;
    LPC_IOCON->P2_13  = D_RESERV | 0;
    LPC_IOCON->P2_14  = D_RESERV | 0;
    LPC_IOCON->P2_15  = D_RESERV | 0;
    LPC_IOCON->P2_16  = D_RESERV | 0;
    LPC_IOCON->P2_17  = D_RESERV | 0;
    LPC_IOCON->P2_18  = D_RESERV | 0;
    LPC_IOCON->P2_19  = D_RESERV | 0;
    LPC_IOCON->P2_20  = D_RESERV | 0;
    LPC_IOCON->P2_21  = D_RESERV | 0;
    LPC_IOCON->P2_22  = D_RESERV | 0;
    LPC_IOCON->P2_23  = D_RESERV | 0;
    LPC_IOCON->P2_24  = D_RESERV | 0;
    LPC_IOCON->P2_25  = D_RESERV | 0;
    LPC_IOCON->P2_26  = D_RESERV | 0;
    LPC_IOCON->P2_27  = D_RESERV | 0;
    LPC_IOCON->P2_28  = D_RESERV | 0;
    LPC_IOCON->P2_29  = D_RESERV | 0;
    LPC_IOCON->P2_30  = D_RESERV | 0;
    LPC_IOCON->P2_31  = D_RESERV | 0;
*/
    LPC_GPIO2->DIR =   0;

/*
    LPC_IOCON->P3_0   = D_RESERV  | 0;
    LPC_IOCON->P3_1   = D_RESERV  | 0;
    LPC_IOCON->P3_2   = D_RESERV  | 0;
    LPC_IOCON->P3_3   = D_RESERV  | 0;
    LPC_IOCON->P3_4   = D_RESERV  | 0;
    LPC_IOCON->P3_5   = D_RESERV  | 0;
    LPC_IOCON->P3_6   = D_RESERV  | 0;
    LPC_IOCON->P3_7   = D_RESERV  | 0;
    LPC_IOCON->P3_8   = D_RESERV  | 0;
    LPC_IOCON->P3_9   = D_RESERV  | 0;
    LPC_IOCON->P3_10  = D_RESERV  | 0;
    LPC_IOCON->P3_11  = D_RESERV  | 0;
    LPC_IOCON->P3_12  = D_RESERV  | 0;
    LPC_IOCON->P3_13  = D_RESERV  | 0;
    LPC_IOCON->P3_14  = D_RESERV  | 0;
    LPC_IOCON->P3_15  = D_RESERV  | 0;
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
    LPC_IOCON->P3_31  = D_RESERV  | 0;

    LPC_GPIO3->DIR =  0 ;

    LPC_IOCON->P4_0   = D_RESERV  | 0;
    LPC_IOCON->P4_1   = D_RESERV  | 0;
    LPC_IOCON->P4_2   = D_RESERV  | 0;
    LPC_IOCON->P4_3   = D_RESERV  | 0;
    LPC_IOCON->P4_4   = D_RESERV  | 0;
    LPC_IOCON->P4_5   = D_RESERV  | 0;
    LPC_IOCON->P4_6   = D_RESERV  | 0;
    LPC_IOCON->P4_7   = D_RESERV  | 0;
    LPC_IOCON->P4_8   = D_RESERV  | 0;
    LPC_IOCON->P4_9   = D_RESERV  | 0;
    LPC_IOCON->P4_10  = D_RESERV  | 0;
    LPC_IOCON->P4_11  = D_RESERV  | 0;
    LPC_IOCON->P4_12  = D_RESERV  | 0;
    LPC_IOCON->P4_13  = D_RESERV  | 0;
    LPC_IOCON->P4_14  = D_RESERV  | 0;
    LPC_IOCON->P4_15  = D_RESERV  | 0;
    LPC_IOCON->P4_16  = D_RESERV  | 0;
    LPC_IOCON->P4_17  = D_RESERV  | 0;
    LPC_IOCON->P4_18  = D_RESERV  | 0;
    LPC_IOCON->P4_19  = D_RESERV  | 0;
    LPC_IOCON->P4_20  = D_RESERV  | D_MODE_PULLUP | 0x3; //SCK1
    LPC_IOCON->P4_21  = D_RESERV  | D_MODE_PULLUP | 0x3; //CS_SPI1
    LPC_IOCON->P4_22  = D_RESERV  | D_MODE_PULLUP | 0x3; //MISO1
    LPC_IOCON->P4_23  = D_RESERV  | D_MODE_PULLUP | 0x3; //MOSI1
    LPC_IOCON->P4_24  = D_RESERV  | 0 ;
    LPC_IOCON->P4_25  = D_RESERV  | 0 ;
    LPC_IOCON->P4_26  = D_RESERV  | 0 ;
    LPC_IOCON->P4_27  = D_RESERV  | 0 ;*/
    LPC_IOCON->P4_28  = D_RESERV  | 0 ; //кт6
    LPC_IOCON->P4_29  = D_RESERV  | 0 ; //кт7  
 //   LPC_IOCON->P4_30  = D_RESERV  | 0 ;
 //   LPC_IOCON->P4_31  = D_RESERV  | 0 ;

    LPC_GPIO4->DIR =  0x30000000;
/*
    LPC_IOCON->P5_0  = D_RESERV | D_MODE_PULLUP |D_HYS_EN | 0; //USEL
    LPC_IOCON->P5_1  = D_RESERV | 0;                    //
    LPC_IOCON->P5_2  = I_RESERV | 0;                    //
    LPC_IOCON->P5_3  = I_RESERV | 0;                    //
    LPC_IOCON->P5_4  = D_RESERV | 0;                    //

    LPC_GPIO5->DIR = 0x1;
*/
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

void GPIO_IRQHandler (void)
{
  LPC_GPIOINT->IO0IntClr = 0xffffffff;

  LPC_GPIOINT->IO2IntClr = 0xffffffff;
 // mUSEL_not();
}


