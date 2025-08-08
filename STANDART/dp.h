#ifndef _CM3_

#ifdef  _NET_IRQ
  #define Addr_Profi        0x300000    // Для RCP
#else   // плата CAN-Profibus
  #define Addr_Profi        0x2000      // Для Profibus-платы
#endif

  #define OWN_ADDRESS     5   // адрес слэйв устройства по умолчанию

#ifdef   _KTE
  #define IDENT1      0x74
  #define IDENT0      0x01
#endif

#ifdef   _KTE_GD
  #define IDENT1      0x74
  #define IDENT0      0x01
#endif

#ifdef   _KTEV
  #define IDENT1      0x74
  #define IDENT0      0x01
#endif

#ifdef   _CCT
  #define IDENT1      0x74
  #define IDENT0      0x02
#endif

#ifdef   _BTE
  #define IDENT1      0x74
  #define IDENT0      0x03
#endif

#ifdef   _Elektroliz
  #define IDENT1      0x74
  #define IDENT0      0x04
#endif

  #define   Low       0
  #define   High      1
  #define   Rising    2
  #define   Falling   3


  #define _Len_Dout_Buf     64
  #define _Len_Din_Buf      64
  #define _Len_Diag_Buf     6
  #define _Len_Cntrl_Buf    64
  #define _Len_SSA_Data     5
  #define _Len_Prm_Data     64
  #define _Len_Spec_Prm_buf 64
  #define _Len_Cfg_Buf      64


  // Регистр прерывания
  #define MAC_Reset           0x01    //;0 the SPC3 has arrived at the offline (through  setting the 'Go_Offline bit' or through a RAM access violation)
  #define GO_LEAVE_DATA_EX    0x02    //;1 The DP_SM has entered or exited the 'DATA_EX' state
  #define Baudrate_Detect     0x04    //;2 The SPC3 has exited the 'Baud_Search state' and found a baud rate.
  #define WD_DP_MODE_TIMEOUT  0x08    //;3 The watchdog timer has run out in the 'DP_Control' WD state.
  #define User_Timer_Clock    0x10    //;4 The time base for the User_Timer_Clocks has run out (1/10ms).
  #define NEW_GC_COMMAND      0x01    //;8 The SPC3 has received a 'Global_Control telegram' with a changed 'GC_Command-Byte,' and this byte is stored in the 'R_GC_Command' RAM cell.
  #define NEW_SSA_DATA        0x02    //;9 The SPC3 has received a 'Set_Slave_Address telegram' and made the data available in the SSA buffer.
  #define NEW_CFG_DATA        0x04    //;10 The SPC3 has received a 'Check_Cfg telegram' and made the data available in the Cfg buffer.
  #define NEW_PRM_DATA        0x08    //;11 The SPC3 has received a 'Set_Param telegram' and made the data available in the Prm buffer.
  #define Diag_Puffer_Changed 0x10    //;12 Due to the request made by 'New_Diag_Cmd,' SPC3 exchanged the diagnostics buffer and again made the old buffer available to the user.
  #define DX_OUT              0x20    //;The SPC3 has received a 'Write_Read_Data telegram' and made the new output data
                                              //  ;available in the N buffer. For a 'Power_On' or for a 'Leave_Master,' the SPC3 deletes
                                              //  ;the N buffer and also generates this interrupt.
  //Mask for Mode Reg0
  #define DIS_START_CONTROL   0x01    //;0 Monitoring the following start bit in UART. Set-Param Telegram overwrites this memory cell in the DP mode. (Refer to the user-specific data.) 0 - enabled.
  #define DIS_STOP_CONTROL    0x02    //;1 Stop bit monitoring in UART. Set-Param telegram overwrites this memory cell in the DP mode. (Refer to the user-specific data.)
  #define EN_FDL_DDB          0x04    //;2 reserved
  #define MinTSDR             0x08    //;3 Default setting for the MinTSDR after reset for DP operation or combi operation 0 = Pure DP operation (default configuration!) 1 = Combi operation
  #define INT_POL             0x10    //;4 Polarity of the interrupt output 0 = The interrupt output is low-active. 1 = The interrupt output is high-active.
  #define EARLY_RDY           0x20    //;5 Moved up ready signal 0 = Ready is generated when the data are valid (read) or when the data are accepted (write). 1 = Ready is moved up by one clock pulse.
  #define SYNC_SUPPORTED      0x40    //;6  1 = Sync_Mode is supported.
  #define FREEZE_SUPPORTED    0x80    //;7  1 = Freeze_Mode is supported.
  #define DP_MODE             0x01    //;8  0 = DP_Mode is disabled. 1 = DP_Mode is enabled. SPC3 sets up all DP_SAPs.
  #define EOI_Time_base       0x02    //;9 Time base for the end of interrupt pulse 0 = The interrupt inactive time is at least 1 usec long. 1 = The interrupt inactive time is at least 1 ms long.
  #define USER_TIMEBASE       0x04    //;10 0 = The User_Time_Clock-Interrupt occurs every 1 ms. 1 = The User_Time_Clock-Interrupt occurs every 10 ms.
  #define WD_Test             0x08    //;11 Test mode for the Watchdog-Timer, no function mode 0 = The WD runs in the function mode. 1 = Not permitted
  #define Spec_Prm_Puf_Mode   0x10    //;12 Special parameter buffer 0 = No special parameter buffer. 1 1 = Special parameter buffer mode .Parameterization data will be stored directly in the special parameter buffer.
  #define Spec_Clear_Mode     0x20    //;13 Special Clear Mode (Fail Safe Mode) 0 = No special clear mode. 1 = Special clear mode. SPC3 will accept datea telegramms with data unit = 0.

  //Mask for Set/Reset bit
  #define START_SPC3          0x01    //Exiting the Offline state 1 = SPC3 exits Offline and goes to passiv-idle addition, the idle timer and Wd timer are started and 'Go_Offline = 0' is set.
  #define EOI                 0x02    //End of Interrupt 1 = End of Interrupt: SPC3 switches the interrupt outputs to inactive and again sets EOI to log.'0.'
  #define Go_Offline          0x04    //Going into the offline state 1 =
  #define User_Leave_Master   0x08    //Request to the DP_SM to go to 'Wait_Prm.' 1 = The user causes the DP_SM to go to 'Wait_Prm.' After this action, SPC3 sets User_Leave_Master to log.'0.'
  #define En_Change_Cfg_Puffer    0x10    //Enabling buffer exchange (Cfg buffer for Read_Cfg buffer) 0 = With 'User_Cfg_Data_Okay_Cmd,' the Cfg buffer may not be exchanged for the Read_Cfg buffer.
                                                // 1 = With 'User_Cfg_Data_Okay_Cmd,' the Cfg buffer must be exchanged for theRead_Cfg buffer.
  #define Res_User_Wd         0x20    //Resetting the User_WD_Timers

  #define _No_DP              0x00
  #define _Read_DP            0x01
  #define _Write_DP           0x02

