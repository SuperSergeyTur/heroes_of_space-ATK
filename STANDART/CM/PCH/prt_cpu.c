//#include "iocon.h"
//#include "user.h"
//#include "common_include.h"
//#include "prt_cpu.h"
/*-----------------15.08.2012 11:22-----------------
 *
 * --------------------------------------------------*/

lword INTReg_GPIO_R[3];
lword INTReg_GPIO_F[3];

void Init_CPU_Ports( void )
{
 // byte i;
 // P0
    LPC_IOCON->P0_0   = D_RESERV | 0x1;                 // CAN0.RX
    LPC_IOCON->P0_1   = D_RESERV | 0x1;                 // CAN0.TX
    LPC_IOCON->P0_2   = D_RESERV | 0x1;                 // UART0.TX
    LPC_IOCON->P0_3   = D_RESERV | 0x1;                 // UART0.RX
#ifndef _Synchr 
    LPC_IOCON->P0_4   = D_RESERV | 0x2;                // CAN1.RX
#else   
    LPC_IOCON->P0_4   = D_RESERV | 0x3;                // вход синхронизации
#endif    
    LPC_IOCON->P0_5   = D_RESERV | 0x2;                // CAN1.TX
    LPC_IOCON->P0_6   = D_RESERV | D_HYS_EN |0;        // CS0
    LPC_IOCON->P0_7   = W_RESERV | W_HYS_EN |0;        // CS1
    
    LPC_IOCON->P0_8   = W_RESERV | W_HYS_EN |0;        // CS2
    LPC_IOCON->P0_9   = W_RESERV | W_HYS_EN |0;        // CS3
    LPC_IOCON->P0_10  = D_RESERV | D_HYS_EN |0;        // CS4
    LPC_IOCON->P0_11  = D_RESERV | D_MODE_PULLUP |0;   // SW4 - тумблер 4
    
    LPC_IOCON->P0_12  = A_RESERV | 0;  
    LPC_IOCON->P0_13  = A_RESERV | 0;  
  //  LPC_IOCON->P0_15  = D_RESERV | D_HYS_EN |0x0;      // SCK
  
  //  LPC_IOCON->P0_17  = D_RESERV | D_HYS_EN |0x0;      // MISO
  //  LPC_IOCON->P0_18  = D_RESERV | D_HYS_EN |0x0;      // MOSI
    LPC_IOCON->P0_19  = D_RESERV |  0;       
    
    LPC_IOCON->P0_20  = D_RESERV | D_MODE_PULLUP | 0;     //SW1 - Останов 
    LPC_IOCON->P0_21  = D_RESERV | D_MODE_PULLUP | 0;     //SW2  
    LPC_IOCON->P0_22  = D_RESERV |  0;       
    LPC_IOCON->P0_23  = A_RESERV | A_ADMODE_AM | 0x1;  // ADC0
    
    LPC_IOCON->P0_24  = A_RESERV | A_ADMODE_AM | 0x1;  // ADC1
    LPC_IOCON->P0_25  = A_RESERV | A_ADMODE_AM | 0x1;  // ADC2
    LPC_IOCON->P0_26  = A_RESERV | 0x2;                // DA0
    LPC_IOCON->P0_27  = I_RESERV | 0;                   
    
    LPC_IOCON->P0_28  = I_RESERV | 0;                   
    LPC_IOCON->P0_29  = U_RESERV | 0;                  
    LPC_IOCON->P0_30  = U_RESERV | 0;                  

    LPC_GPIO0->DIR = 0x0007c0;

// Настройка USEL
    LPC_IOCON->P1_19 = D_RESERV | 0;       // MC_0A
    
    LPC_IOCON->P1_20 = D_RESERV | 0x3;     // FX0
    LPC_IOCON->P1_21 = D_RESERV |D_MODE_PULLUP | 0; // MC_ABORT
    LPC_IOCON->P1_22 = D_RESERV | 0;       // MC_0B
    LPC_IOCON->P1_23 = D_RESERV | 0x3;     // FX1
    
    LPC_IOCON->P1_24 = D_RESERV | 0x3;     // FZ
    LPC_IOCON->P1_25 = D_RESERV | 0;       // MC_1A
    LPC_IOCON->P1_26 = D_RESERV | 0;       // MC_1B
    LPC_IOCON->P1_27 = D_RESERV | 0;       // EBI_RST
    
    LPC_IOCON->P1_28 = D_RESERV | 0;       // MC_2A
    LPC_IOCON->P1_29 = D_RESERV | 0;       // MC_2B
    LPC_IOCON->P1_30 = A_RESERV | A_ADMODE_AM | 0x3; 	// ADC4
#ifndef _Pi1_     
    LPC_IOCON->P1_31 = A_RESERV | A_ADMODE_AM | 0x3; 	// ADC5
#else
    LPC_IOCON->P1_31 = A_RESERV | 0; 	// Pi1.0
#endif   
    LPC_GPIO1->DIR |= 0x3e480000;     //

// Настройка Input Port 0
    LPC_IOCON->P2_0   = D_RESERV | 0;       
    LPC_IOCON->P2_1   = D_RESERV | 0;       
    LPC_IOCON->P2_2   = D_RESERV | 0;       //OUT1
    LPC_IOCON->P2_3   = D_RESERV | 0;       
    
    LPC_IOCON->P2_4   = D_RESERV | 0;       // DA1 (PWM1.5)
    LPC_IOCON->P2_5   = D_RESERV | 0; 					
    LPC_IOCON->P2_6   = D_RESERV | 0; 					
    LPC_IOCON->P2_7   = D_RESERV | 0;       //USel			
    
    LPC_IOCON->P2_8   = D_RESERV | D_HYS_EN | 0;     // Int Драйвер C				
    LPC_IOCON->P2_9   = D_RESERV | D_HYS_EN | 0;     					
    LPC_IOCON->P2_10  = D_RESERV | D_HYS_EN | 0;     // Int Драйвер А 
    LPC_IOCON->P2_11  = D_RESERV | D_HYS_EN | 0;     // Int Драйвер B 
    
    LPC_IOCON->P2_12  = D_RESERV | D_HYS_EN | 0x1;  // INT2- Profibus
    LPC_IOCON->P2_13  = D_RESERV | D_HYS_EN | 0;    // Int Драйвер ДТ
    LPC_IOCON->P2_14  = D_RESERV | D_HYS_EN | 0;    
    LPC_IOCON->P2_15  = D_RESERV | D_HYS_EN | 0;      
    
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
    LPC_IOCON->P2_30  = D_RESERV | 0;    // Po0.6
    LPC_IOCON->P2_31  = D_RESERV | 0;    // Po0.7

    LPC_GPIO2->DIR =   0xFF000094 ;
    LPC_GPIO1->SET = _PIN_NOT_PULSES|_PIN_PULSES;
    LPC_GPIO2->CLR = (1ul<<2);
    LPC_GPIO2->SET = (3ul<<30);


    LPC_IOCON->P3_16  = D_RESERV  | 0;     //PWM_DT
    LPC_IOCON->P3_17  = D_RESERV  | 0;     //PWM_DT1 
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
    //выходы
    LPC_GPIO3->DIR =  0x00030000 ;
    LPC_GPIO3->SET =  0x00030000 ;

    LPC_IOCON->P4_20  = D_RESERV  | D_MODE_PULLUP | 0 | 0x3; //SCK1
    LPC_IOCON->P4_21  = D_RESERV  | D_MODE_PULLUP | 0 | 0x3; //CS_SPI1
    LPC_IOCON->P4_22  = D_RESERV  | D_MODE_PULLUP | 0 | 0x3; //MISO1
    LPC_IOCON->P4_23  = D_RESERV  | D_MODE_PULLUP | 0 | 0x3; //MOSI1
    //выходы
    LPC_GPIO4->DIR =  0x10000000 ;

    LPC_IOCON->P5_0 = D_RESERV  | D_MODE_PULLUP | 0 ;
    LPC_IOCON->P5_1 = D_RESERV  | D_MODE_PULLUP | 0 ;
    LPC_IOCON->P5_2 = I_RESERV  | 0 ;                   //SW3
    LPC_IOCON->P5_3 = I_RESERV  | 0 ;
    LPC_IOCON->P5_4 = D_RESERV  | 0 ; 
    LPC_GPIO5->DIR =  0x00000000;
    
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
void GPIO_IntCmd(uint8_t portNum, uint32_t bitValue, _EGE_STATE edgeState)
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
FunctionalState GPIO_GetIntStatus(uint8_t portNum, uint32_t pinNum, _EGE_STATE edgeState)
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



