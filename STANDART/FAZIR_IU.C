

//    ПРОГРАММА  ФАЗИРОВКИ  ИЗМЕРЕНИЯ  АКТИВНОГО / РЕАКТИВНОГО  ТОКОВ.
//

/*------------------------------------------------------------------*/
/*
 *   Вызов программы осуществляется из списка пультовых программ.
 *   Программа отображает на экране текущий угол фазового сдвига -
 * угол опережения СИ от перехода через нуль из "-" в "+" соответствующей
 * фазы измерямого напряжения статора.
 *   Изменение угла фазировки осуществляется в диапазоне "0...359" градусов
 * посредством следующих клавиш:
 * - в сторону увеличения - клавиша '+' пульта ;
 * - в сторону уменьшения - клавиша '-' пульта.
 *
 *   Выход из программы осуществляется нажатием клавиши 'Esc', при этом
 * значение угла фазировки остается равным последнему подобранному.
 */
void Fazirovka_Us ( void )
{
   register word    ax, bx ;


              //  Контроль пароля: Полный запрет входа.

      if ( Password_control ( 2 ) == 0 )  return   ;
              //---


      if ( M_FirstCallFazir_Us == 1 )  /*  Идентификация первого входа для задания  */
        {                      /* начального условия ...                    */
          output_s ( _Fazir_Us_txt ) ;
          M_FirstCallFazir_Us = 0 ;

          //20-10-08 Isp.all = 0 , Isp._.fazir_us = 1  ;  По Isp != 0 Резервная снимает теперь перекличку...
          output_c ( '\n' ) ;
          return ;
        }

                 //   Отображение текущего угла фазировки.
      if  ( ( TestCompleted_Output() )    // чтобы не мельтешило.
               && ( (u)((w)(Timer1_Ovr - m_time)) > 2 ) )
        {
          output_s ("\rF=")  ;

          ax = _r.Faza_Us / (w)_Grad( 1.0 ) ;
          bx = ax / 100u ;
          output_c ( (b)bx + 0x30 ) ;
          ax %= 100u ;
          bx = ax / 10u ;
          output_c ( (b)bx + 0x30 ) ;
          ax %= 10u ;
          output_c ( (b)ax + 0x30 ) ;
          m_time = Timer1_Ovr ;
        }

               /* Обработка символов из буфера ввода, без 'while
                * до опустошения' (т.к. при ручном вводе этого не надо) */
      if ( TestData_for_Input() )
        {
          mInput_c ( m_ch ) ;
              if ( m_ch == Return )  /* Выход из этого режима */
                {
                  Pult_Prog_Addr = _MainPultProg,  M_FirstCallFazir_Us = 1 ;
                  //20-10-08 Isp.all = 0  ;
                  return ;   // добавить еще какую-то иниц.
                }
              else if ( m_ch == Up ) /* Увеличить УФ плавно с дискретой "1" грд.*/
                {
                  if ( _r.Faza_Us < (w)_Grad( 359.0 ) ) _r.Faza_Us += (w)_Grad( 1.0 );
                }
              else if ( m_ch == Down ) /* Уменьшить УФ плавно с дискретой "1" грд.*/
                {
                  if ( _r.Faza_Us > (w)_Grad( 1.0 ))  _r.Faza_Us -= (w)_Grad( 1.0 );
                }
              else
                {
                  Klav_Buff = m_ch;
                }
        }

 Restart_Output ()  ;

  return ;
}

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/


