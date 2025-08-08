/*  FR IO-MAP HEADER FILE      */
/*  =====================      */
/* CREATED BY IO-WIZARD V2.4   */
/* DATE: 6/6/01 TIME: 1:04:23 PM */
/* 12-05-00 : Version 1 */
/* 16-06-00 : Version 2 ; I2C Registers and Mode Registers added */
/* 30-05-01 : Version 3 ; CAN structure added */
/*                        PDBL0, 1 REGISTER BIT ORDER UPDATED */
/* 06-06-01 : Version 3.1 ; CREG1/1 structure added */
/* DEVICE : MB91362           */
/* HEADERFILE VERSION 2 */

/* ASSEMBLER DEFINITIONS : */

#ifdef  __IO_DEFINE
#define __IO_EXTERN
#else
#define __IO_EXTERN	extern volatile
#endif
#ifdef __IO_DEFINE
#pragma asm
 .GLOBAL _pdr0,     _pdr1,     _pdr2,     _pdr3,     _pdr4,     _pdr5,   _pdr6
 .GLOBAL _ddr0,     _ddr1,     _ddr2,     _ddr3,     _ddr4,     _ddr5,   _ddr6
 .GLOBAL _pfr0,     _pfr1,     _pfr2,     _pfr3,     _pfr4,     _pfr5,   _pfr6
 .GLOBAL _pdr7,     _pdr8,     _pdr9,     _pdrb,     _pdrg,     _pdrh
 .GLOBAL _pdri,     _pdrj,     _pdrk,     _pdrl,     _pdrm,     _pdrn
 .GLOBAL _pdro,     _pdrp,     _pdrq,     _pdrr,     _pdrs,     _eirr
 .GLOBAL _enir,     _elvr,     _dicr,     _hrcl,     _tmrlr0,   _tmr0
 .GLOBAL _tmcsr0,   _tmrlr1,   _tmr1,     _tmcsr1,   _tmrlr2,   _tmr2
 .GLOBAL _tmcsr2,   _ssr0,     _sidr0,    _sodr0,    _scr0,     _smr0
 .GLOBAL _uls0,     _utim0,    _utimr0,   _drcl0,    _utimc0,   _ssr1
 .GLOBAL _sidr1,    _sodr1,    _scr1,     _smr1,     _uls1,     _utim1
 .GLOBAL _utimr1,   _drcl1,    _utimc1,   _ssr2,     _sidr2,    _sodr2
 .GLOBAL _scr2,     _smr2,     _uls2,     _utim2,    _utimr2,   _drcl2
 .GLOBAL _utimc2,   _smcs0,    _ses0,     _sdr0,     _smcs1,    _ses1
 .GLOBAL _sdr1,     _cdcr0,    _psmr0,    _cdcr1,    _psmr1,    _ibcr
 .GLOBAL _ibsr,     _iadr,     _iccr,     _idar,     _idbl,     _admd
 .GLOBAL _adch,     _adcs,     _adcd,     _adbl,     _dacr,     _dadr0
 .GLOBAL _dadr1,    _ddbl,     _iotdbl0,  _ics01,    _iotdbl1,  _ics23
 .GLOBAL _ipcp0,    _ipcp1,    _ipcp2,    _ipcp3,    _ocs01,    _ocs23
 .GLOBAL _occp0,    _occp1,    _occp2,    _occp3,    _tcdt0,    _tccs0
 .GLOBAL _tcdt1,    _tccs1,    _zpd0,     _pwc0,     _zpd1,     _pwc1
 .GLOBAL _zpd2,     _pwc2,     _zpd3,     _pwc3,     _pwc20,    _pwc10
 .GLOBAL _pws20,    _pws10,    _pwc21,    _pwc11,    _pws21,    _pws11
 .GLOBAL _pwc22,    _pwc12,    _pws22,    _pws12,    _pwc23,    _pwc13
 .GLOBAL _pws23,    _pws13,    _smdbl0,   _smdbl1,   _smdbl2,   _smdbl3
 .GLOBAL _sgdbl,    _sgcr,     _sgar,     _sgfr,     _sgtr,     _sgdr
 .GLOBAL _wtdbl,    _wtcr,     _wtbr,     _wthr,     _wtmr,     _wtsr
 .GLOBAL _tmrlr3,   _tmr3,     _tmcsr3,   _tmrlr4,   _tmr4,     _tmcsr4
 .GLOBAL _tmrlr5,   _tmr5,     _tmcsr5,   _gcn10,    _pdbl0,    _gcn20
 .GLOBAL _gcn11,    _pdbl1,    _gcn21,    _ptmr0,    _pcsr0,    _pdut0
 .GLOBAL _pcnh0,    _pcnl0,    _ptmr1,    _pcsr1,    _pdut1,    _pcnh1
 .GLOBAL _pcnl1,    _ptmr2,    _pcsr2,    _pdut2,    _pcnh2,    _pcnl2
 .GLOBAL _ptmr3,    _pcsr3,    _pdut3,    _pcnh3,    _pcnl3,    _ptmr4
 .GLOBAL _pcsr4,    _pdut4,    _pcnh4,    _pcnl4,    _ptmr5,    _pcsr5
 .GLOBAL _pdut5,    _pcnh5,    _pcnl5,    _ptmr6,    _pcsr6,    _pdut6
 .GLOBAL _pcnh6,    _pcnl6,    _ptmr7,    _pcsr7,    _pdut7,    _pcnh7
 .GLOBAL _pcnl7,    _cmcr,     _cmpr,     _cmls0,    _cmls1,    _cmls2
 .GLOBAL _cmls3,    _cmlt0,    _cmlt1,    _cmlt2,    _cmlt3,    _cmac
 .GLOBAL _pdrcr,    _accdbl,   _acsr,     _ibcr2,    _ibsr2,    _itbah2
 .GLOBAL _itbal2,   _itmkh2,   _itmkl2,   _ismk2,    _isba2,    _idar2
 .GLOBAL _iccr2,    _idbl2,    _f362md,   _dmaca0,   _dmacb0,   _dmaca1
 .GLOBAL _dmacb1,   _dmaca2,   _dmacb2,   _dmaca3,   _dmacb3,   _dmaca4
 .GLOBAL _dmacb4,   _dmacr,    _irbs,     _isize,    _ichcr,    _bsd0
 .GLOBAL _bsd1,     _bsdc,     _bsrr,     _ddrg,     _ddrh,     _ddri
 .GLOBAL _ddrj,     _ddrk,     _ddrl,     _ddrm,     _ddrn,     _ddro
 .GLOBAL _ddrp,     _ddrq,     _ddrr,     _ddrs,     _pfrg,     _pfrh
 .GLOBAL _pfri,     _pfrj,     _pfrk,     _pfrl,     _pfrm,     _pfrn
 .GLOBAL _pfro,     _pfrp,     _pfrq,     _pfrr,     _pfrs,     _icr00
 .GLOBAL _icr01,    _icr02,    _icr03,    _icr04,    _icr05,    _icr06
 .GLOBAL _icr07,    _icr08,    _icr09,    _icr10,    _icr11,    _icr12
 .GLOBAL _icr13,    _icr14,    _icr15,    _icr16,    _icr17,    _icr18
 .GLOBAL _icr19,    _icr20,    _icr21,    _icr22,    _icr23,    _icr24
 .GLOBAL _icr25,    _icr26,    _icr27,    _icr28,    _icr29,    _icr30
 .GLOBAL _icr31,    _icr32,    _icr33,    _icr34,    _icr35,    _icr36
 .GLOBAL _icr37,    _icr38,    _icr39,    _icr40,    _icr41,    _icr42
 .GLOBAL _icr43,    _icr44,    _icr45,    _icr46,    _icr47,    _rsrr
 .GLOBAL _stcr,     _tbcr,     _ctbr,     _clkr,     _wpr,      _divr0
 .GLOBAL _divr1,    _ddr7,     _ddr8,     _ddr9,     _ddrb,     _pfr7
 .GLOBAL _pfr8,     _pfr9,     _pfrb,     _pfr27,    _asr0,     _amr0
 .GLOBAL _asr1,     _amr1,     _asr2,     _amr2,     _asr3,     _amr3
 .GLOBAL _asr4,     _amr4,     _asr5,     _amr5,     _asr6,     _amr6
 .GLOBAL _asr7,     _amr7,     _amd0,     _amd1,     _amd2,     _amd3
 .GLOBAL _amd4,     _amd5,     _amd6,     _amd7,     _cse,      _bstr0
 .GLOBAL _dmcr6,    _dmcr7,    _che,      _rfcr,     _modr,     _ler
 .GLOBAL _dmasa0,   _dmada0,   _dmasa1,   _dmada1,   _dmasa2,   _dmada2
 .GLOBAL _dmasa3,   _dmada3,   _dmasa4,   _dmada4,   _fmcs,     _fmwt
 .GLOBAL _canl0,   __canh0,   __canm0,   _creg0,    __canl1,   __canh1
 .GLOBAL __canm1,   _creg1,    __canl2,   __canh2,   __canm2,   _creg2

_pdr0      .EQU 0x000000 /* Port Data Registers */
PDR0       .EQU 0x000000
_pdr1      .EQU 0x000001
PDR1       .EQU 0x000001
_pdr2      .EQU 0x000002
PDR2       .EQU 0x000002
_pdr3      .EQU 0x000003
PDR3       .EQU 0x000003
_pdr4      .EQU 0x000004
PDR4       .EQU 0x000004
_pdr5      .EQU 0x000005
PDR5       .EQU 0x000005
_pdr6      .EQU 0x000006
PDR6       .EQU 0x000006
_pdr7      .EQU 0x000007
PDR7       .EQU 0x000007
_pdr8      .EQU 0x000008
PDR8       .EQU 0x000008
_pdr9      .EQU 0x000009
PDR9       .EQU 0x000009
_pdrb      .EQU 0x00000B
PDRB       .EQU 0x00000B
_pdrg      .EQU 0x000010
PDRG       .EQU 0x000010
_pdrh      .EQU 0x000011
PDRH       .EQU 0x000011
_pdri      .EQU 0x000012
PDRI       .EQU 0x000012
_pdrj      .EQU 0x000013
PDRJ       .EQU 0x000013
_pdrk      .EQU 0x000014
PDRK       .EQU 0x000014
_pdrl      .EQU 0x000015
PDRL       .EQU 0x000015
_pdrm      .EQU 0x000016
PDRM       .EQU 0x000016
_pdrn      .EQU 0x000017
PDRN       .EQU 0x000017
_pdro      .EQU 0x000018
PDRO       .EQU 0x000018
_pdrp      .EQU 0x000019
PDRP       .EQU 0x000019
_pdrq      .EQU 0x00001A
PDRQ       .EQU 0x00001A
_pdrr      .EQU 0x00001B
PDRR       .EQU 0x00001B
_pdrs      .EQU 0x00001C
PDRS       .EQU 0x00001C
_eirr      .EQU 0x000040
EIRR       .EQU 0x000040 /* Ext. Int/NMI */
_enir      .EQU 0x000041
ENIR       .EQU 0x000041
_elvr      .EQU 0x000042
ELVR       .EQU 0x000042
_dicr      .EQU 0x000044
DICR       .EQU 0x000044 /* DLYI/I-Unit */
_hrcl      .EQU 0x000045
HRCL       .EQU 0x000045
_tmrlr0    .EQU 0x000048
TMRLR0     .EQU 0x000048 /* Reload Timer0 */
_tmr0      .EQU 0x00004A
TMR0       .EQU 0x00004A
_tmcsr0    .EQU 0x00004E
TMCSR0     .EQU 0x00004E
_tmrlr1    .EQU 0x000050
TMRLR1     .EQU 0x000050 /* Reload Timer1 */
_tmr1      .EQU 0x000052
TMR1       .EQU 0x000052
_tmcsr1    .EQU 0x000056
TMCSR1     .EQU 0x000056
_tmrlr2    .EQU 0x000058
TMRLR2     .EQU 0x000058 /* Reload Timer2 */
_tmr2      .EQU 0x00005A
TMR2       .EQU 0x00005A
_tmcsr2    .EQU 0x00005E
TMCSR2     .EQU 0x00005E
_ssr0      .EQU 0x000060
SSR0       .EQU 0x000060 /* UART0 */
_sidr0     .EQU 0x000061
SIDR0      .EQU 0x000061
_sodr0     .EQU 0x000061
SODR0      .EQU 0x000061
_scr0      .EQU 0x000062
SCR0       .EQU 0x000062
_smr0      .EQU 0x000063
SMR0       .EQU 0x000063
_uls0      .EQU 0x000064
ULS0       .EQU 0x000064
_utim0     .EQU 0x000068
UTIM0      .EQU 0x000068
_utimr0    .EQU 0x000068
UTIMR0     .EQU 0x000068
_drcl0     .EQU 0x00006A
DRCL0      .EQU 0x00006A
_utimc0    .EQU 0x00006B
UTIMC0     .EQU 0x00006B
_ssr1      .EQU 0x00006C
SSR1       .EQU 0x00006C /* UART1 */
_sidr1     .EQU 0x00006D
SIDR1      .EQU 0x00006D
_sodr1     .EQU 0x00006D
SODR1      .EQU 0x00006D
_scr1      .EQU 0x00006E
SCR1       .EQU 0x00006E
_smr1      .EQU 0x00006F
SMR1       .EQU 0x00006F
_uls1      .EQU 0x000070
ULS1       .EQU 0x000070
_utim1     .EQU 0x000074
UTIM1      .EQU 0x000074
_utimr1    .EQU 0x000074
UTIMR1     .EQU 0x000074
_drcl1     .EQU 0x000076
DRCL1      .EQU 0x000076
_utimc1    .EQU 0x000077
UTIMC1     .EQU 0x000077
_ssr2      .EQU 0x000078
SSR2       .EQU 0x000078 /* UART2 */
_sidr2     .EQU 0x000079
SIDR2      .EQU 0x000079
_sodr2     .EQU 0x000079
SODR2      .EQU 0x000079
_scr2      .EQU 0x00007A
SCR2       .EQU 0x00007A
_smr2      .EQU 0x00007B
SMR2       .EQU 0x00007B
_uls2      .EQU 0x00007C
ULS2       .EQU 0x00007C
_utim2     .EQU 0x000080
UTIM2      .EQU 0x000080
_utimr2    .EQU 0x000080
UTIMR2     .EQU 0x000080
_drcl2     .EQU 0x000082
DRCL2      .EQU 0x000082
_utimc2    .EQU 0x000083
UTIMC2     .EQU 0x000083
_smcs0     .EQU 0x000084
SMCS0      .EQU 0x000084 /* SIO0 */
_ses0      .EQU 0x000086
SES0       .EQU 0x000086
_sdr0      .EQU 0x000087
SDR0       .EQU 0x000087
_smcs1     .EQU 0x000088
SMCS1      .EQU 0x000088 /* SIO1 */
_ses1      .EQU 0x00008A
SES1       .EQU 0x00008A
_sdr1      .EQU 0x00008B
SDR1       .EQU 0x00008B
_cdcr0     .EQU 0x00008C
CDCR0      .EQU 0x00008C /* SIO PRESC */
_psmr0     .EQU 0x00008D
PSMR0      .EQU 0x00008D
_cdcr1     .EQU 0x00008E
CDCR1      .EQU 0x00008E
_psmr1     .EQU 0x00008F
PSMR1      .EQU 0x00008F
_ibcr      .EQU 0x000094
IBCR       .EQU 0x000094 /* I2C */
_ibsr      .EQU 0x000095
IBSR       .EQU 0x000095
_iadr      .EQU 0x000096
IADR       .EQU 0x000096
_iccr      .EQU 0x000097
ICCR       .EQU 0x000097
_idar      .EQU 0x000099
IDAR       .EQU 0x000099
_idbl      .EQU 0x00009B
IDBL       .EQU 0x00009B
_admd      .EQU 0x00009C
ADMD       .EQU 0x00009C /* ADC */
_adch      .EQU 0x00009D
ADCH       .EQU 0x00009D
_adcs      .EQU 0x00009F
ADCS       .EQU 0x00009F
_adcd      .EQU 0x0000A0
ADCD       .EQU 0x0000A0
_adbl      .EQU 0x0000A3
ADBL       .EQU 0x0000A3
_dacr      .EQU 0x0000A5
DACR       .EQU 0x0000A5 /* DAC */
_dadr0     .EQU 0x0000A6
DADR0      .EQU 0x0000A6
_dadr1     .EQU 0x0000A8
DADR1      .EQU 0x0000A8
_ddbl      .EQU 0x0000AB
DDBL       .EQU 0x0000AB
_iotdbl0   .EQU 0x0000AC
IOTDBL0    .EQU 0x0000AC /* Input Capture */
_ics01     .EQU 0x0000AD
ICS01      .EQU 0x0000AD
_iotdbl1   .EQU 0x0000AE
IOTDBL1    .EQU 0x0000AE
_ics23     .EQU 0x0000AF
ICS23      .EQU 0x0000AF
_ipcp0     .EQU 0x0000B0
IPCP0      .EQU 0x0000B0
_ipcp1     .EQU 0x0000B2
IPCP1      .EQU 0x0000B2
_ipcp2     .EQU 0x0000B4
IPCP2      .EQU 0x0000B4
_ipcp3     .EQU 0x0000B6
IPCP3      .EQU 0x0000B6
_ocs01     .EQU 0x0000B8
OCS01      .EQU 0x0000B8 /* Output Capture */
_ocs23     .EQU 0x0000BA
OCS23      .EQU 0x0000BA
_occp0     .EQU 0x0000BC
OCCP0      .EQU 0x0000BC
_occp1     .EQU 0x0000BE
OCCP1      .EQU 0x0000BE
_occp2     .EQU 0x0000C0
OCCP2      .EQU 0x0000C0
_occp3     .EQU 0x0000C2
OCCP3      .EQU 0x0000C2
_tcdt0     .EQU 0x0000C8
TCDT0      .EQU 0x0000C8 /* Free Running Timer0 */
_tccs0     .EQU 0x0000CB
TCCS0      .EQU 0x0000CB
_tcdt1     .EQU 0x0000CC
TCDT1      .EQU 0x0000CC /* Free Running Timer1 */
_tccs1     .EQU 0x0000CF
TCCS1      .EQU 0x0000CF
_zpd0      .EQU 0x0000D0
ZPD0       .EQU 0x0000D0 /* Stepper Motor Control */
_pwc0      .EQU 0x0000D1
PWC0       .EQU 0x0000D1
_zpd1      .EQU 0x0000D2
ZPD1       .EQU 0x0000D2
_pwc1      .EQU 0x0000D3
PWC1       .EQU 0x0000D3
_zpd2      .EQU 0x0000D4
ZPD2       .EQU 0x0000D4
_pwc2      .EQU 0x0000D5
PWC2       .EQU 0x0000D5
_zpd3      .EQU 0x0000D6
ZPD3       .EQU 0x0000D6
_pwc3      .EQU 0x0000D7
PWC3       .EQU 0x0000D7
_pwc20     .EQU 0x0000D8
PWC20      .EQU 0x0000D8
_pwc10     .EQU 0x0000D9
PWC10      .EQU 0x0000D9
_pws20     .EQU 0x0000DA
PWS20      .EQU 0x0000DA
_pws10     .EQU 0x0000DB
PWS10      .EQU 0x0000DB
_pwc21     .EQU 0x0000DC
PWC21      .EQU 0x0000DC
_pwc11     .EQU 0x0000DD
PWC11      .EQU 0x0000DD
_pws21     .EQU 0x0000DE
PWS21      .EQU 0x0000DE
_pws11     .EQU 0x0000DF
PWS11      .EQU 0x0000DF
_pwc22     .EQU 0x0000E0
PWC22      .EQU 0x0000E0
_pwc12     .EQU 0x0000E1
PWC12      .EQU 0x0000E1
_pws22     .EQU 0x0000E2
PWS22      .EQU 0x0000E2
_pws12     .EQU 0x0000E3
PWS12      .EQU 0x0000E3
_pwc23     .EQU 0x0000E4
PWC23      .EQU 0x0000E4
_pwc13     .EQU 0x0000E5
PWC13      .EQU 0x0000E5
_pws23     .EQU 0x0000E6
PWS23      .EQU 0x0000E6
_pws13     .EQU 0x0000E7
PWS13      .EQU 0x0000E7
_smdbl0    .EQU 0x0000E8
SMDBL0     .EQU 0x0000E8
_smdbl1    .EQU 0x0000E9
SMDBL1     .EQU 0x0000E9
_smdbl2    .EQU 0x0000EA
SMDBL2     .EQU 0x0000EA
_smdbl3    .EQU 0x0000EB
SMDBL3     .EQU 0x0000EB
_sgdbl     .EQU 0x0000ED
SGDBL      .EQU 0x0000ED /* Sound Generator */
_sgcr      .EQU 0x0000EE
SGCR       .EQU 0x0000EE
_sgar      .EQU 0x0000F0
SGAR       .EQU 0x0000F0
_sgfr      .EQU 0x0000F1
SGFR       .EQU 0x0000F1
_sgtr      .EQU 0x0000F2
SGTR       .EQU 0x0000F2
_sgdr      .EQU 0x0000F3
SGDR       .EQU 0x0000F3
_wtdbl     .EQU 0x0000F5
WTDBL      .EQU 0x0000F5 /* Real Time Clock (RTC) */
_wtcr      .EQU 0x0000F6
WTCR       .EQU 0x0000F6
_wtbr      .EQU 0x0000F9
WTBR       .EQU 0x0000F9
_wthr      .EQU 0x0000FC
WTHR       .EQU 0x0000FC
_wtmr      .EQU 0x0000FD
WTMR       .EQU 0x0000FD
_wtsr      .EQU 0x0000FE
WTSR       .EQU 0x0000FE
_tmrlr3    .EQU 0x000100
TMRLR3     .EQU 0x000100 /* Reload Timer3 */
_tmr3      .EQU 0x000102
TMR3       .EQU 0x000102
_tmcsr3    .EQU 0x000106
TMCSR3     .EQU 0x000106
_tmrlr4    .EQU 0x000108
TMRLR4     .EQU 0x000108 /* Reload Timer4 */
_tmr4      .EQU 0x00010A
TMR4       .EQU 0x00010A
_tmcsr4    .EQU 0x00010E
TMCSR4     .EQU 0x00010E
_tmrlr5    .EQU 0x000110
TMRLR5     .EQU 0x000110 /* Reload Timer5 */
_tmr5      .EQU 0x000112
TMR5       .EQU 0x000112
_tmcsr5    .EQU 0x000116
TMCSR5     .EQU 0x000116
_gcn10     .EQU 0x000118
GCN10      .EQU 0x000118 /* PWM CNTRL */
_pdbl0     .EQU 0x00011A
PDBL0      .EQU 0x00011A
_gcn20     .EQU 0x00011B
GCN20      .EQU 0x00011B
_gcn11     .EQU 0x00011C
GCN11      .EQU 0x00011C
_pdbl1     .EQU 0x00011E
PDBL1      .EQU 0x00011E
_gcn21     .EQU 0x00011F
GCN21      .EQU 0x00011F
_ptmr0     .EQU 0x000120
PTMR0      .EQU 0x000120 /* PWM0 */
_pcsr0     .EQU 0x000122
PCSR0      .EQU 0x000122
_pdut0     .EQU 0x000124
PDUT0      .EQU 0x000124
_pcnh0     .EQU 0x000126
PCNH0      .EQU 0x000126
_pcnl0     .EQU 0x000127
PCNL0      .EQU 0x000127
_ptmr1     .EQU 0x000128
PTMR1      .EQU 0x000128 /* PWM1 */
_pcsr1     .EQU 0x00012A
PCSR1      .EQU 0x00012A
_pdut1     .EQU 0x00012C
PDUT1      .EQU 0x00012C
_pcnh1     .EQU 0x00012E
PCNH1      .EQU 0x00012E
_pcnl1     .EQU 0x00012F
PCNL1      .EQU 0x00012F
_ptmr2     .EQU 0x000130
PTMR2      .EQU 0x000130 /* PWM2 */
_pcsr2     .EQU 0x000132
PCSR2      .EQU 0x000132
_pdut2     .EQU 0x000134
PDUT2      .EQU 0x000134
_pcnh2     .EQU 0x000136
PCNH2      .EQU 0x000136
_pcnl2     .EQU 0x000137
PCNL2      .EQU 0x000137
_ptmr3     .EQU 0x000138
PTMR3      .EQU 0x000138 /* PWM3 */
_pcsr3     .EQU 0x00013A
PCSR3      .EQU 0x00013A
_pdut3     .EQU 0x00013C
PDUT3      .EQU 0x00013C
_pcnh3     .EQU 0x00013E
PCNH3      .EQU 0x00013E
_pcnl3     .EQU 0x00013F
PCNL3      .EQU 0x00013F
_ptmr4     .EQU 0x000140
PTMR4      .EQU 0x000140 /* PWM4 */
_pcsr4     .EQU 0x000142
PCSR4      .EQU 0x000142
_pdut4     .EQU 0x000144
PDUT4      .EQU 0x000144
_pcnh4     .EQU 0x000146
PCNH4      .EQU 0x000146
_pcnl4     .EQU 0x000147
PCNL4      .EQU 0x000147
_ptmr5     .EQU 0x000148
PTMR5      .EQU 0x000148 /* PWM5 */
_pcsr5     .EQU 0x00014A
PCSR5      .EQU 0x00014A
_pdut5     .EQU 0x00014C
PDUT5      .EQU 0x00014C
_pcnh5     .EQU 0x00014E
PCNH5      .EQU 0x00014E
_pcnl5     .EQU 0x00014F
PCNL5      .EQU 0x00014F
_ptmr6     .EQU 0x000150
PTMR6      .EQU 0x000150 /* PWM6 */
_pcsr6     .EQU 0x000152
PCSR6      .EQU 0x000152
_pdut6     .EQU 0x000154
PDUT6      .EQU 0x000154
_pcnh6     .EQU 0x000156
PCNH6      .EQU 0x000156
_pcnl6     .EQU 0x000157
PCNL6      .EQU 0x000157
_ptmr7     .EQU 0x000158
PTMR7      .EQU 0x000158 /* PWM7 */
_pcsr7     .EQU 0x00015A
PCSR7      .EQU 0x00015A
_pdut7     .EQU 0x00015C
PDUT7      .EQU 0x00015C
_pcnh7     .EQU 0x00015E
PCNH7      .EQU 0x00015E
_pcnl7     .EQU 0x00015F
PCNL7      .EQU 0x00015F
_cmcr      .EQU 0x000164
CMCR       .EQU 0x000164 /* ClockM */
_cmpr      .EQU 0x000166
CMPR       .EQU 0x000166
_cmls0     .EQU 0x000168
CMLS0      .EQU 0x000168
_cmls1     .EQU 0x00016A
CMLS1      .EQU 0x00016A
_cmls2     .EQU 0x00016C
CMLS2      .EQU 0x00016C
_cmls3     .EQU 0x00016E
CMLS3      .EQU 0x00016E
_cmlt0     .EQU 0x000170
CMLT0      .EQU 0x000170
_cmlt1     .EQU 0x000172
CMLT1      .EQU 0x000172
_cmlt2     .EQU 0x000174
CMLT2      .EQU 0x000174
_cmlt3     .EQU 0x000176
CMLT3      .EQU 0x000176
_cmac      .EQU 0x000178
CMAC       .EQU 0x000178
_pdrcr     .EQU 0x00017D
PDRCR      .EQU 0x00017D /* Power Down Reset */
_accdbl    .EQU 0x000180
ACCDBL     .EQU 0x000180 /* Alarm Comparator */
_acsr      .EQU 0x000181
ACSR       .EQU 0x000181
_ibcr2     .EQU 0x000184
IBCR2      .EQU 0x000184 /* I2C */
_ibsr2     .EQU 0x000185
IBSR2      .EQU 0x000185
_itbah2    .EQU 0x000186
ITBAH2     .EQU 0x000186
_itbal2    .EQU 0x000187
ITBAL2     .EQU 0x000187
_itmkh2    .EQU 0x000188
ITMKH2     .EQU 0x000188
_itmkl2    .EQU 0x000189
ITMKL2     .EQU 0x000189
_ismk2     .EQU 0x00018A
ISMK2      .EQU 0x00018A
_isba2     .EQU 0x00018B
ISBA2      .EQU 0x00018B
_idar2     .EQU 0x00018D
IDAR2      .EQU 0x00018D
_iccr2     .EQU 0x00018E
ICCR2      .EQU 0x00018E
_idbl2     .EQU 0x00018F
IDBL2      .EQU 0x00018F
_f362md    .EQU 0x0001FE
F362MD     .EQU 0x0001FE /* MODE REGISTER */
_dmaca0    .EQU 0x000200
DMACA0     .EQU 0x000200 /* DMAC */
_dmacb0    .EQU 0x000204
DMACB0     .EQU 0x000204
_dmaca1    .EQU 0x000208
DMACA1     .EQU 0x000208
_dmacb1    .EQU 0x00020C
DMACB1     .EQU 0x00020C
_dmaca2    .EQU 0x000210
DMACA2     .EQU 0x000210
_dmacb2    .EQU 0x000214
DMACB2     .EQU 0x000214
_dmaca3    .EQU 0x000218
DMACA3     .EQU 0x000218
_dmacb3    .EQU 0x00021C
DMACB3     .EQU 0x00021C
_dmaca4    .EQU 0x000220
DMACA4     .EQU 0x000220
_dmacb4    .EQU 0x000224
DMACB4     .EQU 0x000224
_dmacr     .EQU 0x000240
DMACR      .EQU 0x000240 /* DMAC CNTL */
_irbs      .EQU 0x000300
IRBS       .EQU 0x000300 /* Instruction Cache */
_isize     .EQU 0x000307
ISIZE      .EQU 0x000307
_ichcr     .EQU 0x0003E7
ICHCR      .EQU 0x0003E7
_bsd0      .EQU 0x0003F0
BSD0       .EQU 0x0003F0 /* Bit Search Module */
_bsd1      .EQU 0x0003F4
BSD1       .EQU 0x0003F4
_bsdc      .EQU 0x0003F8
BSDC       .EQU 0x0003F8
_bsrr      .EQU 0x0003FC
BSRR       .EQU 0x0003FC
_ddrg      .EQU 0x000400
DDRG       .EQU 0x000400 /* Port Direction Register */
_ddrh      .EQU 0x000401
DDRH       .EQU 0x000401
_ddri      .EQU 0x000402
DDRI       .EQU 0x000402
_ddrj      .EQU 0x000403
DDRJ       .EQU 0x000403
_ddrk      .EQU 0x000404
DDRK       .EQU 0x000404
_ddrl      .EQU 0x000405
DDRL       .EQU 0x000405
_ddrm      .EQU 0x000406
DDRM       .EQU 0x000406
_ddrn      .EQU 0x000407
DDRN       .EQU 0x000407
_ddro      .EQU 0x000408
DDRO       .EQU 0x000408
_ddrp      .EQU 0x000409
DDRP       .EQU 0x000409
_ddrq      .EQU 0x00040A
DDRQ       .EQU 0x00040A
_ddrr      .EQU 0x00040B
DDRR       .EQU 0x00040B
_ddrs      .EQU 0x00040C
DDRS       .EQU 0x00040C
_pfrg      .EQU 0x000410
PFRG       .EQU 0x000410 /* Port Function Register */
_pfrh      .EQU 0x000411
PFRH       .EQU 0x000411
_pfri      .EQU 0x000412
PFRI       .EQU 0x000412
_pfrj      .EQU 0x000413
PFRJ       .EQU 0x000413
_pfrk      .EQU 0x000414
PFRK       .EQU 0x000414
_pfrl      .EQU 0x000415
PFRL       .EQU 0x000415
_pfrm      .EQU 0x000416
PFRM       .EQU 0x000416
_pfrn      .EQU 0x000417
PFRN       .EQU 0x000417
_pfro      .EQU 0x000418
PFRO       .EQU 0x000418
_pfrp      .EQU 0x000419
PFRP       .EQU 0x000419
_pfrq      .EQU 0x00041A
PFRQ       .EQU 0x00041A
_pfrr      .EQU 0x00041B
PFRR       .EQU 0x00041B
_pfrs      .EQU 0x00041C
PFRS       .EQU 0x00041C
_icr00     .EQU 0x000440
ICR00      .EQU 0x000440 /* Interrupt Control Unit */
_icr01     .EQU 0x000441
ICR01      .EQU 0x000441
_icr02     .EQU 0x000442
ICR02      .EQU 0x000442
_icr03     .EQU 0x000443
ICR03      .EQU 0x000443
_icr04     .EQU 0x000444
ICR04      .EQU 0x000444
_icr05     .EQU 0x000445
ICR05      .EQU 0x000445
_icr06     .EQU 0x000446
ICR06      .EQU 0x000446
_icr07     .EQU 0x000447
ICR07      .EQU 0x000447
_icr08     .EQU 0x000448
ICR08      .EQU 0x000448
_icr09     .EQU 0x000449
ICR09      .EQU 0x000449
_icr10     .EQU 0x00044A
ICR10      .EQU 0x00044A
_icr11     .EQU 0x00044B
ICR11      .EQU 0x00044B
_icr12     .EQU 0x00044C
ICR12      .EQU 0x00044C
_icr13     .EQU 0x00044D
ICR13      .EQU 0x00044D
_icr14     .EQU 0x00044E
ICR14      .EQU 0x00044E
_icr15     .EQU 0x00044F
ICR15      .EQU 0x00044F
_icr16     .EQU 0x000450
ICR16      .EQU 0x000450
_icr17     .EQU 0x000451
ICR17      .EQU 0x000451
_icr18     .EQU 0x000452
ICR18      .EQU 0x000452
_icr19     .EQU 0x000453
ICR19      .EQU 0x000453
_icr20     .EQU 0x000454
ICR20      .EQU 0x000454
_icr21     .EQU 0x000455
ICR21      .EQU 0x000455
_icr22     .EQU 0x000456
ICR22      .EQU 0x000456
_icr23     .EQU 0x000457
ICR23      .EQU 0x000457
_icr24     .EQU 0x000458
ICR24      .EQU 0x000458
_icr25     .EQU 0x000459
ICR25      .EQU 0x000459
_icr26     .EQU 0x00045A
ICR26      .EQU 0x00045A
_icr27     .EQU 0x00045B
ICR27      .EQU 0x00045B
_icr28     .EQU 0x00045C
ICR28      .EQU 0x00045C
_icr29     .EQU 0x00045D
ICR29      .EQU 0x00045D
_icr30     .EQU 0x00045E
ICR30      .EQU 0x00045E
_icr31     .EQU 0x00045F
ICR31      .EQU 0x00045F
_icr32     .EQU 0x000460
ICR32      .EQU 0x000460
_icr33     .EQU 0x000461
ICR33      .EQU 0x000461
_icr34     .EQU 0x000462
ICR34      .EQU 0x000462
_icr35     .EQU 0x000463
ICR35      .EQU 0x000463
_icr36     .EQU 0x000464
ICR36      .EQU 0x000464
_icr37     .EQU 0x000465
ICR37      .EQU 0x000465
_icr38     .EQU 0x000466
ICR38      .EQU 0x000466
_icr39     .EQU 0x000467
ICR39      .EQU 0x000467
_icr40     .EQU 0x000468
ICR40      .EQU 0x000468
_icr41     .EQU 0x000469
ICR41      .EQU 0x000469
_icr42     .EQU 0x00046A
ICR42      .EQU 0x00046A
_icr43     .EQU 0x00046B
ICR43      .EQU 0x00046B
_icr44     .EQU 0x00046C
ICR44      .EQU 0x00046C
_icr45     .EQU 0x00046D
ICR45      .EQU 0x00046D
_icr46     .EQU 0x00046E
ICR46      .EQU 0x00046E
_icr47     .EQU 0x00046F
ICR47      .EQU 0x00046F
_rsrr      .EQU 0x000480
RSRR       .EQU 0x000480 /* Clock Control Unit */
_stcr      .EQU 0x000481
STCR       .EQU 0x000481
_tbcr      .EQU 0x000482
TBCR       .EQU 0x000482
_ctbr      .EQU 0x000483
CTBR       .EQU 0x000483
_clkr      .EQU 0x000484
CLKR       .EQU 0x000484
_wpr       .EQU 0x000485
WPR        .EQU 0x000485
_divr0     .EQU 0x000486
DIVR0      .EQU 0x000486
_divr1     .EQU 0x000487
DIVR1      .EQU 0x000487
_ddr0      .EQU 0x000600
DDR0       .EQU 0x000600 /* T Port Direction Register */
_ddr1      .EQU 0x000601
DDR1       .EQU 0x000601
_ddr2      .EQU 0x000602
DDR2       .EQU 0x000602
_ddr3      .EQU 0x000603
DDR3       .EQU 0x000603
_ddr4      .EQU 0x000604
DDR4       .EQU 0x000604
_ddr5      .EQU 0x000605
DDR5       .EQU 0x000605
_ddr6      .EQU 0x000606
DDR6       .EQU 0x000606
_ddr7      .EQU 0x000607
DDR7       .EQU 0x000607
_ddr8      .EQU 0x000608
DDR8       .EQU 0x000608
_ddr9      .EQU 0x000609
DDR9       .EQU 0x000609
_ddrb      .EQU 0x00060B
DDRB       .EQU 0x00060B
_pfr0      .EQU 0x000610
PFR0       .EQU 0x000610 /* T Port Function Register */
_pfr1      .EQU 0x000611
PFR1       .EQU 0x000611
_pfr2      .EQU 0x000612
PFR2       .EQU 0x000612
_pfr3      .EQU 0x000613
PFR3       .EQU 0x000613
_pfr4      .EQU 0x000614
PFR4       .EQU 0x000614
_pfr5      .EQU 0x000615
PFR5       .EQU 0x000615
_pfr6      .EQU 0x000616
PFR6       .EQU 0x000616
_pfr7      .EQU 0x000617
PFR7       .EQU 0x000617
_pfr8      .EQU 0x000618
PFR8       .EQU 0x000618
_pfr9      .EQU 0x000619
PFR9       .EQU 0x000619
_pfrb      .EQU 0x00061B
PFRB       .EQU 0x00061B
_pfr27     .EQU 0x000627
PFR27      .EQU 0x000627
_asr0      .EQU 0x000640
ASR0       .EQU 0x000640 /* Chip Select Registers */
_amr0      .EQU 0x000642
AMR0       .EQU 0x000642
_asr1      .EQU 0x000644
ASR1       .EQU 0x000644
_amr1      .EQU 0x000646
AMR1       .EQU 0x000646
_asr2      .EQU 0x000648
ASR2       .EQU 0x000648
_amr2      .EQU 0x00064A
AMR2       .EQU 0x00064A
_asr3      .EQU 0x00064C
ASR3       .EQU 0x00064C
_amr3      .EQU 0x00064E
AMR3       .EQU 0x00064E
_asr4      .EQU 0x000650
ASR4       .EQU 0x000650
_amr4      .EQU 0x000652
AMR4       .EQU 0x000652
_asr5      .EQU 0x000654
ASR5       .EQU 0x000654
_amr5      .EQU 0x000656
AMR5       .EQU 0x000656
_asr6      .EQU 0x000658
ASR6       .EQU 0x000658
_amr6      .EQU 0x00065A
AMR6       .EQU 0x00065A
_asr7      .EQU 0x00065C
ASR7       .EQU 0x00065C
_amr7      .EQU 0x00065E
AMR7       .EQU 0x00065E
_amd0      .EQU 0x000660
AMD0       .EQU 0x000660
_amd1      .EQU 0x000661
AMD1       .EQU 0x000661
_amd2      .EQU 0x000662
AMD2       .EQU 0x000662
_amd3      .EQU 0x000663
AMD3       .EQU 0x000663
_amd4      .EQU 0x000664
AMD4       .EQU 0x000664
_amd5      .EQU 0x000665
AMD5       .EQU 0x000665
_amd6      .EQU 0x000666
AMD6       .EQU 0x000666
_amd7      .EQU 0x000667
AMD7       .EQU 0x000667
_cse       .EQU 0x000668
CSE        .EQU 0x000668
_bstr0     .EQU 0x00066A
BSTR0      .EQU 0x00066A
_dmcr6     .EQU 0x00066C
DMCR6      .EQU 0x00066C
_dmcr7     .EQU 0x00066E
DMCR7      .EQU 0x00066E
_che       .EQU 0x000670
CHE        .EQU 0x000670
_rfcr      .EQU 0x000672
RFCR       .EQU 0x000672
_modr      .EQU 0x0007FD
MODR       .EQU 0x0007FD
_ler       .EQU 0x0007FE
LER        .EQU 0x0007FE
_dmasa0    .EQU 0x001000
DMASA0     .EQU 0x001000 /* DMAC */
_dmada0    .EQU 0x001004
DMADA0     .EQU 0x001004
_dmasa1    .EQU 0x001008
DMASA1     .EQU 0x001008
_dmada1    .EQU 0x00100C
DMADA1     .EQU 0x00100C
_dmasa2    .EQU 0x001010
DMASA2     .EQU 0x001010
_dmada2    .EQU 0x001014
DMADA2     .EQU 0x001014
_dmasa3    .EQU 0x001018
DMASA3     .EQU 0x001018
_dmada3    .EQU 0x00101C
DMADA3     .EQU 0x00101C
_dmasa4    .EQU 0x001020
DMASA4     .EQU 0x001020
_dmada4    .EQU 0x001024
DMADA4     .EQU 0x001024
_fmcs      .EQU 0x007000
FMCS       .EQU 0x007000 /* FLASH MEMORY */
_fmwt      .EQU 0x007004
FMWT       .EQU 0x007004
_canl0    .EQU 0x100000
CANL0     .EQU 0x100000 /* Can0 */
__canh0    .EQU 0x100010
_CANH0     .EQU 0x100010
__canm0    .EQU 0x10002C
_CANM0     .EQU 0x10002C
_creg0     .EQU 0x10012C
CREG0      .EQU 0x10012C
__canl1    .EQU 0x100200
_CANL1     .EQU 0x100200 /* CAN1 */
__canh1    .EQU 0x100210
_CANH1     .EQU 0x100210
__canm1    .EQU 0x10022C
_CANM1     .EQU 0x10022C
_creg1     .EQU 0x10032C
CREG1      .EQU 0x10032C
__canl2    .EQU 0x100400
_CANL2     .EQU 0x100400 /* CAN2 */
__canh2    .EQU 0x100410
_CANH2     .EQU 0x100410
__canm2    .EQU 0x10042C
_CANM2     .EQU 0x10042C
_creg2     .EQU 0x10052C
CREG2      .EQU 0x10052C
#pragma endasm
#else

