#ifndef _obj_h
#define _obj_h

//��������� ��� ����������� ������� �������� �������
#define  _kol_obl    ( 1 ) // ���������� �������� �������
extern   word  read_rezerv( void ) ;

             // ����������� �� CAN ��� ������������ �������.
#define can_obj_stop()  can_stop( _CAN0_Port ) = 1
             // ������������ � CAN ����� ������������ �������.
#define can_obj_start()  can_stop( _CAN0_Port ) = 0
#ifndef    _Enc_base_time
  #define  _Enc_base_time   _MkSec( 2000 )//1650 ) // 21.05.2016 15:45 ?�?a a?���� ?�? ? �?� .
//#define  _Enc_base_time   _or.Enc_base_time
//#define  _Enc_base_time   _MkSec( 8000 ) //_MkSec( 12000 )
//#define  _Enc_base_time   _MkSec( 2500 )
#endif

#define _wgL360  (0x1fffu)
#define _wgL180  (0x0fffu)
#define _wgL90   (0x07ffu)

#define _wgL( grd )   ((const w)( (d)_wgL180 / 180.0 * (d)(grd)+0.5 ))

#define _wgLd( grd )   ((const float)( (float)_wgL180 / 180.0 * (float)(grd)))

#define  _msSec( time ) _MkSec( (d)(time) * 1000. / 16. )

  #define  _MkSecl( time )  ((const lw)( (d)(time)  / (d)_TimerDiscreta + (d)0.5 ))
  #define  _Secl( time )  _MkSecl( (d)(time) * (d)1000000.)


#define _Fil_buf_max_Len  40
#define  timer3        		LPC_TIM3->TC 
//#define _Polus   6 //  
#define _Kadapt  4 //  

void        SmulatorDP(void) ;
void        DPLrotNrot ( void );
void        Define_NS2_rot(void);
void        Define_NS2_rot6(void);
byte        CrossoverTEK(void);
//void        back_front_epa_init ( void );
void        Back_Front_Interrupt ( void );
void        SkorAD( void );
word        Linear (word in);





#ifdef  _OBJ_INCLUDE
         byte   Num_obl ;
         //��-�� ����, ��� ��� ������ (��� ������������)
         //������� "Num_obl" ���������� (��� ���������),
         //��� �������������� ��������� �������� ���������� "Name_Agr",
         //�� ������� ������ ��������� ��������� ����� ��� ���������� ����
         //�������������� ���������. �������� "Name_Agr" �������������
         //������ ������ (������� � 1) � ������� "Tabl_name_ust".
         byte   Name_Agr ;
#else
extern   byte   Num_obl ;
extern   byte   Name_Agr ;
#endif
//--------

word        ObjPrg ( word num )   ;
void        Obj_Interrupt (void );
//--------

 #define T1_MR0_Int()
 #define T1_MR1_Int() SkorAD_Interrupt () //Revers_Interrupt ()
 #define T1_MR2_Int()
 #define T1_MR3_Int()

 #define T1_CR0_Int()
 #define T1_CR1_Int()

 #define T2_MR0_Int()
 #define T2_MR1_Int()
 #define T2_MR2_Int() S2_Interrupt ()
 #define T2_MR3_Int()

 #define T2_CR0_Int()
 #define T2_CR1_Int()

 #define T3_MR0_Int()
 #define T3_MR1_Int() S_Interrupt()
 #define T3_MR2_Int()
 #define T3_MR3_Int()

 #define T3_CR0_Int()
 #define T3_CR1_Int()
//------------------------

//���������� ���������� ������ �� ���������� �����

#define    _SInp_max       4
#define    _SOut_max       2

//���������� ����� ( �� ��������� �� 3 ��. )
#undef  _DAC_numb_max
#define _DAC_numb_max         4
//------------------------------
// ����� PPG , ������������� ��� DAC2 :
//#define    _PPG_for_DAC2    4
//------------------------------
// ������ ������ PPG , ������������ ��� ��� . ���������� ��� ���������� ���� ���������� ����� .
// PPG0, PPG1 ������������ ��� ����� �� ������ ������ � ����� .
// PPG2, PPG3 ������������ ��� ����� �� ������ ������ � ����� 12-�� ��������� ���� ( ��� ��� ������� ) .
// PPG5 ������������ ��� ����� �� ����������� ����������� ( ��� ��� ������� ) .
#define      _PPG_for_DAC2    6
#define      _PPG_for_DAC3    7
//------------------------------

// �������� ������� ��� ��� :
// ������ ���� 25 * 80 ��� , �� �.�. �� ������ �� ����� �.�. �������� ���������� , �� ��������� ����� ����� .
#undef     _FzapolnShort_Low
#define    _FzapolnShort_Low      _MkSec( 100 ) // ������������ �������� �������� � ���
#undef     _FzapolnShort_High
#define    _FzapolnShort_High     _MkSec( 20 )  // ������������ ���������� �������� � ���

#undef     _AD_Delta
#define    _AD_Delta         1    // ��� ������ ��������� ���� �� 12-��������� ��� .

// ����� ����� ���������� ������ � 2-� ������ �� 4-� ������ ...
//#define  _Mask_DistSbr    ( _Av_Gercon | _Av_GerconDC | _Av_Gercon3 | _Av_Gercon4 )
#define    _Mask_DistSbr    ( 0 )

//#define  _Mask_AvarSbr    ( _Av_Gercon | _Av_GerconDC | _Av_Gercon3 | _Av_Gercon4 | \
//                            _Av_PUM | _Av_IdMax | _Av_Id_sum_Max | _Av_Iv_Max )
//#define  _Mask_AvarSbr    ( 0 )

//#define  _Mask_Avar       ( _Av_Gercon | _Av_GerconDC | _Av_Gercon3 | _Av_Gercon4 )
//#define  _Mask_Avar       ( 0 )