//--- Ошибка по сети Profibus ---
  #define _DP_NoErr           0x00
  #define _DP_NotPrm          0x01
  #define _DP_NotGrNum        0x02
  #define _DP_NotVar          0x04
  #define _DP_NotWr           0x08

  struct Profibus
  {
    word  addr_Cfg_Buf;
    word  addr_Prm_Buf;
    word  In_PPO[32];
    word  Out_PPO[32];
    byte  Prm_Data[40];
    union
    {
      struct
      {
        word op : 8;
        word gr : 8;
      } _;
      word all;
    } var1;
    word  var2;
    union
    {
      struct
      {
        word  low ;
        word  high;
      } _;
      lw all;
    } var3;
    byte err;
    byte Op;
    byte Gr;
    word Num;

	byte flag_dx ;
  };

union uWord
{
  int wtw;
  struct
  {
    int b1 : 8;
    int b2 : 8;
  } btb;
};

union  dp_set
{
  byte all ;
  struct
   {
     byte  rezerved   : 7 ;
     byte  vkl        : 1 ;
   } _ ;
} ;

#define   _dp_cfg_vkl         0x01


#ifdef _NET_INCLUDE

  struct Profibus Profi_dp;
  char N_Din,N_Dout;
  byte spec_form ;
  word cycle_dp;
  word Timer_DP;
  byte Len_Din, Len_Dout;
  byte data_in, data_out;
  word time_dp_bs;

  word Init_SPC(void);
  void Init_DP(void);
  void DP_driver(void);
  __interrupt void DP_Interrupt (void);
  char do_Addr(void);
  char do_Prm(void);
  char do_Cfg(void);
  char do_Diag (void);
  void do_InOut(void);
  void Work_DP(void);
  void ClrMessageDP(void);
  void SetMessageDP(void);

