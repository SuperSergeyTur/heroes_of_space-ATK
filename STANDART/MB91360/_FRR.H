/*
 FR family I/O register declaration file V30L02
 ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU LIMITED 1998-1999
 LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU LIMITED
*/


/******************************************************************/
/* Sample program for I/O variables of I-cache control registers. */
/******************************************************************/
/* structure of ICHCR */
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91103_SERIES) || \
      defined(__CPU_MB91110_SERIES) || defined(__CPU_MB91121_SERIES)
union io_ichcr {
	unsigned long	word;
	struct {
		unsigned long	    :26;
		unsigned long	GBLK:1;
		unsigned long	ALFL:1;
		unsigned long	EOLK:1;
		unsigned long	ELKR:1;
		unsigned long	FLSH:1;
		unsigned long	ENAB:1;
	} bit;
};
#elif defined(__CPU_MB91360_SERIES)
union io_ichcr {
	unsigned long	word;
	struct {
		unsigned long	    :24;
		unsigned long	RAM :1;
		unsigned long	    :1;
		unsigned long	GBLK:1;
		unsigned long	ALFL:1;
		unsigned long	EOLK:1;
		unsigned long	ELKR:1;
		unsigned long	FLSH:1;
		unsigned long	ENAB:1;
	} bit;
};
#endif

/* structure of IRBS */
#if   defined(__CPU_MB91360_SERIES)
union io_irbs {
	unsigned long	word;
	struct {
		unsigned long	    :16;
		unsigned long	IRBS:4;
		unsigned long	    :12;
	} bit;
};
#endif

/* structure of ISIZE */
#if   defined(__CPU_MB91360_SERIES)
union io_isize {
	unsigned long	word;
	struct {
		unsigned long	    :30;
		unsigned long	SIZE:2;
	} bit;
};
#endif


/*******************************************************/
/* Sample program for I/O variable of clock generator. */
/*******************************************************/
/* structure of clock generator */
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91103_SERIES) || \
      defined(__CPU_MB91106_SERIES) || defined(__CPU_MB91110_SERIES) || \
      defined(__CPU_MB91191_SERIES) || defined(__CPU_MB91121_SERIES) || \
      defined(__CPU_MB91130_SERIES)
struct io_clk {

	/* structure of RSRR */
	union {
		unsigned char	byte;
		struct {
			unsigned char	PONR:1;
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91110_SERIES)
			unsigned char	HSTB:1;
#elif defined(__CPU_MB91103_SERIES) || defined(__CPU_MB91106_SERIES) || \
      defined(__CPU_MB91191_SERIES) || defined(__CPU_MB91121_SERIES) || \
      defined(__CPU_MB91130_SERIES)
			unsigned char	    :1;
#endif
			unsigned char	WDOG:1;
			unsigned char	ERST:1;
			unsigned char	SRST:1;
			unsigned char	    :3;
		} bit;
	} IO_RSRR;

	/* structure of STCR */
	union {
		unsigned char	byte;
		struct {
			unsigned char	STOP:1;
			unsigned char	SLEP:1;
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91103_SERIES) || \
      defined(__CPU_MB91106_SERIES) || defined(__CPU_MB91110_SERIES) || \
      defined(__CPU_MB91121_SERIES)
			unsigned char	HIZX:1;
#elif defined(__CPU_MB91191_SERIES) || defined(__CPU_MB91130_SERIES)
			unsigned char	    :1;
#endif
			unsigned char	SRST:1;
			unsigned char	OSC :2;
			unsigned char	    :2;
		} bit;
	} IO_STCR;

#if   defined(__CPU_MB91191_SERIES)
	unsigned char	:8;
#elif defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91103_SERIES) || \
      defined(__CPU_MB91106_SERIES) || defined(__CPU_MB91110_SERIES) || \
      defined(__CPU_MB91121_SERIES) || defined(__CPU_MB91130_SERIES)
	unsigned char	IO_PDRR;
#endif

	unsigned char	IO_CTBR;

	/* structure of GCR */
 	union {
		unsigned char	byte;
		struct {
			unsigned char	CCK  :2;
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91106_SERIES) || \
      defined(__CPU_MB91110_SERIES) || defined(__CPU_MB91121_SERIES)
			unsigned char	DBLAK:1;
			unsigned char	DBLON:1;
#elif defined(__CPU_MB91103_SERIES) || defined(__CPU_MB91191_SERIES) || \
      defined(__CPU_MB91130_SERIES)
			unsigned char	     :2;
#endif
			unsigned char	PCK  :2;
			unsigned char	     :1;
			unsigned char	CHC  :1;
		} bit;
	} IO_GCR;

	unsigned char	IO_WPR;
};
#elif defined(__CPU_MB91360_SERIES)
struct io_clk {

	/* structure of RSRR */
	union {
		unsigned char	byte;
		struct {
			unsigned char	INIT:1;
			unsigned char	HSTB:1;
			unsigned char	WDOG:1;
			unsigned char	ERST:1;
			unsigned char	SRST:1;
			unsigned char	    :1;
			unsigned char	WT  :2;
		} bit;
	} IO_RSRR;

	/* structure of STCR */
	union {
		unsigned char	byte;
		struct {
			unsigned char	STOP :1;
			unsigned char	SLEEP:1;
			unsigned char	HIZ  :1;
			unsigned char	SRST :1;
			unsigned char	OS   :2;
			unsigned char	     :1;
			unsigned char	OSCD1:1;
		} bit;
	} IO_STCR;

	/* structure of TBCR */
	union {
		unsigned char	byte;
		struct {
			unsigned char	TBIF :1;
			unsigned char	TBIE :1;
			unsigned char	TBC  :3;
			unsigned char	     :1;
			unsigned char	SYNCR:1;
			unsigned char	SYNCS:1;
		} bit;
	} IO_TBCR;

	unsigned char	IO_CTBR;

	/* structure of CLKR */
	union {
		unsigned char	byte;
		struct {
			unsigned char	PLL2S0:1;
			unsigned char	PLL1S :3;
			unsigned char	PLL2EN:1;
			unsigned char	PLL1EN:1;
			unsigned char	CLKS  :2;
		} bit;
	} IO_CLKR;

	unsigned char	IO_WPR;

	/* structure of DIVR0 */
	union {
		unsigned char	byte;
		struct {
			unsigned char	B :4;
			unsigned char	P :4;
		} bit;
	} IO_DIVR0;

	/* structure of DIVR1 */
	union {
		unsigned char	byte;
		struct {
			unsigned char	T :4;
			unsigned char	S :4;
		} bit;
	} IO_DIVR1;

};
#endif

/* structure of PCTR */
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91106_SERIES) || \
      defined(__CPU_MB91110_SERIES) || defined(__CPU_MB91121_SERIES)
union io_pctr {
	unsigned char	byte;
	struct {
		unsigned char	SLCT:2;
		unsigned char	    :2;
		unsigned char	VSTP:1;
		unsigned char	    :3;
	} bit;
};
#elif defined(__CPU_MB91130_SERIES)
union io_pctr {
	unsigned char	byte;
	struct {
		unsigned char	SLCT:2;
		unsigned char	    :2;
		unsigned char	VSTP:1;
		unsigned char	    :1;
		unsigned char	LSTP:1;
		unsigned char	LCLK:1;
	} bit;
};
#endif

/**************************************************************/
/* Sample program for I/O variable of external bus interface. */
/**************************************************************/
/* structure of external bus interface */
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91103_SERIES) || \
      defined(__CPU_MB91106_SERIES) || defined(__CPU_MB91110_SERIES) || \
      defined(__CPU_MB91191_SERIES) || defined(__CPU_MB91121_SERIES) || \
      defined(__CPU_MB91130_SERIES)
struct io_ebus {
	unsigned short	IO_ASR1;
	unsigned short	IO_AMR1;
	unsigned short	IO_ASR2;
	unsigned short	IO_AMR2;
	unsigned short	IO_ASR3;
	unsigned short	IO_AMR3;
	unsigned short	IO_ASR4;
	unsigned short	IO_AMR4;
	unsigned short	IO_ASR5;
	unsigned short	IO_AMR5;
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91103_SERIES) || \
      defined(__CPU_MB91106_SERIES) || defined(__CPU_MB91110_SERIES) || \
      defined(__CPU_MB91121_SERIES) || defined(__CPU_MB91130_SERIES)
	/* structure of AMD0 */
	union {
		unsigned char	byte;
		struct {
			unsigned char	    :3;
			unsigned char	BW  :2;
			unsigned char	WTC :3;
		} bit;
	} IO_AMD0;
#elif defined(__CPU_MB91191_SERIES)
	unsigned char	:8;
#endif
	/* structure of AMD1 */
	union {
		unsigned char	byte;
		struct {
			unsigned char	MPX :1;
			unsigned char	    :2;
			unsigned char	BW  :2;
			unsigned char	WTC :3;
		} bit;
	} IO_AMD1;
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91103_SERIES) || \
      defined(__CPU_MB91106_SERIES) || defined(__CPU_MB91110_SERIES) || \
      defined(__CPU_MB91121_SERIES) || defined(__CPU_MB91130_SERIES)
	/* structure of AMD32 */
	union {
		unsigned char	byte;
		struct {
			unsigned char	BW  :2;
			unsigned char	WT3 :3;
			unsigned char	WT2 :3;
		} bit;
	} IO_AMD32;
	/* structure of AMD4 */
	union {
		unsigned char	byte;
		struct {
			unsigned char	DRME:1;
			unsigned char	    :2;
			unsigned char	BW  :2;
			unsigned char	WTC :3;
		} bit;
	} IO_AMD4;
	/* structure of AMD5 */
	union {
		unsigned char	byte;
		struct {
			unsigned char	DRME:1;
			unsigned char	    :2;
			unsigned char	BW  :2;
			unsigned char	WTC :3;
		} bit;
	} IO_AMD5;
#if   defined(__CPU_MB91130_SERIES)
	unsigned char	:8;
	unsigned short	:16;
#else
	unsigned char	IO_DSCR;
	/* structure of RFCR */
	union {
		unsigned short	hword;
		struct {
			unsigned short	    :2;
			unsigned short	REL :6;
			unsigned short	R1W :1;
			unsigned short	R3W :1;
			unsigned short	    :3;
			unsigned short	STR :1;
			unsigned short	CKS :2;
		} bit;
	} IO_RFCR;
#endif
	unsigned short	IO_EPCR0;
	unsigned short	IO_EPCR1;
#if   defined(__CPU_MB91130_SERIES)
	unsigned short	:16;
	unsigned short	:16;
#else
	/* structure of DMCR4 */
	union {
		unsigned short	hword;
		struct {
			unsigned short	PGS :4;
			unsigned short	Q1W :1;
			unsigned short	Q4W :1;
			unsigned short	DSAS:1;
			unsigned short	HYPR:1;
			unsigned short	PAGE:1;
			unsigned short	CW  :1;
			unsigned short	SLFR:1;
			unsigned short	REFE:1;
			unsigned short	PAR :1;
			unsigned short	PERR:1;
			unsigned short	PEIE:1;
			unsigned short	    :1;
		} bit;
	} IO_DMCR4;
	/* structure of DMCR5 */
	union {
		unsigned short	hword;
		struct {
			unsigned short	PGS :4;
			unsigned short	Q1W :1;
			unsigned short	Q4W :1;
			unsigned short	DSAS:1;
			unsigned short	HYPR:1;
			unsigned short	PAGE:1;
			unsigned short	CW  :1;
			unsigned short	SLFR:1;
			unsigned short	REFE:1;
			unsigned short	PAR :1;
			unsigned short	PERR:1;
			unsigned short	PEIE:1;
			unsigned short	    :1;
		} bit;
	} IO_DMCR5;
#endif
#elif defined(__CPU_MB91191_SERIES)
	unsigned short	:16;
	unsigned short	:16;
	unsigned short	:16;
	unsigned short	:16;
	unsigned short	:16;
	unsigned short	:16;
	unsigned short	:16;
#endif
};
#elif defined(__CPU_MB91360_SERIES)
/* structure of AMD0-AMD7 */
union io_amd {
	unsigned char	byte;
	struct {
		unsigned char	    :2;
		unsigned char	RDYE:1;
		unsigned char	BW  :2;
		unsigned char	WTC :3;
	} bit;
};
/* structure of CHE */
union io_che {
	unsigned char	byte;
	struct {
		unsigned char	CHE7:1;
		unsigned char	CHE6:1;
		unsigned char	CHE5:1;
		unsigned char	CHE4:1;
		unsigned char	CHE3:1;
		unsigned char	CHE2:1;
		unsigned char	CHE1:1;
		unsigned char	CHE0:1;
	} bit;
};
/* structure of CSE */
union io_cse {
	unsigned char	byte;
	struct {
		unsigned char	CSE7:1;
		unsigned char	CSE6:1;
		unsigned char	CSE5:1;
		unsigned char	CSE4:1;
		unsigned char	CSE3:1;
		unsigned char	CSE2:1;
		unsigned char	CSE1:1;
		unsigned char	CSE0:1;
	} bit;
};
/* structure of external bus interface */
struct io_ebus {
	unsigned short	IO_ASR0;
	unsigned short	IO_AMR0;
	unsigned short	IO_ASR1;
	unsigned short	IO_AMR1;
	unsigned short	IO_ASR2;
	unsigned short	IO_AMR2;
	unsigned short	IO_ASR3;
	unsigned short	IO_AMR3;
	unsigned short	IO_ASR4;
	unsigned short	IO_AMR4;
	unsigned short	IO_ASR5;
	unsigned short	IO_AMR5;
	unsigned short	IO_ASR6;
	unsigned short	IO_AMR6;
	unsigned short	IO_ASR7;
	unsigned short	IO_AMR7;
	union io_amd	IO_AMD0;
	union io_amd	IO_AMD1;
	union io_amd	IO_AMD2;
	union io_amd	IO_AMD3;
	union io_amd	IO_AMD4;
	union io_amd	IO_AMD5;
	union io_amd	IO_AMD6;
	union io_amd	IO_AMD7;
	union io_cse	IO_CSE;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	union io_che	IO_CHE;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
};
#endif


/*************************************************/
/* Sample program for I/O variables of I/O port. */
/*************************************************/
/* structure of PDR0 */
#if   defined(__CPU_MB91103_SERIES) || defined(__CPU_MB91191_SERIES)
union io_pdr0 {
	unsigned char	byte;
	struct {
		unsigned char	P07 :1;
		unsigned char	P06 :1;
		unsigned char	P05 :1;
		unsigned char	P04 :1;
		unsigned char	P03 :1;
		unsigned char	P02 :1;
		unsigned char	P01 :1;
		unsigned char	P00 :1;
	} bit;
};
#endif

/* structure of PDR1 */
#if   defined(__CPU_MB91103_SERIES) || defined(__CPU_MB91191_SERIES)
union io_pdr1 {
	unsigned char	byte;
	struct {
		unsigned char	P17 :1;
		unsigned char	P16 :1;
		unsigned char	P15 :1;
		unsigned char	P14 :1;
		unsigned char	P13 :1;
		unsigned char	P12 :1;
		unsigned char	P11 :1;
		unsigned char	P10 :1;
	} bit;
};
#endif

/* structure of PDR2 */
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91103_SERIES) || \
      defined(__CPU_MB91106_SERIES) || defined(__CPU_MB91110_SERIES) || \
      defined(__CPU_MB91191_SERIES) || \
      defined(__CPU_MB91121_SERIES) || defined(__CPU_MB91130_SERIES)
union io_pdr2 {
	unsigned char	byte;
	struct {
		unsigned char	P27 :1;
		unsigned char	P26 :1;
		unsigned char	P25 :1;
		unsigned char	P24 :1;
		unsigned char	P23 :1;
		unsigned char	P22 :1;
		unsigned char	P21 :1;
		unsigned char	P20 :1;
	} bit;
};
#endif

/* structure of PDR3 */
#if   defined(__CPU_MB91106_SERIES) || defined(__CPU_MB91191_SERIES) || \
      defined(__CPU_MB91130_SERIES)
union io_pdr3 {
	unsigned char	byte;
	struct {
		unsigned char	P37 :1;
		unsigned char	P36 :1;
		unsigned char	P35 :1;
		unsigned char	P34 :1;
		unsigned char	P33 :1;
		unsigned char	P32 :1;
		unsigned char	P31 :1;
		unsigned char	P30 :1;
	} bit;
};
#endif

/* structure of PDR4 */
#if   defined(__CPU_MB91106_SERIES) || defined(__CPU_MB91191_SERIES) || \
      defined(__CPU_MB91130_SERIES)
union io_pdr4 {
	unsigned char	byte;
	struct {
		unsigned char	P47 :1;
		unsigned char	P46 :1;
		unsigned char	P45 :1;
		unsigned char	P44 :1;
		unsigned char	P43 :1;
		unsigned char	P42 :1;
		unsigned char	P41 :1;
		unsigned char	P40 :1;
	} bit;
};
#endif