// DAN 07.06.2017 10:30 - ����� ��� ������ ������ � ������ ���������� , �������� � ���� 3 �.�. ������� :
#define    _Mask_Avar       ( _Av_Gercon | _Av_GerconDC | _Av_GerconSN )

//#define  _Mask_AvarPreduprGotovn  ( _Av_Gercon | _Av_GerconDC | _Av_Gercon3 | _Av_Gercon4 )
//#define  _Mask_AvarPreduprGotovn  ( 0 )

#define  _Output_Tst_PPG4        "PPG4=_�_"
#define  _Output_Tst_ppg4        "PPG4=_�_"

//------- ���������� , ����� � ������������� ��������������� �������� :
//  ��� ���� , ����� ����� ������� , ���������������� ��������������� . ������� ����� ����� �����
// � �7 , �������� . ��� ������� ������� _or.Sels_mashtP0 ��� _or.Sels_mashtP1 � �6 , �������.
// ����� ��������� ������������������� � ����������������� �������� � �������� .
//-------
//#define     _Sels_shift0
//#define     _Sels_shift1
//---
//#define     _Sels_mashtP0
//#define     _Sels_mashtP1
//---
//#define     _Sels_mashtM0
//#define     _Sels_mashtM1

/*��� �������� ����������� ���� � ���������� ������/������� ��-*/

            /*  ���������� ������  */

//#define  bo_                   Po0_c._.n0
#define    bo_VV1_stator         Po0_c._.n1  // K9 - ��������� ��1 - ���������� ������������� ������� . // DAN 12.04.2025
//#define  bo_                   Po0_c._.n2
//#define  bo_                   Po0_c._.n3
//#define  bo_                   Po0_c._.n4
//#define  bo_                   Po0_c._.n5
//#define  bo_                   Po0_c._.n6
//#define  bo_                   Po0_c._.n7

//#define  bo_                   PoS_c[0]._.n0
//#define  bo_                   PoS_c[0]._.n1
//#define  bo_                   PoS_c[0]._.n2
//#define  bo_                   PoS_c[0]._.n3
//#define  bo_                   PoS_c[0]._.n4
//#define  bo_                   PoS_c[0]._.n5
//#define  bo_                   PoS_c[0]._.n6
//#define  bo_                   PoS_c[0]._.n7

// ���� ��� ������� , ������� ������ �� ��������� :
#define    bo_Avar               Prt_NULL._.n0
#define    bo_Predupr            Prt_NULL._.n1
#define    bo_Gotov              Prt_NULL._.n2
#define    bo_MT                 Prt_NULL._.n3
#define    bo_Insulat            Prt_NULL._.n4
#define    bo_Vkl_KZ             Prt_NULL._.n5
#define    bo_Vkl_QK1            Prt_NULL._.n6
#define    bo_Zatyan_Pusk        Prt_NULL._.n7

// ���� 2 16 �������� ��� ������� , ������� ������ �� ��������� :
#define  bo_Err_Sifu             Prt_NULL2._.n0
#define  bo_dLDL_set             Prt_NULL2._.n1
//#define  bo_                   Prt_NULL2._.n2
//#define  bo_                   Prt_NULL2._.n3
//#define  bo_                   Prt_NULL2._.n4
//#define  bo_                   Prt_NULL2._.n5
//#define  bo_                   Prt_NULL2._.n6
//#define  bo_                   Prt_NULL2._.n7

            /*  ���������� �����   */

#define    bi_2P24               Pi0_f._.n0
//#define  bi_                   Pi0_f._.n1
#define    bi_AF1P               Pi0_f._.n2
#define    bi_Fsil_rot           Pi0_f._.n3
#define    bi_SQ1                Pi0_f._.n4
//#define  bi_                   Pi0_f._.n5
//#define  bi_                   Pi0_f._.n6
#define    bi_DS1              ( Pi0_f._.n7 == 1 || Klav_Buff == _Reset ) //|| KTE2_DS1 == 1 ) 12.03.2021 - ����� ��������� .

//--------------------------------------------------------------------------
 // �� ���������� ! ����� INT � ����� � ����� 1 - �� ��������� :

//#define  bi_KP_KZ              Pi1_f._.n0  // K�3 - INT7 - KP ��
//#define  bi_                   Pi1_f._.n1  // ������� ��������
//#define  bi_KF_VKask           Pi1_f._.n2  // KF2 - INT5 - KF ������
//#define  bi_KP                 Pi1_f._.n3  // K�2 - INT6 - KP ������
//#define  bi_                   Pi1_f._.n4  //     - INT4
//#define  bi_KF_VKask2          Pi1_f._.n5  // KF3 - INT3 - KF ��
#define    bi_Gercon             Pi1_nm._.n6 // 1B  - INT0 - ������ �������� ���������
#define    bi_GerconAC2          Pi1_nm._.n7 // 2B  - INT1 - ������ ��������� �����������
//--------------------------------------------------------------------------

//#define  bi_KTE_rezerv1        0
//#define  bi_GerconDC           0
//#define  bi_KP                 0 // �������� ������� ���������� �������� �������� �������� .

#define    bi_QK1                KTE2_Rabota
#define    bi_VR1              ( bi_QK1 == 0 )
#define    bi_AR1                0
#define    bi_Vnesh_Avar         0
#define    bi_Razresh_Vkl        1
#define    bi_Bolshe             0
#define    bi_Menshe             0
#define    bi_Rab_Tolch          0
#define    bi_TB                 0
#define    bi_TH                 0
#define    bi_Zapret             0
#define    bi_KTE_rezerv         0
#define    bi_AF1                0 // ��������� ������ ������ ��� ��������������� .
#define    bi_Fors_Temp          bi_Zapret  // ��� �������������� ����������
#define    bi_AK1                1
#define    bi_AK2                1 // ���� ��� ����-�������� Q2 - ��� ���������������� ������ ��������� Q2V .

