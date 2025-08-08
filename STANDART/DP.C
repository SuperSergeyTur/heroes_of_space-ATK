
#ifndef _CM3_
/****************   02.06.2008 11:45   *******************
 * После всего пережитого на ДТЗ им.Ильича сформировался *
 * нижеследуюший алгоритм обработки сообщений Profibus   *
 * На ДТЗ работают 22 абонента на скорости 187,5 кБит/с  *
**********************************************************/

//-------------------------------------------------
// Инициализация перемнных и настройка внешней шины
//-------------------------------------------------
void Init_DP(void)
{
   word i;

 spec_form = 0;

#ifdef _NET_IRQ
 CSE = CSE & 0xF7;
 ASR3 = 0x30;
 AMR3 = 0x00;
 AMD3 = 0x01;      // Area Mode reg AMD3 -> 8-Bit Bus, 1 wait state, no ready-pin
 CSE = CSE | 0x08; // включить CS3

 mSetProfiRes();          // RESET
 for ( i=0; i<300; i++)
 {
 }
 mClrProfiRes();

// Timer_DP = Timer1_Ovr;
 Profi_dp.var1.all = 0;
 Profi_dp.var2 = 0;
 Profi_dp.var3.all = 0;
 Profi_dp.err = 0;
 Profi_dp.Op = 0;
 Profi_dp.Gr = 0;
 Profi_dp.Num = 0;
 for ( i=0; i<16; i++)
 {
    Profi_dp.In_PPO[i] = 0;
    Profi_dp.Out_PPO[i] = 0;
 }
 for ( i=0; i<40; i++)
    Profi_dp.Prm_Data[i] = 0;

#else    // Плата CAN-Profibus

//RESET
 PDR2_P22 = 1;
 for ( i=0; i<3000; i++)
 {
 }
 PDR2_P22 = 0;

 for ( i=0; i<16; i++)
 {
    Profi_dp.In_PPO[i] = 0;
    Profi_dp.Out_PPO[i] = 0;
 }
 for ( i=0; i<40; i++)
    Profi_dp.Prm_Data[i] = 0;

#endif

 Len_Dout = 0;
 Len_Din = 0;
 Profi_dp.flag_dx = 0;

// if ( _r.dp_setting._.vkl == 1 ) Init_SPC();
 Init_SPC();
}

//---------------------------------------------
// Инициализация ASIC SPC3 или VPC3+
//---------------------------------------------
word Init_SPC(void)
{
#ifdef _NET_IRQ
   lw ptr;
#else
   word ptr;
#endif
   int Add;

   _Int_Reg[0] = 0x03;
   __wait_nop();
   __wait_nop();
   __wait_nop();

//	Очистка ОЗУ
   for ( ptr=Addr_Profi; ptr<=(Addr_Profi+0x5FF); ptr++)
   {
      *(b*)ptr = 0;
   }

   if ( (_Status_Reg[0] & 0x01) == 0 )
   {
     _Int_Reg[0] = 0x00 ;
     _Int_Reg[1] = 0x00 ;
     _Int_Ack_Reg[0]=0xFF ;
     _Int_Ack_Reg[1]=0xFF ;

     _Mode_Reg_R = 0xFF ;

     _Mode_Reg0[0]=(SYNC_SUPPORTED + FREEZE_SUPPORTED);
     _Mode_Reg0[1]=(USER_TIMEBASE + DP_MODE + Spec_Clear_Mode );//+ EOI_Base_Time ) ;

     _Int_Mask_Reg[0]=0xF8 ;
     _Int_Mask_Reg[1]=0xC3 ;

// установка сторожевого таймера для поиска несущей
     _WD_Baud_Ctrl_Val = 0x10 ;
     _MinTsdr_Val = 0x0B ;

     _R_User_Wd_Value[0] = 0xFF ;
     _R_User_Wd_Value[1] = 0x01 ;

// признак того, что адрес не изменяется (false)
     _R_Real_No_Add_Change=0xFF;

// установка идентификационного кода
     _R_Ident_Low  = IDENT0;
     _R_Ident_High = IDENT1;

// задать собственный адрес
    _R_TS_Adr = (b)_r.DP_addr;//OWN_ADDRESS

// ------------ Регистры -----------------------------
// инициализация буфера Output
    _R_Len_Dout_Puf = _Len_Dout_Buf;    // длина буфера
    Add= (int) _Dout_Buf1 & 0x7FF;
    _R_Dout_buf_Ptr1=Add >>3;           // номер сегмента буфера 1
    Add=(int) _Dout_Buf2 & 0x7FF;
    _R_Dout_buf_Ptr2=Add >>3;           // номер сегмента буфера 2
    Add=(int) _Dout_Buf3 & 0x7FF;
    _R_Dout_buf_Ptr3=Add >>3;          // номер сегмента буфера 3

// инициализация буфера Input
    _R_Len_Din_Puf = _Len_Din_Buf;      // длина буфера
    Add=(int) _Din_Buf1 & 0x7FF;
    _R_Din_buf_Ptr1=Add >>3;            // номер сегмента буфера 1
    Add=(int) _Din_Buf2 & 0x7FF;
    _R_Din_buf_Ptr2=Add >>3;            // номер сегмента буфера 2
    Add=(int) _Din_Buf3 & 0x7FF;
    _R_Din_buf_Ptr3=Add >>3;            // номер сегмента буфера 3

// инициализация буфера Diagnostic
    _R_Len_Diag_Puf1=_Len_Diag_Buf;    // длина буфера
    Add =(int)  _Diag_Buf1 & 0x7FF;
    _R_Diag_Puf_Ptr1=Add >>3;          // номер сегмента буфера 1
    _R_Len_Diag_Puf2=_Len_Diag_Buf;    // длина буфера
    Add =(int)  _Diag_Buf2 & 0x7FF;
    _R_Diag_Puf_Ptr2=Add >>3;          // номер сегмента буфера 2

// инициализация буфера Auxialiary
    _R_Len_Cntrl_Puf1=_Len_Cntrl_Buf;
    _R_Len_Cntrl_Puf2=_Len_Cntrl_Buf;
    _R_Aux_Puf_Sel=0;
    Add=(int) _Aux_Buf1 & 0x7FF;
    _R_Aux_buf_Ptr1=Add >>3;
    Add=(int) _Aux_Buf2 & 0x7FF;
    _R_Aux_buf_Ptr2=Add >>3;

// инициализация буфера Slave Address
    _R_Len_SSA_Data=5;
    Add=(int) _SSA_Data & 0x7FF;
    _R_SSA_buf_Ptr=Add >> 3;

// инициализация буфера Param
    _R_Len_Prm_Data=_Len_Prm_Data;
    Add=(int) _Prm_Data & 0x7FF;
    Profi_dp.addr_Prm_Buf = Add;
    _R_Prm_buf_Ptr=Add >> 3;

// инициализация буфера Get_Config
    _R_Len_Cfg_Data=_Len_Cfg_Buf;
    Add=(int) _Cfg_Buf & 0x7FF;
    _R_Cfg_Buf_Ptr=Add >> 3;

// инициализация буфера Read_Cfg_Data
    _R_Len_Read_Cfg_Data=_Len_Cfg_Buf;
    Add=(int) _Read_Cfg_Buf & 0x7FF;
    Profi_dp.addr_Cfg_Buf = Add;
    _R_Read_Cfg_buf_Ptr=Add >> 3;

// инициализация прерывания

    _Mode_Reg_S = EOI;

#ifdef _NET_IRQ

  ENIR_EN1 = 0;
  ELVR_LAB1 = Falling;
  EIRR_ER1 = 0;                         // 1111 1101
  ENIR_EN1 = 1;
  ICR01 = 24;

#else  // CAN-Profibus

  ENIR = 0;       //Запрет прерывания INT0, INT1
  ELVR_LALB0 = Falling ;  //Прерывание по спаду сигнала
  EIRR &= 0xFC;           //Сброс флага прерывания по INT0, INT1
  ICR02 = 5 ;             //Установка приоритета прерывания
  ENIR_EN0 = 1 ;      //Разрешение прерывания INT0

#endif

   if ( _r.net_setting._.vkl == 1 ) _Mode_Reg_S = START_SPC3;   // Старт SPC3

   }
 return 1;
}

//----------------------------------
// Обработка прерывания по Profibus
//----------------------------------
__interrupt void DP_Interrupt (void)
{
  pD( 1 ) ;

#ifdef _NET_IRQ
    DP_driver() ;
//    Timer_DP = Timer1_Ovr;
    EIRR_ER1 = 0;
#else
  if ( EIRR_ER1 ) // выбор линии прерывания.
  {
    EIRR_ER1 = 0 ;
  }
  else
  {
     Tint_off = timer1 - Time_int_off ;
     Tint = timer1 ;
     DP_driver() ;
     Tint = timer1 - Tint ;// dlya indication time of int.
     Time_int_off = timer1 ;
	 Timer_DP = Timer1_Ovr;
     EIRR_ER0 = 0;    //  to except interrupts: _Mode_Reg0[1]=(... + EOI_Time_base);
  }

#endif

    _Mode_Reg_S = EOI;

  pD( 0 ) ;

  return ;
}