#else

  extern  struct Profibus Profi_dp;
  extern  char N_Din,N_Dout;
  extern  byte spec_form ;
  extern  word cycle_dp;
  extern  byte Len_Din, Len_Dout;
  extern  byte data_in, data_out;
  extern  word time_dp_bs;

  extern  word Init_SPC(void);
  extern  void Init_DP(void);
  extern  void DP_driver(void);
  extern  __interrupt void DP_Interrupt (void);
  extern  char do_Addr(void);
  extern  char do_Prm(void);
  extern  char do_Cfg(void);
  extern  char do_Diag (void);
  extern  void do_InOut(void);
  extern  void Work_DP(void);
  extern  void ClrMessageDP(void);
  extern  void SetMessageDP(void);



#endif // end DP_INCLUDE

// переменные объявленные в SPC3.asm
  extern  char _Int_Req_Reg[];
  extern  char _Int_Reg[];
  extern  char _Status_Reg[];
  extern  char _Mode_Reg0[];
  extern  char _DIN_Buffer_SM;
  extern  char _New_DIN_Buffer_Cmd;
  extern  char _DOUT_Buffer_SM;
  extern  char _Next_DOUT_Buffer_Cmd;
 // extern  char _DOUT_Buffer_SM;
  extern  char _DIAG_Buffer_SM;
  extern  char _New_DIAG_Puffer_Cmd;
  extern  char _User_Prm_Data_OK;
  extern  char _UserPrmDataNOK;
  extern  char _User_Cfg_Data_OK;
  extern  char _User_Cfg_Data_NOK;
  extern  char _SSA_Bufferfreecmd;
  extern  char _R_TS_Adr;
  extern  char _R_User_Wd_Value[];
  extern  char _R_Len_Dout_Puf;
  extern  char _R_Dout_buf_Ptr1;
  extern  char _R_Dout_buf_Ptr2;
  extern  char _R_Dout_buf_Ptr3;
  extern  char _R_Len_Din_Puf;
  extern  char _R_Din_buf_Ptr1;
  extern  char _R_Din_buf_Ptr2;
  extern  char _R_Din_buf_Ptr3;
  extern  char _R_Len_Diag_Puf1;
  extern  char _R_Len_Diag_Puf2;
  extern  char _R_Diag_Puf_Ptr1;
  extern  char _R_Diag_Puf_Ptr2;
  extern  char _R_Len_Cntrl_Puf1;
  extern  char _R_Len_Cntrl_Puf2;
  extern  char _R_Aux_Puf_Sel;
  extern  char _R_Aux_buf_Ptr1;
  extern  char _R_Aux_buf_Ptr2;
  extern  char _R_Len_SSA_Data;
  extern  char _R_SSA_buf_Ptr;
  extern  char _R_Len_Prm_Data;
  extern  char _R_Prm_buf_Ptr;
  extern  char _R_Len_Cfg_Data;
  extern  char _R_Cfg_Buf_Ptr;
  extern  char _R_Len_Read_Cfg_Data;
  extern  char _R_Read_Cfg_buf_Ptr;
  extern  char _R_Real_No_Add_Change;
  extern  char _R_Ident_Low;
  extern  char _R_Ident_High;
  extern  char _R_GC_Command;
  extern  char _R_Len_Spec_Prm_buf;
  extern  char _Int_Ack_Reg[];
  extern  char _Int_Mask_Reg[];
  extern  char _Mode_Reg_S;
  extern  char _Mode_Reg_R;
  extern  char _WD_Baud_Ctrl_Val;
  extern  char _MinTsdr_Val;
  extern  char _Diag_Buf1[];
  extern  char _Diag_Buf2[];
  extern  char _Aux_Buf1[];
  extern  char _Aux_Buf2[];
  extern  char _SSA_Data[];
  extern  char _Prm_Data[];
  extern  char _Cfg_Buf[];
  extern  char _Read_Cfg_Buf[];
  extern  char _Dout_Buf1[];
  extern  char _Dout_Buf2[];
  extern  char _Dout_Buf3[];
  extern  char _Din_Buf1[];
  extern  char _Din_Buf2[];
  extern  char _Din_Buf3[];

