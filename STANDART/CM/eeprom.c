

/*-----------------31.01.2013 11:19-----------------
 * Инициализация памяти EEPROM
 * Рабочая частота EEPROM = 375 кГц
 * Количество страниц = 64 по 64 байта
 * --------------------------------------------------*/
void EEPROM_Init( void )
{
   lword val, cclk;

// EEPROM автоматически включена после сброса, нона всякий случай еще раз
// записываем бит включения = 0
	LPC_EEPROM->PWRDWN = 0x0;

	cclk = _EEPROMPClk;
	val = (cclk/375000)-1;
	LPC_EEPROM->CLKDIV = val;

// Вычисляются wait state
	val  = ((((cclk / 1000000) * 15) / 1000) + 1);
	val |= (((((cclk / 1000000) * 55) / 1000) + 1) << 8);
	val |= (((((cclk / 1000000) * 35) / 1000) + 1) << 16);
	LPC_EEPROM->WSTATE = val;
}

/*-----------------31.01.2013 11:21-----------------
 * Стирание страницы EEPROM
 * --------------------------------------------------*/
byte EEPROM_Erase( word page_address )
{
	lword i;
    lword count = EEPROM_PAGE_SIZE/4;
    word ax;

    LPC_EEPROM->INT_CLR_STATUS = ((1 << EEPROM_ENDOF_RW) | (1 << EEPROM_ENDOF_PROG));

	//clear page register
    LPC_EEPROM->ADDR = EEPROM_PAGE_OFFSET(0);
	LPC_EEPROM->CMD = EEPROM_CMD_32_BIT_WRITE;
	for ( i=0; i<count; i++ )
	{
		LPC_EEPROM->WDATA = 0;
        ax = Timer1_Ovr;
		while ( !((LPC_EEPROM->INT_STATUS >> EEPROM_ENDOF_RW) & 0x01) )
		{
             if ( (u)((w)(Timer1_Ovr-ax)) >= _Sec(5.0) )
			 {
                LPC_EEPROM->INT_CLR_STATUS = (1 << EEPROM_ENDOF_RW);
				return FALSE;
			 }
		}
		LPC_EEPROM->INT_CLR_STATUS = (1 << EEPROM_ENDOF_RW);
	}

    LPC_EEPROM->INT_CLR_STATUS = (0x1 << EEPROM_ENDOF_PROG);
	LPC_EEPROM->ADDR = EEPROM_PAGE_ADRESS(page_address);
	LPC_EEPROM->CMD = EEPROM_CMD_ERASE_PRG_PAGE;
    ax = Timer1_Ovr;
	while ( !((LPC_EEPROM->INT_STATUS >> EEPROM_ENDOF_PROG) & 0x01) )
	{
        if ( (u)((w)(Timer1_Ovr-ax)) >= _Sec(5.0) )
		{
           LPC_EEPROM->INT_CLR_STATUS = (1 << EEPROM_ENDOF_PROG);
		   return FALSE;
		}
	}
	LPC_EEPROM->INT_CLR_STATUS = (1 << EEPROM_ENDOF_PROG);
	return TRUE;
}

/*-----------------31.01.2013 13:22-----------------
 * Чтение count байт со страницы page_address, начиная с page_offset
 * Данные записываются в *data
 * --------------------------------------------------*/
byte EEPROM_Read( word page_offset, word page_address, void* data, TEEPROM_Mode mode, lword count)
{
    lword i;
	byte  *tmp8  = (byte  *)data;
	word  *tmp16 = (word  *)data;
	lword *tmp32 = (lword *)data;
    word ax;

	LPC_EEPROM->INT_CLR_STATUS = ((1 << EEPROM_ENDOF_RW) | (1 << EEPROM_ENDOF_PROG));
	LPC_EEPROM->ADDR = EEPROM_PAGE_ADRESS(page_address) | EEPROM_PAGE_OFFSET(page_offset);
	if ( mode == MODE_8_BIT )
		LPC_EEPROM->CMD = EEPROM_CMD_8_BIT_READ | EEPROM_CMD_RDPREFETCH;
	else
	  if ( mode == MODE_16_BIT )
	  {
		LPC_EEPROM->CMD = EEPROM_CMD_16_BIT_READ | EEPROM_CMD_RDPREFETCH;
		//check page_offset
		if ( (page_offset &0x01) != 0 )
			return FALSE;;
	  }
	  else
	  {
		LPC_EEPROM->CMD = EEPROM_CMD_32_BIT_READ | EEPROM_CMD_RDPREFETCH;
		//page_offset must be a multiple of 0x04
		if ( (page_offset & 0x03) != 0 )
			return FALSE;;
	}

	//read and store data in buffer
	for ( i=0; i<count; i++ )
	{
	   if ( mode == MODE_8_BIT )
	   {
		  *tmp8 = (byte)(LPC_EEPROM->RDATA);
		  tmp8++;
		  page_offset +=1;
	   }
	   else
	     if ( mode == MODE_16_BIT )
		 {
			 *tmp16 =  (word)(LPC_EEPROM->RDATA);
			 tmp16++;
			 page_offset +=2;
		 }
		 else
		 {
			 *tmp32 = (lword)(LPC_EEPROM->RDATA);
			 tmp32++;
			 page_offset +=4;
		 }
        ax = Timer1_Ovr;
		 while ( !( (LPC_EEPROM->INT_STATUS >> EEPROM_ENDOF_RW) & 0x01 ) )
		 {
            if ( (u)((w)(Timer1_Ovr-ax)) >= _Sec(5.0) )
			 {
                LPC_EEPROM->INT_CLR_STATUS = (1 << EEPROM_ENDOF_RW);
				return FALSE;
			 }
		 }
         LPC_EEPROM->INT_CLR_STATUS = (1 << EEPROM_ENDOF_RW);

		 if ( (page_offset >= EEPROM_PAGE_SIZE) && (i < count - 1) )
		 {
			page_offset = 0;
			page_address++;
			LPC_EEPROM->ADDR = EEPROM_PAGE_ADRESS(page_address) | EEPROM_PAGE_OFFSET(page_offset);
			if ( mode == MODE_8_BIT )
			 	LPC_EEPROM->CMD = EEPROM_CMD_8_BIT_READ | EEPROM_CMD_RDPREFETCH;
			else
			  if ( mode == MODE_16_BIT )
				LPC_EEPROM->CMD = EEPROM_CMD_16_BIT_READ | EEPROM_CMD_RDPREFETCH;
			  else
			 	LPC_EEPROM->CMD = EEPROM_CMD_32_BIT_READ | EEPROM_CMD_RDPREFETCH;
		 }
	}
	return TRUE;
}

