#ifndef _dac_drv_h
#define _dac_drv_h

#define _DAC_setka_max   (w)(+500 )
#define _DAC_setka_min  (sw)(-500 )
#define _DAC_numb_max   1
struct  DAC_data
{
  word   var_num ;
  word   mashtab ;
  sword  offset  ;
};

extern  void  DAC_start   ( void ) ;
extern  void  DAC_Output  ( void ) ;
extern  void  DAC_output ( word num ) ;

#endif