//-------------------------------------------
// Драйвер Profibus - обработка исключительных ситуаций
//-------------------------------------------
void DP_driver(void)
{
	byte ir0, ir1;

//  _Mode_Reg_S = Res_User_Wd;

	ir0 = _Int_Reg[0] ;
	ir1 = _Int_Reg[1] ;

  if  ( ( ir0 & MAC_Reset ) != 0 )           _Int_Ack_Reg[0] = MAC_Reset ;

// переход DP_SM в/из состояния 'DATA_EX'
  if  ( ( ir0 & GO_LEAVE_DATA_EX ) != 0 )    _Int_Ack_Reg[0] = GO_LEAVE_DATA_EX ;

// обнаружена несущая частота ('Baud_Search state')
  if  ( ( ir0 & Baudrate_Detect ) != 0 )     _Int_Ack_Reg[0] = Baudrate_Detect ;

// выход watchdog timer из состояния 'DP_Control'
  if  ( ( ir0 & WD_DP_MODE_TIMEOUT ) != 0 )  _Int_Ack_Reg[0] = WD_DP_MODE_TIMEOUT ;

// сброс User timer
  if  ( ( ir0 & User_Timer_Clock ) != 0 )
  {
     _Int_Ack_Reg[0] = User_Timer_Clock ;
     _Mode_Reg_S = Res_User_Wd ;
  }

// получена 'Global_Control telegram'
  if  ( ( ir1 & NEW_GC_COMMAND ) != 0 )      _Int_Ack_Reg[1] = NEW_GC_COMMAND;

// получена 'Set_Slave_Address telegram'
  if  ( ( ir1 & NEW_SSA_DATA ) != 0 )
  {
     do_Addr();
     _Int_Ack_Reg[1] = NEW_SSA_DATA;
  }

// новые параметры
  if  ( ( ir1 & NEW_PRM_DATA ) != 0 )      do_Prm();

// новая конфигурация
  if  ( ( ir1 & NEW_CFG_DATA ) != 0 )      do_Cfg();


// данные для выдачи на выходы (Writing Outputs)-------
  if  ( ( ir1 & DX_OUT ) != 0 )
  {
     Profi_dp.flag_dx = 1;
     _Int_Ack_Reg[1] = DX_OUT;
  }

// в ответ на 'New_Diag_Cmd,' поменялся буфер диагностики
  if  ( ( ir1 & Diag_Puffer_Changed ) != 0 )
     _Int_Ack_Reg[1] = Diag_Puffer_Changed;

  if  ( ( ir1 & 0x80 ) != 0 )         _Int_Ack_Reg[1]=0x80;

}

//--------------------------------------------------
// Изменение адреса Profibus - gsd-файл не поддерживает (сделано на всякий случай)
//--------------------------------------------------
char do_Addr(void)
{
  if ((_SSA_Data[1]==IDENT1) && (_SSA_Data[2]==IDENT0))
  {
     _r.DP_addr = _SSA_Data[0];
     Write_ust |= _CAN_Wr_ust ;
  }
  return _SSA_Bufferfreecmd;
}

//------------------------------------------------------
// Параметризация
// Длина посылки должны быть 41 байт. Первые 8 байт стандартные - не обрабатываем.
// Остальные: первые 16 - номера выходных переменных,
//            вторые 16 - номера входных переменных.
// Последний байт - наличие переменного поля.
//------------------------------------------------------
char do_Prm(void)
{
  byte *Prm;
  byte Len_Prm;
  byte i;

  if (_R_Len_Prm_Data != 41)
  {
    Profi_dp.err = _DP_NotPrm ;
    return _UserPrmDataNOK;
  }

// параметры сети Profibus DP
  Profi_dp.err = _DP_NoErr;
#ifdef _NET_IRQ
  Prm= (b*)((lw)Addr_Profi + (lw)Profi_dp.addr_Prm_Buf);
#else
  Prm= (b*)((w)Addr_Profi + (w)Profi_dp.addr_Prm_Buf);
#endif
//  _R_User_Wd_Value[0] = Prm[1];
//  _R_User_Wd_Value[1] = Prm[2];
//  _MinTsdr_Val        = Prm[3];
  Len_Prm = _R_Len_Prm_Data - 8 ;
  for ( i=0; i<Len_Prm; i++ )
  {
    Profi_dp.Prm_Data[i] = Prm[i+8] ;
  }

 return _User_Prm_Data_OK;
}

//----------------------------------------------------------
// Конфигурирование
// Основной формат:
// 0..3 бит - длина данных (1..16)
// 4..5 бит - 00 = спец формат
//			  01 = вход
//			  10 = выход
//			  11 = вход/выход
// 6 бит    - 0  = байт
//			  1  = слово
// 7 бит    - 0  = побитово
//			  1  = полное
// Специальный формат (состоит из двух или трех байт посылки):
// Байт 1
// 0..3 бит - длина данных производителя (не используем)
// 4..5 бит - всегда 00
// 6..7 бит - 00 = никаких данных
//			  01 = 1 байт входных данных
//			  10 = 1 байт выходных данных
//			  11 = 1 байт выход + 1 байт вход
// Байт 2(3)
// 0..5 бит - длина данных (1..64)
// 6 бит    - 0  = байт
//			  1  = слово
// 7 бит    - 0  = побитово
//			  1  = полное
//----------------------------------------------------------
char do_Cfg(void)
{
  byte x, num_cfg, ah, al;
  byte cfg_dp, inp, outp;
#ifdef _NET_IRQ
  lw ax ;
#else
  word ax;
#endif

   inp = outp = 0;
   ax = Addr_Profi+0x31 ;
   num_cfg = *(b*)ax;
   ax = Addr_Profi;
#ifdef _NET_IRQ
   ax += (lw)Profi_dp.addr_Cfg_Buf;
#else
   ax += (w)Profi_dp.addr_Cfg_Buf;
#endif
   spec_form = 0 ;
   al = 0 ;
   for ( x=0; x<num_cfg; x++)
   {
     cfg_dp = *(b*)(ax + x) ;
     ah = cfg_dp & 0x30 ;
     switch ( ah )
     {
        case 0x00 : if ( spec_form == 0)   // Special Format
                    {
                       spec_form = cfg_dp & 0xC0 ;
                    }
                    else
                    {
                       switch ( spec_form )
                       {
                         case 0x40 : if ( cfg_dp & 0x40 )
                                       inp = inp + ( (cfg_dp & 0x0F) + 1) * 2;
                                     else
                                       inp = inp + ( (cfg_dp & 0x0F) + 1);
                                     spec_form = 0 ;
                                     break;
                         case 0x80 : if ( cfg_dp & 0x40 )
                                       outp = outp + ( (cfg_dp & 0x0F) + 1) * 2;
                                     else
                                       outp = outp + ( (cfg_dp & 0x0F) + 1);
                                     spec_form = 0 ;
                                     break;
                         case 0xC0 : if ( cfg_dp & 0x40 )
                                     {
                                       if ( al == 1 )
                                       {
                                         inp  = inp  + ( (cfg_dp & 0x0F) + 1) * 2;
                                         al = 0 ;
                                         spec_form = 0 ;
                                       }
                                       else
                                       {
                                         outp = outp + ( (cfg_dp & 0x0F) + 1) * 2;
                                         al = 1 ;
                                       }
                                     }
                                     else
                                     {
                                       if ( al == 1 )
                                       {
                                         inp  = inp  + ( (cfg_dp & 0x0F) + 1);
                                         al = 0 ;
                                         spec_form = 0 ;
                                       }
                                       else
                                       {
                                         outp = outp + ( (cfg_dp & 0x0F) + 1);
                                         al = 1 ;
                                       }
                                     }
                                     break;
                       }
                    }
                    break;
        case 0x10 : if ( cfg_dp & 0x40 )   // Input Base Format
                      inp = inp + ( (cfg_dp & 0x0F) + 1) * 2;
                    else
                      inp = inp + ( (cfg_dp & 0x0F) + 1);
                    break;
        case 0x20 : if ( cfg_dp & 0x40 )   // Output Base Format
                      outp = outp + ( (cfg_dp & 0x0F) + 1) * 2;
                    else
                      outp = outp + ( (cfg_dp & 0x0F) + 1);
                    break;
        case 0x30 : if ( cfg_dp & 0x40 )   // Input-Output Base Format
                    {
                      inp  = inp  + ( (cfg_dp & 0x0F) + 1) * 2;
                      outp = outp + ( (cfg_dp & 0x0F) + 1) * 2;
                    }
                    else
                    {
                      inp  = inp  + ( (cfg_dp & 0x0F) + 1);
                      outp = outp + ( (cfg_dp & 0x0F) + 1);
                    }
                    break;
     }
   }
  _R_Len_Dout_Puf = outp;    // длина буфера
  _R_Len_Din_Puf  = inp;    // длина буфера

  if ( Profi_dp.Prm_Data[32] == 1 )
  { // посылка с переменным полем
    Len_Dout = ( outp - 7)/2;
    Len_Din = ( inp - 7)/2;
    if ( ( outp < 8 ) || ( inp < 8 ) )   // такого варианта быть не может
    {
        Profi_dp.err = _DP_NotVar;
        Profi_dp.var1.all = 0;
        Profi_dp.var2 = 0;
        Profi_dp.var3.all = 0;
    }
  }
  else
  {
    Len_Dout = ( outp + 1)/2;
    Len_Din = ( inp + 1)/2;
  }

// данные конфигурирования правильные
  _Mode_Reg_S = En_Change_Cfg_Puffer;   // установка признака замены Read_Config
   x = _User_Cfg_Data_OK + _New_DIN_Buffer_Cmd;
   N_Din = _New_DIN_Buffer_Cmd;  // чтобы не зависало при старте нужно прочитать 2 раза номер буфера

 return x;
}

