#ifndef _obj_mux_h
#define _obj_mux_h

//-----------------------------------------------------------
// Определения для плат внешнего аналогового мультиплексора .
//-----------------------------------------------------------

// Каналы и платы внешнего аналогового мультиплексора .

#ifdef  _Ch13_Mux
  // Для первой платы внешнего мультиплексора :
  //   - номер платы в старшей тетраде - 0 .
  //   - номер канала АЦП в младшей тетраде - d .
  //#define  _Ch13_Numb  0x000d - определено в AD_DRV.H .
  #define  _Ch131_Numb   0x010d
  #define  _Ch132_Numb   0x020d
  #define  _Ch133_Numb   0x030d
  #define  _Ch134_Numb   0x040d
  #define  _Ch135_Numb   0x050d
  #define  _Ch136_Numb   0x060d
  #define  _Ch137_Numb   0x070d
  #define  _Ch138_Numb   0x080d
  #define  _Ch139_Numb   0x090d
  #define  _Ch13a_Numb   0x0a0d
  #define  _Ch13b_Numb   0x0b0d
  #define  _Ch13c_Numb   0x0c0d
  #define  _Ch13d_Numb   0x0d0d
  #define  _Ch13e_Numb   0x0e0d
  #define  _Ch13f_Numb   0x0f0d
#endif

#ifdef  _Ch14_Mux
  // Для второй платы внешнего мультиплексора :
  //   - номер платы в старшей тетраде - 1 .
  //   - номер канала АЦП в младшей тетраде - e .
  #undef   _Ch14_Numb  //0x000e - определено в AD_DRV.H .
  #define  _Ch14_Numb    0x100e
  #define  _Ch141_Numb   0x110e
  #define  _Ch142_Numb   0x120e
  #define  _Ch143_Numb   0x130e
  #define  _Ch144_Numb   0x140e
  #define  _Ch145_Numb   0x150e
  #define  _Ch146_Numb   0x160e
  #define  _Ch147_Numb   0x170e
  #define  _Ch148_Numb   0x180e
  #define  _Ch149_Numb   0x190e
  #define  _Ch14a_Numb   0x1a0e
  #define  _Ch14b_Numb   0x1b0e
  #define  _Ch14c_Numb   0x1c0e
  #define  _Ch14d_Numb   0x1d0e
  #define  _Ch14e_Numb   0x1e0e
  #define  _Ch14f_Numb   0x1f0e
#endif

#ifdef  _Ch15_Mux
  // Для третьей платы внешнего мультиплексора :
  //   - номер платы в старшей тетраде - 2 .
  //   - номер канала АЦП в младшей тетраде - f .
  #undef   _Ch15_Numb  //0x000f - определено в AD_DRV.H .
  #define  _Ch15_Numb    0x200f
  #define  _Ch151_Numb   0x210f
  #define  _Ch152_Numb   0x220f
  #define  _Ch153_Numb   0x230f
  #define  _Ch154_Numb   0x240f
  #define  _Ch155_Numb   0x250f
  #define  _Ch156_Numb   0x260f
  #define  _Ch157_Numb   0x270f
  #define  _Ch158_Numb   0x280f
  #define  _Ch159_Numb   0x290f
  #define  _Ch15a_Numb   0x2a0f
  #define  _Ch15b_Numb   0x2b0f
  #define  _Ch15c_Numb   0x2c0f
  #define  _Ch15d_Numb   0x2d0f
  #define  _Ch15e_Numb   0x2e0f
  #define  _Ch15f_Numb   0x2f0f
#endif

//------------------------------------------------------------------------------------------------------------------------------

// Уставки масштабов для внешнего мультиплексора .