/* structure of PDR5 */
#if   defined(__CPU_MB91106_SERIES) || defined(__CPU_MB91191_SERIES) || \
      defined(__CPU_MB91130_SERIES)
union io_pdr5 {
	unsigned char	byte;
	struct {
		unsigned char	P57 :1;
		unsigned char	P56 :1;
		unsigned char	P55 :1;
		unsigned char	P54 :1;
		unsigned char	P53 :1;
		unsigned char	P52 :1;
		unsigned char	P51 :1;
		unsigned char	P50 :1;
	} bit;
};
#endif

/* structure of PDR6 */
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91103_SERIES) || \
      defined(__CPU_MB91106_SERIES) || defined(__CPU_MB91110_SERIES) || \
      defined(__CPU_MB91191_SERIES) || \
      defined(__CPU_MB91121_SERIES) || defined(__CPU_MB91130_SERIES)
union io_pdr6 {
	unsigned char	byte;
	struct {
		unsigned char	P67 :1;
		unsigned char	P66 :1;
		unsigned char	P65 :1;
		unsigned char	P64 :1;
		unsigned char	P63 :1;
		unsigned char	P62 :1;
		unsigned char	P61 :1;
		unsigned char	P60 :1;
	} bit;
};
#endif

/* structure of PDR7 */
#if   defined(__CPU_MB91106_SERIES) || defined(__CPU_MB91191_SERIES)
union io_pdr7 {
	unsigned char	byte;
	struct {
		unsigned char	    :7;
		unsigned char	P70 :1;
	} bit;
};
#elif defined(__CPU_MB91360_SERIES)
union io_pdr7 {
	unsigned char	byte;
	struct {
		unsigned char	P77 :1;
		unsigned char	P76 :1;
		unsigned char	P75 :1;
		unsigned char	P74 :1;
		unsigned char	P73 :1;
		unsigned char	P72 :1;
		unsigned char	P71 :1;
		unsigned char	P70 :1;
	} bit;
};
#endif

/* structure of PDR8 */
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91110_SERIES) || \
      defined(__CPU_MB91121_SERIES)
union io_pdr8 {
	unsigned char	byte;
	struct {
		unsigned char	    :2;
		unsigned char	P85 :1;
		unsigned char	    :2;
		unsigned char	P82 :1;
		unsigned char	P81 :1;
		unsigned char	P80 :1;
	} bit;
};
#elif defined(__CPU_MB91103_SERIES)
union io_pdr8 {
	unsigned char	byte;
	struct {
		unsigned char	P87 :1;
		unsigned char	P86 :1;
		unsigned char	P85 :1;
		unsigned char	    :2;
		unsigned char	P82 :1;
		unsigned char	P81 :1;
		unsigned char	P80 :1;
	} bit;
};
#elif defined(__CPU_MB91106_SERIES)
union io_pdr8 {
	unsigned char	byte;
	struct {
		unsigned char	    :2;
		unsigned char	P85 :1;
		unsigned char	P84 :1;
		unsigned char	P83 :1;
		unsigned char	P82 :1;
		unsigned char	P81 :1;
		unsigned char	P80 :1;
	} bit;
};
#elif defined(__CPU_MB91191_SERIES) || defined(__CPU_MB91360_SERIES)
union io_pdr8 {
	unsigned char	byte;
	struct {
		unsigned char	P87 :1;
		unsigned char	P86 :1;
		unsigned char	P85 :1;
		unsigned char	P84 :1;
		unsigned char	P83 :1;
		unsigned char	P82 :1;
		unsigned char	P81 :1;
		unsigned char	P80 :1;
	} bit;
};
union io_pfr8 {
	unsigned char	byte;
	struct {
		unsigned char	P87 :1;
		unsigned char	P86 :1;
		unsigned char	P85 :1;
		unsigned char	P84 :1;
		unsigned char	P83 :1;
		unsigned char	P82 :1;
		unsigned char	    :1;
		unsigned char	P80 :1;
	} bit;
};
#elif defined(__CPU_MB91130_SERIES)
union io_pdr8 {
	unsigned char	byte;
	struct {
		unsigned char	    :1;
		unsigned char	P86 :1;
		unsigned char	P85 :1;
		unsigned char	P84 :1;
		unsigned char	P83 :1;
		unsigned char	P82 :1;
		unsigned char	P81 :1;
		unsigned char	P80 :1;
	} bit;
};
#endif

/* structure of PDR9 */
#if   defined(__CPU_MB91103_SERIES)
union io_pdr9 {
	unsigned char	byte;
	struct {
		unsigned char	    :2;
		unsigned char	P95 :1;
		unsigned char	P94 :1;
		unsigned char	P93 :1;
		unsigned char	P92 :1;
		unsigned char	P91 :1;
		unsigned char	P90 :1;
	} bit;
};
#elif defined(__CPU_MB91191_SERIES)
union io_pdr9 {
	unsigned char	byte;
	struct {
		unsigned char	    :3;
		unsigned char	P94 :1;
		unsigned char	P93 :1;
		unsigned char	P92 :1;
		unsigned char	P91 :1;
		unsigned char	P90 :1;
	} bit;
};
#elif defined(__CPU_MB91360_SERIES)
union io_pdr9 {
	unsigned char	byte;
	struct {
		unsigned char	P97 :1;
		unsigned char	P96 :1;
		unsigned char	P95 :1;
		unsigned char	P94 :1;
		unsigned char	P93 :1;
		unsigned char	P92 :1;
		unsigned char	P91 :1;
		unsigned char	P90 :1;
	} bit;
};
#endif

/* structure of PDRA */
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91110_SERIES) || \
      defined(__CPU_MB91121_SERIES)
union io_pdra {
	unsigned char	byte;
	struct {
		unsigned char	    :1;
		unsigned char	PA6 :1;
		unsigned char	PA5 :1;
		unsigned char	PA4 :1;
		unsigned char	PA3 :1;
		unsigned char	PA2 :1;
		unsigned char	PA1 :1;
		unsigned char	    :1;
	} bit;
};
#elif defined(__CPU_MB91103_SERIES) || defined(__CPU_MB91106_SERIES)
union io_pdra {
	unsigned char	byte;
	struct {
		unsigned char	    :1;
		unsigned char	PA6 :1;
		unsigned char	PA5 :1;
		unsigned char	PA4 :1;
		unsigned char	PA3 :1;
		unsigned char	PA2 :1;
		unsigned char	PA1 :1;
		unsigned char	PA0 :1;
	} bit;
};
#elif defined(__CPU_MB91191_SERIES)
union io_pdra {
	unsigned char	byte;
	struct {
		unsigned char	PA7 :1;
		unsigned char	PA6 :1;
		unsigned char	PA5 :1;
		unsigned char	PA4 :1;
		unsigned char	PA3 :1;
		unsigned char	PA2 :1;
		unsigned char	PA1 :1;
		unsigned char	PA0 :1;
	} bit;
};
#endif

/* structure of PDRB */
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91103_SERIES) || \
      defined(__CPU_MB91106_SERIES) || defined(__CPU_MB91110_SERIES) || \
      defined(__CPU_MB91191_SERIES) || defined(__CPU_MB91360_SERIES) || \
      defined(__CPU_MB91121_SERIES)
union io_pdrb {
	unsigned char	byte;
	struct {
		unsigned char	PB7 :1;
		unsigned char	PB6 :1;
		unsigned char	PB5 :1;
		unsigned char	PB4 :1;
		unsigned char	PB3 :1;
		unsigned char	PB2 :1;
		unsigned char	PB1 :1;
		unsigned char	PB0 :1;
	} bit;
};
#endif

/* structure of PDRC */
#if   defined(__CPU_MB91191_SERIES) || defined(__CPU_MB91130_SERIES)
union io_pdrc {
	unsigned char	byte;
	struct {
		unsigned char	PC7 :1;
		unsigned char	PC6 :1;
		unsigned char	PC5 :1;
		unsigned char	PC4 :1;
		unsigned char	PC3 :1;
		unsigned char	PC2 :1;
		unsigned char	PC1 :1;
		unsigned char	PC0 :1;
	} bit;
};
#endif

/* structure of PDRD */
#if   defined(__CPU_MB91103_SERIES) || defined(__CPU_MB91191_SERIES) || \
      defined(__CPU_MB91130_SERIES)
union io_pdrd {
	unsigned char	byte;
	struct {
		unsigned char	PD7 :1;
		unsigned char	PD6 :1;
		unsigned char	PD5 :1;
		unsigned char	PD4 :1;
		unsigned char	PD3 :1;
		unsigned char	PD2 :1;
		unsigned char	PD1 :1;
		unsigned char	PD0 :1;
	} bit;
};
#endif

/* structure of PDRE */
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91103_SERIES) || \
      defined(__CPU_MB91106_SERIES) || defined(__CPU_MB91121_SERIES) || \
      defined(__CPU_MB91130_SERIES)
union io_pdre {
	unsigned char	byte;
	struct {
		unsigned char	PE7 :1;
		unsigned char	PE6 :1;
		unsigned char	PE5 :1;
		unsigned char	PE4 :1;
		unsigned char	PE3 :1;
		unsigned char	PE2 :1;
		unsigned char	PE1 :1;
		unsigned char	PE0 :1;
	} bit;
};
#elif defined(__CPU_MB91110_SERIES)
union io_pdre {
	unsigned char	byte;
	struct {
		unsigned char	    :4;
		unsigned char	PE3 :1;
		unsigned char	PE2 :1;
		unsigned char	PE1 :1;
		unsigned char	PE0 :1;
	} bit;
};
#endif

/* structure of PCRE */
#if   defined(__CPU_MB91130_SERIES)
union io_pcre {
	unsigned char	byte;
	struct {
		unsigned char	    :6;
		unsigned char	PE1 :1;
		unsigned char	PE0 :1;
	} bit;
};
#endif

/* structure of PDRF */
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91103_SERIES) || \
      defined(__CPU_MB91106_SERIES) || defined(__CPU_MB91110_SERIES) || \
      defined(__CPU_MB91121_SERIES) || defined(__CPU_MB91130_SERIES)
union io_pdrf {
	unsigned char	byte;
	struct {
		unsigned char	PF7 :1;
		unsigned char	PF6 :1;
		unsigned char	PF5 :1;
		unsigned char	PF4 :1;
		unsigned char	PF3 :1;
		unsigned char	PF2 :1;
		unsigned char	PF1 :1;
		unsigned char	PF0 :1;
	} bit;
};
#endif

/* structure of PDRG */
#if   defined(__CPU_MB91103_SERIES) || defined(__CPU_MB91360_SERIES) || \
      defined(__CPU_MB91121_SERIES)
union io_pdrg {
	unsigned char	byte;
	struct {
		unsigned char	PG7 :1;
		unsigned char	PG6 :1;
		unsigned char	PG5 :1;
		unsigned char	PG4 :1;
		unsigned char	PG3 :1;
		unsigned char	PG2 :1;
		unsigned char	PG1 :1;
		unsigned char	PG0 :1;
	} bit;
};
#elif defined(__CPU_MB91110_SERIES) || defined(__CPU_MB91130_SERIES)
union io_pdrg {
	unsigned char	byte;
	struct {
		unsigned char	    :2;
		unsigned char	PG5 :1;
		unsigned char	PG4 :1;
		unsigned char	PG3 :1;
		unsigned char	PG2 :1;
		unsigned char	PG1 :1;
		unsigned char	PG0 :1;
	} bit;
};
#endif

/* structure of PDRH */
#if   defined(__CPU_MB91103_SERIES) || defined(__CPU_MB91110_SERIES) || \
      defined(__CPU_MB91360_SERIES)
union io_pdrh {
	unsigned char	byte;
	struct {
		unsigned char	PH7 :1;
		unsigned char	PH6 :1;
		unsigned char	PH5 :1;
		unsigned char	PH4 :1;
		unsigned char	PH3 :1;
		unsigned char	PH2 :1;
		unsigned char	PH1 :1;
		unsigned char	PH0 :1;
	} bit;
};
#elif defined(__CPU_MB91121_SERIES)
union io_pdrh {
	unsigned char	byte;
	struct {
		unsigned char	PH7 :1;
		unsigned char	PH6 :1;
		unsigned char	PH5 :1;
		unsigned char	PH4 :1;
		unsigned char	    :4;
	} bit;
};
#elif defined(__CPU_MB91130_SERIES)
union io_pdrh {
	unsigned char	byte;
	struct {
		unsigned char	    :5;
		unsigned char	PH2 :1;
		unsigned char	PH1 :1;
		unsigned char	PH0 :1;
	} bit;
};
#endif

/* structure of PDRI */
#if   defined(__CPU_MB91103_SERIES)
union io_pdri {
	unsigned char	byte;
	struct {
		unsigned char	    :4;
		unsigned char	PI3 :1;
		unsigned char	PI2 :1;
		unsigned char	PI1 :1;
		unsigned char	PI0 :1;
	} bit;
};
#elif defined(__CPU_MB91110_SERIES)
union io_pdri {
	unsigned char	byte;
	struct {
		unsigned char	PI7 :1;
		unsigned char	PI6 :1;
		unsigned char	PI5 :1;
		unsigned char	PI4 :1;
		unsigned char	PI3 :1;
		unsigned char	PI2 :1;
		unsigned char	PI1 :1;
		unsigned char	PI0 :1;
	} bit;
};
#elif defined(__CPU_MB91360_SERIES)
union io_pdri {
	unsigned char	byte;
	struct {
		unsigned char	PI7 :1;
		unsigned char	    :3;
		unsigned char	PI3 :1;
		unsigned char	    :3;
	} bit;
};
union io_ddri {
	unsigned char	byte;
	struct {
		unsigned char	    :4;
		unsigned char	PI3 :1;
		unsigned char	    :3;
	} bit;
};
#elif defined(__CPU_MB91121_SERIES)
union io_pdri {
	unsigned char	byte;
	struct {
		unsigned char	    :6;
		unsigned char	PI1 :1;
		unsigned char	PI0 :1;
	} bit;
};
#elif defined(__CPU_MB91130_SERIES)
union io_pdri {
	unsigned char	byte;
	struct {
		unsigned char	    :2;
		unsigned char	PI5 :1;
		unsigned char	PI4 :1;
		unsigned char	PI3 :1;
		unsigned char	PI2 :1;
		unsigned char	PI1 :1;
		unsigned char	PI0 :1;
	} bit;
};
#endif

/* structure of PDRJ */
#if   defined(__CPU_MB91360_SERIES)
union io_pdrj {
	unsigned char	byte;
	struct {
		unsigned char	PJ7 :1;
		unsigned char	PJ6 :1;
		unsigned char	PJ5 :1;
		unsigned char	PJ4 :1;
		unsigned char	PJ3 :1;
		unsigned char	PJ2 :1;
		unsigned char	PJ1 :1;
		unsigned char	PJ0 :1;
	} bit;
};
#elif defined(__CPU_MB91130_SERIES)
union io_pdrj {
	unsigned char	byte;
	struct {
		unsigned char	    :2;
		unsigned char	PJ5 :1;
		unsigned char	PJ4 :1;
		unsigned char	PJ3 :1;
		unsigned char	PJ2 :1;
		unsigned char	PJ1 :1;
		unsigned char	PJ0 :1;
	} bit;
};
#endif

/* structure of PDRK */
#if   defined(__CPU_MB91360_SERIES) || defined(__CPU_MB91130_SERIES)
union io_pdrk {
	unsigned char	byte;
	struct {
		unsigned char	PK7 :1;
		unsigned char	PK6 :1;
		unsigned char	PK5 :1;
		unsigned char	PK4 :1;
		unsigned char	PK3 :1;
		unsigned char	PK2 :1;
		unsigned char	PK1 :1;
		unsigned char	PK0 :1;
	} bit;
};
#endif

/* structure of PDRL */
#if   defined(__CPU_MB91360_SERIES) || defined(__CPU_MB91130_SERIES)
union io_pdrl {
	unsigned char	byte;
	struct {
		unsigned char	PL7 :1;
		unsigned char	PL6 :1;
		unsigned char	PL5 :1;
		unsigned char	PL4 :1;
		unsigned char	PL3 :1;
		unsigned char	PL2 :1;
		unsigned char	PL1 :1;
		unsigned char	PL0 :1;
	} bit;
};
#endif

/* structure of PDRM */
#if   defined(__CPU_MB91360_SERIES)
union io_pdrm {
	unsigned char	byte;
	struct {
		unsigned char	    :4;
		unsigned char	PM3 :1;
		unsigned char	PM2 :1;
		unsigned char	PM1 :1;
		unsigned char	PM0 :1;
	} bit;
};
#endif

/* structure of PDRN */
#if   defined(__CPU_MB91360_SERIES)
union io_pdrn {
	unsigned char	byte;
	struct {
		unsigned char	    :2;
		unsigned char	PN5 :1;
		unsigned char	PN4 :1;
		unsigned char	PN3 :1;
		unsigned char	PN2 :1;
		unsigned char	PN1 :1;
		unsigned char	PN0 :1;
	} bit;
};
#endif

