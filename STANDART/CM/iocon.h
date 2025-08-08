#ifndef  _IOCON_H
  #define  _IOCON_H


//-----------   ��� ����� D   ------------------------
// 2..0 = ������� ����
// 4..3 = ������� ��������� ��������
#define D_MODE_INACTIVE		    (0x00)
#define D_MODE_PULLDOWN         (0x01<<3)
#define D_MODE_PULLUP           (0x02<<3)
#define D_MODE_REPEATER         (0x03<<3)
// 5 = ����������
#define D_HYS_DIS				(0x00)
#define D_HYS_EN				(0x01<<5)
// 6 = �������� �����
#define D_INV_DIS				(0x00)
#define D_INV_EN				(0x01<<6)
// 8..7 = ������
// 9 = ��������� �����
#define D_SLEW_STANDART			(0x00)
#define D_SLEW_FAST				(0x01<<9)
// 10 = ����� ��
#define D_OD_DIS				(0x00)
#define D_OD_EN					(0x01<<10)
// 31..11 = ������
#define D_RESERV				(0x00000000)
//----------------------------------------------------

//-----------   ��� ����� �   ------------------------
// 2..0 = ������� ����
// 4..3 = ������� ��������� ��������
#define A_MODE_INACTIVE		    (0x00)
#define A_MODE_PULLDOWN         (0x01<<3)
#define A_MODE_PULLUP           (0x02<<3)
#define A_MODE_REPEATER         (0x03<<3)
// 5 = ������
// 6 = �������� �����
#define A_INV_DIS				(0x00)
#define A_INV_EN				(0x01<<6)
// 7 = ����� ������ ����������/��������
#define A_ADMODE_AM				(0x00)
#define A_ADMODE_DM				(0x01<<7)
// 8 = ������� ������ 10��
#define A_FILTER_EN				(0x00)
#define A_FILTER_DIS	  		(0x01<<8)
// 9 = ������
// 10 = ����� ��
#define A_OD_DIS				(0x00)
#define A_OD_EN					(0x01<<10)
// 15..11 = ������
// 16 = ��������� ���
#define A_DAC_DIS				(0x00)
#define A_DAC_EN 				(0x01<<16)
// 31..17 = ������
#define A_RESERV				(0x00000000)
//----------------------------------------------------

//-----------   ��� ����� U   ------------------------
// 2..0 = ������� ����
// 31..3 = ������
#define U_RESERV				(0x00000000)
//----------------------------------------------------

//-----------   ��� ����� I   ------------------------
// 2..0 = ������� ����
// 5..3 = ������
// 6 = �������� �����
#define I_INV_DIS				(0x00)
#define I_INV_EN				(0x01<<6)
// 7 = ������
// 8 = ����� ������ I2C (��������� �������� ������� 50�� � �������� �������� ���������� )
#define I_HS_EN					(0x00)
#define I_HS_DIS	  			(0x01<<8)
// 9 = ���������� �������� ����� 4�� (������ Sandart � Fast) ��� 20�� (����� Fast+)
#define I_HD_DIS				(0x00)
#define I_HD_EN					(0x01<<9)
// 31..10 = ������
#define I_RESERV				(0x00000000)
//----------------------------------------------------

//-----------   ��� ����� W   ------------------------
// 2..0 = ������� ����
// 4..3 = ������� ��������� ��������
#define W_MODE_INACTIVE		    (0x00)
#define W_MODE_PULLDOWN         (0x01<<3)
#define W_MODE_PULLUP           (0x02<<3)
#define W_MODE_REPEATER         (0x03<<3)
// 5 = ����������
#define W_HYS_DIS				(0x00)
#define W_HYS_EN				(0x01<<5)
// 6 = �������� �����
#define W_INV_DIS				(0x00)
#define W_INV_EN				(0x01<<6)
// 7 = ������ ������ ���� = 1
#define W_RESERV                (0x01<<7)
// 8 = ������� ������ 10��
#define W_FILTER_EN				(0x00)
#define W_FILTER_DIS	  		(0x01<<8)
// 9 = ��������� �����
#define W_SLEW_STANDART			(0x00)
#define W_SLEW_FAST				(0x01<<9)
// 10 = ����� ��
#define W_OD_DIS				(0x00)
#define W_OD_EN					(0x01<<10)
// 31..11 = ������
//----------------------------------------------------

#endif // _IOCON_H


