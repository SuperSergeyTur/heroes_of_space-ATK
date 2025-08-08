

#ifndef _CM3_
/*-----------------30.08.2010 15:23-----------------
 *   Подпрограмма инициализации сетей.
 * Определение типа сетевой платы и инициализация
 * необходимых переменных
 * --------------------------------------------------*/
void Init_Net( void )
{
  word bTypeNet;
  byte ah ;
  word i, copy ;
  lword ptr;
  int ii;
    copy = Pult_Prog_Addr ;

Speed_Pult () ;

   CSE = CSE & 0xF7;
   ASR3 = 0x30;
   AMR3 = 0x00;
   AMD3 = 0x01;      // Area Mode reg AMD3 -> 16-Bit Bus, 1 wait state
   CSE = CSE | 0x08; // включить CS3

   mSetNetReset();          
   for ( i=0; i<65000; i++)//300  // RESET min=1ms!!!
   {
   }
   mClrNetReset();
   for ( ii=0; ii<650000; ii++)//30 Инициализация наездника не менее 10мс!!!
   {
   }

   bTypeNet = *(b*)((lw) (AddrNet+5));
   if ( bTypeNet == 0xFF) // Сетевая плата не Profibus
   {                    // переинициализируем CS3
	  ah = CSE;
	  CSE = 0;
	  ptr = 0x487;
	  *(b*)ptr = 0x30;
	  for ( i=0; i<30; i++ )
	  {
	  }
      CSE = ah & 0xF7;
//	CSE &= 0xF7;
      ASR3 = 0x30;
      AMR3 = 0x00;
      AMD3 = 0x2D;      // Area Mode reg AMD3 -> 16-Bit Bus, 7 wait state, ready-pin
      CSE = CSE | 0x08; // включить CS3
      mSetNetReset();

   for ( i=0; i<65000; i++)//300
   {
   }
   mClrNetReset();
   for ( ii=0; ii<650000; ii++)//30 Инициализация наездника не менее 10мс!!!
   {
   }      
 /*
   mClrNetReset();          // RESET
   for ( i=0; i<300; i++)
   {
   }
   mSetNetReset();
 /*     for ( i=0; i<30; i++)
      {
      }
   */
      bTypeNet= *(w*)((lw) DR_CHIPID);
      switch ( bTypeNet )
      {
        case 0x0008 :
            // КВВ 2-04-14 output_s( _Net_ModbusRTU_ ) ;
            // КВВ 2-04-14 while ( !TestCompleted_Output() )  ;
            TypeNet = _ModbusRTU_ ;
            NetUstav   = &NetUstav3[0] ;
            Netbts     = &Netbts2[0] ;
            NetIndicat = &NetIndicat2[0] ;
            NetNumUstav = sizeof(NetUstav3) /sizeof(struct UstUzm) ;
            NetNumBUst  = sizeof(Netbts2) /sizeof(struct Bits) ;
            NetNumInd   = sizeof(NetIndicat2) /sizeof(struct Ind) ;
//			Init_RTU();
            break;
        case 0x0009 :
            // КВВ 2-04-14 output_s( _Net_ModbusTCPIP_ ) ;
            // КВВ 2-04-14 while ( !TestCompleted_Output() )  ;
            TypeNet = _ModbusTCPIP_ ;
            NetUstav   = &NetUstav2[0] ;
            Netbts     = &Netbts1[0] ;
            NetIndicat = &NetIndicat2[0] ;
            NetNumUstav = sizeof(NetUstav2) /sizeof(struct UstUzm) ;
            NetNumBUst  = sizeof(Netbts1) /sizeof(struct Bits) ;
            NetNumInd   = sizeof(NetIndicat2) /sizeof(struct Ind) ;
			Init_TCPIP();
            break;
        case 0x000A :
            // КВВ 2-04-14 output_s( _Net_CANopen_ ) ;
            // КВВ 2-04-14 while ( !TestCompleted_Output() )  ;
            TypeNet = _CANopen_ ;
//            NetUstav   = &NetUstav2[0] ;
//            Netbts     = &Netbts1[0] ;
//            NetIndicat = &NetIndicat2[0] ;
//            NetNumUstav = sizeof(NetUstav) /sizeof(struct UstUzm) ;
//            NetNumBUst  = sizeof(Netbts) /sizeof(struct Bits) ;
//            NetNumInd   = sizeof(NetIndicat) /sizeof(struct Ind) ;
//			Init_CANopen();
            break;
        case 0x000B :
            // КВВ 2-04-14 output_s( _Net_RS485FD_ ) ;
            // КВВ 2-04-14 while ( !TestCompleted_Output() )  ;
            TypeNet = _RS485FD_ ;
            NetUstav   = &NetUstav4[0] ;
            Netbts     = &Netbts2[0] ;
            NetIndicat = &NetIndicat3[0] ;
            NetNumUstav = sizeof(NetUstav4) /sizeof(struct UstUzm) ;
            NetNumBUst  = sizeof(Netbts2) /sizeof(struct Bits) ;
            NetNumInd   = sizeof(NetIndicat3) /sizeof(struct Ind) ;
			Init_RS();
            break;
        default:
            // КВВ 2-04-14 output_s( _Net_NotDefine_ ) ;
            // КВВ 2-04-14 while ( !TestCompleted_Output() )  ;
            TypeNet = _NotDefined_ ;

            break;
      }
   }
   else
   {

      switch ( bTypeNet >> 4 )
      {
        case 0 :
        case 0x0B :
        case 0X0C :
        case 0x0D :
            // КВВ 2-04-14 output_s( _Net_ProfibusDP_ ) ;
            // КВВ 2-04-14 while ( !TestCompleted_Output() )  ;
            TypeNet = _ProfibusDP_ ;
            NetUstav   = &NetUstav1[0] ;
            Netbts     = &Netbts1[0] ;
            NetIndicat = &NetIndicat1[0] ;
            NetNumUstav = sizeof(NetUstav1) /sizeof(struct UstUzm) ;
            NetNumBUst  = sizeof(Netbts1) /sizeof(struct Bits) ;
            NetNumInd   = sizeof(NetIndicat1) /sizeof(struct Ind) ;
            Init_DP() ;
            break;
        default:
            // КВВ 2-04-14 output_s( _Net_NotDefine_ ) ;
            // КВВ 2-04-14 while ( !TestCompleted_Output() )  ;
            TypeNet = _NotDefined_ ;
            break;

      }

   }
        //  КВВ 2-04-14 Выводим сообщения после или по ходу загрузки процессора, или после входа в работу для ускорения загрузки.
#ifndef _Quick_Start
    Init_Net_Msg() ;
    while ( !TestCompleted_Output() )  ;
#endif

flag_net = _FLAGNET_NO ;
Speed_Pult () ;

//17-12-13 Vit - перебивает задаваемое в СВСК "А0-..." Pult_Prog_Addr = _Case ( 'A' , '1' ) ,   M_FirstCall = 1 ;
    Pult_Prog_Addr = copy ,   M_FirstCall = 1 ;

}

