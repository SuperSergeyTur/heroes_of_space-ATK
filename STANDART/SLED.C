
//       ПРОГРАММЫ РАБОТЫ СО СЛЕДОМ.
//
//   Включают:
// - программа занесения информации в след;
// - программа распечатки следа в табличном виде на дисплее ПК.
//---------------------------------------------------------

void Start_Sled ( void )
{
  sl_d.index = 0 ;  /* Указатель памяти в поле следа */
  sl_d.index_stop = 0 ;  /* Указатель памяти в поле следа */
  sl_d.print_size = 0 ;   /* Распечатываемый размер следа. */
  sl_d.label = 0 ;  /* метка для программы TestSledTab() */
  sl_d.activ = 0 ;  // bo_SledActiv = 0 ;
  sl_d.Stop = 0 ;
#ifdef _Sld_cond

   sl_cond_old = 0;

#endif
      //   Находим соответствие именам из рабочей таблицы имен
      // в const-таблице и списываем ее свежие параметры (адрес),
      // поскольку при перезашивке адрес переменной мог измениться
      // по-сравнению с устаревшим адресом данной переменной хранящимся в i2c.
  while ( TestSledTab () != 0 ) ;

  return ;
}
//-----------------------

 void Sled ( void )
  {
    register lword ax = 0, lax;
    word bx ;
    register lword ptr ;
    const struct Sled_var register *dptr ;

           //  отсчет времени такта следа.
   // для следа в прерывании if ( (u)((w)(timer1-sl_d.time)) < (u)sled.dt_scan )  return ;
   // sl_d.time = timer1 ;
      /*   Отсчет кратности вызова следа для возможности его растягивания
       * во времени для медленных процессов.
       */ //перенесено вверх чтобы и выбег следа тоже отслеживался кратно.
    if ( ++sl_d.count < sled.kratn ) return ;


  #ifdef    bi_SledVneshStop
    if ( bi_SledVneshStop == 1 )   Prg._.Sled = 0 ;
  #endif


        //  Отсчет выдержки на откл. следа после команды остановки.
    if ( bi_SledStop == 1 )
    {
      if ( bo_SledActiv == 1 )
      {
        if ( sl_d.count2 >= sled.dt_stop )
        {
              //  Фиксируем время остановки следа.
      //  if ( Read _i2c_time() != 4 )
      //  {    //  если в момент аварии след был остановлен, например по "F5",
               // то "msg_av" здесь не обновляется и в i2c записывается то
               // что в нем было записано раньше.
            msg_reg.time = c_time ;
            msg_av = msg_reg ; // для сохранения по аварии в i2c и распечатки по 'F1'.
            bo_SledActiv = 0 ;
            sl_d.print_size = sl_d.index_stop ;   /* Рассчитывем распечатываемый размер следа. */
            sl_d.index_stop = 0 ;   /* готовимся к следующему циклу. */
      //  }
          return ;
        }
        else sl_d.count2++ ;
      }
      else
      {     //  отсчет времени на автоматическое включение следа.
        if ( ((u)((w)(Timer1_Ovr-sl_d.time_out)) >  sled.t_start) &&(sled.t_start != 0))
        {
          bo_SledStart = 1 ;
          sl_d.Stop = 0 ;
        }
          // после "bo_SledStart = 1" все равно должен войти в След по новому циклу.
        return ;
      }
    }
    else
    {
      sl_d.count2 = 0 ;
      bo_SledActiv = 1 ;
    }
    sl_d.time_out = Timer1_Ovr ;

    //if ( ++sl_d.count >= sled.kratn )
      {
        if ( sled.n_kanal > _SledTabSizeMax  ) sled.n_kanal = _SledTabSizeMax ;
        sl_d.count = 0 ;
        ptr = sl_d.index ; // для повышения быстродействия использ. рег.
        do {
             if ( ptr >= _SizeSledPole )  ptr = 0 ;

               //  для уменьшения последующего времени вычислений
               // однократно вычисляем адрес в таблице.
             dptr = &(FullSledTab[sl_d.tab[ax]]) ;

             switch ( dptr->code._.type )
             {
               case 0 :
                        for(bx = 0; bx < sizeof(float); ++bx)
                        {
                            if ( ptr >= _SizeSledPole )  ptr = 0 ;
                            SledPole [ptr++] = *((b*)(dptr->addr)+bx) ;  //плавающую точку заносим в память побайтно
                        }
                        break;
               case 1 : SledPole [ptr++] = *(b*)(dptr->addr) ;
                        break;

               default:;
               case 2 : bx = *(w*)(dptr->addr) ;
                        SledPole [ptr++] = (b)bx  ;  // заносим младший байт,
                          if ( ptr >= _SizeSledPole )  ptr = 0 ;
                        SledPole [ptr++] = (b)(bx>>8) ;// затем старший.
                        break;
               case 3 :                                                          // VSEV 02.07.2020 добавлена проверка на double
                         for(bx = 0; bx < sizeof(double); ++bx)
                        {
                            if ( ptr >= _SizeSledPole )  ptr = 0 ;
                            SledPole [ptr++] = *((b*)(dptr->addr)+bx) ;  //плавающую точку заносим в память побайтно
                        }
                        break;       
               case 4 : lax = *(lw*)(dptr->addr) ;
                        SledPole [ptr++] = (b)lax  ;  // заносим младший байт,
                          if ( ptr >= _SizeSledPole )  ptr = 0 ;
                        SledPole [ptr++] = (b)(lax>>8) ;// затем старший.                      
                          if ( ptr >= _SizeSledPole )  ptr = 0 ;
#if defined (_24_BITS_) ||  defined (_32_BITS_)  
                        SledPole [ptr++] = (b)(lax>>16) ;// затем старший.
                          if ( ptr >= _SizeSledPole )  ptr = 0 ;
                        SledPole [ptr++] = (b)(lax>>24) ;// затем старший.
                        if ( ptr >= _SizeSledPole )  ptr = 0 ;
#endif                        
                        break;
             }
             ax++;
           }
        while ( ax < sled.n_kanal ) ;
            //  наращиваем заполненный размер следа.
        if ( sl_d.index_stop < _SizeSledPole )
        {
          ax = ptr - sl_d.index ;
          if( (slw)ax < 0 ) ax += _SizeSledPole ;
          //------
          sl_d.index_stop += ax ;
          if( sl_d.index_stop > _SizeSledPole ) sl_d.index_stop = _SizeSledPole ;
        }

        sl_d.index = ptr ;
      }
    return ;
  }

