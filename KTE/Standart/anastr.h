#ifndef _ANASTR_H
#define _ANASTR_H

void Avtonastroyka_RT (word code) ;
word ANastr_Ra_Te (void) ;
word ANastr_Tm (void) ;
void Tm_def_AN(void) ;
word AN_Kreg (void) ;

//#define _R0   1000
//#define _Ra_Nom   ((_Ud_Nom*10) / _Id_Nom * _R0 )/10     // _Ra_Nom = 2000, если _Ud_Nom=400d,_Id_Nom=200d

//#define  _AN_Av            "\r\n АН oстановлена!"
//#define  _AN_Ra_Te         "\r\n Rя,Te определены."
//#define  _AN_Tm            "\r\n Tm определена."
//#define  _AN_Err           "\r\n Нет измер.Id-гр "   //"\r\n Ошибка расчета!"
//#define  _AN_Kreg          "\r\n Ki,Kp определены."
//#define  _AN_Iv_min        "\r\n Не снят If!"

#ifdef   _AN_INCLUDE

    byte AnastrRT ;
    byte kn_Label , kp_Label , kpr_Label ;
    byte deln , delp , delpr ;
    byte AN_Label ;
    word AN_Alfa_Inom ;
    word AN_Alfa_05Inom ;
    word Id_AN_high;
    word Id_AN_low;
    word Id_AN_t1;
    word Tei[6];
  //word Rai[6];
    word IN0i[6];
    word OIRT_AN[6];
    word KtpRa_nepr[6];
    word KtpRa_pr[6];
  //word KtpRa_AN_pr, KtpRa_AN_nepr ;
    word iTei;
    byte IN0n ;
     // 12.11.2008 11:34 : DAN - Во время переключения областей уставок принимались типовые ,
     // из-за того что программа меняла сами уставки РТ .
     //word K_perereg_AN_old;
  //sword Id_AN_imp; // 20.05.2009 12:01 - Перенесено в SIFU.H .

    word Test_Point_1_for_AN ;    // test point
    word Test_Point_2_for_AN ;    // test point

// Для определения Tm
    word Id_for_Imax[3] ;
    word T_for_Imax[3] ;
    word Tmi[10];
    word iTmi;
    word Last_Angle_Tm;
	word Id_max_AN ;
    word Id_max_tmp_AN ;
    word k_AN ;
    word n_izm_AN;
	word tmax_AN ;
    word tmax_tmp_AN ;
    word flag_Tm;

    word AN_Id_04Inn, AN_Id_07Inn, AN_Id_05Inom,  AN_Id_95Inom;
    word AN_Alfa_04Inn, AN_Alfa_07Inn, AN_Alfa_95Inom;


// Te = 5 ... 100 [ms]
// Tm = 5 ... 1000 [ms]     - !!!
// To(Tm,Te)[ms] = to[ms*10]
_x_far const word To_x10[1][20] = {
        {60,       91,     116,     136,     154,     171,     186,     200,     213,     226,     238,     250,     261,     271,     281,     291,     301,     310,     319,     328}
       };

    word S_Alfa_IzmDoImp , Id_AN_imp1 ;

    word Ud_AN[6];   // Массив для определения уставки "К-комп-Ud"
                     // для проверки алгоритма определения Гр-Непр-тока :
    word Id_AN[6];   // беззнаковый ток в  2 грд до ИУ .
    word Id_AN1[6];  //    знаковый ток в 10 грд до ИУ .
    word Id_AN2[6];  // беззнаковый ток в 10 грд до ИУ .

#else

    extern byte AnastrRT ;
    extern byte kn_Label , kp_Label , kpr_Label ;
    extern byte deln , delp , delpr ;
    extern byte AN_Label;
    extern word AN_Alfa_Inom;
    extern word AN_Alfa_05Inom;
    extern word Id_AN_high;
    extern word Id_AN_low;
    extern word Id_AN_t1;
    extern word Tei[];
  //extern word Rai[];
    extern word IN0i[];
    extern word OIRT_AN[];
    extern word KtpRa_nepr[];
    extern word KtpRa_pr[];

  //extern word KtpRa_AN_pr, KtpRa_AN_nepr ;
    extern word iTei;
    extern byte IN0n ;
    //extern word K_perereg_AN_old;
  //extern sword Id_AN_imp; // 20.05.2009 12:01 - Перенесено в SIFU.H .

    extern word Test_Point_1_for_AN ;    // test point
    extern word Test_Point_2_for_AN ;    // test point

// Для определения Tm
    extern word Id_for_Imax[] ;
    extern word T_for_Imax[] ;
    extern word Tmi[];
    extern word iTmi;
    extern word Last_Angle_Tm;
    extern word Id_max_AN ;
    extern word Id_max_tmp_AN ;
    extern word k_AN ;
    extern word n_izm_AN;
    extern word tmax_AN ;
    extern word tmax_tmp_AN ;
    extern word flag_Tm;
    extern _x_far const word To_x10[][20] ;
    extern word S_Alfa_IzmDoImp , Id_AN_imp1 ;

    extern word AN_Id_04Inn, AN_Id_07Inn, AN_Id_05Inom,  AN_Id_95Inom;
    extern word AN_Alfa_04Inn, AN_Alfa_07Inn, AN_Alfa_05Inom,  AN_Alfa_95Inom;

    extern word Ud_AN[6];   // Массив для определения уставки "К-комп-Ud"
                            // для проверки алгоритма определения Гр-Непр-тока :
    extern word Id_AN[6];   // беззнаковый ток в  2 грд до ИУ .
    extern word Id_AN1[6];  //    знаковый ток в 10 грд до ИУ .
    extern word Id_AN2[6];  // беззнаковый ток в 10 грд до ИУ .

#endif
#endif