/* structure of PDRO */
#if   defined(__CPU_MB91360_SERIES)
union io_pdro {
	unsigned char	byte;
	struct {
		unsigned char	PO7 :1;
		unsigned char	PO6 :1;
		unsigned char	PO5 :1;
		unsigned char	PO4 :1;
		unsigned char	PO3 :1;
		unsigned char	PO2 :1;
		unsigned char	PO1 :1;
		unsigned char	PO0 :1;
	} bit;
};
#endif

/* structure of PDRP */
#if   defined(__CPU_MB91360_SERIES)
union io_pdrp {
	unsigned char	byte;
	struct {
		unsigned char	PP7 :1;
		unsigned char	PP6 :1;
		unsigned char	PP5 :1;
		unsigned char	PP4 :1;
		unsigned char	PP3 :1;
		unsigned char	PP2 :1;
		unsigned char	PP1 :1;
		unsigned char	PP0 :1;
	} bit;
};
#endif

/* structure of PDRQ */
#if   defined(__CPU_MB91360_SERIES)
union io_pdrq {
	unsigned char	byte;
	struct {
		unsigned char	    :2;
		unsigned char	PQ5 :1;
		unsigned char	PQ4 :1;
		unsigned char	PQ3 :1;
		unsigned char	PQ2 :1;
		unsigned char	PQ1 :1;
		unsigned char	PQ0 :1;
	} bit;
};
#endif

/* structure of PDRR */
#if   defined(__CPU_MB91360_SERIES)
union io_pdrr {
	unsigned char	byte;
	struct {
		unsigned char	PR7 :1;
		unsigned char	PR6 :1;
		unsigned char	PR5 :1;
		unsigned char	PR4 :1;
		unsigned char	PR3 :1;
		unsigned char	PR2 :1;
		unsigned char	PR1 :1;
		unsigned char	PR0 :1;
	} bit;
};
#endif

/* structure of PDRS */
#if   defined(__CPU_MB91360_SERIES)
union io_pdrs {
	unsigned char	byte;
	struct {
		unsigned char	PS7 :1;
		unsigned char	PS6 :1;
		unsigned char	PS5 :1;
		unsigned char	PS4 :1;
		unsigned char	PS3 :1;
		unsigned char	PS2 :1;
		unsigned char	PS1 :1;
		unsigned char	PS0 :1;
	} bit;
};
#endif

/* structure of IO_PORT */
#if   defined(__CPU_MB91101_SERIES)
struct io_port {
	unsigned char	:8;
	unsigned char	IO_DDR2;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	IO_DDR6;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	IO_DDRB;
	unsigned char	IO_DDRA;
	unsigned char	:8;
	unsigned char	IO_DDR8;
};
#elif defined(__CPU_MB91103_SERIES)
struct io_port {
	unsigned char	:8;
	unsigned char	IO_DDR2;
	unsigned char	IO_DDR1;
	unsigned char	IO_DDR0;
	unsigned char	:8;
	unsigned char	IO_DDR6;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	IO_DDRB;
	unsigned char	IO_DDRA;
	unsigned char	IO_DDR9;
	unsigned char	IO_DDR8;
};
#elif defined(__CPU_MB91106_SERIES)
struct io_port {
	unsigned char	IO_DDR3;
	unsigned char	IO_DDR2;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	IO_DDR7;
	unsigned char	IO_DDR6;
	unsigned char	IO_DDR5;
	unsigned char	IO_DDR4;
	unsigned char	IO_DDRB;
	unsigned char	IO_DDRA;
	unsigned char	:8;
	unsigned char	IO_DDR8;
};
#elif defined(__CPU_MB91110_SERIES)
struct io_port {
	unsigned char	:8;
	unsigned char	IO_DDR2;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	IO_DDR6;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	IO_DDRB;
	unsigned char	IO_DDRA;
	unsigned char	:8;
	unsigned char	IO_DDR8;
};
#elif defined(__CPU_MB91191_SERIES)
struct io_port {
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	IO_PFS1;
	unsigned char	:8;
	unsigned char	IO_PFS7;
	unsigned char	IO_PFS6;
	unsigned char	IO_PFS5;
	unsigned char	IO_PFS4;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
};
#elif defined(__CPU_MB91360_SERIES)
struct io_port1 {
	union io_pdrg	IO_DDRG;
	union io_pdrh	IO_DDRH;
	union io_ddri	IO_DDRI;
	union io_pdrj	IO_DDRJ;
	union io_pdrk	IO_DDRK;
	union io_pdrl	IO_DDRL;
	union io_pdrm	IO_DDRM;
	union io_pdrn	IO_DDRN;
	union io_pdro	IO_DDRO;
	union io_pdrp	IO_DDRP;
	union io_pdrq	IO_DDRQ;
	union io_pdrr	IO_DDRR;
	union io_pdrs	IO_DDRS;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	union io_pdrg	IO_PFRG;
	union io_pdrh	IO_PFRH;
	union io_ddri	IO_PFRI;
	union io_pdrj	IO_PFRJ;
	union io_pdrk	IO_PFRK;
	union io_pdrl	IO_PFRL;
	union io_pdrm	IO_PFRM;
	union io_pdrn	IO_PFRN;
	union io_pdro	IO_PFRO;
	union io_pdrp	IO_PFRP;
	union io_pdrq	IO_PFRQ;
	union io_pdrr	IO_PFRR;
	union io_pdrs	IO_PFRS;
};
struct io_port2 {
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	union io_pdr7	IO_DDR7;
	union io_pdr8	IO_DDR8;
	union io_pdr9	IO_DDR9;
	unsigned char	:8;
	union io_pdrb	IO_DDRB;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	union io_pdr7	IO_PFR7;
	union io_pfr8	IO_PFR8;
	union io_pdr9	IO_PFR9;
	unsigned char	:8;
	union io_pdrb	IO_PFRB;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	union io_pdr7	IO_PFR27;
};
#elif defined(__CPU_MB91121_SERIES)
struct io_port {
	unsigned char	:8;
	unsigned char	IO_DDR2;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	IO_DDR6;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	IO_DDRB;
	unsigned char	IO_DDRA;
	unsigned char	:8;
	unsigned char	IO_DDR8;
};
#elif defined(__CPU_MB91130_SERIES)
struct io_port {
	union io_pdr3	IO_DDR3;
	union io_pdr2	IO_DDR2;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	union io_pdr6	IO_DDR6;
	union io_pdr5	IO_DDR5;
	union io_pdr4	IO_DDR4;
	unsigned char	:8;
	unsigned char	:8;
	unsigned char	:8;
	union io_pdr8	IO_DDR8;
};
#endif


/***********************************************************/
/* Sample program for I/O variables of external interrupt. */
/***********************************************************/
/* structure of ENIR */
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91103_SERIES) || \
      defined(__CPU_MB91106_SERIES) || defined(__CPU_MB91110_SERIES) || \
      defined(__CPU_MB91360_SERIES) || defined(__CPU_MB91121_SERIES)
union io_enir {
	unsigned char	byte;
	struct {
		unsigned char	EN7 :1;
		unsigned char	EN6 :1;
		unsigned char	EN5 :1;
		unsigned char	EN4 :1;
		unsigned char	EN3 :1;
		unsigned char	EN2 :1;
		unsigned char	EN1 :1;
		unsigned char	EN0 :1;
	} bit;
};
#endif

/* structure of ENIR0 */
#if   defined(__CPU_MB91130_SERIES)
union io_enir0 {
	unsigned char	byte;
	struct {
		unsigned char	EN7 :1;
		unsigned char	EN6 :1;
		unsigned char	EN5 :1;
		unsigned char	EN4 :1;
		unsigned char	EN3 :1;
		unsigned char	EN2 :1;
		unsigned char	EN1 :1;
		unsigned char	EN0 :1;
	} bit;
};
#endif

/* structure of ENIR1 */
#if   defined(__CPU_MB91130_SERIES)
union io_enir1 {
	unsigned char	byte;
	struct {
		unsigned char	EN15:1;
		unsigned char	EN14:1;
		unsigned char	EN13:1;
		unsigned char	EN12:1;
		unsigned char	EN11:1;
		unsigned char	EN10:1;
		unsigned char	EN9 :1;
		unsigned char	EN8 :1;
	} bit;
};
#endif

/* structure of ENIR2 */
#if   defined(__CPU_MB91130_SERIES)
union io_enir2 {
	unsigned char	byte;
	struct {
		unsigned char	EN23:1;
		unsigned char	EN22:1;
		unsigned char	EN21:1;
		unsigned char	EN20:1;
		unsigned char	EN19:1;
		unsigned char	EN18:1;
		unsigned char	EN17:1;
		unsigned char	EN16:1;
	} bit;
};
#endif

/* structure of EIRR */
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91103_SERIES) || \
      defined(__CPU_MB91106_SERIES) || defined(__CPU_MB91110_SERIES) || \
      defined(__CPU_MB91360_SERIES) || defined(__CPU_MB91121_SERIES)
union io_eirr {
	unsigned char	byte;
	struct {
		unsigned char	ER7 :1;
		unsigned char	ER6 :1;
		unsigned char	ER5 :1;
		unsigned char	ER4 :1;
		unsigned char	ER3 :1;
		unsigned char	ER2 :1;
		unsigned char	ER1 :1;
		unsigned char	ER0 :1;
	} bit;
};
#endif

/* structure of EIRR0 */
#if   defined(__CPU_MB91130_SERIES)
union io_eirr0 {
	unsigned char	byte;
	struct {
		unsigned char	ER7 :1;
		unsigned char	ER6 :1;
		unsigned char	ER5 :1;
		unsigned char	ER4 :1;
		unsigned char	ER3 :1;
		unsigned char	ER2 :1;
		unsigned char	ER1 :1;
		unsigned char	ER0 :1;
	} bit;
};
#endif

/* structure of EIRR1 */
#if   defined(__CPU_MB91130_SERIES)
union io_eirr1 {
	unsigned char	byte;
	struct {
		unsigned char	ER15:1;
		unsigned char	ER14:1;
		unsigned char	ER13:1;
		unsigned char	ER12:1;
		unsigned char	ER11:1;
		unsigned char	ER10:1;
		unsigned char	ER9 :1;
		unsigned char	ER8 :1;
	} bit;
};
#endif

/* structure of EIRR2 */
#if   defined(__CPU_MB91130_SERIES)
union io_eirr2 {
	unsigned char	byte;
	struct {
		unsigned char	ER23:1;
		unsigned char	ER22:1;
		unsigned char	ER21:1;
		unsigned char	ER20:1;
		unsigned char	ER19:1;
		unsigned char	ER18:1;
		unsigned char	ER17:1;
		unsigned char	ER16:1;
	} bit;
};
#endif

/* structure of ELVR */
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91106_SERIES) || \
      defined(__CPU_MB91121_SERIES)
union io_elvr {
	unsigned char	byte;
	struct {
		unsigned char	LBLA3:2;
		unsigned char	LBLA2:2;
		unsigned char	LBLA1:2;
		unsigned char	LBLA0:2;
	} bit;
};
#elif defined(__CPU_MB91103_SERIES) || defined(__CPU_MB91110_SERIES) || \
      defined(__CPU_MB91360_SERIES)
union io_elvr {
	unsigned short	hword;
	struct {
		unsigned short	LBLA7:2;
		unsigned short	LBLA6:2;
		unsigned short	LBLA5:2;
		unsigned short	LBLA4:2;
		unsigned short	LBLA3:2;
		unsigned short	LBLA2:2;
		unsigned short	LBLA1:2;
		unsigned short	LBLA0:2;
	} bit;
};
#endif

/* structure of ELVR0 */
#if   defined(__CPU_MB91130_SERIES)
union io_elvr0 {
	unsigned short	hword;
	struct {
		unsigned short	LBLA7:2;
		unsigned short	LBLA6:2;
		unsigned short	LBLA5:2;
		unsigned short	LBLA4:2;
		unsigned short	LBLA3:2;
		unsigned short	LBLA2:2;
		unsigned short	LBLA1:2;
		unsigned short	LBLA0:2;
	} bit;
};
#endif

/* structure of ELVR1 */
#if   defined(__CPU_MB91130_SERIES)
union io_elvr1 {
	unsigned short	hword;
	struct {
		unsigned short	LBLA15:2;
		unsigned short	LBLA14:2;
		unsigned short	LBLA13:2;
		unsigned short	LBLA12:2;
		unsigned short	LBLA11:2;
		unsigned short	LBLA10:2;
		unsigned short	LBLA9 :2;
		unsigned short	LBLA8 :2;
	} bit;
};
#endif

/* structure of ELVR2 */
#if   defined(__CPU_MB91130_SERIES)
union io_elvr2 {
	unsigned short	hword;
	struct {
		unsigned short	LBLA23:2;
		unsigned short	LBLA22:2;
		unsigned short	LBLA21:2;
		unsigned short	LBLA20:2;
		unsigned short	LBLA19:2;
		unsigned short	LBLA18:2;
		unsigned short	LBLA17:2;
		unsigned short	LBLA16:2;
	} bit;
};
#endif


/****************************************************************/
/* Sample program for I/O variable of delayed interrupt module. */
/****************************************************************/
/* structure of DICR */
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91103_SERIES) || \
      defined(__CPU_MB91106_SERIES) || defined(__CPU_MB91110_SERIES) || \
      defined(__CPU_MB91191_SERIES) || defined(__CPU_MB91360_SERIES) || \
      defined(__CPU_MB91121_SERIES) || defined(__CPU_MB91130_SERIES)
union io_dicr {
	unsigned char	byte;
	struct {
		unsigned char	    :7;
		unsigned char	DLYI:1;
	} bit;
};
#endif


/*******************************************************************/
/* Sample program for I/O variables of interrupt control register. */
/*******************************************************************/
/* structure of ICR00-ICR47 */
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91103_SERIES) || \
      defined(__CPU_MB91106_SERIES) || defined(__CPU_MB91110_SERIES) || \
      defined(__CPU_MB91191_SERIES) || defined(__CPU_MB91360_SERIES) || \
      defined(__CPU_MB91121_SERIES) || defined(__CPU_MB91130_SERIES)
union io_icr {
	unsigned char	byte;
	struct {
		unsigned char	    :3;
		unsigned char	ICR :5;
	} bit;
};
#endif

/* structure of HRCL */
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91103_SERIES) || \
      defined(__CPU_MB91106_SERIES) || defined(__CPU_MB91110_SERIES) || \
      defined(__CPU_MB91121_SERIES) || defined(__CPU_MB91130_SERIES)
union io_hrcl {
	unsigned char	byte;
	struct {
		unsigned char	    :3;
		unsigned char	LVL :5;
	} bit;
};
#elif defined(__CPU_MB91360_SERIES)
union io_hrcl {
	unsigned char	byte;
	struct {
		unsigned char	MHALTI:1;
		unsigned char	      :2;
		unsigned char	LVL   :5;
	} bit;
};
#endif


/*******************************************************/
/* Sample program for I/O variables of DMA controller. */
/*******************************************************/
/* structure of DMACS0 */
#if   defined(__CPU_MB91103_SERIES)
union io_dmacs0 {
	unsigned long	word;
	struct {
		unsigned long	DMAE:1;
		unsigned long	    :1;
		unsigned long	PAUS:1;
		unsigned long	STRG:1;
		unsigned long	DSS :4;
		unsigned long	    :1;
		unsigned long	ERIE:1;
		unsigned long	EDIE:1;
		unsigned long	    :3;
		unsigned long	AKL :1;
		unsigned long	AKOE:1;
		unsigned long	LS  :2;
		unsigned long	IS  :6;
		unsigned long	CPU :4;
		unsigned long	WS  :2;
		unsigned long	    :1;
		unsigned long	MODE:1;
	} bit;
};
#elif defined(__CPU_MB91110_SERIES)
union io_dmacs0 {
	unsigned long	word;
	struct {
		unsigned long	DMAE:1;
		unsigned long	    :1;
		unsigned long	PAUS:1;
		unsigned long	STRG:1;
		unsigned long	    :1;
		unsigned long	DSS :3;
		unsigned long	ERIE:1;
		unsigned long	EDIE:1;
		unsigned long	    :2;
		unsigned long	EPSE:1;
		unsigned long	EPDE:1;
		unsigned long	AKSE:1;
		unsigned long	AKDE:1;
		unsigned long	LS  :2;
		unsigned long	    :1;
		unsigned long	IS  :5;
		unsigned long	    :4;
		unsigned long	WS  :2;
		unsigned long	    :1;
		unsigned long	MODE:1;
	} bit;
};
#endif