/* 08.01.2020 - Масштабы одинаковые , поэтому листинг по каждому каналу не нужен :
#ifdef  _Ch13_Mux
  #define _A7_ADC_Ch13_Mux_masht \
    { "Масшт.n130", &_ar.ADC_Scale[13] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n131", &_ar.ADC_Scale[13] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n132", &_ar.ADC_Scale[13] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n133", &_ar.ADC_Scale[13] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n134", &_ar.ADC_Scale[13] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n135", &_ar.ADC_Scale[13] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n136", &_ar.ADC_Scale[13] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n137", &_ar.ADC_Scale[13] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n138", &_ar.ADC_Scale[13] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n139", &_ar.ADC_Scale[13] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n13a", &_ar.ADC_Scale[13] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n13b", &_ar.ADC_Scale[13] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n13c", &_ar.ADC_Scale[13] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n13d", &_ar.ADC_Scale[13] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n13e", &_ar.ADC_Scale[13] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n13f", &_ar.ADC_Scale[13] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }
#endif

#ifdef  _Ch14_Mux
  #define _A7_ADC_Ch14_Mux_masht \
    { "Масшт.n140", &_ar.ADC_Scale[14] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n141", &_ar.ADC_Scale[14] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n142", &_ar.ADC_Scale[14] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n143", &_ar.ADC_Scale[14] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n144", &_ar.ADC_Scale[14] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n145", &_ar.ADC_Scale[14] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n146", &_ar.ADC_Scale[14] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n147", &_ar.ADC_Scale[14] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n148", &_ar.ADC_Scale[14] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n149", &_ar.ADC_Scale[14] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n14a", &_ar.ADC_Scale[14] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n14b", &_ar.ADC_Scale[14] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n14c", &_ar.ADC_Scale[14] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n14d", &_ar.ADC_Scale[14] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n14e", &_ar.ADC_Scale[14] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n14f", &_ar.ADC_Scale[14] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }
#endif

#ifdef  _Ch15_Mux
  #define _A7_ADC_Ch15_Mux_masht \
    { "Масшт.n150", &_ar.ADC_Scale[15] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n151", &_ar.ADC_Scale[15] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n152", &_ar.ADC_Scale[15] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n153", &_ar.ADC_Scale[15] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n154", &_ar.ADC_Scale[15] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n155", &_ar.ADC_Scale[15] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n156", &_ar.ADC_Scale[15] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n157", &_ar.ADC_Scale[15] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n158", &_ar.ADC_Scale[15] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n159", &_ar.ADC_Scale[15] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n15a", &_ar.ADC_Scale[15] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n15b", &_ar.ADC_Scale[15] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n15c", &_ar.ADC_Scale[15] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n15d", &_ar.ADC_Scale[15] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n15e", &_ar.ADC_Scale[15] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }, \
    { "Масшт.n15f", &_ar.ADC_Scale[15] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) }
#endif
*/
//------------------------------------------------------------------------------------------------------------------------------

// Наименования каналов для внешнего мультиплексора .

#ifdef  _Ch13_Mux
  #define  _ACh13_txt     "n130-IA1      "
  #define  _ACh131_txt    "n131-IB1      "
  #define  _ACh132_txt    "n132-IC1      "
  #define  _ACh133_txt    "n133-IA2      "
  #define  _ACh134_txt    "n134-IB2      "
  #define  _ACh135_txt    "n135-IC2      "
  #define  _ACh136_txt    "n136-резерв   "
  #define  _ACh137_txt    "n137-резерв   "
  #define  _ACh138_txt    "n138-IA3      "
  #define  _ACh139_txt    "n139-IB3      "
  #define  _ACh13a_txt    "n13a-IC3      "
  #define  _ACh13b_txt    "n13b-IA4      "
  #define  _ACh13c_txt    "n13c-IB4      "
  #define  _ACh13d_txt    "n13d-IC4      "
  #define  _ACh13e_txt    "n13e-резерв   "
  #define  _ACh13f_txt    "n13f-резерв   "
#endif

#ifdef  _Ch14_Mux
  #define  _ACh14_txt     "n140-T1-ШС1   "
  #define  _ACh141_txt    "n141-T2-ШС1   "
  #define  _ACh142_txt    "n142-T3-ШС1   "
  #define  _ACh143_txt    "n143-резерв   "
  #define  _ACh144_txt    "n144-T4-ШС1   "
  #define  _ACh145_txt    "n145-T5-ШС1   "
  #define  _ACh146_txt    "n146-T6-ШС1   "
  #define  _ACh147_txt    "n147-резерв   "
  #define  _ACh148_txt    "n148-T1-ШС2   "
  #define  _ACh149_txt    "n149-T2-ШС2   "
  #define  _ACh14a_txt    "n14a-T3-ШС2   "
  #define  _ACh14b_txt    "n14b-резерв   "
  #define  _ACh14c_txt    "n14c-T4-ШС2   "
  #define  _ACh14d_txt    "n14d-T5-ШС2   "
  #define  _ACh14e_txt    "n14e-T6-ШС2   "
  #define  _ACh14f_txt    "n14f-резерв   "
#endif

