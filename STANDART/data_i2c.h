#ifndef data_i2c_h
#define data_i2c_h

void RW_i2c_data (word code);

//Структура для работы с данными по i2c
struct  rld_i2c
{
  byte   *addr_mem;  //адрес начала массива в памяти
  word   addr_i2c;   //адрес начала массива в i2с
  word   size;       //размер массива
  word   chip_addr;  //адрес микросхемы на шине i2c, в которую будет производится запись
  byte   code ;      //код операции - 1 - запись в i2c
                     // все остальное -   чтение из i2c
};
/*------------------------------------------------*/
#ifdef _MAIN_INCLUDE
/*------------------------------------------------*/
 struct rld_i2c* i2c_str;
 word label_dat;
 byte Write_dat_i2c;

#else  // _MAIN_INCLUDE

extern struct rld_i2c* i2c_str;
extern word label_dat;
extern byte Write_dat_i2c;

#endif // _MAIN_INCLUDE
#endif
