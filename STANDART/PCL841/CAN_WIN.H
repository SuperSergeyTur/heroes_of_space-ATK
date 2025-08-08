#ifndef can_win_h
#define can_win_h

#define  _PCL841_WIN
#define  _Extern_names
#define  _CAN_WAGO

#define  _CAN_MASTER
//#define  _MAIN_INCLUDE

#include <vcl.h>
#include <io.h>
#include <fcntl.h>

#include <process.h>
#include "resource.h"

#include "IOcan.h"
//#include "maindat.h"

#include "types.h"
#include "can_code.h"
#include "can_drv.h"
#include "slavedrv.h"
#include "mastdrv.h"
//#include "can_win.h"
#include "var_mtab.h" /* Library function declaration */

//#define  can_setting(port) (CANIO[port-1].port_param)
#define  can_setting(port) (CANIO->port_param)

#define  mTime_out( port ) can_setting(port).connect

       // Код версии протокола CAN.
#ifndef   _Version_code
  #define   _Version_code  0
#endif


//#include "var_mtab.h" /* Library function declaration */
//----------------------------------
#endif