#else // _CM3_

#ifndef  _DP_H
  #define  _DP_H


#define  _DP_START_ADDR	   		_EMC_CS2_BEGIN
#define  _DP_START_ADDRRAM		_EMC_CS2_BEGIN + 0x16 // = 0x98000016
#define  _DP_END_ADDR	   		0x980005FF


#define  _DP_RESET		0x20000000

#define _SIZE_DOUT_BUF		128
#define _SIZE_DIN_BUF		128
#define _SIZE_DIAG_BUF		64//8
#define _SIZE_CTRL_BUF		64
#define _SIZE_SSA_BUF		64//8
#define _SIZE_PRM_BUF		64
#define _SIZE_SPEC_PRM_BUF	64
#define _SIZE_CFG_BUF		64

#if defined( _KTE ) || defined( _KTEV ) || defined( _KTE_GD )
   #define _DP_IDENT_LOW        0x01
   #define _DP_IDENT_HIGH		0x74
#endif
#ifdef _CCT
   #define _DP_IDENT_LOW        0x02
   #define _DP_IDENT_HIGH		0x74
#endif
#ifdef _BTE
   #define _DP_IDENT_LOW        0x03
   #define _DP_IDENT_HIGH		0x74
#endif
#ifdef _Elektroliz
   #define _DP_IDENT_LOW        0x04
   #define _DP_IDENT_HIGH		0x74
#endif

//-----   Формат посылки конфигурации   ---------------------
// | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
//	 |	 |	 |	 |	 |   |   |   |
//	 |	 |	 |	 |	  -----------
//	 |	 |	 |	 |	   0000 -  1 byte/word
//	 |	 |	 |	 | 	   ....
//	 |	 |	 |	 |	   1111 - 16 byte/word
//	 |	 |	 -----
//	 |	 |	 00 - Special Format
//	 |	 |	 01 - Input
//	 |	 |	 10 - Output
//	 |	 |	 11 - Input & Output
//	 |	 0 - Byte
//	 |	 1 - Word
//	 0 - Consistency of Byte/Word
//	 1 - Consistency Entire Length

// Формат посылки конфигурации
#define _DP_SIZE			0x0F   	// Длина данных
#define _DP_IO				0x30   	// Input/Output
#define _DP_TYPE			0x40   	// Тип данных
#define _DP_CONSIST			0x80   	// Вид данных

// Расшифровка поля Input/Output
#define _DP_IO_SPEC		0x00   	// Special Format
#define _DP_IO_INPUT   	0x10	// Input
#define _DP_IO_OUTPUT   	0x20	// Input
#define _DP_IO_INOUT   	0x30	// Input

// Расшифровка поля Тип данных
#define _DP_TYPE_BYTE   	0x00   	// Special Format
#define _DP_TYPE_WORD   	0x40	// Input