//---------------------------------------------------------
// Диагностика
// Формируется автоматически
// Своих диагностических данных не формируем, поэтому просто меняем
// диагностический буфер
//---------------------------------------------------------
char do_Diag (void)
{
  char *Diag;
  char NDiag;
//------------выбор буфера для диагностики--------------------------
//  Diag[0]=0x02;    // 0 байт (0 - Ext_Diag; 1 - Stat_Diag; 2 - Ext_Diag_Overf)
  NDiag = _DIAG_Buffer_SM & 3;
  if (NDiag == 1) Diag=_Diag_Buf1;
  else Diag=_Diag_Buf2;
//--------------формирование буфера диагностики---------------------
/*  Diag[0]=0x02;    // 0 байт (0 - Ext_Diag; 1 - Stat_Diag; 2 - Ext_Diag_Overf)
  Diag[1]=0;
  Diag[2]=0;
  Diag[3]=0;
  Diag[4]=0;
  Diag[5]=0;
  Diag[6]=0;   */
//-------------изменить буфер диагностики------------------------
  return _New_DIAG_Puffer_Cmd;
}

#ifndef _NET_IRQ
// Для платы CAN-Profibus переворачиваем байты в слове
void b2b (void)
{
  byte ah;
   ah = w2w.btb.b1;
   w2w.btb.b1 = w2w.btb.b2;
   w2w.btb.b2 = ah;
}
#endif


//----------------------------------------------------------
// Обработка данных
//----------------------------------------------------------
void do_InOut(void)
{
  word *pOut;
  word *pIn;
  byte Len_var, x, y;
#ifndef _NET_IRQ
  byte var_val;
#endif
  word num;

// выбрать буфер принятых данных
  N_Dout=_Next_DOUT_Buffer_Cmd & 3;

  switch (N_Dout)
  {
    case 1:
         pOut = (w*) _Dout_Buf1;
         break;
	case 2:
         pOut = (w*) _Dout_Buf2;
         break;
	case 3:
         pOut = (w*) _Dout_Buf3;
         break;
  };

// выбрать буфер для формирования данных мастеру
  switch (N_Din)
  {
    case 1:
         pIn = (w*) _Din_Buf1;
         break;
	case 2:
         pIn = (w*) _Din_Buf2;
         break;
	case 3:
         pIn = (w*) _Din_Buf3;
         break;
  };

//-------- Обработка данных -----------
#ifdef _NET_IRQ
  if ( _r.net_setting._.vkl == 1 )
#else
  can_rd.kol = 0;
  can_rd.cur = 0;
  can_wr.kol = 0;
  can_wr.cur = 0;
  var_val = 0;
#endif
{
//------------- Обработка входных данных ---------------
  if ( Profi_dp.Prm_Data[32] == 1 )
  { // посылка с переменным полем
    Len_var = Len_Dout;
    Profi_dp.var1.all  = pOut[Len_var++];
    Profi_dp.var2      = pOut[Len_var++];

#ifdef _NET_IRQ
    Profi_dp.Op = (b)Profi_dp.var1._.op;
    Profi_dp.Gr = (b)Profi_dp.var1._.gr;
    Profi_dp.Num = Profi_dp.var2;
#else
    Profi_dp.Gr = (b)Profi_dp.var1._.op;
    Profi_dp.Op = (b)Profi_dp.var1._.gr;
    w2w.wtw = Profi_dp.var2 ;
    b2b();
    Profi_dp.Num = w2w.wtw;
#endif

	if ( Profi_dp.Op == _Write_DP)  // в переменном поле - параметр на запись
    {
      num = 0;
      if (( Profi_dp.Gr == 0) || ( Profi_dp.var2 == 0 ))
      {
        Profi_dp.err = _DP_NotGrNum;
        goto _no_dp;
      }
      Profi_dp.err = _DP_NoErr;
      if ( Profi_dp.Gr  < 5)      // номер параметра из var_tab
      {
        num = (Profi_dp.Gr-1) * 32 + Profi_dp.Num;
        Profi_dp.var3._.high  = 0 ;

#ifdef _NET_IRQ
        Profi_dp.var3._.low   = pOut[Len_var+1] ;
        if ( var_tab1[num-1].access == 2 )
          *((w*)var_tab1[num-1].addr) = pOut[Len_var+1] ;
        else
          Profi_dp.err = _DP_NotWr;
#else
        w2w.wtw = pOut[Len_var+1] ;
        b2b();
        Profi_dp.var3._.low = w2w.wtw;
        var_val = 1;
        can_wr.num[can_wr.cur++] = num-1;
        w2w.wtw = pOut[Len_var+1] ;
        b2b();
        *((w*)c_t_abKTE[num-1].addr) = w2w.wtw ;
#endif

      }
      else
      {                                 // номер параметра из следа
        num = 128 + Profi_dp.var2;
        Profi_dp.var3._.high  = pOut[Len_var++];
        Profi_dp.var3._.low = pOut[Len_var];

#ifdef _NET_IRQ
        if ( var_tab1[num-1].access == 2 )
          *((lw*)var_tab1[num-1].addr) = Profi_dp.var3.all;
        else
          Profi_dp.err = _DP_NotWr;
#else
        *((lw*)c_t_abKTE[num-1].addr) = Profi_dp.var3.all;
#endif

      }
    }
  }
// Постоянное поле
  for ( x=0; x<Len_Dout; x++ )
  {
	y = x + 16;
    if ( Profi_dp.Prm_Data[y] == 0 )
	{
      pOut[x] = 0;
      Profi_dp.Out_PPO[x] = pOut[x] ;
	}
	else
	{
#ifdef _NET_IRQ
      if ( var_tab1[Profi_dp.Prm_Data[y]-1].access == 2 )
      {
        *((w*)var_tab1[Profi_dp.Prm_Data[y]-1].addr) = pOut[x];
      }
      else
      {
        Profi_dp.err = _DP_NotWr;
      }
      Profi_dp.Out_PPO[x] = pOut[x] ;
#else
    can_wr.kol = Len_Dout + var_val;   // Количество параметров постоянного поля + параметр перменного поля
    can_wr.num[can_wr.cur++] = Profi_dp.Prm_Data[x+16]-1;
    w2w.wtw = pOut[x] ;
    b2b();
    *((w*)c_t_abKTE[Profi_dp.Prm_Data[x+16]-1].addr) = w2w.wtw;
    var_val = 0;
    Profi_dp.Out_PPO[x] = w2w.wtw ;
#endif
	}
  }

 //------------- Обработка выходных данных ---------------

  if ( Profi_dp.Prm_Data[32] == 1 )
  {  // посылка с переменным полем
    Len_var = Len_Din;
    pIn[Len_var++] = Profi_dp.var1.all;
    pIn[Len_var++] = Profi_dp.var2;
    if ( Profi_dp.Op == _Read_DP) // в переменном поле - параметр на чтение
    {
      num = 0;
      if (( Profi_dp.Gr == 0 ) || ( Profi_dp.var2 == 0 ))
      {
        Profi_dp.err = _DP_NotGrNum;
        goto _no_dp;
      }
      Profi_dp.err = _DP_NoErr;
      if ( Profi_dp.Gr < 5)
      {
        num = (Profi_dp.Gr-1) * 32 + Profi_dp.Num;

#ifdef _NET_IRQ
        Profi_dp.var3._.low = *((w*)var_tab1[num-1].addr);
#else
        var_val = 1;
        can_rd.num[can_rd.cur++] = num-1;
        w2w.wtw = *((w*)c_t_abKTE[num-1].addr) ;
        b2b();
        Profi_dp.var3._.low = w2w.wtw ;
#endif

		Profi_dp.var3._.high = 0 ;
        pIn[Len_var+1]   = Profi_dp.var3._.low;
      }
      else
      {
        num = 128 + Profi_dp.var2;

#ifdef _NET_IRQ
        Profi_dp.var3.all = *((lw*)var_tab1[num-1].addr);
#else
        Profi_dp.var3.all = *((lw*)c_t_abKTE[num-1].addr);
#endif

		pIn[Len_var++] = Profi_dp.var3._.high ;
        pIn[Len_var] = Profi_dp.var3._.low;
      }
    }
  }
// Постоянное поле
  for ( x=0; x<Len_Din; x++ )
  {
    if ( Profi_dp.Prm_Data[x] == 0 )
    {
      pIn[x] = 0;
      Profi_dp.In_PPO[x] = pIn[x];
    }
    else
    {

#ifdef _NET_IRQ
      pIn[x] = *((w*)var_tab1[Profi_dp.Prm_Data[x]-1].addr);
      Profi_dp.In_PPO[x] = pIn[x];
#else
      can_rd.kol = Len_Din + var_val;   // Количество параметров постоянного поля + параметр перменного поля
      can_rd.num[can_rd.cur++] = Profi_dp.Prm_Data[x]-1;
      w2w.wtw = *((w*)c_t_abKTE[Profi_dp.Prm_Data[x]-1].addr) ;
      Profi_dp.In_PPO[x] = w2w.wtw;
      b2b();
      pIn[x] = w2w.wtw ;
      var_val = 0;
#endif
    }

  }

//----------------------------------------------
  if ( Profi_dp.Op == _No_DP )
  {
      Profi_dp.err = _DP_NoErr ;
_no_dp :
      Profi_dp.var1.all = 0;
      Profi_dp.var2 = 0;
      Profi_dp.var3.all = 0;
  }
}
  N_Din=_New_DIN_Buffer_Cmd;    // поменять буфер
}

