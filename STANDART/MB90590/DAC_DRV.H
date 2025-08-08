#ifndef _dac_drv_h
#define _dac_drv_h

#define _DAC_setka_max   (w)(+500 )
#define _DAC_setka_min  (sw)(-500 )
#define _DAC_numb_max   3

struct  DAC_data
{
  word  var_num ;
  word  mashtab ;
};

extern  void  DAC_start   ( void ) ;
extern  void  DAC_Output  ( void ) ;
extern  void  DAC0_output ( word num ) ;
extern  void  DAC1_output ( word num ) ;
extern  void  DAC2_output ( word num ) ;
extern  void  DAC3_output ( word num ) ;
extern  void  DAC4_output ( word num ) ;
extern  void  DAC5_output ( word num ) ;

#endif