//-------------------
#define  _ACh0_txt      "n0 -Id      " // ��� �������� ��������� .
#define  _ACh1_txt      "n1 -������  " //"n1 -Id-sr   "
#define  _ACh2_txt      "n2 -I���A   "
#define  _ACh3_txt      "n3 -I���B   "
#define  _ACh4_txt      "n4 -I���C   "
#define  _ACh5_txt      "n5 -������  "
#define  _ACh6_txt      "n6 -Uba     "
#define  _ACh7_txt      "n7 -Uac     "
#define  _ACh8_txt      "n8 -������  "
#define  _ACh9_txt      "n9 -������  "
#define  _ACh10_txt     "n10-������  "
#define  _ACh11_txt     "n11-I���    "
#define  _ACh12_txt     "n12-������  "
#define  _ACh13_txt     "n13-������  "
#define  _ACh14_txt     "n14-������  "
#define  _ACh15_txt     "n15-������. "
#define  _ACh16_txt     "AN-P24      "
#define  _ACh17_txt     "AN-N12      "
#define  _ACh18_txt     "AN-P12      "

            /*  ���������� �����  */

#define    Id_mg_ach            _ar.n00_ach
//#define  Id_sr_ach            _ar.n01_ach
#define    IA_ach               _ar.n02_ach
#define    IB_ach               _ar.n03_ach
#define    IC_ach               _ar.n04_ach
//#define  _ach                 _ar.n05_ach
#define    Uba_ach              _ar.n06_ach
#define    Uac_ach              _ar.n07_ach
//#define  _ach                 _ar.n08_ach
//#define  _ach                 _ar.n09_ach
//#define  _ach                 _ar.n10_ach
#define    Irot_ach             _ar.n11_ach
//#define  _ach                 _ar.n12_ach
//#define  _ach                 _ar.n13_ach
//#define  _ach                 _ar.n14_ach
#define    Zad_res_ach          _ar.n15_ach
#define    Z_sk_ach             Zad_res_ach

#define    P24_ach              _ar.n16_ach
#define    P12_ach              _ar.n18_ach
#define    N12_ach              _ar.n17_ach
//�������������������������������������������������������������������������
//----------- A8 -  ������� ��������� ������� ------------

  #define _KTE_A8_ConfigObj
//--------------------------------------------------------

     //  ��������� ����������������
 union ConfigO {
  word all ;
  struct  {
      word sld_PWM          : 1 ;
      word Vkl_KZ           : 1 ;
      word Vedushiy         : 1 ;
      word EnSimulat        : 1 ;

      word En_Fil_DP        : 1 ;
      word Priv_Filt        : 1 ;
      word RT               : 1 ;
      word N_to_L           : 1 ;
     //----
      word rezerv8          : 1 ;
      word rezerv9          : 1 ;
      word rezerv10         : 1 ;
      word rezerv11         : 1 ;

      word rezerv12         : 1 ;
      word rezerv13         : 1 ;
      word rezerv14         : 1 ;
      word rezerv15         : 1 ;
    } _ ;
} ;

#define   _cfgO_sld_PWM          ((w) 0x0001 )
#define   _cfgO_Vkl_KZ           ((w) 0x0002 )
#define   _cfgO_Vedushiy         ((w) 0x0004 )
#define   _cfgO_EnSimulat        ((w) 0x0008 )


#define _cfgO_En_Fil_DP          ((w) 0x0010 )
#define _cfgO_RT                  ((w) 0x0020 )
#define _cfgO_N_to_L              ((w) 0x0040 )
//#define _cfgO_rezerv7          ((w) 0x0080 )

union flagO {
  word all ;
  struct  {
      word NeFaznRot   : 1 ;
      word trig_Pusk   : 1 ;
      word new_tyr     : 1 ;
      word Pusk_OK     : 1 ; // ��� ���� .

      word VShunt1     : 1 ; // ��� ���� .
      word VShunt2     : 1 ; // ��� ���� .
      word VShunt3     : 1 ; // ��� ���� .
      word KZ          : 1 ; // ��� ���� , � ��� ���� �� �����, ��������� �������� ��� ������ �� ��2
     //----
      word V_trig      : 1 ;
      word Sploshnyak  : 1 ; // ��� ��� .
      word NewSyn      : 1 ;
      word trig_Prinud : 1 ; // ��� ��� - ������� �������������� ���������� .

      word KZ_command  : 1 ; // ��� ���� .
      word KZ_trig     : 1 ; // ��� ���� .
      word Prinud_com  : 1 ; // ��� ��� - ����� �������������� ���������� .
      word CAN1_ok     : 1 ;
    } _ ;
} ;

