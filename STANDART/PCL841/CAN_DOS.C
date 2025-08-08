
//      Переработанные и "усовершенствованные" функции аппаратных
//  драйверов "Advantech". По прототипам вызовов функции остались
//  полностью совместимы с "Advantech".
//      В компиляцию можно включать как эти драйверы так и драйверы
//  "Advantech" - и те и те работоспособны.
//
/*--------------------------------------------------------------------------*/
void  can_reset( BYTE port )
{

  BYTE huge *ptr=MK_FP(gSegment+0x200*port,0x100);
	BYTE a;

	a=*ptr;
	*ptr=a;
	delay(100);
}
/*--------------------------------------------------------------------------*/

void can0w(BYTE addr, BYTE v)
{
	BYTE huge *ptr;
  ptr = MK_FP( gSegment,addr);
	*ptr=v;
}
/*--------------------------------------------------------------------------*/
void can1w(BYTE addr, BYTE v)
{
	BYTE huge *ptr;
  ptr = MK_FP( gSegment,addr+0x200);
	*ptr=v;
}
/*--------------------------------------------------------------------------*/
BYTE can0r( BYTE addr)
{
  BYTE v;
  BYTE huge *ptr;
  ptr = MK_FP(gSegment,addr);
	v=*ptr;
	return(v);
}
/*--------------------------------------------------------------------------*/
BYTE can1r( BYTE addr)
{
  BYTE v;
  BYTE huge *ptr;
  ptr = MK_FP(gSegment,addr+0x200);
	v=*ptr;
	return(v);
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
int canReset( BYTE port )
{
  can_reset( port );
  return 0 ;
}
/*--------------------------------------------------------------------------*/

int  canConfig( BYTE port, CAN_STRUCT can)
{
  BYTE temp;
  canReset( port );
  if( port ==0)
  {
//    if( gIrq0 == IRQ_POLLING)
      can0w(0,1);
      //can0w(0,0x61);
  //  else
    // can0w(0,3);/* reset mode and receive irq */
  }
  else
  {
    //if( gIrq1 == IRQ_POLLING)
      can1w(0,1);
      //can1w(0,0x61);
    //else
    // can1w(0,3);/* reset mode and receive irq */
  }
  if( port ==0)
  {
     can0w(6,can.bt0); /* BT0 */
     can0w(7,can.bt1); /* BT1 */
     temp=can0r(6);
     if( temp !=can.bt0)
       return(0);
     temp=can0r(7);
     if( temp !=can.bt1)
       return(0);
  }
  else
  {
     can1w(6,can.bt0); /* BT0 */
     can1w(7,can.bt1); /* BT1 */
     temp=can1r(6);
     if( temp !=can.bt0)
       return(0);
     temp=can1r(7);
     if( temp !=can.bt1)
       return(0);
  }
   if( port ==0)
   {
     can0w(4,can.acc_code);/* accept code */
     can0w(5,can.acc_mask);/* accept code */
   }
   else
   {
     can1w(4,can.acc_code);/* accept code */
     can1w(5,can.acc_mask);/* accept code */
   }
   if( port ==0)
   {
  #ifdef CANBUS_Micro_PC
     can0w(8,0xde); //для CAN-BUS Micro PC
  #else
     can0w(8,0xfa);
  #endif

  #ifdef _4CAN
     can0w(31,0x40);
  #endif
   }
   else
   {
  #ifdef CANBUS_Micro_PC
     can1w(8,0xde); //для CAN-BUS Micro PC
  #else
     can1w(8,0xfa);
  #endif

  #ifdef _4CAN
     can1w(31,0x40);
  #endif
   }
  return(1);
}
/*--------------------------------------------------------------------------*/
int canInitHW( void ) //int canInitHW( UI segment, BYTE irq0, BYTE irq1)
{
  BYTE data;//, data2;
 // BYTE int_no;

  /*-----------------------
  If app. call this function again, error it.
  --------------------------*/
  /*-----------------------
  if( hw_ok!=0)
  {
    can_err_no=0x1;
    return(0);
  }
  -------------------------*/
  if( gSegment >0xdf00 || gSegment <0xc000 ||(gSegment%0x100))
  {
    //can_err_no=0x10;
    return(0);
  }
  //gSegment=segment;
  data=can0r(0);
  if( data &0x01)
  {
    can0w(0,0x60);
    if(can0r(0) &0x01)
    {
      //can_err_no=0x10;
      return(0);
    }
  }
  can_reset(0);
  if(!(can0r(0) &0x01))
  {
      //can_err_no=0x10;
      return(0);
  }
  //hw_ok=1;
  return(1);
}
/*--------------------------------------------------------------------------*/

//ююююююююююююююююююююююююююююююююююююю
//  Контроль отключения от шины CAN: '_ResetRequest'.
int  canNormalRun( BYTE port )
{
  byte al ;//, v ;
  static word reset = 0 ;
  word time ;
  time = 0 ;

  if ( port == PORT1 )
  {
    al = can0r(0) ;
    if ( (al & _ResetRequest) == 0 )  return( 1 );
    else
      {
        if ( reset++ > 25 )
          {
            reset = 0 ;
            //printf("\r\nCAN reset.");
          }

        can0w( 0, al & ~_ResetRequest );
        while ( (can0r(2) & _BusStatus) != 0 )
          {
            Sleep( 1.0 ) ;
            if ( time++ > 555 ) break;
          }
        return 0 ;
      }
  }
  else if ( port == PORT2 )
  {
    al = can1r(0) ;
    if ( (al & _ResetRequest) == 0 ) return 1 ;
    else
      {
        if ( reset++ > 25 )
          {
            reset = 0 ;
            //printf("\r\nCAN reset.");
          }

        can1w( 0, al & ~_ResetRequest );
        while ( (can1r(2) & _BusStatus) != 0 )
          {
            Sleep( 1.0 ) ;
            if ( time++ > 555 ) break;
          }
        return 0 ;
      }
  }
  return 1 ;
}


/*--------------------------------------------------------------------------*/
int  canReceiveMsg( BYTE port, MSG_STRUCT *msg_ptr)
{
BYTE i,/* v=0,*/ rBuf0[16], rBuf1[16];

   if( port ==0)
   {
     if( can0r(2)&1)
     {
       rBuf0[0]=can0r(20);
       rBuf0[1]=can0r(21);
       for(i=0; i< (rBuf0[1]&0x0f); i++)
         rBuf0[i+2]=can0r((BYTE)(22+i));
       /* release receive buffer*/
       can0w(1,0x04); //0x0c);

       msg_ptr->id=rBuf0[0];
       msg_ptr->id <<=3;
       msg_ptr->id |=(rBuf0[1] >>5);
       msg_ptr->rtr =(rBuf0[1]>>4)&1;
       msg_ptr->dlen =rBuf0[1]&0x0f;
       for(i=0;i< msg_ptr->dlen; i++)
         msg_ptr->data[i]=rBuf0[2+i];
       return( 1);
     }
     else  return( 0);
   }
   else if(port ==1)
   {
     if( can1r(2)&1)
     {
       rBuf1[0]=can1r(20);
       rBuf1[1]=can1r(21);
       for(i=0; i< ( rBuf1[1]&0x0f); i++)
         rBuf1[i+2]=can1r((BYTE)(22+i));
       /* release receive buffer*/
       can1w(1,0x04); //0x0c);

       msg_ptr->id=rBuf1[0];
       msg_ptr->id <<=3;
       msg_ptr->id |=(rBuf1[1] >>5);
       msg_ptr->rtr =(rBuf1[1]>>4)&1;
       msg_ptr->dlen =rBuf1[1]&0x0f;
       for(i=0;i< msg_ptr->dlen; i++)
         msg_ptr->data[i]=rBuf1[2+i];
       return( 1);
     }
     else  return( 0);
   }
   else  return( 0);
}
/*--------------------------------------------------------------------------*/
//ююююююююююююююююююююююююююююююююююююююююююююююююю

int canSendMsg( BYTE  port, MSG_STRUCT msg)
{
  BYTE v;
  BYTE i;
  static word time[2] ;

  if( port==0)
  {
       // проверка доступности буфера записи // и завершения выдачи.
    v=can0r(2); //  завершение выдачи проверять нельзя т.к. после строки
    //  "command 1" _TxCompleteStatus не взводится и все условие не выполняется.
    if ((v & (_TxBuffAccess /*| _TxCompleteStatus*/)) != (_TxBuffAccess /*| _TxCompleteStatus*/))
    {     // отсчет time_out.
      if ( time[port]++ > mTime_out( port ))
      {   // прерываем запись.
        can0w( 1, _AbortTx ); // "command 1".
        time[port] = 0 ;
      }
      return 0 ;
    }
    else time[port] = 0 ;

    v=msg.id>>3;
    can0w(10,v);
    v=msg.id &7;
    v<<=5;
    if( msg.rtr ==1)
      v|=0x10;
      v+=msg.dlen;
    can0w(11,v);
    for(i=0;i<msg.dlen; i++)
    {
      can0w((BYTE)(12+i),msg.data[i]);
    }
    can0w(1,_TxRequest);

    return 1 ;
  }
  else
  {
       // проверка доступности буфера записи и завершения выдачи.
    v=can1r(2);
    if ((v & (_TxBuffAccess /*| _TxCompleteStatus*/)) != (_TxBuffAccess /*| _TxCompleteStatus*/))
    {     // отсчет time_out.
      if ( time[port]++ > mTime_out( port ))
      {   // прерываем запись.
        can1w( 1, _AbortTx );
        time[port] = 0 ;
      }
      return 0 ;
    }
    else time[port] = 0 ;

    v=msg.id>>3;
    can1w(10,v);
    v=msg.id &7;
    v<<=5;
    if( msg.rtr ==1)
      v|=0x10;
      v+=msg.dlen;
    can1w(11,v);
    for(i=0;i<msg.dlen; i++)
    {
      can1w((BYTE)(12+i),msg.data[i]);
    }
    can1w(1,_TxRequest);

    return 1 ;
  }
}
/*--------------------------------------------------------------------------*/