#ifdef  _Ch15_Mux
  #define  _ACh15_txt     "n150-T1-ШС3   "
  #define  _ACh151_txt    "n151-T2-ШС3   "
  #define  _ACh152_txt    "n152-T3-ШС3   "
  #define  _ACh153_txt    "n153-резерв   "
  #define  _ACh154_txt    "n154-T4-ШС3   "
  #define  _ACh155_txt    "n155-T5-ШС3   "
  #define  _ACh156_txt    "n156-T6-ШС3   "
  #define  _ACh157_txt    "n157-резерв   "
  #define  _ACh158_txt    "n158-T1-ШС4   "
  #define  _ACh159_txt    "n159-T2-ШС4   "
  #define  _ACh15a_txt    "n15a-T3-ШС4   "
  #define  _ACh15b_txt    "n15b-резерв   "
  #define  _ACh15c_txt    "n15c-T4-ШС4   "
  #define  _ACh15d_txt    "n15d-T5-ШС4   "
  #define  _ACh15e_txt    "n15e-T6-ШС4   "
  #define  _ACh15f_txt    "n15f-резерв   "
#endif

//------------------------------------------------------------------------------------------------------------------------------

// Определения каналов для внешнего мультиплексора .

#ifdef  _Ch13_Mux
#define    IA1_ach              _ar.n13_ach
#define    IB1_ach              _ar.n131_ach
#define    IC1_ach              _ar.n132_ach
#define    IA2_ach              _ar.n133_ach
#define    IB2_ach              _ar.n134_ach
#define    IC2_ach              _ar.n135_ach
//#define  _ach                 _ar.n136_ach
//#define  _ach                 _ar.n137_ach
#define    IA3_ach              _ar.n138_ach
#define    IB3_ach              _ar.n139_ach
#define    IC3_ach              _ar.n13a_ach
#define    IA4_ach              _ar.n13b_ach
#define    IB4_ach              _ar.n13c_ach
#define    IC4_ach              _ar.n13d_ach
//#define  _ach                 _ar.n13e_ach
//#define  _ach                 _ar.n13f_ach
#endif

#ifdef  _Ch14_Mux
#define    T0_ach               _ar.n14_ach
#define    T1_ach               _ar.n141_ach
#define    T2_ach               _ar.n142_ach
//#define  _ach                 _ar.n143_ach
#define    T3_ach               _ar.n144_ach
#define    T4_ach               _ar.n145_ach
#define    T5_ach               _ar.n146_ach
//#define  _ach                 _ar.n147_ach
#define    T6_ach               _ar.n148_ach
#define    T7_ach               _ar.n149_ach
#define    T8_ach               _ar.n14a_ach
//#define  _ach                 _ar.n14b_ach
#define    T9_ach               _ar.n14c_ach
#define    T10_ach              _ar.n14d_ach
#define    T11_ach              _ar.n14e_ach
//#define   _ach                _ar.n14f_ach
#endif

#ifdef  _Ch15_Mux
#define    T12_ach              _ar.n15_ach
#define    T13_ach              _ar.n151_ach
#define    T14_ach              _ar.n152_ach
//#define   _ach                _ar.n153_ach
#define    T15_ach              _ar.n154_ach
#define    T16_ach              _ar.n155_ach
#define    T17_ach              _ar.n156_ach
//#define   _ach                _ar.n157_ach
#define    T18_ach              _ar.n158_ach
#define    T19_ach              _ar.n159_ach
#define    T20_ach              _ar.n15a_ach
//#define  _ach                 _ar.n15b_ach
#define    T21_ach              _ar.n15c_ach
#define    T22_ach              _ar.n15d_ach
#define    T23_ach              _ar.n15e_ach
//#define  _ach                 _ar.n15f_ach
#endif

//------------------------------------------------------------------------------------------------------------------------------

// Список каналов для внешнего мультиплексора .

#ifdef  _Ch13_Mux
  #define _A4_ADC_Ch13_Mux_list \
                                   { _ACh131_txt   , &_ar.n131_ach }, \
                                   { _ACh132_txt   , &_ar.n132_ach }, \
                                   { _ACh133_txt   , &_ar.n133_ach }, \
                                   { _ACh134_txt   , &_ar.n134_ach }, \
                                   { _ACh135_txt   , &_ar.n135_ach }, \
                                   { _ACh136_txt   , &_ar.n136_ach }, \
                                   { _ACh137_txt   , &_ar.n137_ach }, \
                                   { _ACh138_txt   , &_ar.n138_ach }, \
                                   { _ACh139_txt   , &_ar.n139_ach }, \
                                   { _ACh13a_txt   , &_ar.n13a_ach }, \
                                   { _ACh13b_txt   , &_ar.n13b_ach }, \
                                   { _ACh13c_txt   , &_ar.n13c_ach }, \
                                   { _ACh13d_txt   , &_ar.n13d_ach }, \
                                   { _ACh13e_txt   , &_ar.n13e_ach }, \
                                   { _ACh13f_txt   , &_ar.n13f_ach }
