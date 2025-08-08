#ifndef data_i2c_h
#define data_i2c_h

void RW_i2c_data (word code);

//��������� ��� ������ � ������� �� i2c
struct  rld_i2c
{
  byte   *addr_mem;  //����� ������ ������� � ������
  word   addr_i2c;   //����� ������ ������� � i2�
  word   size;       //������ �������
  word   chip_addr;  //����� ���������� �� ���� i2c, � ������� ����� ������������ ������
  byte   code ;      //��� �������� - 1 - ������ � i2c
                     // ��� ��������� -   ������ �� i2c
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
