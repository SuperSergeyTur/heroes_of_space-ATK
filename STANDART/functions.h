#ifndef _func_h
#define _func_h
#include <math.h>
#define _SecDiscr (d)_TimerDiscreta/(d)1000000.0
union Operand
{
  word all;
  struct
  {
#ifdef _Union_FR   //�������������� ����� ������ ��� FR

    word Number  : 9; // ����� �������� � ����� �������
    word Lenght  : 3; // ����������� ��������
    word Sign    : 1; // ���� �������� (0 - �����������, 1 - ��������)
    word Type    : 3; // ��� ��������
#else

    word Type    : 3; // ��� ��������
    word Sign    : 1; // ���� �������� (0 - �����������, 1 - ��������)
    word Lenght  : 3; // ����������� ��������
    word Number  : 9; // ����� �������� � ����� �������

#endif
  }_;
};

//------------------------------------------------------------
union str_double
{
   double all;
   word  wrd[4];
   byte  bt[8];
};
//------------------------------------------------------------

//�������� ������ �����

word ADD_BB  (union Operand *Operands);
word ADD_WW  (union Operand *Operands);
word ADD_LL  (union Operand *Operands);
word ADD_DD  (union Operand *Operands);
word ADD_BC  (union Operand *Operands);
word ADD_WC  (union Operand *Operands);
word ADD_LC  (union Operand *Operands);
word ADD_DC  (union Operand *Operands);
word ADD_BS  (union Operand *Operands);
word ADD_WS  (union Operand *Operands);
word ADD_LS  (union Operand *Operands);
word ADD_DS  (union Operand *Operands);
word ADD_BBa (union Operand *Operands);
word ADD_WBa (union Operand *Operands);
word ADD_LBa (union Operand *Operands);
word ADD_DBa (union Operand *Operands);


word ADD_BAr (union Operand *Operands);
word ADD_WAr (union Operand *Operands);
word ADD_LAr (union Operand *Operands);
word ADD_DAr (union Operand *Operands);


word SUB_BB  (union Operand *Operands);
word SUB_WW  (union Operand *Operands);
word SUB_LL  (union Operand *Operands);
word SUB_DD  (union Operand *Operands);
word SUB_BC  (union Operand *Operands);
word SUB_WC  (union Operand *Operands);
word SUB_LC  (union Operand *Operands);
word SUB_DC  (union Operand *Operands);
word SUB_CB  (union Operand *Operands);
word SUB_CW  (union Operand *Operands);
word SUB_CL  (union Operand *Operands);
word SUB_CD  (union Operand *Operands);
word SUB_BS  (union Operand *Operands);
word SUB_WS  (union Operand *Operands);
word SUB_LS  (union Operand *Operands);
word SUB_DS  (union Operand *Operands);
word SUB_SB  (union Operand *Operands);
word SUB_SW  (union Operand *Operands);
word SUB_SL  (union Operand *Operands);
word SUB_SD  (union Operand *Operands);
word SUB_BBa (union Operand *Operands);
word SUB_WBa (union Operand *Operands);
word SUB_LBa (union Operand *Operands);
word SUB_DBa (union Operand *Operands);
word SUB_BaB (union Operand *Operands);
word SUB_BaW (union Operand *Operands);
word SUB_BaL (union Operand *Operands);
word SUB_BaD (union Operand *Operands);

word SUB_BAr (union Operand *Operands);
word SUB_WAr (union Operand *Operands);
word SUB_LAr (union Operand *Operands);
word SUB_DAr (union Operand *Operands);
word SUB_ArB (union Operand *Operands);
word SUB_ArW (union Operand *Operands);
word SUB_ArL (union Operand *Operands);
word SUB_ArD (union Operand *Operands);



word MUL_BB  (union Operand *Operands);
word MUL_WW  (union Operand *Operands);
word MUL_LL  (union Operand *Operands);
word MUL_DD  (union Operand *Operands);
word MUL_BC  (union Operand *Operands);
word MUL_WC  (union Operand *Operands);
word MUL_LC  (union Operand *Operands);
word MUL_DC  (union Operand *Operands);
word MUL_BS  (union Operand *Operands);
word MUL_WS  (union Operand *Operands);
word MUL_LS  (union Operand *Operands);
word MUL_DS  (union Operand *Operands);
word MUL_BBa (union Operand *Operands);
word MUL_WBa (union Operand *Operands);
word MUL_LBa (union Operand *Operands);
word MUL_DBa (union Operand *Operands);
word MULU_BB (union Operand *Operands);
word MULU_WW (union Operand *Operands);
word MULU_LL (union Operand *Operands);
word MULU_BC (union Operand *Operands);
word MULU_WC (union Operand *Operands);
word MULU_LC (union Operand *Operands);
word MULU_BS (union Operand *Operands);
word MULU_WS (union Operand *Operands);
word MULU_LS (union Operand *Operands);
word MULU_BBa(union Operand *Operands);
word MULU_WBa(union Operand *Operands);
word MULU_LBa(union Operand *Operands);

word MUL_BAr  (union Operand *Operands);
word MUL_WAr  (union Operand *Operands);
word MUL_LAr  (union Operand *Operands);
word MUL_DAr  (union Operand *Operands);
word MULU_BAr (union Operand *Operands);
word MULU_WAr (union Operand *Operands);
word MULU_LAr (union Operand *Operands);



word DIV_BB  (union Operand *Operands);
word DIV_WW  (union Operand *Operands);
word DIV_LL  (union Operand *Operands);
word DIV_DD  (union Operand *Operands);
word DIV_BC  (union Operand *Operands);
word DIV_WC  (union Operand *Operands);
word DIV_LC  (union Operand *Operands);
word DIV_DC  (union Operand *Operands);
word DIV_CB  (union Operand *Operands);
word DIV_CW  (union Operand *Operands);
word DIV_CL  (union Operand *Operands);
word DIV_CD  (union Operand *Operands);
word DIV_BS  (union Operand *Operands);
word DIV_WS  (union Operand *Operands);
word DIV_LS  (union Operand *Operands);
word DIV_DS  (union Operand *Operands);
word DIV_SB  (union Operand *Operands);
word DIV_SW  (union Operand *Operands);
word DIV_SL  (union Operand *Operands);
word DIV_SD  (union Operand *Operands);
word DIV_BBa (union Operand *Operands);
word DIV_WBa (union Operand *Operands);
word DIV_LBa (union Operand *Operands);
word DIV_DBa (union Operand *Operands);
word DIV_BaB (union Operand *Operands);
word DIV_BaW (union Operand *Operands);
word DIV_BaL (union Operand *Operands);
word DIV_BaD (union Operand *Operands);
word DIVU_BB (union Operand *Operands);
word DIVU_WW (union Operand *Operands);
word DIVU_LL (union Operand *Operands);
word DIVU_BC (union Operand *Operands);
word DIVU_WC (union Operand *Operands);
word DIVU_LC (union Operand *Operands);
word DIVU_CB (union Operand *Operands);
word DIVU_CW (union Operand *Operands);
word DIVU_CL (union Operand *Operands);
word DIVU_BS (union Operand *Operands);
word DIVU_WS (union Operand *Operands);
word DIVU_LS (union Operand *Operands);
word DIVU_SB (union Operand *Operands);
word DIVU_SW (union Operand *Operands);
word DIVU_SL (union Operand *Operands);
word DIVU_BBa(union Operand *Operands);
word DIVU_WBa(union Operand *Operands);
word DIVU_LBa(union Operand *Operands);
word DIVU_BaB(union Operand *Operands);
word DIVU_BaW(union Operand *Operands);
word DIVU_BaL(union Operand *Operands);

word DIV_BAr(union Operand *Operands);
word DIV_WAr(union Operand *Operands);
word DIV_LAr(union Operand *Operands);
word DIV_DAr(union Operand *Operands);
word DIV_ArB(union Operand *Operands);
word DIV_ArW(union Operand *Operands);
word DIV_ArL(union Operand *Operands);
word DIV_ArD (union Operand *Operands);
word DIVU_BAr(union Operand *Operands);
word DIVU_WAr(union Operand *Operands);
word DIVU_LAr(union Operand *Operands);
word DIVU_ArB(union Operand *Operands);
word DIVU_ArW(union Operand *Operands);
word DIVU_ArL(union Operand *Operands);

word NO_BB (union Operand *Operands);
word NO_WW (union Operand *Operands);
word NO_LL (union Operand *Operands);
word NO_BS (union Operand *Operands);
word NO_WS (union Operand *Operands);
word NO_LS (union Operand *Operands);
word NO_BBa(union Operand *Operands);
word NO_WBa(union Operand *Operands);
word NO_LBa(union Operand *Operands);

word NO_BAr     (union Operand *Operands);
word NO_WAr     (union Operand *Operands);
word NO_LAr     (union Operand *Operands);

word OR_BB (union Operand *Operands);
word OR_WW (union Operand *Operands);
word OR_LL (union Operand *Operands);
word OR_BC (union Operand *Operands);
word OR_WC (union Operand *Operands);
word OR_LC (union Operand *Operands);
word OR_BS (union Operand *Operands);
word OR_WS (union Operand *Operands);
word OR_LS (union Operand *Operands);
word OR_BBa(union Operand *Operands);
word OR_WBa(union Operand *Operands);
word OR_LBa(union Operand *Operands);
word OR_BAr     (union Operand *Operands);
word OR_WAr     (union Operand *Operands);
word OR_LAr     (union Operand *Operands);

word XOR_BB (union Operand *Operands);
word XOR_WW (union Operand *Operands);
word XOR_LL (union Operand *Operands);
word XOR_BC (union Operand *Operands);
word XOR_WC (union Operand *Operands);
word XOR_LC (union Operand *Operands);
word XOR_BS (union Operand *Operands);
word XOR_WS (union Operand *Operands);
word XOR_LS (union Operand *Operands);
word XOR_BBa(union Operand *Operands);
word XOR_WBa(union Operand *Operands);
word XOR_LBa(union Operand *Operands);
word XOR_BAr    (union Operand *Operands);
word XOR_WAr    (union Operand *Operands);
word XOR_LAr    (union Operand *Operands);

word AND_BB (union Operand *Operands);
word AND_WW (union Operand *Operands);
word AND_LL (union Operand *Operands);
word AND_BC (union Operand *Operands);
word AND_WC (union Operand *Operands);
word AND_LC (union Operand *Operands);
word AND_BS (union Operand *Operands);
word AND_WS (union Operand *Operands);
word AND_LS (union Operand *Operands);
word AND_BBa(union Operand *Operands);
word AND_WBa(union Operand *Operands);
word AND_LBa(union Operand *Operands);
word AND_BAr    (union Operand *Operands);
word AND_WAr    (union Operand *Operands);
word AND_LAr    (union Operand *Operands);

word ROR_BB (union Operand *Operands);
word ROR_WW (union Operand *Operands);
word ROR_LL (union Operand *Operands);
word ROR_BC (union Operand *Operands);
word ROR_WC (union Operand *Operands);
word ROR_LC (union Operand *Operands);
word ROR_CB (union Operand *Operands);
word ROR_CW (union Operand *Operands);
word ROR_CL (union Operand *Operands);
word ROR_BS (union Operand *Operands);
word ROR_WS (union Operand *Operands);
word ROR_LS (union Operand *Operands);
word ROR_SB (union Operand *Operands);
word ROR_SW (union Operand *Operands);
word ROR_SL (union Operand *Operands);
word ROR_BBa(union Operand *Operands);
word ROR_WBa(union Operand *Operands);
word ROR_LBa(union Operand *Operands);
word ROR_BaB(union Operand *Operands);
word ROR_BaW(union Operand *Operands);
word ROR_BaL(union Operand *Operands);
word ROR_BAr    (union Operand *Operands);
word ROR_WAr    (union Operand *Operands);
word ROR_LAr    (union Operand *Operands);
word ROR_ArB    (union Operand *Operands);
word ROR_ArW    (union Operand *Operands);
word ROR_ArL    (union Operand *Operands);

word RORU_BB (union Operand *Operands);
word RORU_WW (union Operand *Operands);
word RORU_LL (union Operand *Operands);
word RORU_BC (union Operand *Operands);
word RORU_WC (union Operand *Operands);
word RORU_LC (union Operand *Operands);
word RORU_CB (union Operand *Operands);
word RORU_CW (union Operand *Operands);
word RORU_CL (union Operand *Operands);
word RORU_BS (union Operand *Operands);
word RORU_WS (union Operand *Operands);
word RORU_LS (union Operand *Operands);
word RORU_SB (union Operand *Operands);
word RORU_SW (union Operand *Operands);
word RORU_SL (union Operand *Operands);
word RORU_BBa(union Operand *Operands);
word RORU_WBa(union Operand *Operands);
word RORU_LBa(union Operand *Operands);
word RORU_BaB(union Operand *Operands);
word RORU_BaW(union Operand *Operands);
word RORU_BaL(union Operand *Operands);
word RORU_BAr   (union Operand *Operands);
word RORU_WAr   (union Operand *Operands);
word RORU_LAr   (union Operand *Operands);
word RORU_ArB   (union Operand *Operands);
word RORU_ArW   (union Operand *Operands);
word RORU_ArL   (union Operand *Operands);

word ROL_BB (union Operand *Operands);
word ROL_WW (union Operand *Operands);
word ROL_LL (union Operand *Operands);
word ROL_BC (union Operand *Operands);
word ROL_WC (union Operand *Operands);
word ROL_LC (union Operand *Operands);
word ROL_CB (union Operand *Operands);
word ROL_CW (union Operand *Operands);
word ROL_CL (union Operand *Operands);
word ROL_BS (union Operand *Operands);
word ROL_WS (union Operand *Operands);
word ROL_LS (union Operand *Operands);
word ROL_SB (union Operand *Operands);
word ROL_SW (union Operand *Operands);
word ROL_SL (union Operand *Operands);
word ROL_BBa(union Operand *Operands);
word ROL_WBa(union Operand *Operands);
word ROL_LBa(union Operand *Operands);
word ROL_BaB(union Operand *Operands);
word ROL_BaW(union Operand *Operands);
word ROL_BaL(union Operand *Operands);
word ROL_BAr    (union Operand *Operands);
word ROL_WAr    (union Operand *Operands);
word ROL_LAr    (union Operand *Operands);
word ROL_ArB    (union Operand *Operands);
word ROL_ArW    (union Operand *Operands);
word ROL_ArL    (union Operand *Operands);

word BEQ_BB    (union Operand *Operands);
word BEQ_WW    (union Operand *Operands);
word BEQ_LL    (union Operand *Operands);
word BEQ_DD    (union Operand *Operands);
word BEQ_BC    (union Operand *Operands);
word BEQ_WC    (union Operand *Operands);
word BEQ_LC    (union Operand *Operands);
word BEQ_DC    (union Operand *Operands);
word BEQ_BS    (union Operand *Operands);
word BEQ_WS    (union Operand *Operands);
word BEQ_LS    (union Operand *Operands);
word BEQ_DS    (union Operand *Operands);
word BEQ_BBa   (union Operand *Operands);
word BEQ_WBa   (union Operand *Operands);
word BEQ_LBa   (union Operand *Operands);
word BEQ_DBa   (union Operand *Operands);
word BEQ_BaB   (union Operand *Operands);
word BEQ_BaW   (union Operand *Operands);
word BEQ_BaL   (union Operand *Operands);
word BEQ_BaD   (union Operand *Operands);
word BEQ_BaB_C (union Operand *Operands);
word BEQ_BaW_C (union Operand *Operands);
word BEQ_BaL_C (union Operand *Operands);
word BEQ_BaD_C (union Operand *Operands);
word BEQ_BaB_S (union Operand *Operands);
word BEQ_BaW_S (union Operand *Operands);
word BEQ_BaL_S (union Operand *Operands);
word BEQ_BaD_S (union Operand *Operands);
word BEQ_BS_S (union Operand *Operands);
word BEQ_WS_S (union Operand *Operands);
word BEQ_LS_S (union Operand *Operands);
word BEQ_DS_S (union Operand *Operands);
word BEQ_BS_C (union Operand *Operands);
word BEQ_WS_C (union Operand *Operands);
word BEQ_LS_C (union Operand *Operands);
word BEQ_DS_C (union Operand *Operands);

word BEQ_BAr    (union Operand *Operands);
word BEQ_WAr    (union Operand *Operands);
word BEQ_LAr    (union Operand *Operands);
word BEQ_DAr    (union Operand *Operands);
word BEQ_ArB    (union Operand *Operands);
word BEQ_ArW    (union Operand *Operands);
word BEQ_ArL    (union Operand *Operands);
word BEQ_ArD    (union Operand *Operands);
word BEQ_BAr_C  (union Operand *Operands);
word BEQ_WAr_C  (union Operand *Operands);
word BEQ_LAr_C  (union Operand *Operands);
word BEQ_DAr_C  (union Operand *Operands);
word BEQ_BAr_Ba (union Operand *Operands);
word BEQ_WAr_Ba (union Operand *Operands);
word BEQ_LAr_Ba (union Operand *Operands);
word BEQ_DAr_Ba (union Operand *Operands);
word BEQ_BAr_S  (union Operand *Operands);
word BEQ_WAr_S  (union Operand *Operands);
word BEQ_LAr_S  (union Operand *Operands);
word BEQ_DAr_S  (union Operand *Operands);

word BNE_BB    (union Operand *Operands);
word BNE_WW    (union Operand *Operands);
word BNE_LL    (union Operand *Operands);
word BNE_DD    (union Operand *Operands);
word BNE_BC    (union Operand *Operands);
word BNE_WC    (union Operand *Operands);
word BNE_LC    (union Operand *Operands);
word BNE_DC    (union Operand *Operands);
word BNE_BS    (union Operand *Operands);
word BNE_WS    (union Operand *Operands);
word BNE_LS    (union Operand *Operands);
word BNE_DS    (union Operand *Operands);
word BNE_BBa   (union Operand *Operands);
word BNE_WBa   (union Operand *Operands);
word BNE_LBa   (union Operand *Operands);
word BNE_DBa   (union Operand *Operands);
word BNE_BaB   (union Operand *Operands);
word BNE_BaW   (union Operand *Operands);
word BNE_BaL   (union Operand *Operands);
word BNE_BaD   (union Operand *Operands);
word BNE_BaB_C (union Operand *Operands);
word BNE_BaW_C (union Operand *Operands);
word BNE_BaL_C (union Operand *Operands);
word BNE_BaD_C (union Operand *Operands);
word BNE_BaB_S (union Operand *Operands);
word BNE_BaW_S (union Operand *Operands);
word BNE_BaL_S (union Operand *Operands);
word BNE_BaD_S (union Operand *Operands);
word BNE_BS_S (union Operand *Operands);
word BNE_WS_S (union Operand *Operands);
word BNE_LS_S (union Operand *Operands);
word BNE_DS_S (union Operand *Operands);
word BNE_BS_C (union Operand *Operands);
word BNE_WS_C (union Operand *Operands);
word BNE_LS_C (union Operand *Operands);
word BNE_DS_C (union Operand *Operands);
word BNE_BAr    (union Operand *Operands);
word BNE_WAr    (union Operand *Operands);
word BNE_LAr    (union Operand *Operands);
word BNE_DAr    (union Operand *Operands);
word BNE_ArB    (union Operand *Operands);
word BNE_ArW    (union Operand *Operands);
word BNE_ArL    (union Operand *Operands);
word BNE_ArD    (union Operand *Operands);
word BNE_BAr_C  (union Operand *Operands);
word BNE_WAr_C  (union Operand *Operands);
word BNE_LAr_C  (union Operand *Operands);
word BNE_DAr_C  (union Operand *Operands);
word BNE_BAr_Ba (union Operand *Operands);
word BNE_WAr_Ba (union Operand *Operands);
word BNE_LAr_Ba (union Operand *Operands);
word BNE_DAr_Ba (union Operand *Operands);
word BNE_BAr_S  (union Operand *Operands);
word BNE_WAr_S  (union Operand *Operands);
word BNE_LAr_S  (union Operand *Operands);
word BNE_DAr_S  (union Operand *Operands);

