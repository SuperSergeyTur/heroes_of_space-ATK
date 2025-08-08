#ifndef  _EMC_H
  #define  _EMC_H

enum {_EMC_CS0, _EMC_CS1, _EMC_CS2};


// ����c��� ������������ ���  = 1 �� (����. 64��)
#define  _EMC_CS0_BEGIN			0x80000000
#define  _EMC_CS0_END			0x800FFFFF

// ����c��� ������������ ����  = 512 �� (����. 64��)
#define  _EMC_CS1_BEGIN			0x90000000
#define  _EMC_CS1_END			0x9007FFFF

// ����c��� ������������ ��� ���� �������� ���������� (����. 64��)
#define  _EMC_CS2_BEGIN			0x98000000
#define  _EMC_CS2_END			0x9BFFFFFF


slword EMC_Check( byte Region, byte all );
slword emcx @ "RAM_region";


#endif  // _EMC_H


