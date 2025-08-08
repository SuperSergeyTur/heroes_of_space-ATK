#include "rtc.h"
//Инициализация часов реального времени
//День недели от 0 до 6 по этому сравниваем с 7
bool Ctrl_RTC_Regs (void)
{
  if ((LPC_RTC->SEC > 59)||(LPC_RTC->MIN > 59)||(LPC_RTC->HOUR > 24)
      ||( LPC_RTC->DOW >= 7)||(LPC_RTC->DOM > 31)
        ||(LPC_RTC->DOM == 0)||(LPC_RTC->MONTH > 12)||(LPC_RTC->MONTH == 0))
  {
    return false;
  }
  else
  {
    return true;
  }
}

void RTC_Init( void )
{
  word bx = 0;
  //SysError._.RTC = 0 ;
  //Включаем часы
  RTC_Err = false;
  SummerTime_Label = 0;
  Time_WT = 0;
  if ((LPC_RTC->RTC_AUX& RTC_AUX_RTC_OSCF) != 0)
  {
    RTC_Err = true;
  }
  //бит 2 регистра CCR, если 1 - Останавливает часы 
  //бит 3 - при 1 - все счетные регистры изменяются на 1 раз в сек
  //для нормальной работы их нужно обнулять
  LPC_RTC->CCR &= 0x13;
  LPC_RTC->CCR |= RTC_CCR_CLKEN;
  //Три раза считываем регистры, если ошибка - загружаем значения по умолчанию
  do {
    if (!Ctrl_RTC_Regs())
    {
      ++bx;
    }
    else
    {
      bx = 5;
    }
  }
  while(bx < 3);
  
  if ((bx != 5))
  {
    RTC_Err = true;
  //Если в регистрах часов мусор, то мы их очищаем, чтобы не показывало 46 часов 67 минут.
    LPC_RTC->SEC = 0;
    LPC_RTC->MIN = 0;
    LPC_RTC->HOUR = 0;
    LPC_RTC->DOW = 5;
    LPC_RTC->DOM = 9;
    LPC_RTC->MONTH = 5;
    LPC_RTC->YEAR = 25;
  }
  Write_RTC = 0;
  
}
/*
void SetTime( byte Hour, byte Minute, byte Second )
{
= Second;
LPC_RTC->MIN  = Minute;
LPC_RTC->HOUR = Hour;
}

void SetDay(byte Day, byte Month, word Year, byte DayOfWeek, word DayOfYear)
{
LPC_RTC->DOM  = Day;
LPC_RTC->MONTH  = Month;
LPC_RTC->YEAR = Year;
LPC_RTC->DOW  = DayOfWeek;
LPC_RTC->DOY  = DayOfYear;
}
*/
word  Read_i2c_time( void )
{
  d_time.b[0] = LPC_RTC->SEC;
  d_time.b[1] = LPC_RTC->MIN;
  d_time.b[2] = LPC_RTC->HOUR;
  d_time.b[3] = LPC_RTC->DOW;
  d_time.b[4] = LPC_RTC->DOM;
  d_time.b[5] = LPC_RTC->MONTH;
  d_time.b[6] = LPC_RTC->YEAR;
  //переделывем в двоично-десятичную систему
  c_time.b[0] =  (d_time.b[0]/10<<4)+(d_time.b[0]%10);
  c_time.b[1] =  (d_time.b[1]/10<<4)+(d_time.b[1]%10);
  c_time.b[2] =  (d_time.b[2]/10<<4)+(d_time.b[2]%10);
  c_time.b[3] =  (d_time.b[3]/10<<4)+(d_time.b[3]%10)+1;// для того, чтобы согласовать старый формат вывода дня недели с новым
  c_time.b[4] =  (d_time.b[4]/10<<4)+(d_time.b[4]%10);
  c_time.b[5] =  (d_time.b[5]/10<<4)+(d_time.b[5]%10);
  c_time.b[6] =  (d_time.b[6]/10<<4)+(d_time.b[6]%10);
  
  return 0 ;
}
//Сохранение данных часов в регистрах RTC
//в c_time запишется после функции Read_i2c_time
void WriteTime ( I2C_time* ptr )
{
  LPC_RTC->SEC   =  ptr->b[0];
  LPC_RTC->MIN   =  ptr->b[1];
  LPC_RTC->HOUR  =  ptr->b[2];
  LPC_RTC->DOW   =  ptr->b[3];
  LPC_RTC->DOM   =  ptr->b[4];
  LPC_RTC->MONTH =  ptr->b[5];
  LPC_RTC->YEAR  =  ptr->b[6];
}

