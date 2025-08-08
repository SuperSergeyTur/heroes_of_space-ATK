#ifndef  _TYPEDEF_H
  #define  _TYPEDEF_H

//--------   Стандартные типы данных   -----------------------
typedef   unsigned char       byte  ;
typedef   unsigned short      word  ;
typedef   unsigned long       lword ;

typedef   signed char         sbyte  ;
typedef   signed short        sword  ;
typedef   signed long         slword ;

typedef   signed              s  ;
typedef   unsigned            u  ;
typedef   float               f  ;
typedef   double              d  ;

typedef   signed char         int8  ;
typedef   signed short        int16 ;
typedef   signed int          int32 ;
typedef   signed long long    int64 ;

typedef   unsigned char       uint8  ;
typedef   unsigned short      uint16 ;
typedef   unsigned int        uint32 ;
typedef   unsigned long long  uint64 ;

typedef   unsigned char       b  ;
typedef   unsigned short      w  ;
typedef   unsigned long       lw ;

typedef   signed char         sb  ;
typedef   signed short        sw  ;
typedef   signed long         slw ;

typedef   unsigned char       fbyte  ;
typedef   unsigned short      fword  ;
typedef   unsigned long int   flword ;

typedef   signed char         fsbyte  ;
typedef   signed short        fsword  ;
typedef   signed long int     fslword ;

typedef   float               fd  ;
typedef   unsigned char       fb  ;
typedef   unsigned short      fw  ;
typedef   unsigned long int   flw ;

typedef   signed char         fsb  ;
typedef   signed short        fsw  ;
typedef   signed long int     fslw ;

typedef   volatile            word  v ;

//------------------------------------------------------------


//--------   Пользовательские типы данных   -----------------------
// Регистр системных ошибок
  typedef union
  {
	lword    all;
	struct
    {
	  lword  SysTimer	   	: 1;
	  lword  RTC			: 1;
	  lword  Pult			: 1;
	  lword  Reserv			: 29;
	}_;
  } TSysError;

  typedef lword TTimer;

/**
 * @brief Functional State Definition
 */
//typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
//#define PARAM_FUNCTIONALSTATE(State) ((State==DISABLE) || (State==ENABLE))


//#define  FALSE		0
//#define  TRUE		1

#define  FAIL		0
#define  PASS		1

#define register
#define _register 	register
#define _x_far
/*
#define asm_di(_irq) priorityIRQ[_irq] = NVIC_GetPriority( _irq);\
                                        NVIC_SetPriority( _irq, 2)//__disable_irq()//__disable_interrupt()
#define asm_ei(_irq) NVIC_SetPriority( _irq, priorityIRQ[_irq])//__enable_irq()//__enable_interrupt()
*/
#define asm_di()  __disable_irq()
#define asm_ei()  __enable_irq()

#endif // _TYPEDEF_H