//�������������������������������������������������������������������������

 struct  oBlok_Ustavok
  {        //  ������ ����������, ������� ������� �������� �� i-��� ���.
    struct DAC_data dac_numb[ _DAC_numb_max ] ;
    word   Rezerv_DAC [ 12 ] ;

    byte  Ai_CS[_Ai_max];

    byte  AS_CSo[_SOut_max];

    byte  AS_CSi[_SInp_max];

    byte  PiS_Normal[_SInp_max];    //����� ����������������� ����� S400.
    /*    PiS_Normal[0]*/
    /*    PiS_Normal[1]*/
    /*    PiS_Normal[2]*/
    /*    PiS_Normal[3]*/

    byte  PoS_Normal[_SOut_max];
    /*    PoS_Normal[0]*/
    /*    PoS_Normal[1]*/

    union ConfigO  CfgO ;

#ifdef    _Sels_mashtP0
    word   Sels_mashtP0 ;
#endif
#ifdef    _Sels_mashtM0
    word   Sels_mashtM0 ;
#endif
#ifdef    _Sels_shift0
    byte   Sels_shift0 ;
    byte   rezerv0 ;
#endif

#ifdef    _Sels_mashtP1
    word   Sels_mashtP1 ;
#endif
#ifdef    _Sels_mashtM1
    word   Sels_mashtM1 ;
#endif
#ifdef    _Sels_shift1
    byte   Sels_shift1 ;
    byte   rezerv1 ;
#endif

    word   Filtr_Param ;
    word   Ttr_predupr ;
    word   Ttr_4mA ;
    word   Ttr_20mA ;

    double T_Scale ;
    word   T_Pr ;
    word   T_Av ;

    word   T_zaderg_pusk ;
    word   Time_Sploshnyak ;
    word   Time_Zatyan_Pusk ;
    word   Time_snyatIU_KZ ;
    word   Pusk_0_1 ;
    word   Pusk_1_0 ;
    word   N_min[4] ;
    word   Alfa_min_time ;
    word   Alfa_Min_Shunt ;
    word   Alfa_Shunt ;
    word   I_Ogr ;
    word   S_Alfa_F2_Isp ;
    word   rezerved[ 4 ] ;
    float  Rsigma ;
    float  Xsigma ;
    float  Tf_aper ;
    float  Tfil ;
    word   Pary_AD ;
    word   T_Id_flt ;
    word   T_Otkl_Vent ;
    word   T_min_Pusk ;
    word   ZIS_Nachal ;
    word   T_vkl_KZ ;
    word   Alfa_Shunt2 ;
    word   Alfa_Shunt3 ;

    float  Km ;
    word   Pnom ;
    word   Istat ;

    word   dId_sryv ;
    word   S_Alfa_Dvig ;
    word   S_Alfa_Gen ;

    word  N_rot_reg ;

    word   razgFP_N_to_L [ 16 ] ;
    word   rezerv_razgFP_N [ 4 ] ;

    word   tormFP_N_to_L [ 16 ] ;
    word   rezerv_tormFP_N [ 4 ] ;

    word   I_rot_nom ;
    word   Irot_forKZ ;
    word   S_Alfa_Prinud_com ;

    word   K_f_syn3f ;

    word DeltDPSimulat;
    
    word   T_generat ;
    
    word   K_Enc_syn3f;
    
    word   Fil_buf_Len; 

    word   Alfa_minRT;
    
    word   Time_Min_RT; 

    word   rezerv[ 124 ] ;

#ifdef _INTERPRETER
    struct SetpointData MemData;
#endif

    byte  Contrl_sum ;
  } ;

//-------------- �7 - ��������� ������� ------------------

    #define _A7_Obj_Ust \
 { "dL ����. ��  ", &_or.DeltDPSimulat               , 0     ,_wgL( 12.0 )      ,_wgL( 1 )    ,(w*)&_ind_Nom, _wgL( 0.1 )    , 0xff, "���", _form(1,3,1,2) },\
 { "��-���-����  ", &_r.Selsin[0].null    , 0               , _wgL360          , 23           ,(w*)&_ind_Nom,  2             , 0xff, "���", _form(1,3,1,2) },\
 { "������� ������", &_or.Fil_buf_Len      , 1               , _Fil_buf_max_Len , 1            ,(w*)&_ind_Nom,  1             , 0xff, "o�", _form(1,2,0,2) }

//--------------------------------------------------------

    #define _A7_CAN_MASTER_Ust \
    { "���.����.CAN1 ", &_r.AddrDevice1     , 0               , 0x7f             , 1            ,(w*)&_ind_Nom, 1              , 0xff, "��"  , _form(1,3,0,1) }

//------------ �6 - ��������� ��������� ------------------

    //#define _A6_Obj_Ind \

