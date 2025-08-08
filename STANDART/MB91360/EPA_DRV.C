
#include "include.h"

      //   Если надо настроить capture-EPA под какую-то новуюфункцию.
      //  то следует добавить в этот файл новую функцию со своим именем и
      //  соответствующими настройками.

      //   Настройка заданного канала capture-EPA под прием
      //  синхронизации.
word init_syn_epa( word channel )
{
  if     ( channel == _ICS0 ) ICS01 |= _CAP0_NEG_EDGE ;
  else if( channel == _ICS1 ) ICS01 |= _CAP1_NEG_EDGE ;
  else if( channel == _ICS2 ) ICS23 |= _CAP2_NEG_EDGE ;
  else if( channel == _ICS3 ) ICS23 |= _CAP3_NEG_EDGE ;
  return 0 ;
}

      //   Разрешение прерывания по ЕПА.
void ei_syn_epa( word channel )
{
  if( channel == _ICS0 )
  {   // сбрасываем запрос по ЕПА
     ICS01_ICP0 = 0 ;
      // разрешаем прерывания ЕПА.
     ICS01_ICE0 = 1 ;
     ICR26 = _ICS01_PRIORITY ; // приоритет.
  }
  else if( channel == _ICS1 )
  {
    ICS01_ICP1 = 0 ;
    ICS01_ICE1 = 1 ;
    ICR26 = _ICS01_PRIORITY ; // приоритет.
  }
  else if( channel == _ICS2 )
  {
    ICS23_ICP2 = 0 ;
    ICS23_ICE2 = 1 ;
    ICR28 = _ICS23_PRIORITY ; // приоритет.
  }
  else if( channel == _ICS3 )
  {
    ICS23_ICP3 = 0 ;
    ICS23_ICE3 = 1 ;
    ICR28 = _ICS23_PRIORITY ; // приоритет.
  }
  asm_ei();

  return ;
}
            // Сброс запроса прерывания.
void Syn_int_drv( word channel )//, word code )
{
      // сбрасываем запрос по ЕПА
  if     ( channel == _ICS0 )  ICS01_ICP0 = 0 ;
  else if( channel == _ICS1 )  ICS01_ICP1 = 0 ;
  else if( channel == _ICS2 )  ICS23_ICP2 = 0 ;
  else if( channel == _ICS3 )  ICS23_ICP3 = 0 ;
  return ;
}


      //   Настройка заданного канала compare-EPA под CИФУ.
word init_sifu_epa( word channel )
{
  if( channel == _OCS0 )
  {                   //  С/без выдачей стробов на выход ЕПА.
    //OCS01_CMOD = 0, OCS01_OTE0 = 1, OCS01_OTD0 = 1 ;
    OCS01_CMOD = 0, /*OCS01_OTE0 = 0,*/ OCS01_OTD0 = 0 ;
      // сбрасываем запрос по ЕПА
    OCS01_ICP0 = 0 ;
      // разрешаем прерывания ЕПА.
    OCS01_ICE0 = 1 ;
    ICR27 = _OCS01_PRIORITY ; // приоритет.
      // запускаем ЕПА
    OCS01_CST0 = 1 ;
    asm_ei();
  }
  else if( channel == _OCS1 )
  {                   //  С/без выдачей стробов на выход ЕПА.
    //OCS01_CMOD = 0, OCS01_OTE1 = 1, OCS01_OTD1 = 1 ;
    OCS01_CMOD = 0, /*OCS01_OTE1 = 0,*/ OCS01_OTD1 = 0 ;
      // сбрасываем запрос по ЕПА
    OCS01_ICP1 = 0 ;
      // разрешаем прерывания ЕПА.
    OCS01_ICE1 = 1 ;
    ICR27 = _OCS01_PRIORITY ; // приоритет.
      // запускаем ЕПА
    OCS01_CST1 = 1 ;
    asm_ei();
  }
  else if( channel == _OCS2 )
  {                   //  С/без выдачей стробов на выход ЕПА.
    //OCS23_CMOD = 0, OCS23_OTE2 = 1, OCS23_OTD2 = 1 ;
    OCS23_CMOD = 0,/*OCS23_OTE2 = 0,*/ OCS23_OTD2 = 0 ;
      // сбрасываем запрос по ЕПА
    OCS23_ICP2 = 0 ;
      // разрешаем прерывания ЕПА.
    OCS23_ICE2 = 1 ;
    ICR29 = _OCS23_PRIORITY ; // приоритет.
      // запускаем ЕПА
    OCS23_CST2 = 1 ;
    asm_ei();
  }
  else if( channel == _OCS3 )
  {                   //  С/без выдачей стробов на выход ЕПА.
    //OCS23_CMOD = 0, OCS23_OTE3 = 1, OCS23_OTD3 = 1 ;
    OCS23_CMOD = 0,/*OCS23_OTE3 = 0,*/ OCS23_OTD3 = 0 ;
      // сбрасываем запрос по ЕПА
    OCS23_ICP3 = 0 ;
      // разрешаем прерывания ЕПА.
    OCS23_ICE3 = 1 ;

    ICR29 = _OCS23_PRIORITY ; // приоритет.
      // запускаем ЕПА
    OCS23_CST3 = 1 ;
    asm_ei();
  }
  return 0 ;
}


            // Сброс запроса прерывания.
