#include   "can_drv.h"

/*-----------------19.12.2012 9:15------------------
 * Установка скорости работы CAN
 * --------------------------------------------------*/
static void CAN_SetBaudrate (LPC_CAN_TypeDef *CANx, word baudrate)
{
	lword result = 0;
	byte NT, TSEG1, TSEG2;
	lword CANPclk = 0;
	lword BRP;

	CANPclk = PeripheralClock;

	result = (CANPclk / 1000)/ baudrate;

//	 Вычисляем номинальное время
//	 NT (nominal time) = (TSEG1 + TSEG2 + 3)
//	 NT <= 24
//	 TSEG1 >= 2*TSEG2
	for(NT = 24; NT > 0; NT = NT-2)
	{
		if ((result%NT) == 0)
		{
			BRP = result / NT - 1;

			NT--;

			TSEG2 = (NT/3) - 1;

			TSEG1 = NT - (NT/3) - 1;

			break;
		}
	}

//	Переводим в режим сброса
	  CANx->MOD = 0x01;

//	 Устанавливаем timing сегментов
//  Default: SAM = 0x00;
//	SJW = 0x03;
	  CANx->BTR = (TSEG2 << 20) | (TSEG1 << 16) | (3 << 14) | BRP;

//	  CANx->MOD = 0;// Рабочий режим

}

/*-----------------19.12.2012 9:15------------------
 *  Инициализация Acceptance Filter Look-Up Table (AFLUT)
 * --------------------------------------------------*/
void CAN_aflut_Init( void )
{
  word i;


  LPC_SC->PCONP |= CLKPWR_PCONP_PCAN1;

  //Reset CANAF value
	 LPC_CANAF->AFMR = 0x01;
	 for (i = 0; i < 512; i++)
	 {
	 	LPC_CANAF_RAM->mask[i] = 0x00;
	 }

	 LPC_CANAF->SFF_sa = 0x00;
	 LPC_CANAF->SFF_GRP_sa = 0x00;
	 LPC_CANAF->EFF_sa = 0x00;
	 LPC_CANAF->EFF_GRP_sa = 0x00;
	 LPC_CANAF->ENDofTable = 0x00;

	 LPC_CANAF->AFMR = 0x00;

	 can_aflut.count = 0;
	 for ( i = 0; i < 2; i++ )
	 {
	    can_aflut.FC[i]    = 0;
	    can_aflut.SFF[i]   = 0;
	    can_aflut.SFFg[i]  = 0;
	    can_aflut.EFF[i]   = 0;
	    can_aflut.EFFg[i]  = 0;
	 }

}

/*-----------------19.12.2012 9:16------------------
 * Инициализация порта CAN
 * --------------------------------------------------*/