//--------- F1 - ��������� ���������� ��� ����� ----------
     // _sl_form(type,off_sign,print_type,celoe,drob)
    #define _Sld_cnst_Obj \
    {"Lr       ", &Lrot          , _sl_form(2,1,2,3,1),_Grad(1.0),(w*)&_ind1_sld, "g " },\
    {"Lr_DP    ", &Lrot_dp       , _sl_form(2,1,2,3,1),_Grad(1.0),(w*)&_ind1_sld, "g " },\
    {"Lsety    ", &Lsety          , _sl_form(2,1,2,3,1),_Grad(1.0),(w*)&_ind1_sld, "g " },  \
    {"Lwg      ", &wgL_rn         , _sl_form(2,1,2,3,1),_Grad(1.0),(w*)&_ind1_sld, "g " },  \
    {"GradTek  ", &GradTek       , _sl_form(2,1,2,3,1),_Grad(1.0),(w*)&_ind1_sld, "g " },\
    {"nFr      ", &nFrot          , _sl_form(2,1,2,3,1), 360      ,(w*)&_ind1_sld, "Hz "},   \
    {"Fr       ", &Frot          , _sl_form(0,1,2,3,1), 1      ,(w*)&_ind1_sld, "Hz "},   \
    {"Fsr      ", &Fsrot         , _sl_form(0,1,2,3,1),  1      ,(w*)&_ind1_sld, "Hz "},   \
    {"Fsyn     ", &Syn.Fsyn      , _sl_form(0,1,2,3,1),  1      ,(w*)&_ind1_sld, "Hz "},   \
    {"Frotf    ", &Frotf          , _sl_form(0,1,2,3,1), 1      ,(w*)&_ind1_sld, "Hz "},   \
    {"EncGDP   ", (w*)&EncoderGray, _sl_form(2,1,2,3,1), _wgL(1) ,(w*)&_ind1_sld, "�� "},    \
    {"EncDP    ", (w*)&EncoderDP  , _sl_form(2,1,2,3,1), _wgL(1) ,(w*)&_ind1_sld, "�� "},    \
    {"EncDPr   ", (w*)&EncoderDPr, _sl_form(2,1,2,3,1), _wgL(1) ,(w*)&_ind1_sld, "�� "},    \
    {"EncDPf   ", (w*)&EncoderDPf, _sl_form(2,1,2,3,1), _wgL(1) ,(w*)&_ind1_sld, "�� "},    \
    {"EncBin   ", (w*)&EncoderBinar,_sl_form(2,1,2,3,1), _wgL(1) ,(w*)&_ind1_sld, "�� "},\
    {"deltDP   ", (w*)&deltDPr      ,_sl_form(2,1,1,0,0), 1       ,(w*)&_ind1_sld,"h " },\
    {"deltDPr  ", (w*)&deltDP_r     ,_sl_form(2,1,1,0,0), 1       ,(w*)&_ind1_sld,"h " },\
    {"TEK_Grad ", (w*)&TEK_Grad    ,_sl_form(2,1,1,0,0), 1       ,(w*)&_ind1_sld, "h "},\
    {"TEK_Grads", (w*)&TEK_Grads   ,_sl_form(2,1,1,0,0), 1       ,(w*)&_ind1_sld, "h "},\
    {"N_inv    ", (w*)&N_inv       ,_sl_form(2,1,1,0,0), 1       ,(w*)&_ind1_sld, "h "},\
    {"T_Per    ", &T_per           ,_sl_form(2,1,1,0,0), 1       ,(w*)&_ind1_sld,"h " },\
    {"NS2_rot  ", &NS2_rot         ,_sl_form(4,1,1,0,0), 1       ,(w*)&_ind1_sld,"h " },\
    {"Tpp_3syn ", &Tpp_3syn        ,_sl_form(4,1,1,0,0), 1       ,(w*)&_ind1_sld,"h " },\
    {"S_TZ     ", &DP_TZ           ,_sl_form(4,1,1,0,0), 1       ,(w*)&_ind1_sld,"h " },\
    {"S_Ax     ", &S_Ax            ,_sl_form(4,1,1,0,0), 1       ,(w*)&_ind1_sld,"h " },\
    {"S_BX     ", &S_Bx            ,_sl_form(4,1,1,0,0), 1       ,(w*)&_ind1_sld,"h " },\
    {"S_Cx     ", &S_Cx            ,_sl_form(4,0,2,5,0), 1       ,(w*)&_ind1_sld,"  " },\
    {"S_Dx     ", &S_Dx            ,_sl_form(4,1,1,0,0), 1       ,(w*)&_ind1_sld,"h " },\
    {"dT_f0    ", &dT_f0          ,_sl_form(0,0,2,3,3), 1       ,(w*)&_ind1_sld,"ms" },\
    {"Tpp_dp   ", &Tpp_f           ,_sl_form(0,0,2,3,3), 1       ,(w*)&_ind1_sld,"ms" },\
    {"dL_rot   ", &dLrot           ,_sl_form(0,0,2,3,3), _Grad(1),(w*)&_ind1_sld,"���" },\
    {"deltTDP  ", &deltTDP_old     , _sl_form(2,1,2,3,1),1      ,(w*)&_ind1_sld, "ms" },



//    {"TZ_sSec  ", &TZ_sSec         ,_sl_form(2,1,1,0,0), 1       ,(w*)&_ind1_sld,"h " },\
//------------ AD - ��������� ����� �� ��� ---------------

    #define _AD_Obj_DAC \
       { "Lwg       ",  &Lrot             , (w)(0.027* 256.)          }  // 0


//------- FB - ��������� ���������� ��� ������� ----------

    //#define _Jrn_cnst_Obj\

//--------------------------------------------------------

/*------------------------------------------------*/
#ifdef  _OBJ_INCLUDE
/*------------------------------------------------*/


struct  oBlok_Ustavok  _or  ;