/* structure of DMACS1 */
#if   defined(__CPU_MB91103_SERIES)
union io_dmacs1 {
	unsigned long	word;
	struct {
		unsigned long	DMAE:1;
		unsigned long	    :1;
		unsigned long	PAUS:1;
		unsigned long	STRG:1;
		unsigned long	DSS :4;
		unsigned long	    :1;
		unsigned long	ERIE:1;
		unsigned long	EDIE:1;
		unsigned long	    :3;
		unsigned long	AKL :1;
		unsigned long	AKOE:1;
		unsigned long	LS  :2;
		unsigned long	IS  :6;
		unsigned long	CPU :4;
		unsigned long	WS  :2;
		unsigned long	    :1;
		unsigned long	MODE:1;
	} bit;
};
#elif defined(__CPU_MB91110_SERIES)
union io_dmacs1 {
	unsigned long	word;
	struct {
		unsigned long	DMAE:1;
		unsigned long	    :1;
		unsigned long	PAUS:1;
		unsigned long	STRG:1;
		unsigned long	    :1;
		unsigned long	DSS :3;
		unsigned long	ERIE:1;
		unsigned long	EDIE:1;
		unsigned long	    :2;
		unsigned long	EPSE:1;
		unsigned long	EPDE:1;
		unsigned long	AKSE:1;
		unsigned long	AKDE:1;
		unsigned long	LS  :2;
		unsigned long	    :1;
		unsigned long	IS  :5;
		unsigned long	    :4;
		unsigned long	WS  :2;
		unsigned long	    :1;
		unsigned long	MODE:1;
	} bit;
};
#endif

/* structure of DMACS2 */
#if   defined(__CPU_MB91110_SERIES)
union io_dmacs2 {
	unsigned long	word;
	struct {
		unsigned long	DMAE:1;
		unsigned long	    :1;
		unsigned long	PAUS:1;
		unsigned long	STRG:1;
		unsigned long	    :1;
		unsigned long	DSS :3;
		unsigned long	ERIE:1;
		unsigned long	EDIE:1;
		unsigned long	    :2;
		unsigned long	EPSE:1;
		unsigned long	EPDE:1;
		unsigned long	AKSE:1;
		unsigned long	AKDE:1;
		unsigned long	LS  :2;
		unsigned long	    :1;
		unsigned long	IS  :5;
		unsigned long	    :4;
		unsigned long	WS  :2;
		unsigned long	    :1;
		unsigned long	MODE:1;
	} bit;
};
#endif

/* structure of DMACS3 */
#if   defined(__CPU_MB91110_SERIES)
union io_dmacs3 {
	unsigned long	word;
	struct {
		unsigned long	DMAE:1;
		unsigned long	    :1;
		unsigned long	PAUS:1;
		unsigned long	STRG:1;
		unsigned long	    :1;
		unsigned long	DSS :3;
		unsigned long	ERIE:1;
		unsigned long	EDIE:1;
		unsigned long	    :2;
		unsigned long	EPSE:1;
		unsigned long	EPDE:1;
		unsigned long	AKSE:1;
		unsigned long	AKDE:1;
		unsigned long	LS  :2;
		unsigned long	    :1;
		unsigned long	IS  :5;
		unsigned long	    :4;
		unsigned long	WS  :2;
		unsigned long	    :1;
		unsigned long	MODE:1;
	} bit;
};
#endif

/* structure of DMACS4 */
#if   defined(__CPU_MB91103_SERIES)
union io_dmacs4 {
	unsigned long	word;
	struct {
		unsigned long	DMAE:1;
		unsigned long	    :1;
		unsigned long	PAUS:1;
		unsigned long	STRG:1;
		unsigned long	DSS :4;
		unsigned long	    :1;
		unsigned long	ERIE:1;
		unsigned long	EDIE:1;
		unsigned long	    :7;
		unsigned long	IS  :6;
		unsigned long	    :4;
		unsigned long	WS  :2;
		unsigned long	    :1;
		unsigned long	MODE:1;
	} bit;
};
#elif defined(__CPU_MB91110_SERIES)
union io_dmacs4 {
	unsigned long	word;
	struct {
		unsigned long	DMAE:1;
		unsigned long	    :1;
		unsigned long	PAUS:1;
		unsigned long	STRG:1;
		unsigned long	    :1;
		unsigned long	DSS :3;
		unsigned long	ERIE:1;
		unsigned long	EDIE:1;
		unsigned long	    :2;
		unsigned long	EPSE:1;
		unsigned long	EPDE:1;
		unsigned long	AKSE:1;
		unsigned long	AKDE:1;
		unsigned long	LS  :2;
		unsigned long	    :1;
		unsigned long	IS  :5;
		unsigned long	    :4;
		unsigned long	WS  :2;
		unsigned long	    :1;
		unsigned long	MODE:1;
	} bit;
};
#endif

/* structure of DMACS5 */
#if   defined(__CPU_MB91103_SERIES)
union io_dmacs5 {
	unsigned long	word;
	struct {
		unsigned long	DMAE:1;
		unsigned long	    :1;
		unsigned long	PAUS:1;
		unsigned long	STRG:1;
		unsigned long	DSS :4;
		unsigned long	    :1;
		unsigned long	ERIE:1;
		unsigned long	EDIE:1;
		unsigned long	    :7;
		unsigned long	IS  :6;
		unsigned long	    :4;
		unsigned long	WS  :2;
		unsigned long	    :1;
		unsigned long	MODE:1;
	} bit;
};
#endif

/* structure of DMACS6 */
#if   defined(__CPU_MB91103_SERIES)
union io_dmacs6 {
	unsigned long	word;
	struct {
		unsigned long	DMAE:1;
		unsigned long	    :1;
		unsigned long	PAUS:1;
		unsigned long	STRG:1;
		unsigned long	DSS :4;
		unsigned long	    :1;
		unsigned long	ERIE:1;
		unsigned long	EDIE:1;
		unsigned long	    :7;
		unsigned long	IS  :6;
		unsigned long	    :4;
		unsigned long	WS  :2;
		unsigned long	    :1;
		unsigned long	MODE:1;
	} bit;
};
#endif

/* structure of DMACC0 */
#if   defined(__CPU_MB91103_SERIES)
union io_dmacc0 {
	unsigned long	word;
	struct {
		unsigned long	    :9;
		unsigned long	CRS :3;
		unsigned long	    :1;
		unsigned long	CRLD:1;
		unsigned long	DRLD:1;
		unsigned long	SRLD:1;
		unsigned long	DRS :4;
		unsigned long	DCS :2;
		unsigned long	DAS :2;
		unsigned long	SRS :4;
		unsigned long	SCS :2;
		unsigned long	SAS :2;
	} bit;
};
#elif defined(__CPU_MB91110_SERIES)
union io_dmacc0 {
	unsigned long	word;
	struct {
		unsigned long	    :4;
		unsigned long	BLK :4;
		unsigned long	DCS :2;
		unsigned long	SCS :2;
		unsigned long	    :1;
		unsigned long	CRLD:1;
		unsigned long	DRLD:1;
		unsigned long	SRLD:1;
		unsigned long	    :16;
	} bit;
};
#endif

/* structure of DMACC1 */
#if   defined(__CPU_MB91103_SERIES)
union io_dmacc1 {
	unsigned long	word;
	struct {
		unsigned long	    :9;
		unsigned long	CRS :3;
		unsigned long	    :1;
		unsigned long	CRLD:1;
		unsigned long	DRLD:1;
		unsigned long	SRLD:1;
		unsigned long	DRS :4;
		unsigned long	DCS :2;
		unsigned long	DAS :2;
		unsigned long	SRS :4;
		unsigned long	SCS :2;
		unsigned long	SAS :2;
	} bit;
};
#elif defined(__CPU_MB91110_SERIES)
union io_dmacc1 {
	unsigned long	word;
	struct {
		unsigned long	    :4;
		unsigned long	BLK :4;
		unsigned long	DCS :2;
		unsigned long	SCS :2;
		unsigned long	    :1;
		unsigned long	CRLD:1;
		unsigned long	DRLD:1;
		unsigned long	SRLD:1;
		unsigned long	    :16;
	} bit;
};
#endif

/* structure of DMACC2 */
#if   defined(__CPU_MB91110_SERIES)
union io_dmacc2 {
	unsigned long	word;
	struct {
		unsigned long	    :4;
		unsigned long	BLK :4;
		unsigned long	DCS :2;
		unsigned long	SCS :2;
		unsigned long	    :1;
		unsigned long	CRLD:1;
		unsigned long	DRLD:1;
		unsigned long	SRLD:1;
		unsigned long	    :16;
	} bit;
};
#endif

/* structure of DMACC3 */
#if   defined(__CPU_MB91110_SERIES)
union io_dmacc3 {
	unsigned long	word;
	struct {
		unsigned long	    :4;
		unsigned long	BLK :4;
		unsigned long	DCS :2;
		unsigned long	SCS :2;
		unsigned long	    :1;
		unsigned long	CRLD:1;
		unsigned long	DRLD:1;
		unsigned long	SRLD:1;
		unsigned long	    :16;
	} bit;
};
#endif

/* structure of DMACC4 */
#if   defined(__CPU_MB91103_SERIES)
union io_dmacc4 {
	unsigned long	word;
	struct {
		unsigned long	    :9;
		unsigned long	CRS :3;
		unsigned long	    :1;
		unsigned long	CRLD:1;
		unsigned long	DRLD:1;
		unsigned long	SRLD:1;
		unsigned long	DRS :4;
		unsigned long	DCS :2;
		unsigned long	DAS :2;
		unsigned long	SRS :4;
		unsigned long	SCS :2;
		unsigned long	SAS :2;
	} bit;
};
#elif defined(__CPU_MB91110_SERIES)
union io_dmacc4 {
	unsigned long	word;
	struct {
		unsigned long	    :4;
		unsigned long	BLK :4;
		unsigned long	DCS :2;
		unsigned long	SCS :2;
		unsigned long	    :1;
		unsigned long	CRLD:1;
		unsigned long	DRLD:1;
		unsigned long	SRLD:1;
		unsigned long	    :16;
	} bit;
};
#endif

/* structure of DMACC5 */
#if   defined(__CPU_MB91103_SERIES)
union io_dmacc5 {
	unsigned long	word;
	struct {
		unsigned long	    :9;
		unsigned long	CRS :3;
		unsigned long	    :1;
		unsigned long	CRLD:1;
		unsigned long	DRLD:1;
		unsigned long	SRLD:1;
		unsigned long	DRS :4;
		unsigned long	DCS :2;
		unsigned long	DAS :2;
		unsigned long	SRS :4;
		unsigned long	SCS :2;
		unsigned long	SAS :2;
	} bit;
};
#endif

/* structure of DMACC6 */
#if   defined(__CPU_MB91103_SERIES)
union io_dmacc6 {
	unsigned long	word;
	struct {
		unsigned long	    :9;
		unsigned long	CRS :3;
		unsigned long	    :1;
		unsigned long	CRLD:1;
		unsigned long	DRLD:1;
		unsigned long	SRLD:1;
		unsigned long	DRS :4;
		unsigned long	DCS :2;
		unsigned long	DAS :2;
		unsigned long	SRS :4;
		unsigned long	SCS :2;
		unsigned long	SAS :2;
	} bit;
};
#endif

/* structure of DMACA0-DMACA4 */
#if   defined(__CPU_MB91360_SERIES)
union io_dmaca {
	unsigned long	word;
	struct {
		unsigned long	DENB:1;
		unsigned long	PAUS:1;
		unsigned long	STRG:1;
		unsigned long	IS  :5;
		unsigned long	DDNO:4;
		unsigned long	BLK :4;
		unsigned long	DTC :16;
	} bit;
};
#endif

/* structure of DMACB0-DMACB4 */
#if   defined(__CPU_MB91360_SERIES)
union io_dmacb {
	unsigned long	word;
	struct {
		unsigned long	TYPE:2;
		unsigned long	MD  :2;
		unsigned long	WS  :2;
		unsigned long	SADM:1;
		unsigned long	DADM:1;
		unsigned long	DTCR:1;
		unsigned long	SADR:1;
		unsigned long	DADR:1;
		unsigned long	ERIE:1;
		unsigned long	EDIE:1;
		unsigned long	DSS :3;
		unsigned long	SASZ:8;
		unsigned long	DASZ:8;
	} bit;
};
#endif

/* structure of DMACR */
#if   defined(__CPU_MB91103_SERIES)
union io_dmacr {
	unsigned long	word;
	struct {
		unsigned long	    :16;
		unsigned long	DMAE:1;
		unsigned long	DMAH:1;
		unsigned long	    :11;
		unsigned long	PM45:1;
		unsigned long	    :1;
		unsigned long	PM01:1;
	} bit;
};
#elif defined(__CPU_MB91110_SERIES)
union io_dmacr {
	unsigned long	word;
	struct {
		unsigned long	    :16;
		unsigned long	DMAE:1;
		unsigned long	DMAH:1;
		unsigned long	    :13;
		unsigned long	PM01:1;
	} bit;
};
#elif defined(__CPU_MB91360_SERIES)
union io_dmacr {
	unsigned long	word;
	struct {
		unsigned long	DMAE:1;
		unsigned long	    :2;
		unsigned long	PM01:1;
		unsigned long	DMAH:4;
		unsigned long	    :24;
	} bit;
};
#endif

/* structure of DACSR */
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91106_SERIES) || \
      defined(__CPU_MB91121_SERIES) || defined(__CPU_MB91130_SERIES)
union io_dacsr {
	unsigned long	word;
	struct {
		unsigned long	DER7:1;
		unsigned long	DED7:1;
		unsigned long	DIE7:1;
		unsigned long	DOE7:1;
		unsigned long	DER6:1;
		unsigned long	DED6:1;
		unsigned long	DIE6:1;
		unsigned long	DOE6:1;
		unsigned long	DER5:1;
		unsigned long	DED5:1;
		unsigned long	DIE5:1;
		unsigned long	DOE5:1;
		unsigned long	DER4:1;
		unsigned long	DED4:1;
		unsigned long	DIE4:1;
		unsigned long	DOE4:1;
		unsigned long	DER3:1;
		unsigned long	DED3:1;
		unsigned long	DIE3:1;
		unsigned long	DOE3:1;
		unsigned long	DER2:1;
		unsigned long	DED2:1;
		unsigned long	DIE2:1;
		unsigned long	DOE2:1;
		unsigned long	DER1:1;
		unsigned long	DED1:1;
		unsigned long	DIE1:1;
		unsigned long	DOE1:1;
		unsigned long	DER0:1;
		unsigned long	DED0:1;
		unsigned long	DIE0:1;
		unsigned long	DOE0:1;
	} bit;
};
#endif

/* structure of DATCR */
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91106_SERIES) || \
      defined(__CPU_MB91121_SERIES) || defined(__CPU_MB91130_SERIES)
union io_datcr {
	unsigned long	word;
	struct {
		unsigned long	     :10;
		unsigned long	LS2  :2;
		unsigned long	AKSE2:1;
		unsigned long	AKDE2:1;
		unsigned long	EPSE2:1;
		unsigned long	EPDE2:1;
		unsigned long	     :2;
		unsigned long	LS1  :2;
		unsigned long	AKSE1:1;
		unsigned long	AKDE1:1;
		unsigned long	EPSE1:1;
		unsigned long	EPDE1:1;
		unsigned long	     :2;
		unsigned long	LS0  :2;
		unsigned long	AKSE0:1;
		unsigned long	AKDE0:1;
		unsigned long	EPSE0:1;
		unsigned long	EPDE0:1;
	} bit;
};
#endif

/* structure of DMAD */
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91106_SERIES) || \
      defined(__CPU_MB91121_SERIES) || defined(__CPU_MB91130_SERIES)
struct io_dmad {
	struct {
		unsigned long	DMACT :16;
		unsigned long	      :4;
		unsigned long	BLK   :4;
		unsigned long	SCSDCS:4;
		unsigned long	WS    :2;
		unsigned long	MOD   :2;
	} bit;
	unsigned long	IO_SADR;
	unsigned long	IO_DADR;
};
#elif defined(__CPU_MB91360_SERIES)
struct io_dmad {
	unsigned long	IO_DMASA0;
	unsigned long	IO_DMADA0;
	unsigned long	IO_DMASA1;
	unsigned long	IO_DMADA1;
	unsigned long	IO_DMASA2;
	unsigned long	IO_DMADA2;
	unsigned long	IO_DMASA3;
	unsigned long	IO_DMADA3;
	unsigned long	IO_DMASA4;
	unsigned long	IO_DMADA4;
};
#endif

/* structure of STRG */
#if   defined(__CPU_MB91121_SERIES)
union io_strg {
	unsigned char	byte;
	struct {
		unsigned char	    :6;
		unsigned char	CLRX:1;
		unsigned char	TRG :1;
	} bit;
};
#endif