#ifndef _MB91XXX_H
#define _MB91XXX_H

/* BIT-STRUCTURE-DEFINITIONS */

typedef unsigned char		IO_BYTE;
typedef unsigned short		IO_WORD;
typedef unsigned long		IO_LWORD;
typedef const unsigned short	IO_WORD_READ;

typedef union{   /* Port Data Registers */
    IO_BYTE	byte;
    struct{
    IO_BYTE PD07 :1;
    IO_BYTE PD06 :1;
    IO_BYTE PD05 :1;
    IO_BYTE PD04 :1;
    IO_BYTE PD03 :1;
    IO_BYTE PD02 :1;
    IO_BYTE PD01 :1;
    IO_BYTE PD00 :1;
  }bit;
 }PDR0STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PD17 :1;
    IO_BYTE PD16 :1;
    IO_BYTE PD15 :1;
    IO_BYTE PD14 :1;
    IO_BYTE PD13 :1;
    IO_BYTE PD12 :1;
    IO_BYTE PD11 :1;
    IO_BYTE PD10 :1;
  }bit;
 }PDR1STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PD27 :1;
    IO_BYTE PD26 :1;
    IO_BYTE PD25 :1;
    IO_BYTE PD24 :1;
    IO_BYTE PD23 :1;
    IO_BYTE PD22 :1;
    IO_BYTE PD21 :1;
    IO_BYTE PD20 :1;
  }bit;
 }PDR2STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PD37 :1;
    IO_BYTE PD36 :1;
    IO_BYTE PD35 :1;
    IO_BYTE PD34 :1;
    IO_BYTE PD33 :1;
    IO_BYTE PD32 :1;
    IO_BYTE PD31 :1;
    IO_BYTE PD30 :1;
  }bit;
 }PDR3STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PD47 :1;
    IO_BYTE PD46 :1;
    IO_BYTE PD45 :1;
    IO_BYTE PD44 :1;
    IO_BYTE PD43 :1;
    IO_BYTE PD42 :1;
    IO_BYTE PD41 :1;
    IO_BYTE PD40 :1;
  }bit;
 }PDR4STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PD57 :1;
    IO_BYTE PD56 :1;
    IO_BYTE PD55 :1;
    IO_BYTE PD54 :1;
    IO_BYTE PD53 :1;
    IO_BYTE PD52 :1;
    IO_BYTE PD51 :1;
    IO_BYTE PD50 :1;
  }bit;
 }PDR5STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE      :1;
    IO_BYTE      :1;
    IO_BYTE      :1;
    IO_BYTE PD64 :1;
    IO_BYTE PD63 :1;
    IO_BYTE PD62 :1;
    IO_BYTE PD61 :1;
    IO_BYTE PD60 :1;
  }bit;
 }PDR6STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE PD76 :1;
    IO_BYTE PD75 :1;
    IO_BYTE PD74 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
 }PDR7STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PD87 :1;
    IO_BYTE PD86 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE PD82 :1;
    IO_BYTE PD81 :1;
    IO_BYTE  :1;
  }bit;
 }PDR8STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PD97 :1;
    IO_BYTE PD96 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE PD93 :1;
    IO_BYTE PD92 :1;
    IO_BYTE PD91 :1;
    IO_BYTE PD90 :1;
  }bit;
 }PDR9STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE PDB2 :1;
    IO_BYTE PDB1 :1;
    IO_BYTE PDB0 :1;
  }bit;
 }PDRBSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PDG7 :1;
    IO_BYTE PDG6 :1;
    IO_BYTE PDG5 :1;
    IO_BYTE PDG4 :1;
    IO_BYTE PDG3 :1;
    IO_BYTE PDG2 :1;
    IO_BYTE PDG1 :1;
    IO_BYTE PDG0 :1;
  }bit;
 }PDRGSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PDH7 :1;
    IO_BYTE PDH6 :1;
    IO_BYTE PDH5 :1;
    IO_BYTE PDH4 :1;
    IO_BYTE PDH3 :1;
    IO_BYTE PDH2 :1;
    IO_BYTE PDH1 :1;
    IO_BYTE PDH0 :1;
  }bit;
 }PDRHSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PDI7 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE PDI3 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
 }PDRISTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PDJ7 :1;
    IO_BYTE PDJ6 :1;
    IO_BYTE PDJ5 :1;
    IO_BYTE PDJ4 :1;
    IO_BYTE PDJ3 :1;
    IO_BYTE PDJ2 :1;
    IO_BYTE PDJ1 :1;
    IO_BYTE PDJ0 :1;
  }bit;
 }PDRJSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PDK7 :1;
    IO_BYTE PDK6 :1;
    IO_BYTE PDK5 :1;
    IO_BYTE PDK4 :1;
    IO_BYTE PDK3 :1;
    IO_BYTE PDK2 :1;
    IO_BYTE PDK1 :1;
    IO_BYTE PDK0 :1;
  }bit;
 }PDRKSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PDL7 :1;
    IO_BYTE PDL6 :1;
    IO_BYTE PDL5 :1;
    IO_BYTE PDL4 :1;
    IO_BYTE PDL3 :1;
    IO_BYTE PDL2 :1;
    IO_BYTE PDL1 :1;
    IO_BYTE PDL0 :1;
  }bit;
 }PDRLSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE PDM3 :1;
    IO_BYTE PDM2 :1;
    IO_BYTE PDM1 :1;
    IO_BYTE PDM0 :1;
  }bit;
 }PDRMSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE PDN5 :1;
    IO_BYTE PDN4 :1;
    IO_BYTE PDN3 :1;
    IO_BYTE PDN2 :1;
    IO_BYTE PDN1 :1;
    IO_BYTE PDN0 :1;
  }bit;
 }PDRNSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PDO7 :1;
    IO_BYTE PDO6 :1;
    IO_BYTE PDO5 :1;
    IO_BYTE PDO4 :1;
    IO_BYTE PDO3 :1;
    IO_BYTE PDO2 :1;
    IO_BYTE PDO1 :1;
    IO_BYTE PDO0 :1;
  }bit;
 }PDROSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE PDP5 :1;
    IO_BYTE PDP4 :1;
    IO_BYTE PDP3 :1;
    IO_BYTE PDP2 :1;
    IO_BYTE PDP1 :1;
    IO_BYTE PDP0 :1;
  }bit;
 }PDRPSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE PDQ5 :1;
    IO_BYTE PDQ4 :1;
    IO_BYTE PDQ3 :1;
    IO_BYTE PDQ2 :1;
    IO_BYTE PDQ1 :1;
    IO_BYTE PDQ0 :1;
  }bit;
 }PDRQSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PR7 :1;
    IO_BYTE PR6 :1;
    IO_BYTE PR5 :1;
    IO_BYTE PR4 :1;
    IO_BYTE PR3 :1;
    IO_BYTE PR2 :1;
    IO_BYTE PR1 :1;
    IO_BYTE PR0 :1;
  }bit;
 }PDRRSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PDS7 :1;
    IO_BYTE PDS6 :1;
    IO_BYTE PDS5 :1;
    IO_BYTE PDS4 :1;
    IO_BYTE PDS3 :1;
    IO_BYTE PDS2 :1;
    IO_BYTE PDS1 :1;
    IO_BYTE PDS0 :1;
  }bit;
 }PDRSSTR;
typedef union{   /* Ext. Int/NMI */
    IO_BYTE	byte;
    struct{
    IO_BYTE ER7 :1;
    IO_BYTE ER6 :1;
    IO_BYTE ER5 :1;
    IO_BYTE ER4 :1;
    IO_BYTE ER3 :1;
    IO_BYTE ER2 :1;
    IO_BYTE ER1 :1;
    IO_BYTE ER0 :1;
  }bit;
 }EIRRSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE EN7 :1;
    IO_BYTE EN6 :1;
    IO_BYTE EN5 :1;
    IO_BYTE EN4 :1;
    IO_BYTE EN3 :1;
    IO_BYTE EN2 :1;
    IO_BYTE EN1 :1;
    IO_BYTE EN0 :1;
  }bit;
 }ENIRSTR;
typedef union{
    IO_WORD	word;
    struct{
    IO_WORD LB7 :1;
    IO_WORD LA7 :1;
    IO_WORD LB6 :1;
    IO_WORD LA6 :1;
    IO_WORD LB5 :1;
    IO_WORD LA5 :1;
    IO_WORD LB4 :1;
    IO_WORD LA4 :1;
    IO_WORD LB3 :1;
    IO_WORD LA3 :1;
    IO_WORD LB2 :1;
    IO_WORD LA2 :1;
    IO_WORD LB1 :1;
    IO_WORD LA1 :1;
    IO_WORD LB0 :1;
    IO_WORD LA0 :1;
  }bit;
    struct{
    IO_WORD LAB7 :2;
    IO_WORD LAB6 :2;
    IO_WORD LAB5 :2;
    IO_WORD LAB4 :2;
    IO_WORD LAB3 :2;
    IO_WORD LAB2 :2;
    IO_WORD LAB1 :2;
    IO_WORD LAB0 :2;
  }bit1;
 }ELVRSTR;
typedef union{   /* DLYI/I-Unit */
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE DLYI :1;
  }bit;
 }DICRSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE LVL4 :1;
    IO_BYTE LVL3 :1;
    IO_BYTE LVL2 :1;
    IO_BYTE LVL1 :1;
    IO_BYTE LVL0 :1;
  }bit;
 }HRCLSTR;
typedef union{
    IO_WORD	word;
    struct{
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD CSL1 :1;
    IO_WORD CSL0 :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD RELD :1;
    IO_WORD INTE :1;
    IO_WORD UF :1;
    IO_WORD CNTE :1;
    IO_WORD TRG :1;
  }bit;
 }TMCSR0STR;
typedef union{
    IO_WORD	word;
    struct{
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD CSL1 :1;
    IO_WORD CSL0 :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD RELD :1;
    IO_WORD INTE :1;
    IO_WORD UF :1;
    IO_WORD CNTE :1;
    IO_WORD TRG :1;
  }bit;
 }TMCSR1STR;
typedef union{
    IO_WORD	word;
    struct{
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD CSL1 :1;
    IO_WORD CSL0 :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD RELD :1;
    IO_WORD INTE :1;
    IO_WORD UF :1;
    IO_WORD CNTE :1;
    IO_WORD TRG :1;
  }bit;
 }TMCSR2STR;
typedef union{   /* UART0 */
    IO_BYTE	byte;
    struct{
    IO_BYTE PE :1;
    IO_BYTE ORE :1;
    IO_BYTE FRE :1;
    IO_BYTE RDRF :1;
    IO_BYTE TDRE :1;
    IO_BYTE  :1;
    IO_BYTE RIE :1;
    IO_BYTE TIE :1;
  }bit;
 }SSR0STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE D7 :1;
    IO_BYTE D6 :1;
    IO_BYTE D5 :1;
    IO_BYTE D4 :1;
    IO_BYTE D3 :1;
    IO_BYTE D2 :1;
    IO_BYTE D1 :1;
    IO_BYTE D0 :1;
  }bit;
 }SIDR0STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE D7 :1;
    IO_BYTE D6 :1;
    IO_BYTE D5 :1;
    IO_BYTE D4 :1;
    IO_BYTE D3 :1;
    IO_BYTE D2 :1;
    IO_BYTE D1 :1;
    IO_BYTE D0 :1;
  }bit;
 }SODR0STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PEN :1;
    IO_BYTE P :1;
    IO_BYTE SBL :1;
    IO_BYTE CL :1;
    IO_BYTE AD :1;
    IO_BYTE REC :1;
    IO_BYTE RXE :1;
    IO_BYTE TXE :1;
  }bit;
 }SCR0STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE MD1 :1;
    IO_BYTE MD0 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE CS0 :1;
    IO_BYTE  :1;
    IO_BYTE SCKE :1;
    IO_BYTE SOE :1;
  }bit;
 }SMR0STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE NSDO :1;
    IO_BYTE NSDI :1;
    IO_BYTE UTDBL :1;
    IO_BYTE UDBL :1;
  }bit;
 }ULS0STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE UCC1 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE UTIE :1;
    IO_BYTE UNDR :1;
    IO_BYTE  :1;
    IO_BYTE UTST :1;
    IO_BYTE UTCR :1;
  }bit;
 }UTIMC0STR;
typedef union{   /* UART1 */
    IO_BYTE	byte;
    struct{
    IO_BYTE PE :1;
    IO_BYTE ORE :1;
    IO_BYTE FRE :1;
    IO_BYTE RDRF :1;
    IO_BYTE TDRE :1;
    IO_BYTE  :1;
    IO_BYTE RIE :1;
    IO_BYTE TIE :1;
  }bit;
 }SSR1STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE D7 :1;
    IO_BYTE D6 :1;
    IO_BYTE D5 :1;
    IO_BYTE D4 :1;
    IO_BYTE D3 :1;
    IO_BYTE D2 :1;
    IO_BYTE D1 :1;
    IO_BYTE D0 :1;
  }bit;
 }SIDR1STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE D7 :1;
    IO_BYTE D6 :1;
    IO_BYTE D5 :1;
    IO_BYTE D4 :1;
    IO_BYTE D3 :1;
    IO_BYTE D2 :1;
    IO_BYTE D1 :1;
    IO_BYTE D0 :1;
  }bit;
 }SODR1STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PEN :1;
    IO_BYTE P :1;
    IO_BYTE SBL :1;
    IO_BYTE CL :1;
    IO_BYTE AD :1;
    IO_BYTE REC :1;
    IO_BYTE RXE :1;
    IO_BYTE TXE :1;
  }bit;
 }SCR1STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE MD1 :1;
    IO_BYTE MD0 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE CS0 :1;
    IO_BYTE  :1;
    IO_BYTE SCKE :1;
    IO_BYTE SOE :1;
  }bit;
 }SMR1STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE NSDO :1;
    IO_BYTE NSDI :1;
    IO_BYTE UTDBL :1;
    IO_BYTE UDBL :1;
  }bit;
 }ULS1STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE UCC1 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE UTIE :1;
    IO_BYTE UNDR :1;
    IO_BYTE  :1;
    IO_BYTE UTST :1;
    IO_BYTE UTCR :1;
  }bit;
 }UTIMC1STR;
typedef union{   /* UART2 */
    IO_BYTE	byte;
    struct{
    IO_BYTE PE :1;
    IO_BYTE ORE :1;
    IO_BYTE FRE :1;
    IO_BYTE RDRF :1;
    IO_BYTE TDRE :1;
    IO_BYTE  :1;
    IO_BYTE RIE :1;
    IO_BYTE TIE :1;
  }bit;
 }SSR2STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE D7 :1;
    IO_BYTE D6 :1;
    IO_BYTE D5 :1;
    IO_BYTE D4 :1;
    IO_BYTE D3 :1;
    IO_BYTE D2 :1;
    IO_BYTE D1 :1;
    IO_BYTE D0 :1;
  }bit;
 }SIDR2STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE D7 :1;
    IO_BYTE D6 :1;
    IO_BYTE D5 :1;
    IO_BYTE D4 :1;
    IO_BYTE D3 :1;
    IO_BYTE D2 :1;
    IO_BYTE D1 :1;
    IO_BYTE D0 :1;
  }bit;
 }SODR2STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PEN :1;
    IO_BYTE P :1;
    IO_BYTE SBL :1;
    IO_BYTE CL :1;
    IO_BYTE AD :1;
    IO_BYTE REC :1;
    IO_BYTE RXE :1;
    IO_BYTE TXE :1;
  }bit;
 }SCR2STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE MD1 :1;
    IO_BYTE MD0 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE CS0 :1;
    IO_BYTE  :1;
    IO_BYTE SCKE :1;
    IO_BYTE SOE :1;
  }bit;
 }SMR2STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE NSDO :1;
    IO_BYTE NSDI :1;
    IO_BYTE UTDBL :1;
    IO_BYTE UDBL :1;
  }bit;
 }ULS2STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE UCC1 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE UTIE :1;
    IO_BYTE UNDR :1;
    IO_BYTE  :1;
    IO_BYTE UTST :1;
    IO_BYTE UTCR :1;
  }bit;
 }UTIMC2STR;
typedef union{   /* SIO0 */
    IO_WORD	word;
    struct{
    IO_WORD SMD2 :1;
    IO_WORD SMD1 :1;
    IO_WORD SMD0 :1;
    IO_WORD SIE :1;
    IO_WORD SIR :1;
    IO_WORD BUSY :1;
    IO_WORD STOP :1;
    IO_WORD STRT :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD MODE :1;
    IO_WORD BDS :1;
    IO_WORD  :1;
    IO_WORD SCOE :1;
  }bit;
  struct{
    IO_WORD SMD :3;
  }bitc;
 }SMCS0STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE DBL :1;
    IO_BYTE SES :1;
  }bit;
 }SES0STR;
typedef union{   /* SIO1 */
    IO_WORD	word;
    struct{
    IO_WORD SMD2 :1;
    IO_WORD SMD1 :1;
    IO_WORD SMD0 :1;
    IO_WORD SIE :1;
    IO_WORD SIR :1;
    IO_WORD BUSY :1;
    IO_WORD STOP :1;
    IO_WORD STRT :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD MODE :1;
    IO_WORD BDS :1;
    IO_WORD  :1;
    IO_WORD SCOE :1;
  }bit;
  struct{
    IO_WORD SMD :3;
  }bitc;
 }SMCS1STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE DBL :1;
    IO_BYTE SES :1;
  }bit;
 }SES1STR;
typedef union{   /* SIO PRESC */
    IO_BYTE	byte;
    struct{
    IO_BYTE MD :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE DIV3 :1;
    IO_BYTE DIV2 :1;
    IO_BYTE DIV1 :1;
    IO_BYTE DIV0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE DIV :4;
  }bitc;
 }CDCR0STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE MD :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE DIV3 :1;
    IO_BYTE DIV2 :1;
    IO_BYTE DIV1 :1;
    IO_BYTE DIV0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE DIV :4;
  }bitc;
 }CDCR1STR;
typedef union{   /* I2C */
    IO_BYTE	byte;
    struct{
    IO_BYTE BER :1;
    IO_BYTE BEIE :1;
    IO_BYTE SCC :1;
    IO_BYTE MSS :1;
    IO_BYTE ACK :1;
    IO_BYTE GCAA :1;
    IO_BYTE INTE :1;
    IO_BYTE INT :1;
  }bit;
 }IBCRSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE BB :1;
    IO_BYTE RSC :1;
    IO_BYTE AL :1;
    IO_BYTE LRB :1;
    IO_BYTE TRX :1;
    IO_BYTE AAS :1;
    IO_BYTE GCA :1;
    IO_BYTE FBT :1;
  }bit;
 }IBSRSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE A6 :1;
    IO_BYTE A5 :1;
    IO_BYTE A4 :1;
    IO_BYTE A3 :1;
    IO_BYTE A2 :1;
    IO_BYTE A1 :1;
    IO_BYTE A0 :1;
  }bit;
 }IADRSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE EN :1;
    IO_BYTE CS4 :1;
    IO_BYTE CS3 :1;
    IO_BYTE CS2 :1;
    IO_BYTE CS1 :1;
    IO_BYTE CS0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE CS :5;
  }bitc;
 }ICCRSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE D7 :1;
    IO_BYTE D6 :1;
    IO_BYTE D5 :1;
    IO_BYTE D4 :1;
    IO_BYTE D3 :1;
    IO_BYTE D2 :1;
    IO_BYTE D1 :1;
    IO_BYTE D0 :1;
  }bit;
 }IDARSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE DBL :1;
  }bit;
 }IDBLSTR;
typedef union{   /* ADC */
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE MOD1 :1;
    IO_BYTE MOD0 :1;
    IO_BYTE STS1 :1;
    IO_BYTE STS0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE MOD :2;
    IO_BYTE STS :2;
  }bitc;
 }ADMDSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE ANS3 :1;
    IO_BYTE ANS2 :1;
    IO_BYTE ANS1 :1;
    IO_BYTE ANS0 :1;
    IO_BYTE ANE3 :1;
    IO_BYTE ANE2 :1;
    IO_BYTE ANE1 :1;
    IO_BYTE ANE0 :1;
  }bit;
  struct{
    IO_BYTE ANS :4;
    IO_BYTE ANE :4;
  }bitc;
 }ADCHSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE BUSY :1;
    IO_BYTE INT :1;
    IO_BYTE INTE :1;
    IO_BYTE PAUS :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE STRT :1;
    IO_BYTE  :1;
  }bit;
 }ADCSSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE DBL :1;
  }bit;
 }ADBLSTR;
typedef union{   /* DAC */
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE MODE :1;
    IO_BYTE DAE1 :1;
    IO_BYTE DAE0 :1;
  }bit;
 }DACRSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE DBL :1;
  }bit;
 }DDBLSTR;
typedef union{   /* Input Capture */
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE DBLT :1;
    IO_BYTE DBLI :1;
    IO_BYTE DBLO :1;
  }bit;
 }IOTDBL0STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE ICP1 :1;
    IO_BYTE ICP0 :1;
    IO_BYTE ICE1 :1;
    IO_BYTE ICE0 :1;
    IO_BYTE EG11 :1;
    IO_BYTE EG10 :1;
    IO_BYTE EG01 :1;
    IO_BYTE EG00 :1;
  }bit;
 }ICS01STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE DBLT :1;
    IO_BYTE DBLI :1;
    IO_BYTE DBLO :1;
  }bit;
 }IOTDBL1STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE ICP3 :1;
    IO_BYTE ICP2 :1;
    IO_BYTE ICE3 :1;
    IO_BYTE ICE2 :1;
    IO_BYTE EG11 :1;
    IO_BYTE EG10 :1;
    IO_BYTE EG01 :1;
    IO_BYTE EG00 :1;
  }bit;
 }ICS23STR;
typedef union{   /* Output Capture */
    IO_WORD	word;
    struct{
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD CMOD :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD OTD1 :1;
    IO_WORD OTD0 :1;
    IO_WORD ICP1 :1;
    IO_WORD ICP0 :1;
    IO_WORD ICE1 :1;
    IO_WORD ICE0 :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD CST1 :1;
    IO_WORD CST0 :1;
  }bit;
 }OCS01STR;
typedef union{
    IO_WORD	word;
    struct{
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD CMOD :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD OTD3 :1;
    IO_WORD OTD2 :1;
    IO_WORD ICP3 :1;
    IO_WORD ICP2 :1;
    IO_WORD ICE3 :1;
    IO_WORD ICE2 :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD CST3 :1;
    IO_WORD CST2 :1;
  }bit;
 }OCS23STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE IVF :1;
    IO_BYTE IVFE :1;
    IO_BYTE STOP :1;
    IO_BYTE MODE :1;
    IO_BYTE CLR :1;
    IO_BYTE CLK1 :1;
    IO_BYTE CLK0 :1;
  }bit;
 }TCCS0STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE IVF :1;
    IO_BYTE IVFE :1;
    IO_BYTE STOP :1;
    IO_BYTE MODE :1;
    IO_BYTE CLR :1;
    IO_BYTE CLK1 :1;
    IO_BYTE CLK0 :1;
  }bit;
 }TCCS1STR;
typedef union{   /* Stepper Motor Control */
    IO_BYTE	byte;
    struct{
    IO_BYTE S1 :1;
    IO_BYTE S0 :1;
    IO_BYTE TS :1;
    IO_BYTE T2 :1;
    IO_BYTE T1 :1;
    IO_BYTE T0 :1;
    IO_BYTE PD :1;
    IO_BYTE RS :1;
  }bit;
  struct{
    IO_BYTE S :2;
    IO_BYTE :1;
    IO_BYTE T :3;
  }bitc;
 }ZPD0STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE P1 :1;
    IO_BYTE P0 :1;
    IO_BYTE CE :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE TST :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE P :2;
  }bitc;
 }PWC0STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE S1 :1;
    IO_BYTE S0 :1;
    IO_BYTE TS :1;
    IO_BYTE T2 :1;
    IO_BYTE T1 :1;
    IO_BYTE T0 :1;
    IO_BYTE PD :1;
    IO_BYTE RS :1;
  }bit;
  struct{
    IO_BYTE S :2;
    IO_BYTE :1;
    IO_BYTE T :3;
  }bitc;
 }ZPD1STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE P1 :1;
    IO_BYTE P0 :1;
    IO_BYTE CE :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE TST :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE P :2;
  }bitc;
 }PWC1STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE S1 :1;
    IO_BYTE S0 :1;
    IO_BYTE TS :1;
    IO_BYTE T2 :1;
    IO_BYTE T1 :1;
    IO_BYTE T0 :1;
    IO_BYTE PD :1;
    IO_BYTE RS :1;
  }bit;
  struct{
    IO_BYTE S :2;
    IO_BYTE :1;
    IO_BYTE T :3;
  }bitc;
 }ZPD2STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE P1 :1;
    IO_BYTE P0 :1;
    IO_BYTE CE :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE TST :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE P :2;
  }bitc;
 }PWC2STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE S1 :1;
    IO_BYTE S0 :1;
    IO_BYTE TS :1;
    IO_BYTE T2 :1;
    IO_BYTE T1 :1;
    IO_BYTE T0 :1;
    IO_BYTE PD :1;
    IO_BYTE RS :1;
  }bit;
  struct{
    IO_BYTE S :2;
    IO_BYTE :1;
    IO_BYTE T :3;
  }bitc;
 }ZPD3STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE P1 :1;
    IO_BYTE P0 :1;
    IO_BYTE CE :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE TST :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE P :2;
  }bitc;
 }PWC3STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE BS :1;
    IO_BYTE P2 :1;
    IO_BYTE P1 :1;
    IO_BYTE P0 :1;
    IO_BYTE M2 :1;
    IO_BYTE M1 :1;
    IO_BYTE M0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE P :3;
    IO_BYTE M :3;
  }bitc;
 }PWS20STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE P2 :1;
    IO_BYTE P1 :1;
    IO_BYTE P0 :1;
    IO_BYTE M2 :1;
    IO_BYTE M1 :1;
    IO_BYTE M0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE P :3;
    IO_BYTE M :3;
  }bitc;
 }PWS10STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE BS :1;
    IO_BYTE P2 :1;
    IO_BYTE P1 :1;
    IO_BYTE P0 :1;
    IO_BYTE M2 :1;
    IO_BYTE M1 :1;
    IO_BYTE M0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE P :3;
    IO_BYTE M :3;
  }bitc;
 }PWS21STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE P2 :1;
    IO_BYTE P1 :1;
    IO_BYTE P0 :1;
    IO_BYTE M2 :1;
    IO_BYTE M1 :1;
    IO_BYTE M0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE P :3;
    IO_BYTE M :3;
  }bitc;
 }PWS11STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE BS :1;
    IO_BYTE P2 :1;
    IO_BYTE P1 :1;
    IO_BYTE P0 :1;
    IO_BYTE M2 :1;
    IO_BYTE M1 :1;
    IO_BYTE M0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE P :3;
    IO_BYTE M :3;
  }bitc;
 }PWS22STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE P2 :1;
    IO_BYTE P1 :1;
    IO_BYTE P0 :1;
    IO_BYTE M2 :1;
    IO_BYTE M1 :1;
    IO_BYTE M0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE P :3;
    IO_BYTE M :3;
  }bitc;
 }PWS12STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE BS :1;
    IO_BYTE P2 :1;
    IO_BYTE P1 :1;
    IO_BYTE P0 :1;
    IO_BYTE M2 :1;
    IO_BYTE M1 :1;
    IO_BYTE M0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE P :3;
    IO_BYTE M :3;
  }bitc;
 }PWS23STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE P2 :1;
    IO_BYTE P1 :1;
    IO_BYTE P0 :1;
    IO_BYTE M2 :1;
    IO_BYTE M1 :1;
    IO_BYTE M0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE P :3;
    IO_BYTE M :3;
  }bitc;
 }PWS13STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE DBL :1;
  }bit;
 }SMDBL0STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE DBL :1;
  }bit;
 }SMDBL1STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE DBL :1;
  }bit;
 }SMDBL2STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE DBL :1;
  }bit;
 }SMDBL3STR;
typedef union{   /* Sound Generator */
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE DBL :1;
  }bit;
 }SGDBLSTR;
typedef union{
    IO_WORD	word;
    struct{
    IO_WORD TST :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD BUSY :1;
    IO_WORD DEC :1;
    IO_WORD S1 :1;
    IO_WORD S0 :1;
    IO_WORD TONE :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD INTE :1;
    IO_WORD INT :1;
    IO_WORD ST :1;
  }bit;
 }SGCRSTR;
typedef union{   /* Real Time Clock (RTC) */
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE DBL :1;
  }bit;
 }WTDBLSTR;
typedef union{
    IO_WORD	word;
    struct{
    IO_WORD INTE3 :1;
    IO_WORD INT3 :1;
    IO_WORD INTE2 :1;
    IO_WORD INT2 :1;
    IO_WORD INTE1 :1;
    IO_WORD INT1 :1;
    IO_WORD INTE0 :1;
    IO_WORD INT0 :1;
    IO_WORD TST2 :1;
    IO_WORD TST1 :1;
    IO_WORD TST0 :1;
    IO_WORD  :1;
    IO_WORD RUN :1;
    IO_WORD UPDT :1;
    IO_WORD  :1;
    IO_WORD ST :1;
  }bit;
 }WTCRSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE H4 :1;
    IO_BYTE H3 :1;
    IO_BYTE H2 :1;
    IO_BYTE H1 :1;
    IO_BYTE H0 :1;
  }bit;
 }WTHRSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE M5 :1;
    IO_BYTE M4 :1;
    IO_BYTE M3 :1;
    IO_BYTE M2 :1;
    IO_BYTE M1 :1;
    IO_BYTE M0 :1;
  }bit;
 }WTMRSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE S5 :1;
    IO_BYTE S4 :1;
    IO_BYTE S3 :1;
    IO_BYTE S2 :1;
    IO_BYTE S1 :1;
    IO_BYTE S0 :1;
  }bit;
 }WTSRSTR;
typedef union{
    IO_WORD	word;
    struct{
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD CSL1 :1;
    IO_WORD CSL0 :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD RELD :1;
    IO_WORD INTE :1;
    IO_WORD UF :1;
    IO_WORD CNTE :1;
    IO_WORD TRG :1;
  }bit;
 }TMCSR3STR;
typedef union{
    IO_WORD	word;
    struct{
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD CSL1 :1;
    IO_WORD CSL0 :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD RELD :1;
    IO_WORD INTE :1;
    IO_WORD UF :1;
    IO_WORD CNTE :1;
    IO_WORD TRG :1;
  }bit;
 }TMCSR4STR;
typedef union{
    IO_WORD	word;
    struct{
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD CSL1 :1;
    IO_WORD CSL0 :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD RELD :1;
    IO_WORD INTE :1;
    IO_WORD UF :1;
    IO_WORD CNTE :1;
    IO_WORD TRG :1;
  }bit;
 }TMCSR5STR;
typedef union{   /* PWM CNTRL */
    IO_WORD	word;
    struct{
    IO_WORD TSEL33 :1;
    IO_WORD TSEL32 :1;
    IO_WORD TSEL31 :1;
    IO_WORD TSEL30 :1;
    IO_WORD TSEL23 :1;
    IO_WORD TSEL22 :1;
    IO_WORD TSEL21 :1;
    IO_WORD TSEL20 :1;
    IO_WORD TSEL13 :1;
    IO_WORD TSEL12 :1;
    IO_WORD TSEL11 :1;
    IO_WORD TSEL10 :1;
    IO_WORD TSEL03 :1;
    IO_WORD TSEL02 :1;
    IO_WORD TSEL01 :1;
    IO_WORD TSEL00 :1;
  }bit;
 }GCN10STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE DBC0 :1;
    IO_BYTE DBL3 :1;
    IO_BYTE DBL2 :1;
    IO_BYTE DBL1 :1;
    IO_BYTE DBL0 :1;
  }bit;
 }PDBL0STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE EN3 :1;
    IO_BYTE EN2 :1;
    IO_BYTE EN1 :1;
    IO_BYTE EN0 :1;
  }bit;
 }GCN20STR;