/*-----------------31.01.2013 13:37-----------------
 * Запись count байт по адресу page_address со смещением page_offset
 * --------------------------------------------------*/
byte EEPROM_Write( word page_offset, word page_address, void* data, TEEPROM_Mode mode, lword count)
{
    lword i;
    byte *tmp8   = (byte *)data;
    word *tmp16  = (word *)data;
    lword *tmp32 = (lword *)data;
    word ax;

	LPC_EEPROM->INT_CLR_STATUS = ((1 << EEPROM_ENDOF_RW) | (1 << EEPROM_ENDOF_PROG));
	//check page_offset
	if ( mode == MODE_16_BIT )
	{
		if ( (page_offset & 0x01) != 0 ) return FALSE;
	}
	else
	   if ( mode == MODE_32_BIT )
	   {
	 	  if ( (page_offset & 0x03) != 0 ) return FALSE;
	   }
	LPC_EEPROM->ADDR = EEPROM_PAGE_OFFSET( page_offset );
	for ( i=0; i<count; i++ )
	{
		//update data to page register
		if ( mode == MODE_8_BIT )
		{
		   LPC_EEPROM->CMD = EEPROM_CMD_8_BIT_WRITE;
		   LPC_EEPROM -> WDATA = *tmp8;
		   tmp8++;
		   page_offset +=1;
		}
		else
		   if ( mode == MODE_16_BIT )
		   {
			  LPC_EEPROM->CMD = EEPROM_CMD_16_BIT_WRITE;
			  LPC_EEPROM -> WDATA = *tmp16;
			  tmp16++;
			  page_offset +=2;
		   }
		   else
		   {
			  LPC_EEPROM->CMD = EEPROM_CMD_32_BIT_WRITE;
			  LPC_EEPROM -> WDATA = *tmp32;
			  tmp32++;
			  page_offset +=4;
		   }
        ax = Timer1_Ovr;
		while ( !((LPC_EEPROM->INT_STATUS >> EEPROM_ENDOF_RW) & 0x01 ) )
		{
            if ( (u)((w)(Timer1_Ovr-ax)) >= _Sec(5.0) )
			 {
                LPC_EEPROM->INT_CLR_STATUS = (1 << EEPROM_ENDOF_RW);
				return FALSE;
			 }
		}
		LPC_EEPROM->INT_CLR_STATUS = (1 << EEPROM_ENDOF_RW);
		if ( (page_offset >= EEPROM_PAGE_SIZE) | (i == count-1) )
		{
			//update to EEPROM memory
		   LPC_EEPROM->INT_CLR_STATUS = (0x1 << EEPROM_ENDOF_PROG);
		   LPC_EEPROM->ADDR = EEPROM_PAGE_ADRESS(page_address);
		   LPC_EEPROM->CMD = EEPROM_CMD_ERASE_PRG_PAGE;
            ax = Timer1_Ovr;
		   while ( !( (LPC_EEPROM->INT_STATUS >> EEPROM_ENDOF_PROG) & 0x01 ) )
		   {
            if ( (u)((w)(Timer1_Ovr-ax)) >= _Sec(5.0) )
			 {
                LPC_EEPROM->INT_CLR_STATUS = (1 << EEPROM_ENDOF_PROG);
				return FALSE;
			 }
		   }
		   LPC_EEPROM->INT_CLR_STATUS = (1 << EEPROM_ENDOF_PROG);
		}
		if ( page_offset >= EEPROM_PAGE_SIZE )
		{
		   page_offset = 0;
		   page_address +=1;
		   LPC_EEPROM->ADDR =0;
		   if ( page_address > EEPROM_PAGE_NUM - 1) page_address = 0;
		}
	}
	return TRUE;
}


