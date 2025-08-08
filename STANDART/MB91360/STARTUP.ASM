;*******************************************************
;    MB91360 Series startup routine V3.0
;    ===================================
;
;   Version for MB91360 Starterkit
;
;   Startup-Routine for MB91360 series. Initializes
;   the device after reset and prepares C-operation.
;   Features :
;   - defines all IO variables (includes MB91360.H)
;   - declares memory sections IO,STACK,DATA,CODE,INTVEC
;   - initializes STACK and DATA area (internal RAM)
;   - defines all interrupt-vectors (includes INTVECS.INC)
;   - sets clock for CPU, Resources, ext.Bus and CAN
;   - enables the intruction cache
;   - configures ext.interrupt 0 as ABORT-handler
;   - starts user code in "main()"
;
;   Startaddress is 1F:4000 (fixed reset entry)
;   Table Base (location of Interrupt-Vectors) is 1F:FC00
;
;   NOTE : This software is subject to the rules of our standard
;   DISCLAIMER, that is delivered with our SW-tools (CD-ROM "Micros"
;   or see our webpage "www.fujitsu-fme.com").
;
;   (c) Fujitsu Microelectronics Europe GmbH 1999
;   Version 3.0
;   MM 08/12/99
;*******************************************************

; Global settings :

#define PLL 48              // select PLL-Clock (16,32,48 or 64 MHz)
#define CACHE 0            // instruction cache on (1) or off (0)
#define ABORT 0             // enable(1) or disable(0) USER0-Button for ABORT
#define SIMULATOR 0         // set to 1 when using the simulator
#define STACK_SIZE 0x800-4  // define stack size 2k (3D000...3D7FC)

;*******************************************************
;   IO Symbol definition
;*******************************************************

#define __IO_DEFINE         // Activate IO assembler definitions
#include "MB91360.H"        // in headerfile

        .export start
        .export __exit
        .export uninitial_int
        .import _main
        .import _exit
        .import __stream_init
        .import _RAM_INIT
        .import _ROM_INIT

;*******************************************************
;   Declare STACK (RAM) area and reserve space
;*******************************************************

        .section        STACK, stack, align=4
        .res.b          STACK_SIZE
stack_top:
        .res.w  1

;*******************************************************
;   Fixed Reset Vector (Simulator information only)
;*******************************************************

#if SIMULATOR
        .SECTION        FIXVECT,const,locate=0xFFC00
        .GLOBAL         _fixvectors
_fixvectors:
        .ORG   0xFFFFC
        .DATA   start                   ; reset-vector
#endif

;*******************************************************
;   Interrupt-Vector definition
;*******************************************************

#include "inc361.inc";"Intvecs.inc"

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
        .section        CONST, const, align=4

;*******************************************************


;*******************************************************
;   Start of Init-Routine
;   =====================
;
;   Operation will start here after reset
;   (fixed Reset entry from BootROM -> 1F:4000)
;*******************************************************

        .section        START,  code,  align=4
start:
        nop     ; Reset-entry

;*******************************************************
;       Set Stack Pointer and Table Base Register
;*******************************************************

        ldi     #stack_top, sp          ; set Stack Pointer
        ldi     #0x1FFC00,R0            ; set Table Base
        mov     r0,tbr


#if !SIMULATOR

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

    ldi #CMCR, R12  ; CAN clock :
#if   PLL == 64
    ldi #0x0180, r1 ; CAN = PLL/4
                    ; PLL=64MHz -> CAN-Clk=16MHz
#else
    ldi #0x0080, r1 ; CAN = PLL/2
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

;    LDI:8   #0x12, R12  ; Check which Oscillator is used
;    LDUB    @R12, R0    ; read Clock-Selector Pin (Port I:7)
;    LDI     #0x80, R1
;    AND     R1, R0
;    CMP     #0, R0
;    BNE32   U4MHZ, R12  ; skip nect few lines if 4 MHz is used
;
;    ldi #CLKR, R12      ; 32 kHz Osc used :
;    ldi #0x08,r2                ; enable PLL2
;    orb r2,@r12         ; in Clock Control Reg

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
    btsth #0x8, @R12		; Check interrupt flag
    beq lock_time		; time elapsed when set


    ldi #CLKR, R12  ; PLL lock time elapsed :
    ldi #0x02,r2
    orb r2,@r12     ; select PLL as clock source

    ldi #0x06,r2
    orb r2,@r12		; activate main clock now


;*******************************************************
;   Instruction cache
;*******************************************************

#if CACHE
    ldi #ICHCR, r12     ; switch on Instruction Cache
    ldi #0B00000110,r1
    stb r1,@r12
    ldi #0B00000001,r1
    stb r1,@r12
    ldi #0B00000111,r1
    stb r1,@r12
    nop
    nop
#endif

#endif

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


;;      copy rom (initialize variables)

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


       ldi  #start_main, r12
       jmp  @r12            ; jump to main code


;*******************************************************
;	end of startup-routines
;*******************************************************

        .section        CODE,  code,  align=4

start_main:

        call32  _main, r12	;   jump to user routine (main)

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
/* ERROR : UNINITIALIZED INTERRUPT      !                               */  NOP
/* An interrupt was called for which no				*/
/* interrupt vector is defined !					*/
/* Leave the debugger and correct your 				*/
/* project (see instructions in INTVECT.ASM) !		*/
/*													*/
/*##################################################*/


 bra uninitial_int



        .end    start