#endif

#ifdef  _Ch14_Mux
  #define _A4_ADC_Ch14_Mux_list \
                                   { _ACh141_txt   , &_ar.n141_ach }, \
                                   { _ACh142_txt   , &_ar.n142_ach }, \
                                   { _ACh143_txt   , &_ar.n143_ach }, \
                                   { _ACh144_txt   , &_ar.n144_ach }, \
                                   { _ACh145_txt   , &_ar.n145_ach }, \
                                   { _ACh146_txt   , &_ar.n146_ach }, \
                                   { _ACh147_txt   , &_ar.n147_ach }, \
                                   { _ACh148_txt   , &_ar.n148_ach }, \
                                   { _ACh149_txt   , &_ar.n149_ach }, \
                                   { _ACh14a_txt   , &_ar.n14a_ach }, \
                                   { _ACh14b_txt   , &_ar.n14b_ach }, \
                                   { _ACh14c_txt   , &_ar.n14c_ach }, \
                                   { _ACh14d_txt   , &_ar.n14d_ach }, \
                                   { _ACh14e_txt   , &_ar.n14e_ach }, \
                                   { _ACh14f_txt   , &_ar.n14f_ach }
#endif

#ifdef  _Ch15_Mux
  #define _A4_ADC_Ch15_Mux_list \
                                   { _ACh151_txt   , &_ar.n151_ach }, \
                                   { _ACh152_txt   , &_ar.n152_ach }, \
                                   { _ACh153_txt   , &_ar.n153_ach }, \
                                   { _ACh154_txt   , &_ar.n154_ach }, \
                                   { _ACh155_txt   , &_ar.n155_ach }, \
                                   { _ACh156_txt   , &_ar.n156_ach }, \
                                   { _ACh157_txt   , &_ar.n157_ach }, \
                                   { _ACh158_txt   , &_ar.n158_ach }, \
                                   { _ACh159_txt   , &_ar.n159_ach }, \
                                   { _ACh15a_txt   , &_ar.n15a_ach }, \
                                   { _ACh15b_txt   , &_ar.n15b_ach }, \
                                   { _ACh15c_txt   , &_ar.n15c_ach }, \
                                   { _ACh15d_txt   , &_ar.n15d_ach }, \
                                   { _ACh15e_txt   , &_ar.n15e_ach }, \
                                   { _ACh15f_txt   , &_ar.n15f_ach }
#endif

// Для алгоритма аналогового измерения температуры каждого охладителя в каждом силовом шкафу :
#ifdef _Dat_Temp_Max

  struct Hot
    {
      word  Temperat   ;
      word  BKnumb     ;
    }   ;

 struct Izm_BK  // Для измерения аналоговых сигналов
{
  struct Channel_AD *ach ;
  word  full ;
} ;


