// Инициализация ДЗВ
void init_DZV(void)
{

  DDR2_D26 = 0; // установка направления работы Р26(INT6) - вход
  DDR2_D27 = 0; // установка направления работы Р27(INT7) - вход

// ENIR - Interrupt request enable register
// биты EN0-EN7: 0 - флаг прерывания устанавливается, но запрос в ICR не осуществляется
//               1 - запрос в ICR
  ENIR_EN6 = 0;
  ENIR_EN7 = 0;

/*
  уровни срабатывания прерывания
  0 - нижний уровень
  1 - верхний уровень
  2 - передний фронт
  3 - задний фронт
*/
  ELVR_LALB6 = _DZVA_Ok_level; // установка уровня срабатывания прерывания для INT6
  ELVR_LALB7 = _DZVK_Ok_level; // установка уровня срабатывания прерывания для INT7

  Clr_DZV() ;
  //EIRR_ER6 = 0; // сброс флага прерывания по INT6
  //EIRR_ER7 = 0; // сброс флага прерывания по INT7
}

// состояние ДЗВ А
// если сработало ДЗВ, то сбрасываем флаг и возвращаем 1
byte DZVA_Ok(void)
{
  register byte ah;

  ah = EIRR_ER6;
  if ( ah ) EIRR_ER6 = 0;
  return ah;
}

// состояние ДЗВ К
// если сработало ДЗВ, то сбрасываем флаг и возвращаем 1
byte DZVK_Ok(void)
{
  register byte ah;

  ah = EIRR_ER7;
  if ( ah ) EIRR_ER7 = 0;
  return ah;
}

// сброс всех ДЗВ
// сбрасываем флаги для INT6, INT7
void Clr_DZV(void)
{
  EIRR_ER6 = 0;
  EIRR_ER7 = 0;
}

// сброс ДЗВ А
// сбрасываем флаг для INT6
void Clr_DZVA(void)
{
  EIRR_ER6 = 0;
}

// сброс ДЗВ К
// сбрасываем флаг для INT7
void Clr_DZVK(void)
{
  EIRR_ER7 = 0;
}