_x_far const  struct  oBlok_Ustavok  _oc   =
  {
 /*   word  dac_numb[0] ;   sys    */ { {  0 ,  (w)(0.12 * 256)     , 0   },   //DA0
 /*   word  dac_numb[1] ;   Iv#    */   {  3 ,  (w)(1.00 * 256/_K_diskr) , 0   },   //DA1->PPG8
 /*   word  dac_numb[2] ;   Id��   */   {  6 ,  (w)(0.12 * 256)     , -500},   //PPG6
 /*   word  dac_numb[2] ;    N     */   {  4 ,  (w)(0.12 * 256)     , -500} }, //PPG7
 /*   word  Rezerv_DAC [ 12 ] ;    */ { 0 },

 /*   byte  Ai_CS[_Ai_max];        */ { 2, 5, 9, 10, 4 }, // 0xff - ��� ������.

 /*   byte  AS_CSo[_SOut_max];     */ { 2, 5 },

 /*   byte  AS_CSi[_SInp_max];     */ { 0, 1, 3, 4 },

 /*   byte  PiS_Normal[_SInp_max]; */
                                      {
 /*         PiS_Normal[0]          */   0xff,
 /*         PiS_Normal[1]          */   0xff,
 /*         PiS_Normal[2]          */   0xff,
 /*         PiS_Normal[3]          */   0xff
                                      },
 /*   byte  PoS_Normal[_SOut_max]; */
                                      {
 /*         PoS_Normal[0]          */   0x00,
 /*         PoS_Normal[1]          */   0x00
                                      },
 /*   union ConfigO  CfgO ;        */ { _cfgO_sld_PWM | _cfgO_Vedushiy} ,

#ifdef    _Sels_mashtP0
 /*   word   Sels_mashtP0 ;        */ (w)( 1.00 * 256.) ,
#endif
#ifdef    _Sels_mashtM0
 /*   word   Sels_mashtM0 ;        */ (w)( 1.00 * 256.) ,
#endif
#ifdef    _Sels_shift0
 /*   byte   Sels_shift0 ;         */ 1 ,
 /*   byte   rezerv0 ;             */ 0 ,
#endif

#ifdef    _Sels_mashtP1
 /*   word   Sels_mashtP1 ;        */ (w)( 1.00 * 256.) ,
#endif
#ifdef    _Sels_mashtM1
 /*   word   Sels_mashtM1 ;        */ (w)( 1.00 * 256.) ,
#endif
#ifdef    _Sels_shift1
 /*   byte   Sels_shift1 ;         */ 1 ,
 /*   byte   rezerv1 ;             */ 0 ,
#endif

 /*  word   Filtr_Param ;          */ 20 ,//0xDA85 ,
 /*  word   Ttr_predupr ;          */ 140 * 10 ,
 /*  word   Ttr_4mA ;              */ (w)(int)(-50.* 10) ,  //0.* 10 ,
 /*  word   Ttr_20mA ;             */ 200 * 10 ,            //250 * 10 ,

 /*  double T_Scale ;              */ 1.00 ,
 /*  word   T_Pr ;                 */ 50*10, //��. �������
 /*  word   T_Av ;                 */ 85*10, //��. �������

 /*   word   T_zaderg_pusk ;       */  _Sec( 0.61 ) ,
 /*   word   Time_Sploshnyak ;     */  _Sec( 3 ) ,
 /*   word   Time_Zatyan_Pusk ;    */  _Sec( 60 ) ,
 /*   word   Time_snyatIU_KZ ;     */  _Sec( 2 ) ,
 /*   word   Pusk_0_1 ;            */  _Skor_nom( 0.1 ) ,
 /*   word   Pusk_1_0 ;            */  _Skor_nom( 1.0 ) ,
 /*   word   N_min;                */{ _Skor_nom(0.3), _Skor_nom(0.6), _Skor_nom(0.7), _Skor_nom(0.91) },
 /*   word   Alfa_min_time ;       */  _fSec( 0.06 ),
 /*   word   Alfa_Min_Shunt ;      */  _Grad( 6 ) ,
 /*   word   Alfa_Shunt ;          */  _Grad( 60 ) ,
 /*   word   I_Ogr ;               */  _Id_nom( 1.5 ) ,
 /*   word   S_Alfa_F2_Isp ;       */  _Grad( 6 ) ,
 /*   word   rezerved[ 4 ] ;       */ { 0 },
 /*   float  Rsigma ;              */  0      , // ��   //0.068 , - ��� ������ .
 /*   float  Xsigma ;              */  0      , // ��   //0.119 , - ��� ������ .
 /*   float  Tf_aper ;             */  0.0424 , // ���������� ������� ����.����� 1 ������� - ��� �������������� ( Tf= 1/(2*_PI*S���*f���)
 /*   float  Tfil ;                */  0.0110 , // ���������� ������� ���������� ������� ����� ���������� ��� 0.011 ��� ( �� ��������� ��������� - 0.2...0.5 ��� )
 /*   word   Pary_AD ;             */  3 ,     // ����� ��� �������
 /*   word   T_Id_flt ;            */  _fSec(0.1) , // ������ ���� ������ ��� �� .
 /*   word   T_Otkl_Vent ;         */  _Sec(1*60) ,
 /*   word   T_min_Pusk ;          */  _Sec(30) ,
 /*   word   ZIS_Nachal ;          */  _Skor_nom( 0.00 ) ,
 /*   word   T_vkl_KZ ;            */  _Sec(5) ,
 /*   word   Alfa_Shunt2 ;         */  _Grad( 60 ) ,
 /*   word   Alfa_Shunt3 ;         */  _Grad( 60 ) ,

 /*   float  Km ;                  */  2.20 ,      //2.70 ,    - ��� ������ .       �� = M����/M��� , ��
 /*   word   Pnom ;           ���  */  1250 ,      //5 ,       - ��� ������ .       ���� , ���
 /*   word   Istat ;           �   */  144*10 ,    //14.7*10 , - ��� ������ .       Is , �

 /*   word   dId_sryv ;            */  _Id_nom( 0.40 ) ,
 /*   word   S_Alfa_Dvig ;         */  _Grad( 6 ) ,
 /*   word   S_Alfa_Gen ;          */  _Grad( 120 ) ,

 /*   word  N_rot_reg ;            */ _Skor_nom( 0.70 ) ,

 /*   word  razgFP_N_to_L[ 16 ];   */  {
 /*         razgFP_N_to_L[  0 ];   */    _Grad( 66.5 ),  //   0��/���  (0%)
 /*         razgFP_N_to_L[  1 ];   */    _Grad( 65.2 ),  //  25��/��� ( 5%)
 /*         razgFP_N_to_L[  2 ];   */    _Grad( 63.7 ),  //  50��/��� (10%)
 /*         razgFP_N_to_L[  3 ];   */    _Grad( 62.0 ),  //  75��/��� (15%)
 /*         razgFP_N_to_L[  4 ];   */    _Grad( 60.2 ),  // 100��/��� (20%)
 /*         razgFP_N_to_L[  5 ];   */    _Grad( 57.9 ),  // 125��/��� (25%)
 /*         razgFP_N_to_L[  6 ];   */    _Grad( 55.3 ),  // 150��/��� (30%)
 /*         razgFP_N_to_L[  7 ];   */    _Grad( 52.2 ),  // 175��/��� (35%)
 /*         razgFP_N_to_L[  8 ];   */    _Grad( 48.4 ),  // 200��/��� (40%)
 /*         razgFP_N_to_L[  9 ];   */    _Grad( 43.6 ),  // 225��/��� (45%)
 /*         razgFP_N_to_L[ 10 ];   */    _Grad( 37.2 ),  // 250��/��� (50%)
 /*         razgFP_N_to_L[ 11 ];   */    _Grad( 27.8 ),  // 275��/��� (55%)
 /*         razgFP_N_to_L[ 12 ];   */    _Grad(  5.0 ),  // 300��/��� (60%)
 /*         razgFP_N_to_L[ 13 ];   */    _Grad(  5.0 ),  // 325��/��� (65%)
 /*         razgFP_N_to_L[ 14 ];   */    _Grad(  5.0 ),  // 350��/��� (70%)
 /*         razgFP_N_to_L[ 15 ];   */     0 } ,
 /*   word  rezerv_razgFP_N[ 4 ];  */  { 0 },

 /*   word  tormFP_N_to_L[ 16 ];   */  {
 /*         tormFP_N_to_L[  0 ];   */    _Grad( 66.5 ),  //   0��/���  (0%)
 /*         tormFP_N_to_L[  1 ];   */    _Grad( 65.2 ),  //  25��/��� ( 5%)
 /*         tormFP_N_to_L[  2 ];   */    _Grad( 63.7 ),  //  50��/��� (10%)
 /*         tormFP_N_to_L[  3 ];   */    _Grad( 62.0 ),  //  75��/��� (15%)
 /*         tormFP_N_to_L[  4 ];   */    _Grad( 60.2 ),  // 100��/��� (20%)
 /*         tormFP_N_to_L[  5 ];   */    _Grad( 57.9 ),  // 125��/��� (25%)
 /*         tormFP_N_to_L[  6 ];   */    _Grad( 55.3 ),  // 150��/��� (30%)
 /*         tormFP_N_to_L[  7 ];   */    _Grad( 52.2 ),  // 175��/��� (35%)
 /*         tormFP_N_to_L[  8 ];   */    _Grad( 48.4 ),  // 200��/��� (40%)
 /*         tormFP_N_to_L[  9 ];   */    _Grad( 43.6 ),  // 225��/��� (45%)
 /*         tormFP_N_to_L[ 10 ];   */    _Grad( 37.2 ),  // 250��/��� (50%)
 /*         tormFP_N_to_L[ 11 ];   */    _Grad( 27.8 ),  // 275��/��� (55%)
 /*         tormFP_N_to_L[ 12 ];   */    _Grad(  5.0 ),  // 300��/��� (60%)
 /*         tormFP_N_to_L[ 13 ];   */    _Grad(  5.0 ),  // 325��/��� (65%)
 /*         tormFP_N_to_L[ 14 ];   */    _Grad(  5.0 ),  // 350��/��� (70%)
 /*         tormFP_N_to_L[ 15 ];   */     0 } ,
 /*   word  rezerv_tormFP_N[ 4 ];  */  { 0 },
                                   // ������� ������������ ���� ������ , ���� ��� ��������� �� ��������� � ����� ������� :
 /*   word   I_rot_nom ;        A  */  650 ,       // 16       - ��� ������ .
 /*   word   Irot_forKZ ;          */  _Id_nom( 1.50 ) ,
 /*   word   S_Alfa_Prinud_com     */  _Grad( 170 ),

 /*   word   K_f_syn3f ;           */  0,

 /*   word DeltDPSimulat;          */  0,
 
 /*   word   T_generat ;           */  _msSec( 20 ) ,

/*    word   K_Enc_syn3f;          */    0,

/*    word   Fil_buf_Len;          */   10,

/*    word   Alfa_minRT;           */   _Grad(6),
    
/*    word   Time_Min_RT;          */   _fSec(0.1),  

/*   word  rezerv[ 129 ] ;        */ { 0 },

#ifdef _INTERPRETER
 /*   struct SetpointData MemData; */ { 0 },
#endif

 /*   byte  Contrl_sum ;           */   0
  } ;

