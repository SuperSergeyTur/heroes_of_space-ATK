 .SECTION DP, DATA, locate=0x300000;

 .GLOBAL __Int_Req_Reg,       __Int_Reg,              __Status_Reg,     __Mode_Reg0;
 .GLOBAL __DIN_Buffer_SM,     __New_DIN_Buffer_Cmd;
 .GLOBAL __DOUT_Buffer_SM,    __Next_DOUT_Buffer_Cmd, __DOUT_Buffer_SM;
 .GLOBAL __DIAG_Buffer_SM,    __New_DIAG_Puffer_Cmd;
 .GLOBAL __User_Prm_Data_OK,  __UserPrmDataNOK,    __User_Cfg_Data_OK,   __User_Cfg_Data_NOK;
 .GLOBAL __SSA_Bufferfreecmd, __R_TS_Adr,          __R_User_Wd_Value;
 .GLOBAL __R_Len_Dout_Puf,    __R_Dout_buf_Ptr1,   __R_Dout_buf_Ptr2, __R_Dout_buf_Ptr3;
 .GLOBAL __R_Len_Din_Puf,     __R_Din_buf_Ptr1,    __R_Din_buf_Ptr2,  __R_Din_buf_Ptr3;
 .GLOBAL __R_Len_Diag_Puf1,   __R_Len_Diag_Puf2,   __R_Diag_Puf_Ptr1, __R_Diag_Puf_Ptr2;
 .GLOBAL __R_Len_Cntrl_Puf1,  __R_Len_Cntrl_Puf2;
 .GLOBAL __R_Aux_Puf_Sel,     __R_Aux_buf_Ptr1,    __R_Aux_buf_Ptr2;
 .GLOBAL __R_Len_SSA_Data,    __R_SSA_buf_Ptr,     __R_Len_Prm_Data,  __R_Prm_buf_Ptr;
 .GLOBAL __R_Len_Cfg_Data,    __R_Cfg_Buf_Ptr,     __R_Len_Read_Cfg_Data, __R_Read_Cfg_buf_Ptr;
 .GLOBAL __R_Real_No_Add_Change, __R_Ident_Low,    __R_Ident_High,    __R_GC_Command, __R_Len_Spec_Prm_buf;
 .GLOBAL __Int_Ack_Reg,       __Int_Mask_Reg,      __Mode_Reg_S,      __Mode_Reg_R;
 .GLOBAL __WD_Baud_Ctrl_Val,  __MinTsdr_Val;
 .GLOBAL __Diag_Buf1,         __Diag_Buf2,         __Aux_Buf1,        __Aux_Buf2;
 .GLOBAL __SSA_Data,          __Prm_Data,          __Cfg_Buf,         __Read_Cfg_Buf;
 .GLOBAL __Dout_Buf1,         __Dout_Buf2,         __Dout_Buf3;
 .GLOBAL __Din_Buf1,          __Din_Buf2,          __Din_Buf3;


Len_Dout_Buf    .equ    128
Len_Din_Buf     .equ    128
Len_Diag_Buf    .equ    64
Len_Cntrl_Buf   .equ    64
Len_SSA_Data    .equ    64
Len_Prm_Data    .equ    64
Len_Cfg_Buf     .equ    64

// Резервирование внутренних регистров
__Int_Req_Reg           .res.b  2 //    0       ;16 bit Interrupt- Controller - Register
__Int_Reg               .res.b  2 //    2       ;Read  Access Interrupt Register
__Status_Reg            .res.b  2 //    4       ;Read 16 bit Status Register
                        .res.b  2 //    6-7