word can_config( byte port )
{
	LPC_CAN_TypeDef* pCan;
	word baudrate ;
	word i, Num_IDLUT, shift_id, SID;
    lword entry, data_temp;


	if ( port == _CAN0_Port )
	{
  	   pCan = LPC_CAN1;

       LPC_SC->PCONP |= CLKPWR_PCONP_PCAN1;
      // LPC_IOCON->P0_0  = D_RESERV | 0x1;                   // CAN0.RX
      // LPC_IOCON->P0_1  = D_RESERV | 0x1;                   // CAN0.TX
	}
	else if ( port == _CAN1_Port )
	{
  	   pCan = LPC_CAN2;

       LPC_SC->PCONP |= CLKPWR_PCONP_PCAN2;
      // LPC_IOCON->P0_4  = D_RESERV | 0x2;                   // CAN1.RX
      // LPC_IOCON->P0_5  = D_RESERV | 0x2;                   // CAN1.TX
	}
	else
	  return 0;

	can_fifo[port].mailbox = 0;
	can_fifo[port].rmsg[0].flag = 0;
	can_fifo[port].rmsg[1].flag = 0;
	can_fifo[port].rmsg[2].flag = 0;

    can_irq_flag = 0;

	pCan->MOD = 1; // Переводим в режим сброса
	pCan->IER = 0; // Отключаем все прерывания
	pCan->GSR = 0;

// Request command to release Rx, Tx buffer and clear data overrun
	//pCan->CMR = CAN_CMR_AT | CAN_CMR_RRB | CAN_CMR_CDO;
	pCan->CMR = (1 << 1) | (1 << 2) | (1 << 3);

// Читаем регистр ICR для сброса всех прерываний
	i = pCan->ICR;
	pCan->MOD = 0;// Рабочий режим

// Установка скорости
    if ( can_setting(port).config._.bt_125k == 1 )
    {
      baudrate = 125;
    }
    else
     if ( can_setting(port).config._.bt_250k == 1 )
     {
       baudrate = 250;
     }
     else
	   if ( can_setting(port).config._.bt_1M == 1 )
       {
         baudrate = 1000;
       }
       else
       {
         baudrate = 100;
       }
	CAN_SetBaudrate (pCan, baudrate);

	CAN_ResetAllMailbox(port);

	LPC_CANAF->AFMR = 0x01;

// Установка прерываний
    pCan->IER |= 0x0001;  // Прерывание на прием сообщений
	NVIC_SetPriority(CAN_IRQn, _CAN_IRQ_PRIORITY);
    NVIC_EnableIRQ(CAN_IRQn);

//--------------------------------------------------------------
	if ( can_setting(port).config._.vkl == 1 )
	{
	  if ( mco_vkl == 0 )
	  {
		can_reInit(port) = 0;
//----------------- Настройка фильтров в AFLUT ------------------

		if ( can_setting(port).config._.master == 1 )
		{
			if (( can_aflut.SFFg[_CAN1_Port] != 0 ) && ( port == _CAN0_Port ))
			{
			   LPC_CANAF_RAM->mask[can_aflut.count] = LPC_CANAF_RAM->mask[can_aflut.count-1];
	   		   LPC_CANAF->EFF_sa = LPC_CANAF->EFF_sa - (1<<2);
                           can_aflut.count--;
			}

			shift_id = 11 - _r.can[port].master_addr_size;
       		SID = ( _r.can[port].addr << shift_id ) + 0x1;
	   		entry = (port << 29) | (0 << 28) | (SID<<16);

       		SID = ( _r.can[port].addr << shift_id ) + 0x7F;
	   		entry += (port << 13) | (0 << 12) | (SID);

	   	   	LPC_CANAF_RAM->mask[can_aflut.count++] = entry;
	   		LPC_CANAF->EFF_sa = LPC_CANAF->EFF_sa + (1<<2);
			can_aflut.SFFg[port] = 1;
			if (( can_aflut.SFFg[_CAN1_Port] != 0 ) && ( port == _CAN0_Port ))
			{
	   		    LPC_CANAF->EFF_sa = LPC_CANAF->EFF_sa + (1<<2);
			    can_aflut.SFFg[_CAN1_Port] = 1;
			}
		}
		else //  can_setting(port).config._.master == 0
		{
			if ( port == _CAN0_Port )
			{
				if ( can_aflut.SFFg[_CAN1_Port] != 0 )
				{
				   data_temp = LPC_CANAF_RAM->mask[can_aflut.SFFg[_CAN1_Port] - 1];
				   can_aflut.count = 0;
				}
	   		    Num_IDLUT = ( 1 << _r.can[port].master_addr_size ) - 1; // Вычисляем количество идентификаторов
	   		    shift_id = 11 - _r.can[port].master_addr_size;
	   		    for ( i = 1; i <= Num_IDLUT; i++  )
	   		    {
				   if ( can_aflut.SFF[_CAN1_Port] != 0 )
				   {
				   	  LPC_CANAF_RAM->mask[can_aflut.count] = LPC_CANAF_RAM->mask[i-1];
				   }
// Прием всех идентификаторов от возможных мастеров включен (0<<28) и (0<<12)
	      		   SID = ( i << shift_id ) + _r.can[port].addr;
	      		   entry = (port << 29) | (0 << 28) | (SID << 16);

	      		   SID = ( i << shift_id ) + _r.can[port].addr_p;
	      		   entry += (port << 13) | (0 << 12) | ( SID );
	      	       LPC_CANAF_RAM->mask[i-1] = entry;
				   can_aflut.count++;
	  		    }
	  		    LPC_CANAF->SFF_GRP_sa = LPC_CANAF->SFF_sa + (can_aflut.count << 2);
				can_aflut.SFF[_CAN0_Port] = Num_IDLUT;
    	        LPC_CANAF->EFF_sa = LPC_CANAF->SFF_GRP_sa;
				if ( can_aflut.SFFg[_CAN1_Port]!= 0 )
				{
	      	        LPC_CANAF_RAM->mask[can_aflut.count++] = data_temp;
					LPC_CANAF->EFF_sa = LPC_CANAF->SFF_GRP_sa + (1<<2);
				}
			}
			else // port == _CAN1_Port
			{
				if ( can_aflut.SFFg[_CAN0_Port]!= 0 )
				{
				   data_temp = LPC_CANAF_RAM->mask[can_aflut.SFFg[_CAN0_Port] - 1];
				   can_aflut.count = 0;
				}
	   		    Num_IDLUT = ( 1 << _r.can[port].master_addr_size ) - 1; // Вычисляем количество идентификаторов
	   		    shift_id = 11 - _r.can[port].master_addr_size;
	   		    for ( i = 1; i <= Num_IDLUT; i++  )
	   		    {
// Прием всех идентификаторов от возможных мастеров включен (0<<28) и (0<<12)
	      		   SID = ( i << shift_id ) + _r.can[port].addr;
	      		   entry = (port << 29) | (0 << 28) | (SID << 16);

	      		   SID = ( i << shift_id ) + _r.can[port].addr_p;
	      		   entry += (port << 13) | (0 << 12) | ( SID );
	      	       LPC_CANAF_RAM->mask[can_aflut.count++] = entry;
	  		    }
	  		    LPC_CANAF->SFF_GRP_sa = LPC_CANAF->SFF_sa + (can_aflut.count << 2);
				can_aflut.SFF[_CAN1_Port] = Num_IDLUT;
    	        LPC_CANAF->EFF_sa = LPC_CANAF->SFF_GRP_sa;
				if ( can_aflut.SFFg[_CAN0_Port]!= 0 )
				{
	      	        LPC_CANAF_RAM->mask[can_aflut.count++] = data_temp;
					LPC_CANAF->EFF_sa = LPC_CANAF->SFF_GRP_sa + (1<<2);
				}

			}
		}
    	LPC_CANAF->EFF_GRP_sa = LPC_CANAF->EFF_sa;
    	LPC_CANAF->ENDofTable = LPC_CANAF->EFF_GRP_sa;
		LPC_CANAF->AFMR = 0x00;  // Нормальный режим (не FullCAN)

	  }
	  else   // mco_vkl == 1
	  {
			if ( port == _CAN0_Port )
			{
				if ( can_aflut.SFFg[_CAN1_Port]!= 0 )
				{
				   data_temp = LPC_CANAF_RAM->mask[can_aflut.SFFg[_CAN1_Port] - 1];
				   can_aflut.count = 0;
				}
// прописываем идентификаторы NMT= 0, SYNC = 0x80
	      		SID = 0x0000;
	      		entry = (port << 29) | (0 << 28) | (SID << 16);

	      		SID = 0x0080;
	      		entry += (port << 13) | (0 << 12) | ( SID );
	      	    LPC_CANAF_RAM->mask[can_aflut.count++] = entry;
// прописываем идентификаторы TIMESTAMP = 0x100
	      		SID = 0x0100;
	      		entry = (port << 29) | (0 << 28) | (SID << 16);

	      		SID = 0x0101; // этот идентификатор отключаем
	      		entry += (port << 13) | (1 << 12) | ( SID );
	      	    LPC_CANAF_RAM->mask[can_aflut.count++] = entry;
// прописываем идентификаторы PDO1rx, PDO2rx
	      		SID = 0x0200 + _r.can[port].addr;
	      		entry = (port << 29) | (0 << 28) | (SID << 16);

	      		SID = 0x0300 + _r.can[port].addr;
	      		entry += (port << 13) | (0 << 12) | ( SID );
	      	    LPC_CANAF_RAM->mask[can_aflut.count++] = entry;
// прописываем идентификаторы PDO3rx, PDO4rx
	      		SID = 0x0400 + _r.can[port].addr;
	      		entry = (port << 29) | (0 << 28) | (SID << 16);

	      		SID = 0x0500 + _r.can[port].addr;
	      		entry += (port << 13) | (0 << 12) | ( SID );
	      	    LPC_CANAF_RAM->mask[can_aflut.count++] = entry;
// прописываем идентификаторы SDOrx, NMTerr
	      		SID = 0x0600 + _r.can[port].addr;
	      		entry = (port << 29) | (0 << 28) | (SID << 16);

	      		SID = 0x0700 + _r.can[port].addr;
	      		entry += (port << 13) | (0 << 12) | ( SID );
	      	    LPC_CANAF_RAM->mask[can_aflut.count++] = entry;

				LPC_CANAF->SFF_GRP_sa = LPC_CANAF->SFF_sa + (can_aflut.count << 2);
				can_aflut.SFF[_CAN0_Port] = LPC_CANAF->SFF_GRP_sa;
    	        LPC_CANAF->EFF_sa = LPC_CANAF->SFF_GRP_sa;

				if ( can_aflut.SFFg[_CAN1_Port]!= 0 )
				{
	      	        LPC_CANAF_RAM->mask[can_aflut.count++] = data_temp;
					LPC_CANAF->EFF_sa = LPC_CANAF->SFF_GRP_sa + (1<<2);
				}
			}
    	LPC_CANAF->EFF_GRP_sa = LPC_CANAF->EFF_sa;
    	LPC_CANAF->ENDofTable = LPC_CANAF->EFF_GRP_sa;
		LPC_CANAF->AFMR = 0x00;  // Нормальный режим (не FullCAN)
	  }

	  pCan->MOD = 0;// Рабочий режим
      pCan->CMR = 0;
      can_reInit(port) = 0 ;
	}
	else  // выключаем CAN
	{
		can_reInit(port) = 1;
		can_deInit(port);
	  	pCan->MOD = 1;// Отключаемся
	}
      can_dd[port].Avar    = 0 ;
      can_dd[port].Error_send = 0 ;
      can_dd[port].Error_receive = 0 ;
      can_dd[port].Can_stop= 0 ;

return 1;
}


