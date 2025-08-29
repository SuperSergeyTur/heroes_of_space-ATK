
#include "obj_def.h"    // Для удобного выбора _***_INCLUDE

#define  _MAIN_INCLUDE
#define  _MSG_INCLUDE
#define  _REG_INCLUDE
#define  _TEPLO_INCLUDE
#define  _VOZB_INCLUDE
#define  _FLASH_INCLUDE
#define  _AVAR_INCLUDE
#define  _LINK_INCLUDE
#define  _SQR_INCLUDE
#define  _OBJ_INCLUDE
#define  _CAN_INCLUDE
#define  _AN_INCLUDE
#define  _RAM_INCLUDE
#define  _NET_INCLUDE
#define  _SLED_CONDITION_INCLUDE
#define  _JOURNAL_INCLUDE
#define  _CANOPEN_INCLUDE
#define  _INTERPRETER_INCLUDE
#define  _INT_MEM_INCLUDE

#include "include.h"

#ifdef   _AVTONASTR
 #include "anastr.c"
#endif

#ifdef _CombRedact
 #include "CombRedact.c"
#endif

//#ifdef  _WatchDog      // Выполнено в SYSTEM.C .
//#include "watchdog.c"
//#endif

#ifdef  _CM3_
   #include "system.c"
 //#include "iocon.c"
   #include "system_LPC177x.c"
   #include "timer.c"
   #include "DateConvert.cpp"
   #include "rtc.c"
   #include "emc.c"
   #include "lpc177x_8x_clkpwr.c"
   #include "lpc177x_8x_exti.c"
   #include "lpc177x_8x_mcpwm.c"
   #include "lpc177x_8x_pinsel.c"

#else
   #include "timerdrv.c"
#endif

#ifdef _INTERPRETER
#include "interpreter.c"
#include "RW_Prog.c"
#endif

//#include "datetime.c"
#include "fazir.c"
#include "gercon.c"
#include "setab1.c"
#include "indicatr.c"
#include "epa_drv.c"
#include "norton.c"
#include "msg.c"
#include "prt_cpu.c"
#include "ad_drv.c"
#include "DMA_CM_drv.c"
#include "uart_drv.c"
#include "ssio.c"
#include "cse.c"
#include "sqr.c"
#include "tst_adc.c"
#include "tst_in.c"
#include "tst_out.c"
#include "monitor.c"
#include "pult.c"
#include "ustavki.c"
#include "prt_drv.c"
#include "#ust_rez.c"
#include "clock.c"
#include "synch1f.c"
#include "sifu.c"
#include "ppg_drv.c"
#include "dac_drv.c"
#include "dac_tabl.c"
#include "tst_dac.c"
#include "avar.c"
#include "sled.c"
#include "s400.c"
#include "link.c"
#include "filtr.c"
#include "upravl.c"
#include "f2_drv.c"
//---
#ifdef   _SIFU2_
#include "sifu2.c"
#endif
//---
//---
#ifdef _Vozb_KTE
    #include "rtv.c"
    #include "sifu_v.c"
#endif
#if defined( _RVId ) || !defined( _Vozb_KTE ) || defined( It_ach )
    #include "usred.c"
#endif
//---

#ifndef _ZI_30min
 #include "zi1.c"
#else
 #include "zi2.c"
#endif

#ifdef  _CM3_
  #include "flash.c"
#else
  #include "at24c64.c"
 #ifdef  _FR50N_
  #include "ram.c"
 #endif
#endif

#include "#ust_i2c.c"
#include "Data_i2c.c"

#include "pdf.c"
#include "save_av.c"
#include "obj.c"
#include "obj_reg.c"
#include "izm.c"
#include "insulat.c"
#include "rt.c"
//#include "revers.c"
#include "cikl.c"

#include "_main1.c"
#ifdef _Sld_cond
 #include "sld_stop.c"
#endif

//---
#ifdef _JOURNAL
 #include "journal.c"
#endif
//---

//#include "vectors.c"
//#include "at24c64.c"
//#include "#ust_i2c.c"
#include "teplo_e.c"
//#include "teplo_un.c"
//#include "teplo_r.c"
//#include "#ust_rez.c"
//#include "Data_i2c.c"
//#include "depn.c"
#include "regsc.c"
//#include "reg_eds.c"

//#include "alarm.c"
//#include "teplo.c"
#include "zad_skor.c"
//#include "i2c_time.c"
#include "selsin.c"


#include "test_i2c.c"
#include "can_slv.c"
#include "rw_i2c.c"
#include "read_ust.c"

//---
#ifdef _CAN_MASTER
 #include "can_mast.c"
#endif
//---

#include "procat.c"
#include "rev_pola.c"

#ifdef _CM3_
  #include "rs485.c"
  #include "CRC16.c"
  #include "mb.c"
  #include "mb_rtu.c"
#endif
//---
#ifdef   _NET_IRQ
  #include "NetIndicatr.c"
  #include "NetSetab.c"
#ifndef _CM3_
  #include "mb.c"
#endif
  #include "net.c"
  #include "tcpip.c"
  #include "DP.c"
  #include "rs.c"
#endif
#ifdef   _CANOPEN
  #include "array.c"
//#include "mco_can.c"
  #include "mco_dict.c"
  #include "mco_emcy.c"
  #include "mco_nmt.c"
  #include "mco_pdo.c"
  #include "mco_sdoserver.c"
  #include "mco_sdoclient.c"
  #include "mco_sync.c"
  #include "mco_task.c"
#endif
//---
