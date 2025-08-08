#include <types.h>
#include <DateConvert.h>

/*                   D7...D4         D3...D0
b[0]:   10 seconds       seconds      00-59
b[1]:   10 minutes       minutes      00-59
b[2]:   10 hours          hours      0-1/00-23
b[3]:                     day         01-07
b[4]:   10 date           date        01-31
b[5]:   10 month          month       01-12
b[6]:   10 years          years       00-99
b[7]:   Control Byte
*/


lword DateConverter::secondsSinceReferenceDate(I2C_time* ptr, bool adjustForDST, bool BCD_on) 
{
  lword totalSeconds;
  lword daysDiff;
  word second ; // Секунды
  word minute ; // Минуты
  word hour   ;   // Часы
  
  word dateNum; // Число
  word month  ;  // Месяц
  word year   ;   // Год
  if (BCD_on)
  {
    // Преобразование BCD в десятичные значения
    second = bcdToDec(ptr->b[0]); 
    minute = bcdToDec(ptr->b[1]); 
    hour = bcdToDec(ptr->b[2]);           
    dateNum = bcdToDec(ptr->b[4]);
    month = bcdToDec(ptr->b[5]);  
    year = bcdToDec(ptr->b[6]);   
    
  }
  else
  {
    second  = ptr->b[0]; 
    minute  = ptr->b[1]; 
    hour    = ptr->b[2];       
    dateNum = ptr->b[4];
    month   = ptr->b[5];  
    year    = ptr->b[6];       
  }
  // Коррекция часа, если учитывается переход на летнее время
  if (adjustForDST && isDST(year, month, dateNum, hour)) {
    hour -= 1; // Летнее время: час уменьшаем на 1
  }
  
  // Вычисление разницы в днях между текущей датой и опорной датой
  daysDiff = calculateDaysSinceReference(year, month, dateNum);
  
  // Вычисление общего количества секунд
  totalSeconds = daysDiff * 86400L; // Секунд в дне
  totalSeconds += hour * 3600L;         // Секунд в часе
  totalSeconds += minute * 60L;         // Секунд в минуте
  totalSeconds += second;               // Секунды
  
  return totalSeconds;
}


// Метод для преобразования BCD в десятичное число
word DateConverter::bcdToDec(uint8_t bcd) 
{
  return (bcd >> 4) * 10 + (bcd & 0x0F);
}

// Метод для проверки, является ли год високосным
bool DateConverter::isLeapYear(word year) 
{
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Метод для вычисления количества дней в месяце
word DateConverter::daysInMonth(word month, word year) 
{
  if (month == 2) {
    return isLeapYear(year) ? 29 : 28;
  } else if (month == 4 || month == 6 || month == 9 || month == 11) {
    return 30;
  } else {
    return 31;
  }
}

//Вычисляет количество дней, прошедших с опорной даты.   
lword DateConverter::calculateDaysSinceReference(word year, word month, word day) 
{
  lword days = 0;
  
  // Если год совпадает с опорным, считаем только дни в текущем году
  if (year == refYear) {
    for (word m = refMonth; m < month; ++m) {
      days += daysInMonth(m, year);
    }
    days += day - refDay;
  } else {
    // Добавляем дни до конца опорного года
    for (word m = refMonth; m <= 12; ++m) {
      days += daysInMonth(m, refYear);
    }
    days -= refDay;
    
    // Добавляем дни за полные годы между опорным и текущим годом
    for (word y = refYear + 1; y < year; ++y) {
      days += isLeapYear(y) ? 366 : 365;
    }
    
    // Добавляем дни в текущем году
    for (word m = 1; m < month; ++m) {
      days += daysInMonth(m, year);
    }
    days += day;
  }
  
  return days;
}

// Возвращает день последнего воскресенья в указанном месяце и году.
word DateConverter::getLastSunday(word month, word year) 
{
    // Корректировка для января и февраля
    if (month < 3) {
        month += 12;
        year -= 1;
    }

    // Вычисляем день недели для первого дня месяца (алгоритм Зеллера)
    // День недели (0 = суббота, 1 = воскресенье, ..., 6 = пятница)
    word h = (1 + (13 * (month + 1)) / 5 + year + year / 4 - year / 100 + year / 400)%7;
    

    // Преобразуем к формату 0 = воскресенье, 1 = понедельник, ..., 6 = суббота
    word firstDayOfWeek = (h + 5) % 7;

    // Вычисляем день последнего воскресенья
    word days = daysInMonth(month > 12 ? month - 12 : month, year + (month > 12 ? 1 : 0));
    return days - ((firstDayOfWeek + days - 1) % 7);
}

//Проверяет, действует ли летнее время для указанной даты и часа.
bool DateConverter::isDST(word year, word month, word day, word hour)
{
  // Летнее время начинается в последнее воскресенье марта и заканчивается в последнее воскресенье октября.
  if (month < 3 || month > 10) return false; // Зимнее время
  if (month > 3 && month < 10) return true;  // Летнее время
  
  // Для марта и октября проверяем конкретные даты
  if (month == 3) {
    // Летнее время начинается в последнее воскресенье марта
    int lastSunday = getLastSunday(3, year);
    if (day > lastSunday || (day == lastSunday && hour >= 2)) {
      return true;
    }
  } else if (month == 10) {
    // Летнее время заканчивается в последнее воскресенье октября
    int lastSunday = getLastSunday(10, year);
    if (day < lastSunday || (day == lastSunday && hour < 3)) {
      return true;
    }
  }
  
  return false;
  
}
