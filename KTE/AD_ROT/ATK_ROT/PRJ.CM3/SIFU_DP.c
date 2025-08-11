
//         ��������� ���������� ���� ���������������.
//------------------------------------------------------------


// ���������-���������� ���������� ����������������.

void S_Interrupt ( void )
{
  enum {i0,i1,i2,i3};
  word ax,cx;
  lword lax, lbx;
  //---------------------
  pS( 1 ) ;
  // ��������� (��� ���������) ���������� ��� ����������:
  Sifu_int_drv(_sifu_epa_con) ;  // ����� ������� ����������.
  
  //---------------------
#ifdef  mVObj_mask    // ��������� ���������� ��� ����������:
  mVObj_mask() ;  // ���������� pts-EPA0 ��� ���������� ����������.
#endif
  //---------------------
  if ( _or.CfgO._.Vedushiy)
  {
    
    S.flg._.BegImp = 1 ;  // 08.08.05 09:36
    //  ���������  ���������� ��� ���, ������� �� .
    asm_ei() ;
    
    switch( S.NumInt )
    {
    case i1 :
      
     
/*      //Usa.flg._.F_5Gerc = 1 ;             // ����� ������
      
      //if ( Usa.flg._.F_5Gerc == 1 )   // ������� ���� 5�� - ������������ ���������
      {
        do { ax = Timer1_Ovr , bx = timer1 ; } while ( ax != Timer1_Ovr ) ;
        ax <<= 12 ;      //  �� ��������������� ������� �������� ������� ������� ������� �������� �� "Timer1_Ovr"
        ax  += (bx>>4);  //  � ������� ���� � ������� �������� (������� �������) �� "Timer1" �����������
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
        
        /* DAN 19.05.2016 13:15 - � ������� � ����� ��������������� .
        if ( trig_Pusk == 1 )   // �������� ��������� ���������� �� ������ ������ � ������
        {
        // ���� �� ������ ��� ������ 6-�� ���������� �� �� ������ - ���� ��������� �����-���
        if ( count_tir > 6  &&  _or.CfgO._.Contr_kol_tir_za_T == 1 )  goto sync ;
      }
        
        //S.flg._.TZ_Ok = 0 ;
        
        //LocRot_label++ ; DAN 19.05.2016 13:15 - � ������� � ����� ��������������� .
        
        //goto perfr ; DAN 19.05.2016 13:15 - � ������� � ����� ����� ��� .
      }
      */
      //perfr: DAN 19.05.2016 13:15 - � ������� � ����� ����� ��� .
      
      asm_di();//����� �� ������ ����� ����������
      
      if ( Otkl_Imp == 0 )
      {
        if      ( S.NumMost == 1 ) {
          mFzapoln1_stop() ;// ������� ��� ��������� ����������.
          mFzapoln1_start() ;                                             
          mPort_Imp(S.NIP) ; // DAN ���������� ����� , ��� �������� ���������� ,
        }                    // ��� �������� ������������ ������ , �.�. �� ������ .
        else if ( S.NumMost == 2 ) {
          mFzapoln2_stop() ;// ������� ��� ��������� ����������.
          mFzapoln2_start() ;
        }
      }
      else
      {
        mFzapoln1_stop() ;// ������� ��� ��������� ����������.
        mFzapoln2_stop() ;// ������� ��� ��������� ����������.
        mPort_Imp( FOR0 [0] ) ;
      }
      
      S.flg._.ImpSet1 = 1 ; // �� ����������
      
      
      asm_ei();
      if ( flgO._.Prinud_com == 0 || flgO._.trig_Prinud == 0 )
      {
        time_Prinud = timer1 ;   // �������� �������� .
        mPPG4_set( 1 ) ;         // ��� ������� ������� .
        flgO._.trig_Prinud = 0 ; // ����� ����� ������ ������� ������� .
      }
      
      if ( Prg._.Cikl == 1 )    Cikl () ; // DAN 03.06.2016 9:14 .
      
      
      Puls_counter++ ;
      
      
      //-----
      //--  ������� ����� �� - �������� ������������ � ������ ����������
      T_gen = DP_TZ +  ((lw)_r.S_ImpLong * Tpp_3syn >> 14 ) ;
      
      
      //if ( (_or.CfgO._.GeneratSynh3f == 0 &&  bi_QK1 == 1) ||  Isp._.Predupr == 1 )
      //if ( _or.CfgO._.GeneratSynh3f == 0  ||  Isp._.Predupr == 1 ) DAN 19.05.2016 10:52 - � ����� � CfgO � ��� �� ����� "0"...
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
      
      //---------  ����  -------------
      
      S.flg._.Fmax = 0 ;
      S.flg._.Fmin = 0 ;
      S.flg._.Fdmin  = 0 ;
      S.flg._.Fdmax  = 0 ;
      
      //count_tir++  ; DAN 19.05.2016 10:52 // ��� �������� ����� ��� �� ������ ���� ������
      
      N_inv++ ;                   // ��������� �������� ���������
      if ( N_inv == 07 )   N_inv = 1 ;
      
      if ( Av._.Sdvig_imp == 1 ) goto sdv ; // ����� ��������� � �����_����.
      else         cx = S.Alfa ;
      
      cx = S.Alfa ;
      
      //   ����������� ����������� �� �� � ������������ ���� ���� �����
      // ���������������;  ��-����� ������ ����� ������ ���� ...
      //  ������������ ����.
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
      
      // ��.
      if ( cx < S.Alfa_Old  )
      {
        ax = S.Alfa_Old - cx ;
        
        if ( ax > _r.S_DeltaAlfa_Max)
        {
          ax = _r.S_DeltaAlfa_Max;      //   ���� ����� ������������ ���� ��� �� ��,
          cx = S.Alfa_Old - ax ;    //   ��, �������������, ����������� �� _r.Alfa_Min ����
          S.flg._.Fdmin = 1 ;   //   � ���� �� ������ ���� ����� � ��-����� �����
          S.flg._.Fmin  = 0 ; // <- ������� ����������� _r.Alfa_Min ������������.
        }
        
        lax = T_60gr - ( (lw)ax * Tpp_3syn >> 14 ) ;
      }
      else
      {
        ax = cx - S.Alfa_Old ;
        // ��-�� ���������� �� ������ �������� ��
        if ( Av._.Sdvig_imp == 1 ) goto s2 ; // ����� �� ��� ������ ��������� � �����_����.
        if ( ax > (_r.S_DeltaAlfa_Max*2) )
        {
          ax = _r.S_DeltaAlfa_Max*2 ;    // ���� ����� ������������ ���� ��� �� ��,
          cx = S.Alfa_Old + ax ; // ��, �������������, ����������� �� AlfaMax ����
          S.flg._.Fdmax = 1 ;                // � ���� �� ������ ���� ����� � ��-����� �����
          S.flg._.Fmax = 0;                  // <- ������� ����������� Fmax ������������.
        }
        
      s2: lax = T_60gr + ( (lw)ax * Tpp_3syn >> 14 ) ;
      }
     // S_Cx = bx;
      /* DAN 03.08.2016 15:14
      // �������� �������� �������� � Lmin �� ����������
      if ( S.flg._.Fdmin == 1 )    { trig_Fdmin = 1 ;  count_after_Fdmin = 0 ; }
      else  if ( trig_Fdmin == 1 )
      {
      if ( count_after_Fdmin++ > 5 ) { trig_Fdmin = 0 , count_after_Fdmin = 0 ; }
    } */
      
      S.Alfa_Old = cx;      // ������ ��� ������ ������.
      
      /* DAN 03.08.2016 15:14
      //-----  ������������� ���� � ������ �������� ����������� ������� ������� ������� ---
      Alfa_kor = F_to_Lkor () ;    // ���������� ������ ������ � ���� ���������
      
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
      
     // TZ_sSec += bx ;       // ��� �����
      
      DP_TZ  += lax; //TZ_sSec << 4 ;  // ������ ��������� � ������� ������
      // S.TZ_msec = TZ_sSec >> 12 ;
#ifndef _UPTF // ��� ��� :
       if ( flgO._.Prinud_com == 1 ) // �������������� ���������� - ��� ����������� �� ������ �� 15 �� , � ������� �������
                                     // �� ����� ��1 ��������� ������� ������� ������� ���� ��� �������������� ����������
                                     // ���������� ��������� ����������� . �������� Nw ������ � �������������� ����������
                                     // �� ������ ���� ������ 80% ! ����� �������� ����� ��������� .
       {
               if ( flgO._.trig_Prinud == 0 ) // ��� ������������� .
               {
                     mPPG4_set( 0 ) ;         // ������� ������������ ������� ������� ���� � ��1 .
                     flgO._.trig_Prinud = 1 ; // ���� ������ ������� ������� .
                     //---
                     // ��������� ������ ������ :
                   //mFzapoln1_stop() ;         // �� ������� ��������� ���������� , ����� �� ��������� ������� �� �� 2� �� .
                     if ( flgO._.NeFaznRot == 0 )
                     {
                        S.NIP = FOR01 [N_inv]  ; // �������� ������ �������������� , ��� ������ .
                     }
                     else
                     {
                        S.NIP = FOR21 [N_inv]  ; // �������� ������ ������ , ��� �������������� , ��� ���������� ������ .
                     }
               }
               // ���������� ������ ������ ��������� �� 10-20 �� :
               if ( (w)(u)(timer1-time_Prinud) >= _MkSec(15*1000) )
               {                     
                     flgO._.new_tyr = 1 ; // ���� ���������� �� .
                     //---
                     flgO._.trig_Prinud = 0 ; // ���������� ���� ������ ������� ������� .
               }
       }
       else
#endif
      
      //if ( bi_Revers == 0 )       DAN 21.04.2016 11:35
      {
        // ����� ������������ ��������. ������ NIP  ����� ���������� ����� � ����������.
        S.NIP = FOR0[N_inv] ;  // �������� � ���������������
      }
      
      if ( Otkl_Imp != 0x0 ) S.NIP = FOR0[0] ;
      
      
      // Usa.flg._.F_5Gerc = 1 ;
      asm_di();
      if ( flgO._.NewSyn == 1 )  // ���� ������ ������������
      {
        flgO._.NewSyn = 0 ;
        //   mUSEL_clr();
        //S.flg._.Syn_Ok = 1 ;
          S_Ax = DP_TZ ;               // ��� �����
           S_Ex = *Timer3;
          lbx = DP_TZ ;
        
          S_Dx = NS2_rot ;           // ��� �����
        
          lax = NS2_rot - T_60gr*TEK_Grs;      // ����������� NS2 �� �� ������
          TEK_Grads = TEK_Grs ;          // ��� �����
          
          S_Cx = N_inv;
          
          // }
          // else           // ���� ����������� ������������� �� ������ ���������� ������� Uab  �� �����
          // {
          if ( N_inv >= _r.S_FazirovVS ) lax += T_60gr * (lw)(N_inv - _r.S_FazirovVS ) ;
          else                           lax += T_60gr * (lw)(6u + N_inv - _r.S_FazirovVS)  ;
          // }
          S_Bx = lax;
          //S_Dx = bx ;
          lax +=  (lw)( _r.S_FazirovUgol + S.Alfa_Old ) * (lw)Tpp_3syn >> 14   ;  // ���������  ������������ ���� � ���� ���������
          
        DP_TZ = lax  ;                // ��� �����
        //S_Cx = 0;
        // ����� ������������ �������� ���������� ������� ������ �� �� ������� ������������
        // DAN 27.05.2016 15:32 - ���� 6-�� ������� ������������� ������ ������ ������ .
        //if ( S.flg._.Kratn6 == 1 )   // ���� 6-��������� ������������� �� ������ ���������� ������� Uab  �� �����
        //{
          if ( _r.Cfg._.Ne_Revers == 1 && trig_Privyazk_TZ == 0 )
          {
            if ((DP_TZ - lbx) >= (Tpp_3syn/3)  && ( (lbx - DP_TZ) >= (Tpp_3syn/3) )) // ��� ������������ � � ������ ��� �������� ���������
            {
              
              //for ( cx = 0 ; cx < 6 ; cx++ )  // ���������� ������
              //{
                DP_TZ -= Tpp_3syn*2 ;
              //}
              
              //  flgO._.n10 = 1 ;
              
              if ( _r.Cfg._.Kontaktor == 1 && S.flg._.Fdmin != 1 )  // ���� ��� �������� � ������� Lmin
              {
                if (( (DP_TZ - lbx) >= (Tpp_3syn/3) ) && ( (lbx - DP_TZ) >= (Tpp_3syn/3) ))  //if (( (u)((w)(S.TZ - ax)) >= (w)Tsyn/8 ) && ( (u)((w)(ax - S.TZ)) >= (w)Tsyn/8 ))  // <- ����� �� ��� ��������� 'alfa'
                {
                  
                 // for ( cx = 0 ; cx < 12 ; cx++ )  // ����������� ��� �������
                 // {
                    DP_TZ += Tpp_3syn*4; 
                 // }
                  
                  //  flgO._.n11 = 1 ;
                  
                }  //  � �������� ��������� ���������� �� �������� ��� ����� ������ ����� ��������.
              }
                
               
            }
          }
        //}
        //DP_TZ  = TZ_sSec << 4 ;           // ������ ��������� � ������� ������
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
        //mFzapoln1_stop() ;// ������� ��� ��������� ����������.
        //mFzapoln2_stop() ;
        S.flg._.ImpSet1 = 0 ; // ��� ���������� �������� ��� � �������.
        //������� ������ 2 �������� ����� ��������� �������������. 
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
  // ��������� (��� ���������) ���������� ��� ����������:
  // Sifu_int_drv(_sifu_epa_con) ;  // ����� ������� ����������.
  
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
ax <<= 12 ;      //  �� ��������������� ������� �������� ������� ������� ������� �������� �� "Timer1_Ovr"
ax  += (bx>>4);  //  � ������� ���� � ������� �������� (������� �������) �� "Timer1" �����������
//  �������� � ��������� 16���-1.0���.

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

// ��������� (��� ���������) ���������� ��� ����������:
Sifu_int_drv(_sifu_epa_con) ;  // ����� ������� ����������.

do { ax = Timer1_Ovr , bx = timer1 ; } while ( ax != Timer1_Ovr ) ;
ax <<= 12 ;      //  �� ��������������� ������� �������� ������� ������� ������� �������� �� "Timer1_Ovr"
ax  += (bx>>4);  //  � ������� ���� � ������� �������� (������� �������) �� "Timer1" �����������
//  �������� � ��������� 16���-1.0���.



//-------------------------

//if ((u)((w)(g_ax-T_gen)) >= 0) {}
//else   { return; }

if ((sw)(ax-T_gen) >= 0) {}
  else   { return; }


//if ( ( _or.CfgO._.GeneratSynh3f == 0 ) ||  Isp._.Predupr == 1 ) DAN 19.05.2016 10:52
{

//if ( Usb.flg._.Shunt_rot == 0 ) // ������������ ������ (������ ������ �� ����������) ��� .
{
//      mPort_Imp(FOR0[0]) ;
//      mFzapoln1_stop() ;// ������� ��� ��������� ����������.
//      mFzapoln2_stop() ;
//      S.flg._.ImpSet1 = 0 ; // ��� ���������� �������� ��� � �������.
        }

return ;
  }
}
*/