void can_deInit( byte port )
{
   lword num_temp, i;

   LPC_CANAF->AFMR = 0x01;
   if ( port == _CAN0_Port )
   {
       if ( can_aflut.SFF[_CAN0_Port] != 0) // работал как slave
	   {
	   	  if ( can_aflut.SFF[_CAN1_Port] != 0 ) // CAN1_Port тоже работал как slave
		  {
			 num_temp = can_aflut.SFF[_CAN0_Port];
			 for ( i = 0; i < num_temp; i++ )
			 {
			   LPC_CANAF_RAM->mask[i] = LPC_CANAF_RAM->mask[num_temp + i];
			   can_aflut.count--;
			 }
			 LPC_CANAF->SFF_GRP_sa = LPC_CANAF->SFF_sa + ( can_aflut.count<< 2);
			 LPC_CANAF->EFF_sa = LPC_CANAF->SFF_GRP_sa;
			 can_aflut.SFF[_CAN1_Port] = LPC_CANAF->SFF_GRP_sa>>2;
		  }
		  else // _CAN1_Port не slave
		  {
			 if ( can_aflut.SFFg[_CAN1_Port] == 0) // _CAN1_Port не master
			 {
			    LPC_CANAF->SFF_sa = 0;
			    LPC_CANAF->SFF_GRP_sa = 0;
			    LPC_CANAF->EFF_sa = 0;
			 	can_aflut.count = 0;
			 }
			 else // can_aflut.SFFg[_CAN1_Port] != 0 // _CAN1_Port master
			 {
			    LPC_CANAF_RAM->mask[0] = LPC_CANAF_RAM->mask[can_aflut.SFF[_CAN0_Port]];
			    LPC_CANAF->SFF_GRP_sa = 0;
			    LPC_CANAF->EFF_sa = 1<<2;
			 	can_aflut.count = 1;
			 }
		  }
	   }
	   else // работал как master
	   {
		  if ( can_aflut.SFFg[port] != 0 ) // _CAN0_Port master
		  {
	   	     if ( can_aflut.SFF[_CAN1_Port] != 0 ) // _CAN1_Port slave
		     {
		        LPC_CANAF->EFF_sa = LPC_CANAF->SFF_GRP_sa;
			    can_aflut.count--;
		     }
		     else // _CAN1_Port не slave
		     {
			    if ( can_aflut.SFFg[_CAN1_Port] == 0 ) // _CAN1_Port не master
			    {
			       LPC_CANAF->EFF_sa = 0;
				   can_aflut.count = 0;
			    }
			    else // _CAN1_Port master
			    {
				   LPC_CANAF_RAM->mask[0] = LPC_CANAF_RAM->mask[1];
			       LPC_CANAF->EFF_sa = 1<<2;
				   can_aflut.count = 1;
			    }
		     }
		  }
	   }
	   can_aflut.SFF[_CAN0_Port]  = 0;
	   can_aflut.SFFg[_CAN0_Port] = 0;
   }
   else // port == _CAN1_Port
   {
       if ( can_aflut.SFF[_CAN1_Port] != 0) // работал как slave
	   {
	   	  if ( can_aflut.SFF[_CAN0_Port] != 0 ) // _CAN0_Port slave
		  {
			 can_aflut.count -= can_aflut.SFF[_CAN1_Port];
			 LPC_CANAF->SFF_GRP_sa = LPC_CANAF->SFF_sa + ( can_aflut.count<< 2);
			 LPC_CANAF->EFF_sa = LPC_CANAF->SFF_GRP_sa;
		  }
		  else // _CAN0_Port не slave
		  {
			 if ( can_aflut.SFFg[_CAN0_Port] == 0) // _CAN0_Port не master
			 {
			    LPC_CANAF->SFF_sa = 0;
			    LPC_CANAF->SFF_GRP_sa = 0;
			    LPC_CANAF->EFF_sa = 0;
			 	can_aflut.count = 0;
			 }
			 else // can_aflut.SFFg[_CAN1_Port] != 0  // _CAN0_Port master
			 {
			    LPC_CANAF_RAM->mask[0] = LPC_CANAF_RAM->mask[can_aflut.count];
			    LPC_CANAF->SFF_GRP_sa = LPC_CANAF->SFF_sa;
			    LPC_CANAF->EFF_sa = 1<<2;
			 	can_aflut.count = 1;
			 }
		  }
	   }
	   else // работал не slave
	   {
		  if ( can_aflut.SFFg[port] != 0 ) // работал как master
		  {
	   	     if ( can_aflut.SFF[_CAN0_Port] != 0 ) // _CAN0_Port slave
		     {
		        LPC_CANAF->EFF_sa = LPC_CANAF->SFF_GRP_sa;
			    can_aflut.count--;
		     }
		     else
		     {
			    if ( can_aflut.SFFg[_CAN0_Port] == 0 )  // _CAN0_Port не master
			    {
			       LPC_CANAF->EFF_sa = 0;
				   can_aflut.count = 0;
			    }
			    else // _CAN0_Port master
			    {
			       LPC_CANAF->EFF_sa = 1<<2;
				   can_aflut.count = 1;
			    }
			 }
		  }
	   }
	   can_aflut.SFF[_CAN1_Port]  = 0;
	   can_aflut.SFFg[_CAN1_Port] = 0;
   }
   LPC_CANAF->EFF_GRP_sa = LPC_CANAF->EFF_sa;
   LPC_CANAF->ENDofTable = LPC_CANAF->EFF_GRP_sa;
   LPC_CANAF->AFMR = 0x00;  // Нормальный режим (не FullCAN)
}