typedef union{
    IO_WORD	word;
    struct{
    IO_WORD TSEL73 :1;
    IO_WORD TSEL72 :1;
    IO_WORD TSEL71 :1;
    IO_WORD TSEL70 :1;
    IO_WORD TSEL63 :1;
    IO_WORD TSEL62 :1;
    IO_WORD TSEL61 :1;
    IO_WORD TSEL60 :1;
    IO_WORD TSEL53 :1;
    IO_WORD TSEL52 :1;
    IO_WORD TSEL51 :1;
    IO_WORD TSEL50 :1;
    IO_WORD TSEL43 :1;
    IO_WORD TSEL42 :1;
    IO_WORD TSEL41 :1;
    IO_WORD TSEL40 :1;
  }bit;
 }GCN11STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE DBC1 :1;
    IO_BYTE DBL7 :1;
    IO_BYTE DBL6 :1;
    IO_BYTE DBL5 :1;
    IO_BYTE DBL4 :1;
  }bit;
 }PDBL1STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE EN3 :1;
    IO_BYTE EN2 :1;
    IO_BYTE EN1 :1;
    IO_BYTE EN0 :1;
  }bit;
 }GCN21STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE CNTE :1;
    IO_BYTE STGR :1;
    IO_BYTE MDSE :1;
    IO_BYTE RTRG :1;
    IO_BYTE CKS1 :1;
    IO_BYTE CKS0 :1;
    IO_BYTE PGMS :1;
    IO_BYTE  :1;
  }bit;
 }PCNH0STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE EGS1 :1;
    IO_BYTE EGS0 :1;
    IO_BYTE IREN :1;
    IO_BYTE IRQF :1;
    IO_BYTE IRS1 :1;
    IO_BYTE IRS0 :1;
    IO_BYTE  :1;
    IO_BYTE OSEL :1;
  }bit;
 }PCNL0STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE CNTE :1;
    IO_BYTE STGR :1;
    IO_BYTE MDSE :1;
    IO_BYTE RTRG :1;
    IO_BYTE CKS1 :1;
    IO_BYTE CKS0 :1;
    IO_BYTE PGMS :1;
    IO_BYTE  :1;
  }bit;
 }PCNH1STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE EGS1 :1;
    IO_BYTE EGS0 :1;
    IO_BYTE IREN :1;
    IO_BYTE IRQF :1;
    IO_BYTE IRS1 :1;
    IO_BYTE IRS0 :1;
    IO_BYTE  :1;
    IO_BYTE OSEL :1;
  }bit;
 }PCNL1STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE CNTE :1;
    IO_BYTE STGR :1;
    IO_BYTE MDSE :1;
    IO_BYTE RTRG :1;
    IO_BYTE CKS1 :1;
    IO_BYTE CKS0 :1;
    IO_BYTE PGMS :1;
    IO_BYTE  :1;
  }bit;
 }PCNH2STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE EGS1 :1;
    IO_BYTE EGS0 :1;
    IO_BYTE IREN :1;
    IO_BYTE IRQF :1;
    IO_BYTE IRS1 :1;
    IO_BYTE IRS0 :1;
    IO_BYTE  :1;
    IO_BYTE OSEL :1;
  }bit;
 }PCNL2STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE CNTE :1;
    IO_BYTE STGR :1;
    IO_BYTE MDSE :1;
    IO_BYTE RTRG :1;
    IO_BYTE CKS1 :1;
    IO_BYTE CKS0 :1;
    IO_BYTE PGMS :1;
    IO_BYTE  :1;
  }bit;
 }PCNH3STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE EGS1 :1;
    IO_BYTE EGS0 :1;
    IO_BYTE IREN :1;
    IO_BYTE IRQF :1;
    IO_BYTE IRS1 :1;
    IO_BYTE IRS0 :1;
    IO_BYTE  :1;
    IO_BYTE OSEL :1;
  }bit;
 }PCNL3STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE CNTE :1;
    IO_BYTE STGR :1;
    IO_BYTE MDSE :1;
    IO_BYTE RTRG :1;
    IO_BYTE CKS1 :1;
    IO_BYTE CKS0 :1;
    IO_BYTE PGMS :1;
    IO_BYTE  :1;
  }bit;
 }PCNH4STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE EGS1 :1;
    IO_BYTE EGS0 :1;
    IO_BYTE IREN :1;
    IO_BYTE IRQF :1;
    IO_BYTE IRS1 :1;
    IO_BYTE IRS0 :1;
    IO_BYTE  :1;
    IO_BYTE OSEL :1;
  }bit;
 }PCNL4STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE CNTE :1;
    IO_BYTE STGR :1;
    IO_BYTE MDSE :1;
    IO_BYTE RTRG :1;
    IO_BYTE CKS1 :1;
    IO_BYTE CKS0 :1;
    IO_BYTE PGMS :1;
    IO_BYTE  :1;
  }bit;
 }PCNH5STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE EGS1 :1;
    IO_BYTE EGS0 :1;
    IO_BYTE IREN :1;
    IO_BYTE IRQF :1;
    IO_BYTE IRS1 :1;
    IO_BYTE IRS0 :1;
    IO_BYTE  :1;
    IO_BYTE OSEL :1;
  }bit;
 }PCNL5STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE CNTE :1;
    IO_BYTE STGR :1;
    IO_BYTE MDSE :1;
    IO_BYTE RTRG :1;
    IO_BYTE CKS1 :1;
    IO_BYTE CKS0 :1;
    IO_BYTE PGMS :1;
    IO_BYTE  :1;
  }bit;
 }PCNH6STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE EGS1 :1;
    IO_BYTE EGS0 :1;
    IO_BYTE IREN :1;
    IO_BYTE IRQF :1;
    IO_BYTE IRS1 :1;
    IO_BYTE IRS0 :1;
    IO_BYTE  :1;
    IO_BYTE OSEL :1;
  }bit;
 }PCNL6STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE CNTE :1;
    IO_BYTE STGR :1;
    IO_BYTE MDSE :1;
    IO_BYTE RTRG :1;
    IO_BYTE CKS1 :1;
    IO_BYTE CKS0 :1;
    IO_BYTE PGMS :1;
    IO_BYTE  :1;
  }bit;
 }PCNH7STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE EGS1 :1;
    IO_BYTE EGS0 :1;
    IO_BYTE IREN :1;
    IO_BYTE IRQF :1;
    IO_BYTE IRS1 :1;
    IO_BYTE IRS0 :1;
    IO_BYTE  :1;
    IO_BYTE OSEL :1;
  }bit;
 }PCNL7STR;
typedef union{   /* Power Down Reset */
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE CDSBLE :1;
    IO_BYTE PD :1;
    IO_BYTE EN :1;
  }bit;
 }PDRCRSTR;
typedef union{   /* Alarm Comparator */
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE CDBLE :1;
  }bit;
 }ACCDBLSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE OUT2 :1;
    IO_BYTE OUT1 :1;
    IO_BYTE IRQ :1;
    IO_BYTE IEN :1;
    IO_BYTE PD :1;
  }bit;
 }ACSRSTR;
typedef union{   /* I2C */
    IO_BYTE	byte;
    struct{
    IO_BYTE BER :1;
    IO_BYTE BEIE :1;
    IO_BYTE SCC :1;
    IO_BYTE MSS :1;
    IO_BYTE ACK :1;
    IO_BYTE GCAA :1;
    IO_BYTE INTE :1;
    IO_BYTE INT :1;
  }bit;
 }IBCR2STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE BB :1;
    IO_BYTE RSC :1;
    IO_BYTE AL :1;
    IO_BYTE LRB :1;
    IO_BYTE TRX :1;
    IO_BYTE AAS :1;
    IO_BYTE GCA :1;
    IO_BYTE ADT :1;
  }bit;
 }IBSR2STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE TA9 :1;
    IO_BYTE TA8 :1;
  }bit;
 }ITBAH2STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE TA7 :1;
    IO_BYTE TA6 :1;
    IO_BYTE TA5 :1;
    IO_BYTE TA4 :1;
    IO_BYTE TA3 :1;
    IO_BYTE TA2 :1;
    IO_BYTE TA1 :1;
    IO_BYTE TA0 :1;
  }bit;
 }ITBAL2STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE ENTB :1;
    IO_BYTE RAL :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE TM9 :1;
    IO_BYTE TM8 :1;
  }bit;
 }ITMKH2STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE TM7 :1;
    IO_BYTE TM6 :1;
    IO_BYTE TM5 :1;
    IO_BYTE TM4 :1;
    IO_BYTE TM3 :1;
    IO_BYTE TM2 :1;
    IO_BYTE TM1 :1;
    IO_BYTE TM0 :1;
  }bit;
 }ITMKL2STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE ENSB :1;
    IO_BYTE SM6 :1;
    IO_BYTE SM5 :1;
    IO_BYTE SM4 :1;
    IO_BYTE SM3 :1;
    IO_BYTE SM2 :1;
    IO_BYTE SM1 :1;
    IO_BYTE SM0 :1;
  }bit;
 }ISMK2STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE SA6 :1;
    IO_BYTE SA5 :1;
    IO_BYTE SA4 :1;
    IO_BYTE SA3 :1;
    IO_BYTE SA2 :1;
    IO_BYTE SA1 :1;
    IO_BYTE SA0 :1;
  }bit;
 }ISBA2STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE NSF :1;
    IO_BYTE EN :1;
    IO_BYTE CS4 :1;
    IO_BYTE CS3 :1;
    IO_BYTE CS2 :1;
    IO_BYTE CS1 :1;
    IO_BYTE CS0 :1;
  }bit;
 }ICCR2STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE DBL :1;
  }bit;
 }IDBL2STR;
typedef union{   /* MODE REGISTER */
    IO_BYTE	byte;
    struct{
    IO_BYTE FMD7 :1;
    IO_BYTE FMD6 :1;
    IO_BYTE FMD5 :1;
    IO_BYTE FMD4 :1;
    IO_BYTE FMD3 :1;
    IO_BYTE FMD2 :1;
    IO_BYTE FMD1 :1;
    IO_BYTE FMD0 :1;
  }bit;
 }F362MDSTR;
typedef union{   /* Port Direction Register */
    IO_BYTE	byte;
    struct{
    IO_BYTE DD07 :1;
    IO_BYTE DD06 :1;
    IO_BYTE DD05 :1;
    IO_BYTE DD04 :1;
    IO_BYTE DD03 :1;
    IO_BYTE DD02 :1;
    IO_BYTE DD01 :1;
    IO_BYTE DD00 :1;
  }bit;
 }DDR0STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE DD17 :1;
    IO_BYTE DD16 :1;
    IO_BYTE DD15 :1;
    IO_BYTE DD14 :1;
    IO_BYTE DD13 :1;
    IO_BYTE DD12 :1;
    IO_BYTE DD11 :1;
    IO_BYTE DD10 :1;
  }bit;
 }DDR1STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE DD27 :1;
    IO_BYTE DD26 :1;
    IO_BYTE DD25 :1;
    IO_BYTE DD24 :1;
    IO_BYTE DD23 :1;
    IO_BYTE DD22 :1;
    IO_BYTE DD21 :1;
    IO_BYTE DD20 :1;
  }bit;
 }DDR2STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE DD37 :1;
    IO_BYTE DD36 :1;
    IO_BYTE DD35 :1;
    IO_BYTE DD34 :1;
    IO_BYTE DD33 :1;
    IO_BYTE DD32 :1;
    IO_BYTE DD31 :1;
    IO_BYTE DD30 :1;
  }bit;
 }DDR3STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE DD47 :1;
    IO_BYTE DD46 :1;
    IO_BYTE DD45 :1;
    IO_BYTE DD44 :1;
    IO_BYTE DD43 :1;
    IO_BYTE DD42 :1;
    IO_BYTE DD41 :1;
    IO_BYTE DD40 :1;
  }bit;
 }DDR4STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE DD57 :1;
    IO_BYTE DD56 :1;
    IO_BYTE DD55 :1;
    IO_BYTE DD54 :1;
    IO_BYTE DD53 :1;
    IO_BYTE DD52 :1;
    IO_BYTE DD51 :1;
    IO_BYTE DD50 :1;
  }bit;
 }DDR5STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE      :1;
    IO_BYTE      :1;
    IO_BYTE      :1;
    IO_BYTE DD64 :1;
    IO_BYTE DD63 :1;
    IO_BYTE DD62 :1;
    IO_BYTE DD61 :1;
    IO_BYTE DD60 :1;
  }bit;
 }DDR6STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE      :1;
    IO_BYTE DD76 :1;
    IO_BYTE DD75 :1;
    IO_BYTE DD74 :1;
    IO_BYTE      :1;
    IO_BYTE      :1;
    IO_BYTE      :1;
    IO_BYTE      :1;
  }bit;
 }DDR7STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE      :1;
    IO_BYTE      :1;
    IO_BYTE      :1;
    IO_BYTE      :1;
    IO_BYTE      :1;
    IO_BYTE DD82 :1;
    IO_BYTE DD81 :1;
    IO_BYTE      :1;
  }bit;
 }DDR8STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE DD97 :1;
    IO_BYTE DD96 :1;
    IO_BYTE      :1;
    IO_BYTE      :1;
    IO_BYTE DD93 :1;
    IO_BYTE DD92 :1;
    IO_BYTE DD91 :1;
    IO_BYTE DD90 :1;
  }bit;
 }DDR9STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE DDB2 :1;
    IO_BYTE DDB1 :1;
    IO_BYTE DDB0 :1;
  }bit;
 }DDRBSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE DDG7 :1;
    IO_BYTE DDG6 :1;
    IO_BYTE DDG5 :1;
    IO_BYTE DDG4 :1;
    IO_BYTE DDG3 :1;
    IO_BYTE DDG2 :1;
    IO_BYTE DDG1 :1;
    IO_BYTE DDG0 :1;
  }bit;
 }DDRGSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE DDH7 :1;
    IO_BYTE DDH6 :1;
    IO_BYTE DDH5 :1;
    IO_BYTE DDH4 :1;
    IO_BYTE DDH3 :1;
    IO_BYTE DDH2 :1;
    IO_BYTE DDH1 :1;
    IO_BYTE DDH0 :1;
  }bit;
 }DDRHSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE DDI3 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
 }DDRISTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE DDJ7 :1;
    IO_BYTE DDJ6 :1;
    IO_BYTE DDJ5 :1;
    IO_BYTE DDJ4 :1;
    IO_BYTE DDJ3 :1;
    IO_BYTE DDJ2 :1;
    IO_BYTE DDJ1 :1;
    IO_BYTE DDJ0 :1;
  }bit;
 }DDRJSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE DDK7 :1;
    IO_BYTE DDK6 :1;
    IO_BYTE DDK5 :1;
    IO_BYTE DDK4 :1;
    IO_BYTE DDK3 :1;
    IO_BYTE DDK2 :1;
    IO_BYTE DDK1 :1;
    IO_BYTE DDK0 :1;
  }bit;
 }DDRKSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE DDL7 :1;
    IO_BYTE DDL6 :1;
    IO_BYTE DDL5 :1;
    IO_BYTE DDL4 :1;
    IO_BYTE DDL3 :1;
    IO_BYTE DDL2 :1;
    IO_BYTE DDL1 :1;
    IO_BYTE DDL0 :1;
  }bit;
 }DDRLSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE DDM3 :1;
    IO_BYTE DDM2 :1;
    IO_BYTE DDM1 :1;
    IO_BYTE DDM0 :1;
  }bit;
 }DDRMSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE DDN5 :1;
    IO_BYTE DDN4 :1;
    IO_BYTE DDN3 :1;
    IO_BYTE DDN2 :1;
    IO_BYTE DDN1 :1;
    IO_BYTE DDN0 :1;
  }bit;
 }DDRNSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE DDO7 :1;
    IO_BYTE DDO6 :1;
    IO_BYTE DDO5 :1;
    IO_BYTE DDO4 :1;
    IO_BYTE DDO3 :1;
    IO_BYTE DDO2 :1;
    IO_BYTE DDO1 :1;
    IO_BYTE DDO0 :1;
  }bit;
 }DDROSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE DDP5 :1;
    IO_BYTE DDP4 :1;
    IO_BYTE DDP3 :1;
    IO_BYTE DDP2 :1;
    IO_BYTE DDP1 :1;
    IO_BYTE DDP0 :1;
  }bit;
 }DDRPSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE DDQ5 :1;
    IO_BYTE DDQ4 :1;
    IO_BYTE DDQ3 :1;
    IO_BYTE DDQ2 :1;
    IO_BYTE DDQ1 :1;
    IO_BYTE DDQ0 :1;
  }bit;
 }DDRQSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE DR7 :1;
    IO_BYTE DR6 :1;
    IO_BYTE DR5 :1;
    IO_BYTE DR4 :1;
    IO_BYTE DR3 :1;
    IO_BYTE DR2 :1;
    IO_BYTE DR1 :1;
    IO_BYTE DR0 :1;
  }bit;
 }DDRRSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE DDS7 :1;
    IO_BYTE DDS6 :1;
    IO_BYTE DDS5 :1;
    IO_BYTE DDS4 :1;
    IO_BYTE DDS3 :1;
    IO_BYTE DDS2 :1;
    IO_BYTE DDS1 :1;
    IO_BYTE DDS0 :1;
  }bit;
 }DDRSSTR;
typedef union{   /* Port Function Register */
    IO_BYTE	byte;
    struct{
    IO_BYTE PF07 :1;
    IO_BYTE PF06 :1;
    IO_BYTE PF05 :1;
    IO_BYTE PF04 :1;
    IO_BYTE PF03 :1;
    IO_BYTE PF02 :1;
    IO_BYTE PF01 :1;
    IO_BYTE PF00 :1;
  }bit;
 }PFR0STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PF17 :1;
    IO_BYTE PF16 :1;
    IO_BYTE PF15 :1;
    IO_BYTE PF14 :1;
    IO_BYTE PF13 :1;
    IO_BYTE PF12 :1;
    IO_BYTE PF11 :1;
    IO_BYTE PF10 :1;
  }bit;
 }PFR1STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PF27 :1;
    IO_BYTE PF26 :1;
    IO_BYTE PF25 :1;
    IO_BYTE PF24 :1;
    IO_BYTE PF23 :1;
    IO_BYTE PF22 :1;
    IO_BYTE PF21 :1;
    IO_BYTE PF20 :1;
  }bit;
 }PFR2STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PF37 :1;
    IO_BYTE PF36 :1;
    IO_BYTE PF35 :1;
    IO_BYTE PF34 :1;
    IO_BYTE PF33 :1;
    IO_BYTE PF32 :1;
    IO_BYTE PF31 :1;
    IO_BYTE PF30 :1;
  }bit;
 }PFR3STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PF47 :1;
    IO_BYTE PF46 :1;
    IO_BYTE PF45 :1;
    IO_BYTE PF44 :1;
    IO_BYTE PF43 :1;
    IO_BYTE PF42 :1;
    IO_BYTE PF41 :1;
    IO_BYTE PF40 :1;
  }bit;
 }PFR4STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PF57 :1;
    IO_BYTE PF56 :1;
    IO_BYTE PF55 :1;
    IO_BYTE PF54 :1;
    IO_BYTE PF53 :1;
    IO_BYTE PF52 :1;
    IO_BYTE PF51 :1;
    IO_BYTE PF50 :1;
  }bit;
 }PFR5STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE      :1;
    IO_BYTE      :1;
    IO_BYTE      :1;
    IO_BYTE PF64 :1;
    IO_BYTE PF63 :1;
    IO_BYTE PF62 :1;
    IO_BYTE PF61 :1;
    IO_BYTE PF60 :1;
  }bit;
 }PFR6STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE PF76 :1;
    IO_BYTE PF75 :1;
    IO_BYTE PF74 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
 }PFR7STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE PF82 :1;
    IO_BYTE PF81 :1;
    IO_BYTE  :1;
  }bit;
 }PFR8STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PF97 :1;
    IO_BYTE PF96 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE PF93 :1;
    IO_BYTE PF92 :1;
    IO_BYTE PF91 :1;
    IO_BYTE PF90 :1;
  }bit;
 }PFR9STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE PFB2 :1;
    IO_BYTE PFB1 :1;
    IO_BYTE PFB0 :1;
  }bit;
 }PFRBSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PFG7 :1;
    IO_BYTE PFG6 :1;
    IO_BYTE PFG5 :1;
    IO_BYTE PFG4 :1;
    IO_BYTE PFG3 :1;
    IO_BYTE PFG2 :1;
    IO_BYTE PFG1 :1;
    IO_BYTE PFG0 :1;
  }bit;
 }PFRGSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PFH7 :1;
    IO_BYTE PFH6 :1;
    IO_BYTE PFH5 :1;
    IO_BYTE PFH4 :1;
    IO_BYTE PFH3 :1;
    IO_BYTE PFH2 :1;
    IO_BYTE PFH1 :1;
    IO_BYTE PFH0 :1;
  }bit;
 }PFRHSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE PFI3 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
 }PFRISTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PFJ7 :1;
    IO_BYTE PFJ6 :1;
    IO_BYTE PFJ5 :1;
    IO_BYTE PFJ4 :1;
    IO_BYTE PFJ3 :1;
    IO_BYTE PFJ2 :1;
    IO_BYTE PFJ1 :1;
    IO_BYTE PFJ0 :1;
  }bit;
 }PFRJSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PFK7 :1;
    IO_BYTE PFK6 :1;
    IO_BYTE PFK5 :1;
    IO_BYTE PFK4 :1;
    IO_BYTE PFK3 :1;
    IO_BYTE PFK2 :1;
    IO_BYTE PFK1 :1;
    IO_BYTE PFK0 :1;
  }bit;
 }PFRKSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PFL7 :1;
    IO_BYTE PFL6 :1;
    IO_BYTE PFL5 :1;
    IO_BYTE PFL4 :1;
    IO_BYTE PFL3 :1;
    IO_BYTE PFL2 :1;
    IO_BYTE PFL1 :1;
    IO_BYTE PFL0 :1;
  }bit;
 }PFRLSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE PFM3 :1;
    IO_BYTE PFM2 :1;
    IO_BYTE PFM1 :1;
    IO_BYTE PFM0 :1;
  }bit;
 }PFRMSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE PFN5 :1;
    IO_BYTE PFN4 :1;
    IO_BYTE PFN3 :1;
    IO_BYTE PFN2 :1;
    IO_BYTE PFN1 :1;
    IO_BYTE PFN0 :1;
  }bit;
 }PFRNSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PFO7 :1;
    IO_BYTE PFO6 :1;
    IO_BYTE PFO5 :1;
    IO_BYTE PFO4 :1;
    IO_BYTE PFO3 :1;
    IO_BYTE PFO2 :1;
    IO_BYTE PFO1 :1;
    IO_BYTE PFO0 :1;
  }bit;
 }PFROSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE PFP5 :1;
    IO_BYTE PFP4 :1;
    IO_BYTE PFP3 :1;
    IO_BYTE PFP2 :1;
    IO_BYTE PFP1 :1;
    IO_BYTE PFP0 :1;
  }bit;
 }PFRPSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE PFQ5 :1;
    IO_BYTE PFQ4 :1;
    IO_BYTE PFQ3 :1;
    IO_BYTE PFQ2 :1;
    IO_BYTE PFQ1 :1;
    IO_BYTE PFQ0 :1;
  }bit;
 }PFRQSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PR7 :1;
    IO_BYTE PR6 :1;
    IO_BYTE PR5 :1;
    IO_BYTE PR4 :1;
    IO_BYTE PR3 :1;
    IO_BYTE PR2 :1;
    IO_BYTE PR1 :1;
    IO_BYTE PR0 :1;
  }bit;
 }PFRRSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PFS7 :1;
    IO_BYTE PFS6 :1;
    IO_BYTE PFS5 :1;
    IO_BYTE PFS4 :1;
    IO_BYTE PFS3 :1;
    IO_BYTE PFS2 :1;
    IO_BYTE PFS1 :1;
    IO_BYTE PFS0 :1;
  }bit;
 }PFRSSTR;
typedef union{   /* Clock Control Unit */
    IO_BYTE	byte;
    struct{
    IO_BYTE INIT :1;
    IO_BYTE HSTB :1;
    IO_BYTE WDOG :1;
    IO_BYTE ERST :1;
    IO_BYTE SRST :1;
    IO_BYTE  :1;
    IO_BYTE WT1 :1;
    IO_BYTE WT0 :1;
  }bit;
 }RSRRSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE STOP :1;
    IO_BYTE SLEEP :1;
    IO_BYTE HIZ :1;
    IO_BYTE SRST :1;
    IO_BYTE OS1 :1;
    IO_BYTE OS0 :1;
    IO_BYTE  :1;
    IO_BYTE OSCD1 :1;
  }bit;
 }STCRSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE TBIF :1;
    IO_BYTE TBIE :1;
    IO_BYTE TBC2 :1;
    IO_BYTE TBC1 :1;
    IO_BYTE TBC0 :1;
    IO_BYTE  :1;
    IO_BYTE SYNCR :1;
    IO_BYTE SYNCS :1;
  }bit;
 }TBCRSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE PLL2S0 :1;
    IO_BYTE PLL1S2 :1;
    IO_BYTE PLL1S1 :1;
    IO_BYTE PLL1S0 :1;
    IO_BYTE PLL2EN :1;
    IO_BYTE PLL1EN :1;
    IO_BYTE CLKS1 :1;
    IO_BYTE CLKS0 :1;
  }bit;
 }CLKRSTR;
typedef union{   /* FLASH MEMORY */
    IO_BYTE	byte;
    struct{
    IO_BYTE FACCE :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE RDYEG :1;
    IO_BYTE RDY :1;
    IO_BYTE  :1;
    IO_BYTE WRE :1;
    IO_BYTE LPM :1;
  }bit;
 }FMCSSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE FAC1 :1;
    IO_BYTE FAC0 :1;
    IO_BYTE EQINH :1;
    IO_BYTE WTC2 :1;
    IO_BYTE WTC1 :1;
    IO_BYTE WTC0 :1;
  }bit;
 }FMWTSTR;
typedef union{
    IO_WORD	word;
    struct{
    IO_WORD DTR_W :1;
    IO_WORD DTR_B :1;
    IO_WORD IDR_W :1;
    IO_WORD IDR_B :1;
    IO_WORD AMR_W :1;
    IO_WORD AMR_B :1;
    IO_WORD AMS_W :1;
    IO_WORD AMS_B :1;
    IO_WORD E_INT :1;
    IO_WORD S_INT :1;
    IO_WORD C_INT :1;
    IO_WORD L_INV :1;
    IO_WORD C_CLK :1;
    IO_WORD L_CLK :1;
    IO_WORD SYNCH :1;
    IO_WORD CDSBLE :1;
  }bit;
 }CREG0STR;
typedef union{
    IO_WORD	word;
    struct{
    IO_WORD DTR_W :1;
    IO_WORD DTR_B :1;
    IO_WORD IDR_W :1;
    IO_WORD IDR_B :1;
    IO_WORD AMR_W :1;
    IO_WORD AMR_B :1;
    IO_WORD AMS_W :1;
    IO_WORD AMS_B :1;
    IO_WORD E_INT :1;
    IO_WORD S_INT :1;
    IO_WORD C_INT :1;
    IO_WORD L_INV :1;
    IO_WORD C_CLK :1;
    IO_WORD L_CLK :1;
    IO_WORD SYNCH :1;
    IO_WORD CDSBLE :1;
  }bit;
 }CREG1STR;
typedef union{
    IO_WORD	word;
    struct{
    IO_WORD DTR_W :1;
    IO_WORD DTR_B :1;
    IO_WORD IDR_W :1;
    IO_WORD IDR_B :1;
    IO_WORD AMR_W :1;
    IO_WORD AMR_B :1;
    IO_WORD AMS_W :1;
    IO_WORD AMS_B :1;
    IO_WORD E_INT :1;
    IO_WORD S_INT :1;
    IO_WORD C_INT :1;
    IO_WORD L_INV :1;
    IO_WORD C_CLK :1;
    IO_WORD L_CLK :1;
    IO_WORD SYNCH :1;
    IO_WORD CDSBLE :1;
  }bit;
 }CREG2STR;

/* C-DECLARATIONS */

__IO_EXTERN PDR0STR pdr0;   /* Port Data Registers */
#define PDR0 pdr0.byte
#define PDR0_PD07 pdr0.bit.PD07
#define PDR0_PD06 pdr0.bit.PD06
#define PDR0_PD05 pdr0.bit.PD05
#define PDR0_PD04 pdr0.bit.PD04
#define PDR0_PD03 pdr0.bit.PD03
#define PDR0_PD02 pdr0.bit.PD02
#define PDR0_PD01 pdr0.bit.PD01
#define PDR0_PD00 pdr0.bit.PD00
__IO_EXTERN PDR1STR pdr1;
#define PDR1 pdr1.byte
#define PDR1_PD17 pdr1.bit.PD17
#define PDR1_PD16 pdr1.bit.PD16
#define PDR1_PD15 pdr1.bit.PD15
#define PDR1_PD14 pdr1.bit.PD14
#define PDR1_PD13 pdr1.bit.PD13
#define PDR1_PD12 pdr1.bit.PD12
#define PDR1_PD11 pdr1.bit.PD11
#define PDR1_PD10 pdr1.bit.PD10
__IO_EXTERN PDR2STR pdr2;
#define PDR2 pdr2.byte
#define PDR2_PD27 pdr2.bit.PD27
#define PDR2_PD26 pdr2.bit.PD26
#define PDR2_PD25 pdr2.bit.PD25
#define PDR2_PD24 pdr2.bit.PD24
#define PDR2_PD23 pdr2.bit.PD23
#define PDR2_PD22 pdr2.bit.PD22
#define PDR2_PD21 pdr2.bit.PD21
#define PDR2_PD20 pdr2.bit.PD20
__IO_EXTERN PDR3STR pdr3;
#define PDR3 pdr3.byte
#define PDR3_PD37 pdr3.bit.PD37
#define PDR3_PD36 pdr3.bit.PD36
#define PDR3_PD35 pdr3.bit.PD35
#define PDR3_PD34 pdr3.bit.PD34
#define PDR3_PD33 pdr3.bit.PD33
#define PDR3_PD32 pdr3.bit.PD32
#define PDR3_PD31 pdr3.bit.PD31
#define PDR3_PD30 pdr3.bit.PD30
__IO_EXTERN PDR4STR pdr4;
#define PDR4 pdr4.byte
#define PDR4_PD47 pdr4.bit.PD47
#define PDR4_PD46 pdr4.bit.PD46
#define PDR4_PD45 pdr4.bit.PD45
#define PDR4_PD44 pdr4.bit.PD44
#define PDR4_PD43 pdr4.bit.PD43
#define PDR4_PD42 pdr4.bit.PD42
#define PDR4_PD41 pdr4.bit.PD41
#define PDR4_PD40 pdr4.bit.PD40
__IO_EXTERN PDR5STR pdr5;
#define PDR5 pdr5.byte
#define PDR5_PD57 pdr5.bit.PD57
#define PDR5_PD56 pdr5.bit.PD56
#define PDR5_PD55 pdr5.bit.PD55
#define PDR5_PD54 pdr5.bit.PD54
#define PDR5_PD53 pdr5.bit.PD53
#define PDR5_PD52 pdr5.bit.PD52
#define PDR5_PD51 pdr5.bit.PD51
#define PDR5_PD50 pdr5.bit.PD50
__IO_EXTERN PDR6STR pdr6;
#define PDR6 pdr6.byte
#define PDR6_PD64 pdr6.bit.PD64
#define PDR6_PD63 pdr6.bit.PD63
#define PDR6_PD62 pdr6.bit.PD62
#define PDR6_PD61 pdr6.bit.PD61
#define PDR6_PD60 pdr6.bit.PD60
__IO_EXTERN PDR7STR pdr7;
#define PDR7 pdr7.byte
#define PDR7_PD76 pdr7.bit.PD76
#define PDR7_PD75 pdr7.bit.PD75
#define PDR7_PD74 pdr7.bit.PD74
__IO_EXTERN PDR8STR pdr8;
#define PDR8 pdr8.byte
#define PDR8_PD87 pdr8.bit.PD87
#define PDR8_PD86 pdr8.bit.PD86
#define PDR8_PD82 pdr8.bit.PD82
#define PDR8_PD81 pdr8.bit.PD81
__IO_EXTERN PDR9STR pdr9;
#define PDR9 pdr9.byte
#define PDR9_PD97 pdr9.bit.PD97
#define PDR9_PD96 pdr9.bit.PD96
#define PDR9_PD93 pdr9.bit.PD93
#define PDR9_PD92 pdr9.bit.PD92
#define PDR9_PD91 pdr9.bit.PD91
#define PDR9_PD90 pdr9.bit.PD90
__IO_EXTERN PDRBSTR pdrb;
#define PDRB pdrb.byte
#define PDRB_PDB2 pdrb.bit.PDB2
#define PDRB_PDB1 pdrb.bit.PDB1
#define PDRB_PDB0 pdrb.bit.PDB0
__IO_EXTERN PDRGSTR pdrg;
#define PDRG pdrg.byte
#define PDRG_PDG7 pdrg.bit.PDG7
#define PDRG_PDG6 pdrg.bit.PDG6
#define PDRG_PDG5 pdrg.bit.PDG5
#define PDRG_PDG4 pdrg.bit.PDG4
#define PDRG_PDG3 pdrg.bit.PDG3
#define PDRG_PDG2 pdrg.bit.PDG2
#define PDRG_PDG1 pdrg.bit.PDG1
#define PDRG_PDG0 pdrg.bit.PDG0
__IO_EXTERN PDRHSTR pdrh;
#define PDRH pdrh.byte
#define PDRH_PDH7 pdrh.bit.PDH7
#define PDRH_PDH6 pdrh.bit.PDH6
#define PDRH_PDH5 pdrh.bit.PDH5
#define PDRH_PDH4 pdrh.bit.PDH4
#define PDRH_PDH3 pdrh.bit.PDH3
#define PDRH_PDH2 pdrh.bit.PDH2
#define PDRH_PDH1 pdrh.bit.PDH1
#define PDRH_PDH0 pdrh.bit.PDH0
__IO_EXTERN PDRISTR pdri;
#define PDRI pdri.byte
#define PDRI_PDI7 pdri.bit.PDI7
#define PDRI_PDI3 pdri.bit.PDI3
__IO_EXTERN PDRJSTR pdrj;
#define PDRJ pdrj.byte
#define PDRJ_PDJ7 pdrj.bit.PDJ7
#define PDRJ_PDJ6 pdrj.bit.PDJ6
#define PDRJ_PDJ5 pdrj.bit.PDJ5
#define PDRJ_PDJ4 pdrj.bit.PDJ4
#define PDRJ_PDJ3 pdrj.bit.PDJ3
#define PDRJ_PDJ2 pdrj.bit.PDJ2
#define PDRJ_PDJ1 pdrj.bit.PDJ1
#define PDRJ_PDJ0 pdrj.bit.PDJ0
__IO_EXTERN PDRKSTR pdrk;
#define PDRK pdrk.byte
#define PDRK_PDK7 pdrk.bit.PDK7
#define PDRK_PDK6 pdrk.bit.PDK6
#define PDRK_PDK5 pdrk.bit.PDK5
#define PDRK_PDK4 pdrk.bit.PDK4
#define PDRK_PDK3 pdrk.bit.PDK3
#define PDRK_PDK2 pdrk.bit.PDK2
#define PDRK_PDK1 pdrk.bit.PDK1
#define PDRK_PDK0 pdrk.bit.PDK0
__IO_EXTERN PDRLSTR pdrl;
#define PDRL pdrl.byte
#define PDRL_PDL7 pdrl.bit.PDL7
#define PDRL_PDL6 pdrl.bit.PDL6
#define PDRL_PDL5 pdrl.bit.PDL5
#define PDRL_PDL4 pdrl.bit.PDL4
#define PDRL_PDL3 pdrl.bit.PDL3
#define PDRL_PDL2 pdrl.bit.PDL2
#define PDRL_PDL1 pdrl.bit.PDL1
#define PDRL_PDL0 pdrl.bit.PDL0
__IO_EXTERN PDRMSTR pdrm;
#define PDRM pdrm.byte
#define PDRM_PDM3 pdrm.bit.PDM3
#define PDRM_PDM2 pdrm.bit.PDM2
#define PDRM_PDM1 pdrm.bit.PDM1
#define PDRM_PDM0 pdrm.bit.PDM0
__IO_EXTERN PDRNSTR pdrn;
#define PDRN pdrn.byte
#define PDRN_PDN5 pdrn.bit.PDN5
#define PDRN_PDN4 pdrn.bit.PDN4
#define PDRN_PDN3 pdrn.bit.PDN3
#define PDRN_PDN2 pdrn.bit.PDN2
#define PDRN_PDN1 pdrn.bit.PDN1
#define PDRN_PDN0 pdrn.bit.PDN0
__IO_EXTERN PDROSTR pdro;
#define PDRO pdro.byte
#define PDRO_PDO7 pdro.bit.PDO7
#define PDRO_PDO6 pdro.bit.PDO6
#define PDRO_PDO5 pdro.bit.PDO5
#define PDRO_PDO4 pdro.bit.PDO4
#define PDRO_PDO3 pdro.bit.PDO3
#define PDRO_PDO2 pdro.bit.PDO2
#define PDRO_PDO1 pdro.bit.PDO1
#define PDRO_PDO0 pdro.bit.PDO0
__IO_EXTERN PDRPSTR pdrp;
#define PDRP pdrp.byte
#define PDRP_PDP5 pdrp.bit.PDP5
#define PDRP_PDP4 pdrp.bit.PDP4
#define PDRP_PDP3 pdrp.bit.PDP3
#define PDRP_PDP2 pdrp.bit.PDP2
#define PDRP_PDP1 pdrp.bit.PDP1
#define PDRP_PDP0 pdrp.bit.PDP0
__IO_EXTERN PDRQSTR pdrq;
#define PDRQ pdrq.byte
#define PDRQ_PDQ5 pdrq.bit.PDQ5
#define PDRQ_PDQ4 pdrq.bit.PDQ4
#define PDRQ_PDQ3 pdrq.bit.PDQ3
#define PDRQ_PDQ2 pdrq.bit.PDQ2
#define PDRQ_PDQ1 pdrq.bit.PDQ1
#define PDRQ_PDQ0 pdrq.bit.PDQ0
__IO_EXTERN PDRRSTR pdrr;
#define PDRR pdrr.byte
#define PDRR_PR7 pdrr.bit.PR7
#define PDRR_PR6 pdrr.bit.PR6
#define PDRR_PR5 pdrr.bit.PR5
#define PDRR_PR4 pdrr.bit.PR4
#define PDRR_PR3 pdrr.bit.PR3
#define PDRR_PR2 pdrr.bit.PR2
#define PDRR_PR1 pdrr.bit.PR1
#define PDRR_PR0 pdrr.bit.PR0
__IO_EXTERN PDRSSTR pdrs;
#define PDRS pdrs.byte
#define PDRS_PDS7 pdrs.bit.PDS7
#define PDRS_PDS6 pdrs.bit.PDS6
#define PDRS_PDS5 pdrs.bit.PDS5
#define PDRS_PDS4 pdrs.bit.PDS4
#define PDRS_PDS3 pdrs.bit.PDS3
#define PDRS_PDS2 pdrs.bit.PDS2
#define PDRS_PDS1 pdrs.bit.PDS1
#define PDRS_PDS0 pdrs.bit.PDS0
__IO_EXTERN EIRRSTR eirr;   /* Ext. Int/NMI */
#define EIRR eirr.byte
#define EIRR_ER7 eirr.bit.ER7
#define EIRR_ER6 eirr.bit.ER6
#define EIRR_ER5 eirr.bit.ER5
#define EIRR_ER4 eirr.bit.ER4
#define EIRR_ER3 eirr.bit.ER3
#define EIRR_ER2 eirr.bit.ER2
#define EIRR_ER1 eirr.bit.ER1
#define EIRR_ER0 eirr.bit.ER0
__IO_EXTERN ENIRSTR enir;
#define ENIR enir.byte
#define ENIR_EN7 enir.bit.EN7
#define ENIR_EN6 enir.bit.EN6
#define ENIR_EN5 enir.bit.EN5
#define ENIR_EN4 enir.bit.EN4
#define ENIR_EN3 enir.bit.EN3
#define ENIR_EN2 enir.bit.EN2
#define ENIR_EN1 enir.bit.EN1
#define ENIR_EN0 enir.bit.EN0
__IO_EXTERN ELVRSTR elvr;
#define ELVR elvr.word
#define ELVR_LB7 elvr.bit.LB7
#define ELVR_LA7 elvr.bit.LA7
#define ELVR_LB6 elvr.bit.LB6
#define ELVR_LA6 elvr.bit.LA6
#define ELVR_LB5 elvr.bit.LB5
#define ELVR_LA5 elvr.bit.LA5
#define ELVR_LB4 elvr.bit.LB4
#define ELVR_LA4 elvr.bit.LA4
#define ELVR_LB3 elvr.bit.LB3
#define ELVR_LA3 elvr.bit.LA3
#define ELVR_LB2 elvr.bit.LB2
#define ELVR_LA2 elvr.bit.LA2
#define ELVR_LB1 elvr.bit.LB1
#define ELVR_LA1 elvr.bit.LA1
#define ELVR_LB0 elvr.bit.LB0
#define ELVR_LA0 elvr.bit.LA0