void Init_Net_Msg( void )
{
      switch ( TypeNet )
      {
        case _ModbusRTU_ :
            output_s( _Net_ModbusRTU_ ) ;
            break;
        case _ModbusTCPIP_ :
            output_s( _Net_ModbusTCPIP_ ) ;
            break;
        case _CANopen_ :
            output_s( _Net_CANopen_ ) ;
            break;
        case _RS485FD_ :
            output_s( _Net_RS485FD_ ) ;
            break;
        case _ProfibusDP_ :
            output_s( _Net_ProfibusDP_ ) ;
            break;
        case _NotDefined_ :
            output_s( _Net_NotDefine_ ) ;
            break;
      }

    return ;
}
/*-----------------30.08.2010 15:24-----------------
 *  Подпрограмма обработки сетевых данных
 * --------------------------------------------------*/
word  Work_Net( byte flag )
{
	word err = 0;

  switch ( TypeNet )
  {
	case _ProfibusDP_ :
		Work_DP();
		break;
	case _ModbusTCPIP_ :
        Work_TCPIP();
		break;
	case _ModbusRTU_ :
//		Work_RTU();
		break;
	case _CANopen_ :
//		Work_CANopen();
		break;
	case _RS485FD_ :
        err = Work_RS( flag );
		break;
	default:
		break;
  }
  return err;
}