//----------------------
//    ���� ������� �� ����������������� �� ������� "F9-������� �������":
//  ��� ����������� ������� ��������� �������� � �.�.
_x_far const struct SBlok_Ustavok _sc =
  {
      //  ������� ���������: 1�������� = 1�, 1�.
                                       {   {  0, 0 },
 /* struct  {  word  oe , fe ;  } Id ; */     { _Id_nom( 1.0 ),   600 },    //16/0.816=20 //I���/0.816 , � // I�.������. = 650 � , Id = 650/0.816 = 800 � , �� ����������� �� Id = 600 �.
 /* struct  {  word  oe , fe ;  } Ud ; */     { _Ud_nom( 1.0 ),  1200 },    //216         //U��� , �       //
 /* struct  {  word  oe , fe ;  } Us ; */     { _Iv_nom( 1.0 ),  6000 },    //380         //Us   , �
 /* struct  {  word  oe , fe ;  } N  ; */     { _Skor_nom( 1.0 ), 500 } },  //925         //N    , ��/���
      //  ������� ��������� ��������:
 /* word   Id  ;                       */     {   600,   //16/0.816=20                    //I��� , �
 /* word   Ud  ;                       */        1200,   //216                            //U��� , �       // U���.������. = 1200 � , Ud = 1.35*1200 = 1620 � .
 /* word   Us  ;                       */        6000,   //380                            //Us   , �
 /* word   N   ;                       */         500 }, //925                            //N    , ��/���

 /* word Contrl_sum;                   */    0
  };

        /*   ������� ������� �������� ���������� ������� ��� ��������
         * ����� P0.
         *   ������� ������� ����� �������� ���� ���������� �������.
         * ����� ������� ������� ������� ������������ ������ ��������
         * ������� �����, ����� ������� - ������ ��������.
         */
_x_far const word  P0_tu [ 8 ] = { _Drb_msec( 25 ), _Drb_msec( 50 ),
                            _Drb_msec( 50 ), _Drb_msec( 50 ),
                            _Drb_msec( 50 ), _Drb_msec( 50 ),
                            _Drb_msec( 50 ), _Drb_msec( 50 ) } ;

_x_far const word  P1_tu [ 8 ] = { _Drb_msec( 50 ), _Drb_msec( 50 ),
                            _Drb_msec( 50 ), _Drb_msec( 50 ),
                            _Drb_msec( 20 ), _Drb_msec( 20 ),
                            _Drb_msec(  0 ), _Drb_msec(  0 ) } ;

