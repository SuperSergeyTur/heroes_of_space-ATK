

//    ПРОГРАММА  ФАЗИРОВКИ  СИФУ  ВОЗБУДИТЕЛЯ  В  РЕЖИМЕ  ДИАЛОГА  С
//  ПОЛЬЗОВАТЕЛЕМ  ПОСРЕДСТВОМ  ПУЛЬТА  ЛИБО  КОМПЬЮТЕРА .

/*------------------------------------------------------------------*/
/*   Программа может быть вызвана только в фазе сборки готовности при
 * отсутствии сигнала "Готовность".
 *   Вызов программы осуществляется из списка пультовых программ.
 *   После входа в программу импульсы подаются с углом управ-
 * ления '0' градусов.
 *   Программа отображает на экране текущий заданный ей угол фазировки - угол
 * опережения СИ от перехода через нуль из "-" в "+" силового напряжения "Uac".
 *   Изменение угла фазировки "грубо" с дискретностью 60-градусов осуществ-
 * ляется в диапазоне "0...300"-градусов посредством клавиши 'f' или 'F'.
 *   Изменение угла фазировки "точно" с дискретностью 1-градус осуществляется
 * в диапазоне "0...+60" градусов посредством следующих клавиш:
 * - в сторону увеличения - клавиша '+' пульта ;
 * - в сторону уменьшения - клавиша '-' пульта.
 *
 *   В процессе подбора угла фазировки программа преобразует его в
 * необходимый для СИФУ вид, выделяя из него две составляющие:
 * - номер тиристора, ТЕК которого наименее отстает от СИ:
 *                                          Ъ
 *                                          і x = 0, то  _r.V_FazirovVS = 1 ;
 * x = целая часть от ( Ф / 60грд. ), если <
 *                                          і x > 0, то  _r.V_FazirovVS = 7 - x ;
 *                                          А
 * - угол отставания ТЕК данного тиристора от СИ:
 *        _r.V_FazirovUgol = остаток часть от ( Ф / 60грд. ) .
 *
 *   Выход из программы осуществляется нажатием клавиши 'Esc', при этом
 * значение угла фазировки остается равным последнему подобранному.
 */

#ifndef    bi_OtklFazirV
  #define  bi_OtklFazirV   bi_Q1
#endif
  //---

