//
//     При использовании PCL-841 в качестве чистого Slave (а не slave, как
//  составной части master), возникают ограничения на допустимые номера
//  адресов slave в сети, связанные с тем, что маска PCL охватывает только
//  старшие 8 из 11 разрядов идентификатора, а его 3 младшие всегда
//  замаскированы. Т.е. PCL будет отвечать на все адреса которые охватывает
//  страница из 3-х разрядов примыкающая к ее собственному адресу, например:
//    при адресе: 0x10 => отвечает за 0x10...0x17,
//                  20 => отвечает за   16...23.
//   Таким образом, для согласной работы slave-абонентов в сети адреса следует
// задавать кратными 8-ми: 1,8,16... При сетке мастера 4 будут доступны под
// адреса slave "11-(4+1)-3=3"-разряда, с 3-го по 5-тый включительно.
//
//             master / служеб/ slave/ всегда замаскир.
//           ЪДДДДДБДДДДДїЪБїЪДДДБДДДїЪДДДБДДДї
//           [10][9][8][7][6][5][4][3][2][1][0]

//#########################################
#ifdef _PCL841_WIN
//#########################################

#include "841_win.c"

//#########################################
#else
//#########################################

#include "841_dos.c"
#include "can_dos.c"

//#########################################
#endif
//#########################################

word  can_test( byte port )
{
  word ax ;
  if ( canNormalRun( port ) == 0 ) ax = 1 ;
  else                             ax = 0 ;
  return ax ;
}

//--------------  ИНИЦИАЛИЗАЦИЯ АППАРАТНОЙ ЧАСТИ 'CAN'.
word  can_config ( byte port )
{
   static CAN_STRUCT   can1;

    /*---- reset can controller	*/
    canReset( port );

        // Формируем для мастера свой идентификатор.

  /*  ax = (1 << can_setting(port).master_addr_size) - 1 ;
    if ( can_setting(port).addr > ax ) can_setting(port).addr = 0 ;
          // сдвигаем, чтобы добавить бит признака master(=1)/slave(=0).
    bx = (can_setting(port).addr << 1) + 1 ;
    ax = 5-1 + _FullAddr_Size - can_setting(port).master_addr_size ;
    can1.acc_code = (b)(bx << (ax - 8)) ;
  21.04.03 16:31*/
    can1.acc_code = (b)(SetOwn_ID( port, can_setting(port).addr ) >> 24) ;

          //  Сформировать мастеру свою маску фильтрации сообщений.
             /*      маска: маскируется единицами. */
           /*-----------------22.11.01 11:45-------------------
            У slave маскируются только разряды адресной сетки mastera без
         бита-указателя master/slave.
            У mastera маскируются разряды адресной сетки slave и
         бит-указатель master/slave.
           --------------------------------------------------*/
 /* ax = _FullAddr_Size - can_setting(port).master_addr_size;
    ax = ( 1 << ax ) - 1;
    ax <<= 5 ;  */

#ifndef _OTHER_MASK
    //can1.acc_mask  = (b)(ax >> 8) ;
    can1.acc_mask  = ~(b)( SetOwn_Mask( port ) >> 24) ;
#else
    can1.acc_mask  = _OTHER_MASK ; //0xFF ;
#endif

    can1.bt0 = can_setting(port).btime0;
    can1.bt1 = can_setting(port).btime1;

#ifndef _PCL841_WIN
    if(canConfig(port,can1) == 0)  return 2;
#else
    if(canConfig(port,can1) != 0)  return 2;
#endif

    canNormalRun( port );

  return 0;
}