__DIN_Buffer_SM         .res.b  1 //    08h     ;Read Buffer assignment of the DP_Din_Buffer_State_Machine
__New_DIN_Buffer_Cmd    .res.b  1 //    09h     ;READ 0..1 The user makes a new DP Din buffer available in the N state.
__DOUT_Buffer_SM        .res.b  1 //    0Ah     ;read Buffer assignment of the DP_Dout_Puffer_State_Machine
__Next_DOUT_Buffer_Cmd  .res.b  1 //    0Bh     ;read 0..1 The user fetches the last DP Dout-Buffer from the N state.
__DIAG_Buffer_SM        .res.b  1 //    0Ch     ;read 0..3 Buffer assignment for the DP_Diag_Puffer_State_Machine
__New_DIAG_Puffer_Cmd	.res.b	1 //	0Dh	;read 0..1 The user makes a new DP Diag Buffer available to the SPC3.
__User_Prm_Data_OK	.res.b	1 //	0Eh	;read 0..1 The user positively acknowledges the user parameter setting data of a Set_Param-Telegram.
__UserPrmDataNOK        .res.b  1 //    0Fh     ;read 0..1 The user negatively acknowledges the user parameter setting data of a Set_Param-Telegram.
__User_Cfg_Data_OK	.res.b	1 //	10h	;read 0..1 The user positively acknowledges the configuration data of a Check_Config-Telegram.
__User_Cfg_Data_NOK	.res.b	1 //	11h	;read 0..1 The user negatively acknowledges the configuration data of a Check_Config-Telegram.
                        .res.b  2 //    12-13
__SSA_Bufferfreecmd	.res.b	1 //	14h	;read The user has fetched the data from the SSA buffer and enables the buffer again.
                        .res.b  1 //    15h
__R_TS_Adr              .res.b  1 //    16h     ;Set up station address of the relevant SPC3
                        .res.b  1 //    17h
__R_User_Wd_Value	.res.b	2 //	18h	;Based on an internal 16-bit wachdog timer, the user is monitored in the DP_Mode.
__R_Len_Dout_Puf	.res.b	1 //	1AH	;Length of the 3 Dout buffers
__R_Dout_buf_Ptr1	.res.b	1 //	1BH  	;Segment base address of Dout buffer 1
__R_Dout_buf_Ptr2	.res.b	1 //	1CH  	;Segment base address of Dout buffer 2
__R_Dout_buf_Ptr3	.res.b	1 //	1DH  	;Segment base address of Dout buffer 3
__R_Len_Din_Puf		.res.b	1 //	1EH  	;Length of the 3 Din buffers
__R_Din_buf_Ptr1	.res.b	1 //	1FH  	;Segment base address of Din buffer 1
__R_Din_buf_Ptr2	.res.b	1 //	20H  	;Segment base address of Din buffer 2
__R_Din_buf_Ptr3	.res.b	1 //	21H  	;Segment base address of Din buffer 3
                        .res.b  2 //    22h-23
__R_Len_Diag_Puf1	.res.b	1 //	24H  	;Length of Diag buffer 1
__R_Len_Diag_Puf2	.res.b	1 //	25H  	;Length of Diag buffer 2
__R_Diag_Puf_Ptr1	.res.b	1 //	26H  	;Segment base address of Diag buffer 1
__R_Diag_Puf_Ptr2	.res.b	1 //	27H  	;Segment base address of Diag buffer 2
__R_Len_Cntrl_Puf1	.res.b	1 //	28H  	;Length of Aux buffer 1 and the control buffer belonging to it, for example, SSA-Buf, Prm-Buf, Cfg-Buf, Read-Cfg-Buf
__R_Len_Cntrl_Puf2	.res.b	1 //	29H  	;Length of Aux-Buffer 2 and the control buffer belonging to it,for example, SSA-Buf, Prm-Buf, Cfg-Buf, Read-Cfg-Buf
__R_Aux_Puf_Sel		.res.b	1 //	2AH  	;Bit_array, in which the assignments of the Aux-buffers ? are defined to the control buffers, SSA-Buf, Prm-Buf, Cfg-Buf
__R_Aux_buf_Ptr1	.res.b	1 //	2BH  	;Segment base address of auxiliary buffer 1
__R_Aux_buf_Ptr2	.res.b	1 //	2CH  	;Segment base address of auxiliary buffer 2
__R_Len_SSA_Data	.res.b	1 //	2DH  	;Length of the input data in the Set_Slave_Address-buffer
__R_SSA_buf_Ptr		.res.b	1 //	2EH  	;Segment base address of the Set_Slave_Address-buffer
__R_Len_Prm_Data	.res.b	1 //	2FH  	;Length of the input data in the Set_Param-buffer
__R_Prm_buf_Ptr		.res.b	1 //	30H  	;Segment base address of the Set_Param-buffer
__R_Len_Cfg_Data	.res.b	1 //	31H  	;Length of the input data in the Check_Config-buffer
__R_Cfg_Buf_Ptr		.res.b	1 //	32H  	;Segment base address of the Check_Config-buffer
__R_Len_Read_Cfg_Data   .res.b  1 //    33H     ;Length of the input data in the Get_Config-buffer
__R_Read_Cfg_buf_Ptr    .res.b  1 //    34H     ;Segment base address of the Get_Config-buffer
                        .res.b  4 //    35-38