/*-----------------30.08.2010 15:27-----------------
 *  Обработчик прерывания для платы-наездника
 * --------------------------------------------------*/
void RIDER_driver( void )
{
  word  ax, bx ;

   READ_NET( ax, DR_ISR ) ;
   bx = 0 ;

   if ( (ax & DR_ISR_SF ) != 0 )
   {
      bx |= DR_ISR_SF ;
   }

   if ( (ax & DR_ISR_LT ) != 0 )
   {
      bx |= DR_ISR_LT ;
   }

   if ( (ax & DR_ISR_ND ) != 0 )
   {
      flag_newdata = 1 ;
      bx |= DR_ISR_ND ;
   }
   WRITE_NET( DR_IAR, bx ) ;
}


//----------------------------------
// Обработка прерывания по сети
//----------------------------------
__interrupt void Net_Interrupt (void)
{

  switch ( TypeNet )
  {
    case _ProfibusDP_ :
        DP_driver() ;
        _Mode_Reg_S = EOI;
        break;
    case _ModbusTCPIP_ :
        RIDER_driver();
        WRITE_NET( DR_CR, DR_CR_EOI );
        break;
    case _ModbusRTU_ :
        RIDER_driver();
        WRITE_NET( DR_CR, DR_CR_EOI );
        break;
    case _CANopen_ :
//      CAN_driver();
        break;
    case _RS485FD_ :
        RIDER_driver();
        WRITE_NET( DR_CR, DR_CR_EOI );
        break;
    default:
        WRITE_NET( DR_CR, DR_CR_EOI );
        break;
  }
  EIRR_ER1 = 0;

}

#else // _CM3_

TECRRegs* NetRam = (TECRRegs*)0x98000000;

void NET_Reset( void )
{
  word  i;
  

//#ifndef  _ETHERNET // Для PROFIBUS-DP :
  if (TypeNet == _ProfibusDP_)  
  {
  LPC_GPIO1->SET  = _DP_RESET;
    for ( i=0; i<500; i++)
    {
    }
  LPC_GPIO1->CLR  = _DP_RESET;
  }
  else              // Для MODBUS TCP :
  {
    LPC_GPIO1->CLR  = _DP_RESET;
    for ( i=0; i<65000; i++)//500 // RESET min=1ms!!!
    {
    }

    LPC_GPIO1->SET  = _DP_RESET;
    
    //выдержка на инициализацию наездника
    i = Timer1_Ovr;
    while ((u)((w)(Timer1_Ovr - i))< _Sec(0.5) );    
    
  }

}


/*-----------------30.08.2010 15:23-----------------
 *   Подпрограмма инициализации сетей.
 * Определение типа сетевой платы и инициализация
 * необходимых переменных
 * --------------------------------------------------*/
