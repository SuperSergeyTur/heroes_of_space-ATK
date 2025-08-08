
//         ПРОГРАММА  РЕГУЛЯТОРА ТОКА ЯКОРЯ .
//----------------------------------------------------------

void RegTok (void)
{
  word  ax, cx ;
  lword lax ;

  if ( _r.KRTNI != 0 )
  {
    ax = Id_flt.out - ZIDN ;

    lax = _r.KRTNI;

    if ( lax == 0 )
     {             // инициализация интегратора при Ки = 0 :
       OIRT = 0 ;
       OIRT_drob = 0 ;
       goto v4 ;
     }

    //-------------- 01.04.09 -------------------------------------

    lax = (lw)( (d)_Skor_nom(0.01) / (d)_Id_nom ( 0.01 ) * time_Integr/1000 * 65535. * 64. ) / lax ;
    lax &= 0x7ffffffful ;  //защита от "-" коэфф.
    //--------------------------------------------------


    //-----------------03.08.07 12:53-------------------
    //---------- preventive overflow control -----------
    cx = ax ;                     // ошибка .
    if ( (sw)cx < 0 )  cx = -cx ; // выпрямленная ошибка .
    // Если lax = 0 , то процессор _CM3_ при делении на нуль получает нуль , входит в условие
    // и выдаёт максимальный выход , что есть неправильно . Поэтому проверяем , что lax != 0 :
    if ( ((lw)cx >= (lw)0x7fffffff / lax) && (lax != 0) )    // sravnivaem modul oshibki
     {                                       // s maksimalno dopustimoy
       if ( (sw)ax >= 0 ) lax = 0x7fffffff ; // pri vychislennom 'Ki',
       else               lax = 0x80000000 ; // dlya 32-bit setki oshibkoy.
     }
    else  lax = (slw)lax * (slw)(sw)ax ;
    //asm   mul  lax , ax ;   // умножение интегр. коэффициента на ошибку
    //--------------------------------------------------

    //-----------------03.08.07 12:53-------------------
       //  Подготовка к контролю переполнения (без использ.'asm'):
       // если до сложения/вычитания операнды были одного знака, а результат
       // получился другого знака - значит произошло переполнение.
     cx = 2 ;
     if ( (slw)lax >= 0 ) // запоминаем сочетание знаков операндов.
      {
          if( (sw)OIRT >= 0 ) cx = 0 ; // +/+
      }
     else if( (sw)OIRT <  0 ) cx = 1 ; // -/-

     lax += (slw)(sw)OIRT << 16 ;
     lax += (lw)(w)OIRT_drob ;   // DROB ISN'T SIGNED !

              /* Проверка переполнений. */
                  //  переполнение в плюс?
          if     ( cx == 0 && (slw)lax <  0 ) goto v1 ;
                  //  переполнение в минус?
          else if( cx == 1 && (slw)lax >= 0 ) goto v2 ;
    //--------------------------------------------------

              /* Проверка ограничений. */
          if ( (slw)lax < ((slw)0 ) )
            {
    v2:       lax = 0 ;
            }
          else if ( (slw)lax >= ((slw)_Skor_nom(1.00) << 16) )
            {
    v1:       lax = (lw)_Skor_nom(1.00) << 16 ;
            }

         OIRT = (slw)lax >> 16 ; // дробная часть уходит, целая записывается .
         OIRT_drob = lax ;       // запись дробной части .
  }

  v4:

  return;
}



//------------------------------------
		/*Программа линеаризации */

void Linear (void)
{
   register word  ax , bx , cx ;

  if ( ORT <= _Ugol_90 )  ax = ORT ;
  else                    ax = _Ugol_180 - ORT ;
    bx  = LIN [ ax >> 8 ] ;
    cx  = LIN [(ax >> 8) + 1 ] ;
    cx -= bx ;
    bx += (w)( (lw)cx * (lw)(ax & 0x00FFu) / 0x0100ul ) ;
  if ( ORT <= _Ugol_90 ) S.Alfa = bx;
  else                   S.Alfa = _Ugol_180 - bx ;
return;

}

//------------------------------------
        /*Программа ЗИРТ */

 void Zad_IntensRT ( struct ZIRT *zip )
{
//    Т.к. эта функция вызывается как из фона так и
//  из прерываний то, по-скольку компилятор не позволяет описать функцию
//  как реентерабельную, для сохранения временных переменных в стеке их
//  следует описать как автоматические, а не как регистровые (т.к.
//  автоматические переменные компилятор распологает в стеке).

//  Однополярный ЗИРТ , для однополярного РТ .

#if _K_diskr == 1 // 10-ти разрядный АЦП - 200d .
  lword lax ;
   word ax;

//ax = (w)( timer1 - zip->time ) / (w)_Sec( 1.0 ) ;
// FAA  _Sec( 4.0 ) - dla povisheniya tocnosti v preobrazov. makrosa (esli brat _Sec( 1.0 ) to pri tempe 70 za 10 sek poluchaem ~810, a pri _Sec( 4.0 ) oshibka ne vidna
  ax = (w)((lw)(4ul * (lw)(w)( timer1 - zip->time ) ) / (lw)_Sec( 4.0 )) ;
  zip->time = timer1 ;  // запись момента текущей отработки ЗИ.

  if ( (w)zip->in != (w)zip->out )
    {
      lax = (lw)zip->drob ;
      lax += (lw)zip->out << 16 ;

      if ( (w)zip->in > (w)zip->out )
        {
          lax += (lw)*zip->temp_p * (lw)ax ;
          zip->drob = (w) lax;
          zip->out  = (w) ( lax >> 16 ) ;
          if ( (w)zip->out > (w)zip->in ) zip->out = zip->in ;
        }
      else
       {
          lax -= (lw)*zip->temp_m * (lw)ax ;
          zip->drob = (w) lax;
          zip->out  = (w) ( lax >> 16 ) ;
          if ( (w)zip->out < (w)zip->in ) zip->out = zip->in ;
    }  }
#else // 12-ти разрядный АЦП - 800d .

   double ax;

// FAA  _Sec( 4.0 ) - dla povisheniya tocnosti v preobrazov. makrosa (esli brat _Sec( 1.0 ) to pri tempe 70 za 10 sek poluchaem ~810, a pri _Sec( 4.0 ) oshibka ne vidna
//ax = (d)(w)( timer1 - zip->time ) / (d)((lw)_Sec( 1.0 ) << 16);
  ax = (d)((lw)(4ul * (lw)(w)( timer1 - zip->time )))/ (d)((lw)_Sec( 4.0 ) << 16);
  zip->time = timer1 ;  // запись момента текущей отработки ЗИ.

  // Темпы берутся с номиналом 200 дискрет , поэтому приводим в соответствие с номиналом .

  if ( zip->in != zip->out )
    {
      if ( zip->in > zip->out )
        {
          zip->out += (d)*zip->temp_p * (d)_K_diskr * ax ;
          if ( zip->out > zip->in ) zip->out = zip->in ;
        }
      else
       {
          zip->out -= (d)*zip->temp_m * (d)_K_diskr * ax ;
          if ( zip->out < zip->in ) zip->out = zip->in ;
    }  }
#endif

  return ;
}

void Set_ZIRT ( struct ZIRT *zip , word ax )
{
#if _K_diskr == 1 // 10-ти разрядный АЦП - 200d .
  zip->in = ax ;
  zip->out = ax ;
#else // 12-ти разрядный АЦП - 800d .
  zip->in = (d)ax ;
  zip->out = (d)ax ;
#endif
  zip->drob = 0 ;
  zip->time = timer1 ;

  return ;
}