void ReadRTC( I2C_time* ptr )
{
  ptr->b[0] = LPC_RTC->SEC;
  ptr->b[1] = LPC_RTC->MIN;
  ptr->b[2] = LPC_RTC->HOUR;
  ptr->b[3] = LPC_RTC->DOW;
  ptr->b[4] = LPC_RTC->DOM;
  ptr->b[5] = LPC_RTC->MONTH;
  ptr->b[6] = LPC_RTC->YEAR;
}

/*------------------------------------------------------------------*/
/*   Программа распечатки времени считанного из часов реального времени.
*/

void PrintTime ( I2C_time* ptr )
{
  register word  ax ;
  //Контроль содержимого регистров, если там мусор - то очищаем их.
  if ((_byte_DBC_to_DEC(ptr->b[0]) > 59)||(_byte_DBC_to_DEC(ptr->b[1])> 59)||(_byte_DBC_to_DEC(ptr->b[2]) > 24)
      ||( _byte_DBC_to_DEC(ptr->b[3])> 8)||( _byte_DBC_to_DEC(ptr->b[3]) == 0)||(_byte_DBC_to_DEC(ptr->b[4]) > 31)
        ||(_byte_DBC_to_DEC(ptr->b[4]) == 0)||(_byte_DBC_to_DEC(ptr->b[5]) > 12)||(_byte_DBC_to_DEC(ptr->b[5]) == 0))
  {
    
    ptr->b[0] = 0;
    ptr->b[1] = 0;
    ptr->b[2] = 0;
    ptr->b[3] = 8;
    ptr->b[4] = 1;
    ptr->b[5] = 1;
    ptr->b[6] = 0;
  }
  
  
  // распечатка дня, месяца, года.
  for ( ax = 4 ; ax != 7 ; ax++ )
  {       // десятки.
    m_ch = ptr->b[ax] >> 4 ;
    output_c( m_ch + 0x30 ) ;
    // единицы.
    m_ch = ptr->b[ax] & 0x0f ;
    output_c( m_ch + 0x30 ) ;
    output_c( '.' ) ;
  }
  // распечатка дня недели.
  output_s( Day[ptr->b[3]-1] ) ;
  
  output_s( "\r\n" ) ;
  
  // распечатка часов, минут, секунд.
  for ( ax = 2 ; (sw)ax >= 0 ; ax-- )
  {       // десятки.
    m_ch = ptr->b[ax] >> 4 ;
    output_c( m_ch + 0x30 ) ;
    // единицы.
    m_ch = ptr->b[ax] & 0x0f ;
    output_c( m_ch + 0x30 ) ;
    if( ax != 0 ) output_c( ':' ) ;
  }
  
  return ;
}
//--------------
void Write_to_RTC(word code)
{
  I2C_time* ptr;
  
  switch (code)
  {
  case _Link_TimeWr:
    --l_time.b[3];//сдвинуть день недели, т.к. в компе день недели 1-7, а нам надо 0-6
    ptr = &l_time;
    Calibr_cynch_time(ptr);
    RTC_Err = false;
    LPC_RTC->RTC_AUX |= RTC_AUX_RTC_OSCF;
    break;
  case _Int_TimeWr:
    ptr = &d_time;
    break;
  case _ExternSynhWr:
    ptr = &d_time;
    break;
    
  };
  if (code != 0)
  {
    WriteTime ( ptr );
  }
}
//--------------
void Calibr_cynch_time(I2C_time* ptr)
{
  I2C_time Calibr_Time;
  lword lax, lbx, lcx;  
  DateConverter CalibrDateConvert;
  bool Save = false;
  ReadRTC( &Calibr_Time);    
  lbx = Load_from_i2c(4 ,Calibr_addr ,(b*)&lax, _Adr_Flash_i2c);
  if (lbx == 0)
  {
    //Берем количество секунд от контрольной даты.
    lbx = CalibrDateConvert.secondsSinceReferenceDate(ptr,(bool)_WinTimeOn, false);
    Save = true; 
    
    if (lbx > lax) 
    {
      //Контрольный промежуток времени
      lax = (lbx - lax);
      //Если попали в заданный промежуток, то калибруем
      if(lax < (lw)_Calibr_Delta_Max)
      {
        if(lax > (lw)_Calibr_Delta_Min)
        {
          
          //Получаем время часов
          lcx =  CalibrDateConvert.secondsSinceReferenceDate(&Calibr_Time,(bool)_WinTimeOn, false);
          //разница в показаниях в секундах
          float fbx = (float)(slw)(lbx - lcx);
          
          //получаем сколько суток прошло с момента последней синхронизации          
          float fax = ((float)(slw)lax/fbx);//Округляем до единиц
          if ((LPC_RTC->CCR & 0x10) != 0)
          {
            lax = LPC_RTC->CALIBRATION;
          }
          else
          {
            lax = 0;
          }
          fbx = (float)(lax & 0x1ffff);
          if ((lax &0x20000) != 0)
          {
            fbx *= -1;
          }
          fbx+= fax;
          lax = 0;
          if (fbx < 0)
          {
            lax |= 0x20000;
            fbx = fabs(fbx);
          }
          if (fbx > 131072)
          {
            fbx = 131072;
          }
          if ((lw)fbx != 0)
          {
            LPC_RTC->CCR |= 0x10;//calibration enable
          }
          lax += (lw)(fbx+0.5);
          LPC_RTC->CALIBRATION = lax;
        }
        else
        {
          Save = false;
        }
      }
    }
  }
  if (Save)
  {
    //Засекаем время 
    Save_into_i2c( 4,(b*)&lbx, Calibr_addr, _Adr_Flash_i2c );                
    
  }
}

