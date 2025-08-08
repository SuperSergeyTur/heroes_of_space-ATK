#include "mb.h"
#include "mb_rtu.h"

void MBRTU_Init( void )
{
        RS485_Init();
	flag_rs485 = 0;
	newFrame = 1;
        FrameCount = 0;   //SAP - number string table frame

	__BUF_RESET(RSBuf.tx_head);
	__BUF_RESET(RSBuf.tx_tail);
	__BUF_RESET(RSBuf.rx_head);
	__BUF_RESET(RSBuf.rx_tail);
}

//------------Modbus RTU Slave--------------------------------
word MBRTU_Slave( void )
{
   byte i;
   word crc, crcCalc, Len;
   static byte Frame[_RING_BUFSIZE];
   static word time_Tx, time_TxMax;

#ifdef _DMA_RS485_
    // ��������� ���������� �� ����� �� UART ������ ����� �������� ������ �� DMA ���
    // ����, ���-�� ����� �� ��� � DMA ������������ �� �������
   if ((RS485_DMA_CH_TC != 0) || (RS485_DMA_CH_ERR != 0) ||
     (((LPC_UART2->RS485CTRL & UART_RS485CTRL_RX_DIS) != 0 ) && ((u)((w)(timer1 - time_Tx)) > time_TxMax)) )
   {// ���� ����� �� ������� �������� ���������� �� DMA
     if (( RS485_DMA_CH_TC == 0 ) && (RS485_DMA_CH_ERR == 0))  RS485_DMA_Disable ();
     RS485_DMA_CH_TC = 0; RS485_DMA_CH_ERR = 0 ;
     LPC_UART2->RS485CTRL &= ~(UART_RS485CTRL_RX_DIS) ;
   }
#endif

// ����� ���������� - Timer_rs
 if ((u)((w)(timer1 - Timer_rs)) < Time_rs_frame) //&& (newbyte == 1)) 08.05.18 - ���� ���� ���� ���� ��� ������. UART, ����� �������� �������� ������������ �������
 {
   newFrame = 0;
   newbyte = 0;
 }
 else
 {
   newFrame = 1;
   if ( flag_rs485 == 1) // if ( pUsart->Frame == 1 )   ?????
   {
     flag_rs485 = 0;     //  pUsart->Frame = 0 ;        ?????
     Len = 0;
     //------------------------------------------------------------------
     NVIC_DisableIRQ( UART2_IRQn );
     while ( !( __BUF_IS_EMPTY(RSBuf.rx_head, RSBuf.rx_tail)))
     {
       Frame[Len++] = RSBuf.rx[RSBuf.rx_tail++];
     }
     RS485_ResetBuffer();
     NVIC_EnableIRQ( UART2_IRQn );
     if (( Len < 3 ) || (Len > _RING_BUFSIZE))
     {
       return 1;
     }
// check CRC
     crc = (word)Frame[Len-2] + (((word)Frame[Len-1]) << 8);
     Len -= 2;
     crcCalc = CRC16( Frame, Len );
     if ( crcCalc == crc )
     {
       request.func = Frame[1];
       Len -= 2;
       for ( i = 0; i < Len; i++ )
       {
	 request.data[i] = (word)Frame[i+2];
       }
     }
     else
     {
       return 2;
     }
     Len = modbus_slave( &request, &answer );
     Frame[0] = _r.rs485.addr;
     Frame[1] = answer.func;
     for ( i = 0; i < Len; i++ )
     {
       Frame[i+2]  = (byte)answer.data[i];
     }
     Len += 2;
// create CRC
     crc = CRC16( Frame, Len );
     Frame[Len++] = (byte)(crc & 0x00FF);
     Frame[Len++] = (byte)((crc >> 8) & 0x00FF);
     RS485_Send( Frame, Len ) ;
     // ������������ ���������� ����� �� ��������. �.�. ���� �� ���������� �������� ������ ������ �� �����.
     time_TxMax = (w)(( (lw)Time_rs_frame * ( (lw)Len & 0xfful )) / 3ul) + _MkSec( 10000 ) ;
     time_Tx = timer1 ;
     return 0;
   }
 }
 return 0;
}
//-------------------------------------------------------------

