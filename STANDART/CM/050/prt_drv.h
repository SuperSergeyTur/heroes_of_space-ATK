#ifndef _PRT_DRV_H
#define _PRT_DRV_H

extern void  Port_input ( word code ) ;
extern void  Port_output ( void ) ;
extern void  Port_output_clr ( void ) ;


//  ���� ����������� ��� ��������� ������� ���������� ��������.

#define  _QV_Msk       (1u << 20)  // ���� P1.20
#define  _D1_Msk       (1u << 29)  // ���� P1.29

#define   mSET_Q1()    LPC_GPIO1->CLR = _QV_Msk
#define   mCLR_Q1()    LPC_GPIO1->SET = _QV_Msk

#define   mSET_D1()    LPC_GPIO1->SET |= _D1_Msk
#define   mCLR_D1()    LPC_GPIO1->CLR |= _D1_Msk

#define   mSetStrobInsul()     mSET_D1(), S.flg._.MyStrobInsul = 1
#define   mClrStrobInsul()     mCLR_D1(), S.flg._.MyStrobInsul = 0

//#define  _ADC_MUX_Msk         (7UL<<27)
//#define  _ADC_MUX_SET(n)		((n & 0x07)<<27)


//#define  _ADC_USR_Msk			(3UL<<29)

//#define  _ADC_SELL_Msk                  (1UL<<31)


//---------------------------

     // ���������� �� ('0'). - ����
#define   mIU_Enable()
     // ������ �� ('1').     - ����
#define   mIU_Disable()


#define   mPort_Imp( data )  LPC_GPIO2->PIN =(LPC_GPIO2->PIN&0xffffffc0)|( (data & 0x3F) )

#define   Port_imp_copy      LPC_GPIO2->PIN

#define   mClr_ImpVozb()    mPort_Imp( 0x3F )


#define  USEL_Msk		(lword)0x00000010 // ���� 5.4
//#define  PINSTOP_Msk	(lword)0x00000001 // ���� 5.0

#define   mUSEL_set()  LPC_GPIO5->CLR = USEL_Msk
#define   mUSEL_clr()  LPC_GPIO5->SET = USEL_Msk

static __INLINE void mUSEL_not()
{
  if ( (LPC_GPIO5->PIN & USEL_Msk) == 0 )
  {
	 mUSEL_clr();
  }
  else
  {
	 mUSEL_set();
  }
}

#define    USEL     ((LPC_GPIO5->PIN &= USEL_Msk) != 0)

#define   mTst_autostart()   (  LPC_GPIO0->PIN & (1u<<5) )



   //   ����������� ������� ��� �������� �������� ��������� �������
   // ����������/������������, �� ���������� � �������� �������,
   //     ���������� �������� "0.5 ����"..."12.0 ���" ;
#define  _Drb_msec( ax )  _MkSec( (d)ax * 1000. / 256. )

//-----  �������� ������� ����� ��������. --
// �������� ����������� ��� ����������� ��������� ����� �� ���� ��������.

  union Prt   {
        byte all ;
        struct {  word  n0  : 1 ;
                  word  n1  : 1 ;
                  word  n2  : 1 ;
                  word  n3  : 1 ;
                  word  n4  : 1 ;
                  word  n5  : 1 ;
                  word  n6  : 1 ;
                  word  n7  : 1 ; }  _ ;
              } ;

/*-----  �������� ������� ����� ����������� ��������. -- */
/* �������� ����������� ��� ����������� ��������� ����� �� ���� ��������. */

  union Prt16   {
        word all ;
        struct {  word  n0 : 1 ;
                  word  n1 : 1 ;
                  word  n2 : 1 ;
                  word  n3 : 1 ;
                  word  n4 : 1 ;
                  word  n5 : 1 ;
                  word  n6 : 1 ;
                  word  n7  : 1 ;
                  word  n8  : 1 ;
                  word  n9  : 1 ;
                  word  n10 : 1 ;
                  word  n11 : 1 ;
                  word  n12 : 1 ;
                  word  n13 : 1 ;
                  word  n14 : 1 ;
                  word  n15 : 1 ; }  _ ;
              } ;

 typedef union Prt16 Port16n ;



 typedef union Prt Port8n  ;

/*------------------------------------------------*/
#ifdef   _MAIN_INCLUDE
/*------------------------------------------------*/

//-----  ������ ��������������� ������ �������� ������� ��������. --

_register union Prt  Po0_c, Po0_nm ;  // ����� ���������� � �������� ����.

//--- ������ ��������������� ������ ������� ������� ��������.

         union Prt  Pi0_c ;  //  �������������� ��������� �����.
         union Prt  Pi0_nm ;// ��������������� ��������� �����.
_register union Prt  Pi0_f ;  // ��������������� ��������� �����.
         union Prt  Pi0_cf ; /* �������������� ��������������� ��������� �����. */

word  P0_t [ 8 ] ; //  ������� ����� ��� ����� ������� ��� ����������
                   // �������� ����� P0.

//   PORT '1'

         union Prt  Pi1_c ;  /*  �������������� ��������� �����. */
         union Prt  Pi1_nm ;/* ��������������� ��������� �����. */
_register union Prt  Pi1_f ;  /* ��������������� ��������� �����. */
         union Prt  Pi1_cf ; /* �������������� ��������������� ��������� �����. */

word  P1_t [ 8 ] ; /*  ������� ����� ��� ����� ������� ��� ���������� */
                   /* �������� ����� P1. */

#ifdef   _Pi2_
//   PORT '2'

         union Prt  Pi2_c ;  /*  �������������� ��������� �����. */
         union Prt  Pi2_nm ;/* ��������������� ��������� �����. */
_register union Prt  Pi2_f ;  /* ��������������� ��������� �����. */
         union Prt  Pi2_cf ; /* �������������� ��������������� ��������� �����. */

word  P2_t [ 8 ] ; /*  ������� ����� ��� ����� ������� ��� ���������� */
                   /* �������� ����� P2. */
#endif

/*------------------------------------------------*/
#else
/*------------------------------------------------*/

extern _register     union Prt    Po0_c, Po0_nm ;

/*------------------------------------------------*/

extern              union Prt     Pi0_c ,  Pi0_nm ;
extern _register    union Prt     Pi0_f ;
extern   union Prt  Pi0_cf ; /* �������������� ��������������� ��������� �����. */
extern     word  P0_t [ 8 ] ;

extern              union Prt     Pi1_c ,  Pi1_nm ;
extern _register    union Prt     Pi1_f ;
extern   union Prt  Pi1_cf ; /* �������������� ��������������� ��������� �����. */
extern     word  P1_t [ 8 ] ;

#ifdef   _Pi2_
  extern   union Prt  Pi2_c ;
  extern   union Prt  Pi2_nm ;
  extern   _register union Prt  Pi2_f ;
  extern   union Prt  Pi2_cf ;
  extern   word  P2_t [ 8 ] ;
#endif

/*------------------------------------------------*/
#endif
#endif
