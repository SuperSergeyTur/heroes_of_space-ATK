#ifndef _sred
#define _sred


//–абоча€ структура дл€ усреднител€
typedef struct 
{
  word* out; //¬ыходное значение
  word in;  //¬ыходное значение(измер€емое)
  word n;   //„исло измерений
  word time; //¬рем€ последнего расчета среднего значени€
  word dT;   //ѕромежуток, за который проводитс€ усреднение
  word time1;
  word label;
  lword sum;  //—умма измеренных значений
  word mod;   //установленный в 1 обозначает, что мы проводим усреднение модул€
  struct Channel_AD* ach ; //јдрес аналогового канала усредн€емой величины
} Usrednit_Str;
/*#ifdef _MAIN_INCLUDE


#else


#endif*/
void Usrednitel( Usrednit_Str  *usr, byte label);

#endif