// Special Format ( состоит из 2-х или 3-х байт )
// 1-й байт
// | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0
//	 |   |   0   0   -   -   -   -
//	  ---
//	  00 - пустой
//	  01 - 1 input
//	  10 - 1 output
//	  11 - 1 input + 1 output
// 2-й байт - output
// 3-й байт - input
// | 7 | 6 |
//	 |   |
//	 |   0 - байт
//	 |   1 - слово
//	 0 - побитово
//	 1 - полное

#define _DP_SPEC_DATA	0xC0
#define _DP_SPEC_EMPTY	0x00
#define _DP_SPEC_IN		0x40
#define _DP_SPEC_OUT		0x80
#define _DP_SPEC_INOUT	0xC0



typedef struct
{
// Control Registers
//            READ							WRITE
  byte		IntReqRegL;			// 00h - IntReqRegL
  byte		IntReqRegH;         // 01h - IntReqRegH
  byte		IntRegL;            // 02h - IntAckRegL
  byte		IntRegH;            // 03h - IntAckRegH
  byte		StatusRegL;         // 04h - IntMaskRegL
  byte		StatusRegH;         // 05h - IntMaskRegH
  byte		ModeReg0L;          // 06h - ModeReg0L
  byte		ModeReg0H;          // 07h - ModeReg0H
  byte		DinBufferSM;        // 08h - ModeReg1S
  byte		NewDinBufferCmd;    // 09h - ModeReg1R
  byte		DoutBufferSM;       // 0Ah - WDBaudControl
  byte		NewDoutBufferCmd;   // 0Bh - MinTsdr
  byte		DiagBufferSM;   	// 0Ch - ModeReg2
  byte		NewDiagBufferCmd;   // 0Dh - SyncPWReg
  byte		UserPrmDataOk;   	// 0Eh - ControlCmdReg
  byte		UserPrmDataNotOk;   // 0Fh - GroupSelReg
  byte		UserCfgDataOk;   	// 10h
  byte		UserCfgDataNotOk;   // 11h
  byte		DXBoutBufferSM;   	// 12h
  byte		DXBoutBufferCmd;   	// 13h
  byte		SSABufferFreeCmd;   // 14h
  byte		ModeReg1;   		// 15h
// Organizational Registers
  byte		TSAddr;	 			// 16h
  byte		SAPListPtr;			// 17h
  byte		UserWDValueL;		// 18h
  byte		UserWDValueH;		// 19h
  byte		LenDoutBuf;	 		// 1Ah
  byte		DoutBufPtr1;		// 1Bh
  byte		DoutBufPtr2;		// 1Ch
  byte		DoutBufPtr3;		// 1Dh
  byte		LenDinBuf;	 		// 1Eh
  byte		DinBufPtr1;			// 1Fh
  byte		DinBufPtr2;			// 20h
  byte		DinBufPtr3;			// 21h
  byte		LenDXBoutBuf;	 	// 22h
  byte		DXBoutBufPtr1;	 	// 23h
  byte		LenDiagBuf1;	 	// 24h
  byte		LenDiagBuf2;	 	// 25h
  byte		DiagBufPtr1;	 	// 26h
  byte		DiagBufPtr2;	 	// 27h
  byte		LenCntrlBuf1;	 	// 28h
  byte		LenCntrlBuf2;	 	// 29h
  byte		AuxBufSel;		 	// 2Ah
  byte		AuxBufPtr1;		 	// 2Bh
  byte		AuxBufPtr2;		 	// 2Ch
  byte		LenSSAData;		 	// 2Dh
  byte		SSABufPtr;		 	// 2Eh
  byte		LenPrmData;		 	// 2Fh
  byte		PrmBufPtr;			// 30h
  byte		LenCfgData;			// 31h
  byte		CfgBufPtr;		 	// 32h
  byte		LenReadCfgData;	 	// 33h
  byte		ReadCfgBufPtr;	 	// 34h
  byte		LenDXBLinkBuf;	 	// 35h
  byte		DXBLinkBufPtr;	 	// 36h
  byte		LenDXBStatusBuf; 	// 37h
  byte		DXBStatusBufPtr; 	// 38h
  byte		RealNoAddChng; 		// 39h
  byte		IdentLow;		 	// 3Ah
  byte		IdentHigh;		 	// 3Bh
  byte		GCCommand;		 	// 3Ch
  byte		LenSpecPrmBuf;	 	// 3Dh
  byte		DXBoutBufPtr2;	 	// 3Eh
  byte		DXBoutBufPtr3;	 	// 3Fh
// Data Registers
  byte		DiagBuf1[_SIZE_DIAG_BUF];	// 040h - 07Fh
  byte		DiagBuf2[_SIZE_DIAG_BUF];	// 080h - 0BFh
  byte 		AuxBuf1[_SIZE_CTRL_BUF];	// 0C0h - 0FFh
  byte 		AuxBuf2[_SIZE_CTRL_BUF];	// 100h - 13Fh
  byte 		SSABuf[_SIZE_SSA_BUF];		// 140h - 17Fh
  byte 		PrmBuf[_SIZE_PRM_BUF];		// 180h - 1BFh
  byte 		CfgBuf[_SIZE_CFG_BUF];		// 1C0h - 1FFh
  byte 		ReadCfgBuf[_SIZE_CFG_BUF];	// 200h - 23Fh
  byte 		DoutBuf1[_SIZE_DOUT_BUF];   // 240h - 27Fh
  byte 		DoutBuf2[_SIZE_DOUT_BUF];   // 280h - 2BFh
  byte 		DoutBuf3[_SIZE_DOUT_BUF];   // 2C0h - 2FFh
  byte 		DinBuf1[_SIZE_DIN_BUF];     // 300h - 33Fh
  byte 		DinBuf2[_SIZE_DIN_BUF];     // 340h - 37Fh
  byte 		DinBuf3[_SIZE_DIN_BUF];     // 380h - 3BFh
}TDPRegs;