word can_test( byte port )
{
   LPC_CAN_TypeDef* pCan;
   lword status;
   byte i;

   if ( port == _CAN0_Port )
   {
      pCan = LPC_CAN1;
   }
   else
   {
      pCan = LPC_CAN2;
   }

// Выключить контроллер CAN и программы.
  if ( tst_can_stop(port) == 1 )
  {    // для возможности работы с CAN из монитора без рабочей программы.
      if ( can_reInit(port) == 0 )
      {
        can_deInit(port);
        can_reInit(port) = 1 ; // Для автоматического срабатывания переинициализации.
        pCan->MOD = 1; // отключаем CAN

       can_fifo[port].rmsg[0].flag = 0;
	   for ( i=0; i<8; i++ )
	   {
	      can_fifo[port].rmsg[0].msg.data[i] = 0;
	   }
      }
      return 1 ;
  }
// Переинициализация по команде с пульта после смены уставок CAN.
  if ( can_reInit(port) == 1 )
    {
      can_deInit(port);
      can_init(port);
      can_reInit(port) = 0 ;
      return 1 ;
    }
   //ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД

	status = pCan->GSR;

// Ошибки - CAN еще не отключился от шины.
	if ( ( status & _CAN_GSR_ES ) ==  _CAN_GSR_ES  )
	{
       can_dd[port].Avar++ ;
	}
// CAN отключился от шины - BOff
    if ( ( status & _CAN_GSR_BS ) == _CAN_GSR_BS )
	{
//	   can_init(port);
       can_reInit(port) = 1 ;
       mSet_ServiceMsg( _Srv_ResCan ) ;
       return 2 ;
	}


    if ( ((pCan->SR & _CAN_SR_TBS1) != _CAN_SR_TBS1) &&
         ((pCan->SR & _CAN_SR_TBS2) != _CAN_SR_TBS2 ) )
    {
       if   ( (u)((w)(timer1-can_dd[port].time_out_send14)) > _TimeOut_send ) pCan->CMR = _CAN_CMR_AT;
       if   ( (u)((w)(timer1-can_dd[port].time_out_send13)) > _TimeOut_send ) pCan->CMR = _CAN_CMR_AT;

       if ( ( (u)((w)(timer1-can_dd[port].time_out_send14)) > _TimeOut_send ) &&
            ( (u)((w)(timer1-can_dd[port].time_out_send13)) > _TimeOut_send ) )
       {
       // pCan->CMR = _CAN_CMR_AT;//сброс запроса передачи.
          can_dd[port].Error_send++ ;
       }
    }

/*  if ( (pCan->SR & _CAN_SR_TBS2) != _CAN_SR_TBS2 )
    {
       if ( (u)((w)(timer1-can_dd[port].time_out_send13)) > _TimeOut_send )
       {
          pCan->CMR = _CAN_CMR_AT;//сброс запроса передачи.
          can_dd[port].Error_send++ ;
       }
    }*/
	return 0;
}

