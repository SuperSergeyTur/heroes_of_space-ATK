#ifndef _DZV_h
#define _DZV_h

/*
  уровни срабатывания прерывания
  0 - нижний уровень
  1 - верхний уровень
  2 - передний фронт
  3 - задний фронт
*/
#define _DZVA_Ok_level 0
#define _DZVK_Ok_level 0
#define _DZVA2_Ok_level 0
#define _DZVK2_Ok_level 0

void init_DZV(void);
void init_DZV2(void);

byte DZVA_Ok(void);
byte DZVA_Ok2(void);

byte DZVK_Ok(void);
byte DZVK_Ok2(void);

void Clr_DZV(void);
void Clr_DZV2(void);

void Clr_DZVA(void);
void Clr_DZVA2(void);

void Clr_DZVK(void);
void Clr_DZVK2(void);

#endif
