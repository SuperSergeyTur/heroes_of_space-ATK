;*******************************************************
;    MB91360 Series startup routine V3.1
;    ===================================
;
;   Version for MB91F362
;
;   Startup-Routine for MB91F362. Initializes
;   the device after reset and prepares C-operation.
;   Features :
;   - defines all IO variables (includes MB91362.H)
;   - declares memory sections IO,STACK,DATA,CODE,INTVEC
;   - initializes STACK and DATA area (internal RAM)
;   - defines all interrupt-vectors (includes INTVECS.INC)
;   - sets clock for CPU, Resources, ext.Bus and CAN (4MHz only)
;   - starts user code in "main()"
;
;   Startaddress is 0F:4000 (fixed reset entry)
;   Table Base (location of Interrupt-Vectors) is 0F:FC00
;
;   NOTE : This software is subject to the rules of our standard
;   DISCLAIMER, that is delivered with our SW-tools (CD-ROM "Micros"
;   or see our webpage "www.fujitsu-fme.com").
;
;   (c) Fujitsu Microelectronics Europe GmbH 2000
;   Version 3.1
;   MM 02/05/00
;   ME 02/05/01            add ABORT function from MB91F361
;*******************************************************

; Global settings :
; Устанавливаем PLL=32 или 64, т.к. CAN-clock при 48 может принимать значения
; 24, 12, 8 , ... В итоге параметр TQ в CAN не совпадает с параметрами в платах с
; контроллерами MB90 и CAN не работает :
#define PLL 32              // select PLL-Clock (16,32,48 or 64 MHz)
#define SIMULATOR 0         // set to 1 when using the simulator
#define CHANGECS 1          // enable (1) or disable (0) CS-settings
#define STACK_SIZE 0x800-4  // define stack size 2k (3D000...3D7FC)
#define ABORT 0             // enable(1) or disable(0) USER0-Button for ABORT
#define I_RAM 1             // enable(1) or disable(0) copy to I_RAM

;*******************************************************
;   IO Symbol definition
;*******************************************************

#define __IO_DEFINE         // Activate IO assembler definitions
#include "MB91362.h"        // in headerfile

        .export start
        .export __exit
        .export uninitial_int
        .import _main
        .import _exit
        .import __stream_init
        .import _RAM_INIT
        .import _ROM_INIT
#if I_RAM
        .import _RAM_IRAM
        .import _ROM_IRAM
#endif

;*******************************************************
;   Declare STACK (RAM) area and reserve space
;*******************************************************

        .section        STACK, stack, align=4
        .res.b          STACK_SIZE
stack_top:
        .res.w  1

;*******************************************************
;   Interrupt-Vector definition
;*******************************************************

#include "362.inc"

;*******************************************************
;   Fixed Reset Vector (Simulator information only)
;*******************************************************

#if SIMULATOR
        .ORG   0xFFFFC
        .DATA   start           ; reset-vector
#endif

;*******************************************************
;   Declare IO-Sections and reserve space
;*******************************************************

        .SECTION        IO, DATA, locate=0x0
        .RES.B  0x1028

        .SECTION        CAN, DATA, locate=0x100000
        .RES.B  0x800

;*******************************************************
;   Declare user sections
;*******************************************************

        .section        DATA,  data,  align=4
        .section        INIT,  data,  align=4
        .section        IRAM,  code,  align=4
        .section        CONST, const, align=4

;*******************************************************


;*******************************************************
;   Start of Init-Routine
;   =====================
;
;   Operation will start here after reset
;   (fixed Reset entry from BootROM -> 0F:4000)
;*******************************************************

        .section        START,  code,  align=4
start:
        nop     ; Reset-entry

       LDI  #DIVR0,R12
       LDI  #0x00, R1          ; Facc and fix R-Vector on ; BIROM and LPM off
       STB  R1,@R12

_MAIN00:
       LDI  #CSE,R12            ; Включаем
       LDI  #0x80, R1
       STB  R1,@R12

       LDI  #AMD0,R12
       LDI  #0x08, R1
       STB  R1,@R12