void Init_Net( void )
{
  word bTypeNet[3] = {0xff,0xff,0xff};
  word i, ax = 0;
  byte *ad_tst;
  
  ad_tst = (b*)NetRam;
  ad_tst += 4;
    Speed_Pult () ;
    ax = 0;
  *ad_tst = 0x1f;    
 // LPC_EMC->StaticConfig2 = 0x81;
    
  while ( ax == 0)
  {    
//     for ( i=0; i<500; i++)//500  Инициализация наездника не менее 10мс!!!
//    {
//    }
  //Samon NET_Reset();
    //выдержка на инициализацию наездника
  //Samon     i = Timer1_Ovr;
  //Samon     while ((u)((w)(Timer1_Ovr - i))< _Sec(0.5) );
    //Делаем три считывания идентификатора, если считываются разные значения - сеть не
    // определена, надо либо перенастраивать шину, либо писать что сети нет, 
    //т.е в последнем считывании ставим 0xff
   bTypeNet[0] = *(ad_tst+1)>>4;//NetRam->BoardID;//*(b*)((lw)(_EMC_CS2_BEGIN + 5));   
    for ( i=0; i<500; i++)
     {
    }
    
   bTypeNet[1] = *(ad_tst+1)>>4;//NetRam->BoardID;//*(b*)((lw)(_EMC_CS2_BEGIN + 5));
   if (bTypeNet[1] != bTypeNet[0])
   {
     bTypeNet[2] = 0xff;
   }
   else
   {
     
    for ( i=0; i<500; i++)
    {
    }
    bTypeNet[2] = *(ad_tst+1)>>4;//NetRam->BoardID;//*(b*)((lw)(_EMC_CS2_BEGIN + 5));
    if (bTypeNet[2] != bTypeNet[1])
    {
      bTypeNet[2] = 0x0f;
    }
   }
   
   if (((bTypeNet[2] == 0  )||(bTypeNet[2] == 0xb)
      ||(bTypeNet[2] == 0xc)||(bTypeNet[2] == 0xd))
      && LPC_EMC->StaticConfig2 == 0x81)
     {
        bTypeNet[2] = 0x0f;
     }
   
   ax =1;
   //Определяем по последнему считыванию
      switch ( bTypeNet[2] )
      {
        case 0 :
        case 0x0B :
        case 0X0C :
        case 0x0D :
           
            output_s( _Net_ProfibusDP_ ) ;
            while ( !TestCompleted_Output() )  ;
            TypeNet = _ProfibusDP_ ;
            NET_Reset();
            //выдержка на инициализацию наездника
            i = Timer1_Ovr;
            while ((u)((w)(Timer1_Ovr - i))< _Sec(0.5) );
            NetUstav   = &NetUstav1[0] ;
            Netbts     = &Netbts1[0] ;
            NetIndicat = &NetIndicat1[0] ;
            NetNumUstav = sizeof(NetUstav1) /sizeof(struct UstUzm) ;
            NetNumBUst  = sizeof(Netbts1) /sizeof(struct Bits) ;
            NetNumInd   = sizeof(NetIndicat1) /sizeof(struct Ind) ;
            Init_DP() ;
            break;
        case 0x08 :
            
            output_s( _Net_ModbusRTU_ ) ;
            while ( !TestCompleted_Output() )  ;
            TypeNet = _ModbusRTU_ ;
            NET_Reset();
            //выдержка на инициализацию наездника
            i = Timer1_Ovr;
            while ((u)((w)(Timer1_Ovr - i))< _Sec(0.5) );
           
            output_s( _Net_ProfibusDP_ ) ;
            while ( !TestCompleted_Output() )  ;
            NetUstav   = &NetUstav3[0] ;
            
            Netbts     = &Netbts2[0] ;
            NetIndicat = &NetIndicat2[0] ;
            NetNumUstav = sizeof(NetUstav3) /sizeof(struct UstUzm) ;
            NetNumBUst  = sizeof(Netbts2) /sizeof(struct Bits) ;
            NetNumInd   = sizeof(NetIndicat2) /sizeof(struct Ind) ;
//          Init_RTU();
            break;
        case 0x09 :
           
            output_s( _Net_ModbusTCPIP_ ) ;
             
            while ( !TestCompleted_Output() )  ;
            TypeNet     = _ModbusTCPIP_ ;
            NET_Reset();// Samon -  Было закоментировано
           
            NetUstav    = &NetUstav2[0] ;
            
            Netbts      = &Netbts1[0] ;
            NetIndicat  = &NetIndicat2[0] ;
            NetNumUstav = sizeof(NetUstav2) /sizeof(struct UstUzm) ;
            NetNumBUst  = sizeof(Netbts1) /sizeof(struct Bits) ;
            NetNumInd   = sizeof(NetIndicat2) /sizeof(struct Ind) ;

            Init_TCPIP();
            
            break;
        case 0x0A :
           
            output_s( _Net_CANopen_ ) ;
            while ( !TestCompleted_Output() )  ;
            TypeNet = _CANopen_ ;
            NET_Reset();
            //выдержка на инициализацию наездника
            i = Timer1_Ovr;
            while ((u)((w)(Timer1_Ovr - i))< _Sec(0.5) );
           
            output_s( _Net_ProfibusDP_ ) ;
            while ( !TestCompleted_Output() )  ;
//            NetUstav   = &NetUstav2[0] ;
//            Netbts     = &Netbts1[0] ;
//            NetIndicat = &NetIndicat2[0] ;
//            NetNumUstav = sizeof(NetUstav) /sizeof(struct UstUzm) ;
//            NetNumBUst  = sizeof(Netbts) /sizeof(struct Bits) ;
//            NetNumInd   = sizeof(NetIndicat) /sizeof(struct Ind) ;
//          Init_CANopen();
            break;
        case 0x07 :
            output_s( _Net_RS485FD_ ) ;
            while ( !TestCompleted_Output() )  ;
            TypeNet = _RS485FD_ ;
            NET_Reset();
            //выдержка на инициализацию наездника
            i = Timer1_Ovr;
            while ((u)((w)(Timer1_Ovr - i))< _Sec(0.5) );
           
            output_s( _Net_ProfibusDP_ ) ;
            while ( !TestCompleted_Output() )  ;
            NetUstav   = &NetUstav4[0] ;
            Netbts     = &Netbts2[0] ;
            NetIndicat = &NetIndicat3[0] ;
            NetNumUstav = sizeof(NetUstav4) /sizeof(struct UstUzm) ;
            NetNumBUst  = sizeof(Netbts2) /sizeof(struct Bits) ;
            NetNumInd   = sizeof(NetIndicat3) /sizeof(struct Ind) ;
            Init_RS();
            break;
        default:
            if (LPC_EMC->StaticConfig2 == 0x80)
            {
               ax = 0;
               LPC_EMC->StaticConfig2 = 0x81;
               NET_Reset(); //Samon
            }
            else
            {
              output_s( _Net_NotDefine_ ) ;
               while ( !TestCompleted_Output() )  ;
               TypeNet = _NotDefined_ ;
            }
            break;

      }
  }


flag_net = _FLAGNET_NO ;
Speed_Pult () ;
Pult_Prog_Addr = _Case ( 'A' , '1' ) ,   M_FirstCall = 1 ;

}

