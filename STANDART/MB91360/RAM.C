
//-------------
#ifdef  MB91362
//-------------

word Init_RAM(void)
{
   byte al ;
   word ax ;
   lw bx ;

    CSE &= 0xFB; // 1111 1011

// ASR,AMR - адресное пространство
// AMD - 2-0 - wait state
//       4,3 - 00 - 8 bit, 01 - 16 bit, 10 - 32 bit
//       5 - 1 - Ready pin enable, 0 - Ready pin disable

#ifdef _32K_RAM
    ASR2 = 0x3F;
    AMR2 = 0x07;
    AMD2 = 0x01;      // Area Mode reg AMD2 -> 8-Bit Bus, 1 wait state, no ready-pin
#else
    ASR2 = 0x30;
    AMR2 = 0x01;
    AMD2 = 0x05;      // Area Mode reg AMD2 -> 8-Bit Bus, 5 wait state, no ready-pin
#endif

    F362MD = 0x00;   // activate ext. bus

    CSE |= 0x04; // 0000 0100

        //  КВВ 2-04-14 Обходим тест по Watchdog для ускорения загрузки и входа в работу.
#ifdef _Quick_Start
  #ifdef _WatchDog

    if ( watchdog_reset_test() == 1 )  goto  obhod ;

  #endif
#endif

    ax = 0;
    al = 0;
    //  Запись в память последовательно чисел 1...256,1...256, и т.д.
    for ( bx = RAM_START ; bx <= RAM_END ; bx++ )
    {
      *(b*)bx = ax;
      if ( al == 0)
      {
        if ( ax < 255 ) ax++;
        else al = 1;
      }
      else
      {
        if ( ax > 0 ) ax--;
        else al = 0;
      }
    }

    ax = 0;
    al = 0;
    // Считывание последовательно из памяти ранее занесенных данных.
    for ( bx = RAM_START ; bx <= RAM_END ; bx++ )
    {
      //   Проверка после каждого считывания на соответствие ранее
      // занесенным данным.
      if ( ax != *(b*)bx ) return 1;
      if ( al == 0)
      {
        if ( ax < 255 ) ax++;
        else al = 1;
      }
      else
      {
        if ( ax > 0 ) ax--;
        else al = 0;
      }
    }

#ifdef  _Quick_Start
  #ifdef _WatchDog
    obhod:
  #endif
#endif

    //  Запись в память нулей
    for ( bx = RAM_START ; bx <= RAM_END ; bx++ ) *(b*)bx = 0;
    //  Проверка на чистоту
    for ( bx = RAM_START ; bx <= RAM_END ; bx++ )
    {
      if ( *(b*)bx != 0 ) return 1;
    }

    return 0;
}

/*
void Work_RAM(void)
{
//    word i;//,bx;
    lw bx;
//    static byte Proba_mas[100000];
  //  byte bh;
//  for ( i=0; i<1000; i++) {
//    Proba_mas[i] = i;
//  }

  bx = 0x300001;
  *(b*)bx = 0x55;

}
*/

//-------------
#else  //#ifdef  MB91362
//-------------

void Init_RAM(void)
{
//    PFR9_PF96 = 1;

    CSE = 0x02; // оставляем включеным только CS1 - выборка Флэши

// ASR,AMR - адресное пространство
// AMD - 2-0 - wait state
//       4,3 - 00 - 8 bit, 01 - 16 bit, 10 - 32 bit
//       5 - 1 - Ready pin enable, 0 - Ready pin disable
    ASR2 = 0x3F;
    AMR2 = 0x07;
    AMD2 = 0x00;      // Area Mode reg AMD2 -> 8-Bit Bus, 0 wait state, no ready-pin


    F362MD = 0x00;   // activate ext. bus

    CSE = 0x87; // включены CS0, CS1, CS2, CS7

}

/*
void Work_RAM(void)
{
   lw i;//,bx;
//    static byte Proba_mas[100000];
  //  byte bh;
  for ( i=0; i<50000; i++)
  {
    Proba_mas[i] = i;
  }
  for ( i=50000; i<100000; i++)
  {
    Proba_mas[i] = 100000 - i;
  }

}
*/

//-------------
#endif  //#ifdef  MB91362
//-------------

///////////////////////////////////////////////////////////////////////////////

//------------------
#ifdef _TEST_RAM_INCLUDE
//------------------

