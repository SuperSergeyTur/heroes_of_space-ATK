#include "emc.h"
//загрузка данных из флешки
static __INLINE void Flash_Recall( void )
{
   byte *addr;
   byte data;

     addr = (byte *)(0x90009C70);// 0x00004E38
     data = (byte)*addr;
     addr = (byte *)(0x9001638E);// 0x0000B1C7
     data = (byte)*addr;
     addr = (byte *)(0x900107C0);// 0x000083E0
     data = (byte)*addr;
     addr = (byte *)(0x9000F83E);// 0x00007C1F
     data = (byte)*addr;
     addr = (byte *)(0x9000E07E);// 0x0000703F
     data = (byte)*addr;
     addr = (byte *)(0x900098C6);// 0x00004C63
     data = (byte)*addr;
}
//запись данных во флешку
static __INLINE byte Flash_Store( word n )
{
   byte *addr;
   byte data;
   byte bh = 4;
   if (n == 0)
   {
      Store_Label = 0;
      bh = 0;
   }
   else
   {
     switch (Store_Label)
     {
     default:
     case 0:
       addr = (byte *)(0x90009C70); // 0x00004E38;
       data = (byte)*addr;
       addr = (byte *)(0x9001638E); // 0x0000B1C7
       data = (byte)*addr;
       addr = (byte *)(0x900107C0); // 0x000083E0
       data = (byte)*addr;
       addr = (byte *)(0x9000F83E); // 0x00007C1F
       data = (byte)*addr;
       addr = (byte *)(0x9000E07E); // 0x0000703F
       data = (byte)*addr;
       addr = (byte *)(0x90011F80); // 0x00008FC0
       data = (byte)*addr;
       time_Store = timer1;
       ++Store_Label;
     case 1:
       if ((u)((w)(timer1 - time_Store))> _MkSec(8000))
       {
         Store_Label = 0;
         bh = 0;
       }
       break;
     }
   }
   return bh;
}

/*-----------------17.08.2012 13:31-----------------
 * Инициализация EMC
 * --------------------------------------------------*/
void EMC_Init( void )
{
//lword TimerFlash = 0;

    LPC_SC->PCONP |= CLKPWR_PCONP_PCEMC;
    LPC_SC->EMCDLYCTL   = 0x00001010;
    LPC_EMC->Control 	= 0x00000001;
    LPC_EMC->Config  	= 0x00000000;

//--------------   Конфигурирование портов   ------------------------
	LPC_IOCON->P3_0  = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.D0
	LPC_IOCON->P3_1  = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.D1
	LPC_IOCON->P3_2  = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.D2
	LPC_IOCON->P3_3  = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.D3
	LPC_IOCON->P3_4  = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.D4
	LPC_IOCON->P3_5  = D_RESERV | D_MODE_PULLUP | 0X1; 	// EMC.D5
	LPC_IOCON->P3_6  = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.D6
	LPC_IOCON->P3_7  = D_RESERV | D_MODE_PULLUP | 0X1;  // EMC.D7
	LPC_IOCON->P3_8  = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.D8
	LPC_IOCON->P3_9  = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.D9
	LPC_IOCON->P3_10 = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.D10
	LPC_IOCON->P3_11 = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.D11
	LPC_IOCON->P3_12 = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.D12
	LPC_IOCON->P3_13 = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.D13
	LPC_IOCON->P3_14 = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.D14
	LPC_IOCON->P3_15 = D_RESERV | D_MODE_PULLUP | 0X1; 	// EMC.D15

	LPC_IOCON->P4_0  = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.A0
	LPC_IOCON->P4_1  = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.A1
	LPC_IOCON->P4_2  = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.A2
	LPC_IOCON->P4_3  = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.A3
	LPC_IOCON->P4_4  = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.A4
	LPC_IOCON->P4_5  = D_RESERV | D_MODE_PULLUP | 0X1; 	// EMC.A5
	LPC_IOCON->P4_6  = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.A6
	LPC_IOCON->P4_7  = D_RESERV | D_MODE_PULLUP | 0X1;  // EMC.A7
	LPC_IOCON->P4_8  = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.A8
	LPC_IOCON->P4_9  = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.A9
	LPC_IOCON->P4_10 = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.A10
	LPC_IOCON->P4_11 = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.A11
	LPC_IOCON->P4_12 = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.A12
	LPC_IOCON->P4_13 = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.A13
	LPC_IOCON->P4_14 = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.A14
	LPC_IOCON->P4_15 = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.A15
	LPC_IOCON->P4_16 = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.A16
	LPC_IOCON->P4_17 = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.A17
	LPC_IOCON->P4_18 = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.A18
	LPC_IOCON->P4_19 = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.A19

	LPC_IOCON->P4_24 = D_RESERV | D_MODE_PULLUP | 0x1;  // EMC.OE
	LPC_IOCON->P4_25 = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.WR
	LPC_IOCON->P4_26 = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.BLS0
	LPC_IOCON->P4_27 = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.BLS1

	LPC_IOCON->P4_30 = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.CS0
	LPC_IOCON->P4_31 = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.CS1
	LPC_IOCON->P2_14 = D_RESERV | D_MODE_PULLUP | 0x1; 	// EMC.CS2

	LPC_IOCON->P0_16 = D_RESERV | D_MODE_PULLUP | 0; 	// EMC.RDY
	LPC_IOCON->P1_29 = D_RESERV | 0; 					// EMC.RESET
//------------------------------------------------------------------

//---------------   Конфигурация адресного пространства ОЗУ   -------------------------
    LPC_EMC->StaticConfig0   = 0x1;
    LPC_EMC->StaticWaitWen0  = 0;
    LPC_EMC->StaticWaitOen0  = 0; // должен быть 0 - иначе WaitRd надо увеличивать
    LPC_EMC->StaticWaitRd0   = 0x1; // 1 - потому что с 0 не работает
    LPC_EMC->StaticWaitPage0 = 0;
    LPC_EMC->StaticWaitWr0   = 0;
    LPC_EMC->StaticWaitTurn0 = 0;
//-------------------------------------------------------------------------------------

//---------------   Конфигурация адресного пространства флэш   ------------------------
    LPC_EMC->StaticConfig1   = 0x00080081;//0x81;
    LPC_EMC->StaticWaitWen1  = 0x2;//0;
    LPC_EMC->StaticWaitOen1  = 0x2;//0; // должен быть 0 - иначе WaitRd надо увеличивать
    LPC_EMC->StaticWaitRd1   = 0x4; // 1 - потому что с 0 не работает
    LPC_EMC->StaticWaitPage1 = 0;
    LPC_EMC->StaticWaitWr1   = 0x4;//0;
    LPC_EMC->StaticWaitTurn1 = 0;
//-------------------------------------------------------------------------------------

//-------------   Конфигурация адресного пространства сетевой платы   -----------------
    LPC_EMC->StaticConfig2   = 0x80;   // для начала настраиваем на 8-bit
    LPC_EMC->StaticWaitWen2  = 0;
    LPC_EMC->StaticWaitOen2  = 0;     // должен быть 0 - иначе WaitRd надо увеличивать
    LPC_EMC->StaticWaitRd2   = 0x7;    //
    LPC_EMC->StaticWaitPage2 = 0;
    LPC_EMC->StaticWaitWr2   = 0x5;
    LPC_EMC->StaticWaitTurn2 = 0;
//-------------------------------------------------------------------------------------
	emcx = EMC_Check( _EMC_CS0 );

    /* 25.05.2015 15:59 Паиилобм закоменвиаовавм паовеакг ЭОЗУ , в.к. она блла бделана длп Flash-пампви NVRAM ,
                        на ковоаой можно блло из длеи пеаенебви во внгваенноо ОЗУ и бпокойно паовеаивм длеи .
                        А бейзаб , когда закгпили более деиевле магнивонлекваизебкие Flash MRAM , в ковоаой
                        нев внгваенней ОЗУ вакап паовеака паиводив паобво к обнгленио длеики .
    for (TimerFlash = 0; TimerFlash < 600000; TimerFlash++) {}  // ожидаем восстановление флэш-памяти
	emcx = EMC_Check( _EMC_CS1 );
	Flash_Recall();
	for (TimerFlash = 0; TimerFlash < 600000; TimerFlash++) {}  // ожидаем восстановление флэш-памяти
        //инициализация записи
        Flash_Store(0);*/
}

