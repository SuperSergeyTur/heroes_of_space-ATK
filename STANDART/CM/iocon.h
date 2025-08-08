#ifndef  _IOCON_H
  #define  _IOCON_H


//-----------   Тип порта D   ------------------------
// 2..0 = функция пина
// 4..3 = наличие резистора подтяжки
#define D_MODE_INACTIVE		    (0x00)
#define D_MODE_PULLDOWN         (0x01<<3)
#define D_MODE_PULLUP           (0x02<<3)
#define D_MODE_REPEATER         (0x03<<3)
// 5 = гистерезис
#define D_HYS_DIS				(0x00)
#define D_HYS_EN				(0x01<<5)
// 6 = инверсия входа
#define D_INV_DIS				(0x00)
#define D_INV_EN				(0x01<<6)
// 8..7 = резерв
// 9 = медленный выход
#define D_SLEW_STANDART			(0x00)
#define D_SLEW_FAST				(0x01<<9)
// 10 = выход ОК
#define D_OD_DIS				(0x00)
#define D_OD_EN					(0x01<<10)
// 31..11 = резерв
#define D_RESERV				(0x00000000)
//----------------------------------------------------

//-----------   Тип порта А   ------------------------
// 2..0 = функция пина
// 4..3 = наличие резистора подтяжки
#define A_MODE_INACTIVE		    (0x00)
#define A_MODE_PULLDOWN         (0x01<<3)
#define A_MODE_PULLUP           (0x02<<3)
#define A_MODE_REPEATER         (0x03<<3)
// 5 = резерв
// 6 = инверсия входа
#define A_INV_DIS				(0x00)
#define A_INV_EN				(0x01<<6)
// 7 = выбор режима аналоговый/цифровой
#define A_ADMODE_AM				(0x00)
#define A_ADMODE_DM				(0x01<<7)
// 8 = входной фильтр 10нс
#define A_FILTER_EN				(0x00)
#define A_FILTER_DIS	  		(0x01<<8)
// 9 = резерв
// 10 = выход ОК
#define A_OD_DIS				(0x00)
#define A_OD_EN					(0x01<<10)
// 15..11 = резерв
// 16 = включение ЦАП
#define A_DAC_DIS				(0x00)
#define A_DAC_EN 				(0x01<<16)
// 31..17 = резерв
#define A_RESERV				(0x00000000)
//----------------------------------------------------

//-----------   Тип порта U   ------------------------
// 2..0 = функция пина
// 31..3 = резерв
#define U_RESERV				(0x00000000)
//----------------------------------------------------

//-----------   Тип порта I   ------------------------
// 2..0 = функция пина
// 5..3 = резерв
// 6 = инверсия входа
#define I_INV_DIS				(0x00)
#define I_INV_EN				(0x01<<6)
// 7 = резерв
// 8 = режим работы I2C (включение входного фильтра 50нс и контроля скорости нарастания )
#define I_HS_EN					(0x00)
#define I_HS_DIS	  			(0x01<<8)
// 9 = управление выходным током 4мА (режимы Sandart и Fast) или 20мА (режим Fast+)
#define I_HD_DIS				(0x00)
#define I_HD_EN					(0x01<<9)
// 31..10 = резерв
#define I_RESERV				(0x00000000)
//----------------------------------------------------

//-----------   Тип порта W   ------------------------
// 2..0 = функция пина
// 4..3 = наличие резистора подтяжки
#define W_MODE_INACTIVE		    (0x00)
#define W_MODE_PULLDOWN         (0x01<<3)
#define W_MODE_PULLUP           (0x02<<3)
#define W_MODE_REPEATER         (0x03<<3)
// 5 = гистерезис
#define W_HYS_DIS				(0x00)
#define W_HYS_EN				(0x01<<5)
// 6 = инверсия входа
#define W_INV_DIS				(0x00)
#define W_INV_EN				(0x01<<6)
// 7 = резерв должен быть = 1
#define W_RESERV                (0x01<<7)
// 8 = входной фильтр 10нс
#define W_FILTER_EN				(0x00)
#define W_FILTER_DIS	  		(0x01<<8)
// 9 = медленный выход
#define W_SLEW_STANDART			(0x00)
#define W_SLEW_FAST				(0x01<<9)
// 10 = выход ОК
#define W_OD_DIS				(0x00)
#define W_OD_EN					(0x01<<10)
// 31..11 = резерв
//----------------------------------------------------

#endif // _IOCON_H


