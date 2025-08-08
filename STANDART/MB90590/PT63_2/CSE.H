#ifndef  _cse_head
#define  _cse_head

void  Set_cs_sio (byte numb) ;
void  Clr_cs_sio (byte numb) ;

#define     _CS0            PDR4_P40
#define     _CS1            PDR4_P41
#define     _CS2            PDR4_P42
#define     _CS3            PDR4_P43
#define     _CS4            PDR4_P44

#define  Set_num_port(num)   PDR4 |= num
#define  Clr_num_port()      PDR4 &= 0xFC // чтобы _CS0 и _CS1 обнулять одновременно

#endif