/*-----------------20.12.2012 13:37-----------------
 * Отправка сообщения в порт
 * --------------------------------------------------*/
word canSend( byte port, struct canMSG_Fuj *ptr )
{
   LPC_CAN_TypeDef* pCan;
   lword data;

   if ( port == _CAN0_Port )
   {
      pCan = LPC_CAN1;
   }
   else
   {
      pCan = LPC_CAN2;
   }

   if ( (pCan->SR & _CAN_SR_TBS1) == _CAN_SR_TBS1 )
   {
// Канал передачи 1 доступен для работы
	  pCan->TFI1 &= ~ 0xC00F0000;
	  pCan->TFI1 |= ((ptr->cfg.dlen) << 16);
	  pCan->TID1 = ptr->id >> 21;

	  data = (ptr->data[0]) | (((ptr->data[1]))<< 8) | ((ptr->data[2]) << 16) | ((ptr->data[3]) << 24);
	  pCan->TDA1 = data;

	  data = (ptr->data[4]) | (((ptr->data[5])) << 8)|((ptr->data[6]) << 16)|((ptr->data[7]) << 24);
	  pCan->TDB1 = data;

	  pCan->CMR = 0x21;
      can_dd[port].time_out_send14 = timer1 ;

	  return 0;
   }
   else
      if ( (pCan->SR & _CAN_SR_TBS2) == _CAN_SR_TBS2 )
      {
// Канал передачи 2 доступен для работы
	     pCan->TFI2 &= ~ 0xC00F0000;
	     pCan->TFI2 |= ((ptr->cfg.dlen) << 16);
	     pCan->TID2 = ptr->id >> 21;

	     data = (ptr->data[0]) | (((ptr->data[1]))<< 8) | ((ptr->data[2]) << 16) | ((ptr->data[3]) << 24);
	     pCan->TDA2 = data;

	     data = (ptr->data[4]) | (((ptr->data[5])) << 8)|((ptr->data[6]) << 16)|((ptr->data[7]) << 24);
	     pCan->TDB2 = data;

	     pCan->CMR = 0x41;
         can_dd[port].time_out_send13 = timer1 ;

          return 0;
      }
	  else
	  {
	  	 return 1;
	  }
   return 0;
}

