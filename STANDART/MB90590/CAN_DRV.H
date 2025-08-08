
#ifndef _can_drv_h
#define _can_drv_h
//----------

           // Общее количество CAN-портов контроллера.
#define    _Num_CAN_Ports    2

#define   _CAN0_Port         0
#define   _CAN1_Port         1

//--------------------- для CAN0 ----------------------------

#define _RMsg0_1  1
// Номер объекта сооб. через который производится прием у CAN0.
#define _SMsg0_1  13
// Номер 1-го объекта сооб. через который производится передача у CAN0.
#define _SMsg0_2  14
// Номер 2-го объекта сооб. через который производится передача у CAN0.
//----------
#define can0_con CSR0_HALT
//#define can_msg1con0
#define can0_msg15id IDRX0(15)
#define can0_msg14id IDRX0(14)
#define can0_msg13id IDRX0(13)
#define can0_msg12id IDRX0(12)
#define can0_msg11id IDRX0(11)
#define can0_msg10id IDRX0(10)
#define can0_msg9id IDRX0(9)
#define can0_msg8id IDRX0(8)
#define can0_msg7id IDRX0(7)
#define can0_msg6id IDRX0(6)
#define can0_msg5id IDRX0(5)
#define can0_msg4id IDRX0(4)
#define can0_msg3id IDRX0(3)
#define can0_msg2id IDRX0(2)
#define can0_msg1id IDRX0(1)
#define can0_msg0id IDRX0(0)

//#define big_tab     16
//#define small_tab   2

//#define Res_Bit[big_tab] { 0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080, 0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000, }

/*#define Res_Bit[big_tab]  { 0x0001, 0x0002, 0x0004, 0x0008,
                            0x0010, 0x0020, 0x0040, 0x0080,
                            0x0100, 0x0200, 0x0400, 0x0800,
                            0x1000, 0x2000, 0x4000, 0x8000, }
*/
/*
#define Res_Bit[0]  0x0001
#define Res_Bit[1]  0x0002
#define Res_Bit[2]  0x0004
#define Res_Bit[3]  0x0008
#define Res_Bit[4]  0x0010
#define Res_Bit[5]  0x0020
#define Res_Bit[6]  0x0040
#define Res_Bit[7]  0x0080
#define Res_Bit[8]  0x0100
#define Res_Bit[9]  0x0200
#define Res_Bit[10] 0x0400
#define Res_Bit[11] 0x0800
#define Res_Bit[12] 0x1000
#define Res_Bit[13] 0x2000
#define Res_Bit[14] 0x4000
#define Res_Bit[15] 0x8000
*/


//#define smes_port[small_tab]  {  0x0000,  0x0010 }
/*#define smes_port[0]   0x0000
#define smes_port[1]   0x0010
*/

//#define smesB_port[small_tab]  {  0x0000,  0x0100 }
/*#define smesB_port[0]  0x0000
#define smesB_port[1]  0x0100
*/

  // Маска для срезания лишних кроме старших 11 бит идентификатора.
  //     0xFF.E0.00.00
  //       і  А<>Щ  і пеаебвановка байв.
  //       АДД<ДД>ДДЩ
#define  _ID11  0x0000E0FF

//--------------------- для CAN1 ----------------------------

#define _RMsg1_1  1
// Номер объекта сооб. через который производится прием у CAN1.
#define _SMsg1_1  13
// Номер 1-го объекта сооб. через который производится передача у CAN1.
#define _SMsg1_2  14
// Номер 2-го объекта сооб. через который производится передача у CAN1.

//----------
#define can1_con CSR1_HALT
//#define can_msg1con0
#define can1_msg15id IDRX1(15)
#define can1_msg14id IDRX1(14)
#define can1_msg13id IDRX1(13)
#define can1_msg12id IDRX1(12)
#define can1_msg11id IDRX1(11)
#define can1_msg10id IDRX1(10)
#define can1_msg9id IDRX1(9)
#define can1_msg8id IDRX1(8)
#define can1_msg7id IDRX1(7)
#define can1_msg6id IDRX1(6)
#define can1_msg5id IDRX1(5)
#define can1_msg4id IDRX1(4)
#define can1_msg3id IDRX1(3)
#define can1_msg2id IDRX1(2)
#define can1_msg1id IDRX1(1)
#define can1_msg0id IDRX1(0)


struct canMSG_Fuj {
        lword  id ;
        struct
        {
          byte dlen ;
          //byte dir ;
        } cfg ;
        byte data[8];
} ;

     // Блок данных для i-того CAN-порта.
