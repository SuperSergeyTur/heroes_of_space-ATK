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
  word second ; // �������
  word minute ; // ������
  word hour   ;   // ����
  
  word dateNum; // �����
  word month  ;  // �����
  word year   ;   // ���
  if (BCD_on)
  {
    // �������������� BCD � ���������� ��������
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
  // ��������� ����, ���� ����������� ������� �� ������ �����
  if (adjustForDST && isDST(year, month, dateNum, hour)) {
    hour -= 1; // ������ �����: ��� ��������� �� 1
  }
  
  // ���������� ������� � ���� ����� ������� ����� � ������� �����
  daysDiff = calculateDaysSinceReference(year, month, dateNum);
  
  // ���������� ������ ���������� ������
  totalSeconds = daysDiff * 86400L; // ������ � ���
  totalSeconds += hour * 3600L;         // ������ � ����
  totalSeconds += minute * 60L;         // ������ � ������
  totalSeconds += second;               // �������
  
  return totalSeconds;
}


// ����� ��� �������������� BCD � ���������� �����
word DateConverter::bcdToDec(uint8_t bcd) 
{
  return (bcd >> 4) * 10 + (bcd & 0x0F);
}

// ����� ��� ��������, �������� �� ��� ����������
bool DateConverter::isLeapYear(word year) 
{
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// ����� ��� ���������� ���������� ���� � ������
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

//��������� ���������� ����, ��������� � ������� ����.   
lword DateConverter::calculateDaysSinceReference(word year, word month, word day) 
{
  lword days = 0;
  
  // ���� ��� ��������� � �������, ������� ������ ��� � ������� ����
  if (year == refYear) {
    for (word m = refMonth; m < month; ++m) {
      days += daysInMonth(m, year);
    }
    days += day - refDay;
  } else {
    // ��������� ��� �� ����� �������� ����
    for (word m = refMonth; m <= 12; ++m) {
      days += daysInMonth(m, refYear);
    }
    days -= refDay;
    
    // ��������� ��� �� ������ ���� ����� ������� � ������� �����
    for (word y = refYear + 1; y < year; ++y) {
      days += isLeapYear(y) ? 366 : 365;
    }
    
    // ��������� ��� � ������� ����
    for (word m = 1; m < month; ++m) {
      days += daysInMonth(m, year);
    }
    days += day;
  }
  
  return days;
}

// ���������� ���� ���������� ����������� � ��������� ������ � ����.
word DateConverter::getLastSunday(word month, word year) 
{
    // ������������� ��� ������ � �������
    if (month < 3) {
        month += 12;
        year -= 1;
    }

    // ��������� ���� ������ ��� ������� ��� ������ (�������� �������)
    // ���� ������ (0 = �������, 1 = �����������, ..., 6 = �������)
    word h = (1 + (13 * (month + 1)) / 5 + year + year / 4 - year / 100 + year / 400)%7;
    

    // ����������� � ������� 0 = �����������, 1 = �����������, ..., 6 = �������
    word firstDayOfWeek = (h + 5) % 7;

    // ��������� ���� ���������� �����������
    word days = daysInMonth(month > 12 ? month - 12 : month, year + (month > 12 ? 1 : 0));
    return days - ((firstDayOfWeek + days - 1) % 7);
}

//���������, ��������� �� ������ ����� ��� ��������� ���� � ����.
bool DateConverter::isDST(word year, word month, word day, word hour)
{
  // ������ ����� ���������� � ��������� ����������� ����� � ������������� � ��������� ����������� �������.
  if (month < 3 || month > 10) return false; // ������ �����
  if (month > 3 && month < 10) return true;  // ������ �����
  
  // ��� ����� � ������� ��������� ���������� ����
  if (month == 3) {
    // ������ ����� ���������� � ��������� ����������� �����
    int lastSunday = getLastSunday(3, year);
    if (day > lastSunday || (day == lastSunday && hour >= 2)) {
      return true;
    }
  } else if (month == 10) {
    // ������ ����� ������������� � ��������� ����������� �������
    int lastSunday = getLastSunday(10, year);
    if (day < lastSunday || (day == lastSunday && hour < 3)) {
      return true;
    }
  }
  
  return false;
  
}