//-------------------------------------------------
// Подпрограмма для main
//-------------------------------------------------
void Work_DP(void)
{

  static byte old_dp_setting = 0;
  lw    ptr;
  byte   bh;

  _Mode_Reg_S = Res_User_Wd;

// Если вынести обработку данных с прерывания в фон,
// то получится
  if ( _r.net_setting._.vkl == 1 )
  {
	 if ( old_dp_setting == 0 )
	 {
		_Mode_Reg_S = START_SPC3;
	 }
	 old_dp_setting = _r.net_setting._.vkl ;
     if ( Profi_dp.flag_dx == 1 )
     {
       do_InOut();
       Profi_dp.flag_dx = 0;
     }
  }
  else
  {
	 if ( old_dp_setting == 1 )
	 {
		_Mode_Reg_S = Go_Offline;
	 }
	 old_dp_setting = _r.net_setting._.vkl ;
     Profi_dp.flag_dx = 0;
     time_dp_bs = Timer1_Ovr;
     return;
  }
    ptr = Addr_Profi + 0x04;
    bh = (*(b*)ptr) & 0xC0;
    if ( bh == 0 )
	{
      if ( (u)(w)(Timer1_Ovr - time_dp_bs) > _Sec(0.2) )
	  {
		 Init_DP();
	  }
	}
	else
	{
	   time_dp_bs = Timer1_Ovr;
	}

#ifdef _NET_IRQ
  ClrMessageDP();
  if ( _r.net_setting._.vkl == 1 ) SetMessageDP();
#else
  message();
#endif

}

//------------------
#ifdef _NET_IRQ
//------------------

void ClrMessageDP(void)
{
  mClr_ServiceMsg2( _Srv2_DP_Wait_Prm );
  mClr_ServiceMsg2( _Srv2_DP_Wait_Cfg );
  mClr_ServiceMsg2( _Srv2_DP_Data_Ex  );
  mClr_ServiceMsg2( _Srv2_DP_Baud_S   );

  mClr_ServiceMsg2( _Srv2_DP_Baud_C   );
  mClr_ServiceMsg2( _Srv2_DP_Control  );
  mClr_ServiceMsg2( _Srv2_DP_Snotf    );
  mClr_ServiceMsg2( _Srv2_DP_S12M     );

  mClr_ServiceMsg2( _Srv2_DP_S6M      );
  mClr_ServiceMsg2( _Srv2_DP_S3M      );
  mClr_ServiceMsg2( _Srv2_DP_S1M      );
  mClr_ServiceMsg2( _Srv2_DP_S500k    );

  mClr_ServiceMsg2( _Srv2_DP_S187k    );
  mClr_ServiceMsg2( _Srv2_DP_S93k     );
  mClr_ServiceMsg2( _Srv2_DP_S45k     );
  mClr_ServiceMsg2( _Srv2_DP_S19k     );

  mClr_ServiceMsg2( _Srv2_DP_S9k      );
  mClr_ServiceMsg2( _Srv2_DP_Nconf    );

  return ;
}

void SetMessageDP(void)
{
  lw ptr;
  byte ah, bh;

    ptr = Addr_Profi + 0x04;
    ah = (*(b*)ptr) & 0x30;
    if ( ah == 0 )         mSet_ServiceMsg2( _Srv2_DP_Wait_Prm );
    else if ( ah == 0x10 ) mSet_ServiceMsg2( _Srv2_DP_Wait_Cfg );
    else if ( ah == 0x20 ) mSet_ServiceMsg2( _Srv2_DP_Data_Ex  );

    bh = (*(b*)ptr) & 0xC0;
    if ( bh == 0 )         mSet_ServiceMsg2( _Srv2_DP_Baud_S );
    else if ( bh == 0x40 ) mSet_ServiceMsg2( _Srv2_DP_Baud_C );
    else if ( bh == 0x80 ) mSet_ServiceMsg2( _Srv2_DP_Control );

   if ( bh != 0 )
   {
     ptr++;
     ah = (*(b*)ptr) & 0x0F;
     switch ( ah )
     {
      case 0:
            mSet_ServiceMsg2( _Srv2_DP_S12M );
            break;
      case 1:
            mSet_ServiceMsg2( _Srv2_DP_S6M );
            break;
      case 2:
            mSet_ServiceMsg2( _Srv2_DP_S3M );
            break;
      case 3:
            mSet_ServiceMsg2( _Srv2_DP_S1M );
            break;
      case 4:
            mSet_ServiceMsg2( _Srv2_DP_S500k );
            break;
      case 5:
            mSet_ServiceMsg2( _Srv2_DP_S187k );
            break;
      case 6:
            mSet_ServiceMsg2( _Srv2_DP_S93k );
            break;
      case 7:
            mSet_ServiceMsg2( _Srv2_DP_S45k );
            break;
      case 8:
            mSet_ServiceMsg2( _Srv2_DP_S19k );
            break;
      case 9:
            mSet_ServiceMsg2( _Srv2_DP_S9k );
            break;
      default:
            mSet_ServiceMsg2( _Srv2_DP_Snotf );
            break;
     }
   }
   if ( Profi_dp.err != _DP_NoErr)  mSet_ServiceMsg2( _Srv2_DP_Nconf );

  return ;
}


void Test_DP(void)
{
   byte bh , bl, al ;
   word ax ;
   lw bx ;

   char *ptr ;

      //   Следует следить, чтобы номера меток здесь и далее шли
      //  последовательно по возрастающей.
  enum { i0, i1, i2 };


              //  Контроль пароля: Полный запрет входа.

      if ( Password_control ( 2 ) == 0 )  return   ;
              //---


      if ( M_FirstCall == 1 )  //  Идентификация первого входа для задания
        {                      // начального условия ...
          output_s ( _Test_DP_txt "\r\n") ;
          M_FirstCall = 0 ;
          Label = 0 , m_index = 0 ;
          return ;
        }

    switch ( Label )
    {
      default: Label = i0;
      case i0:
          if ( TestCompleted_Output() )
            {
              if ( m_index == 0 ) output_s ( _Test_No_txt  ) ;
              else                output_s ( _Test_Yes_txt ) ;
              Label = i1 ;
              break ;
            }

      case i1: // Обработка символов из буфера ввода, без 'while
               // до опустошения' (т.к. при ручном вводе этого не надо)
      if ( TestData_for_Input() )
        {
          mInput_c ( bh ) ;
              if ( bh == Return )  // Выход из этого режима
                {
             end: Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                  return ;   // добавить еще какую-то иниц.
                }
              else if ( bh == Up || bh == Down ) // Изменить выбор.
                {
                  m_index = ~m_index,  Label = i0 ;
                }
              else if ( bh == Enter )
                {
                  if ( m_index == 0 ) goto end ;
                  output_s ( _Waiting_txt "\n\r") ;
                  Label = i2 ;
        }       }
          break ;
    //-----------------

      case i2:
            //  заранее укладываем концовку текста адреса т.к. она всегда постоянная.
          m_buff[6] = 'h', m_buff[7] = '\r', m_buff[8] = 0 ;//NULL ;
          ax = 0;
          al = 0;
            //  Запись в память последовательно чисел 1...256,1...256, и т.д.
          for ( bx = Addr_Profi+0x0040; bx <= Addr_Profi+0x05FF ; bx++ )
           {
             *(b*)bx = ax;
             if ( al == 0)
             {
                if ( ax < 255 ) ax++;
                else al = 1;
             }
             else
             {
                if ( ax > 0 ) ax--;
                else al = 0;
             }
                // Преобразование адреса в символьный вид и вывод
             for ( bl = 5 ; (signed char) bl  >= 0 ; bl -- )
               {
                 bh = (b)( bx >> 4u*bl ) & 0x0fu ;
                 bh +=  ( bh <= 0x9 )  ?  0x30u  :  0x37u ;
                 m_buff[5-bl] = bh ; //output_c ( bh ) ;
               }
             if ( TestCompleted_Output() )  output_s ( m_buff ) ;
             //----------

           }

          ax = 0;
          al = 0;
            // Считывание последовательно из памяти ранее занесенных данных.
          for ( bx = Addr_Profi+0x0040 ; bx <= Addr_Profi+0x05FF ; bx++ )
           {
                // Преобразование адреса в символьный вид и вывод
             for ( bl = 5 ; (signed char) bl  >= 0 ; bl -- )
               {
                 bh = (b)( bx >> 4u*bl ) & 0x0fu ;
                 bh +=  ( bh <= 0x9 )  ?  0x30u  :  0x37u ;
                 m_buff[5-bl] = bh ; //output_c ( bh ) ;
               }
             if( TestCompleted_Output() )  output_s ( m_buff ) ;
             //----------

               //   Проверка после каждого считывания на соответствие ранее
               // занесенным данным.
             if ( ax != *(b*)bx )
               {
                 ptr = _Error_DP_txt ;
                 output_s ( m_buff ) ; // вывод конечного адреса остановки.
                 for ( m_time = Timer1_Ovr ; (w)(Timer1_Ovr-m_time) < _Sec(3.0); ) ;
                 goto end3;
               }
             if ( al == 0)
             {
                if ( ax < 255 ) ax++;
                else al = 1;
             }
             else
             {
                if ( ax > 0 ) ax--;
                else al = 0;
             }
           }
         ptr = "  Ok.   "  ;
   end3:
         output_s ( ptr ) ; // вывод (не)исправности.
         for ( m_time = Timer1_Ovr ; (w)(Timer1_Ovr-m_time) < _Sec(3.0); ) ;
         goto end;
    }

}