#ifdef _ModbusMaster
//------------Modbus RTU Master--------------------------------
word MBRTU_Master( void )
{
   byte i;
   word crc, crcCalc, Len;
   static byte Frame[_RING_BUFSIZE];
   static word time_Tx, time_TxMax;

   word counter = 0;
   static lword TimerFrame = 0;

  #ifdef _DMA_RS485_
    // ��������� ���������� �� ����� �� UART ������ ����� �������� ������ �� DMA ���
    // ����, ���-�� ����� �� ��� � DMA ������������ �� �������
 if ((RS485_DMA_CH_TC != 0) || (RS485_DMA_CH_ERR != 0) ||
     (((LPC_UART2->RS485CTRL & UART_RS485CTRL_RX_DIS) != 0 ) && ((u)((w)(timer1 - time_Tx)) > time_TxMax)) )
  {  // ���� ����� �� ������� �������� ���������� �� DMA
   if (( RS485_DMA_CH_TC == 0 ) && (RS485_DMA_CH_ERR == 0))  RS485_DMA_Disable ();

   RS485_DMA_CH_TC = 0; RS485_DMA_CH_ERR = 0 ;
   LPC_UART2->RS485CTRL &= ~(UART_RS485CTRL_RX_DIS) ;
  }
#endif

  while ( counter < NumFrames )                      // ������� ����������� ������
  {
//-------------------------- request-----------------------------------------------
    if ( flag_busy == 0 )                            // ���� ��� �������� �������
    {
      if ( *SetMBFrame[FrameCount].TimeCycle != 0 )   // 0 = �� ������� -   ????????????????????
      {
       // if ( (timer1 - TimerFrame) >= 50 )           // ����������� ����� ����� ������ � ����� ��������. 50 �����
       // {
          //if ( (timer1 - SetMBFrame[FrameCount].CurTime) >= SetMBFrame[FrameCount].TimeCycle )// ����� ����� ��������� �������� ������ � ����� ����� ������� ���� ����������� ��� �������
          if ( (w)(u)(Timer1_Ovr-SetMBFrame[FrameCount].CurTime) >= *SetMBFrame[FrameCount].TimeCycle )
          { // CurTime - ��������� ����� � ���� �����. � ������ ����� �� ���������
            // TimeCycle - 3,5 char. �������� ������� (���������� ����������): $master\_silence$ = 28 bit / $V_{uart}$
            TimerFrame = timer1;
  	    // �������� ����� ������ � ��������� ������� ��� ����������
            Len = modbusMasterSend( FrameCount, &request);
         //--------------------------------
//----------------������� ����� ---------------------------------------
           //������ �������� (��������)
           Frame[0] = _r.rs485.addr;
	   //������� ��� ������
           Frame[1] = request.func;
           //���������� ����� ��������� ������
           for ( i = 0; i < Len; i++ )
	   {
	     Frame[i+2]  = (byte)request.data[i];
	   }
	   Len += 2;
// ---------------create CRC-------------------------------------------
           crc = CRC16( Frame, Len );
	   Frame[Len++] = (byte)(crc & 0x00FF);
     	   Frame[Len++] = (byte)((crc >> 8) & 0x00FF);
//---------------------  SEND------------------------------------------
           //³������� ������
           RS485_Send( Frame, Len ) ;
           // ������������ ���������� ����� �� ��������. �.�. ���� �� ���������� �������� ������ ������ �� �����.
           time_TxMax = (w)(( (lw)Time_rs_frame * ( (lw)Len & 0xfful )) / 3ul) + _MkSec( 10000 ) ;
           time_Tx = timer1 ;
           flag_busy = 1;
//------------------   SEND -------------------------------------------
	   SetMBFrame[FrameCount].CurTime = Timer1_Ovr;
           TimeWait = Timer1_fSec;
           return 0;
         }
       //}
     }
     FrameCount++; // ����� ������
     counter++;    // ��������
     if ( FrameCount >= NumFrames )  FrameCount = 0; // ������� � ������� ���� ������� ������
   }
   else  // flag_busy = 1 - ������� ����� �� ������
   {
//--------------------------------answer----------------------------------------
     // ����� ���������� - Timer_rs
     if ((u)((w)(timer1 - Timer_rs)) < Time_rs_frame) //&& (newbyte == 1)) 08.05.18 - ���� ���� ���� ���� ��� ������. UART, ����� �������� �������� ������������ �������
     {
       newFrame = 0;
       newbyte = 0;
     }
     else
     {
       newFrame = 1;
       if ( flag_rs485 == 1)
       {
         flag_rs485 = 0;
         Len = 0;
         //------------------------------------------------------------------
         NVIC_DisableIRQ( UART2_IRQn );
         while ( !( __BUF_IS_EMPTY(RSBuf.rx_head, RSBuf.rx_tail)))
         {
           Frame[Len++] = RSBuf.rx[RSBuf.rx_tail++];
         }
         RS485_ResetBuffer();
         NVIC_EnableIRQ( UART2_IRQn );
         if (( Len < 3 ) || (Len > _RING_BUFSIZE))
         {
           return 1;
         }
         // check CRC
         crc = (word)Frame[Len-2] + (((word)Frame[Len-1]) << 8);
         Len -= 2;
         crcCalc = CRC16( Frame, Len );
         if ( crcCalc == crc )
         {
           answer.func = Frame[1];
           Len -= 2;
           for ( i = 0; i < Len; i++ )
           {
             answer.data[i] = (word)Frame[i+2];
           }
         }
         else
         {
           return 2;
         }
        //----------------------------------------------------------------------
        // �������� ����� ������ � ��������� ������ ��� ����������
         Len = modbusMasterReceive( FrameCount, &answer);
         //FrameCount++; ������������� ����� � ��������, ����� ���������� ����� ����. ������ ��� ���� ������ ���������
         //��� � �������� ����������.
         if ( FrameCount >= NumFrames )  FrameCount = 0;
         TimerFrame = timer1;
         //flag_busy = 0;       //��������� ��������� ������� �������� ������ ����� ��������� ����
         //SetMBFrame[FrameCount].CurTime = timer1; // ����� ����� ��������.
	 return 0 ;
       }
       else
       {
         //����� �������� ������ ���� ����� ��� ��������� ������
         if  ( (u)((w)(Timer1_fSec-TimeWait)) > _r.time_read ) // ���� ��� ������� - ������ ������� ��������
	 {
	   flag_busy = 0;       //��������� ��������� ������� ��������, ���� �� ������ �����
           TimerFrame = timer1;
	   FrameCount++;        //������������� �����
           if ( FrameCount >= NumFrames )  FrameCount = 0;
           //SetMBFrame[FrameCount].CurTime = timer1; // ����� ����� ��������.
	   return 0  ;
	 }
	 else
	 {
	   return 0;
	 }
       }
     }
   }
 }
 return 0;
}
#endif     // _ModbusMaster