#define ELVR_LAB7 elvr.bit1.LAB7
#define ELVR_LAB6 elvr.bit1.LAB6
#define ELVR_LAB5 elvr.bit1.LAB5
#define ELVR_LAB4 elvr.bit1.LAB4
#define ELVR_LAB3 elvr.bit1.LAB3
#define ELVR_LAB2 elvr.bit1.LAB2
#define ELVR_LAB1 elvr.bit1.LAB1
#define ELVR_LAB0 elvr.bit1.LAB0

__IO_EXTERN DICRSTR dicr;   /* DLYI/I-Unit */
#define DICR dicr.byte
#define DICR_DLYI dicr.bit.DLYI
__IO_EXTERN HRCLSTR hrcl;
#define HRCL hrcl.byte
#define HRCL_LVL4 hrcl.bit.LVL4
#define HRCL_LVL3 hrcl.bit.LVL3
#define HRCL_LVL2 hrcl.bit.LVL2
#define HRCL_LVL1 hrcl.bit.LVL1
#define HRCL_LVL0 hrcl.bit.LVL0
__IO_EXTERN __io IO_WORD tmrlr0;   /* Reload Timer0 */
#define TMRLR0 tmrlr0
__IO_EXTERN __io IO_WORD tmr0;
#define TMR0 tmr0
__IO_EXTERN __io TMCSR0STR tmcsr0;
#define TMCSR0 tmcsr0.word
#define TMCSR0_CSL1 tmcsr0.bit.CSL1
#define TMCSR0_CSL0 tmcsr0.bit.CSL0
#define TMCSR0_RELD tmcsr0.bit.RELD
#define TMCSR0_INTE tmcsr0.bit.INTE
#define TMCSR0_UF tmcsr0.bit.UF
#define TMCSR0_CNTE tmcsr0.bit.CNTE
#define TMCSR0_TRG tmcsr0.bit.TRG
__IO_EXTERN __io IO_WORD tmrlr1;   /* Reload Timer1 */
#define TMRLR1 tmrlr1
__IO_EXTERN __io IO_WORD tmr1;
#define TMR1 tmr1
__IO_EXTERN __io TMCSR1STR tmcsr1;
#define TMCSR1 tmcsr1.word
#define TMCSR1_CSL1 tmcsr1.bit.CSL1
#define TMCSR1_CSL0 tmcsr1.bit.CSL0
#define TMCSR1_RELD tmcsr1.bit.RELD
#define TMCSR1_INTE tmcsr1.bit.INTE
#define TMCSR1_UF tmcsr1.bit.UF
#define TMCSR1_CNTE tmcsr1.bit.CNTE
#define TMCSR1_TRG tmcsr1.bit.TRG
__IO_EXTERN __io IO_WORD tmrlr2;   /* Reload Timer2 */
#define TMRLR2 tmrlr2
__IO_EXTERN __io IO_WORD tmr2;
#define TMR2 tmr2
__IO_EXTERN __io TMCSR2STR tmcsr2;
#define TMCSR2 tmcsr2.word
#define TMCSR2_CSL1 tmcsr2.bit.CSL1
#define TMCSR2_CSL0 tmcsr2.bit.CSL0
#define TMCSR2_RELD tmcsr2.bit.RELD
#define TMCSR2_INTE tmcsr2.bit.INTE
#define TMCSR2_UF tmcsr2.bit.UF
#define TMCSR2_CNTE tmcsr2.bit.CNTE
#define TMCSR2_TRG tmcsr2.bit.TRG
__IO_EXTERN __io SSR0STR ssr0;   /* UART0 */
#define SSR0 ssr0.byte
#define SSR0_PE ssr0.bit.PE
#define SSR0_ORE ssr0.bit.ORE
#define SSR0_FRE ssr0.bit.FRE
#define SSR0_RDRF ssr0.bit.RDRF
#define SSR0_TDRE ssr0.bit.TDRE
#define SSR0_RIE ssr0.bit.RIE
#define SSR0_TIE ssr0.bit.TIE
__IO_EXTERN __io SIDR0STR sidr0;
#define SIDR0 sidr0.byte
#define SIDR0_D7 sidr0.bit.D7
#define SIDR0_D6 sidr0.bit.D6
#define SIDR0_D5 sidr0.bit.D5
#define SIDR0_D4 sidr0.bit.D4
#define SIDR0_D3 sidr0.bit.D3
#define SIDR0_D2 sidr0.bit.D2
#define SIDR0_D1 sidr0.bit.D1
#define SIDR0_D0 sidr0.bit.D0
__IO_EXTERN __io SODR0STR sodr0;
#define SODR0 sodr0.byte
#define SODR0_D7 sodr0.bit.D7
#define SODR0_D6 sodr0.bit.D6
#define SODR0_D5 sodr0.bit.D5
#define SODR0_D4 sodr0.bit.D4
#define SODR0_D3 sodr0.bit.D3
#define SODR0_D2 sodr0.bit.D2
#define SODR0_D1 sodr0.bit.D1
#define SODR0_D0 sodr0.bit.D0
__IO_EXTERN __io SCR0STR scr0;
#define SCR0 scr0.byte
#define SCR0_PEN scr0.bit.PEN
#define SCR0_P scr0.bit.P
#define SCR0_SBL scr0.bit.SBL
#define SCR0_CL scr0.bit.CL
#define SCR0_AD scr0.bit.AD
#define SCR0_REC scr0.bit.REC
#define SCR0_RXE scr0.bit.RXE
#define SCR0_TXE scr0.bit.TXE
__IO_EXTERN __io SMR0STR smr0;
#define SMR0 smr0.byte
#define SMR0_MD1 smr0.bit.MD1
#define SMR0_MD0 smr0.bit.MD0
#define SMR0_CS0 smr0.bit.CS0
#define SMR0_SCKE smr0.bit.SCKE
#define SMR0_SOE smr0.bit.SOE
__IO_EXTERN __io ULS0STR uls0;
#define ULS0 uls0.byte
#define ULS0_NSDO uls0.bit.NSDO
#define ULS0_NSDI uls0.bit.NSDI
#define ULS0_UTDBL uls0.bit.UTDBL
#define ULS0_UDBL uls0.bit.UDBL
__IO_EXTERN __io IO_WORD utim0;
#define UTIM0 utim0
__IO_EXTERN __io IO_WORD utimr0;
#define UTIMR0 utimr0
__IO_EXTERN __io IO_BYTE drcl0;
#define DRCL0 drcl0
__IO_EXTERN __io UTIMC0STR utimc0;
#define UTIMC0 utimc0.byte
#define UTIMC0_UCC1 utimc0.bit.UCC1
#define UTIMC0_UTIE utimc0.bit.UTIE
#define UTIMC0_UNDR utimc0.bit.UNDR
#define UTIMC0_UTST utimc0.bit.UTST
#define UTIMC0_UTCR utimc0.bit.UTCR
__IO_EXTERN __io SSR1STR ssr1;   /* UART1 */
#define SSR1 ssr1.byte
#define SSR1_PE ssr1.bit.PE
#define SSR1_ORE ssr1.bit.ORE
#define SSR1_FRE ssr1.bit.FRE
#define SSR1_RDRF ssr1.bit.RDRF
#define SSR1_TDRE ssr1.bit.TDRE
#define SSR1_RIE ssr1.bit.RIE
#define SSR1_TIE ssr1.bit.TIE
__IO_EXTERN __io SIDR1STR sidr1;
#define SIDR1 sidr1.byte
#define SIDR1_D7 sidr1.bit.D7
#define SIDR1_D6 sidr1.bit.D6
#define SIDR1_D5 sidr1.bit.D5
#define SIDR1_D4 sidr1.bit.D4
#define SIDR1_D3 sidr1.bit.D3
#define SIDR1_D2 sidr1.bit.D2
#define SIDR1_D1 sidr1.bit.D1
#define SIDR1_D0 sidr1.bit.D0
__IO_EXTERN __io SODR1STR sodr1;
#define SODR1 sodr1.byte
#define SODR1_D7 sodr1.bit.D7
#define SODR1_D6 sodr1.bit.D6
#define SODR1_D5 sodr1.bit.D5
#define SODR1_D4 sodr1.bit.D4
#define SODR1_D3 sodr1.bit.D3
#define SODR1_D2 sodr1.bit.D2
#define SODR1_D1 sodr1.bit.D1
#define SODR1_D0 sodr1.bit.D0
__IO_EXTERN __io SCR1STR scr1;
#define SCR1 scr1.byte
#define SCR1_PEN scr1.bit.PEN
#define SCR1_P scr1.bit.P
#define SCR1_SBL scr1.bit.SBL
#define SCR1_CL scr1.bit.CL
#define SCR1_AD scr1.bit.AD
#define SCR1_REC scr1.bit.REC
#define SCR1_RXE scr1.bit.RXE
#define SCR1_TXE scr1.bit.TXE
__IO_EXTERN __io SMR1STR smr1;
#define SMR1 smr1.byte
#define SMR1_MD1 smr1.bit.MD1
#define SMR1_MD0 smr1.bit.MD0
#define SMR1_CS0 smr1.bit.CS0
#define SMR1_SCKE smr1.bit.SCKE
#define SMR1_SOE smr1.bit.SOE
__IO_EXTERN __io ULS1STR uls1;
#define ULS1 uls1.byte
#define ULS1_NSDO uls1.bit.NSDO
#define ULS1_NSDI uls1.bit.NSDI
#define ULS1_UTDBL uls1.bit.UTDBL
#define ULS1_UDBL uls1.bit.UDBL
__IO_EXTERN __io IO_WORD utim1;
#define UTIM1 utim1
__IO_EXTERN __io IO_WORD utimr1;
#define UTIMR1 utimr1
__IO_EXTERN __io IO_BYTE drcl1;
#define DRCL1 drcl1
__IO_EXTERN __io UTIMC1STR utimc1;
#define UTIMC1 utimc1.byte
#define UTIMC1_UCC1 utimc1.bit.UCC1
#define UTIMC1_UTIE utimc1.bit.UTIE
#define UTIMC1_UNDR utimc1.bit.UNDR
#define UTIMC1_UTST utimc1.bit.UTST
#define UTIMC1_UTCR utimc1.bit.UTCR
__IO_EXTERN __io SSR2STR ssr2;   /* UART2 */
#define SSR2 ssr2.byte
#define SSR2_PE ssr2.bit.PE
#define SSR2_ORE ssr2.bit.ORE
#define SSR2_FRE ssr2.bit.FRE
#define SSR2_RDRF ssr2.bit.RDRF
#define SSR2_TDRE ssr2.bit.TDRE
#define SSR2_RIE ssr2.bit.RIE
#define SSR2_TIE ssr2.bit.TIE
__IO_EXTERN __io SIDR2STR sidr2;
#define SIDR2 sidr2.byte
#define SIDR2_D7 sidr2.bit.D7
#define SIDR2_D6 sidr2.bit.D6
#define SIDR2_D5 sidr2.bit.D5
#define SIDR2_D4 sidr2.bit.D4
#define SIDR2_D3 sidr2.bit.D3
#define SIDR2_D2 sidr2.bit.D2
#define SIDR2_D1 sidr2.bit.D1
#define SIDR2_D0 sidr2.bit.D0
__IO_EXTERN __io SODR2STR sodr2;
#define SODR2 sodr2.byte
#define SODR2_D7 sodr2.bit.D7
#define SODR2_D6 sodr2.bit.D6
#define SODR2_D5 sodr2.bit.D5
#define SODR2_D4 sodr2.bit.D4
#define SODR2_D3 sodr2.bit.D3
#define SODR2_D2 sodr2.bit.D2
#define SODR2_D1 sodr2.bit.D1
#define SODR2_D0 sodr2.bit.D0
__IO_EXTERN __io SCR2STR scr2;
#define SCR2 scr2.byte
#define SCR2_PEN scr2.bit.PEN
#define SCR2_P scr2.bit.P
#define SCR2_SBL scr2.bit.SBL
#define SCR2_CL scr2.bit.CL
#define SCR2_AD scr2.bit.AD
#define SCR2_REC scr2.bit.REC
#define SCR2_RXE scr2.bit.RXE
#define SCR2_TXE scr2.bit.TXE
__IO_EXTERN __io SMR2STR smr2;
#define SMR2 smr2.byte
#define SMR2_MD1 smr2.bit.MD1
#define SMR2_MD0 smr2.bit.MD0
#define SMR2_CS0 smr2.bit.CS0
#define SMR2_SCKE smr2.bit.SCKE
#define SMR2_SOE smr2.bit.SOE
__IO_EXTERN __io ULS2STR uls2;
#define ULS2 uls2.byte
#define ULS2_NSDO uls2.bit.NSDO
#define ULS2_NSDI uls2.bit.NSDI
#define ULS2_UTDBL uls2.bit.UTDBL
#define ULS2_UDBL uls2.bit.UDBL
__IO_EXTERN __io IO_WORD utim2;
#define UTIM2 utim2
__IO_EXTERN __io IO_WORD utimr2;
#define UTIMR2 utimr2
__IO_EXTERN __io IO_BYTE drcl2;
#define DRCL2 drcl2
__IO_EXTERN __io UTIMC2STR utimc2;
#define UTIMC2 utimc2.byte
#define UTIMC2_UCC1 utimc2.bit.UCC1
#define UTIMC2_UTIE utimc2.bit.UTIE
#define UTIMC2_UNDR utimc2.bit.UNDR
#define UTIMC2_UTST utimc2.bit.UTST
#define UTIMC2_UTCR utimc2.bit.UTCR
__IO_EXTERN __io SMCS0STR smcs0;   /* SIO0 */
#define SMCS0 smcs0.word
#define SMCS0_SMD2 smcs0.bit.SMD2
#define SMCS0_SMD1 smcs0.bit.SMD1
#define SMCS0_SMD0 smcs0.bit.SMD0
#define SMCS0_SIE smcs0.bit.SIE
#define SMCS0_SIR smcs0.bit.SIR
#define SMCS0_BUSY smcs0.bit.BUSY
#define SMCS0_STOP smcs0.bit.STOP
#define SMCS0_STRT smcs0.bit.STRT
#define SMCS0_MODE smcs0.bit.MODE
#define SMCS0_BDS smcs0.bit.BDS
#define SMCS0_SCOE smcs0.bit.SCOE
#define SMCS0_SMD smcs0.bitc.SMD
__IO_EXTERN __io SES0STR ses0;
#define SES0 ses0.byte
#define SES0_DBL ses0.bit.DBL
#define SES0_SES ses0.bit.SES
__IO_EXTERN __io IO_BYTE sdr0;
#define SDR0 sdr0
__IO_EXTERN __io SMCS1STR smcs1;   /* SIO1 */
#define SMCS1 smcs1.word
#define SMCS1_SMD2 smcs1.bit.SMD2
#define SMCS1_SMD1 smcs1.bit.SMD1
#define SMCS1_SMD0 smcs1.bit.SMD0
#define SMCS1_SIE smcs1.bit.SIE
#define SMCS1_SIR smcs1.bit.SIR
#define SMCS1_BUSY smcs1.bit.BUSY
#define SMCS1_STOP smcs1.bit.STOP
#define SMCS1_STRT smcs1.bit.STRT
#define SMCS1_MODE smcs1.bit.MODE
#define SMCS1_BDS smcs1.bit.BDS
#define SMCS1_SCOE smcs1.bit.SCOE
#define SMCS1_SMD smcs1.bitc.SMD
__IO_EXTERN __io SES1STR ses1;
#define SES1 ses1.byte
#define SES1_DBL ses1.bit.DBL
#define SES1_SES ses1.bit.SES
__IO_EXTERN __io IO_BYTE sdr1;
#define SDR1 sdr1
__IO_EXTERN __io CDCR0STR cdcr0;   /* SIO PRESC */
#define CDCR0 cdcr0.byte
#define CDCR0_MD cdcr0.bit.MD
#define CDCR0_DIV3 cdcr0.bit.DIV3
#define CDCR0_DIV2 cdcr0.bit.DIV2
#define CDCR0_DIV1 cdcr0.bit.DIV1
#define CDCR0_DIV0 cdcr0.bit.DIV0
#define CDCR0_DIV cdcr0.bitc.DIV
__IO_EXTERN __io IO_BYTE psmr0;
#define PSMR0 psmr0
__IO_EXTERN __io CDCR1STR cdcr1;
#define CDCR1 cdcr1.byte
#define CDCR1_MD cdcr1.bit.MD
#define CDCR1_DIV3 cdcr1.bit.DIV3
#define CDCR1_DIV2 cdcr1.bit.DIV2
#define CDCR1_DIV1 cdcr1.bit.DIV1
#define CDCR1_DIV0 cdcr1.bit.DIV0
#define CDCR1_DIV cdcr1.bitc.DIV
__IO_EXTERN __io IO_BYTE psmr1;
#define PSMR1 psmr1
__IO_EXTERN __io IBCRSTR ibcr;   /* I2C */
#define IBCR ibcr.byte
#define IBCR_BER ibcr.bit.BER
#define IBCR_BEIE ibcr.bit.BEIE
#define IBCR_SCC ibcr.bit.SCC
#define IBCR_MSS ibcr.bit.MSS
#define IBCR_ACK ibcr.bit.ACK
#define IBCR_GCAA ibcr.bit.GCAA
#define IBCR_INTE ibcr.bit.INTE
#define IBCR_INT ibcr.bit.INT
__IO_EXTERN __io IBSRSTR ibsr;
#define IBSR ibsr.byte
#define IBSR_BB ibsr.bit.BB
#define IBSR_RSC ibsr.bit.RSC
#define IBSR_AL ibsr.bit.AL
#define IBSR_LRB ibsr.bit.LRB
#define IBSR_TRX ibsr.bit.TRX
#define IBSR_AAS ibsr.bit.AAS
#define IBSR_GCA ibsr.bit.GCA
#define IBSR_FBT ibsr.bit.FBT
__IO_EXTERN __io IADRSTR iadr;
#define IADR iadr.byte
#define IADR_A6 iadr.bit.A6
#define IADR_A5 iadr.bit.A5
#define IADR_A4 iadr.bit.A4
#define IADR_A3 iadr.bit.A3
#define IADR_A2 iadr.bit.A2
#define IADR_A1 iadr.bit.A1
#define IADR_A0 iadr.bit.A0
__IO_EXTERN __io ICCRSTR iccr;
#define ICCR iccr.byte
#define ICCR_EN iccr.bit.EN
#define ICCR_CS4 iccr.bit.CS4
#define ICCR_CS3 iccr.bit.CS3
#define ICCR_CS2 iccr.bit.CS2
#define ICCR_CS1 iccr.bit.CS1
#define ICCR_CS0 iccr.bit.CS0
#define ICCR_CS iccr.bitc.CS
__IO_EXTERN __io IDARSTR idar;
#define IDAR idar.byte
#define IDAR_D7 idar.bit.D7
#define IDAR_D6 idar.bit.D6
#define IDAR_D5 idar.bit.D5
#define IDAR_D4 idar.bit.D4
#define IDAR_D3 idar.bit.D3
#define IDAR_D2 idar.bit.D2
#define IDAR_D1 idar.bit.D1
#define IDAR_D0 idar.bit.D0
__IO_EXTERN __io IDBLSTR idbl;
#define IDBL idbl.byte
#define IDBL_DBL idbl.bit.DBL
__IO_EXTERN __io ADMDSTR admd;   /* ADC */
#define ADMD admd.byte
#define ADMD_MOD1 admd.bit.MOD1
#define ADMD_MOD0 admd.bit.MOD0
#define ADMD_STS1 admd.bit.STS1
#define ADMD_STS0 admd.bit.STS0
#define ADMD_MOD admd.bitc.MOD
#define ADMD_STS admd.bitc.STS
__IO_EXTERN __io ADCHSTR adch;
#define ADCH adch.byte
#define ADCH_ANS3 adch.bit.ANS3
#define ADCH_ANS2 adch.bit.ANS2
#define ADCH_ANS1 adch.bit.ANS1
#define ADCH_ANS0 adch.bit.ANS0
#define ADCH_ANE3 adch.bit.ANE3
#define ADCH_ANE2 adch.bit.ANE2
#define ADCH_ANE1 adch.bit.ANE1
#define ADCH_ANE0 adch.bit.ANE0
#define ADCH_ANS adch.bitc.ANS
#define ADCH_ANE adch.bitc.ANE
__IO_EXTERN __io ADCSSTR adcs;
#define ADCS adcs.byte
#define ADCS_BUSY adcs.bit.BUSY
#define ADCS_INT adcs.bit.INT
#define ADCS_INTE adcs.bit.INTE
#define ADCS_PAUS adcs.bit.PAUS
#define ADCS_STRT adcs.bit.STRT
__IO_EXTERN __io IO_WORD adcd;
#define ADCD adcd
__IO_EXTERN __io ADBLSTR adbl;
#define ADBL adbl.byte
#define ADBL_DBL adbl.bit.DBL
__IO_EXTERN __io DACRSTR dacr;   /* DAC */
#define DACR dacr.byte
#define DACR_MODE dacr.bit.MODE
#define DACR_DAE1 dacr.bit.DAE1
#define DACR_DAE0 dacr.bit.DAE0
__IO_EXTERN __io IO_WORD dadr0;
#define DADR0 dadr0
__IO_EXTERN __io IO_WORD dadr1;
#define DADR1 dadr1
__IO_EXTERN __io DDBLSTR ddbl;
#define DDBL ddbl.byte
#define DDBL_DBL ddbl.bit.DBL
__IO_EXTERN __io IOTDBL0STR iotdbl0;   /* Input Capture */
#define IOTDBL0 iotdbl0.byte
#define IOTDBL0_DBLT iotdbl0.bit.DBLT
#define IOTDBL0_DBLI iotdbl0.bit.DBLI
#define IOTDBL0_DBLO iotdbl0.bit.DBLO
__IO_EXTERN __io ICS01STR ics01;
#define ICS01 ics01.byte
#define ICS01_ICP1 ics01.bit.ICP1
#define ICS01_ICP0 ics01.bit.ICP0
#define ICS01_ICE1 ics01.bit.ICE1
#define ICS01_ICE0 ics01.bit.ICE0
#define ICS01_EG11 ics01.bit.EG11
#define ICS01_EG10 ics01.bit.EG10
#define ICS01_EG01 ics01.bit.EG01
#define ICS01_EG00 ics01.bit.EG00
__IO_EXTERN __io IOTDBL1STR iotdbl1;
#define IOTDBL1 iotdbl1.byte
#define IOTDBL1_DBLT iotdbl1.bit.DBLT
#define IOTDBL1_DBLI iotdbl1.bit.DBLI
#define IOTDBL1_DBLO iotdbl1.bit.DBLO
__IO_EXTERN __io ICS23STR ics23;
#define ICS23 ics23.byte
#define ICS23_ICP3 ics23.bit.ICP3
#define ICS23_ICP2 ics23.bit.ICP2
#define ICS23_ICE3 ics23.bit.ICE3
#define ICS23_ICE2 ics23.bit.ICE2
#define ICS23_EG11 ics23.bit.EG11
#define ICS23_EG10 ics23.bit.EG10
#define ICS23_EG01 ics23.bit.EG01
#define ICS23_EG00 ics23.bit.EG00
__IO_EXTERN __io IO_WORD ipcp0;
#define IPCP0 ipcp0
__IO_EXTERN __io IO_WORD ipcp1;
#define IPCP1 ipcp1
__IO_EXTERN __io IO_WORD ipcp2;
#define IPCP2 ipcp2
__IO_EXTERN __io IO_WORD ipcp3;
#define IPCP3 ipcp3
__IO_EXTERN __io OCS01STR ocs01;   /* Output Capture */
#define OCS01 ocs01.word
#define OCS01_CMOD ocs01.bit.CMOD
#define OCS01_OTD1 ocs01.bit.OTD1
#define OCS01_OTD0 ocs01.bit.OTD0
#define OCS01_ICP1 ocs01.bit.ICP1
#define OCS01_ICP0 ocs01.bit.ICP0
#define OCS01_ICE1 ocs01.bit.ICE1
#define OCS01_ICE0 ocs01.bit.ICE0
#define OCS01_CST1 ocs01.bit.CST1
#define OCS01_CST0 ocs01.bit.CST0
__IO_EXTERN __io OCS23STR ocs23;
#define OCS23 ocs23.word
#define OCS23_CMOD ocs23.bit.CMOD
#define OCS23_OTD3 ocs23.bit.OTD3
#define OCS23_OTD2 ocs23.bit.OTD2
#define OCS23_ICP3 ocs23.bit.ICP3
#define OCS23_ICP2 ocs23.bit.ICP2
#define OCS23_ICE3 ocs23.bit.ICE3
#define OCS23_ICE2 ocs23.bit.ICE2
#define OCS23_CST3 ocs23.bit.CST3
#define OCS23_CST2 ocs23.bit.CST2
__IO_EXTERN __io IO_WORD occp0;
#define OCCP0 occp0
__IO_EXTERN __io IO_WORD occp1;
#define OCCP1 occp1
__IO_EXTERN __io IO_WORD occp2;
#define OCCP2 occp2
__IO_EXTERN __io IO_WORD occp3;
#define OCCP3 occp3
__IO_EXTERN __io IO_WORD tcdt0;   /* Free Running Timer0 */
#define TCDT0 tcdt0
__IO_EXTERN __io TCCS0STR tccs0;
#define TCCS0 tccs0.byte
#define TCCS0_IVF tccs0.bit.IVF
#define TCCS0_IVFE tccs0.bit.IVFE
#define TCCS0_STOP tccs0.bit.STOP
#define TCCS0_MODE tccs0.bit.MODE
#define TCCS0_CLR tccs0.bit.CLR
#define TCCS0_CLK1 tccs0.bit.CLK1
#define TCCS0_CLK0 tccs0.bit.CLK0
__IO_EXTERN __io IO_WORD tcdt1;   /* Free Running Timer1 */
#define TCDT1 tcdt1
__IO_EXTERN __io TCCS1STR tccs1;
#define TCCS1 tccs1.byte
#define TCCS1_IVF tccs1.bit.IVF
#define TCCS1_IVFE tccs1.bit.IVFE
#define TCCS1_STOP tccs1.bit.STOP
#define TCCS1_MODE tccs1.bit.MODE
#define TCCS1_CLR tccs1.bit.CLR
#define TCCS1_CLK1 tccs1.bit.CLK1
#define TCCS1_CLK0 tccs1.bit.CLK0
__IO_EXTERN __io ZPD0STR zpd0;   /* Stepper Motor Control */
#define ZPD0 zpd0.byte
#define ZPD0_S1 zpd0.bit.S1
#define ZPD0_S0 zpd0.bit.S0
#define ZPD0_TS zpd0.bit.TS
#define ZPD0_T2 zpd0.bit.T2
#define ZPD0_T1 zpd0.bit.T1
#define ZPD0_T0 zpd0.bit.T0
#define ZPD0_PD zpd0.bit.PD
#define ZPD0_RS zpd0.bit.RS
#define ZPD0_S zpd0.bitc.S
#define ZPD0_T zpd0.bitc.T
__IO_EXTERN __io PWC0STR pwc0;
#define PWC0 pwc0.byte
#define PWC0_P1 pwc0.bit.P1
#define PWC0_P0 pwc0.bit.P0
#define PWC0_CE pwc0.bit.CE
#define PWC0_TST pwc0.bit.TST
#define PWC0_P pwc0.bitc.P
__IO_EXTERN __io ZPD1STR zpd1;
#define ZPD1 zpd1.byte
#define ZPD1_S1 zpd1.bit.S1
#define ZPD1_S0 zpd1.bit.S0
#define ZPD1_TS zpd1.bit.TS
#define ZPD1_T2 zpd1.bit.T2
#define ZPD1_T1 zpd1.bit.T1
#define ZPD1_T0 zpd1.bit.T0
#define ZPD1_PD zpd1.bit.PD
#define ZPD1_RS zpd1.bit.RS
#define ZPD1_S zpd1.bitc.S
#define ZPD1_T zpd1.bitc.T
__IO_EXTERN __io PWC1STR pwc1;
#define PWC1 pwc1.byte
#define PWC1_P1 pwc1.bit.P1
#define PWC1_P0 pwc1.bit.P0
#define PWC1_CE pwc1.bit.CE
#define PWC1_TST pwc1.bit.TST
#define PWC1_P pwc1.bitc.P
__IO_EXTERN __io ZPD2STR zpd2;
#define ZPD2 zpd2.byte
#define ZPD2_S1 zpd2.bit.S1
#define ZPD2_S0 zpd2.bit.S0
#define ZPD2_TS zpd2.bit.TS
#define ZPD2_T2 zpd2.bit.T2
#define ZPD2_T1 zpd2.bit.T1
#define ZPD2_T0 zpd2.bit.T0
#define ZPD2_PD zpd2.bit.PD
#define ZPD2_RS zpd2.bit.RS
#define ZPD2_S zpd2.bitc.S
#define ZPD2_T zpd2.bitc.T
__IO_EXTERN __io PWC2STR pwc2;
#define PWC2 pwc2.byte
#define PWC2_P1 pwc2.bit.P1
#define PWC2_P0 pwc2.bit.P0
#define PWC2_CE pwc2.bit.CE
#define PWC2_TST pwc2.bit.TST
#define PWC2_P pwc2.bitc.P
__IO_EXTERN __io ZPD3STR zpd3;
#define ZPD3 zpd3.byte
#define ZPD3_S1 zpd3.bit.S1
#define ZPD3_S0 zpd3.bit.S0
#define ZPD3_TS zpd3.bit.TS
#define ZPD3_T2 zpd3.bit.T2
#define ZPD3_T1 zpd3.bit.T1
#define ZPD3_T0 zpd3.bit.T0
#define ZPD3_PD zpd3.bit.PD
#define ZPD3_RS zpd3.bit.RS
#define ZPD3_S zpd3.bitc.S
#define ZPD3_T zpd3.bitc.T
__IO_EXTERN __io PWC3STR pwc3;
#define PWC3 pwc3.byte
#define PWC3_P1 pwc3.bit.P1
#define PWC3_P0 pwc3.bit.P0
#define PWC3_CE pwc3.bit.CE
#define PWC3_TST pwc3.bit.TST
#define PWC3_P pwc3.bitc.P
__IO_EXTERN __io IO_BYTE pwc20;
#define PWC20 pwc20
__IO_EXTERN __io IO_BYTE pwc10;
#define PWC10 pwc10
__IO_EXTERN __io PWS20STR pws20;
#define PWS20 pws20.byte
#define PWS20_BS pws20.bit.BS
#define PWS20_P2 pws20.bit.P2
#define PWS20_P1 pws20.bit.P1
#define PWS20_P0 pws20.bit.P0
#define PWS20_M2 pws20.bit.M2
#define PWS20_M1 pws20.bit.M1
#define PWS20_M0 pws20.bit.M0
#define PWS20_P pws20.bitc.P
#define PWS20_M pws20.bitc.M
__IO_EXTERN __io PWS10STR pws10;
#define PWS10 pws10.byte
#define PWS10_P2 pws10.bit.P2
#define PWS10_P1 pws10.bit.P1
#define PWS10_P0 pws10.bit.P0
#define PWS10_M2 pws10.bit.M2
#define PWS10_M1 pws10.bit.M1
#define PWS10_M0 pws10.bit.M0
#define PWS10_P pws10.bitc.P
#define PWS10_M pws10.bitc.M
__IO_EXTERN __io IO_BYTE pwc21;
#define PWC21 pwc21
__IO_EXTERN __io IO_BYTE pwc11;
#define PWC11 pwc11
__IO_EXTERN __io PWS21STR pws21;
#define PWS21 pws21.byte
#define PWS21_BS pws21.bit.BS
#define PWS21_P2 pws21.bit.P2
#define PWS21_P1 pws21.bit.P1
#define PWS21_P0 pws21.bit.P0
#define PWS21_M2 pws21.bit.M2
#define PWS21_M1 pws21.bit.M1
#define PWS21_M0 pws21.bit.M0
#define PWS21_P pws21.bitc.P
#define PWS21_M pws21.bitc.M
__IO_EXTERN __io PWS11STR pws11;
#define PWS11 pws11.byte
#define PWS11_P2 pws11.bit.P2
#define PWS11_P1 pws11.bit.P1
#define PWS11_P0 pws11.bit.P0
#define PWS11_M2 pws11.bit.M2
#define PWS11_M1 pws11.bit.M1
#define PWS11_M0 pws11.bit.M0
#define PWS11_P pws11.bitc.P
#define PWS11_M pws11.bitc.M
__IO_EXTERN __io IO_BYTE pwc22;
#define PWC22 pwc22
__IO_EXTERN __io IO_BYTE pwc12;
#define PWC12 pwc12
__IO_EXTERN __io PWS22STR pws22;
#define PWS22 pws22.byte
#define PWS22_BS pws22.bit.BS
#define PWS22_P2 pws22.bit.P2
#define PWS22_P1 pws22.bit.P1
#define PWS22_P0 pws22.bit.P0
#define PWS22_M2 pws22.bit.M2
#define PWS22_M1 pws22.bit.M1
#define PWS22_M0 pws22.bit.M0
#define PWS22_P pws22.bitc.P
#define PWS22_M pws22.bitc.M
__IO_EXTERN __io PWS12STR pws12;
#define PWS12 pws12.byte
#define PWS12_P2 pws12.bit.P2
#define PWS12_P1 pws12.bit.P1
#define PWS12_P0 pws12.bit.P0
#define PWS12_M2 pws12.bit.M2
#define PWS12_M1 pws12.bit.M1
#define PWS12_M0 pws12.bit.M0
#define PWS12_P pws12.bitc.P
#define PWS12_M pws12.bitc.M
__IO_EXTERN __io IO_BYTE pwc23;
#define PWC23 pwc23
__IO_EXTERN __io IO_BYTE pwc13;
#define PWC13 pwc13
__IO_EXTERN __io PWS23STR pws23;
#define PWS23 pws23.byte
#define PWS23_BS pws23.bit.BS
#define PWS23_P2 pws23.bit.P2
#define PWS23_P1 pws23.bit.P1
#define PWS23_P0 pws23.bit.P0
#define PWS23_M2 pws23.bit.M2
#define PWS23_M1 pws23.bit.M1
#define PWS23_M0 pws23.bit.M0
#define PWS23_P pws23.bitc.P
#define PWS23_M pws23.bitc.M
__IO_EXTERN __io PWS13STR pws13;
#define PWS13 pws13.byte
#define PWS13_P2 pws13.bit.P2
#define PWS13_P1 pws13.bit.P1
#define PWS13_P0 pws13.bit.P0
#define PWS13_M2 pws13.bit.M2
#define PWS13_M1 pws13.bit.M1
#define PWS13_M0 pws13.bit.M0
#define PWS13_P pws13.bitc.P
#define PWS13_M pws13.bitc.M
__IO_EXTERN __io SMDBL0STR smdbl0;
#define SMDBL0 smdbl0.byte
#define SMDBL0_DBL smdbl0.bit.DBL
__IO_EXTERN __io SMDBL1STR smdbl1;
#define SMDBL1 smdbl1.byte
#define SMDBL1_DBL smdbl1.bit.DBL
__IO_EXTERN __io SMDBL2STR smdbl2;
#define SMDBL2 smdbl2.byte
#define SMDBL2_DBL smdbl2.bit.DBL
__IO_EXTERN __io SMDBL3STR smdbl3;
#define SMDBL3 smdbl3.byte
#define SMDBL3_DBL smdbl3.bit.DBL
__IO_EXTERN __io SGDBLSTR sgdbl;   /* Sound Generator */
#define SGDBL sgdbl.byte
#define SGDBL_DBL sgdbl.bit.DBL
__IO_EXTERN __io SGCRSTR sgcr;
#define SGCR sgcr.word
#define SGCR_TST sgcr.bit.TST
#define SGCR_BUSY sgcr.bit.BUSY
#define SGCR_DEC sgcr.bit.DEC
#define SGCR_S1 sgcr.bit.S1
#define SGCR_S0 sgcr.bit.S0
#define SGCR_TONE sgcr.bit.TONE
#define SGCR_INTE sgcr.bit.INTE
#define SGCR_INT sgcr.bit.INT
#define SGCR_ST sgcr.bit.ST
__IO_EXTERN __io IO_BYTE sgar;
#define SGAR sgar
__IO_EXTERN __io IO_BYTE sgfr;
#define SGFR sgfr
__IO_EXTERN __io IO_BYTE sgtr;
#define SGTR sgtr
__IO_EXTERN __io IO_BYTE sgdr;
#define SGDR sgdr
__IO_EXTERN __io WTDBLSTR wtdbl;   /* Real Time Clock (RTC) */
#define WTDBL wtdbl.byte
#define WTDBL_DBL wtdbl.bit.DBL
__IO_EXTERN __io WTCRSTR wtcr;
#define WTCR wtcr.word
#define WTCR_INTE3 wtcr.bit.INTE3
#define WTCR_INT3 wtcr.bit.INT3
#define WTCR_INTE2 wtcr.bit.INTE2
#define WTCR_INT2 wtcr.bit.INT2
#define WTCR_INTE1 wtcr.bit.INTE1
#define WTCR_INT1 wtcr.bit.INT1
#define WTCR_INTE0 wtcr.bit.INTE0
#define WTCR_INT0 wtcr.bit.INT0
#define WTCR_TST2 wtcr.bit.TST2
#define WTCR_TST1 wtcr.bit.TST1
#define WTCR_TST0 wtcr.bit.TST0
#define WTCR_RUN wtcr.bit.RUN
#define WTCR_UPDT wtcr.bit.UPDT
#define WTCR_ST wtcr.bit.ST
/*-------------------------------------------------------------------*/
/* INC360_1.INC :  Special IO variables of watch timer. */
/* (changed to HIGH-MID-LOW on 15.3.99) */