#if defined _Dat_Temp_Max == 24 // Для 4х силовых шкафов :
  // Индикация аналогового измерения температуры каждого охладителя в каждом силовом шкафу .
  #define _A6_ADC_multiplex_temp \
    { "n-BK  , Hot-T ", { &Hotest.BKnumb  , &Hotest.Temperat },{ 1             , 10             },{ ", "  ,"Г"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,2,0,2),_form(0,3,1,2)} },\
    { "T1-ШС1, T2-ШС1", { &Temper[0]      , &Temper[1]       },{10             , 10             },{ "Г,"  ,"Г"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,2),_form(0,3,0,2)} },\
    { "T3-ШС1, T4-ШС1", { &Temper[2]      , &Temper[3]       },{10             , 10             },{ "Г,"  ,"Г"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,2),_form(0,3,0,2)} },\
    { "T5-ШС1, T6-ШС1", { &Temper[4]      , &Temper[5]       },{10             , 10             },{ "Г,"  ,"Г"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,2),_form(0,3,0,2)} },\
    { "T1-ШС2, T2-ШС2", { &Temper[6]      , &Temper[7]       },{10             , 10             },{ "Г,"  ,"Г"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,2),_form(0,3,0,2)} },\
    { "T3-ШС2, T4-ШС2", { &Temper[8]      , &Temper[9]       },{10             , 10             },{ "Г,"  ,"Г"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,2),_form(0,3,0,2)} },\
    { "T5-ШС2, T6-ШС2", { &Temper[10]     , &Temper[11]      },{10             , 10             },{ "Г,"  ,"Г"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,2),_form(0,3,0,2)} },\
    { "T1-ШС3, T2-ШС3", { &Temper[12]     , &Temper[13]      },{10             , 10             },{ "Г,"  ,"Г"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,2),_form(0,3,0,2)} },\
    { "T3-ШС3, T4-ШС3", { &Temper[14]     , &Temper[15]      },{10             , 10             },{ "Г,"  ,"Г"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,2),_form(0,3,0,2)} },\
    { "T5-ШС3, T6-ШС3", { &Temper[16]     , &Temper[17]      },{10             , 10             },{ "Г,"  ,"Г"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,2),_form(0,3,0,2)} },\
    { "T1-ШС4, T2-ШС4", { &Temper[18]     , &Temper[19]      },{10             , 10             },{ "Г,"  ,"Г"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,2),_form(0,3,0,2)} },\
    { "T3-ШС4, T4-ШС4", { &Temper[20]     , &Temper[21]      },{10             , 10             },{ "Г,"  ,"Г"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,2),_form(0,3,0,2)} },\
    { "T5-ШС4, T6-ШС4", { &Temper[22]     , &Temper[23]      },{10             , 10             },{ "Г,"  ,"Г"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,2),_form(0,3,0,2)} }

  // Переменные следа аналогового измерения температуры каждого охладителя в каждом силовом шкафу .
  #define _F0_ADC_multiplex_temp \
    {"Hot-T    ", &Hotest.Temperat,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"n-BK     ", &Hotest.BKnumb  ,_sl_form(2,1,2,2,0), 1        ,(w*)&_ind1_sld,"d "  },\
    {"countIzm ", &Counter_Izm_T  ,_sl_form(2,1,2,2,0), 1        ,(w*)&_ind1_sld,"d "  },\
    {"T1-ShS1  ", &Temper[0]      ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T2-ShS1  ", &Temper[1]      ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T3-ShS1  ", &Temper[2]      ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T4-ShS1  ", &Temper[3]      ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T5-ShS1  ", &Temper[4]      ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T6-ShS1  ", &Temper[5]      ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T1-ShS2  ", &Temper[6]      ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T2-ShS2  ", &Temper[7]      ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T3-ShS2  ", &Temper[8]      ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T4-ShS2  ", &Temper[9]      ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T5-ShS2  ", &Temper[10]     ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T6-ShS2  ", &Temper[11]     ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T1-ShS3  ", &Temper[12]     ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T2-ShS3  ", &Temper[13]     ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T3-ShS3  ", &Temper[14]     ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T4-ShS3  ", &Temper[15]     ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T5-ShS3  ", &Temper[16]     ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T6-ShS3  ", &Temper[17]     ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T1-ShS4  ", &Temper[18]     ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T2-ShS4  ", &Temper[19]     ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T3-ShS4  ", &Temper[20]     ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T4-ShS4  ", &Temper[21]     ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T5-ShS4  ", &Temper[22]     ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T6-ShS4  ", &Temper[23]     ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  }

#else // Для 2х силовых шкафов :
  // Индикация аналогового измерения температуры каждого охладителя в каждом силовом шкафу .
  #define _A6_ADC_multiplex_temp \
    { "n-BK  , Hot-T ", { &Hotest.BKnumb  , &Hotest.Temperat },{ 1             , 10             },{ ", "  ,"Г"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,2,0,2),_form(0,3,1,2)} },\
    { "T1-ШС1, T2-ШС1", { &Temper[0]      , &Temper[1]       },{10             , 10             },{ "Г,"  ,"Г"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,2),_form(0,3,0,2)} },\
    { "T3-ШС1, T4-ШС1", { &Temper[2]      , &Temper[3]       },{10             , 10             },{ "Г,"  ,"Г"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,2),_form(0,3,0,2)} },\
    { "T5-ШС1, T6-ШС1", { &Temper[4]      , &Temper[5]       },{10             , 10             },{ "Г,"  ,"Г"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,2),_form(0,3,0,2)} },\
    { "T1-ШС2, T2-ШС2", { &Temper[6]      , &Temper[7]       },{10             , 10             },{ "Г,"  ,"Г"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,2),_form(0,3,0,2)} },\
    { "T3-ШС2, T4-ШС2", { &Temper[8]      , &Temper[9]       },{10             , 10             },{ "Г,"  ,"Г"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,2),_form(0,3,0,2)} },\
    { "T5-ШС2, T6-ШС2", { &Temper[10]     , &Temper[11]      },{10             , 10             },{ "Г,"  ,"Г"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,2),_form(0,3,0,2)} }

  // Переменные следа аналогового измерения температуры каждого охладителя в каждом силовом шкафу .
  #define _F0_ADC_multiplex_temp \
    {"Hot-T    ", &Hotest.Temperat,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"n-BK     ", &Hotest.BKnumb  ,_sl_form(2,1,2,2,0), 1        ,(w*)&_ind1_sld,"d "  },\
    {"countIzm ", &Counter_Izm_T  ,_sl_form(2,1,2,2,0), 1        ,(w*)&_ind1_sld,"d "  },\
    {"T1-ShS1  ", &Temper[0]      ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T2-ShS1  ", &Temper[1]      ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T3-ShS1  ", &Temper[2]      ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T4-ShS1  ", &Temper[3]      ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T5-ShS1  ", &Temper[4]      ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T6-ShS1  ", &Temper[5]      ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T1-ShS2  ", &Temper[6]      ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T2-ShS2  ", &Temper[7]      ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T3-ShS2  ", &Temper[8]      ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T4-ShS2  ", &Temper[9]      ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T5-ShS2  ", &Temper[10]     ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  },\
    {"T6-ShS2  ", &Temper[11]     ,_sl_form(2,0,2,3,1), 10       ,(w*)&_ind1_sld,"g "  }
