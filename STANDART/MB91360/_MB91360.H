/*
 MB91360 series I/O register declaration file V30L02
 ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU LIMITED 1998-1999
 LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU LIMITED
*/

#include "_frr.h"

#ifdef __IO_DEFINE
#define __IO_EXTERN
#else
#define __IO_EXTERN     extern
#endif

/* I/O Area Address */
#ifdef __IO_DEFINE
#pragma section IO=IO_REG,locate=0x000000
#endif

__IO_EXTERN __io union io_cmcr	IO_CMCR;	/* addr 164-165h */

__IO_EXTERN __io union io_irbs 	IO_IRBS;	/* addr 300-303h */
__IO_EXTERN __io union io_isize	IO_ISIZE;	/* addr 304-307h */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_308_3E3[220];/* addr 308-3E3h */
#endif
__IO_EXTERN __io union io_ichcr	IO_ICHCR;	/* addr 3E4-3E7h */

extern volatile struct io_clk   IO_CLK;		/* addr 480-487h */

extern volatile unsigned char	IO_MODR;	/* addr 7FDh */









#ifdef __IO_DEFINE
static __io unsigned char	dmy_00_06[7];	/* addr 000-006h */
#endif
__IO_EXTERN __io union io_pdr7	IO_PDR7;	/* addr 007h */
__IO_EXTERN __io union io_pdr8	IO_PDR8;	/* addr 008h */
__IO_EXTERN __io union io_pdr9	IO_PDR9;	/* addr 009h */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_0A;		/* addr 00Ah */
#endif
__IO_EXTERN __io union io_pdrb	IO_PDRB;	/* addr 00Bh */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_0C_0F[4];	/* addr 00C-00Fh */
#endif
__IO_EXTERN __io union io_pdrg	IO_PDRG;	/* addr 010h */
__IO_EXTERN __io union io_pdrh	IO_PDRH;	/* addr 011h */
__IO_EXTERN __io union io_pdri	IO_PDRI;	/* addr 012h */
__IO_EXTERN __io union io_pdrj	IO_PDRJ;	/* addr 013h */
__IO_EXTERN __io union io_pdrk	IO_PDRK;	/* addr 014h */
__IO_EXTERN __io union io_pdrl	IO_PDRL;	/* addr 015h */
__IO_EXTERN __io union io_pdrm	IO_PDRM;	/* addr 016h */
__IO_EXTERN __io union io_pdrn	IO_PDRN;	/* addr 017h */
__IO_EXTERN __io union io_pdro	IO_PDRO;	/* addr 018h */
__IO_EXTERN __io union io_pdrp	IO_PDRP;	/* addr 019h */
__IO_EXTERN __io union io_pdrq	IO_PDRQ;	/* addr 01Ah */
__IO_EXTERN __io union io_pdrr	IO_PDRR;	/* addr 01Bh */
__IO_EXTERN __io union io_pdrs	IO_PDRS;	/* addr 01Ch */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_1D_1F[3];	/* addr 01D-01Fh */
#endif
#ifdef __IO_DEFINE
static __io unsigned char	dmy_20_3F[32];	/* addr 020-03Fh */
#endif
__IO_EXTERN __io union io_eirr	IO_EIRR;	/* addr 040h */
__IO_EXTERN __io union io_enir	IO_ENIR;	/* addr 041h */
__IO_EXTERN __io union io_elvr	IO_ELVR;	/* addr 042-043h */
__IO_EXTERN __io union io_dicr	IO_DICR;	/* addr 044h */
__IO_EXTERN __io union io_hrcl	IO_HRCL;	/* addr 045h */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_46_47[2];	/* addr 046-047h */
#endif
__IO_EXTERN __io unsigned short	IO_TMRLR0;	/* addr 048-049h */
__IO_EXTERN __io const unsigned short IO_TMR0;	/* addr 04A-04Bh */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_4C_4D[2];	/* addr 04C-04Dh */
#endif
__IO_EXTERN __io union io_tmcsr	IO_TMCSR0;	/* addr 04E-04Fh */
__IO_EXTERN __io unsigned short	IO_TMRLR1;	/* addr 050-051h */
__IO_EXTERN __io const unsigned short IO_TMR1;	/* addr 052-053h */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_54_55[2];	/* addr 054-055h */
#endif
__IO_EXTERN __io union io_tmcsr	IO_TMCSR1;	/* addr 056-057h */
__IO_EXTERN __io unsigned short	IO_TMRLR2;	/* addr 058-059h */
__IO_EXTERN __io const unsigned short IO_TMR2;	/* addr 05A-05Bh */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_5C_5D[2];	/* addr 05C-05Dh */
#endif
__IO_EXTERN __io union io_tmcsr	IO_TMCSR2;	/* addr 05E-05Fh */
__IO_EXTERN __io union io_ssr	IO_SSR0;	/* addr 060h */
__IO_EXTERN __io unsigned char	IO_SIDR0;	/* addr 061h */
__IO_EXTERN __io union io_scr	IO_SCR0;	/* addr 062h */
__IO_EXTERN __io union io_smr	IO_SMR0;	/* addr 063h */
__IO_EXTERN __io union io_uls	IO_ULS0;	/* addr 064h */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_65_67[3];	/* addr 065-067h */
#endif
__IO_EXTERN __io unsigned short	IO_UTIM0;	/* addr 068-069h */
__IO_EXTERN __io unsigned char	IO_DRCL0;	/* addr 06Ah */
__IO_EXTERN __io union io_utimc	IO_UTIMC0;	/* addr 06Bh */
__IO_EXTERN __io union io_ssr	IO_SSR1;	/* addr 06Ch */
__IO_EXTERN __io unsigned char	IO_SIDR1;	/* addr 06Dh */
__IO_EXTERN __io union io_scr	IO_SCR1;	/* addr 06Eh */
__IO_EXTERN __io union io_smr	IO_SMR1;	/* addr 06Fh */
__IO_EXTERN __io union io_uls	IO_ULS1;	/* addr 070h */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_71_73[3];	/* addr 071-073h */
#endif
__IO_EXTERN __io unsigned short	IO_UTIM1;	/* addr 074-075h */
__IO_EXTERN __io unsigned char	IO_DRCL1;	/* addr 076h */
__IO_EXTERN __io union io_utimc	IO_UTIMC1;	/* addr 077h */
__IO_EXTERN __io union io_ssr	IO_SSR2;	/* addr 078h */
__IO_EXTERN __io unsigned char	IO_SIDR2;	/* addr 079h */
__IO_EXTERN __io union io_scr	IO_SCR2;	/* addr 07Ah */
__IO_EXTERN __io union io_smr	IO_SMR2;	/* addr 07Bh */
__IO_EXTERN __io union io_uls	IO_ULS2;	/* addr 07Ch */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_7D_7F[3];	/* addr 07D-07Fh */
#endif
__IO_EXTERN __io unsigned short	IO_UTIM2;	/* addr 080-081h */
__IO_EXTERN __io unsigned char	IO_DRCL2;	/* addr 082h */
__IO_EXTERN __io union io_utimc	IO_UTIMC2;	/* addr 083h */
__IO_EXTERN __io union io_smcs	IO_SMCS0;	/* addr 084-085h */
__IO_EXTERN __io union io_ses 	IO_SES0;	/* addr 086h */
__IO_EXTERN __io unsigned char	IO_SDR0;	/* addr 087h */
__IO_EXTERN __io union io_smcs	IO_SMCS1;	/* addr 088-089h */
__IO_EXTERN __io union io_ses 	IO_SES1;	/* addr 08Ah */
__IO_EXTERN __io unsigned char	IO_SDR1;	/* addr 08Bh */
__IO_EXTERN __io union io_cdcr	IO_CDCR0;	/* addr 08Ch */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_8D;		/* addr 08Dh */
#endif
__IO_EXTERN __io union io_cdcr	IO_CDCR1;	/* addr 08Eh */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_8F;		/* addr 08Fh */
#endif
#ifdef __IO_DEFINE
static __io unsigned char	dmy_90_93[4];	/* addr 090-093h */
#endif
__IO_EXTERN __io union io_ibcr 	IO_IBCR;	/* addr 094h */
__IO_EXTERN __io const union io_ibsr IO_IBSR;	/* addr 095h */
__IO_EXTERN __io unsigned char	IO_IADR;	/* addr 096h */
__IO_EXTERN __io union io_iccr 	IO_ICCR;	/* addr 097h */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_98;		/* addr 098h */
#endif
__IO_EXTERN __io unsigned char	IO_IDAR;	/* addr 099h */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_9A;		/* addr 09Ah */
#endif
__IO_EXTERN __io union io_idbl 	IO_IDBL;	/* addr 09Bh */
__IO_EXTERN __io union io_admd 	IO_ADMD;	/* addr 09Ch */
__IO_EXTERN __io union io_adch 	IO_ADCH;	/* addr 09Dh */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_9E;		/* addr 09Eh */
#endif
__IO_EXTERN __io union io_adcs 	IO_ADCS;	/* addr 09Fh */
__IO_EXTERN __io unsigned short	IO_ADCD;	/* addr 0A0-0A1h */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_A2;		/* addr 0A2h */
#endif
__IO_EXTERN __io union io_adbl 	IO_ADBL;	/* addr 0A3h */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_A4;		/* addr 0A4h */
#endif
__IO_EXTERN __io union io_dacr	IO_DACR;	/* addr 0A5h */
__IO_EXTERN __io unsigned short	IO_DADR0;	/* addr 0A6-0A7h */
__IO_EXTERN __io unsigned short	IO_DADR1;	/* addr 0A8-0A9h */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_AA;		/* addr 0AAh */
#endif
__IO_EXTERN __io union io_ddbl 	IO_DDBL;	/* addr 0ABh */
__IO_EXTERN __io union io_iotdbl IO_IOTDBL0;	/* addr 0ACh */
__IO_EXTERN __io union io_ics01	IO_ICS01;	/* addr 0ADh */
__IO_EXTERN __io union io_iotdbl IO_IOTDBL1;	/* addr 0AEh */
__IO_EXTERN __io union io_ics23	IO_ICS23;	/* addr 0AFh */
__IO_EXTERN __io const unsigned short IO_IPCP0;	/* addr 0B0-0B1h */
__IO_EXTERN __io const unsigned short IO_IPCP1;	/* addr 0B2-0B3h */
__IO_EXTERN __io const unsigned short IO_IPCP2;	/* addr 0B4-0B5h */
__IO_EXTERN __io const unsigned short IO_IPCP3;	/* addr 0B6-0B7h */
__IO_EXTERN __io union io_ocs01	IO_OCS01;	/* addr 0B8-0B9h */
__IO_EXTERN __io union io_ocs23	IO_OCS23;	/* addr 0BA-0BBh */
__IO_EXTERN __io unsigned short	IO_OCCP0;	/* addr 0BC-0BDh */
__IO_EXTERN __io unsigned short	IO_OCCP1;	/* addr 0BE-0BFh */
__IO_EXTERN __io unsigned short	IO_OCCP2;	/* addr 0C0-0C1h */
__IO_EXTERN __io unsigned short	IO_OCCP3;	/* addr 0C2-0C3h */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_C4_C7[4];	/* addr 0C4-0C7h */
#endif
__IO_EXTERN __io unsigned short	IO_TCDT0;	/* addr 0C8-0C9h */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_CA;		/* addr 0CAh */
#endif
__IO_EXTERN __io union io_tccs 	IO_TCCS0;	/* addr 0CBh */
__IO_EXTERN __io unsigned short	IO_TCDT1;	/* addr 0CC-0CDh */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_CE;		/* addr 0CEh */
#endif
__IO_EXTERN __io union io_tccs 	IO_TCCS1;	/* addr 0CFh */
__IO_EXTERN __io union io_zpd 	IO_ZPD0;	/* addr 0D0h */
__IO_EXTERN __io union io_pwc 	IO_PWC0;	/* addr 0D1h */
__IO_EXTERN __io union io_zpd 	IO_ZPD1;	/* addr 0D2h */
__IO_EXTERN __io union io_pwc 	IO_PWC1;	/* addr 0D3h */
__IO_EXTERN __io union io_zpd 	IO_ZPD2;	/* addr 0D4h */
__IO_EXTERN __io union io_pwc 	IO_PWC2;	/* addr 0D5h */
__IO_EXTERN __io union io_zpd 	IO_ZPD3;	/* addr 0D6h */
__IO_EXTERN __io union io_pwc 	IO_PWC3;	/* addr 0D7h */
__IO_EXTERN __io unsigned char	IO_PWC20;	/* addr 0D8h */
__IO_EXTERN __io unsigned char	IO_PWC10;	/* addr 0D9h */
__IO_EXTERN __io union io_pws2	IO_PWS20;	/* addr 0DAh */
__IO_EXTERN __io union io_pws1	IO_PWS10;	/* addr 0DBh */
__IO_EXTERN __io unsigned char	IO_PWC21;	/* addr 0DCh */
__IO_EXTERN __io unsigned char	IO_PWC11;	/* addr 0DDh */
__IO_EXTERN __io union io_pws2	IO_PWS21;	/* addr 0DEh */
__IO_EXTERN __io union io_pws1	IO_PWS11;	/* addr 0DFh */
__IO_EXTERN __io unsigned char	IO_PWC22;	/* addr 0E0h */
__IO_EXTERN __io unsigned char	IO_PWC12;	/* addr 0E1h */
__IO_EXTERN __io union io_pws2	IO_PWS22;	/* addr 0E2h */
__IO_EXTERN __io union io_pws1	IO_PWS12;	/* addr 0E3h */
__IO_EXTERN __io unsigned char	IO_PWC23;	/* addr 0E4h */
__IO_EXTERN __io unsigned char	IO_PWC13;	/* addr 0E5h */
__IO_EXTERN __io union io_pws2	IO_PWS23;	/* addr 0E6h */
__IO_EXTERN __io union io_pws1	IO_PWS13;	/* addr 0E7h */
__IO_EXTERN __io union io_smdbl	IO_SMDBL0;	/* addr 0E8h */
__IO_EXTERN __io union io_smdbl	IO_SMDBL1;	/* addr 0E9h */
__IO_EXTERN __io union io_smdbl	IO_SMDBL2;	/* addr 0EAh */
__IO_EXTERN __io union io_smdbl	IO_SMDBL3;	/* addr 0EBh */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_EC;		/* addr 0ECh */
#endif
__IO_EXTERN __io union io_sgdbl	IO_SGDBL;	/* addr 0EDh */
__IO_EXTERN __io union io_sgcr 	IO_SGCR;	/* addr 0EE-0EFh */
__IO_EXTERN __io unsigned char	IO_SGAR;	/* addr 0F0h */
__IO_EXTERN __io unsigned char	IO_SGFR;	/* addr 0F1h */
__IO_EXTERN __io unsigned char	IO_SGTR;	/* addr 0F2h */
__IO_EXTERN __io unsigned char	IO_SGDR;	/* addr 0F3h */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_F4;		/* addr 0F4h */
#endif
__IO_EXTERN __io union io_wtdbl	IO_WTDBL;	/* addr 0F5h */
__IO_EXTERN __io union io_wtcr 	IO_WTCR;	/* addr 0F6-0F7h */
__IO_EXTERN __io union io_wtbr 	IO_WTBR;	/* addr 0F8-0FBh */
__IO_EXTERN __io union io_wthr 	IO_WTHR;	/* addr 0FCh */
__IO_EXTERN __io union io_wtmr 	IO_WTMR;	/* addr 0FDh */
__IO_EXTERN __io union io_wtsr 	IO_WTSR;	/* addr 0FEh */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_FF;		/* addr 0FFh */
#endif
__IO_EXTERN __io unsigned short	IO_TMRLR3;	/* addr 100-101h */
__IO_EXTERN __io const unsigned short IO_TMR3;	/* addr 102-103h */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_104_105[2];	/* addr 104-105h */
#endif
__IO_EXTERN __io union io_tmcsr	IO_TMCSR3;	/* addr 106-107h */
__IO_EXTERN __io unsigned short	IO_TMRLR4;	/* addr 108-109h */
__IO_EXTERN __io const unsigned short IO_TMR4;	/* addr 10A-10Bh */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_10C_10D[2];	/* addr 10C-10Dh */
#endif
__IO_EXTERN __io union io_tmcsr	IO_TMCSR4;	/* addr 10E-10Fh */
__IO_EXTERN __io unsigned short	IO_TMRLR5;	/* addr 110-111h */
__IO_EXTERN __io const unsigned short IO_TMR5;	/* addr 112-113h */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_114_115[2];	/* addr 114-115h */
#endif
__IO_EXTERN __io union io_tmcsr	IO_TMCSR5;	/* addr 116-117h */
__IO_EXTERN __io union io_gcn1	IO_GCN10;	/* addr 118-119h */
__IO_EXTERN __io union io_gcn20	IO_GCN20;	/* addr 11A-11Bh */
__IO_EXTERN __io union io_gcn1	IO_GCN11;	/* addr 11C-11Dh */
__IO_EXTERN __io union io_gcn21	IO_GCN21;	/* addr 11E-11Fh */
__IO_EXTERN __io const unsigned short IO_PTMR0;	/* addr 120-121h */
__IO_EXTERN __io unsigned short	IO_PCSR0;	/* addr 122-123h */
__IO_EXTERN __io unsigned short	IO_PDUT0;	/* addr 124-125h */
__IO_EXTERN __io union io_pcn 	IO_PCN0;	/* addr 126-127h */
__IO_EXTERN __io const unsigned short IO_PTMR1;	/* addr 128-129h */
__IO_EXTERN __io unsigned short	IO_PCSR1;	/* addr 12A-12Bh */
__IO_EXTERN __io unsigned short	IO_PDUT1;	/* addr 12C-12Dh */
__IO_EXTERN __io union io_pcn 	IO_PCN1;	/* addr 12E-12Fh */
__IO_EXTERN __io const unsigned short IO_PTMR2;	/* addr 130-131h */
__IO_EXTERN __io unsigned short	IO_PCSR2;	/* addr 132-133h */
__IO_EXTERN __io unsigned short	IO_PDUT2;	/* addr 134-135h */
__IO_EXTERN __io union io_pcn 	IO_PCN2;	/* addr 136-137h */
__IO_EXTERN __io const unsigned short IO_PTMR3;	/* addr 138-139h */
__IO_EXTERN __io unsigned short	IO_PCSR3;	/* addr 13A-13Bh */
__IO_EXTERN __io unsigned short	IO_PDUT3;	/* addr 13C-13Dh */
__IO_EXTERN __io union io_pcn 	IO_PCN3;	/* addr 13E-13Fh */
__IO_EXTERN __io const unsigned short IO_PTMR4;	/* addr 140-141h */
__IO_EXTERN __io unsigned short	IO_PCSR4;	/* addr 142-143h */
__IO_EXTERN __io unsigned short	IO_PDUT4;	/* addr 144-145h */
__IO_EXTERN __io union io_pcn 	IO_PCN4;	/* addr 146-147h */
__IO_EXTERN __io const unsigned short IO_PTMR5;	/* addr 148-149h */
__IO_EXTERN __io unsigned short	IO_PCSR5;	/* addr 14A-14Bh */
__IO_EXTERN __io unsigned short	IO_PDUT5;	/* addr 14C-14Dh */
__IO_EXTERN __io union io_pcn 	IO_PCN5;	/* addr 14E-14Fh */
__IO_EXTERN __io const unsigned short IO_PTMR6;	/* addr 150-151h */
__IO_EXTERN __io unsigned short	IO_PCSR6;	/* addr 152-153h */
__IO_EXTERN __io unsigned short	IO_PDUT6;	/* addr 154-155h */
__IO_EXTERN __io union io_pcn 	IO_PCN6;	/* addr 156-157h */
__IO_EXTERN __io const unsigned short IO_PTMR7;	/* addr 158-159h */
__IO_EXTERN __io unsigned short	IO_PCSR7;	/* addr 15A-15Bh */
__IO_EXTERN __io unsigned short	IO_PDUT7;	/* addr 15C-15Dh */
__IO_EXTERN __io union io_pcn 	IO_PCN7;	/* addr 15E-15Fh */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_160_163[4];	/* addr 160-163h */
#endif
#ifdef __IO_DEFINE
static __io unsigned char	dmy_166_17B[22];/* addr 166-17Bh */
#endif
__IO_EXTERN __io union io_pdrcr IO_PDRCR;	/* addr 17C-17Dh */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_17E_17F[2];	/* addr 17E-17Fh */
#endif
__IO_EXTERN __io union io_alarm IO_ALARM;	/* addr 180-181h */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_182_1FF[126];/* addr 182-1FFh */
#endif
__IO_EXTERN __io union io_dmaca IO_DMACA0;	/* addr 200-203h */
__IO_EXTERN __io union io_dmacb IO_DMACB0;	/* addr 204-207h */
__IO_EXTERN __io union io_dmaca IO_DMACA1;	/* addr 208-20Bh */
__IO_EXTERN __io union io_dmacb IO_DMACB1;	/* addr 20C-20Fh */
__IO_EXTERN __io union io_dmaca IO_DMACA2;	/* addr 210-213h */
__IO_EXTERN __io union io_dmacb IO_DMACB2;	/* addr 214-217h */
__IO_EXTERN __io union io_dmaca IO_DMACA3;	/* addr 218-21Bh */
__IO_EXTERN __io union io_dmacb IO_DMACB3;	/* addr 21C-21Fh */
__IO_EXTERN __io union io_dmaca IO_DMACA4;	/* addr 220-223h */
__IO_EXTERN __io union io_dmacb IO_DMACB4;	/* addr 224-227h */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_228_23F[24];/* addr 228-23Fh */
#endif
__IO_EXTERN __io union io_dmacr	IO_DMACR;	/* addr 240-243h */
#ifdef __IO_DEFINE
static __io unsigned char	dmy_244_2FF[188];/* addr 244-2FFh */
#endif
#ifdef __IO_DEFINE
static __io unsigned char	dmy_3E8_3EF[8]; /* addr 3E8-3EFh */
#endif
__IO_EXTERN __io unsigned long	IO_BSD0;	/* addr 3F0-3F3h */
__IO_EXTERN __io unsigned long	IO_BSD1;	/* addr 3F4-3F7h */
__IO_EXTERN __io unsigned long	IO_BSDC;	/* addr 3F8-3FBh */
__IO_EXTERN __io const unsigned long IO_BSRR;	/* addr 3FC-3FFh */

#ifdef __IO_DEFINE
#pragma section DATA=IO_ICR,locate=0x000440
#endif

extern volatile struct io_port1 IO_PORT1;	/* addr 400-41Ch */

__IO_EXTERN volatile union io_icr IO_ICR[48];	/* addr 440-46Fh */

extern volatile struct io_port2 IO_PORT2;	/* addr 600-627h */

extern volatile struct io_ebus  IO_EBUS;	/* addr 640-673h */

extern volatile struct io_dmad	IO_DMAD;	/* addr 1000-1027h */

extern volatile struct io_can 	IO_CAN[4];	/* addr 100000-1007FFh */