//-------------------------------------------------------------------

void MBRTU_Background( void )
{
  static word countErr;
   if ( _r.rs485.config._.vkl == 1 )
   {
     if ( state_rs == _RS_BUSOFF )
     {
       MBRTU_Init();
     }
     if ( _r.rs485.config._.master == 1 )
     {
#ifdef _ModbusMaster
       if ( MBRTU_Master() )
       {
         if ( countErr++ >2 )
         {
#ifdef _Srv2_Modbus
	   mSet_ServiceMsg2( _Srv2_Modbus );
#elif  _Srv_Modbus
       mSet_ServiceMsg ( _Srv_Modbus) ;
#else
       mSet_ServiceMsg3 (_Srv3_Modbus) ;
#endif
         }
       }
       else
       {
         countErr = 0;
#ifdef _Srv2_Modbus
	 mClr_ServiceMsg2( _Srv2_Modbus );
#elif  _Srv_Modbus
       mClr_ServiceMsg ( _Srv_Modbus) ;
#else
       mClr_ServiceMsg3 (_Srv3_Modbus) ;
#endif
       }
#endif
     }
     else  // _r.rs485.config._.master == 0
     {
       if ( MBRTU_Slave() )
       {
         if ( countErr++ >2 )
         {
#ifdef _Srv2_Modbus
	   mSet_ServiceMsg2( _Srv2_Modbus )	;
#elif  _Srv_Modbus
       mSet_ServiceMsg ( _Srv_Modbus) ;
#else
       mSet_ServiceMsg3 (_Srv3_Modbus) ;
#endif
         }
       }
       else
       {
         countErr = 0;
#ifdef _Srv2_Modbus
	 mClr_ServiceMsg2( _Srv2_Modbus )	;
#elif  _Srv_Modbus
       mClr_ServiceMsg ( _Srv_Modbus) ;
#else
       mClr_ServiceMsg3 (_Srv3_Modbus) ;
#endif
       }
     }
   }
   else
   {
     if ( state_rs == _RS_BUSWORK ) RS485_deInit();
   }
}

/*
���������� �����, ������������� �� ������ ���� ������ 125�� holding registers (������������ ���������� ��� Modbus RTU) ��� ���������
���������� �����:

������ �����: 8N1 (8 data bit, no parity bit, 1 stop bit)
�������� uart: $V_{uart}$ = 19200 bit/s
�������� �������� �������� ������: $V_{data}$ = 15360 bit/s
�������� �������: $master\_silence$ = 28 bit / $V_{uart}$ (��� ���������� ���������� ��������, ������ ������)
�������� ������ �������� ����������: $slave\_silence$ = 0.04 s (�������� ������� �� �������� ����������)
������� � �������� 125�� holding registers: 8 byte ��� 64 bit
����� �� 125� holding registers: 256 byte ��� 2048 bit

������� ��� ������� ������� ����� ������:

$T_{cycle} = silence\_master + 64 bit / V_{data} + slave\_silence + 2048 bit / V_{data} = 0.179 s$

�� ������������ Modbus � ����� RS-485/422 ����� ���������� 32 ������� ����������. ����� ������� ��������� ��� �� ������ ���������������,
������ �� �����. ����� ������ � ����� �������� ����� ����������� ������ �� $N$ ������� ���������, ���� �������� $T_{cycle}$ �� $N$ �������
��� ������ �������� ���������� $T_{full}$.
��������� �������� $T_{full}$ (������ � ���������� ������������ ���������� holding registers) ��� ��������� ���������� �����:
������ �����: 8N1, $V_{uart}$ = 19200 bit/s, ���������� ������� ���������, $N$ = 16
$T_{full}$ = 5.727 s
������ �����: 8N1, $V_{uart}$ = 9600 bit/s, ���������� ������� ���������, $N$ = 16
$T_{full}$ = 10.173 s
������ �����: 7E1, $V_{uart}$ = 19200 bit/s, ���������� ������� ���������, $N$ = 16
$T_{full}$ = 6.355 s
������ �����: 8N1, $V_{uart}$ = 19200 bit/s, ���������� ������� ���������, $N$ = 2
$T_{full}$ = 0.716 s
*/
