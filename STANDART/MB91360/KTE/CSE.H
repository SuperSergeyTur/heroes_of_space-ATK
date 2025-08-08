#ifndef  _cse_head
#define  _cse_head

void  Set_cs_sio (byte numb) ;
void  Clr_cs_sio (byte numb) ;

#define     _CS0            PDRN_PDN0
#define     _CS1            PDRN_PDN1
#define     _CS2            PDRN_PDN2
#define     _CS3            PDRM_PDM0
#define     _CS4            PDRM_PDM1
#define     _CS5            PDRQ_PDQ4
#define     _CS6            PDRQ_PDQ5

#define  Set_num_port(num)   PDRN |= num  // так будут работать до 4х плат (3 разряда, 8 портов) .
#define  Clr_num_port()      PDRN &= 0xFC // чтобы _CS0 и _CS1 обнулять одновременно

#endif
