#ifndef _can_mast_h
#define _can_mast_h
//------------------------------------

   //     ВЗВЕСТИ В UST_CNST.H БИТ
  //  can_setting(port).config._.master = 1 ;

#include "can_code.h"
#include "can_drv.h"
#include "slavedrv.h"
#include "mastdrv.h"

       // Код версии протокола CAN.
#ifndef   _Version_code
  #define   _Version_code  0
#endif

#define  can_setting(port) (_r.can[port])

#define  mTime_out( port ) can_setting(port).connect

//#define _INIT_CAN_OBJ   0
//#define _WORK_CAN_OBJ   1

word  can_init ( byte port ) ;

      //   Инициализация таблиц переменных в ОЗУ из константных
      // таблиц в ПЗУ.
void init_var_mtab ( void )  ;

word can_master ( byte port , byte code ) ;

#define  Mbi_canConnect   canr.StatReg2._.n7
//vmz 09122014
#define  Mbi_canConnect2   canr.StatReg3._.n7
//void can_logic  ( byte oper ) ;

//void can_Set_Addr( void );
/*
union BitsMaster
{
  word all;
  struct
  {
    word bit_master   : 1 ; // бит мастера
    word num_master   : 3 ; // его порядковый номер

    word rezerv1      : 4 ; //

    word rezerv2      : 4 ; //

    word rezerv3      : 2 ; //
    word free_master  : 1 ; // Чистый мастер - есть еще хотя бы один слэйв
    word reserve      : 1 ; //
  } _;
};

union Rev
{
  word all ;
  struct
    {
      word DZV_OK      : 1  ;
      word Revers_OK   : 1  ;
      word rezerved    : 14 ;
    } _ ;
} ;

union StatusReg
{
  byte all ;
  struct
  {
    word Ready      : 1 ;
    word Predupr    : 1 ;
    word Avar       : 1 ;
    word KTE_Rezerv : 1 ;

    word StateQK    : 1 ;  // бит мастера
    word GotovQK    : 1 ;  //
    word rezerv3    : 1 ;  //
    word Connect    : 1 ;  // для теста наличия связи.
  } _ ;
};

union DataReg
{
  byte all;
  struct
  {
    byte connect  : 1 ;
    byte link     : 1 ;
    byte rezerv   : 6 ;
  } _;
};
*/
#ifdef _CAN_INCLUDE

//byte tst1, tst2;

//union  Rev       R_V[2];
//union  StatusReg StsM[2];
//union  DataReg   DataM[2];
//union BitsMaster sMaster;

word   Opros_time ;

//vmz 122014
word   Opros_time2 ;
word   time_scan2 ;

//byte   Err_Dev1  ;
//word   Time_Dev1 ;
word   Tst_Read_Dev[8], Tst_Write_Dev[2] ;
word Tst_Write_Dev2 ;
//vmz 122014
word   Tst_Read_Dev21, Tst_Write_Dev21 ;

//word   Test_can ;

#else

//extern byte tst1;

//extern union  Rev         R_V[];
//extern union  StatusReg   StsM[];
//extern union  DataReg     DataM[];
//extern union  BitsMaster  sMaster;

extern word   Opros_time ;

//vmz 122014
extern word   Opros_time2 ;
extern word   time_scan2 ;

//extern byte   Err_Dev1  ;
//extern word   Time_Dev1 ;
extern word   Tst_Read_Dev1, Tst_Write_Dev1 ;

//vmz 122014
extern word   Tst_Read_Dev21, Tst_Write_Dev21 ;

//extern word   Test_can ;

#endif
//------------------------------------

#endif

