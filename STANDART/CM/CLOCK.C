// Программа индикации времени из часов-календаря.
#include <math.h>
typedef union {
  word all;
  struct {
    word Count_Down :1;
    word sign       :1;
    word Null       :1;
  }_;
} Calibr_Count_state;
void Calc_calibr(float *in, bool Down_btn );

void xClock ( I2C_time* ptr )
{
  _register word    ax , cx ;
  _register byte  bl;
  
  //_register lword  lax ;
  
  if ( M_FirstCall == 1 )  /*  Идентификация первого входа для задания  */
  {                      /* начального условия ...                    */
    M_FirstCall = 0 ;
    Label = 100 ;
    m_index = 0 ;
    t_clock = Timer1_Ovr;
    
    return ;
  }
  
  switch ( Label )
  {
  default:
  case 100:
    Time_label = 0;
    Label = 101;
  case 101:
    output_s ( _Clock_prompt ) ;
    output_c ( '\n' ) ;
    Label = 103 ;
  case 103:
    // Пропуск вывода, если не завершен предыдущий вывод.
    if (  TestCompleted_Output() )
    {
      output_c ('\r') ;
      output_s (AWelcome) ;
      output_s ( c_Clock[m_index] ) ;
      Label = 105 ;
      break ;
    }
  case 105:
    while (  TestData_for_Input() )
    {
      mInput_c ( m_ch ) ;
      if ( m_ch == Return )
      {
        Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
        return ;   // добавить еще какую-то иниц.
      }
      else if ( m_ch == Up ) /* Изменить номер индицируемой переменной.*/
      {
        if ( ++m_index >= 2 ) m_index = 0 ;
        Label = 103 ;
      }    /* переход к следующей настройке */
      else if ( m_ch == Down ) /* Изменить номер индицируемой переменной.*/
      {
        if ( (sw)(--m_index) < 0 ) m_index = 1 ;
        Label = 103 ;
      }
      else if ( m_ch == Enter )
      {
        output_s ( "\n\r" ) ;
        output_s ( c_Clock[m_index] ) ;
        output_c ( '\n' ) ;
        
        Label = m_index+2 ;
      }
      else
      {
        Klav_Buff = m_ch;
      }
      
    }
    if (AWelcome != AWell_old )
    {
      AWell_old = AWelcome;
      Label = 103;
    }
    
    break ;
    //-------------------
    
  case 2:
    // Ожидание завершения предыдущего вывода + тактирование,
    if  ( (  TestCompleted_Output() )    // чтобы не мельтешило.
         && ( (u)((w)(Timer1_Ovr - m_time)) > 2 ) )
    {
      output_c ( '\r' ) ;
      output_s (AWelcome) ;
      for ( ax = 2; (sw)ax >= 1; --ax  )
      {
        bl =ptr->b[ax];
        
        cx = bl/10 ;
        cx += 0x30;
        output_c ( cx );
        cx = (bl%10)+0x30;
        output_c ( cx );
        output_c ( ':' );
        
      }
      
      bl =ptr->b[0];
      
      cx = bl/10;
      cx += 0x30;
      output_c ( cx );
      cx = (bl%10 )+0x30;
      output_c ( cx );
      output_c ( ' ' );
      
      m_time = Timer1_Ovr ;
    }
    
    while (  TestData_for_Input() )
    {
      mInput_c ( m_ch ) ;
      if ( m_ch == Return )  Label = 102 ;
      else
      {
        Klav_Buff = m_ch;
      }
    }
    //if ( (u)((w)(Timer1_Ovr - t_clock)) > _Sec(0.1) )  Label = 4;
    
    break ;
    //-------------------
  case 3:
    // Ожидание завершения предыдущего вывода + тактирование,
    if  ( (  TestCompleted_Output() )    // чтобы не мельтешило.
         && ( (u)((w)(Timer1_Ovr - m_time)) > 2 ) )
    {
      output_c ( '\r' ) ;
      output_s (AWelcome) ;
      for ( ax = 4; ax <= 5; ++ax  )
      {
        bl =ptr->b[ax];
        
        cx = bl/10 ;
        cx += 0x30;
        output_c ( cx );
        cx = (bl%10 )+0x30;
        output_c ( cx );
        output_c ( '.' );
        
      }
      bl =ptr->b[6];
      
      cx = bl/10;
      cx += 0x30;
      output_c ( cx );
      cx = (bl%10)+0x30;
      output_c ( cx );
      if (ptr->b[3] > 7)
      {
        ptr->b[3] = 7;
      }
      //День недели от 0 до 6
      
      output_s ( Day[(ptr->b[3])] );
      
      m_time = Timer1_Ovr ;
    }
    
    while (  TestData_for_Input() )
    {
      mInput_c ( m_ch ) ;
      if ( m_ch == Return )  Label = 102 ;
      else
      {
        Klav_Buff = m_ch;
      }
    }
    break ;
    
  }
  
  Restart_Output ()  ;
  
  return ;
}