/* struture of WTBR */
struct wtbrs {
	unsigned char	HIGH ;
	unsigned char	MID ;
	unsigned char	LOW;
};

/* I/O register variables */
__IO_EXTERN __io struct wtbrs	wtbr;


/* alias macro definition for WTBR */
#define WTBR_LOW wtbr.LOW
#define WTBR_MID wtbr.MID
#define WTBR_HIGH wtbr.HIGH

/*-------------------------------------------------------------------*/
__IO_EXTERN __io WTHRSTR wthr;
#define WTHR wthr.byte
#define WTHR_H4 wthr.bit.H4
#define WTHR_H3 wthr.bit.H3
#define WTHR_H2 wthr.bit.H2
#define WTHR_H1 wthr.bit.H1
#define WTHR_H0 wthr.bit.H0
__IO_EXTERN __io WTMRSTR wtmr;
#define WTMR wtmr.byte
#define WTMR_M5 wtmr.bit.M5
#define WTMR_M4 wtmr.bit.M4
#define WTMR_M3 wtmr.bit.M3
#define WTMR_M2 wtmr.bit.M2
#define WTMR_M1 wtmr.bit.M1
#define WTMR_M0 wtmr.bit.M0
__IO_EXTERN __io WTSRSTR wtsr;
#define WTSR wtsr.byte
#define WTSR_S5 wtsr.bit.S5
#define WTSR_S4 wtsr.bit.S4
#define WTSR_S3 wtsr.bit.S3
#define WTSR_S2 wtsr.bit.S2
#define WTSR_S1 wtsr.bit.S1
#define WTSR_S0 wtsr.bit.S0
__IO_EXTERN IO_WORD tmrlr3;   /* Reload Timer3 */
#define TMRLR3 tmrlr3
__IO_EXTERN IO_WORD tmr3;
#define TMR3 tmr3
__IO_EXTERN TMCSR3STR tmcsr3;
#define TMCSR3 tmcsr3.word
#define TMCSR3_CSL1 tmcsr3.bit.CSL1
#define TMCSR3_CSL0 tmcsr3.bit.CSL0
#define TMCSR3_RELD tmcsr3.bit.RELD
#define TMCSR3_INTE tmcsr3.bit.INTE
#define TMCSR3_UF tmcsr3.bit.UF
#define TMCSR3_CNTE tmcsr3.bit.CNTE
#define TMCSR3_TRG tmcsr3.bit.TRG
__IO_EXTERN IO_WORD tmrlr4;   /* Reload Timer4 */
#define TMRLR4 tmrlr4
__IO_EXTERN IO_WORD tmr4;
#define TMR4 tmr4
__IO_EXTERN TMCSR4STR tmcsr4;
#define TMCSR4 tmcsr4.word
#define TMCSR4_CSL1 tmcsr4.bit.CSL1
#define TMCSR4_CSL0 tmcsr4.bit.CSL0
#define TMCSR4_RELD tmcsr4.bit.RELD
#define TMCSR4_INTE tmcsr4.bit.INTE
#define TMCSR4_UF tmcsr4.bit.UF
#define TMCSR4_CNTE tmcsr4.bit.CNTE
#define TMCSR4_TRG tmcsr4.bit.TRG
__IO_EXTERN IO_WORD tmrlr5;   /* Reload Timer5 */
#define TMRLR5 tmrlr5
__IO_EXTERN IO_WORD tmr5;
#define TMR5 tmr5
__IO_EXTERN TMCSR5STR tmcsr5;
#define TMCSR5 tmcsr5.word
#define TMCSR5_CSL1 tmcsr5.bit.CSL1
#define TMCSR5_CSL0 tmcsr5.bit.CSL0
#define TMCSR5_RELD tmcsr5.bit.RELD
#define TMCSR5_INTE tmcsr5.bit.INTE
#define TMCSR5_UF tmcsr5.bit.UF
#define TMCSR5_CNTE tmcsr5.bit.CNTE
#define TMCSR5_TRG tmcsr5.bit.TRG
__IO_EXTERN GCN10STR gcn10;   /* PWM CNTRL */
#define GCN10 gcn10.word
#define GCN10_TSEL33 gcn10.bit.TSEL33
#define GCN10_TSEL32 gcn10.bit.TSEL32
#define GCN10_TSEL31 gcn10.bit.TSEL31
#define GCN10_TSEL30 gcn10.bit.TSEL30
#define GCN10_TSEL23 gcn10.bit.TSEL23
#define GCN10_TSEL22 gcn10.bit.TSEL22
#define GCN10_TSEL21 gcn10.bit.TSEL21
#define GCN10_TSEL20 gcn10.bit.TSEL20
#define GCN10_TSEL13 gcn10.bit.TSEL13
#define GCN10_TSEL12 gcn10.bit.TSEL12
#define GCN10_TSEL11 gcn10.bit.TSEL11
#define GCN10_TSEL10 gcn10.bit.TSEL10
#define GCN10_TSEL03 gcn10.bit.TSEL03
#define GCN10_TSEL02 gcn10.bit.TSEL02
#define GCN10_TSEL01 gcn10.bit.TSEL01
#define GCN10_TSEL00 gcn10.bit.TSEL00
__IO_EXTERN PDBL0STR pdbl0;
#define PDBL0 pdbl0.byte
#define PDBL0_DBC0 pdbl0.bit.DBC0
#define PDBL0_DBL3 pdbl0.bit.DBL3
#define PDBL0_DBL2 pdbl0.bit.DBL2
#define PDBL0_DBL1 pdbl0.bit.DBL1
#define PDBL0_DBL0 pdbl0.bit.DBL0
__IO_EXTERN GCN20STR gcn20;
#define GCN20 gcn20.byte
#define GCN20_EN3 gcn20.bit.EN3
#define GCN20_EN2 gcn20.bit.EN2
#define GCN20_EN1 gcn20.bit.EN1
#define GCN20_EN0 gcn20.bit.EN0
__IO_EXTERN GCN11STR gcn11;
#define GCN11 gcn11.word
#define GCN11_TSEL73 gcn11.bit.TSEL73
#define GCN11_TSEL72 gcn11.bit.TSEL72
#define GCN11_TSEL71 gcn11.bit.TSEL71
#define GCN11_TSEL70 gcn11.bit.TSEL70
#define GCN11_TSEL63 gcn11.bit.TSEL63
#define GCN11_TSEL62 gcn11.bit.TSEL62
#define GCN11_TSEL61 gcn11.bit.TSEL61
#define GCN11_TSEL60 gcn11.bit.TSEL60
#define GCN11_TSEL53 gcn11.bit.TSEL53
#define GCN11_TSEL52 gcn11.bit.TSEL52
#define GCN11_TSEL51 gcn11.bit.TSEL51
#define GCN11_TSEL50 gcn11.bit.TSEL50
#define GCN11_TSEL43 gcn11.bit.TSEL43
#define GCN11_TSEL42 gcn11.bit.TSEL42
#define GCN11_TSEL41 gcn11.bit.TSEL41
#define GCN11_TSEL40 gcn11.bit.TSEL40
__IO_EXTERN PDBL1STR pdbl1;
#define PDBL1 pdbl1.byte
#define PDBL1_DBC1 pdbl1.bit.DBC1
#define PDBL1_DBL7 pdbl1.bit.DBL7
#define PDBL1_DBL6 pdbl1.bit.DBL6
#define PDBL1_DBL5 pdbl1.bit.DBL5
#define PDBL1_DBL4 pdbl1.bit.DBL4
__IO_EXTERN GCN21STR gcn21;
#define GCN21 gcn21.byte
#define GCN21_EN3 gcn21.bit.EN3
#define GCN21_EN2 gcn21.bit.EN2
#define GCN21_EN1 gcn21.bit.EN1
#define GCN21_EN0 gcn21.bit.EN0
__IO_EXTERN IO_WORD ptmr0;   /* PWM0 */
#define PTMR0 ptmr0
__IO_EXTERN IO_WORD pcsr0;
#define PCSR0 pcsr0
__IO_EXTERN IO_WORD pdut0;
#define PDUT0 pdut0
__IO_EXTERN PCNH0STR pcnh0;
#define PCNH0 pcnh0.byte
#define PCNH0_CNTE pcnh0.bit.CNTE
#define PCNH0_STGR pcnh0.bit.STGR
#define PCNH0_MDSE pcnh0.bit.MDSE
#define PCNH0_RTRG pcnh0.bit.RTRG
#define PCNH0_CKS1 pcnh0.bit.CKS1
#define PCNH0_CKS0 pcnh0.bit.CKS0
#define PCNH0_PGMS pcnh0.bit.PGMS
__IO_EXTERN PCNL0STR pcnl0;
#define PCNL0 pcnl0.byte
#define PCNL0_EGS1 pcnl0.bit.EGS1
#define PCNL0_EGS0 pcnl0.bit.EGS0
#define PCNL0_IREN pcnl0.bit.IREN
#define PCNL0_IRQF pcnl0.bit.IRQF
#define PCNL0_IRS1 pcnl0.bit.IRS1
#define PCNL0_IRS0 pcnl0.bit.IRS0
#define PCNL0_OSEL pcnl0.bit.OSEL
__IO_EXTERN IO_WORD ptmr1;   /* PWM1 */
#define PTMR1 ptmr1
__IO_EXTERN IO_WORD pcsr1;
#define PCSR1 pcsr1
__IO_EXTERN IO_WORD pdut1;
#define PDUT1 pdut1
__IO_EXTERN PCNH1STR pcnh1;
#define PCNH1 pcnh1.byte
#define PCNH1_CNTE pcnh1.bit.CNTE
#define PCNH1_STGR pcnh1.bit.STGR
#define PCNH1_MDSE pcnh1.bit.MDSE
#define PCNH1_RTRG pcnh1.bit.RTRG
#define PCNH1_CKS1 pcnh1.bit.CKS1
#define PCNH1_CKS0 pcnh1.bit.CKS0
#define PCNH1_PGMS pcnh1.bit.PGMS
__IO_EXTERN PCNL1STR pcnl1;
#define PCNL1 pcnl1.byte
#define PCNL1_EGS1 pcnl1.bit.EGS1
#define PCNL1_EGS0 pcnl1.bit.EGS0
#define PCNL1_IREN pcnl1.bit.IREN
#define PCNL1_IRQF pcnl1.bit.IRQF
#define PCNL1_IRS1 pcnl1.bit.IRS1
#define PCNL1_IRS0 pcnl1.bit.IRS0
#define PCNL1_OSEL pcnl1.bit.OSEL
__IO_EXTERN IO_WORD ptmr2;   /* PWM2 */
#define PTMR2 ptmr2
__IO_EXTERN IO_WORD pcsr2;
#define PCSR2 pcsr2
__IO_EXTERN IO_WORD pdut2;
#define PDUT2 pdut2
__IO_EXTERN PCNH2STR pcnh2;
#define PCNH2 pcnh2.byte
#define PCNH2_CNTE pcnh2.bit.CNTE
#define PCNH2_STGR pcnh2.bit.STGR
#define PCNH2_MDSE pcnh2.bit.MDSE
#define PCNH2_RTRG pcnh2.bit.RTRG
#define PCNH2_CKS1 pcnh2.bit.CKS1
#define PCNH2_CKS0 pcnh2.bit.CKS0
#define PCNH2_PGMS pcnh2.bit.PGMS
__IO_EXTERN PCNL2STR pcnl2;
#define PCNL2 pcnl2.byte
#define PCNL2_EGS1 pcnl2.bit.EGS1
#define PCNL2_EGS0 pcnl2.bit.EGS0
#define PCNL2_IREN pcnl2.bit.IREN
#define PCNL2_IRQF pcnl2.bit.IRQF
#define PCNL2_IRS1 pcnl2.bit.IRS1
#define PCNL2_IRS0 pcnl2.bit.IRS0
#define PCNL2_OSEL pcnl2.bit.OSEL
__IO_EXTERN IO_WORD ptmr3;   /* PWM3 */
#define PTMR3 ptmr3
__IO_EXTERN IO_WORD pcsr3;
#define PCSR3 pcsr3
__IO_EXTERN IO_WORD pdut3;
#define PDUT3 pdut3
__IO_EXTERN PCNH3STR pcnh3;
#define PCNH3 pcnh3.byte
#define PCNH3_CNTE pcnh3.bit.CNTE
#define PCNH3_STGR pcnh3.bit.STGR
#define PCNH3_MDSE pcnh3.bit.MDSE
#define PCNH3_RTRG pcnh3.bit.RTRG
#define PCNH3_CKS1 pcnh3.bit.CKS1
#define PCNH3_CKS0 pcnh3.bit.CKS0
#define PCNH3_PGMS pcnh3.bit.PGMS
__IO_EXTERN PCNL3STR pcnl3;
#define PCNL3 pcnl3.byte
#define PCNL3_EGS1 pcnl3.bit.EGS1
#define PCNL3_EGS0 pcnl3.bit.EGS0
#define PCNL3_IREN pcnl3.bit.IREN
#define PCNL3_IRQF pcnl3.bit.IRQF
#define PCNL3_IRS1 pcnl3.bit.IRS1
#define PCNL3_IRS0 pcnl3.bit.IRS0
#define PCNL3_OSEL pcnl3.bit.OSEL
__IO_EXTERN IO_WORD ptmr4;   /* PWM4 */
#define PTMR4 ptmr4
__IO_EXTERN IO_WORD pcsr4;
#define PCSR4 pcsr4
__IO_EXTERN IO_WORD pdut4;
#define PDUT4 pdut4
__IO_EXTERN PCNH4STR pcnh4;
#define PCNH4 pcnh4.byte
#define PCNH4_CNTE pcnh4.bit.CNTE
#define PCNH4_STGR pcnh4.bit.STGR
#define PCNH4_MDSE pcnh4.bit.MDSE
#define PCNH4_RTRG pcnh4.bit.RTRG
#define PCNH4_CKS1 pcnh4.bit.CKS1
#define PCNH4_CKS0 pcnh4.bit.CKS0
#define PCNH4_PGMS pcnh4.bit.PGMS
__IO_EXTERN PCNL4STR pcnl4;
#define PCNL4 pcnl4.byte
#define PCNL4_EGS1 pcnl4.bit.EGS1
#define PCNL4_EGS0 pcnl4.bit.EGS0
#define PCNL4_IREN pcnl4.bit.IREN
#define PCNL4_IRQF pcnl4.bit.IRQF
#define PCNL4_IRS1 pcnl4.bit.IRS1
#define PCNL4_IRS0 pcnl4.bit.IRS0
#define PCNL4_OSEL pcnl4.bit.OSEL
__IO_EXTERN IO_WORD ptmr5;   /* PWM5 */
#define PTMR5 ptmr5
__IO_EXTERN IO_WORD pcsr5;
#define PCSR5 pcsr5
__IO_EXTERN IO_WORD pdut5;
#define PDUT5 pdut5
__IO_EXTERN PCNH5STR pcnh5;
#define PCNH5 pcnh5.byte
#define PCNH5_CNTE pcnh5.bit.CNTE
#define PCNH5_STGR pcnh5.bit.STGR
#define PCNH5_MDSE pcnh5.bit.MDSE
#define PCNH5_RTRG pcnh5.bit.RTRG
#define PCNH5_CKS1 pcnh5.bit.CKS1
#define PCNH5_CKS0 pcnh5.bit.CKS0
#define PCNH5_PGMS pcnh5.bit.PGMS
__IO_EXTERN PCNL5STR pcnl5;
#define PCNL5 pcnl5.byte
#define PCNL5_EGS1 pcnl5.bit.EGS1
#define PCNL5_EGS0 pcnl5.bit.EGS0
#define PCNL5_IREN pcnl5.bit.IREN
#define PCNL5_IRQF pcnl5.bit.IRQF
#define PCNL5_IRS1 pcnl5.bit.IRS1
#define PCNL5_IRS0 pcnl5.bit.IRS0
#define PCNL5_OSEL pcnl5.bit.OSEL
__IO_EXTERN IO_WORD ptmr6;   /* PWM6 */
#define PTMR6 ptmr6
__IO_EXTERN IO_WORD pcsr6;
#define PCSR6 pcsr6
__IO_EXTERN IO_WORD pdut6;
#define PDUT6 pdut6
__IO_EXTERN PCNH6STR pcnh6;
#define PCNH6 pcnh6.byte
#define PCNH6_CNTE pcnh6.bit.CNTE
#define PCNH6_STGR pcnh6.bit.STGR
#define PCNH6_MDSE pcnh6.bit.MDSE
#define PCNH6_RTRG pcnh6.bit.RTRG
#define PCNH6_CKS1 pcnh6.bit.CKS1
#define PCNH6_CKS0 pcnh6.bit.CKS0
#define PCNH6_PGMS pcnh6.bit.PGMS
__IO_EXTERN PCNL6STR pcnl6;
#define PCNL6 pcnl6.byte
#define PCNL6_EGS1 pcnl6.bit.EGS1
#define PCNL6_EGS0 pcnl6.bit.EGS0
#define PCNL6_IREN pcnl6.bit.IREN
#define PCNL6_IRQF pcnl6.bit.IRQF
#define PCNL6_IRS1 pcnl6.bit.IRS1
#define PCNL6_IRS0 pcnl6.bit.IRS0
#define PCNL6_OSEL pcnl6.bit.OSEL
__IO_EXTERN IO_WORD ptmr7;   /* PWM7 */
#define PTMR7 ptmr7
__IO_EXTERN IO_WORD pcsr7;
#define PCSR7 pcsr7
__IO_EXTERN IO_WORD pdut7;
#define PDUT7 pdut7
__IO_EXTERN PCNH7STR pcnh7;
#define PCNH7 pcnh7.byte
#define PCNH7_CNTE pcnh7.bit.CNTE
#define PCNH7_STGR pcnh7.bit.STGR
#define PCNH7_MDSE pcnh7.bit.MDSE
#define PCNH7_RTRG pcnh7.bit.RTRG
#define PCNH7_CKS1 pcnh7.bit.CKS1
#define PCNH7_CKS0 pcnh7.bit.CKS0
#define PCNH7_PGMS pcnh7.bit.PGMS
__IO_EXTERN PCNL7STR pcnl7;
#define PCNL7 pcnl7.byte
#define PCNL7_EGS1 pcnl7.bit.EGS1
#define PCNL7_EGS0 pcnl7.bit.EGS0
#define PCNL7_IREN pcnl7.bit.IREN
#define PCNL7_IRQF pcnl7.bit.IRQF
#define PCNL7_IRS1 pcnl7.bit.IRS1
#define PCNL7_IRS0 pcnl7.bit.IRS0
#define PCNL7_OSEL pcnl7.bit.OSEL
__IO_EXTERN IO_WORD cmcr;   /* ClockM */
#define CMCR cmcr
__IO_EXTERN IO_WORD cmpr;
#define CMPR cmpr
__IO_EXTERN IO_WORD cmls0;
#define CMLS0 cmls0
__IO_EXTERN IO_WORD cmls1;
#define CMLS1 cmls1
__IO_EXTERN IO_WORD cmls2;
#define CMLS2 cmls2
__IO_EXTERN IO_WORD cmls3;
#define CMLS3 cmls3
__IO_EXTERN IO_WORD cmlt0;
#define CMLT0 cmlt0
__IO_EXTERN IO_WORD cmlt1;
#define CMLT1 cmlt1
__IO_EXTERN IO_WORD cmlt2;
#define CMLT2 cmlt2
__IO_EXTERN IO_WORD cmlt3;
#define CMLT3 cmlt3
__IO_EXTERN IO_WORD cmac;
#define CMAC cmac
__IO_EXTERN PDRCRSTR pdrcr;   /* Power Down Reset */
#define PDRCR pdrcr.byte
#define PDRCR_CDSBLE pdrcr.bit.CDSBLE
#define PDRCR_PD pdrcr.bit.PD
#define PDRCR_EN pdrcr.bit.EN
__IO_EXTERN ACCDBLSTR accdbl;   /* Alarm Comparator */
#define ACCDBL accdbl.byte
#define ACCDBL_CDBLE accdbl.bit.CDBLE
__IO_EXTERN ACSRSTR acsr;
#define ACSR acsr.byte
#define ACSR_OUT2 acsr.bit.OUT2
#define ACSR_OUT1 acsr.bit.OUT1
#define ACSR_IRQ acsr.bit.IRQ
#define ACSR_IEN acsr.bit.IEN
#define ACSR_PD acsr.bit.PD
__IO_EXTERN IBCR2STR ibcr2;   /* I2C */
#define IBCR2 ibcr2.byte
#define IBCR2_BER ibcr2.bit.BER
#define IBCR2_BEIE ibcr2.bit.BEIE
#define IBCR2_SCC ibcr2.bit.SCC
#define IBCR2_MSS ibcr2.bit.MSS
#define IBCR2_ACK ibcr2.bit.ACK
#define IBCR2_GCAA ibcr2.bit.GCAA
#define IBCR2_INTE ibcr2.bit.INTE
#define IBCR2_INT ibcr2.bit.INT
__IO_EXTERN IBSR2STR ibsr2;
#define IBSR2 ibsr2.byte
#define IBSR2_BB ibsr2.bit.BB
#define IBSR2_RSC ibsr2.bit.RSC
#define IBSR2_AL ibsr2.bit.AL
#define IBSR2_LRB ibsr2.bit.LRB
#define IBSR2_TRX ibsr2.bit.TRX
#define IBSR2_AAS ibsr2.bit.AAS
#define IBSR2_GCA ibsr2.bit.GCA
#define IBSR2_ADT ibsr2.bit.ADT
__IO_EXTERN ITBAH2STR itbah2;
#define ITBAH2 itbah2.byte
#define ITBAH2_TA9 itbah2.bit.TA9
#define ITBAH2_TA8 itbah2.bit.TA8
__IO_EXTERN ITBAL2STR itbal2;
#define ITBAL2 itbal2.byte
#define ITBAL2_TA7 itbal2.bit.TA7
#define ITBAL2_TA6 itbal2.bit.TA6
#define ITBAL2_TA5 itbal2.bit.TA5
#define ITBAL2_TA4 itbal2.bit.TA4
#define ITBAL2_TA3 itbal2.bit.TA3
#define ITBAL2_TA2 itbal2.bit.TA2
#define ITBAL2_TA1 itbal2.bit.TA1
#define ITBAL2_TA0 itbal2.bit.TA0
__IO_EXTERN ITMKH2STR itmkh2;
#define ITMKH2 itmkh2.byte
#define ITMKH2_ENTB itmkh2.bit.ENTB
#define ITMKH2_RAL itmkh2.bit.RAL
#define ITMKH2_TM9 itmkh2.bit.TM9
#define ITMKH2_TM8 itmkh2.bit.TM8
__IO_EXTERN ITMKL2STR itmkl2;
#define ITMKL2 itmkl2.byte
#define ITMKL2_TM7 itmkl2.bit.TM7
#define ITMKL2_TM6 itmkl2.bit.TM6
#define ITMKL2_TM5 itmkl2.bit.TM5
#define ITMKL2_TM4 itmkl2.bit.TM4
#define ITMKL2_TM3 itmkl2.bit.TM3
#define ITMKL2_TM2 itmkl2.bit.TM2
#define ITMKL2_TM1 itmkl2.bit.TM1
#define ITMKL2_TM0 itmkl2.bit.TM0
__IO_EXTERN ISMK2STR ismk2;
#define ISMK2 ismk2.byte
#define ISMK2_ENSB ismk2.bit.ENSB
#define ISMK2_SM6 ismk2.bit.SM6
#define ISMK2_SM5 ismk2.bit.SM5
#define ISMK2_SM4 ismk2.bit.SM4
#define ISMK2_SM3 ismk2.bit.SM3
#define ISMK2_SM2 ismk2.bit.SM2
#define ISMK2_SM1 ismk2.bit.SM1
#define ISMK2_SM0 ismk2.bit.SM0
__IO_EXTERN ISBA2STR isba2;
#define ISBA2 isba2.byte
#define ISBA2_SA6 isba2.bit.SA6
#define ISBA2_SA5 isba2.bit.SA5
#define ISBA2_SA4 isba2.bit.SA4
#define ISBA2_SA3 isba2.bit.SA3
#define ISBA2_SA2 isba2.bit.SA2
#define ISBA2_SA1 isba2.bit.SA1
#define ISBA2_SA0 isba2.bit.SA0
__IO_EXTERN IO_BYTE idar2;
#define IDAR2 idar2
__IO_EXTERN ICCR2STR iccr2;
#define ICCR2 iccr2.byte
#define ICCR2_NSF iccr2.bit.NSF
#define ICCR2_EN iccr2.bit.EN
#define ICCR2_CS4 iccr2.bit.CS4
#define ICCR2_CS3 iccr2.bit.CS3
#define ICCR2_CS2 iccr2.bit.CS2
#define ICCR2_CS1 iccr2.bit.CS1
#define ICCR2_CS0 iccr2.bit.CS0
__IO_EXTERN IDBL2STR idbl2;
#define IDBL2 idbl2.byte
#define IDBL2_DBL idbl2.bit.DBL
__IO_EXTERN F362MDSTR f362md;   /* MODE REGISTER */
#define F362MD f362md.byte
#define F362MD_FMD7 f362md.bit.FMD7
#define F362MD_FMD6 f362md.bit.FMD6
#define F362MD_FMD5 f362md.bit.FMD5
#define F362MD_FMD4 f362md.bit.FMD4
#define F362MD_FMD3 f362md.bit.FMD3
#define F362MD_FMD2 f362md.bit.FMD2
#define F362MD_FMD1 f362md.bit.FMD1
#define F362MD_FMD0 f362md.bit.FMD0
__IO_EXTERN IO_LWORD dmaca0;   /* DMAC */
#define DMACA0 dmaca0
__IO_EXTERN IO_LWORD dmacb0;
#define DMACB0 dmacb0
__IO_EXTERN IO_LWORD dmaca1;
#define DMACA1 dmaca1
__IO_EXTERN IO_LWORD dmacb1;
#define DMACB1 dmacb1
__IO_EXTERN IO_LWORD dmaca2;
#define DMACA2 dmaca2
__IO_EXTERN IO_LWORD dmacb2;
#define DMACB2 dmacb2
__IO_EXTERN IO_LWORD dmaca3;
#define DMACA3 dmaca3
__IO_EXTERN IO_LWORD dmacb3;
#define DMACB3 dmacb3
__IO_EXTERN IO_LWORD dmaca4;
#define DMACA4 dmaca4
__IO_EXTERN IO_LWORD dmacb4;
#define DMACB4 dmacb4
__IO_EXTERN IO_BYTE dmacr;   /* DMAC CNTL */
#define DMACR dmacr
__IO_EXTERN IO_LWORD irbs;   /* Instruction Cache */
#define IRBS irbs
__IO_EXTERN IO_BYTE isize;
#define ISIZE isize
__IO_EXTERN IO_BYTE ichcr;
#define ICHCR ichcr
__IO_EXTERN IO_LWORD bsd0;   /* Bit Search Module */
#define BSD0 bsd0
__IO_EXTERN IO_LWORD bsd1;
#define BSD1 bsd1
__IO_EXTERN IO_LWORD bsdc;
#define BSDC bsdc
__IO_EXTERN IO_LWORD bsrr;
#define BSRR bsrr
__IO_EXTERN DDR0STR ddr0;   /* Port Direction Register */
#define DDR0 ddr0.byte
#define DDR0_DD07 ddr0.bit.DD07
#define DDR0_DD06 ddr0.bit.DD06
#define DDR0_DD05 ddr0.bit.DD05
#define DDR0_DD04 ddr0.bit.DD04
#define DDR0_DD03 ddr0.bit.DD03
#define DDR0_DD02 ddr0.bit.DD02
#define DDR0_DD01 ddr0.bit.DD01
#define DDR0_DD00 ddr0.bit.DD00
__IO_EXTERN DDR1STR ddr1;
#define DDR1 ddr1.byte
#define DDR1_DD17 ddr1.bit.DD17
#define DDR1_DD16 ddr1.bit.DD16
#define DDR1_DD15 ddr1.bit.DD15
#define DDR1_DD14 ddr1.bit.DD14
#define DDR1_DD13 ddr1.bit.DD13
#define DDR1_DD12 ddr1.bit.DD12
#define DDR1_DD11 ddr1.bit.DD11
#define DDR1_DD10 ddr1.bit.DD10
__IO_EXTERN DDR2STR ddr2;
#define DDR2 ddr2.byte
#define DDR2_DD27 ddr2.bit.DD27
#define DDR2_DD26 ddr2.bit.DD26
#define DDR2_DD25 ddr2.bit.DD25
#define DDR2_DD24 ddr2.bit.DD24
#define DDR2_DD23 ddr2.bit.DD23
#define DDR2_DD22 ddr2.bit.DD22
#define DDR2_DD21 ddr2.bit.DD21
#define DDR2_DD20 ddr2.bit.DD20
__IO_EXTERN DDR3STR ddr3;
#define DDR3 ddrg.byte
#define DDR3_DD37 ddr3.bit.DD37
#define DDR3_DD36 ddr3.bit.DD36
#define DDR3_DD35 ddr3.bit.DD35
#define DDR3_DD34 ddr3.bit.DD34
#define DDR3_DD33 ddr3.bit.DD33
#define DDR3_DD32 ddr3.bit.DD32
#define DDR3_DD31 ddr3.bit.DD31
#define DDR3_DD30 ddr3.bit.DD30
__IO_EXTERN DDR4STR ddr4;
#define DDR4 ddr4.byte
#define DDR4_DD47 ddr4.bit.DD47
#define DDR4_DD46 ddr4.bit.DD46
#define DDR4_DD45 ddr4.bit.DD45
#define DDR4_DD44 ddr4.bit.DD44
#define DDR4_DD43 ddr4.bit.DD43
#define DDR4_DD42 ddr4.bit.DD42
#define DDR4_DD41 ddr4.bit.DD41
#define DDR4_DD40 ddr4.bit.DD40
__IO_EXTERN DDR5STR ddr5;
#define DDR5 ddr5.byte
#define DDR5_DD57 ddr5.bit.DD57
#define DDR5_DD56 ddr5.bit.DD56
#define DDR5_DD55 ddr5.bit.DD55
#define DDR5_DD54 ddr5.bit.DD54
#define DDR5_DD53 ddr5.bit.DD53
#define DDR5_DD52 ddr5.bit.DD52
#define DDR5_DD51 ddr5.bit.DD51
#define DDR5_DD50 ddr5.bit.DD50
__IO_EXTERN DDR6STR ddr6;
#define DDR6 ddr6.byte
#define DDR6_DD64 ddr6.bit.DD64
#define DDR6_DD63 ddr6.bit.DD63
#define DDR6_DD62 ddr6.bit.DD62
#define DDR6_DD61 ddr6.bit.DD61
#define DDR6_DD60 ddr6.bit.DD60
__IO_EXTERN DDR7STR ddr7;
#define DDR7 ddr7.byte
#define DDR7_DD76 ddr7.bit.DD76
#define DDR7_DD75 ddr7.bit.DD75
#define DDR7_DD74 ddr7.bit.DD74
__IO_EXTERN DDR8STR ddr8;
#define DDR8 ddr8.byte
#define DDR8_DD82 ddr8.bit.DD82
#define DDR8_DD81 ddr8.bit.DD81
__IO_EXTERN DDR9STR ddr9;
#define DDR9 ddr9.byte
#define DDR9_DD97 ddr9.bit.DD97
#define DDR9_DD96 ddr9.bit.DD96
#define DDR9_DD93 ddr9.bit.DD93
#define DDR9_DD92 ddr9.bit.DD92
#define DDR9_DD91 ddr9.bit.DD91
#define DDR9_DD90 ddr9.bit.DD90
__IO_EXTERN DDRBSTR ddrb;
#define DDRB ddrb.byte
#define DDRB_DDB2 ddrb.bit.DDB2
#define DDRB_DDB1 ddrb.bit.DDB1
#define DDRB_DDB0 ddrb.bit.DDB0
__IO_EXTERN DDRGSTR ddrg;
#define DDRG ddrg.byte
#define DDRG_DDG7 ddrg.bit.DDG7
#define DDRG_DDG6 ddrg.bit.DDG6
#define DDRG_DDG5 ddrg.bit.DDG5
#define DDRG_DDG4 ddrg.bit.DDG4
#define DDRG_DDG3 ddrg.bit.DDG3
#define DDRG_DDG2 ddrg.bit.DDG2
#define DDRG_DDG1 ddrg.bit.DDG1
#define DDRG_DDG0 ddrg.bit.DDG0
__IO_EXTERN DDRHSTR ddrh;
#define DDRH ddrh.byte
#define DDRH_DDH7 ddrh.bit.DDH7
#define DDRH_DDH6 ddrh.bit.DDH6
#define DDRH_DDH5 ddrh.bit.DDH5
#define DDRH_DDH4 ddrh.bit.DDH4
#define DDRH_DDH3 ddrh.bit.DDH3
#define DDRH_DDH2 ddrh.bit.DDH2
#define DDRH_DDH1 ddrh.bit.DDH1
#define DDRH_DDH0 ddrh.bit.DDH0
__IO_EXTERN DDRISTR ddri;
#define DDRI ddri.byte
#define DDRI_DDI3 ddri.bit.DDI3
__IO_EXTERN DDRJSTR ddrj;
#define DDRJ ddrj.byte
#define DDRJ_DDJ7 ddrj.bit.DDJ7
#define DDRJ_DDJ6 ddrj.bit.DDJ6
#define DDRJ_DDJ5 ddrj.bit.DDJ5
#define DDRJ_DDJ4 ddrj.bit.DDJ4
#define DDRJ_DDJ3 ddrj.bit.DDJ3
#define DDRJ_DDJ2 ddrj.bit.DDJ2
#define DDRJ_DDJ1 ddrj.bit.DDJ1
#define DDRJ_DDJ0 ddrj.bit.DDJ0
__IO_EXTERN DDRKSTR ddrk;
#define DDRK ddrk.byte
#define DDRK_DDK7 ddrk.bit.DDK7
#define DDRK_DDK6 ddrk.bit.DDK6
#define DDRK_DDK5 ddrk.bit.DDK5
#define DDRK_DDK4 ddrk.bit.DDK4
#define DDRK_DDK3 ddrk.bit.DDK3
#define DDRK_DDK2 ddrk.bit.DDK2
#define DDRK_DDK1 ddrk.bit.DDK1
#define DDRK_DDK0 ddrk.bit.DDK0
__IO_EXTERN DDRLSTR ddrl;
#define DDRL ddrl.byte
#define DDRL_DDL7 ddrl.bit.DDL7
#define DDRL_DDL6 ddrl.bit.DDL6
#define DDRL_DDL5 ddrl.bit.DDL5
#define DDRL_DDL4 ddrl.bit.DDL4
#define DDRL_DDL3 ddrl.bit.DDL3
#define DDRL_DDL2 ddrl.bit.DDL2
#define DDRL_DDL1 ddrl.bit.DDL1
#define DDRL_DDL0 ddrl.bit.DDL0
__IO_EXTERN DDRMSTR ddrm;
#define DDRM ddrm.byte
#define DDRM_DDM3 ddrm.bit.DDM3
#define DDRM_DDM2 ddrm.bit.DDM2
#define DDRM_DDM1 ddrm.bit.DDM1
#define DDRM_DDM0 ddrm.bit.DDM0
__IO_EXTERN DDRNSTR ddrn;
#define DDRN ddrn.byte
#define DDRN_DDN5 ddrn.bit.DDN5
#define DDRN_DDN4 ddrn.bit.DDN4
#define DDRN_DDN3 ddrn.bit.DDN3
#define DDRN_DDN2 ddrn.bit.DDN2
#define DDRN_DDN1 ddrn.bit.DDN1
#define DDRN_DDN0 ddrn.bit.DDN0
__IO_EXTERN DDROSTR ddro;
#define DDRO ddro.byte
#define DDRO_DDO7 ddro.bit.DDO7
#define DDRO_DDO6 ddro.bit.DDO6
#define DDRO_DDO5 ddro.bit.DDO5
#define DDRO_DDO4 ddro.bit.DDO4
#define DDRO_DDO3 ddro.bit.DDO3
#define DDRO_DDO2 ddro.bit.DDO2
#define DDRO_DDO1 ddro.bit.DDO1
#define DDRO_DDO0 ddro.bit.DDO0
__IO_EXTERN DDRPSTR ddrp;
#define DDRP ddrp.byte
#define DDRP_DDP5 ddrp.bit.DDP5
#define DDRP_DDP4 ddrp.bit.DDP4
#define DDRP_DDP3 ddrp.bit.DDP3
#define DDRP_DDP2 ddrp.bit.DDP2
#define DDRP_DDP1 ddrp.bit.DDP1
#define DDRP_DDP0 ddrp.bit.DDP0
__IO_EXTERN DDRQSTR ddrq;
#define DDRQ ddrq.byte
#define DDRQ_DDQ5 ddrq.bit.DDQ5
#define DDRQ_DDQ4 ddrq.bit.DDQ4
#define DDRQ_DDQ3 ddrq.bit.DDQ3
#define DDRQ_DDQ2 ddrq.bit.DDQ2
#define DDRQ_DDQ1 ddrq.bit.DDQ1
#define DDRQ_DDQ0 ddrq.bit.DDQ0
__IO_EXTERN DDRRSTR ddrr;
#define DDRR ddrr.byte
#define DDRR_DR7 ddrr.bit.DR7
#define DDRR_DR6 ddrr.bit.DR6
#define DDRR_DR5 ddrr.bit.DR5
#define DDRR_DR4 ddrr.bit.DR4
#define DDRR_DR3 ddrr.bit.DR3
#define DDRR_DR2 ddrr.bit.DR2
#define DDRR_DR1 ddrr.bit.DR1
#define DDRR_DR0 ddrr.bit.DR0
__IO_EXTERN DDRSSTR ddrs;
#define DDRS ddrs.byte
#define DDRS_DDS7 ddrs.bit.DDS7
#define DDRS_DDS6 ddrs.bit.DDS6
#define DDRS_DDS5 ddrs.bit.DDS5
#define DDRS_DDS4 ddrs.bit.DDS4
#define DDRS_DDS3 ddrs.bit.DDS3
#define DDRS_DDS2 ddrs.bit.DDS2
#define DDRS_DDS1 ddrs.bit.DDS1
#define DDRS_DDS0 ddrs.bit.DDS0
__IO_EXTERN PFR0STR pfr0;   /* Port Function Register */
#define PFR0 pfr0.byte
#define PFR0_PF07 pfr0.bit.PF07
#define PFR0_PF06 pfr0.bit.PF06
#define PFR0_PF05 pfr0.bit.PF05
#define PFR0_PF04 pfr0.bit.PF04
#define PFR0_PF03 pfr0.bit.PF03
#define PFR0_PF02 pfr0.bit.PF02
#define PFR0_PF01 pfr0.bit.PF01
#define PFR0_PF00 pfr0.bit.PF00
__IO_EXTERN PFR1STR pfr1;
#define PFR1 pfr1.byte
#define PFR1_PF17 pfr1.bit.PF17
#define PFR1_PF16 pfr1.bit.PF16
#define PFR1_PF15 pfr1.bit.PF15
#define PFR1_PF14 pfr1.bit.PF14
#define PFR1_PF13 pfr1.bit.PF13
#define PFR1_PF12 pfr1.bit.PF12
#define PFR1_PF11 pfr1.bit.PF11
#define PFR1_PF10 pfr1.bit.PF10
__IO_EXTERN PFR2STR pfr2;
#define PFR2 pfr2.byte
#define PFR2_PF27 pfr2.bit.PF27
#define PFR2_PF26 pfr2.bit.PF26
#define PFR2_PF25 pfr2.bit.PF25
#define PFR2_PF24 pfr2.bit.PF24
#define PFR2_PF23 pfr2.bit.PF23
#define PFR2_PF22 pfr2.bit.PF22
#define PFR2_PF21 pfr2.bit.PF21
#define PFR2_PF20 pfr2.bit.PF20
__IO_EXTERN PFR3STR pfr3;
#define PFR3 pfr3.byte
#define PFR3_PF37 pfr3.bit.PF37
#define PFR3_PF36 pfr3.bit.PF36
#define PFR3_PF35 pfr3.bit.PF35
#define PFR3_PF34 pfr3.bit.PF34
#define PFR3_PF33 pfr3.bit.PF33
#define PFR3_PF32 pfr3.bit.PF32
#define PFR3_PF31 pfr3.bit.PF31
#define PFR3_PF30 pfr3.bit.PF30
__IO_EXTERN PFR4STR pfr4;
#define PFR4 pfr4.byte
#define PFR4_PF47 pfr4.bit.PF47
#define PFR4_PF46 pfr4.bit.PF46
#define PFR4_PF45 pfr4.bit.PF45
#define PFR4_PF44 pfr4.bit.PF44
#define PFR4_PF43 pfr4.bit.PF43
#define PFR4_PF42 pfr4.bit.PF42
#define PFR4_PF41 pfr4.bit.PF41
#define PFR4_PF40 pfr4.bit.PF40
__IO_EXTERN PFR5STR pfr5;
#define PFR5 pfr5.byte
#define PFR5_PF57 pfr5.bit.PF57
#define PFR5_PF56 pfr5.bit.PF56
#define PFR5_PF55 pfr5.bit.PF55
#define PFR5_PF54 pfr5.bit.PF54
#define PFR5_PF53 pfr5.bit.PF53
#define PFR5_PF52 pfr5.bit.PF52
#define PFR5_PF51 pfr5.bit.PF51
#define PFR5_PF50 pfr5.bit.PF50
__IO_EXTERN PFR6STR pfr6;
#define PFR6 pfr6.byte
#define PFR6_PF64 pfr6.bit.PF64
#define PFR6_PF63 pfr6.bit.PF63
#define PFR6_PF62 pfr6.bit.PF62
#define PFR6_PF61 pfr6.bit.PF61
#define PFR6_PF60 pfr6.bit.PF60
__IO_EXTERN PFR7STR pfr7;
#define PFR7 pfr7.byte
#define PFR7_PF76 pfr7.bit.PF76
#define PFR7_PF75 pfr7.bit.PF75
#define PFR7_PF74 pfr7.bit.PF74
__IO_EXTERN PFR8STR pfr8;
#define PFR8 pfr8.byte
#define PFR8_PF82 pfr8.bit.PF82
#define PFR8_PF81 pfr8.bit.PF81
__IO_EXTERN PFR9STR pfr9;
#define PFR9 pfr9.byte
#define PFR9_PF97 pfr9.bit.PF97
#define PFR9_PF96 pfr9.bit.PF96
#define PFR9_PF93 pfr9.bit.PF93
#define PFR9_PF92 pfr9.bit.PF92
#define PFR9_PF91 pfr9.bit.PF91
#define PFR9_PF90 pfr9.bit.PF90
__IO_EXTERN PFRBSTR pfrb;
#define PFRB pfrb.byte
#define PFRB_PFB2 pfrb.bit.PFB2
#define PFRB_PFB1 pfrb.bit.PFB1
#define PFRB_PFB0 pfrb.bit.PFB0
__IO_EXTERN IO_BYTE pfr27;
#define PFR27 pfr27
__IO_EXTERN PFRGSTR pfrg;   /* Port Function Register */
#define PFRG pfrg.byte
#define PFRG_PFG7 pfrg.bit.PFG7
#define PFRG_PFG6 pfrg.bit.PFG6
#define PFRG_PFG5 pfrg.bit.PFG5
#define PFRG_PFG4 pfrg.bit.PFG4
#define PFRG_PFG3 pfrg.bit.PFG3
#define PFRG_PFG2 pfrg.bit.PFG2
#define PFRG_PFG1 pfrg.bit.PFG1
#define PFRG_PFG0 pfrg.bit.PFG0
__IO_EXTERN PFRHSTR pfrh;
#define PFRH pfrh.byte
#define PFRH_PFH7 pfrh.bit.PFH7
#define PFRH_PFH6 pfrh.bit.PFH6
#define PFRH_PFH5 pfrh.bit.PFH5
#define PFRH_PFH4 pfrh.bit.PFH4
#define PFRH_PFH3 pfrh.bit.PFH3
#define PFRH_PFH2 pfrh.bit.PFH2
#define PFRH_PFH1 pfrh.bit.PFH1
#define PFRH_PFH0 pfrh.bit.PFH0
__IO_EXTERN PFRISTR pfri;
#define PFRI pfri.byte
#define PFRI_PFI3 pfri.bit.PFI3
__IO_EXTERN PFRJSTR pfrj;
#define PFRJ pfrj.byte
#define PFRJ_PFJ7 pfrj.bit.PFJ7
#define PFRJ_PFJ6 pfrj.bit.PFJ6
#define PFRJ_PFJ5 pfrj.bit.PFJ5
#define PFRJ_PFJ4 pfrj.bit.PFJ4
#define PFRJ_PFJ3 pfrj.bit.PFJ3
#define PFRJ_PFJ2 pfrj.bit.PFJ2
#define PFRJ_PFJ1 pfrj.bit.PFJ1
#define PFRJ_PFJ0 pfrj.bit.PFJ0
__IO_EXTERN PFRKSTR pfrk;
#define PFRK pfrk.byte
#define PFRK_PFK7 pfrk.bit.PFK7
#define PFRK_PFK6 pfrk.bit.PFK6
#define PFRK_PFK5 pfrk.bit.PFK5
#define PFRK_PFK4 pfrk.bit.PFK4
#define PFRK_PFK3 pfrk.bit.PFK3
#define PFRK_PFK2 pfrk.bit.PFK2
#define PFRK_PFK1 pfrk.bit.PFK1
#define PFRK_PFK0 pfrk.bit.PFK0
__IO_EXTERN PFRLSTR pfrl;
#define PFRL pfrl.byte
#define PFRL_PFL7 pfrl.bit.PFL7
#define PFRL_PFL6 pfrl.bit.PFL6
#define PFRL_PFL5 pfrl.bit.PFL5
#define PFRL_PFL4 pfrl.bit.PFL4
#define PFRL_PFL3 pfrl.bit.PFL3
#define PFRL_PFL2 pfrl.bit.PFL2
#define PFRL_PFL1 pfrl.bit.PFL1
#define PFRL_PFL0 pfrl.bit.PFL0
__IO_EXTERN PFRMSTR pfrm;
#define PFRM pfrm.byte
#define PFRM_PFM3 pfrm.bit.PFM3
#define PFRM_PFM2 pfrm.bit.PFM2
#define PFRM_PFM1 pfrm.bit.PFM1
#define PFRM_PFM0 pfrm.bit.PFM0
__IO_EXTERN PFRNSTR pfrn;
#define PFRN pfrn.byte
#define PFRN_PFN5 pfrn.bit.PFN5
#define PFRN_PFN4 pfrn.bit.PFN4
#define PFRN_PFN3 pfrn.bit.PFN3
#define PFRN_PFN2 pfrn.bit.PFN2
#define PFRN_PFN1 pfrn.bit.PFN1
#define PFRN_PFN0 pfrn.bit.PFN0
__IO_EXTERN PFROSTR pfro;
#define PFRO pfro.byte
#define PFRO_PFO7 pfro.bit.PFO7
#define PFRO_PFO6 pfro.bit.PFO6
#define PFRO_PFO5 pfro.bit.PFO5
#define PFRO_PFO4 pfro.bit.PFO4
#define PFRO_PFO3 pfro.bit.PFO3
#define PFRO_PFO2 pfro.bit.PFO2
#define PFRO_PFO1 pfro.bit.PFO1
#define PFRO_PFO0 pfro.bit.PFO0
__IO_EXTERN PFRPSTR pfrp;
#define PFRP pfrp.byte
#define PFRP_PFP5 pfrp.bit.PFP5
#define PFRP_PFP4 pfrp.bit.PFP4
#define PFRP_PFP3 pfrp.bit.PFP3
#define PFRP_PFP2 pfrp.bit.PFP2
#define PFRP_PFP1 pfrp.bit.PFP1
#define PFRP_PFP0 pfrp.bit.PFP0
__IO_EXTERN PFRQSTR pfrq;
#define PFRQ pfrq.byte
#define PFRQ_PFQ5 pfrq.bit.PFQ5
#define PFRQ_PFQ4 pfrq.bit.PFQ4
#define PFRQ_PFQ3 pfrq.bit.PFQ3
#define PFRQ_PFQ2 pfrq.bit.PFQ2
#define PFRQ_PFQ1 pfrq.bit.PFQ1
#define PFRQ_PFQ0 pfrq.bit.PFQ0
__IO_EXTERN PFRRSTR pfrr;
#define PFRR pfrr.byte
#define PFRR_PR7 pfrr.bit.PR7
#define PFRR_PR6 pfrr.bit.PR6
#define PFRR_PR5 pfrr.bit.PR5
#define PFRR_PR4 pfrr.bit.PR4
#define PFRR_PR3 pfrr.bit.PR3
#define PFRR_PR2 pfrr.bit.PR2
#define PFRR_PR1 pfrr.bit.PR1
#define PFRR_PR0 pfrr.bit.PR0
__IO_EXTERN PFRSSTR pfrs;
#define PFRS pfrs.byte
#define PFRS_PFS7 pfrs.bit.PFS7
#define PFRS_PFS6 pfrs.bit.PFS6
#define PFRS_PFS5 pfrs.bit.PFS5
#define PFRS_PFS4 pfrs.bit.PFS4
#define PFRS_PFS3 pfrs.bit.PFS3
#define PFRS_PFS2 pfrs.bit.PFS2
#define PFRS_PFS1 pfrs.bit.PFS1
#define PFRS_PFS0 pfrs.bit.PFS0
__IO_EXTERN IO_BYTE icr00;   /* Interrupt Control Unit */
#define ICR00 icr00
__IO_EXTERN IO_BYTE icr01;
#define ICR01 icr01
__IO_EXTERN IO_BYTE icr02;
#define ICR02 icr02
__IO_EXTERN IO_BYTE icr03;
#define ICR03 icr03
__IO_EXTERN IO_BYTE icr04;
#define ICR04 icr04
__IO_EXTERN IO_BYTE icr05;
#define ICR05 icr05
__IO_EXTERN IO_BYTE icr06;
#define ICR06 icr06
__IO_EXTERN IO_BYTE icr07;
#define ICR07 icr07
__IO_EXTERN IO_BYTE icr08;
#define ICR08 icr08
__IO_EXTERN IO_BYTE icr09;
#define ICR09 icr09
__IO_EXTERN IO_BYTE icr10;
#define ICR10 icr10
__IO_EXTERN IO_BYTE icr11;
#define ICR11 icr11
__IO_EXTERN IO_BYTE icr12;
#define ICR12 icr12
__IO_EXTERN IO_BYTE icr13;
#define ICR13 icr13
__IO_EXTERN IO_BYTE icr14;
#define ICR14 icr14
__IO_EXTERN IO_BYTE icr15;
#define ICR15 icr15
__IO_EXTERN IO_BYTE icr16;
#define ICR16 icr16
__IO_EXTERN IO_BYTE icr17;
#define ICR17 icr17
__IO_EXTERN IO_BYTE icr18;
#define ICR18 icr18
__IO_EXTERN IO_BYTE icr19;
#define ICR19 icr19
__IO_EXTERN IO_BYTE icr20;
#define ICR20 icr20
__IO_EXTERN IO_BYTE icr21;
#define ICR21 icr21
__IO_EXTERN IO_BYTE icr22;
#define ICR22 icr22
__IO_EXTERN IO_BYTE icr23;
#define ICR23 icr23
__IO_EXTERN IO_BYTE icr24;
#define ICR24 icr24
__IO_EXTERN IO_BYTE icr25;
#define ICR25 icr25
__IO_EXTERN IO_BYTE icr26;
#define ICR26 icr26
__IO_EXTERN IO_BYTE icr27;
#define ICR27 icr27
__IO_EXTERN IO_BYTE icr28;
#define ICR28 icr28
__IO_EXTERN IO_BYTE icr29;
#define ICR29 icr29
__IO_EXTERN IO_BYTE icr30;
#define ICR30 icr30
__IO_EXTERN IO_BYTE icr31;
#define ICR31 icr31
__IO_EXTERN IO_BYTE icr32;
#define ICR32 icr32
__IO_EXTERN IO_BYTE icr33;
#define ICR33 icr33
__IO_EXTERN IO_BYTE icr34;
#define ICR34 icr34
__IO_EXTERN IO_BYTE icr35;
#define ICR35 icr35
__IO_EXTERN IO_BYTE icr36;
#define ICR36 icr36
__IO_EXTERN IO_BYTE icr37;
#define ICR37 icr37
__IO_EXTERN IO_BYTE icr38;
#define ICR38 icr38
__IO_EXTERN IO_BYTE icr39;
#define ICR39 icr39
__IO_EXTERN IO_BYTE icr40;
#define ICR40 icr40
__IO_EXTERN IO_BYTE icr41;
#define ICR41 icr41
__IO_EXTERN IO_BYTE icr42;
#define ICR42 icr42
__IO_EXTERN IO_BYTE icr43;
#define ICR43 icr43
__IO_EXTERN IO_BYTE icr44;
#define ICR44 icr44
__IO_EXTERN IO_BYTE icr45;
#define ICR45 icr45
__IO_EXTERN IO_BYTE icr46;
#define ICR46 icr46
__IO_EXTERN IO_BYTE icr47;
#define ICR47 icr47
__IO_EXTERN RSRRSTR rsrr;   /* Clock Control Unit */
#define RSRR rsrr.byte
#define RSRR_INIT rsrr.bit.INIT
#define RSRR_HSTB rsrr.bit.HSTB
#define RSRR_WDOG rsrr.bit.WDOG
#define RSRR_ERST rsrr.bit.ERST
#define RSRR_SRST rsrr.bit.SRST
#define RSRR_WT1 rsrr.bit.WT1
#define RSRR_WT0 rsrr.bit.WT0
__IO_EXTERN STCRSTR stcr;
#define STCR stcr.byte
#define STCR_STOP stcr.bit.STOP
#define STCR_SLEEP stcr.bit.SLEEP
#define STCR_HIZ stcr.bit.HIZ
#define STCR_SRST stcr.bit.SRST
#define STCR_OS1 stcr.bit.OS1
#define STCR_OS0 stcr.bit.OS0
#define STCR_OSCD1 stcr.bit.OSCD1
__IO_EXTERN TBCRSTR tbcr;
#define TBCR tbcr.byte
#define TBCR_TBIF tbcr.bit.TBIF
#define TBCR_TBIE tbcr.bit.TBIE
#define TBCR_TBC2 tbcr.bit.TBC2
#define TBCR_TBC1 tbcr.bit.TBC1
#define TBCR_TBC0 tbcr.bit.TBC0
#define TBCR_SYNCR tbcr.bit.SYNCR
#define TBCR_SYNCS tbcr.bit.SYNCS
__IO_EXTERN IO_BYTE ctbr;
#define CTBR ctbr
__IO_EXTERN CLKRSTR clkr;
#define CLKR clkr.byte
#define CLKR_PLL2S0 clkr.bit.PLL2S0
#define CLKR_PLL1S2 clkr.bit.PLL1S2
#define CLKR_PLL1S1 clkr.bit.PLL1S1
#define CLKR_PLL1S0 clkr.bit.PLL1S0
#define CLKR_PLL2EN clkr.bit.PLL2EN
#define CLKR_PLL1EN clkr.bit.PLL1EN
#define CLKR_CLKS1 clkr.bit.CLKS1
#define CLKR_CLKS0 clkr.bit.CLKS0
__IO_EXTERN IO_BYTE wpr;
#define WPR wpr
__IO_EXTERN IO_BYTE divr0;
#define DIVR0 divr0
__IO_EXTERN IO_BYTE divr1;
#define DIVR1 divr1
__IO_EXTERN IO_WORD asr0;   /* Chip Select Registers */
#define ASR0 asr0
__IO_EXTERN IO_WORD amr0;
#define AMR0 amr0
__IO_EXTERN IO_WORD asr1;
#define ASR1 asr1
__IO_EXTERN IO_WORD amr1;
#define AMR1 amr1
__IO_EXTERN IO_WORD asr2;
#define ASR2 asr2
__IO_EXTERN IO_WORD amr2;
#define AMR2 amr2
__IO_EXTERN IO_WORD asr3;
#define ASR3 asr3
__IO_EXTERN IO_WORD amr3;
#define AMR3 amr3
__IO_EXTERN IO_WORD asr4;
#define ASR4 asr4
__IO_EXTERN IO_WORD amr4;
#define AMR4 amr4
__IO_EXTERN IO_WORD asr5;
#define ASR5 asr5
__IO_EXTERN IO_WORD amr5;
#define AMR5 amr5
__IO_EXTERN IO_WORD asr6;
#define ASR6 asr6
__IO_EXTERN IO_WORD amr6;
#define AMR6 amr6
__IO_EXTERN IO_WORD asr7;
#define ASR7 asr7
__IO_EXTERN IO_WORD amr7;
#define AMR7 amr7
__IO_EXTERN IO_BYTE amd0;
#define AMD0 amd0
__IO_EXTERN IO_BYTE amd1;
#define AMD1 amd1
__IO_EXTERN IO_BYTE amd2;
#define AMD2 amd2
__IO_EXTERN IO_BYTE amd3;
#define AMD3 amd3
__IO_EXTERN IO_BYTE amd4;
#define AMD4 amd4
__IO_EXTERN IO_BYTE amd5;
#define AMD5 amd5
__IO_EXTERN IO_BYTE amd6;
#define AMD6 amd6
__IO_EXTERN IO_BYTE amd7;
#define AMD7 amd7
__IO_EXTERN IO_BYTE cse;
#define CSE cse
__IO_EXTERN IO_BYTE bstr0;
#define BSTR0 bstr0
__IO_EXTERN IO_WORD dmcr6;
#define DMCR6 dmcr6
__IO_EXTERN IO_WORD dmcr7;
#define DMCR7 dmcr7
__IO_EXTERN IO_BYTE che;
#define CHE che
__IO_EXTERN IO_WORD rfcr;
#define RFCR rfcr
__IO_EXTERN IO_BYTE modr;
#define MODR modr
__IO_EXTERN IO_BYTE ler;
#define LER ler
__IO_EXTERN IO_LWORD dmasa0;   /* DMAC */
#define DMASA0 dmasa0
__IO_EXTERN IO_LWORD dmada0;
#define DMADA0 dmada0
__IO_EXTERN IO_LWORD dmasa1;
#define DMASA1 dmasa1
__IO_EXTERN IO_LWORD dmada1;
#define DMADA1 dmada1
__IO_EXTERN IO_LWORD dmasa2;
#define DMASA2 dmasa2
__IO_EXTERN IO_LWORD dmada2;
#define DMADA2 dmada2
__IO_EXTERN IO_LWORD dmasa3;
#define DMASA3 dmasa3
__IO_EXTERN IO_LWORD dmada3;
#define DMADA3 dmada3
__IO_EXTERN IO_LWORD dmasa4;
#define DMASA4 dmasa4
__IO_EXTERN IO_LWORD dmada4;
#define DMADA4 dmada4
__IO_EXTERN FMCSSTR fmcs;   /* FLASH MEMORY */
#define FMCS fmcs.byte
#define FMCS_FACCE fmcs.bit.FACCE
#define FMCS_RDYEG fmcs.bit.RDYEG
#define FMCS_RDY fmcs.bit.RDY
#define FMCS_WRE fmcs.bit.WRE
#define FMCS_LPM fmcs.bit.LPM
__IO_EXTERN FMWTSTR fmwt;
#define FMWT fmwt.byte
#define FMWT_FAC1 fmwt.bit.FAC1
#define FMWT_FAC0 fmwt.bit.FAC0
#define FMWT_EQINH fmwt.bit.EQINH
#define FMWT_WTC2 fmwt.bit.WTC2
#define FMWT_WTC1 fmwt.bit.WTC1
#define FMWT_WTC0 fmwt.bit.WTC0
/*
 * CANIO: control structures of CAN for FR-controllers
 *
 * Version: 1.0            23.01.99     HLO
 *      - original version
 * Version: 2.0            26.02.99     HLO
 *      - unsigned int replace by IO_WORD (FR/LX have diff int)
 *      - unsigned char replace by IO_BYTE
 *      - changed for reverse bit order
 * Version: 2.1            28.05.01     HLO
 *      - "const" specifier added to several bit members, the CAN-controller
 *        on external bus does not support the read-modify-write instructions,
 *        which is a problem with status registers
 * Version: 2.2            30.05.01     HLO
 *      - "const" specifier removed from BVALR
 *        although there is a risk of lost update RMW-instructions are needed
 *        the lost update needs to be covered by the application

 */

