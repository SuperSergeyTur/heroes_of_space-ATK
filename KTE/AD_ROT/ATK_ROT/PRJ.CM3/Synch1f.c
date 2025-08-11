//        ПРОГРАММА СТАРТОВОЙ ПРИВЯЗКИ К СИНХРОНИЗАЦИИ.
//------------------------------------------------------------------

//-----------------
//     Один экземпляр стартовой программы пользователя для агрегатов
//  с одним источником синхронизации.
//     Для агрегатов с не одним источником синхронизации, следует добавлять
//  свои стартовые программы подобные этой.
//-----------------
  // chtoby v setku vlazylo bolee 2-x periodov i period vlazyl v znakov. setku.
#define _Tmax_setka   ( (w)(0xFFFFu/2.3) ) // /2.3 => 35Hz

  //---
#ifndef   _Extern_Synch
  //---
word Synch_Start ( void )
  {
  //lword lax;
      // настройка EPA - передаем его условный номер.
#ifndef  _Synch_3f

  #ifndef  _DMA_Synch
    init_syn_epa( _synch_epa_con ) ;
    Syn.epa_time = (lw*)&_synch_epa_time ;
  #else
    init_syn_dma() ; //    init_syn_dma( _synch_dma_con ) ;
    Syn.epa_time  = (w*)&_synch_dma_time ;
  #endif

    Sync_start ( &Syn ) ;   // остальная инициализация.

#else

  #ifndef  _DMA_Synch

   #ifndef _CM3_
    init_syn_epa( _synch_epa_con ) ;
    init_syn_epa( _synch2_epa_con ) ;
    init_syn_epa( _synch3_epa_con ) ;

    Syn.epa_time  = (w*)&_synch_epa_time ;
    Syn2.epa_time = (w*)&_synch2_epa_time ;
    Syn3.epa_time = (w*)&_synch3_epa_time ;

   #else     //  ДЛЯ СВТГ, а КТЕ не может сюда попасть???

    Syn.epa_time  = (w*)&_SyncTCA_time ; //(w*)&_synch_epa_time ;
    Syn2.epa_time = (w*)&_SyncTCB_time ; //(w*)&_synch2_epa_time ;
    Syn3.epa_time = (w*)&_SyncTCC_time ; //(w*)&_synch3_epa_time ;

   #endif

  #else
    init_syn_dma() ; //    init_syn_dma( _synch_dma_con ) ;

    Syn.epa_time  = (w*)&_synch_dma_time ;
    Syn2.epa_time = (w*)&_synch2_dma_time ;
    Syn3.epa_time = (w*)&_synch3_dma_time ;
  #endif

    Sync_start ( &Syn ) ;   // остальная инициализация.
    Sync_start ( &Syn2 ) ;   // остальная инициализация.
    Sync_start ( &Syn3 ) ;   // остальная инициализация.

    Tsyn = _MkSec( 20000 ) ;  //  Общие для 3-х фаз период и
    Fsyn_380 = 50*256 ;           //          частота.

#endif

    return  0 ;
  }


/*  ПРОГРАММА ОБРАБОТКИ СИНХРОНИЗАЦИИ */

void Synch_3f ( void )
{
          Synch ( &Syn ) ;

  #ifdef  _Synch_3f

          Synch ( &Syn2 ) ;
          Synch ( &Syn3 ) ;
                        //   Выбираем отсчет периода и частоты по одной из фаз.
        if ( _r.Cfg._.Sync_3f == 1 )
        {
          if      ( (u)(w)(Timer1_Ovr - Syn.T1_ovr )  <= 2  )  Tsyn = Hw( Syn.lTsyn ),  Fsyn_380 = Syn.Fsyn ;
          else if ( (u)(w)(Timer1_Ovr - Syn2.T1_ovr ) <= 2  )  Tsyn = Hw( Syn2.lTsyn ), Fsyn_380 = Syn2.Fsyn ;
          else if ( (u)(w)(Timer1_Ovr - Syn3.T1_ovr ) <= 2  )  Tsyn = Hw( Syn3.lTsyn ), Fsyn_380 = Syn3.Fsyn ;
        }
        else
        {
          Tsyn = Hw( Syn.lTsyn ),  Fsyn_380 = Syn.Fsyn ;
        }

  #endif
  return ;
}
  //---
#endif
  //---
//------------------------------------------------------

//-----------------
//   Универсальная часть программы синхронизации.
//-----------------