void xOvr_Time_Schet(I2C_time* ptr)
{
  
  if ((Write_RTC&0x1f) != 0)
  {
    Write_to_RTC(Write_RTC);
    Write_RTC = 0;
    
  }
  Read_i2c_time() ;
  *ptr = c_time ;
  
  if (_WinTimeOn != 0)
  {
    //Проверка перехода на зимнее/летнее врем
    if (((Write_RTC&0x80) == 0)&& (WinterSummer_time() == 2))
    {
      Write_RTC = _Int_TimeWr;
    }
  }
  
  if (RTC_Err)
  {
#ifdef _Srv2_RTC_Err
    mSet_ServiceMsg2 (_Srv2_RTC_Err) ;
#elif  _Srv_RTC_Err
    mSet_ServiceMsg (_Srv_RTC_Err) ;
#else   
    mSet_ServiceMsg3 (_Srv3_RTC_Err) ;
#endif
  }
  else
  {
#ifdef _Srv2_RTC_Err
    mClr_ServiceMsg2 (_Srv2_RTC_Err) ;
#elif  _Srv_RTC_Err
    mClr_ServiceMsg (_Srv_RTC_Err) ;
#else
    mClr_ServiceMsg3 (_Srv3_RTC_Err) ;
#endif
  }
  return ;
}