/*----------------------------------------------------------*/
//    Поскольку приходится выводить длинные строки, то чтобы программа
//  могла работать в циклах используется метод "по частям"(через switch) +
//  + разбиение строк по-полам.

#ifndef    _Sled_data_txt
  #define  _Sled_data_txt  "Дата:\r\n"
#endif
/*
void SledPrint ( void )
{
    enum { k0, k1, k3, k5, k7, k8, k9, k10, k11 };

    register  word    ax , bx , cx , ex ;
    byte  sig_old;
    byte *ptr;
    register  lword  lax ;
    float dax;
    const struct Sled_var register *dptr ;

        // Вычисление количества страниц умещающихся в следе 
    static word mNumPageSled  ;
    static word PageCount ;    // Указатель номера текущей страницы 
    static word  StrInPage ;    // Указатель номера текущей строки в странице 
        // размер страницы следа 
    static word page_size  ;


              //  Контроль пароля: Полный запрет входа.

      if ( Password_control ( 2 ) == 0 )  return   ;
              //---


    if ( M_FirstCall == 1 )  //  Идентификация первого входа для задания  
      {                      // начального условия ...                    
        M_FirstCall = 0 ;
        Label = k10 , m_time = Timer1_Ovr ;
            // Останавливаем След.
          bo_SledStart = 0 ;
        output_s ( _Sled_prompt ) ;
      }
       //  пока находимся в распечатке следа, острочиваем автозапуск следа.
    sl_d.time_out = Timer1_Ovr ;

         //  Ожидание окончания вывода имеющихся в буфере 'TXD' символов.
    if ( !TestCompleted_Output() )  return ;

    switch (Label)
      {
        default :
        case k10 :  // Распечатка времени остановки следа. 
                    //  выдержка времени на фиксацию времени остановки следа. 
              if ( bo_SledActiv == 0 || (u)((w)(Timer1_Ovr - m_time)) > _Sec(1.5))
              {
                output_s ( "\r\n"_Sled_data_txt) ;
                PrintTime ( &msg_av.time ) ;
                output_s ( _Sled_txt1 ) ;//output_s ( _Sled_txt0 ) ;
                Label = k3 ;
              }
            break;

        case k3 :// Задаем количество строк в странице при распечатке следа 
          if (  TestCompleted_Output() )
            {
              output_c ( '\r' ) ;
              output_s( AWelcome ) ;
              output_s( " N = " ) ;

              ax = (w) sled.page_size ;
              output_c ( ax / 10  + 0x30 ) ;
              output_c ( ax % 10  + 0x30 ) ;
              Label = k5 ;
              break ;
            }
      case k5 :
              if (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                    {
                 end: Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                      return ;   // добавить еще какую-то иниц.
                    }
                  else if ( m_ch == Up ) // Перейти к другому пункту меню.
                    {
                      if ( sled.page_size < 20  )
                      {
                        sled.page_size++ ;
                        Label = k3 ;
                    } }
                  else if ( m_ch == Down ) // Перейти к другому пункту меню.
                    {
                      if ( sled.page_size != 1 )
                      {
                        sled.page_size-- ;
                        Label = k3 ;
                    } }
                  else if ( m_ch == Enter ) // перейти в режим изменения уставки
                    {
                      if ( sled.n_kanal > _SledTabSizeMax  )
                      {
                        sled.n_kanal = _SledTabSizeMax ;
                      }
                       //  Вычисление размера страницы следа.
                      for ( ax = 0, bx = 0 ; ax < sled.n_kanal ; ax++ )
                      {
                        if ((FullSledTab[sl_d.tab[ax]]).code._.type != 0 && (FullSledTab[sl_d.tab[ax]]).code._.type != 3)  //  if ((FullSledTab[sl_d.tab[ax]]).code._.type != 0) // VSEV 03.07.2020 добавлена проверка на double
                        {
                           bx += (w)(FullSledTab[sl_d.tab[ax]]).code._.type ;
                        }
                        else if ((FullSledTab[sl_d.tab[ax]]).code._.type == 0)    
                        {                                                         
                            bx += sizeof(float);                                  
                        }                                                           
                        else if ((FullSledTab[sl_d.tab[ax]]).code._.type == 3)                                              
                        {
                            bx += sizeof(double);
                        }
                        /*
                        if ((FullSledTab[sl_d.tab[ax]]).code._.type != 0 )  //
                        {
                           bx += (w)(FullSledTab[sl_d.tab[ax]]).code._.type ;
                        }
                        else                                   
                        {                                                         
                            bx += sizeof(float);                                 
                        } 
                        */

                     /* }
                      page_size = (w)sled.page_size * bx ;
                         //  Вычисление максимального кол-ва страниц в
                        // распечатываемом следе.
                      mNumPageSled = (w)sl_d.print_size / (w)page_size ;
                      PageCount = mNumPageSled ;

                      Label = k0 ;
                      return ;
                    }
                  else  Klav_Buff = m_ch;
                }
              if (AWelcome != AWell_old )
              {
                AWell_old = AWelcome;
                Label = k3;
              }

              break ;
            //-------------------
            break;

        case k0 :  // Распечатка текстовых наименований переменных следа 
              m_ext = 0 ;
              Label = k1 ;
              output_s ("\r\n") ;
        case k1 :
                  // по 4 переменным в строке
              if ( m_ext%4 == 0 )  output_s ("\r\n") ;
                ax = (m_ext+1)/10 ;
                if ( ax == 0 ) output_c ( ' ') ;
                else           output_c ( ax+0x30 ) ;
                output_c ( (m_ext+1)%10+0x30 ) ;
                output_c ( '.') ;
              output_s ( sled.tab[m_ext].txt ) ;
              m_ext++ ;
              if ( m_ext >= sled.n_kanal )
              {
                //output_s ( _Sled_txt1 ) ;
                Label = k11 ;
              }
            break;

        case k11 :
           //   Начальные условия для распечатки
          StrInPage = 0 ;        // страницы из следа.
             // Отступление на i-тую страницу вверх от конца следа 
          ax = (w)(mNumPageSled - PageCount + 1) * page_size ;
          m_index = sl_d.index - ax ;
          if ( sl_d.index < ax ) m_index += _SizeSledPole ;

               //     Заголовок начала страницы   
          output_s ( _Page_txt ) ;
               // Вывод номера страницы в десятичной форме 
          ax = (w) PageCount ;
          ex = ax / 1000  ;
          ax %= 1000 ;
          if ( ex != 0 ) output_c ( ex + 0x30 ) ;
          ex = ax / 100  ;
          ax %= 100 ;
          if ( ex != 0 ) output_c ( ex + 0x30 ) ;
          ex = ax / 10  ;
          if ( ex != 0 ) output_c ( ex + 0x30 ) ;
          output_c ( ax % 10  + 0x30 ) ;
          Label = k7 ;
          break ;

        case k7 :  // Распечатка построчно страницы из следа 
          if ( StrInPage++ < sled.page_size )
            {
              output_s ("\r\n ") ;
              m_ext = 0,  Label = k8 ;  // для вывода по частям.

        case k8 :// Для распечатки по частям выходим после вывода i-той переменной.
              if ( m_ext < sled.n_kanal )
              {
                  // однократно вычисляем адрес в таблице.
                dptr = &( FullSledTab[sl_d.tab[m_ext]]) ;
                       // Считывание байта из следа 
                switch ( dptr->code._.type )
                {
                  case 0:
                           ptr = (b*)&dax;
                           *ptr = SledPole[m_index] ;

                           for ( bx = 1; bx < sizeof(float);++bx)
                           {
                                ++ptr;
                                if ( (u)m_index == (u)(_SizeSledPole - 1))
                                                        m_index = 0 ;
                                else                    m_index++ ;
                                *ptr = SledPole[m_index] ;
                           }
                           break;

                  default:;
                      //  Считываем знак.
                  case 1 : if ( dptr->code._.off_sign == 0 )
                                      ax = (sw)(sb)SledPole[m_index] ;
                           else       ax = ( w)( b)SledPole[m_index] ;
                           break;

                  case 2 : ax = (w)(b)SledPole[m_index] ; // считываем, как беззнаковое.
                               // прогонка адреса.
                           if ( (u)m_index == (u)(_SizeSledPole - 1))
                                                   m_index = 0 ;
                           else                    m_index++ ;
                           ax += (w)(b)SledPole[m_index] * (w)256u ;// склеиваем.
                           break;
                  case 3 :                                                  //VSEV 03.07.2020
                            ptr = (b*)&dax;
                           *ptr = SledPole[m_index] ;

                           for ( bx = 1; bx < sizeof(double);++bx)
                           {
                                ++ptr;
                                if ( (u)m_index == (u)(_SizeSledPole - 1))
                                                        m_index = 0 ;
                                else                    m_index++ ;
                                *ptr = SledPole[m_index] ;
                           }
                           break;
                }
                    // прогонка адреса.
                if ( (u)m_index == (u)(_SizeSledPole - 1)) m_index = 0 ;
                else                                       m_index++ ;

                  //  Распечатка: либо в десятичном виде с точкой
                  // либо в 16-ричном.
                switch ( dptr->code._.print_type )
                {
                  default:;
                  case 1 :
                    bx = (w)dptr->code._.type * 2 - 1 ;
                    for ( ; (sw) bx >= 0 ; bx -- )
                      {
                        ex = (b)( ax >> 4u*bx ) & 0x0fu ;
                        ex +=  ( ex <= 0x9 )  ?  0x30u  :  0x37u ;
                        output_c ( ex ) ;
                      }
                    break;
                //--------------------
                  case 2 :
                     cx = *(w*)dptr->abs_nom;
                     bx = dptr->nom ;
                     if (dptr->code._.type == 0)
                     {
                        if ( dptr->code._.off_sign == 0 )
                        {    // Если распечатка со знаком - выделяем знак и модуль.
                            if ( dax >= 0 )    sig_old = '+' ;
                            else   dax *= -1 , sig_old = '-' ;
                        }
                        // приводим содержимое ячейки к его номиналам.
                        dax *= (float)cx;
                        dax /= (float)bx;
                        lax = (lw)dax;
                        dax = dax - lax;//выделение дробной части
                     }
                     else if (dptr->code._.type == 3)
                     {
                        if ( dptr->code._.off_sign == 0 )
                        {    // Если распечатка со знаком - выделяем знак и модуль.
                            if ( dax >= 0 )    sig_old = '+' ;
                            else   dax *= -1 , sig_old = '-' ;
                        }
                        // приводим содержимое ячейки к его номиналам.
                        dax *= (double)cx;
                        dax /= (double)bx;
                        lax = (lw)dax;
                        dax = dax - lax;//выделение дробной части
                     }
                     else
                     {
                        if ( dptr->code._.off_sign == 0 )
                        {    // Если распечатка со знаком - выделяем знак и модуль.
                            if ( (sw)ax >= 0 )    sig_old = '+' ;
                            else   ax = ~ax + 1 , sig_old = '-' ;
                        }
                        // приводим содержимое ячейки к его номиналам.
                        lax =  (lw)ax*(lw)cx;
                        m_time = lax%bx;
                        lax /=bx;
                     }
                     if(lax > 0xffffu) lax = 0xffff;

                               // распечатка целой части - максимум 5 символов.
                     ex = 5 - dptr->code._.celoe ; //сколько первых символов пропустить
                     if ( ex == 5 ) ex = 2 ; // для совместимости - если заданы были нули то принимаем формат "3.2".
                     else if ( (sw)ex < 0 ) ex = 0 ;
                     for ( ax = 10000, cx = 0 ; ax != 1 ; ax /= 10 )
                     {
                       bx = lax / ax ;
                       lax %= ax;
                           // пока идут первые нули - не выводим их:
                       if ( bx == 0 && cx == 0 )
                       {     // а пропускаем лишние нулевые символы,
                         if ( ex != 0 ) ex-- ;
                            // или заменяем пробелами.
                         else  output_c (' ') ;
                       }
                       else
                       {
                         if(cx == 0)
                         {
                           if ( (dptr->code._.off_sign == 0) ) output_c ( sig_old ) ;
                           cx = 1 ;
                         }
                          // первые нули закончились.
                         output_c ( (b)bx + 0x30 ) ;
                       }
                     }   // распечатываем последнюю цифру.
                     if(cx == 0)
                     {
                       if ( dptr->code._.off_sign == 0 ) output_c ( sig_old ) ;
                     }
                     output_c ( (b)(w)lax + 0x30 ) ;
                       // распечатка дробной части
                     if ( dptr->code._.celoe == 0 ) ex = 2 ;// по умолчанию.
                     else ex = dptr->code._.drob ;
                     if ( ex != 0 )
                     {
                       output_c ( '.' ) ;
                       if ( dptr->code._.type == 0 )
                       {
                            for ( ; ex != 0 ; ex-- )
                            {
                                dax *=10;
                                ax = (w)m_dax ;
                                output_c ( (b)ax + 0x30 ) ;
                            }

                       }
                       else
                       {
                            bx = dptr->nom ;
                            lax = m_time ; // восстанавливаем остаток.
                            for ( ; ex != 0 ; ex-- )
                            {
                                lax*=10  ;
                                ax = lax/bx ;
                                lax %= bx;
                                output_c ( (b)ax + 0x30 ) ;
                            }

                       }
                     }
                    break;
                  }
                output_s ( dptr->txt2 ) ;
                m_ext++ ;
              }
              else Label = k7 ;
            }
          else
            {     // В начале последней строки индицируем состояние следа.
              if ( bo_SledActiv == 0 ) output_s ("\r.\r") ;
              else                     output_s ("\r!\r") ;
              Label = k9 ;
            }
          break ;

        case k9 :    //  отсюда переключится на "Label = 0" только
                   // по клавише "Up" или "Down", или выйдем по "Esc"
                 // Обработка символов из буфера ввода до опустошения. 
            if (  TestData_for_Input() )
            {
              mInput_c ( m_ch ) ;

              if ( m_ch == Return )  // Выход из этого режима 
                {
                  goto end ;
                }
                  // Перейти к выводу следующей страницы 
              else if ( m_ch == Up)
                {
                  if ( PageCount != mNumPageSled )
                    {
                      PageCount++ ;
                      Label = k0 ;
                }  }
                  // Перейти к выводу предыдущей страницы 
              else if ( m_ch == Down )
                {
                  if ( PageCount != 1 )
                    {
                      PageCount-- ;
                      Label = k0 ;
                }   }  //  Запуск/остановка следа.
              else if ( m_ch == Enter )
                {
                  if ( bo_SledStart == 0 )
                  {
                    bo_SledStart = 1 ;
                     // В начале последней строки индицируем состояние следа.
                    output_s ("\r!\r") ;
                  }
                  else
                  {
                    bo_SledStart = 0 ;
                    Label = k10 ; // возвращаемся к перерасчету кол-ва страниц.
                    //output_s ("\r.\r") ;
                  }
                }
              else  Klav_Buff = m_ch;
            }
          break ;
      }

  return ;
}
*/
/*----------------------------------------------------------*/
//
//     Задание списка переменных заносимых в след выбором их
//  из полного списка.
//  Настройка следа аналогично журналу.
// m_index - пункт "Меню1"
// m_time  - порядковый номер переменной
// m_ext   - пункт "Меню2"
// m_addr  - номер новой переменной