/***********************************************************************/
/* Sample program for I/O variables of I/O extendted serial interface. */
/***********************************************************************/
/* structure of SMCS */
#if   defined(__CPU_MB91103_SERIES)
union io_smcs {
	unsigned short	hword;
	struct {
		unsigned short	SMD :3;
		unsigned short	SIE :1;
		unsigned short	SIR :1;
		unsigned short	BUSY:1;
		unsigned short	STOP:1;
		unsigned short	STRT:1;
		unsigned short	    :4;
		unsigned short	MODE:1;
		unsigned short	BDS :1;
		unsigned short	SOE :1;
		unsigned short	SCOE:1;
	} bit;
};
#elif defined(__CPU_MB91360_SERIES)
union io_smcs {
	unsigned short	hword;
	struct {
		unsigned short	SMD :3;
		unsigned short	SIE :1;
		unsigned short	SIR :1;
		unsigned short	BUSY:1;
		unsigned short	STOP:1;
		unsigned short	STRT:1;
		unsigned short	    :4;
		unsigned short	MODE:1;
		unsigned short	BDS :1;
		unsigned short	    :1;
		unsigned short	SCOE:1;
	} bit;
};
#endif

/* structure of SES */
#if   defined(__CPU_MB91360_SERIES)
union io_ses {
	unsigned char	byte;
	struct {
		unsigned char	    :6;
		unsigned char	DBL :1;
		unsigned char	NEG :1;
	} bit;
};
#endif


/************************************************/
/* Sample program for I/O variables of U-TIMER. */
/************************************************/
/* structure of UTIMC0-UTIMC2 */
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91103_SERIES) || \
      defined(__CPU_MB91106_SERIES) || defined(__CPU_MB91121_SERIES)
union io_utimc {
	unsigned char	byte;
	struct {
		unsigned char	UCC1:1;
		unsigned char	    :2;
		unsigned char	UTIE:1;
		unsigned char	UNDR:1;
		unsigned char	CLKS:1;
		unsigned char	UTST:1;
		unsigned char	UTCR:1;
	} bit;
};
#elif defined(__CPU_MB91360_SERIES)
union io_utimc {
	unsigned char	byte;
	struct {
		unsigned char	UCC1:1;
		unsigned char	    :2;
		unsigned char	UTIE:1;
		unsigned char	UNDR:1;
		unsigned char	    :1;
		unsigned char	UTST:1;
		unsigned char	UTCR:1;
	} bit;
};
#endif


/*********************************************/
/* Sample program for I/O variables of UART. */
/*********************************************/
/* structure of SMR0-SMR4 */
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91103_SERIES) || \
      defined(__CPU_MB91106_SERIES) || defined(__CPU_MB91121_SERIES)
union io_smr {
	unsigned char	byte;
	struct {
		unsigned char	MD  :2;
		unsigned char	    :4;
		unsigned char	SCKE:1;
		unsigned char	SOE :1;
	} bit;
};
#elif defined(__CPU_MB91110_SERIES) || defined(__CPU_MB91130_SERIES)
union io_smr {
	unsigned char	byte;
	struct {
		unsigned char	MD  :2;
		unsigned char	CS  :3;
		unsigned char	    :1;
		unsigned char	SCKE:1;
		unsigned char	SOE :1;
	} bit;
};
#elif defined(__CPU_MB91360_SERIES)
union io_smr {
	unsigned char	byte;
	struct {
		unsigned char	MD  :2;
		unsigned char	    :4;
		unsigned char	SCKE:1;
		unsigned char	    :1;
	} bit;
};
#endif

/* structure of SCR0-SCR4 */
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91103_SERIES) || \
      defined(__CPU_MB91106_SERIES) || defined(__CPU_MB91110_SERIES) || \
      defined(__CPU_MB91360_SERIES) || defined(__CPU_MB91121_SERIES)
union io_scr {
	unsigned char	byte;
	struct {
		unsigned char	PEN :1;
		unsigned char	P   :1;
		unsigned char	SBL :1;
		unsigned char	CL  :1;
		unsigned char	AD  :1;
		unsigned char	REC :1;
		unsigned char	RXE :1;
		unsigned char	TXE :1;
	} bit;
};
#elif defined(__CPU_MB91130_SERIES)
union io_scr {
	unsigned char	byte;
	struct {
		unsigned char	PEN :1;
		unsigned char	P   :1;
		unsigned char	SBL :1;
		unsigned char	CL  :1;
		unsigned char	AD  :1;
		unsigned char	    :1;
		unsigned char	RXE :1;
		unsigned char	TXE :1;
	} bit;
};
#endif

/* structure of SSR0-SSR4 */
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91103_SERIES) || \
      defined(__CPU_MB91106_SERIES) || defined(__CPU_MB91110_SERIES) || \
      defined(__CPU_MB91360_SERIES) || defined(__CPU_MB91121_SERIES)
union io_ssr {
	unsigned char	byte;
	struct {
		unsigned char	PE  :1;
		unsigned char	ORE :1;
		unsigned char	FRE :1;
		unsigned char	RDRF:1;
		unsigned char	TDRE:1;
		unsigned char	    :1;
		unsigned char	RIE :1;
		unsigned char	TIE :1;
	} bit;
};
#elif defined(__CPU_MB91130_SERIES)
union io_ssr {
	unsigned char	byte;
	struct {
		unsigned char	PE  :1;
		unsigned char	ORE :1;
		unsigned char	FRE :1;
		unsigned char	RDRF:1;
		unsigned char	TDRE:1;
		unsigned char	BDS :1;
		unsigned char	RIE :1;
		unsigned char	TIE :1;
	} bit;
};
#endif

/* structure of CDCR */
#if   defined(__CPU_MB91110_SERIES)
union io_cdcr {
	unsigned char	byte;
	struct {
		unsigned char	MD  :1;
		unsigned char	    :2;
		unsigned char	DIV :5;
	} bit;
};
#elif defined(__CPU_MB91360_SERIES) || defined(__CPU_MB91130_SERIES)
union io_cdcr {
	unsigned char	byte;
	struct {
		unsigned char	MD  :1;
		unsigned char	    :3;
		unsigned char	DIV :4;
	} bit;
};
#endif

/* structure of ULS0-ULS2 */
#if   defined(__CPU_MB91360_SERIES)
union io_uls {
	unsigned char	byte;
	struct {
		unsigned char	     :4;
		unsigned char	NSDO :1;
		unsigned char	NSDI :1;
		unsigned char	UTDBL:1;
		unsigned char	UDBL :1;
	} bit;
};
#endif


/******************************************************/
/* Sample program for I/O variables of A/D converter. */
/******************************************************/
/* structure of ADCS */
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91103_SERIES) || \
      defined(__CPU_MB91106_SERIES) || defined(__CPU_MB91110_SERIES) || \
      defined(__CPU_MB91121_SERIES) || defined(__CPU_MB91130_SERIES)
union io_adcs {
	unsigned short	hword;
	struct {
		unsigned short	BUSY:1;
		unsigned short	INT :1;
		unsigned short	INTE:1;
		unsigned short	PAUS:1;
		unsigned short	STS :2;
		unsigned short	STRT:1;
		unsigned short	    :1;
		unsigned short	MD  :2;
		unsigned short	ANS :3;
		unsigned short	ANE :3;
	} bit;
};
#elif defined(__CPU_MB91360_SERIES)
union io_adcs {
	unsigned char	byte;
	struct {
		unsigned char	BUSY:1;
		unsigned char	INT :1;
		unsigned char	INTE:1;
		unsigned char	PAUS:1;
		unsigned char	    :2;
		unsigned char	STRT:1;
		unsigned char	    :1;
	} bit;
};
#endif

/* structure of ADCR */
#if   defined(__CPU_MB91130_SERIES)
union io_adcr {
	unsigned short	hword;
	struct {
		unsigned short	      :6;
		unsigned short	DATA10:10;
	} bit;
	struct {
		unsigned short	      :8;
		unsigned short	DATA8 :8;
	} bitc;
};
#endif

/* structure of ADC */
#if   defined(__CPU_MB91191_SERIES)
union io_adc {
	unsigned short	hword;
	struct {
		unsigned short	    :3;
		unsigned short	ADMV:1;
		unsigned short	HCNS:1;
		unsigned short	HCS :1;
		unsigned short	SCS :1;
		unsigned short	SSTR:1;
		unsigned short	    :5;
		unsigned short	HI  :3;
	} bit;
};
#endif

/* structure of ADCH */
#if   defined(__CPU_MB91360_SERIES)
union io_adch {
	unsigned char	byte;
	struct {
		unsigned char	ANS :4;
		unsigned char	ANE :4;
	} bit;
};
#endif

/* structure of ADMD */
#if   defined(__CPU_MB91360_SERIES)
union io_admd {
	unsigned char	byte;
	struct {
		unsigned char	    :4;
		unsigned char	MOD :2;
		unsigned char	STS :2;
	} bit;
};
#endif

/* structure of ADBL */
#if   defined(__CPU_MB91360_SERIES)
union io_adbl {
	unsigned char	byte;
	struct {
		unsigned char	    :7;
		unsigned char	DBL :1;
	} bit;
};
#endif

/* structure of SCIS */
#if   defined(__CPU_MB91191_SERIES)
union io_scis {
	unsigned short	hword;
	struct {
		unsigned short	IF  :1;
		unsigned short	IE  :1;
		unsigned short	ID  :1;
		unsigned short	IC  :1;
		unsigned short	IB  :1;
		unsigned short	IA  :1;
		unsigned short	I9  :1;
		unsigned short	I8  :1;
		unsigned short	I7  :1;
		unsigned short	I6  :1;
		unsigned short	I5  :1;
		unsigned short	I4  :1;
		unsigned short	I3  :1;
		unsigned short	I2  :1;
		unsigned short	I1  :1;
		unsigned short	I0  :1;
	} bit;
};
#endif

/* structure of SCFD */
#if   defined(__CPU_MB91191_SERIES)
union io_scfd {
	unsigned short	hword;
	struct {
		unsigned short	C   :4;
		unsigned short	    :2;
		unsigned short	D   :10;
	} bit;
};
#endif

/* structure of SCSR */
#if   defined(__CPU_MB91191_SERIES)
union io_scsr {
	unsigned char	byte;
	struct {
		unsigned char	SCEF:1;
		unsigned char	SECR:1;
		unsigned char	SCIE:1;
		unsigned char	    :2;
		unsigned char	SFCR:1;
		unsigned char	SFUL:1;
		unsigned char	SEMP:1;
	} bit;
};
#endif

/* structure of HCSR */
#if   defined(__CPU_MB91191_SERIES)
union io_hcsr {
	unsigned char	byte;
	struct {
		unsigned char	HCEF:1;
		unsigned char	HECR:1;
		unsigned char	HCIE:1;
		unsigned char	    :2;
		unsigned char	HFCR:1;
		unsigned char	HFUL:1;
		unsigned char	HEMP:1;
	} bit;
};
#endif

/* structure of HCFD */
#if   defined(__CPU_MB91191_SERIES)
union io_hcfd {
	unsigned short	hword;
	struct {
		unsigned short	RS  :1;
		unsigned short	C   :3;
		unsigned short	    :2;
		unsigned short	D   :10;
	} bit;
};
#endif


/*****************************************************/
/* Sample program for I/O variables of 16-bit timer. */
/*****************************************************/
/* struture of T0CR-T4CR */
#if   defined(__CPU_MB91191_SERIES)
union io_tncr {
	unsigned short	hword;
	struct {
		unsigned short	    :5;
		unsigned short	FCLR:1;
		unsigned short	IFLG:1;
		unsigned short	TIE :1;
		unsigned short	    :3;
		unsigned short	LREQ:1;
		unsigned short	LFLG:1;
		unsigned short	TC  :2;
		unsigned short	TSTR:1;
	} bit;
};
#endif


/***************************************************************/
/* Sample program for I/O variables of 8/16-bit timer/counter. */
/***************************************************************/
/* struture of T5CR1 */
#if   defined(__CPU_MB91191_SERIES)
union io_t5cr1 {
	unsigned char	byte;
	struct {
		unsigned char	TIF1 :1;
		unsigned char	TFCR1:1;
		unsigned char	TIE1 :1;
		unsigned char	     :1;
		unsigned char	TCS1 :3;
		unsigned char	TSTR1:1;
	} bit;
};
#endif

/* struture of T5CR0 */
#if   defined(__CPU_MB91191_SERIES)
union io_t5cr0 {
	unsigned char	byte;
	struct {
		unsigned char	TIF0 :1;
		unsigned char	TFCR0:1;
		unsigned char	TIE0 :1;
		unsigned char	CINV :1;
		unsigned char	TCS0 :3;
		unsigned char	TSTR0:1;
	} bit;
};
#endif

/* struture of T5DR */
#if   defined(__CPU_MB91191_SERIES)
union io_t5dr {
	unsigned short	hword;
	struct {
		unsigned char	T5DR1;
		unsigned char	T5DR0;
	} byte;
};
#endif

/* struture of T5CD */
#if   defined(__CPU_MB91191_SERIES)
union io_t5cd {
	unsigned short	hword;
	struct {
		unsigned char	T5CD1;
		unsigned char	T5CD0;
	} byte;
};
#endif


/************************************************************/
/* Sample program for I/O variables of 16-bit reload timer. */
/************************************************************/
/* struture of TMCSR0-TMCSR5 */
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91103_SERIES) || \
      defined(__CPU_MB91106_SERIES) || defined(__CPU_MB91110_SERIES) || \
      defined(__CPU_MB91121_SERIES) || defined(__CPU_MB91130_SERIES)
union io_tmcsr {
	unsigned short	hword;
	struct {
		unsigned short	    :4;
		unsigned short	CSL :2;
		unsigned short	MOD :3;
		unsigned short	OUTE:1;
		unsigned short	OUTL:1;
		unsigned short	RELD:1;
		unsigned short	INTE:1;
		unsigned short	UF  :1;
		unsigned short	CNTE:1;
		unsigned short	TRG :1;
	} bit;
};
#elif defined(__CPU_MB91360_SERIES)
union io_tmcsr {
	unsigned short	hword;
	struct {
		unsigned short	    :4;
		unsigned short	CSL :2;
		unsigned short	    :5;
		unsigned short	RELD:1;
		unsigned short	INTE:1;
		unsigned short	UF  :1;
		unsigned short	CNTE:1;
		unsigned short	TRG :1;
	} bit;
};
#endif


/**************************************************/
/* Sample program for I/O variables of PWM timer. */
/**************************************************/
/* struture of PCN0-PCN7 */
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91106_SERIES) || \
      defined(__CPU_MB91110_SERIES) || defined(__CPU_MB91121_SERIES) || \
      defined(__CPU_MB91130_SERIES)
union io_pcn {
	unsigned short	hword;
	struct {
		unsigned short	CNTE:1;
		unsigned short	STGR:1;
		unsigned short	MDSE:1;
		unsigned short	RTRG:1;
		unsigned short	CKS :2;
		unsigned short	PGMS:1;
		unsigned short	    :1;
		unsigned short	EGS :2;
		unsigned short	IREN:1;
		unsigned short	IRQF:1;
		unsigned short	IRS :2;
		unsigned short	POEN:1;
		unsigned short	OSEL:1;
	} bit;
};
#elif defined(__CPU_MB91360_SERIES)
union io_pcn {
	unsigned short	hword;
	struct {
		unsigned short	CNTE:1;
		unsigned short	STGR:1;
		unsigned short	MDSE:1;
		unsigned short	RTRG:1;
		unsigned short	CKS :2;
		unsigned short	PGMS:1;
		unsigned short	    :1;
		unsigned short	EGS :2;
		unsigned short	IREN:1;
		unsigned short	IRQF:1;
		unsigned short	IRS :2;
		unsigned short	    :1;
		unsigned short	OSEL:1;
	} bit;
};
#endif

/* struture of GCN1,GCN10-GCN11 */
#if   defined(__CPU_MB91101_SERIES) || defined(__CPU_MB91106_SERIES) || \
      defined(__CPU_MB91360_SERIES) || defined(__CPU_MB91121_SERIES) || \
      defined(__CPU_MB91130_SERIES)
union io_gcn1 {
	unsigned short	hword;
	struct {
		unsigned short	TSEL3:4;
		unsigned short	TSEL2:4;
		unsigned short	TSEL1:4;
		unsigned short	TSEL0:4;
	} bit;
};
#endif

/* struture of PDBL0/GCN20 */
#if   defined(__CPU_MB91360_SERIES)
union io_gcn20 {
	unsigned short	hword;
	struct {
		unsigned short	    :3;
		unsigned short	DBL3:1;
		unsigned short	DBL2:1;
		unsigned short	DBL1:1;
		unsigned short	DBL0:1;
		unsigned short	DBC0:1;
		unsigned short	    :4;
		unsigned short	EN  :4;
	} bit;
};
#endif

/* struture of PDBL1/GCN21 */
#if   defined(__CPU_MB91360_SERIES)
union io_gcn21 {
	unsigned short	hword;
	struct {
		unsigned short	    :3;
		unsigned short	DBL7:1;
		unsigned short	DBL6:1;
		unsigned short	DBL5:1;
		unsigned short	DBL4:1;
		unsigned short	DBC1:1;
		unsigned short	    :4;
		unsigned short	EN  :4;
	} bit;
};
#endif


