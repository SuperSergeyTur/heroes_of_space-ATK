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
    // Формируем разрешение на прием по UART только после отправки данных по DMA или
    // если, что-то пошло не так в DMA контролируем по времени
   if ((RS485_DMA_CH_TC != 0) || (RS485_DMA_CH_ERR != 0) ||
     (((LPC_UART2->RS485CTRL & UART_RS485CTRL_RX_DIS) != 0 ) && ((u)((w)(timer1 - time_Tx)) > time_TxMax)) )
   {// если зашли по таймеру запретим прерывание по DMA
     if (( RS485_DMA_CH_TC == 0 ) && (RS485_DMA_CH_ERR == 0))  RS485_DMA_Disable ();
     RS485_DMA_CH_TC = 0; RS485_DMA_CH_ERR = 0 ;
     LPC_UART2->RS485CTRL &= ~(UART_RS485CTRL_RX_DIS) ;
   }
#endif

// Время прерывания - Timer_rs
 if ((u)((w)(timer1 - Timer_rs)) < Time_rs_frame) //&& (newbyte == 1)) 08.05.18 - если цикл фона чаще чем прерыв. UART, тогда ошибочно начинаем обрабатывать посылку
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
     // Контролируем допустимое время на отправку. Т.к. пока не закончится отправка введен запрет на прием.
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
    // Формируем разрешение на прием по UART только после отправки данных по DMA или
    // если, что-то пошло не так в DMA контролируем по времени
 if ((RS485_DMA_CH_TC != 0) || (RS485_DMA_CH_ERR != 0) ||
     (((LPC_UART2->RS485CTRL & UART_RS485CTRL_RX_DIS) != 0 ) && ((u)((w)(timer1 - time_Tx)) > time_TxMax)) )
  {  // если зашли по таймеру запретим прерывание по DMA
   if (( RS485_DMA_CH_TC == 0 ) && (RS485_DMA_CH_ERR == 0))  RS485_DMA_Disable ();

   RS485_DMA_CH_TC = 0; RS485_DMA_CH_ERR = 0 ;
   LPC_UART2->RS485CTRL &= ~(UART_RS485CTRL_RX_DIS) ;
  }