#define 	IntAckRegL		IntRegL					// 02h
#define 	IntAckRegH		IntRegH                 // 03h
#define 	IntMaskRegL		StatusRegL              // 04h
#define 	IntMaskRegH		StatusRegH              // 05h
#define 	ModeReg1S		DinBufferSM             // 08h
#define 	ModeReg1R		NewDinBufferCmd         // 09h
#define 	WDBaudControl	DoutBufferSM            // 0Ah
#define 	MinTsdr			NewDoutBufferCmd        // 0Bh
#define 	ModeReg2		DiagBufferSM            // 0Ch
#define 	SyncPWReg		NewDiagBufferCmd        // 0Dh
#define 	ControlCmdReg	UserPrmDataOk           // 0Eh
#define 	GroupSelReg		UserPrmDataNotOk        // 0Fh

//***********   Описание битовых регистров   **************
//-----   Mode Register 0 (06h)  -----
#define 	MR0_DisStartControl		0x01
#define 	MR0_DisStopControl		0x02
#define 	MR0_WDBase				0x04
#define 	MR0_MinTsdr				0x08
#define 	MR0_IntPol				0x10
#define 	MR0_EarlyRdy			0x20
#define 	MR0_SyncSupport			0x40
#define 	MR0_FreezeSupport		0x80

//-----   Mode Register 0 (07h)  -----
#define 	MR0_DPMode				0x01
#define 	MR0_EOITimeBase			0x02
#define 	MR0_UserTimeBase		0x04
#define 	MR0_SetExtPrmSupport	0x08
#define 	MR0_SpecPrmBufMode		0x10
#define 	MR0_SpecClrMode			0x20
#define 	MR0_PrmCmdSupport		0x40

//-----   Mode Register 1 (08h, 09h)  -----
#define 	MR1_Start				0x01
#define 	MR1_EOI					0x02
#define 	MR1_GoOffline			0x04
#define 	MR1_UserLeave			0x08
#define 	MR1_EnChngCfgBuf		0x10
#define 	MR1_ResUserWD			0x20

