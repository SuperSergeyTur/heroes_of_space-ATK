#ifndef _inc_h
#define _inc_h
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/

#define  _KTE

          //  Задаем номинал тока возбуждения 4.0В.
#define  _Iv_Nom      400u

          //  Задаем коэф.умножения измерения для повышения точности измерения.
#define  _Skor_Shift  3

#define   _MainPultProg  _NortonPultProg
#define   _Link
// в "obj.h" #define  _kol_obl    ( 1 ) // Количество областей уставок
//           #define   Num_obl      1
                                // 26.03.2018 - CAN прерывания для 590 не включаем , т.к. он зависает в
//#ifndef    _CAN_MASTER        //              прерываниях на новых стандартах , после добавления СМ3 .
//    #define   _CAN_SLAVE_IRQ  // CAN на прерываниях нельзя совмещать с CAN-Мастером.
//#endif

#ifdef   _WatchDog
    #define  _Msg_WDT                 _Pr_WDT
    #define  _SetMsg_WatchDog( lax )  mSet_PreduprMsg( lax )
    #define  _RegMsg_WatchDog         Reg_PreduprMsg
#endif

#include <stdio.h>
#include <sfrs_fuj.h>
#include <types.h>
#include <apb_fuj.h>
#include <timerdrv.h>
#include <prt_cpu.h>
#include <prt_drv.h>
#include <uart_drv.h>
#include <ad_drv.h>
#include <ppg_drv.h>
#include <epa_drv.h>
#include <dac_drv.h>
#include <asm_fuj.h>

#include <data_i2c.h>
#include <at24c64.h>
#include <i2c_time.h>
#include <monitor.h>
#include <macro.h>
#include <sqr.h>

#include <zi1.h>
#include <datetime.h>

#include <config.h>
#ifdef _Vozb_KTE
 #include "sifu_v.h"
#endif
#include <usred.h>
#include <synch1f.h>
#include <selsin.h>
#include <reg_eds.h>
#include <zad_skor.h>
#include <revers.h>
#include <cikl.h>
#include <izm.h>
#include <sifu.h>
#include <gercon.h>
//#include <teplo_un.h>
//#include <teplo_r.h>
//#include <#teplo_r.h>
#include <cse.h>
#include <ssio.h>
//---
#ifdef   _AVTONASTR
 #include "anastr.h"
#endif
//---
#include <filtr.h>
#include <can_obj.h>
#include <insulat.h>
#include <f_zapoln.h>

  #ifdef _CAN_MASTER
#include "can_mast.h"
  #else
#include "can_slv.h"
  #endif

#include <extrn.h>
#include <pdf.h>

  #ifdef _Sld_cond
#include "sld_stop.h"
  #endif

#include <ust.h>
#include <obj.h>
#include <sled.h>
#include <avar.h>
#include <s400.h>
#include <rt.h>
#include <link.h>

  #ifdef _CAN_MASTER
#include "var_mtab.h"
  #endif

  #ifdef _JOURNAL
#include "journal.h" // НЕ ПЕРЕМЕЩАТЬ - должно быть до <msg_tabl.h>
  #endif

#include <ust_cnst.h>
#include <teplo_e.h>
#include <teplo_er.h>
#include <msg_tabl.h>
#include <msg.h>
#include <rev_pola.h>
#include <sld_cnst.h>
#include <var_tab.h>

  #ifdef _JOURNAL
#include "jrn_cnst.h" // НЕ ПЕРЕМЕЩАТЬ - должно быть после <msg.h>
  #endif


//#include <can_vozb.h>
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/
#endif