;       LDI  #PFR27,R1
;       LDI  #0x0000, R0
;       STB  R0,@R1
;
;       LDI #0x610, R14            ;0x610
;       STB R0,@(R14, 0x0)
;       STB R0,@(R14, 0x1)
;       stb r0,@(r14, 0x2)
;       stb r0,@(r14, 0x3)
;       stb r0,@(r14, 0x4)
;       stb r0,@(r14, 0x5)
;       stb r0,@(r14, 0x6)
;       stb r0,@(r14, 0x7)
;       ldi #0xF9, r0
;       stb r0,@(r14, 0x8)
;       ldi #0x04, r0
;       stb r0,@(r14, 0x9)

;*************************************************************************
;       Flash initialization
;*************************************************************************

       LDI  #FMCS,R12
       LDI  #0x60, R0          ; Facc and fix R-Vector on ; BIROM and LPM off
       STB  R0,@R12

       LDI  #FMWT,R12
       LDI  #0x13, R0          ; Facc L width = 1 cyc ; 3 wait states
       STB  R0,@R12


;*******************************************************
;       Set Stack Pointer and Table Base Register
;*******************************************************

        ldi     #stack_top, sp          ; set Stack Pointer
        ldi     #0x0FFC00,R0            ; set Table Base
        mov     r0,tbr


#if !SIMULATOR

        LDI     #CSE,R12              ; Chip select enable register
        LDI     #0x81,R1              ; enable CS0, CS7
        STB     R1,@R12

;*******************************************************
;       Clock Settings
;*******************************************************

;   set R-Bus to 16 MHz :

    ldi #DIVR0, R12     ; R-Bus clock :
#if   PLL == 16
    ldi #0x00, r1       ; R-Bus = PLL /1 (if PLL=16MHz)
#elif PLL == 32
    ldi #0x01, r1       ; R-Bus = PLL /2 (if PLL=32MHz)
#elif PLL == 48
    ldi #0x02, r1       ; R-Bus = PLL /3 (if PLL=48MHz)
#elif PLL == 64
    ldi #0x03, r1       ; R-Bus = PLL /4 (if PLL=64MHz)
#endif
    stb r1,@r12


;   set ext.Bus clock to 16 MHz :

    ldi #DIVR1, R12     ; external bus clock :
#if   PLL == 16
    ldi #0x00, r1       ; ext-Bus = PLL/1 (if PLL=16MHz)
#elif PLL == 32
    ldi #0x10, r1       ; ext-Bus = PLL/2 (if PLL=32MHz)
#elif PLL == 48
    ldi #0x20, r1       ; ext-Bus = PLL/3 (if PLL=48MHz)
#elif PLL == 64
    ldi #0x30, r1       ; ext-Bus = PLL/4 (if PLL=64MHz)
#endif
    stb r1,@r12


;   set CAN clock :

    ldi #CMCR, R12      ; CAN clock :
#if   PLL == 64
    ldi #0x0180, r1     ; CAN = PLL/4
                        ; PLL=64MHz -> CAN-Clk=16MHz
#else
    ldi #0x0080, r1     ; CAN = PLL/2
                        ; PLL=16Mhz -> CAN-Clk=8MHz
                        ; PLL=32Mhz -> CAN-Clk=16MHz
                        ; PLL=48Mhz -> CAN-Clk=24MHz
#endif
    sth r1,@r12

;   configure main PLL :

    ldi #CLKR, R12      ; set main PLL clock to :
#if   PLL == 16
    ldi #0x34, R1       ; 16 MHz
#elif PLL == 32
    ldi #0x44, R1       ; 32 MHz
#elif PLL == 48
    ldi #0x64, R1       ; 48 MHz
#elif PLL == 64
    ldi #0x74, R1       ; 64 MHz
#endif
    stb r1,@r12

U4MHZ:

;   PLL lock time wait loop :

    ldi #TBCR, R12		; Initialize Time Based Counter to :
    ldi #0x03, R1		; 2^11 Clocks (1.024ms @4Mhz ; 128ms @32kHz)
    stb R1, @R12

    ldi #CTBR, R12		; Reset Time Based Counter
    ldi #0xA5, R1
    ldi #0x5A, R2
    stb R1, @R12		; write reset sequence
    stb R2, @R12

    ldi #TBCR, R12		; clear interrupt flag of
    ldi #0x7F, R1		; Time Based Counter
    andb R1, @R12
