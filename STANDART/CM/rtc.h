#ifndef  _RTC_H
  #define  _RTC_H

/** Clock enable */
#define RTC_CCR_CLKEN			((1<<0))

/** RTC Oscillator Fail detect flag */
#define RTC_AUX_RTC_OSCF		((1<<4))

/** Oscillator Fail Detect interrupt enable*/
#define RTC_AUXEN_RTC_OSCFEN	((1<<4))


typedef union
{
  lword all;
  struct
  {
	 lword  Sec			: 6;
	 lword  res1		: 2;
	 lword  Min			: 6;
	 lword  res2		: 2;
	 lword  Hour		: 5;
	 lword  res3		: 3;
	 lword  DoW			: 3;
	 lword  res4		: 5;
  } _;
} TTime;

typedef union
{
  lword all;
  struct
  {
	 lword  Day			: 5;
	 lword  res1		: 3;
	 lword  Month		: 4;
	 lword  res2		: 4;
	 lword  Year		: 12;
	 lword  res3		: 4;
  } _;
} TDate;

typedef struct
{
  lword	 DoY			: 12;
  lword  res			: 20;
} TDoY;

        //  Определения для часов реального времени.
  #define  _Adr_sec     0
  #define  _Adr_min     1
  #define  _Adr_hour    2
  #define  _Adr_day     3
  #define  _Adr_dat     4
  #define  _Adr_mon     5
  //??? #define  _Adr_Contr   7

typedef struct
{
    byte b[8] ;
/*                   D7...D4         D3...D0
        time.b[0]:   10 seconds       seconds      00-59
        time.b[1]:   10 minutes       minutes      00-59
        time.b[2]:   10 hours          hours      0-1/00-23
        time.b[3]:                     day         01-07
        time.b[4]:   10 date           date        01-31
        time.b[5]:   10 month          month       01-12
        time.b[6]:   10 years          years       00-99
        time.b[7]:   Control Byte
*/
} I2C_time;

struct  Calibr_time
{
  word hours;
  word min;
  word sec;
};
/*
#define Forw_Cal   "Вперед    "
#define Back_Cal   "Назад     "
*/
#define GetTime()           (LPC_RTC->CTIME0)
#define GetDate()	    (LPC_RTC->CTIME1)
#define GetDateOfYear()     (LPC_RTC->CTIME2)

#define _Link_TimeWr  0x1
#define _Int_TimeWr   0x2
#define _ExternSynhWr 0x3
#define _No_WinTime   0x80

#define _byte_DBC_to_DEC(data) ((data&0x0f)+(data>>4)*10)

void RTC_Init( void );
void SetTime( byte Hour, byte Minute, byte Second );
void SetDay(byte Day, byte Month, word Year, byte DayOfWeek, word DayOfYear);
void Write_to_RTC(word code);
word WinterSummer_time(void);
void Calibr_cynch_time(I2C_time* ptr);

extern    word    Read_i2c_time( void ) ;
extern    void    PrintTime ( I2C_time* ptr ) ;
extern    void    xOvr_Time_Schet(I2C_time* ptr);
extern    void    xClock ( I2C_time* ptr);
extern    void    xClock_ust ( I2C_time* ptr);
        // Делаем подмены для совместимости.
#define   Ovr_Time_Schet()    xOvr_Time_Schet( &c_time )
#define   Clock()             xClock( &d_time )
#define   Clock_ust()         xClock_ust( &d_time )
void ExternSynhTime_RTC(byte code,  I2C_time* ptr);

#ifndef _WinTimeOn

#define _WinTimeOn _r.SetWinTime

#endif

//const char *const  cal_Clock[] = { "Час        ","Напрямок" };

// Врея по умолчанию для функции установки время по внешней команде. Ниже пропис.макр.устанавливают время 12:00:00
#ifndef SET_EXTERNAL_SYNH_SECOND
  #define SET_EXTERNAL_SYNH_SECOND  0x00
  #define SET_EXTERNAL_SYNH_MIN     0x00
  #define SET_EXTERNAL_SYNH_HOUR    0x0C
#endif
//Количество скунда в сутках
#define _Sec_in_Day   (24.0*3600.0)
#define _Calibr_Delta_Max  (((6*30)+3)*_Sec_in_Day ) //Количество секунд в 6-ти месяцах (+3 исходя из того, что в 6 месяцах может быть 3 по 31 дню)
#define _Calibr_Delta_Min  ( 3*_Sec_in_Day ) //Количество секунд в 3-х днях(минимум три дня между замерами для точности калибровки)

#ifdef _MAIN_INCLUDE

    //TTime  TimeCurr;
    //TDate  DateCurr;
       word *addr_val;
    word Write_RTC;
    bool RTC_Err @ "RAM_region";
    word WinTime;
    word SummerTime_Label;
  //Время в двоично-десятичной системе
    I2C_time c_time ;
 //Время в обычной системе
    I2C_time d_time ;
    I2C_time l_time ;
    byte Time_label;
    word I2C_Time_Ovr;
    float caltime;
    lword calibr;
    word Time_WT;
    //struct  Calibr_time caltime;
    

#else
extern word Write_RTC;

extern I2C_time c_time ;
extern I2C_time d_time ;
extern I2C_Time_Ovr l_time ;
extern byte Time_label;
extern word I2C_Time_Ovr;
extern float caltime;
extern lword calibr;
extern bool RTC_Err;
extern word WinTime;
extern word SummerTime_Label;
extern word *addr_val;
extern word Time_WT;
//extern struct  Calibr_time caltime;
//extern const char *const  cal_Clock[] ;

#endif

#endif // _RTC_H
