/*
 FR family I/O register declaration file V30L02
 ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU LIMITED 1998-1999
 LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU LIMITED
*/

#if   defined(__CPU_MB91101__) || defined(__CPU_MB91V101__)
#define __CPU_MB91101_SERIES
#include "_mb91101.h"

#elif defined(__CPU_MB91103__)
#define __CPU_MB91103_SERIES
#include "_mb91103.h"

#elif defined(__CPU_MB91106__) || defined(__CPU_MB91V106__)
#define __CPU_MB91106_SERIES
#include "_mb91106.h"

#elif defined(__CPU_MB91F109__)
#define __CPU_MB91F109_SERIES
#include "_mb91109.h"

#elif defined(__CPU_MB91110__) || defined(__CPU_MB91V110__)
#define __CPU_MB91110_SERIES
#include "_mb91110.h"

#elif defined(__CPU_MB91121__) || defined(__CPU_MB91V121__)
#define __CPU_MB91121_SERIES
#include "_mb91121.h"

#elif defined(__CPU_MB91130__) || \
      defined(__CPU_MB91133__) || defined(__CPU_MB91FV133__)
#define __CPU_MB91130_SERIES
#include "_mb91130.h"

#elif defined(__CPU_MB91191__) || defined(__CPU_MB91FV191__) || \
      defined(__CPU_MB91192__) || defined(__CPU_MB91FV192__)
#define __CPU_MB91191_SERIES
#include "_mb91191.h"

#elif defined(__CPU_MB91360__)  || \
      defined(__CPU_MB91V360__) || defined(__CPU_MB91F361__)
#define __CPU_MB91360_SERIES
#include "_mb91360.h"

#else
#error "The I/O register file of the specified CPU option does not exist"

#endif

