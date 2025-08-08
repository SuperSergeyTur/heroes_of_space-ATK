
//  Для Fujitsu 21-11-2002

//   08.06.05 10:53 *TDS*
//--------------------
//      ИНИЦИАЛИЗАЦИЯ ОБЪЕКТОВ СООБЩЕНИЙ  CAN.

 word  can_config ( byte port )
{
register union
{
  lword lax ;
  byte  b[4] ;
} buff ;
register byte ah ;

//        port = port ;// для устранения предупр. о неиспользов. "port"

        if ( port == 0 )
        {
        can0_con = 1  ; // Остановить контроллер CAN.
        CSR_TOE = 0 ; // Pin - "не CAN", а общего назначения

#ifdef   _CAN_SHARED  //  CAN-используется и другими программами, по-этому
                     //  msg1...msg12 не переинициализируем.
        BVALR_BVAL1  = 0 ;//выключить 1-й объект сообщения
        BVALR_BVAL2  = 0 ;//выключить 2-й объект сообщения //vmz
        BVALR_BVAL3  = 0 ;//выключить 3-й объект сообщения //vmz
        BVALR_BVAL4  = 0 ;//выключить 1-й объект сообщения
        BVALR_BVAL5 = 0 ;//выключить 5-й объект сообщения
        BVALR_BVAL6 = 0 ;//выключить 6-й объект сообщения
#else
           //  CAN-используется только этой программой.
        BVALR = 0 ; //все объекты сообщений отключены
#endif

// ****************************************************************************
          //настройка MO15 - прием
            // формируем свой ID.
        buff.lax = SetOwn_ID( port, can_setting(port).addr ) ;
         ah        = buff.b[3] ;
         buff.b[3] = buff.b[0] ;
         buff.b[0] = ah ;
         ah        = buff.b[2] ;
         buff.b[2] = buff.b[1] ;
         buff.b[1] = ah ;

        can0_msg1id = buff.lax ;
        can0_msg2id = buff.lax ; //vmz

        buff.lax = SetOwn_ID( port, can_setting(port).addr_p ) ;
         ah        = buff.b[3] ;
         buff.b[3] = buff.b[0] ;
         buff.b[0] = ah ;
         ah        = buff.b[2] ;
         buff.b[2] = buff.b[1] ;
         buff.b[1] = ah ;

        can0_msg3id = buff.lax ;
        can0_msg4id = buff.lax ; //vmz
      //---------
        IDER  = 0 ; //все объекты - СТАНДАРТНЫЙ ФРЕЙМ
        TRTRR = 0 ; //все объекты - DATA FRAME (не REMOTE FRAME)
        RFWTR = 0 ; //немедленная передача фрейма данных после установки
        TIER = 0x0000Ul ; //disables transmission complete interrupt

#ifdef _CAN_SLAVE_IRQ
        RIER = 0x001EUl;
        ICR00 = 6;
#else
        RIER = 0x0000Ul ; //disables receprion complete interrupt
        ICR00 = 7;
#endif

// ****************************************************************************
/*      маски: маскируются нулями. */
/*      маски: стандартная - выключена, расширенная - выключена; */

//196   can_sgmsk = 0xffffUl;
        //vmz AMSR0  = 0xfffffffBUl; //для всех объектов принимать маску AMR1,
                               //кроме 1(15)-го объекта сообщений (AMR0)
        AMSR  = 0xEAABUl; //vmz для всех объектов принимать маску AMR1,
                               //кроме 1(15),2,3-го объекта сообщений (AMR0)
        AMRX0 = 0x0000Ul; // "0" - нет маски
        AMRX1 = 0x0000Ul; // "0" - нет маски

/*      маски: локальная. */

//196   can_msg15con0 = Set_MsgVal;
        BVALR_BVAL1 = 1 ;//включить 1-й (15-й) объект сообщения
        BVALR_BVAL2 = 1 ;//включить 2-й объект сообщения vmz
        BVALR_BVAL3 = 1 ;//включить 3-й объект сообщения vmz
        BVALR_BVAL4 = 1 ;//включить 3-й объект сообщения vmz

//196   can_msg15con0 = Set_RXIE;


      //---------

       //настройка MO14 - передача
//196   can_msg14cfg  = _DIR_SEND ;//передача для "универсального" обмена

//196   can_msg14con0 = Set_MsgVal;
        can0_msg6id = 0 ;  //  чтобы у 6-го и 5-го не было одинаковых 'id'.
        BVALR_BVAL6 = 1 ;//включить 6-й объект сообщения
    //    can_msg14con0 = Set_TXIE;

       //настройка MO13 - передача, если занят MO14
//196   can_msg13cfg  = _DIR_SEND ;//передача для "универсального" обмена
//196   can_msg13con0 = Set_MsgVal;
        can0_msg5id = 1 ;  //  чтобы у 6-го и 5-го не было одинаковых 'id'.
        BVALR_BVAL5 = 1 ;//включить 5-й объект сообщения
    //    can_msg13con0 = Set_TXIE;

            //  формируем свою маску.
        buff.lax = SetOwn_Mask( port ) ;

          //asm  xchb lax   ,lax+3 ;
          //asm  xchb lax+1 ,lax+2 ;
         //buff.lax = lax ;
         ah        = buff.b[3] ;
         buff.b[3] = buff.b[0] ;
         buff.b[0] = ah ;
         ah        = buff.b[2] ;
         buff.b[2] = buff.b[1] ;
         buff.b[1] = ah ;
        //lax = ~buff.lax ;
//196    can_msk15 = lax ;
        //AMRX00 = ~buff.lax ; // маска для 1-го объекта
        AMRX0 = ~buff.lax ; // маска для 1-го, 2-го и 3-го объектов vmz
//--------------------------------------------------------------------------
//        Разрешить модернизацию регистров синхронизации

//196   can_con = 0x41;//Разрешить модернизацию регистров синхронизации

//      три выборки, BRP, TSEG1, TSEG2 = 3; => V = 210 000
//      can_btime0 = 0x43;
//      can_btime1 = 0xff;//b3;
//      три выборки, BRP=0, TSEG1=2, TSEG2 =1; SPL=1 => V =1 112 000

//      can_btime0 = 0xc0;//    0       0       921 000
//      can_btime1 = 0x94;//    1       4       --------

//      Задать скорость CAN-узла = 800 000 бит/сек
//**********************************************************
//      Внимание! У ADAM-4525 это соответствует 1600H
//**********************************************************
//      Задать скорость CAN-узла = 400 000 бит/сек
//**********************************************************
//      Внимание! У ADAM-4525 это соответствует 1601H
//**********************************************************

//      Задать скорость CAN-узла = 125 000 бит/сек
//**********************************************************
//      Внимание! У ADAM-4525 это соответствует 1C03H
//**********************************************************/
        //can_btime0 = 0x00;//    0       0       400 000
        //can_btime1 = 0x7d;//    7       13      --------

// ОЧИСТИТЬ НАКОПИВШИЕСЯ ЗАПРОСЫ ПРЕРЫВАНИЙ.

//196 can_btime0 = can_setting(port).btime0 ; //    0       4       125 000
//196 can_btime1 = can_setting(port).btime1 ; //    7       6       --------

          // задание типовых скоростей.
      if ( can_setting(port).config._.bt_125k == 1 )
      {
        BTR =  (w)bt_125k.bt0 | ((w)bt_125k.bt1 << 8);
      }
      else if ( can_setting(port).config._.bt_250k == 1 )
      {
        BTR =  (w)bt_250k.bt0 | ((w)bt_250k.bt1 << 8);
      }
      else if ( can_setting(port).config._.bt_1M == 1 )
      {
        BTR =  (w)bt_1M.bt0 | ((w)bt_1M.bt1 << 8);
      }
      else // если не задана типовая скорость - задаем скорость пользователя.
      {
        BTR =  (w)can_setting(port).btime0 | ((w)can_setting(port).btime1 << 8);
      }

        //Запретить модернизацию регистров синхронизации и запустить контроллер.
//196 can_con = 0x0 ;//0x01;
      CSR_TOE = 1 ; // Pin - для передачи по CAN

        //Запретить модернизацию регистров синхронизации и запустить контроллер.
      if ( can_setting(port).config._.vkl == 1 )
      {
        can_reInit(port) = 0 ;
        can0_con = 0 ; // Включить контроллер CAN.
      }
      else
      {
        can_reInit(port) = 1 ;
        can0_con = 0x01 ;
      }
    }
//      Конец инициализации для CAN;

      //can_dd[port].Error   = 0 ;
      can_dd[port].Avar    = 0 ;
      can_dd[port].Error_send = 0 ;
      can_dd[port].Error_receive = 0 ;
      can_dd[port].Can_stop= 0 ;

        return 0 ;
}
//-------------------------------------------------