word BGT_BB    (union Operand *Operands);
word BGT_WW    (union Operand *Operands);
word BGT_LL    (union Operand *Operands);
word BGT_DD    (union Operand *Operands);
word BGT_BC    (union Operand *Operands);
word BGT_WC    (union Operand *Operands);
word BGT_LC    (union Operand *Operands);
word BGT_DC    (union Operand *Operands);
word BGT_BS    (union Operand *Operands);
word BGT_WS    (union Operand *Operands);
word BGT_LS    (union Operand *Operands);
word BGT_DS    (union Operand *Operands);
word BGT_BBa   (union Operand *Operands);
word BGT_WBa   (union Operand *Operands);
word BGT_LBa   (union Operand *Operands);
word BGT_DBa   (union Operand *Operands);
word BGT_BaB   (union Operand *Operands);
word BGT_BaW   (union Operand *Operands);
word BGT_BaL   (union Operand *Operands);
word BGT_BaD   (union Operand *Operands);
word BGT_BaB_C (union Operand *Operands);
word BGT_BaW_C (union Operand *Operands);
word BGT_BaL_C (union Operand *Operands);
word BGT_BaD_C (union Operand *Operands);
word BGT_BaB_S (union Operand *Operands);
word BGT_BaW_S (union Operand *Operands);
word BGT_BaL_S (union Operand *Operands);
word BGT_BaD_S (union Operand *Operands);
word BGT_BS_S (union Operand *Operands);
word BGT_WS_S (union Operand *Operands);
word BGT_LS_S (union Operand *Operands);
word BGT_DS_S (union Operand *Operands);
word BGT_BS_C (union Operand *Operands);
word BGT_WS_C (union Operand *Operands);
word BGT_LS_C (union Operand *Operands);
word BGT_DS_C (union Operand *Operands);
word BGT_BAr    (union Operand *Operands);
word BGT_WAr    (union Operand *Operands);
word BGT_LAr    (union Operand *Operands);
word BGT_DAr    (union Operand *Operands);
word BGT_ArB    (union Operand *Operands);
word BGT_ArW    (union Operand *Operands);
word BGT_ArL    (union Operand *Operands);
word BGT_ArD    (union Operand *Operands);
word BGT_BAr_C  (union Operand *Operands);
word BGT_WAr_C  (union Operand *Operands);
word BGT_LAr_C  (union Operand *Operands);
word BGT_DAr_C  (union Operand *Operands);
word BGT_BAr_Ba (union Operand *Operands);
word BGT_WAr_Ba (union Operand *Operands);
word BGT_LAr_Ba (union Operand *Operands);
word BGT_DAr_Ba (union Operand *Operands);
word BGT_BAr_S  (union Operand *Operands);
word BGT_WAr_S  (union Operand *Operands);
word BGT_LAr_S  (union Operand *Operands);
word BGT_DAr_S  (union Operand *Operands);

word BGTU_BB   (union Operand *Operands);
word BGTU_WW   (union Operand *Operands);
word BGTU_LL   (union Operand *Operands);
word BGTU_BC   (union Operand *Operands);
word BGTU_WC   (union Operand *Operands);
word BGTU_LC   (union Operand *Operands);
word BGTU_BS   (union Operand *Operands);
word BGTU_WS   (union Operand *Operands);
word BGTU_LS   (union Operand *Operands);
word BGTU_BBa  (union Operand *Operands);
word BGTU_WBa  (union Operand *Operands);
word BGTU_LBa  (union Operand *Operands);
word BGTU_BaB  (union Operand *Operands);
word BGTU_BaW  (union Operand *Operands);
word BGTU_BaL  (union Operand *Operands);
word BGTU_BaB_C(union Operand *Operands);
word BGTU_BaW_C(union Operand *Operands);
word BGTU_BaL_C(union Operand *Operands);
word BGTU_BaB_S(union Operand *Operands);
word BGTU_BaW_S(union Operand *Operands);
word BGTU_BaL_S(union Operand *Operands);
word BGTU_BS_S(union Operand *Operands);
word BGTU_WS_S(union Operand *Operands);
word BGTU_LS_S(union Operand *Operands);
word BGTU_BS_C(union Operand *Operands);
word BGTU_WS_C(union Operand *Operands);
word BGTU_LS_C(union Operand *Operands);
word BGTU_BAr   (union Operand *Operands);
word BGTU_WAr   (union Operand *Operands);
word BGTU_LAr   (union Operand *Operands);
word BGTU_ArB   (union Operand *Operands);
word BGTU_ArW   (union Operand *Operands);
word BGTU_ArL   (union Operand *Operands);
word BGTU_BAr_C (union Operand *Operands);
word BGTU_WAr_C (union Operand *Operands);
word BGTU_LAr_C (union Operand *Operands);
word BGTU_BAr_Ba(union Operand *Operands);
word BGTU_WAr_Ba(union Operand *Operands);
word BGTU_LAr_Ba(union Operand *Operands);
word BGTU_BAr_S (union Operand *Operands);
word BGTU_WAr_S (union Operand *Operands);
word BGTU_LAr_S (union Operand *Operands);

word BLT_BB    (union Operand *Operands);
word BLT_WW    (union Operand *Operands);
word BLT_LL    (union Operand *Operands);
word BLT_DD    (union Operand *Operands);
word BLT_BC    (union Operand *Operands);
word BLT_WC    (union Operand *Operands);
word BLT_LC    (union Operand *Operands);
word BLT_DC    (union Operand *Operands);
word BLT_BS    (union Operand *Operands);
word BLT_WS    (union Operand *Operands);
word BLT_LS    (union Operand *Operands);
word BLT_DS    (union Operand *Operands);
word BLT_BBa   (union Operand *Operands);
word BLT_WBa   (union Operand *Operands);
word BLT_LBa   (union Operand *Operands);
word BLT_DBa   (union Operand *Operands);
word BLT_BaB   (union Operand *Operands);
word BLT_BaW   (union Operand *Operands);
word BLT_BaL   (union Operand *Operands);
word BLT_BaD   (union Operand *Operands);
word BLT_BaB_C (union Operand *Operands);
word BLT_BaW_C (union Operand *Operands);
word BLT_BaL_C (union Operand *Operands);
word BLT_BaD_C (union Operand *Operands);
word BLT_BaB_S (union Operand *Operands);
word BLT_BaW_S (union Operand *Operands);
word BLT_BaL_S (union Operand *Operands);
word BLT_BaD_S (union Operand *Operands);
word BLT_BS_S (union Operand *Operands);
word BLT_WS_S (union Operand *Operands);
word BLT_LS_S (union Operand *Operands);
word BLT_DS_S (union Operand *Operands);
word BLT_BS_C (union Operand *Operands);
word BLT_WS_C (union Operand *Operands);
word BLT_LS_C (union Operand *Operands);
word BLT_DS_C (union Operand *Operands);
word BLT_BAr    (union Operand *Operands);
word BLT_WAr    (union Operand *Operands);
word BLT_LAr    (union Operand *Operands);
word BLT_DAr    (union Operand *Operands);
word BLT_ArB    (union Operand *Operands);
word BLT_ArW    (union Operand *Operands);
word BLT_ArL    (union Operand *Operands);
word BLT_ArD    (union Operand *Operands);
word BLT_BAr_C  (union Operand *Operands);
word BLT_WAr_C  (union Operand *Operands);
word BLT_LAr_C  (union Operand *Operands);
word BLT_DAr_C  (union Operand *Operands);
word BLT_BAr_Ba (union Operand *Operands);
word BLT_WAr_Ba (union Operand *Operands);
word BLT_LAr_Ba (union Operand *Operands);
word BLT_DAr_Ba (union Operand *Operands);
word BLT_BAr_S  (union Operand *Operands);
word BLT_WAr_S  (union Operand *Operands);
word BLT_LAr_S  (union Operand *Operands);
word BLT_DAr_S  (union Operand *Operands);

word BLTU_BB   (union Operand *Operands);
word BLTU_WW   (union Operand *Operands);
word BLTU_LL   (union Operand *Operands);
word BLTU_BC   (union Operand *Operands);
word BLTU_WC   (union Operand *Operands);
word BLTU_LC   (union Operand *Operands);
word BLTU_BS   (union Operand *Operands);
word BLTU_WS   (union Operand *Operands);
word BLTU_LS   (union Operand *Operands);
word BLTU_BBa  (union Operand *Operands);
word BLTU_WBa  (union Operand *Operands);
word BLTU_LBa  (union Operand *Operands);
word BLTU_BaB  (union Operand *Operands);
word BLTU_BaW  (union Operand *Operands);
word BLTU_BaL  (union Operand *Operands);
word BLTU_BaB_C(union Operand *Operands);
word BLTU_BaW_C(union Operand *Operands);
word BLTU_BaL_C(union Operand *Operands);
word BLTU_BaB_S(union Operand *Operands);
word BLTU_BaW_S(union Operand *Operands);
word BLTU_BaL_S(union Operand *Operands);
word BLTU_BS_S(union Operand *Operands);
word BLTU_WS_S(union Operand *Operands);
word BLTU_LS_S(union Operand *Operands);
word BLTU_BS_C(union Operand *Operands);
word BLTU_WS_C(union Operand *Operands);
word BLTU_LS_C(union Operand *Operands);
word BLTU_BAr   (union Operand *Operands);
word BLTU_WAr   (union Operand *Operands);
word BLTU_LAr   (union Operand *Operands);
word BLTU_ArB   (union Operand *Operands);
word BLTU_ArW   (union Operand *Operands);
word BLTU_ArL   (union Operand *Operands);
word BLTU_BAr_C (union Operand *Operands);
word BLTU_WAr_C (union Operand *Operands);
word BLTU_LAr_C (union Operand *Operands);
word BLTU_BAr_Ba(union Operand *Operands);
word BLTU_WAr_Ba(union Operand *Operands);
word BLTU_LAr_Ba(union Operand *Operands);
word BLTU_BAr_S (union Operand *Operands);
word BLTU_WAr_S (union Operand *Operands);
word BLTU_LAr_S (union Operand *Operands);

word BGE_BB    (union Operand *Operands);
word BGE_WW    (union Operand *Operands);
word BGE_LL    (union Operand *Operands);
word BGE_DD    (union Operand *Operands);
word BGE_BC    (union Operand *Operands);
word BGE_WC    (union Operand *Operands);
word BGE_LC    (union Operand *Operands);
word BGE_DC    (union Operand *Operands);
word BGE_BS    (union Operand *Operands);
word BGE_WS    (union Operand *Operands);
word BGE_LS    (union Operand *Operands);
word BGE_DS    (union Operand *Operands);
word BGE_BBa   (union Operand *Operands);
word BGE_WBa   (union Operand *Operands);
word BGE_LBa   (union Operand *Operands);
word BGE_DBa   (union Operand *Operands);
word BGE_BaB   (union Operand *Operands);
word BGE_BaW   (union Operand *Operands);
word BGE_BaL   (union Operand *Operands);
word BGE_BaD   (union Operand *Operands);
word BGE_BaB_C (union Operand *Operands);
word BGE_BaW_C (union Operand *Operands);
word BGE_BaL_C (union Operand *Operands);
word BGE_BaD_C (union Operand *Operands);
word BGE_BaB_S (union Operand *Operands);
word BGE_BaW_S (union Operand *Operands);
word BGE_BaL_S (union Operand *Operands);
word BGE_BaD_S (union Operand *Operands);
word BGE_BS_S (union Operand *Operands);
word BGE_WS_S (union Operand *Operands);
word BGE_LS_S (union Operand *Operands);
word BGE_DS_S (union Operand *Operands);
word BGE_BS_C (union Operand *Operands);
word BGE_WS_C (union Operand *Operands);
word BGE_LS_C (union Operand *Operands);
word BGE_DS_C (union Operand *Operands);
word BGE_BAr    (union Operand *Operands);
word BGE_WAr    (union Operand *Operands);
word BGE_LAr    (union Operand *Operands);
word BGE_DAr    (union Operand *Operands);
word BGE_ArB    (union Operand *Operands);
word BGE_ArW    (union Operand *Operands);
word BGE_ArL    (union Operand *Operands);
word BGE_ArD    (union Operand *Operands);
word BGE_BAr_C  (union Operand *Operands);
word BGE_WAr_C  (union Operand *Operands);
word BGE_LAr_C  (union Operand *Operands);
word BGE_DAr_C  (union Operand *Operands);
word BGE_BAr_Ba (union Operand *Operands);
word BGE_WAr_Ba (union Operand *Operands);
word BGE_LAr_Ba (union Operand *Operands);
word BGE_DAr_Ba (union Operand *Operands);
word BGE_BAr_S  (union Operand *Operands);
word BGE_WAr_S  (union Operand *Operands);
word BGE_LAr_S  (union Operand *Operands);
word BGE_DAr_S  (union Operand *Operands);

word BGEU_BB   (union Operand *Operands);
word BGEU_WW   (union Operand *Operands);
word BGEU_LL   (union Operand *Operands);
word BGEU_BC   (union Operand *Operands);
word BGEU_WC   (union Operand *Operands);
word BGEU_LC   (union Operand *Operands);
word BGEU_BS   (union Operand *Operands);
word BGEU_WS   (union Operand *Operands);
word BGEU_LS   (union Operand *Operands);
word BGEU_BBa  (union Operand *Operands);
word BGEU_WBa  (union Operand *Operands);
word BGEU_LBa  (union Operand *Operands);
word BGEU_BaB  (union Operand *Operands);
word BGEU_BaW  (union Operand *Operands);
word BGEU_BaL  (union Operand *Operands);
word BGEU_BaB_C(union Operand *Operands);
word BGEU_BaW_C(union Operand *Operands);
word BGEU_BaL_C(union Operand *Operands);
word BGEU_BaB_S(union Operand *Operands);
word BGEU_BaW_S(union Operand *Operands);
word BGEU_BaL_S(union Operand *Operands);
word BGEU_BS_S(union Operand *Operands);
word BGEU_WS_S(union Operand *Operands);
word BGEU_LS_S(union Operand *Operands);
word BGEU_BS_C(union Operand *Operands);
word BGEU_WS_C(union Operand *Operands);
word BGEU_LS_C(union Operand *Operands);
word BGEU_BAr   (union Operand *Operands);
word BGEU_WAr   (union Operand *Operands);
word BGEU_LAr   (union Operand *Operands);
word BGEU_ArB   (union Operand *Operands);
word BGEU_ArW   (union Operand *Operands);
word BGEU_ArL   (union Operand *Operands);
word BGEU_BAr_C (union Operand *Operands);
word BGEU_WAr_C (union Operand *Operands);
word BGEU_LAr_C (union Operand *Operands);
word BGEU_BAr_Ba(union Operand *Operands);
word BGEU_WAr_Ba(union Operand *Operands);
word BGEU_LAr_Ba(union Operand *Operands);
word BGEU_BAr_S (union Operand *Operands);
word BGEU_WAr_S (union Operand *Operands);
word BGEU_LAr_S (union Operand *Operands);

word BLE_BB    (union Operand *Operands);
word BLE_WW    (union Operand *Operands);
word BLE_LL    (union Operand *Operands);
word BLE_DD    (union Operand *Operands);
word BLE_BC    (union Operand *Operands);
word BLE_WC    (union Operand *Operands);
word BLE_LC    (union Operand *Operands);
word BLE_DC    (union Operand *Operands);
word BLE_BS    (union Operand *Operands);
word BLE_WS    (union Operand *Operands);
word BLE_LS    (union Operand *Operands);
word BLE_DS    (union Operand *Operands);
word BLE_BBa   (union Operand *Operands);
word BLE_WBa   (union Operand *Operands);
word BLE_LBa   (union Operand *Operands);
word BLE_DBa   (union Operand *Operands);
word BLE_BaB   (union Operand *Operands);
word BLE_BaW   (union Operand *Operands);
word BLE_BaL   (union Operand *Operands);
word BLE_BaD   (union Operand *Operands);
word BLE_BaB_C (union Operand *Operands);
word BLE_BaW_C (union Operand *Operands);
word BLE_BaL_C (union Operand *Operands);
word BLE_BaD_C (union Operand *Operands);
word BLE_BaB_S (union Operand *Operands);
word BLE_BaW_S (union Operand *Operands);
word BLE_BaL_S (union Operand *Operands);
word BLE_BaD_S (union Operand *Operands);
word BLE_BS_S (union Operand *Operands);
word BLE_WS_S (union Operand *Operands);
word BLE_LS_S (union Operand *Operands);
word BLE_DS_S (union Operand *Operands);
word BLE_BS_C (union Operand *Operands);
word BLE_WS_C (union Operand *Operands);
word BLE_LS_C (union Operand *Operands);
word BLE_DS_C (union Operand *Operands);
word BLE_BAr    (union Operand *Operands);
word BLE_WAr    (union Operand *Operands);
word BLE_LAr    (union Operand *Operands);
word BLE_DAr    (union Operand *Operands);
word BLE_ArB    (union Operand *Operands);
word BLE_ArW    (union Operand *Operands);
word BLE_ArL    (union Operand *Operands);
word BLE_ArD    (union Operand *Operands);
word BLE_BAr_C  (union Operand *Operands);
word BLE_WAr_C  (union Operand *Operands);
word BLE_LAr_C  (union Operand *Operands);
word BLE_DAr_C  (union Operand *Operands);
word BLE_BAr_Ba (union Operand *Operands);
word BLE_WAr_Ba (union Operand *Operands);
word BLE_LAr_Ba (union Operand *Operands);
word BLE_DAr_Ba (union Operand *Operands);
word BLE_BAr_S  (union Operand *Operands);
word BLE_WAr_S  (union Operand *Operands);
word BLE_LAr_S  (union Operand *Operands);
word BLE_DAr_S  (union Operand *Operands);

word BLEU_BB   (union Operand *Operands);
word BLEU_WW   (union Operand *Operands);
word BLEU_LL   (union Operand *Operands);
word BLEU_BC   (union Operand *Operands);
word BLEU_WC   (union Operand *Operands);
word BLEU_LC   (union Operand *Operands);
word BLEU_BS   (union Operand *Operands);
word BLEU_WS   (union Operand *Operands);
word BLEU_LS   (union Operand *Operands);
word BLEU_BBa  (union Operand *Operands);
word BLEU_WBa  (union Operand *Operands);
word BLEU_LBa  (union Operand *Operands);
word BLEU_BaB  (union Operand *Operands);
word BLEU_BaW  (union Operand *Operands);
word BLEU_BaL  (union Operand *Operands);
word BLEU_BaB_C(union Operand *Operands);
word BLEU_BaW_C(union Operand *Operands);
word BLEU_BaL_C(union Operand *Operands);
word BLEU_BaB_S(union Operand *Operands);
word BLEU_BaW_S(union Operand *Operands);
word BLEU_BaL_S(union Operand *Operands);
word BLEU_BS_S(union Operand *Operands);
word BLEU_WS_S(union Operand *Operands);
word BLEU_LS_S(union Operand *Operands);
word BLEU_BS_C(union Operand *Operands);
word BLEU_WS_C(union Operand *Operands);
word BLEU_LS_C(union Operand *Operands);
word BLEU_BAr   (union Operand *Operands);
word BLEU_WAr   (union Operand *Operands);
word BLEU_LAr   (union Operand *Operands);
word BLEU_ArB   (union Operand *Operands);
word BLEU_ArW   (union Operand *Operands);
word BLEU_ArL   (union Operand *Operands);
word BLEU_BAr_C (union Operand *Operands);
word BLEU_WAr_C (union Operand *Operands);
word BLEU_LAr_C (union Operand *Operands);
word BLEU_BAr_Ba(union Operand *Operands);
word BLEU_WAr_Ba(union Operand *Operands);
word BLEU_LAr_Ba(union Operand *Operands);
word BLEU_BAr_S (union Operand *Operands);
word BLEU_WAr_S (union Operand *Operands);
word BLEU_LAr_S (union Operand *Operands);