#endif

#else // _CM3_
#include "lpc177x_8x_exti.h"

#define  SIZE_PRM_DATA	41

void DP_driver( void )
{
	byte ir0, ir1;

	ir0 = Profi_dp.Regs->IntRegL;
	ir1 = Profi_dp.Regs->IntRegH;

        timer_dp_wait = Timer1_Ovr;

//-----   Low register   -----
	if ( (ir0 & IR_MACReset) == IR_MACReset )
	    Profi_dp.Regs->IntAckRegL = IR_MACReset;

	if ( (ir0 & IR_DataExch) == IR_DataExch )
	    Profi_dp.Regs->IntAckRegL = IR_DataExch;

	if ( (ir0 & IR_BuadRateDetect) == IR_BuadRateDetect )
	    Profi_dp.Regs->IntAckRegL = IR_BuadRateDetect;

	if ( (ir0 & IR_WDControlTimeout) == IR_WDControlTimeout )
	    Profi_dp.Regs->IntAckRegL = IR_WDControlTimeout;

	if ( (ir0 & IR_UserTimerClock) == IR_UserTimerClock )
	{
	    Profi_dp.Regs->IntAckRegL = IR_UserTimerClock;
		Profi_dp.Regs->ModeReg1S = MR1_ResUserWD;
	}
	if ( (ir0 & IR_DXBLinkError) == IR_DXBLinkError )
	    Profi_dp.Regs->IntAckRegL = IR_DXBLinkError;

	if ( (ir0 & IR_NewExtPrmData) == IR_NewExtPrmData )
	    Profi_dp.Regs->IntAckRegL = IR_NewExtPrmData;

	if ( (ir0 & IR_DXBOut) == IR_DXBOut )
	    Profi_dp.Regs->IntAckRegL = IR_DXBOut;
//-----------------------------------

//-----   High register   -----
	if ( (ir1 & IR_NewGCCmd) == IR_NewGCCmd )
	    Profi_dp.Regs->IntAckRegH = IR_NewGCCmd;

	if ( (ir1 & IR_NewSSAData) == IR_NewSSAData )
	{
		DP_SetAddr();
	    Profi_dp.Regs->IntAckRegH = IR_NewSSAData;
	}

	if ( (ir1 & IR_NewCfgData) == IR_NewCfgData )
	{
		DP_SetCfg();
	}

	if ( (ir1 & IR_NewPrmData) == IR_NewPrmData )
	{
		DP_SetParam();
	}

	if ( (ir1 & IR_DiagBufferChng) == IR_DiagBufferChng )
		DP_Diag();
	    Profi_dp.Regs->IntAckRegH = IR_DiagBufferChng;

	if ( (ir1 & IR_DXOut) == IR_DXOut )
	{
		Flag_DataExch = 1;
	    Profi_dp.Regs->IntAckRegH = IR_DXOut;
	}

	if ( (ir1 & IR_PdlEndInd) == IR_PdlEndInd )
	    Profi_dp.Regs->IntAckRegH = IR_PdlEndInd;

	if ( (ir1 & IR_FDLInd) == IR_FDLInd )
	{
	    Profi_dp.Regs->IntAckRegH = IR_FDLInd;
	}
//-----------------------------------
	Profi_dp.Regs->ModeReg1S = MR1_EOI;
}



