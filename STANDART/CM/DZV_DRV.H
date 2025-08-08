#ifndef _DZV_h
#define _DZV_h

#define _DZVA_Ok_level  1
#define _DZVK_Ok_level  1
#define _DZVA2_Ok_level 1
#define _DZVK2_Ok_level 1
  //那吕  INT5, P0-19
  //那率  INT6, P0-20
  //那吕  INT4, P2-15
  //那率  INT3, P2-13

#define _DZVA_Port      0
#define _DZVK_Port      0
#define _DZVA2_Port     2
#define _DZVK2_Port     2

#define _DZVA_Bit       19
#define _DZVK_Bit       20
#define _DZVA2_Bit      15
#define _DZVK2_Bit      13


void init_DZV(void);
void init_DZV2(void);

byte DZVA_Ok(void);
byte DZVA2_Ok(void);

byte DZVK_Ok(void);
byte DZVK2_Ok(void);

void Clr_DZV(void);
void Clr_DZV2(void);

void Clr_DZVA(void);
void Clr_DZVA2(void);

void Clr_DZVK(void);
void Clr_DZVK2(void);

byte dzva1, dzvk1, dzva2, dzvk2;
#endif