void Sifu_int_drv( word channel )//, word code )
{
      // сбрасываем запрос по ЕПА
  if     ( channel == _OCS0 )  OCS01_ICP0 = 0 ;
  else if( channel == _OCS1 )  OCS01_ICP1 = 0 ;
  else if( channel == _OCS2 )  OCS23_ICP2 = 0 ;
  else if( channel == _OCS3 )  OCS23_ICP3 = 0 ;/*, OCS23_OTD3 = 1 ;*/
  return ;
}


// Отключение прирывания СИФУ .
// 10.09.2015 - Проверено на 12-пульсных КТЭ (Мариуполь/Шандро и Xарьков/Электротяжмаш).
word off_sifu_epa( word channel )
{
  if( channel == _OCS0 )
  {                   //  С/без выдачей стробов на выход ЕПА.
    //OCS01_CMOD = 0, OCS01_OTE0 = 1, OCS01_OTD0 = 1 ;
    OCS01_CMOD = 0, /*OCS01_OTE0 = 0,*/ OCS01_OTD0 = 0 ;
      // сбрасываем запрос по ЕПА
    OCS01_ICP0 = 0 ;
      // запрещаем прерывания ЕПА.
    OCS01_ICE0 = 0 ;
    //ICR27 = _OCS01_PRIORITY ; // приоритет.
      // отключаем ЕПА
    OCS01_CST0 = 0 ;
    asm_ei();
  }
  else if( channel == _OCS1 )
  {                   //  С/без выдачей стробов на выход ЕПА.
    //OCS01_CMOD = 0, OCS01_OTE1 = 1, OCS01_OTD1 = 1 ;
    OCS01_CMOD = 0, /*OCS01_OTE1 = 0,*/ OCS01_OTD1 = 0 ;
      // сбрасываем запрос по ЕПА
    OCS01_ICP1 = 0 ;
      // запрещаем прерывания ЕПА.
    OCS01_ICE1 = 0 ;
    //ICR27 = _OCS01_PRIORITY ; // приоритет.
      // запускаем ЕПА
    OCS01_CST1 = 0 ;
    asm_ei();
  }
  else if( channel == _OCS2 )
  {                   //  С/без выдачей стробов на выход ЕПА.
    //OCS23_CMOD = 0, OCS23_OTE2 = 1, OCS23_OTD2 = 1 ;
    OCS23 = 0x0; /*OCS23_OTE2 = 0,/ OCS23_OTD2 = 0 ;
      // сбрасываем запрос по ЕПА
    OCS23_ICP2 = 0 ;
      // запрещаем прерывания ЕПА.
    OCS23_ICE2 = 1 ;*/
    ICR29 = _OCS23_PRIORITY ; // приоритет.
      // запускаем ЕПА
    //OCS23_CST2 = 1 ;
    asm_ei();
  }
  else if( channel == _OCS3 )
  {                   //  С/без выдачей стробов на выход ЕПА.
    //OCS23_CMOD = 0, OCS23_OTE3 = 1, OCS23_OTD3 = 1 ;
    OCS23 = 0x0 , /*OCS23_OTE3 = 0, OCS23_OTD3 = 0 ;
      // сбрасываем запрос по ЕПА
    OCS23_ICP3 = 0 ;
      // запрещаем прерывания ЕПА.
    OCS23_ICE3 = 1 ;*/

    ICR29 = _OCS23_PRIORITY ; // приоритет.
      // запускаем ЕПА
 //   OCS23_CST3 = 1 ;
    asm_ei();
  }
  return 0 ;
}
