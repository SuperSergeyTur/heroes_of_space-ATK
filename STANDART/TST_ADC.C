

//         ПРОГРАММА ТЕСТИРОВАНИЯ КАНАЛОВ АЦП .
//------------------------------------------------------------------
/*   Режим доступен из "Готовности".
 *   Функции:
 * - выбор тестируемого канала из таблицы путем перебора ;
 * - индикация уставки смещения и измеряемого значения в выбранном канале.
 *   Клавиши:
 * - "+" в режиме выбора канала - выбор канала ;
 * - "Enter" в режиме выбора канала - переход к индикации смещения и измерений ;
 * - "Esc" в режиме выбора канала - возврат в диспетчер ;
 * - "+" в режиме индикации - увеличение модуля уставки смещения АЦП ;
 * - "-" в режиме индикации - уменьшение модуля уставки смещения АЦП ;
 * - "Esc" в режиме индикации - переход к режиму выбора канала.
 */

  // Для запрета установки нулей в объектных программах (в работе, ...), где 0 - отсутствие запрета
#ifndef ObjOffADC_Offset
  #define ObjOffADC_Offset (1)
#endif



void TstADC_Drive ( void )
{
   register word    ax ;

      if ( M_FirstCall == 1 )  /*  Идентификация первого входа для задания  */
        {                      /* начального условия ...                    */
          M_FirstCall = 0 ;

          if ( Mon.Password_Ok == 0 )  Label = 200 ;  // Вход с предупреждением о пароле.
          else                         Label = 210 ;  // Обычный вход.

          return ;
        }

  switch ( Label )
    {
      default:
      case 200:  //  Контроль пароля: ограничение.
              output_s ( _PasswordLtd_txt ) ;
              m_time = Timer1_Ovr ;
              Label = 201 ;
      case 201:
              if ( (u)(w)(Timer1_Ovr - m_time) < _Time_Password_txt )  break ;
               //---

      case 210:  //  Обычный вход.
              Label = 100 ;
              output_s ( _ADC_Tst_txt ) ;

      case 100:
              m_index = 0 ;
      case 101:
              output_c ( '\n' ) ;
              Label = 103 ;
      case 103:  // Ожидание завершения предыдущего вывода.
              if ( TestCompleted_Output() )
                {
                  output_s ( _ADC_chnl ) ;
#ifdef ADCiklTst
                if ( m_index == _Nm ) output_s ( _AutoSetADC_txt ) ;
                else
#endif
                 {
                  output_s ( Nstx[ m_index ].txt ) ;
                 }
                  Label = 105 ;
                  break ;
                }
      case 105:if ( TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                    {
                      Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                      //Mon.Otkl_InOut = 0 ;
                      return ;   // добавить еще какую-то иниц.
                    }
#ifndef ADCiklTst
                  else if ( m_ch == Down ) /* Выбрать номер канала.*/
                    {
                      if ( ++m_index >= _Nm ) m_index = 0 ;
                      Label = 103 ;
                    }    /* переход к следующей настройке */
                  else if ( m_ch == Up ) /* Выбрать номер канала.*/
                    {
                      if ( m_index-- == 0 ) m_index = _Nm - 1 ;
                      Label = 103 ;
                    }    /* переход к следующей настройке */
                  else if ( m_ch == Enter )
                    {
                      m_addr = Nstx[ m_index ].ach->offset;
                      Label = 20 ;
                    }
#else
                  else if ( m_ch == Down ) /* Выбрать номер канала.*/
                    {
                      if ( ++m_index > _Nm ) m_index = 0 ;
                      Label = 103 ;
                    }    /* переход к следующей настройке */
                  else if ( m_ch == Up ) /* Выбрать номер канала.*/
                    {
                      if ( m_index-- == 0 ) m_index = _Nm ;
                      Label = 103 ;
                    }    /* переход к следующей настройке */
                  else if ( m_ch == Enter )
                  {
                    if ( _Nm == m_index )
                     {
                       if ( Mon.Password_Ok == 0 )  Label = 200 ;
                       else                         Label = 220 ;
                     }
                    else
                     {
                        m_addr = Nstx[ m_index ].ach->offset;
                        Label = 20 ;
                     }
                  }
#endif
                  else
                    {
                      Klav_Buff = m_ch;
                    }
                }
              break ;
            //-------------------

      case 20:
              output_c ( '\n' ) ;
              Label = 23 ;
      case 23:
                 // Ожидание завершения предыдущего вывода + тактирование,
                      // чтобы не мельтешило.
              if (( TestCompleted_Output() ) && ( (u)((w)(Timer1_Ovr - m_time)) > 2 ))
                {
                  output_s ( "\rС=" ) ;
              #ifndef _BTE_NEW
                  ax = Nstx[ m_index ].ach->offset * 2 ;
              #else
                    // В BTE_NEW с 0 по 7  канал имеем смещение и знак относительно смещения + полный уровень АЦП =0...5 В. Измерять физич.
                    // единицы в вольтах есть возможность только на АЦП и уже смещенный сигнал
                    //           С 8 по 13 канал нет смещения и уровень АЦП по внутр пинанию контроллера +3,3 В
                  ax = Nstx[ m_index ].ach->offset ;
              #endif
                  m_ch = ax / _AD_VOLT + 0x30,  ax %= _AD_VOLT ;
                  output_c ( m_ch ) ;
                  output_c ( '.' ) ;

                  ax *= 10,  m_ch = ax / _AD_VOLT + 0x30,  ax %= _AD_VOLT ;
                  output_c ( m_ch ) ;
                  ax *= 10,  m_ch = ax / _AD_VOLT + 0x30,  ax %= _AD_VOLT ;
                  output_c ( m_ch ) ;
                  ax *= 10,  m_ch = ax / _AD_VOLT + 0x30 ;
                  output_c ( m_ch ) ;

                  m_ext = _AD_BUSY  ;
                  AD_Izm( *Nstx[ m_index ].ach , &m_ext ) ;
                  Label = 30 ;
                  break ;
          case 30:
                  if ( m_ext == _AD_BUSY ) break ; // ожидание готовности измерения.

                    /*   Преобразование рез.изм. в знаковое со смещением. */

                  mIzmData_Conversion( m_ext , ax , *Nstx[ m_index ].ach ) ;

                    /*  Вывод знака. */
                  if ( (sw)ax >= 0 )  output_s ( " U=+" ) ;
                  else
                    {
                      output_s ( " U=-" ) ;
                      ax = ~ax + 1 ;
                    }
                    //   Приведение полученного измерения к масштабу
                    // напряжения на входе платы ввода/вывода.
                    // 205 - значение соотв. одному вольту в дискретах АЦП.
// 28.12.2023 В "obj_def.h" задаются двуполярные каналы из таблицы Nstx: "#define _Bipolar_Chanels_ADC(chanel) if(chanel== 1)".
// Аналогично ранее заданному "_BTE_NEW". Актуально для новых плат .050, .051.
#ifndef _Bipolar_Chanels_ADC
            #ifndef _BTE_NEW
                  ax *= 2 ;
            #else
                    // В BTE_NEW с 0 по 7  канал имеем смещение и знак относительно смещения + полный уровень АЦП =0...5 В. Измерять физич.
                    // единицы в вольтах есть возможность только на АЦП и уже смещенный сигнал
                    //           С 8 по 13 канал нет смещения и уровень АЦП по внутр пинанию контроллера +3,3 В
                  if (m_index >= 8 ) ax *= 2 ;
            #endif
#else
                  _Bipolar_Chanels_ADC( m_index ) ax *= 2 ;
#endif         // _Bipolar_Chanels_ADC
                  //    ax = (w)( (lw)ax * (lw)Nstx[ m_index ].koef >> 8 ) ;

                    /* Вывод целой части: при 205-ти 'ax' - не выйдет за 9.98 */
             //     m_ch = ax / (205*10) + 0x30,  ax %= (205*10) ;
             //     output_c ( m_ch ) ;
                  m_ch = ax / _AD_VOLT + 0x30,  ax %= _AD_VOLT ;
                  output_c ( m_ch ) ;
                  output_c ( '.' ) ;

                    /*   Вывод дробной части: достаточно 2-знака, т.к.
                     * дискрета АЦП приведенная ко входу ячейки ввода/вывода
                     * равна +-10мВ.
                     */
                  ax *= 10,  m_ch = ax / _AD_VOLT + 0x30,  ax %= _AD_VOLT ;
                  output_c ( m_ch ) ;
                  ax *= 10,  m_ch = ax / _AD_VOLT + 0x30,  ax %= _AD_VOLT ;
                  output_c ( m_ch ) ;
                  ax *= 10,  m_ch = ax / _AD_VOLT + 0x30 ;
                  output_c ( m_ch ) ;

                  m_time = Timer1_Ovr ;
                  Label = 23 ;
                }
              if ( TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                  {
                        Nstx[ m_index ].ach->offset = m_addr;
                        output_s ( _ADC_Tst_txt ) ;
                        Label = 101 ;
                  }
                  else if ( m_ch == Enter )
                  {
                        output_s ( _ADC_Tst_txt ) ;
                        Label = 101 ;
                  }
                  else if ( m_ch == Up && Mon.Password_Ok == 1 )   /* изменение смещения. */
                    {
                      if ( (Nstx[m_index].ach->offset+=_AD_Delta) > _AD_MaxOffset ) Nstx[m_index].ach->offset = _AD_MaxOffset ;
                    }
                  else if ( m_ch == Down && Mon.Password_Ok == 1 ) /* изменение смещения. */
                    {
                      if ( (sw)(Nstx[m_index].ach->offset-=_AD_Delta) <= 0 ) Nstx[m_index].ach->offset = 0;
                    }
                  else
                    {
                      Klav_Buff = m_ch;
                    }
                }
              break ;
            //-------------------


#ifdef ADCiklTst

      case 220:
              output_c ( '\n' ) ;
              m_index = 0 ;
              Label = 223 ;

      case 223 :
          if ( TestCompleted_Output() )
            {    // Начать установку нулей Да/Нет
              if ( m_index == 0 ) output_s ( _SetNo_txt ) ;
              else                output_s ( _SetYes_txt ) ;
              Label = 225 ;
              break ;
            }

      case 225:
          if ( TestData_for_Input() )
           {
            mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                  { // Выбрана отмена установки. Вернемся на нулевой канал
                        m_index = 0;
                        Label = 101 ;
                  }
                 else if ( m_ch == Up || m_ch == Down ) /* Изменить выбор. */
                  {
                        m_index = ~m_index,  Label = 223  ;
                  }
                 else if ( m_ch == Enter )
                 {  // Выбрана установка нулей. Перейдем к предварительной проверке
                        if ( m_index == 0 )  {Label = 101 ; break ;}
                        Label = 230 ;
                  }
                 else   Klav_Buff = m_ch;
           }

          break ;

      case 230:
                 // Косвенно по допустимому уровню сигнала определим наличие на входе сигнала с датчиков, чтоб ошибочно его не обнулить
               if ( ObjOffADC_Offset == 1 ) { Label = 244 ; break ; }
               AutoOffsetADC  (0);
               Label = 232 ;
            //   break ;

      case 232:
              ax = AutoOffsetADC(1);

              if ( (sw)ax == 1 )
               {
                  // Тест ОК
                 Label = 243 ;
               }
             else if ( (sw)ax == -1 )
               {
                  // Во время установки нулей выявлен канал с завышенным U. Что может говорить о наличии сигнала на датчике.
                 output_s ( _PresentInpSign_txt ) ;
                 output_c ( '\n' ) ;
                 m_index = 0 ;
                 Label = 235 ; //Спросим: все равно продолжить или Нет
               }

             break ;

      case 235 :
          if ( TestCompleted_Output() )
            {    // Продолжить установку нулей Да/Нет
              if ( m_index == 0 ) output_s ( _ContinueNo_txt  ) ;
              else                output_s ( _ContinueYes_txt ) ;
              Label = 237 ;
              break ;
            }

      case 237:

          if ( TestData_for_Input() )
           {
            mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                  { //Если Нет вернемся на нулевой канал
                        m_index = 0;
                        Label = 101 ;
                  }
                 else if ( m_ch == Up || m_ch == Down ) /* Изменить выбор. */
                  {
                        m_index = ~m_index,  Label = 235  ;
                  }
                 else if ( m_ch == Enter )
                 {  //Если Да: перейдем к предварительной проверке
                        if ( m_index == 0 )  {Label = 101 ; break ;}
                        AutoOffsetADC(0);
                        Label = 240 ;
                  }
                 else   Klav_Buff = m_ch;
           }

              break ;


       case 240:
                  ax = AutoOffsetADC(2);
                  if ( ax == 1 )        Label = 243 ;
                  if ( (sw)ax == -1 )   Label = 242 ;
              break ;

       case 242:
                  m_time = Timer1_Ovr ;
                  output_s ( _SetBad_txt ) ;
                  output_c ( '\n' ) ;
                  output_s ( _CheckByHand_txt ) ;
                  Label = 245 ;
              break ;

       case 243:
                  m_time = Timer1_Ovr ;
                  output_s ( _SetOk_txt ) ;
                  output_c ( '\n' ) ;
                  output_s ( _CheckByHand_txt ) ;
                  Label = 245 ;
              break ;

       case 244:
                  m_time = Timer1_Ovr ;
                  output_s ( _ProgInhibit_txt ) ;
                  output_c ( '\n' ) ;
                  output_s ( _SetByHand_txt ) ;
                  Label = 245 ;

       case 245:

              if ( (u)((w)(Timer1_Ovr - m_time)) > _Sec( 2.0 ))
               {
                 m_index = 0;
                 Label = 101 ;
               }
              break ;
#endif
            //-------------------

      }

  Restart_Output ()  ;

  return ;
}