_x_far const word  PS_tu [_SInp_max][ 8 ] = {
                                       {_Drb_msec( 50 ), _Drb_msec( 50 ),
                                        _Drb_msec( 50 ), _Drb_msec( 50 ),
                                        _Drb_msec( 50 ), _Drb_msec( 50 ),
                                        _Drb_msec( 50 ), _Drb_msec( 50 )
                                       },
                                       {_Drb_msec( 50 ), _Drb_msec( 50 ),
                                        _Drb_msec( 50 ), _Drb_msec( 50 ),
                                        _Drb_msec( 50 ), _Drb_msec( 50 ),
                                        _Drb_msec( 50 ), _Drb_msec( 50 )
                                       },
                                       {_Drb_msec( 50 ), _Drb_msec( 50 ),
                                        _Drb_msec( 50 ), _Drb_msec( 50 ),
                                        _Drb_msec( 50 ), _Drb_msec( 50 ),
                                        _Drb_msec( 50 ), _Drb_msec( 50 )
                                       },
                                       {_Drb_msec( 50 ), _Drb_msec( 50 ),
                                        _Drb_msec( 50 ), _Drb_msec( 50 ),
                                        _Drb_msec( 50 ), _Drb_msec( 50 ),
                                        _Drb_msec( 50 ), _Drb_msec( 50 )
                                       }
                                      };

union Prt Prt_NULL;
union Prt16 Prt_NULL2;
word  Izm_T_full , T_izm ;
word Time_ErrSifu;
word Time_TestFaz;
word TEK_Grads;
Reg_Str RT_Str;
word Time_Min_RT, trg_MinRT;
lword* Timer3;
lword DP_TZ;
word Err_counter[2];
float NS2_f, NS2_f1;
#pragma section =  "RAM_region"
KalmanFilter kalman(0.0f, 0.0f, 0.01f, 0.1f); // ��������� �����
//word Alfa_kor_Old , Alfa_kor ;
word T_per ;
//word TZ_sSec ;
lword T_gen;
Simulator_DP  DPSimulator;
word Accel;
word TimeStopSled;
word Trg_Sled;
float dN_max, Tpp_f;
float dT_f0;
word fr1,fr2, fr3;
word Time_f0;
byte N_inv;
byte trig_Priv_TZ , trig_Privyazk_TZ ;
float DP_buffer[_Fil_buf_max_Len];  // ����� ��� �������� ����������� ��������
word DP_index;      // ������ �������� ��������� � ������
//word Fil_buf_Len;
word Lrot_dp;
//struct tab_Ivz Ivz ; // ������ ��������������.
//Usrednit_Str Id_usr;
//word  Id_usr_full , Id_Usr ;
struct  fil  Id_flt ;
word Time_Sifu2[4] ;
word SimCounter;
word  Irot_full , Irot , dIrot ;
word  SkorPDF ;
float F_Lrot;
word TimeFrot;
word SifuRotCount;
word  wgL_rot , wgL_dp , wgL_rn_old ;
float deltwgL ;
word  wgL_rn , DProt ;
lword  TimeDP_old;
word deltTimDP;
word deltDP, deltDP_r, EncDP_old,EncDP_old_r  ;
lword QueryTimeOk/*, QueryTimeOvrOk , QueryTimeOvr , QueryTimeOvrOk_old*/;
word EncoderGray , EncoderBinar ;
word deltTDP_old, EncoderDP ,EncoderDPf ,EncoderDPr;

word  deltDPr ;//, dDp ;
byte  excess_delt ;
word  Lsety , Lrot_old, Ndpr , Lsety_old, Time_DLRot; 
float dLrot, dLdT, delta_L ;
float Velos_f;
lword  NS2_rot , NS2_rot_old , T_NS2_rot;
word  Syn_NS2_old  ;
byte priznak_CAN2_no;// ������� ������ ����� �� CAN2
byte count_CAN2_no;//������� "���������" CAN-�����
word Bbx , TEK_Grad , TEK_Grs , GradTek;
lword S_Ax, S_Bx,S_Cx, S_Dx, S_Ex ;
//word Frotdrob  
float Frotf, Fsrot  ;
word DPFiltr_drob , Encf ;
word  Tsrot ;
lword Tpp_3syn;
lword T_60gr ;
lword T_syn;
byte L_L[2];
lword Timer_long;
//������� ���������� :
union flagO flgO ;
word  Alfa_min_time ;
word  Time_shunt_end , Time_shunt , Time_Zatyan_Pusk , Time_Pusk ; //, timeSploshnyak ;
word  time_Reg , time_Integr , time_Puls ;
word  Timer_Pusk , Skor_Pusk ;
word  time_T_izm ;
word  Time_Irot_forKZ ;
/*------------------------------------------------*/
#else
/*------------------------------------------------*/

extern union Prt Prt_NULL;
extern union Prt Prt_NULL2;
extern word  Izm_T_full , T_izm ;
//extern struct tab_Ivz Ivz ;
//extern Usrednit_Str Id_usr;
//extern word  Id_usr_full , Id_Usr ;
extern struct  fil  Id_flt ;
extern word  Irot_full , Irot , dIrot ;
extern word  SkorPDF ;

extern union flagO flgO ;
extern word  Alfa_min_time ;
extern word  Time_shunt_end , Time_shunt , Time_Zatyan_Pusk , Time_Pusk ; //, timeSploshnyak ;
extern word  time_Reg , time_Integr , time_Puls ;
extern word  Timer_Pusk , Skor_Pusk ;
extern word  time_T_izm ;
extern word  Time_Irot_forKZ ;

/*------------------------------------------------*/

extern  struct        oBlok_Ustavok   _or ;
extern  _x_far const struct  oBlok_Ustavok   _oc ;
extern  _x_far const struct  SBlok_Ustavok   _sc ;

extern _x_far const word  P0_tu [ 8 ] ;
extern _x_far const word  P1_tu [ 8 ] ;

/*������������������������������������������������*/
#endif
#endif