#ifndef __CANSTR
#define __CANSTR

typedef struct
{
  union{
    IO_WORD word;
    struct{
            IO_WORD BVAL15 :1;
            IO_WORD BVAL14 :1;
            IO_WORD BVAL13 :1;
            IO_WORD BVAL12 :1;
            IO_WORD BVAL11 :1;
            IO_WORD BVAL10 :1;
            IO_WORD BVAL9  :1;
            IO_WORD BVAL8  :1;
            IO_WORD BVAL7  :1;
            IO_WORD BVAL6  :1;
            IO_WORD BVAL5  :1;
            IO_WORD BVAL4  :1;
            IO_WORD BVAL3  :1;
            IO_WORD BVAL2  :1;
            IO_WORD BVAL1  :1;
            IO_WORD BVAL0  :1;
    } bit;
  } bvalr;
  union{
    IO_WORD word;
    struct{
      IO_WORD TREQ15 :1;
      IO_WORD TREQ14 :1;
      IO_WORD TREQ13 :1;
      IO_WORD TREQ12 :1;
      IO_WORD TREQ11 :1;
      IO_WORD TREQ10 :1;
      IO_WORD TREQ9  :1;
      IO_WORD TREQ8  :1;
      IO_WORD TREQ7  :1;
      IO_WORD TREQ6  :1;
      IO_WORD TREQ5  :1;
      IO_WORD TREQ4  :1;
      IO_WORD TREQ3  :1;
      IO_WORD TREQ2  :1;
      IO_WORD TREQ1  :1;
      IO_WORD TREQ0  :1;
    } bit;
  } treqr;
  union{
    IO_WORD word;
    struct{
      IO_WORD TCAN15 :1;
      IO_WORD TCAN14 :1;
      IO_WORD TCAN13 :1;
      IO_WORD TCAN12 :1;
      IO_WORD TCAN11 :1;
      IO_WORD TCAN10 :1;
      IO_WORD TCAN9  :1;
      IO_WORD TCAN8  :1;
      IO_WORD TCAN7  :1;
      IO_WORD TCAN6  :1;
      IO_WORD TCAN5  :1;
      IO_WORD TCAN4  :1;
      IO_WORD TCAN3  :1;
      IO_WORD TCAN2  :1;
      IO_WORD TCAN1  :1;
      IO_WORD TCAN0  :1;
    } bit;
  } tcanr;
  union{
    IO_WORD word;
    struct{
      const IO_WORD TC15 :1;
      const IO_WORD TC14 :1;
      const IO_WORD TC13 :1;
      const IO_WORD TC12 :1;
      const IO_WORD TC11 :1;
      const IO_WORD TC10 :1;
      const IO_WORD TC9  :1;
      const IO_WORD TC8  :1;
      const IO_WORD TC7  :1;
      const IO_WORD TC6  :1;
      const IO_WORD TC5  :1;
      const IO_WORD TC4  :1;
      const IO_WORD TC3  :1;
      const IO_WORD TC2  :1;
      const IO_WORD TC1  :1;
      const IO_WORD TC0  :1;
    } bit;
 } tcr;
  union{
    IO_WORD word;
    struct{
      IO_WORD RC15 :1;
      IO_WORD RC14 :1;
      IO_WORD RC13 :1;
      IO_WORD RC12 :1;
      IO_WORD RC11 :1;
      IO_WORD RC10 :1;
      IO_WORD RC9  :1;
      IO_WORD RC8  :1;
      IO_WORD RC7  :1;
      IO_WORD RC6  :1;
      IO_WORD RC5  :1;
      IO_WORD RC4  :1;
      IO_WORD RC3  :1;
      IO_WORD RC2  :1;
      IO_WORD RC1  :1;
      IO_WORD RC0  :1;
    } bit;
  } rcr;
  union{
    IO_WORD word;
    struct{
      const IO_WORD RRTR15 :1;
      const IO_WORD RRTR14 :1;
      const IO_WORD RRTR13 :1;
      const IO_WORD RRTR12 :1;
      const IO_WORD RRTR11 :1;
      const IO_WORD RRTR10 :1;
      const IO_WORD RRTR9  :1;
      const IO_WORD RRTR8  :1;
      const IO_WORD RRTR7  :1;
      const IO_WORD RRTR6  :1;
      const IO_WORD RRTR5  :1;
      const IO_WORD RRTR4  :1;
      const IO_WORD RRTR3  :1;
      const IO_WORD RRTR2  :1;
      const IO_WORD RRTR1  :1;
      const IO_WORD RRTR0  :1;
    } bit;
  } rrtrr;
  union{
    IO_WORD word;
    struct{
      IO_WORD ROVR15 :1;
      IO_WORD ROVR14 :1;
      IO_WORD ROVR13 :1;
      IO_WORD ROVR12 :1;
      IO_WORD ROVR11 :1;
      IO_WORD ROVR10 :1;
      IO_WORD ROVR9  :1;
      IO_WORD ROVR8  :1;
      IO_WORD ROVR7  :1;
      IO_WORD ROVR6  :1;
      IO_WORD ROVR5  :1;
      IO_WORD ROVR4  :1;
      IO_WORD ROVR3  :1;
      IO_WORD ROVR2  :1;
      IO_WORD ROVR1  :1;
      IO_WORD ROVR0  :1;
    } bit;
  } rovrr;
  union{
    IO_WORD word;
    struct{
            IO_WORD RIE15 :1;
            IO_WORD RIE14 :1;
            IO_WORD RIE13 :1;
            IO_WORD RIE12 :1;
            IO_WORD RIE11 :1;
            IO_WORD RIE10 :1;
            IO_WORD RIE9  :1;
            IO_WORD RIE8  :1;
            IO_WORD RIE7  :1;
            IO_WORD RIE6  :1;
            IO_WORD RIE5  :1;
            IO_WORD RIE4  :1;
            IO_WORD RIE3  :1;
            IO_WORD RIE2  :1;
            IO_WORD RIE1  :1;
            IO_WORD RIE0  :1;
    } bit;
  } rier;
} CANLSTR;

typedef struct
{
  union{
    IO_WORD word;
      struct{
      const IO_WORD TS 	 :1;
      const IO_WORD RS 	 :1;
            IO_WORD  	 :1;
            IO_WORD  	 :1;
            IO_WORD  	 :1;
            IO_WORD NT 	 :1;
      const IO_WORD NS1  :1;
      const IO_WORD NS0  :1;
            IO_WORD TOE  :1;
            IO_WORD      :1;
            IO_WORD      :1;
            IO_WORD      :1;
            IO_WORD  	 :1;
            IO_WORD NIE  :1;
            IO_WORD      :1;
            IO_WORD HALT :1;
    }bit;
    struct{
            IO_WORD 	 :1;
            IO_WORD 	 :1;
            IO_WORD 	 :1;
            IO_WORD 	 :1;
            IO_WORD 	 :1;
            IO_WORD 	 :1;
      const IO_WORD NS   :2;
    }bitc;
  }csr;
  union{
    IO_WORD word;
    IO_WORD byte;
    struct{
            IO_WORD NTE  :1;
            IO_WORD TCE  :1;
            IO_WORD RCE  :1;
            IO_WORD      :1;
            IO_WORD MBP3 :1;
            IO_WORD MBP2 :1;
            IO_WORD MBP1 :1;
            IO_WORD MBP0 :1;
    } bit;
    struct{
            IO_WORD      :8;
            IO_WORD      :4;
            IO_WORD MBP  :4;
    } bitc;
  } leir;
  const union{
    IO_WORD word;
    struct{
      IO_WORD TEC7 :1;
      IO_WORD TEC6 :1;
      IO_WORD TEC5 :1;
      IO_WORD TEC4 :1;
      IO_WORD TEC3 :1;
      IO_WORD TEC2 :1;
      IO_WORD TEC1 :1;
      IO_WORD TEC0 :1;
      IO_WORD REC7 :1;
      IO_WORD REC6 :1;
      IO_WORD REC5 :1;
      IO_WORD REC4 :1;
      IO_WORD REC3 :1;
      IO_WORD REC2 :1;
      IO_WORD REC1 :1;
      IO_WORD REC0 :1;
    }bit;
    struct{
      IO_BYTE TEC;
      IO_BYTE REC;
    }bitc;
  }rtec;
  union{
    IO_WORD word;
    struct{
            IO_WORD      :1;
            IO_WORD TS22 :1;
            IO_WORD TS21 :1;
            IO_WORD TS20 :1;
            IO_WORD TS13 :1;
            IO_WORD TS12 :1;
            IO_WORD TS11 :1;
            IO_WORD TS10 :1;
            IO_WORD RSJ1 :1;
            IO_WORD RSJ0 :1;
            IO_WORD PSC5 :1;
            IO_WORD PSC4 :1;
            IO_WORD PSC3 :1;
            IO_WORD PSC2 :1;
            IO_WORD PSC1 :1;
            IO_WORD PSC0 :1;
    } bit;
    struct{
            IO_WORD TS2 :3;
            IO_WORD TS1 :4;
            IO_WORD RSJ :2;
            IO_WORD PSC :6;
    } bitc;
  } btr;
  union{
    IO_WORD word;
      struct{
            IO_WORD IDE15 :1;
            IO_WORD IDE14 :1;
            IO_WORD IDE13 :1;
            IO_WORD IDE12 :1;
            IO_WORD IDE11 :1;
            IO_WORD IDE10 :1;
            IO_WORD IDE9  :1;
            IO_WORD IDE8  :1;
            IO_WORD IDE7  :1;
            IO_WORD IDE6  :1;
            IO_WORD IDE5  :1;
            IO_WORD IDE4  :1;
            IO_WORD IDE3  :1;
            IO_WORD IDE2  :1;
            IO_WORD IDE1  :1;
            IO_WORD IDE0  :1;
    } bit;
  } ider;
  union{
    IO_WORD word;
    struct{
            IO_WORD TRTR15 :1;
            IO_WORD TRTR14 :1;
            IO_WORD TRTR13 :1;
            IO_WORD TRTR12 :1;
            IO_WORD TRTR11 :1;
            IO_WORD TRTR10 :1;
            IO_WORD TRTR9  :1;
            IO_WORD TRTR8  :1;
            IO_WORD TRTR7  :1;
            IO_WORD TRTR6  :1;
            IO_WORD TRTR5  :1;
            IO_WORD TRTR4  :1;
            IO_WORD TRTR3  :1;
            IO_WORD TRTR2  :1;
            IO_WORD TRTR1  :1;
            IO_WORD TRTR0  :1;
    } bit;
  } trtrr;
  union{
    IO_WORD word;
    struct{
            IO_WORD RFWT15 :1;
            IO_WORD RFWT14 :1;
            IO_WORD RFWT13 :1;
            IO_WORD RFWT12 :1;
            IO_WORD RFWT11 :1;
            IO_WORD RFWT10 :1;
            IO_WORD RFWT9  :1;
            IO_WORD RFWT8  :1;
            IO_WORD RFWT7  :1;
            IO_WORD RFWT6  :1;
            IO_WORD RFWT5  :1;
            IO_WORD RFWT4  :1;
            IO_WORD RFWT3  :1;
            IO_WORD RFWT2  :1;
            IO_WORD RFWT1  :1;
            IO_WORD RFWT0  :1;
    } bit;
  } rfwtr;
  union{
    IO_WORD word;
    struct{
            IO_WORD TIE15 :1;
            IO_WORD TIE14 :1;
            IO_WORD TIE13 :1;
            IO_WORD TIE12 :1;
            IO_WORD TIE11 :1;
            IO_WORD TIE10 :1;
            IO_WORD TIE9  :1;
            IO_WORD TIE8  :1;
            IO_WORD TIE7  :1;
            IO_WORD TIE6  :1;
            IO_WORD TIE5  :1;
            IO_WORD TIE4  :1;
            IO_WORD TIE3  :1;
            IO_WORD TIE2  :1;
            IO_WORD TIE1  :1;
            IO_WORD TIE0  :1;
  } bit;
 } tier;
  union{
    unsigned long     dword;
    struct{
            IO_WORD    AMS151 :1;
            IO_WORD    AMS150 :1;
            IO_WORD    AMS141 :1;
            IO_WORD    AMS140 :1;
            IO_WORD    AMS131 :1;
            IO_WORD    AMS130 :1;
            IO_WORD    AMS121 :1;
            IO_WORD    AMS120 :1;
            IO_WORD    AMS111 :1;
            IO_WORD    AMS110 :1;
            IO_WORD    AMS101 :1;
            IO_WORD    AMS100 :1;
            IO_WORD    AMS91  :1;
            IO_WORD    AMS90  :1;
            IO_WORD    AMS81  :1;
            IO_WORD    AMS80  :1;
            IO_WORD    AMS71  :1;
            IO_WORD    AMS70  :1;
            IO_WORD    AMS61  :1;
            IO_WORD    AMS60  :1;
            IO_WORD    AMS51  :1;
            IO_WORD    AMS50  :1;
            IO_WORD    AMS41  :1;
            IO_WORD    AMS40  :1;
            IO_WORD    AMS31  :1;
            IO_WORD    AMS30  :1;
            IO_WORD    AMS21  :1;
            IO_WORD    AMS20  :1;
            IO_WORD    AMS11  :1;
            IO_WORD    AMS10  :1;
            IO_WORD    AMS01  :1;
            IO_WORD    AMS00  :1;
    }bit;
    struct{
            IO_WORD    AMS15 :2;
            IO_WORD    AMS14 :2;
            IO_WORD    AMS13 :2;
            IO_WORD    AMS12 :2;
            IO_WORD    AMS11 :2;
            IO_WORD    AMS10 :2;
            IO_WORD    AMS9  :2;
            IO_WORD    AMS8  :2;
            IO_WORD    AMS7  :2;
            IO_WORD    AMS6  :2;
            IO_WORD    AMS5  :2;
            IO_WORD    AMS4  :2;
            IO_WORD    AMS3  :2;
            IO_WORD    AMS2  :2;
            IO_WORD    AMS1  :2;
            IO_WORD    AMS0  :2;
    } bitc;
  } amsr;
  union {
    unsigned long   dword;
    unsigned short  word;
    struct {
              IO_WORD AM28 :1;
              IO_WORD AM27 :1;
              IO_WORD AM26 :1;
              IO_WORD AM25 :1;
              IO_WORD AM24 :1;
              IO_WORD AM23 :1;
              IO_WORD AM22 :1;
              IO_WORD AM21 :1;

              IO_WORD AM20 :1;
              IO_WORD AM19 :1;
              IO_WORD AM18 :1;
              IO_WORD AM17 :1;
              IO_WORD AM16 :1;
              IO_WORD AM15 :1;
              IO_WORD AM14 :1;
              IO_WORD AM13 :1;

              IO_WORD AM12 :1;
              IO_WORD AM11 :1;
              IO_WORD AM10 :1;
              IO_WORD AM9  :1;
              IO_WORD AM8  :1;
              IO_WORD AM7  :1;
              IO_WORD AM6  :1;
              IO_WORD AM5  :1;

              IO_WORD AM4  :1;
              IO_WORD AM3  :1;
              IO_WORD AM2  :1;
              IO_WORD AM1  :1;
              IO_WORD AM0  :1;
              IO_WORD      :3;
    } bit_ext;
    struct {
              IO_WORD AM10 :1;
              IO_WORD AM9  :1;
              IO_WORD AM8  :1;
              IO_WORD AM7  :1;
              IO_WORD AM6  :1;
              IO_WORD AM5  :1;
              IO_WORD AM4  :1;
              IO_WORD AM3  :1;

              IO_WORD AM2 :1;
              IO_WORD AM1 :1;
              IO_WORD AM0 :1;
              IO_WORD     :5;
    } bit_std;
    struct {
              IO_WORD AM21_28    : 8;
              IO_WORD AM13_20    : 8;
              IO_WORD AM5_12     : 8;
              IO_WORD AM0_4      : 5;
              IO_WORD unused     : 3;            /* unused bits */
    } bitc_ext;
    struct {
              IO_WORD AM3_10 : 8;
              IO_WORD AM0_2  : 3;
              IO_WORD unused : 5;                /* unused bits   */
              /*IO_WORD upper    :16;            /* unused bits */
    } bitc_std;
  } amr[2];
} CANHSTR;