word    can_test ( byte port )
{
  if (port==0)
  {
    //    для CAN 0
    // Выключить контроллер CAN и программы.
  if ( tst_can_stop(port) == 1 )
    {    // для возможности работы с CAN из монитора без рабочей программы.
      if ( can_reInit(port) == 0 )
      {
        can_reInit(port) = 1 ; // Для автоматического срабатывания переинициализации.
        can0_con = 1;// Остановить контроллер CAN.
        BVALR_BVAL1  = 0 ;//выключить 1-й объект сообщения
        BVALR_BVAL2  = 0 ;//выключить 2-й объект сообщения vmz
        BVALR_BVAL3  = 0 ;//выключить 3-й объект сообщения vmz
        BVALR_BVAL4  = 0 ;//выключить 3-й объект сообщения vmz
        BVALR_BVAL5 = 0 ;//выключить 13-й объект сообщения
        BVALR_BVAL6 = 0 ;//выключить 14-й объект сообщения
      }
      return 1 ;
    }

    // Переинициализация по команде с пульта после смены уставок CAN.
  if ( can_reInit(port) == 1 )
    {
      can_init(port);
      can_reInit(port) = 0 ;
      return 1 ;
    }
   //ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД

                // Ошибки - CAN еще не отключился от шины.
            if ((CSR & _NS_status) == 0x0100 || (CSR & _NS_status) == 0x0200)
              {
                can_dd[port].Avar++ ;
              }

                // CAN отключился от шины - BOff
            if ((CSR & _NS_status) == 0x0300 )
              {
//196           can_con &= Res_InitCan;
                 //  одного can_con для перезапуска CAN после i-того отключения
                 //  (коротили шину) не хватало, по-этому поставили
                 //  полную переинициализацию.
                 //  can_con = 0; // Включить контроллер CAN.
                can_init(port);

                mSet_ServiceMsg( _Srv_ResCan ) ;

                  // После Аварии CAN возврат в рабочую программу
                return 2 ;
              }

          // CAN не выставил предупреждение об ошибках
        // Проверка наличия потерянных сообщений. MsgLst = can_msgx_con.15,7,8.
      //----------
            // Проверка: не истекло ли время таймаута на передачу.
//196   if ((can_msg14con1 & _Tst_TxRqst) == _TxRqst )
        if (TREQR_TREQ6)
//        if (!TCR0_TC14) или так
        {
          if ( (u)(w)(timer1-can_dd[port].time_out_send6) > _TimeOut_send )
          {
//196       can_msg14con1 = Res_TxRqst;//сброс передачи.
            TCANR_TCAN6 = 1;//сброс запроса передачи.
            can_dd[port].Error_send++ ;
          }
        }
//        else
//        {
//         TCR0_TC14 = 0 ;
//        }
            // Проверка: не истекло ли время таймаута на передачу.
//196   if ((can_msg13con1 & _Tst_TxRqst) == _TxRqst )
        if (TREQR_TREQ5)
//        if (!TCR0_TC13) или так
        {
          if ( (u)(w)(timer1-can_dd[port].time_out_send5) > _TimeOut_send )
          {
//196       can_msg13con1 = Res_TxRqst;//сброс передачи.
            TCANR_TCAN5 = 1;//сброс запроса передачи.
            can_dd[port].Error_send++ ;
          }
        }
//        else
//        {
//         TCR0_TC13 = 0 ;
//        }
  }

  return 0 ;
}
//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД

