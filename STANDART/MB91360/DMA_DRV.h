#ifndef _dma_h
#define _dma_h

//—труктура, определ€юща€€ настройку канала DMA дл€ синхронизации
struct  DMA_Syn
{
   word  dest;   //приемника
   struct     //источник передачи
   {
     word src    :5;                    // канал, по которму будет передаватьс€ запрос
     word level  :2;                    // уровень срабатывани€
   } req;

};
void DMA_start(struct DMA_Syn* in);
void ExtInt_DMA_ini(struct DMA_Syn in );

word Synch_Start_DMA ( void )  ;

        /*   ѕрив€зка синхронизации к DMA.  */
#define   _synch_dma_con     0
#define   _synch_dma_time    DMA_Synh[0].dest
#define   _synch1_dma_con    1
#define   _synch1_dma_time   DMA_Synh[1].dest
#define   _synch2_dma_con    2
#define   _synch2_dma_time   DMA_Synh[2].dest
#define   _synch3_dma_con    3
#define   _synch3_dma_time   DMA_Synh[3].dest

//»сточник запроса дл€ конкретного канала по умолчанию, если не используетс€ - задаетс€ 0
#ifndef _DMA0_ExtINT
#define _DMA0_ExtINT   _DMA_ExtINT0
#endif

#ifndef _DMA1_ExtINT
#define _DMA1_ExtINT   0
#endif

#ifndef _DMA2_ExtINT
#define _DMA2_ExtINT   _DMA_ExtINT2
#endif

#ifndef _DMA3_ExtINT
#define _DMA3_ExtINT   _DMA_ExtINT3
#endif

#ifndef _DMA4_ExtINT
#define _DMA4_ExtINT   0
#endif

//ћакросы задани€ источника запроса DMA
//External DMA - pin H level or rasing edge
#define _DMAext_h    0x0e  //01110
//External DMA - pin L level or falling edge
#define _DMAext_l    0x0f  //01111
//UART 0 RX Interrupt
#define _DMA_UART0RX 0x10  //10000
//UART 0 TX Interrupt
#define _DMA_UART0TX 0x11  //10001
//UART 1 RX Interrupt
#define _DMA_UART1RX 0x12  //10010
//UART 1 TX Interrupt
#define _DMA_UART1TX 0x13  //10011
//External Interrupt 0
#define _DMA_ExtINT0 0x14  //10100
//External Interrupt 1
#define _DMA_ExtINT1 0x15  //10101
//Reload Timer 0 Interrupt
#define _DMA_RelTmr0 0x16  //10110
//Reload Timer 1 Interrupt
#define _DMA_RelTmr1 0x17  //10111
//External Interrupt 2
#define _DMA_ExtINT2 0x18  //11000
//External Interrupt 3
#define _DMA_ExtINT3 0x19  //11001
//UART 2 RX Interrupt
#define _DMA_UART2RX 0x1a  //11010
//UART 2 TX Interrupt
#define _DMA_UART2TX 0x1b  //11011
//SIO 0 Interrupt
#define _DMA_SIO0    0x1c  //11100
//I2C Interrupt
#define _DMA_I2C     0x1d  //11101
//A/D Converter Interrupt
#define _DMA_ADC     0x1e  //11110
//SIO 1 Interrupt
#define _DMA_SIO1    0x1f  //11111


#define   Int_Low       0
#define   Int_High      1
#define   Int_Rising    2
#define   Int_Falling   3

#ifdef _MAIN_INCLUDE

struct  DMA_Syn    DMA_Synh[5];

#else

extern struct  DMA_Syn   DMA_Synh[]  ;

#endif
#endif
