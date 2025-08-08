//        Программа расчета величин Tau,Kq и 1/Kq в соответствии
// с вышеизложенной теорией.

# include  <stdio.h>
# include  <dos.h>
# include  <stdlib.h>
# include  <process.h>
# include  <math.h>

  typedef unsigned char     byte  ;
  typedef unsigned int      word  ;
  typedef unsigned int      w     ;
  typedef unsigned long int lword ;
  typedef unsigned long int lw    ;

void write_error ( FILE *fp )
    {
      fclose (fp ) ;
      system ("del #teplo.h") ;
      printf ("\n\n  Сложности с записью в рабочий файл < #teplo.h > !") ;
      printf ("\n\n    РАБОЧИЙ ФАЙЛ < #TEPLO.H > НЕ СФОРМИРОВАН !") ;
      printf ("\n\n РАБОТА ПРОГРАММЫ ПРЕРВАНА !") ;
      return ;
    }


        void main (int argc, char *argv[])
{

 int  n , i , err , warning = 0 ;
 lword xKq[25] ;
 lword xKq_Ohlad ;
 lword xKq1 ;
 lword xKq_Obratn ;
 double Ip[25] ;
 double tp[25] ;
 double tp_Ohlad ;

 double dt , tau  ;
 double Im ;  // Ipn-1%
 double It_Nom ,Kq ;
 float x ;
 FILE *fp ;

 system ("cls")  ;
 fp = fopen ("#teplo_u.h","r") ;
 if ( fp != NULL )
   {
     fclose (fp) ;
     fp = fopen ("#teplo_u.bak","r") ;
     if ( fp != NULL )
       {
         fclose (fp) ;
   system ("del #teplo_u.bak")  ;
       }
     system ("rename #teplo_u.h #teplo_u.bak")  ;
   }

printf ("\n\n    Введите, пожалуйста, принятое в Вашей программе значение ")  ;
printf ("\n  (в дискретах) соответствующее номинальному току используемому")  ;
printf ("\n  для теплового расчета: ")  ;

  scanf  ("%f",&x)  ;
  It_Nom=(double)x  ;
  printf ("\n значение соответствующее номинальному току\n составляет %-9.2fдискрет ?! ... хорошо.",It_Nom)  ;

 printf ("\n  Введите, пожалуйста, количество элементов токово-временной таблицы : ")  ;
 scanf  ("%d",&n)  ;
 if     ( n > 11 )
			{
                                printf ("\n   Неужели есть необходимость использовать такое большое количество элементов ?!")  ;
                                printf ("\n Не сумеете ли Вы обойтись 11-ю элементами ?!",n)  ;
                                printf ("\n\n    РАБОЧИЙ ФАЙЛ < #TEPLO.H > НЕ СФОРМИРОВАН !") ;
                                printf ("\n\n РАБОТА ПРОГРАММЫ ПРЕРВАНА !") ;
				return  ;
			}
 printf (" %3d элементов ?! ... хорошо,",n)  ;
 printf ("\nтеперь введите, пожалуйста, токово-временную таблицу\n(по убывающей в зависимости от тока) :")  ;

 for ( i = 0 ; i < n  ; i++ )
	{
  printf ("\nее %2d-й элемент: ток (в номиналах)  - ",i+1)  ;
  scanf  ("%f",&x)  ;
  Ip[i]=(double)x  ;

  if ( (i != 0) && ( Ip[i] >= Ip[i-1] ))
    {
      printf ("\n\n   Таблица должна вводиться по убывающей в зависимости от тока!")  ;
      printf ("\n\n РАБОТА ПРОГРАММЫ ПРЕРВАНА !") ;
      return ;
    }

  printf ("           время (сек) - ")  ;
  scanf  ("%f",&x)  ;
  tp[i]=(double)x  ;
  printf ("\n ток = %-9.2f* Iном   , а время = %-9.2fсек ?! ... хорошо,",Ip[i],tp[i])  ;
	}
  printf ("\b.")  ;

printf ("\n\n   Введите, пожалуйста, требуемое время охлаждения после нагрева до\n макс. значения (сек): ")  ;
  scanf  ("%f",&x)  ;
  tp_Ohlad = (double)x  ;
  printf ("\n время охлаждения составляет %-9.2fсек ?! ... хорошо.", tp_Ohlad )  ;

  Im = ( Ip[n-1] * It_Nom - 1. ) / It_Nom  ;

printf ("\n\n   Введите, пожалуйста, период цикла прозводимого Вашей программой\n  теплового перерасчета (сек) :  ")  ;
  scanf  ("%f",&x)  ;
  dt=(double)x  ;
  printf ("\n  период цикла перерасчета составляет %-9.2fсек ?! ... хорошо.",dt)  ;

  printf ("\n\n  Результаты расчета:")  ;

 xKq_Obratn = 0xffffu ;

 for ( i = 0 ; i < n  ; i++ )
	{
  tau = -tp[i] / log( (Ip[i]*It_Nom-Im*It_Nom) / (Ip[i]*It_Nom-It_Nom) )  ;
  Kq = 1-exp(-dt/tau)  ;

  xKq1 = (lw)(1./Kq) ;
  if ( xKq1 < xKq_Obratn ) xKq_Obratn = xKq1 ;

  xKq[i] = (lw)(Kq*256.*256.*256.) + 1u  ;  /* "+1" - для округления в большую сторону */
  printf ("\n  I = % 9.2f   tau = % 9.2f  Kq = % 9.6f (0.%08lxh) ",Ip[i],tau,Kq,xKq[i])  ;
  if ( xKq[i] >= 0x00ffffu )
    {
      warning++ ;
      xKq[i] = 0x00ffffu  ;
      Kq = (double) xKq[i] / 256. / 256. / 256. ;
      xKq1 = xKq_Obratn = (lw)(1./Kq) ;

      printf ("\n\n    ПРЕДУПРЕЖДЕНИЕ:") ;
      printf ("\n    Коэффициент для данной точки таблицы вышел за допустимый") ;
      printf ("\n диапазон. Коэффициент ограничен на уровне %f и при этом", Kq) ;
      printf ("\n время выдержки для данной точки составит %f сек.",dt / log( 1 - Kq ) * log((Ip[i]*It_Nom-Im*It_Nom)/(Ip[i]*It_Nom-It_Nom))) ;
      printf ("\n Измените данные для этой точки или время цикла перерасчета") ;
      printf ("\n для всех точек, либо согласитесь с принятым ограничением.") ;
    }
  }

  tau = -tp_Ohlad / log( (Ip[n-1]*It_Nom-Im*It_Nom) / (Ip[n-1]*It_Nom-It_Nom) )  ;
  Kq = 1-exp(-dt/tau)  ;
  xKq_Ohlad = (lw)(Kq*256.*256.*256.) ; /* для охлаждения "+1" - не надо для округления в большую сторону */
  printf ("\n\n  (для охлаждения)  tau = % 9.2f  Kq = % 9.6f (0.%08lxh)",tau,Kq,xKq_Ohlad)  ;
  if ( xKq_Ohlad >= 0x00ffffu )
    {
      warning++ ;
      xKq_Ohlad = 0x00ffffu  ;
      Kq = (double) xKq_Ohlad / 256. / 256. / 256. ;

      printf ("\n\n    ПРЕДУПРЕЖДЕНИЕ:") ;
      printf ("\n    Коэффициент для режима охлаждения вышел за допустимый") ;
      printf ("\n диапазон. Коэффициент ограничен на уровне %f и при этом", Kq) ;
      printf ("\n время выдержки охлаждения составит %f сек.",dt / log( 1 - Kq ) * log( (Ip[n-1]*It_Nom-Im*It_Nom) / (Ip[n-1]*It_Nom-It_Nom) )) ;
      printf ("\n Измените данные для охлаждения или время цикла перерасчета") ;
      printf ("\n для всех точек, либо согласитесь с принятым ограничением.") ;
    }

  //--------------------------------------------------------------

  fp = fopen ("#teplo_u.h","w") ;

  if ( fp == NULL )
    {
      printf ("\n\n  Сложности с открытием рабочего файла < #teplo_u.h > !") ;
      printf ("\n\n    РАБОЧИЙ ФАЙЛ < #TEPLO_U.H > НЕ СФОРМИРОВАН !") ;
      printf ("\n\n РАБОТА ПРОГРАММЫ ПРЕРВАНА !") ;
      return ;
    }

  err  = fprintf ( fp, "\n /* Файл сформирован программой < %s >. */", argv[0] ) ;

  err |= fprintf ( fp, "\n\n  #ifndef _Teplo_dat_h" ) ;

  err |= fprintf ( fp, "\n  #define _Teplo_dat_h" ) ;

  err |= fprintf ( fp, "\n\n    /*   Значение в дискретах, соответствующее номинальному " ) ;
  err |= fprintf ( fp, "\n     * значению тока, используемого для теплового расчета.  */" ) ;
  err |= fprintf ( fp, "\n\n  #define  _It_Nom_dat       ( (w) %-3d )", (w)(It_Nom+0.5) ) ;

  err |= fprintf ( fp, "\n\n    /* Количество точек заданной токовременной таблицы. */" ) ;
  err |= fprintf ( fp, "\n\n  #define  _NumTeploPoint_dat ( (b) %-2d )", (byte)n ) ;

  err |= fprintf ( fp, "\n\n/*------------------------------------------------*/" ) ;
  err |= fprintf ( fp, "\n#ifdef _MAIN_INCLUDE  " ) ;
  err |= fprintf ( fp, "\n/*------------------------------------------------*/" ) ;

  err |= fprintf ( fp, "\n\n    /*   Таблица токов заданной токовременной таблицы. */") ;

  err |= fprintf ( fp, "\n\n  const word  _Tok_dat [ _NumTeploPoint_dat ] = {" ) ;

  for ( i = n - 1 ; i != 0 ; i-- )
    {
      err |= fprintf ( fp, "\n                             (d) %-f * (d)_It_Nom_dat + (d) 0.5 ,", Ip[i] ) ;
    }
  err |= fprintf ( fp, "\n                             (d) %-f * (d)_It_Nom_dat + (d) 0.5  ", Ip[0] ) ;
  err |= fprintf ( fp, "\n                                    };" ) ;

  err |= fprintf ( fp, "\n\n    /*   Таблица коэффициентов расчета нагрева. Коэффициенты ") ;
  err |= fprintf ( fp, "\n     *  в таблице расположены соответственно токам в вышеприведеной таблице.") ;
  err |= fprintf ( fp, "\n     *  Обе таблицы используются для нахождения коэфф. расчета как функции") ;
  err |= fprintf ( fp, "\n     *  текущего тока. На интервалах между точками коэффициент вычисляется") ;
  err |= fprintf ( fp, "\n     *  путем линейной аппроксимации.") ;
  err |= fprintf ( fp, "\n     */") ;

  err |= fprintf ( fp, "\n\n  const word  _Kq_dat  [ _NumTeploPoint_dat ] = {" ) ;

  for ( i = n - 1 ; i != 0 ; i-- )
    {
      err |= fprintf ( fp, "\n                                      0x%04xu ,", (w)xKq[i] ) ;
    }
  err |= fprintf ( fp, "\n                                      0x%04xu", (w)xKq[0] ) ;
  err |= fprintf ( fp, "\n                                    };" ) ;

  err |= fprintf ( fp, "\n\nconst struct Teplo_Data tpl_dat =" ) ;
  err |= fprintf ( fp, "\n{" ) ;

  err |= fprintf ( fp, "\n\n    /* Количество точек заданной токовременной таблицы. */" ) ;
  err |= fprintf ( fp, "\n\n  /* word   NumTeploPoint = */   _NumTeploPoint_dat," ) ;

  err |= fprintf ( fp, "\n\n    /* Время цикла перерасчета тепловой защиты ( в милисекундах). */" ) ;
  err |= fprintf ( fp, "\n\n  /* word   TimeCikl_Teplo = */  %-d, ", (w)(dt*1000) ) ;

  err |= fprintf ( fp, "\n\n    /*   Макс. доп. значение нагрева ( вычисляется в том же масштабе,") ;
  err |= fprintf ( fp, "\n     * что и ток). Соответствует макс.доп. значению старших двух байт") ;
  err |= fprintf ( fp, "\n     * теплового интегратора.") ;
  err |= fprintf ( fp, "\n     */" ) ;

  err |= fprintf ( fp, "\n\n  /* word   TeploMax = */ (w)( %-f * (d)_It_Nom_dat + (d) 0.5),", Im ) ;

  err |= fprintf ( fp, "\n\n    /*   Значение в дискретах, соответствующее номинальному " ) ;
  err |= fprintf ( fp, "\n     * значению тока, используемого для теплового расчета.  */" ) ;
  err |= fprintf ( fp, "\n    /*   Номинальное значение нагрева вычисляется в том же масштабе,") ;
  err |= fprintf ( fp, "\n     * что и ток. Соответствует установившемуся значению старших двух байт") ;
  err |= fprintf ( fp, "\n     * теплового интегратора при длительном номинальном токе.") ;
  err |= fprintf ( fp, "\n     */" ) ;

  err |= fprintf ( fp, "\n\n  /* word   TeploNom = */    _It_Nom_dat,") ;

  err |= fprintf ( fp, "\n\n    /*   Таблица токов заданной токовременной таблицы. */") ;

  err |= fprintf ( fp, "\n\n/* const word  *Tok = */  (word*)&_Tok_dat[0]," ) ;

  err |= fprintf ( fp, "\n\n    /*   Таблица коэффициентов расчета нагрева. */") ;

  err |= fprintf ( fp, "\n\n/* const word  *Kq = */ (word*)&_Kq_dat[0]," ) ;

  err |= fprintf ( fp, "\n\n    /*   Коэффициент расчета охлаждения. */") ;
  err |= fprintf ( fp, "\n\n/* const word  Kq_Ohlad = */ 0x%04xu,", (w)xKq_Ohlad  ) ;

  err |= fprintf ( fp, "\n\n    /*   Коэффициент расчета допустимого тока как функции вычисленного нагрева.") ;
  err |= fprintf ( fp, "\n     *  Следовало бы иметь таблицу коэфф. расположенных соответственно токам,") ;
  err |= fprintf ( fp, "\n     *  но в этом случае отсутствует плавность наложения ограничения на ток (при ") ;
  err |= fprintf ( fp, "\n     *  монотонном(!) нагреве или охлаждении) из-за перехода от одного коэффициента") ;
  err |= fprintf ( fp, "\n     *  к другому (в зависимости от диапазона тока).") ;
  err |= fprintf ( fp, "\n     *    Поэтому выбран один обратный коэфф. соответствующий наибольшему коэфф. из") ;
  err |= fprintf ( fp, "\n     *  таблицы '_Kq[]', что обеспечивает наибольшую плавность наростания или снижения") ;
  err |= fprintf ( fp, "\n     *  ограничения и его несколько более раннее наложение.") ;
  err |= fprintf ( fp, "\n     *  Если выбрать обратный коэфф. соответствующий наименьшему коэфф. из таблицы") ;
  err |= fprintf ( fp, "\n     *  '_Kq[]', то при этом будет наблюдаться резкое наростание или снижение") ;
  err |= fprintf ( fp, "\n     *  ограничения при его несколько более позднем наложение.") ;
  err |= fprintf ( fp, "\n     */") ;

  err |= fprintf ( fp, "\n\n/* const word  _Kq_Obratn = */ 0x%04xu", (w)xKq_Obratn ) ;
  err |= fprintf ( fp, "\n\n};") ;

  err |= fprintf ( fp, "\n\n/*------------------------------------------------*/" ) ;
  err |= fprintf ( fp, "\n#else " ) ;
  err |= fprintf ( fp, "\n/*------------------------------------------------*/" ) ;


  err |= fprintf ( fp, "\n\n  extern const word  _Tok_dat [ _NumTeploPoint_dat ]  ;" ) ;
  err |= fprintf ( fp, "\n\n  extern const word  _Kq_dat [ _NumTeploPoint_dat ]  ;" ) ;
  err |= fprintf ( fp, "\n\n  extern const struct Teplo_Data tpl_dat ;" ) ;


  err |= fprintf ( fp, "\n\n/*---------------------------------------------*/" ) ;
  err |= fprintf ( fp, "\n  #endif" ) ;
  err |= fprintf ( fp, "\n  #endif" ) ;

  if ( err < 0 )
    {
      write_error ( fp )  ;
      return ;
    }

  fclose ( fp ) ;

  printf ("\n\n\n   РАБОЧИЙ ФАЙЛ < #TEPLO.H > СФОРМИРОВАН !") ;
  printf ("\n\n   РАБОТА ПРОГРАММЫ ЗАВЕРШЕНА !") ;
  printf ("\n\n   ПРЕДУПРЕЖДЕНИЙ:      %d.\r\n\r\n", warning) ;

 return  ;
}