/********************************************************/
/* Sample program for I/O variables of Up/Down counter. */
/********************************************************/
/* structure of CCR0,CCR1 */
#if   defined(__CPU_MB91103_SERIES)
union io_ccr {
	unsigned short	hword;
	struct {
		unsigned short	    :1;
		unsigned short	CDCF:1;
		unsigned short	CFIE:1;
		unsigned short	CLKS:1;
		unsigned short	CMS :2;
		unsigned short	CES :2;
		unsigned short	    :1;
		unsigned short	CTUT:1;
		unsigned short	UCRE:1;
		unsigned short	RLDE:1;
		unsigned short	UDCC:1;
		unsigned short	CGSC:1;
		unsigned short	CGE :2;
	} bit;
};
#elif defined(__CPU_MB91130_SERIES)
union io_ccr {
	unsigned short	hword;
	struct {
		unsigned short	M16E:1;
		unsigned short	CDCF:1;
		unsigned short	CFIE:1;
		unsigned short	CLKS:1;
		unsigned short	CMS :2;
		unsigned short	CES :2;
		unsigned short	    :1;
		unsigned short	CTUT:1;
		unsigned short	UCRE:1;
		unsigned short	RLDE:1;
		unsigned short	UDCC:1;
		unsigned short	CGSC:1;
		unsigned short	CGE :2;
	} bit;
};
#endif

/* structure of CSR0,CSR1 */
#if   defined(__CPU_MB91103_SERIES) || defined(__CPU_MB91130_SERIES)
union io_csr {
	unsigned char	byte;
	struct {
		unsigned char	CSTR:1;
		unsigned char	CITE:1;
		unsigned char	UDIE:1;
		unsigned char	CMPF:1;
		unsigned char	OVFF:1;
		unsigned char	UDFF:1;
		unsigned char	UDF :2;
	} bit;
};
#endif


/***********************************************************/
/* Sample program for I/O variables of input/output timer. */
/***********************************************************/
/* structure of TCCS */
#if   defined(__CPU_MB91103_SERIES) || defined(__CPU_MB91360_SERIES)
union io_tccs {
	unsigned char	byte;
	struct {
		unsigned char	    :1;
		unsigned char	IVF :1;
		unsigned char	IVFE:1;
		unsigned char	STOP:1;
		unsigned char	MODE:1;
		unsigned char	CLR :1;
		unsigned char	CLK :2;
	} bit;
};
#elif defined(__CPU_MB91130_SERIES)
union io_tccs {
	unsigned short	hword;
	struct {
		unsigned short	ECLK:1;
		unsigned short	    :2;
		unsigned short	MSI :3;
		unsigned short	ICLR:1;
		unsigned short	ICRE:1;
		unsigned short	IVF :1;
		unsigned short	IVFE:1;
		unsigned short	STOP:1;
		unsigned short	MODE:1;
		unsigned short	SCLR:1;
		unsigned short	CLK :3;
	} bit;
};
#endif

/* structure of OCS01 */
#if   defined(__CPU_MB91103_SERIES)
union io_ocs01 {
	unsigned short	hword;
	struct {
		unsigned short	    :3;
		unsigned short	CMOD:1;
		unsigned short	OTE1:1;
		unsigned short	OTE0:1;
		unsigned short	OTD1:1;
		unsigned short	OTD0:1;
		unsigned short	ICP1:1;
		unsigned short	ICP0:1;
		unsigned short	ICE1:1;
		unsigned short	ICE0:1;
		unsigned short	    :2;
		unsigned short	CST1:1;
		unsigned short	CST0:1;
	} bit;
};
#elif defined(__CPU_MB91360_SERIES)
union io_ocs01 {
	unsigned short	hword;
	struct {
		unsigned short	    :3;
		unsigned short	CMOD:1;
		unsigned short	    :2;
		unsigned short	OTD1:1;
		unsigned short	OTD0:1;
		unsigned short	ICP1:1;
		unsigned short	ICP0:1;
		unsigned short	ICE1:1;
		unsigned short	ICE0:1;
		unsigned short	    :2;
		unsigned short	CST1:1;
		unsigned short	CST0:1;
	} bit;
};
#elif defined(__CPU_MB91130_SERIES)
union io_ocs01 {
	unsigned short	hword;
	struct {
		unsigned short	    :3;
		unsigned short	CMOD:1;
		unsigned short	OTE1:1;
		unsigned short	OTE0:1;
		unsigned short	OTD1:1;
		unsigned short	OTD0:1;
		unsigned short	IOP1:1;
		unsigned short	IOP0:1;
		unsigned short	IOE1:1;
		unsigned short	IOE0:1;
		unsigned short	    :2;
		unsigned short	CST1:1;
		unsigned short	CST0:1;
	} bit;
};
#endif

/* structure of OCS23 */
#if   defined(__CPU_MB91103_SERIES)
union io_ocs23 {
	unsigned short	hword;
	struct {
		unsigned short	    :3;
		unsigned short	CMOD:1;
		unsigned short	OTE3:1;
		unsigned short	OTE2:1;
		unsigned short	OTD3:1;
		unsigned short	OTD2:1;
		unsigned short	ICP3:1;
		unsigned short	ICP2:1;
		unsigned short	ICE3:1;
		unsigned short	ICE2:1;
		unsigned short	    :2;
		unsigned short	CST3:1;
		unsigned short	CST2:1;
	} bit;
};
#elif defined(__CPU_MB91360_SERIES)
union io_ocs23 {
	unsigned short	hword;
	struct {
		unsigned short	    :3;
		unsigned short	CMOD:1;
		unsigned short	    :2;
		unsigned short	OTD3:1;
		unsigned short	OTD2:1;
		unsigned short	ICP3:1;
		unsigned short	ICP2:1;
		unsigned short	ICE3:1;
		unsigned short	ICE2:1;
		unsigned short	    :2;
		unsigned short	CST3:1;
		unsigned short	CST2:1;
	} bit;
};
#elif defined(__CPU_MB91130_SERIES)
union io_ocs23 {
	unsigned short	hword;
	struct {
		unsigned short	    :3;
		unsigned short	CMOD:1;
		unsigned short	OTE3:1;
		unsigned short	OTE2:1;
		unsigned short	OTD3:1;
		unsigned short	OTD2:1;
		unsigned short	IOP3:1;
		unsigned short	IOP2:1;
		unsigned short	IOE3:1;
		unsigned short	IOE2:1;
		unsigned short	    :2;
		unsigned short	CST3:1;
		unsigned short	CST2:1;
	} bit;
};
#endif

/* structure of OCS45 */
#if   defined(__CPU_MB91103_SERIES)
union io_ocs45 {
	unsigned short	hword;
	struct {
		unsigned short	    :3;
		unsigned short	CMOD:1;
		unsigned short	OTE5:1;
		unsigned short	OTE4:1;
		unsigned short	OTD5:1;
		unsigned short	OTD4:1;
		unsigned short	ICP5:1;
		unsigned short	ICP4:1;
		unsigned short	ICE5:1;
		unsigned short	ICE4:1;
		unsigned short	    :2;
		unsigned short	CST5:1;
		unsigned short	CST4:1;
	} bit;
};
#elif defined(__CPU_MB91130_SERIES)
union io_ocs45 {
	unsigned short	hword;
	struct {
		unsigned short	    :3;
		unsigned short	CMOD:1;
		unsigned short	OTE5:1;
		unsigned short	OTE4:1;
		unsigned short	OTD5:1;
		unsigned short	OTD4:1;
		unsigned short	IOP5:1;
		unsigned short	IOP4:1;
		unsigned short	IOE5:1;
		unsigned short	IOE4:1;
		unsigned short	    :2;
		unsigned short	CST5:1;
		unsigned short	CST4:1;
	} bit;
};
#endif

/* structure of OCS67 */
#if   defined(__CPU_MB91103_SERIES)
union io_ocs67 {
	unsigned short	hword;
	struct {
		unsigned short	    :3;
		unsigned short	CMOD:1;
		unsigned short	OTE7:1;
		unsigned short	OTE6:1;
		unsigned short	OTD7:1;
		unsigned short	OTD6:1;
		unsigned short	ICP7:1;
		unsigned short	ICP6:1;
		unsigned short	ICE7:1;
		unsigned short	ICE6:1;
		unsigned short	    :2;
		unsigned short	CST7:1;
		unsigned short	CST6:1;
	} bit;
};
#elif defined(__CPU_MB91130_SERIES)
union io_ocs67 {
	unsigned short	hword;
	struct {
		unsigned short	    :3;
		unsigned short	CMOD:1;
		unsigned short	OTE7:1;
		unsigned short	OTE6:1;
		unsigned short	OTD7:1;
		unsigned short	OTD6:1;
		unsigned short	IOP7:1;
		unsigned short	IOP6:1;
		unsigned short	IOE7:1;
		unsigned short	IOE6:1;
		unsigned short	    :2;
		unsigned short	CST7:1;
		unsigned short	CST6:1;
	} bit;
};
#endif

/* structure of ICS01 */
#if   defined(__CPU_MB91103_SERIES) || defined(__CPU_MB91360_SERIES) || \
      defined(__CPU_MB91130_SERIES)
union io_ics01 {
	unsigned char	byte;
	struct {
		unsigned char	ICP1:1;
		unsigned char	ICP0:1;
		unsigned char	ICE1:1;
		unsigned char	ICE0:1;
		unsigned char	EG1 :2;
		unsigned char	EG0 :2;
	} bit;
};
#endif

/* structure of ICS23 */
#if   defined(__CPU_MB91103_SERIES) || defined(__CPU_MB91360_SERIES) || \
      defined(__CPU_MB91130_SERIES)
union io_ics23 {
	unsigned char	byte;
	struct {
		unsigned char	ICP3:1;
		unsigned char	ICP2:1;
		unsigned char	ICE3:1;
		unsigned char	ICE2:1;
		unsigned char	EG3 :2;
		unsigned char	EG2 :2;
	} bit;
};
#endif

/* structure of IOTDBL */
#if   defined(__CPU_MB91360_SERIES)
union io_iotdbl {
	unsigned char	byte;
	struct {
		unsigned char	    :5;
		unsigned char	DBLT:1;
		unsigned char	DBLI:1;
		unsigned char	DBLO:1;
	} bit;
};
#endif


/********************************************************/
/* Sample program for I/O variable of FRC capture unit. */
/********************************************************/
/* structure of CIC0 */
#if   defined(__CPU_MB91191_SERIES)
union io_cic0 {
	unsigned char	byte;
	struct {
		unsigned char	 RF1E:1;
		unsigned char	 RF0E:1;
		unsigned char	 CFGE:1;
		unsigned char	 DFGE:1;
		unsigned char	 EI2E:1;
		unsigned char	 EI1E:1;
		unsigned char	 EI0E:1;
		unsigned char	     :1;
	} bit;
};
#endif

/* structure of CIC1 */
#if   defined(__CPU_MB91191_SERIES)
union io_cic1 {
	unsigned char	byte;
	struct {
		unsigned char	 FCIF:1;
		unsigned char	 FCLR:1;
		unsigned char	 FCIE:1;
		unsigned char	     :2;
		unsigned char	 EIV2:1;
		unsigned char	 EIV1:1;
		unsigned char	 EIV0:1;
	} bit;
};
#endif

/* structure of CPFC */
#if   defined(__CPU_MB91191_SERIES)
union io_cpfc {
	unsigned char	byte;
	struct {
		unsigned char	    :4;
		unsigned char	FUL :1;
		unsigned char	EMP :1;
		unsigned char	CLR :1;
		unsigned char	INC :1;
	} bit;
};
#endif

/* structure of CAPS */
#if   defined(__CPU_MB91191_SERIES)
union io_caps {
	unsigned char	byte;
	struct {
		unsigned char	RFG1:1;
		unsigned char	RFG0:1;
		unsigned char	CFG :1;
		unsigned char	DFG :1;
		unsigned char	EXI2:1;
		unsigned char	EXI1:1;
		unsigned char	EXI0:1;
		unsigned char	SOFT:1;
	} bit;
};
#endif


/*******************************************/
/* Sample program for I/O variable of PPG. */
/*******************************************/
/* structure of PPG */
#if   defined(__CPU_MB91191_SERIES)
struct io_ppg {
	/* structure of PPG0C */
	union {
		unsigned char	byte;
		struct {
			unsigned char	    :4;
			unsigned char	IF  :1;
			unsigned char	FCLR:1;
			unsigned char	IE  :1;
			unsigned char	ST  :1;
		} bit;
	} IO_PPG0C;

	unsigned char	IO_PPG0SA;

	unsigned char	:8;
	unsigned char	:8;

	/* structure of PPG1C */
	union {
		unsigned char	byte;
		struct {
			unsigned char	    :4;
			unsigned char	IF  :1;
			unsigned char	FCLR:1;
			unsigned char	IE  :1;
			unsigned char	ST  :1;
		} bit;
	} IO_PPG1C;

	unsigned char	IO_PPG1SA;

	unsigned char	:8;
	unsigned char	:8;
};
#endif


/*******************************************/
/* Sample program for I/O variable of RTG. */
/*******************************************/
/* structure of RTG0C */
#if   defined(__CPU_MB91191_SERIES)
union io_rtg0c {
	unsigned char	byte;
	struct {
		unsigned char	IF  :1;
		unsigned char	FCLR:1;
		unsigned char	IE  :1;
		unsigned char	OUTE:1;
		unsigned char	TSEL:1;
		unsigned char	CLR :1;
		unsigned char	FUL :1;
		unsigned char	EMP :1;
	} bit;
};
#endif

/* structure of RTG1C */
#if   defined(__CPU_MB91191_SERIES)
union io_rtg1c {
	unsigned char	byte;
	struct {
		unsigned char	IF  :1;
		unsigned char	FCLR:1;
		unsigned char	IE  :1;
		unsigned char	OUTE:1;
		unsigned char	    :1;
		unsigned char	CLR :1;
		unsigned char	FUL :1;
		unsigned char	EMP :1;
	} bit;
};
#endif

/* structure of RTG2C */
#if   defined(__CPU_MB91191_SERIES)
union io_rtg2c {
	unsigned char	byte;
	struct {
		unsigned char	IF  :1;
		unsigned char	FCLR:1;
		unsigned char	IE  :1;
		unsigned char	OUTE:1;
		unsigned char	    :1;
		unsigned char	CLR :1;
		unsigned char	FUL :1;
		unsigned char	EMP :1;
	} bit;
};
#endif

/* structure of RTG0D-RTG2D */
#if   defined(__CPU_MB91191_SERIES)
union io_rtgd {
	unsigned char	byte;
	struct {
		unsigned char	    :3;
		unsigned char	OD  :5;
	} bit;
};
#endif


/************************************************************************/
/* Sample program for I/O variable of 10-bit general-purpose prescaler. */
/************************************************************************/
/* structure of GPRC */
#if   defined(__CPU_MB91191_SERIES)
union io_gprc {
	unsigned char	byte;
	struct {
		unsigned char	    :2;
		unsigned char	INV :1;
		unsigned char	OM  :1;
		unsigned char	LDM :1;
		unsigned char	PCS :2;
		unsigned char	ST  :1;
	} bit;
};
#endif


/**************************************************/
/* Sample program for I/O variable of serial I/O. */
/**************************************************/
/* structure of SIO */
#if   defined(__CPU_MB91191_SERIES)
struct io_sio {
	/* structure of S0CR */
	union {
		unsigned char	byte;
		struct {
			unsigned char	SIF :1;
			unsigned char	ICLR:1;
			unsigned char	SIE :1;
			unsigned char	CSAF:1;
			unsigned char	ACLR:1;
			unsigned char	CSE :1;
			unsigned char	DIR :1;
			unsigned char	ST  :1;
		} bit;
	} IO_S0CR;

	/* structure of S0MR */
	union {
		unsigned char	byte;
		struct {
			unsigned char	    :3;
			unsigned char	IC  :2;
			unsigned char	SC  :3;
		} bit;
	} IO_S0MR;

	unsigned char	IO_S0AO;

	/* structure of S0BR */
	union {
		unsigned char	byte;
		struct {
			unsigned char	BMOD:1;
			unsigned char	BC  :7;
		} bit;
	} IO_S0BR;

	/* structure of S1CR */
	union {
		unsigned char	byte;
		struct {
			unsigned char	SIF :1;
			unsigned char	ICLR:1;
			unsigned char	SIE :1;
			unsigned char	CSAF:1;
			unsigned char	ACLR:1;
			unsigned char	CSE :1;
			unsigned char	DIR :1;
			unsigned char	ST  :1;
		} bit;
	} IO_S1CR;

	/* structure of S1MR */
	union {
		unsigned char	byte;
		struct {
			unsigned char	    :3;
			unsigned char	IC  :2;
			unsigned char	SC  :3;
		} bit;
	} IO_S1MR;

