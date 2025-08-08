
void ISR_CAN(byte port)
{
   CANLSTR* pCANL_port;
   CANMSTR* pCANM_port;
   byte numMailbox;
   lword temp;

   pCANL_port = (CANLSTR*)(0x100000 + port*0x200);
   pCANM_port = (CANMSTR*)(0x10002C + port*0x200);


    for ( numMailbox = 0; numMailbox < NUM_MAILBOX_MAX; numMailbox++ )
	{
mco_povtor:
	   if ( (pCANL_port->rcr.word & (1 << numMailbox)) == (1 << numMailbox) &&
	        (pCANL_port->rier.word & (1 << numMailbox)) == (1 << numMailbox) )
	   {

		   pCANTransfer = &cantransfer[numMailbox];
           temp = ((pCANM_port->idr[numMailbox].dword & 0xFF000000) >> 8) + ((pCANM_port->idr[numMailbox].dword & 0x00FF0000) << 8);
		   pCANTransfer->identifier = temp >> 21;

		   pCANTransfer->data_low_reg =	  ((pCANM_port->dtr[numMailbox].dwords[0] & 0xFF000000) >> 8)
										+ ((pCANM_port->dtr[numMailbox].dwords[0] & 0x00FF0000) << 8)
		        						+ ((pCANM_port->dtr[numMailbox].dwords[0] & 0x0000FF00) >> 8)
		        						+ ((pCANM_port->dtr[numMailbox].dwords[0] & 0x000000FF) << 8);
		   pCANTransfer->data_high_reg =  ((pCANM_port->dtr[numMailbox].dwords[1] & 0xFF000000) >> 8)
										+ ((pCANM_port->dtr[numMailbox].dwords[1] & 0x00FF0000) << 8)
		        						+ ((pCANM_port->dtr[numMailbox].dwords[1] & 0x0000FF00) >> 8)
		        						+ ((pCANM_port->dtr[numMailbox].dwords[1] & 0x000000FF) << 8);
           pCANTransfer->size = pCANM_port->dlcr[numMailbox].word & 0x0F;
           pCANTransfer->mailbox_number = numMailbox;
		   if (pCANL_port->rovrr.word & (1 << numMailbox) == (1 << numMailbox))
		   {
		      pCANL_port->rovrr.word &= ~(1 << numMailbox);
              can_dd[port].Error_receive++ ;
              goto mco_povtor ;
		   }
           can_irq_flag |= (1 << numMailbox);
		   #ifdef  _MCO_CAN_IRQ
			  MCO_Server(pCANTransfer);
		   #endif
		   pCANL_port->rcr.word &= ~(1 << numMailbox);
		   return;
	   }
	}
}

byte CAN_Init( byte port )
{
   CANHSTR* pCANH_port;
   CANLSTR* pCANL_port;
   CANMSTR* pCANM_port;

   pCANL_port = (CANLSTR*)(0x100000 + port*0x200);
   pCANH_port = (CANHSTR*)(0x100010 + port*0x200);
   pCANM_port = (CANMSTR*)(0x10002C + port*0x200);
   pCANH_port->csr.bit.HALT = 1;
   pCANH_port->csr.bit.TOE = 0;
   pCANL_port->rier.word = 0;
   pCANL_port->bvalr.word = 0;

   can_irq_flag = 0;

	if ( CAN_BaudRateCalculate( pCANH_port, 0 ) == 0 )  return 0;

    CAN_ResetAllMailbox(port);

	pCANH_port->amr[0].dword = 0x700F0000 ;
	pCANH_port->amr[1].dword = 0x00F00000 ;

    ICR11 = 30;
	if ( CAN_Synchronisation(port) == 1 )   return 1;
    else 						        return 0;
}

byte CAN_BaudRateCalculate( CANHSTR *base_CAN, lword baudrate )
{
	if ( _r.can[0].config._.bt_125k == 1 )
	{
      base_CAN->btr.word = 0x4987 ;
	}
	else
	  if ( _r.can[0].config._.bt_250k == 1 )
	  {
         base_CAN->btr.word = 0x4983 ;
	  }
	  else
	    if ( _r.can[0].config._.bt_1M == 1 )
	    {
           base_CAN->btr.word = 0x4980 ;
	    }
	baudrate = 0;
    return 1;
}