word Init_DP( void )
{
  byte* ptr;
  EXTI_InitTypeDef eint_cfg;
  byte i;

  Profi_dp.Regs = (TDPRegs*)_EMC_CS2_BEGIN;//&DPRegs;
  Profi_dp.Ident.IdentL = _DP_IDENT_LOW;
  Profi_dp.Ident.IdentH = _DP_IDENT_HIGH;
  Profi_dp.NumDinBuf = 0;
  Profi_dp.NumDoutBuf = 0;
  Profi_dp.LenDin = 0;
  Profi_dp.LenDout = 0;
  Profi_dp.var1.all = 0;
  Profi_dp.var2 = 0;
  Profi_dp.var3.all = 0;
  Profi_dp.err = 0;
  Profi_dp.Op = 0;
  Profi_dp.Gr = 0;
  Profi_dp.Num = 0;
  Flag_DataExch = 0;


 for ( i=0; i<16; i++)
 {
    Profi_dp.In_PPO[i] = 0;
    Profi_dp.Out_PPO[i] = 0;
 }
 for ( i=0; i<40; i++)
    Profi_dp.Prm_Data[i] = 0;

  // pin RESET
  LPC_IOCON->P1_29 = D_RESERV | D_MODE_PULLUP | 0;    // EMC.RESET
  LPC_IOCON->P2_12 = D_RESERV | D_MODE_PULLUP | 1;    // EMC.EINT2
  LPC_GPIO1->DIR |= _DP_RESET;
  NET_Reset();

  // Задержка после RESET'a
for ( byte i=0; i<20; i++)
{
}

   Profi_dp.Regs->IntAckRegL = 0x03;
   for ( ptr = (b*)_DP_START_ADDRRAM; ptr <= (b*)_DP_END_ADDR; ptr++ )
   {
      *ptr = 0;
   }

   if ( ( Profi_dp.Regs->StatusRegL & SR_Offline ) == 0 )
   {
	  Profi_dp.Regs->IntRegL = 0x00;
	  Profi_dp.Regs->IntRegH = 0x00;
	  Profi_dp.Regs->IntAckRegL = 0xFF;
	  Profi_dp.Regs->IntAckRegH = 0xFF;

	  Profi_dp.Regs->ModeReg1R = 0xFF;

	  Profi_dp.Regs->ModeReg0L = MR0_SyncSupport | MR0_FreezeSupport ;
	  Profi_dp.Regs->ModeReg0H = MR0_UserTimeBase | MR0_DPMode | MR0_SpecClrMode ;

      Profi_dp.Regs->IntMaskRegL = 0xE8;// /*IR_WDControlTimeout | IR_UserTimerClock |*/
	  					  //IR_DXBLinkError | IR_NewExtPrmData | IR_DXBOut ; // 0xD8
	  Profi_dp.Regs->IntMaskRegH = 0xC3;//IR_NewGCCmd | IR_NewSSAData | IR_PdlEndInd | IR_FDLInd ; // 0xC3

	  Profi_dp.Regs->WDBaudControl = 0x10;
	  Profi_dp.Regs->MinTsdr = 0x0B;

	  Profi_dp.Regs->UserWDValueL = 0xFF;
	  Profi_dp.Regs->UserWDValueH = 0x01;

	  Profi_dp.Regs->RealNoAddChng = 0xFF;

	  Profi_dp.Regs->IdentLow  = Profi_dp.Ident.IdentL ;
	  Profi_dp.Regs->IdentHigh = Profi_dp.Ident.IdentH ;
	  Profi_dp.Regs->TSAddr	  = _r.DP_addr;

//-----   Настройка буферов   -----
//    Выходной буфер
	  Profi_dp.Regs->LenDoutBuf = _SIZE_DOUT_BUF ;
	  ptr = (byte*)&(Profi_dp.Regs->DoutBuf1);
	  Profi_dp.Regs->DoutBufPtr1 = (byte)((((lword)ptr) & 0x7FF) >> 3);
	  ptr = (byte*)&(Profi_dp.Regs->DoutBuf2);
	  Profi_dp.Regs->DoutBufPtr2 = (byte)((((lword)ptr) & 0x7FF) >> 3);
	  ptr = (byte*)&(Profi_dp.Regs->DoutBuf3);
	  Profi_dp.Regs->DoutBufPtr3 = (byte)((((lword)ptr) & 0x7FF) >> 3);

//    Входной буфер
	  Profi_dp.Regs->LenDinBuf = _SIZE_DIN_BUF ;
	  ptr = (byte*)&(Profi_dp.Regs->DinBuf1);
	  Profi_dp.Regs->DinBufPtr1 = (byte)((((lword)ptr) & 0x7FF) >> 3);
	  ptr = (byte*)&(Profi_dp.Regs->DinBuf2);
	  Profi_dp.Regs->DinBufPtr2 = (byte)((((lword)ptr) & 0x7FF) >> 3);
	  ptr = (byte*)&(Profi_dp.Regs->DinBuf3);
	  Profi_dp.Regs->DinBufPtr3 = (byte)((((lword)ptr) & 0x7FF) >> 3);

//    Диагностический буфер
	  Profi_dp.Regs->LenDiagBuf1 = 6;//_SIZE_DIAG_BUF ;
	  ptr = (byte*)&(Profi_dp.Regs->DiagBuf1);
	  Profi_dp.Regs->DiagBufPtr1 = (byte)((((lword)ptr) & 0x7FF) >> 3);
	  Profi_dp.Regs->LenDiagBuf2 = _SIZE_DIAG_BUF ;
	  ptr = (byte*)&(Profi_dp.Regs->DiagBuf2);
	  Profi_dp.Regs->DiagBufPtr2 = (byte)((((lword)ptr) & 0x7FF) >> 3);

//    Auxialiary буфер
	  Profi_dp.Regs->LenCntrlBuf1 = _SIZE_CTRL_BUF ;
	  Profi_dp.Regs->LenCntrlBuf2 = _SIZE_CTRL_BUF ;
	  Profi_dp.Regs->AuxBufSel = 0;
	  ptr = (byte*)&(Profi_dp.Regs->AuxBuf1);
	  Profi_dp.Regs->AuxBufPtr1 = (byte)((((lword)ptr) & 0x7FF) >> 3);
	  ptr = (byte*)&(Profi_dp.Regs->AuxBuf2);
	  Profi_dp.Regs->AuxBufPtr2 = (byte)((((lword)ptr) & 0x7FF) >> 3);

//    Slave Address буфер
	  Profi_dp.Regs->LenSSAData = 5;//_SIZE_SSA_BUF ;
	  ptr = (byte*)&(Profi_dp.Regs->SSABuf);
	  Profi_dp.Regs->SSABufPtr = (byte)((((lword)ptr) & 0x7FF) >> 3);

//    Буфер параметризации
	  Profi_dp.Regs->LenPrmData = _SIZE_PRM_BUF ;
	  ptr = (byte*)&(Profi_dp.Regs->PrmBuf);
	  Profi_dp.Regs->PrmBufPtr = (byte)((((lword)ptr) & 0x7FF) >> 3);

//    Буфер конфигурации
	  Profi_dp.Regs->LenCfgData = _SIZE_CFG_BUF ;
	  ptr = (byte*)&(Profi_dp.Regs->CfgBuf);
	  Profi_dp.Regs->CfgBufPtr = (byte)((((lword)ptr) & 0x7FF) >> 3);

//    Буфер чтения конфигурации
	  Profi_dp.Regs->LenReadCfgData = _SIZE_CFG_BUF ;
	  ptr = (byte*)&(Profi_dp.Regs->ReadCfgBuf);

	  Profi_dp.Regs->ReadCfgBufPtr = (byte)((((lword)ptr) & 0x7FF) >> 3);

	  Profi_dp.Regs->ModeReg1S = MR1_EOI;
//-----------------------------------

//    Настраиваем прерывани
	  eint_cfg.EXTI_Line = EXTI_EINT2;
	  eint_cfg.EXTI_Mode = EXTI_MODE_LEVEL_SENSITIVE;//EXTI_MODE_EDGE_SENSITIVE;
	  eint_cfg.EXTI_polarity = EXTI_POLARITY_LOW_ACTIVE_OR_FALLING_EDGE;
	  EXTI_Config( &eint_cfg );

	  Profi_dp.Regs->ModeReg1S = MR1_EOI;
      EXTI_Config(&eint_cfg);
      NVIC_SetPriority( EINT2_IRQn, IntPriority(0, 3));
      NVIC_EnableIRQ( EINT2_IRQn );
	  if ( _r.net_setting._.vkl == 1 )
	     Profi_dp.Regs->ModeReg1S = MR1_Start;
   }

   timer_dp_wait = Timer1_Ovr;
   count_dp_wait = 0;
   return 1;
}


void DP_SetIdent( TIdentDP ident )
{
   Profi_dp.Ident.IdentL = ident.IdentL;
   Profi_dp.Ident.IdentH = ident.IdentH;
}

byte DP_GetSpeed( void )
{
  return Profi_dp.Regs->StatusRegH;
}

void DP_SetAddr( void )
{
  byte reg;
  if (( Profi_dp.Regs->SSABuf[1] == Profi_dp.Ident.IdentL ) && ( Profi_dp.Regs->SSABuf[1] == Profi_dp.Ident.IdentH ))
   {
//  Записать новый адрес
   }
   reg = Profi_dp.Regs->SSABufferFreeCmd;

}

void DP_SetParam( void )
{
   byte LenPrm, reg,i;
   byte* ptr;
//	   DP_delay();

	if ( Profi_dp.Regs->LenPrmData != 41)//SIZE_PRM_DATA )
	{
	   Profi_dp.err = _DP_NotPrm;
	   reg = Profi_dp.Regs->UserPrmDataNotOk;
	}
	else
	{
	   Profi_dp.err = _DP_NoErr;
	   LenPrm = Profi_dp.Regs->LenPrmData - 8;
	   ptr = (byte*)(_DP_START_ADDR + ((lword)(Profi_dp.Regs->PrmBufPtr) << 3)+8);
	   for ( i = 0; i < LenPrm; i++ )
	   {
		  Profi_dp.Prm_Data[i] = *ptr;
		  ptr++;
       }
	   reg = Profi_dp.Regs->UserPrmDataOk;
	}
   return ;
}