	unsigned char	IO_S1AO;

	/* structure of S1BR */
	union {
		unsigned char	byte;
		struct {
			unsigned char	BMOD:1;
			unsigned char	BC  :7;
		} bit;
	} IO_S1BR;

	/* structure of S2CR */
	union {
		unsigned char	byte;
		struct {
			unsigned char	SIF :1;
			unsigned char	ICLR:1;
			unsigned char	SIE :1;
			unsigned char	CSAF:1;
			unsigned char	ACLR:1;
			unsigned char	CSE :1;
			unsigned char	DIR :1;
			unsigned char	ST  :1;
		} bit;
	} IO_S2CR;

	/* structure of S2MR */
	union {
		unsigned char	byte;
		struct {
			unsigned char	    :3;
			unsigned char	IC  :2;
			unsigned char	SC  :3;
		} bit;
	} IO_S2MR;

	unsigned char	IO_S2AO;

	/* structure of S2BR */
	union {
		unsigned char	byte;
		struct {
			unsigned char	BMOD:1;
			unsigned char	BC  :7;
		} bit;
	} IO_S2BR;

};
#endif


/*************************************************/
/* Sample program for I/O variable of I-RAM/ROM. */
/*************************************************/
/* structure of IRMC */
#if   defined(__CPU_MB91110_SERIES)
union io_irmc {
	unsigned long	word;
	struct {
		unsigned long	    :31;
		unsigned long	IRMD:1;
	} bit;
};
#endif


/***************************************************/
/* Sample program for I/O variable of servo input. */
/***************************************************/
/* structure of CAPC */
#if   defined(__CPU_MB91191_SERIES)
union io_capc {
	unsigned char	byte;
	struct {
		unsigned char	CFGD:1;
		unsigned char	FCLR:1;
		unsigned char	CMTS:1;
		unsigned char	MTCS:1;
		unsigned char	    :3;
		unsigned char	DUB :1;
	} bit;
};
#endif

/* structure of DRMC */
#if   defined(__CPU_MB91191_SERIES)
union io_drmc {
	unsigned char	byte;
	struct {
		unsigned char	DFGD :1;
		unsigned char	DFCLR:1;
		unsigned char	DMTS :1;
		unsigned char	MTCS :1;
		unsigned char	DINV :1;
		unsigned char	DPGD :1;
		unsigned char	DPCLR:1;
		unsigned char	DPGE :1;
	} bit;
};
#endif

/* structure of DRMDVC */
#if   defined(__CPU_MB91191_SERIES)
union io_drmdvc {
	unsigned char	byte;
	struct {
		unsigned char	    :4;
		unsigned char	DIV :4;
	} bit;
};
#endif

/* structure of RLC */
#if   defined(__CPU_MB91191_SERIES)
union io_rlc {
	unsigned char	byte;
	struct {
		unsigned char	RL1D  :1;
		unsigned char	R1FCLR:1;
		unsigned char	R1MTS :1;
		unsigned char	R1MTCS:1;
		unsigned char	RL0D  :1;
		unsigned char	R0FCLR:1;
		unsigned char	R0MTS :1;
		unsigned char	R0MTCS:1;
	} bit;
};
#endif


/**************************************************/
/* Sample program for I/O variable of 12-bit PWM. */
/**************************************************/
/* structure of PWM0C,PWM1C */
#if   defined(__CPU_MB91191_SERIES)
union io_pwmc {
	unsigned char	byte;
	struct {
		unsigned char	TEST:1;
		unsigned char	    :3;
		unsigned char	STR :1;
		unsigned char	CKS :1;
		unsigned char	LFLG:1;
		unsigned char	LREQ:1;
	} bit;
};
#endif


/*************************************************/
/* Sample program for I/O variable of 8-bit PWC. */
/*************************************************/
/* structure of PWCC */
#if   defined(__CPU_MB91191_SERIES)
union io_pwcc {
	unsigned char	byte;
	struct {
		unsigned char	TEST:1;
		unsigned char	    :3;
		unsigned char	CAPE:1;
		unsigned char	CAPF:1;
		unsigned char	MSKE:1;
		unsigned char	ST  :1;
	} bit;
};
#endif


/**********************************************************/
/* Sample program for I/O variable of external interrupt. */
/**********************************************************/
/* structure of KEYC */
#if   defined(__CPU_MB91191_SERIES)
union io_keyc {
	unsigned char	byte;
	struct {
		unsigned char	KIE7:1;
		unsigned char	KIE6:1;
		unsigned char	KIE5:1;
		unsigned char	KIE4:1;
		unsigned char	KIE3:1;
		unsigned char	KIE2:1;
		unsigned char	KIE1:1;
		unsigned char	KIE0:1;
	} bit;
};
#endif

/* structure of KEYS */
#if   defined(__CPU_MB91191_SERIES)
union io_keys {
	unsigned char	byte;
	struct {
		unsigned char	KIS7:1;
		unsigned char	KIS6:1;
		unsigned char	KIS5:1;
		unsigned char	KIS4:1;
		unsigned char	KIS3:1;
		unsigned char	KIS2:1;
		unsigned char	KIS1:1;
		unsigned char	KIS0:1;
	} bit;
};
#endif

/* structure of EIE */
#if   defined(__CPU_MB91191_SERIES)
union io_eie {
	unsigned char	byte;
	struct {
		unsigned char	INT2E:1;
		unsigned char	INT1E:1;
		unsigned char	INT0E:1;
		unsigned char	     :1;
		unsigned char	I2CLR:1;
		unsigned char	I1CLR:1;
		unsigned char	I0CLR:1;
		unsigned char	     :1;
	} bit;
};
#endif

/* structure of EIF */
#if   defined(__CPU_MB91191_SERIES)
union io_eif {
	unsigned char	byte;
	struct {
		unsigned char	    :4;
		unsigned char	IF2 :1;
		unsigned char	IF1 :1;
		unsigned char	IF0 :1;
		unsigned char	TEST:1;
	} bit;
};
#endif


/*********************************************************/
/* Sample program for I/O variable of bit serach module. */
/*********************************************************/
/* structure of BSD */
#if   defined(__CPU_MB91191_SERIES)
struct io_bsd {
	unsigned long	IO_BSD0;
	unsigned long	IO_BSD1;
	unsigned long	IO_BSDC;
	unsigned long	IO_BSRR;
};
#endif


/****************************************************/
/* Sample program for I/O variable of wait control. */
/****************************************************/
/* structure of WAITC */
#if   defined(__CPU_MB91191_SERIES)
union io_waitc {
	unsigned char	byte;
	struct {
		unsigned char	    :6;
		unsigned char	WTC :2;
	} bit;
};
#endif


/********************************************************/
/* Sample program for I/O variables of clock generator. */
/********************************************************/
/* structure of CMCR */
#if   defined(__CPU_MB91360_SERIES)
union io_cmcr {
	unsigned short	hword;
	struct {
		unsigned short	PRE   :8;
		unsigned short	PRES  :1;
		unsigned short	      :4;
		unsigned short	MTST  :1;
		unsigned short	      :2;
	} bit;
};
#endif


/******************************************************/
/* Sample program for I/O variables of D/A converter. */
/******************************************************/
/* structure of DACR */
#if   defined(__CPU_MB91360_SERIES)
union io_dacr {
	unsigned char	byte;
	struct {
		unsigned char	    :5;
		unsigned char	MODE:1;
		unsigned char	DAE1:1;
		unsigned char	DAE0:1;
	} bit;
};
#endif

/* structure of DACR0 */
#if   defined(__CPU_MB91130_SERIES)
union io_dacr0 {
	unsigned char	byte;
	struct {
		unsigned char	    :7;
		unsigned char	DAE0:1;
	} bit;
};
#endif

/* structure of DACR1 */
#if   defined(__CPU_MB91130_SERIES)
union io_dacr1 {
	unsigned char	byte;
	struct {
		unsigned char	    :7;
		unsigned char	DAE1:1;
	} bit;
};
#endif

/* structure of DACR2 */
#if   defined(__CPU_MB91130_SERIES)
union io_dacr2 {
	unsigned char	byte;
	struct {
		unsigned char	    :7;
		unsigned char	DAE2:1;
	} bit;
};
#endif

/* structure of DDBL */
#if   defined(__CPU_MB91360_SERIES)
union io_ddbl {
	unsigned char	byte;
	struct {
		unsigned char	    :7;
		unsigned char	DBL :1;
	} bit;
};
#endif


/******************************************************/
/* Sample program for I/O variables of IIC interface. */
/******************************************************/
/* structure of IBSR */
#if   defined(__CPU_MB91360_SERIES)
union io_ibsr {
	unsigned char	byte;
	struct {
		unsigned char	BB  :1;
		unsigned char	RSC :1;
		unsigned char	AL  :1;
		unsigned char	LRB :1;
		unsigned char	TRX :1;
		unsigned char	AAS :1;
		unsigned char	GCA :1;
		unsigned char	FBT :1;
	} bit;
};
#endif

/* structure of IBCR */
#if   defined(__CPU_MB91360_SERIES)
union io_ibcr {
	unsigned char	byte;
	struct {
		unsigned char	BER :1;
		unsigned char	BEIE:1;
		unsigned char	SCC :1;
		unsigned char	MSS :1;
		unsigned char	ACK :1;
		unsigned char	GCAA:1;
		unsigned char	INTE:1;
		unsigned char	INT :1;
	} bit;
};
#endif

/* structure of ICCR */
#if   defined(__CPU_MB91360_SERIES)
union io_iccr {
	unsigned char	byte;
	struct {
		unsigned char	    :2;
		unsigned char	EN  :1;
		unsigned char	CS  :5;
	} bit;
};
#endif

/* structure of IDBL */
#if   defined(__CPU_MB91360_SERIES)
union io_idbl {
	unsigned char	byte;
	struct {
		unsigned char	    :7;
		unsigned char	DBL :1;
	} bit;
};
#endif


/*********************************************************/
/* Sample program for I/O variables of alarm comparator. */
/*********************************************************/
/* structure of ACCDBL/ACSR */
#if   defined(__CPU_MB91360_SERIES)
union io_alarm {
	unsigned short	hword;
	struct {
		unsigned short	     :7;
		unsigned short	CDBLE:1;
		unsigned short	     :3;
		unsigned short	OUT2 :1;
		unsigned short	OUT1 :1;
		unsigned short	IRQ  :1;
		unsigned short	IEN  :1;
		unsigned short	PD   :1;
	} bit;
};
#endif


/********************************************************/
/* Sample program for I/O variable of power down reset. */
/********************************************************/
/* structure of PDRCR */
#if   defined(__CPU_MB91360_SERIES)
union io_pdrcr {
	unsigned short	hword;
	struct {
		unsigned short	      :13;
		unsigned short	CDSBLE:1;
		unsigned short	PD    :1;
		unsigned short	EN    :1;
	} bit;
};
#endif


/********************************************************/
/* Sample program for I/O variables of sound generator. */
/********************************************************/
/* structure of SGCR */
#if   defined(__CPU_MB91360_SERIES)
union io_sgcr {
	unsigned short	hword;
	struct {
		unsigned short	TST :1;
		unsigned short	    :5;
		unsigned short	BUSY:1;
		unsigned short	DEC :1;
		unsigned short	S   :2;
		unsigned short	TONE:1;
		unsigned short	    :2;
		unsigned short	INTE:1;
		unsigned short	INT :1;
		unsigned short	ST  :1;
	} bit;
};
#endif

/* structure of SGDBL */
#if   defined(__CPU_MB91360_SERIES)
union io_sgdbl {
	unsigned char	byte;
	struct {
		unsigned char	   :7;
		unsigned char	DBL:1;
	} bit;
};
#endif


/******************************************************************/
/* Sample program for I/O variables of stepping motor controller. */
/******************************************************************/
/* structure of PWC0-PWC3 */
#if   defined(__CPU_MB91360_SERIES)
union io_pwc {
	unsigned char	byte;
	struct {
		unsigned char	   :2;
		unsigned char	P  :2;
		unsigned char	CE :1;
		unsigned char	   :2;
		unsigned char	TST:1;
	} bit;
};
#endif

/* structure of ZPD0-ZPD3 */
#if   defined(__CPU_MB91360_SERIES)
union io_zpd {
	unsigned char	byte;
	struct {
		unsigned char	S  :2;
		unsigned char	TS :1;
		unsigned char	T  :3;
		unsigned char	PD :1;
		unsigned char	RS :1;
	} bit;
};
#endif

/* structure of PWS10-PWS13 */
#if   defined(__CPU_MB91360_SERIES)
union io_pws1 {
	unsigned char	byte;
	struct {
		unsigned char	   :2;
		unsigned char	P  :3;
		unsigned char	M  :3;
	} bit;
};
#endif

/* structure of PWS20-PWS23 */
#if   defined(__CPU_MB91360_SERIES)
union io_pws2 {
	unsigned char	byte;
	struct {
		unsigned char	   :1;
		unsigned char	BS :1;
		unsigned char	P  :3;
		unsigned char	M  :3;
	} bit;
};
#endif

/* structure of SMDBL0-SMDBL3 */
#if   defined(__CPU_MB91360_SERIES)
union io_smdbl {
	unsigned char	byte;
	struct {
		unsigned char	   :7;
		unsigned char	DBL:1;
	} bit;
};
#endif


/*******************************************************/
/* Sample program for I/O variables of realtime clock. */
/*******************************************************/
/* structure of WTCR */
#if   defined(__CPU_MB91360_SERIES)
union io_wtcr {
	unsigned short	hword;
	struct {
		unsigned short	INTE3:1;
		unsigned short	INT3 :1;
		unsigned short	INTE2:1;
		unsigned short	INT2 :1;
		unsigned short	INTE1:1;
		unsigned short	INT1 :1;
		unsigned short	INTE0:1;
		unsigned short	INT0 :1;
		unsigned short	TST  :3;
		unsigned short	     :1;
		unsigned short	RUN  :1;
		unsigned short	UPDT :1;
		unsigned short	     :1;
		unsigned short	ST   :1;
	} bit;
};
#endif

/* structure of WTBR */
#if   defined(__CPU_MB91360_SERIES)
union io_wtbr {
	unsigned long	word;
	struct {
		unsigned long	 :11;
		unsigned long	D:21;
	} bit;
};
#endif

/* structure of WTSR */
#if   defined(__CPU_MB91360_SERIES)
union io_wtsr {
	unsigned char	byte;
	struct {
		unsigned char	 :2;
		unsigned char	S:6;
	} bit;
};
#endif

/* structure of WTMR */
#if   defined(__CPU_MB91360_SERIES)
union io_wtmr {
	unsigned char	byte;
	struct {
		unsigned char	 :2;
		unsigned char	M:6;
	} bit;
};
#endif

/* structure of WTHR */
#if   defined(__CPU_MB91360_SERIES)
union io_wthr {
	unsigned char	byte;
	struct {
		unsigned char	 :3;
		unsigned char	H:5;
	} bit;
};
#endif

/* structure of WTDBL */
#if   defined(__CPU_MB91360_SERIES)
union io_wtdbl {
	unsigned char	byte;
	struct {
		unsigned char	   :7;
		unsigned char	DBL:1;
	} bit;
};
#endif

/*******************************************************/
/* Sample program for I/O variables of CAN controller. */
/*******************************************************/
/* structure of control registers */
#if   defined(__CPU_MB91360_SERIES)
struct io_can {

	/* structure of BVALR */
	union {
		unsigned short	hword;
		struct {
			unsigned short	BVAL15:1;
			unsigned short	BVAL14:1;
			unsigned short	BVAL13:1;
			unsigned short	BVAL12:1;
			unsigned short	BVAL11:1;
			unsigned short	BVAL10:1;
			unsigned short	BVAL9 :1;
			unsigned short	BVAL8 :1;
			unsigned short	BVAL7 :1;
			unsigned short	BVAL6 :1;
			unsigned short	BVAL5 :1;
			unsigned short	BVAL4 :1;
			unsigned short	BVAL3 :1;
			unsigned short	BVAL2 :1;
			unsigned short	BVAL1 :1;
			unsigned short	BVAL0 :1;
		} bit;
	} IO_BVALR;

	/* structure of TREQR */
	union {
		unsigned short	hword;
		struct {
			unsigned short	TREQ15:1;
			unsigned short	TREQ14:1;
			unsigned short	TREQ13:1;
			unsigned short	TREQ12:1;
			unsigned short	TREQ11:1;
			unsigned short	TREQ10:1;
			unsigned short	TREQ9 :1;
			unsigned short	TREQ8 :1;
			unsigned short	TREQ7 :1;
			unsigned short	TREQ6 :1;
			unsigned short	TREQ5 :1;
			unsigned short	TREQ4 :1;
			unsigned short	TREQ3 :1;
			unsigned short	TREQ2 :1;
			unsigned short	TREQ1 :1;
			unsigned short	TREQ0 :1;
		} bit;
	} IO_TREQR;