__R_Real_No_Add_Change  .res.b  1 //    39H     ;This parameter specifies whether the DP slave address may again be changed at a later time point.
__R_Ident_Low		.res.b	1 //	3AH  	;The user sets the parameters for the Ident_Low value.
__R_Ident_High		.res.b	1 //	3BH  	;The user sets the parameters for the Ident_High value.
__R_GC_Command		.res.b	1 //	3CH  	;The Global_Control_Command last received
__R_Len_Spec_Prm_buf	.res.b	1 //	3DH  	;If parameters are set for the Spec_Prm_Buffer_Mode (seemode register 0), this cell defines the length of the param buffer.
                        .res.b  2
// Буфер диагностики
__Diag_Buf1                     .res.b  8*((Len_Diag_Buf+7)/8)  //40 (8)
__Diag_Buf2                     .res.b  8*((Len_Diag_Buf+7)/8)  //48 (9)
// Резервирование буферов
__Aux_Buf1                      .res.b  8*((Len_Cntrl_Buf+7)/8) //50 (0A)
__Aux_Buf2                      .res.b  8*((Len_Cntrl_Buf+7)/8) //60 (0╤)
__SSA_Data                      .res.b  8*((Len_SSA_Data+7)/8)  //70 (0E)
__Prm_Data                      .res.b  8*((Len_Prm_Data+7)/8)  //80 (10)
__Cfg_Buf                       .res.b  8*((Len_Cfg_Buf+7)/8)   //90 (12)
__Read_Cfg_Buf                  .res.b  8*((Len_Cfg_Buf+7)/8)   //A0 (14)
// Буферы приема и передачи данных
__Dout_Buf1                     .res.b  8*((Len_Dout_Buf+7)/8)  //B0 (16)
__Dout_Buf2                     .res.b  8*((Len_Dout_Buf+7)/8)  //C8 (19)
__Dout_Buf3                     .res.b  8*((Len_Dout_Buf+7)/8)  //E0 (1╤)
__Din_Buf1                      .res.b  8*((Len_Din_Buf+7)/8)   //F8 (1F)
__Din_Buf2                      .res.b  8*((Len_Din_Buf+7)/8)   //110(22)
__Din_Buf3                      .res.b  8*((Len_Din_Buf+7)/8)   //128(25)

// Регистры только для записи
                        .ORG 0x300002
__Int_Ack_Reg		.res.b	2	//02h	;Write Access 16 bit bit=1 The IRR bit is deleted bit=0 The IRR bit remains unchanged.
__Int_Mask_Reg		.res.b	2	//04h	;Write bit=1 Mask is set and the interrupt is disabled.
__Mode_Reg0             .res.b  2       //06h-07h ;16 bit Mode register
__Mode_Reg_S		.res.b	1	//08h   ;Mode register for set bits
__Mode_Reg_R		.res.b	1	//09h   ;Mode register for reset bits
__WD_Baud_Ctrl_Val	.res.b	1	//0Ah	;write Root value for baud rate monitoring
__MinTsdr_Val		.res.b	1	//0Bh	;write MinTsdr time
