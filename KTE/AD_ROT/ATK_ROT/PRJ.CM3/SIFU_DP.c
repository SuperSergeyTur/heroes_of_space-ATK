
//         ПРОГРАММА УПРАВЛЕНИЯ СИФУ ПРЕОБРАЗОВАТЕЛЯ.
//------------------------------------------------------------


// Программа-прерывание управления преобразователем.

void S_Interrupt ( void )
{
  enum {i0,i1,i2,i3};
  word ax,cx;
  lword lax, lbx;
  //---------------------
  pS( 1 ) ;
  // Объектное (под процессор) дополнение для прерываний:
  Sifu_int_drv(_sifu_epa_con) ;  // сброс запроса прерывания.
  
  //---------------------
#ifdef  mVObj_mask    // Объектное дополнение для прерываний:
  mVObj_mask() ;  // разрешения pts-EPA0 для частотного заполнения.
#endif
  //---------------------
  if ( _or.CfgO._.Vedushiy)
  {
    
    S.flg._.BegImp = 1 ;  // 08.08.05 09:36
    //  разрешить  прерывания для АЦП, гашения ИУ .
    asm_ei() ;
    
    switch( S.NumInt )
    {
    case i1 :
      
     
/*      //Usa.flg._.F_5Gerc = 1 ;             // потом убрать
      
      //if ( Usa.flg._.F_5Gerc == 1 )   // Частота выше 5Гц - естественная коммутаци
      {
        do { ax = Timer1_Ovr , bx = timer1 ; } while ( ax != Timer1_Ovr ) ;
        ax <<= 12 ;      //  Из четырехбайтного полного значения времени берутся младший полубайт от "Timer1_Ovr"
        ax  += (bx>>4);  //  и старший байт и младший полубайт (старшие разряды) от "Timer1" принимающие
        //Timer_long = timer1;
        T_per =  ax ;
        
        
        if (T_per <  TZ_sSec)
        {
         // 
           if ((TZ_sSec - T_per) < 0x1fff)
           {
             S.flg._.TZ_Ok = 1 ;
             break;
           }
        }
        else
        {
          //S_Dx =T_per  - TZ_sSec ;
          //S.flg._.TZ_Ok = 0 ;
        }*/
                 
       // ax = T_per - ;
        
//        if ((sw)(T_per-TZ_sSec) >= 0 && (sw)(T_per-TZ_sSec) < 500) {}
//        else   { break; }
        
        /* DAN 19.05.2016 13:15 - В Каборге у Макса закоментировано .
        if ( trig_Pusk == 1 )   // контроль количесва тиристоров за период только в работе
        {
        // если за период уже больше 6-ти тиристоров ИУ не выдаем - ждем следующей синхр-ции
        if ( count_tir > 6  &&  _or.CfgO._.Contr_kol_tir_za_T == 1 )  goto sync ;
      }
        
        //S.flg._.TZ_Ok = 0 ;
        
        //LocRot_label++ ; DAN 19.05.2016 13:15 - В Каборге у Макса закоментировано .
        
        //goto perfr ; DAN 19.05.2016 13:15 - В Каборге у Макса этого нет .
      }
      */
      //perfr: DAN 19.05.2016 13:15 - В Каборге у Макса этого нет .
      
      asm_di();//Чтобы не влезло левое прерывание
      
      if ( Otkl_Imp == 0 )
      {
        if      ( S.NumMost == 1 ) {
          mFzapoln1_stop() ;// снимаем оба частотных заполнения.
          mFzapoln1_start() ;                                             
          mPort_Imp(S.NIP) ; // DAN перенесено снизу , для быстрого выполнения ,
        }                    // без контроля Шунтирования Ротора , т.к. не подъём .
        else if ( S.NumMost == 2 ) {
          mFzapoln2_stop() ;// снимаем оба частотных заполнения.
          mFzapoln2_start() ;
        }
      }
      else
      {
        mFzapoln1_stop() ;// снимаем оба частотных заполнения.
        mFzapoln2_stop() ;// снимаем оба частотных заполнения.
        mPort_Imp( FOR0 [0] ) ;
      }
      
      S.flg._.ImpSet1 = 1 ; // ИУ установлен
      
      
      asm_ei();
      if ( flgO._.Prinud_com == 0 || flgO._.trig_Prinud == 0 )
      {
        time_Prinud = timer1 ;   // Подтяжка выдержки .
        mPPG4_set( 1 ) ;         // Нет нулевой полочки .
        flgO._.trig_Prinud = 0 ; // Сброс флага начала нулевой полочки .
      }
      
      if ( Prg._.Cikl == 1 )    Cikl () ; // DAN 03.06.2016 9:14 .
      
      
      Puls_counter++ ;
      
      
      //-----
      //--  Зарядка конца ИУ - импульсы сбрасываются в другом прерывании
      T_gen = DP_TZ +  ((lw)_r.S_ImpLong * Tpp_3syn >> 14 ) ;
      
      
      //if ( (_or.CfgO._.GeneratSynh3f == 0 &&  bi_QK1 == 1) ||  Isp._.Predupr == 1 )
      //if ( _or.CfgO._.GeneratSynh3f == 0  ||  Isp._.Predupr == 1 ) DAN 19.05.2016 10:52 - У Макса в CfgO и так всё равно "0"...
      /*    {
      // if ( Usb.flg._.F_po_N == 1 )  Tpp_3syn = Tpp_n ;
      ax = _r.S_ImpLong ;
      T_gen = TZ_sSec + (w)( (lw)ax * (lw)Tpp_3syn >> 14 ) ;
      ax = T_gen << 4 ;
      _sifu_epa_time ( ax ) ;
    }
      */
 //     mUSEL_set();
 //      _sifu_epa_time ( T_gen<<4 );
 //     break; 
   
//    case i2 :
      
      //---------  СИФУ  -------------
      
      S.flg._.Fmax = 0 ;
      S.flg._.Fmin = 0 ;
      S.flg._.Fdmin  = 0 ;
      S.flg._.Fdmax  = 0 ;
      
      //count_tir++  ; DAN 19.05.2016 10:52 // для контроля числа тир за период сети ротора
      
      N_inv++ ;                   // следующий тиристор инвертора
      if ( N_inv == 07 )   N_inv = 1 ;
      
      if ( Av._.Sdvig_imp == 1 ) goto sdv ; // сдвиг импульсов в Альфа_Макс.
      else         cx = S.Alfa ;
      
      cx = S.Alfa ;
      
      //   Наступление ограничений по ЗИ и ограничителю угла друг друга
      // взаимоисключают;  по-этому поводу будет ссылка ниже ...
      //  Ограничитель угла.
      if ( cx > _r.S_Alfa_Max)
      {
      sdv: cx = _r.S_Alfa_Max;
      S.flg._.Fmax = 1;
      }
      else if ( cx < _r.S_Alfa_Min )
      {
        cx = _r.S_Alfa_Min ;
        S.flg._.Fmin = 1;
      }
      
      // ЗИ.
      if ( cx < S.Alfa_Old  )
      {
        ax = S.Alfa_Old - cx ;
        
        if ( ax > _r.S_DeltaAlfa_Max)
        {
          ax = _r.S_DeltaAlfa_Max;      //   если после ограничителя угол сел на ЗИ,
          cx = S.Alfa_Old - ax ;    //   то, следовательно, ограничение по _r.Alfa_Min если
          S.flg._.Fdmin = 1 ;   //   и было то отпало само собой и по-этому здесь
          S.flg._.Fmin  = 0 ; // <- признак ограничения _r.Alfa_Min сбрасывается.
        }
        
        lax = T_60gr - ( (lw)ax * Tpp_3syn >> 14 ) ;
      }
      else
      {
        ax = cx - S.Alfa_Old ;
        // из-за перекрытия ИУ нельзя обходить ЗИ
        if ( Av._.Sdvig_imp == 1 ) goto s2 ; // Обход ЗИ при сдвиге импульсов в Альфа_Макс.
        if ( ax > (_r.S_DeltaAlfa_Max*2) )
        {
          ax = _r.S_DeltaAlfa_Max*2 ;    // если после ограничителя угол сел на ЗИ,
          cx = S.Alfa_Old + ax ; // то, следовательно, ограничение по AlfaMax если
          S.flg._.Fdmax = 1 ;                // и было то отпало само собой и по-этому здесь
          S.flg._.Fmax = 0;                  // <- признак ограничения Fmax сбрасывается.
        }
        
      s2: lax = T_60gr + ( (lw)ax * Tpp_3syn >> 14 ) ;
      }
     // S_Cx = bx;
      /* DAN 03.08.2016 15:14
      // Задержка триггера динамики в Lmin на отключение
      if ( S.flg._.Fdmin == 1 )    { trig_Fdmin = 1 ;  count_after_Fdmin = 0 ; }
      else  if ( trig_Fdmin == 1 )
      {
      if ( count_after_Fdmin++ > 5 ) { trig_Fdmin = 0 , count_after_Fdmin = 0 ; }
    } */
      
      S.Alfa_Old = cx;      // раньше это делать нельзя.
      
      /* DAN 03.08.2016 15:14
      //-----  Корректировка СИФУ с учетом задержки аппаратного фильтра второго порядка ---
      Alfa_kor = F_to_Lkor () ;    // Функционал чатоты ротора в Угол коррекции
      
      if ( Alfa_kor != Alfa_kor_Old )
      {
      if ( Alfa_kor > Alfa_kor_Old )
      {
      if (  (Alfa_kor - Alfa_kor_Old) > _r.Temp_ZSkBM )
      {
      bx += (w)( (lw)(_r.Temp_ZSkBM) * (lw)Tpp_3syn >> 14 ) , Alfa_kor_Old += _r.Temp_ZSkBM ;
    }
      else  bx += (w)( (lw)(Alfa_kor - Alfa_kor_Old) * (lw)Tpp_3syn >> 14 ) , Alfa_kor_Old = Alfa_kor;
    }
      else
      {
      if ( (Alfa_kor_Old - Alfa_kor) > _r.Temp_ZSkBM )
      {
      bx -= (w)( (lw)(_r.Temp_ZSkBM) * (lw)Tpp_3syn >> 14 ) , Alfa_kor_Old -= _r.Temp_ZSkBM ;
    }
      else  bx -= (w)( (lw)(Alfa_kor_Old - Alfa_kor) * (lw)Tpp_3syn >> 14 ) , Alfa_kor_Old = Alfa_kor;
    }
    } */
      
      
      
      //----------------
      
     // TZ_sSec += bx ;       // для следа
      
      DP_TZ  += lax; //TZ_sSec << 4 ;  // теперь переводим в обычный формат
      // S.TZ_msec = TZ_sSec >> 12 ;
#ifndef _UPTF // Для АТК :
       if ( flgO._.Prinud_com == 1 ) // Принудительная коммутации - для оттягивания ИУ ротора на 15 мс , в течении которых
                                     // на плату АР1 инвертора подаётся нулевое задание тока для принудительной коммутации
                                     // тиристоров роторного выпрямителя . Скорость Nw ротора в принудительной коммутации
                                     // не должна быть меньше 80% ! Иначе импульсы будут сбиваться .
       {
               if ( flgO._.trig_Prinud == 0 ) // Для однократности .
               {
                     mPPG4_set( 0 ) ;         // Команда формирования нулевой полочки тока в АР1 .
                     flgO._.trig_Prinud = 1 ; // Флаг начала нулевой полочки .
                     //---
                     // Формируем Задние Фронты :
                   //mFzapoln1_stop() ;         // не снимаем частотное заполнение , чтобы не испортить длинные ИУ из 2х ИУ .
                     if ( flgO._.NeFaznRot == 0 )
                     {
                        S.NIP = FOR01 [N_inv]  ; // Импульсы только подтверждающие , без первых .
                     }
                     else
                     {
                        S.NIP = FOR21 [N_inv]  ; // Импульсы только первые , без подтверждающих , для нефазности ротора .
                     }
               }
               // Оттягиваем выдачу нового тиристора на 10-20 мс :
               if ( (w)(u)(timer1-time_Prinud) >= _MkSec(15*1000) )
               {                     
                     flgO._.new_tyr = 1 ; // флаг разрешения ИУ .
                     //---
                     flgO._.trig_Prinud = 0 ; // сбрасываем флаг начала нулевой полочки .
               }
       }
       else
#endif
      
      //if ( bi_Revers == 0 )       DAN 21.04.2016 11:35
      {
        // здесь используется промежут. ячейка NIP  чтобы сэкономить время в прерывании.
        S.NIP = FOR0[N_inv] ;  // импульсы с подтверждающими
      }
      
      if ( Otkl_Imp != 0x0 ) S.NIP = FOR0[0] ;
      
      
      // Usa.flg._.F_5Gerc = 1 ;
      asm_di();
      if ( flgO._.NewSyn == 1 )  // если пришла синхронизаци
      {
        flgO._.NewSyn = 0 ;
        //   mUSEL_clr();
        //S.flg._.Syn_Ok = 1 ;
          S_Ax = DP_TZ ;               // для следа
           S_Ex = *Timer3;
          lbx = DP_TZ ;
        
          S_Dx = NS2_rot ;           // для следа
        
          lax = NS2_rot - T_60gr*TEK_Grs;      // вычисленное NS2 по ДП ротора
          TEK_Grads = TEK_Grs ;          // для следа
          
          S_Cx = N_inv;
          
          // }
          // else           // если однократная синхронизация за период напряжения статора Uab  по ТЕКам
          // {
          if ( N_inv >= _r.S_FazirovVS ) lax += T_60gr * (lw)(N_inv - _r.S_FazirovVS ) ;
          else                           lax += T_60gr * (lw)(6u + N_inv - _r.S_FazirovVS)  ;
          // }
          S_Bx = lax;
          //S_Dx = bx ;
          lax +=  (lw)( _r.S_FazirovUgol + S.Alfa_Old ) * (lw)Tpp_3syn >> 14   ;  // добавляем  фазировочный угол и угол управлени
          
        DP_TZ = lax  ;                // для следа
        //S_Cx = 0;
        // После перепривязки проверка отклонения момента выдачи УИ от момента расчитанного
        // DAN 27.05.2016 15:32 - флаг 6-ти кратной синхронизации должен стоять всегда .
        //if ( S.flg._.Kratn6 == 1 )   // если 6-тикратная синхронизация за период напряжения статора Uab  по ТЕКам
        //{
          if ( _r.Cfg._.Ne_Revers == 1 && trig_Privyazk_TZ == 0 )
          {
            if ((DP_TZ - lbx) >= (Tpp_3syn/3)  && ( (lbx - DP_TZ) >= (Tpp_3syn/3) )) // без перепривязки и в случае его большого отклонени
            {
              
              //for ( cx = 0 ; cx < 6 ; cx++ )  // вычитается период
              //{
                DP_TZ -= Tpp_3syn*2 ;
              //}
              
              //  flgO._.n10 = 1 ;
              
              if ( _r.Cfg._.Kontaktor == 1 && S.flg._.Fdmin != 1 )  // если нет динамики в сторону Lmin
              {
                if (( (DP_TZ - lbx) >= (Tpp_3syn/3) ) && ( (lbx - DP_TZ) >= (Tpp_3syn/3) ))  //if (( (u)((w)(S.TZ - ax)) >= (w)Tsyn/8 ) && ( (u)((w)(ax - S.TZ)) >= (w)Tsyn/8 ))  // <- Когда мы при маленьком 'alfa'
                {
                  
                 // for ( cx = 0 ; cx < 12 ; cx++ )  // добавляется два периода
                 // {
                    DP_TZ += Tpp_3syn*4; 
                 // }
                  
                  //  flgO._.n11 = 1 ;
                  
                }  //  и задержке обработки очередного СИ получили его после начала новой шестерки.
              }
                
               
            }
          }
        //}
        //DP_TZ  = TZ_sSec << 4 ;           // теперь переводим в обычный формат
        //S_Cx = TZ_sSec - S_Bx;
      }
      asm_ei();      

   S.flg._.TZ_Ok = 0 ;
      _sifu_epa_time ( T_gen );
       S.NumInt = i3 ;    
       break;
    case i3 :
     // mUSEL_clr();
        //mPort_Imp(FOR0[0]) ;
        //mFzapoln1_stop() ;// снимаем оба частотных заполнения.
        //mFzapoln2_stop() ;
        S.flg._.ImpSet1 = 0 ; // для разрешения контроля ДЗВ в реверсе.
        //Разница больше 2 периодов будет считаться переполнением. 
        if ((DP_TZ < *Timer3) && ((*Timer3 - DP_TZ) < Tpp_3syn*6 ))
        {
          _sifu_epa_time ( *Timer3 + _MkSec(20) );
          
        }
        else
        {
          
          _sifu_epa_time ( DP_TZ );
        }
        
        S.NumInt = i1 ;    
      
      break;
    }
  }
  // Объектное (под процессор) дополнение для прерываний:
  // Sifu_int_drv(_sifu_epa_con) ;  // сброс запроса прерывания.
  
  pS( 0 ) ;
  
  //  Sled () ;   //150-200mcs
  
  return;
}
/*
void  back_front_epa_init ( void )
{

word ax, bx ;

init_sifu_epa( _sifu_epa_con ) ;

do { ax = Timer1_Ovr , bx = timer1 ; } while ( ax != Timer1_Ovr ) ;
ax <<= 12 ;      //  Из четырехбайтного полного значения времени берутся младший полубайт от "Timer1_Ovr"
ax  += (bx>>4);  //  и старший байт и младший полубайт (старшие разряды) от "Timer1" принимающие
//  значения в диапазоне 16мкс-1.0сек.

ax += _or.T_generat ;
T_gen = ax ;

ax = T_gen << 4 ;

_sifu_epa_time ( ax );

return ;
}


void Back_Front_Interrupt ( void )
{

enum {i0,i1,i2,i3,i4,i5};
word ax, bx;
//---------------------

// Объектное (под процессор) дополнение для прерываний:
Sifu_int_drv(_sifu_epa_con) ;  // сброс запроса прерывания.

do { ax = Timer1_Ovr , bx = timer1 ; } while ( ax != Timer1_Ovr ) ;
ax <<= 12 ;      //  Из четырехбайтного полного значения времени берутся младший полубайт от "Timer1_Ovr"
ax  += (bx>>4);  //  и старший байт и младший полубайт (старшие разряды) от "Timer1" принимающие
//  значения в диапазоне 16мкс-1.0сек.



//-------------------------

//if ((u)((w)(g_ax-T_gen)) >= 0) {}
//else   { return; }

if ((sw)(ax-T_gen) >= 0) {}
  else   { return; }


//if ( ( _or.CfgO._.GeneratSynh3f == 0 ) ||  Isp._.Predupr == 1 ) DAN 19.05.2016 10:52
{

//if ( Usb.flg._.Shunt_rot == 0 ) // Шунтирования ротора (режима подачи ИУ сплошняком) нет .
{
//      mPort_Imp(FOR0[0]) ;
//      mFzapoln1_stop() ;// снимаем оба частотных заполнения.
//      mFzapoln2_stop() ;
//      S.flg._.ImpSet1 = 0 ; // для разрешения контроля ДЗВ в реверсе.
        }

return ;
  }
}
*/