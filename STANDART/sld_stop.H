#ifndef _sled_stop_h
#define _sled_stop_h


//Шаблон структуры для задания переменной пуска/остановки следа
struct sled_cond
{
  word numb ; //номер переменной в таблице следа
  word mean ; //значение, относительно которого надо плясать
  union
  {
    word all;
    struct
    {
#ifndef _Union_FR

      word bit    :4;                   // номер бита в слове

      word cond   :2;                   // условие: больше - 2, меньше - 1, равно - 0
      word enable :1;                   //  включение функции.
      word type   :1;                   // Тип - битовый - 1 или аналоговый - 0

      word old    :1;
#else

      word rezerv :7;
      word old    :1;

      word type   :1;                   // Тип - битовый - 1 или аналоговый - 0
      word enable :1;                   //  включение функции.
      word cond   :2;                   // условие: больше - 2, меньше - 1, равно - 0

      word bit    :4;                   // номер бита в слове

#endif
    }_;
  }bits;
};

//#define _Scond_prompt    "\r\nСлед:условия "
#define _Scond_prompt      "\r\nРегiстр.:умови"

void Cond_Sled_Stop (void);
void Cond_Sled_Start (void);
word Sled_Cond_cont (struct sled_cond* in);
void Sled_Cond_sel (void);
word Key_tst(word min, word max, word lab, word inv);



#ifdef _SLED_CONDITION_INCLUDE

const char *Sld_Start_Stop[2] = { _sldStop,
                                  _sldStart };
const char *Sld_Name[8] =
{
  _sldParameter  ,
  _sldType       ,
  _sldBitNumber  ,
  _sldCondition  ,
  _sldValue      ,
  _sldDelay      ,
  _sldFilterTime ,
  _sldOnCondition
};
const char *Sld_type[2] =
{
  _sldAnal,
  _sldBit
};
const char *Sld_en[2] =
{
  _sldOff,
  _sldOn
};

const char *Sld_cond[3] =
{
  _sldEquals,
  _sldLess  ,
  _sldMore
};

struct sled_cond *adr_m_tmp;
word *adr_t_delay, *adr_f_delay, *adr_delay;
word TimeDelay_Start, TimeDelay_Stop;
word TimeFiltr_Start, TimeFiltr_Stop;
//struct sled_cond Start_cond;
//struct sled_cond Stop_cond;
word sld_max,sld_min, sl_cond_old;
#else
extern word sld_max,sld_min, sl_cond_old; ;
extern word TimeDelay_Start, TimeDelay_Stop;
extern word TimeFiltr_Start, TimeFiltr_Stop;
extern const char *Sld_Start_Stop[];
extern struct sled_cond *adr_m_tmp;
extern const char *Sld_Name[];
extern const char *Sld_type[];
extern const char *Sld_cond[];
extern const char *Sld_en[];
extern word *adr_t_delay, *adr_f_delay, *adr_delay;

//extern struct sled_cond Start_cond;
//extern struct sled_cond Stop_cond;


#endif
#endif