typedef struct
{
    IO_WORD ram[16];
    union {
    unsigned long   dword;
    unsigned short  word;
    struct {
        const IO_WORD ID28 :1;
        const IO_WORD ID27 :1;
        const IO_WORD ID26 :1;
        const IO_WORD ID25 :1;
        const IO_WORD ID24 :1;
        const IO_WORD ID23 :1;
        const IO_WORD ID22 :1;
        const IO_WORD ID21 :1;

        const IO_WORD ID20 :1;
        const IO_WORD ID19 :1;
        const IO_WORD ID18 :1;
        const IO_WORD ID17 :1;
        const IO_WORD ID16 :1;
        const IO_WORD ID15 :1;
        const IO_WORD ID14 :1;
        const IO_WORD ID13 :1;

        const IO_WORD ID12 :1;
        const IO_WORD ID11 :1;
        const IO_WORD ID10 :1;
        const IO_WORD ID9  :1;
        const IO_WORD ID8  :1;
        const IO_WORD ID7  :1;
        const IO_WORD ID6  :1;
        const IO_WORD ID5  :1;

        const IO_WORD ID4 :1;
        const IO_WORD ID3 :1;
        const IO_WORD ID2 :1;
        const IO_WORD ID1 :1;
        const IO_WORD ID0 :1;
		const IO_WORD     :3;
    } bit_ext;
    struct {
        const IO_WORD AM10:1;
        const IO_WORD AM9 :1;
        const IO_WORD AM8 :1;
        const IO_WORD AM7 :1;
        const IO_WORD AM6 :1;
        const IO_WORD AM5 :1;
        const IO_WORD AM4 :1;
        const IO_WORD AM3 :1;

        const IO_WORD AM2 :1;
        const IO_WORD AM1 :1;
        const IO_WORD AM0 :1;
        const IO_WORD     :5;
    } bit_std;
    struct {
        const IO_WORD ID21_28 : 8;
        const IO_WORD ID13_20 : 8;
        const IO_WORD ID5_12  : 8;
        const IO_WORD ID0_4   : 5;
        const IO_WORD unused  : 3;         /* unused bits */
    } bitc_ext;
    struct {
        const IO_WORD ID3_10  : 8;
        const IO_WORD ID0_2   : 3;
        const IO_WORD unused  : 5;             /* unused bits   */
    } bitc_std;
  } idr[16];
  union{
    IO_WORD         word;
    struct {
        IO_WORD     :1;
        IO_WORD     :1;
        IO_WORD     :1;
        IO_WORD     :1;
        IO_WORD     :1;
        IO_WORD     :1;
        IO_WORD     :1;
        IO_WORD     :1;
        IO_WORD     :1;
        IO_WORD     :1;
        IO_WORD     :1;
        IO_WORD     :1;
        IO_WORD     DLC3:1;
        IO_WORD     DLC2:1;
        IO_WORD     DLC1:1;
        IO_WORD     DLC0:1;
    } bit;
    struct {
        IO_WORD        :12;
        IO_WORD     DLC: 4;
    } bitc;
  } dlcr[16];
  union{
          unsigned long dwords [2];
          long          longs  [2];
          IO_WORD       words  [4];
          int           ints   [2];
          short         shorts [4];
    const IO_BYTE       bytes  [8]; /* because of word access*/
    const char          chars  [8]; /* because of word access*/
          float         floats [2];
          double        adouble;
  }dtr[16];
} CANMSTR;

#endif	/* CANSTR */
__IO_EXTERN CREG0STR creg0;
#define CREG0 creg0.word
#define CREG0_DTR_W creg0.bit.DTR_W
#define CREG0_DTR_B creg0.bit.DTR_B
#define CREG0_IDR_W creg0.bit.IDR_W
#define CREG0_IDR_B creg0.bit.IDR_B
#define CREG0_AMR_W creg0.bit.AMR_W
#define CREG0_AMR_B creg0.bit.AMR_B
#define CREG0_AMS_W creg0.bit.AMS_W
#define CREG0_AMS_B creg0.bit.AMS_B
#define CREG0_E_INT creg0.bit.E_INT
#define CREG0_S_INT creg0.bit.S_INT
#define CREG0_C_INT creg0.bit.C_INT
#define CREG0_L_INV creg0.bit.L_INV
#define CREG0_C_CLK creg0.bit.C_CLK
#define CREG0_L_CLK creg0.bit.L_CLK
#define CREG0_SYNCH creg0.bit.SYNCH
#define CREG0_CDSBLE creg0.bit.CDSBLE
__IO_EXTERN CREG1STR creg1;
#define CREG1 creg1.word
#define CREG1_DTR_W creg1.bit.DTR_W
#define CREG1_DTR_B creg1.bit.DTR_B
#define CREG1_IDR_W creg1.bit.IDR_W
#define CREG1_IDR_B creg1.bit.IDR_B
#define CREG1_AMR_W creg1.bit.AMR_W
#define CREG1_AMR_B creg1.bit.AMR_B
#define CREG1_AMS_W creg1.bit.AMS_W
#define CREG1_AMS_B creg1.bit.AMS_B
#define CREG1_E_INT creg1.bit.E_INT
#define CREG1_S_INT creg1.bit.S_INT
#define CREG1_C_INT creg1.bit.C_INT
#define CREG1_L_INV creg1.bit.L_INV
#define CREG1_C_CLK creg1.bit.C_CLK
#define CREG1_L_CLK creg1.bit.L_CLK
#define CREG1_SYNCH creg1.bit.SYNCH
#define CREG1_CDSBLE creg1.bit.CDSBLE
__IO_EXTERN CREG2STR creg2;
#define CREG2 creg2.word
#define CREG2_DTR_W creg2.bit.DTR_W
#define CREG2_DTR_B creg2.bit.DTR_B
#define CREG2_IDR_W creg2.bit.IDR_W
#define CREG2_IDR_B creg2.bit.IDR_B
#define CREG2_AMR_W creg2.bit.AMR_W
#define CREG2_AMR_B creg2.bit.AMR_B
#define CREG2_AMS_W creg2.bit.AMS_W
#define CREG2_AMS_B creg2.bit.AMS_B
#define CREG2_E_INT creg2.bit.E_INT
#define CREG2_S_INT creg2.bit.S_INT
#define CREG2_C_INT creg2.bit.C_INT
#define CREG2_L_INV creg2.bit.L_INV
#define CREG2_C_CLK creg2.bit.C_CLK
#define CREG2_L_CLK creg2.bit.L_CLK
#define CREG2_SYNCH creg2.bit.SYNCH
#define CREG2_CDSBLE creg2.bit.CDSBLE
/*
 * CANIO: Macros for control structures of triple CAN for FR-controllers
 *
 * Version: 1.0            23.01.99     FMG, HLO
 *      - original version
 * Version: 1.1            27.01.99     FMG, tka
 *      - idrx0 changed to IDRX0
 * Version: 1.2            11.02.99     FMG, HLO
 *      - "extern" declaration changed to predefined macros of
 *        IO-Wizard, requires IO-Wizard 1.7 or later
 *      - DRT1_LWPTR changed to DTR1_DWPTR macro
 * Version: 2.0            28.05.01     HLO
 *      - LX-version adopted to FR
 *      - __IO_EXTENDED changed to __IO_EXTERN, CAN is on external bus
 */

#ifndef __CANMAC
#define __CANMAC

__IO_EXTERN CANLSTR canl0;
__IO_EXTERN CANLSTR _canl1;
__IO_EXTERN CANLSTR _canl2;

/* CAN0 macros */
#define BVALR0           canl0.bvalr.word
#define BVALR0_BVAL0     canl0.bvalr.bit.BVAL0
#define BVALR0_BVAL1     canl0.bvalr.bit.BVAL1
#define BVALR0_BVAL2     canl0.bvalr.bit.BVAL2
#define BVALR0_BVAL3     canl0.bvalr.bit.BVAL3
#define BVALR0_BVAL4     canl0.bvalr.bit.BVAL4
#define BVALR0_BVAL5     canl0.bvalr.bit.BVAL5
#define BVALR0_BVAL6     canl0.bvalr.bit.BVAL6
#define BVALR0_BVAL7     canl0.bvalr.bit.BVAL7
#define BVALR0_BVAL8     canl0.bvalr.bit.BVAL8
#define BVALR0_BVAL9     canl0.bvalr.bit.BVAL9
#define BVALR0_BVAL10    canl0.bvalr.bit.BVAL10
#define BVALR0_BVAL11    canl0.bvalr.bit.BVAL11
#define BVALR0_BVAL12    canl0.bvalr.bit.BVAL12
#define BVALR0_BVAL13    canl0.bvalr.bit.BVAL13
#define BVALR0_BVAL14    canl0.bvalr.bit.BVAL14
#define BVALR0_BVAL15    canl0.bvalr.bit.BVAL15

#define TREQR0           canl0.treqr.word
#define TREQR0_TREQ0     canl0.treqr.bit.TREQ0
#define TREQR0_TREQ1     canl0.treqr.bit.TREQ1
#define TREQR0_TREQ2     canl0.treqr.bit.TREQ2
#define TREQR0_TREQ3     canl0.treqr.bit.TREQ3
#define TREQR0_TREQ4     canl0.treqr.bit.TREQ4
#define TREQR0_TREQ5     canl0.treqr.bit.TREQ5
#define TREQR0_TREQ6     canl0.treqr.bit.TREQ6
#define TREQR0_TREQ7     canl0.treqr.bit.TREQ7
#define TREQR0_TREQ8     canl0.treqr.bit.TREQ8
#define TREQR0_TREQ9     canl0.treqr.bit.TREQ9
#define TREQR0_TREQ10    canl0.treqr.bit.TREQ10
#define TREQR0_TREQ11    canl0.treqr.bit.TREQ11
#define TREQR0_TREQ12    canl0.treqr.bit.TREQ12
#define TREQR0_TREQ13    canl0.treqr.bit.TREQ13
#define TREQR0_TREQ14    canl0.treqr.bit.TREQ14
#define TREQR0_TREQ15    canl0.treqr.bit.TREQ15

#define TCANR0           canl0.tcanr.word
#define TCANR0_TCAN0     canl0.tcanr.bit.TCAN0
#define TCANR0_TCAN1     canl0.tcanr.bit.TCAN1
#define TCANR0_TCAN2     canl0.tcanr.bit.TCAN2
#define TCANR0_TCAN3     canl0.tcanr.bit.TCAN3
#define TCANR0_TCAN4     canl0.tcanr.bit.TCAN4
#define TCANR0_TCAN5     canl0.tcanr.bit.TCAN5
#define TCANR0_TCAN6     canl0.tcanr.bit.TCAN6
#define TCANR0_TCAN7     canl0.tcanr.bit.TCAN7
#define TCANR0_TCAN8     canl0.tcanr.bit.TCAN8
#define TCANR0_TCAN9     canl0.tcanr.bit.TCAN9
#define TCANR0_TCAN10    canl0.tcanr.bit.TCAN10
#define TCANR0_TCAN11    canl0.tcanr.bit.TCAN11
#define TCANR0_TCAN12    canl0.tcanr.bit.TCAN12
#define TCANR0_TCAN13    canl0.tcanr.bit.TCAN13
#define TCANR0_TCAN14    canl0.tcanr.bit.TCAN14
#define TCANR0_TCAN15    canl0.tcanr.bit.TCAN15

#define TCR0             canl0.tcr.word
#define TCR0_TC0         canl0.tcr.bit.TC0
#define TCR0_TC1         canl0.tcr.bit.TC1
#define TCR0_TC2         canl0.tcr.bit.TC2
#define TCR0_TC3         canl0.tcr.bit.TC3
#define TCR0_TC4         canl0.tcr.bit.TC4
#define TCR0_TC5         canl0.tcr.bit.TC5
#define TCR0_TC6         canl0.tcr.bit.TC6
#define TCR0_TC7         canl0.tcr.bit.TC7
#define TCR0_TC8         canl0.tcr.bit.TC8
#define TCR0_TC9         canl0.tcr.bit.TC9
#define TCR0_TC10        canl0.tcr.bit.TC10
#define TCR0_TC11        canl0.tcr.bit.TC11
#define TCR0_TC12        canl0.tcr.bit.TC12
#define TCR0_TC13        canl0.tcr.bit.TC13
#define TCR0_TC14        canl0.tcr.bit.TC14
#define TCR0_TC15        canl0.tcr.bit.TC15

#define RCR0             canl0.rcr.word
#define RCR0_RC0         canl0.rcr.bit.RC0
#define RCR0_RC1         canl0.rcr.bit.RC1
#define RCR0_RC2         canl0.rcr.bit.RC2
#define RCR0_RC3         canl0.rcr.bit.RC3
#define RCR0_RC4         canl0.rcr.bit.RC4
#define RCR0_RC5         canl0.rcr.bit.RC5
#define RCR0_RC6         canl0.rcr.bit.RC6
#define RCR0_RC7         canl0.rcr.bit.RC7
#define RCR0_RC8         canl0.rcr.bit.RC8
#define RCR0_RC9         canl0.rcr.bit.RC9
#define RCR0_RC10        canl0.rcr.bit.RC10
#define RCR0_RC11        canl0.rcr.bit.RC11
#define RCR0_RC12        canl0.rcr.bit.RC12
#define RCR0_RC13        canl0.rcr.bit.RC13
#define RCR0_RC14        canl0.rcr.bit.RC14
#define RCR0_RC15        canl0.rcr.bit.RC15

#define RRTRR0           canl0.rrtrr.word
#define RRTRR0_RRTR0     canl0.rrtrr.bit.RRTR0
#define RRTRR0_RRTR1     canl0.rrtrr.bit.RRTR1
#define RRTRR0_RRTR2     canl0.rrtrr.bit.RRTR2
#define RRTRR0_RRTR3     canl0.rrtrr.bit.RRTR3
#define RRTRR0_RRTR4     canl0.rrtrr.bit.RRTR4
#define RRTRR0_RRTR5     canl0.rrtrr.bit.RRTR5
#define RRTRR0_RRTR6     canl0.rrtrr.bit.RRTR6
#define RRTRR0_RRTR7     canl0.rrtrr.bit.RRTR7
#define RRTRR0_RRTR8     canl0.rrtrr.bit.RRTR8
#define RRTRR0_RRTR9     canl0.rrtrr.bit.RRTR9
#define RRTRR0_RRTR10    canl0.rrtrr.bit.RRTR10
#define RRTRR0_RRTR11    canl0.rrtrr.bit.RRTR11
#define RRTRR0_RRTR12    canl0.rrtrr.bit.RRTR12
#define RRTRR0_RRTR13    canl0.rrtrr.bit.RRTR13
#define RRTRR0_RRTR14    canl0.rrtrr.bit.RRTR14
#define RRTRR0_RRTR15    canl0.rrtrr.bit.RRTR15

#define ROVRR0           canl0.rovrr.word
#define ROVRR0_ROVR0     canl0.rovrr.bit.ROVR0
#define ROVRR0_ROVR1     canl0.rovrr.bit.ROVR1
#define ROVRR0_ROVR2     canl0.rovrr.bit.ROVR2
#define ROVRR0_ROVR3     canl0.rovrr.bit.ROVR3
#define ROVRR0_ROVR4     canl0.rovrr.bit.ROVR4
#define ROVRR0_ROVR5     canl0.rovrr.bit.ROVR5
#define ROVRR0_ROVR6     canl0.rovrr.bit.ROVR6
#define ROVRR0_ROVR7     canl0.rovrr.bit.ROVR7
#define ROVRR0_ROVR8     canl0.rovrr.bit.ROVR8
#define ROVRR0_ROVR9     canl0.rovrr.bit.ROVR9
#define ROVRR0_ROVR10    canl0.rovrr.bit.ROVR10
#define ROVRR0_ROVR11    canl0.rovrr.bit.ROVR11
#define ROVRR0_ROVR12    canl0.rovrr.bit.ROVR12
#define ROVRR0_ROVR13    canl0.rovrr.bit.ROVR13
#define ROVRR0_ROVR14    canl0.rovrr.bit.ROVR14
#define ROVRR0_ROVR15    canl0.rovrr.bit.ROVR15

#define RIER0            canl0.rier.word
#define RIER0_RIE0       canl0.rier.bit.RIE0
#define RIER0_RIE1       canl0.rier.bit.RIE1
#define RIER0_RIE2       canl0.rier.bit.RIE2
#define RIER0_RIE3       canl0.rier.bit.RIE3
#define RIER0_RIE4       canl0.rier.bit.RIE4
#define RIER0_RIE5       canl0.rier.bit.RIE5
#define RIER0_RIE6       canl0.rier.bit.RIE6
#define RIER0_RIE7       canl0.rier.bit.RIE7
#define RIER0_RIE8       canl0.rier.bit.RIE8
#define RIER0_RIE9       canl0.rier.bit.RIE9
#define RIER0_RIE10      canl0.rier.bit.RIE10
#define RIER0_RIE11      canl0.rier.bit.RIE11
#define RIER0_RIE12      canl0.rier.bit.RIE12
#define RIER0_RIE13      canl0.rier.bit.RIE13
#define RIER0_RIE14      canl0.rier.bit.RIE14
#define RIER0_RIE15      canl0.rier.bit.RIE15

/* CAN1 macros */
#define BVALR1           _canl1.bvalr.word
#define BVALR1_BVAL0     _canl1.bvalr.bit.BVAL0
#define BVALR1_BVAL1     _canl1.bvalr.bit.BVAL1
#define BVALR1_BVAL2     _canl1.bvalr.bit.BVAL2
#define BVALR1_BVAL3     _canl1.bvalr.bit.BVAL3
#define BVALR1_BVAL4     _canl1.bvalr.bit.BVAL4
#define BVALR1_BVAL5     _canl1.bvalr.bit.BVAL5
#define BVALR1_BVAL6     _canl1.bvalr.bit.BVAL6
#define BVALR1_BVAL7     _canl1.bvalr.bit.BVAL7
#define BVALR1_BVAL8     _canl1.bvalr.bit.BVAL8
#define BVALR1_BVAL9     _canl1.bvalr.bit.BVAL9
#define BVALR1_BVAL10    _canl1.bvalr.bit.BVAL10
#define BVALR1_BVAL11    _canl1.bvalr.bit.BVAL11
#define BVALR1_BVAL12    _canl1.bvalr.bit.BVAL12
#define BVALR1_BVAL13    _canl1.bvalr.bit.BVAL13
#define BVALR1_BVAL14    _canl1.bvalr.bit.BVAL14
#define BVALR1_BVAL15    _canl1.bvalr.bit.BVAL15

#define TREQR1           _canl1.treqr.word
#define TREQR1_TREQ0     _canl1.treqr.bit.TREQ0
#define TREQR1_TREQ1     _canl1.treqr.bit.TREQ1
#define TREQR1_TREQ2     _canl1.treqr.bit.TREQ2
#define TREQR1_TREQ3     _canl1.treqr.bit.TREQ3
#define TREQR1_TREQ4     _canl1.treqr.bit.TREQ4
#define TREQR1_TREQ5     _canl1.treqr.bit.TREQ5
#define TREQR1_TREQ6     _canl1.treqr.bit.TREQ6
#define TREQR1_TREQ7     _canl1.treqr.bit.TREQ7
#define TREQR1_TREQ8     _canl1.treqr.bit.TREQ8
#define TREQR1_TREQ9     _canl1.treqr.bit.TREQ9
#define TREQR1_TREQ10    _canl1.treqr.bit.TREQ10
#define TREQR1_TREQ11    _canl1.treqr.bit.TREQ11
#define TREQR1_TREQ12    _canl1.treqr.bit.TREQ12
#define TREQR1_TREQ13    _canl1.treqr.bit.TREQ13
#define TREQR1_TREQ14    _canl1.treqr.bit.TREQ14
#define TREQR1_TREQ15    _canl1.treqr.bit.TREQ15

#define TCANR1           _canl1.tcanr.word
#define TCANR1_TCAN0     _canl1.tcanr.bit.TCAN0
#define TCANR1_TCAN1     _canl1.tcanr.bit.TCAN1
#define TCANR1_TCAN2     _canl1.tcanr.bit.TCAN2
#define TCANR1_TCAN3     _canl1.tcanr.bit.TCAN3
#define TCANR1_TCAN4     _canl1.tcanr.bit.TCAN4
#define TCANR1_TCAN5     _canl1.tcanr.bit.TCAN5
#define TCANR1_TCAN6     _canl1.tcanr.bit.TCAN6
#define TCANR1_TCAN7     _canl1.tcanr.bit.TCAN7
#define TCANR1_TCAN8     _canl1.tcanr.bit.TCAN8
#define TCANR1_TCAN9     _canl1.tcanr.bit.TCAN9
#define TCANR1_TCAN10    _canl1.tcanr.bit.TCAN10
#define TCANR1_TCAN11    _canl1.tcanr.bit.TCAN11
#define TCANR1_TCAN12    _canl1.tcanr.bit.TCAN12
#define TCANR1_TCAN13    _canl1.tcanr.bit.TCAN13
#define TCANR1_TCAN14    _canl1.tcanr.bit.TCAN14
#define TCANR1_TCAN15    _canl1.tcanr.bit.TCAN15

#define TCR1             _canl1.tcr.word
#define TCR1_TC0         _canl1.tcr.bit.TC0
#define TCR1_TC1         _canl1.tcr.bit.TC1
#define TCR1_TC2         _canl1.tcr.bit.TC2
#define TCR1_TC3         _canl1.tcr.bit.TC3
#define TCR1_TC4         _canl1.tcr.bit.TC4
#define TCR1_TC5         _canl1.tcr.bit.TC5
#define TCR1_TC6         _canl1.tcr.bit.TC6
#define TCR1_TC7         _canl1.tcr.bit.TC7
#define TCR1_TC8         _canl1.tcr.bit.TC8
#define TCR1_TC9         _canl1.tcr.bit.TC9
#define TCR1_TC10        _canl1.tcr.bit.TC10
#define TCR1_TC11        _canl1.tcr.bit.TC11
#define TCR1_TC12        _canl1.tcr.bit.TC12
#define TCR1_TC13        _canl1.tcr.bit.TC13
#define TCR1_TC14        _canl1.tcr.bit.TC14
#define TCR1_TC15        _canl1.tcr.bit.TC15

#define RCR1             _canl1.rcr.word
#define RCR1_RC0         _canl1.rcr.bit.RC0
#define RCR1_RC1         _canl1.rcr.bit.RC1
#define RCR1_RC2         _canl1.rcr.bit.RC2
#define RCR1_RC3         _canl1.rcr.bit.RC3
#define RCR1_RC4         _canl1.rcr.bit.RC4
#define RCR1_RC5         _canl1.rcr.bit.RC5
#define RCR1_RC6         _canl1.rcr.bit.RC6
#define RCR1_RC7         _canl1.rcr.bit.RC7
#define RCR1_RC8         _canl1.rcr.bit.RC8
#define RCR1_RC9         _canl1.rcr.bit.RC9
#define RCR1_RC10        _canl1.rcr.bit.RC10
#define RCR1_RC11        _canl1.rcr.bit.RC11
#define RCR1_RC12        _canl1.rcr.bit.RC12
#define RCR1_RC13        _canl1.rcr.bit.RC13
#define RCR1_RC14        _canl1.rcr.bit.RC14
#define RCR1_RC15        _canl1.rcr.bit.RC15

#define RRTRR1           _canl1.rrtrr.word
#define RRTRR1_RRTR0     _canl1.rrtrr.bit.RRTR0
#define RRTRR1_RRTR1     _canl1.rrtrr.bit.RRTR1
#define RRTRR1_RRTR2     _canl1.rrtrr.bit.RRTR2
#define RRTRR1_RRTR3     _canl1.rrtrr.bit.RRTR3
#define RRTRR1_RRTR4     _canl1.rrtrr.bit.RRTR4
#define RRTRR1_RRTR5     _canl1.rrtrr.bit.RRTR5
#define RRTRR1_RRTR6     _canl1.rrtrr.bit.RRTR6
#define RRTRR1_RRTR7     _canl1.rrtrr.bit.RRTR7
#define RRTRR1_RRTR8     _canl1.rrtrr.bit.RRTR8
#define RRTRR1_RRTR9     _canl1.rrtrr.bit.RRTR9
#define RRTRR1_RRTR10    _canl1.rrtrr.bit.RRTR10
#define RRTRR1_RRTR11    _canl1.rrtrr.bit.RRTR11
#define RRTRR1_RRTR12    _canl1.rrtrr.bit.RRTR12
#define RRTRR1_RRTR13    _canl1.rrtrr.bit.RRTR13
#define RRTRR1_RRTR14    _canl1.rrtrr.bit.RRTR14
#define RRTRR1_RRTR15    _canl1.rrtrr.bit.RRTR15

#define ROVRR1           _canl1.rovrr.word
#define ROVRR1_ROVR0     _canl1.rovrr.bit.ROVR0
#define ROVRR1_ROVR1     _canl1.rovrr.bit.ROVR1
#define ROVRR1_ROVR2     _canl1.rovrr.bit.ROVR2
#define ROVRR1_ROVR3     _canl1.rovrr.bit.ROVR3
#define ROVRR1_ROVR4     _canl1.rovrr.bit.ROVR4
#define ROVRR1_ROVR5     _canl1.rovrr.bit.ROVR5
#define ROVRR1_ROVR6     _canl1.rovrr.bit.ROVR6
#define ROVRR1_ROVR7     _canl1.rovrr.bit.ROVR7
#define ROVRR1_ROVR8     _canl1.rovrr.bit.ROVR8
#define ROVRR1_ROVR9     _canl1.rovrr.bit.ROVR9
#define ROVRR1_ROVR10    _canl1.rovrr.bit.ROVR10
#define ROVRR1_ROVR11    _canl1.rovrr.bit.ROVR11
#define ROVRR1_ROVR12    _canl1.rovrr.bit.ROVR12
#define ROVRR1_ROVR13    _canl1.rovrr.bit.ROVR13
#define ROVRR1_ROVR14    _canl1.rovrr.bit.ROVR14
#define ROVRR1_ROVR15    _canl1.rovrr.bit.ROVR15

#define RIER1            _canl1.rier.word
#define RIER1_RIE0       _canl1.rier.bit.RIE0
#define RIER1_RIE1       _canl1.rier.bit.RIE1
#define RIER1_RIE2       _canl1.rier.bit.RIE2
#define RIER1_RIE3       _canl1.rier.bit.RIE3
#define RIER1_RIE4       _canl1.rier.bit.RIE4
#define RIER1_RIE5       _canl1.rier.bit.RIE5
#define RIER1_RIE6       _canl1.rier.bit.RIE6
#define RIER1_RIE7       _canl1.rier.bit.RIE7
#define RIER1_RIE8       _canl1.rier.bit.RIE8
#define RIER1_RIE9       _canl1.rier.bit.RIE9
#define RIER1_RIE10      _canl1.rier.bit.RIE10
#define RIER1_RIE11      _canl1.rier.bit.RIE11
#define RIER1_RIE12      _canl1.rier.bit.RIE12
#define RIER1_RIE13      _canl1.rier.bit.RIE13
#define RIER1_RIE14      _canl1.rier.bit.RIE14
#define RIER1_RIE15      _canl1.rier.bit.RIE15

/* CAN2 macros */
#define BVALR2           _canl2.bvalr.word
#define BVALR2_BVAL0     _canl2.bvalr.bit.BVAL0
#define BVALR2_BVAL1     _canl2.bvalr.bit.BVAL1
#define BVALR2_BVAL2     _canl2.bvalr.bit.BVAL2
#define BVALR2_BVAL3     _canl2.bvalr.bit.BVAL3
#define BVALR2_BVAL4     _canl2.bvalr.bit.BVAL4
#define BVALR2_BVAL5     _canl2.bvalr.bit.BVAL5
#define BVALR2_BVAL6     _canl2.bvalr.bit.BVAL6
#define BVALR2_BVAL7     _canl2.bvalr.bit.BVAL7
#define BVALR2_BVAL8     _canl2.bvalr.bit.BVAL8
#define BVALR2_BVAL9     _canl2.bvalr.bit.BVAL9
#define BVALR2_BVAL10    _canl2.bvalr.bit.BVAL10
#define BVALR2_BVAL11    _canl2.bvalr.bit.BVAL11
#define BVALR2_BVAL12    _canl2.bvalr.bit.BVAL12
#define BVALR2_BVAL13    _canl2.bvalr.bit.BVAL13
#define BVALR2_BVAL14    _canl2.bvalr.bit.BVAL14
#define BVALR2_BVAL15    _canl2.bvalr.bit.BVAL15

#define TREQR2           _canl2.treqr.word
#define TREQR2_TREQ0     _canl2.treqr.bit.TREQ0
#define TREQR2_TREQ1     _canl2.treqr.bit.TREQ1
#define TREQR2_TREQ2     _canl2.treqr.bit.TREQ2
#define TREQR2_TREQ3     _canl2.treqr.bit.TREQ3
#define TREQR2_TREQ4     _canl2.treqr.bit.TREQ4
#define TREQR2_TREQ5     _canl2.treqr.bit.TREQ5
#define TREQR2_TREQ6     _canl2.treqr.bit.TREQ6
#define TREQR2_TREQ7     _canl2.treqr.bit.TREQ7
#define TREQR2_TREQ8     _canl2.treqr.bit.TREQ8
#define TREQR2_TREQ9     _canl2.treqr.bit.TREQ9
#define TREQR2_TREQ10    _canl2.treqr.bit.TREQ10
#define TREQR2_TREQ11    _canl2.treqr.bit.TREQ11
#define TREQR2_TREQ12    _canl2.treqr.bit.TREQ12
#define TREQR2_TREQ13    _canl2.treqr.bit.TREQ13
#define TREQR2_TREQ14    _canl2.treqr.bit.TREQ14
#define TREQR2_TREQ15    _canl2.treqr.bit.TREQ15

#define TCANR2           _canl2.tcanr.word
#define TCANR2_TCAN0     _canl2.tcanr.bit.TCAN0
#define TCANR2_TCAN1     _canl2.tcanr.bit.TCAN1
#define TCANR2_TCAN2     _canl2.tcanr.bit.TCAN2
#define TCANR2_TCAN3     _canl2.tcanr.bit.TCAN3
#define TCANR2_TCAN4     _canl2.tcanr.bit.TCAN4
#define TCANR2_TCAN5     _canl2.tcanr.bit.TCAN5
#define TCANR2_TCAN6     _canl2.tcanr.bit.TCAN6
#define TCANR2_TCAN7     _canl2.tcanr.bit.TCAN7
#define TCANR2_TCAN8     _canl2.tcanr.bit.TCAN8
#define TCANR2_TCAN9     _canl2.tcanr.bit.TCAN9
#define TCANR2_TCAN10    _canl2.tcanr.bit.TCAN10
#define TCANR2_TCAN11    _canl2.tcanr.bit.TCAN11
#define TCANR2_TCAN12    _canl2.tcanr.bit.TCAN12
#define TCANR2_TCAN13    _canl2.tcanr.bit.TCAN13
#define TCANR2_TCAN14    _canl2.tcanr.bit.TCAN14
#define TCANR2_TCAN15    _canl2.tcanr.bit.TCAN15

#define TCR2             _canl2.tcr.word
#define TCR2_TC0         _canl2.tcr.bit.TC0
#define TCR2_TC1         _canl2.tcr.bit.TC1
#define TCR2_TC2         _canl2.tcr.bit.TC2
#define TCR2_TC3         _canl2.tcr.bit.TC3
#define TCR2_TC4         _canl2.tcr.bit.TC4
#define TCR2_TC5         _canl2.tcr.bit.TC5
#define TCR2_TC6         _canl2.tcr.bit.TC6
#define TCR2_TC7         _canl2.tcr.bit.TC7
#define TCR2_TC8         _canl2.tcr.bit.TC8
#define TCR2_TC9         _canl2.tcr.bit.TC9
#define TCR2_TC10        _canl2.tcr.bit.TC10
#define TCR2_TC11        _canl2.tcr.bit.TC11
#define TCR2_TC12        _canl2.tcr.bit.TC12
#define TCR2_TC13        _canl2.tcr.bit.TC13
#define TCR2_TC14        _canl2.tcr.bit.TC14
#define TCR2_TC15        _canl2.tcr.bit.TC15

#define RCR2             _canl2.rcr.word
#define RCR2_RC0         _canl2.rcr.bit.RC0
#define RCR2_RC1         _canl2.rcr.bit.RC1
#define RCR2_RC2         _canl2.rcr.bit.RC2
#define RCR2_RC3         _canl2.rcr.bit.RC3
#define RCR2_RC4         _canl2.rcr.bit.RC4
#define RCR2_RC5         _canl2.rcr.bit.RC5
#define RCR2_RC6         _canl2.rcr.bit.RC6
#define RCR2_RC7         _canl2.rcr.bit.RC7
#define RCR2_RC8         _canl2.rcr.bit.RC8
#define RCR2_RC9         _canl2.rcr.bit.RC9
#define RCR2_RC10        _canl2.rcr.bit.RC10
#define RCR2_RC11        _canl2.rcr.bit.RC11
#define RCR2_RC12        _canl2.rcr.bit.RC12
#define RCR2_RC13        _canl2.rcr.bit.RC13
#define RCR2_RC14        _canl2.rcr.bit.RC14
#define RCR2_RC15        _canl2.rcr.bit.RC15

#define RRTRR2           _canl2.rrtrr.word
#define RRTRR2_RRTR0     _canl2.rrtrr.bit.RRTR0
#define RRTRR2_RRTR1     _canl2.rrtrr.bit.RRTR1
#define RRTRR2_RRTR2     _canl2.rrtrr.bit.RRTR2
#define RRTRR2_RRTR3     _canl2.rrtrr.bit.RRTR3
#define RRTRR2_RRTR4     _canl2.rrtrr.bit.RRTR4
#define RRTRR2_RRTR5     _canl2.rrtrr.bit.RRTR5
#define RRTRR2_RRTR6     _canl2.rrtrr.bit.RRTR6
#define RRTRR2_RRTR7     _canl2.rrtrr.bit.RRTR7
#define RRTRR2_RRTR8     _canl2.rrtrr.bit.RRTR8
#define RRTRR2_RRTR9     _canl2.rrtrr.bit.RRTR9
#define RRTRR2_RRTR10    _canl2.rrtrr.bit.RRTR10
#define RRTRR2_RRTR11    _canl2.rrtrr.bit.RRTR11
#define RRTRR2_RRTR12    _canl2.rrtrr.bit.RRTR12
#define RRTRR2_RRTR13    _canl2.rrtrr.bit.RRTR13
#define RRTRR2_RRTR14    _canl2.rrtrr.bit.RRTR14
#define RRTRR2_RRTR15    _canl2.rrtrr.bit.RRTR15

#define ROVRR2           _canl2.rovrr.word
#define ROVRR2_ROVR0     _canl2.rovrr.bit.ROVR0
#define ROVRR2_ROVR1     _canl2.rovrr.bit.ROVR1
#define ROVRR2_ROVR2     _canl2.rovrr.bit.ROVR2
#define ROVRR2_ROVR3     _canl2.rovrr.bit.ROVR3
#define ROVRR2_ROVR4     _canl2.rovrr.bit.ROVR4
#define ROVRR2_ROVR5     _canl2.rovrr.bit.ROVR5
#define ROVRR2_ROVR6     _canl2.rovrr.bit.ROVR6
#define ROVRR2_ROVR7     _canl2.rovrr.bit.ROVR7
#define ROVRR2_ROVR8     _canl2.rovrr.bit.ROVR8
#define ROVRR2_ROVR9     _canl2.rovrr.bit.ROVR9
#define ROVRR2_ROVR10    _canl2.rovrr.bit.ROVR10
#define ROVRR2_ROVR11    _canl2.rovrr.bit.ROVR11
#define ROVRR2_ROVR12    _canl2.rovrr.bit.ROVR12
#define ROVRR2_ROVR13    _canl2.rovrr.bit.ROVR13
#define ROVRR2_ROVR14    _canl2.rovrr.bit.ROVR14
#define ROVRR2_ROVR15    _canl2.rovrr.bit.ROVR15