word MOV_B_B    (union Operand *Operands);
word MOV_B_W    (union Operand *Operands);
word MOV_B_L    (union Operand *Operands);
word MOV_B_D    (union Operand *Operands);
word MOV_B_C    (union Operand *Operands);
word MOV_B_SB   (union Operand *Operands);
word MOV_B_SW   (union Operand *Operands);
word MOV_B_SL   (union Operand *Operands);
word MOV_B_SD   (union Operand *Operands);
word MOV_B_BaB  (union Operand *Operands);
word MOV_B_BaW  (union Operand *Operands);
word MOV_B_BaL  (union Operand *Operands);
word MOV_B_BaD  (union Operand *Operands);
word MOV_W_B    (union Operand *Operands);
word MOV_W_W    (union Operand *Operands);
word MOV_W_L    (union Operand *Operands);
word MOV_W_D    (union Operand *Operands);
word MOV_W_C    (union Operand *Operands);
word MOV_W_SB   (union Operand *Operands);
word MOV_W_SW   (union Operand *Operands);
word MOV_W_SL   (union Operand *Operands);
word MOV_W_SD   (union Operand *Operands);
word MOV_W_BaB  (union Operand *Operands);
word MOV_W_BaW  (union Operand *Operands);
word MOV_W_BaL  (union Operand *Operands);
word MOV_W_BaD  (union Operand *Operands);
word MOV_L_B    (union Operand *Operands);
word MOV_L_W    (union Operand *Operands);
word MOV_L_L    (union Operand *Operands);
word MOV_L_D    (union Operand *Operands);
word MOV_L_C    (union Operand *Operands);
word MOV_L_SB   (union Operand *Operands);
word MOV_L_SW   (union Operand *Operands);
word MOV_L_SL   (union Operand *Operands);
word MOV_L_SD   (union Operand *Operands);
word MOV_L_BaB  (union Operand *Operands);
word MOV_L_BaW  (union Operand *Operands);
word MOV_L_BaL  (union Operand *Operands);
word MOV_L_BaD  (union Operand *Operands);
word MOV_D_B    (union Operand *Operands);
word MOV_D_W    (union Operand *Operands);
word MOV_D_L    (union Operand *Operands);
word MOV_D_D    (union Operand *Operands);
word MOV_D_C    (union Operand *Operands);
word MOV_D_SB   (union Operand *Operands);
word MOV_D_SW   (union Operand *Operands);
word MOV_D_SL   (union Operand *Operands);
word MOV_D_SD   (union Operand *Operands);
word MOV_D_BaB  (union Operand *Operands);
word MOV_D_BaW  (union Operand *Operands);
word MOV_D_BaL  (union Operand *Operands);
word MOV_D_BaD  (union Operand *Operands);
word MOV_BaB_B  (union Operand *Operands);
word MOV_BaB_W  (union Operand *Operands);
word MOV_BaB_L  (union Operand *Operands);
word MOV_BaB_D  (union Operand *Operands);
word MOV_BaB_C  (union Operand *Operands);
word MOV_BaB_SB (union Operand *Operands);
word MOV_BaB_SW (union Operand *Operands);
word MOV_BaB_SL (union Operand *Operands);
word MOV_BaB_SD (union Operand *Operands);
word MOV_BaB_BaB(union Operand *Operands);
word MOV_BaB_BaW(union Operand *Operands);
word MOV_BaB_BaL(union Operand *Operands);
word MOV_BaB_BaD(union Operand *Operands);
word MOV_BaW_B  (union Operand *Operands);
word MOV_BaW_W  (union Operand *Operands);
word MOV_BaW_L  (union Operand *Operands);
word MOV_BaW_D  (union Operand *Operands);
word MOV_BaW_C  (union Operand *Operands);
word MOV_BaW_SB (union Operand *Operands);
word MOV_BaW_SW (union Operand *Operands);
word MOV_BaW_SL (union Operand *Operands);
word MOV_BaW_SD (union Operand *Operands);
word MOV_BaW_BaB(union Operand *Operands);
word MOV_BaW_BaW(union Operand *Operands);
word MOV_BaW_BaL(union Operand *Operands);
word MOV_BaW_BaD(union Operand *Operands);
word MOV_BaL_B  (union Operand *Operands);
word MOV_BaL_W  (union Operand *Operands);
word MOV_BaL_L  (union Operand *Operands);
word MOV_BaL_D  (union Operand *Operands);
word MOV_BaL_C  (union Operand *Operands);
word MOV_BaL_SB (union Operand *Operands);
word MOV_BaL_SW (union Operand *Operands);
word MOV_BaL_SL (union Operand *Operands);
word MOV_BaL_SD (union Operand *Operands);
word MOV_BaL_BaB(union Operand *Operands);
word MOV_BaL_BaW(union Operand *Operands);
word MOV_BaL_BaL(union Operand *Operands);
word MOV_BaL_BaD(union Operand *Operands);
word MOV_BaD_B  (union Operand *Operands);
word MOV_BaD_W  (union Operand *Operands);
word MOV_BaD_L  (union Operand *Operands);
word MOV_BaD_D  (union Operand *Operands);
word MOV_BaD_C  (union Operand *Operands);
word MOV_BaD_SB (union Operand *Operands);
word MOV_BaD_SW (union Operand *Operands);
word MOV_BaD_SL (union Operand *Operands);
word MOV_BaD_SD (union Operand *Operands);
word MOV_BaD_BaB(union Operand *Operands);
word MOV_BaD_BaW(union Operand *Operands);
word MOV_BaD_BaL(union Operand *Operands);
word MOV_BaD_BaD(union Operand *Operands);
word MOV_BAr_B    (union Operand *Operands);
word MOV_BAr_W    (union Operand *Operands);
word MOV_BAr_L    (union Operand *Operands);
word MOV_BAr_D    (union Operand *Operands);
word MOV_BAr_C    (union Operand *Operands);
word MOV_BAr_SB   (union Operand *Operands);
word MOV_BAr_SW   (union Operand *Operands);
word MOV_BAr_SL   (union Operand *Operands);
word MOV_BAr_SD   (union Operand *Operands);
word MOV_BAr_BaB  (union Operand *Operands);
word MOV_BAr_BaW  (union Operand *Operands);
word MOV_BAr_BaL  (union Operand *Operands);
word MOV_BAr_BaD  (union Operand *Operands);
word MOV_WAr_B    (union Operand *Operands);
word MOV_WAr_W    (union Operand *Operands);
word MOV_WAr_L    (union Operand *Operands);
word MOV_WAr_D    (union Operand *Operands);
word MOV_WAr_C    (union Operand *Operands);
word MOV_WAr_SB   (union Operand *Operands);
word MOV_WAr_SW   (union Operand *Operands);
word MOV_WAr_SL   (union Operand *Operands);
word MOV_WAr_SD   (union Operand *Operands);
word MOV_WAr_BaB  (union Operand *Operands);
word MOV_WAr_BaW  (union Operand *Operands);
word MOV_WAr_BaL  (union Operand *Operands);
word MOV_WAr_BaD  (union Operand *Operands);
word MOV_LAr_B    (union Operand *Operands);
word MOV_LAr_W    (union Operand *Operands);
word MOV_LAr_L    (union Operand *Operands);
word MOV_LAr_D    (union Operand *Operands);
word MOV_LAr_C    (union Operand *Operands);
word MOV_LAr_SB   (union Operand *Operands);
word MOV_LAr_SW   (union Operand *Operands);
word MOV_LAr_SL   (union Operand *Operands);
word MOV_LAr_SD   (union Operand *Operands);
word MOV_LAr_BaB  (union Operand *Operands);
word MOV_LAr_BaW  (union Operand *Operands);
word MOV_LAr_BaL  (union Operand *Operands);
word MOV_LAr_BaD  (union Operand *Operands);
word MOV_DAr_B    (union Operand *Operands);
word MOV_DAr_W    (union Operand *Operands);
word MOV_DAr_L    (union Operand *Operands);
word MOV_DAr_D    (union Operand *Operands);
word MOV_DAr_C    (union Operand *Operands);
word MOV_DAr_SB   (union Operand *Operands);
word MOV_DAr_SW   (union Operand *Operands);
word MOV_DAr_SL   (union Operand *Operands);
word MOV_DAr_SD   (union Operand *Operands);
word MOV_DAr_BaB  (union Operand *Operands);
word MOV_DAr_BaW  (union Operand *Operands);
word MOV_DAr_BaL  (union Operand *Operands);
word MOV_DAr_BaD  (union Operand *Operands);
word MOV_B_BAr    (union Operand *Operands);
word MOV_W_BAr    (union Operand *Operands);
word MOV_L_BAr    (union Operand *Operands);
word MOV_D_BAr    (union Operand *Operands);
word MOV_BaB_BAr  (union Operand *Operands);
word MOV_BaW_BAr  (union Operand *Operands);
word MOV_BaL_BAr  (union Operand *Operands);
word MOV_BaD_BAr  (union Operand *Operands);
word MOV_B_WAr    (union Operand *Operands);
word MOV_W_WAr    (union Operand *Operands);
word MOV_L_WAr    (union Operand *Operands);
word MOV_D_WAr    (union Operand *Operands);
word MOV_BaB_WAr  (union Operand *Operands);
word MOV_BaW_WAr  (union Operand *Operands);
word MOV_BaL_WAr  (union Operand *Operands);
word MOV_BaD_WAr  (union Operand *Operands);
word MOV_B_LAr    (union Operand *Operands);
word MOV_W_LAr    (union Operand *Operands);
word MOV_L_LAr    (union Operand *Operands);
word MOV_D_LAr    (union Operand *Operands);
word MOV_BaB_LAr  (union Operand *Operands);
word MOV_BaW_LAr  (union Operand *Operands);
word MOV_BaL_LAr  (union Operand *Operands);
word MOV_BaD_LAr  (union Operand *Operands);
word MOV_B_DAr    (union Operand *Operands);
word MOV_W_DAr    (union Operand *Operands);
word MOV_L_DAr    (union Operand *Operands);
word MOV_D_DAr    (union Operand *Operands);
word MOV_BaB_DAr  (union Operand *Operands);
word MOV_BaW_DAr  (union Operand *Operands);
word MOV_BaL_DAr  (union Operand *Operands);
word MOV_BaD_DAr  (union Operand *Operands);
word MOV_BAr_BAr  (union Operand *Operands);
word MOV_BAr_WAr  (union Operand *Operands);
word MOV_BAr_LAr  (union Operand *Operands);
word MOV_BAr_DAr  (union Operand *Operands);
word MOV_WAr_BAr  (union Operand *Operands);
word MOV_WAr_WAr  (union Operand *Operands);
word MOV_WAr_LAr  (union Operand *Operands);
word MOV_WAr_DAr  (union Operand *Operands);
word MOV_LAr_BAr  (union Operand *Operands);
word MOV_LAr_WAr  (union Operand *Operands);
word MOV_LAr_LAr  (union Operand *Operands);
word MOV_LAr_DAr  (union Operand *Operands);
word MOV_DAr_BAr  (union Operand *Operands);
word MOV_DAr_WAr  (union Operand *Operands);
word MOV_DAr_LAr  (union Operand *Operands);
word MOV_DAr_DAr  (union Operand *Operands);

word MOVU_W_B    (union Operand *Operands);
word MOVU_W_SB   (union Operand *Operands);
word MOVU_W_BaB  (union Operand *Operands);
word MOVU_L_B    (union Operand *Operands);
word MOVU_L_W    (union Operand *Operands);
word MOVU_L_SB   (union Operand *Operands);
word MOVU_L_SW   (union Operand *Operands);
word MOVU_L_BaB  (union Operand *Operands);
word MOVU_L_BaW  (union Operand *Operands);
word MOVU_D_B    (union Operand *Operands);
word MOVU_D_W    (union Operand *Operands);
word MOVU_D_L    (union Operand *Operands);
word MOVU_D_SB   (union Operand *Operands);
word MOVU_D_SW   (union Operand *Operands);
word MOVU_D_SL   (union Operand *Operands);
word MOVU_D_BaB  (union Operand *Operands);
word MOVU_D_BaW  (union Operand *Operands);
word MOVU_D_BaL  (union Operand *Operands);
word MOVU_BaW_B  (union Operand *Operands);
word MOVU_BaW_SB (union Operand *Operands);
word MOVU_BaW_BaB(union Operand *Operands);
word MOVU_BaL_B  (union Operand *Operands);
word MOVU_BaL_W  (union Operand *Operands);
word MOVU_BaL_SB (union Operand *Operands);
word MOVU_BaL_SW (union Operand *Operands);
word MOVU_BaL_BaB(union Operand *Operands);
word MOVU_BaL_BaW(union Operand *Operands);
word MOVU_BaD_B  (union Operand *Operands);
word MOVU_BaD_W  (union Operand *Operands);
word MOVU_BaD_L  (union Operand *Operands);
word MOVU_BaD_SB (union Operand *Operands);
word MOVU_BaD_SW (union Operand *Operands);
word MOVU_BaD_SL (union Operand *Operands);
word MOVU_BaD_BaB(union Operand *Operands);
word MOVU_BaD_BaW(union Operand *Operands);
word MOVU_BaD_BaL(union Operand *Operands);

word MOVU_WAr_B   (union Operand *Operands);
word MOVU_WAr_SB  (union Operand *Operands);
word MOVU_WAr_BaB (union Operand *Operands);
word MOVU_LAr_B   (union Operand *Operands);
word MOVU_LAr_W   (union Operand *Operands);
word MOVU_LAr_SB  (union Operand *Operands);
word MOVU_LAr_SW  (union Operand *Operands);
word MOVU_LAr_BaB (union Operand *Operands);
word MOVU_LAr_BaW (union Operand *Operands);
word MOVU_DAr_B   (union Operand *Operands);
word MOVU_DAr_W   (union Operand *Operands);
word MOVU_DAr_L   (union Operand *Operands);
word MOVU_DAr_SB  (union Operand *Operands);
word MOVU_DAr_SW  (union Operand *Operands);
word MOVU_DAr_SL  (union Operand *Operands);
word MOVU_DAr_BaB (union Operand *Operands);
word MOVU_DAr_BaW (union Operand *Operands);
word MOVU_DAr_BaL (union Operand *Operands);
word MOVU_W_BAr   (union Operand *Operands);
word MOVU_L_BAr   (union Operand *Operands);
word MOVU_D_BAr   (union Operand *Operands);
word MOVU_BaW_BAr (union Operand *Operands);
word MOVU_BaL_BAr (union Operand *Operands);
word MOVU_BaD_BAr (union Operand *Operands);
word MOVU_L_WAr   (union Operand *Operands);
word MOVU_D_WAr   (union Operand *Operands);
word MOVU_BaL_WAr (union Operand *Operands);
word MOVU_BaD_WAr (union Operand *Operands);
word MOVU_D_LAr   (union Operand *Operands);
word MOVU_BaD_LAr (union Operand *Operands);
word MOVU_WAr_BAr (union Operand *Operands);
word MOVU_LAr_BAr (union Operand *Operands);
word MOVU_LAr_WAr (union Operand *Operands);
word MOVU_DAr_BAr (union Operand *Operands);
word MOVU_DAr_WAr (union Operand *Operands);
word MOVU_DAr_LAr (union Operand *Operands);

word SetMsg_Av (union Operand *Operands);
word SetMsg_Pr (union Operand *Operands);
word SetMsg_Srv(union Operand *Operands);

word ClrMsg_Av (union Operand *Operands);
word ClrMsg_Pr (union Operand *Operands);
word ClrMsg_Srv(union Operand *Operands);

word ClrAllMsg_Av (union Operand *Operands);
word ClrAllMsg_Pr (union Operand *Operands);
word ClrAllMsg_Srv(union Operand *Operands);

word GOTO(union Operand *Operands);
word CALL(union Operand *Operands);
word CALL_B(union Operand *Operands);
word RET (union Operand *Operands);

word rezerv  (union Operand *Operands);

//������� �������
word bSin    (union Operand *Operands);
word bCos    (union Operand *Operands);
word bTan    (union Operand *Operands);
word bAsin   (union Operand *Operands);
word bAcos   (union Operand *Operands);
word bAtan   (union Operand *Operands);
word bSqr    (union Operand *Operands);
word bAbsD   (union Operand *Operands);
word bAbsI   (union Operand *Operands);
word bLimD   (union Operand *Operands);
word bLimI   (union Operand *Operands);
word bIZUD   (union Operand *Operands);
word bIZUI   (union Operand *Operands);
word bZI     (union Operand *Operands);
word bini_ZI (union Operand *Operands);
word bPI_reg (union Operand *Operands);
word bFiltr  (union Operand *Operands);
word bAverage (union Operand *Operands);


struct Tabl_Obj_MSG
{
  char Avar[32][18]  ;
  char Predupr[32][18]  ;
  char Service[32][18]  ;
};

//���������� ������ �������� ������� �������
#define _Numb_blocks_bSin      0xffff
#define _Numb_blocks_bCos      0xffff
#define _Numb_blocks_bTan      0xffff
#define _Numb_blocks_bAsin     0xffff
#define _Numb_blocks_bAcos     0xffff
#define _Numb_blocks_bAtan     0xffff
#define _Numb_blocks_bSqr      0xffff
#define _Numb_blocks_bAbsD     0xffff
#define _Numb_blocks_bAbsI     0xffff
#define _Numb_blocks_bLimD     0xffff
#define _Numb_blocks_bLimI     0xffff
#define _Numb_blocks_bIZUD     0x10
#define _Numb_blocks_bIZUI     0x10
#define _Numb_blocks_bZI       0x10
#define _Numb_blocks_bini_ZI   0xffff
#define _Numb_blocks_bPI_reg   0x10
#define _Numb_blocks_bFiltr    0x10
#define _Numb_blocks_bAverage  0x10

struct base_IZU
{
    word  first;
    word  drob;
    word  time;
};
struct base_ZI
{
    word  first;
    word in_2  ;
    word out_lin;
    word out_2;
    word drob_lin;
    word drob_2;
    word drob;
    word in2_copy;
    word out2_copy;
    word outl_copy;
    word start_m;
    word start_p;
    word time_s;
    word time;
    union
    {
        word all;
        struct
        {
            word trg_pl       :1;
            word trg_min      :1;
            word trg_lin      :1;

            word trg_pl_end   :1;
            word trg_min_end  :1;

        }_;
    } prz;
} ;

struct  bPI_reg_str
{
   word  first;
   word  integrator;
   word  int_drob;
   word  time;
   union
   {
    word all;
    struct
    {
        word ltd_int_p   :1;
        word ltd_int_m   :1;
    }_;

   }lims;
};

struct bfil_str
{
    word first;
    word time ;  //������� �����
    word drob ;
};

struct bAverage_str
{
    word first;
    word n;     //����� ���������
    word time;  //����� ���������� ������� �������� ��������
    slword counter;
};

//struct MSG_Obj_regs
//{
//  union   LW_Reg  avar_first ;        /* ������� ������ ������ */
//  union   LW_Reg  avar ;              /* ������� ��������� ������ */
//  union   LW_Reg  predupr ;           /* ������� �������������� */
//  union   LW_Reg  service ;           /* ������� ��������� ��������� */
//} ;
#define  _Max_Func   0x576
#define  _Numb_Basef 18

#ifdef _INTERPRETER_INCLUDE

struct Tabl_Obj_MSG   Tabl_Msg_obj;
//��������� ������� �������
struct base_IZU b_timeIZUd[_Numb_blocks_bIZUD];
struct base_IZU b_timeIZUi[_Numb_blocks_bIZUI];
struct base_ZI  base_ZIstr[_Numb_blocks_bZI];
struct bPI_reg_str bPI_str[_Numb_blocks_bPI_reg];
struct bfil_str    bfilstr[_Numb_blocks_bFiltr];
struct bAverage_str bAveragestr[_Numb_blocks_bAverage];

//struct MSG_Obj_regs   MSGObjregs;

// ������ ������� ���������� �������: Oprg*[x]
word (*Base_func[_Numb_Basef])(union Operand* ) =
{
    bSin,
    bCos,
    bTan,
    bAsin,
    bAcos,
    bAtan,
    bSqr ,
    bAbsD,
    bAbsI,
    bLimD,
    bLimI,
    bIZUD,
    bIZUI,
    bZI  ,
    bini_ZI,
    bPI_reg,
    bFiltr,
    bAverage
};