void Sync_start ( struct Synchr *syn )
  {
    syn->NS_EPA = *syn->epa_time ;
    syn->NS     = syn->NS_EPA ; // timer1 ;18.02.07 22:07
    syn->tsyn   = _MkSec( 20000 ) ;

    syn->Fsyn   = 50.0 ;
    Hw( syn->lTsyn ) = _MkSec( 20000 ) ; // для работы СИФУ.
    syn->KSDT   = 3 ;// 1 ;
    syn->NS2    = timer1 ; // chtoby zapustilos SIFU.
    syn->b_SIv  = 1 , syn->b_SIu = 1 , syn->b_SIi = 1 , syn->b_SIauto = 1 ;
    syn->T1_ovr = Timer1_Ovr-_Sec(60) ; /* Для того, чтобы знать время последнего СИ */
    //syn->time_out = Timer1_fSec - _Tmax_setka ;
    syn->NS_OLD = 0 ;
    syn->dt_old = 0 ;
    syn->b_ns_old = 0 ;
    syn->b_nsx_old = 0 ;

    return ;
  }
//------------------------------------------------------

/*  ПРОГРАММА ОБРАБОТКИ СИНХРОНИЗАЦИИ */

void Synch ( struct Synchr *syn )
{
  register word  ax , bx , cx ;
  register lword lcx ;
  float fax;

            // подтягиваем выдержку по отсутствию синхр.
    if ( (*Timer3-syn->T1_ovr) > 0x7fff ) syn->T1_ovr = *Timer3-0x7fff ;
        //---
        /*   По изменению содержимого ЕПА по сравнению с предыдущим вызовом
          * судится о том, что пришел синхроимпульс (ну или помеха) */
    if ( syn->NS_EPA == *syn->epa_time )
    { //--- Если после последнего измерения ЕПА уже был "подозрительный" СИ , и
      // прошел (период + _r.dTsyn_max) , и ЕПА больше не меняется ...
      if ( syn->KSDT == 0 )
      {
        ax = (w)(*Timer3 - (syn->NS2 + (syn->lTsyn>>16)) ) ;
             //  проверяем как знаковое, чтобы ложно не срабатывать сразу,
            // как только приняли новое NS2.
        if ( (sw)ax >= (sw)_MkSec( 20 * 55 ))  // _r.dTsyn_max )
        {     //--- Смотрим по триггеру "syn->b_ns_old" наличие пока не принятого
              // "подозрительного" СИ :
                // был ли годный СИ?
          if ( syn->b_ns_old != 0 ) goto sover ;
                // был ли отбракованный СИ?
          else  if ( syn->b_nsx_old != 0 ) syn->KSDT = 1 ;
                // не было никакого СИ.
          else                             syn->KSDT = 3 ;
        }
      }    // проверка отсутствия синхр.вообще.
      else if ( syn->KSDT != 3 )
      {      // control otsutstv.sync. ili perioda nige 30Hz.
        if ( (*Timer3 - syn->NS_EPA) >= _Tmax_setka ) syn->KSDT = 3 ;
      }
      return ;
    }
    else
    {
      syn->NS_EPA = *syn->epa_time ;   /* Запоминается текущее содержимое ЕПА */
        //---
      if ( syn->KSDT == 0 )
      {   /* Определяется значение периода СИ, а точнее
            * интервал времени между текущим и прошлым отфильтрованным.
            */
        ax = syn->NS_EPA - syn->NS2 ;
          /*   Грубое приближение на отклонение периода pri lozhnom srabat.
            * comparatora, na perehode 180grd, i чтобы
            * исключить переход к перепривязке в последующем алгоритме.
            */                                      // идем на запоминание NS.
        if ( ax < (w)((syn->lTsyn>>16)-_r.dTsyn_max) )  syn->b_nsx_old = 1 ;
        else
        {
        //--- Интервал между фактическим моментом прихода СИ и "желаемым":
        ax -= (syn->lTsyn>>16) ;
        cx = ax ;
        if ( (sw)ax < 0 ) ax = -ax ;

        //--- Смотрим по триггеру "syn->b_ns_old" наличие пока не принятого
        // "подозрительного" СИ . Если новый интервал между фактическим
        // моментом прихода СИ и "желаемым" меньше старого :
        if ( syn->b_ns_old == 0 || ax < syn->dt_old )
          {     //   Проверка отклонения периода на разрешимый допуск,
            if ( (sw)ax <= (sw)_r.dTsyn_max )
            {
              //--- Записываем все параметры этой точки прихода СИ на
              // случай , если потом она окажется самой "правильной" :
              syn->b_ns_old = 1 ; // взводим триггер прихода синхронизации .
              syn->NS_OLD = syn->NS_EPA ; // момент прихода СИ .
              syn->dt_old = ax ; // интервал до "идеальной" точки привязки .
              syn->dTsyn  = cx ; // отклонение периода .
              return ;
            }
            else  syn->KSDT = 1 ;
          }
        //--- Новый момент прихода СИ имеет худший интервал до "идеальной"
        // точки привязки , - значит нужно брать старую точку прихода СИ :
        else if ( ax > syn->dt_old )
          {
           /*  Вычисление усредненного периода (2-х байтного) СИ, прибавлением или
            * вычитанием из полного (4-х байтного) периода СИ отклонения (мгновен-
            * ного периода от усредненного) поделенного на "N" сдвигом вправо
            * относительно целой части периода СИ на n-раз ("K_synchr") или, что
            * тоже самое, сдвигом влево относительно дробной части на (16-n)-раз.
            *   Условно, таким образом, в старшие два байта, используемые в даль-
            * нейшем как усредненное значение периода, идет целая часть результата
            * деления отклонения, а в младшие два байта - остаток.
            *   Накопление остатка в младших двух байтах обеспечивает 'плавное'
            * отслеживание периода. При отбрасывании же остатка появлялся гистерезис,
            * т.е. чтобы усредненный период изменился на 1дискр. реальный период
            * должен был измениться на величину большую величины делящего коэффициента
            * (т.е. на столько, чтобы это изменение не пошло в остаток)
            */
    sover: lcx = syn->lTsyn + ((slw)(sw)syn->dTsyn << ( 16 - _r.K_synchr )) ;

                    // zaschita ot shuma - если распущены фильтры:
            if ( (w)(lcx >> 16) < _MkSec(12500) || (w)(lcx >> 16) > _MkSec(30*1000) )   // predel 80Hz //100Hz .
            {
              syn->KSDT = 3 ;
              return ;
            }

            syn->lTsyn = lcx ; // запоминаем новый период .

              /*  Вычисление текущего, отфильтрованного момента СИ. */
            ax = syn->NS2 + (syn->lTsyn>>16) , cx = syn->NS_OLD - ax ;
            Syn_NS2_old = syn->NS2;
            syn->NS2 = ax + ((sw)cx >> _r.Kf_synch ) ;
            //---
            // Запоминаем измерение как предыдущее измерение ЕПА :
            syn->NS = syn->NS_OLD ;
        sx:
            //---------------
            // Перевод периода в частоту.
            fax = (float)(Hw( syn->lTsyn )) ;
            syn->Fsyn = (float)_MkSecl(1000000)  / fax ;
            //---
            syn->b_SIv = 1, syn->b_SIu = 1, syn->b_SIi = 1, syn->b_SIauto = 1 ;
            syn->T1_ovr = Timer1_Ovr ; /* Для того, чтобы знать время последнего СИ */
            //---------------
            syn->NS_OLD = 0 ; // Инициализация для следующего определения .
            syn->dt_old = 0 ;
            syn->b_ns_old = 0 ;
            syn->b_nsx_old = 0 ;
            //--- Выход без записи syn->NS , чтобы не портить
            // весь алгоритм и не вывалиться на ветку KSDT != 0 :
            return ;
          }
        }
      }
      else
      {     // проверяем - не первое ли это ЕПА после долгой паузы?
        if ( syn->KSDT != 3 )
        {
          // Определяется мгновенное значение периода СИ, а точнее
          // интервал времени между текущим и прошлым измерениями ЕПА.
          ax = syn->NS_EPA - syn->NS ;
          cx = ax - (syn->lTsyn>>16) ;  // отклонение периода.

            /* Попытка перепривязки к каждой новой точке до тех пор пока
              * эти точки снова не пойдут с интервалом " TC +- dx ".
              */
          if ( ax >= _MkSec(12500)  &&  ax <= _MkSec(30000) ) // zaschita ot shuma: predel 80Hz //100Hz, .
          {
            if ( syn->KSDT == 1 )  syn->tsyn = ax,  syn->KSDT = 2 ;
            else  // lovim sredi musora dva podryad stabilnyh perioda:
            {    // raznica mezhdu mgnovennym tekushim i proshlym periodami.
              bx = ax - syn->tsyn ;
              if ( (sw)bx < 0 ) bx = -bx ;
              lcx = ((lw)syn->tsyn + (lw)ax ) << (16-1) ; // usredn '(a+b)/2'
              syn->tsyn = ax ;
                //---  esli otklonenie menshe chem 1/50 perioda(2%), to Ok.
              if ( bx <= (ax/50) )
              {    /*   Сбойная точка наконец-то удовлетворила всем требованиям
                    * и по-этому принимается, как новая официальная точка привязки */
                syn->lTsyn = lcx ;
                Syn_NS2_old = syn->NS2 ;
                syn->NS2 = syn->NS_EPA ;
                syn->NS = syn->NS_EPA ;
                syn->KSDT = 0 ;   /* Сброс признака сбоев по СИ */
                goto sx ;
              }
          } }
          else  syn->KSDT = 1 ;
        }
        else  syn->KSDT = 1 ;
      }
      syn->NS = syn->NS_EPA ;
    }

 return;
}
//-----------------------------------------------