#endif

  while ( counter < NumFrames )                      // Счетчик очередности фрейма
  {
//-------------------------- request-----------------------------------------------
    if ( flag_busy == 0 )                            // Флаг для отправки запроса
    {
      if ( *SetMBFrame[FrameCount].TimeCycle != 0 )   // 0 = по команде -   ????????????????????
      {
       // if ( (timer1 - TimerFrame) >= 50 )           // Минимальное время после ответа и перед запросом. 50 тиков
       // {
          //if ( (timer1 - SetMBFrame[FrameCount].CurTime) >= SetMBFrame[FrameCount].TimeCycle )// время после последней отправки фрейма и время через которое надо запрашивать эту посылку
          if ( (w)(u)(Timer1_Ovr-SetMBFrame[FrameCount].CurTime) >= *SetMBFrame[FrameCount].TimeCycle )
          { // CurTime - расчетное время в ходе цикла. В фрейме можно не указывать
            // TimeCycle - 3,5 char. Задержка мастера (минимально допустимая): $master\_silence$ = 28 bit / $V_{uart}$
            TimerFrame = timer1;
  	    // Посылаем номер фрейма и структуру запроса для заполнения
            Len = modbusMasterSend( FrameCount, &request);
         //--------------------------------
//----------------Формуємо фрейм ---------------------------------------
           //адреса пристрою (абонента)
           Frame[0] = _r.rs485.addr;
	   //Функція для слейва
           Frame[1] = request.func;
           //Заповнюємо фрейм корисними даними
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
           //Відправка запиту
           RS485_Send( Frame, Len ) ;
           // Контролируем допустимое время на отправку. Т.к. пока не закончится отправка введен запрет на прием.
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
     FrameCount++; // номер фрейма
     counter++;    // лічильник
     if ( FrameCount >= NumFrames )  FrameCount = 0; // рівняння з розміром самої таблиці фреймів
   }
   else  // flag_busy = 1 - ожидаем ответ от слейва
   {
//--------------------------------answer----------------------------------------
     // Время прерывания - Timer_rs
     if ((u)((w)(timer1 - Timer_rs)) < Time_rs_frame) //&& (newbyte == 1)) 08.05.18 - если цикл фона чаще чем прерыв. UART, тогда ошибочно начинаем обрабатывать посылку
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
        // Посылаем номер фрейма и структуру приема для заполнения
         Len = modbusMasterReceive( FrameCount, &answer);
         //FrameCount++; перелистываем фрейм в ожидании, когда закончится прием инфы. Потому как сюда зайдет несколько
         //раз в процессе считывания.
         if ( FrameCount >= NumFrames )  FrameCount = 0;
         TimerFrame = timer1;
         //flag_busy = 0;       //Разрешаем следующую посылку мастером только после временной пауы
         //SetMBFrame[FrameCount].CurTime = timer1; // Время между пакетами.
	 return 0 ;
       }
       else
       {
         //Время ожидания ответа либо время для прочтения ответа
         if  ( (u)((w)(Timer1_fSec-TimeWait)) > _r.time_read ) // Пока без уставки - просто жесткое значение
	 {
	   flag_busy = 0;       //Разрешаем повторную посылку мастером, если не пришел ответ
           TimerFrame = timer1;
	   FrameCount++;        //Перелистываем фрейм
           if ( FrameCount >= NumFrames )  FrameCount = 0;
           //SetMBFrame[FrameCount].CurTime = timer1; // Время между пакетами.
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
Рассчитаем время, затрачиваемое на полный цикл чтения 125ти holding registers (максимальное количество для Modbus RTU) при следующих
параметрах линии:

Формат кадра: 8N1 (8 data bit, no parity bit, 1 stop bit)
Скорость uart: $V_{uart}$ = 19200 bit/s
Скорость передачи полезных данных: $V_{data}$ = 15360 bit/s
Задержка мастера: $master\_silence$ = 28 bit / $V_{uart}$ (это минимально допустимая задержка, обычно больше)
Задержка ответа ведомого устройства: $slave\_silence$ = 0.04 s (значение зависит от ведомого устройства)
Посылка с запросом 125ти holding registers: 8 byte или 64 bit
Ответ со 125ю holding registers: 256 byte или 2048 bit

Формула для расчёта времени цикла чтения:

$T_{cycle} = silence\_master + 64 bit / V_{data} + slave\_silence + 2048 bit / V_{data} = 0.179 s$

По спецификации Modbus к линии RS-485/422 можно подключить 32 ведомых устройства. Опрос ведомых устройств так же ведётся последовательно,
обычно по кругу. Чтобы понять с какой скорость будут обновляться данные от $N$ ведомых устройств, надо умножить $T_{cycle}$ на $N$ Назовем
это полным временем обновления $T_{full}$.
Несколько расчётов $T_{full}$ (читаем и записываем максимальное количество holding registers) при различных параметрах связи:
Формат кадра: 8N1, $V_{uart}$ = 19200 bit/s, Количество ведомых устройств, $N$ = 16
$T_{full}$ = 5.727 s
Формат кадра: 8N1, $V_{uart}$ = 9600 bit/s, Количество ведомых устройств, $N$ = 16
$T_{full}$ = 10.173 s
Формат кадра: 7E1, $V_{uart}$ = 19200 bit/s, Количество ведомых устройств, $N$ = 16
$T_{full}$ = 6.355 s
Формат кадра: 8N1, $V_{uart}$ = 19200 bit/s, Количество ведомых устройств, $N$ = 2
$T_{full}$ = 0.716 s
*/
