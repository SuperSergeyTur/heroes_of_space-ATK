#ifndef  _cse_head
#define  _cse_head

void  Set_cs_sio (byte numb) ;
void  Clr_cs_sio (byte numb) ;
#ifndef  Port_CS
    #define  Port_CS  LPC_GPIO2
#endif


#define _Set_CS(pin)  Port_CS->SET |= 0x1UL<<(pin & 0x7) 
                     

#define _Clr_CS(pin) Port_CS->CLR |= 0x1UL<<(pin & 0x7) 

#define  Set_num_port(num)   (Port_CS->SET = (num &0x03)<<2)  // так будут работать до 4х плат (3 разряда, 8 портов) .
#define  Clr_num_port()      (Port_CS->CLR = 0x7c)
// Чтобы иметь возможность задавать свои CS (для порта 0: просто номер , для порта 1: 32+)
#ifndef  _CS0
    #define  _CS0   2
#endif

#ifndef  _CS1
    #define  _CS1   3
#endif

#ifndef  _CS2
    #define  _CS2   4
#endif

#ifndef  _CS3
    #define  _CS3   5
#endif

#ifndef  _CS4
    #define  _CS4   6
#endif


#ifdef  _MAIN_INCLUDE

const lword  CS_IO[5]  = { _CS0,
                           _CS1,
                           _CS2,
                           _CS3,
                           _CS4
                         };

#else

extern const lword  CS_IO[];

#endif


#endif