word (*Oprg[_Max_Func])(union Operand* ) =
{
    rezerv          , // 0x000 //
    ADD_BB          , // 0x001 //   byte = byte + byte
    ADD_WW          , // 0x002 //   word = word + word
    ADD_LL          , // 0x003 //   lword = lword + lword
    ADD_DD          , // 0x004 //   double = double + double
    ADD_BC          , // 0x005 //   byte = byte + const
    ADD_WC          , // 0x006 //   word = word + const
    ADD_LC          , // 0x007 //   lword = lword + const
    ADD_DC          , // 0x008 //   double = double + const
    ADD_BS          , // 0x009 //   byte = byte + byte_�������
    ADD_WS          , // 0x00A //   word = word + word_�������
    ADD_LS          , // 0x00B //   lword = lword + lword_�������
    ADD_DS          , // 0x00C //   double = double + double_�������
    ADD_BBa         , // 0x00D //   byte = byte + byte_�������
    ADD_WBa         , // 0x00E //   word = word + word_�������
    ADD_LBa         , // 0x00F //   lword = lword + lword_�������
    ADD_DBa         , // 0x010 //   double = double + double_�������
    ADD_BAr         , // 0x011 //   byte = byte + �������� �������
    ADD_WAr         , // 0x012 //   word = word + �������� �������
    ADD_LAr         , // 0x013 //   lword = lword + �������� �������
    ADD_DAr         , // 0x014 //   double = double + �������� �������
    rezerv          , // 0x015 //
    rezerv          , // 0x016 //
    rezerv          , // 0x017 //
    rezerv          , // 0x018 //
    rezerv          , // 0x019 //
    rezerv          , // 0x01A //
    rezerv          , // 0x01B //
    rezerv          , // 0x01C //
    rezerv          , // 0x01D //
    rezerv          , // 0x01E //
    rezerv          , // 0x01F //
    rezerv          , // 0x020 //
    SUB_BB          , // 0x021 //  byte = byte - byte
    SUB_WW          , // 0x022 //  word = word - word
    SUB_LL          , // 0x023 //  lword = lword - lword
    SUB_DD          , // 0x024 //  double = double - double
    SUB_BC          , // 0x025 //  byte = byte - const
    SUB_WC          , // 0x026 //  word = word - const
    SUB_LC          , // 0x027 //  lword = lword - const
    SUB_DC          , // 0x028 //  double = double - const
    SUB_CB          , // 0x029 //  byte = const - byte
    SUB_CW          , // 0x02A //  word = const - word
    SUB_CL          , // 0x02B //  lword = const - lword
    SUB_CD          , // 0x02C //  double = const - double
    SUB_BS          , // 0x02D //  byte = byte - byte_�������
    SUB_WS          , // 0x02E //  word = word - word_�������
    SUB_LS          , // 0x02F //  lword = lword - lword_�������
    SUB_DS          , // 0x030 //  double = double - double_�������
    SUB_SB          , // 0x031 //  byte = byte_������� - byte
    SUB_SW          , // 0x032 //  word = word_������� - word
    SUB_SL          , // 0x033 //  lword = lword_������� - lword
    SUB_SD          , // 0x034 //  double = double_������� - double
    SUB_BBa         , // 0x035 //  byte = byte - byte_�������
    SUB_WBa         , // 0x036 //  word = word - word_�������
    SUB_LBa         , // 0x037 //  lword = lword - lword_�������
    SUB_DBa         , // 0x038 //  double = double - double_�������
    SUB_BaB         , // 0x039 //  byte = byte_������� - byte
    SUB_BaW         , // 0x03A //  word = word_������� - word
    SUB_BaL         , // 0x03B //  lword = lword_������� - lword
    SUB_BaD         , // 0x03C //  double = double_������� - double
    SUB_BAr         , // 0x03D //  byte   = byte   - �������� �������
    SUB_WAr         , // 0x03E //  word   = word   - �������� �������
    SUB_LAr         , // 0x03F //  lword  = lword  - �������� �������
    SUB_DAr         , // 0x040 //  double = double - �������� �������
    SUB_ArB         , // 0x041 //  byte   = �������� ������� -  byte
    SUB_ArW         , // 0x042 //  word   = �������� ������� -  word
    SUB_ArL         , // 0x043 //  lword  = �������� ������� -  lword
    SUB_ArD         , // 0x044 //  double = �������� ������� -  double
    rezerv          , // 0x045 //
    rezerv          , // 0x046 //
    rezerv          , // 0x047 //
    rezerv          , // 0x048 //
    rezerv          , // 0x049 //
    rezerv          , // 0x04A //
    rezerv          , // 0x04B //
    rezerv          , // 0x04C //
    MUL_BB          , // 0x04D //  (sb)byte = (sb)byte * (sb)byte
    MUL_WW          , // 0x04E //  (sw)word = (sw)word * (sw)word
    MUL_LL          , // 0x04F //  (slw)lword = (slw)lword * (slw)lword
    MUL_DD          , // 0x050 //  double = double * double
    MUL_BC          , // 0x051 //  (sb)byte = (sb)byte * (sb)const
    MUL_WC          , // 0x052 //  (sw)word = (sw)word * (sw)const
    MUL_LC          , // 0x053 //  (slw)lword = (slw)lword * (slw)const
    MUL_DC          , // 0x054 //  double = double * const
    MUL_BS          , // 0x055 //  (sb)byte = (sb)byte * (sb)byte_�������
    MUL_WS          , // 0x056 //  (sw)word = (sw)word * (sw)word_�������
    MUL_LS          , // 0x057 //  (slw)lword = (slw)lword * (slw)lword_�������
    MUL_DS          , // 0x058 //  double = double * double_�������
    MUL_BBa         , // 0x059 //  (sb)byte = (sb)byte * (sb)byte_�������
    MUL_WBa         , // 0x05A //  (sw)word = (sw)word * (sw)word_�������
    MUL_LBa         , // 0x05B //  (slw)lword = (slw)lword * (slw)lword_�������
    MUL_DBa         , // 0x05C //  double = double * double_�������
    MULU_BB         , // 0x05D //  (b)byte = (b)byte * (b)byte
    MULU_WW         , // 0x05E //  (w)word = (w)word * (w)word
    MULU_LL         , // 0x05F //  (lw)lword = (lw)lword * (lw)lword
    MULU_BC         , // 0x060 //  (b)byte = (b)byte * (b)const
    MULU_WC         , // 0x061 //  (w)word = (w)word * (w)const
    MULU_LC         , // 0x062 //  (lw)lword = (lw)lword * (lw)const
    MULU_BS         , // 0x063 //  (b)byte = (b)byte * (b)byte_�������
    MULU_WS         , // 0x064 //  (w)word = (w)word * (w)word_�������
    MULU_LS         , // 0x065 //  (lw)lword = (lw)lword * (lw)lword_�������
    MULU_BBa        , // 0x066 //  (b)byte = (b)byte * (b)byte_�������
    MULU_WBa        , // 0x067 //  (w)word = (w)word * (w)word_�������
    MULU_LBa        , // 0x068 //  (lw)lword = (lw)lword * (lw)lword_�������
    MUL_BAr         , // 0x069 //  (sb)byte = (sb)byte * (sb)�������� �������
    MUL_WAr         , // 0x06A //  (sw)word = (sw)word * (sw)�������� �������
    MUL_LAr         , // 0x06B //  (slw)lword = (slw)lword * (slw)�������� �������
    MUL_DAr         , // 0x06C //  double =  double * �������� �������
    MULU_BAr        , // 0x06D //  byte   =  byte   * �������� �������
    MULU_WAr        , // 0x06E //  word   =  word   * �������� �������
    MULU_LAr        , // 0x06F //  lword  =  lword  * �������� �������
    rezerv          , // 0x070 //
    rezerv          , // 0x071 //
    rezerv          , // 0x072 //
    rezerv          , // 0x073 //
    rezerv          , // 0x074 //
    rezerv          , // 0x075 //
    rezerv          , // 0x076 //
    rezerv          , // 0x077 //
    rezerv          , // 0x078 //
    DIV_BB          , // 0x079 //  (sb)byte = (sb)byte / (sb)byte
    DIV_WW          , // 0x07A //  (sw)word = (sw)word / (sw)word
    DIV_LL          , // 0x07B //  (slw)lword = (slw)lword / (slw)lword
    DIV_DD          , // 0x07C //  double = double / double
    DIV_BC          , // 0x07D //  (sb)byte = (sb)byte / (sb)const
    DIV_WC          , // 0x07E //  (sw)word = (sw)word / (sw)const
    DIV_LC          , // 0x07F //  (slw)lword = (slw)lword / (slw)const
    DIV_DC          , // 0x080 //  double = double / const
    DIV_CB          , // 0x081 //  (sb)byte = (sb)const / (sb)byte
    DIV_CW          , // 0x082 //  (sw)word = (sw)const / (sw)word
    DIV_CL          , // 0x083 //  (slw)lword = (slw)const / (slw)lword
    DIV_CD          , // 0x084 //  double = const / double
    DIV_BS          , // 0x085 //  (sb)byte = (sb)byte / (sb)byte_�������
    DIV_WS          , // 0x086 //  (sw)word = (sw)word / (sw)word_�������
    DIV_LS          , // 0x087 //  (slw)lword = (slw)lword / (slw)lword_�������
    DIV_DS          , // 0x088 //  double = double / double_�������
    DIV_SB          , // 0x089 //  (sb)byte = (sb)byte_������� / (sb)byte
    DIV_SW          , // 0x08A //  (sw)word = (sw)word_������� / (sw)word
    DIV_SL          , // 0x08B //  (slw)lword = (slw)lword_������� / (slw)lword
    DIV_SD          , // 0x08C //  double = double_������� / double
    DIV_BBa         , // 0x08D //  (sb)byte = (sb)byte / (sb)byte_�������
    DIV_WBa         , // 0x08E //  (sw)word = (sw)word / (sw)word_�������
    DIV_LBa         , // 0x08F //  (slw)lword = (slw)lword / (slw)lword_�������
    DIV_DBa         , // 0x090 //  double = double / double_�������
    DIV_BaB         , // 0x091 //  (sb)byte = (sb)byte_������� / (sb)byte
    DIV_BaW         , // 0x092 //  (sw)word = (sw)word_������� / (sw)word
    DIV_BaL         , // 0x093 //  (slw)lword = (slw)lword_������� / (slw)lword
    DIV_BaD         , // 0x094 //  double = double_������� / double
    DIVU_BB         , // 0x095 //  (b)byte = (b)byte / (b)byte
    DIVU_WW         , // 0x096 //  (w)word = (w)word / (w)word
    DIVU_LL         , // 0x097 //  (lw)lword = (lw)lword / (lw)lword
    DIVU_BC         , // 0x098 //  (b)byte = (b)byte / (b)const
    DIVU_WC         , // 0x099 //  (w)word = (w)word / (w)const
    DIVU_LC         , // 0x09A //  (lw)lword = (lw)lword / (lw)const
    DIVU_CB         , // 0x09B //  (b)byte = (b)const / (b)byte
    DIVU_CW         , // 0x09C //  (w)word = (w)const / (w)word
    DIVU_CL         , // 0x09D //  (lw)lword = (lw)const / (lw)lword
    DIVU_BS         , // 0x09E //  (b)byte = (b)byte / (b)byte_�������
    DIVU_WS         , // 0x09F //  (w)word = (w)word / (w)word_�������
    DIVU_LS         , // 0x0A0 //  (lw)lword = (lw)lword / (lw)lword_�������
    DIVU_SB         , // 0x0A1 //  (b)byte = (b)byte_������� / (b)byte
    DIVU_SW         , // 0x0A2 //  (w)word = (w)word_������� / (w)word
    DIVU_SL         , // 0x0A3 //  (lw)lword = (lw)lword_������� / (lw)lword
    DIVU_BBa        , // 0x0A4 //  (b)byte = (b)byte / (b)byte_�������
    DIVU_WBa        , // 0x0A5 //  (w)word = (w)word / (w)word_�������
    DIVU_LBa        , // 0x0A6 //  (lw)lword = (lw)lword / (lw)lword_�������
    DIVU_BaB        , // 0x0A7 //  (b)byte = (b)byte_������� / (b)byte
    DIVU_BaW        , // 0x0A8 //  (w)word = (w)word_������� / (w)word
    DIVU_BaL        , // 0x0A9 //  (lw)lword = (lw)lword_������� / (lw)lword
    DIV_BAr         , // 0x0AA //  (sb)byte   = (sb)byte   /  �������� �������
    DIV_WAr         , // 0x0AB //  (sw)word   = (sw)word   /  �������� �������
    DIV_LAr         , // 0x0AC //  (slw)lword = (slw)lword /  �������� �������
    DIV_DAr         , // 0x0AD //  double     = double     /  �������� �������
    DIV_ArB         , // 0x0AE //  (sb)byte   = �������� ������� /  (sb)byte
    DIV_ArW         , // 0x0AF //  (sw)word   = �������� ������� /  (sw)word
    DIV_ArL         , // 0x0B0 //  (slw)lword = �������� ������� /  (slw)lword
    DIV_ArD         , // 0x0B1 //  double     = �������� ������� /  double
    DIVU_BAr        , // 0x0B2 //  byte   = byte  /  �������� �������
    DIVU_WAr        , // 0x0B3 //  word   = word  /  �������� �������
    DIVU_LAr        , // 0x0B4 //  lword  = lword /  �������� �������
    DIVU_ArB        , // 0x0B5 //  byte   = �������� ������� /  byte
    DIVU_ArW        , // 0x0B6 //  word   = �������� ������� /  word
    DIVU_ArL        , // 0x0B7 //  lword  = �������� ������� /  lword
    rezerv          , // 0x0B8 //
    rezerv          , // 0x0B9 //
    rezerv          , // 0x0BA //
    rezerv          , // 0x0BB //
    rezerv          , // 0x0BC //
    rezerv          , // 0x0BD //
    rezerv          , // 0x0BE //
    rezerv          , // 0x0BF //
    rezerv          , // 0x0C0 //
    rezerv          , // 0x0C1 //
    rezerv          , // 0x0C2 //
    rezerv          , // 0x0C3 //
    rezerv          , // 0x0C4 //
    rezerv          , // 0x0C5 //
    rezerv          , // 0x0C6 //
    NO_BB           , // 0x0C7 //  byte = ~byte
    NO_WW           , // 0x0C8 //  word = ~word
    NO_LL           , // 0x0C9 //  lword = ~lword
    NO_BS           , // 0x0CA //  byte = ~byte_�������
    NO_WS           , // 0x0CB //  word = ~word_�������
    NO_LS           , // 0x0CC //  lword = ~lword_�������
    NO_BBa          , // 0x0CD //  byte = ~byte_�������
    NO_WBa          , // 0x0CE //  word = ~word_�������
    NO_LBa          , // 0x0CF //  lword = ~lword_�������
    NO_BAr          , // 0x0D0 //  byte  = ~�������� �������
    NO_WAr          , // 0x0D1 //  word  = ~�������� �������
    NO_LAr          , // 0x0D2 //  lword = ~�������� �������
    rezerv          , // 0x0D3 //
    rezerv          , // 0x0D4 //
    rezerv          , // 0x0D5 //
    rezerv          , // 0x0D6 //
    rezerv          , // 0x0D7 //
    rezerv          , // 0x0D8 //
    rezerv          , // 0x0D9 //
    rezerv          , // 0x0DA //
    rezerv          , // 0x0DB //
    rezerv          , // 0x0DC //
    rezerv          , // 0x0DD //
    rezerv          , // 0x0DE //
    rezerv          , // 0x0DF //
    OR_BB           , // 0x0E0 //  byte = byte | byte
    OR_WW           , // 0x0E1 //  word = word | word
    OR_LL           , // 0x0E2 //  lword = lword | lword
    OR_BC           , // 0x0E3 //  byte = byte | const
    OR_WC           , // 0x0E4 //  word = word | const
    OR_LC           , // 0x0E5 //  lword = lword | const
    OR_BS           , // 0x0E6 //  byte = byte | byte_�������
    OR_WS           , // 0x0E7 //  word = word | word_�������
    OR_LS           , // 0x0E8 //  lword = lword | lword_�������
    OR_BBa          , // 0x0E9 //  byte = byte | byte_�������
    OR_WBa          , // 0x0EA //  word = word | word_�������
    OR_LBa          , // 0x0EB //  lword = lword | lword_�������
    OR_BAr          , // 0x0EC //  byte  = byte  | �������� �������
    OR_WAr          , // 0x0ED //  word  = word  | �������� �������
    OR_LAr          , // 0x0EE //  lword = lword | �������� �������
    rezerv          , // 0x0EF //
    rezerv          , // 0x0F0 //
    rezerv          , // 0x0F1 //
    rezerv          , // 0x0F2 //
    rezerv          , // 0x0F3 //
    rezerv          , // 0x0F4 //
    rezerv          , // 0x0F5 //
    rezerv          , // 0x0F6 //
    rezerv          , // 0x0F7 //
    rezerv          , // 0x0F8 //
    rezerv          , // 0x0F9 //
    rezerv          , // 0x0FA //
    rezerv          , // 0x0FB //
    XOR_BB          , // 0x0FC //  byte = byte ^ byte
    XOR_WW          , // 0x0FD //  word = word ^ word
    XOR_LL          , // 0x0FE //  lword = lword ^ lword
    XOR_BC          , // 0x0FF //  byte = byte ^ const
    XOR_WC          , // 0x100 //  word = word ^ const
    XOR_LC          , // 0x101 //  lword = lword ^ const
    XOR_BS          , // 0x102 //  byte = byte ^ byte_�������
    XOR_WS          , // 0x103 //  word = word ^ word_�������
    XOR_LS          , // 0x104 //  lword = lword ^ lword_�������
    XOR_BBa         , // 0x105 //  byte = byte ^ byte_�������
    XOR_WBa         , // 0x106 //  word = word ^ word_�������
    XOR_LBa         , // 0x107 //  lword = lword ^ lword_�������
    XOR_BAr         , // 0x108 //  byte  = byte  ^  �������� �������
    XOR_WAr         , // 0x109 //  word  = word  ^  �������� �������
    XOR_LAr         , // 0x10A //  lword = lword ^  �������� �������
    rezerv          , // 0x10B //
    rezerv          , // 0x10C //
    rezerv          , // 0x10D //
    rezerv          , // 0x10E //
    rezerv          , // 0x10F //
    rezerv          , // 0x110 //
    rezerv          , // 0x111 //
    rezerv          , // 0x112 //
    rezerv          , // 0x113 //
    rezerv          , // 0x114 //
    rezerv          , // 0x115 //
    rezerv          , // 0x116 //
    rezerv          , // 0x117 //
    AND_BB          , // 0x118 //  byte  = byte  & byte
    AND_WW          , // 0x119 //  word  = word  & word
    AND_LL          , // 0x11A //  lword = lword & lword
    AND_BC          , // 0x11B //  byte  = byte  & const
    AND_WC          , // 0x11C //  word  = word  & const
    AND_LC          , // 0x11D //  lword = lword & const
    AND_BS          , // 0x11E //  byte  = byte  & byte_�������
    AND_WS          , // 0x11F //  word  = word  & word_�������
    AND_LS          , // 0x120 //  lword = lword & lword_�������
    AND_BBa         , // 0x121 //  byte  = byte  & byte_�������
    AND_WBa         , // 0x122 //  word  = word  & word_�������
    AND_LBa         , // 0x123 //  lword = lword & lword_�������
    AND_BAr         , // 0x124 //  byte  = byte  & �������� �������
    AND_WAr         , // 0x125 //  word  = word  & �������� �������
    AND_LAr         , // 0x126 //  lword = lword & �������� �������
    rezerv          , // 0x127 //
    rezerv          , // 0x128 //
    rezerv          , // 0x129 //
    rezerv          , // 0x12A //
    rezerv          , // 0x12B //
    rezerv          , // 0x12C //
    rezerv          , // 0x12D //
    rezerv          , // 0x12E //
    rezerv          , // 0x12F //
    rezerv          , // 0x130 //
    rezerv          , // 0x131 //
    rezerv          , // 0x132 //
    rezerv          , // 0x133 //
    ROR_BB          , // 0x134 //  (sb)byte = (sb)byte >> byte
    ROR_WW          , // 0x135 //  (sw)word = (sw)word >> word
    ROR_LL          , // 0x136 //  (slw)lword = (slw)lword >> lword
    ROR_BC          , // 0x137 //  (sb)byte = (sb)byte >> const
    ROR_WC          , // 0x138 //  (sw)word = (sw)word >> const
    ROR_LC          , // 0x139 //  (slw)lword = (slw)lword >> const
    ROR_CB          , // 0x13A //  (sb)byte = (sb)const >> byte
    ROR_CW          , // 0x13B //  (sw)word = (sw)const >> word
    ROR_CL          , // 0x13C //  (slw)lword = (slw)const >> lword
    ROR_BS          , // 0x13D //  (sb)byte = (sb)byte >> byte_�������
    ROR_WS          , // 0x13E //  (sw)word = (sw)word >> word_�������
    ROR_LS          , // 0x13F //  (slw)lword = (slw)lword >> lword_�������
    ROR_SB          , // 0x140 //  (sb)byte = (sb)byte_������� >> byte
    ROR_SW          , // 0x141 //  (sw)word = (sw)word_������� >> word
    ROR_SL          , // 0x142 //  (slw)lword = (slw)lword_������� >> lword
    ROR_BBa         , // 0x143 //  (sb)byte = (sb)byte >> byte_�������
    ROR_WBa         , // 0x144 //  (sw)word = (sw)word >> word_�������
    ROR_LBa         , // 0x145 //  (slw)lword = (slw)lword >> lword_�������
    ROR_BaB         , // 0x146 //  (sb)byte = (sb)byte_������� >> byte
    ROR_BaW         , // 0x147 //  (sw)word = (sw)word_������� >> word
    ROR_BaL         , // 0x148 //  (slw)lword = (slw)lword_������� >> lword
    ROR_BAr         , // 0x149 //  (sb)byte   = (sb)byte   >> �������� �������
    ROR_WAr         , // 0x14A //  (sw)word   = (sw)word   >> �������� �������
    ROR_LAr         , // 0x14B //  (slw)lword = (slw)lword >> �������� �������
    ROR_ArB         , // 0x14C //  (sb)byte   = (sb)�������� ������� >> byte
    ROR_ArW         , // 0x14D //  (sw)word   = (sw)�������� ������� >> word
    ROR_ArL         , // 0x14E //  (slw)lword = (slw)�������� ������� >> lword
    rezerv          , // 0x14F //
    rezerv          , // 0x150 //
    rezerv          , // 0x151 //
    rezerv          , // 0x152 //
    rezerv          , // 0x153 //
    rezerv          , // 0x154 //
    rezerv          , // 0x155 //
    rezerv          , // 0x156 //
    rezerv          , // 0x157 //
    rezerv          , // 0x158 //
    RORU_BB         , // 0x159 //  (b)byte = (b)byte >> byte
    RORU_WW         , // 0x15A //  (w)word = (w)word >> word
    RORU_LL         , // 0x15B //  (lw)lword = (lw)lword >> lword
    RORU_BC         , // 0x15C //  (b)byte = (b)byte >> const
    RORU_WC         , // 0x15D //  (w)word = (w)word >> const
    RORU_LC         , // 0x15E //  (lw)lword = (lw)lword >> const
    RORU_CB         , // 0x15F //  (b)byte = (b)const >> byte
    RORU_CW         , // 0x160 //  (w)word = (w)const >> word
    RORU_CL         , // 0x161 //  (lw)lword = (lw)const >> lword
    RORU_BS         , // 0x162 //  (b)byte = (b)byte >> byte_�������
    RORU_WS         , // 0x163 //  (w)word = (w)word >> word_�������
    RORU_LS         , // 0x164 //  (lw)lword = (lw)lword >> lword_�������
    RORU_SB         , // 0x165 //  (b)byte = (b)byte_������� >> byte
    RORU_SW         , // 0x166 //  (w)word = (w)word_������� >> word
    RORU_SL         , // 0x167 //  (lw)lword = (lw)lword_������� >> lword
    RORU_BBa        , // 0x168 //  (b)byte = (b)byte >> byte_�������
    RORU_WBa        , // 0x169 //  (w)word = (w)word >> word_�������
    RORU_LBa        , // 0x16A //  (lw)lword = (lw)lword >> lword_�������
    RORU_BaB        , // 0x16B //  (b)byte = (b)byte_������� >> byte
    RORU_BaW        , // 0x16C //  (w)word = (w)word_������� >> word
    RORU_BaL        , // 0x16D //  (lw)lword = (lw)lword_������� >> lword
    RORU_BAr        , // 0x16E //  byte   = byte   >> �������� �������
    RORU_WAr        , // 0x16F //  word   = word   >> �������� �������
    RORU_LAr        , // 0x170 //  lword  = lword >> �������� �������
    RORU_ArB        , // 0x171 //  byte   = �������� ������� >> byte
    RORU_ArW        , // 0x172 //  word   = �������� ������� >> word
    RORU_ArL        , // 0x173 //  lword  = �������� ������� >> lword
    rezerv          , // 0x174 //
    rezerv          , // 0x175 //
    rezerv          , // 0x176 //
    rezerv          , // 0x177 //
    rezerv          , // 0x178 //
    rezerv          , // 0x179 //
    rezerv          , // 0x17A //
    rezerv          , // 0x17B //
    rezerv          , // 0x17C //
    rezerv          , // 0x17D //
    ROL_BB          , // 0x17E //  byte = byte << byte
    ROL_WW          , // 0x17F //  word = word << word
    ROL_LL          , // 0x180 //  lword = lword << lword
    ROL_BC          , // 0x181 //  byte = byte << const
    ROL_WC          , // 0x182 //  word = word << const
    ROL_LC          , // 0x183 //  lword = lword << const
    ROL_CB          , // 0x184 //  byte = const << byte
    ROL_CW          , // 0x185 //  word = const << word
    ROL_CL          , // 0x186 //  lword = const << lword
    ROL_BS          , // 0x187 //  byte = byte << byte_�������
    ROL_WS          , // 0x188 //  word = word << word_�������
    ROL_LS          , // 0x189 //  lword = lword << lword_�������
    ROL_SB          , // 0x18A //  byte = byte_������� << byte
    ROL_SW          , // 0x18B //  word = word_������� << word
    ROL_SL          , // 0x18C //  lword = lword_������� << lword
    ROL_BBa         , // 0x18D //  byte = byte << byte_�������
    ROL_WBa         , // 0x18E //  word = word << word_�������
    ROL_LBa         , // 0x18F //  lword = lword << lword_�������
    ROL_BaB         , // 0x190 //  byte = byte_������� << byte
    ROL_BaW         , // 0x191 //  word = word_������� << word
    ROL_BaL         , // 0x192 //  lword = lword_������� << lword
    ROL_BAr         , // 0x193 //  byte = byte   << �������� �������
    ROL_WAr         , // 0x194 //  word = word   << �������� �������
    ROL_LAr         , // 0x195 //  lword = lword << �������� �������
    ROL_ArB         , // 0x196 //  byte = �������� ������� <<  byte
    ROL_ArW         , // 0x197 //  word = �������� ������� <<  word
    ROL_ArL         , // 0x198 //  lword =�������� ������� <<  lword
    rezerv          , // 0x199 //
    rezerv          , // 0x19A //
    rezerv          , // 0x19B //
    rezerv          , // 0x19C //
    rezerv          , // 0x19D //
    rezerv          , // 0x19E //
    rezerv          , // 0x19F //
    rezerv          , // 0x1A0 //
    rezerv          , // 0x1A1 //
    rezerv          , // 0x1A2 //
    BEQ_BB          , // 0x1A3 //  if( byte == byte ) goto label
    BEQ_WW          , // 0x1A4 //  if( word == word ) goto label
    BEQ_LL          , // 0x1A5 //  if( lword == lword ) goto label
    BEQ_DD          , // 0x1A6 //  if( double == double ) goto label
    BEQ_BC          , // 0x1A7 //  if( byte == const ) goto label
    BEQ_WC          , // 0x1A8 //  if( word == const ) goto label
    BEQ_LC          , // 0x1A9 //  if( lword == const ) goto label
    BEQ_DC          , // 0x1AA //  if( double == const ) goto label
    BEQ_BS          , // 0x1AB //  if( byte == byte_������� ) goto label
    BEQ_WS          , // 0x1AC //  if( word == word_������� ) goto label
    BEQ_LS          , // 0x1AD //  if( lword == lword_������� ) goto label
    BEQ_DS          , // 0x1AE //  if( double == double_������� ) goto label
    BEQ_BBa         , // 0x1AF //  if( byte == byte_������� ) goto label
    BEQ_WBa         , // 0x1B0 //  if( word == word_������� ) goto label
    BEQ_LBa         , // 0x1B1 //  if( lword == lword_������� ) goto label
    BEQ_DBa         , // 0x1B2 //  if( double == double_������� ) goto label
    BEQ_BaB         , // 0x1B3 //  if( ������� == ������� ) goto label
    BEQ_BaW         , // 0x1B4 //  if( ������� == ������� ) goto label
    BEQ_BaL         , // 0x1B5 //  if( ������� == ������� ) goto label
    BEQ_BaD         , // 0x1B6 //  if( ������� == ������� ) goto label
    BEQ_BaB_C       , // 0x1B7 //  if( ������� == const ) goto label
    BEQ_BaW_C       , // 0x1B8 //  if( ������� == const ) goto label
    BEQ_BaL_C       , // 0x1B9 //  if( ������� == const ) goto label
    BEQ_BaD_C       , // 0x1BA //  if( ������� == const ) goto label
    BEQ_BaB_S       , // 0x1BB //  if( ������� == byte_������� ) goto label
    BEQ_BaW_S       , // 0x1BC //  if( ������� == word_������� ) goto label
    BEQ_BaL_S       , // 0x1BD //  if( ������� == lword_������� ) goto label
    BEQ_BaD_S       , // 0x1BE //  if( ������� == double_������� ) goto label
    BEQ_BS_S        , // 0x1BF //  if( byte_�������   == byte_������� ) goto label
    BEQ_WS_S        , // 0x1C0 //  if( word_�������   == word_������� ) goto label
    BEQ_LS_S        , // 0x1C1 //  if( lword_�������  == lword_������� ) goto label
    BEQ_DS_S        , // 0x1C2 //  if( double_������� == double_������� ) goto label
    BEQ_BS_C        , // 0x1C3 //  if( byte_�������   == const ) goto label
    BEQ_WS_C        , // 0x1C4 //  if( word_�������   == const ) goto label
    BEQ_LS_C        , // 0x1C5 //  if( lword_�������  == const ) goto label
    BEQ_DS_C        , // 0x1C6 //  if( double_������� == const ) goto label
    BEQ_BAr         , // 0x1C7 //  if( byte   ==  �������� ������� ) goto label
    BEQ_WAr         , // 0x1C8 //  if( word   ==  �������� ������� ) goto label
    BEQ_LAr         , // 0x1C9 //  if( lword  ==  �������� ������� ) goto label
    BEQ_DAr         , // 0x1CA //  if( double ==  �������� ������� ) goto label
    BEQ_ArB         , // 0x1CB //  if( byte_�������� �������   ==  �������� ������� ) goto label
    BEQ_ArW         , // 0x1CC //  if( word_�������� �������   ==  �������� ������� ) goto label
    BEQ_ArL         , // 0x1CD //  if( lword_�������� �������  ==  �������� ������� ) goto label
    BEQ_ArD         , // 0x1CE //  if( double_�������� ������� ==  �������� ������� ) goto label
    BEQ_BAr_C       , // 0x1CF //  if( const_byte      ==  �������� ������� ) goto label
    BEQ_WAr_C       , // 0x1D0 //  if( const_word      ==  �������� ������� ) goto label
    BEQ_LAr_C       , // 0x1D1 //  if( const_lword     ==  �������� ������� ) goto label
    BEQ_DAr_C       , // 0x1D2 //  if( const_double    ==  �������� ������� ) goto label
    BEQ_BAr_Ba      , // 0x1D3 //  if( byte_�������    ==  �������� ������� ) goto label
    BEQ_WAr_Ba      , // 0x1D4 //  if( word_�������    ==  �������� ������� ) goto label
    BEQ_LAr_Ba      , // 0x1D5 //  if( lword_�������   ==  �������� ������� ) goto label
    BEQ_DAr_Ba      , // 0x1D6 //  if( double_�������  ==  �������� ������� ) goto label
    BEQ_BAr_S       , // 0x1D7 //  if( byte_�������    ==  �������� ������� ) goto label
    BEQ_WAr_S       , // 0x1D8 //  if( word_�������    ==  �������� ������� ) goto label
    BEQ_LAr_S       , // 0x1D9 //  if( lword_�������   ==  �������� ������� ) goto label
    BEQ_DAr_S       , // 0x1DA //  if( double_�������  ==  �������� ������� ) goto label
    rezerv          , // 0x1DB //
    rezerv          , // 0x1DC //
    rezerv          , // 0x1DD //
    rezerv          , // 0x1DE //
    rezerv          , // 0x1DF //
    rezerv          , // 0x1E0 //
    rezerv          , // 0x1E1 //
    rezerv          , // 0x1E2 //
    rezerv          , // 0x1E3 //
    rezerv          , // 0x1E4 //
    rezerv          , // 0x1E5 //
    rezerv          , // 0x1E6 //
    rezerv          , // 0x1E7 //
    rezerv          , // 0x1E8 //
    rezerv          , // 0x1E9 //
    rezerv          , // 0x1EA //
    BNE_BB          , // 0x1EB //  if( byte != byte ) goto label
    BNE_WW          , // 0x1EC //  if( word != word ) goto label
    BNE_LL          , // 0x1ED //  if( lword != lword ) goto label
    BNE_DD          , // 0x1EE //  if( double != double ) goto label
    BNE_BC          , // 0x1EF //  if( byte != const ) goto label
    BNE_WC          , // 0x1F0 //  if( word != const ) goto label
    BNE_LC          , // 0x1F1 //  if( lword != const ) goto label
    BNE_DC          , // 0x1F2 //  if( double != const ) goto label
    BNE_BS          , // 0x1F3 //  if( byte != byte_������� ) goto label
    BNE_WS          , // 0x1F4 //  if( word != word_������� ) goto label
    BNE_LS          , // 0x1F5 //  if( lword != lword_������� ) goto label
    BNE_DS          , // 0x1F6 //  if( double != double_������� ) goto label
    BNE_BBa         , // 0x1F7 //  if( byte != byte_������� ) goto label
    BNE_WBa         , // 0x1F8 //  if( word != word_������� ) goto label
    BNE_LBa         , // 0x1F9 //  if( lword != lword_������� ) goto label
    BNE_DBa         , // 0x1FA //  if( double != double_������� ) goto label
    BNE_BaB         , // 0x1FB //  if( ������� != ������� ) goto label
    BNE_BaW         , // 0x1FC //  if( ������� != ������� ) goto label
    BNE_BaL         , // 0x1FD //  if( ������� != ������� ) goto label
    BNE_BaD         , // 0x1FE //  if( ������� != ������� ) goto label
    BNE_BaB_C       , // 0x1FF //  if( ������� != const ) goto label
    BNE_BaW_C       , // 0x200 //  if( ������� != const ) goto label
    BNE_BaL_C       , // 0x201 //  if( ������� != const ) goto label
    BNE_BaD_C       , // 0x202 //  if( ������� != const ) goto label
    BNE_BaB_S       , // 0x203 //  if( ������� != byte_������� ) goto label
    BNE_BaW_S       , // 0x204 //  if( ������� != word_������� ) goto label
    BNE_BaL_S       , // 0x205 //  if( ������� != lword_�������) goto label
    BNE_BaD_S       , // 0x206 //  if( ������� != double_�������) goto label
    BNE_BS_S        , // 0x207 //  if( byte_�������   != byte_������� ) goto label
    BNE_WS_S        , // 0x208 //  if( word_�������   != word_������� ) goto label
    BNE_LS_S        , // 0x209 //  if( lword_�������  != lword_������� ) goto label
    BNE_DS_S        , // 0x20A //  if( double_������� != double_������� ) goto label
    BNE_BS_C        , // 0x20B //  if( byte_�������   != const ) goto label
    BNE_WS_C        , // 0x20C //  if( word_�������   != const ) goto label
    BNE_LS_C        , // 0x20D //  if( lword_�������  != const ) goto label
    BNE_DS_C        , // 0x20E //  if( double_������� != const ) goto label
    BNE_BAr         , // 0x20F //  if( byte   !=  �������� ������� ) goto label
    BNE_WAr         , // 0x210 //  if( word   !=  �������� ������� ) goto label
    BNE_LAr         , // 0x211 //  if( lword  !=  �������� ������� ) goto label
    BNE_DAr         , // 0x212 //  if( double !=  �������� ������� ) goto label
    BNE_ArB         , // 0x213 //  if( byte_�������� �������   !=  �������� ������� ) goto label
    BNE_ArW         , // 0x214 //  if( word_�������� �������   !=  �������� ������� ) goto label
    BNE_ArL         , // 0x215 //  if( lword_�������� �������  !=  �������� ������� ) goto label
    BNE_ArD         , // 0x216 //  if( double_�������� ������� !=  �������� ������� ) goto label
    BNE_BAr_C       , // 0x217 //  if( const_byte      !=  �������� ������� ) goto label
    BNE_WAr_C       , // 0x218 //  if( const_word      !=  �������� ������� ) goto label
    BNE_LAr_C       , // 0x219 //  if( const_lword     !=  �������� ������� ) goto label
    BNE_DAr_C       , // 0x21A //  if( const_double    !=  �������� ������� ) goto label
    BNE_BAr_Ba      , // 0x21B //  if( byte_�������    !=  �������� ������� ) goto label
    BNE_WAr_Ba      , // 0x21C //  if( word_�������    !=  �������� ������� ) goto label
    BNE_LAr_Ba      , // 0x21D //  if( lword_�������   !=  �������� ������� ) goto label
    BNE_DAr_Ba      , // 0x21E //  if( double_�������  !=  �������� ������� ) goto label
    BNE_BAr_S       , // 0x21F //  if( byte_�������    !=  �������� ������� ) goto label
    BNE_WAr_S       , // 0x220 //  if( word_�������    !=  �������� ������� ) goto label
    BNE_LAr_S       , // 0x221 //  if( lword_�������   !=  �������� ������� ) goto label
    BNE_DAr_S       , // 0x222 //  if( double_�������  !=  �������� ������� ) goto label
    rezerv          , // 0x223 //
    rezerv          , // 0x224 //
    rezerv          , // 0x225 //
    rezerv          , // 0x226 //
    rezerv          , // 0x227 //
    rezerv          , // 0x228 //
    rezerv          , // 0x229 //
    rezerv          , // 0x22A //
    rezerv          , // 0x22B //
    rezerv          , // 0x22C //
    rezerv          , // 0x22D //
    rezerv          , // 0x22E //
    rezerv          , // 0x22F //
    rezerv          , // 0x230 //
    rezerv          , // 0x231 //
    rezerv          , // 0x232 //
    BGT_BB          , // 0x233 //  if( (sb)byte > (sb)byte ) goto label
    BGT_WW          , // 0x234 //  if( (sw)word > (sw)word ) goto label
    BGT_LL          , // 0x235 //  if( (slw)lword > (slw)lword ) goto label
    BGT_DD          , // 0x236 //  if( double > double ) goto label
    BGT_BC          , // 0x237 //  if( (sb)byte > const ) goto label
    BGT_WC          , // 0x238 //  if( (sw)word > const ) goto label
    BGT_LC          , // 0x239 //  if( (slw)lword > const ) goto label
    BGT_DC          , // 0x23A //  if( double > const ) goto label
    BGT_BS          , // 0x23B //  if( (sb)byte > (sb)byte_������� ) goto label
    BGT_WS          , // 0x23C //  if( (sw)word > (sw)word_������� ) goto label
    BGT_LS          , // 0x23D //  if( (slw)lword > (slw)lword_������� ) goto label
    BGT_DS          , // 0x23E //  if( double > double_������� ) goto label
    BGT_BBa         , // 0x23F //  if( (sb)byte   > (sb)byte_������� ) goto label
    BGT_WBa         , // 0x240 //  if( (sw)word   > (sw)word_������� ) goto label
    BGT_LBa         , // 0x241 //  if( (slw)lword > (slw)lword_������� ) goto label
    BGT_DBa         , // 0x242 //  if( double     > double_������� ) goto label
    BGT_BaB         , // 0x243 //  if( ������� > ������� ) goto label
    BGT_BaW         , // 0x244 //  if( ������� > ������� ) goto label
    BGT_BaL         , // 0x245 //  if( ������� > ������� ) goto label
    BGT_BaD         , // 0x246 //  if( ������� > ������� ) goto label
    BGT_BaB_C       , // 0x247 //  if( ������� > const ) goto label
    BGT_BaW_C       , // 0x248 //  if( ������� > const ) goto label
    BGT_BaL_C       , // 0x249 //  if( ������� > const ) goto label
    BGT_BaD_C       , // 0x24A //  if( ������� > const ) goto label
    BGT_BaB_S       , // 0x24B //  if( ������� > byte_�������   ) goto label
    BGT_BaW_S       , // 0x24C //  if( ������� > word_�������   ) goto label
    BGT_BaL_S       , // 0x24D //  if( ������� > lword_�������  ) goto label
    BGT_BaD_S       , // 0x24E //  if( ������� > double_������� ) goto label
    BGT_BS_S        , // 0x24F //  if( byte_�������   > byte_������� ) goto label
    BGT_WS_S        , // 0x250 //  if( word_�������   > word_������� ) goto label
    BGT_LS_S        , // 0x251 //  if( lword_�������  > lword_������� ) goto label
    BGT_DS_S        , // 0x252 //  if( double_������� > double_������� ) goto label
    BGT_BS_C        , // 0x253 //  if( byte_�������   > const ) goto label
    BGT_WS_C        , // 0x254 //  if( word_�������   > const ) goto label
    BGT_LS_C        , // 0x255 //  if( lword_�������  > const ) goto label
    BGT_DS_C        , // 0x256 //  if( double_������� > const ) goto label
    BGT_BAr         , // 0x257 //  if( byte   > �������� ������� ) goto label
    BGT_WAr         , // 0x258 //  if( word   > �������� ������� ) goto label
    BGT_LAr         , // 0x259 //  if( lword  > �������� ������� ) goto label
    BGT_DAr         , // 0x25A //  if( double > �������� ������� ) goto label
    BGT_ArB         , // 0x25B //  if( byte_�������� �������   > �������� ������� ) goto label
    BGT_ArW         , // 0x25C //  if( word_�������� �������   > �������� ������� ) goto label
    BGT_ArL         , // 0x25D //  if( lword_�������� �������  > �������� ������� ) goto label
    BGT_ArD         , // 0x25E //  if( double_�������� ������� > �������� ������� ) goto label
    BGT_BAr_C       , // 0x25F //  if( const_byte      >  �������� ������� ) goto label
    BGT_WAr_C       , // 0x260 //  if( const_word      >  �������� ������� ) goto label
    BGT_LAr_C       , // 0x261 //  if( const_lword     >  �������� ������� ) goto label
    BGT_DAr_C       , // 0x262 //  if( const_double    >  �������� ������� ) goto label
    BGT_BAr_Ba      , // 0x263 //  if( byte_�������    >  �������� ������� ) goto label
    BGT_WAr_Ba      , // 0x264 //  if( word_�������    >  �������� ������� ) goto label
    BGT_LAr_Ba      , // 0x265 //  if( lword_�������   >  �������� ������� ) goto label
    BGT_DAr_Ba      , // 0x266 //  if( double_�������  >  �������� ������� ) goto label
    BGT_BAr_S       , // 0x267 //  if( byte_�������    >  �������� ������� ) goto label
    BGT_WAr_S       , // 0x268 //  if( word_�������    >  �������� ������� ) goto label
    BGT_LAr_S       , // 0x269 //  if( lword_�������   >  �������� ������� ) goto label
    BGT_DAr_S       , // 0x26A //  if( double_�������  >  �������� ������� ) goto label
    rezerv          , // 0x26B //
    rezerv          , // 0x26C //
    rezerv          , // 0x26D //
    rezerv          , // 0x26E //
    rezerv          , // 0x26F //
    rezerv          , // 0x270 //
    rezerv          , // 0x271 //
    rezerv          , // 0x272 //
    rezerv          , // 0x273 //
    rezerv          , // 0x274 //
    rezerv          , // 0x275 //
    rezerv          , // 0x276 //
    rezerv          , // 0x277 //
    rezerv          , // 0x278 //
    rezerv          , // 0x279 //
    rezerv          , // 0x27A //
    BGTU_BB         , // 0x27B //  if( byte  > byte ) goto label
    BGTU_WW         , // 0x27C //  if( word  > word ) goto label
    BGTU_LL         , // 0x27D //  if( lword > lword ) goto label
    BGTU_BC         , // 0x27E //  if( byte  > const ) goto label
    BGTU_WC         , // 0x27F //  if( word  > const ) goto label
    BGTU_LC         , // 0x280 //  if( lword > const ) goto label
    BGTU_BS         , // 0x281 //  if( byte  > byte_������� ) goto label
    BGTU_WS         , // 0x282 //  if( word  > word_������� ) goto label
    BGTU_LS         , // 0x283 //  if( lword > lword_������� ) goto label
    BGTU_BBa        , // 0x284 //  if( byte > byte_������� ) goto label
    BGTU_WBa        , // 0x285 //  if( word > word_������� ) goto label
    BGTU_LBa        , // 0x286 //  if( lword > lword_������� ) goto label
    BGTU_BaB        , // 0x287 //  if( ������� > ������� ) goto label
    BGTU_BaW        , // 0x288 //  if( ������� > ������� ) goto label
    BGTU_BaL        , // 0x289 //  if( ������� > ������� ) goto label
    BGTU_BaB_C      , // 0x28A //  if( ������� > const ) goto label
    BGTU_BaW_C      , // 0x28B //  if( ������� > const ) goto label
    BGTU_BaL_C      , // 0x28C //  if( ������� > const ) goto label
    BGTU_BaB_S      , // 0x28D //  if( ������� > byte_�������  ) goto label
    BGTU_BaW_S      , // 0x28E //  if( ������� > word_�������  ) goto label
    BGTU_BaL_S      , // 0x28F //  if( ������� > lword_������� ) goto label
    BGTU_BS_S       , // 0x290 //  if( byte_�������   > byte_������� ) goto label
    BGTU_WS_S       , // 0x291 //  if( word_�������   > word_������� ) goto label
    BGTU_LS_S       , // 0x292 //  if( lword_�������  > lword_������� ) goto label
    BGTU_BS_C       , // 0x293 //  if( byte_�������   > const ) goto label
    BGTU_WS_C       , // 0x294 //  if( word_�������   > const ) goto label
    BGTU_LS_C       , // 0x295 //  if( lword_�������  > const ) goto label
    BGTU_BAr        , // 0x296 //  if( byte                    > �������� ������� ) goto label
    BGTU_WAr        , // 0x297 //  if( word                    > �������� ������� ) goto label
    BGTU_LAr        , // 0x298 //  if( lword                   > �������� ������� ) goto label
    BGTU_ArB        , // 0x299 //  if( byte_�������� �������   > �������� ������� ) goto label
    BGTU_ArW        , // 0x29A //  if( word_�������� �������   > �������� ������� ) goto label
    BGTU_ArL        , // 0x29B //  if( lword_�������� �������  > �������� ������� ) goto label
    BGTU_BAr_C      , // 0x29C //  if( const_byte      >  �������� ������� ) goto label
    BGTU_WAr_C      , // 0x29D //  if( const_word      >  �������� ������� ) goto label
    BGTU_LAr_C      , // 0x29E //  if( const_lword     >  �������� ������� ) goto label
    BGTU_BAr_Ba     , // 0x29F //  if( byte_�������    >  �������� ������� ) goto label
    BGTU_WAr_Ba     , // 0x2A0 //  if( word_�������    >  �������� ������� ) goto label
    BGTU_LAr_Ba     , // 0x2A1 //  if( lword_�������   >  �������� ������� ) goto label
    BGTU_BAr_S      , // 0x2A2 //  if( byte_�������    >  �������� ������� ) goto label
    BGTU_WAr_S      , // 0x2A3 //  if( word_�������    >  �������� ������� ) goto label
    BGTU_LAr_S      , // 0x2A4 //  if( lword_�������   >  �������� ������� ) goto label
    rezerv          , // 0x2A5 //
    rezerv          , // 0x2A6 //
    rezerv          , // 0x2A7 //
    rezerv          , // 0x2A8 //
    rezerv          , // 0x2A9 //
    rezerv          , // 0x2AA //
    rezerv          , // 0x2AB //
    rezerv          , // 0x2AC //
    rezerv          , // 0x2AD //
    rezerv          , // 0x2AE //
    rezerv          , // 0x2AF //
    rezerv          , // 0x2B0 //
    rezerv          , // 0x2B1 //
    rezerv          , // 0x2B2 //
    rezerv          , // 0x2B3 //
    rezerv          , // 0x2B4 //
    BLT_BB          , // 0x2B5 //  if( (sb)byte   < (sb)byte ) goto label
    BLT_WW          , // 0x2B6 //  if( (sw)word   < (sw)word ) goto label
    BLT_LL          , // 0x2B7 //  if( (slw)lword < (slw)lword ) goto label
    BLT_DD          , // 0x2B8 //  if( double     < double ) goto label
    BLT_BC          , // 0x2B9 //  if( (sb)byte   < const ) goto label
    BLT_WC          , // 0x2BA //  if( (sw)word   < const ) goto label
    BLT_LC          , // 0x2BB //  if( (slw)lword < const ) goto label
    BLT_DC          , // 0x2BC //  if( double     < const ) goto label
    BLT_BS          , // 0x2BD //  if( (sb)byte < (sb)byte_������� ) goto label
    BLT_WS          , // 0x2BE //  if( (sw)word < (sw)word_������� ) goto label
    BLT_LS          , // 0x2BF //  if( (slw)lword < (slw)lword_������� ) goto label
    BLT_DS          , // 0x2C0 //  if( double < double_������� ) goto label
    BLT_BBa         , // 0x2C1 //  if( (sb)byte < (sb)byte_������� ) goto label
    BLT_WBa         , // 0x2C2 //  if( (sw)word < (sw)word_������� ) goto label
    BLT_LBa         , // 0x2C3 //  if( (slw)lword < (slw)lword_������� ) goto label
    BLT_DBa         , // 0x2C4 //  if( double < double_������� ) goto label
    BLT_BaB         , // 0x2C5 //  if( ������� < ������� ) goto label
    BLT_BaW         , // 0x2C6 //  if( ������� < ������� ) goto label
    BLT_BaL         , // 0x2C7 //  if( ������� < ������� ) goto label
    BLT_BaD         , // 0x2C8 //  if( ������� < ������� ) goto label
    BLT_BaB_C       , // 0x2C9 //  if( ������� < const ) goto label
    BLT_BaW_C       , // 0x2CA //  if( ������� < const ) goto label
    BLT_BaL_C       , // 0x2CB //  if( ������� < const ) goto label
    BLT_BaD_C       , // 0x2CC //  if( ������� < const ) goto label
    BLT_BaB_S       , // 0x2CD //  if( ������� < byte_�������  ) goto label
    BLT_BaW_S       , // 0x2CE //  if( ������� < word_�������  ) goto label
    BLT_BaL_S       , // 0x2CF //  if( ������� < lword_������� ) goto label
    BLT_BaD_S       , // 0x2D0 //  if( ������� < double_�������) goto label
    BLT_BS_S        , // 0x2D1 //  if( byte_�������   < byte_������� ) goto label
    BLT_WS_S        , // 0x2D2 //  if( word_�������   < word_������� ) goto label
    BLT_LS_S        , // 0x2D3 //  if( lword_�������  < lword_������� ) goto label
    BLT_DS_S        , // 0x2D4 //  if( double_������� < double_������� ) goto label
    BLT_BS_C        , // 0x2D5 //  if( byte_�������   < const ) goto label
    BLT_WS_C        , // 0x2D6 //  if( word_�������   < const ) goto label
    BLT_LS_C        , // 0x2D7 //  if( lword_�������  < const ) goto label
    BLT_DS_C        , // 0x2D8 //  if( double_������� < const ) goto label
    BLT_BAr         , // 0x2D9 //  if( byte                    <  �������� ������� ) goto label
    BLT_WAr         , // 0x2DA //  if( word                    <  �������� ������� ) goto label
    BLT_LAr         , // 0x2DB //  if( lword                   <  �������� ������� ) goto label
    BLT_DAr         , // 0x2DC //  if( double                  <  �������� ������� ) goto label
    BLT_ArB         , // 0x2DD //  if( byte_�������� �������   <  �������� ������� ) goto label
    BLT_ArW         , // 0x2DE //  if( word_�������� �������   <  �������� ������� ) goto label
    BLT_ArL         , // 0x2DF //  if( lword_�������� �������  <  �������� ������� ) goto label
    BLT_ArD         , // 0x2E0 //  if( double_�������� ������� <  �������� ������� ) goto label
    BLT_BAr_C       , // 0x2E1 //  if( const_byte      <  �������� ������� ) goto label
    BLT_WAr_C       , // 0x2E2 //  if( const_word      <  �������� ������� ) goto label
    BLT_LAr_C       , // 0x2E3 //  if( const_lword     <  �������� ������� ) goto label
    BLT_DAr_C       , // 0x2E4 //  if( const_double    <  �������� ������� ) goto label
    BLT_BAr_Ba      , // 0x2E5 //  if( byte_�������    <  �������� ������� ) goto label
    BLT_WAr_Ba      , // 0x2E6 //  if( word_�������    <  �������� ������� ) goto label
    BLT_LAr_Ba      , // 0x2E7 //  if( lword_�������   <  �������� ������� ) goto label
    BLT_DAr_Ba      , // 0x2E8 //  if( double_�������  <  �������� ������� ) goto label
    BLT_BAr_S       , // 0x2E9 //  if( byte_�������    <  �������� ������� ) goto label
    BLT_WAr_S       , // 0x2EA //  if( word_�������    <  �������� ������� ) goto label
    BLT_LAr_S       , // 0x2EB //  if( lword_�������   <  �������� ������� ) goto label
    BLT_DAr_S       , // 0x2EC //  if( double_�������  <  �������� ������� ) goto label
    rezerv          , // 0x2ED //
    rezerv          , // 0x2EE //
    rezerv          , // 0x2EF //
    rezerv          , // 0x2F0 //
    rezerv          , // 0x2F1 //
    rezerv          , // 0x2F2 //
    rezerv          , // 0x2F3 //
    rezerv          , // 0x2F4 //
    rezerv          , // 0x2F5 //
    rezerv          , // 0x2F6 //
    rezerv          , // 0x2F7 //
    rezerv          , // 0x2F8 //
    rezerv          , // 0x2F9 //
    rezerv          , // 0x2FA //
    rezerv          , // 0x2FB //
    rezerv          , // 0x2FC //
    BLTU_BB         , // 0x2FD //  if( byte < byte ) goto label
    BLTU_WW         , // 0x2FE //  if( word < word ) goto label
    BLTU_LL         , // 0x2FF //  if( lword < lword ) goto label
    BLTU_BC         , // 0x300 //  if( byte < const ) goto label
    BLTU_WC         , // 0x301 //  if( word < const ) goto label
    BLTU_LC         , // 0x302 //  if( lword < const ) goto label
    BLTU_BS         , // 0x303 //  if( byte < byte_������� ) goto label
    BLTU_WS         , // 0x304 //  if( word < word_������� ) goto label
    BLTU_LS         , // 0x305 //  if( lword < lword_������� ) goto label
    BLTU_BBa        , // 0x306 //  if( byte  < byte_������� ) goto label
    BLTU_WBa        , // 0x307 //  if( word  < word_������� ) goto label
    BLTU_LBa        , // 0x308 //  if( lword < lword_������� ) goto label
    BLTU_BaB        , // 0x309 //  if( ������� < ������� ) goto label
    BLTU_BaW        , // 0x30A //  if( ������� < ������� ) goto label
    BLTU_BaL        , // 0x30B //  if( ������� < ������� ) goto label
    BLTU_BaB_C      , // 0x30C //  if( ������� < const ) goto label
    BLTU_BaW_C      , // 0x30D //  if( ������� < const ) goto label
    BLTU_BaL_C      , // 0x30E //  if( ������� < const ) goto label
    BLTU_BaB_S      , // 0x30F //  if( ������� < byte_������� ) goto label
    BLTU_BaW_S      , // 0x310 //  if( ������� < word_������� ) goto label
    BLTU_BaL_S      , // 0x311 //  if( ������� < lword_������� ) goto label
    BLTU_BS_S       , // 0x312 //  if( byte_�������  < byte_������� ) goto label
    BLTU_WS_S       , // 0x313 //  if( word_�������  < word_������� ) goto label
    BLTU_LS_S       , // 0x314 //  if( lword_������� < lword_������� ) goto label
    BLTU_BS_C       , // 0x315 //  if( byte_�������  < const ) goto label
    BLTU_WS_C       , // 0x316 //  if( word_�������  < const ) goto label
    BLTU_LS_C       , // 0x317 //  if( lword_������� < const ) goto label
    BLTU_BAr        , // 0x318 //  if( byte                    < �������� ������� ) goto label
    BLTU_WAr        , // 0x319 //  if( word                    < �������� ������� ) goto label
    BLTU_LAr        , // 0x31A //  if( lword                   < �������� ������� ) goto label
    BLTU_ArB        , // 0x31B //  if( byte_�������� �������   < �������� ������� ) goto label
    BLTU_ArW        , // 0x31C //  if( word_�������� �������   < �������� ������� ) goto label
    BLTU_ArL        , // 0x31D //  if( lword_�������� �������  < �������� ������� ) goto label
    BLTU_BAr_C      , // 0x31E //  if( const_byte      <  �������� ������� ) goto label
    BLTU_WAr_C      , // 0x31F //  if( const_word      <  �������� ������� ) goto label
    BLTU_LAr_C      , // 0x320 //  if( const_lword     <  �������� ������� ) goto label
    BLTU_BAr_Ba     , // 0x321 //  if( byte_�������    <  �������� ������� ) goto label
    BLTU_WAr_Ba     , // 0x322 //  if( word_�������    <  �������� ������� ) goto label
    BLTU_LAr_Ba     , // 0x323 //  if( lword_�������   <  �������� ������� ) goto label
    BLTU_BAr_S      , // 0x324 //  if( byte_�������    <  �������� ������� ) goto label
    BLTU_WAr_S      , // 0x325 //  if( word_�������    <  �������� ������� ) goto label
    BLTU_LAr_S      , // 0x326 //  if( lword_�������   <  �������� ������� ) goto label
    rezerv          , // 0x327 //
    rezerv          , // 0x328 //
    rezerv          , // 0x329 //
    rezerv          , // 0x32A //
    rezerv          , // 0x32B //
    rezerv          , // 0x32C //
    rezerv          , // 0x32D //
    rezerv          , // 0x32E //
    rezerv          , // 0x32F //
    rezerv          , // 0x330 //
    rezerv          , // 0x331 //
    rezerv          , // 0x332 //
    rezerv          , // 0x333 //
    rezerv          , // 0x334 //
    rezerv          , // 0x335 //
    rezerv          , // 0x336 //
    BGE_BB          , // 0x337 //  if( (sb)byte >= (sb)byte ) goto label
    BGE_WW          , // 0x338 //  if( (sw)word >= (sw)word ) goto label
    BGE_LL          , // 0x339 //  if( (slw)lword >= (slw)lword ) goto label
    BGE_DD          , // 0x33A //  if( double >= double ) goto label
    BGE_BC          , // 0x33B //  if( (sb)byte >= const ) goto label
    BGE_WC          , // 0x33C //  if( (sw)word >= const ) goto label
    BGE_LC          , // 0x33D //  if( (slw)lword >= const ) goto label
    BGE_DC          , // 0x33E //  if( double >= const ) goto label
    BGE_BS          , // 0x33F //  if( (sb)byte >= (sb)byte_������� ) goto label
    BGE_WS          , // 0x340 //  if( (sw)word >= (sw)word_������� ) goto label
    BGE_LS          , // 0x341 //  if( (slw)lword >= (slw)lword_������� ) goto label
    BGE_DS          , // 0x342 //  if( double >= double_������� ) goto label
    BGE_BBa         , // 0x343 //  if( (sb)byte >= (sb)byte_������� ) goto label
    BGE_WBa         , // 0x344 //  if( (sw)word >= (sw)word_������� ) goto label
    BGE_LBa         , // 0x345 //  if( (slw)lword >= (slw)lword_������� ) goto label
    BGE_DBa         , // 0x346 //  if( double >= double_������� ) goto label
    BGE_BaB         , // 0x347 //  if( ������� >= ������� ) goto label
    BGE_BaW         , // 0x348 //  if( ������� >= ������� ) goto label
    BGE_BaL         , // 0x349 //  if( ������� >= ������� ) goto label
    BGE_BaD         , // 0x34A //  if( ������� >= ������� ) goto label
    BGE_BaB_C       , // 0x34B //  if( ������� >= const ) goto label
    BGE_BaW_C       , // 0x34C //  if( ������� >= const ) goto label
    BGE_BaL_C       , // 0x34D //  if( ������� >= const ) goto label
    BGE_BaD_C       , // 0x34E //  if( ������� >= const ) goto label
    BGE_BaB_S       , // 0x34F //  if( ������� >= byte_������� ) goto label
    BGE_BaW_S       , // 0x350 //  if( ������� >= word_������� ) goto label
    BGE_BaL_S       , // 0x351 //  if( ������� >= lword_�������) goto label
    BGE_BaD_S       , // 0x352 //  if( ������� >= double_�������) goto label
    BGE_BS_S        , // 0x353 //  if( byte_�������   >= byte_������� ) goto label
    BGE_WS_S        , // 0x354 //  if( word_�������   >= word_������� ) goto label
    BGE_LS_S        , // 0x355 //  if( lword_�������  >= lword_������� ) goto label
    BGE_DS_S        , // 0x356 //  if( double_������� >= double_������� ) goto label
    BGE_BS_C        , // 0x357 //  if( byte_�������   >= const ) goto label
    BGE_WS_C        , // 0x358 //  if( word_�������   >= const ) goto label
    BGE_LS_C        , // 0x359 //  if( lword_�������  >= const ) goto label
    BGE_DS_C        , // 0x35A //  if( double_������� >= const ) goto label
    BGE_BAr         , // 0x35B //  if( byte                    >=  �������� ������� ) goto label
    BGE_WAr         , // 0x35C //  if( word                    >=  �������� ������� ) goto label
    BGE_LAr         , // 0x35D //  if( lword                   >=  �������� ������� ) goto label
    BGE_DAr         , // 0x35E //  if( double                  >=  �������� ������� ) goto label
    BGE_ArB         , // 0x35F //  if( byte_�������� �������   >=  �������� ������� ) goto label
    BGE_ArW         , // 0x360 //  if( word_�������� �������   >=  �������� ������� ) goto label
    BGE_ArL         , // 0x361 //  if( lword_�������� �������  >=  �������� ������� ) goto label
    BGE_ArD         , // 0x362 //  if( double_�������� ������� >=  �������� ������� ) goto label
    BGE_BAr_C       , // 0x363 //  if( byte_�������� �������   >= const  ) goto label
    BGE_WAr_C       , // 0x364 //  if( word_�������� �������   >= const  ) goto label
    BGE_LAr_C       , // 0x365 //  if( lword_�������� �������  >= const  ) goto label
    BGE_DAr_C       , // 0x366 //  if( double_�������� ������� >= const  ) goto label
    BGE_BAr_Ba      , // 0x367 //  if( byte_�������� �������   >= �������   ) goto label
    BGE_WAr_Ba      , // 0x368 //  if( word_�������� �������   >= �������   ) goto label
    BGE_LAr_Ba      , // 0x369 //  if( lword_�������� �������  >= �������   ) goto label
    BGE_DAr_Ba      , // 0x36A //  if( double_�������� ������� >= �������   ) goto label
    BGE_BAr_S       , // 0x36B //  if( byte_�������� �������   >= �������   ) goto label
    BGE_WAr_S       , // 0x36C //  if( word_�������� �������   >= �������   ) goto label
    BGE_LAr_S       , // 0x36D //  if( lword_�������� �������  >= �������   ) goto label
    BGE_DAr_S       , // 0x36E //  if( double_�������� ������� >= �������   ) goto label
    rezerv          , // 0x36F //
    rezerv          , // 0x370 //
    rezerv          , // 0x371 //
    rezerv          , // 0x372 //
    rezerv          , // 0x373 //
    rezerv          , // 0x374 //
    rezerv          , // 0x375 //
    rezerv          , // 0x376 //
    rezerv          , // 0x377 //
    rezerv          , // 0x378 //
    rezerv          , // 0x379 //
    rezerv          , // 0x37A //
    rezerv          , // 0x37B //
    rezerv          , // 0x37C //
    rezerv          , // 0x37D //
    rezerv          , // 0x37E //
    BGEU_BB         , // 0x37F //  if( byte >= byte ) goto label
    BGEU_WW         , // 0x380 //  if( word >= word ) goto label
    BGEU_LL         , // 0x381 //  if( lword >= lword ) goto label
    BGEU_BC         , // 0x382 //  if( byte >= const ) goto label
    BGEU_WC         , // 0x383 //  if( word >= const ) goto label
    BGEU_LC         , // 0x384 //  if( lword >= const ) goto label
    BGEU_BS         , // 0x385 //  if( byte >= byte_������� ) goto label
    BGEU_WS         , // 0x386 //  if( word  >= word_������� ) goto label
    BGEU_LS         , // 0x387 //  if( lword >= lword_������� ) goto label
    BGEU_BBa        , // 0x388 //  if( byte  >= byte_������� ) goto label
    BGEU_WBa        , // 0x389 //  if( word  >= word_������� ) goto label
    BGEU_LBa        , // 0x38A //  if( lword >= lword_������� ) goto label
    BGEU_BaB        , // 0x38B //  if( ������� >= ������� ) goto label
    BGEU_BaW        , // 0x38C //  if( ������� >= ������� ) goto label
    BGEU_BaL        , // 0x38D //  if( ������� >= ������� ) goto label
    BGEU_BaB_C      , // 0x38E //  if( ������� >= const ) goto label
    BGEU_BaW_C      , // 0x38F //  if( ������� >= const ) goto label
    BGEU_BaL_C      , // 0x390 //  if( ������� >= const ) goto label
    BGEU_BaB_S      , // 0x391 //  if( ������� >= byte_�������  ) goto label
    BGEU_BaW_S      , // 0x392 //  if( ������� >= word_�������  ) goto label
    BGEU_BaL_S      , // 0x393 //  if( ������� >= lword_������� ) goto label
    BGEU_BS_S       , // 0x394 //  if( byte_�������  >= byte_������� ) goto label
    BGEU_WS_S       , // 0x395 //  if( word_�������  >= word_������� ) goto label
    BGEU_LS_S       , // 0x396 //  if( lword_������� >= lword_������� ) goto label
    BGEU_BS_C       , // 0x397 //  if( byte_�������  >= const ) goto label
    BGEU_WS_C       , // 0x398 //  if( word_�������  >= const ) goto label
    BGEU_LS_C       , // 0x399 //  if( lword_������� >= const ) goto label
    BGEU_BAr        , // 0x39A //  if( byte                    >= �������� ������� ) goto label
    BGEU_WAr        , // 0x39B //  if( word                    >= �������� ������� ) goto label
    BGEU_LAr        , // 0x39C //  if( lword                   >= �������� ������� ) goto label
    BGEU_ArB        , // 0x39D //  if( byte_�������� �������   >= �������� ������� ) goto label
    BGEU_ArW        , // 0x39E //  if( word_�������� �������   >= �������� ������� ) goto label
    BGEU_ArL        , // 0x39F //  if( lword_�������� �������  >= �������� ������� ) goto label
    BGEU_BAr_C      , // 0x3A0 //  if( byte_�������� �������   >= const  ) goto label
    BGEU_WAr_C      , // 0x3A1 //  if( word_�������� �������   >= const  ) goto label
    BGEU_LAr_C      , // 0x3A2 //  if( lword_�������� �������  >= const  ) goto label
    BGEU_BAr_Ba     , // 0x3A3 //  if( byte_�������� �������   >= �������   ) goto label
    BGEU_WAr_Ba     , // 0x3A4 //  if( word_�������� �������   >= �������   ) goto label
    BGEU_LAr_Ba     , // 0x3A5 //  if( lword_�������� �������  >= �������   ) goto label
    BGEU_BAr_S      , // 0x3A6 //  if( byte_�������� �������   >= �������   ) goto label
    BGEU_WAr_S      , // 0x3A7 //  if( word_�������� �������   >= �������   ) goto label
    BGEU_LAr_S      , // 0x3A8 //  if( lword_�������� �������  >= �������   ) goto label
    rezerv          , // 0x3A9 //
    rezerv          , // 0x3AA //
    rezerv          , // 0x3AB //
    rezerv          , // 0x3AC //
    rezerv          , // 0x3AD //
    rezerv          , // 0x3AE //
    rezerv          , // 0x3AF //
    rezerv          , // 0x3B0 //
    rezerv          , // 0x3B1 //
    rezerv          , // 0x3B2 //
    rezerv          , // 0x3B3 //
    rezerv          , // 0x3B4 //
    rezerv          , // 0x3B5 //
    rezerv          , // 0x3B6 //
    rezerv          , // 0x3B7 //
    rezerv          , // 0x3B8 //
    BLE_BB          , // 0x3B9 //  if( (sb)byte <= (sb)byte ) goto label
    BLE_WW          , // 0x3BA //  if( (sw)word <= (sw)word ) goto label
    BLE_LL          , // 0x3BB //  if( (slw)lword <= (slw)lword ) goto label
    BLE_DD          , // 0x3BC //  if( double     <= double ) goto label
    BLE_BC          , // 0x3BD //  if( (sb)byte   <= const ) goto label
    BLE_WC          , // 0x3BE //  if( (sw)word   <= const ) goto label
    BLE_LC          , // 0x3BF //  if( (slw)lword <= const ) goto label
    BLE_DC          , // 0x3C0 //  if( double     <= const ) goto label
    BLE_BS          , // 0x3C1 //  if( (sb)byte   <= (sb)byte_������� ) goto label
    BLE_WS          , // 0x3C2 //  if( (sw)word   <= (sw)word_������� ) goto label
    BLE_LS          , // 0x3C3 //  if( (slw)lword <= (slw)lword_������� ) goto label
    BLE_DS          , // 0x3C4 //  if( double     <= double_������� ) goto label
    BLE_BBa         , // 0x3C5 //  if( (sb)byte   <= (sb)byte_������� ) goto label
    BLE_WBa         , // 0x3C6 //  if( (sw)word   <= (sw)word_������� ) goto label
    BLE_LBa         , // 0x3C7 //  if( (slw)lword <= (slw)lword_������� ) goto label
    BLE_DBa         , // 0x3C8 //  if( double     <= double_������� ) goto label
    BLE_BaB         , // 0x3C9 //  if( ������� <= ������� ) goto label
    BLE_BaW         , // 0x3CA //  if( ������� <= ������� ) goto label
    BLE_BaL         , // 0x3CB //  if( ������� <= ������� ) goto label
    BLE_BaD         , // 0x3CC //  if( ������� <= ������� ) goto label
    BLE_BaB_C       , // 0x3CD //  if( ������� <= const ) goto label
    BLE_BaW_C       , // 0x3CE //  if( ������� <= const ) goto label
    BLE_BaL_C       , // 0x3CF //  if( ������� <= const ) goto label
    BLE_BaD_C       , // 0x3D0 //  if( ������� <= const ) goto label
    BLE_BaB_S       , // 0x3D1 //  if( ������� <= byte_�������   ) goto label
    BLE_BaW_S       , // 0x3D2 //  if( ������� <= word_�������   ) goto label
    BLE_BaL_S       , // 0x3D3 //  if( ������� <= lword_�������  ) goto label
    BLE_BaD_S       , // 0x3D4 //  if( ������� <= double_������� ) goto label
    BLE_BS_S        , // 0x3D5 //  if( byte_�������   <= byte_������� ) goto label
    BLE_WS_S        , // 0x3D6 //  if( word_�������   <= word_������� ) goto label
    BLE_LS_S        , // 0x3D7 //  if( lword_�������  <= lword_������� ) goto label
    BLE_DS_S        , // 0x3D8 //  if( double_������� <= double_������� ) goto label
    BLE_BS_C        , // 0x3D9 //  if( byte_�������   <= const ) goto label
    BLE_WS_C        , // 0x3DA //  if( word_�������   <= const ) goto label
    BLE_LS_C        , // 0x3DB //  if( lword_�������  <= const ) goto label
    BLE_DS_C        , // 0x3DC //  if( double_������� <= const ) goto label
    BLE_BAr         , // 0x3DD //  if( byte                    <=  �������� ������� ) goto label
    BLE_WAr         , // 0x3DE //  if( word                    <=  �������� ������� ) goto label
    BLE_LAr         , // 0x3DF //  if( lword                   <=  �������� ������� ) goto label
    BLE_DAr         , // 0x3E0 //  if( double                  <=  �������� ������� ) goto label
    BLE_ArB         , // 0x3E1 //  if( byte_�������� �������   <=  �������� ������� ) goto label
    BLE_ArW         , // 0x3E2 //  if( word_�������� �������   <=  �������� ������� ) goto label
    BLE_ArL         , // 0x3E3 //  if( lword_�������� �������  <=  �������� ������� ) goto label
    BLE_ArD         , // 0x3E4 //  if( double_�������� ������� <=  �������� ������� ) goto label
    BLE_BAr_C       , // 0x3E5 //  if( const_byte      <=  �������� ������� ) goto label
    BLE_WAr_C       , // 0x3E6 //  if( const_word      <=  �������� ������� ) goto label
    BLE_LAr_C       , // 0x3E7 //  if( const_lword     <=  �������� ������� ) goto label
    BLE_DAr_C       , // 0x3E8 //  if( const_double    <=  �������� ������� ) goto label
    BLE_BAr_Ba      , // 0x3E9 //  if( byte_�������    <=  �������� ������� ) goto label
    BLE_WAr_Ba      , // 0x3EA //  if( word_�������    <=  �������� ������� ) goto label
    BLE_LAr_Ba      , // 0x3EB //  if( lword_�������   <=  �������� ������� ) goto label
    BLE_DAr_Ba      , // 0x3EC //  if( double_�������  <=  �������� ������� ) goto label
    BLE_BAr_S       , // 0x3ED //  if( byte_�������    <=  �������� ������� ) goto label
    BLE_WAr_S       , // 0x3EE //  if( word_�������    <=  �������� ������� ) goto label
    BLE_LAr_S       , // 0x3EF //  if( lword_�������   <=  �������� ������� ) goto label
    BLE_DAr_S       , // 0x3F0 //  if( double_�������  <=  �������� ������� ) goto label
    rezerv          , // 0x3F1 //
    rezerv          , // 0x3F2 //
    rezerv          , // 0x3F3 //
    rezerv          , // 0x3F4 //
    rezerv          , // 0x3F5 //
    rezerv          , // 0x3F6 //
    rezerv          , // 0x3F7 //
    rezerv          , // 0x3F8 //
    rezerv          , // 0x3F9 //
    rezerv          , // 0x3FA //
    rezerv          , // 0x3FB //
    rezerv          , // 0x3FC //
    rezerv          , // 0x3FD //
    rezerv          , // 0x3FE //
    rezerv          , // 0x3FF //
    rezerv          , // 0x400 //
    BLEU_BB         , // 0x401 //  if( byte <= byte ) goto label
    BLEU_WW         , // 0x402 //  if( word <= word ) goto label
    BLEU_LL         , // 0x403 //  if( lword <= lword ) goto label
    BLEU_BC         , // 0x404 //  if( byte <= const ) goto label
    BLEU_WC         , // 0x405 //  if( word <= const ) goto label
    BLEU_LC         , // 0x406 //  if( lword <= const ) goto label
    BLEU_BS         , // 0x407 //  if( byte  <= byte_������� ) goto label
    BLEU_WS         , // 0x408 //  if( word  <= word_������� ) goto label
    BLEU_LS         , // 0x409 //  if( lword <= lword_������� ) goto label
    BLEU_BBa        , // 0x40A //  if( byte  <= byte_������� ) goto label
    BLEU_WBa        , // 0x40B //  if( word  <= word_������� ) goto label
    BLEU_LBa        , // 0x40C //  if( lword <= lword_������� ) goto label
    BLEU_BaB        , // 0x40D //  if( ������� <= ������� ) goto label
    BLEU_BaW        , // 0x40E //  if( ������� <= ������� ) goto label
    BLEU_BaL        , // 0x40F //  if( ������� <= ������� ) goto label
    BLEU_BaB_C      , // 0x410 //  if( ������� <= const ) goto label
    BLEU_BaW_C      , // 0x411 //  if( ������� <= const ) goto label
    BLEU_BaL_C      , // 0x412 //  if( ������� <= const ) goto label
    BLEU_BaB_S      , // 0x413 //  if( ������� <= byte_������� ) goto label
    BLEU_BaW_S      , // 0x414 //  if( ������� <= word_������� ) goto label
    BLEU_BaL_S      , // 0x415 //  if( ������� <= lword_�������) goto label
    BLEU_BS_S       , // 0x416 //  if( byte_�������  <=  byte_������� ) goto label
    BLEU_WS_S       , // 0x417 //  if( word_�������  <=  word_������� ) goto label
    BLEU_LS_S       , // 0x418 //  if( lword_������� <=  lword_������� ) goto label
    BLEU_BS_C       , // 0x419 //  if( byte_�������  <=  const ) goto label
    BLEU_WS_C       , // 0x41A //  if( word_�������  <=  const ) goto label
    BLEU_LS_C       , // 0x41B //  if( lword_������� <=  const ) goto label
    BLEU_BAr        , // 0x41C //  if( byte                    <= �������� ������� ) goto label
    BLEU_WAr        , // 0x41D //  if( word                    <= �������� ������� ) goto label
    BLEU_LAr        , // 0x41E //  if( lword                   <= �������� ������� ) goto label
    BLEU_ArB        , // 0x41F //  if( byte_�������� �������   <= �������� ������� ) goto label
    BLEU_ArW        , // 0x420 //  if( word_�������� �������   <= �������� ������� ) goto label
    BLEU_ArL        , // 0x421 //  if( lword_�������� �������  <= �������� ������� ) goto label
    BLEU_BAr_C      , // 0x422 //  if( byte_�������� �������   <= const  ) goto label
    BLEU_WAr_C      , // 0x423 //  if( word_�������� �������   <= const  ) goto label
    BLEU_LAr_C      , // 0x424 //  if( lword_�������� �������  <= const  ) goto label
    BLEU_BAr_Ba     , // 0x425 //  if( byte_�������� �������   <= �������   ) goto label
    BLEU_WAr_Ba     , // 0x426 //  if( word_�������� �������   <= �������   ) goto label
    BLEU_LAr_Ba     , // 0x427 //  if( lword_�������� �������  <= �������   ) goto label
    BLEU_BAr_S      , // 0x428 //  if( byte_�������� �������   <= �������   ) goto label
    BLEU_WAr_S      , // 0x429 //  if( word_�������� �������   <= �������   ) goto label
    BLEU_LAr_S      , // 0x42A //  if( lword_�������� �������  <= �������   ) goto label
    rezerv          , // 0x42B //
    rezerv          , // 0x42C //
    rezerv          , // 0x42D //
    rezerv          , // 0x42E //
    rezerv          , // 0x42F //
    rezerv          , // 0x430 //
    rezerv          , // 0x431 //
    rezerv          , // 0x432 //
    rezerv          , // 0x433 //
    rezerv          , // 0x434 //
    rezerv          , // 0x435 //
    rezerv          , // 0x436 //
    rezerv          , // 0x437 //
    rezerv          , // 0x438 //
    rezerv          , // 0x439 //
    rezerv          , // 0x43A //
    MOV_B_B         , // 0x43B //  byte = byte
    MOV_B_W         , // 0x43C //  byte = word
    MOV_B_L         , // 0x43D //  byte = lword
    MOV_B_D         , // 0x43E //  byte = double
    MOV_B_C         , // 0x43F //  byte = const
    MOV_B_SB        , // 0x440 //  byte = byte_�������
    MOV_B_SW        , // 0x441 //  byte = word_�������
    MOV_B_SL        , // 0x442 //  byte = lword_�������
    MOV_B_SD        , // 0x443 //  byte = double_�������
    MOV_B_BaB       , // 0x444 //  byte = byte_�������
    MOV_B_BaW       , // 0x445 //  byte = word_�������
    MOV_B_BaL       , // 0x446 //  byte = lword_�������
    MOV_B_BaD       , // 0x447 //  byte = double_�������
    MOV_W_B         , // 0x448 //  word = byte
    MOV_W_W         , // 0x449 //  word = word
    MOV_W_L         , // 0x44A //  word = lword
    MOV_W_D         , // 0x44B //  word = double
    MOV_W_C         , // 0x44C //  word = const
    MOV_W_SB        , // 0x44D //  word = byte_�������
    MOV_W_SW        , // 0x44E //  word = word_�������
    MOV_W_SL        , // 0x44F //  word = lword_�������
    MOV_W_SD        , // 0x450 //  word = double_�������
    MOV_W_BaB       , // 0x451 //  word = byte_�������
    MOV_W_BaW       , // 0x452 //  word = word_�������
    MOV_W_BaL       , // 0x453 //  word = lword_�������
    MOV_W_BaD       , // 0x454 //  word = double_�������
    MOV_L_B         , // 0x455 //  lword = byte
    MOV_L_W         , // 0x456 //  lword = word
    MOV_L_L         , // 0x457 //  lword = lword
    MOV_L_D         , // 0x458 //  lword = double
    MOV_L_C         , // 0x459 //  lword = const
    MOV_L_SB        , // 0x45A //  lword = byte_�������
    MOV_L_SW        , // 0x45B //  lword = word_�������
    MOV_L_SL        , // 0x45C //  lword = lword_�������
    MOV_L_SD        , // 0x45D //  lword = double_�������
    MOV_L_BaB       , // 0x45E //  lword = byte_�������
    MOV_L_BaW       , // 0x45F //  lword = word_�������
    MOV_L_BaL       , // 0x460 //  lword = lword_�������
    MOV_L_BaD       , // 0x461 //  lword = double_�������
    MOV_D_B         , // 0x462 //  double = byte
    MOV_D_W         , // 0x463 //  double = word
    MOV_D_L         , // 0x464 //  double = lword
    MOV_D_D         , // 0x465 //  double = double
    MOV_D_C         , // 0x466 //  double = const
    MOV_D_SB        , // 0x467 //  double = byte_�������
    MOV_D_SW        , // 0x468 //  double = word_�������
    MOV_D_SL        , // 0x469 //  double = lword_�������
    MOV_D_SD        , // 0x46A //  double = double_�������
    MOV_D_BaB       , // 0x46B //  double = byte_�������
    MOV_D_BaW       , // 0x46C //  double = word_�������
    MOV_D_BaL       , // 0x46D //  double = lword_�������
    MOV_D_BaD       , // 0x46E //  double = double_�������
    MOV_BaB_B       , // 0x46F //  byte_������� = byte
    MOV_BaB_W       , // 0x470 //  byte_������� = word
    MOV_BaB_L       , // 0x471 //  byte_������� = lword
    MOV_BaB_D       , // 0x472 //  byte_������� = double
    MOV_BaB_C       , // 0x473 //  byte_������� = const
    MOV_BaB_SB      , // 0x474 //  byte_������� = byte_�������
    MOV_BaB_SW      , // 0x475 //  byte_������� = word_�������
    MOV_BaB_SL      , // 0x476 //  byte_������� = lword_�������
    MOV_BaB_SD      , // 0x477 //  byte_������� = double_�������
    MOV_BaB_BaB     , // 0x478 //  byte_������� = byte_�������
    MOV_BaB_BaW     , // 0x479 //  byte_������� = word_�������
    MOV_BaB_BaL     , // 0x47A //  byte_������� = lword_�������
    MOV_BaB_BaD     , // 0x47B //  byte_������� = double_�������
    MOV_BaW_B       , // 0x47C //  word_������� = byte
    MOV_BaW_W       , // 0x47D //  word_������� = word
    MOV_BaW_L       , // 0x47E //  word_������� = lword
    MOV_BaW_D       , // 0x47F //  word_������� = double
    MOV_BaW_C       , // 0x480 //  word_������� = const
    MOV_BaW_SB      , // 0x481 //  word_������� = byte_�������
    MOV_BaW_SW      , // 0x482 //  word_������� = word_�������
    MOV_BaW_SL      , // 0x483 //  word_������� = lword_�������
    MOV_BaW_SD      , // 0x484 //  word_������� = double_�������
    MOV_BaW_BaB     , // 0x485 //  word_������� = byte_�������
    MOV_BaW_BaW     , // 0x486 //  word_������� = word_�������
    MOV_BaW_BaL     , // 0x487 //  word_������� = lword_�������
    MOV_BaW_BaD     , // 0x488 //  word_������� = double_�������
    MOV_BaL_B       , // 0x489 //  lword_������� = byte
    MOV_BaL_W       , // 0x48A //  lword_������� = word
    MOV_BaL_L       , // 0x48B //  lword_������� = lword
    MOV_BaL_D       , // 0x48C //  lword_������� = double
    MOV_BaL_C       , // 0x48D //  lword_������� = const
    MOV_BaL_SB      , // 0x48E //  lword_������� = byte_�������
    MOV_BaL_SW      , // 0x48F //  lword_������� = word_�������
    MOV_BaL_SL      , // 0x490 //  lword_������� = lword_�������
    MOV_BaL_SD      , // 0x491 //  lword_������� = double_�������
    MOV_BaL_BaB     , // 0x492 //  lword_������� = byte_�������
    MOV_BaL_BaW     , // 0x493 //  lword_������� = word_�������
    MOV_BaL_BaL     , // 0x494 //  lword_������� = lword_�������
    MOV_BaL_BaD     , // 0x495 //  lword_������� = double_�������
    MOV_BaD_B       , // 0x496 //  double_������� = byte
    MOV_BaD_W       , // 0x497 //  double_������� = word
    MOV_BaD_L       , // 0x498 //  double_������� = lword
    MOV_BaD_D       , // 0x499 //  double_������� = double
    MOV_BaD_C       , // 0x49A //  double_������� = const
    MOV_BaD_SB      , // 0x49B //  double_������� = byte_�������
    MOV_BaD_SW      , // 0x49C //  double_������� = word_�������
    MOV_BaD_SL      , // 0x49D //  double_������� = lword_�������
    MOV_BaD_SD      , // 0x49E //  double_������� = double_�������
    MOV_BaD_BaB     , // 0x49F //  double_������� = byte_�������
    MOV_BaD_BaW     , // 0x4A0 //  double_������� = word_�������
    MOV_BaD_BaL     , // 0x4A1 //  double_������� = lword_�������
    MOV_BaD_BaD     , // 0x4A2 //  double_������� = double_�������
    MOV_BAr_B       , // 0x4A3 // �������� ������� byte = byte
    MOV_BAr_W       , // 0x4A4 // �������� ������� byte = word
    MOV_BAr_L       , // 0x4A5 // �������� ������� byte = lword
    MOV_BAr_D       , // 0x4A6 // �������� ������� byte = double
    MOV_BAr_BAr     , // 0x4A7 // �������� ������� byte = �������� ������� byte
    MOV_BAr_WAr     , // 0x4A8 // �������� ������� byte = �������� ������� word
    MOV_BAr_LAr     , // 0x4A9 // �������� ������� byte = �������� ������� lword
    MOV_BAr_DAr     , // 0x4AA // �������� ������� byte = �������� ������� double
    MOV_BAr_C       , // 0x4AB // �������� ������� byte = const
    MOV_BAr_SB      , // 0x4AC // �������� ������� byte = byte_�������
    MOV_BAr_SW      , // 0x4AD // �������� ������� byte = word_�������
    MOV_BAr_SL      , // 0x4AE // �������� ������� byte = lword_�������
    MOV_BAr_SD      , // 0x4AF // �������� ������� byte = double_�������
    MOV_BAr_BaB     , // 0x4B0 // �������� ������� byte = byte_�������
    MOV_BAr_BaW     , // 0x4B1 // �������� ������� byte = word_�������
    MOV_BAr_BaL     , // 0x4B2 // �������� ������� byte = lword_�������
    MOV_BAr_BaD     , // 0x4B3 // �������� ������� byte = double_�������
    MOV_WAr_B       , // 0x4B4 // �������� ������� word = byte
    MOV_WAr_W       , // 0x4B5 // �������� ������� word = word
    MOV_WAr_L       , // 0x4B6 // �������� ������� word = lword
    MOV_WAr_D       , // 0x4B7 // �������� ������� word = double
    MOV_WAr_BAr     , // 0x4B8 // �������� ������� word = byte   �������� �������
    MOV_WAr_WAr     , // 0x4B9 // �������� ������� word = word   �������� �������
    MOV_WAr_LAr     , // 0x4BA // �������� ������� word = lword  �������� �������
    MOV_WAr_DAr     , // 0x4BB // �������� ������� word = double �������� �������
    MOV_WAr_C       , // 0x4BC // �������� ������� word = const
    MOV_WAr_SB      , // 0x4BD // �������� ������� word = byte_�������
    MOV_WAr_SW      , // 0x4BE // �������� ������� word = word_�������
    MOV_WAr_SL      , // 0x4BF // �������� ������� word = lword_�������
    MOV_WAr_SD      , // 0x4C0 // �������� ������� word = double_�������
    MOV_WAr_BaB     , // 0x4C1 // �������� ������� word = byte_�������
    MOV_WAr_BaW     , // 0x4C2 // �������� ������� word = word_�������
    MOV_WAr_BaL     , // 0x4C3 // �������� ������� word = lword_�������
    MOV_WAr_BaD     , // 0x4C4 // �������� ������� word = double_�������
    MOV_LAr_B       , // 0x4C5 // �������� ������� lword = byte
    MOV_LAr_W       , // 0x4C6 // �������� ������� lword = word
    MOV_LAr_L       , // 0x4C7 // �������� ������� lword = lword
    MOV_LAr_D       , // 0x4C8 // �������� ������� lword = double
    MOV_LAr_BAr     , // 0x4C9 // �������� ������� lword = byte   �������� �������
    MOV_LAr_WAr     , // 0x4CA // �������� ������� lword = word   �������� �������
    MOV_LAr_LAr     , // 0x4CB // �������� ������� lword = lword  �������� �������
    MOV_LAr_DAr     , // 0x4CC // �������� ������� lword = double �������� �������
    MOV_LAr_C       , // 0x4CD // �������� ������� lword = const
    MOV_LAr_SB      , // 0x4CE // �������� ������� lword = byte_�������
    MOV_LAr_SW      , // 0x4CF // �������� ������� lword = word_�������
    MOV_LAr_SL      , // 0x4D0 // �������� ������� lword = lword_�������
    MOV_LAr_SD      , // 0x4D1 // �������� ������� lword = double_�������
    MOV_LAr_BaB     , // 0x4D2 // �������� ������� lword = byte_�������
    MOV_LAr_BaW     , // 0x4D3 // �������� ������� lword = word_�������
    MOV_LAr_BaL     , // 0x4D4 // �������� ������� lword = lword_�������
    MOV_LAr_BaD     , // 0x4D5 // �������� ������� lword = double_�������
    MOV_DAr_B       , // 0x4D6 // �������� ������� double = byte
    MOV_DAr_W       , // 0x4D7 // �������� ������� double = word
    MOV_DAr_L       , // 0x4D8 // �������� ������� double = lword
    MOV_DAr_D       , // 0x4D9 // �������� ������� double = double
    MOV_DAr_BAr     , // 0x4DA // �������� ������� double = byte   �������� �������
    MOV_DAr_WAr     , // 0x4DB // �������� ������� double = word   �������� �������
    MOV_DAr_LAr     , // 0x4DC // �������� ������� double = lword  �������� �������
    MOV_DAr_DAr     , // 0x4DD // �������� ������� double = double �������� �������
    MOV_DAr_C       , // 0x4DE // �������� ������� double = const
    MOV_DAr_SB      , // 0x4DF // �������� ������� double = byte_�������
    MOV_DAr_SW      , // 0x4E0 // �������� ������� double = word_�������
    MOV_DAr_SL      , // 0x4E1 // �������� ������� double = lword_�������
    MOV_DAr_SD      , // 0x4E2 // �������� ������� double = double_�������
    MOV_DAr_BaB     , // 0x4E3 // �������� ������� double = byte_�������
    MOV_DAr_BaW     , // 0x4E4 // �������� ������� double = word_�������
    MOV_DAr_BaL     , // 0x4E5 // �������� ������� double = lword_�������
    MOV_DAr_BaD     , // 0x4E6 // �������� ������� double = double_�������
    MOV_B_BAr       , // 0x4E7 //    byte           = �������� ������� byte
    MOV_W_BAr       , // 0x4E8 //    word           = �������� ������� byte
    MOV_L_BAr       , // 0x4E9 //    lword          = �������� ������� byte
    MOV_D_BAr       , // 0x4EA //    double         = �������� ������� byte
    MOV_BaB_BAr     , // 0x4EB //    byte_�������   = �������� ������� byte
    MOV_BaW_BAr     , // 0x4EC //    word_�������   = �������� ������� byte
    MOV_BaL_BAr     , // 0x4ED //    lword_�������  = �������� ������� byte
    MOV_BaD_BAr     , // 0x4EE //    double_������� = �������� ������� byte
    MOV_B_WAr       , // 0x4EF //    byte           = �������� ������� word
    MOV_W_WAr       , // 0x4F0 //    word           = �������� ������� word
    MOV_L_WAr       , // 0x4F1 //    lword          = �������� ������� word
    MOV_D_WAr       , // 0x4F2 //    double         = �������� ������� word
    MOV_BaB_WAr     , // 0x4F3 //    byte_�������   = �������� ������� word
    MOV_BaW_WAr     , // 0x4F4 //    word_�������   = �������� ������� word
    MOV_BaL_WAr     , // 0x4F5 //    lword_�������  = �������� ������� word
    MOV_BaD_WAr     , // 0x4F6 //    double_������� = �������� ������� word
    MOV_B_LAr       , // 0x4F7 //    byte           = �������� ������� lword
    MOV_W_LAr       , // 0x4F8 //    word           = �������� ������� lword
    MOV_L_LAr       , // 0x4F9 //    lword          = �������� ������� lword
    MOV_D_LAr       , // 0x4FA //    double         = �������� ������� lword
    MOV_BaB_LAr     , // 0x4FB //    byte_�������   = �������� ������� lword
    MOV_BaW_LAr     , // 0x4FC //    word_�������   = �������� ������� lword
    MOV_BaL_LAr     , // 0x4FD //    lword_�������  = �������� ������� lword
    MOV_BaD_LAr     , // 0x4FE //    double_������� = �������� ������� lword
    MOV_B_DAr       , // 0x4FF //    byte           = �������� ������� double
    MOV_W_DAr       , // 0x500 //    word           = �������� ������� double
    MOV_L_DAr       , // 0x501 //    lword          = �������� ������� double
    MOV_D_DAr       , // 0x502 //    double         = �������� ������� double
    MOV_BaB_DAr     , // 0x503 //    byte_�������   = �������� ������� double
    MOV_BaW_DAr     , // 0x504 //    word_�������   = �������� ������� double
    MOV_BaL_DAr     , // 0x505 //    lword_�������  = �������� ������� double
    MOV_BaD_DAr     , // 0x506 //    double_������� = �������� ������� double
    MOVU_W_B        , // 0x507 //  word = byte
    MOVU_W_SB       , // 0x508 //  word = byte_�������
    MOVU_W_BaB      , // 0x509 //  word = byte_�������
    MOVU_L_B        , // 0x50A //  lword = byte
    MOVU_L_W        , // 0x50B //  lword = word
    MOVU_L_SB       , // 0x50C //  lword = byte_�������
    MOVU_L_SW       , // 0x50D //  lword = word_�������
    MOVU_L_BaB      , // 0x50E //  lword = byte_�������
    MOVU_L_BaW      , // 0x50F //  lword = word_�������
    MOVU_D_B        , // 0x510 //  double = byte
    MOVU_D_W        , // 0x511 //  double = word
    MOVU_D_L        , // 0x512 //  double = lword
    MOVU_D_SB       , // 0x513 //  double = byte_�������
    MOVU_D_SW       , // 0x514 //  double = word_�������
    MOVU_D_SL       , // 0x515 //  double = lword_�������
    MOVU_D_BaB      , // 0x516 //  double = byte_�������
    MOVU_D_BaW      , // 0x517 //  double = word_�������
    MOVU_D_BaL      , // 0x518 //  double = lword_�������
    MOVU_BaW_B      , // 0x519 //  word_������� = byte
    MOVU_BaW_SB     , // 0x51A //  word_������� = byte_�������
    MOVU_BaW_BaB    , // 0x51B //  word_������� = byte_�������
    MOVU_BaL_B      , // 0x51C //  lword_������� = byte
    MOVU_BaL_W      , // 0x51D //  lword_������� = word
    MOVU_BaL_SB     , // 0x51E //  lword_������� = byte_�������
    MOVU_BaL_SW     , // 0x51F //  lword_������� = word_�������
    MOVU_BaL_BaB    , // 0x520 //  lword_������� = byte_�������
    MOVU_BaL_BaW    , // 0x521 //  lword_������� = word_�������
    MOVU_BaD_B      , // 0x522 //  double_������� = byte
    MOVU_BaD_W      , // 0x523 //  double_������� = word
    MOVU_BaD_L      , // 0x524 //  double_������� = lword
    MOVU_BaD_SB     , // 0x525 //  double_������� = byte_�������
    MOVU_BaD_SW     , // 0x526 //  double_������� = word_�������
    MOVU_BaD_SL     , // 0x527 //  double_������� = lword_�������
    MOVU_BaD_BaB    , // 0x528 //  double_������� = byte_�������
    MOVU_BaD_BaW    , // 0x529 //  double_������� = word_�������
    MOVU_BaD_BaL    , // 0x52A //  double_������� = lword_�������
    MOVU_WAr_B      , // 0x52B // �������� ������� word = byte
    MOVU_WAr_BAr    , // 0x52C // �������� ������� word = byte �������� �������
    MOVU_WAr_SB     , // 0x52D // �������� ������� word = byte_�������
    MOVU_WAr_BaB    , // 0x52E // �������� ������� word = byte_�������
    MOVU_LAr_B      , // 0x52F // �������� ������� lword = byte
    MOVU_LAr_W      , // 0x530 // �������� ������� lword = word
    MOVU_LAr_BAr    , // 0x531 // �������� ������� lword = byte �������� �������
    MOVU_LAr_WAr    , // 0x532 // �������� ������� lword = word �������� �������
    MOVU_LAr_SB     , // 0x533 // �������� ������� lword = byte_�������
    MOVU_LAr_SW     , // 0x534 // �������� ������� lword = word_�������
    MOVU_LAr_BaB    , // 0x535 // �������� ������� lword = byte_�������
    MOVU_LAr_BaW    , // 0x536 // �������� ������� lword = word_�������
    MOVU_DAr_B      , // 0x537 // �������� ������� double = byte
    MOVU_DAr_W      , // 0x538 // �������� ������� double = word
    MOVU_DAr_L      , // 0x539 // �������� ������� double = lword
    MOVU_DAr_BAr    , // 0x53A // �������� ������� double = byte  �������� �������
    MOVU_DAr_WAr    , // 0x53B // �������� ������� double = word  �������� �������
    MOVU_DAr_LAr    , // 0x53C // �������� ������� double = lword �������� �������
    MOVU_DAr_SB     , // 0x53D // �������� ������� double = byte_�������
    MOVU_DAr_SW     , // 0x53E // �������� ������� double = word_�������
    MOVU_DAr_SL     , // 0x53F // �������� ������� double = lword_�������
    MOVU_DAr_BaB    , // 0x540 // �������� ������� double = byte_�������
    MOVU_DAr_BaW    , // 0x541 // �������� ������� double = word_�������
    MOVU_DAr_BaL    , // 0x542 // �������� ������� double = lword_�������
    MOVU_W_BAr      , // 0x543 // word          =  �������� ������� byte
    MOVU_L_BAr      , // 0x544 // lword         =  �������� ������� byte
    MOVU_D_BAr      , // 0x545 // double        =  �������� ������� byte
    MOVU_BaW_BAr    , // 0x546 // word_�������  =  �������� ������� byte
    MOVU_BaL_BAr    , // 0x547 // lword_������� =  �������� ������� byte
    MOVU_BaD_BAr    , // 0x548 // double_�������=  �������� ������� byte
    MOVU_L_WAr      , // 0x549 // lword         =  �������� ������� word
    MOVU_D_WAr      , // 0x54A // double        =  �������� ������� word
    MOVU_BaL_WAr    , // 0x54B // lword_������� =  �������� ������� word
    MOVU_BaD_WAr    , // 0x54C // double_�������=  �������� ������� word
    MOVU_D_LAr      , // 0x54D // double        =  �������� ������� lword
    MOVU_BaD_LAr    , // 0x54E // double_�������=  �������� ������� lword
    rezerv          , // 0x54F //
    rezerv          , // 0x550 //
    rezerv          , // 0x551 //
    rezerv          , // 0x552 //
    rezerv          , // 0x553 //
    rezerv          , // 0x554 //
    rezerv          , // 0x555 //
    rezerv          , // 0x556 //
    rezerv          , // 0x557 //
    rezerv          , // 0x558 //
    SetMsg_Av       , // 0x559 //  RegAvMsg |= const(1...32)   +
    SetMsg_Pr       , // 0x55A //  RegPrMsg |= const(1...32)   +
    SetMsg_Srv      , // 0x55B //  RegSrvMsg |= const(1...32)  +
    ClrMsg_Av       , // 0x55C //  RegAvMsg &= ~const(1...32)  +
    ClrMsg_Pr       , // 0x55D //  RegPrMsg &= ~const(1...32)  +
    ClrMsg_Srv      , // 0x55E //  RegSrvMsg &= ~const(1...32) +
    ClrAllMsg_Av    , // 0x55F //  RegAvMsg = 0                +
    ClrAllMsg_Pr    , // 0x560 //  RegPrMsg = 0                +
    ClrAllMsg_Srv   , // 0x561 //  RegSrvMsg = 0               +
    rezerv          , // 0x562 //
    rezerv          , // 0x563 //
    rezerv          , // 0x564 //
    rezerv          , // 0x565 //
    rezerv          , // 0x566 //
    rezerv          , // 0x567 //
    rezerv          , // 0x568 //
    rezerv          , // 0x569 //
    rezerv          , // 0x56A //
    rezerv          , // 0x56B //
    rezerv          , // 0x56C //
    rezerv          , // 0x56D //
    rezerv          , // 0x56E //
    rezerv          , // 0x56F //
    rezerv          , // 0x570 //
    rezerv          , // 0x571 //
    GOTO            , // 0x572 //  goto label
    CALL            , // 0x573 //  call programm()
    CALL_B          , // 0x574 //  call base_programm()
    RET               // 0x575 //  return

};


#else

extern struct Tabl_Obj_MSG   Tabl_Msg_obj;
extern struct base_IZU b_timeIZUd[];
extern struct base_IZU b_timeIZUi[];
extern struct base_ZI  base_ZIstr[];
extern struct bPI_reg_str bPI_str[];
extern struct bfil_str    bfilstr[];
extern struct bAverage_str bAveragestr[];
//extern struct MSG_Obj_regs   MSGObjregs;

extern word (*Oprg[])( union Operand* );
extern word (*Base_func[])(union Operand* );

#endif
#endif
