#ifndef  _MB_H
  #define  _MB_H

// Типы запросов (функции)
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
#define     _TcpIp_MaxPacketSize    1550  //[0x40]; 2019-09-24 KVV+TDS - не проходили длинные посылки на запись в контроллер

// Коды ошибок
#define     _Code_Not_Support       1   // Код функции не поддерживаетс
#define     _Address_Not_Support    2   // Адрес регистра < 1 и > допустимого адреса
#define     _Out_Of_Quantity        3   // Количество битов (регистров) < 1 и > допустимого
#define     _Param_Not_Support      4   // Регистр не поддерживает эту функцию
#define     _End_Of_Quantity        5   // Конец массива

// Структура для обработки данных из/в буффер данных 
typedef struct
{
  word func;
  //byte *data;
  word data[_TcpIp_MaxPacketSize];//[0x40]; 2019-09-24 KVV+TDS - не проходили длинные посылки на запись в контроллер
} Tmodbus_packet;

//   ----------------SAP Структура Фрейма запроса-------------------------------
typedef struct
{
   byte Addr;       // адрес абонента                             - не исп. (Адрес пропис. в другой структуре)
   byte Func;       // функция                                    - использ.
   lword Start;      // стартовый адрес в таблице мастера          - использ.
   word Count;      // количество регистров                       - использ.
   word StartSlave; // стартовый адрес в таблице слейва           - не исп.
   word *TimeCycle; // время через которое надо запрашивать эту посылку, 0 = по команде - пока исп.
   word CurTime;   // время после последней отправки фрейма                            - пока исп.
} TSettingModbusFrame;

#define _Num_VirtualCAN_Ports		        1
#define _ModbusOverCAN_port			0

word modbus_slave( Tmodbus_packet *Receive, Tmodbus_packet *Send );  
word modbusMasterSend( word frameCount, Tmodbus_packet *Send);            //SAP 
word modbusMasterReceive( word frameCount, Tmodbus_packet *Receive);      //SAP
#endif  //  _MB_H