lock_time:
    btsth #0x8, @R12	; Check interrupt flag
    beq lock_time		; time elapsed when set


    ldi #CLKR, R12      ; PLL lock time elapsed :
    ldi #0x02,r2
    orb r2,@r12         ; select PLL as clock source

    ldi #0x06,r2
    orb r2,@r12		    ; activate main clock now

;********************************************************
;   Enable external INT0 for USER0-Button (ABORT)
;********************************************************

#if ABORT

	LDI:8    #0x10,R0 	; set interrupt control register  ICR00 = 16
	LDI:32   #_icr00,R12
	STB      R0,@R12

	LDI:8    #0x1F,R1 	; disable all other interrupts (ICR01..ICR47 = 31)
	LDI:32   #_icr01,R4
     MOV      R4, R5
fillICRs:
	STB      R1,@R5
	ADD      #1,R4
	LDI:20   #0x470,R0
	ADD      #1,R5
	CMP      R0,R4
	BLT      fillICRs

	LDI:32   #0x41,R11
	LDI:32   #0x42,R10
	BANDL    #0xE,@R11 	; enable interrupt #0
	LDUH     @R10,R0	; set lower 2 bits of ELVR to 1
	LDI:20   #0x3,R1    ; (interrupt will be signaled at button down)
	OR       R1,R0
	STH      R0,@R10

	LDI:32   #0x40,R0	; clear old interrupts
	BANDL    #0xE,@R0
	BORL     #1,@R11	; enable INT0 now

	ORCCR    #0x10		; enable interrupts
	STILM    #0x1E		; set global interrupt level to 30

#endif


#endif                  ; end of simulator used

;********************************************************
;   C setup (clears Data RAM and initializes variables)
;********************************************************

;       clear DATA section

        ldi:8   #0, r0

        ldi     #sizeof DATA &~0x3, r1
        ldi     #DATA, r13

        cmp     #0, r1
        beq     data_clr1
data_clr0:
        add2    #-4, r1
        bne:d   data_clr0
        st      r0, @(r13, r1)

data_clr1:
        ldi:8   #sizeof DATA & 0x3, r1
        ldi     #DATA + (sizeof DATA & ~0x3), r13

        cmp     #0, r1
        beq     data_clr_end
data_clr2:
        add2    #-1, r1
        bne:d   data_clr2
        stb     r0, @(r13, r1)
data_clr_end:

;********************************************************
;       copy rom (initialize variables)
;********************************************************

        ldi     #_RAM_INIT, r0
        ldi     #_ROM_INIT, r1
        ldi     #sizeof(INIT), r2
        cmp     #0, r2
        beq:d   copy_rom_end
        ldi     #3, r12
        and     r2, r12
        beq:d   copy_rom2
        mov     r2, r13
        mov     r2, r3
        sub     r12, r3
copy_rom1:
        add     #-1, r13
        ldub    @(r13, r1), r12
        cmp     r3, r13
        bhi:d   copy_rom1
        stb     r12, @(r13, r0)
        cmp     #0, r3
        beq:d   copy_rom_end
copy_rom2:
        add     #-4, r13
        ld      @(r13, r1), r12
        bgt:d   copy_rom2
        st      r12, @(r13, r0)
copy_rom_end:

;********************************************************
;       copy code from Flash to I-RAM
;********************************************************
#if I_RAM
        ldi     #_RAM_IRAM, r0
        ldi     #_ROM_IRAM, r1
        ldi     #sizeof(IRAM), r2
        cmp     #0, r2
        beq:d   copy_iram_end
        ldi     #3, r12
        and     r2, r12
        beq:d   copy_iram2
        mov     r2, r13
        mov     r2, r3
        sub     r12, r3
copy_iram1:
        add     #-1, r13
        ldub    @(r13, r1), r12
        cmp     r3, r13
        bhi:d   copy_iram1
        stb     r12, @(r13, r0)
        cmp     #0, r3
        beq:d   copy_iram_end
copy_iram2:
        add     #-4, r13
        ld      @(r13, r1), r12
        bgt:d   copy_iram2
        st      r12, @(r13, r0)
copy_iram_end:
#endif

        ldi  #start_main, r12
        jmp  @r12            ; jump to main code


;*******************************************************
;   code to copy to FASTRAM (see above)
;*******************************************************

