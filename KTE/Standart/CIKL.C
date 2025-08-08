
void  Cikl ( void )
{
    if ( ++SCHCIKL >= TCIKL )
    {
        SCHCIKL = 0 ;
        YKST ++ ;
    //SAP 19.01.21-------Перевод указателя  YKST в индекс массива + добавление выбранных циклов
    //-------------------для правильного отсчета, что б исключить 2 0-ля в середине таблицы
        if (( YKST > _CiklLong-1 )       //  if (( YKST > &CiklTab[_CiklLong-1] )
                   ||
            //(( CiklTab[YKST] == 0 )      // (( *YKST == 0 )
            //       &&
            // ( YKST != _CiklLong-1 )     //( YKST != &CiklTab[_CiklLong-1] )
            //       &&
            // ( CiklTab[YKST + 1] == 0 )
            //       &&
             (YKST > YKSTc-1))  YKST = 0 ; //(*( YKST + 1 ) == 0 )))  YKST = CiklTab ;
    }
    OCIKL = CiklTab[YKST];//*YKST ;
    //------------------------------------------------------------------------------------------
  //ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД

#ifdef _REG_POL
    if      ( Ckl._.RP == 1 )  ZUgol = OCIKL ;
    else
#endif
         if ( Ckl._.RS == 1 )  Z_Skor = OCIKL ;
    else if ( Ckl._.RT == 1 || Ckl._.RT1 == 1 || Ckl._.RT2 == 1 )
      {
/*--------------- SAP 18.01.21 - задания изначально 0, задаются в f2_drv.c
#ifndef _KTE_GD
        if ( OCIKL == 0 )  OCIKL = _Id_nom( 0.01 ) ; //0x0002 ;
#else
        if ( OCIKL == 0 )  OCIKL = _Ig_nom( 0.01 ) ; //0x0002 ;
#endif
 ----------------------------*/
        OuRegS_dop_kod = OCIKL ;
      }
    else if ( Ckl._.RN   == 1 )     ORT      = OCIKL ;
    else if ( Ckl._.SIFU == 1 )     S.Alfa   = OCIKL ;
#ifdef  _Vozb_KTE
    else if ( Ckl._.SIFUV== 1 )     V.Alfa   = OCIKL ;
#endif
      // Строчка выполняется в REG_EDS.C :
    //else if ( Ckl._.RTV  == 1 )     V.Iv_zad = OCIKL ;
      // Если использовать , то предусмотреть возврат уставки в норм. значение :
      // Строчка выполняется в REG_EDS.C :
    //else if ( Ckl._.Reg_EDS == 1 )  _r.Z_II_EDS = OCIKL ;

    return ;
}

#ifndef _WM591
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
      //   Переключение длины и скважности ИУ.
      //
word Short_ImpLong ( void )
{ // 25.02.2008 19:17 - добавлен контроль реверса из СИФУ , чтобы не переключать
  // ошибочно на длинные ИУ при реверсе :
  // 20.07.2017 8:22  - добавлен контроль теста на пробой тиристоров :
  if( IDV >= _r.Id_short_imp || S.flg._.Revers == 1 || flg_RaTe._.tyr_tst_go == 1 )
  {
      //   При наличии тока ИУ задаются короткими с низкой скважностью.
    if ( _r_S_ImpLong != _r.S_ImpLong )
    {
      _r_S_ImpLong = _r.S_ImpLong ;
      mSet_Fzapoln1( _FzapolnShort_Low, _FzapolnShort_High ) ;
      mSet_Fzapoln2( _FzapolnShort_Low, _FzapolnShort_High ) ;
      S.flg._.longImp = 0 ;
      return 1 ; // возвращаем "1", однократно по переключению на короткие ИУ .
  } }
  else
  {
      //   При отсутсвии тока ИУ задаются длинными с большой скважностью.
    if ( _r_S_ImpLong != _Grad(120)  )
    {
      _r_S_ImpLong = _Grad(120) ;
      mSet_Fzapoln1( _FzapolnLong_Low, _FzapolnLong_High ) ;
      mSet_Fzapoln2( _FzapolnLong_Low, _FzapolnLong_High ) ;
      S.flg._.longImp = 1 ;
  } }

  return 0 ;
}

#endif

#ifdef  _IU_60_Qubler
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
      //   Переключение скважности ИУ : Переменная скважность ИУ - переключение скважности
      // по переменной "code".
      //   Длина ИУ переключается в СИФУ по флагу реверса "S.flg._.Revers" .
      //   Если скважность аппаратная , ничего переделывать не надо , просто в "Конфиг1"
      // отключить "Частотн.ИУ"
word Short_ImpLongQubler ( word code )
{
  switch ( code )
  {
    case 0 :
      // Первые 6грд ИУ с низкой скважностью.
      if ( S.flg._.longImp == 1 ) // переинициализация , только если были длинные ИУ
      {                          // ( не было реверса )
        mSet_Fzapoln1( _FzapolnShort_Low, _FzapolnShort_High ) ;
        mSet_Fzapoln2( _FzapolnShort_Low, _FzapolnShort_High ) ;
      }
    break;

    case 1 :
      if ( S.flg._.Revers == 1 ) // При реверсе не нужно переинициализировать скважность .
       {
           S.flg._.longImp = 0 ;
           return 1 ; // Возврат "1" , чтобы ИУ были короткими .
       }
      else S.flg._.longImp = 1 ;
      //---
      // Остальные (60-6)грд ИУ с большой скважностью.
      mSet_Fzapoln1( _FzapolnLong_Low, _FzapolnLong_High ) ;
      mSet_Fzapoln2( _FzapolnLong_Low, _FzapolnLong_High ) ;
    break;
  }
return 0 ;
}
#endif  //#ifdef  _IU_60_Qubler
