#ifndef  _cse_head
#define  _cse_head

void  Set_cs_sio (byte numb) ;
void  Clr_cs_sio (byte numb) ;

#ifndef  Port_CS
    #define  Port_CS  LPC_GPIO2
#endif

#ifndef  Pin_Port_CS
    #define  PinPort_CS  0x1C000000
#endif


//#ifndef  Port1_CS
//    #define  Port1_CS LPC_GPIO1
//#endif

// Проверяем  5-й разряд (0x20 = 32дес) , если он в 1 , то это порт LPC_GPIO1 :
//#define _Set_CS(pin) if ( (pin & 0x20) != 0) { Port1_CS->SET |= 0x1UL<<(pin & 0x1f) ; } \
//                     else                    { Port_CS->SET  |= 0x1UL<<pin          ; }

//#define _Clr_CS(pin) if ( (pin & 0x20) != 0) { Port1_CS->CLR |= 0x1UL<<(pin & 0x1f) ; } \
//                     else                    { Port_CS->CLR  |= 0x1UL<<pin          ; }


  // так будут работать до 8 портов (но 8-ой порт должен быть входным см. ниже).
//#define  Set_num_port(num)   Port_CS->PIN |=(((lw)num<<26) & PinPort_CS )
#define  Set_num_port(num)   Port_CS->PIN = ( Port_CS->PIN & (~PinPort_CS)) | (((lw)num<<26) & PinPort_CS )

  // Очистка незадействованным адресом (на самом деле просто смена адреса, для того чтоб не оставлять заданным
  // существующий адрес и не переживать, о том что в фоне могут поменяться значения PINов порта и соответственно
  // поменяться значения на выходе микросхемы адрес которой был установлен последним )
#define  Clr_num_port()      Port_CS->PIN |= PinPort_CS;


// Чтобы иметь возможность задавать свои CS (для порта 0: просто номер , для порта 1: 32+)
#ifndef  _CS0
    #define  _CS0   26
#endif

#ifndef  _CS1
    #define  _CS1   27
#endif

#ifndef  _CS2
    #define  _CS2   28
#endif

#ifndef  _CS3
    #define  _CS3   9
#endif

#ifndef  _CS4
    #define  _CS4   10
#endif

#ifndef  _CS5
    #define  _CS5   11
#endif

#ifndef  _CS6
    #define  _CS6   22
#endif

#ifndef  _CS7
    #define  _CS7   0  //32+0  // CAP5
#endif

#ifndef  _CS8
    #define  _CS8   0  //32+27 // CAP6
#endif

#ifndef  _CS9
    #define  _CS9   0
#endif

#ifdef  _MAIN_INCLUDE

const lword  CS_IO[10] = { _CS0,
                           _CS1,
                           _CS2,
                           _CS3,
                           _CS4,
                           _CS5,
                           _CS6,
                           _CS7,
                           _CS8,
                           _CS9
                         };

#else

extern const lword  CS_IO[];

#endif


#endif