/*-----------------20.12.2012 13:38-----------------
 * Прием сообщений
 * --------------------------------------------------*/
word canReceive( byte port, struct canMSG_Fuj *ptr )
{
   LPC_CAN_TypeDef* pCan;
   byte i;
   byte numMailbox;

   if ( port == _CAN0_Port )
   {
      pCan = LPC_CAN1;
   }
   else
   {
      pCan = LPC_CAN2;
   }

   numMailbox = can_fifo[port].mailbox;
   if ( can_fifo[port].rmsg[0].flag == 1 )
   {
	  can_fifo[port].rmsg[0].flag = 0;
povtor:
asm_di();
          ptr->id       = can_fifo[port].rmsg[0].msg.id;
	  ptr->cfg.dlen = can_fifo[port].rmsg[0].msg.cfg.dlen;

	  for ( i=0; i<8; i++ )
	  {
	     ptr->data[i]=  can_fifo[port].rmsg[0].msg.data[i];
	  }


	  if ( numMailbox > 0 )
	  {
	  	 memcpy(&(can_fifo[port].rmsg[0]), &(can_fifo[port].rmsg[1]), sizeof(TMailBox));
         can_fifo[port].rmsg[1].flag = 0;
		 numMailbox--;
		 if ( numMailbox > 0)
	  	   memcpy(&(can_fifo[port].rmsg[1]), &(can_fifo[port].rmsg[2]), sizeof(TMailBox));
         can_fifo[port].rmsg[2].flag = 0;
	  }
      can_fifo[port].mailbox = numMailbox;
asm_ei();


      if ( (pCan->GSR & _CAN_GSR_DOS) == _CAN_GSR_DOS )
      {
       //если есть переполнение может быть наложение "старых"
       //и "новых" данных - необходимо перечитать данные
	     pCan->CMR = _CAN_CMR_CDO;
         can_dd[port].Error_receive++ ;
         goto povtor ;
      }
      return 1;
   }
   return 0 ;
}


/*-----------------24.12.2012 9:51------------------
 * Прерывания по CAN
 * --------------------------------------------------*/