void DP_SetCfg( void )
{
  byte i, ah = 0, al = 0;
  byte length = Profi_dp.Regs->LenCfgData;
  byte SpecFormat = 0;
  byte outp = 0, inp = 0;
  byte reg;
  byte* ptr;

	   ptr = (byte*)(_DP_START_ADDR + ((lword)(Profi_dp.Regs->CfgBufPtr) << 3));
	   for ( i = 0; i < length; i++ )
	   {
		  Profi_dp.ConfigData[i] = *ptr;
		  ptr++;
       }
  for ( i = 0; i < length; i++ )
  {
	 ah = Profi_dp.ConfigData[i] & _DP_IO;
	 switch ( ah )
	 {
	 	case _DP_IO_SPEC :
			if ( SpecFormat == 0 )
			{
			   SpecFormat = Profi_dp.ConfigData[i] & _DP_SPEC_DATA;
			}
			else
			{
				switch ( SpecFormat )
				{
					case _DP_SPEC_IN :
						if ( Profi_dp.ConfigData[i] & _DP_TYPE )
						   inp = inp + ((Profi_dp.ConfigData[i] & _DP_SIZE) + 1) * 2 ;
						else
						   inp = inp + ((Profi_dp.ConfigData[i] & _DP_SIZE) + 1) ;
						break;
					case _DP_SPEC_OUT :
						if ( Profi_dp.ConfigData[i] & _DP_TYPE )
						   outp = outp + ((Profi_dp.ConfigData[i] & _DP_SIZE) + 1) * 2 ;
						else
						   outp = outp + ((Profi_dp.ConfigData[i] & _DP_SIZE) + 1) ;
						break;
					case _DP_SPEC_INOUT :
						if ( Profi_dp.ConfigData[i] & _DP_TYPE )
						{
						   if ( al == 1 )
						   {
						   	  al = 0;
							  SpecFormat = 0;
						      inp = inp + ((Profi_dp.ConfigData[i] & _DP_SIZE) + 1) * 2 ;

						   }
						   else
						   {
							  al = 1;
                                                          reg = Profi_dp.ConfigData[i] & _DP_SIZE;
                                                          reg = (reg+1)*2;
                                                          outp = outp + reg;
						   }
						}
						else
						{
						   if ( al == 1 )
						   {
						   	  al = 0;
							  SpecFormat = 0;
						      inp = inp + ((Profi_dp.ConfigData[i] & _DP_SIZE) + 1) ;
						   }
						   else
						   {
							  al = 1;
						      outp = outp + ((Profi_dp.ConfigData[i] & _DP_SIZE) + 1) ;
						   }
						}
						break;
				}
			}
			break;
	 	case _DP_IO_INPUT :
			if ( Profi_dp.ConfigData[i] & _DP_TYPE )
			   inp = inp + ((Profi_dp.ConfigData[i] & _DP_SIZE) + 1) * 2 ;
			else
			   inp = inp + ((Profi_dp.ConfigData[i] & _DP_SIZE) + 1) ;
			break;
	 	case _DP_IO_OUTPUT :
			if ( Profi_dp.ConfigData[i] & _DP_TYPE )
			   outp = outp + ((Profi_dp.ConfigData[i] & _DP_SIZE) + 1) * 2 ;
			else
			   outp = outp + ((Profi_dp.ConfigData[i] & _DP_SIZE) + 1) ;
			break;
	 	case _DP_IO_INOUT :
			if ( Profi_dp.ConfigData[i] & _DP_TYPE )
			{
			   inp  = inp  + ((Profi_dp.ConfigData[i] & _DP_SIZE) + 1) * 2 ;
			   outp = outp + ((Profi_dp.ConfigData[i] & _DP_SIZE) + 1) * 2 ;
			}
			else
			{
			   inp  = inp  + ((Profi_dp.ConfigData[i] & _DP_SIZE) + 1) ;
			   outp = outp + ((Profi_dp.ConfigData[i] & _DP_SIZE) + 1) ;
			}
			break;
	 }
  }

  Profi_dp.Regs->LenDinBuf = inp;
  Profi_dp.Regs->LenDoutBuf = outp;

  if ( Profi_dp.Prm_Data[32] == 1 ) // имеется переменное поле
  {
 /*   Profi_dp.LenDout = ( outp - 7)/2;
    Profi_dp.LenDin = ( inp - 7)/2;
    if ( ( outp < 8 ) || ( inp < 8 ) )
    {
        Profi_dp.err = _DP_NotVar;
        Profi_dp.var1.all = 0;
        Profi_dp.var2 = 0;
        Profi_dp.var3.all = 0;
    }
*/  }
  else
  {
    Profi_dp.LenDout = ( outp + 1)/2;
    Profi_dp.LenDin = ( inp + 1)/2;
  }

  Profi_dp.Regs->ModeReg1S = MR1_EnChngCfgBuf ;
  reg = Profi_dp.Regs->UserCfgDataOk + Profi_dp.Regs->NewDinBufferCmd ;
  NumDinBuf = Profi_dp.Regs->NewDinBufferCmd;
}

byte DP_Diag( void )
{
  byte reg;

  reg = Profi_dp.Regs->DiagBufferSM & 3;
//-------------изменить буфер диагностики------------------------
  reg = Profi_dp.Regs->NewDiagBufferCmd;
  return reg;

}


void DP_DataExch( void )
{
   byte* pOut;
   byte* pIn;
   word x, y;
   word inW, outW;

   NumDoutBuf = Profi_dp.Regs->NewDoutBufferCmd & 3;
   switch (NumDoutBuf)
   {
    case 1:
         pOut = Profi_dp.Regs->DoutBuf1 ;
         break;
	case 2:
         pOut = Profi_dp.Regs->DoutBuf2 ;
         break;
	case 3:
         pOut = Profi_dp.Regs->DoutBuf3 ;
         break;
  };

  switch (NumDinBuf)
  {
    case 1:
         pIn = Profi_dp.Regs->DinBuf1;
         break;
	case 2:
         pIn = Profi_dp.Regs->DinBuf2;
         break;
	case 3:
         pIn = Profi_dp.Regs->DinBuf3;
         break;
  };

	  if ( _r.net_setting._.vkl == 1 )
  {
     if ( Profi_dp.Prm_Data[32] == 1 )
     {
// tds - эта часть никому не нужна, а иногда путает Заказчика
/*		LengthVar = Profi_dp.LenDout;
        Profi_dp.var1.all  = pOut[LengthVar++];
        Profi_dp.var2      = pOut[LengthVar++];

        Profi_dp.Op = (b)Profi_dp.var1._.op;
        Profi_dp.Gr = (b)Profi_dp.var1._.gr;
        Profi_dp.Num = Profi_dp.var2;

	    if ( Profi_dp.Op == _Write_DP)  //
        {
           num = 0;
           if (( Profi_dp.Gr == 0) || ( Profi_dp.var2 == 0 ))
           {
              Profi_dp.err = _DP_NotGrNum;
              goto _no_dp;
           }
           Profi_dp.err = _DP_NoErr;
           if ( Profi_dp.Gr  < 5)      // номер параметра из var_tab
           {
              num = (Profi_dp.Gr-1) * 32 + Profi_dp.Num;
              Profi_dp.var3._.high  = 0 ;

              Profi_dp.var3._.low   = pOut[LengthVar+1] ;
              if ( var_tab1[num-1].access == 2 )
                 *((w*)var_tab1[num-1].addr) = pOut[LengthVar+1] ;
             else
                 Profi_dp.err = _DP_NotWr;

           }
           else
           {
              num = 128 + Profi_dp.var2;
              Profi_dp.var3._.high  = pOut[LengthVar++];
              Profi_dp.var3._.low = pOut[LengthVar];
              if ( var_tab1[num-1].access == 2 )
                 *((lw*)var_tab1[num-1].addr) = Profi_dp.var3.all;
              else
                 Profi_dp.err = _DP_NotWr;
           }
        }      */
     }

     for ( x = 0; x < Profi_dp.LenDout; x++ )
     {
	    y = x + 16;
        if ( Profi_dp.Prm_Data[y] == 0 )
	    {
           pOut[x] = 0;
           Profi_dp.Out_PPO[x] = pOut[x] ;
	    }
	    else
	    {
			outW = (word)*pOut << 8;
			pOut++;
			outW +=  (word)*pOut ;
			pOut++;
           if ( var_tab1[Profi_dp.Prm_Data[y]-1].access == 2 )
          {
             *((w*)var_tab1[Profi_dp.Prm_Data[y]-1].addr) = outW;
          }
          else
          {
             Profi_dp.err = _DP_NotWr;
          }
          Profi_dp.Out_PPO[x] = outW ;
  }
     }

 //----------------------------

     if ( Profi_dp.Prm_Data[32] == 1 )
     {  // посылка с переменным полем
// tds - эта часть никому не нужна, а иногда путает Заказчика
/*        Len_var = Profi_dp.LenDin;
        pIn[Len_var++] = Profi_dp.var1.all;
        pIn[Len_var++] = Profi_dp.var2;
        if ( Profi_dp.Op == _Read_DP) // в переменном поле - параметр на чтение
        {
           num = 0;
           if (( Profi_dp.Gr == 0 ) || ( Profi_dp.var2 == 0 ))
           {
              Profi_dp.err = _DP_NotGrNum;
              goto _no_dp;
           }
           Profi_dp.err = _DP_NoErr;
           if ( Profi_dp.Gr < 5)
           {
               num = (Profi_dp.Gr-1) * 32 + Profi_dp.Num;

               Profi_dp.var3._.low = *((w*)var_tab1[num-1].addr);

	           Profi_dp.var3._.high = 0 ;
               pIn[Len_var+1]   = Profi_dp.var3._.low;
           }
           else
           {
              num = 128 + Profi_dp.var2;

              Profi_dp.var3.all = *((lw*)var_tab1[num-1].addr);

		      pIn[LengthVar++] = Profi_dp.var3._.high ;
              pIn[LengthVar] = Profi_dp.var3._.low;
           }
        } */
     }
// Постоянное поле
     for ( x=0; x<Profi_dp.LenDin; x++ )
     {
        if ( Profi_dp.Prm_Data[x] == 0 )
        {
           pIn[x] = 0;
		   inW = 0;
           Profi_dp.In_PPO[x] = inW;
        }
        else
        {

		   inW = *((w*)var_tab1[Profi_dp.Prm_Data[x]-1].addr);
		   *pIn = (byte)((inW & 0xFF00) >> 8);
		   pIn++;
		   *pIn = (byte)(inW & 0x00FF);
		   pIn++;
           Profi_dp.In_PPO[x] = inW;
        }

     }

//----------------------------------------------
     if ( Profi_dp.Op == _No_DP )
     {
        Profi_dp.err = _DP_NoErr ;
//_no_dp :
        Profi_dp.var1.all = 0;
        Profi_dp.var2 = 0;
        Profi_dp.var3.all = 0;
     }
  }
  NumDinBuf = Profi_dp.Regs->NewDinBufferCmd;
}