#endif

  // Вывод на ЦАП температуры самого горячего охладителя .
  #define _AD_ADC_multiplex_temp \
    { "Hot-T     ",  &Hotest.Temperat, (w)(0.20 * 256.) }

#endif //#ifdef _Dat_Temp_Max


/*------------------------------------------------*/
#ifdef  _OBJ_INCLUDE
/*------------------------------------------------*/

// Количество плат и количество мультиплексированных каналов :
// Массив задержек времени на срабатывание сигнала выборки и на зарядку/разрядку ёмкости 470pF .
// Выдержки врмени согласованы с Тараном :
//   12 мкс для Фазных Токов .
//   30 мкс для Датчиков Температуры ( добавка для зарядки/разрядки ёмкости на развязке S415 )

#ifdef _Adc_Extend
  _x_far const word  MUX_delay [ _Num_Mux ][ 16 ] = {
                                    #ifdef  _Ch13_Mux
                                       {_MkSec(12), _MkSec(12), _MkSec(12), _MkSec(12),
                                        _MkSec(12), _MkSec(12), _MkSec(12), _MkSec(12),
                                        _MkSec(12), _MkSec(12), _MkSec(12), _MkSec(12),
                                        _MkSec(12), _MkSec(12), _MkSec(12), _MkSec(12)
                                       },
                                    #endif
                                    #ifdef  _Ch14_Mux
                                       {_MkSec(30), _MkSec(30), _MkSec(30), _MkSec(30),
                                        _MkSec(30), _MkSec(30), _MkSec(30), _MkSec(30),
                                        _MkSec(30), _MkSec(30), _MkSec(30), _MkSec(30),
                                        _MkSec(30), _MkSec(30), _MkSec(30), _MkSec(30)
                                       },
                                    #endif
                                    #ifdef  _Ch15_Mux
                                       {_MkSec(30), _MkSec(30), _MkSec(30), _MkSec(30),
                                        _MkSec(30), _MkSec(30), _MkSec(30), _MkSec(30),
                                        _MkSec(30), _MkSec(30), _MkSec(30), _MkSec(30),
                                        _MkSec(30), _MkSec(30), _MkSec(30), _MkSec(30)
                                       }
                                    #endif
                                      };
#endif

#ifdef _Dat_Temp_Max
  sword  Temper[_Dat_Temp_Max] ;
  struct Izm_BK   Izm_Temp[_Dat_Temp_Max] ;
  struct Izm_BK  *pru ;
  word   Counter_Izm_T ;
  struct Hot Hotest , Vrem ;
#endif

/*------------------------------------------------*/
#else
/*------------------------------------------------*/

#ifdef _Dat_Temp_Max
  extern  sword  Temper[] ;
  extern  struct Izm_BK   Izm_Temp[] ;
  extern  struct Izm_BK  *pru ;
  extern  word   Counter_Izm_T ;
  extern  struct Hot Hotest , Vrem ;
#endif

/*------------------------------------------------*/
#endif
/*------------------------------------------------*/

#endif