void SetSledTab ( void )
{

    register  byte  ah ;
    register  word  ax ;
    register lword lax , lbx ;


              //  Контроль пароля: Полный запрет входа.

      if ( Password_control ( 2 ) == 0 )  return   ;
              //---


    if ( M_FirstCall == 1 )  /*  Идентификация первого входа для задания  */
      {                      /* начального условия ...                    */
        M_FirstCall = 0 ;
        Label = 0 ;
        //output_s ( _SetSled_prompt ) ;
		m_index = 0;
    	m_ext = 0;
    	m_addr = 0;

      }

        //--------------------

  switch ( Label )
  {
      default:
      case 0:
          output_s ( _SetSled_prompt ) ; // "\n\rНастр. регистр: \n" на верхней строке
          Label = 1;
          //--------------------
	  case 1:
          if ( TestCompleted_Output() )
          {
            output_c ( '\r' );
            output_s ( AWelcome );
            output_s ( Menu1S[ m_index ].txt ); //Кратность, автостарт, переменных, список
            Label = 2;
          }
          break ;
      //Работаем с "Меню1": кратность, автостарт, число переменных, список переменных
	  case 2:
          if ( TestData_for_Input() )
          {
            mInput_c ( m_ch );
            if ( m_ch == Return )  // Выход из этого режима
            {
              Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1;
              return;   // добавить еще какую-то иниц.
            }
            else if ( m_ch == Down ) //увеличить пункт "Меню1"
            {
              m_index++;
              if ( m_index >= Menu1S_size ) m_index = 0;
              Label = 1;
            }
            else if ( m_ch == Up )  //уменьшить пункт "Меню1"
            {
              m_index--;
              if ( (sw)m_index < 0 ) m_index = Menu1S_size - 1;
              Label = 1;
            }
            else if ( m_ch == Enter ) Label = 3;
            else Klav_Buff = m_ch;
          }
          if ( AWelcome != AWell_old )
          {
            AWell_old = AWelcome;
            Label = 1;
          }
          break;
	  case 3:
          if ( TestCompleted_Output() )
          {
            output_s ( "\n\r" ); //выводим на верхнюю строку пункт "Меню1"
            output_s ( Menu1S[ m_index ].txt );
            output_c ( '\n' );
            Label = Menu1S[ m_index ].label;
          }
          break;

    //-------------------------------------------------------------------------------
	  case 10: //"Кратность"
		  m_time = sled.kratn ; // сохраняем прежнюю кратность .
          Label = 11;

      case 11: //Вывод кратности следа .
          if (  TestCompleted_Output() )
            {
              output_c ( '\r' ) ;
              output_s( AWelcome ) ;
             //----
              lax = (lw)(sled.kratn) * (lw)(sled.dt_scan) ;
              ax  = lax / 1000 ;
              lbx = lax % 1000 ; // остаток от деления кратности на делитель
             //----
              m_ch = ax/100 + 0x30 ;
              ax %= 100 ;
               // Вывод первой цифры - сотен .
              if ( m_ch != 0x30 ) output_c ( m_ch ) , ah = 1 ; // признак 100 .
              else ah = 0 ; // признак того , что сотни нет .
             //----
              m_ch = ax/10 + 0x30 ;
              ax %= 10 ;
               // вывод второй цифры - десятков (также если есть 1 в старшем разряде) .
              if ( m_ch != 0x30 || ah == 1 ) output_c ( m_ch ) ;
             //----
              m_ch = ax + 0x30 ;
              output_c ( m_ch ) ;  // вывод третьей цифры - единиц .
              output_c ( '.' ) ;
             //----
                   m_ch = lbx/100 ;         // *10/1000
                   output_c ( m_ch + 0x30 ) ; // вывод дробной части .
             //----
                   m_ch = (lbx % 100)/10 ;  // *100/1000
                   output_c ( m_ch + 0x30 ) ; // вывод дробной части .
             //----
              output_s ( "мск " ) ;
             //----
              Label = 12 ;
              break ;
            }
            //-------------------
      case 12: //    Режим изменения кратности следа .
          if ( TestData_for_Input() )
           {
             mInput_c ( m_ch ) ;
             if ( m_ch == Return )  /* Выход из этого режима */
              {
                sled.kratn = m_time ; // Восстанавливаем прежнюю кратность
                //Label = k4 ; // Переход к выбору количества переменных
                //Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                //return ;   // добавить еще какую-то иниц.
				Label = 0;
              }

             else if ( m_ch == Up )   // Увеличить кратность :
               {
                 if ( sled.kratn < 31 )
                  {
                     sled.kratn ++ ; // увеличиваем кратность на 1 .
                     Label = 11 ; // возврат на вывод кратности .
                  }
               }
             else if ( m_ch == Down ) // Уменьшить кратность :
               {
                 if ( sled.kratn > 0 )
                  {
                     sled.kratn -- ; // уменьшаем кратность на 1 .
                     Label = 11 ; // возврат на вывод кратности
                  }
               }
             else if ( m_ch == Enter ) Label = 0 ; // Кратность принята .
             else
               {
                 Klav_Buff = m_ch;
               }
           }
          if (AWelcome != AWell_old )
           {
             AWell_old = AWelcome;
             Label = 11 ;
           }
          break ;
       	    //------------------------------------------
	  //---------------Автостарт---------------
      case 20:  //    Выбор времени автостарта .
          //output_s ( _SetSled_txt7 ) ;
          m_time = sled.t_start;   // сохраняем прежнюю кратность .
          Label = 21 ;
        //--------------------
      case 21: //    Вывод кратности следа .
          if (  TestCompleted_Output() )
            {
              output_c ( '\r' ) ;
              output_s( AWelcome ) ;
             //----
              ax = sled.t_start + _Sec(3) ; //3 сек - 0,05 мин, для округления
              m_ch  = ax / _Sec(600);
              ax = ax % _Sec(600) ; // остаток от деления кратности на делитель
             //----

              if ( m_ch != 0)
              {
                m_ch += 0x30;
              }
              else m_ch = ' ';

              output_c ( m_ch ) ;

              m_ch = ax/_Sec(60);
              ax %= _Sec(60) ;

              output_c ( m_ch+0x30 ) ;
              output_c ( '.' ) ;

             //----
                    ax *= 10 ;
                   m_ch = ax / _Sec(60);
                   output_c ( m_ch + 0x30 ) ; // вывод дробной части .
             //----
              output_s ( " мин " ) ;
             //----
              Label = 22 ;
              break ;
            }
            //-------------------

      case 22: //    Режим изменения кратности следа .
          if ( TestData_for_Input() )
           {
             mInput_c ( m_ch ) ;
             if ( m_ch == Return )  // Выход из этого режима
              {
                 sled.t_start = m_time ;
                 Label = 0 ;
              }

             else if ( m_ch == Up )   // Увеличить кратность :
               {
                 ax =  sled.t_start + _Sec(30) ; // увеличиваем кратность на 1 .
                 if ( ax < _Sec(3600) )
                 {
                    sled.t_start = ax;
                 }
                 else sled.t_start = _Sec(3600);
                 Label = 21 ; // возврат на вывод кратности .
               }
             else if ( m_ch == Down ) // Уменьшить кратность :
               {
                 if (sled.t_start < _Sec(30) ) sled.t_start = 0;
                 else sled.t_start -= _Sec(30) ; // увеличиваем кратность на 1 .
                 Label = 21 ; // возврат на вывод кратности
               }
             else if ( m_ch == Enter ) Label = 0 ; // Кратность принята .
             else
               {
                 Klav_Buff = m_ch;
               }
           }
          if (AWelcome != AWell_old )
           {
             AWell_old = AWelcome;
             Label = 21 ;
           }
              break ;
            //-------------------
	  //------     Выбор количества переменных.  -----------------//
      case 30:  //    Выбор количества переменных.
                //output_s ( _SetSled_txt0 ) ;
                m_addr = sled.n_kanal ; // сохраняем прежнее кол-во каналов .
                Label = 31 ;
      case 31:
          if (  TestCompleted_Output() )
            {
              output_c ( '\r' ) ;
              output_s( AWelcome ) ;
              output_s( " N = " ) ;

              ax = (w) sled.n_kanal ;
              output_c ( ax / 10  + 0x30 ) ;
              output_c ( ax % 10  + 0x30 ) ;
              Label = 32 ;
              break ;
            }
      case 32 :
              if (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                    {
                      sled.n_kanal = m_addr ; // восстанавливаем кол-во .
                      Label = 0 ;
                      return ;
                    }
                  else if ( m_ch == Up ) /* Перейти к другому пункту меню.*/
                    {
                      if ( sled.n_kanal < _SledTabSizeMax  )
                      {
                        sled.n_kanal++ ;
                        Prg._.Sled = 1 ;//данные следа теперь перемешались - запускаем его.
                        Label = 31 ;
                    } }
                  else if ( m_ch == Down ) /* Перейти к другому пункту меню.*/
                    {
                      if ( sled.n_kanal != 1 )
                      {
                        sled.n_kanal-- ;
                        Prg._.Sled = 1 ;//данные следа теперь перемешались - запускаем его.
                        Label = 31 ;
                    } }
                  else if ( m_ch == Enter ) // перейти в режим изменения уставки
                    {
                      Label = 0 ;
                      //m_index = 0 ;
                      //return ;
                    }
                  else  Klav_Buff = m_ch;
                }
              if (AWelcome != AWell_old )
              {
                AWell_old = AWelcome;
                Label = 31;
              }

              break ;
            //-------------------

	    //-------------------------------------------------------------------------------
      case 39:
         if ( TestCompleted_Output() )
         {
            output_s ( "\n\r" ); //выводим на верхнюю строку пункт "Меню1"
            output_s ( Menu1S[ m_index ].txt );
            output_c ( '\n' );
            Label = 41;
         }
         break;

	  //----------------     Список   ---------------------------------------
      case 40:  //  Просмотр уже заданных переменных.
		 if( sled.n_kanal == 0 )
          {
            m_index = 1;
            output_s ( "\r" ); //выводим на верхнюю строку пункт "Меню1"
            output_s ( Menu1S[ m_index ].txt );
            output_c ( '\n' );
            Label = Menu1S[ m_index ].label;
            break;
          }
          m_time = 0;
          Label = 41 ;
      case 41 :
          if (  TestCompleted_Output() )
            {
              output_c ( '\r' ) ;
              output_s( AWelcome ) ;
              output_s( "n" ) ;
                 // распечатка номера переменной.
              //ax = m_index + 1 ;
			  ax = m_time + 1;
			  output_c ( ax / 10  + 0x30 ) ;
              output_c ( ax % 10  + 0x30 ) ;
              output_c ( '-' ) ;

              // распечатка наименования переменной.
              output_s( sled.tab[m_time].txt ) ;
			  //output_s( sled.tab[m_index].txt ) ;
              Label = 42  ;
              break ;
            }
      case 42  :
              if (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                    {
                      Label = 0  ;
                      //return ;   // добавить еще какую-то иниц.
                    }
                  else if ( m_ch == Down ) /* Перейти к другому пункту меню.*/
                    {
                      if ( /*m_index*/m_time < (sled.n_kanal-1) )
                      {
                        /*m_index*/m_time++ ;
                        Label = 41  ;
                      }
                      else if ( /*m_index*/m_time < sled.n_kanal ) Label = 43 ;
                    }
                  else if ( m_ch == Up ) /* Перейти к другому пункту меню.*/
                    {
                      if ( /*m_index*/m_time != 0 )
                      {
                        /*m_index*/m_time-- ;
                        Label = 41 ;
                    } }
                  else if ( m_ch == Enter ) // перейти в режим изменения уставки
                    {
                      Label = 50 ;
                      m_ext = 0 ;
                      return ;
                    }
                  else  Klav_Buff = m_ch;
                }
              if (AWelcome != AWell_old )
              {
                AWell_old = AWelcome;
                Label = 40 ;
              }
              break ;
            //-------------------

      case 43 :
          output_c ( '\r' ) ;
          output_s( AWelcome ) ;
          output_s ( _SetSled_txt6 ) ;
          Label = 44 ;

      case 44 :
          if ( TestData_for_Input() )
           {
             mInput_c ( m_ch ) ;
             if ( m_ch == Enter )  /* Выход из этого режима */
              {
				Label = 0 ;
                //Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                return ;   // добавить еще какую-то иниц.
              }
             else if ( m_ch == Return ) Label = 39 ;
             else if ( m_ch == Up ) /* Перейти к другому пункту меню.*/
              {
                Label = 41 ;
              }
             else
              {
                Klav_Buff = m_ch;
              }
           }
          if (AWelcome != AWell_old )
           {
             AWell_old = AWelcome;
             Label = 10 ;//or 0
           }
              break ;
            //-------------------

      case 50 :  //  Выбор новой переменной в список заданных переменных.
              output_s ( _SetSled_txt2 ) ;
              Label = 51 ;
      case 51 :  //  Выбор новой переменной в список заданных переменных.
          if (  TestCompleted_Output() )
            {
              output_c ( '\r' ) ;
              output_s( AWelcome ) ;
              output_s( "#" ) ;
                 // распечатка номера переменной.
              ax = m_ext + 1 ;
              output_c ( ax / 100 + 0x30 ) ;
              ax %= 100 ;
              output_c ( ax / 10  + 0x30 ) ;
              output_c ( ax % 10  + 0x30 ) ;
              output_c ( '-' ) ;

                 // распечатка наименования переменной.
              output_s( FullSledTab[m_ext].txt ) ;
              Label = 60  ;
              break ;
            }
      case 60  :
              if (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                    {
                      Label = 39  ;
                      //return ;   // добавить еще какую-то иниц.
                    }
                  else if ( m_ch == Down ) /* Перейти к другому пункту меню.*/
                    {
                      if ( m_ext < (FullSledTab_size-1) )
                      {
                        m_ext++ ;
                        Label = 51  ;
                    } }
                  else if ( m_ch == Up ) /* Перейти к другому пункту меню.*/
                    {
                      if ( m_ext != 0 )
                      {
                        m_ext-- ;
                        Label = 51  ;
                    } }
                  else if ( m_ch == Enter )
                    {
                        // Перезаписываем имя выбранной переменной в рабочую табл.
                      ax = 0 ;
                      while( (m_ch = FullSledTab[m_ext].txt[ax]) != 0 )
                      {
                        sled.tab[m_time/*m_index*/].txt[ax++] = m_ch ;
                      }
                      sled.tab[/*m_index*/m_time].txt[ax] = 0 ;
                      sl_d.tab[m_time/*m_index*/] = m_ext ;
                      Prg._.Sled = 1 ;//данные следа теперь перемешались - запускаем его.

                       //  Обычная переменная или задаваемая прямым адресом?
                   /* if( sled.tab[m_index].txt[0] == '@' )
                      {   // Переходим к заданию адреса.
                        m_time = 4 ;  // буфер для накопления адреса.
                        for ( ax = 0 ; ax <= 4 ; ax++ ) m_buff[ax] = 0 ;
                        Label = k60 ;
                      }
                      else  */
                         Label = 39 ;
                      //return ;
                    }
                  else  Klav_Buff = m_ch;
                }
              if (AWelcome != AWell_old )
              {
                AWell_old = AWelcome;
                Label = 50 ;
              }
              break ;
      //-------------------
  /*
      case k60:  //  Задание адреса переменной.
              output_s ( _SetSled_txt3 ) ;
              Label = k65;
      case k65:
          if (  TestCompleted_Output() )
            {
              output_c ( '\r' ) ;
              output_s( AWelcome ) ;
              output_s( " :" ) ;
                 // распечатка адреса переменной.
              for ( ax = 5 ; ax != 0 ; ax-- )
              {
                m_ch = m_buff[ax-1] ;
                if( m_ch <= 0x9 ) output_c ( m_ch + '0' ) ; // 0...9
                else         output_c ( m_ch + 'A' - 10 ) ; // A...F
                     // имя переменной оформляем номером адреса.
                sled.tab[m_index].txt[6-ax] = m_ch ;
              }
              output_c ( 'H' ) ;
              sled.tab[m_index].txt[6] = 'H' ;

                     // Устанавливаем курсор на нужную позицию.
              for ( ax = 0 ; ax <= m_time+1 ; ax++ )  output_c ( '\b' ) ;

              Label = k70 ;
              break ;
            }
      case k70 :
              if (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                    ax = m_buff[m_time] ;
                  if ( m_ch == Return )
                    {
                      Label = k40 ;
                      return ;   // добавить еще какую-то иниц.
                    }
                  else if ( m_ch == Up ) // Перейти к другому пункту меню.
                    {
                      if ( ax < 0xF )
                      {
                        ax++ ;
                        m_buff[m_time] = ax ;
                        Label = k65 ;
                      }
                    }
                  else if ( m_ch == Down ) // Перейти к другому пункту меню.
                    {
                      if ( ax != 0 )
                      {
                        ax-- ;
                        m_buff[m_time] = ax ;
                        Label = k65 ;
                      }
                    }
                  else if ( m_ch == Enter )
                    {   //  Перезаписываем выбранную переменную в рабочую табл.
                      if( m_time != 0 ) // заданы ли все цифры адреса?
                      {
                        m_time-- ;  // еще нет.
                        Label = k65 ;
                      }
                      else
                      {   // склеиваем адрес.
                        lax = 0 ;
                        for ( ax = 4 ; (sw)ax >= 0 ; ax-- )
                        {
                          lax <<= 4 ;
                          lax += m_buff[ax] ;
                        }
#ifdef   _24_BITS_
                        sled.xtab.addr = (void*)lax ;
#else
                        sled.xtab.addr = (void*)(w)lax ;
#endif
                          // переходим к выбору типа переменной.
                        m_time = 0 ;
                        Label = k80 ;
                      }
                      return ;
                    }
                  else  Klav_Buff = m_ch;
                }
              if (AWelcome != AWell_old )
              {
                AWell_old = AWelcome;
                Label = k60;
              }
              break ;
      //-------------------

      case k80:  //  Задание типа переменной.
              output_s ( _SetSled_txt4 ) ;
              Label = k85;
      case k85:
          if (  TestCompleted_Output() )
            {
              output_c ( '\r' ) ;
              output_s( AWelcome ) ;
              output_s( sled_types[m_time].txt ) ;

              Label = k90 ;
              break ;
            }
      case k90 :
              if (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                    ax = m_buff[m_time] ;
                  if ( m_ch == Return )
                    {
                      Label = k60 ;
                      return ;   // добавить еще какую-то иниц.
                    }
                  else if ( m_ch == Up ) // Перейти к другому пункту меню.
                    {
                      if ( m_time < (u)(sled_types_size-1) )
                      {
                        m_time++ ;
                        Label = k85 ;
                    } }
                  else if ( m_ch == Down ) // Перейти к другому пункту меню.
                    {
                      if ( m_time != 0 )
                      {
                        m_time-- ;
                        Label = k85 ;
                    } }
                  else if ( m_ch == Enter )
                    {   //  Выбор закончен.
                      sled.xtab.code.all = sled_types[m_time].code ;
                      sled.xtab.txt2[0]  = sled_types[m_time].txt2 ;
                      Label = k20 ;   // возвращаемся на самый верх.
                      return ;
                    }
                  else  Klav_Buff = m_ch;
                }
              if (AWelcome != AWell_old )
              {
                AWell_old = AWelcome;
                Label = k80;
              }
              break ;   */
    }
  return ;
}

