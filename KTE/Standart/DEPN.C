
//     ПРОГРАММА ДАТЧИКА ЭДС ПО НАПРЯЖЕНИЮ  'Ud'.
//------------------------------------------------------------

 //-------
   // В программе датчика ЭДС по напряжению DatEDS_Ud () в переменной "EDS"
   // в случае отрицательной ЭДС в старшем бите выставляется единица ,
   // в случае положительной ЭДС без изменений .
   // Во всех подпрограммах , использующих переменную "EDS" для того , чтобы
   // получить чистый модуль ЭДС производится операция "EDS & 0x7fff" ,
   // заменяющая единицу в старшем бите при ее наличии на нуль .
 //-------
// 13.10.06 14:03 в программу датчика ЭДС по напряжению DatEDS_Ud ()
// внесены следующие изменения :
// 1. Переменная "EDS" названа ЭДС в коде им.Шестакова "EDS_shest_kod" .
// 2. Если есть аппаратный ДЭДС , то в программе формируются переменные
//    prEDS и iEDS , - для индикации программной и аналаговой ЭДС одновременно .
// 3. Окончательное определение ЭДС для записи в переменную "EDS_dop_kod" ,
//    определение режима инвертор/выпрямитель и определение ED1 для расчета
//    гранично-непререрывного тока производится в конце программы по биту
//    в А8 - "Датчик скор." .
 //-------
// 16.04.2008 11:00 - Для всех подпрограмм , использовавших переменную "EDS"
// в виде "EDS & 0x7fff" , переменная "EDS" вычисляется как модуль ЭДС ,
// т.к. правильно сдвинуть "EDS_shest_kod" сложно .