//-----   Mode Register 2 (0Ch)  -----
#define 	MR2_NewGCIntMode		0x01
#define 	MR2_NoChkGCRes			0x02
#define 	MR2_DXIntMode			0x04
#define 	MR2_DXIntPort			0x08
#define     MR2_SyncEna				0x10
#define 	MR2_SyncPol				0x20
#define 	MR2_NoChkPrmRes			0x40
#define 	MR2_4kBMode				0x80

//-----   Status Register L (04h)  -----
#define 	SR_Offline				0x01
#define 	SR_DiagFlag				0x04
#define 	SR_DPState				0x30
#define 	SR_WDState				0xC0

//-----   Status Register H (05h)  -----
#define 	SR_BaudRate				0x0F
#define 	SR_Release 				0xF0

//-----   Interrupt Register L (00h)  -----
#define 	IR_MACReset				0x01
#define 	IR_DataExch				0x02
#define 	IR_BuadRateDetect		0x04
#define 	IR_WDControlTimeout		0x08
#define 	IR_UserTimerClock		0x10
#define 	IR_DXBLinkError			0x20
#define 	IR_NewExtPrmData		0x40
#define 	IR_DXBOut				0x80

//-----   Interrupt Register H (01h)  -----
#define 	IR_NewGCCmd				0x01
#define 	IR_NewSSAData			0x02
#define 	IR_NewCfgData			0x04
#define 	IR_NewPrmData			0x08
#define 	IR_DiagBufferChng		0x10
#define 	IR_DXOut				0x20
#define 	IR_PdlEndInd			0x40
#define 	IR_FDLInd				0x80

//-----   Aux Buffer Select (2Ah)  -----
#define 	ABS_SetPrm				0x01
#define 	ABS_ChkCfg				0x02
#define 	ABS_SetSlaveAddr		0x04

//*********************************************************
//#ifdef _DP_

//TDPRegs DPRegs @ 0x98000000;

//#else

//TDPRegs DPRegs;

//#endif
  #define _No_DP              0x00
  #define _Read_DP            0x01
  #define _Write_DP           0x02

  #define _DP_NoErr           0x00
  #define _DP_NotPrm          0x01
  #define _DP_NotGrNum        0x02
  #define _DP_NotVar          0x04
  #define _DP_NotWr           0x08

typedef struct
{
   byte		IdentL;
   byte 	IdentH;
} TIdentDP;

typedef struct
{
   byte 	Address;
   union
   {
	  byte 	all;
	  struct
	  {
		byte	on		: 1 ;
		byte	res		: 7 ;
	  }_;
   }Setting;
} TDPoption;

#define _DP_profi_on	0x01


struct TProfibusDP
{
	TDPRegs* Regs;
	TIdentDP Ident;
	byte Prm_Data[_SIZE_PRM_BUF];
	byte ConfigData[_SIZE_CFG_BUF];
	byte NumDinBuf;
	byte NumDoutBuf;
	byte LenDin;
	byte LenDout;
	TDPoption Opt;
    word  In_PPO[32];
    word  Out_PPO[32];

	union
    {
      struct
      {
        word op : 8;
        word gr : 8;
      } _;
      word all;
    } var1;

	word  var2;

	union
    {
      struct
      {
        word  low ;
        word  high;
      } _;
      lword all;
    } var3;

	byte err;
    byte Op;
    byte Gr;
    word Num;
} Profi_dp;

byte NumDinBuf, NumDoutBuf;
word Len_var;
byte Flag_DataExch;
word timer_dp_wait, count_dp_wait;

	void DP_SetAddr( void );
	void DP_SetParam( void );
	void DP_SetCfg( void );
	byte DP_Diag( void );
	word Init_DP( void );
	void DP_driver( void );
    byte DP_GetSpeed( void );
	void DP_SetIdent( TIdentDP ident );
    void DP_DataExch( void );
	void Work_DP( void );
	void Test_DP(void);
	void ClrMessageDP(void);
	void SetMessageDP(void);


#endif  // _DP_H


#endif // _CM3_