// Программа настройки времени в часах-календаре.
void xClock_ust ( I2C_time* ptr)
{
  _register word    ax , bx , cx ;
  float fax,fbx, fcx;
  //_register byte  bl;
  _register lword  lax;//,lbx ;
  static I2C_time s_time;
  static word R_WSTime_On, WTime;
  //static float Calibr_Buf;
  //  Контроль пароля: Полный запрет входа.
  
  if ( Password_control ( 2 ) == 0 )  return   ;
  //---
  
  
  if ( M_FirstCall == 1 )  //  Идентификация первого входа для задани
  {                      // начального условия ...
    M_FirstCall = 0 ;
    Label = 100 ;
    m_index = 5 ; // 0
    Time_label = 0;
    Write_RTC |= _No_WinTime;
    return ;
  }
  
  switch ( Label )
  {
  case 100:
    s_time = *ptr;
    Label = 101;
    
  case 101:
    /* bx = s_time.b[0]|| 0x80;
    if ( Mon.i2c_busy == 1 ) break; //  Ждем пока освободится шина.
    Mon.i2c_busy = 1 ;  // Устанавливаем признак, что теперь шина занята.
    i2c_label = 0;
    ax = Save_into_i2c  ( 1 , (b*)&bx , _Adr_sec  ,_Adr_Clock_i2c) ;
    Mon.i2c_busy = 0 ;
    t_clock = Timer1_Ovr;*/
    Label = 102;
    break;
    
  default:
  case 102:
    output_s ( _Clock1_prompt ) ;
    output_c ( '\n' ) ;
    Label = 103 ;
    break;
    
  case 103:
    // Пропуск вывода, если не завершен предыдущий вывод.
    if (  TestCompleted_Output() )
    {
      output_c ('\r') ;
      output_s (AWelcome) ;
      output_s ( u_Clock[m_index] ) ;
      Label = 105 ;
      break ;
    }
  case 105:
    while (  TestData_for_Input() )
    {
      mInput_c ( m_ch ) ;
      if ( m_ch == Return )
      {
        Label = 106;
        break;
      }
      else if ( m_ch == Up ) /* Изменить номер индицируемой переменной.*/
      {
        if ( ++m_index >= 8 ) m_index = 0 ;
        Label = 103 ;
      }    /* переход к следующей настройке */
      else if ( m_ch == Down ) /* Изменить номер индицируемой переменной.*/
      {
        if ( (sw)(--m_index) < 0 ) m_index = 7 ;
        Label = 103 ;
      }
      else if ( m_ch == Enter )
      {
        output_s ( "\n\r " ) ;
        output_s ( u_Clock[m_index] ) ;
        output_s ( ":\n" ) ;
        Label = m_index ;
      }
      else
      {
        Klav_Buff = m_ch;
      }
      
    }
    if (AWelcome != AWell_old )
    {
      AWell_old = AWelcome;
      Label = 103;
    }
    
    break ;
    //-------------------
  case 106:
    if ( (u)((w)(Timer1_Ovr - t_clock)) > _Sec(0.25) )
    {
      *ptr = s_time;
      Write_RTC = _Int_TimeWr;
      /* LPC_RTC->SEC = s_time.b[0];
      LPC_RTC->MIN = s_time.b[1] ;
      LPC_RTC->HOUR= s_time.b[2] ;
      LPC_RTC->DOW = s_time.b[3] ;
      LPC_RTC->DOM = s_time.b[4]  ;
      LPC_RTC->MONTH = s_time.b[5] ;
      LPC_RTC->YEAR  = s_time.b[6];*/
      RTC_Err = false;
      LPC_RTC->RTC_AUX |= RTC_AUX_RTC_OSCF;
      Label = 107;
      t_clock =  Timer1_Ovr;
    }
    break;
  case 107:
    if (Write_RTC == 0)
    {
      Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
    }
    return ;   // добавить еще какую-то иниц.
    
  case 0:
    clock_max = 59;
    n_clock = 1;
    Label = 70;
    break;
  case 1:
    clock_max = 23;
    n_clock = 2;
    Label =70 ;
    break;
  case 2:
    Label = 80;
    break;
  case 3:
    clock_max = 31;
    n_clock = 4;
    Label = 70;
    break;
  case 4:
    clock_max = 12;
    n_clock = 5;
    Label = 70;
    break;
  case 5:
    clock_max = 99;
    n_clock = 6;
    Label = 70;
    break;
  case 70:
    
    clock_ed  =s_time.b[n_clock];
    if ( (u)clock_ed> clock_max) clock_ed = clock_max;
    Label = 60;
    
  case 60:
    if  ( (  TestCompleted_Output() )    // чтобы не мельтешило.
         && ( (u)((w)(Timer1_Ovr - m_time)) > _Sec(0.15) ) )
    {
      output_c ( '\r');
      output_s (AWelcome) ;
      cx = clock_ed/10;
      cx += 0x30;
      output_c ( cx );
      cx = (clock_ed%10)+0x30;
      output_c ( cx );
      output_c ( '\r');
      m_time = Timer1_Ovr ;
    }
    
    while ( TestData_for_Input() )
    {
      mInput_c ( m_ch ) ;
      if ( m_ch == Return )
      {
        output_c ('\n');
        Label = 102 ;
      }
      else if ( m_ch == Up )
      {
        if ( clock_ed == clock_max )
        {
          if ( (n_clock == 6) || (n_clock == 1)
              ||(n_clock == 2))
          {
            clock_ed = 0;
          }
          else clock_ed = 1;
        }
        else clock_ed++ ;
      }
      else if ( m_ch == Down )
      {
        if ( (n_clock == 6) || (n_clock == 1)
            ||(n_clock == 2))
        {
          ax = 0;
        }
        else ax = 1;
        
        if ( clock_ed != ax )
        {
          clock_ed--;
        }
        else clock_ed = clock_max;
      }
      else if (m_ch == Enter)
      {
        s_time.b[n_clock] = clock_ed;
        output_c ('\n');
        Label = 102 ;
      }
      else
      {
        Klav_Buff = m_ch;
      }
      
    }
    break ;
    
  case 6:
    // if ((LPC_RTC->CALIBRATION&0x20000)!=0) calibr = ~calibr+1;
    if ((LPC_RTC->CCR & 0x10) != 0)
    {
      //calibr =  LPC_RTC->CALIBRATION&0x20000;
      caltime =86400.0/(float)(LPC_RTC->CALIBRATION&0x1ffff); //86400 - 24*3600 - количество секунд в сутках
      if (caltime > 10000.0 )
      {
        if ((LPC_RTC->CALIBRATION&0x20000) == 0)
        {
          LPC_RTC->CALIBRATION = 0x9;//8.64
        }
        else
        {
          LPC_RTC->CALIBRATION = 0x20009;//8.64 | 0x20000
        }
        caltime = 10000.0;
      }
      if ((LPC_RTC->CALIBRATION&0x20000)!= 0)
      {
        caltime *= -1;
      }
    }
    else
    {
      caltime = 0;
    }
    //caltime.hours = lax/3600;
    //lax %=3600;
    //caltime.min = (slw)lax/60;
    //caltime.sec = (slw)lax%60;
    clock_ed = 0;
    Label = 61 ;
    break;
  case 61:
    // Пропуск вывода, если не завершен предыдущий вывод.
    if (  TestCompleted_Output() )
    {
      //output_c ('\r') ;
      //output_s (AWelcome) ;
      //output_s ( cal_Clock[0] ) ;
      Label = 63 ;
      break ;
    }
    
  case 62:
    while ( TestData_for_Input() )
    {
      mInput_c ( m_ch ) ;
      if ( m_ch == Return )
      {
        output_c ('\n');
        Label = 102 ;
      }
      else if ( m_ch == Up )
      {
        if ( (sb)(++clock_ed) >= 1 ) clock_ed = 0;
        Label = 61;
      }
      else if ( m_ch == Down )
      {
        if ( (sb)(--clock_ed)< 0 ) clock_ed = 1;
        Label = 61;
        
      }
      else if (m_ch == Enter)
      {
        output_c ( '\n');
        switch ( clock_ed)
        {
        default:
          clock_ed = 0;
        case 0:
          Label = 63;
          break;
        case 1:
          Label = 67;
          break;
        }
        
      }
      else
      {
        Klav_Buff = m_ch;
      }
      
    }
    break ;
  case 63 :
    if  (   TestCompleted_Output() )    // чтобы не мельтешило.
    {
      output_c ( '\r');
      //output_s (AWelcome) ;
      
      // fcx = modff(caltime,&fax);
      bx = 0;
      if (caltime < 0)
      {
        ax = 1; //число отрицательное
        
      }
      else
      {
        ax = 0;
      }
      fcx = fabsf(caltime); //Модуль
      modff(fcx,&fax); //берем целую часть
      for ( fbx = 10000 ; fbx > 1 ; fbx /= 10 )
      {
        fax = fax/fbx;
        
        if ((w)fax != 0)
        {
          bx = 1;
        }
        
        if (bx == 0)
        {
          output_c ( ' ' ) ;
        }
        else
        {
          if (ax != 0)
          {
            output_c ( '-' ) ;
            ax = 0;
          }
          output_c ( (b)fax + 0x30 ) ;
        }
        //Остаток от деления  calibr на fbx
        fax = fmodf( fcx , fbx );
      }
      
      if (ax != 0)
      {
        output_c ( '-' ) ;
      }
      // распечатываем последнюю цифру.
      output_c ( (b)fax + 0x30 ) ;
      if (fcx < 100)
      {
        if (fcx < 1)
        {
          ax = 1000;
        }        
        else if (fcx < 10)
        {
          ax = 100;
        } 
        else
        {
          ax = 10;
        }
        
        output_c ( '.' ) ;
        
        for ( fbx = 10 ; fbx <= (float)ax ; fbx *= 10 )
        { 
          //Разделение на целую (кладется в fcx) и дробную(кладется в fax) части  fax
          fax = modff( fcx , &fcx );
          fcx = fax*10;
          output_c ( (b)fcx + 0x30 ) ;
          
        }
      }
      output_s ( _Calibr_txt ) ;
      
      Label = 64;
      break;
    }
  case 64:
    while ( TestData_for_Input() )
    {
      mInput_c ( m_ch ) ;
      
      if (caltime > 0)
      {
        ax = 1;
      }
      else
      {
        ax = 0;
      }
      
      if ( m_ch == Return )
      {
        output_c ('\n');
        Label = 102 ;
      }
      else if ( m_ch == Up )
      {
        Calc_calibr(&caltime, false );
        Label = 63;
      }
      else if ( m_ch == Down )
      {
        Calc_calibr(&caltime, true );
        Label = 63;
        
      }
      else if (m_ch == Enter)
      {
        Label = 65;
      }
      else
      {
        Klav_Buff = m_ch;
      }
      
    }    
    break ;
  case 65:
    output_c ('\n');
    if (caltime < 0)
    {
      calibr = 0x20000;
      caltime = fabsf(caltime);
    }
    else
    {
      calibr = 0;
    }
    
    fax = 86400.0/caltime;
    //131071 - максимальное число,которое можно записать в регистр
    if ( isinf(fax))
    {
      calibr = 0;
      lax = 0;
      LPC_RTC->CCR &= (~0x10);//calibration disable
      
    }
    else
    {
      if (isnan (fax))
      {
        lax = 0;
      }
      else
      {
        if (fax > 131071.0)
        {
          lax = 131071;
        }
        else
        {
          lax = (lw)(fax+0.5);
        }
        
      }
      
      /* if ((calibr != 0)&&(calibr != 0x20000))
      {
      calibr = LPC_RTC->CALIBRATION &0x20000;
    }
      */
      LPC_RTC->CCR |= 0x10;//calibration enable
    }
    calibr |= lax;
    LPC_RTC->CALIBRATION = calibr;
    
    Label = 103 ;
    break;
    /*
  case 67:
    if  (   TestCompleted_Output() )    // чтобы не мельтешило.
    {
    output_c ( '\r');
    output_s (AWelcome) ;
    if (calibr == 0)
    {
    output_s (Forw_Cal) ;
  }
    else
    {
    output_s (Back_Cal) ;
  }
    Label = 68;
    break;
  }
    
  case 68:
    while ( TestData_for_Input() )
    {
    mInput_c ( m_ch ) ;
    if ( m_ch == Return )
    {
    output_c ('\n');
    Label = 6 ;
  }
    else if (( m_ch == Up ) || ( m_ch == Down ))
    {
    if (calibr == 0) calibr = 0x20000;
    else calibr = 0;
    Label = 67;
    
  }
    else if (m_ch == Enter)
    {
    Label = 65;
  }
    else
    {
    Klav_Buff = m_ch;
  }
    
  }
    break ;
    */
  case 7 :
    R_WSTime_On = _WinTimeOn;
    WTime = WinTime;
  case 75:
    output_c ( '\r');
    output_s (AWelcome) ;
    m_time = Timer1_Ovr ;
    if (R_WSTime_On == 1)
    {
      output_s ( _On_txt );
      
    }
    else
    {
      output_s ( _Off_txt );
    }
    Label = 71;
    break ;
  case 71:
    if  (  TestCompleted_Output() )    // чтобы не мельтешило.
    {
      while ( TestData_for_Input() )
      {
        mInput_c ( m_ch ) ;
        if ( m_ch == Return )
        {
          output_c ('\n');
          Label = 102 ;
        }
        else if ( (m_ch == Up)|| ( m_ch == Down ))
        {
          if (R_WSTime_On == 1)
          {
            R_WSTime_On = 0;
          }
          else
          {
            R_WSTime_On = 1;
          }
          Label = 75;
          
        }
        else if (m_ch == Enter)
        {
          //output_c ('\n');
          _WinTimeOn = R_WSTime_On;
          if (R_WSTime_On == 1)
          {
            Label = 72 ;
          }
          else
          {
            output_c ('\n');
            Label = 102 ;
            
          }
        }
        else
        {
          Klav_Buff = m_ch;
        }
      }
    }
    break;
  case 72:
    output_c ( '\r');
    output_s (AWelcome) ;
    m_time = Timer1_Ovr ;
    if (WTime == 0)
    {
      output_s ( _Summer_txt );
    }
    else
    {
      output_s ( _Winter_txt );
    }
    Label = 73;
    break;
  case 73:
    if  (  TestCompleted_Output() )    // чтобы не мельтешило.
    {
      while ( TestData_for_Input() )
      {
        mInput_c ( m_ch ) ;
        if ( m_ch == Return )
        {
          output_c ('\n');
          Label = 102 ;
        }
        else if ( (m_ch == Up)|| ( m_ch == Down ))
        {
          if (WTime == 1)
          {
            WTime = 0;
          }
          else
          {
            WTime = 1;
          }
          Label = 72;
          
        }
        else if ( m_ch == Enter )
        {
          WinTime = WTime;
          output_c ('\n');
          Label = 102 ;
        }
        else
        {
          Klav_Buff = m_ch;
        }
      }
    }
    break;
  case 80:
    clock_ed =s_time.b[3];
    if ( (u)clock_ed >= 7) clock_ed = 6;
    //else if (clock_ed == 0 ) clock_ed = 1;
    Label = 8;
  case 8:
    if  ( (  TestCompleted_Output() )    // чтобы не мельтешило.
         && ( (u)((w)(Timer1_Ovr - m_time)) > _Sec(0.15) ) )
    {
      
      output_c ( '\r');
      output_s (AWelcome) ;
      output_s ( Day[clock_ed] );
      m_time = Timer1_Ovr ;
    }
    
    while ( TestData_for_Input() )
    {
      mInput_c ( m_ch ) ;
      if ( m_ch == Return )
      {
        output_c ('\n');
        Label = 102 ;
      }
      else if ( m_ch == Up )
      {
        if ( clock_ed == 6 )
        {
          clock_ed = 0;
        }
        else ++clock_ed;
      }
      else if ( m_ch == Down )
      {
        if ( clock_ed != 0 )
        {
          --clock_ed;
        }
        else clock_ed = 6;
      }
      else if (m_ch == Enter)
      {
        s_time.b[3] = clock_ed;
        output_c ('\n');
        Label = 102 ;
      }
      else
      {
        Klav_Buff = m_ch;
      }
      
    }
    break ;
    
  }
  Restart_Output ()  ;
  
  return ;
}
//----------------------------------------------------------
void Calc_calibr(float *in, bool Down_btn )
{
  Calibr_Count_state State;
  float fax, fcx, fbx = 1, out = *in;
  State.all = 0;
  if (out >= 0)
  {
    State._.sign = false;
  }
  else
  {
    State._.sign = true;
  }
  
  if (Down_btn)
  {
    
    if (out > 0)
    {
      State._.Count_Down = false;
      if (out <=  86400.0/131071.0)
      {
        State._.Count_Down = true;
        out = 0;
        State._.Null = true;
        //sign = true;
      }
    }
    else
    {
      if (out == 0)
      {
        State._.sign = true;
      }
      State._.Count_Down = true;
    }
  }
  else
  { 
    if (out < 0)
    {
      State._.Count_Down = false;
      if (out >= -86400.0/131071.0)
      {
        State._.Count_Down = true;
        State._.sign = false;
        out = 0;
        State._.Null = true;
        
      }
    }
    else
    {
      if (out == 0)
      {
        State._.sign = false;
      }      
      State._.Count_Down = true;      
      
    }
  }
  if (!State._.Null)
  {
    modff((86400.0/fabsf(out)+0.5), &fax);
    if (isinf(fax)|| fax > 131071)
    {
      fax = 131071;    
    }
    else if (isnan(fax))
    {
      fax = 0;
    }
    fbx = 1.157e-5; // 1/86400
    if (fax > 86400/100)
    {
      fbx = 1.157e-6;// 0.1/86400
      if (fax > 86400/10)
      {             
        fbx = 1.157e-7;// 0.01/86400
        if (fax > 86400)
        {
          fbx = 1.157e-8;// 0.001/86400
        }      
      }
    }
    if (!State._.Count_Down)
    {
      modff(fax,&fcx);
      fax = fax/(1-fax*fbx);
      fbx = modff(fax,&fax);
      if ((fax == fcx ) & (fbx != 0))
      {
        ++fax;
      }
      if (!isnormal(fax)) 
      {
        fax = 1;
      }
      if (fax < 131071)
      {
        out = 86400.0/fax;
      }
      else
      {
        out = 86400.0/131071;
      }
    }
    else
    {
      fax = fax/(1+fax*fbx);
      fbx = modff(fax,&fax);
      
      if (!isnormal(fax))
      {
        fax = 1;
      }
      if (fax > 1)
      {
        out = 86400.0/fax;
      }
      else
      {
        out = 86400.0;
      }    
    }
  }
  if (State._.sign)
  {
    *in = out *-1;
  }
  else
  {
    *in = out;
  }
  
}