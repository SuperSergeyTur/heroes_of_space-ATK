

//    ПРОГРАММА  ВЫБОРА ЦАПа И ВЫБОРА ВЫВОДИМОГО НА ЦАП ПАРАМЕТРА В
// РЕЖИМЕ ДИАЛОГА С ПОЛЬЗОВАТЕЛЕМ ПОСРЕДСТВОМ ПУЛЬТА ЛИБО КОМПЬЮТЕРА .

/*------------------------------------------------------------------*/
/*
 */

void   Vybor_DAC_tabl ( void )
{
   register byte  bh ;


              //  Контроль пароля: Полный запрет входа.

      if ( Password_control ( 2 ) == 0 )  return   ;
              //---


      if ( M_FirstCall == 1 )  /*  Идентификация первого входа для задания  */
        {                      /* начального условия ...                    */
          M_FirstCall = 0 ;
          Label = 0 ;
          m_ext = 0 ;
          return ;
        }

  switch ( Label )
    {
      case 0:
              output_s ( _DAC_tabl_txt ) ;
              output_c ( '\n' ) ;
              Label = 1 ;
      case 1:  // Ожидание завершения предыдущего вывода.
              if ( TestCompleted_Output() )
                {
                  output_c ( '\r' ) ;
                  output_s( AWelcome );
                  output_s ( DAC_tab1[ m_ext ].txt ) ;
                  Label = 2 ;
                  break ;
                }
      case 2:  while ( TestData_for_Input() )
                {
                  mInput_c ( bh ) ;
                  if ( bh == Return )
                    {
                end:  Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                      output_s ( "\r\n Ok." ) ;
                      return ;   // добавить еще какую-то иниц.
                    }
                  else if ( bh == Down ) /* Выбрать номер порта.*/
                    {
                      if ( ++m_ext >= _DAC_Ntab1 ) m_ext = 0 ;
                      Label = 1 ;
                    }
                  else if ( bh == Up ) /* Выбрать номер порта.*/
                    {
                      if ( m_ext-- == 0 ) m_ext = _DAC_Ntab1 - 1 ;
                      Label = 1 ;
                    }    /* переход к следующей настройке */
                  else if ( bh == Enter )
                  {
                   m_index = DAC_tab1[ m_ext ].p->var_num;
                       // не выводим последнюю тетсовую переменную.
                   if ( m_index >= (_DAC_Ntab2-1) ) m_index = _DAC_Ntab2-2 ;

                   output_s ( "\n\r" ) ;
                   //output_s ( DAC_tab1[ m_ext ].txt ) ;
                   //output_c ( '\n' ) ;
                   Label = 3 ;
                  }
                  else
                  {
                    Klav_Buff = bh;
                  }

                }
              if (AWelcome != AWell_old )
              {
                AWell_old = AWelcome;
                Label = 1;
              }
              break ;
            //-------------------
      case 3:  // Ожидание завершения предыдущего вывода.
              if ( TestCompleted_Output() )
                {
                  output_c ( '\r' ) ;
                  output_s( AWelcome );
                  output_s ( DAC_tab2[ m_index ].txt ) ;
                  Label = 4 ;
                  break ;
                }
      case 4:  while ( TestData_for_Input() )
                {
                  mInput_c ( bh ) ;
                  if ( bh == Return )  Label = 0 ;
                  else if ( bh == Down ) /* Выбрать номер порта.*/
                    {
                      if ( ++m_index >= (_DAC_Ntab2-1) ) m_index = 0 ;
                      Label = 3 ;
                    }
                  else if ( bh == Up ) /* Выбрать номер порта.*/
                    {
                      if ( m_index-- == 0 ) m_index = _DAC_Ntab2 - 2 ;
                      Label = 3 ;
                    }    /* переход к следующей настройке */
                  else if ( bh == Enter )
                    {

                      DAC_tab1[ m_ext ].p->var_num = m_index;
                      DAC_tab1[ m_ext ].p->mashtab = DAC_tab2[ m_index ].mashtab ;

                      goto end ;
                    }
                  else
                  {
                    Klav_Buff = bh;
                  }

                }
              if (AWelcome != AWell_old )
              {
                AWell_old = AWelcome;
                Label = 3;
              }

              break ;
            //-------------------
      }

  Restart_Output ()  ;

  return ;
}