word canSend( byte port , struct canMSG_Fuj *ptr )
{
  register union
  {
    lword lax ;
    byte  b[4] ;
  } buff ;

//      lax = ptr->id ;
//10.04.03 11:13#ifdef   _CAN_MASTER
  register byte ah ;
//10.04.03 11:13#endif

//        port = port ;// для устранения предупр. о неиспользов. "port"

      buff.lax = ptr->id ;
//10.04.03 11:14#ifdef   _CAN_MASTER   // для чистого slave переворачивание не имеет смысла
          //asm  xchb lax   ,lax+3 ; // т.к. он какой ID принял такой и отослал
          //asm  xchb lax+1 ,lax+2 ;
  //      buff.lax = lax ;
      //if ( can_setting(port).config._.master== 1 )
      //{
         ah        = buff.b[3] ;
         buff.b[3] = buff.b[0] ;
         buff.b[0] = ah ;
         ah        = buff.b[2] ;
         buff.b[2] = buff.b[1] ;
         buff.b[1] = ah ;
      //}
//        lax = buff.lax ;
//10.04.03 11:14#endif
  //    ptr->id = lax; нельзя, иначе это изменит в источнике

          //  У более чем одного передающего объекта не могут лежать
          // одинаковые адреса передачи даже если передает только один т.к.:
          // если передает старший по номеру объект, после его передачи будут
          // просканированы все объекты сооб. от младшего к старшему
          // и первый у кого будет найден переданный адрес будет ошибочно
          // принят как передающий и у него будет сброшен запрос передачи
          // (хотя он и не был взведен), а настоящий передающий объект
          // останется взведенным и будет передавать бесконечно.
          //
      if ( port==0 )
      {
        //для CAN 0
               // Проверка: не занят ли 6-й канал передачи.
//196   if ( ((can_msg14con1 & _Tst_TxRqst) != _TxRqst ) &&
//196                                       ( can_msg13id != ptr->id ))
                                // при проверке срезаем лишние кроме 11-ти старших разрядов
        if ( (!TREQR_TREQ6) && ((IDRX(5)&_ID11) != buff.lax) )//IDRX14 ))
                                       //(IDRX0(13) != ptr->id) - проверить
        {
        //у MO6 нет запроса на передачу И ID у MO5 не тот, что требуется сейчас

//196     can_msg14con1 = Set_CpuUpd;
          //can_msg14con1 = Set_NewDat;
//196       *(struct canMSG_Fuj*)&can_msg14id = *ptr;
//196       can_msg14id = lax;

//            BVALR0_BVAL14 = 0 ;
            Load_ptr(port,6,ptr);
            //IDRX0(14) = lax;
            IDRX(6) = buff.lax;
//            BVALR0_BVAL14 = 1 ;
       //   can_msg14con0 = Res_IntPnd;  без прерываний
             //пытаюсь отправить
//196     can_msg14con1 = Set_NewDat & Res_CpuUpd & Set_TxRqst;
          TREQR_TREQ6 = 1 ;

          //can_msg14con1 = Set_TxRqst;//пытаюсь отправить
          can_dd[port].time_out_send6 = timer1 ;
        }    // Проверка: не занят ли 5-й канал передачи.
//196   else if ( ((can_msg13con1 & _Tst_TxRqst) != _TxRqst ) &&
//196                                       ( can_msg14id != ptr->id ))
        else if ( (!TREQR_TREQ5) &&  ((IDRX(6)&_ID11) != buff.lax) )
                                       //(IDRX0(14) != ptr->id) - проверить
        {
        //у MO5 нет запроса на передачу И ID у MO6 не тот, что требуется сейчас
//196     can_msg13con1 = Set_CpuUpd;
//196       *(struct canMSG_Fuj*)&can_msg13id = *ptr;
//196       can_msg13id = lax ;
//            BVALR0_BVAL13 = 0 ;
            Load_ptr(port,5,ptr);
//            IDRX0(13) = lax;
            IDRX(5) = buff.lax;
//            BVALR0_BVAL13 = 1 ;

             //пытаюсь отправить
//196     can_msg13con1 = Set_NewDat & Res_CpuUpd & Set_TxRqst;
          TREQR_TREQ5 = 1 ;
          can_dd[port].time_out_send5 = timer1 ;
        }
        else
        {
          //09.04.06 00:37can_dd[port].Error_send++ ;
               //------------
          return 1 ;
        }
  return 0 ;
      }
 return 0;
}

