
// KVV 2025-06-10 ������� ��������� �� �������� �������� ��� ���� ��� ��������� ����������� 
// �� �������� ���� � ���������������, � ���� ���� ������� ǲ ����� ����������� �� ������� �������� 

 sword CalcZSkorProizv( word code, sword zadSkor )
 {
     static sword  zadSkorOld;
     static  word  timeOld;
     static sword  proizv;

     // Init
     if (code == 0)
     {
         proizv = 0;
         zadSkorOld  = zadSkor;
         timeOld = Timer1_fSec;
         return 0;
     }

     // ��� ���� ǲ-�� 3.5% ǲ ���� ���������� �� 1 �������� �� 17����, 
     // ���� ��� ������� ������ ����� 100���� + �� ��� �� ������������ ��� ���������
     word time = Timer1_fSec;
     if ((u)((w)(time - timeOld)) >= _fSec(0.100)) 
     {
         timeOld = time;
         //---

         proizv = (sw)(zadSkor - zadSkorOld) * 10 ; // ... * 10 = ... / fSec(0.100) * fSec(1.0)  ������� ����������� � �������
         //---

         zadSkorOld = zadSkor;
     }
     
     return proizv;
 }
 //-----------------------------


 lword CalcKpZSkorProizv( word kp, sword proizv )
 {
     word ax = proizv;
     lword lax = kp;

         //-----------------03.08.07 12:53-------------------
                                        // "<< 8"-�������� "Kp*256" �� �������
    #ifdef _KTE_GD   //----- 15.10.08 ---------------
        lax = lax * _Ig_nom(0.01) / _Skor_nom(0.01) << 8 ; // �����."Ki=x*65536".
    #else
        lax = lax * _Id_nom(0.01) / _Skor_nom(0.01) << 8 ; // �����."Ki=x*65536".
    #endif
        lax &= 0x7ffffffful ;   //������ �� "-" �����.
        //--------------------------------------------------
  

    //-----------------03.08.07 12:53-------------------
    //---------- preventive overflow control -----------
        word cx = ax;                     // ������ .
        if ((sw)cx < 0)  cx = -cx; // ������������ ������ .
        // ���� lax = 0 , �� ��������� _CM3_ ��� ������� �� ���� �������� ���� , ������ � �������
        // � ����� ������������ ����� , ��� ���� ����������� . ������� ��������� , ��� lax != 0 :
        if (((lw)cx >= (lw)0x7fffffff / lax) && (lax != 0))    // sravnivaem modul oshibki
        {                                       // s maksimalno dopustimoy
            if ((sw)ax >= 0) lax = 0x7fffffff; // pri vychislennom 'Kp',
            else             lax = 0x80000000; // dlya 32-bit setki oshibkoy.
        }
        else  lax = (slw)lax * (slw)(sw)ax;

     return lax;
 }
 //-----------------------------


 lword AddProizvToValue( lword proizv, lword toValue )
 {

     lword lax = proizv;

         //-----------------03.08.07 12:53-------------------
       //  ���������� � �������� ������������ (��� �������.'asm'):
       // ���� �� ��������/��������� �������� ���� ������ �����, � ���������
       // ��������� ������� ����� - ������ ��������� ������������.
     word cx = 2 ;
     if ( (slw)lax >= 0 ) // ���������� ��������� ������ ���������.
      {
          if( (slw)toValue >= 0 ) cx = 0 ; // +/+
      }
     else if( (slw)toValue <  0 ) cx = 1 ; // -/-

     lax += (slw)toValue; 
     
     lword result = 0;

              /* �������� ������������. */
                  //  ������������ � ����?
          if     ( cx == 0 && (slw)lax <  0 ) goto p1 ;
                  //  ������������ � �����?
          else if( cx == 1 && (slw)lax >= 0 ) goto p2 ;
    //--------------------------------------------------

     
              /* �������� �����������. */
#ifdef  _CM3_
          if ( (slw)lax < (slw)0xf8000000 ) // 0xfe000000
            {
    p2:       result = (slw)0xf8000000 ; // -512*4 ������� .
            }  // �� ���������� � ���� �����, ����� ����� ���� ���������.��������.
          else if ( (slw)lax >= (slw)0x07ff0000 )  //0x01ff0000
            {
    p1:       result = (slw)0x07ff0000 ; // +512*4 ������� .
            }
#else
          if ( (slw)lax < (slw)0xfe000000 )
            {
    p2:       result = (slw)0xfe000000 ; // -512 ������� .
            }  // �� ���������� � ���� �����, ����� ����� ���� ���������.��������.
          else if ( (slw)lax >= (slw)0x01ff0000 )
            {
    p1:       result = (slw)0x01ff0000 ; // +512 ������� .
            }
#endif
          else result = (slw)lax ;

     return result;
 }
 //-----------------------------

 
 lword AddZSkorProizv( word code, sword zadSkor, lword toValue )
 {
     if (code == 0)
     {
         CalcZSkorProizv( 0, zadSkor );
         return toValue;
     }

     ZSkorProizv = CalcZSkorProizv( 1, zadSkor );

     lword lax = CalcKpZSkorProizv( _or.KRSPZSkorProizv, ZSkorProizv );

     ZSkorProizvKp = (slw)lax >> 16 ;

     if ( _or.KRSPZSkorProizv == 0 )  return toValue;
    
     lax = AddProizvToValue( lax, toValue );
     
     return lax;
 }
 //-----------------------------