//---------------------------------------------------

  //   Находим соответствие всем именам из рабочей таблицы имен
  // в const-таблице и списываем ее свежие параметры (адрес),
  // поскольку при перезашивке адрес переменной мог измениться
  // по-сравнению с устаревшим адресом данной переменной хранящимся в i2c.

word  TestSledTab ( void )
{
   enum { k0, k10 };

  static byte index1 ; //  индекс поиска внутри рабочей таблицы.
  static byte index2 ; //  индекс поиска внутри const-таблицы.
  char *ptr1 ;
  const char *ptr2 ;
  byte   ah, bh ;

  switch ( sl_d.label )
  {
    default:;     // начало поиска.
    case k0 : index1 = 0, index2 = 0 ;
              sl_d.label = k10 ;
       break;
        //-----------------
    case k10:      // перебираем порциями не более 3-х переменных.
              for ( ah = 3 ; ah != 0 ; ah-- )
              {     //  Если задан прямой адрес, то пропускаем.
                if ( sled.tab[index1].txt[0] == '@' ) goto next ;

                ptr1 = &sled.tab[index1].txt[0] ;
                ptr2 = &FullSledTab[index2].txt[0] ;
                     //  сравниваем имена.
                for ( bh = 0 ; ; bh++ )
                {
                      // имя не равно.
                  if ( ptr1[bh] != ptr2[bh] )  break ;

                      // имя закончилось?... значит имя найдено.
                  if ( ptr1[bh] == 0 || ptr1[bh] == ' ' )  // NULL Vit-07.12.07 14:13
                  {      // задаем соответствующий имени указатель на
                        //     переменную в базовой таблице.
                    sl_d.tab[index1] = index2 ;

               next:  // начинаем поиск следующей переменной.
                    if ( ++index1 >= _SledTabSizeMax )
                    {     // вся таблица проверена.
                      sl_d.label = k0 ; // взводим метку на начало.
                      return 0 ;
                    }
                    index2 = -1 ; // сбрасываем указатель.
                    break ;
                  }
                }
                    // переходим к следующей переменной в константной таблице.
                if ( ++index2 >= FullSledTab_size ) // переменные в списке закончились.
                {    // имя не найдено:
                  ptr1[0] = '?' ; // помечаем его '?' и пропускаем.
                  sl_d.tab[index1] = 0; //Сбрасываем в 0 номер элемента чтобы была определенность, а не мусор в адресе
                  goto next ;
                }
              }
       break;
        //-----------------
  }

  return 4 ;  // проверка продолжается.
}