//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД

word canReceive( byte port , struct canMSG_Fuj *ptr )
{
//10.04.03 11:15#ifdef   _CAN_MASTER
  register union
  {
    lword lax ;
    byte  b[4] ;
  } buff ;
  register byte ah ;
//10.04.03 11:15#endif
//  register lword lax ;
//        port = port ;// для устранения предупр. о неиспользов. "port"
   if ( port==0 )
   {
    //для CAN 0
//196 if (can_int==0x02) //Есть операция с МО15
    if (RCR_RC1) //Есть операция с МО1(MO15) - был прием
    {
       // считывание 15-го объекта сообщения.
//196 *ptr = *(struct canMSG_Fuj*)&can_msg15id ;
povtor:
       // считывание 1(15)-го объекта сообщения.
      Save_ptr(port,1,ptr) ;
      if (ROVRR_ROVR1)
      {
       //если есть переполнение может быть наложение "старых"
       //и "новых" данных - необходимо перечитать данные
       ROVRR_ROVR1 = 0 ;
       can_dd[port].Error_receive++ ;
       goto povtor ;
      }
       //переполнения не было - данные действительны
       RCR_RC1 = 0 ;
//196 can_msg15con0 = Res_IntPnd;
//196 can_msg15con1 = Res_NewDat & Res_RmtPnd;
      goto ret ;
    }
//vmz beg
    if (RCR_RC2) //Есть операция с МО2
    {
povtor2:
       // считывание 2-го объекта сообщения.
      Save_ptr(port,2,ptr) ;
      if (ROVRR_ROVR2)
      {
       //если есть переполнение может быть наложение "старых"
       //и "новых" данных - необходимо перечитать данные
       ROVRR_ROVR2 = 0 ;
       can_dd[port].Error_receive++ ;
       goto povtor2 ;
      }
       //переполнения не было - данные действительны
       RCR_RC2 = 0 ;
      goto ret ;
    }
//----------------------------------
    if (RCR_RC3) //Есть операция с МО3
    {
povtor3:
       // считывание 3-го объекта сообщения.
      Save_ptr(port,3,ptr) ;
      if (ROVRR_ROVR3)
      {
       //если есть переполнение может быть наложение "старых"
       //и "новых" данных - необходимо перечитать данные
       ROVRR_ROVR3 = 0 ;
       can_dd[port].Error_receive++ ;
       goto povtor3 ;
      }
       //переполнения не было - данные действительны
       RCR_RC3 = 0 ;
      goto ret ;
    }
//----------------------------------
    if (RCR_RC4) //Есть операция с МО3
    {
povtor4:
       // считывание 3-го объекта сообщения.
      Save_ptr(port,4,ptr) ;
      if (ROVRR_ROVR4)
      {
       //если есть переполнение может быть наложение "старых"
       //и "новых" данных - необходимо перечитать данные
       ROVRR_ROVR4 = 0 ;
       can_dd[port].Error_receive++ ;
       goto povtor4 ;
      }
       //переполнения не было - данные действительны
       RCR_RC4 = 0 ;
      goto ret ;
    }
  return 0 ;
ret:
//10.04.03 11:15#ifdef   _CAN_MASTER   // для чистого slave переворачивание не имеет смысла
  //if ( can_setting(port).config._.master== 1 )
  //{
    buff.lax = ptr->id ;
//      lax = ptr->id ;
          //asm  xchb lax   ,lax+3 ;
          //asm  xchb lax+1 ,lax+2 ;
       ah        = buff.b[3] ;
       buff.b[3] = buff.b[0] ;
       buff.b[0] = ah ;
       ah        = buff.b[2] ;
       buff.b[2] = buff.b[1] ;
       buff.b[1] = ah ;
//        lax = buff.lax ;
    ptr->id = buff.lax;
  //}
//10.04.03 11:16#endif

  return 1 ; // приняты данные для 'slave'.
   }

  return 0 ;

}