void Fazirovka_Is ( void )
{
   register word    ax , bx , cx ;


              //  Контроль пароля: Полный запрет входа.

      if ( Password_control ( 2 ) == 0 )  return   ;
              //---


      if ( M_FirstCallFazir_Is == 1 )  /*  Идентификация первого входа для задания  */
        {                      /* начального условия ...                    */
          output_s ( _Fazir_Is_txt ) ;
          M_FirstCallFazir_Is = 0 ;

          //20-10-08 Isp.all = 0 , Isp._.fazir_is = 1  ;  По Isp != 0 Резервная снимает теперь перекличку...
          output_s ( _Fazir_Is_txt_Ia_Ir "\n" )  ;
          return ;
        }

                 //   Отображение текущего угла фазировки.
      if  ( ( TestCompleted_Output() )    // чтобы не мельтешило.
               && ( (u)((w)(Timer1_Ovr - m_time)) > 2 ) )
        {
          output_c ( '\r' )  ;
          ax = _r.Faza_Is / (w)_Grad( 1.0 ) ;
          bx = ax / 100u ;
          output_c ( (b)bx + 0x30 ) ;
          ax %= 100u ;
          bx = ax / 10u ;
          output_c ( (b)bx + 0x30 ) ;
          ax %= 10u ;
          output_c ( (b)ax + 0x30 ) ;
          output_c ( '.' )  ;
          ax = ((_r.Faza_Is % (w)_Grad( 1.0 )) * 10 ) / (w)_Grad( 1.0 ) ;
          output_c ( (b)ax + 0x30 ) ;

          //for ( cx = 0 ; cx < _Nnd_size ; cx++ )  // Отображение токов статора для
          for ( cx = 0 ; cx < 2 ; cx++ )  // Отображение токов статора для
            {                            // контроля их соотношения.
              ax = *Nnd[cx] ;
              if ( (sw)ax >= 0 )    output_s ( "+" ) ;
              else   ax = ~ax + 1 , output_s ( "-" ) ;

              bx = _Is_Nom / 100 ; // bx = 1% от номинала
              //bx = _Q_Nom / 100 ; // bx = 1% от номинала
              if ( bx == 0 ) bx = 1 ;
              //if ( ax > (w)(bx * 999u ))  ax =  bx * 999 ;
              if ( ax > (w)(bx *  99u ))  ax =  bx *  99 ;

              ax /= bx ;
              //m_ch = ax / 100 + 0x30,  ax %= 100 ;
              //output_c ( m_ch ) ;
              m_ch = ax / 10 + 0x30,  ax %= 10 ;
              output_c ( m_ch ) ;
              output_c ( ax + 0x30 ) ;
              //output_c ( '%' )  ;
            }
               // Вывод косинуса.
          //ax = f_Cos_fi ;
          ax = *Nnd[2] ;
          if ( (sw)ax >= 0 )    output_s ( "+" ) ;
          else   ax = ~ax + 1 , output_s ( "-" ) ;
          cx = _Cos_nom( 1.0 ) ;
          bx = ax / cx,  ax %= cx ;
          output_c ( (b)bx + 0x30 ) ;
          output_c ( '.' ) ;
          ax *= 10u,  bx = ax / cx,  ax %= cx ;
          output_c ( (b)bx + 0x30 ) ;
          ax *= 10u,  bx = ax / cx,  ax %= cx ;
          output_c ( (b)bx + 0x30 ) ;
          m_time = Timer1_Ovr ;
        }

               /* Обработка символов из буфера ввода, без 'while
                * до опустошения' (т.к. при ручном вводе этого не надо) */
          if ( TestData_for_Input() )
            {
              mInput_c ( m_ch ) ;
              if ( m_ch == Return )  /* Выход из этого режима */
                {
                  Pult_Prog_Addr = _MainPultProg,  M_FirstCallFazir_Is = 1 ;
                  //20-10-08 Isp.all = 0  ;
                  return ;   // добавить еще какую-то иниц.
                }
              else if ( m_ch == Up ) /* Увеличить УФ плавно с дискретой "1" грд.*/
                {
                  if ( _r.Faza_Is <= (w)_Grad( 359.0 ) ) _r.Faza_Is += (w)_Grad( 0.51 );
                  else                                   _r.Faza_Is  = (w)_Grad( 0.0  );
                }
              else if ( m_ch == Down ) /* Уменьшить УФ плавно с дискретой "1" грд.*/
                {
                  if ( _r.Faza_Is >= (w)_Grad( 0.51 )) _r.Faza_Is -= (w)_Grad(   0.51 );
                  else                                 _r.Faza_Is  = (w)_Grad( 359.51  );
                }
              else
                {
                  Klav_Buff = m_ch;
                }
            }

 Restart_Output ()  ;

  return ;
}

