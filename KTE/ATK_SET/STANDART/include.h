
#ifndef  _INCLUDE_H
#define  _INCLUDE_H
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/

#define  _KTE
#define  _32_BITS_


          //  Задаем номинал тока возбуждения 4.0В.
#define  _Iv_Nom     ( 400u * _K_diskr )

          //  Задаем коэф.умножения измерения для повышения точности измерения.
#define  _Skor_Shift  1  // ЭДС и задание скорости имеют номинал 1600 дискрет .

#define _MainPultProg  _NortonPultProg

#ifdef _CANOPEN
    #define _MCO_CAN_IRQ
#endif

#ifndef    _CAN_MASTER
    #define   _CAN_SLAVE_IRQ  // CAN на прерываниях нельзя совмещать с CAN-Мастером.
#endif

#ifdef   _WatchDog
    #define  _Msg_WDT                 _Pr_WDT
    #define  _SetMsg_WatchDog( lax )  mSet_PreduprMsg( lax )
#endif

#define  _SizeSledPole      32000


#include <types.h>
#include "lang.h"
#ifdef _CM3_
   #include <stdint.h>
   #include <string.h>
//   #include <LPC177x_8x.h>
   #include "LPC407x_8x_177x_8x.h"
   #include <system_LPC177x.h>
#ifndef CORE_M4
   #include "core_cm3.h"
#else
   #include "core_cm4.h"
#endif
   #include <iocon.h>
   #include <timer.h>
   #include <rtc.h>
   #include "DateConvert.h"
   #include <emc.h>
   #include <asm_nxp.h>
   #include <math.h>
   #include "lpc177x_8x_mcpwm.h"
   #include "lpc177x_8x_pinsel.h"
#else
   #include <stdio.h>
   #include <sfrs_fuj.h>
   #include <apb_fuj.h>
   #include <timerdrv.h>
   #include <i2c_time.h>
#endif

#include <data_i2c.h>
#include <DMA_CM_drv.h>
#include <uart_drv.h>
#include <izm.h>
#include <ad_drv.h>
#include <ssio.h>
#include <DT_monitor.h>
#include <monitor.h>
#include <macro.h>

#ifdef   _AVTONASTR
 #include "anastr.h"
#endif

#include <epa_drv.h>
#include <dac_drv.h>
//---
#ifdef _Vozb_KTE
    #include "sifu_v.h"
#endif
#include <usred.h>
//---
#ifdef _NET_IRQ
 #include "net.h"
#endif
//---
#include <synch1f.h>
#include <selsin.h>
#include <reg_eds.h>
#include <zad_skor.h>
#include <revers.h>
#include <cikl.h>
#include <sifu.h>
//---
#ifdef   _SIFU2_
 #include "sifu2.h"
#endif
//---
#include <gercon.h>
#include <ppg_drv.h>
#include <f_zapoln.h>

#include <datetime.h>
#include <config.h>
#include <sqr.h>


#include <zi1.h>
#include <prt_cpu.h>
#include <prt_drv.h>

#include <filtr.h>
#include <can_obj.h>
#include <insulat.h>

  #ifdef _CAN_MASTER
#include "can_mast.h"
  #else
#include "can_slv.h"
  #endif

//#ifdef   _CANOPEN     // Здесь определены переменные , используемые в CAN_DRV.c и без Can Open .
  #include "mco_task.h"
//#endif

#ifdef _CM3_
  #include "rs485.h"
  #include "mb.h"
  #include "mb_rtu.h"
#endif

#include <extrn.h>
//#include <extint.h>
#include <pdf.h>

  #ifdef _Sld_cond
#include "sld_stop.h"
  #endif

#include "ust.h"

  #ifdef _INTERPRETER
#include <interpreter.h>
  #endif

#include "obj_mux.h"
#include "obj.h"

#include "cse.h"

#include <avar.h>
#include <s400.h>
#include <rt.h>
#include <sled.h>
#include <link.h>


  #ifdef _CAN_MASTER
#include "var_mtab.h"
  #endif

  #ifdef _JOURNAL
#include "journal.h" // НЕ ПЕРЕМЕЩАТЬ - должно быть до <msg_tabl.h>
  #endif

#ifdef  _CM3_
  #include <flash.h>
#else
  #include <at24c64.h>
  #include <ram.h>
#endif

#include <ust_cnst.h>
#include <teplo_e.h>
#include <teplo_er.h>
#include <msg_tabl.h>
#include <msg.h>
#include <rev_pola.h>
#include <sld_cnst.h>
#include <var_tab.h>
#ifdef  _FR50N_
  #include <alarm.h>
#endif

  #ifdef _JOURNAL
#include "jrn_cnst.h" // НЕ ПЕРЕМЕЩАТЬ - должно быть после <msg.h>
  #endif

//---
#ifdef _NET_IRQ
#ifndef _CM3_
 #include "mb.h"
#endif
 #include "tcpip.h"
 #include "dp.h"
 #include "rs.h"
 #include "NetPult.h"
#endif
//---

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/
#endif // _INCLUDE_H