/*-----------------30.08.2010 15:24-----------------
 *  Подпрограмма обработки сетевых данных
 * --------------------------------------------------*/
word  Work_Net( byte flag )
{
    word err = 0;

  switch ( TypeNet )
  {
    case _ProfibusDP_ :
        Work_DP();
        break;
    case _ModbusTCPIP_ :
        Work_TCPIP();
        break;
    case _ModbusRTU_ :
//      Work_RTU();
        break;
    case _CANopen_ :
//      Work_CANopen();
        break;
    case _RS485FD_ :
//        err = Work_RS( flag );
        break;
    default:
        break;
  }
  return err;
}


/*-----------------30.08.2010 15:27-----------------
 *  Обработчик прерывания для платы-наездника
 * --------------------------------------------------*/
//------------------------------
// Функция заглушка (временная)
//------------------------------
void RIDER_driver()
{

}


//----------------------------------
// Обработка прерывания по сети
//----------------------------------
extern "C" {

void  EINT2_IRQHandler( void )
{
  switch ( TypeNet )
  {
    case _ProfibusDP_ :
        DP_driver ();
        break;
    case _ModbusTCPIP_ :
        RIDER_driver();
        break;
    case _ModbusRTU_ :
        RIDER_driver();
        break;
    case _CANopen_ :
        break;
    case _RS485FD_ :
        RIDER_driver();
        break;
    default:
        break;
  }
  LPC_SC->EXTINT |= 0x04;

}
}//extern "C"
void Init_Net_Msg( void )
{
      switch ( TypeNet )
      {
        case _ModbusRTU_ :
            output_s( _Net_ModbusRTU_ ) ;
            break;
        case _ModbusTCPIP_ :
            output_s( _Net_ModbusTCPIP_ ) ;
            break;
        case _CANopen_ :
            output_s( _Net_CANopen_ ) ;
            break;
        case _RS485FD_ :
            output_s( _Net_RS485FD_ ) ;
            break;
        case _ProfibusDP_ :
            output_s( _Net_ProfibusDP_ ) ;
            break;
        case _NotDefined_ :
            output_s( _Net_NotDefine_ ) ;
            break;
      }

    return ;
}

#endif // _CM3_