extern "C" {
void CAN_IRQHandler(void)
{
   LPC_CAN_TypeDef* pCan;
   lword  data;
   word numMailbox;

    pCan = LPC_CAN1;
	if (pCan->ICR & 0x01 )
	{
	  if ( mco_vkl == 0)
	  {
		 numMailbox = can_fifo[0].mailbox;
		 if ( can_fifo[0].rmsg[numMailbox].flag == 1 )
		 {
		 	if ( numMailbox < 2 ) numMailbox++;
			else       goto end_irq0;
		 }

	     can_fifo[0].rmsg[numMailbox].msg.id       = pCan->RID << 21;
	     can_fifo[0].rmsg[numMailbox].msg.cfg.dlen = (b)(((pCan->RFS) & 0x000F0000) >> 16);

	     data = pCan->RDA;
	     can_fifo[0].rmsg[numMailbox].msg.data[0]=  data & 0x000000FF;
	     can_fifo[0].rmsg[numMailbox].msg.data[1]= (data & 0x0000FF00) >> 8;
	     can_fifo[0].rmsg[numMailbox].msg.data[2]= (data & 0x00FF0000) >> 16;
	     can_fifo[0].rmsg[numMailbox].msg.data[3]= (data & 0xFF000000) >> 24;

	     data = pCan->RDB;
	     can_fifo[0].rmsg[numMailbox].msg.data[4]=  data & 0x000000FF;
	     can_fifo[0].rmsg[numMailbox].msg.data[5]= (data & 0x0000FF00) >> 8;
	     can_fifo[0].rmsg[numMailbox].msg.data[6]= (data & 0x00FF0000) >> 16;
	     can_fifo[0].rmsg[numMailbox].msg.data[7]= (data & 0xFF000000) >> 24;

		 can_fifo[0].rmsg[numMailbox].flag = 1;
		 can_fifo[0].mailbox = numMailbox;

end_irq0:
	     pCan->CMR = _CAN_CMR_RRB;
#ifdef _CAN_SLAVE_IRQ
	     canSlaveDrive(_CAN0_Port);
#endif
	  }
	  else
	  {
		 switch ( ((pCan->RID) & 0x00000780) >> 7 )
		 {
		 	case _COBID_NMT :
				numMailbox = MB_BROADCAST;
				break;
		 	case _COBID_PDO1RX :
				numMailbox = MB_PDO_RX;
				break;
		 	case _COBID_PDO2RX :
				numMailbox = MB_PDO21_RX;
				break;
		 	case _COBID_PDO3RX :
				numMailbox = MB_PDO22_RX;
				break;
		 	case _COBID_PDO4RX :
				numMailbox = MB_PDO23_RX;
				break;
		 	case _COBID_SDORX :
				numMailbox = MB_SDO_RX;
				break;
		 	case _COBID_NMTERR :
				numMailbox = MB_NMT_RX;
				break;
		 }

	 	 pCANTransfer = &cantransfer[numMailbox];
		 pCANTransfer->identifier = pCan->RID;
		 pCANTransfer->data_low_reg  = pCan->RDA;
		 pCANTransfer->data_high_reg = pCan->RDB;

		 pCANTransfer->size = (((pCan->RFS) & 0x000F0000) >> 16);
         pCANTransfer->mailbox_number = numMailbox;

		 can_fifo[0].rmsg[0].flag = 1;
	     pCan->CMR = _CAN_CMR_RRB;
         can_irq_flag |= (1 << numMailbox);
#ifdef  _MCO_CAN_IRQ
		 MCO_Server(pCANTransfer);
#endif
	  }
	}
#if _Num_CAN_Ports > 1 
    pCan = LPC_CAN2;
	if (pCan->ICR & 0x01 )
	{
	  if ( mco_vkl == 0)
	  {
		 numMailbox = can_fifo[1].mailbox;
		 if ( can_fifo[1].rmsg[numMailbox].flag == 1 )
		 {
		 	if ( numMailbox < 2 ) numMailbox++;
			else       goto end_irq1;
		 }

	     can_fifo[1].rmsg[numMailbox].msg.id       = pCan->RID << 21;
	     can_fifo[1].rmsg[numMailbox].msg.cfg.dlen = (b)(((pCan->RFS) & 0x000F0000) >> 16);

	     data = pCan->RDA;
	     can_fifo[1].rmsg[numMailbox].msg.data[0]=  data & 0x000000FF;
	     can_fifo[1].rmsg[numMailbox].msg.data[1]= (data & 0x0000FF00) >> 8;
	     can_fifo[1].rmsg[numMailbox].msg.data[2]= (data & 0x00FF0000) >> 16;
	     can_fifo[1].rmsg[numMailbox].msg.data[3]= (data & 0xFF000000) >> 24;

	     data = pCan->RDB;
	     can_fifo[1].rmsg[numMailbox].msg.data[4]=  data & 0x000000FF;
	     can_fifo[1].rmsg[numMailbox].msg.data[5]= (data & 0x0000FF00) >> 8;
	     can_fifo[1].rmsg[numMailbox].msg.data[6]= (data & 0x00FF0000) >> 16;
	     can_fifo[1].rmsg[numMailbox].msg.data[7]= (data & 0xFF000000) >> 24;

		 can_fifo[1].rmsg[numMailbox].flag = 1;
		 can_fifo[1].mailbox = numMailbox;

end_irq1:
	  	pCan->CMR = _CAN_CMR_RRB;

//	  	flag_CanReceive[1][mailbox[1]] = 1;
#ifdef _CAN_SLAVE_IRQ
	  	canSlaveDrive(_CAN1_Port);
#endif
	  }
	  else
	  {
		 switch ( ((pCan->RID) & 0x00000780) >> 7 )
		 {
		 	case _COBID_NMT :
				numMailbox = MB_BROADCAST;
				break;
		 	case _COBID_PDO1RX :
				numMailbox = MB_PDO_RX;
				break;
		 	case _COBID_PDO2RX :
				numMailbox = MB_PDO21_RX;
				break;
		 	case _COBID_PDO3RX :
				numMailbox = MB_PDO22_RX;
				break;
		 	case _COBID_PDO4RX :
				numMailbox = MB_PDO23_RX;
				break;
		 	case _COBID_SDORX :
				numMailbox = MB_SDO_RX;
				break;
		 	case _COBID_NMTERR :
				numMailbox = MB_NMT_RX;
				break;
		 }

	 	 pCANTransfer = &cantransfer[numMailbox];
		 pCANTransfer->identifier = pCan->RID;
		 pCANTransfer->data_low_reg  = pCan->RDA;
		 pCANTransfer->data_high_reg = pCan->RDB;

		 pCANTransfer->size = (((pCan->RFS) & 0x000F0000) >> 16);
         pCANTransfer->mailbox_number = numMailbox;

		 can_fifo[0].rmsg[0].flag = 1;
	     pCan->CMR = _CAN_CMR_RRB;
         can_irq_flag |= (1 << numMailbox);
#ifdef  _MCO_CAN_IRQ
		 MCO_Server(pCANTransfer);
#endif
	  }
    }
#endif
}
}//extern "C"
void CAN_ResetTransfer( TCAN_Transfer *pTransfer )
{
    pTransfer->state = CAN_IDLE;
    pTransfer->test_can = 0;
    pTransfer->mode_reg = 0;
    pTransfer->acceptance_mask_reg = 0;
    pTransfer->identifier = 0;
    pTransfer->data_low_reg = 0;
    pTransfer->data_high_reg = 0;
    pTransfer->control_reg = 0;
    pTransfer->mailbox_in_use = 0;
    pTransfer->size = 0;
}