void DatEDS_Ud  ( void )
{
 register byte  tst1, tst2, tst3, tst4 ;
 register word  dx, bx , cx, ax , zx ;
 register word ix ;
 //register slword lcx ;

      // должно стоять перед вызовом датчика ЭДС.
  if ( Prg._.RegTok == 0 && S.Disable == 0 )  // СИФУ - Штатная схема или Работа Первой секцией в 6 пульсном режиме .
    { // для подсчета ЭДС в режиме "СИФУ от резистора" :
      IDN = IDV ;
      INN = _r.INN0 ;
#ifdef  _SIFU2_
      INN_dvig = _or.INN0_dvig ;
#endif
      IDN1 = IDN ;
    }
//---
#ifdef  _SIFU2_
//---
  else if ( Prg._.RegTok == 0 && S.Disable == 1 ) // СИФУ - Работа Второй секцией в 6 пульсном режиме .
    { // для подсчета ЭДС в режиме "СИФУ от резистора" :
      IDN = IDV2 ;
      INN = _or.INN0_2_ ;
      IDN1 = IDN ;
    }
   // Перекладываем параметры РТ2 в РТ1 , для того , чтобы программный ДЭДС работал в режиме ШС2 :
   else if ( Prg._.RegTok == 1 && S.Disable == 1 ) // Работа РТ - Второй секцией в 6 пульсном режиме .
   {
      IDN = IDN_2_ ;
      INN = INN_2_ ;
      IDN1 = IDN1_2_ ;
   }

// DAN 25.11.2016 10:15 - Компенсация Ud в 12-ти пульсной схеме должна проводится по другому - решил Шестаков .
if ( _r.Sk_str._.KompUd_12p == 1 )
{
  if ( IDN >= INN_dvig ) // Если ток больше гранично-непрерывного тока в Двигателе :
  {
       if ( IDN >= INN ) // Если ток больше гранично-непрерывного тока в Мосту :
       {
         bx = 1 + _r.K_Kompen_Ud ; // Компенсация без изменений .
       }
       else              // Если ток меньше гранично-непрерывного тока в Мосту :
       {
         ax = IDN - INN_dvig ;
         if ( (sw)(INN - INN_dvig) < 0 ) bx = 0 ; // защита от ошибочно заданного гранично-непрерывного тока в Двигателе .
         else  bx = 1 + ( ax * _r.K_Kompen_Ud ) /  ( INN - INN_dvig )  ;
       }
  }
  else bx = 0 ; // Ток меньше гранично-непрерывного тока в Двигателе - Компенсации нет .

  ix = UdSr ;         // Компенсация в 12-ти пульном режиме применяется обратная , чем в 6-ти пульсном :
  if ( S.NumMost == 2 )  ix += bx ;
  else                   ix -= bx ;
}
else
//---
#endif
//---
{    // Для компенсации в 6-ти пульсной схеме :
  if ( IDN >= INN )  ax = INN + 1 ;
  else               ax = IDN ;
  bx = 1 + ( ax * _r.K_Kompen_Ud ) /  ( INN + 1 )  ;

  ix = UdSr ;
  if ( S.NumMost == 2 )  ix -= bx ;
  else                   ix += bx ;
}

  // DAN 25.11.2016 10:15 - для контроля в следе :
  Kompen_Ud = bx ; // Величина Компенсации Ud .
  UdSr_Komp = ix ; // Скомпенсированное Ud для ДЭДС .

  /*zx = ZIDN ; 11.11.2008 15:55 DAN: Нельзя брать Задание вместо Тока, тк они могут не совпадать.
  if ( Prg._.RegTok == 0 )*/   zx = IDN ;

  if ( (sw)ix >= 0 )
    {
      ZnUdSr = 0 ;
    //if ( ix > 0x01ffu ) ix = 0x01ffu ;  // 08.10.2013 - перенесено вниз .
    }
  else
    {
      ZnUdSr = 1 ;
      ix = ~ix + 1 ;
    }
  if ( ix > 0x01ffu*_K_diskr ) ix = 0x01ffu*_K_diskr ; // 511*_K_diskr

  tst1 = 0 , tst2 = 0, tst3 = 0,  ax = 0, bx = 0, cx = 0, dx = 0 ;
//  ix =  (w) ( (lw)(w)ix * (lw)(w)Masht_Eds >> 8 ) ;
   if ( ix == 0 ) ZnUdSr = 0 ;
  EDS1 = EDS_shest_kod & 0x7fffu ; //08.10.2013 16:04 DAN 0x7ffu ;
  ZNEDS1 = ZNEDS ;
  EDS_P -= EDS_P / 6 ;

  if ( zx < INN )  tst1 = 1 ;
  if ( IDN1 >= INN )
    {
      if ( IDN >= INN )
        {
          tst4 = 1 ;
          if ( IDN >= IDN1 )  ax = IDN - IDN1 ;
          else
            {
              tst2 = 1 ;
              ax = IDN1 - IDN ;
            }
  DEP1:
          if (tst1 == 0)
            {
              if (zx > IDN ) cx = zx - IDN  ;
              else  cx = IDN - zx , tst3 = 1 ;
            }
          else
            {
              cx = (IDN -INN ) + 1,  tst3 = 1;
            }
             goto DEP9;
        }
      else ax = (IDN1 - INN) + 1 , tst2 = 1 ;
      goto DEP8;
    }
  else
    {
      ax = 0 ;
      if ( IDN >= INN )
        {
          ax = ( IDN - INN ) + 1 ;
          goto DEP1;
        }
DEP8:
      bx = 0 ;
      if ( tst1 == 0 )
        {
          if ( zx > 3*INN - 2*IDN ) cx = zx - (3*INN - 2* IDN);
          else cx = 0;
        }
      else cx = 0;
      goto DEP10 ;
    }
DEP9:
  bx = (w) (((lw)( IDN - INN ) *(w) _r.KEDS_R ) >> 8 ) ;
DEP10:
  cx = (w) (((lw) cx * (w)_r.KEDS_T ) >> 8 )  ;

  dx =  ax * _r.KEDS_P   ;

  if ( ZnEDS_P == tst2 )  EDS_P = EDS_P+ dx  ;
  else
    {
      if ( EDS_P >= dx )  EDS_P = EDS_P - dx ;
      else  EDS_P = dx - EDS_P , ZnEDS_P = ZnEDS_P ^ 0x01 ;
    }
   dx =  EDS_P >>  8 ;

  if ( ZnEDS_P == tst3 ) cx = dx + cx ;
  else
    {
      if ( cx >= dx ) cx = cx - dx ;
      else            cx = dx - cx , tst3 =  tst3 ^ 0x01 ;
    }
  if ( tst3 == 1 )
    {
      if ( bx >= cx )  bx = bx - cx , tst3 = tst3 ^ 0x01;
      else             bx = cx - bx ;
    }
  else bx = bx + cx ;
  if ( ZnUdSr == tst3 )
    {
      if ( S.NumMost  == 2 )
        {
DEP11:    bx = bx + ix;
          goto DEP7;
        }
      else
        {
DEP3:     if ( bx >= ix )
            {
              bx = bx - ix ;
              tst2 = ZnUdSr ^ 0x01;
            }
          else
            {
              bx = ix - bx ;
DEP7:         tst2 = ZnUdSr  ;
            }
        }
    }
  else
    {
      if ( S.NumMost == 2 ) goto  DEP3;
      else           goto DEP11;
    }

  if ( bx == 0 )  tst2 = 0 ;

//DEP6:
    cx =   EDS1 ;

  //---------------------- 18.10.2021 - нефильтрованная ЭДС -------------------
  EDS_shest_kod_nf = bx ;
  if ( tst2 == 1 ) EDS_shest_kod_nf |=  0x8000u ;
  else             EDS_shest_kod_nf &= ~0x8000u ;

        if ( (sw)EDS_shest_kod_nf >= 0 ) EDS_dop_kod_nf = EDS_shest_kod_nf ;
        else
        {
        EDS_dop_kod_nf = EDS_shest_kod_nf ^ 0x7fff ;
        EDS_dop_kod_nf++  ;
        }
  EDS_dop_kod_nf <<= (sw)_Skor_Shift ; // ЭДС знаковая .
  //---------------------------------------------------------------------------

  if  ( _r.Sk_str._.FiltrEds == 1 )
    {

        if ( tst2 == ZNEDS1 )
         {
          if ( bx == cx )  goto fa ; // если разность равна нулю - обойти фильтр
         }
      if ( ZNEDS1 == 1 )
        {
         cx ^= 0xffffu ; // преобразование прошлого ЭДС в дополнительный код
         cx++  ;
        }
      if ( tst2   == 1 )
        {
         bx ^= 0xffffu ;   // преобразование ЭДС в дополнительный код
         bx++  ;
        }

        dx = bx - cx ;   // dx - разность между настоящим и прошлым значениями ЭДС
        ax = KFE ;

  /*-- расчет коэффициента фильтрации KFE, зависящий от величины порога Porog_FE --*/
            // если разность превышает порог
         if ( (sw)dx >= (sw)_r.Porog_FE || (sw)dx <= (sw)( ~_r.Porog_FE + 1 ))
            {
             if ( pFE == 1 )  // проверка повторности превышения.
               {
                ax = ax / 2 ; // деление КFE на два .
                if ( ax < 1 )  ax = 1 ;
               }
             else  pFE = 1 ; // регистрация первого превышения.
            }
         else  // если разность не вылезла за порог
           {
            if ( pFE == 1 )  pFE = 0 ; // превышение было одиночное.
            else
              {
               ax = ax * 2 ; // умножение КFE на два .
               if ( ax > _r.K_FE )   ax = _r.K_FE ;  // ограничение KFE.
              }
           }

          //lcx = (slw)(sw)dx ;
          //asm div  lcx , ax ;  // деление разности на рассчитанный  KFE.
          //dx = (sw)lcx ;
          //bx = (slw)lcx >> 16 ;

          bx = (sw)dx % (sw)ax ;
          dx = (sw)dx / (sw)ax ;
          if ( dx == 0 && (sw)bx > 0 )  dx = 1 ;
          if ( dx == 0 && (sw)bx < 0 )  dx =  0xffff ;
          KFE = ax ;
          bx = cx + dx ; // добавляем полученную разность к EDS1.
          tst2 = 0 ;
          if ( (sw)bx < 0 )
           {
            bx ^= 0xffffu ;
            bx++  ;
            tst2 = 1 ;
           }

       }
  fa:

//ED1 = (b) (((lw) bx * (w)_r.KKEDS ) >> 8 ) ;  13.10.06 14:03
  EDS_shest_kod = bx ;
  if ( tst2 == 1 ) EDS_shest_kod |=  0x8000u ;
  else             EDS_shest_kod &= ~0x8000u ;
  ZNEDS = tst2 ;
/*if ( ZNEDS == 0 )
    {
      if ( S.NumMost == 1 ) S.flg._.Invertor = 0 ;
      else                  S.flg._.Invertor = 1 ;
    }
  else
    {
      if ( S.NumMost == 1 ) S.flg._.Invertor = 1 ;
      else                  S.flg._.Invertor = 0 ;
    }                                              13.10.06 14:03 */

        if ( (sw)EDS_shest_kod >= 0 ) prEDS = EDS_shest_kod ;
        else
        {
        prEDS = EDS_shest_kod ^ 0x7fff ;
        prEDS++  ;
        }

#ifdef  EDS_ach
      // проверка готовности измерения :
      while ( iEDS_full == _AD_BUSY );
      mIzmData_Conversion ( iEDS_full , s_ax , EDS_ach ) ;
      iEDS = (sw)( (slw)(sw)s_ax * (slw)(sw)_r.Mashtab_EDS >> 8 ) ;

//---
// ВЫБОР ДАТЧИКОВ ЭДС : ПРОГРАММНЫЙ ИЛИ АППАРАТНЫЙ .
//---------------------------------------------------

      if ( _r.Sk_str._.EDS_Appar == 1 ) EDS_dop_kod = iEDS ; // АППАРАТНЫЙ ДЭДС .
      else // Если аппаратного ДЭДС нет , программный выполнится в любом случае,
#endif     // не смотря на значение бита _r.Sk_str._.EDS_Appar :
       {                                                     // ПРОГРАММНЫЙ ДЭДС :
          EDS_dop_kod = prEDS ;
       }

     //-- Определение режима инверт(выпрям) --//
      if ( (sw)EDS_dop_kod >= 0 ) // ЭДС знаковая .
      {
        EDS = EDS_dop_kod ;
        if ( S.NumMost == 1 ) S.flg._.Invertor = 0 ;
        else                  S.flg._.Invertor = 1 ;
      }
      else
      {
        EDS = ~EDS_dop_kod + 1 ;
        if ( S.NumMost == 1 ) S.flg._.Invertor = 1 ;
        else                  S.flg._.Invertor = 0 ;
      }

      // определение ED1 для расчета гранично непрер. тока - ЭДС берется по модулю .
      // ED1 с помощью _K_diskr всё так же привязана к 400 дискретам , чтоб не
      // менялись жизненно важные части - пересчет интегральной части при реверсе и
      // пересчёт гранично-непрерывного тока в зависмости от ЭДС :
      ED1 = (b) (((lw)EDS * (w)_r.KKEDS/_K_diskr ) >> 8 ) ;
      // сдвигать раньше нельзя , т.к. таблица TABLINN[ ED1 ] привязана к 400 дискретам :
      EDS_dop_kod <<= (sw)_Skor_Shift ; // ЭДС знаковая .
      EDS <<= _Skor_Shift ;             // ЭДС по модулю .

  return  ;
}