;copycode:

;# define CS0 0x00080000 ; Chip-select area 0 (above Flash)
;# define CS1 0x00180000 ; Chip-select area 1 (Flash) -> 512k FlashROM
;# define AM1 0x07       ; Memory-Area : 18:0000..1F:FFFF
;# define CS7 0x00100000 ; Chip-select area 7 (CAN) : 10:0000..10:FFFF

;        LDI     #CSE,R12              ; Chip select enable register :
;        LDI     #0x00,R1              ; disable all before any modifications
;        STB     R1,@R12

;        LDI     #ASR0,R12             ; CS0 (Default) : area select reg ASR0
;        LDI     #CS0>>16,R0           ; Start address of CS0 area is 20:0000
;        STH     R0,@R12
;        LDI     #AMR0,R12             ; area mask reg   AMR0
;        LDI     #0x0F,R1              ; End   address of CS0 area is 2F:FFFF
;        STH     R1,@R12               ;
;        LDI     #AMD0,R12             ; Area Mode reg   AMD0
;        LDI     #0x11,R1              ; 32-Bit Bus, 1 wait state, no ready-pin
;        STB     R1,@R12

        ;LDI     #ASR1,R12             ; CS1 : area select reg
        ;LDI     #CS1>>16,R0           ; Start address of CS1 area
        ;STH     R0,@R12
        ;LDI     #AMR1,R12             ; area mask reg   AMR1
        ;LDI     #AM1,R1               ; End   address of CS1 area
        ;STH     R1,@R12               ;
        ;LDI     #AMD1,R12             ; Area Mode reg   AMD1
        ;LDI     #0x11,R1              ; 32-Bit Bus, 1 wait state, no ready-pin
        ;STB     R1,@R12

;        LDI     #ASR7,R12             ; CS7 (CAN) : area select reg ASR7
;        LDI     #CS7>>16,R0           ; Start address of CS7 area
;        STH     R0,@R12
;        LDI     #AMR7,R12             ; area mask reg   AMR7
;        LDI     #0x00,R1              ; End   address of CS7 area
;        STH     R1,@R12               ;
;        LDI     #AMD7,R12             ; Area Mode reg   AMD7
;        LDI     #0x29,R1              ; 16-Bit Bus, 1 wait state, ready-pin enabled
;        STB     R1,@R12

;        LDI     #CSE,R12              ; Chip select enable register
;        LDI     #0x81,R1              ; enable CS0, CS1 and CS7
;        STB     R1,@R12

;       RET                            ; return to startup-routine

;copycode_end:


;*******************************************************
;	end of startup-routines
;*******************************************************

       .section CODE, code, align=4

start_main:



        call32  _main, r12      ;   jump to user routine (main)

__exit:
end:
    bra end         		; in case of return from main

;*******************************************************
;   error handler for uninitialized interrupts
;*******************************************************

uninitial_int:
        INTE	; break here

/*##################################################*/
/*													*/
/* ERROR : UNINITIALIZED INTERRUPT	!				*/				NOP
/* An interrupt was called for which no				*/
/* interrupt vector is defined !					*/
/* Leave the debugger and correct your 				*/
/* project (see instructions in INTVECT.ASM) !		*/
/*													*/
/*##################################################*/

        bra uninitial_int

;*******************************************************
;   handler for ABORT-Button (USER0)
;*******************************************************

abortbutton:

#if ABORT

	STM0     (R4,R5,R6,R7)
	STM1     (R12,R13)
	STM0     (R0,R1,R2,R3)
	ST       MDH,@-R15
	ST       MDL,@-R15
	ENTER    #004

	LDI:32   #0x040,R0	; clear interrupt cause
	BANDL    #0xE,@R0

	LEAVE
	LD       @R15+,MDL
	LD       @R15+,MDH
	LDM0     (R0,R1,R2,R3)
	LDM1     (R12,R13)
	LDM0     (R4,R5,R6,R7)

	INTE     			; break here

/*##################################################*/
/*													*/
/* You pressed ABORT (USER0) 						*/			RETI
/* on the Starterkit !								*/
/* Execute a single-step to return					*/
/* to the source file or add breakpoints ! 			*/
/*													*/
/*##################################################*/

    #endif

;*******************************************************

    .end    start