#define RIER2            _canl2.rier.word
#define RIER2_RIE0       _canl2.rier.bit.RIE0
#define RIER2_RIE1       _canl2.rier.bit.RIE1
#define RIER2_RIE2       _canl2.rier.bit.RIE2
#define RIER2_RIE3       _canl2.rier.bit.RIE3
#define RIER2_RIE4       _canl2.rier.bit.RIE4
#define RIER2_RIE5       _canl2.rier.bit.RIE5
#define RIER2_RIE6       _canl2.rier.bit.RIE6
#define RIER2_RIE7       _canl2.rier.bit.RIE7
#define RIER2_RIE8       _canl2.rier.bit.RIE8
#define RIER2_RIE9       _canl2.rier.bit.RIE9
#define RIER2_RIE10      _canl2.rier.bit.RIE10
#define RIER2_RIE11      _canl2.rier.bit.RIE11
#define RIER2_RIE12      _canl2.rier.bit.RIE12
#define RIER2_RIE13      _canl2.rier.bit.RIE13
#define RIER2_RIE14      _canl2.rier.bit.RIE14
#define RIER2_RIE15      _canl2.rier.bit.RIE15


__IO_EXTERN CANHSTR _canh0;
__IO_EXTERN CANHSTR _canh1;
__IO_EXTERN CANHSTR _canh2;

/* CAN0 macros */
#define CSR0             _canh0.csr.word
#define CSR0_HALT        _canh0.csr.bit.HALT
#define CSR0_NIE         _canh0.csr.bit.NIE
#define CSR0_TOE         _canh0.csr.bit.TOE
#define CSR0_NS0         _canh0.csr.bit.NS0
#define CSR0_NS1         _canh0.csr.bit.NS1
#define CSR0_NT          _canh0.csr.bit.NT
#define CSR0_RS          _canh0.csr.bit.RS
#define CSR0_TS          _canh0.csr.bit.TS
#define CSR0_NS          _canh0.csr.bitc.NS

#define LEIR0            _canh0.leir.byte
#define LEIR0_MBP0       _canh0.leir.bit.MBP0
#define LEIR0_MBP1       _canh0.leir.bit.MBP1
#define LEIR0_MBP2       _canh0.leir.bit.MBP2
#define LEIR0_MBP3       _canh0.leir.bit.MBP3
#define LEIR0_RCE        _canh0.leir.bit.RCE
#define LEIR0_TCE        _canh0.leir.bit.TCE
#define LEIR0_NTE        _canh0.leir.bit.NTE
#define LEIR0_MBP        _canh0.leir.bitc.MBP

#define RTEC0            _canh0.rtec.word
#define RTEC0_REC0       _canh0.rtec.bit.REC0
#define RTEC0_REC1       _canh0.rtec.bit.REC1
#define RTEC0_REC2       _canh0.rtec.bit.REC2
#define RTEC0_REC3       _canh0.rtec.bit.REC3
#define RTEC0_REC4       _canh0.rtec.bit.REC4
#define RTEC0_REC5       _canh0.rtec.bit.REC5
#define RTEC0_REC6       _canh0.rtec.bit.REC6
#define RTEC0_REC7       _canh0.rtec.bit.REC7
#define RTEC0_TEC0       _canh0.rtec.bit.TEC0
#define RTEC0_TEC1       _canh0.rtec.bit.TEC1
#define RTEC0_TEC2       _canh0.rtec.bit.TEC2
#define RTEC0_TEC3       _canh0.rtec.bit.TEC3
#define RTEC0_TEC4       _canh0.rtec.bit.TEC4
#define RTEC0_TEC5       _canh0.rtec.bit.TEC5
#define RTEC0_TEC6       _canh0.rtec.bit.TEC6
#define RTEC0_TEC7       _canh0.rtec.bit.TEC7
#define RTEC0_REC        _canh0.rtec.bitc.REC
#define RTEC0_TEC        _canh0.rtec.bitc.TEC

#define BTR0             _canh0.btr.word
#define BTR0_PSC0        _canh0.btr.bit.PSC0
#define BTR0_PSC1        _canh0.btr.bit.PSC1
#define BTR0_PSC2        _canh0.btr.bit.PSC2
#define BTR0_PSC3        _canh0.btr.bit.PSC3
#define BTR0_PSC4        _canh0.btr.bit.PSC4
#define BTR0_PSC5        _canh0.btr.bit.PSC5
#define BTR0_RSJ0        _canh0.btr.bit.RSJ0
#define BTR0_RSJ1        _canh0.btr.bit.RSJ1
#define BTR0_TS10        _canh0.btr.bit.TS10
#define BTR0_TS11        _canh0.btr.bit.TS11
#define BTR0_TS12        _canh0.btr.bit.TS12
#define BTR0_TS13        _canh0.btr.bit.TS13
#define BTR0_TS20        _canh0.btr.bit.TS20
#define BTR0_TS21        _canh0.btr.bit.TS21
#define BTR0_TS22        _canh0.btr.bit.TS22
#define BTR0_PSC         _canh0.btr.bitc.PSC
#define BTR0_RSJ         _canh0.btr.bitc.RSJ
#define BTR0_TS1         _canh0.btr.bitc.TS1
#define BTR0_TS2         _canh0.btr.bitc.TS2

#define IDER0            _canh0.ider.word
#define IDER0_IDE0       _canh0.ider.bit.IDE0
#define IDER0_IDE1       _canh0.ider.bit.IDE1
#define IDER0_IDE2       _canh0.ider.bit.IDE2
#define IDER0_IDE3       _canh0.ider.bit.IDE3
#define IDER0_IDE4       _canh0.ider.bit.IDE4
#define IDER0_IDE5       _canh0.ider.bit.IDE5
#define IDER0_IDE6       _canh0.ider.bit.IDE6
#define IDER0_IDE7       _canh0.ider.bit.IDE7
#define IDER0_IDE8       _canh0.ider.bit.IDE8
#define IDER0_IDE9       _canh0.ider.bit.IDE9
#define IDER0_IDE10      _canh0.ider.bit.IDE10
#define IDER0_IDE11      _canh0.ider.bit.IDE11
#define IDER0_IDE12      _canh0.ider.bit.IDE12
#define IDER0_IDE13      _canh0.ider.bit.IDE13
#define IDER0_IDE14      _canh0.ider.bit.IDE14
#define IDER0_IDE15      _canh0.ider.bit.IDE15

#define TRTRR0           _canh0.trtrr.word
#define TRTRR0_TRTR0     _canh0.trtrr.bit.TRTR0
#define TRTRR0_TRTR1     _canh0.trtrr.bit.TRTR1
#define TRTRR0_TRTR2     _canh0.trtrr.bit.TRTR2
#define TRTRR0_TRTR3     _canh0.trtrr.bit.TRTR3
#define TRTRR0_TRTR4     _canh0.trtrr.bit.TRTR4
#define TRTRR0_TRTR5     _canh0.trtrr.bit.TRTR5
#define TRTRR0_TRTR6     _canh0.trtrr.bit.TRTR6
#define TRTRR0_TRTR7     _canh0.trtrr.bit.TRTR7
#define TRTRR0_TRTR8     _canh0.trtrr.bit.TRTR8
#define TRTRR0_TRTR9     _canh0.trtrr.bit.TRTR9
#define TRTRR0_TRTR10    _canh0.trtrr.bit.TRTR10
#define TRTRR0_TRTR11    _canh0.trtrr.bit.TRTR11
#define TRTRR0_TRTR12    _canh0.trtrr.bit.TRTR12
#define TRTRR0_TRTR13    _canh0.trtrr.bit.TRTR13
#define TRTRR0_TRTR14    _canh0.trtrr.bit.TRTR14
#define TRTRR0_TRTR15    _canh0.trtrr.bit.TRTR15

#define RFWTR0           _canh0.rfwtr.word
#define RFWTR0_RFWT0     _canh0.rfwtr.bit.RFWT0
#define RFWTR0_RFWT1     _canh0.rfwtr.bit.RFWT1
#define RFWTR0_RFWT2     _canh0.rfwtr.bit.RFWT2
#define RFWTR0_RFWT3     _canh0.rfwtr.bit.RFWT3
#define RFWTR0_RFWT4     _canh0.rfwtr.bit.RFWT4
#define RFWTR0_RFWT5     _canh0.rfwtr.bit.RFWT5
#define RFWTR0_RFWT6     _canh0.rfwtr.bit.RFWT6
#define RFWTR0_RFWT7     _canh0.rfwtr.bit.RFWT7
#define RFWTR0_RFWT8     _canh0.rfwtr.bit.RFWT8
#define RFWTR0_RFWT9     _canh0.rfwtr.bit.RFWT9
#define RFWTR0_RFWT10    _canh0.rfwtr.bit.RFWT10
#define RFWTR0_RFWT11    _canh0.rfwtr.bit.RFWT11
#define RFWTR0_RFWT12    _canh0.rfwtr.bit.RFWT12
#define RFWTR0_RFWT13    _canh0.rfwtr.bit.RFWT13
#define RFWTR0_RFWT14    _canh0.rfwtr.bit.RFWT14
#define RFWTR0_RFWT15    _canh0.rfwtr.bit.RFWT15

#define TIER0            _canh0.tier.word
#define TIER0_TIE0       _canh0.tier.bit.TIE0
#define TIER0_TIE1       _canh0.tier.bit.TIE1
#define TIER0_TIE2       _canh0.tier.bit.TIE2
#define TIER0_TIE3       _canh0.tier.bit.TIE3
#define TIER0_TIE4       _canh0.tier.bit.TIE4
#define TIER0_TIE5       _canh0.tier.bit.TIE5
#define TIER0_TIE6       _canh0.tier.bit.TIE6
#define TIER0_TIE7       _canh0.tier.bit.TIE7
#define TIER0_TIE8       _canh0.tier.bit.TIE8
#define TIER0_TIE9       _canh0.tier.bit.TIE9
#define TIER0_TIE10      _canh0.tier.bit.TIE10
#define TIER0_TIE11      _canh0.tier.bit.TIE11
#define TIER0_TIE12      _canh0.tier.bit.TIE12
#define TIER0_TIE13      _canh0.tier.bit.TIE13
#define TIER0_TIE14      _canh0.tier.bit.TIE14
#define TIER0_TIE15      _canh0.tier.bit.TIE15

#define AMSR0            _canh0.amsr.dword
#define AMSR0_AMS0       _canh0.amsr.bitc.AMS0
#define AMSR0_AMS1       _canh0.amsr.bitc.AMS1
#define AMSR0_AMS2       _canh0.amsr.bitc.AMS2
#define AMSR0_AMS3       _canh0.amsr.bitc.AMS3
#define AMSR0_AMS4       _canh0.amsr.bitc.AMS4
#define AMSR0_AMS5       _canh0.amsr.bitc.AMS5
#define AMSR0_AMS6       _canh0.amsr.bitc.AMS6
#define AMSR0_AMS7       _canh0.amsr.bitc.AMS7
#define AMSR0_AMS8       _canh0.amsr.bitc.AMS8
#define AMSR0_AMS9       _canh0.amsr.bitc.AMS9
#define AMSR0_AMS10      _canh0.amsr.bitc.AMS10
#define AMSR0_AMS11      _canh0.amsr.bitc.AMS11
#define AMSR0_AMS12      _canh0.amsr.bitc.AMS12
#define AMSR0_AMS13      _canh0.amsr.bitc.AMS13
#define AMSR0_AMS14      _canh0.amsr.bitc.AMS14
#define AMSR0_AMS15      _canh0.amsr.bitc.AMS15

#define AMR00            _canh0.amr[0].word  /* AMR0 for CAN0 (std ID bits) */
#define AMR10            _canh0.amr[1].word  /* AMR1 for CAN0 (std ID bits) */
#define AMRX00           _canh0.amr[0].dword /* AMR0 for CAN0 (ext ID bits) */
#define AMRX10           _canh0.amr[1].dword /* AMR1 for CAN0 (ext ID bits) */

/* CAN1 macros */
#define CSR1             _canh1.csr.word
#define CSR1_HALT        _canh1.csr.bit.HALT
#define CSR1_NIE         _canh1.csr.bit.NIE
#define CSR1_TOE         _canh1.csr.bit.TOE
#define CSR1_NS0         _canh1.csr.bit.NS0
#define CSR1_NS1         _canh1.csr.bit.NS1
#define CSR1_NT          _canh1.csr.bit.NT
#define CSR1_RS          _canh1.csr.bit.RS
#define CSR1_TS          _canh1.csr.bit.TS
#define CSR1_NS          _canh1.csr.bitc.NS

#define LEIR1            _canh1.leir.byte
#define LEIR1_MBP0       _canh1.leir.bit.MBP0
#define LEIR1_MBP1       _canh1.leir.bit.MBP1
#define LEIR1_MBP2       _canh1.leir.bit.MBP2
#define LEIR1_MBP3       _canh1.leir.bit.MBP3
#define LEIR1_RCE        _canh1.leir.bit.RCE
#define LEIR1_TCE        _canh1.leir.bit.TCE
#define LEIR1_NTE        _canh1.leir.bit.NTE
#define LEIR1_MBP        _canh1.leir.bitc.MBP

#define RTEC1            _canh1.rtec.word
#define RTEC1_REC0       _canh1.rtec.bit.REC0
#define RTEC1_REC1       _canh1.rtec.bit.REC1
#define RTEC1_REC2       _canh1.rtec.bit.REC2
#define RTEC1_REC3       _canh1.rtec.bit.REC3
#define RTEC1_REC4       _canh1.rtec.bit.REC4
#define RTEC1_REC5       _canh1.rtec.bit.REC5
#define RTEC1_REC6       _canh1.rtec.bit.REC6
#define RTEC1_REC7       _canh1.rtec.bit.REC7
#define RTEC1_TEC0       _canh1.rtec.bit.TEC0
#define RTEC1_TEC1       _canh1.rtec.bit.TEC1
#define RTEC1_TEC2       _canh1.rtec.bit.TEC2
#define RTEC1_TEC3       _canh1.rtec.bit.TEC3
#define RTEC1_TEC4       _canh1.rtec.bit.TEC4
#define RTEC1_TEC5       _canh1.rtec.bit.TEC5
#define RTEC1_TEC6       _canh1.rtec.bit.TEC6
#define RTEC1_TEC7       _canh1.rtec.bit.TEC7
#define RTEC1_REC        _canh1.rtec.bitc.REC
#define RTEC1_TEC        _canh1.rtec.bitc.TEC

#define BTR1             _canh1.btr.word
#define BTR1_PSC0        _canh1.btr.bit.PSC0
#define BTR1_PSC1        _canh1.btr.bit.PSC1
#define BTR1_PSC2        _canh1.btr.bit.PSC2
#define BTR1_PSC3        _canh1.btr.bit.PSC3
#define BTR1_PSC4        _canh1.btr.bit.PSC4
#define BTR1_PSC5        _canh1.btr.bit.PSC5
#define BTR1_RSJ0        _canh1.btr.bit.RSJ0
#define BTR1_RSJ1        _canh1.btr.bit.RSJ1
#define BTR1_TS10        _canh1.btr.bit.TS10
#define BTR1_TS11        _canh1.btr.bit.TS11
#define BTR1_TS12        _canh1.btr.bit.TS12
#define BTR1_TS13        _canh1.btr.bit.TS13
#define BTR1_TS20        _canh1.btr.bit.TS20
#define BTR1_TS21        _canh1.btr.bit.TS21
#define BTR1_TS22        _canh1.btr.bit.TS22
#define BTR1_PSC         _canh1.btr.bitc.PSC
#define BTR1_RSJ         _canh1.btr.bitc.RSJ
#define BTR1_TS1         _canh1.btr.bitc.TS1
#define BTR1_TS2         _canh1.btr.bitc.TS2

#define IDER1            _canh1.ider.word
#define IDER1_IDE0       _canh1.ider.bit.IDE0
#define IDER1_IDE1       _canh1.ider.bit.IDE1
#define IDER1_IDE2       _canh1.ider.bit.IDE2
#define IDER1_IDE3       _canh1.ider.bit.IDE3
#define IDER1_IDE4       _canh1.ider.bit.IDE4
#define IDER1_IDE5       _canh1.ider.bit.IDE5
#define IDER1_IDE6       _canh1.ider.bit.IDE6
#define IDER1_IDE7       _canh1.ider.bit.IDE7
#define IDER1_IDE8       _canh1.ider.bit.IDE8
#define IDER1_IDE9       _canh1.ider.bit.IDE9
#define IDER1_IDE10      _canh1.ider.bit.IDE10
#define IDER1_IDE11      _canh1.ider.bit.IDE11
#define IDER1_IDE12      _canh1.ider.bit.IDE12
#define IDER1_IDE13      _canh1.ider.bit.IDE13
#define IDER1_IDE14      _canh1.ider.bit.IDE14
#define IDER1_IDE15      _canh1.ider.bit.IDE15

#define TRTRR1           _canh1.trtrr.word
#define TRTRR1_TRTR0     _canh1.trtrr.bit.TRTR0
#define TRTRR1_TRTR1     _canh1.trtrr.bit.TRTR1
#define TRTRR1_TRTR2     _canh1.trtrr.bit.TRTR2
#define TRTRR1_TRTR3     _canh1.trtrr.bit.TRTR3
#define TRTRR1_TRTR4     _canh1.trtrr.bit.TRTR4
#define TRTRR1_TRTR5     _canh1.trtrr.bit.TRTR5
#define TRTRR1_TRTR6     _canh1.trtrr.bit.TRTR6
#define TRTRR1_TRTR7     _canh1.trtrr.bit.TRTR7
#define TRTRR1_TRTR8     _canh1.trtrr.bit.TRTR8
#define TRTRR1_TRTR9     _canh1.trtrr.bit.TRTR9
#define TRTRR1_TRTR10    _canh1.trtrr.bit.TRTR10
#define TRTRR1_TRTR11    _canh1.trtrr.bit.TRTR11
#define TRTRR1_TRTR12    _canh1.trtrr.bit.TRTR12
#define TRTRR1_TRTR13    _canh1.trtrr.bit.TRTR13
#define TRTRR1_TRTR14    _canh1.trtrr.bit.TRTR14
#define TRTRR1_TRTR15    _canh1.trtrr.bit.TRTR15

#define RFWTR1           _canh1.rfwtr.word
#define RFWTR1_RFWT0     _canh1.rfwtr.bit.RFWT0
#define RFWTR1_RFWT1     _canh1.rfwtr.bit.RFWT1
#define RFWTR1_RFWT2     _canh1.rfwtr.bit.RFWT2
#define RFWTR1_RFWT3     _canh1.rfwtr.bit.RFWT3
#define RFWTR1_RFWT4     _canh1.rfwtr.bit.RFWT4
#define RFWTR1_RFWT5     _canh1.rfwtr.bit.RFWT5
#define RFWTR1_RFWT6     _canh1.rfwtr.bit.RFWT6
#define RFWTR1_RFWT7     _canh1.rfwtr.bit.RFWT7
#define RFWTR1_RFWT8     _canh1.rfwtr.bit.RFWT8
#define RFWTR1_RFWT9     _canh1.rfwtr.bit.RFWT9
#define RFWTR1_RFWT10    _canh1.rfwtr.bit.RFWT10
#define RFWTR1_RFWT11    _canh1.rfwtr.bit.RFWT11
#define RFWTR1_RFWT12    _canh1.rfwtr.bit.RFWT12
#define RFWTR1_RFWT13    _canh1.rfwtr.bit.RFWT13
#define RFWTR1_RFWT14    _canh1.rfwtr.bit.RFWT14
#define RFWTR1_RFWT15    _canh1.rfwtr.bit.RFWT15

#define TIER1            _canh1.tier.word
#define TIER1_TIE0       _canh1.tier.bit.TIE0
#define TIER1_TIE1       _canh1.tier.bit.TIE1
#define TIER1_TIE2       _canh1.tier.bit.TIE2
#define TIER1_TIE3       _canh1.tier.bit.TIE3
#define TIER1_TIE4       _canh1.tier.bit.TIE4
#define TIER1_TIE5       _canh1.tier.bit.TIE5
#define TIER1_TIE6       _canh1.tier.bit.TIE6
#define TIER1_TIE7       _canh1.tier.bit.TIE7
#define TIER1_TIE8       _canh1.tier.bit.TIE8
#define TIER1_TIE9       _canh1.tier.bit.TIE9
#define TIER1_TIE10      _canh1.tier.bit.TIE10
#define TIER1_TIE11      _canh1.tier.bit.TIE11
#define TIER1_TIE12      _canh1.tier.bit.TIE12
#define TIER1_TIE13      _canh1.tier.bit.TIE13
#define TIER1_TIE14      _canh1.tier.bit.TIE14
#define TIER1_TIE15      _canh1.tier.bit.TIE15

#define AMSR1            _canh1.amsr.dword
#define AMSR1_AMS0       _canh1.amsr.bitc.AMS0
#define AMSR1_AMS1       _canh1.amsr.bitc.AMS1
#define AMSR1_AMS2       _canh1.amsr.bitc.AMS2
#define AMSR1_AMS3       _canh1.amsr.bitc.AMS3
#define AMSR1_AMS4       _canh1.amsr.bitc.AMS4
#define AMSR1_AMS5       _canh1.amsr.bitc.AMS5
#define AMSR1_AMS6       _canh1.amsr.bitc.AMS6
#define AMSR1_AMS7       _canh1.amsr.bitc.AMS7
#define AMSR1_AMS8       _canh1.amsr.bitc.AMS8
#define AMSR1_AMS9       _canh1.amsr.bitc.AMS9
#define AMSR1_AMS10      _canh1.amsr.bitc.AMS10
#define AMSR1_AMS11      _canh1.amsr.bitc.AMS11
#define AMSR1_AMS12      _canh1.amsr.bitc.AMS12
#define AMSR1_AMS13      _canh1.amsr.bitc.AMS13
#define AMSR1_AMS14      _canh1.amsr.bitc.AMS14
#define AMSR1_AMS15      _canh1.amsr.bitc.AMS15

#define AMR01            _canh1.amr[0].word  /* AMR0 for CAN1 (std ID bits) */
#define AMR11            _canh1.amr[1].word  /* AMR1 for CAN1 (std ID bits) */
#define AMRX01           _canh1.amr[0].dword /* AMR0 for CAN1 (ext ID bits) */
#define AMRX11           _canh1.amr[1].dword /* AMR1 for CAN1 (ext ID bits) */

/* CAN2 macros */
#define CSR2             _canh2.csr.word
#define CSR2_HALT        _canh2.csr.bit.HALT
#define CSR2_NIE         _canh2.csr.bit.NIE
#define CSR2_TOE         _canh2.csr.bit.TOE
#define CSR2_NS0         _canh2.csr.bit.NS0
#define CSR2_NS1         _canh2.csr.bit.NS1
#define CSR2_NT          _canh2.csr.bit.NT
#define CSR2_RS          _canh2.csr.bit.RS
#define CSR2_TS          _canh2.csr.bit.TS
#define CSR2_NS          _canh2.csr.bitc.NS

#define LEIR2            _canh2.leir.byte
#define LEIR2_MBP0       _canh2.leir.bit.MBP0
#define LEIR2_MBP1       _canh2.leir.bit.MBP1
#define LEIR2_MBP2       _canh2.leir.bit.MBP2
#define LEIR2_MBP3       _canh2.leir.bit.MBP3
#define LEIR2_RCE        _canh2.leir.bit.RCE
#define LEIR2_TCE        _canh2.leir.bit.TCE
#define LEIR2_NTE        _canh2.leir.bit.NTE
#define LEIR2_MBP        _canh2.leir.bitc.MBP

#define RTEC2            _canh2.rtec.word
#define RTEC2_REC0       _canh2.rtec.bit.REC0
#define RTEC2_REC1       _canh2.rtec.bit.REC1
#define RTEC2_REC2       _canh2.rtec.bit.REC2
#define RTEC2_REC3       _canh2.rtec.bit.REC3
#define RTEC2_REC4       _canh2.rtec.bit.REC4
#define RTEC2_REC5       _canh2.rtec.bit.REC5
#define RTEC2_REC6       _canh2.rtec.bit.REC6
#define RTEC2_REC7       _canh2.rtec.bit.REC7
#define RTEC2_TEC0       _canh2.rtec.bit.TEC0
#define RTEC2_TEC1       _canh2.rtec.bit.TEC1
#define RTEC2_TEC2       _canh2.rtec.bit.TEC2
#define RTEC2_TEC3       _canh2.rtec.bit.TEC3
#define RTEC2_TEC4       _canh2.rtec.bit.TEC4
#define RTEC2_TEC5       _canh2.rtec.bit.TEC5
#define RTEC2_TEC6       _canh2.rtec.bit.TEC6
#define RTEC2_TEC7       _canh2.rtec.bit.TEC7
#define RTEC2_REC        _canh2.rtec.bitc.REC
#define RTEC2_TEC        _canh2.rtec.bitc.TEC

#define BTR2             _canh2.btr.word
#define BTR2_PSC0        _canh2.btr.bit.PSC0
#define BTR2_PSC1        _canh2.btr.bit.PSC1
#define BTR2_PSC2        _canh2.btr.bit.PSC2
#define BTR2_PSC3        _canh2.btr.bit.PSC3
#define BTR2_PSC4        _canh2.btr.bit.PSC4
#define BTR2_PSC5        _canh2.btr.bit.PSC5
#define BTR2_RSJ0        _canh2.btr.bit.RSJ0
#define BTR2_RSJ1        _canh2.btr.bit.RSJ1
#define BTR2_TS10        _canh2.btr.bit.TS10
#define BTR2_TS11        _canh2.btr.bit.TS11
#define BTR2_TS12        _canh2.btr.bit.TS12
#define BTR2_TS13        _canh2.btr.bit.TS13
#define BTR2_TS20        _canh2.btr.bit.TS20
#define BTR2_TS21        _canh2.btr.bit.TS21
#define BTR2_TS22        _canh2.btr.bit.TS22
#define BTR2_PSC         _canh2.btr.bitc.PSC
#define BTR2_RSJ         _canh2.btr.bitc.RSJ
#define BTR2_TS1         _canh2.btr.bitc.TS1
#define BTR2_TS2         _canh2.btr.bitc.TS2

#define IDER2            _canh2.ider.word
#define IDER2_IDE0       _canh2.ider.bit.IDE0
#define IDER2_IDE1       _canh2.ider.bit.IDE1
#define IDER2_IDE2       _canh2.ider.bit.IDE2
#define IDER2_IDE3       _canh2.ider.bit.IDE3
#define IDER2_IDE4       _canh2.ider.bit.IDE4
#define IDER2_IDE5       _canh2.ider.bit.IDE5
#define IDER2_IDE6       _canh2.ider.bit.IDE6
#define IDER2_IDE7       _canh2.ider.bit.IDE7
#define IDER2_IDE8       _canh2.ider.bit.IDE8
#define IDER2_IDE9       _canh2.ider.bit.IDE9
#define IDER2_IDE10      _canh2.ider.bit.IDE10
#define IDER2_IDE11      _canh2.ider.bit.IDE11
#define IDER2_IDE12      _canh2.ider.bit.IDE12
#define IDER2_IDE13      _canh2.ider.bit.IDE13
#define IDER2_IDE14      _canh2.ider.bit.IDE14
#define IDER2_IDE15      _canh2.ider.bit.IDE15

#define TRTRR2           _canh2.trtrr.word
#define TRTRR2_TRTR0     _canh2.trtrr.bit.TRTR0
#define TRTRR2_TRTR1     _canh2.trtrr.bit.TRTR1
#define TRTRR2_TRTR2     _canh2.trtrr.bit.TRTR2
#define TRTRR2_TRTR3     _canh2.trtrr.bit.TRTR3
#define TRTRR2_TRTR4     _canh2.trtrr.bit.TRTR4
#define TRTRR2_TRTR5     _canh2.trtrr.bit.TRTR5
#define TRTRR2_TRTR6     _canh2.trtrr.bit.TRTR6
#define TRTRR2_TRTR7     _canh2.trtrr.bit.TRTR7
#define TRTRR2_TRTR8     _canh2.trtrr.bit.TRTR8
#define TRTRR2_TRTR9     _canh2.trtrr.bit.TRTR9
#define TRTRR2_TRTR10    _canh2.trtrr.bit.TRTR10
#define TRTRR2_TRTR11    _canh2.trtrr.bit.TRTR11
#define TRTRR2_TRTR12    _canh2.trtrr.bit.TRTR12
#define TRTRR2_TRTR13    _canh2.trtrr.bit.TRTR13
#define TRTRR2_TRTR14    _canh2.trtrr.bit.TRTR14
#define TRTRR2_TRTR15    _canh2.trtrr.bit.TRTR15

#define RFWTR2           _canh2.rfwtr.word
#define RFWTR2_RFWT0     _canh2.rfwtr.bit.RFWT0
#define RFWTR2_RFWT1     _canh2.rfwtr.bit.RFWT1
#define RFWTR2_RFWT2     _canh2.rfwtr.bit.RFWT2
#define RFWTR2_RFWT3     _canh2.rfwtr.bit.RFWT3
#define RFWTR2_RFWT4     _canh2.rfwtr.bit.RFWT4
#define RFWTR2_RFWT5     _canh2.rfwtr.bit.RFWT5
#define RFWTR2_RFWT6     _canh2.rfwtr.bit.RFWT6
#define RFWTR2_RFWT7     _canh2.rfwtr.bit.RFWT7
#define RFWTR2_RFWT8     _canh2.rfwtr.bit.RFWT8
#define RFWTR2_RFWT9     _canh2.rfwtr.bit.RFWT9
#define RFWTR2_RFWT10    _canh2.rfwtr.bit.RFWT10
#define RFWTR2_RFWT11    _canh2.rfwtr.bit.RFWT11
#define RFWTR2_RFWT12    _canh2.rfwtr.bit.RFWT12
#define RFWTR2_RFWT13    _canh2.rfwtr.bit.RFWT13
#define RFWTR2_RFWT14    _canh2.rfwtr.bit.RFWT14
#define RFWTR2_RFWT15    _canh2.rfwtr.bit.RFWT15

#define TIER2            _canh2.tier.word
#define TIER2_TIE0       _canh2.tier.bit.TIE0
#define TIER2_TIE1       _canh2.tier.bit.TIE1
#define TIER2_TIE2       _canh2.tier.bit.TIE2
#define TIER2_TIE3       _canh2.tier.bit.TIE3
#define TIER2_TIE4       _canh2.tier.bit.TIE4
#define TIER2_TIE5       _canh2.tier.bit.TIE5
#define TIER2_TIE6       _canh2.tier.bit.TIE6
#define TIER2_TIE7       _canh2.tier.bit.TIE7
#define TIER2_TIE8       _canh2.tier.bit.TIE8
#define TIER2_TIE9       _canh2.tier.bit.TIE9
#define TIER2_TIE10      _canh2.tier.bit.TIE10
#define TIER2_TIE11      _canh2.tier.bit.TIE11
#define TIER2_TIE12      _canh2.tier.bit.TIE12
#define TIER2_TIE13      _canh2.tier.bit.TIE13
#define TIER2_TIE14      _canh2.tier.bit.TIE14
#define TIER2_TIE15      _canh2.tier.bit.TIE15

#define AMSR2            _canh2.amsr.dword
#define AMSR2_AMS0       _canh2.amsr.bitc.AMS0
#define AMSR2_AMS1       _canh2.amsr.bitc.AMS1
#define AMSR2_AMS2       _canh2.amsr.bitc.AMS2
#define AMSR2_AMS3       _canh2.amsr.bitc.AMS3
#define AMSR2_AMS4       _canh2.amsr.bitc.AMS4
#define AMSR2_AMS5       _canh2.amsr.bitc.AMS5
#define AMSR2_AMS6       _canh2.amsr.bitc.AMS6
#define AMSR2_AMS7       _canh2.amsr.bitc.AMS7
#define AMSR2_AMS8       _canh2.amsr.bitc.AMS8
#define AMSR2_AMS9       _canh2.amsr.bitc.AMS9
#define AMSR2_AMS10      _canh2.amsr.bitc.AMS10
#define AMSR2_AMS11      _canh2.amsr.bitc.AMS11
#define AMSR2_AMS12      _canh2.amsr.bitc.AMS12
#define AMSR2_AMS13      _canh2.amsr.bitc.AMS13
#define AMSR2_AMS14      _canh2.amsr.bitc.AMS14
#define AMSR2_AMS15      _canh2.amsr.bitc.AMS15

#define AMR02            _canh2.amr[0].word  /* AMR0 for CAN0 (std ID bits) */
#define AMR12            _canh2.amr[1].word  /* AMR1 for CAN0 (std ID bits) */
#define AMRX02           _canh2.amr[0].dword /* AMR0 for CAN0 (ext ID bits) */
#define AMRX12           _canh2.amr[1].dword /* AMR1 for CAN0 (ext ID bits) */

__IO_EXTERN CANMSTR _canm0;
__IO_EXTERN CANMSTR _canm1;
__IO_EXTERN CANMSTR _canm2;

/* CAN0 macros */
#define IDR0(buf)            (_canm0.idr[buf].word)
#define IDRX0(buf)           (_canm0.idr[buf].dword)

#define DLCR0(buf)           (_canm0.dlcr[buf].word)
#define DLCR0_DLC0(buf)      (_canm0.dlcr[buf].bit.DLC0)
#define DLCR0_DLC1(buf)      (_canm0.dlcr[buf].bit.DLC1)
#define DLCR0_DLC2(buf)      (_canm0.dlcr[buf].bit.DLC2)
#define DLCR0_DLC3(buf)      (_canm0.dlcr[buf].bit.DLC3)

#define DTR0_BPTR(  buf)     (_canm0.dtr[buf].bytes )
#define DTR0_WPTR(  buf)     (_canm0.dtr[buf].words )
#define DTR0_LWPTR( buf)     (_canm0.dtr[buf].dwords)
#define DTR0_CPTR(  buf)     (_canm0.dtr[buf].chars )
#define DTR0_IPTR(  buf)     (_canm0.dtr[buf].ints  )
#define DTR0_LPTR(  buf)     (_canm0.dtr[buf].longs )

#define DTR0_BYTE(  buf,i)   (_canm0.dtr[buf].bytes  [i])
#define DTR0_WORD(  buf,i)   (_canm0.dtr[buf].words  [i])
#define DTR0_DWORD( buf,i)   (_canm0.dtr[buf].dwords [i])
#define DTR0_CHAR(  buf,i)   (_canm0.dtr[buf].chars  [i])
#define DTR0_INT(   buf,i)   (_canm0.dtr[buf].ints   [i])
#define DTR0_LONGS( buf,i)   (_canm0.dtr[buf].longs  [i])
#define DTR0_FLOATS(buf,i)   (_canm0.dtr[buf].floats [i])
#define DTR0_DOUBLE(buf  )   (_canm0.dtr[buf].adouble   )

/* CAN1 macros */
#define IDR1(buf)            (_canm1.idr[buf].word)
#define IDRX1(buf)           (_canm1.idr[buf].dword)

#define DLCR1(buf)           (_canm1.dlcr[buf].word)
#define DLCR1_DLC0(buf)      (_canm1.dlcr[buf].bit.DLC0)
#define DLCR1_DLC1(buf)      (_canm1.dlcr[buf].bit.DLC1)
#define DLCR1_DLC2(buf)      (_canm1.dlcr[buf].bit.DLC2)
#define DLCR1_DLC3(buf)      (_canm1.dlcr[buf].bit.DLC3)

#define DTR1_BPTR(  buf)     (_canm1.dtr[buf].bytes )
#define DTR1_WPTR(  buf)     (_canm1.dtr[buf].words )
#define DTR1_DWPTR( buf)     (_canm1.dtr[buf].dwords)
#define DTR1_CPTR(  buf)     (_canm1.dtr[buf].chars )
#define DTR1_IPTR(  buf)     (_canm1.dtr[buf].ints  )
#define DTR1_LPTR(  buf)     (_canm1.dtr[buf].longs )

#define DTR1_BYTE(  buf,i)   (_canm1.dtr[buf].bytes  [i])
#define DTR1_WORD(  buf,i)   (_canm1.dtr[buf].words  [i])
#define DTR1_DWORD( buf,i)   (_canm1.dtr[buf].dwords [i])
#define DTR1_CHAR(  buf,i)   (_canm1.dtr[buf].chars  [i])
#define DTR1_INT(   buf,i)   (_canm1.dtr[buf].ints   [i])
#define DTR1_LONGS( buf,i)   (_canm1.dtr[buf].longs  [i])
#define DTR1_FLOATS(buf,i)   (_canm1.dtr[buf].floats [i])
#define DTR1_DOUBLE(buf  )   (_canm1.dtr[buf].adouble   )

/* CAN2 macros */
#define IDR2(buf)            (_canm2.idr[buf].word)
#define IDRX2(buf)           (_canm2.idr[buf].dword)

#define DLCR2(buf)           (_canm2.dlcr[buf].word)
#define DLCR2_DLC0(buf)      (_canm2.dlcr[buf].bit.DLC0)
#define DLCR2_DLC1(buf)      (_canm2.dlcr[buf].bit.DLC1)
#define DLCR2_DLC2(buf)      (_canm2.dlcr[buf].bit.DLC2)
#define DLCR2_DLC3(buf)      (_canm2.dlcr[buf].bit.DLC3)

#define DTR2_BPTR(  buf)     (_canm2.dtr[buf].bytes )
#define DTR2_WPTR(  buf)     (_canm2.dtr[buf].words )
#define DTR2_LWPTR( buf)     (_canm2.dtr[buf].dwords)
#define DTR2_CPTR(  buf)     (_canm2.dtr[buf].chars )
#define DTR2_IPTR(  buf)     (_canm2.dtr[buf].ints  )
#define DTR2_LPTR(  buf)     (_canm2.dtr[buf].longs )

#define DTR2_BYTE(  buf,i)   (_canm2.dtr[buf].bytes  [i])
#define DTR2_WORD(  buf,i)   (_canm2.dtr[buf].words  [i])
#define DTR2_DWORD( buf,i)   (_canm2.dtr[buf].dwords [i])
#define DTR2_CHAR(  buf,i)   (_canm2.dtr[buf].chars  [i])
#define DTR2_INT(   buf,i)   (_canm2.dtr[buf].ints   [i])
#define DTR2_LONGS( buf,i)   (_canm2.dtr[buf].longs  [i])
#define DTR2_FLOATS(buf,i)   (_canm2.dtr[buf].floats [i])
#define DTR2_DOUBLE(buf  )   (_canm2.dtr[buf].adouble   )

#endif /* CANMAC */
#endif
#endif                   /* __MB91XXX_H */
