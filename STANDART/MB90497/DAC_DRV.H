#ifndef _dac_drv_h
#define _dac_drv_h

struct  DAC_data
{
  word  var_num ;
  word  mashtab ;
};

#define _DAC_setka_max   (w)(+500 )
#define _DAC_setka_min  (sw)(-500 )

extern  void  DAC0_output ( word num ) ;
extern  void  DAC1_output ( word num ) ;

#endif