	unsigned short	IO_TCANR;

	/* structure of TCR */
	union {
		unsigned short	hword;
		struct {
			unsigned short	TC15:1;
			unsigned short	TC14:1;
			unsigned short	TC13:1;
			unsigned short	TC12:1;
			unsigned short	TC11:1;
			unsigned short	TC10:1;
			unsigned short	TC9 :1;
			unsigned short	TC8 :1;
			unsigned short	TC7 :1;
			unsigned short	TC6 :1;
			unsigned short	TC5 :1;
			unsigned short	TC4 :1;
			unsigned short	TC3 :1;
			unsigned short	TC2 :1;
			unsigned short	TC1 :1;
			unsigned short	TC0 :1;
		} bit;
	} IO_TCR;

	/* structure of RCR */
	union {
		unsigned short	hword;
		struct {
			unsigned short	RC15:1;
			unsigned short	RC14:1;
			unsigned short	RC13:1;
			unsigned short	RC12:1;
			unsigned short	RC11:1;
			unsigned short	RC10:1;
			unsigned short	RC9 :1;
			unsigned short	RC8 :1;
			unsigned short	RC7 :1;
			unsigned short	RC6 :1;
			unsigned short	RC5 :1;
			unsigned short	RC4 :1;
			unsigned short	RC3 :1;
			unsigned short	RC2 :1;
			unsigned short	RC1 :1;
			unsigned short	RC0 :1;
		} bit;
	} IO_RCR;

	/* structure of RRTRR */
	union {
		unsigned short	hword;
		struct {
			unsigned short	RRTR15:1;
			unsigned short	RRTR14:1;
			unsigned short	RRTR13:1;
			unsigned short	RRTR12:1;
			unsigned short	RRTR11:1;
			unsigned short	RRTR10:1;
			unsigned short	RRTR9 :1;
			unsigned short	RRTR8 :1;
			unsigned short	RRTR7 :1;
			unsigned short	RRTR6 :1;
			unsigned short	RRTR5 :1;
			unsigned short	RRTR4 :1;
			unsigned short	RRTR3 :1;
			unsigned short	RRTR2 :1;
			unsigned short	RRTR1 :1;
			unsigned short	RRTR0 :1;
		} bit;
	} IO_RRTRR;

	/* structure of ROVRR */
	union {
		unsigned short	hword;
		struct {
			unsigned short	ROVR15:1;
			unsigned short	ROVR14:1;
			unsigned short	ROVR13:1;
			unsigned short	ROVR12:1;
			unsigned short	ROVR11:1;
			unsigned short	ROVR10:1;
			unsigned short	ROVR9 :1;
			unsigned short	ROVR8 :1;
			unsigned short	ROVR7 :1;
			unsigned short	ROVR6 :1;
			unsigned short	ROVR5 :1;
			unsigned short	ROVR4 :1;
			unsigned short	ROVR3 :1;
			unsigned short	ROVR2 :1;
			unsigned short	ROVR1 :1;
			unsigned short	ROVR0 :1;
		} bit;
	} IO_ROVRR;

	/* structure of RIER */
	union {
		unsigned short	hword;
		struct {
			unsigned short	RIE15:1;
			unsigned short	RIE14:1;
			unsigned short	RIE13:1;
			unsigned short	RIE12:1;
			unsigned short	RIE11:1;
			unsigned short	RIE10:1;
			unsigned short	RIE9 :1;
			unsigned short	RIE8 :1;
			unsigned short	RIE7 :1;
			unsigned short	RIE6 :1;
			unsigned short	RIE5 :1;
			unsigned short	RIE4 :1;
			unsigned short	RIE3 :1;
			unsigned short	RIE2 :1;
			unsigned short	RIE1 :1;
			unsigned short	RIE0 :1;
		} bit;
	} IO_RIER;

	/* structure of CSR */
	union {
		unsigned short	hword;
		struct {
			unsigned short	TS  :1;
			unsigned short	RS  :1;
			unsigned short	    :3;
			unsigned short	NT  :1;
			unsigned short	NS  :2;
			unsigned short	TOE :1;
			unsigned short	    :4;
			unsigned short	NIE :1;
			unsigned short	    :1;
			unsigned short	HALT:1;
		} bit;
	} IO_CSR;

	unsigned char	:8;

	/* structure of LEIR */
	union {
		unsigned char	byte;
		struct {
			unsigned char	NTE :1;
			unsigned char	TCE :1;
			unsigned char	RCE :1;
			unsigned char	    :1;
			unsigned char	MBP :4;
		} bit;
	} IO_LEIR;

	/* structure of RTEC */
	struct {
		unsigned char	TEC;
		unsigned char	REC;
	} IO_RTEC;

	/* structure of BTR */
	union {
		unsigned short	hword;
		struct {
			unsigned short	    :1;
			unsigned short	TS2 :3;
			unsigned short	TS1 :4;
			unsigned short	RSJ :2;
			unsigned short	PSC :6;
		} bit;
	} IO_BTR;

	/* structure of IDER */
	union {
		unsigned short	hword;
		struct {
			unsigned short	IDE15:1;
			unsigned short	IDE14:1;
			unsigned short	IDE13:1;
			unsigned short	IDE12:1;
			unsigned short	IDE11:1;
			unsigned short	IDE10:1;
			unsigned short	IDE9 :1;
			unsigned short	IDE8 :1;
			unsigned short	IDE7 :1;
			unsigned short	IDE6 :1;
			unsigned short	IDE5 :1;
			unsigned short	IDE4 :1;
			unsigned short	IDE3 :1;
			unsigned short	IDE2 :1;
			unsigned short	IDE1 :1;
			unsigned short	IDE0 :1;
		} bit;
	} IO_IDER;

	/* structure of TRTRR */
	union {
		unsigned short	hword;
		struct {
			unsigned short	TRTR15:1;
			unsigned short	TRTR14:1;
			unsigned short	TRTR13:1;
			unsigned short	TRTR12:1;
			unsigned short	TRTR11:1;
			unsigned short	TRTR10:1;
			unsigned short	TRTR9 :1;
			unsigned short	TRTR8 :1;
			unsigned short	TRTR7 :1;
			unsigned short	TRTR6 :1;
			unsigned short	TRTR5 :1;
			unsigned short	TRTR4 :1;
			unsigned short	TRTR3 :1;
			unsigned short	TRTR2 :1;
			unsigned short	TRTR1 :1;
			unsigned short	TRTR0 :1;
		} bit;
	} IO_TRTRR;

	/* structure of RFWTR */
	union {
		unsigned short	hword;
		struct {
			unsigned short	RFWT15:1;
			unsigned short	RFWT14:1;
			unsigned short	RFWT13:1;
			unsigned short	RFWT12:1;
			unsigned short	RFWT11:1;
			unsigned short	RFWT10:1;
			unsigned short	RFWT9 :1;
			unsigned short	RFWT8 :1;
			unsigned short	RFWT7 :1;
			unsigned short	RFWT6 :1;
			unsigned short	RFWT5 :1;
			unsigned short	RFWT4 :1;
			unsigned short	RFWT3 :1;
			unsigned short	RFWT2 :1;
			unsigned short	RFWT1 :1;
			unsigned short	RFWT0 :1;
		} bit;
	} IO_RFWTR;

	/* structure of TIER */
	union {
		unsigned short	hword;
		struct {
			unsigned short	TIE15:1;
			unsigned short	TIE14:1;
			unsigned short	TIE13:1;
			unsigned short	TIE12:1;
			unsigned short	TIE11:1;
			unsigned short	TIE10:1;
			unsigned short	TIE9 :1;
			unsigned short	TIE8 :1;
			unsigned short	TIE7 :1;
			unsigned short	TIE6 :1;
			unsigned short	TIE5 :1;
			unsigned short	TIE4 :1;
			unsigned short	TIE3 :1;
			unsigned short	TIE2 :1;
			unsigned short	TIE1 :1;
			unsigned short	TIE0 :1;
		} bit;
	} IO_TIER;

	/* structure of AMSR */
	union {
		unsigned long	word;
		struct {
			unsigned long	AMS3 :2;
			unsigned long	AMS2 :2;
			unsigned long	AMS1 :2;
			unsigned long	AMS0 :2;
			unsigned long	AMS7 :2;
			unsigned long	AMS6 :2;
			unsigned long	AMS5 :2;
			unsigned long	AMS4 :2;
			unsigned long	AMS11:2;
			unsigned long	AMS10:2;
			unsigned long	AMS9 :2;
			unsigned long	AMS8 :2;
			unsigned long	AMS15:2;
			unsigned long	AMS14:2;
			unsigned long	AMS13:2;
			unsigned long	AMS12:2;
		} bit;
	} IO_AMSR;

	/* structure of AMR0 */
	union {
		unsigned long	word;
		struct {
			unsigned long	AM28:1;
			unsigned long	AM27:1;
			unsigned long	AM26:1;
			unsigned long	AM25:1;
			unsigned long	AM24:1;
			unsigned long	AM23:1;
			unsigned long	AM22:1;
			unsigned long	AM21:1;
			unsigned long	AM20:1;
			unsigned long	AM19:1;
			unsigned long	AM18:1;
			unsigned long	AM17:1;
			unsigned long	AM16:1;
			unsigned long	AM15:1;
			unsigned long	AM14:1;
			unsigned long	AM13:1;
			unsigned long	AM12:1;
			unsigned long	AM11:1;
			unsigned long	AM10:1;
			unsigned long	AM9 :1;
			unsigned long	AM8 :1;
			unsigned long	AM7 :1;
			unsigned long	AM6 :1;
			unsigned long	AM5 :1;
			unsigned long	AM4 :1;
			unsigned long	AM3 :1;
			unsigned long	AM2 :1;
			unsigned long	AM1 :1;
			unsigned long	AM0 :1;
			unsigned long	    :3;
		} bit;
	} IO_AMR0;

	/* structure of AMR1 */
	union {
		unsigned long	word;
		struct {
			unsigned long	AM28:1;
			unsigned long	AM27:1;
			unsigned long	AM26:1;
			unsigned long	AM25:1;
			unsigned long	AM24:1;
			unsigned long	AM23:1;
			unsigned long	AM22:1;
			unsigned long	AM21:1;
			unsigned long	AM20:1;
			unsigned long	AM19:1;
			unsigned long	AM18:1;
			unsigned long	AM17:1;
			unsigned long	AM16:1;
			unsigned long	AM15:1;
			unsigned long	AM14:1;
			unsigned long	AM13:1;
			unsigned long	AM12:1;
			unsigned long	AM11:1;
			unsigned long	AM10:1;
			unsigned long	AM9 :1;
			unsigned long	AM8 :1;
			unsigned long	AM7 :1;
			unsigned long	AM6 :1;
			unsigned long	AM5 :1;
			unsigned long	AM4 :1;
			unsigned long	AM3 :1;
			unsigned long	AM2 :1;
			unsigned long	AM1 :1;
			unsigned long	AM0 :1;
			unsigned long	    :3;
		} bit;
	} IO_AMR1;

	unsigned long	IO_RAM[8];

	/* structure of IDR */
	union {
		unsigned long	word;
		struct {
			unsigned long	ID28:1;
			unsigned long	ID27:1;
			unsigned long	ID26:1;
			unsigned long	ID25:1;
			unsigned long	ID24:1;
			unsigned long	ID23:1;
			unsigned long	ID22:1;
			unsigned long	ID21:1;
			unsigned long	ID20:1;
			unsigned long	ID19:1;
			unsigned long	ID18:1;
			unsigned long	ID17:1;
			unsigned long	ID16:1;
			unsigned long	ID15:1;
			unsigned long	ID14:1;
			unsigned long	ID13:1;
			unsigned long	ID12:1;
			unsigned long	ID11:1;
			unsigned long	ID10:1;
			unsigned long	ID9 :1;
			unsigned long	ID8 :1;
			unsigned long	ID7 :1;
			unsigned long	ID6 :1;
			unsigned long	ID5 :1;
			unsigned long	ID4 :1;
			unsigned long	ID3 :1;
			unsigned long	ID2 :1;
			unsigned long	ID1 :1;
			unsigned long	ID0 :1;
			unsigned long	    :3;
		} bit;
	} IO_IDR[16];

	/* structure of DLCR */
	union {
		unsigned short	hword;
		struct {
			unsigned short	    :12;
			unsigned short	DLC :4;
		} bit;
	} IO_DLCR[16];

	/* structure of DTR */
	struct {
		unsigned long	BYTE0_3;
		unsigned long	BYTE4_7;
	} IO_DTR[16];

	/* structure of CREG */
	union {
		unsigned short	hword;
		struct {
			unsigned short	      :8;
			unsigned short	EINT  :1;
			unsigned short	SINT  :1;
			unsigned short	CINV  :1;
			unsigned short	LINV  :1;
			unsigned short	CBPASS:1;
			unsigned short	LBPASS:1;
			unsigned short	DIRECT:1;
			unsigned short	CDSBLE:1;
		} bit;
	} IO_CREG;

};
#endif


/***************************************************/
/* Sample program for I/O variables of DSP macros. */
/***************************************************/
/* structure of OFAS */
#if   defined(__CPU_MB91121_SERIES)
union io_ofas {
	unsigned short	hword;
	struct {
		unsigned short	     :4;
		unsigned short	OFA  :12;
	} bit;
};
#endif

/* structure of STRS */
#if   defined(__CPU_MB91121_SERIES)
union io_strs {
	unsigned short	hword;
	struct {
		unsigned short	     :4;
		unsigned short	STA  :12;
	} bit;
};
#endif

/* structure of OFSC */
#if   defined(__CPU_MB91121_SERIES)
union io_ofsc {
	unsigned char	byte;
	struct {
		unsigned char	OFIE :1;
		unsigned char	OFIC :1;
		unsigned char	YRMD :1;
		unsigned char	STRM :1;
		unsigned char	     :3;
		unsigned char	OFCC :1;
	} bit;
};
#endif

/* structure of OFSD */
#if   defined(__CPU_MB91121_SERIES)
union io_ofsd {
	unsigned short	hword;
	struct {
		unsigned short	OFS  :6;
		unsigned short	OFC  :10;
	} bit;
};
#endif

/* structure of Y-BANKC */
#if   defined(__CPU_MB91121_SERIES)
union io_y_bankc {
	unsigned char	byte;
	struct {
		unsigned char	YBEN :1;
		unsigned char	     :2;
		unsigned char	RDMAe:1;
		unsigned char	WDMAe:1;
		unsigned char	YBF  :1;
		unsigned char	YBSW :1;
		unsigned char	YBMD :1;
	} bit;
};
#endif

/* structure of Y-BANKC */
#if   defined(__CPU_MB91121_SERIES)
union io_dsp_csr {
	unsigned char	byte;
	struct {
		unsigned char	SatDSP:1;
		unsigned char	USR   :3;
		unsigned char	IrqDSP:1;
		unsigned char	IeDSP :1;
		unsigned char	HitDSP:1;
		unsigned char	RunDSP:1;
	} bit;
	struct {
		unsigned char	      :7;
		unsigned char	GoDSP :1;
	} bitc;
};
#endif


/**************************************************************/
/* Sample program for I/O variable of 4-bit level comparator. */
/**************************************************************/
/* structure of LVLC */
#if   defined(__CPU_MB91130_SERIES)
union io_lvlc {
	unsigned char	byte;
	struct {
		unsigned char	RD   :4;
		unsigned char	CPLV :1;
		unsigned char	INT  :1;
		unsigned char	INTE :1;
		unsigned char	CPEN :1;
	} bit;
};
#endif


/**********************************************************/
/* Sample program for I/O variable of waveform generator. */
/**********************************************************/
/* structure of dtcr */
#if   defined(__CPU_MB91130_SERIES)
union io_dtcr {
	unsigned char	byte;
	struct {
		unsigned char	DMOD :1;
		unsigned char	GTEN :1;
		unsigned char	PPGE :1;
		unsigned char	TMIF :1;
		unsigned char	TMIE :1;
		unsigned char	TMD  :3;
	} bit;
};
#endif

/* structure of SIGCR */
#if   defined(__CPU_MB91130_SERIES)
union io_sigcr {
	unsigned char	byte;
	struct {
		unsigned char	DTIE :1;
		unsigned char	DTIL :1;
		unsigned char	NRSL :1;
		unsigned char	DCK  :3;
		unsigned char	PGS  :2;
	} bit;
};
#endif


/********************************************************************/
/* Sample program for I/O variable of flash memory status register. */
/********************************************************************/
/* structure of FSTR */
#if   defined(__CPU_MB91F109_SERIES)
union io_fstr {
	unsigned char	byte;
	struct {
		unsigned char	INTE  :1;
		unsigned char	RDYINT:1;
		unsigned char	WE    :1;
		unsigned char	RDY   :1;
		unsigned char	      :4;
	} bit;
};
#endif

