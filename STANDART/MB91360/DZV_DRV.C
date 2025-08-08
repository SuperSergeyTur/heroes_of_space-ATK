#ifndef _dzv_drv_c
#define _dzv_drv_c

void init_DZV(void)
{

  DDRK_DDK2 = 0; // установка направления работы РK2(INT2) - вход
  DDRK_DDK3 = 0; // установка направления работы РK3(INT3) - вход

// ENIR - Interrupt request enable register
// биты EN0-EN7: 0 - флаг прерывания устанавливается, но запрос в ICR не осуществляется
//               1 - запрос в ICR
  ENIR_EN2 = 0;
  ENIR_EN3 = 0;

/*
  уровни срабатывания прерывания
  0 - нижний уровень
  1 - верхний уровень
  2 - передний фронт
  3 - задний фронт
*/
  ELVR_LAB2 = _DZVA_Ok_level; // установка уровня срабатывания прерывания для INT4
  ELVR_LAB3 = _DZVK_Ok_level; // установка уровня срабатывания прерывания для INT5

  Clr_DZV() ;
}
//***************

void init_DZV2(void)
{

  DDRK_DDK4 = 0; // установка направления работы РK4(INT4) - вход
  DDRK_DDK5 = 0; // установка направления работы РK5(INT5) - вход

// ENIR - Interrupt request enable register
// биты EN0-EN7: 0 - флаг прерывания устанавливается, но запрос в ICR не осуществляется
//               1 - запрос в ICR
  ENIR_EN4 = 0;
  ENIR_EN5 = 0;

/*
  уровни срабатывания прерывания
  0 - нижний уровень
  1 - верхний уровень
  2 - передний фронт
  3 - задний фронт
*/
  ELVR_LAB4 = _DZVA2_Ok_level; // установка уровня срабатывания прерывания для INT4
  ELVR_LAB5 = _DZVK2_Ok_level; // установка уровня срабатывания прерывания для INT5

  Clr_DZV2() ;
}

// состояние ДЗВ А
// если сработало ДЗВ, то сбрасываем флаг и возвращаем 1
byte DZVA_Ok(void)
{
  register byte ah;
  ah = 0 ;
  ah = EIRR_ER2;
  if ( ah ) EIRR_ER2 = 0;
  return ah;
}
byte DZVA2_Ok(void)
{
  register byte ah;
  ah = 0 ;
  ah = EIRR_ER4;
  if ( ah ) EIRR_ER4 = 0;
  return ah;
}

// состояние ДЗВ К
// если сработало ДЗВ, то сбрасываем флаг и возвращаем 1
byte DZVK_Ok(void)
{
  register byte ah;
  ah = 0 ;
  ah = EIRR_ER3;
  if ( ah ) EIRR_ER3 = 0;
  return ah;
}
byte DZVK2_Ok(void)
{
  register byte ah;
  ah = 0 ;
  ah = EIRR_ER5;
  if ( ah ) EIRR_ER5 = 0;
  return ah;
}

// сброс всех ДЗВ
// сбрасываем флаги для INT4, INT5
void Clr_DZV(void)
{
  EIRR_ER2 = 0;
  EIRR_ER3 = 0;
}

void Clr_DZV2(void)
{
  EIRR_ER4 = 0;
  EIRR_ER5 = 0;
}

// сброс ДЗВ А
// сбрасываем флаг для INT5
void Clr_DZVA(void)   { EIRR_ER2 = 0; }
void Clr_DZVA2(void)  { EIRR_ER4 = 0; }

// сброс ДЗВ К
// сбрасываем флаг для INT4
void Clr_DZVK(void)   { EIRR_ER3 = 0; }
void Clr_DZVK2(void)  { EIRR_ER5 = 0; }

#endif