byte CAN_Synchronisation( byte port )
{
   CANHSTR* pCANH_port;

   pCANH_port = (CANHSTR*)(0x100010 + port*0x200);



   pCANH_port->csr.bit.TOE = 1;
   if ( can_setting(port).config._.vkl == 1 )
   {
      pCANH_port->csr.bit.HALT = 0;
      can_reInit(port) = 0 ;
   }
   else
   {
      pCANH_port->csr.bit.HALT = 1;
      can_reInit(port) = 1 ;

   }
   return 1;
}

void CAN_ResetTransfer( TCAN_Transfer *pTransfer )
{
    pTransfer->state = CAN_IDLE;
    pTransfer->can_number = 0;
    pTransfer->mailbox_number = 0;
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

void CAN_InitMailboxRegisters( TCAN_Transfer *pTransfer )
{
    CANHSTR* pCANH_port;
    CANLSTR* pCANL_port;
    CANMSTR* pCANM_port;
	lword temp;

    pCANL_port = (CANLSTR*)(0x100000 + pTransfer->can_number*0x200);
    pCANH_port = (CANHSTR*)(0x100010 + pTransfer->can_number*0x200);
    pCANM_port = (CANMSTR*)(0x10002C + pTransfer->can_number*0x200);

    pTransfer->mailbox_in_use |= 1 << (pTransfer->mailbox_number);
    // MailBox Control Register
    pCANL_port->bvalr.word &= ~(1 << pTransfer->mailbox_number); //все объекты сообщений отключены
    pCANH_port->ider.word  &= 0;//~(1 << pTransfer->mailbox_number); //все объекты - СТАНДАРТНЫЙ ФРЕЙМ
    pCANH_port->trtrr.word &= 0;//~(1 << pTransfer->mailbox_number); //все объекты - DATA FRAME (не REMOTE FRAME)
    pCANH_port->rfwtr.word &= 0;//~(1 << pTransfer->mailbox_number); //немедленная передача фрейма данных после установки

	if ( pTransfer->acceptance_mask_reg == 0 )
	{
		temp = ~(3 << ((lword)pTransfer->mailbox_number * 2));
	    pCANH_port->amsr.dword &= ((temp & 0xFFFF0000) >> 16) + ((temp & 0x0000FFFF) << 16);
		temp =  0 << ((lword)pTransfer->mailbox_number * 2);
	    pCANH_port->amsr.dword |= ((temp & 0xFFFF0000) >> 16) + ((temp & 0x0000FFFF) << 16);
	}
	else
	{
	   if ( pTransfer->acceptance_mask_reg == 1 )
	   {
  	   		temp = ~(3 << ((lword)pTransfer->mailbox_number * 2));
	    	pCANH_port->amsr.dword &= ((temp & 0xFFFF0000) >> 16) + ((temp & 0x0000FFFF) << 16);
			temp =  2 << ((lword)pTransfer->mailbox_number * 2);
	    	pCANH_port->amsr.dword |= ((temp & 0xFFFF0000) >> 16) + ((temp & 0x0000FFFF) << 16);

	   }
	   else
	   {
			temp = ~(3 << ((lword)pTransfer->mailbox_number * 2));
	    	pCANH_port->amsr.dword &= ((temp & 0xFFFF0000) >> 16) + ((temp & 0x0000FFFF) << 16);
			temp =  3 << ((lword)pTransfer->mailbox_number * 2);
	    	pCANH_port->amsr.dword |= ((temp & 0xFFFF0000) >> 16) + ((temp & 0x0000FFFF) << 16);
	   }
	}

	temp = pTransfer->identifier << 21;
	pCANM_port->idr[pTransfer->mailbox_number].dword = ((temp & 0xFF000000) >> 8)
	   												 + ((temp & 0x00FF0000) << 8);

    // MailBox Data Low Register
    pCANM_port->dtr[pTransfer->mailbox_number].dwords[0] = pTransfer->data_low_reg;
    // MailBox Data High Register
    pCANM_port->dtr[pTransfer->mailbox_number].dwords[1] = pTransfer->data_high_reg;
    // MailBox Control Register
    pCANM_port->dlcr[pTransfer->mailbox_number].bitc.DLC = pTransfer->control_reg;

    pCANL_port->bvalr.word |= 1 << pTransfer->mailbox_number; //все объекты сообщений отключены
}

void CAN_ResetAllMailbox( byte port )
{
    byte i;
	TCAN_Transfer *pTransfer;

    for ( i=0; i<8; i++ )
	{
		pTransfer = &cantransfer[i];
		pCANTransfer[i].can_number = port;
	    CAN_ResetTransfer( pTransfer );
        pCANTransfer->can_number = port;
        pCANTransfer->mailbox_number = i;
        pCANTransfer->mode_reg = 0; //AT91C_CAN_MOT_DIS;
        pCANTransfer->acceptance_mask_reg = 0;
        pCANTransfer->identifier = 0;
        pCANTransfer->data_low_reg = 0x00000000;
        pCANTransfer->data_high_reg = 0x00000000;
        pCANTransfer->control_reg = 0x00000000;
        CAN_InitMailboxRegisters( pTransfer );
    }
}


byte CAN_SendMsg( TCAN_Transfer *pTransfer )
{

	word temp;
	CANLSTR* pCANL_port;
    CANMSTR* pCANM_port;

    pCANL_port = (CANLSTR*)(0x100000 + pTransfer->can_number*0x200);
    pCANM_port = (CANMSTR*)(0x10002C + pTransfer->can_number*0x200);


    can_dd[pTransfer->can_number].time_out_send[pTransfer->mailbox_number] = timer1;


	pTransfer->identifier <<= 5;

	temp = ((pTransfer->identifier & 0xFF00) >> 8) + ((pTransfer->identifier & 0x00FF) << 8);

	pCANM_port->idr[pTransfer->mailbox_number].word =  temp ;

    pCANM_port->dtr[pTransfer->mailbox_number].dwords[0] = ((pTransfer->data_low_reg & 0xFF000000) >> 8)
														 + ((pTransfer->data_low_reg & 0x00FF0000) << 8)
														 + ((pTransfer->data_low_reg & 0x0000FF00) >> 8)
														 + ((pTransfer->data_low_reg & 0x000000FF) << 8);
    // MailBox Data High Register
    pCANM_port->dtr[pTransfer->mailbox_number].dwords[1] = ((pTransfer->data_high_reg & 0xFF000000) >> 8)
														 + ((pTransfer->data_high_reg & 0x00FF0000) << 8)
														 + ((pTransfer->data_high_reg & 0x0000FF00) >> 8)
														 + ((pTransfer->data_high_reg & 0x000000FF) << 8);
    pCANM_port->dlcr[pTransfer->mailbox_number].bitc.DLC = pTransfer->size;

	pCANL_port->treqr.word |= (1 << pTransfer->mailbox_number);

    return CAN_STATUS_SUCCESS;
}


byte SetRxMailbox( byte port, word ID, byte mb )
{
   TCAN_Transfer   canTransfer;
   CANLSTR* pCANL_port;

   pCANL_port = (CANLSTR*)(0x100000 + port*0x200);

   if  ( mb > NUM_MAILBOX_MAX )
   {
	   return 0;
   }
   canTransfer.can_number = port;
   canTransfer.mailbox_number = mb;
//   canTransfer.mode_reg = AT91C_CAN_MOT_RX ;

   if ( (ID == 0x700) || (ID == 0x680) )
   {
          canTransfer.acceptance_mask_reg = 1;//0x700; // 0 1110 0000000
   }
   else
   {
	 if ( (ID > 0) && (ID < 128) )
	 {
          canTransfer.acceptance_mask_reg = 2;//0x07F; // 0 0000 1111111
	 }
	 else
	 {
          canTransfer.acceptance_mask_reg = 0;//0x600; // 0 1100 0000000
	 }
   }

   canTransfer.identifier = ID;
   canTransfer.data_low_reg = 0;
   canTransfer.data_high_reg = 0;
   canTransfer.control_reg = 0;
   CAN_InitMailboxRegisters( &canTransfer );
   mSetIRQ_Mailbox( pCANL_port, mb );
   return 1;
}

byte SetTxMailbox( byte port, word ID, byte mb )
{
   TCAN_Transfer   canTransfer;

   if ( (mb > 8) || (ID > 127) )
   {
	  return 0;
   }
    // Init Mailbox
    canTransfer.can_number = port;
    CAN_ResetTransfer( &canTransfer );
    canTransfer.mailbox_number = mb;
    canTransfer.acceptance_mask_reg = 0;
    canTransfer.identifier = ID;
    canTransfer.data_low_reg = 0x00000000;
    canTransfer.data_high_reg = 0x00000000;
    canTransfer.control_reg = 0x0;
    CAN_InitMailboxRegisters( &canTransfer );
	return 1;
}


word mco_test( byte port )
{

   CANHSTR* pCANH_port;
   CANLSTR* pCANL_port;
   CANMSTR* pCANM_port;

   pCANL_port = (CANLSTR*)(0x100000 + port*0x200);
   pCANH_port = (CANHSTR*)(0x100010 + port*0x200);
   pCANM_port = (CANMSTR*)(0x10002C + port*0x200);

  if ( tst_can_stop(port) == 1 )
    {    // для возможности работы с CAN из монитора без рабочей программы.
      if ( can_reInit(port) == 0 )
      {
        can_reInit(port) = 1 ; // Для автоматического срабатывания переинициализации.
        pCANL_port->bvalr.word = 0; //все объекты сообщений отключены
        pCANL_port->rier.word = 0;
        pCANL_port->bvalr.word = 0;
        pCANH_port->csr.bit.HALT = 1;
      }
      return 1 ;
    }


                // Ошибки - CAN еще не отключился от шины.
    if ((pCANH_port->csr.word & _NS_status) == 0x0100 || (pCANH_port->csr.word & _NS_status) == 0x0200)
    {
         can_dd[port].Avar++ ;
    }

                // CAN отключился от шины - BOff
    if ((pCANH_port->csr.word & _NS_status) == 0x0300 )
    {
       MCO_Init(port);
       mSet_ServiceMsg( _Srv_ResCan ) ;

				  // После Аварии CAN возврат в рабочую программу
       return 2 ;
    }


// Отправка NMT
    if ((pCANL_port->treqr.word & (1 << MB_NMT_TX)) == (1 << MB_NMT_TX))
    {
      if ( (u)((w)(timer1-can_dd[port].time_out_send[MB_NMT_TX])) > _TimeOut_send )
      {
         pCANL_port->tcanr.word |= (1 << MB_NMT_TX);//сброс запроса передачи.
         can_dd[port].Error_send++ ;
      }
    }
// Отправка SDO
    if ((pCANL_port->treqr.word & (1 << MB_SDO_TX)) == (1 << MB_SDO_TX))
    {
      if ( (u)((w)(timer1-can_dd[port].time_out_send[MB_SDO_TX])) > _TimeOut_send )
      {
         pCANL_port->tcanr.word |= (1 << MB_SDO_TX);//сброс запроса передачи.
         can_dd[port].Error_send++ ;
      }
    }
// Отправка PDO
    if ((pCANL_port->treqr.word & (1 << MB_PDO_TX)) == (1 << MB_PDO_TX))
    {
      if ( (u)((w)(timer1-can_dd[port].time_out_send[MB_PDO_TX])) > _TimeOut_send )
      {
         pCANL_port->tcanr.word |= (1 << MB_PDO_TX);//сброс запроса передачи.
         can_dd[port].Error_send++ ;
      }
    }
// Отправка PDO21
    if ((pCANL_port->treqr.word & (1 << MB_PDO21_TX)) == (1 << MB_PDO21_TX))
    {
      if ( (u)((w)(timer1-can_dd[port].time_out_send[MB_PDO21_TX])) > _TimeOut_send )
      {
         pCANL_port->tcanr.word |= (1 << MB_PDO21_TX);//сброс запроса передачи.
         can_dd[port].Error_send++ ;
      }
    }
// Отправка PDO22
    if ((pCANL_port->treqr.word & (1 << MB_PDO22_TX)) == (1 << MB_PDO22_TX))
    {
      if ( (u)((w)(timer1-can_dd[port].time_out_send[MB_PDO22_TX])) > _TimeOut_send )
      {
         pCANL_port->tcanr.word |= (1 << MB_PDO22_TX);//сброс запроса передачи.
         can_dd[port].Error_send++ ;
      }
    }
// Отправка PDO23
    if ((pCANL_port->treqr.word & (1 << MB_PDO23_TX)) == (1 << MB_PDO23_TX))
    {
      if ( (u)((w)(timer1-can_dd[port].time_out_send[MB_PDO23_TX])) > _TimeOut_send )
      {
         pCANL_port->tcanr.word |= (1 << MB_PDO23_TX);//сброс запроса передачи.
         can_dd[port].Error_send++ ;
      }
    }
	return 0;
}