#ifdef ADCiklTst

sword AutoOffsetADC ( word num )
{

  word ax;
  static word      Lab, time, NCkl;
  static word      m_ext, m_index, SetBad;
  static fslword   meanAD[ sizeof(Nstx)/sizeof(const struct Stx) + 1 ];

  if (num == 0 ) { Lab = 0; m_ext = 0; m_index = 0; NCkl=0; SetBad = 0; return 0; }

  switch ( Lab )
  {
  case 0:
                  m_ext = _AD_BUSY  ;
                  AD_Izm( *Nstx[ m_index ].ach , &m_ext ) ;
                  Lab = 5 ;
                  break;

  case 5:
                  if ( m_ext == _AD_BUSY ) break ; // ожидание готовности измерения.

                  mIzmData_Conversion( m_ext , ax , *Nstx[ m_index ].ach ) ;
                    // Накапливаем для послед. усреднения
                  if ( NCkl == 0 ) meanAD[ m_index ]  = (slw)(sw)ax;
                  else             meanAD[ m_index ] += (slw)(sw)ax;

                  if ( (sw)ax < 0 ) ax = ~ax + 1 ;
                    // Если попалось значение > допустимого, можно предположить что на этом входе висит сигнал
                    // Проверка на выход за допуск только для входного параметра ==1
                  if ( ( ax > _r_max_U_AD_Izm && PermitTstACh[ m_index ] != 0  )&& num == 1 ) Lab = 10;
                  else Lab = 7;

                  time = timer1;
                  break ;

  case 7:
                    // Произведем измерения в разных точках с частотой не кратной сети для следующего прохода текущего m_index
                  if ( (u)(w)(timer1 - time) < _MkSec(800) ) break;
                  //if (m_index == 0 ) NCkl++;

                  if ( ++m_index >= _Nm )
                   {
                    m_index = 0 ;
                      // Усреднение по каналам
                    if ( ++NCkl >= ADCiklTst )
                     {
                      for (ax=0; ax < _Nm ; ax++)
                       {
                        meanAD[ax] = meanAD[ax] / ADCiklTst ;
                          // Производим смещ. только в указанных каналах
                          // Не производим смещение если вышли за сетку мин. макс. (оставляем для ручной проверки).
                        if (PermitTstACh[ ax ] == 0 || ((sw)((sw)Nstx[ax].ach->offset + (sw)meanAD[ax]) < 0) ||
                            ((sw)((sw)Nstx[ax].ach->offset + (sw)meanAD[ax]) > _AD_MaxOffset ) )
                         {
                          if ( PermitTstACh[ ax ] != 0 )
                           {
                            SetBad = 1;
                           }
                          continue;
                         }
                        else
                         {
                          Nstx[ax].ach->offset += (sw)meanAD[ax];
                         }
                       }
                      if ( SetBad != 0 ) return -1;
                      else               return  1;
                     }
                   }

                  Lab = 0 ;
                  break;

  case 10:
                  return -1;

  }
  return 0;
}

#endif

