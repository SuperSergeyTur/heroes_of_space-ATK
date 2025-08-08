
#ifndef _can_drv_h
#define _can_drv_h
//----------

#define   _CAN0_Port         0
#define   _Num_CAN_Ports     1

//--------------------- для CAN0 ----------------------------
#define _RMsg0_1  1
// Номер объекта сооб. через который производится прием у CAN0.
#define _SMsg0_1  5 //13
// Номер 1-го объекта сооб. через который производится передача у CAN0.
#define _SMsg0_2  6 //14
// Номер 2-го объекта сооб. через который производится передача у CAN0.
//----------
#define can0_con CSR_HALT
//#define can_msg1con0
#define can0_msg7id IDRX(7)
#define can0_msg6id IDRX(6)
#define can0_msg5id IDRX(5)
#define can0_msg4id IDRX(4)
#define can0_msg3id IDRX(3)
#define can0_msg2id IDRX(2)
#define can0_msg1id IDRX(1)
#define can0_msg0id IDRX(0)

  // Маска для срезания лишних кроме старших 11 бит идентификатора.
  //     0xFF.E0.00.00
  //       і  А<>Щ  і пеаебвановка байв.
  //       АДД<ДД>ДДЩ
#define  _ID11  0x0000E0FF



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
 word time_out_send6 , time_out_send5 ;
 byte Can_reInit ;
 byte Can_stop ;
};

#define canMSG_hw canMSG_Fuj

word canSend_196( byte port , struct canMSG_Fuj *ptr ) ;
word canReceive_196( byte port , struct canMSG_Fuj *ptr ) ;

extern word Load_ptr(byte port,int buf,struct canMSG_Fuj *ptr) ;
extern word Save_ptr(byte port,int buf,struct canMSG_Fuj *ptr) ;


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
__interrupt void CAN0_RX_Interrupt(void);
     // Блок данных для i-того CAN-порта.
struct CAN_drv_data   can_dd[ _Num_CAN_Ports] ;
                            //  bt0 , bt1
const struct Baud bt_125k = { 0x87, 0x49 } ;
const struct Baud bt_250k = { 0x83, 0x49 } ;
const struct Baud bt_1M   = { 0x80, 0x49 } ;

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/
#else
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/

extern struct CAN_drv_data   can_dd[] ;

extern const struct Baud bt_125k ;
extern const struct Baud bt_250k ;
extern const struct Baud bt_1M   ;

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/
#endif
#endif
