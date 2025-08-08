
#ifndef _can_slv_h
#define _can_slv_h

//#define   _CAN_SHARED  //  CAN-используется и другими программами.

#include <can_code.h>
#include "can_drv.h"
#include "slavedrv.h"

#ifdef _Micro_Master
  #include "micrmast.h"
#endif

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/

       // Код версии протокола CAN.
#ifndef   _Version_code
  #define   _Version_code  0
#endif

#ifndef  can_setting
  #define  can_setting(port) (_r.can[port])
#endif

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/
#endif
