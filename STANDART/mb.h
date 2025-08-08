#ifndef  _MB_H
  #define  _MB_H

// ���� �������� (�������)
#define     _R_Coils                1
#define     _R_Discrete_Inputs      2
#define     _R_Holding_Registers    3
#define     _R_Input_Register       4
#define     _W_Single_Coils         5
#define     _W_Single_Register      6
#define     _R_Exception_Status     7
#define     _Diagnostic             8
#define     _Get_Com_Event_Counter  11
#define     _Get_Com_Event_Log      12
#define     _W_Multiple_Coils       15
#define     _W_Multiple_Registers   16
#define     _Report_Slave_ID        17
#define     _R_File_Record          20
#define     _W_File_Record          21
#define     _Mask_Write_Register    22
#define     _RW_Multiple_Registers  23
#define     _R_FIFO_Queue           24
#define     _R_Device_Ident         43
#define     _CAN_Frame              70
#define     _R_StructL              71
#define     _W_StructL              72
#define     _TcpIp_MaxPacketSize    1550  //[0x40]; 2019-09-24 KVV+TDS - �� ��������� ������� ������� �� ������ � ����������

// ���� ������
#define     _Code_Not_Support       1   // ��� ������� �� �������������
#define     _Address_Not_Support    2   // ����� �������� < 1 � > ����������� ������
#define     _Out_Of_Quantity        3   // ���������� ����� (���������) < 1 � > �����������
#define     _Param_Not_Support      4   // ������� �� ������������ ��� �������
#define     _End_Of_Quantity        5   // ����� �������

// ��������� ��� ��������� ������ ��/� ������ ������ 
typedef struct
{
  word func;
  //byte *data;
  word data[_TcpIp_MaxPacketSize];//[0x40]; 2019-09-24 KVV+TDS - �� ��������� ������� ������� �� ������ � ����������
} Tmodbus_packet;

//   ----------------SAP ��������� ������ �������-------------------------------
typedef struct
{
   byte Addr;       // ����� ��������                             - �� ���. (����� ������. � ������ ���������)
   byte Func;       // �������                                    - �������.
   lword Start;      // ��������� ����� � ������� �������          - �������.
   word Count;      // ���������� ���������                       - �������.
   word StartSlave; // ��������� ����� � ������� ������           - �� ���.
   word *TimeCycle; // ����� ����� ������� ���� ����������� ��� �������, 0 = �� ������� - ���� ���.
   word CurTime;   // ����� ����� ��������� �������� ������                            - ���� ���.
} TSettingModbusFrame;

#define _Num_VirtualCAN_Ports		        1
#define _ModbusOverCAN_port			0

word modbus_slave( Tmodbus_packet *Receive, Tmodbus_packet *Send );  
word modbusMasterSend( word frameCount, Tmodbus_packet *Send);            //SAP 
word modbusMasterReceive( word frameCount, Tmodbus_packet *Receive);      //SAP
#endif  //  _MB_H