//--------------
//4 - продолжается изменение
//1 - авария_
//2 - необходима запись времени
//0 - ничего не делаем
word WinterSummer_time(void)
{
  enum {wt0, wt1, wt2, wt3, wt4, wt5};
  //byte Set_hour = 25 ;
  // bool out = false;
  bool Plus = false;
  bool Minus = false;
  word ax = 4;
  //Расчитываем переход на зимнее врем
  switch ( SummerTime_Label)
  {
  case wt0 :    
    SummerTime_Label = wt2;
    
    if (WinTime == 0)
    {
      if ((d_time.b[5] <= 3)||(d_time.b[5] >= 10))
      {
        //Ищем дату перехода
        if (d_time.b[5] == 10)
        {
          //последнее воскресенье октября не может наступить раньше 25 числа
          if (d_time.b[4] >= 25  )
          {
            //Последнее воскресенье месяца
            if (d_time.b[3] == 6)
            {
              //Четыре часа ночи
              if (d_time.b[2] >= 4)
              {
                Minus = true;
              }
            }
            else
            {
              //Если 25+DOW меньше текущей даты, то, значит, воскресенье уже было, а
              //время не изменили
              if ((25+d_time.b[3])< d_time.b[4])
              {
                Minus = true;
              }
            }
            
          }
          
        }
        else //Если в зимнее время не переключились еще
        {
          //Если еще рано до даты перехода
          if(d_time.b[5] == 3)
          {
            //До последнего воскресень
            if( d_time.b[4] < 25)
            {
              Minus = true;
            }
            else
            {
              if (d_time.b[3] == 6)
              {
                
                if (d_time.b[2] <= 3)
                {
                  Minus = true;
                }
              }
              else
              {
                //Если 25+DOW меньше текущей даты, то, значит, воскресенье уже было, а
                //время не изменили
                if ((25+d_time.b[3])> d_time.b[4])
                {
                  Minus = true;
                }
              }
            }
          }
          else
          {
            Minus = true;
          }
          
        }
        
      }
    }
    else //WinTime != 0
    {
      /*    if (WinTime > 1)
      {
      WinTime = 1;
    }
      */
      if ((d_time.b[5] >= 3)&&(d_time.b[5] <= 10))
      {
        //Ищем дату перехода
        if (d_time.b[5] == 3)
        {
          //последнее воскресенье марта не может наступить раньше 25 числа
          if (d_time.b[4] >= 25  )
          {
            //Последнее воскресенье месяца
            if (d_time.b[3] == 6)
            {
              //Четыре часа ночи
              if (d_time.b[2] >= 4)
              {
                Plus = true;
              }
            }
            else
            {
              //Если 25+DOW меньше текущей даты, то, значит, воскресенье уже было, а
              //время не изменили
              if ((25+d_time.b[3])< d_time.b[4])
              {
                Plus = true;
              }
            }
            
          }
          
        }
        else //Если в летнее время не переключились еще
        {
          //Если еще рано до даты перехода
          if(d_time.b[5] == 10)
          {
            //До последнего воскресень
            if( d_time.b[4] < 25)
            {
              Plus = true;
            }
            else
            {
              if (d_time.b[3] == 6)
              {//делаем час запаса, чтобы не мельтешило, когда на зимнее время переходим
                if (d_time.b[2] < 3)
                {
                  Plus = true;
                }
              }
              else
              {
                //Если 25+DOW меньше текущей даты, то, значит, воскресенье уже было, а
                //время не изменили
                if ((25+d_time.b[3])> d_time.b[4])
                {
                  Plus = true;
                }
              }
            }
          }
          else
          {
            Plus = true;
          }
          
        }
        
      }
      
    }
    
    if ((Plus != Minus)&&(WinTime <= 1))
    {
      
      if (Minus)
      {
        //Чтобы не переключать еще и дату
        if (d_time.b[2] > 0)
        {
          //На всякий случай, чтобы не попасть на переключение часа
          if (d_time.b[1] < 58)
          {
            //на час назад
            --d_time.b[2];
            WinTime = 1;
            ax = 2 ;
            SummerTime_Label = wt3;
          }
        }
      }
      
      if (Plus)
      {
        //Чтобы не переключать еще и дату
        if (d_time.b[2] < 23)
        {
          //На всякий случай, чтобы не попасть на переключение часа
          if (d_time.b[1] < 58)
          {
            //на час вперед
            ++d_time.b[2];
            WinTime = 0;
            ax = 2;
            SummerTime_Label = wt3;
          }
        }
        
      }
    }
    break;
  case wt2 :
    if ((u)((w)(Timer1_Ovr - Time_WT)) >= _Sec(120) )
    {
      SummerTime_Label = wt0;
      Time_WT = Timer1_Ovr;
    }
    ax = 0;
    break;
  case wt3 :
    
    if ( Mon.i2c_busy != 1 )
    {
      Mon.i2c_busy = 1 ;  // Устанавливаем признак, что теперь шина занята.
      SummerTime_Label = wt4;
    }
    break;
    
  case wt4 :
    
    ax = xSave_into_i2c(2 , (b*)&WinTime , WinTime_addr ,_Adr_Flash_i2c);
    
    // Проверка, закончилась-ли запись блока
    if ( ax != 4 )
    {
      Mon.i2c_busy = 0 ;
      SummerTime_Label = wt2;
      
      if ( ax != 0 )
      {
        // Все остальные значения ах - чтение из i2c неудачно
        ax = 1;  // Возврат 1 - неудачное чтение из i2c
      }
    }
    break;
    
    
  }
  
  return ax ;
}

//---------
// Установка часов на константное время, по внешней команде. ФАА 02.20
//---------
void ExternSynhTime_RTC(byte code,  I2C_time* ptr)   
{
  static I2C_time snh_time;
  static word   trigger_save;
  
  if(code == 0) trigger_save = 0;
  else if (trigger_save == 0 && Write_RTC == 0) // Запись по переднему фронту команды и нет команды записи времени от других программ
  {
    snh_time = *ptr;
    
    snh_time.b[0] = SET_EXTERNAL_SYNH_SECOND;  //перезаписываем секунды
    snh_time.b[1] = SET_EXTERNAL_SYNH_MIN;     //перезаписываем минуты 
    snh_time.b[2] = SET_EXTERNAL_SYNH_HOUR;    //перезаписываем часы
    
    Write_RTC = _ExternSynhWr, trigger_save = 1;
    *ptr = snh_time;
  }
}