void Work_DP(void)
{

  static byte old_dp_setting = 0;

  if ( _r.net_setting._.vkl == 1 )
  {
	 if ( old_dp_setting == 0 )
	 {
		//Profi_dp.Regs->ModeReg1S = MR1_Start;
           Init_DP();
	 }
	 old_dp_setting = _r.net_setting._.vkl ;


          if ((u)((w)(Timer1_Ovr - timer_dp_wait)) >= _Sec(0.2))
          {
              Init_DP();
//              timer_dp_wait = Timer1_Ovr;
              count_dp_wait++;
          }


	 if (( Flag_DataExch == 1) && ((Profi_dp.Regs->StatusRegL & 0x30)==0x20))
	 {
		Flag_DataExch = 0;
		DP_DataExch( );
	 }
  }
  else
  {
	 if ( old_dp_setting == 1 )
	 {
		Profi_dp.Regs->ModeReg1S = MR1_GoOffline;
	 }
	 old_dp_setting = _r.net_setting._.vkl ;
	 Flag_DataExch = 0;
  }

  ClrMessageDP();
  if ( _r.net_setting._.vkl == 1 ) SetMessageDP();

}


void ClrMessageDP(void)
{
  mClr_ServiceMsg2( _Srv2_DP_Wait_Prm );
  mClr_ServiceMsg2( _Srv2_DP_Wait_Cfg );
  mClr_ServiceMsg2( _Srv2_DP_Data_Ex  );
  mClr_ServiceMsg2( _Srv2_DP_Baud_S   );

  mClr_ServiceMsg2( _Srv2_DP_Baud_C   );
  mClr_ServiceMsg2( _Srv2_DP_Control  );
  mClr_ServiceMsg2( _Srv2_DP_Snotf    );
  mClr_ServiceMsg2( _Srv2_DP_S12M     );

  mClr_ServiceMsg2( _Srv2_DP_S6M      );
  mClr_ServiceMsg2( _Srv2_DP_S3M      );
  mClr_ServiceMsg2( _Srv2_DP_S1M      );
  mClr_ServiceMsg2( _Srv2_DP_S500k    );

  mClr_ServiceMsg2( _Srv2_DP_S187k    );
  mClr_ServiceMsg2( _Srv2_DP_S93k     );
  mClr_ServiceMsg2( _Srv2_DP_S45k     );
  mClr_ServiceMsg2( _Srv2_DP_S19k     );

  mClr_ServiceMsg2( _Srv2_DP_S9k      );
  mClr_ServiceMsg2( _Srv2_DP_Nconf    );

  return ;
}

void SetMessageDP(void)
{
  byte ah, bh;

	ah = Profi_dp.Regs->StatusRegL & 0x30;
    if ( ah == 0 )         mSet_ServiceMsg2( _Srv2_DP_Wait_Prm );
    else if ( ah == 0x10 ) mSet_ServiceMsg2( _Srv2_DP_Wait_Cfg );
    else if ( ah == 0x20 ) mSet_ServiceMsg2( _Srv2_DP_Data_Ex  );

    bh = Profi_dp.Regs->StatusRegL & 0xC0;
    if ( bh == 0 )         mSet_ServiceMsg2( _Srv2_DP_Baud_S );
    else if ( bh == 0x40 ) mSet_ServiceMsg2( _Srv2_DP_Baud_C );
    else if ( bh == 0x80 ) mSet_ServiceMsg2( _Srv2_DP_Control );

   if ( bh != 0 )
   {
	 ah = Profi_dp.Regs->StatusRegH & 0x0F;
     switch ( ah )
     {
      case 0:
            mSet_ServiceMsg2( _Srv2_DP_S12M );
            break;
      case 1:
            mSet_ServiceMsg2( _Srv2_DP_S6M );
            break;
      case 2:
            mSet_ServiceMsg2( _Srv2_DP_S3M );
            break;
      case 3:
            mSet_ServiceMsg2( _Srv2_DP_S1M );
            break;
      case 4:
            mSet_ServiceMsg2( _Srv2_DP_S500k );
            break;
      case 5:
            mSet_ServiceMsg2( _Srv2_DP_S187k );
            break;
      case 6:
            mSet_ServiceMsg2( _Srv2_DP_S93k );
            break;
      case 7:
            mSet_ServiceMsg2( _Srv2_DP_S45k );
            break;
      case 8:
            mSet_ServiceMsg2( _Srv2_DP_S19k );
            break;
      case 9:
            mSet_ServiceMsg2( _Srv2_DP_S9k );
            break;
      default:
            mSet_ServiceMsg2( _Srv2_DP_Snotf );
            break;
     }
   }
   if ( Profi_dp.err != _DP_NoErr)  mSet_ServiceMsg2( _Srv2_DP_Nconf );

  return ;
}


void Test_DP(void)
{
   byte bh , bl, al ;
   word ax ;
   lw bx ;

   char *ptr ;

      //   Следует следить, чтобы номера меток здесь и далее шли
      //  последовательно по возрастающей.
  enum { i0, i1, i2 };


              //  Контроль пароля: Полный запрет входа.

      if ( Password_control ( 2 ) == 0 )  return   ;
              //---


      if ( M_FirstCall == 1 )  //  Идентификация первого входа для задания
        {                      // начального условия ...
          output_s ( _Test_DP_txt "\r\n") ;
          M_FirstCall = 0 ;
          Label = 0 , m_index = 0 ;
          return ;
        }

    switch ( Label )
    {
      default: Label = i0;
      case i0:
          if ( TestCompleted_Output() )
            {
              if ( m_index == 0 ) output_s ( _Test_No_txt  ) ;
              else                output_s ( _Test_Yes_txt ) ;
              Label = i1 ;
              break ;
            }

      case i1: // Обработка символов из буфера ввода, без 'while
               // до опустошения' (т.к. при ручном вводе этого не надо)
      if ( TestData_for_Input() )
        {
          mInput_c ( bh ) ;
              if ( bh == Return )  // Выход из этого режима
                {
             end: Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                  return ;   // добавить еще какую-то иниц.
                }
              else if ( bh == Up || bh == Down ) // Изменить выбор.
                {
                  m_index = ~m_index,  Label = i0 ;
                }
              else if ( bh == Enter )
                {
                  if ( m_index == 0 ) goto end ;
                  output_s ( _Waiting_txt "\n\r") ;
                  Label = i2 ;
        }       }
          break ;
    //-----------------

      case i2:
            //  заранее укладываем концовку текста адреса т.к. она всегда постоянная.
          m_buff[6] = 'h', m_buff[7] = '\r', m_buff[8] = 0 ;//NULL ;
          ax = 0;
          al = 0;
            //  Запись в память последовательно чисел 1...256,1...256, и т.д.
          for ( bx = _DP_START_ADDRRAM; bx <= _DP_END_ADDR ; bx++ )
           {
             *(b*)bx = ax;
             if ( al == 0)
             {
                if ( ax < 255 ) ax++;
                else al = 1;
             }
             else
             {
                if ( ax > 0 ) ax--;
                else al = 0;
             }
                // Преобразование адреса в символьный вид и вывод
             for ( bl = 5 ; (signed char) bl  >= 0 ; bl -- )
               {
                 bh = (b)( bx >> 4u*bl ) & 0x0fu ;
                 bh +=  ( bh <= 0x9 )  ?  0x30u  :  0x37u ;
                 m_buff[5-bl] = bh ; //output_c ( bh ) ;
               }
             if ( TestCompleted_Output() )  output_s ( m_buff ) ;
             //----------

           }

          ax = 0;
          al = 0;
            // Считывание последовательно из памяти ранее занесенных данных.
          for ( bx = _DP_START_ADDRRAM ; bx <= _DP_END_ADDR ; bx++ )
           {
                // Преобразование адреса в символьный вид и вывод
             for ( bl = 5 ; (signed char) bl  >= 0 ; bl -- )
               {
                 bh = (b)( bx >> 4u*bl ) & 0x0fu ;
                 bh +=  ( bh <= 0x9 )  ?  0x30u  :  0x37u ;
                 m_buff[5-bl] = bh ; //output_c ( bh ) ;
               }
             if( TestCompleted_Output() )  output_s ( m_buff ) ;
             //----------

               //   Проверка после каждого считывания на соответствие ранее
               // занесенным данным.
             if ( ax != *(b*)bx )
               {
                 ptr = _Error_DP_txt ;
                 output_s ( m_buff ) ; // вывод конечного адреса остановки.
                 for ( m_time = Timer1_Ovr ; (w)(Timer1_Ovr-m_time) < _Sec(3.0); ) ;
                 goto end3;
               }
             if ( al == 0)
             {
                if ( ax < 255 ) ax++;
                else al = 1;
             }
             else
             {
                if ( ax > 0 ) ax--;
                else al = 0;
             }
           }
         ptr = "  Ok.   "  ;
   end3:
         output_s ( ptr ) ; // вывод (не)исправности.
         for ( m_time = Timer1_Ovr ; (w)(Timer1_Ovr-m_time) < _Sec(3.0); ) ;
         goto end;
    }

}


#endif // _CM3_