struct CAN_drv_data
{
 byte Error_receive;
 byte Avar;
 byte Error_send ;
 word time_out_send14 , time_out_send13 ;
 byte Can_reInit ;
 byte Can_stop ;
};

#define canMSG_hw canMSG_Fuj

word canSend_196( byte port , struct canMSG_Fuj *ptr ) ;
word canReceive_196( byte port , struct canMSG_Fuj *ptr ) ;

extern word Load_ptr(byte port,int buf,struct canMSG_Fuj *ptr) ;
extern word Save_ptr(byte port,int buf,struct canMSG_Fuj *ptr) ;
extern word xWrite_msgP( byte port, byte n_obj, struct canMSG_Fuj *ptr );


           //  Время выдержки на передачу ответа мастеру.
#define  _TimeOut_send      _MkSec(10000)

#define  can_reInit(port)  (can_dd[port].Can_reInit)
#define  can_stop(port)    (can_dd[port].Can_stop)
#define  tst_can_stop(port)  ( can_dd[port].Can_stop == 1 || can_setting(port).config._.vkl == 0 )

/*------------------------------------------------------------------*/

#define  Res_InitCan    0xfe /* 0x1111 1110 */

/*------------------------------------------------------------------*/


#define  Set_MsgVal 0xBF /* 0x1011 1111b */
#define  Set_TXIE   0xEF /* 0x1110 1111b */
#define  Set_RXIE   0xFB /* 0x1111 1011b */
#define  Set_IntPnd 0xFE /* 0x1111 1110b */

#define  Set_RmtPnd 0xBF /* 0x1011 1111b */
#define  Set_TxRqst 0xEF /* 0x1110 1111b */
#define  Set_MsgLst 0xFB /* 0x1111 1011b */
#define  Set_CpuUpd 0xFB /* 0x1111 1011b */
#define  Set_NewDat 0xFE /* 0x1111 1110b */

#define  Res_MsgVal 0x7F /* 0x0111 1111b */
#define  Res_TXIE   0xDF /* 0x1101 1111b */
#define  Res_RXIE   0xF7 /* 0x1111 0111b */
#define  Res_IntPnd 0xFD /* 0x1111 1101b */

#define  Res_RmtPnd 0x7F /* 0x0111 1111b */
#define  Res_TxRqst 0xDF /* 0x1101 1111b */
#define  Res_MsgLst 0xF7 /* 0x1111 0111b */
#define  Res_CpuUpd 0xF7 /* 0x1111 0111b */
#define  Res_NewDat 0xFD /* 0x1111 1101b */

#define  _TxRqst     0x20 /* 0x0010 0000b */
#define  _Tst_TxRqst 0x30 /* 0x0011 0000b */

#define  _MsgLst     0x08 /* 0x0000 1000b */
#define  _Tst_MsgLst 0x0C /* 0x0000 1100b */

#define  _DIR_SEND     0x08 /* 0x0000 1000b */
#define  _DIR_RECEIVE  0x00 /* 0x0000 0000b */

#define  _Boff_status  0x80 /* 0x0000 0000b */
#define  _Warn_status  0x40 /* 0x0000 0000b */
#define  _NS_status  0x0300 /* 0x0000 0011 0000 0000b */

struct Baud  { byte bt0, bt1 ; } ;

#define   _bt0_100k     0x0f
#define   _bt1_100k     0x16

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/
#ifdef  _MAIN_INCLUDE
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/
__interrupt  void CAN0_RX_Interrupt ( void );
__interrupt  void CAN1_RX_Interrupt ( void );

     // Блок данных для i-того CAN-порта.
struct CAN_drv_data   can_dd[ _Num_CAN_Ports] ;
                            //  bt0 , bt1
const struct Baud bt_125k = { 0x87, 0x49 } ;
const struct Baud bt_250k = { 0x83, 0x49 } ;
const struct Baud bt_1M   = { 0x80, 0x49 } ;
const word smes_port[2]   = {  0x0000,  0x0010 } ;
const word smesB_port[2]  = {  0x0000,  0x0100 } ;
const word Res_Bit[16]  = { 0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080, 0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000 } ;
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/
#else
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/

extern struct CAN_drv_data   can_dd[] ;

extern const struct Baud bt_125k ;
extern const struct Baud bt_250k ;
extern const struct Baud bt_1M   ;
extern const word smes_port[2]     ;
extern const word smesB_port[2]    ;
extern const word Res_Bit[16]      ;
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/
#endif
#endif