//-----------------------------------------------
word Load_ptr(byte port, int buf,struct canMSG_Fuj *ptr)
// Переложить из структуры в регистры объекта сообщения
// id, dlen, data[8]
{
  register byte i ;
  if ( port==0 )
  {
   //для CAN 0
   IDRX(buf) = ptr->id ;
   DLCR(buf) = ptr->cfg.dlen ;
   for ( i=0; i < 8; i += 2  )
    {
     DTR_WORD(buf,i/2) = (w)(ptr->data[i]) | ((w)(ptr->data[i+1]) << 8) ;
     // *(char*)&(DTR0_BYTE(buf,i)) = ptr->data[i] ; по-байтно не работает.
    }
   return 0 ;
  }
  return 0;
}
//-----------------------------------------------
word Save_ptr(byte port, int buf,struct canMSG_Fuj *ptr)
// Переложить из регистра объекта сообщения в структуру
// id, dlen, data[8]
{
  register byte i ;

  if ( port==0 )
  {
   //для CAN 0
   ptr->id = IDRX(buf) & _ID11 ; // срезаем лишние кроме 11-ти старших разрядов,
   ptr->cfg.dlen = DLCR(buf) ;  // т.к. CAN-контроллер иногда заглючивает и
                                //  помещает в них мусор, а затем у мастера
                               // срабатывает защита по несовпадению id.
   //            for ( i=0; i < 8; i=i+2 )
   for ( i=0; i < 8; i++ )
    {
      //ptr->data[i]   = DTR0_WORD(buf,i) ;
      //ptr->data[i+1] = DTR0_WORD(buf,i) >> 8 ;
      ptr->data[i] = DTR_BYTE(buf,i) ;
    }
  return 0;
  }
  return 0;
}

__interrupt void CAN0_RX_Interrupt( void)
{
  canSlaveDrive(_CAN0_Port);
}


