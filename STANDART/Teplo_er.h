#ifndef _teplo_h
#define _teplo_h

#define  Teplo_Programm( num )  Teplo_exp ( num, &tpl, &ctpl ) ;

#define    Id_TeploIntegr   tpl.Integr_w

#define    Id_teplo_max     tpl.I_max

//#define    Id_teplo         tpl.Ix

//#define   _NumTeploPoint_r   5

//------------------------------

#ifdef  _MAIN_INCLUDE

word  Id_teplo ;

      struct TEPLO_Data    tpl ;
const struct TEPLO_cData  ctpl =
{
 /* word  *Iptr ;           */    &Id_teplo, //Id,

 /* word   TeploNom  ;      */    _Id_nom(1.0),

 /* word   NumTeploPoint  ; */    sizeof(_r.I2Tr.I)/sizeof(word),

 /* word   *Tok ;           */    &_r.I2Tr.I[0],

 /* word   *Time_dat_ptr ;  */    &_r.I2Tr.T[0],

 /* word   *Time_ohlad ;    */    &_r.I2Tr.Tohl
};

#else

extern word  Id_teplo ;

extern       struct TEPLO_Data    tpl ;
extern const struct TEPLO_cData  ctpl ;

/*------------------------------------------------*/
#endif
#endif

