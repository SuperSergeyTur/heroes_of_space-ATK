#ifndef _teplo_s_h
#define _teplo_s_h

#define  Teplo_s_Programm( num )  Teplo_exp ( num, &tpls, &ctpls ) ;

#define    Is_TeploIntegr  tpls.Integr_w

#define    Is_teplo_max    tpls.I_max

//#define    Is_teplo        tpls.Ix

#define   _NumTeploPoint_s   5

//------------------------------

#ifdef  _MAIN_INCLUDE

word  Is_teplo ;

      struct TEPLO_Data    tpls ;
const struct TEPLO_cData  ctpls =
{
 /* word  *Iptr ;           */    &Is_teplo, //Is_p,

 /* word   TeploNom  ;      */    _Is_nom(1.0),

 /* word   NumTeploPoint  ; */    sizeof(_r.I2Ts.I)/sizeof(word),

 /* word   *Tok ;           */    &_r.I2Ts.I[0],

 /* word   *Time_dat_ptr ;  */    &_r.I2Ts.T[0],

 /* word   *Time_ohlad ;    */    &_r.I2Ts.Tohl
};

#else

extern word  Is_teplo ;

extern       struct TEPLO_Data    tpls ;
extern const struct TEPLO_cData  ctpls ;

/*------------------------------------------------*/
#endif
#endif

