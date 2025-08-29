
// KVV 2025-06-10 дадаемо проізводну по завданню швидкості для того щоб допомогти інтегратору 
// не залазити дуже у перерегулювання, а потім після зупинки ЗІ довго повертатися на потрібне значення 

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

     // при темпі ЗІ-РС 3.5% ЗІ буде змінюватися на 1 дискрету за 17мсек, 
     // тому для точності беремо період 100мсек + ще щоб не проскакували нулі проізводної
     word time = Timer1_fSec;
     if ((u)((w)(time - timeOld)) >= _fSec(0.100)) 
     {
         timeOld = time;
         //---

         proizv = (sw)(zadSkor - zadSkorOld) * 10 ; // ... * 10 = ... / fSec(0.100) * fSec(1.0)  перевод микросекунд в секунды
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
                                        // "<< 8"-догоняем "Kp*256" до формата
    #ifdef _KTE_GD   //----- 15.10.08 ---------------
        lax = lax * _Ig_nom(0.01) / _Skor_nom(0.01) << 8 ; // коэфф."Ki=x*65536".
    #else
        lax = lax * _Id_nom(0.01) / _Skor_nom(0.01) << 8 ; // коэфф."Ki=x*65536".
    #endif
        lax &= 0x7ffffffful ;   //защита от "-" коэфф.
        //--------------------------------------------------
  

    //-----------------03.08.07 12:53-------------------
    //---------- preventive overflow control -----------
        word cx = ax;                     // ошибка .
        if ((sw)cx < 0)  cx = -cx; // выпрямленная ошибка .
        // Если lax = 0 , то процессор _CM3_ при делении на нуль получает нуль , входит в условие
        // и выдаёт максимальный выход , что есть неправильно . Поэтому проверяем , что lax != 0 :
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
       //  Подготовка к контролю переполнения (без использ.'asm'):
       // если до сложения/вычитания операнды были одного знака, а результат
       // получился другого знака - значит произошло переполнение.
     word cx = 2 ;
     if ( (slw)lax >= 0 ) // запоминаем сочетание знаков операндов.
      {
          if( (slw)toValue >= 0 ) cx = 0 ; // +/+
      }
     else if( (slw)toValue <  0 ) cx = 1 ; // -/-

     lax += (slw)toValue; 
     
     lword result = 0;

              /* Проверка переполнений. */
                  //  переполнение в плюс?
          if     ( cx == 0 && (slw)lax <  0 ) goto p1 ;
                  //  переполнение в минус?
          else if( cx == 1 && (slw)lax >= 0 ) goto p2 ;
    //--------------------------------------------------

     
              /* Проверка ограничений. */
#ifdef  _CM3_
          if ( (slw)lax < (slw)0xf8000000 ) // 0xfe000000
            {
    p2:       result = (slw)0xf8000000 ; // -512*4 дискрет .
            }  // не подпускаем к краю сетки, чтобы можно было контролир.переполн.
          else if ( (slw)lax >= (slw)0x07ff0000 )  //0x01ff0000
            {
    p1:       result = (slw)0x07ff0000 ; // +512*4 дискрет .
            }
#else
          if ( (slw)lax < (slw)0xfe000000 )
            {
    p2:       result = (slw)0xfe000000 ; // -512 дискрет .
            }  // не подпускаем к краю сетки, чтобы можно было контролир.переполн.
          else if ( (slw)lax >= (slw)0x01ff0000 )
            {
    p1:       result = (slw)0x01ff0000 ; // +512 дискрет .
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