void CAN_ResetAllMailbox( byte port )
{
    byte i;
	TCAN_Transfer *pTransfer;

    for ( i=0; i<16; i++ )
	{
		pTransfer = &cantransfer[i];
		pTransfer->can_number = port;
	    CAN_ResetTransfer( pTransfer );
        pTransfer->can_number = port;
        pTransfer->mailbox_number = i;
        pTransfer->mode_reg = 0;
        pTransfer->acceptance_mask_reg = 0;
        pTransfer->identifier = 0;
        pTransfer->data_low_reg = 0x00000000;
        pTransfer->data_high_reg = 0x00000000;
        pTransfer->control_reg = 0x00000000;
    }
}

byte SetRxMailbox( byte port, word ID, byte mb )
{
	TCAN_Transfer *pTransfer;

   if  ( mb > NUM_MAILBOX_MAX )
   {
	   return 0;
   }
   pTransfer = &cantransfer[mb];


   pTransfer->identifier = ID;
   pTransfer->data_low_reg = 0;
   pTransfer->data_high_reg = 0;
   pTransfer->control_reg = 0;
   return 1;
}

byte SetTxMailbox( byte port, word ID, byte mb )
{
	TCAN_Transfer *pTransfer;

   if ( (mb > 16) || (ID > 127) )
   {
	  return 0;
   }
    // Init Mailbox
   pTransfer = &cantransfer[mb];
   CAN_ResetTransfer( pTransfer );
   pTransfer->mailbox_number = mb;
   pTransfer->acceptance_mask_reg = 0;
   pTransfer->identifier = ID;
   pTransfer->data_low_reg = 0x00000000;
   pTransfer->data_high_reg = 0x00000000;
   pTransfer->control_reg = 0x0;
   return 1;
}

byte CAN_SendMsg( TCAN_Transfer *pTransfer )
{

   LPC_CAN_TypeDef* pCan;

   if ( pTransfer->can_number == _CAN0_Port )
   {
      pCan = LPC_CAN1;
   }
   else
   {
      pCan = LPC_CAN2;
   }

   can_dd[pTransfer->can_number].time_out_send[pTransfer->mailbox_number] = timer1;

   if ( (pCan->SR & _CAN_SR_TBS1) == _CAN_SR_TBS1 )
   {
// Канал передачи 1 доступен для работы
	  pCan->TFI1 &= ~ 0xC00F0000;
	  pCan->TFI1 |= ((pTransfer->size) << 16);
	  pCan->TID1 = pTransfer->identifier;

	  pCan->TDA1 = pTransfer->data_low_reg;

	  pCan->TDB1 = pTransfer->data_high_reg;

	  pCan->CMR = 0x21;
      can_dd[pTransfer->can_number].time_out_send14 = timer1 ;

      return CAN_STATUS_SUCCESS;
   }
   else
      if ( (pCan->SR & _CAN_SR_TBS2) == _CAN_SR_TBS2 )
      {
// Канал передачи 2 доступен для работы
	     pCan->TFI2 &= ~ 0xC00F0000;
	     pCan->TFI2 |= ((pTransfer->size) << 16);
	     pCan->TID2 = pTransfer->identifier;

	     pCan->TDA2 = pTransfer->data_low_reg;

	     pCan->TDB2 = pTransfer->data_high_reg;

	     pCan->CMR = 0x41;
         can_dd[pTransfer->can_number].time_out_send13 = timer1 ;

	     return CAN_STATUS_SUCCESS;
      }
	  else
	  {
	  	 return CAN_STATUS_ABORTED;
	  }
   return CAN_STATUS_SUCCESS;
}

