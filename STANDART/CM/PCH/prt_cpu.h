#ifndef _prt_cpu_h
#define _prt_cpu_h

void  Init_CPU_Ports ( void ) ;
void GPIO_IntCmd(uint8_t portNum, uint32_t bitValue, uint8_t edgeState);
FunctionalState GPIO_GetIntStatus(uint8_t portNum, uint32_t pinNum, uint8_t edgeState);
void GPIO_ClearInt(uint8_t portNum, uint32_t bitValue);
extern lword INTReg_GPIO_R[];
extern lword INTReg_GPIO_F[];


#endif