void Test_RAM(void)
{
   byte bh , bl, al ;
   word ax ;
   lw bx ;

   char *ptr ;

      //   Следует следить, чтобы номера меток здесь и далее шли
      //  последовательно по возрастающей.
  enum { i0, i1, i2 };


              //  Контроль пароля: Полный запрет входа.

      if ( Password_control ( 2 ) == 0 )  return   ;
              //---


      if ( M_FirstCall == 1 )  //  Идентификация первого входа для задания
        {                      // начального условия ...
          output_s ( _Test_RAM_txt "\r\n") ;
          M_FirstCall = 0 ;
          Label = 0 , m_index = 0 ;
          return ;
        }

    switch ( Label )
    {
      default: Label = i0;
      case i0:
          if ( TestCompleted_Output() )
            {
              if ( m_index == 0 ) output_s ( _Test_No_txt  ) ;
              else                output_s ( _Test_Yes_txt ) ;
              Label = i1 ;
              break ;
            }

      case i1: // Обработка символов из буфера ввода, без 'while
               // до опустошения' (т.к. при ручном вводе этого не надо)
      if ( TestData_for_Input() )
        {
          mInput_c ( bh ) ;
              if ( bh == Return )  /* Выход из этого режима */
                {
             end: Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                  return ;   // добавить еще какую-то иниц.
                }
              else if ( bh == Up || bh == Down ) /* Изменить выбор. */
                {
                  m_index = ~m_index,  Label = i0 ;
                }
              else if ( bh == Enter )
                {
                  if ( m_index == 0 ) goto end ;
                  output_s ( _Waiting_txt "\n\r") ;
                  Label = i2 ;
        }       }
          break ;
    //-----------------

      case i2:
            //  заранее укладываем концовку текста адреса т.к. она всегда постоянная.
          m_buff[6] = 'h', m_buff[7] = '\r', m_buff[8] = 0 ;//NULL ;
          ax = 0;
          al = 0;
            //  Запись в память последовательно чисел 1...256,1...256, и т.д.
          for ( bx = RAM_START ; bx <= RAM_END ; bx++ )
           {
             *(b*)bx = ax;
             if ( al == 0)
             {
                if ( ax < 255 ) ax++;
                else al = 1;
             }
             else
             {
                if ( ax > 0 ) ax--;
                else al = 0;
             }
                /* Преобразование адреса в символьный вид и вывод */
             for ( bl = 5 ; (signed char) bl  >= 0 ; bl -- )
               {
                 bh = (b)( bx >> 4u*bl ) & 0x0fu ;
                 bh +=  ( bh <= 0x9 )  ?  0x30u  :  0x37u ;
                 m_buff[5-bl] = bh ; //output_c ( bh ) ;
               }
             if ( TestCompleted_Output() )  output_s ( m_buff ) ;
             //----------

           }

          ax = 0;
          al = 0;
            // Считывание последовательно из памяти ранее занесенных данных.
          for ( bx = RAM_START ; bx <= RAM_END ; bx++ )
           {
                /* Преобразование адреса в символьный вид и вывод */
             for ( bl = 5 ; (signed char) bl  >= 0 ; bl -- )
               {
                 bh = (b)( bx >> 4u*bl ) & 0x0fu ;
                 bh +=  ( bh <= 0x9 )  ?  0x30u  :  0x37u ;
                 m_buff[5-bl] = bh ; //output_c ( bh ) ;
               }
             if( TestCompleted_Output() )  output_s ( m_buff ) ;
             //----------

               //   Проверка после каждого считывания на соответствие ранее
               // занесенным данным.
             if ( ax != *(b*)bx )
               {
                 ptr = _Error_RAM_txt ;
                 output_s ( m_buff ) ; // вывод конечного адреса остановки.
                 for ( m_time = Timer1_Ovr ; (w)(Timer1_Ovr-m_time) < _Sec(3.0); ) ;
                 goto end3;
               }
             if ( al == 0)
             {
                if ( ax < 255 ) ax++;
                else al = 1;
             }
             else
             {
                if ( ax > 0 ) ax--;
                else al = 0;
             }
           }
         ptr = "  Ok.   "  ;
   end3:
         output_s ( ptr ) ; // вывод (не)исправности.
         for ( m_time = Timer1_Ovr ; (w)(Timer1_Ovr-m_time) < _Sec(3.0); ) ;
         goto end;
    }

}
//------------------
#endif  //#ifdef _TEST_RAM_INCLUDE
//------------------