/*-----------------18.09.2012 11:19-----------------
 * Функция очистки области памяти - запись всей памяти нулями
 * --------------------------------------------------*/
void EMC_zero( lword Begin, lword End )
{
  word *addr;
  for ( addr=(word *)Begin; addr<(word*)End; addr =(addr+1) )
   {
	  *addr = 0;
   }
}

/*-----------------17.08.2012 13:31-----------------
 * Проверка области памяти
 * возвращает: адрес неправильно прочитанных данных
 * -1 = даныые все верны
 * -2 = указанная область памяти не обслуживается
 * --------------------------------------------------*/
slword EMC_Check( byte Region )
{
   byte dir = 0;
   byte val, val2;
   byte *addr;
   lword BeginAddr, EndAddr;


   if ( Region > 2 ) ;  // Проверка ОЗУ сетевых плат проводится в соответствии с типом платы
   if ( Region == _EMC_CS0 )
   {
   	  BeginAddr = _EMC_CS0_BEGIN;
	  EndAddr   = _EMC_CS0_END;
   }
   else
     if ( Region == _EMC_CS1 )
     {
   	    BeginAddr = _EMC_CS1_BEGIN;
	    EndAddr   = _EMC_CS1_END;
     }
	 else
	   return -2;

   val = 0;
   for ( addr=(byte *)BeginAddr; addr<(byte*)EndAddr; addr =(addr+1) )
   {
	  *addr = val;
	  if ( dir == 0)
        if ( val < 255 ) val++;
        else dir = 1;
      else
        if ( val > 0 ) val--;
        else dir = 0;
   }
//-----   проверка   -----
   dir = 0;
   val = val2 = 0;
   for ( addr=(byte *)BeginAddr; addr<(byte*)EndAddr; addr = (addr+1) )
   {
      val2 = (byte)*addr;
      if (val != val2) return (slword)addr;
	  if ( dir == 0)
        if ( val < 255 ) val++;
        else dir = 1;
      else
        if ( val > 0 ) val--;
        else dir = 0;
   }
   EMC_zero( BeginAddr, EndAddr );
   return -1;
}