void Fazirovka_V ( void )
{
   register word    ax ;


              //  Контроль пароля: Полный запрет входа.

      if ( Password_control ( 2 ) == 0 )  return   ;
              //---


      if ( M_FirstCallFazir == 1 )  /*  Идентификация первого входа для задания  */
        {                      /* начального условия ...                    */
          output_s ( _Fazir_vozb_txt ) ;
          M_FirstCallFazir = 0 ,   LabelFazir = 0 ;
          Isp._.Predupr = 1;
          m_ext = _r.V_Alfa_Min  ;   // сохранение уставки.
              //---
          return ;
        }        //  Серега добавил для встроенного возб.КТЭ.
      //---
      #ifdef _Vozb_KTE
        else if ( (Prg._.Gotovn == 0)&&(Av._.Avar == 0) )
        {  // Чтобы в паузе формирования предупреждения не принимались клавиши ,
          if ( TestData_for_Input() )     // изменяющие существующую фазировку .
            {
              mInput_c ( m_ch ) ;
               if ( m_ch == Return )  /* Выход из этого режима */
                {
                  goto end;
                }
            }
         return ;
        }
      #endif
      //---

          /*   Контроль того, что импульсы действительно сдвинулись в нуль,
           * а не заблокированы авариями, например "Id_max".
           */
    if ( LabelFazir != 25 )
    {                                        // 29.05.07 09:33
      if ( Prg._.Gotovn == 0 )
        {
          output_s ( _Dostup_Gotovn_txt ) ;
          goto end1 ;
        }
      if ( bi_OtklFazirV == 1 )
        {
          output_s ( _Fazir_txt_Q1) ;
          goto end1;
        }
      else if ( bi_Avtomat220 == 0 )
        {
          output_s ( _Fazir_txt_avt220 ) ;
          goto end1;
        }
        //---
      if ( ( LabelFazir >= 10 && V.Alfa_Old != 0 )
                         ||
           ( LabelFazir >= 17 && Otkl_Imp != 0 ))
        {
          output_s ( _Fazir_sdvig_txt ) ;
          goto  end1 ;
        }
    }

    switch ( LabelFazir )
     {
      default: LabelFazir = 0 ;
      case 0:
          mOtkl_Imp( _VR1_imp ) ;
          _r.V_Alfa_Min = 0 ;   // сдвиг импульсов в нуль.
          mSet_Alfa( 0 ) ;

          m_time = Timer1_Ovr ;
          LabelFazir = 5 ;
          break ;

      case 5:  /* Выдержка, чтобы импульсы успели сместиться в нуль. */
          if ( (u)((w)(Timer1_Ovr - m_time)) < (w)_Sec( 1.0 ) ) break ;

          output_c ( '\n' ) ;
//-----
#ifdef  _Fazir_2Mosta  //---- для двухмостовых возбудителей.
          NumMost = 1 ; // m_index = 1 ;//NumMost ;
          LabelFazir = 10 ;
#else
          LabelFazir = 17 ;
          mVkl_Imp( _All_imp ) ;
#endif //-----
//-----
          break ;

      case 10:
//-----
          mOtkl_Imp( _VR1_imp ) ;//Vit 29.05.07 09:29
#ifdef  _Fazir_2Mosta  //---- для двухмостовых возбудителей.
          if ( TestCompleted_Output() )
            {       //   Отображение текущих номера моста и угла фазировки.
              output_s ( _Fazir_Most )  ;
              m_ch = (b)NumMost  & 0x0fu ;
              m_ch += 0x30u ;
              output_c ( m_ch ) ;
              LabelFazir = 15 ;
              break ;
            }

      case 15: /* Обработка символов из буфера ввода, без 'while
                * до опустошения' (т.к. при ручном вводе этого не надо) */
          if ( TestData_for_Input() )
            {
              mInput_c ( m_ch ) ;
                  if ( m_ch == Return )  /* Выход из этого режима */
#endif //-----
//----- // оставлено для выхода по "Esc".
                    {
                 end: LabelFazir = 2,  M_FirstCallFazir = 1 ;// Pult_Prog_Addr = _MainPultProg ,  M_FirstCall = 1 ;
                      Isp._.Predupr = 0;
                      mSet_Alfa( _r.V_Alfa_Start ) ;   // на всякий случай.
                      _r.V_Alfa_Min  =  m_ext ; // восстановление уставки
                      return ;   // добавить еще какую-то иниц.
                    }
//-----
#ifdef  _Fazir_2Mosta  //---- для двухмостовых возбудителей.
                  else if ( m_ch == Up ) /* Изменить выбор. */
                    {
                      if ( NumMost == 1 ) NumMost = 2  ; //m_index
                      else                NumMost = 1  ; //m_index
                      LabelFazir = 10 ;
                      break ;
                    }
                  else if ( m_ch == Enter )
                    {
                      output_c ( '\n' ) ;
                      //NumMost = m_index ;
                      LabelFazir = 17 ;
                      mVkl_Imp( _All_imp ^ _Rev_imp ) ;
            }       }
          break ;
#endif //-----
//-----

      case 17:   //   Отображение текущего угла фазировки.
        if ( TestCompleted_Output() )
          {
            output_s ("\rN=")  ;
            m_ch = _r.V_FazirovVS + 0x30 ;
            output_c ( m_ch ) ;
            output_s (",F=")  ;

            ax = _r.V_FazirovUgol / (w)_Grad( 1.0 ) ;
            m_ch = ax / 10u ;
            output_c ( (b)m_ch + 0x30 ) ;
            m_ch = ax % 10u ;
            output_c ( (b)m_ch + 0x30 ) ;

            LabelFazir = 20 ;
            break ;
          }

      case 20: /* Обработка символов из буфера ввода, без 'while
                * до опустошения' (т.к. при ручном вводе этого не надо) */
      if ( TestData_for_Input() )
        {
          mInput_c ( m_ch ) ;
              if ( m_ch == Return )  /* Выход из этого режима */
                {
                //  mOtkl_Imp( _VR1_imp ) ;    Vit 29.05.07 09:29
                  output_c ( '\n' ) ;
                  LabelFazir = 10 ;
                }
              else if ( m_ch == Up ) /* Увеличить УФ плавно с дискретой "1" грд.*/
                {
                  _r.V_FazirovUgol += _Grad( 1.0 );
                  if ( _r.V_FazirovUgol > _Grad( 60.0 ) ) _r.V_FazirovUgol = _Grad( 60.0 );
                  LabelFazir = 17 ;
                }
              else if ( m_ch == Down ) /* Уменьшить УФ плавно с дискретой "1" грд.*/
                {
                  _r.V_FazirovUgol -= _Grad( 1.0 );
                  if ( (sw)_r.V_FazirovUgol < 0 )  _r.V_FazirovUgol = 0 ;
                  LabelFazir = 17 ;
                }
              else if ( m_ch == Enter ) /* Изменить номер ФТ.*/
                {
                  _r.V_FazirovVS --;             // изменяется циклически в сторону уменьшения.
                  if ( _r.V_FazirovVS  == 0 )  _r.V_FazirovVS  = 6;
                  LabelFazir = 17 ;
                }
        }
            break ;
          //----------
        end1:   // при первом входе - выход без отключения ИУ - если вошли в Фазир. в Работе.
            if ( LabelFazir != 0 )
            {
              mOtkl_Imp( _VR1_imp ) ;
            }
            m_time = Timer1_Ovr,  LabelFazir = 25 ;
              //---
            break ;

      case 25:
              if ( (u)((w)(Timer1_Ovr-m_time)) > _Sec( 2.0 ) )  goto end;
            break ;
    }

 Restart_Output ()  ;

  return ;
}

