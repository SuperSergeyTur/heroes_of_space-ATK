//----- Сложение--------------
word ADD_BB   (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] + MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word ADD_WW   (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] + MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word ADD_LL   (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] + MemData.lwData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word ADD_DD   (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] =  MemData.dData[Operands[1]._.Number] + MemData.dData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word ADD_BC  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] + Operands[2].all;
    return 0;

}
//--------------------------------
word ADD_WC  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] + Operands[2].all;
    return 0;

}
//--------------------------------
word ADD_LC  (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[3].all<<16)+Operands[2].all;
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] + lax;
    return 0;

}
//--------------------------------
word ADD_DC  (union Operand *Operands)
{
    union str_double d_lax;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[5].all;
    d_lax.wrd[1] =  Operands[4].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[2].all;
#else

    d_lax.wrd[0] =  Operands[2].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[4].all;
    d_lax.wrd[3] =  Operands[5].all;

#endif
    MemData.dData[Operands[0]._.Number] =  MemData.dData[Operands[1]._.Number] + d_lax.all;
    return 0;

}
//--------------------------------
word ADD_BS  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] + _or.MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word ADD_WS  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] + _or.MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word ADD_LS  (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] + _or.MemData.lwData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word ADD_DS  (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] =  MemData.dData[Operands[1]._.Number] + _or.MemData.dData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word ADD_BBa (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] + *(b*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}
//--------------------------------
word ADD_WBa (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] + *(w*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}
//--------------------------------
word ADD_LBa (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] + *(lw*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}

//--------------------------------
word ADD_DBa (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] =  MemData.dData[Operands[1]._.Number] + *(double*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}
//--------------------------------
word ADD_BAr (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number]
                                         + MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}

//--------------------------------
word ADD_WAr (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number]
                                         + MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}

//--------------------------------
word ADD_LAr (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number]
                                         + MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}

//--------------------------------
word ADD_DAr (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] =  MemData.dData[Operands[1]._.Number]
                                         + MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}


//----- Вычитание-------------
word SUB_BB   (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] - MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word SUB_WW   (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] - MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word SUB_LL   (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] - MemData.lwData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word SUB_DD   (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] =  MemData.dData[Operands[1]._.Number] - MemData.dData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word SUB_BC  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] - Operands[2].all;
    return 0;

}
//--------------------------------
word SUB_WC  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] - Operands[2].all;
    return 0;

}
//--------------------------------
word SUB_LC  (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[3].all<<16)+Operands[2].all;
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] - lax;
    return 0;

}
//--------------------------------
word SUB_DC  (union Operand *Operands)
{
    union str_double d_lax;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[5].all;
    d_lax.wrd[1] =  Operands[4].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[2].all;
#else

    d_lax.wrd[0] =  Operands[2].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[4].all;
    d_lax.wrd[3] =  Operands[5].all;

#endif
    MemData.dData[Operands[0]._.Number] =  MemData.dData[Operands[1]._.Number] - d_lax.all;
    return 0;

}
//--------------------------------
word SUB_CB  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  Operands[2].all - MemData.bData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------
word SUB_CW  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = Operands[2].all - MemData.wData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------
word SUB_CL  (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[3].all<<16)+Operands[2].all;
    MemData.lwData[Operands[0]._.Number] =  lax - MemData.lwData[Operands[1]._.Number];
    return 0;

}
//--------------------------------
word SUB_CD  (union Operand *Operands)
{
    union str_double d_lax;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[5].all;
    d_lax.wrd[1] =  Operands[4].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[2].all;
#else

    d_lax.wrd[0] =  Operands[2].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[4].all;
    d_lax.wrd[3] =  Operands[5].all;

#endif
    MemData.dData[Operands[0]._.Number] = d_lax.all  - MemData.dData[Operands[1]._.Number];
    return 0;

}
//--------------------------------
word SUB_BS  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] - _or.MemData.bData[Operands[2]._.Number];
    return 0;

}

//--------------------------------
word SUB_WS  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] - _or.MemData.wData[Operands[2]._.Number];
    return 0;

}

//--------------------------------
word SUB_LS  (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] - _or.MemData.lwData[Operands[2]._.Number];
    return 0;

}

//--------------------------------
word SUB_DS  (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] =  MemData.dData[Operands[1]._.Number] - _or.MemData.dData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word SUB_SB  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = _or.MemData.bData[Operands[1]._.Number] - MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word SUB_SW  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = _or.MemData.wData[Operands[1]._.Number] - MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word SUB_SL  (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = _or.MemData.lwData[Operands[1]._.Number] - MemData.lwData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word SUB_SD  (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = _or.MemData.dData[Operands[1]._.Number] - MemData.dData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word SUB_BBa (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] - *(b*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}
//--------------------------------
word SUB_WBa (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] - *(w*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}
//--------------------------------
word SUB_LBa (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] - *(lw*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}
//--------------------------------
word SUB_DBa (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] =  MemData.dData[Operands[1]._.Number] - *(double*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}

//--------------------------------
word SUB_BaB (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = *(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr - MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word SUB_BaW (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = *(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr - MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word SUB_BaL (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = *(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr - MemData.lwData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word SUB_BaD (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = *(double*)var_tab1[Std_Vars[Operands[1]._.Number]].addr - MemData.dData[Operands[2]._.Number];
    return 0;

}
word SUB_BAr (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number]
                                         - MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word SUB_WAr (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number]
                                         - MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word SUB_LAr (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number]
                                         - MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word SUB_DAr (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] =  MemData.dData[Operands[1]._.Number]
                                         - MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word SUB_ArB (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number]
                                         - MemData.bData[Operands[2]._.Number];
    return 0;

}
word SUB_ArW (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number]
                                         - MemData.wData[Operands[2]._.Number];
    return 0;

}
word SUB_ArL (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number]
                                         - MemData.lwData[Operands[2]._.Number];
    return 0;

}
word SUB_ArD (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] =  MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number]
                                         - MemData.dData[Operands[2]._.Number];
    return 0;

}

//------Умножение--------------
//------Знаковое---------------
word MUL_BB   (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  (sb)MemData.bData[Operands[1]._.Number] * (sb)MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word MUL_WW   (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  (sw)MemData.wData[Operands[1]._.Number] * (sw)MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word MUL_LL   (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  (slw)MemData.lwData[Operands[1]._.Number] * (slw)MemData.lwData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word MUL_DD   (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] =  MemData.dData[Operands[1]._.Number] * MemData.dData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word MUL_BC  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  (sb)MemData.bData[Operands[1]._.Number] * (sb)Operands[2].all;
    return 0;

}
//--------------------------------
word MUL_WC  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  (sw)MemData.wData[Operands[1]._.Number] * (sw)Operands[2].all;
    return 0;

}
//--------------------------------
word MUL_LC  (union Operand *Operands)
{
    slword lax;
    lax = ((lw)Operands[3].all<<16)+Operands[2].all;
    MemData.lwData[Operands[0]._.Number] =  (slw)MemData.lwData[Operands[1]._.Number] * lax;
    return 0;

}
//--------------------------------
word MUL_DC  (union Operand *Operands)
{
    union str_double d_lax;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[5].all;
    d_lax.wrd[1] =  Operands[4].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[2].all;
#else

    d_lax.wrd[0] =  Operands[2].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[4].all;
    d_lax.wrd[3] =  Operands[5].all;

#endif
    MemData.dData[Operands[0]._.Number] =  MemData.dData[Operands[1]._.Number] * d_lax.all;
    return 0;

}
//--------------------------------
word MUL_BS  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  (sb)MemData.bData[Operands[1]._.Number] * (sb)_or.MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word MUL_WS  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  (sw)MemData.wData[Operands[1]._.Number] * (sw)_or.MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word MUL_LS  (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  (slw)MemData.lwData[Operands[1]._.Number] * (slw)_or.MemData.lwData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word MUL_DS  (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] =  MemData.dData[Operands[1]._.Number] * _or.MemData.dData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word MUL_BBa (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  (sb)MemData.bData[Operands[1]._.Number] * *(sb*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}
//--------------------------------
word MUL_WBa (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  (sw)MemData.wData[Operands[1]._.Number] * *(sw*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}
//--------------------------------
word MUL_LBa (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  (slw)MemData.lwData[Operands[1]._.Number] * *(slw*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}
//--------------------------------
word MUL_DBa (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] =  MemData.dData[Operands[1]._.Number] * *(double*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}
word MUL_BAr  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  (sb)MemData.bData[Operands[1]._.Number] *
                 (sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word MUL_WAr  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  (sw)MemData.wData[Operands[1]._.Number] *
                 (sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word MUL_LAr  (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  (slw)MemData.lwData[Operands[1]._.Number] *
                 (slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word MUL_DAr  (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] =  MemData.dData[Operands[1]._.Number] *
                 MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}


//---------Беззнаковое------------


word MULU_BB   (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] * MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word MULU_WW   (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] * MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word MULU_LL   (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] * MemData.lwData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word MULU_BC  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] * Operands[2].all;
    return 0;

}
//--------------------------------
word MULU_WC  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] * Operands[2].all;
    return 0;

}
//--------------------------------
word MULU_LC  (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[3].all<<16)+Operands[2].all;
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] * lax;
    return 0;

}
//--------------------------------
word MULU_BS  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] * _or.MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word MULU_WS  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] * _or.MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word MULU_LS  (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] * _or.MemData.lwData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word MULU_BBa (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] * *(b*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}
//--------------------------------
word MULU_WBa (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] * *(w*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}
//--------------------------------
word MULU_LBa (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] * *(lw*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}
word MULU_BAr  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] *
                 MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word MULU_WAr  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] *
                 MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word MULU_LAr  (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] *
                 MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}


//----- Деление---------------

//------Знаковое---------------

word DIV_BB   (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  (sb)MemData.bData[Operands[1]._.Number] / (sb)MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word DIV_WW   (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  (sw)MemData.wData[Operands[1]._.Number] / (sw)MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word DIV_LL   (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  (slw)MemData.lwData[Operands[1]._.Number] / (slw)MemData.lwData[Operands[2]._.Number];
    return 0;

}

//--------------------------------
word DIV_DD   (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] =  MemData.dData[Operands[1]._.Number] / MemData.dData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word DIV_BC  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  (sb)MemData.bData[Operands[1]._.Number] / (sb)Operands[2].all;
    return 0;

}
//--------------------------------
word DIV_WC  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  (sw)MemData.wData[Operands[1]._.Number] / (sw)Operands[2].all;
    return 0;

}
//--------------------------------
word DIV_LC  (union Operand *Operands)
{
    slword lax;
    lax = ((lw)Operands[3].all<<16)+Operands[2].all;
    MemData.lwData[Operands[0]._.Number] =  (slw)MemData.lwData[Operands[1]._.Number] / lax;
    return 0;

}
//--------------------------------
word DIV_DC  (union Operand *Operands)
{
    union str_double d_lax;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[5].all;
    d_lax.wrd[1] =  Operands[4].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[2].all;
#else

    d_lax.wrd[0] =  Operands[2].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[4].all;
    d_lax.wrd[3] =  Operands[5].all;

#endif
    MemData.dData[Operands[0]._.Number] =  MemData.dData[Operands[1]._.Number] / d_lax.all;
    return 0;

}
//--------------------------------
word DIV_CB  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  (sb)Operands[2].all / (sb)MemData.bData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------
word DIV_CW  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = (sw)Operands[2].all / (sw)MemData.wData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------
word DIV_CL  (union Operand *Operands)
{
    slword lax;
    lax = ((lw)Operands[3].all<<16)+Operands[2].all;
    MemData.lwData[Operands[0]._.Number] =  lax / (slw)MemData.lwData[Operands[1]._.Number];
    return 0;

}
//--------------------------------
word DIV_CD  (union Operand *Operands)
{
    union str_double d_lax;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[5].all;
    d_lax.wrd[1] =  Operands[4].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[2].all;
#else

    d_lax.wrd[0] =  Operands[2].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[4].all;
    d_lax.wrd[3] =  Operands[5].all;

#endif
    MemData.dData[Operands[0]._.Number] =  d_lax.all / MemData.dData[Operands[1]._.Number];
    return 0;

}
//--------------------------------
word DIV_BS  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  (sb)MemData.bData[Operands[1]._.Number] / (sb)_or.MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word DIV_WS  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  (sw)MemData.wData[Operands[1]._.Number] / (sw)_or.MemData.wData[Operands[2]._.Number];
    return 0;

}

//--------------------------------
word DIV_LS  (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  (slw)MemData.lwData[Operands[1]._.Number] / (slw)_or.MemData.lwData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word DIV_DS  (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] =  MemData.dData[Operands[1]._.Number] / _or.MemData.dData[Operands[2]._.Number];
    return 0;

}

//--------------------------------
word DIV_SB  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = (sb)_or.MemData.bData[Operands[1]._.Number] / (sb)MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word DIV_SW  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = (sw)_or.MemData.wData[Operands[1]._.Number] / (sw)MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word DIV_SL (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = _or.MemData.lwData[Operands[1]._.Number] / MemData.lwData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word DIV_SD  (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = _or.MemData.dData[Operands[1]._.Number] / MemData.dData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word DIV_BBa (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  (sb)MemData.bData[Operands[1]._.Number] / *(sb*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}
//--------------------------------
word DIV_WBa (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  (sw)MemData.wData[Operands[1]._.Number] / *(sw*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}
//--------------------------------
word DIV_LBa (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  (slw)MemData.lwData[Operands[1]._.Number] / *(slw*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}

//--------------------------------
word DIV_DBa (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] =  MemData.dData[Operands[1]._.Number] / *(double*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}

//--------------------------------
word DIV_BaB (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = *(sb*)var_tab1[Std_Vars[Operands[1]._.Number]].addr / (sb)MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word DIV_BaW (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = *(sw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr / (sw)MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word DIV_BaL (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = *(slw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr / (slw)MemData.lwData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word DIV_BaD (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = *(double*)var_tab1[Std_Vars[Operands[1]._.Number]].addr / MemData.dData[Operands[2]._.Number];
    return 0;

}

word DIV_BAr(union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  (sb)MemData.bData[Operands[1]._.Number] /
                 (sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word DIV_WAr(union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  (sw)MemData.wData[Operands[1]._.Number] /
                 (sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word DIV_LAr(union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  (slw)MemData.lwData[Operands[1]._.Number] /
                 (slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word DIV_DAr(union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] =  MemData.dData[Operands[1]._.Number] /
                 MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word DIV_ArB(union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =
    (sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] /(sb)MemData.bData[Operands[2]._.Number] ;
    return 0;

}
word DIV_ArW(union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =
    (sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] / (sw)MemData.wData[Operands[2]._.Number] ;
    return 0;

}
word DIV_ArL(union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =
   (slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] / (slw)MemData.lwData[Operands[2]._.Number] ;
    return 0;

}
word DIV_ArD(union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] =
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] / MemData.dData[Operands[2]._.Number] ;
    return 0;

}

//------Беззнаковое---------------

word DIVU_BB   (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] / MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word DIVU_WW   (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] / MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word DIVU_LL   (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] / MemData.lwData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word DIVU_BC  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] / Operands[2].all;
    return 0;

}
//--------------------------------
word DIVU_WC  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] / Operands[2].all;
    return 0;

}
//--------------------------------
word DIVU_LC  (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[3].all<<16)+Operands[2].all;
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] / lax;
    return 0;

}
//--------------------------------
word DIVU_CB  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  Operands[2].all / MemData.bData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------
word DIVU_CW  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = Operands[2].all / MemData.wData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------
word DIVU_CL  (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[3].all<<16)+Operands[2].all;
    MemData.lwData[Operands[0]._.Number] =  lax / MemData.lwData[Operands[1]._.Number];
    return 0;

}
//--------------------------------
word DIVU_BS  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] / _or.MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word DIVU_WS  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] / _or.MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word DIVU_LS  (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] / _or.MemData.lwData[Operands[2]._.Number];
    return 0;

}

//--------------------------------
word DIVU_SB  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = _or.MemData.bData[Operands[1]._.Number] / MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word DIVU_SW  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = _or.MemData.wData[Operands[1]._.Number] / MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word DIVU_SL  (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = _or.MemData.lwData[Operands[1]._.Number] / MemData.lwData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word DIVU_BBa (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] / *(b*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}
//--------------------------------
word DIVU_WBa (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] / *(w*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}
//--------------------------------
word DIVU_LBa (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  (lw)MemData.lwData[Operands[1]._.Number] / *(lw*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}

//--------------------------------
word DIVU_BaB (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = *(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr / MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word DIVU_BaW (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = *(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr / MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word DIVU_BaL (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = *(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr / MemData.lwData[Operands[2]._.Number];
    return 0;

}

word DIVU_BAr(union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] /
                 MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word DIVU_WAr(union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] /
                 MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word DIVU_LAr(union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] /
                 MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word DIVU_ArB(union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =
    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] / MemData.bData[Operands[2]._.Number] ;
    return 0;

}
word DIVU_ArW(union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =
    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] / MemData.wData[Operands[2]._.Number] ;
    return 0;

}
word DIVU_ArL(union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =
            MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] / MemData.lwData[Operands[2]._.Number] ;
    return 0;

}

//------Инверсия---------------

word NO_BB   (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = ~MemData.bData[Operands[1]._.Number];
    return 0;

}
//--------------------------------
word NO_WW   (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = ~MemData.wData[Operands[1]._.Number];
    return 0;

}
//--------------------------------
word NO_LL   (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = ~MemData.lwData[Operands[1]._.Number];
    return 0;

}
//--------------------------------
word NO_BS  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  ~_or.MemData.bData[Operands[1]._.Number];
    return 0;

}
//--------------------------------
word NO_WS  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  ~_or.MemData.wData[Operands[1]._.Number];
    return 0;

}
//--------------------------------
word NO_LS  (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  ~_or.MemData.lwData[Operands[1]._.Number];
    return 0;

}
//--------------------------------
word NO_BBa (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  ~(*(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr);
    return 0;

}
//--------------------------------
word NO_WBa (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  ~(*(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr);
    return 0;

}
//--------------------------------
word NO_LBa (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  ~(*(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr);
    return 0;

}

word NO_BAr     (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = ~MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
    return 0;

}

word NO_WAr     (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = ~MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
    return 0;

}
word NO_LAr     (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = ~MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
    return 0;

}


//------Логическое ИЛИ--------------
word OR_BB   (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] | MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word OR_WW   (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] | MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word OR_LL   (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] | MemData.lwData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word OR_BC  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] | Operands[2].all;
    return 0;

}
//--------------------------------
word OR_WC  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] | Operands[2].all;
    return 0;

}
//--------------------------------
word OR_LC  (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[3].all<<16)+Operands[2].all;
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] | lax;
    return 0;

}
//--------------------------------
word OR_BS  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] | _or.MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word OR_WS  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] | _or.MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word OR_LS  (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] | _or.MemData.lwData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word OR_BBa (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] | (*(b*)var_tab1[Std_Vars[Operands[2]._.Number]].addr);
    return 0;

}
//--------------------------------
word OR_WBa (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] | (*(w*)var_tab1[Std_Vars[Operands[2]._.Number]].addr);
    return 0;

}
//--------------------------------
word OR_LBa (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] | (*(lw*)var_tab1[Std_Vars[Operands[2]._.Number]].addr);
    return 0;

}

word OR_BAr     (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] |
                 MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word OR_WAr     (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] |
                 MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word OR_LAr     (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] |
                 MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}

//------Исключающее ИЛИ--------------
word XOR_BB   (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] ^ MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word XOR_WW   (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] ^ MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word XOR_LL   (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] ^ MemData.lwData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word XOR_BC  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] ^ Operands[2].all;
    return 0;

}
//--------------------------------
word XOR_WC  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] ^ Operands[2].all;
    return 0;

}
//--------------------------------
word XOR_LC  (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[3].all<<16)+Operands[2].all;
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] ^ lax;
    return 0;

}
//--------------------------------
word XOR_BS  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] ^ _or.MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word XOR_WS  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] ^ _or.MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word XOR_LS  (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] ^ _or.MemData.lwData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word XOR_BBa (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] ^ (*(b*)var_tab1[Std_Vars[Operands[2]._.Number]].addr);
    return 0;

}
//--------------------------------
word XOR_WBa (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] ^ (*(w*)var_tab1[Std_Vars[Operands[2]._.Number]].addr);
    return 0;

}
//--------------------------------
word XOR_LBa (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] ^ (*(lw*)var_tab1[Std_Vars[Operands[2]._.Number]].addr);
    return 0;

}

word XOR_BAr     (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] ^
                 MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word XOR_WAr     (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] ^
                 MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word XOR_LAr     (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] ^
                 MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}

//------Логическое И--------------
word AND_BB   (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] & MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word AND_WW   (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] & MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word AND_LL   (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] & MemData.lwData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word AND_BC  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] & Operands[2].all;
    return 0;

}
//--------------------------------
word AND_WC  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] & Operands[2].all;
    return 0;

}
//--------------------------------
word AND_LC  (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[3].all<<16)+Operands[2].all;
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] & lax;
    return 0;

}
//--------------------------------
word AND_BS  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] & _or.MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word AND_WS  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] & _or.MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word AND_LS  (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] & _or.MemData.lwData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word AND_BBa (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] & (*(b*)var_tab1[Std_Vars[Operands[2]._.Number]].addr);
    return 0;

}
//--------------------------------
word AND_WBa (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] & (*(w*)var_tab1[Std_Vars[Operands[2]._.Number]].addr);
    return 0;

}
//--------------------------------
word AND_LBa (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] & (*(lw*)var_tab1[Std_Vars[Operands[2]._.Number]].addr);
    return 0;

}

word AND_BAr    (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] &
                 MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word AND_WAr    (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] &
                 MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word AND_LAr    (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] &
                 MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}

//----- Сдвиг вправо---------------

//------Знаковый---------------

word ROR_BB   (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  (sb)MemData.bData[Operands[1]._.Number] >> MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word ROR_WW   (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  (sw)MemData.wData[Operands[1]._.Number] >> MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word ROR_LL   (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  (slw)MemData.lwData[Operands[1]._.Number] >> MemData.lwData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word ROR_BC  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  (sb)MemData.bData[Operands[1]._.Number] >> Operands[2].all;
    return 0;

}
//--------------------------------
word ROR_WC  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  (sw)MemData.wData[Operands[1]._.Number] >> Operands[2].all;
    return 0;

}
//--------------------------------
word ROR_LC  (union Operand *Operands)
{
    slword lax;
    lax = ((lw)Operands[3].all<<16)+Operands[2].all;
    MemData.lwData[Operands[0]._.Number] =  (slw)MemData.lwData[Operands[1]._.Number] >> lax;
    return 0;

}
//--------------------------------
word ROR_CB  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  (sb)Operands[2].all >> MemData.bData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------
word ROR_CW  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = (sw)Operands[2].all >> MemData.wData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------
word ROR_CL  (union Operand *Operands)
{
    slword lax;
    lax = ((lw)Operands[3].all<<16)+Operands[2].all;
    MemData.lwData[Operands[0]._.Number] =  lax >> MemData.lwData[Operands[1]._.Number];
    return 0;

}
//--------------------------------
word ROR_BS  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  (sb)MemData.bData[Operands[1]._.Number] >> _or.MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word ROR_WS  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  (sw)MemData.wData[Operands[1]._.Number] >> _or.MemData.wData[Operands[2]._.Number];
    return 0;

}

//--------------------------------
word ROR_LS  (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  (slw)MemData.lwData[Operands[1]._.Number] >> _or.MemData.lwData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word ROR_SB  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = (sb)_or.MemData.bData[Operands[1]._.Number] >> MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word ROR_SW  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = (sw)_or.MemData.wData[Operands[1]._.Number] >> MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word ROR_SL  (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = (slw)_or.MemData.lwData[Operands[1]._.Number] >> MemData.lwData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word ROR_BBa (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  (sb)MemData.bData[Operands[1]._.Number] >> *(b*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}
//--------------------------------
word ROR_WBa (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  (sw)MemData.wData[Operands[1]._.Number] >> *(w*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}
//--------------------------------
word ROR_LBa (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  (slw)MemData.lwData[Operands[1]._.Number] >> *(lw*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}

//--------------------------------
word ROR_BaB (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = *(sb*)var_tab1[Std_Vars[Operands[1]._.Number]].addr >> MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word ROR_BaW (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = *(sw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr >> MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word ROR_BaL (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = *(slw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr >> MemData.lwData[Operands[2]._.Number];
    return 0;

}
word ROR_BAr    (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  (sb)MemData.bData[Operands[1]._.Number] >>
                 MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word ROR_WAr    (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  (sw)MemData.wData[Operands[1]._.Number] >>
                 MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word ROR_LAr    (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  (slw)MemData.lwData[Operands[1]._.Number] >>
                 MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word ROR_ArB    (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  (sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] >>
                                              MemData.bData[Operands[2]._.Number];
    return 0;

}
word ROR_ArW    (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  (sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] >>
                                              MemData.wData[Operands[2]._.Number];
    return 0;

}
word ROR_ArL    (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  (slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] >>
                                              MemData.lwData[Operands[2]._.Number];
    return 0;

}
//------Беззнаковый---------------

word RORU_BB   (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] >> MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word RORU_WW   (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] >> MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word RORU_LL   (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] >> MemData.lwData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word RORU_BC  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] >> Operands[2].all;
    return 0;

}
//--------------------------------
word RORU_WC  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] >> Operands[2].all;
    return 0;

}
//--------------------------------
word RORU_LC  (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[3].all<<16)+Operands[2].all;
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] >> lax;
    return 0;

}
//--------------------------------
word RORU_CB  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  Operands[2].all >> MemData.bData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------
word RORU_CW  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = Operands[2].all >> MemData.wData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------
word RORU_CL  (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[3].all<<16)+Operands[2].all;
    MemData.lwData[Operands[0]._.Number] =  lax >> MemData.lwData[Operands[1]._.Number];
    return 0;

}
//--------------------------------
word RORU_BS  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] >> _or.MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word RORU_WS  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] >> _or.MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word RORU_LS  (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] >> _or.MemData.lwData[Operands[2]._.Number];
    return 0;

}

//--------------------------------
word RORU_SB  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = _or.MemData.bData[Operands[1]._.Number] >> MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word RORU_SW  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = _or.MemData.wData[Operands[1]._.Number] >> MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word RORU_SL  (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = _or.MemData.lwData[Operands[1]._.Number] >> MemData.lwData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word RORU_BBa (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] >> *(b*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}
//--------------------------------
word RORU_WBa (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] >> *(w*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}
//--------------------------------
word RORU_LBa (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  (lw)MemData.lwData[Operands[1]._.Number] >> *(lw*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}

//--------------------------------
word RORU_BaB (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = *(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr >> MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word RORU_BaW (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = *(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr >> MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word RORU_BaL (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = *(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr >> MemData.lwData[Operands[2]._.Number];
    return 0;

}

word RORU_BAr    (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] >>
                 MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word RORU_WAr    (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] >>
                 MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word RORU_LAr    (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] >>
                 MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word RORU_ArB    (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] >>
                                              MemData.bData[Operands[2]._.Number];
    return 0;

}
word RORU_ArW    (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] >>
                                              MemData.wData[Operands[2]._.Number];
    return 0;

}
word RORU_ArL    (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] >>
                                              MemData.lwData[Operands[2]._.Number];
    return 0;

}
//------Сдвиг влево---------------

word ROL_BB   (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] << MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word ROL_WW   (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] << MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word ROL_LL   (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] << MemData.lwData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word ROL_BC  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] << Operands[2].all;
    return 0;

}
//--------------------------------
word ROL_WC  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] << Operands[2].all;
    return 0;

}
//--------------------------------
word ROL_LC  (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[3].all<<16)+Operands[2].all;
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] << lax;
    return 0;

}
//--------------------------------
word ROL_CB  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  Operands[2].all << MemData.bData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------
word ROL_CW  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = Operands[2].all << MemData.wData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------
word ROL_CL  (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[3].all<<16)+Operands[2].all;
    MemData.lwData[Operands[0]._.Number] =  lax << MemData.lwData[Operands[1]._.Number];
    return 0;

}
//--------------------------------
word ROL_BS  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] << _or.MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word ROL_WS  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] << _or.MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word ROL_LS  (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  MemData.lwData[Operands[1]._.Number] << _or.MemData.lwData[Operands[2]._.Number];
    return 0;

}

//--------------------------------
word ROL_SB  (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = _or.MemData.bData[Operands[1]._.Number] << MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word ROL_SW  (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = _or.MemData.wData[Operands[1]._.Number] << MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word ROL_SL  (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = _or.MemData.lwData[Operands[1]._.Number] << MemData.lwData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word ROL_BBa (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] << *(b*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}
//--------------------------------
word ROL_WBa (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =  MemData.wData[Operands[1]._.Number] << *(w*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}
//--------------------------------
word ROL_LBa (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =  (lw)MemData.lwData[Operands[1]._.Number] << *(lw*)var_tab1[Std_Vars[Operands[2]._.Number]].addr;
    return 0;

}

//--------------------------------
word ROL_BaB (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = *(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr << MemData.bData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word ROL_BaW (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = *(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr << MemData.wData[Operands[2]._.Number];
    return 0;

}
//--------------------------------
word ROL_BaL (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = *(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr << MemData.lwData[Operands[2]._.Number];
    return 0;

}

word ROL_BAr    (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =  MemData.bData[Operands[1]._.Number] <<
                 MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word ROL_WAr    (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =      MemData.wData[Operands[1]._.Number] <<
                 MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word ROL_LAr    (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =       MemData.lwData[Operands[1]._.Number] <<
                 MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[2]._.Number]._.Number];
    return 0;

}
word ROL_ArB    (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] =      MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] <<
                                              MemData.bData[Operands[2]._.Number];
    return 0;

}
word ROL_ArW    (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] =      MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] <<
                                              MemData.wData[Operands[2]._.Number];
    return 0;

}
word ROL_ArL    (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] =       MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] <<
                                              MemData.lwData[Operands[2]._.Number];
    return 0;

}

//------Переход, если равно---------------

word BEQ_BB   (union Operand *Operands)
{
    if (MemData.bData[Operands[0]._.Number] == MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BEQ_WW   (union Operand *Operands)
{
    if (MemData.wData[Operands[0]._.Number] == MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BEQ_LL   (union Operand *Operands)
{
    if (MemData.lwData[Operands[0]._.Number] == MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BEQ_DD   (union Operand *Operands)
{
    if (MemData.dData[Operands[0]._.Number] == MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BEQ_BC  (union Operand *Operands)
{
    if (MemData.bData[Operands[0]._.Number] == Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BEQ_WC  (union Operand *Operands)
{
    if (MemData.wData[Operands[0]._.Number] == Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BEQ_LC  (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[2].all<<16)+Operands[1].all;
    if (MemData.lwData[Operands[0]._.Number] == lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}
//--------------------------------
word BEQ_DC  (union Operand *Operands)
{
    union str_double d_lax;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[4].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[2].all;
    d_lax.wrd[3] =  Operands[1].all;
#else

    d_lax.wrd[0] =  Operands[1].all;
    d_lax.wrd[1] =  Operands[2].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[4].all;

#endif

    if (MemData.dData[Operands[0]._.Number] == d_lax.all )
    {
      if (Operands[5].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[5].all;

    }
    return 0;

}
//--------------------------------
word BEQ_BS  (union Operand *Operands)
{
    if (MemData.bData[Operands[0]._.Number] == _or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BEQ_WS  (union Operand *Operands)
{
    if (MemData.wData[Operands[0]._.Number] == _or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BEQ_LS  (union Operand *Operands)
{
    if (MemData.lwData[Operands[0]._.Number] == _or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BEQ_DS  (union Operand *Operands)
{
    if (MemData.dData[Operands[0]._.Number] == _or.MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}

//--------------------------------
word BEQ_BBa (union Operand *Operands)
{
    if (MemData.bData[Operands[0]._.Number] == *(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BEQ_WBa (union Operand *Operands)
{
    if (MemData.wData[Operands[0]._.Number] == *(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BEQ_LBa (union Operand *Operands)
{
    if (MemData.lwData[Operands[0]._.Number] == *(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BEQ_DBa (union Operand *Operands)
{
    if (MemData.dData[Operands[0]._.Number] == *(double*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BEQ_BaB (union Operand *Operands)
{
    if (*(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr == *(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BEQ_BaW (union Operand *Operands)
{
    if (*(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr == *(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BEQ_BaL (union Operand *Operands)
{
    if (*(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr == *(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BEQ_BaD (union Operand *Operands)
{
    if (*(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr == *(double*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BEQ_BaB_S (union Operand *Operands)
{
    if (*(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr == _or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BEQ_BaW_S (union Operand *Operands)
{
    if (*(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr == _or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BEQ_BaL_S (union Operand *Operands)
{
    if (*(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr == _or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BEQ_BaD_S (union Operand *Operands)
{
    if (*(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr == _or.MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BEQ_BaB_C (union Operand *Operands)
{
    if (*(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr == Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BEQ_BaW_C (union Operand *Operands)
{
    if (*(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr == Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BEQ_BaL_C (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[2].all<<16)+Operands[1].all;
    if (*(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr == lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}
//--------------------------------
word BEQ_BaD_C (union Operand *Operands)
{
    union str_double d_lax;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[4].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[2].all;
    d_lax.wrd[3] =  Operands[1].all;
#else

    d_lax.wrd[0] =  Operands[1].all;
    d_lax.wrd[1] =  Operands[2].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[4].all;

#endif

    if (*(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr == d_lax.all )
    {
      if (Operands[5].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[5].all;

    }
    return 0;

}
//--------------------------------
word BEQ_BS_S  (union Operand *Operands)
{
    if (_or.MemData.bData[Operands[0]._.Number] == _or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BEQ_WS_S  (union Operand *Operands)
{
    if ( _or.MemData.wData[Operands[0]._.Number]== _or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BEQ_LS_S  (union Operand *Operands)
{
    if (_or.MemData.lwData[Operands[0]._.Number] == _or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BEQ_DS_S  (union Operand *Operands)
{
    if (_or.MemData.dData[Operands[0]._.Number] == _or.MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BEQ_BS_C (union Operand *Operands)
{
    if (_or.MemData.bData[Operands[0]._.Number] == Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BEQ_WS_C (union Operand *Operands)
{
    if (_or.MemData.wData[Operands[0]._.Number] == Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BEQ_LS_C (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[2].all<<16)+Operands[1].all;
    if (_or.MemData.lwData[Operands[0]._.Number] == lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}
//--------------------------------
word BEQ_DS_C (union Operand *Operands)
{
    union str_double d_lax;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[4].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[2].all;
    d_lax.wrd[3] =  Operands[1].all;
#else

    d_lax.wrd[0] =  Operands[1].all;
    d_lax.wrd[1] =  Operands[2].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[4].all;

#endif
    if (_or.MemData.dData[Operands[0]._.Number] == d_lax.all )
    {
      if (Operands[5].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[5].all;

    }
    return 0;

}
word BEQ_BAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.bData[Operands[0]._.Number] ==

    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BEQ_WAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.wData[Operands[0]._.Number]

            ==

    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}
word BEQ_LAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.lwData[Operands[0]._.Number]

            ==

    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}
word BEQ_DAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.dData[Operands[0]._.Number]

            ==

    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}
word BEQ_ArB    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            ==

        MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}
word BEQ_ArW    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            ==

    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}
word BEQ_ArL    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            ==

    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}
word BEQ_ArD    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            ==

    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}
word BEQ_BAr_C  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] ==  Operands[1].all)
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}
word BEQ_WAr_C  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] ==  Operands[1].all)
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}
word BEQ_LAr_C  (union Operand *Operands)
{
    lword lax;
    word out;
     out = 0;
    lax = ((lw)Operands[2].all<<16)+Operands[1].all;
    if (MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] == lax )
    {
      if (Operands[3].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[3].all;
      }

    }
    return out;

}
word BEQ_DAr_C  (union Operand *Operands)
{
    union str_double d_lax;
    word out;
     out = 0;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[4].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[2].all;
    d_lax.wrd[3] =  Operands[1].all;
#else

    d_lax.wrd[0] =  Operands[1].all;
    d_lax.wrd[1] =  Operands[2].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[4].all;

#endif
    if (MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] == d_lax.all )
    {
      if (Operands[5].all > ObjPrgData.Size)
      {
        out = _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[5].all;
      }

    }
    return out;

}
word BEQ_BAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if (MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            == *(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BEQ_WAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if (MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            == *(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}
word BEQ_LAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if (MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            == *(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}
word BEQ_DAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if (MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            == *(d*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}
word BEQ_BAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] == _or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}
word BEQ_WAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] == _or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}
word BEQ_LAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] == _or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}
word BEQ_DAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] == _or.MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

//------Переход, если не равно---------------

word BNE_BB   (union Operand *Operands)
{
    if (MemData.bData[Operands[0]._.Number] != MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BNE_WW   (union Operand *Operands)
{
    if (MemData.wData[Operands[0]._.Number] != MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BNE_LL   (union Operand *Operands)
{
    if (MemData.lwData[Operands[0]._.Number] != MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BNE_DD   (union Operand *Operands)
{
    if (MemData.dData[Operands[0]._.Number] != MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BNE_BC  (union Operand *Operands)
{
    if (MemData.bData[Operands[0]._.Number] != Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BNE_WC  (union Operand *Operands)
{
    if (MemData.wData[Operands[0]._.Number] != Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BNE_LC  (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[2].all<<16)+Operands[1].all;
    if (MemData.lwData[Operands[0]._.Number] != lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}
//--------------------------------
word BNE_DC  (union Operand *Operands)
{
    union str_double d_lax;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[4].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[2].all;
    d_lax.wrd[3] =  Operands[1].all;
#else

    d_lax.wrd[0] =  Operands[1].all;
    d_lax.wrd[1] =  Operands[2].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[4].all;

#endif
    if (MemData.dData[Operands[0]._.Number] != d_lax.all )
    {
      if (Operands[5].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[5].all;

    }
    return 0;

}
//--------------------------------
word BNE_BS  (union Operand *Operands)
{
    if (MemData.bData[Operands[0]._.Number] != _or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BNE_WS  (union Operand *Operands)
{
    if (MemData.wData[Operands[0]._.Number] != _or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BNE_LS  (union Operand *Operands)
{
    if (MemData.lwData[Operands[0]._.Number] != _or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BNE_DS  (union Operand *Operands)
{
    if (MemData.dData[Operands[0]._.Number] != _or.MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}

//--------------------------------
word BNE_BBa (union Operand *Operands)
{
    if (MemData.bData[Operands[0]._.Number] != *(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BNE_WBa (union Operand *Operands)
{
    if (MemData.wData[Operands[0]._.Number] != *(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BNE_LBa (union Operand *Operands)
{
    if (MemData.lwData[Operands[0]._.Number] != *(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}

//--------------------------------
word BNE_DBa (union Operand *Operands)
{
    if (MemData.dData[Operands[0]._.Number] != *(double*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BNE_BaB (union Operand *Operands)
{
    if (*(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr != *(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BNE_BaW (union Operand *Operands)
{
    if (*(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr != *(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BNE_BaL (union Operand *Operands)
{
    if (*(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr != *(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BNE_BaD (union Operand *Operands)
{
    if (*(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr != *(double*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BNE_BaB_S (union Operand *Operands)
{
    if (*(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr != _or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BNE_BaW_S (union Operand *Operands)
{
    if (*(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr != _or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BNE_BaL_S (union Operand *Operands)
{
    if (*(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr != _or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BNE_BaD_S (union Operand *Operands)
{
    if (*(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr != _or.MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BNE_BaB_C (union Operand *Operands)
{
    if (*(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr != Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BNE_BaW_C (union Operand *Operands)
{
    if (*(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr != Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BNE_BaL_C (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[2].all<<16)+Operands[1].all;
    if (*(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr != lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}
//--------------------------------
word BNE_BaD_C (union Operand *Operands)
{
    union str_double d_lax;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[4].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[2].all;
    d_lax.wrd[3] =  Operands[1].all;
#else

    d_lax.wrd[0] =  Operands[1].all;
    d_lax.wrd[1] =  Operands[2].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[4].all;

#endif
    if (*(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr != d_lax.all )
    {
      if (Operands[5].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[5].all;

    }
    return 0;

}
//--------------------------------
word BNE_BS_S  (union Operand *Operands)
{
    if (_or.MemData.bData[Operands[0]._.Number] != _or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BNE_WS_S  (union Operand *Operands)
{
    if ( _or.MemData.wData[Operands[0]._.Number]!= _or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BNE_LS_S  (union Operand *Operands)
{
    if (_or.MemData.lwData[Operands[0]._.Number] != _or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BNE_DS_S  (union Operand *Operands)
{
    if (_or.MemData.dData[Operands[0]._.Number] != _or.MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BNE_BS_C (union Operand *Operands)
{
    if (_or.MemData.bData[Operands[0]._.Number] != Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BNE_WS_C (union Operand *Operands)
{
    if (_or.MemData.wData[Operands[0]._.Number] != Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BNE_LS_C (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[2].all<<16)+Operands[1].all;
    if (_or.MemData.lwData[Operands[0]._.Number] != lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}
//--------------------------------
word BNE_DS_C (union Operand *Operands)
{
    union str_double d_lax;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[4].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[2].all;
    d_lax.wrd[3] =  Operands[1].all;
#else

    d_lax.wrd[0] =  Operands[1].all;
    d_lax.wrd[1] =  Operands[2].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[4].all;

#endif
    if (_or.MemData.dData[Operands[0]._.Number] != d_lax.all )
    {
      if (Operands[5].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[5].all;

    }
    return 0;

}

word BNE_BAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.bData[Operands[0]._.Number] !=

    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BNE_WAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.wData[Operands[0]._.Number]

            !=

    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BNE_LAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.lwData[Operands[0]._.Number]

            !=

    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BNE_DAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.dData[Operands[0]._.Number]

            !=

    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BNE_ArB    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            !=

    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BNE_ArW    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            !=

    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}
word BNE_ArL    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            !=

    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}
word BNE_ArD    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            !=

    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BNE_BAr_C  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            !=  Operands[1].all)
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BNE_WAr_C  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            !=  Operands[1].all)
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BNE_LAr_C  (union Operand *Operands)
{
    lword lax;
    word out;
    out = 0;
    lax = ((lw)Operands[2].all<<16)+Operands[1].all;
    if (MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] != lax )
    {
      if (Operands[3].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[3].all;
      }

    }
    return out;

}

word BNE_DAr_C  (union Operand *Operands)
{
    union str_double d_lax;
    word out;
     out = 0;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[4].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[2].all;
    d_lax.wrd[3] =  Operands[1].all;
#else

    d_lax.wrd[0] =  Operands[1].all;
    d_lax.wrd[1] =  Operands[2].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[4].all;

#endif

    if (MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] != d_lax.all )
    {
      if (Operands[5].all > ObjPrgData.Size)
      {
        out = _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[5].all;
      }

    }
    return out;

}

word BNE_BAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if (MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            != *(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BNE_WAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if (MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            != *(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BNE_LAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if (MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            != *(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BNE_DAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if (MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            != *(d*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BNE_BAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] != _or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BNE_WAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] != _or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BNE_LAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] != _or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BNE_DAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] != _or.MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

//------Переход, если больше---------------

//------С учетом знака------

word BGT_BB   (union Operand *Operands)
{
    if ((sb)MemData.bData[Operands[0]._.Number] > (sb)MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGT_WW   (union Operand *Operands)
{
    if ((sw)MemData.wData[Operands[0]._.Number] > (sw)MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGT_LL   (union Operand *Operands)
{
    if ((slw)MemData.lwData[Operands[0]._.Number] > (slw)MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGT_DD   (union Operand *Operands)
{
    if (MemData.dData[Operands[0]._.Number] > MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGT_BC  (union Operand *Operands)
{
    if ((sb)MemData.bData[Operands[0]._.Number] > (sb)Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGT_WC  (union Operand *Operands)
{
    if ((sw)MemData.wData[Operands[0]._.Number] > (sw)Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGT_LC  (union Operand *Operands)
{
    slword lax;
    lax = ((lw)Operands[2].all<<16)+Operands[1].all;
    if ((slw)MemData.lwData[Operands[0]._.Number] > lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}
//--------------------------------
word BGT_DC  (union Operand *Operands)
{
    union str_double d_lax;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[4].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[2].all;
    d_lax.wrd[3] =  Operands[1].all;
#else

    d_lax.wrd[0] =  Operands[1].all;
    d_lax.wrd[1] =  Operands[2].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[4].all;

#endif

    if (MemData.dData[Operands[0]._.Number] > d_lax.all )
    {
      if (Operands[5].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[5].all;

    }
    return 0;

}
//--------------------------------
word BGT_BS  (union Operand *Operands)
{
    if ((sb)MemData.bData[Operands[0]._.Number] > (sb)_or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGT_WS  (union Operand *Operands)
{
    if ((sw)MemData.wData[Operands[0]._.Number] > (sw)_or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGT_LS  (union Operand *Operands)
{
    if ((slw)MemData.lwData[Operands[0]._.Number] > (slw)_or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGT_DS  (union Operand *Operands)
{
    if (MemData.dData[Operands[0]._.Number] > _or.MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}

//--------------------------------
word BGT_BBa (union Operand *Operands)
{
    if ((sb)MemData.bData[Operands[0]._.Number] > *(sb*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGT_WBa (union Operand *Operands)
{
    if ((sw)MemData.wData[Operands[0]._.Number] > *(sw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGT_LBa (union Operand *Operands)
{
    if ((slw)MemData.lwData[Operands[0]._.Number] > *(slw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGT_DBa (union Operand *Operands)
{
    if (MemData.dData[Operands[0]._.Number] > *(double*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGT_BaB (union Operand *Operands)
{
    if (*(sb*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >  *(sb*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGT_BaW (union Operand *Operands)
{
    if (*(sw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >  *(sw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGT_BaL (union Operand *Operands)
{
    if (*(slw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >  *(slw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGT_BaD (union Operand *Operands)
{
    if (*(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >  *(double*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGT_BaB_S (union Operand *Operands)
{
    if (*(sb*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >  (sb)_or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGT_BaW_S (union Operand *Operands)
{
    if (*(sw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >  (sw)_or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGT_BaL_S (union Operand *Operands)
{
    if (*(slw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >  (slw)_or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGT_BaD_S (union Operand *Operands)
{
    if (*(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >  _or.MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGT_BaB_C (union Operand *Operands)
{
    if (*(sb*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >  (sb)Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGT_BaW_C (union Operand *Operands)
{
    if (*(sw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >  (sw)Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGT_BaL_C (union Operand *Operands)
{
    slword lax;
    lax = ((slw)Operands[2].all<<16)+Operands[1].all;
    if (*(slw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >  lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}
//--------------------------------
word BGT_BaD_C (union Operand *Operands)
{
    union str_double d_lax;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[4].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[2].all;
    d_lax.wrd[3] =  Operands[1].all;
#else

    d_lax.wrd[0] =  Operands[1].all;
    d_lax.wrd[1] =  Operands[2].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[4].all;

#endif
    if (*(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >  d_lax.all )
    {
      if (Operands[5].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[5].all;

    }
    return 0;

}
//--------------------------------
word BGT_BS_S  (union Operand *Operands)
{
    if ((sb)_or.MemData.bData[Operands[0]._.Number] > (sb)_or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGT_WS_S  (union Operand *Operands)
{
    if ( (sw)_or.MemData.wData[Operands[0]._.Number]> (sw)_or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGT_LS_S  (union Operand *Operands)
{
    if ((slw)_or.MemData.lwData[Operands[0]._.Number] > (slw)_or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGT_DS_S  (union Operand *Operands)
{
    if (_or.MemData.dData[Operands[0]._.Number] > _or.MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGT_BS_C (union Operand *Operands)
{
    if ((sb)_or.MemData.bData[Operands[0]._.Number] > (sb)Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGT_WS_C (union Operand *Operands)
{
    if ((sw)_or.MemData.wData[Operands[0]._.Number] > (sw)Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGT_LS_C (union Operand *Operands)
{
    slword lax;
    lax = ((slw)Operands[2].all<<16)+Operands[1].all;
    if ((slw)_or.MemData.lwData[Operands[0]._.Number] > lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}
//--------------------------------
word BGT_DS_C (union Operand *Operands)
{
    union str_double d_lax;
    //Прекладывание double для FR
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[4].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[2].all;
    d_lax.wrd[3] =  Operands[1].all;
#else

    d_lax.wrd[0] =  Operands[1].all;
    d_lax.wrd[1] =  Operands[2].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[4].all;

#endif
    if (_or.MemData.dData[Operands[0]._.Number] > d_lax.all )
    {
      if (Operands[5].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[5].all;

    }
    return 0;

}
word BGT_BAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sb)MemData.bData[Operands[0]._.Number] >

    (sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGT_WAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sw)MemData.wData[Operands[0]._.Number]

            >

    (sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGT_LAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if ((slw)MemData.lwData[Operands[0]._.Number]

            >

    (slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGT_DAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.dData[Operands[0]._.Number]

            >

    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGT_ArB    (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            >

    (sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGT_ArW    (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            >

    (sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}
word BGT_ArL    (union Operand *Operands)
{
    word out;
    out = 0;
    if ((slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            >

    (slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}
word BGT_ArD    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            >

    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGT_BAr_C  (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            >  (sb)Operands[1].all)
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGT_WAr_C  (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            >  (sw)Operands[1].all)
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGT_LAr_C  (union Operand *Operands)
{
    slword lax;
    word out;
     out = 0;
    lax = ((slw)(sw)Operands[2].all<<16)+(sw)Operands[1].all;
    if ((slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] > lax )
    {
      if (Operands[3].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[3].all;
      }

    }
    return out;

}

word BGT_DAr_C  (union Operand *Operands)
{
    union str_double d_lax;
    word out;
     out = 0;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[4].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[2].all;
    d_lax.wrd[3] =  Operands[1].all;
#else

    d_lax.wrd[0] =  Operands[1].all;
    d_lax.wrd[1] =  Operands[2].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[4].all;

#endif

    if (MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] > d_lax.all )
    {
      if (Operands[5].all > ObjPrgData.Size)
      {
        out = _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[5].all;
      }

    }
    return out;

}

word BGT_BAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if ((sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            > *(sb*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BGT_WAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if ((sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            > *(sw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BGT_LAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if ((slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            > *(slw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BGT_DAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if (MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            > *(d*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BGT_BAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] > (sb)_or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGT_WAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] > (sw)_or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGT_LAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if ((slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] > (slw)_or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGT_DAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] > _or.MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

//------Без учета знака------

word BGTU_BB   (union Operand *Operands)
{
    if (MemData.bData[Operands[0]._.Number] > MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGTU_WW   (union Operand *Operands)
{
    if (MemData.wData[Operands[0]._.Number] > MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGTU_LL   (union Operand *Operands)
{
    if (MemData.lwData[Operands[0]._.Number] > MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGTU_BC  (union Operand *Operands)
{
    if (MemData.bData[Operands[0]._.Number] > Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGTU_WC  (union Operand *Operands)
{
    if (MemData.wData[Operands[0]._.Number] > Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGTU_LC  (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[2].all<<16)+Operands[1].all;
    if (MemData.lwData[Operands[0]._.Number] > lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}
//--------------------------------
word BGTU_BS  (union Operand *Operands)
{
    if (MemData.bData[Operands[0]._.Number] > _or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGTU_WS  (union Operand *Operands)
{
    if (MemData.wData[Operands[0]._.Number] > _or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGTU_LS  (union Operand *Operands)
{
    if (MemData.lwData[Operands[0]._.Number] > _or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}

//--------------------------------
word BGTU_BBa (union Operand *Operands)
{
    if (MemData.bData[Operands[0]._.Number] > *(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGTU_WBa (union Operand *Operands)
{
    if (MemData.wData[Operands[0]._.Number] > *(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGTU_LBa (union Operand *Operands)
{
    if (MemData.lwData[Operands[0]._.Number] > *(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGTU_BaB (union Operand *Operands)
{
    if (*(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >  *(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGTU_BaW (union Operand *Operands)
{
    if (*(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >  *(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGTU_BaL (union Operand *Operands)
{
    if (*(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >  *(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGTU_BaB_S (union Operand *Operands)
{
    if (*(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >  _or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGTU_BaW_S (union Operand *Operands)
{
    if (*(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >  _or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGTU_BaL_S (union Operand *Operands)
{
    if (*(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >  _or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGTU_BaB_C (union Operand *Operands)
{
    if (*(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >  Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGTU_BaW_C (union Operand *Operands)
{
    if (*(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >  Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGTU_BaL_C (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[2].all<<16)+Operands[1].all;
    if (*(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >  lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}

//--------------------------------
word BGTU_BS_S  (union Operand *Operands)
{
    if (_or.MemData.bData[Operands[0]._.Number] > _or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGTU_WS_S  (union Operand *Operands)
{
    if ( _or.MemData.wData[Operands[0]._.Number]> _or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGTU_LS_S  (union Operand *Operands)
{
    if (_or.MemData.lwData[Operands[0]._.Number] > _or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGTU_BS_C (union Operand *Operands)
{
    if (_or.MemData.bData[Operands[0]._.Number] > Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGTU_WS_C (union Operand *Operands)
{
    if (_or.MemData.wData[Operands[0]._.Number] > Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGTU_LS_C (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[2].all<<16)+Operands[1].all;
    if (_or.MemData.lwData[Operands[0]._.Number] > lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}

word BGTU_BAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.bData[Operands[0]._.Number] >

    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGTU_WAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.wData[Operands[0]._.Number]

            >

    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGTU_LAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.lwData[Operands[0]._.Number]

            >

    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGTU_ArB    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            >

    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGTU_ArW    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            >

    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}
word BGTU_ArL    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            >

    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGTU_BAr_C  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] >  Operands[1].all)
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGTU_WAr_C  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] >  Operands[1].all)
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGTU_LAr_C  (union Operand *Operands)
{
    lword lax;
    word out;
     out = 0;
    lax = ((lw)Operands[2].all<<16)+Operands[1].all;
    if (MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] > lax )
    {
      if (Operands[3].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[3].all;
      }

    }
    return out;

}

word BGTU_BAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if (MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            > *(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BGTU_WAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if (MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            > *(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BGTU_LAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if (MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            > *(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BGTU_BAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            > _or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGTU_WAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            > _or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGTU_LAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            > _or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

//------Переход, если меньше---------------

//------С учетом знака------

word BLT_BB   (union Operand *Operands)
{
    if ((sb)MemData.bData[Operands[0]._.Number] < (sb)MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLT_WW   (union Operand *Operands)
{
    if ((sw)MemData.wData[Operands[0]._.Number] < (sw)MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLT_LL   (union Operand *Operands)
{
    if ((slw)MemData.lwData[Operands[0]._.Number] < (slw)MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}

//--------------------------------
word BLT_DD   (union Operand *Operands)
{
    if (MemData.dData[Operands[0]._.Number] < MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLT_BC  (union Operand *Operands)
{
    if ((sb)MemData.bData[Operands[0]._.Number] < (sb)Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLT_WC  (union Operand *Operands)
{
    if ((sw)MemData.wData[Operands[0]._.Number] < (sw)Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLT_LC  (union Operand *Operands)
{
    slword lax;
    lax = ((lw)Operands[2].all<<16)+Operands[1].all;
    if ((slw)MemData.lwData[Operands[0]._.Number] < lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}
//--------------------------------
word BLT_DC  (union Operand *Operands)
{
    union str_double d_lax;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[4].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[2].all;
    d_lax.wrd[3] =  Operands[1].all;
#else

    d_lax.wrd[0] =  Operands[1].all;
    d_lax.wrd[1] =  Operands[2].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[4].all;

#endif
    if (MemData.dData[Operands[0]._.Number] < d_lax.all )
    {
      if (Operands[5].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[5].all;

    }
    return 0;

}
//--------------------------------
word BLT_BS  (union Operand *Operands)
{
    if ((sb)MemData.bData[Operands[0]._.Number] < (sb)_or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLT_WS  (union Operand *Operands)
{
    if ((sw)MemData.wData[Operands[0]._.Number] < (sw)_or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLT_LS  (union Operand *Operands)
{
    if ((slw)MemData.lwData[Operands[0]._.Number] < (slw)_or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLT_DS  (union Operand *Operands)
{
    if (MemData.dData[Operands[0]._.Number] < _or.MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}

//--------------------------------
word BLT_BBa (union Operand *Operands)
{
    if ((sb)MemData.bData[Operands[0]._.Number] < *(sb*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLT_WBa (union Operand *Operands)
{
    if ((sw)MemData.wData[Operands[0]._.Number] < *(sw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLT_LBa (union Operand *Operands)
{
    if ((slw)MemData.lwData[Operands[0]._.Number] < *(slw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLT_DBa (union Operand *Operands)
{
    if (MemData.dData[Operands[0]._.Number] < *(double*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLT_BaB (union Operand *Operands)
{
    if (*(sb*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <  *(sb*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLT_BaW (union Operand *Operands)
{
    if (*(sw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <  *(sw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLT_BaL (union Operand *Operands)
{
    if (*(slw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <  *(slw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLT_BaD (union Operand *Operands)
{
    if (*(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <  *(double*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLT_BaB_S (union Operand *Operands)
{
    if (*(sb*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <  (sb)_or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLT_BaW_S (union Operand *Operands)
{
    if (*(sw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <  (sw)_or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLT_BaL_S (union Operand *Operands)
{
    if (*(slw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <  (slw)_or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLT_BaD_S (union Operand *Operands)
{
    if (*(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <  _or.MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLT_BaB_C (union Operand *Operands)
{
    if (*(sb*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <  (sb)Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLT_BaW_C (union Operand *Operands)
{
    if (*(sw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <  (sw)Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLT_BaL_C (union Operand *Operands)
{
    slword lax;
    lax = ((slw)Operands[2].all<<16)+Operands[1].all;
    if (*(slw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <  lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}
//--------------------------------
word BLT_BaD_C (union Operand *Operands)
{
    union str_double d_lax;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[4].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[2].all;
    d_lax.wrd[3] =  Operands[1].all;
#else

    d_lax.wrd[0] =  Operands[1].all;
    d_lax.wrd[1] =  Operands[2].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[4].all;

#endif
    if (*(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <  d_lax.all )
    {
      if (Operands[5].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[5].all;

    }
    return 0;

}
//--------------------------------
word BLT_BS_S  (union Operand *Operands)
{
    if ((sb)_or.MemData.bData[Operands[0]._.Number] < (sb)_or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLT_WS_S  (union Operand *Operands)
{
    if ( (sw)_or.MemData.wData[Operands[0]._.Number]< (sw)_or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLT_LS_S  (union Operand *Operands)
{
    if ((slw)_or.MemData.lwData[Operands[0]._.Number] < (slw)_or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLT_DS_S  (union Operand *Operands)
{
    if (_or.MemData.dData[Operands[0]._.Number] < _or.MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLT_BS_C (union Operand *Operands)
{
    if ((sb)_or.MemData.bData[Operands[0]._.Number] < (sb)Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLT_WS_C (union Operand *Operands)
{
    if ((sw)_or.MemData.wData[Operands[0]._.Number] < (sw)Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLT_LS_C (union Operand *Operands)
{
    slword lax;
    lax = ((slw)Operands[2].all<<16)+Operands[1].all;
    if ((slw)_or.MemData.lwData[Operands[0]._.Number] < lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}
//--------------------------------
word BLT_DS_C (union Operand *Operands)
{
    union str_double d_lax;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[4].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[2].all;
    d_lax.wrd[3] =  Operands[1].all;
#else

    d_lax.wrd[0] =  Operands[1].all;
    d_lax.wrd[1] =  Operands[2].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[4].all;

#endif
    if (_or.MemData.dData[Operands[0]._.Number] < d_lax.all )
    {
      if (Operands[5].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[5].all;

    }
    return 0;

}

word BLT_BAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sb)MemData.bData[Operands[0]._.Number] <

    (sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLT_WAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sw)MemData.wData[Operands[0]._.Number]

            <

    (sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLT_LAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if ((slw)MemData.lwData[Operands[0]._.Number]

            <

    (slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLT_DAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.dData[Operands[0]._.Number]

            <

    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLT_ArB    (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            <

    (sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLT_ArW    (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            <

    (sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}
word BLT_ArL    (union Operand *Operands)
{
    word out;
    out = 0;
    if ((slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            <

    (slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}
word BLT_ArD    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            <

    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLT_BAr_C  (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            <  (sb)Operands[1].all)
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLT_WAr_C  (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            <  (sw)Operands[1].all)
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLT_LAr_C  (union Operand *Operands)
{
    slword lax;
    word out;
     out = 0;
    lax = ((slw)(sw)Operands[2].all<<16)+(sw)Operands[1].all;
    if ((slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] < lax )
    {
      if (Operands[3].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[3].all;
      }

    }
    return out;

}

word BLT_DAr_C  (union Operand *Operands)
{
    union str_double d_lax;
    word out;
     out = 0;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[4].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[2].all;
    d_lax.wrd[3] =  Operands[1].all;
#else

    d_lax.wrd[0] =  Operands[1].all;
    d_lax.wrd[1] =  Operands[2].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[4].all;

#endif

    if (MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] < d_lax.all )
    {
      if (Operands[5].all > ObjPrgData.Size)
      {
        out = _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[5].all;
      }

    }
    return out;

}

word BLT_BAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if ((sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            < *(sb*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BLT_WAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if ((sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            < *(sw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BLT_LAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if ((slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            < *(slw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BLT_DAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if (MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            < *(d*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BLT_BAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            < (sb)_or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLT_WAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            < (sw)_or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLT_LAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if ((slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            < (slw)_or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLT_DAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            < _or.MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

//------Без учета знака------

word BLTU_BB   (union Operand *Operands)
{
    if (MemData.bData[Operands[0]._.Number] < MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLTU_WW   (union Operand *Operands)
{
    if (MemData.wData[Operands[0]._.Number] < MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLTU_LL   (union Operand *Operands)
{
    if (MemData.lwData[Operands[0]._.Number] < MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLTU_BC  (union Operand *Operands)
{
    if (MemData.bData[Operands[0]._.Number] < Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLTU_WC  (union Operand *Operands)
{
    if (MemData.wData[Operands[0]._.Number] < Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLTU_LC  (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[2].all<<16)+Operands[1].all;
    if (MemData.lwData[Operands[0]._.Number] < lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}
//--------------------------------
word BLTU_BS  (union Operand *Operands)
{
    if (MemData.bData[Operands[0]._.Number] < _or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLTU_WS  (union Operand *Operands)
{
    if (MemData.wData[Operands[0]._.Number] < _or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLTU_LS  (union Operand *Operands)
{
    if (MemData.lwData[Operands[0]._.Number] < _or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}

//--------------------------------
word BLTU_BBa (union Operand *Operands)
{
    if (MemData.bData[Operands[0]._.Number] < *(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLTU_WBa (union Operand *Operands)
{
    if (MemData.wData[Operands[0]._.Number] < *(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLTU_LBa (union Operand *Operands)
{
    if (MemData.lwData[Operands[0]._.Number] < *(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLTU_BaB (union Operand *Operands)
{
    if (*(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <  *(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLTU_BaW (union Operand *Operands)
{
    if (*(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <  *(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLTU_BaL (union Operand *Operands)
{
    if (*(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <  *(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLTU_BaB_S (union Operand *Operands)
{
    if (*(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <  _or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLTU_BaW_S (union Operand *Operands)
{
    if (*(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <  _or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLTU_BaL_S (union Operand *Operands)
{
    if (*(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <  _or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLTU_BaB_C (union Operand *Operands)
{
    if (*(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <  Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLTU_BaW_C (union Operand *Operands)
{
    if (*(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <  Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLTU_BaL_C (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[2].all<<16)+Operands[1].all;
    if (*(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <  lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}
//--------------------------------
word BLTU_BS_S  (union Operand *Operands)
{
    if (_or.MemData.bData[Operands[0]._.Number] < _or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLTU_WS_S  (union Operand *Operands)
{
    if ( _or.MemData.wData[Operands[0]._.Number]< _or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLTU_LS_S  (union Operand *Operands)
{
    if (_or.MemData.lwData[Operands[0]._.Number] < _or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLTU_BS_C (union Operand *Operands)
{
    if (_or.MemData.bData[Operands[0]._.Number] < Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLTU_WS_C (union Operand *Operands)
{
    if (_or.MemData.wData[Operands[0]._.Number] < Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLTU_LS_C (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[2].all<<16)+Operands[1].all;
    if (_or.MemData.lwData[Operands[0]._.Number] < lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}

word BLTU_BAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.bData[Operands[0]._.Number] <

    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLTU_WAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.wData[Operands[0]._.Number]

            <

    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLTU_LAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.lwData[Operands[0]._.Number]

            <

    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLTU_ArB    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            <

    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLTU_ArW    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            <

    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}
word BLTU_ArL    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            <

    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLTU_BAr_C  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] <  Operands[1].all)
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLTU_WAr_C  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] <  Operands[1].all)
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLTU_LAr_C  (union Operand *Operands)
{
    lword lax;
    word out;
     out = 0;
    lax = ((lw)Operands[2].all<<16)+Operands[1].all;
    if (MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] < lax )
    {
      if (Operands[3].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[3].all;
      }

    }
    return out;

}

word BLTU_BAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if (MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            < *(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BLTU_WAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if (MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            < *(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BLTU_LAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if (MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            < *(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BLTU_BAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            < _or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLTU_WAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] < _or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLTU_LAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] < _or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

//------Переход, если больше или равно---------------

//------С учетом знака------

word BGE_BB   (union Operand *Operands)
{
    if ((sb)MemData.bData[Operands[0]._.Number] >= (sb)MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGE_WW   (union Operand *Operands)
{
    if ((sw)MemData.wData[Operands[0]._.Number] >= (sw)MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGE_LL   (union Operand *Operands)
{
    if ((slw)MemData.lwData[Operands[0]._.Number] >= (slw)MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGE_DD   (union Operand *Operands)
{
    if (MemData.dData[Operands[0]._.Number] >= MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGE_BC  (union Operand *Operands)
{
    if ((sb)MemData.bData[Operands[0]._.Number] >= (sb)Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGE_WC  (union Operand *Operands)
{
    if ((sw)MemData.wData[Operands[0]._.Number] >= (sw)Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGE_LC  (union Operand *Operands)
{
    slword lax;
    lax = ((lw)Operands[2].all<<16)+Operands[1].all;
    if ((slw)MemData.lwData[Operands[0]._.Number] >= lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}
//--------------------------------
word BGE_DC  (union Operand *Operands)
{
    union str_double d_lax;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[4].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[2].all;
    d_lax.wrd[3] =  Operands[1].all;
#else

    d_lax.wrd[0] =  Operands[1].all;
    d_lax.wrd[1] =  Operands[2].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[4].all;

#endif
    if (MemData.dData[Operands[0]._.Number] >= d_lax.all )
    {
      if (Operands[5].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[5].all;

    }
    return 0;

}
//--------------------------------
word BGE_BS  (union Operand *Operands)
{
    if ((sb)MemData.bData[Operands[0]._.Number] >= (sb)_or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGE_WS  (union Operand *Operands)
{
    if ((sw)MemData.wData[Operands[0]._.Number] >= (sw)_or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}

//--------------------------------
word BGE_LS  (union Operand *Operands)
{
    if ((slw)MemData.lwData[Operands[0]._.Number] >= (slw)_or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGE_DS  (union Operand *Operands)
{
    if (MemData.dData[Operands[0]._.Number] >= _or.MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}

//--------------------------------
word BGE_BBa (union Operand *Operands)
{
    if ((sb)MemData.bData[Operands[0]._.Number] >= *(sb*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGE_WBa (union Operand *Operands)
{
    if ((sw)MemData.wData[Operands[0]._.Number] >= *(sw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGE_LBa (union Operand *Operands)
{
    if ((slw)MemData.lwData[Operands[0]._.Number] >= *(slw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGE_DBa (union Operand *Operands)
{
    if (MemData.dData[Operands[0]._.Number] >= *(double*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGE_BaB (union Operand *Operands)
{
    if (*(sb*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >= *(sb*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGE_BaW (union Operand *Operands)
{
    if (*(sw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >= *(sw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGE_BaL (union Operand *Operands)
{
    if (*(slw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >= *(slw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGE_BaD (union Operand *Operands)
{
    if (*(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >= *(double*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGE_BaB_S (union Operand *Operands)
{
    if (*(sb*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >= (sb)_or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGE_BaW_S (union Operand *Operands)
{
    if (*(sw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >= (sw)_or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGE_BaL_S (union Operand *Operands)
{
    if (*(slw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >= (slw)_or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGE_BaD_S (union Operand *Operands)
{
    if (*(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >= _or.MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGE_BaB_C (union Operand *Operands)
{
    if (*(sb*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >= (sb)Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGE_BaW_C (union Operand *Operands)
{
    if (*(sw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >= (sw)Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGE_BaL_C (union Operand *Operands)
{
    slword lax;
    lax = ((slw)Operands[2].all<<16)+Operands[1].all;
    if (*(slw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >= lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}
//--------------------------------
word BGE_BaD_C (union Operand *Operands)
{
    union str_double d_lax;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[4].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[2].all;
    d_lax.wrd[3] =  Operands[1].all;
#else

    d_lax.wrd[0] =  Operands[1].all;
    d_lax.wrd[1] =  Operands[2].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[4].all;

#endif
    if (*(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >= d_lax.all )
    {
      if (Operands[5].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[5].all;

    }
    return 0;

}
//--------------------------------
word BGE_BS_S  (union Operand *Operands)
{
    if ((sb)_or.MemData.bData[Operands[0]._.Number] >= (sb)_or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGE_WS_S  (union Operand *Operands)
{
    if ( (sw)_or.MemData.wData[Operands[0]._.Number]>= (sw)_or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGE_LS_S  (union Operand *Operands)
{
    if ((slw)_or.MemData.lwData[Operands[0]._.Number] >= (slw)_or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGE_DS_S  (union Operand *Operands)
{
    if (_or.MemData.dData[Operands[0]._.Number] >= _or.MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGE_BS_C (union Operand *Operands)
{
    if ((sb)_or.MemData.bData[Operands[0]._.Number] >= (sb)Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGE_WS_C (union Operand *Operands)
{
    if ((sw)_or.MemData.wData[Operands[0]._.Number] >= (sw)Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGE_LS_C (union Operand *Operands)
{
    slword lax;
    lax = ((slw)Operands[2].all<<16)+Operands[1].all;
    if ((slw)_or.MemData.lwData[Operands[0]._.Number] >= lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}
//--------------------------------
word BGE_DS_C (union Operand *Operands)
{
    union str_double d_lax;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[4].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[2].all;
    d_lax.wrd[3] =  Operands[1].all;
#else

    d_lax.wrd[0] =  Operands[1].all;
    d_lax.wrd[1] =  Operands[2].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[4].all;

#endif
    if (_or.MemData.dData[Operands[0]._.Number] >= d_lax.all )
    {
      if (Operands[5].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[5].all;

    }
    return 0;

}

word BGE_BAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sb)MemData.bData[Operands[0]._.Number] >=

    (sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGE_WAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sw)MemData.wData[Operands[0]._.Number]

            >=

    (sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGE_LAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if ((slw)MemData.lwData[Operands[0]._.Number]

            >=

    (slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGE_DAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.dData[Operands[0]._.Number]

            >=

    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGE_ArB    (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            >=

    (sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGE_ArW    (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            >=

    (sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}
word BGE_ArL    (union Operand *Operands)
{
    word out;
    out = 0;
    if ((slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            >=

    (slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}
word BGE_ArD    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            >=

    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGE_BAr_C  (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            >=  (sb)Operands[1].all)
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGE_WAr_C  (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            >=  (sw)Operands[1].all)
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGE_LAr_C  (union Operand *Operands)
{
    slword lax;
    word out;
     out = 0;
    lax = ((slw)(sw)Operands[2].all>>16)+(sw)Operands[1].all;
    if ((slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] >= lax )
    {
      if (Operands[3].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[3].all;
      }

    }
    return out;

}

word BGE_DAr_C  (union Operand *Operands)
{
    union str_double d_lax;
    word out;
     out = 0;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[4].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[2].all;
    d_lax.wrd[3] =  Operands[1].all;
#else

    d_lax.wrd[0] =  Operands[1].all;
    d_lax.wrd[1] =  Operands[2].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[4].all;

#endif

    if (MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] >= d_lax.all )
    {
      if (Operands[5].all > ObjPrgData.Size)
      {
        out = _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[5].all;
      }

    }
    return out;

}

word BGE_BAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if ((sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            >= *(sb*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BGE_WAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if ((sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            >= *(sw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BGE_LAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if ((slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            >= *(slw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BGE_DAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if (MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            >= *(d*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BGE_BAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            >= (sb)_or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGE_WAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            >= (sw)_or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGE_LAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if ((slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            >= (slw)_or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGE_DAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            >= _or.MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}
//------Без учета знака------

word BGEU_BB   (union Operand *Operands)
{
    if (MemData.bData[Operands[0]._.Number] >= MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGEU_WW   (union Operand *Operands)
{
    if (MemData.wData[Operands[0]._.Number] >= MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGEU_LL   (union Operand *Operands)
{
    if (MemData.lwData[Operands[0]._.Number] >= MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGEU_BC  (union Operand *Operands)
{
    if (MemData.bData[Operands[0]._.Number] >= Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGEU_WC  (union Operand *Operands)
{
    if (MemData.wData[Operands[0]._.Number] >= Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGEU_LC  (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[2].all<<16)+Operands[1].all;
    if (MemData.lwData[Operands[0]._.Number] >= lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}
//--------------------------------
word BGEU_BS  (union Operand *Operands)
{
    if (MemData.bData[Operands[0]._.Number] >= _or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGEU_WS  (union Operand *Operands)
{
    if (MemData.wData[Operands[0]._.Number] >= _or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGEU_LS  (union Operand *Operands)
{
    if (MemData.lwData[Operands[0]._.Number] >= _or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}

//--------------------------------
word BGEU_BBa (union Operand *Operands)
{
    if (MemData.bData[Operands[0]._.Number] >= *(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGEU_WBa (union Operand *Operands)
{
    if (MemData.wData[Operands[0]._.Number] >= *(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGEU_LBa (union Operand *Operands)
{
    if (MemData.lwData[Operands[0]._.Number] >= *(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}

//--------------------------------
word BGEU_BaB (union Operand *Operands)
{
    if (*(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >= *(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGEU_BaW (union Operand *Operands)
{
    if (*(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >= *(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGEU_BaL (union Operand *Operands)
{
    if (*(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >= *(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGEU_BaB_S (union Operand *Operands)
{
    if (*(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >= _or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGEU_BaW_S (union Operand *Operands)
{
    if (*(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >= _or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGEU_BaL_S (union Operand *Operands)
{
    if (*(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >= _or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGEU_BaB_C (union Operand *Operands)
{
    if (*(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >= Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGEU_BaW_C (union Operand *Operands)
{
    if (*(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >= Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGEU_BaL_C (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[2].all<<16)+Operands[1].all;
    if (*(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr >= lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}
//--------------------------------
word BGEU_BS_S  (union Operand *Operands)
{
    if (_or.MemData.bData[Operands[0]._.Number] >= _or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGEU_WS_S  (union Operand *Operands)
{
    if ( _or.MemData.wData[Operands[0]._.Number]>= _or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGEU_LS_S  (union Operand *Operands)
{
    if (_or.MemData.lwData[Operands[0]._.Number] >= _or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGEU_BS_C (union Operand *Operands)
{
    if (_or.MemData.bData[Operands[0]._.Number] >= Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGEU_WS_C (union Operand *Operands)
{
    if (_or.MemData.wData[Operands[0]._.Number] >= Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BGEU_LS_C (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[2].all<<16)+Operands[1].all;
    if (_or.MemData.lwData[Operands[0]._.Number] >= lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}

word BGEU_BAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.bData[Operands[0]._.Number] >=

    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGEU_WAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.wData[Operands[0]._.Number]

            >=

    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGEU_LAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.lwData[Operands[0]._.Number]

            >=

    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGEU_ArB    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            >=

    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGEU_ArW    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            >=

    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}
word BGEU_ArL    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            >=

    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGEU_BAr_C  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            >=  Operands[1].all)
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGEU_WAr_C  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            >=  Operands[1].all)
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGEU_LAr_C  (union Operand *Operands)
{
    lword lax;
    word out;
     out = 0;
    lax = ((lw)Operands[2].all>>16)+Operands[1].all;
    if (MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] >= lax )
    {
      if (Operands[3].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[3].all;
      }

    }
    return out;

}

word BGEU_BAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if (MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            >= *(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BGEU_WAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if (MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            >= *(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BGEU_LAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if (MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            >= *(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BGEU_BAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] >= _or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGEU_WAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] >= _or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BGEU_LAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] >= _or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

//------Переход, если меньше или равно---------------

//------С учетом знака------

word BLE_BB   (union Operand *Operands)
{
    if ((sb)MemData.bData[Operands[0]._.Number] <= (sb)MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLE_WW   (union Operand *Operands)
{
    if ((sw)MemData.wData[Operands[0]._.Number] <= (sw)MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLE_LL   (union Operand *Operands)
{
    if ((slw)MemData.lwData[Operands[0]._.Number] <= (slw)MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLE_DD   (union Operand *Operands)
{
    if (MemData.dData[Operands[0]._.Number] <= MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLE_BC  (union Operand *Operands)
{
    if ((sb)MemData.bData[Operands[0]._.Number] <= (sb)Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLE_WC  (union Operand *Operands)
{
    if ((sw)MemData.wData[Operands[0]._.Number] <= (sw)Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLE_LC  (union Operand *Operands)
{
    slword lax;
    lax = ((lw)Operands[2].all<<16)+Operands[1].all;
    if ((slw)MemData.lwData[Operands[0]._.Number] <= lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}
//--------------------------------
word BLE_DC  (union Operand *Operands)
{
    union str_double d_lax;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[4].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[2].all;
    d_lax.wrd[3] =  Operands[1].all;
#else

    d_lax.wrd[0] =  Operands[1].all;
    d_lax.wrd[1] =  Operands[2].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[4].all;

#endif

    if (MemData.dData[Operands[0]._.Number] <= d_lax.all )
    {
      if (Operands[5].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[5].all;

    }
    return 0;

}
//--------------------------------
word BLE_BS  (union Operand *Operands)
{
    if ((sb)MemData.bData[Operands[0]._.Number] <= (sb)_or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLE_WS  (union Operand *Operands)
{
    if ((sw)MemData.wData[Operands[0]._.Number] <= (sw)_or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLE_LS  (union Operand *Operands)
{
    if ((slw)MemData.lwData[Operands[0]._.Number] <= (slw)_or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLE_DS  (union Operand *Operands)
{
    if (MemData.dData[Operands[0]._.Number] <= _or.MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}

//--------------------------------
word BLE_BBa (union Operand *Operands)
{
    if ((sb)MemData.bData[Operands[0]._.Number] <= *(sb*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLE_WBa (union Operand *Operands)
{
    if ((sw)MemData.wData[Operands[0]._.Number] <= *(sw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLE_LBa (union Operand *Operands)
{
    if ((slw)MemData.lwData[Operands[0]._.Number] <= *(slw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLE_DBa (union Operand *Operands)
{
    if (MemData.dData[Operands[0]._.Number] <= *(double*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLE_BaB (union Operand *Operands)
{
    if (*(sb*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <= *(sb*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLE_BaW (union Operand *Operands)
{
    if (*(sw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <= *(sw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLE_BaL (union Operand *Operands)
{
    if (*(slw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <= *(slw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLE_BaD (union Operand *Operands)
{
    if (*(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <= *(double*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLE_BaB_S (union Operand *Operands)
{
    if (*(sb*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <= (sb)_or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLE_BaW_S (union Operand *Operands)
{
    if (*(sw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <= (sw)_or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLE_BaL_S (union Operand *Operands)
{
    if (*(slw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <= (slw)_or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLE_BaD_S (union Operand *Operands)
{
    if (*(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <= _or.MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLE_BaB_C (union Operand *Operands)
{
    if (*(sb*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <= (sb)Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLE_BaW_C (union Operand *Operands)
{
    if (*(sw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <= (sw)Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLE_BaL_C (union Operand *Operands)
{
    slword lax;
    lax = ((slw)Operands[2].all<<16)+Operands[1].all;
    if (*(slw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <= lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}
//--------------------------------
word BLE_BaD_C (union Operand *Operands)
{
    union str_double d_lax;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[4].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[2].all;
    d_lax.wrd[3] =  Operands[1].all;
#else

    d_lax.wrd[0] =  Operands[1].all;
    d_lax.wrd[1] =  Operands[2].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[4].all;

#endif
    if (*(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <= d_lax.all )
    {
      if (Operands[5].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[5].all;

    }
    return 0;

}
//--------------------------------
word BLE_BS_S  (union Operand *Operands)
{
    if ((sb)_or.MemData.bData[Operands[0]._.Number] <= (sb)_or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLE_WS_S  (union Operand *Operands)
{
    if ( (sw)_or.MemData.wData[Operands[0]._.Number]<= (sw)_or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLE_LS_S  (union Operand *Operands)
{
    if ((slw)_or.MemData.lwData[Operands[0]._.Number] <= (slw)_or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLE_DS_S  (union Operand *Operands)
{
    if (_or.MemData.dData[Operands[0]._.Number] <= _or.MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLE_BS_C (union Operand *Operands)
{
    if ((sb)_or.MemData.bData[Operands[0]._.Number] <= (sb)Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLE_WS_C (union Operand *Operands)
{
    if ((sw)_or.MemData.wData[Operands[0]._.Number] <= (sw)Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLE_LS_C (union Operand *Operands)
{
    slword lax;
    lax = ((slw)Operands[2].all<<16)+Operands[1].all;
    if ((slw)_or.MemData.lwData[Operands[0]._.Number] <= lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}
//--------------------------------
word BLE_DS_C (union Operand *Operands)
{
    union str_double d_lax;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[4].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[2].all;
    d_lax.wrd[3] =  Operands[1].all;
#else

    d_lax.wrd[0] =  Operands[1].all;
    d_lax.wrd[1] =  Operands[2].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[4].all;

#endif
    if (_or.MemData.dData[Operands[0]._.Number] <= d_lax.all )
    {
      if (Operands[5].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[5].all;

    }
    return 0;

}

word BLE_BAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sb)MemData.bData[Operands[0]._.Number] <=

    (sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLE_WAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sw)MemData.wData[Operands[0]._.Number]

            <=

    (sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLE_LAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if ((slw)MemData.lwData[Operands[0]._.Number]

            <=

    (slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLE_DAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.dData[Operands[0]._.Number]

            <=

    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLE_ArB    (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            <=

    (sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLE_ArW    (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            <=

    (sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}
word BLE_ArL    (union Operand *Operands)
{
    word out;
    out = 0;
    if ((slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            <=

    (slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}
word BLE_ArD    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            <=

    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLE_BAr_C  (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            <=  (sb)Operands[1].all)
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLE_WAr_C  (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            <=  (sw)Operands[1].all)
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLE_LAr_C  (union Operand *Operands)
{
    slword lax;
    word out;
     out = 0;
    lax = ((slw)(sw)Operands[2].all<<16)+(sw)Operands[1].all;
    if ((slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            <= lax )
    {
      if (Operands[3].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[3].all;
      }

    }
    return out;

}

word BLE_DAr_C  (union Operand *Operands)
{
    union str_double d_lax;
    word out;
     out = 0;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[4].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[2].all;
    d_lax.wrd[3] =  Operands[1].all;
#else

    d_lax.wrd[0] =  Operands[1].all;
    d_lax.wrd[1] =  Operands[2].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[4].all;

#endif

    if (MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] <= d_lax.all )
    {
      if (Operands[5].all > ObjPrgData.Size)
      {
        out = _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[5].all;
      }

    }
    return out;

}

word BLE_BAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if ((sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            <= *(sb*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BLE_WAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if ((sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            <= *(sw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BLE_LAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if ((slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            <= *(slw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BLE_DAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if (MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            <= *(d*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BLE_BAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            <= (sb)_or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLE_WAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if ((sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            <= (sw)_or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLE_LAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if ((slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            <= (slw)_or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLE_DAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] <= _or.MemData.dData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

//------Без учета знака------

word BLEU_BB   (union Operand *Operands)
{
    if (MemData.bData[Operands[0]._.Number] <= MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLEU_WW   (union Operand *Operands)
{
    if (MemData.wData[Operands[0]._.Number] <= MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLEU_LL   (union Operand *Operands)
{
    if (MemData.lwData[Operands[0]._.Number] <= MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLEU_BC  (union Operand *Operands)
{
    if (MemData.bData[Operands[0]._.Number] <= Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLEU_WC  (union Operand *Operands)
{
    if (MemData.wData[Operands[0]._.Number] <= Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLEU_LC  (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[2].all<<16)+Operands[1].all;
    if (MemData.lwData[Operands[0]._.Number] <= lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}
//--------------------------------
word BLEU_BS  (union Operand *Operands)
{
    if (MemData.bData[Operands[0]._.Number] <= _or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLEU_WS  (union Operand *Operands)
{
    if (MemData.wData[Operands[0]._.Number] <= _or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}

//--------------------------------
word BLEU_LS  (union Operand *Operands)
{
    if (MemData.lwData[Operands[0]._.Number] <= _or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}

//--------------------------------
word BLEU_BBa (union Operand *Operands)
{
    if (MemData.bData[Operands[0]._.Number] <= *(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLEU_WBa (union Operand *Operands)
{
    if (MemData.wData[Operands[0]._.Number] <= *(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLEU_LBa (union Operand *Operands)
{
    if (MemData.lwData[Operands[0]._.Number] <= *(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLEU_BaB (union Operand *Operands)
{
    if (*(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <= *(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLEU_BaW (union Operand *Operands)
{
    if (*(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <= *(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLEU_BaL (union Operand *Operands)
{
    if (*(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <= *(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLEU_BaB_S (union Operand *Operands)
{
    if (*(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <= _or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLEU_BaW_S (union Operand *Operands)
{
    if (*(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <= _or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLEU_BaL_S (union Operand *Operands)
{
    if (*(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <= _or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLEU_BaB_C (union Operand *Operands)
{
    if (*(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <= Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLEU_BaW_C (union Operand *Operands)
{
    if (*(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <= Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLEU_BaL_C (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[2].all<<16)+Operands[1].all;
    if (*(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr <= lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}
//--------------------------------
word BLEU_BS_S  (union Operand *Operands)
{
    if (_or.MemData.bData[Operands[0]._.Number] <= _or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLEU_WS_S  (union Operand *Operands)
{
    if ( _or.MemData.wData[Operands[0]._.Number]<= _or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLEU_LS_S  (union Operand *Operands)
{
    if (_or.MemData.lwData[Operands[0]._.Number] <= _or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLEU_BS_C (union Operand *Operands)
{
    if (_or.MemData.bData[Operands[0]._.Number] <= Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLEU_WS_C (union Operand *Operands)
{
    if (_or.MemData.wData[Operands[0]._.Number] <= Operands[1].all )
    {
      if (Operands[2].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[2].all;

    }
    return 0;

}
//--------------------------------
word BLEU_LS_C (union Operand *Operands)
{
    lword lax;
    lax = ((lw)Operands[2].all<<16)+Operands[1].all;
    if (_or.MemData.lwData[Operands[0]._.Number] <= lax )
    {
      if (Operands[3].all > ObjPrgData.Size) return _Goto_Oveflow;
      ObjPrgData.ProgrammCounter = Operands[3].all;

    }
    return 0;

}


word BLEU_BAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.bData[Operands[0]._.Number] <=

    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLEU_WAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.wData[Operands[0]._.Number]

            <=

    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLEU_LAr    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.lwData[Operands[0]._.Number]

            <=

    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLEU_ArB    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            <=

    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLEU_ArW    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            <=

    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}
word BLEU_ArL    (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]

            <=

    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLEU_BAr_C  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            <=  Operands[1].all)
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLEU_WAr_C  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            <=  Operands[1].all)
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLEU_LAr_C  (union Operand *Operands)
{
    lword lax;
    word out;
     out = 0;
    lax = ((lw)Operands[2].all<<16)+Operands[1].all;
    if (MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] <= lax )
    {
      if (Operands[3].all > ObjPrgData.Size)
      {
            out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[3].all;
      }

    }
    return out;

}

word BLEU_BAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if (MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            <= *(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BLEU_WAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if (MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            <= *(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BLEU_LAr_Ba (union Operand *Operands)
{
     word out;
     out = 0;
    if (MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            <= *(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;
}

word BLEU_BAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            <= _or.MemData.bData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLEU_WAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            <= _or.MemData.wData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}

word BLEU_LAr_S  (union Operand *Operands)
{
    word out;
    out = 0;
    if (MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number]
            <= _or.MemData.lwData[Operands[1]._.Number] )
    {
      if (Operands[2].all > ObjPrgData.Size)
      {
        out =  _Goto_Oveflow;
      }
      else
      {
        ObjPrgData.ProgrammCounter = Operands[2].all;
      }

    }
    return out;

}
//------Положить одну ячейку в другую---------------
//--------------Беззнаковое-----------

word MOV_B_B   (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = MemData.bData[Operands[1]._.Number] ;
    return 0;

}

//--------------------------------

word MOV_B_W   (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = MemData.wData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOV_B_L   (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = MemData.lwData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOV_B_D   (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = (sb)MemData.dData[Operands[1]._.Number];
    return 0;

}
//--------------------------------

word MOV_B_C   (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = Operands[1].all;
    return 0;

}

//--------------------------------
word MOV_B_SB   (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = _or.MemData.bData[Operands[1]._.Number] ;
    return 0;
}

//--------------------------------
word MOV_B_SW   (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = _or.MemData.wData[Operands[1]._.Number] ;
    return 0;
}

//--------------------------------
word MOV_B_SL   (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = _or.MemData.lwData[Operands[1]._.Number] ;
    return 0;
}

//--------------------------------
word MOV_B_SD   (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = (sb)_or.MemData.dData[Operands[1]._.Number] ;
    return 0;
}

//--------------------------------

word MOV_B_BaB   (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = (*(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}

//--------------------------------

word MOV_B_BaW   (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = (sb)(*(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}

//--------------------------------

word MOV_B_BaL   (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = (sb)(*(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}

//--------------------------------

word MOV_B_BaD   (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = (sb)(*(double*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}

//--------------------------------

word MOV_W_B   (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = (sw)(sb)MemData.bData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOV_W_W   (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = MemData.wData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOV_W_L   (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = MemData.lwData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOV_W_D   (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = (sw)MemData.dData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOV_W_C   (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = Operands[1].all;
    return 0;

}

//--------------------------------

word MOV_W_SB   (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = (sw)(sb)_or.MemData.bData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOV_W_SW   (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = _or.MemData.wData[Operands[1]._.Number] ;
    return 0;

}

//--------------------------------

word MOV_W_SL   (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = _or.MemData.lwData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOV_W_SD   (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = (sw)_or.MemData.wData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOV_W_BaB   (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = (sw)(*(sb*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}

//--------------------------------

word MOV_W_BaW   (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = (*(sw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}
//--------------------------------

word MOV_W_BaL   (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = (sw)(*(slw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}
//--------------------------------

word MOV_W_BaD   (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = (sw)(*(double*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}
//--------------------------------
word MOV_L_B   (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = (slw)(sb)MemData.bData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOV_L_W   (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = (slw)(sw)MemData.wData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOV_L_L   (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = MemData.lwData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOV_L_D   (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = (slw)MemData.dData[Operands[1]._.Number];
    return 0;

}
//--------------------------------

word MOV_L_C   (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = ((slw)Operands[2].all<<16)+Operands[1].all;

    return 0;
}

//--------------------------------

word MOV_L_SB  (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = (slw)(sb)_or.MemData.bData[Operands[1]._.Number] ;
    return 0;

}

//--------------------------------

word MOV_L_SW  (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = (slw)(sw)_or.MemData.wData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOV_L_SL  (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = (slw)_or.MemData.lwData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOV_L_SD  (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = (slw)_or.MemData.dData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------
word MOV_L_BaB   (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = (slw)(*(sb*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}

//--------------------------------
word MOV_L_BaW   (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = (slw)(*(sw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}

//--------------------------------
word MOV_L_BaL   (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = (*(slw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}

//--------------------------------
word MOV_L_BaD   (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = (slw)(*(double*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}

//--------------------------------
word MOV_D_B   (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = (double)(sb)MemData.bData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOV_D_W   (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = (double)(sw)MemData.wData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOV_D_L   (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = (double)(slw)MemData.lwData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOV_D_D   (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = MemData.dData[Operands[1]._.Number];
    return 0;

}
//--------------------------------

word MOV_D_C   (union Operand *Operands)
{
    union str_double d_lax;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[4].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[2].all;
    d_lax.wrd[3] =  Operands[1].all;
#else

    d_lax.wrd[0] =  Operands[1].all;
    d_lax.wrd[1] =  Operands[2].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[4].all;

#endif
    MemData.dData[Operands[0]._.Number] = d_lax.all;

    return 0;
}

//--------------------------------

word MOV_D_SB  (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = (double)(sb)_or.MemData.bData[Operands[1]._.Number] ;
    return 0;

}

//--------------------------------

word MOV_D_SW  (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = (double)(sw)_or.MemData.wData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOV_D_SL  (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = (double)(slw)_or.MemData.lwData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOV_D_SD  (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = _or.MemData.dData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------
word MOV_D_BaB   (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = (double)(*(sb*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}

//--------------------------------
word MOV_D_BaW   (union Operand *Operands)
{
   // sword ax;
   // ax = *;
    MemData.dData[Operands[0]._.Number] = (double)(*(sw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr);
    return 0;

}

//--------------------------------
word MOV_D_BaL   (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = (double)(*(slw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}

//--------------------------------
word MOV_D_BaD   (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = (*(double*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}
//--------------------------------

word MOV_BaB_B   (union Operand *Operands)
{
    *(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = MemData.bData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOV_BaB_W   (union Operand *Operands)
{
    *(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = MemData.wData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOV_BaB_L   (union Operand *Operands)
{
    *(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = MemData.lwData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOV_BaB_D   (union Operand *Operands)
{
    *(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (sb)MemData.dData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOV_BaB_C(union Operand *Operands)
{

    *(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr =  (sb)Operands[1].all;
    return 0;

}

//--------------------------------

word MOV_BaB_SB   (union Operand *Operands)
{

    *(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = _or.MemData.bData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOV_BaB_SW   (union Operand *Operands)
{

    *(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = _or.MemData.wData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOV_BaB_SL   (union Operand *Operands)
{

    *(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = _or.MemData.lwData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOV_BaB_SD   (union Operand *Operands)
{

    *(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (sb)_or.MemData.dData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOV_BaB_BaB   (union Operand *Operands)
{
    *(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (*(sb*)var_tab1[Std_Vars[Operands[1]._.Number]].addr);
    return 0;

}
//--------------------------------

word MOV_BaB_BaW   (union Operand *Operands)
{
    *(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (sb)(*(sw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr);
    return 0;

}
//--------------------------------

word MOV_BaB_BaL   (union Operand *Operands)
{
    *(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (sb)(*(slw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr);
    return 0;

}
//--------------------------------

word MOV_BaB_BaD   (union Operand *Operands)
{
    *(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (sb)(*(double*)var_tab1[Std_Vars[Operands[1]._.Number]].addr);
    return 0;
}
//--------------------------------

word MOV_BaW_B   (union Operand *Operands)
{
    *(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (sw)(sb)MemData.bData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOV_BaW_W   (union Operand *Operands)
{
    *(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (sw)MemData.wData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOV_BaW_L   (union Operand *Operands)
{
    *(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (sw)MemData.lwData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOV_BaW_D   (union Operand *Operands)
{
    *(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (sw)MemData.dData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOV_BaW_C(union Operand *Operands)
{

    *(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr =  Operands[1].all;
    return 0;

}

//--------------------------------

word MOV_BaW_SB   (union Operand *Operands)
{

    *(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (sw)(sb)_or.MemData.bData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOV_BaW_SW   (union Operand *Operands)
{

    *(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (sw)_or.MemData.wData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOV_BaW_SL   (union Operand *Operands)
{

    *(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (sw)_or.MemData.lwData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOV_BaW_SD   (union Operand *Operands)
{

    *(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (sw)_or.MemData.dData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOV_BaW_BaB   (union Operand *Operands)
{
    *(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (sw)(*(sb*)var_tab1[Std_Vars[Operands[1]._.Number]].addr);
    return 0;

}
//--------------------------------

word MOV_BaW_BaW   (union Operand *Operands)
{
    *(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (*(sw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr);
    return 0;

}
//--------------------------------

word MOV_BaW_BaL   (union Operand *Operands)
{
    *(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (sw)(*(slw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr);
    return 0;

}
//--------------------------------

word MOV_BaW_BaD   (union Operand *Operands)
{
    *(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (sw)(*(double*)var_tab1[Std_Vars[Operands[1]._.Number]].addr);
    return 0;

}
//--------------------------------

word MOV_BaL_B   (union Operand *Operands)
{
    *(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (slw)(sb)MemData.bData[Operands[1]._.Number];
    return 0;
}

//--------------------------------

word MOV_BaL_W   (union Operand *Operands)
{
    *(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (slw)(sw)MemData.wData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOV_BaL_L   (union Operand *Operands)
{
    *(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (slw)MemData.lwData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOV_BaL_D   (union Operand *Operands)
{
    *(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (slw)MemData.dData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOV_BaL_C(union Operand *Operands)
{

    *(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr =  (slw)((lw)Operands[2].all<<16)+Operands[1].all;
    return 0;

}

//--------------------------------

word MOV_BaL_SB   (union Operand *Operands)
{

    *(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (slw)(sb)_or.MemData.bData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOV_BaL_SW   (union Operand *Operands)
{

    *(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (slw)(sw)_or.MemData.wData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOV_BaL_SL   (union Operand *Operands)
{

    *(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (slw)_or.MemData.lwData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOV_BaL_SD   (union Operand *Operands)
{

    *(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (slw)_or.MemData.dData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOV_BaL_BaB   (union Operand *Operands)
{
    *(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (slw)(*(sb*)var_tab1[Std_Vars[Operands[1]._.Number]].addr);
    return 0;

}
//--------------------------------

word MOV_BaL_BaW   (union Operand *Operands)
{
    *(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (slw)(*(sw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr);
    return 0;

}
//--------------------------------

word MOV_BaL_BaL   (union Operand *Operands)
{
    *(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (*(slw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr);
    return 0;

}
//--------------------------------

word MOV_BaL_BaD   (union Operand *Operands)
{
    *(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (slw)(*(double*)var_tab1[Std_Vars[Operands[1]._.Number]].addr);
    return 0;

}
//--------------------------------

word MOV_BaD_B   (union Operand *Operands)
{
    *(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (double)(sb)MemData.bData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOV_BaD_W   (union Operand *Operands)
{
    *(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (double)(sw)MemData.wData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOV_BaD_L   (union Operand *Operands)
{
    *(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (double)(slw)MemData.lwData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOV_BaD_D   (union Operand *Operands)
{
    *(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = MemData.dData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOV_BaD_C(union Operand *Operands)
{

    union str_double d_lax;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[4].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[2].all;
    d_lax.wrd[3] =  Operands[1].all;
#else

    d_lax.wrd[0] =  Operands[1].all;
    d_lax.wrd[1] =  Operands[2].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[4].all;

#endif

    *(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr =  d_lax.all;
    return 0;

}

//--------------------------------

word MOV_BaD_SB   (union Operand *Operands)
{

    *(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (double)(sb)_or.MemData.bData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOV_BaD_SW   (union Operand *Operands)
{

    *(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (double)(sw)_or.MemData.wData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOV_BaD_SL   (union Operand *Operands)
{

    *(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (double)(slw)_or.MemData.lwData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOV_BaD_SD   (union Operand *Operands)
{

    *(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = _or.MemData.dData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOV_BaD_BaB   (union Operand *Operands)
{
    *(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (double)(*(sb*)var_tab1[Std_Vars[Operands[1]._.Number]].addr);
    return 0;

}
//--------------------------------

word MOV_BaD_BaW   (union Operand *Operands)
{
    *(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (double)(*(sw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr);
    return 0;

}
//--------------------------------

word MOV_BaD_BaL   (union Operand *Operands)
{
    *(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (double)(*(slw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr);
    return 0;

}
//--------------------------------

word MOV_BaD_BaD   (union Operand *Operands)
{
    *(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (*(double*)var_tab1[Std_Vars[Operands[1]._.Number]].addr);
    return 0;

}
word MOV_BAr_B    (union Operand *Operands)
{
    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = MemData.bData[Operands[1]._.Number] ;
    return 0;

}

word MOV_BAr_W    (union Operand *Operands)
{
    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = MemData.wData[Operands[1]._.Number] ;
    return 0;

}
word MOV_BAr_L    (union Operand *Operands)
{
    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = MemData.lwData[Operands[1]._.Number] ;
    return 0;

}
word MOV_BAr_D    (union Operand *Operands)
{
    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (sb)MemData.dData[Operands[1]._.Number] ;
    return 0;

}
word MOV_BAr_C    (union Operand *Operands)
{
    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = Operands[1].all ;
    return 0;

}

word MOV_BAr_SB   (union Operand *Operands)
{
    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = _or.MemData.bData[Operands[1]._.Number] ;
    return 0;

}
word MOV_BAr_SW   (union Operand *Operands)
{
    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = _or.MemData.wData[Operands[1]._.Number] ;
    return 0;

}
word MOV_BAr_SL   (union Operand *Operands)
{
    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = _or.MemData.lwData[Operands[1]._.Number] ;
    return 0;

}
word MOV_BAr_SD   (union Operand *Operands)
{
    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (sb)_or.MemData.dData[Operands[1]._.Number] ;
    return 0;

}
word MOV_BAr_BaB  (union Operand *Operands)
{
    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (*(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}
word MOV_BAr_BaW  (union Operand *Operands)
{
    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (sb)(*(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}
word MOV_BAr_BaL  (union Operand *Operands)
{
    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (sb)(*(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}
word MOV_BAr_BaD  (union Operand *Operands)
{
    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (sb)(*(d*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}

word MOV_WAr_B    (union Operand *Operands)
{
    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (sw)(sb)MemData.bData[Operands[1]._.Number] ;
    return 0;

}

word MOV_WAr_W    (union Operand *Operands)
{

    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = MemData.wData[Operands[1]._.Number] ;
    return 0;

}
word MOV_WAr_L    (union Operand *Operands)
{
    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = MemData.lwData[Operands[1]._.Number] ;
    return 0;

}
word MOV_WAr_D    (union Operand *Operands)
{
    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (sw)MemData.dData[Operands[1]._.Number] ;
    return 0;

}
word MOV_WAr_C    (union Operand *Operands)
{
    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = Operands[1].all ;
    return 0;

}

word MOV_WAr_SB   (union Operand *Operands)
{
    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (sw)(sb)_or.MemData.bData[Operands[1]._.Number] ;
    return 0;

}
word MOV_WAr_SW   (union Operand *Operands)
{
    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = _or.MemData.wData[Operands[1]._.Number] ;
    return 0;

}
word MOV_WAr_SL   (union Operand *Operands)
{
    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = _or.MemData.lwData[Operands[1]._.Number] ;
    return 0;

}
word MOV_WAr_SD   (union Operand *Operands)
{
    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (sw)_or.MemData.dData[Operands[1]._.Number] ;
    return 0;

}
word MOV_WAr_BaB  (union Operand *Operands)
{
    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (sw)(sb)(*(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}
word MOV_WAr_BaW  (union Operand *Operands)
{
    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (sw)(*(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}
word MOV_WAr_BaL  (union Operand *Operands)
{
    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (sw)(*(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}
word MOV_WAr_BaD  (union Operand *Operands)
{
    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (sw)(*(d*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}
word MOV_LAr_B    (union Operand *Operands)
{
    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (slw)(sb)MemData.bData[Operands[1]._.Number] ;
    return 0;

}

word MOV_LAr_W    (union Operand *Operands)
{
    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (slw)(sw)MemData.wData[Operands[1]._.Number] ;
    return 0;

}
word MOV_LAr_L    (union Operand *Operands)
{
    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = MemData.lwData[Operands[1]._.Number] ;
    return 0;

}
word MOV_LAr_D    (union Operand *Operands)
{
    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (slw)MemData.dData[Operands[1]._.Number] ;
    return 0;

}
word MOV_LAr_C    (union Operand *Operands)
{
    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (slw)((lw)Operands[2].all<<16)+Operands[1].all;
    return 0;

}

word MOV_LAr_SB   (union Operand *Operands)
{
    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (slw)(sb)_or.MemData.bData[Operands[1]._.Number] ;
    return 0;

}
word MOV_LAr_SW   (union Operand *Operands)
{
    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (slw)(sw)_or.MemData.wData[Operands[1]._.Number] ;
    return 0;

}
word MOV_LAr_SL   (union Operand *Operands)
{
    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = _or.MemData.lwData[Operands[1]._.Number] ;
    return 0;

}
word MOV_LAr_SD   (union Operand *Operands)
{
    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (slw)_or.MemData.dData[Operands[1]._.Number] ;
    return 0;

}
word MOV_LAr_BaB  (union Operand *Operands)
{
    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (slw)(sb)(*(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}
word MOV_LAr_BaW  (union Operand *Operands)
{
    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (slw)(sw)(*(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}
word MOV_LAr_BaL  (union Operand *Operands)
{
    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (slw)(*(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}
word MOV_LAr_BaD  (union Operand *Operands)
{
    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (slw)(*(d*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}

word MOV_DAr_B    (union Operand *Operands)
{
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (double)(sb)MemData.bData[Operands[1]._.Number] ;
    return 0;

}

word MOV_DAr_W    (union Operand *Operands)
{
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (double)(sw)MemData.wData[Operands[1]._.Number] ;
    return 0;

}
word MOV_DAr_L    (union Operand *Operands)
{
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (double)(slw)MemData.lwData[Operands[1]._.Number] ;
    return 0;

}
word MOV_DAr_D    (union Operand *Operands)
{
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = MemData.dData[Operands[1]._.Number] ;
    return 0;

}
word MOV_DAr_C    (union Operand *Operands)
{
    union str_double d_lax;
#ifdef _Union_FR  //переворачиваем байты только для FR

    //Прекладывание double для FR
    d_lax.wrd[0] =  Operands[4].all;
    d_lax.wrd[1] =  Operands[3].all;
    d_lax.wrd[2] =  Operands[2].all;
    d_lax.wrd[3] =  Operands[1].all;
#else

    d_lax.wrd[0] =  Operands[1].all;
    d_lax.wrd[1] =  Operands[2].all;
    d_lax.wrd[2] =  Operands[3].all;
    d_lax.wrd[3] =  Operands[4].all;

#endif

    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = d_lax.all;
    return 0;

}

word MOV_DAr_SB   (union Operand *Operands)
{
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (double)(sb)_or.MemData.bData[Operands[1]._.Number] ;
    return 0;

}
word MOV_DAr_SW   (union Operand *Operands)
{
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (double)(sw)_or.MemData.wData[Operands[1]._.Number] ;
    return 0;

}
word MOV_DAr_SL   (union Operand *Operands)
{
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (double)(slw)_or.MemData.lwData[Operands[1]._.Number] ;
    return 0;

}
word MOV_DAr_SD   (union Operand *Operands)
{
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = _or.MemData.dData[Operands[1]._.Number] ;
    return 0;

}
word MOV_DAr_BaB  (union Operand *Operands)
{
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (double)(sb)(*(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}
word MOV_DAr_BaW  (union Operand *Operands)
{
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (double)(sw)(*(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}
word MOV_DAr_BaL  (union Operand *Operands)
{
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (double)(slw)(*(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}
word MOV_DAr_BaD  (union Operand *Operands)
{
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (*(double*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}
word MOV_B_BAr    (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
    return 0;

}
word MOV_W_BAr    (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = (sw)(sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
    return 0;

}
word MOV_L_BAr    (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = (slw)(sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
    return 0;

}
word MOV_D_BAr    (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = (double)(sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
    return 0;

}
word MOV_BaB_BAr  (union Operand *Operands)
{
        *(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr =  MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
        return 0;
}
word MOV_BaW_BAr  (union Operand *Operands)
{
        *(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr =  (sw)(sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
        return 0;
}
word MOV_BaL_BAr  (union Operand *Operands)
{
        *(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr =  (slw)(sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
        return 0;
}
word MOV_BaD_BAr  (union Operand *Operands)
{
        *(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr =  (double)(sb)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
        return 0;
}

word MOV_B_WAr    (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
    return 0;

}
word MOV_W_WAr    (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
    return 0;

}
word MOV_L_WAr    (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = (slw)(sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
    return 0;

}
word MOV_D_WAr    (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = (double)(sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
    return 0;

}
word MOV_BaB_WAr  (union Operand *Operands)
{
        *(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr =  MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
        return 0;
}
word MOV_BaW_WAr  (union Operand *Operands)
{
        *(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr =  MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
        return 0;
}
word MOV_BaL_WAr  (union Operand *Operands)
{
        *(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr =  (slw)(sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
        return 0;
}
word MOV_BaD_WAr  (union Operand *Operands)
{
        *(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr =  (double)(sw)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
        return 0;
}
word MOV_B_LAr    (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
    return 0;

}
word MOV_W_LAr    (union Operand *Operands)
{

    MemData.wData[Operands[0]._.Number] = MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
    return 0;

}
word MOV_L_LAr    (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
    return 0;

}
word MOV_D_LAr    (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = (double)(slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
    return 0;

}
word MOV_BaB_LAr  (union Operand *Operands)
{
        *(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr =  MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
        return 0;
}
word MOV_BaW_LAr  (union Operand *Operands)
{
        *(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr =  MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
        return 0;
}
word MOV_BaL_LAr  (union Operand *Operands)
{
        *(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
        return 0;
}
word MOV_BaD_LAr  (union Operand *Operands)
{
        *(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr =  (double)(slw)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
        return 0;
}

word MOV_B_DAr    (union Operand *Operands)
{
    MemData.bData[Operands[0]._.Number] = (sb)MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
    return 0;

}
word MOV_W_DAr    (union Operand *Operands)
{

    MemData.wData[Operands[0]._.Number] = (sw)MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
    return 0;

}
word MOV_L_DAr    (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = (slw)MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
    return 0;

}
word MOV_D_DAr    (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
    return 0;

}
word MOV_BaB_DAr  (union Operand *Operands)
{
        *(b*)var_tab1[Std_Vars[Operands[0]._.Number]].addr =  (sb)MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
        return 0;
}
word MOV_BaW_DAr  (union Operand *Operands)
{
        *(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr =  (sw)MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
        return 0;
}
word MOV_BaL_DAr  (union Operand *Operands)
{
        *(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (slw)MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
        return 0;
}
word MOV_BaD_DAr  (union Operand *Operands)
{
        *(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr =  MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
        return 0;
}
word MOV_BAr_BAr  (union Operand *Operands)
{
    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] =
    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] ;
    return 0;

}
word MOV_BAr_WAr  (union Operand *Operands)
{
    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] =
    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] ;
    return 0;

}
word MOV_BAr_LAr  (union Operand *Operands)
{
    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] =
    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] ;
    return 0;

}
word MOV_BAr_DAr  (union Operand *Operands)
{
    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] =
    (sb)MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] ;
    return 0;

}

word MOV_WAr_BAr  (union Operand *Operands)
{
    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] =
    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] ;
    return 0;

}

word MOV_WAr_WAr  (union Operand *Operands)
{
    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] =
    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] ;
    return 0;

}
word MOV_WAr_LAr  (union Operand *Operands)
{
    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] =
    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] ;
    return 0;

}
word MOV_WAr_DAr  (union Operand *Operands)
{
    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] =
    (sw)MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] ;
    return 0;

}
word MOV_LAr_BAr  (union Operand *Operands)
{
    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] =
    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] ;
    return 0;

}

word MOV_LAr_WAr  (union Operand *Operands)
{
    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] =
    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] ;
    return 0;

}
word MOV_LAr_LAr  (union Operand *Operands)
{
    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] =
    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] ;
    return 0;

}
word MOV_LAr_DAr  (union Operand *Operands)
{
    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] =
    (slw)MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] ;
    return 0;

}
word MOV_DAr_BAr  (union Operand *Operands)
{
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] =
    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] ;
    return 0;

}

word MOV_DAr_WAr  (union Operand *Operands)
{
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] =
    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] ;
    return 0;

}
word MOV_DAr_LAr  (union Operand *Operands)
{
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] =
    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] ;
    return 0;

}
word MOV_DAr_DAr  (union Operand *Operands)
{
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] =
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] ;
    return 0;

}


//--------------Беззнаковое-----------


//--------------------------------

word MOVU_W_B   (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = (w)MemData.bData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOVU_W_SB   (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = (w)_or.MemData.bData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOVU_W_BaB   (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = (w)(*(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}

//--------------------------------
word MOVU_L_B   (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = (lw)MemData.bData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOVU_L_W   (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = (lw)MemData.wData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOVU_L_SB  (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = (lw)_or.MemData.bData[Operands[1]._.Number] ;
    return 0;

}

//--------------------------------

word MOVU_L_SW  (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = (lw)_or.MemData.wData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------
word MOVU_L_BaB   (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = (lw)(*(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}

//--------------------------------
word MOVU_L_BaW   (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = (lw)(*(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}

//--------------------------------
word MOVU_D_B   (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = (double)(b)MemData.bData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOVU_D_W   (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = (double)(w)MemData.wData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOVU_D_L   (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = (double)(lw)MemData.lwData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOVU_D_SB  (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = (double)(b)_or.MemData.bData[Operands[1]._.Number] ;
    return 0;

}

//--------------------------------

word MOVU_D_SW  (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = (double)(w)_or.MemData.wData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOVU_D_SL  (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = (double)(lw)_or.MemData.lwData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------
word MOVU_D_BaB   (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = (double)(*(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}

//--------------------------------
word MOVU_D_BaW   (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = (double)(*(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}

//--------------------------------
word MOVU_D_BaL   (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = (double)(*(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}

//--------------------------------

word MOVU_BaW_B   (union Operand *Operands)
{
    *(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (w)MemData.bData[Operands[1]._.Number];
    return 0;

}
//--------------------------------

word MOVU_BaW_SB   (union Operand *Operands)
{

    *(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (w)_or.MemData.bData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOVU_BaW_BaB   (union Operand *Operands)
{
    *(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (w)(*(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr);
    return 0;

}
//--------------------------------

word MOVU_BaL_B   (union Operand *Operands)
{
    *(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (lw)MemData.bData[Operands[1]._.Number];
    return 0;
}

//--------------------------------

word MOVU_BaL_W   (union Operand *Operands)
{
    *(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (lw)MemData.wData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOVU_BaL_SB   (union Operand *Operands)
{

    *(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (lw)_or.MemData.bData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOVU_BaL_SW   (union Operand *Operands)
{

    *(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (lw)_or.MemData.wData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOVU_BaL_BaB   (union Operand *Operands)
{
    *(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (lw)(*(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr);
    return 0;

}
//--------------------------------

word MOVU_BaL_BaW   (union Operand *Operands)
{
    *(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (lw)(*(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr);
    return 0;

}
//--------------------------------

word MOVU_BaD_B   (union Operand *Operands)
{
    *(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (double)(b)MemData.bData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOVU_BaD_W   (union Operand *Operands)
{
    *(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (double)(w)MemData.wData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOVU_BaD_L   (union Operand *Operands)
{
    *(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (double)(lw)MemData.lwData[Operands[1]._.Number];
    return 0;

}

//--------------------------------

word MOVU_BaD_SB   (union Operand *Operands)
{

    *(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (double)(b)_or.MemData.bData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOVU_BaD_SW   (union Operand *Operands)
{

    *(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (double)(w)_or.MemData.wData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOVU_BaD_SL   (union Operand *Operands)
{

    *(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (double)(lw)_or.MemData.lwData[Operands[1]._.Number] ;
    return 0;

}
//--------------------------------

word MOVU_BaD_BaB   (union Operand *Operands)
{
    *(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (double)(*(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr);
    return 0;

}
//--------------------------------

word MOVU_BaD_BaW   (union Operand *Operands)
{
    *(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (double)(*(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr);
    return 0;

}
//--------------------------------

word MOVU_BaD_BaL   (union Operand *Operands)
{
    *(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr = (double)(*(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr);
    return 0;

}

word MOVU_WAr_B    (union Operand *Operands)
{
    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = MemData.bData[Operands[1]._.Number] ;
    return 0;

}

word MOVU_WAr_SB   (union Operand *Operands)
{
    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = _or.MemData.bData[Operands[1]._.Number] ;
    return 0;

}

word MOVU_WAr_BaB  (union Operand *Operands)
{
    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (*(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}
word MOVU_LAr_B    (union Operand *Operands)
{
    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = MemData.bData[Operands[1]._.Number] ;
    return 0;

}

word MOVU_LAr_W    (union Operand *Operands)
{
    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = MemData.wData[Operands[1]._.Number] ;
    return 0;

}
word MOVU_LAr_SB   (union Operand *Operands)
{
    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = _or.MemData.bData[Operands[1]._.Number] ;
    return 0;

}
word MOVU_LAr_SW   (union Operand *Operands)
{

    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = _or.MemData.wData[Operands[1]._.Number] ;
    return 0;

}

word MOVU_LAr_BaB  (union Operand *Operands)
{
    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (*(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}
word MOVU_LAr_BaW  (union Operand *Operands)
{
    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (*(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}

word MOVU_DAr_B    (union Operand *Operands)
{
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (double)MemData.bData[Operands[1]._.Number] ;
    return 0;

}

word MOVU_DAr_W    (union Operand *Operands)
{
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (double)MemData.wData[Operands[1]._.Number] ;
    return 0;

}
word MOVU_DAr_L    (union Operand *Operands)
{
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (double)MemData.lwData[Operands[1]._.Number] ;
    return 0;

}

word MOVU_DAr_SB   (union Operand *Operands)
{
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (double)_or.MemData.bData[Operands[1]._.Number] ;
    return 0;

}
word MOVU_DAr_SW   (union Operand *Operands)
{
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (double)_or.MemData.wData[Operands[1]._.Number] ;
    return 0;

}
word MOVU_DAr_SL   (union Operand *Operands)
{
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (double)_or.MemData.lwData[Operands[1]._.Number] ;
    return 0;

}
word MOVU_DAr_BaB (union Operand *Operands)
{
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (double)(*(b*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}
word MOVU_DAr_BaW  (union Operand *Operands)
{
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (double)(*(w*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}
word MOVU_DAr_BaL  (union Operand *Operands)
{
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] = (double)(*(lw*)var_tab1[Std_Vars[Operands[1]._.Number]].addr) ;
    return 0;

}

word MOVU_W_BAr    (union Operand *Operands)
{
    MemData.wData[Operands[0]._.Number] = MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
    return 0;

}
word MOVU_L_BAr    (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
    return 0;

}
word MOVU_D_BAr    (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = (double)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
    return 0;

}
word MOVU_BaW_BAr  (union Operand *Operands)
{
        *(w*)var_tab1[Std_Vars[Operands[0]._.Number]].addr =  MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
        return 0;
}
word MOVU_BaL_BAr  (union Operand *Operands)
{
        *(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr =  MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
        return 0;
}
word MOVU_BaD_BAr  (union Operand *Operands)
{
        *(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr =  (double)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
        return 0;
}

word MOVU_L_WAr    (union Operand *Operands)
{
    MemData.lwData[Operands[0]._.Number] = MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
    return 0;

}
word MOVU_D_WAr    (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = (double)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
    return 0;

}
word MOVU_BaL_WAr  (union Operand *Operands)
{
        *(lw*)var_tab1[Std_Vars[Operands[0]._.Number]].addr =  MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
        return 0;
}
word MOVU_BaD_WAr  (union Operand *Operands)
{
        *(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr =  (double)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
        return 0;
}
word MOVU_D_LAr    (union Operand *Operands)
{
    MemData.dData[Operands[0]._.Number] = (double)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
    return 0;

}
word MOVU_BaD_LAr  (union Operand *Operands)
{
        *(double*)var_tab1[Std_Vars[Operands[0]._.Number]].addr =  (double)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number];
        return 0;
}

word MOVU_WAr_BAr (union Operand *Operands)
{
    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] =
    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] ;
    return 0;

}
word MOVU_LAr_BAr (union Operand *Operands)
{
    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] =
    MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] ;
    return 0;

}
word MOVU_LAr_WAr (union Operand *Operands)
{
    MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] =
    MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] ;
    return 0;

}
word MOVU_DAr_BAr (union Operand *Operands)
{
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] =
    (double)MemData.bData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] ;
    return 0;

}
word MOVU_DAr_WAr (union Operand *Operands)
{
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] =
    (double)MemData.wData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] ;
    return 0;

}
word MOVU_DAr_LAr (union Operand *Operands)
{
    MemData.dData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[0]._.Number]._.Number] =
    (double)MemData.lwData[Stack.body.oStack[Stack.body.Stack[Stack.Stack_Pointer-1]+Operands[1]._.Number]._.Number] ;
    return 0;

}

//-------Выдача сообщений---------

word SetMsg_Av (union Operand *Operands)
{
    lword lax;
    if (Operands[0].all <= 32 )
    {
        lax = 1;
        lax <<= Operands[0].all-1;
        Reg_AvarMsg_obj |= lax;
    }
    else return _AvMsg_Oveflow;
    return 0;

}
//--------------------------------

word SetMsg_Pr (union Operand *Operands)
{
    lword lax;
    if (Operands[0].all <= 32 )
    {
        lax = 1;
        lax <<= Operands[0].all-1;
        Reg_PreduprMsg_obj |= lax;
    }
    else return _PrMsg_Oveflow;
    return 0;

}
//--------------------------------

word SetMsg_Srv(union Operand *Operands)
{
    lword lax;
    if (Operands[0].all <= 32 )
    {
        lax = 1;
        lax <<= Operands[0].all-1;
        Reg_ServiceMsg_obj |= lax;
    }
    else return _SrvMsg_Oveflow;
    return 0;

}

//-------Снятие сообщений---------

word ClrMsg_Av (union Operand *Operands)
{
    lword lax;
    if (Operands[0].all <= 32 )
    {
        lax = 1;
        lax <<= Operands[0].all-1;
        Reg_AvarMsg_obj &= ~lax;
    }
    else return _AvMsg_Oveflow;
    return 0;

}
//--------------------------------

word ClrMsg_Pr (union Operand *Operands)
{
    lword lax;
    if (Operands[0].all <= 32 )
    {
        lax = 1;
        lax <<= Operands[0].all-1;
        Reg_PreduprMsg_obj &= ~lax;
    }
    else return _PrMsg_Oveflow;
    return 0;

}
//--------------------------------

word ClrMsg_Srv(union Operand *Operands)
{
    lword lax;
    if (Operands[0].all <= 32 )
    {
        lax = 1;
        lax <<= Operands[0].all-1;
        Reg_ServiceMsg_obj &= ~lax;
    }
    else return _SrvMsg_Oveflow;
    return 0;

}

//-------Снятие всех сообщений---------
word ClrAllMsg_Av (union Operand *Operands)
{
    if (Operands[0].all == 0xffff )
    {
        Reg_AvarMsg_obj = 0;
    }
    else return _Err_Oper;
    return 0;

}
//--------------------------------

word ClrAllMsg_Pr (union Operand *Operands)
{
    if (Operands[0].all == 0xffff )
    {
        Reg_PreduprMsg_obj = 0;
    }
    else return _Err_Oper;

    return 0;

}
//--------------------------------

word ClrAllMsg_Srv(union Operand *Operands)
{
    if (Operands[0].all == 0xffff )
    {
        Reg_ServiceMsg_obj = 0;
    }
    else return _Err_Oper;
    return 0;
}


//--------

word CALL(union Operand *Operands)
{
    word ax, i, out;
    out = 0;
    //SP указывает на следующую пустую ячейку в стеке, и проверка на переполнение
    if (Stack.Stack_Pointer >= _STACK_SIZE )
    {
            out =  _Stack_Oveflow;
    }
    else
    {
        Stack.body.Stack[Stack.Stack_Pointer] = ObjPrgData.ProgrammCounter;
        ++Stack.Stack_Pointer;

        ObjPrgData.ProgrammCounter = Operands[0].all;

        if (ObjPrgData.ProgrammCounter > ObjPrgData.Size)
        {
                out = _Goto_Oveflow;
        }
        else
        {
            if (Stack.Stack_Pointer >= _STACK_SIZE )
            {
                    out =  _Stack_Oveflow;
            }
            else
            {
                //Указатель на первый аргумент функции в стеке
                ax = Stack.Stack_Pointer;
                for ( i=1; i<= (Operands[_Tmp_Opers_max].all-1); i++)
                {
                    if (Stack.Stack_Pointer >= _STACK_SIZE )
                    {
                        out =  _Stack_Oveflow;
                        i = Operands[_Tmp_Opers_max].all;
                    }
                    else
                    {
                        Stack.body.Stack[Stack.Stack_Pointer] = Operands[i].all;
                        ++Stack.Stack_Pointer ;
                    }
                }

                if ((out !=  _Stack_Oveflow)&&(Stack.Stack_Pointer < _STACK_SIZE))
                {
                    //Записываем последним указатель на первый аргумент функиции в стеке
                    Stack.body.Stack[Stack.Stack_Pointer] = ax;
                    //SP указывает на следующую пустую ячейку в стеке
                    ++Stack.Stack_Pointer;
                }
                else
                {
                    //Переполнение стека
                    out =  _Stack_Oveflow;
                }
            }
        }
    }
    return out;
}

//--------------------------------

word CALL_B(union Operand *Operands)
{
    word out;
    out = 0;


    if (Operands[0].all > _Numb_Basef-1)
    {
        out = _Wrong_Base_func;
    }
    else
    {
        out =  (*Base_func[Base_func_decoding[Operands[0].all]])( Operands );

    }
    return out;
}

//--------------------------------

word RET (union Operand* Operands)
{
    word out;
    out = 0;
    //Забираем со стека указатель на первый аргумент.
    Stack.Stack_Pointer =  Stack.body.Stack[(Stack.Stack_Pointer-1)];
    //Выше него лежит адрес возврата, сдвигаем указатель и проверяем на опустошение стека
    if ((sw)(--Stack.Stack_Pointer) < 0)
    {
        out =  _Stack_Underflow;
    }
    else
    {
        //Забираем значение со стека и считаем эту ячейку пустой, по этому SP будет указывать на нее
        ObjPrgData.ProgrammCounter = Stack.body.Stack[Stack.Stack_Pointer];
        //Проверка на переход за блок программ
        if (ObjPrgData.ProgrammCounter > ObjPrgData.Size)
        {
                out = _Goto_Oveflow;
        }
    }
    Operands[0].all = out;
    return out;

}

/*
//--------------------------------
//Положить данные в стек, указывается адресс источника и его размер в байтах
//возвращает результат операции 0 - все нормально, 1 - переполнение
word PUSH( byte*in, word size)
{
   word i;
    for ( i = 0; i <= size; ++i)
    {
        Stack.Stack[Stack.Stack_Pointer] = in[i];

        if (++Stack.Stack_Pointer >= _STACK_SIZE ) return _Stack_Oveflow;
    }
    return 0;
}


//--------------------------------
//Забрать данные из стека, указывается адресс приемника и его размер в байтах
//возвращает результат операции 0 - все нормально, 1 - переполнение
word POP( byte*in, word size)
{
   word i;
    for ( i = 0; i <= size; ++i)
    {
        if ( (sw)(--Stack.Stack_Pointer) < 0) return _Stack_Underflow;
        in[i] = Stack.Stack[Stack.Stack_Pointer];
    }
    return 0;
}
*/

//--------------------------------
word GOTO (union Operand *Operands)
{
    //word ax;
    ObjPrgData.ProgrammCounter = Operands[0].all;
    if (ObjPrgData.ProgrammCounter > ObjPrgData.Size) return _Goto_Oveflow;
    return 0;
}

//--------------------------------
word rezerv  (union Operand *Operands)
{
    Operands[0].all = Operands[0].all;
    return _Err_Comm;
}

//Базовые функции
//--------------------------------
//L[0] - Номер функции
//L[1] - Номер блока
//L[2] - выход
//L[3] - входная величина

word bSin (union Operand *Operands)
{
  MemData.dData[Operands[2]._.Number] = sin(MemData.dData[Operands[3]._.Number]);
  return 0;
}
//--------------------------------
//L[0] - Номер функции
//L[1] - Номер блока
//L[2] - выход
//L[3] - входная величина
word bCos (union Operand *Operands)
{
  MemData.dData[Operands[2]._.Number] = cos(MemData.dData[Operands[3]._.Number]);
  return 0;
}
//--------------------------------
//L[0] - Номер функции
//L[1] - Номер блока
//L[2] - выход
//L[3] - входная величина
word bTan (union Operand *Operands)
{
  MemData.dData[Operands[2]._.Number] = tan(MemData.dData[Operands[3]._.Number]);
  return 0;
}
//--------------------------------
//L[0] - Номер функции
//L[1] - Номер блока
//L[2] - выход
//L[3] - входная величина
word bAsin (union Operand *Operands)
{
  MemData.dData[Operands[2]._.Number] = asin(MemData.dData[Operands[3]._.Number]);
  return 0;
}
//--------------------------------
//L[0] - Номер функции
//L[1] - Номер блока
//L[2] - выход
//L[3] - входная величина
word bAcos (union Operand *Operands)
{
  MemData.dData[Operands[2]._.Number] = acos(MemData.dData[Operands[3]._.Number]);
  return 0;
}
//--------------------------------
//L[0] - Номер функции
//L[1] - Номер блока
//L[2] - выход
//L[3] - входная величина
word bAtan (union Operand *Operands)
{
  MemData.dData[Operands[2]._.Number] = atan(MemData.dData[Operands[3]._.Number]);
  return 0;
}

//--------------------------------
//L[0] - Номер функции
//L[1] - Номер блока
//L[2] - выход
//L[3] - входная величина
word bSqr (union Operand *Operands)
{
  MemData.dData[Operands[2]._.Number] = sqrt(MemData.dData[Operands[3]._.Number]);
  return 0;
}

//--------------------------------
//L[0] - Номер функции
//L[1] - Номер блока
//L[2] - выход
//L[3] - входная величина
word bAbsD (union Operand *Operands)
{
  if (MemData.dData[Operands[3]._.Number] < 0)
  {
    MemData.dData[Operands[2]._.Number] = MemData.dData[Operands[3]._.Number]*(-1);

  }
  else
  {
    MemData.dData[Operands[2]._.Number] = MemData.dData[Operands[3]._.Number];
  }

  return 0;
}

//--------------------------------
//L[0] - Номер функции
//L[1] - Номер блока
//L[2] - выход
//L[3] - входная величина
word bAbsI (union Operand *Operands)
{
  if (MemData.lwData[Operands[3]._.Number] < 0)
  {
    MemData.lwData[Operands[2]._.Number] = ~MemData.lwData[Operands[3]._.Number]+1;

  }
  else
  {
    MemData.lwData[Operands[2]._.Number] = MemData.lwData[Operands[3]._.Number];
  }

  return 0;
}
//--------------------------------
//L[0] - Номер функции
//L[1] - Номер блока
//L[2] - выход
//L[3] - входная величина
//L[4] - максимум
//L[5] - минимум

word bLimD (union Operand *Operands)
{
  if (MemData.dData[Operands[3]._.Number] > MemData.dData[Operands[4]._.Number])
  {
    MemData.dData[Operands[2]._.Number] = MemData.dData[Operands[4]._.Number];

  }
  else if (MemData.dData[Operands[3]._.Number] < MemData.dData[Operands[5]._.Number] )
  {
    MemData.dData[Operands[2]._.Number] = MemData.dData[Operands[5]._.Number];
  }
  else
  {
    MemData.dData[Operands[2]._.Number] = MemData.dData[Operands[3]._.Number];
  }

  return 0;
}

//--------------------------------
//L[0] - Номер функции
//L[1] - Номер блока
//L[2] - выход
//L[3] - входная величина
//L[4] - максимум
//L[5] - минимум
word bLimI (union Operand *Operands)
{
  if ((slw)MemData.lwData[Operands[3]._.Number] > (slw)MemData.lwData[Operands[4]._.Number])
  {
    MemData.lwData[Operands[2]._.Number] = MemData.lwData[Operands[4]._.Number];

  }
  else if ((slw)MemData.lwData[Operands[3]._.Number] < (slw)MemData.lwData[Operands[5]._.Number] )
  {
    MemData.lwData[Operands[2]._.Number] = MemData.lwData[Operands[5]._.Number];
  }
  else
  {
    MemData.lwData[Operands[2]._.Number] = MemData.lwData[Operands[3]._.Number];
  }
  return 0;
}
//--------------------------------
//Функция ИЗУ - интегро задающее устройство: изменение задания с заданным темпом по команде больше, меньше
//L[0] - Номер функции
//L[1] - Номер блока
//L[2] - выход
//L[3] - темп  нарастания, дискр/ сек
//L[4] - темп  спада, дискр /сек
//L[5] - ограничение  по максимуму
//L[6] - ограничение  по минимуму
//L[7] - Слово управления: Значение 1 - вверх, Значение 2 - вниз, Значение 4 - сброс значений в 0

word bIZUD (union Operand *Operands)
{
    double ax;
    byte Upr;
    double LimMax, LimMin, IZUout;
    struct base_IZU *ptr = &b_timeIZUd[Operands[1].all];
    LimMax = MemData.dData[Operands[5]._.Number];
    LimMin = MemData.dData[Operands[6]._.Number];
    Upr =  MemData.bData[Operands[7]._.Number];
    IZUout = MemData.dData[Operands[2]._.Number];

    //Начальная инициализация
    if ( (ptr->first != 1))
    {
        ptr->time = timer1;
        ptr->first = 1;
        MemData.dData[Operands[2]._.Number] = 0;
    }
    else
    {

        ax = (double)(w)(timer1 -  ptr->time);
        ptr->time = timer1;

        if ((Upr&0x04) != 0 )
        {
            //Команда установки выхода в 0
            if (LimMin < 0)
            {
                IZUout = 0;

            }
            else
            {
                IZUout = LimMin;
            }
           // ptr->time = timer1;
            ptr->drob = 0;
        }
        else if ( (Upr&0x01) != 0 )
        {
            //Команда больше
            ax *= MemData.dData[Operands[3]._.Number];
            fr6 = ax;
            ax *= _SecDiscr;
            fr7 = ax;
            IZUout += ax;
        }
        else if ( (Upr&0x02) != 0 )
        {

            //Команда меньше
            ax *= MemData.dData[Operands[4]._.Number];
            fr6 = ax;
            ax *= _SecDiscr;
            fr7 = ax;
            IZUout -= ax;
        }
        //Ограничения
        if (IZUout < LimMin )
        {
            IZUout = LimMin;
        }
        else if (IZUout > LimMax )
        {
            IZUout = LimMax;
        }
    }
    //Возвращаем выход
    MemData.dData[Operands[2]._.Number] = IZUout;
    return 0;
}

//--------------------------------
//ИЗУ с lword
//L[0] - Номер функции
//L[1] - Номер блока
//L[2] - выход
//L[3] - темп  нарастания, дискр/ сек
//L[4] - темп  спада, дискр /сек
//L[5] - ограничение  по максимуму
//L[6] - ограничение  по минимуму
//L[7] - Слово управления: Значение 1 - вверх, Значение 2 - вниз, Значение 4 - сброс значений в 0

word bIZUI (union Operand *Operands)
{
    word ax;
    byte Upr;
    lword lbx;
    slword LimMax, LimMin, IZUout;
    //Перекладываем значения во внутренние переменные для ускорения работы программы
    struct base_IZU *ptr = &b_timeIZUi[Operands[1].all];
    LimMax = MemData.lwData[Operands[5]._.Number];
    LimMin = MemData.lwData[Operands[6]._.Number];
    Upr =  MemData.bData[Operands[7]._.Number];
    IZUout = MemData.lwData[Operands[2]._.Number];
    //Начальная инициализация
    if ( (ptr->first != 1))
    {
        ptr->first = 1;
        ptr->time = timer1;
        ptr->drob = 0;
        //Команда установки выхода в 0
        if ((slw)LimMin < 0)
        {
            IZUout = 0;

        }
        else
        {
            IZUout = LimMin;
        }
    }
    else
    {
        //Рачет dT
        ax = timer1 -  ptr->time;
    //    lax = (lw)_Sec(1)<<16;
        ptr->time = timer1;

        if ((Upr&0x04) != 0 )
        {
            //Команда установки выхода в 0
            if ((slw)LimMin < 0)
            {
                IZUout = 0;

            }
            else
            {
                IZUout = LimMin;
            }
           // ptr->time = timer1;
            ptr->drob = 0;
        }
        else if ( (Upr&0x01) != 0 )
        {
            //Команда больше
            lbx = (lw)ax * MemData.lwData[Operands[3]._.Number];
            lbx /= _Sec(1);
            lbx =(lw)lbx + (lw)ptr->drob;
            ptr->drob = lbx&0xffff;
           /* //Если промежуток времени слишком мал, от ждем когда получим изменение хотя бы 1
            if (lbx != 0 )
            {
                ptr->time = timer1;
                IZUout += lbx;
            }*/
            IZUout += (lbx>>16);
        }
        else if ( (Upr&0x02) != 0 )
        {

            //Команда меньше
            lbx = (lw)ax * MemData.lwData[Operands[4]._.Number];
            lbx /=  _Sec(1);
            lbx =(lw)lbx + (lw)ptr->drob;
            ptr->drob = lbx&0xffff;

            /*//Если промежуток времени слишком мал, от ждем когда получим изменение хотя бы 1
            if (lbx != 0 )
            {
                ptr->time = timer1;
                IZUout -= lbx;
            } */
            IZUout -= (lbx>>16);
        }
     /*   else
        {
            //Нет команд: засекаем время последнего вызова.
            ptr->time = timer1;
        } */
        //Ограничения
        if ((slw)IZUout < (slw)LimMin )
        {
            IZUout = LimMin;
        }
        else if ((slw)IZUout > (slw)LimMax )
        {
            IZUout = LimMax;
        }
        //Возвращаем выход
    }
    MemData.lwData[Operands[2]._.Number] = IZUout;
    return 0;
}
//--------------------------------
//L[0] - Номер функции
//L[1] - Номер блока
//L[2] - Выходная величина
//L[3] - Входная величина
//L[4] - Темп разгона в + (дискрета/сек)
//L[5] - Темп разгона в -(дискрета/сек)
//L[6] - Темп торможения в + (дискрета/сек)
//L[7] - Темп торможения в -(дискрета/сек)
//L[8] - Темп параболического ЗИ (дискрета/сек)
word bZI (union Operand *Operands)
{
  /*register*/  lword lax ;
  /*register*/   word ax ;
  /*register*/   word bx;
  /*register*/   byte lbl ;
  /*register*/   byte sign_lin ;
  word *TempUpP, *TempDowP;
  word *TempUpM, *TempDowM;
  word *TempParab;
  word ziin,ziout;
   struct base_ZI * ptr = &base_ZIstr[Operands[1].all];

    if ( (ptr->first != 1))
    {
        ptr->first = 1;
        MemData.wData[Operands[2]._.Number]  = 0 ;
        MemData.wData[Operands[3]._.Number]  = 0 ;

        ptr->in_2  = 0 ;
        ptr->out_lin = 0 ;
        ptr->out_2 = 0 ;
        ptr->drob_lin = 0;
        ptr->drob_2 = 0;
        ptr->drob  = 0;
        ptr->prz.all = 0 ;
        ptr->time = timer1 ;

    }
    else
    {
        ziin  = MemData.wData[Operands[3]._.Number];
        ziout = MemData.wData[Operands[2]._.Number];
        //Темпы могут быть как уставкой, так и переменной
        //Разгон в плюс
        if (Operands[4]._.Type == _SETPOINT)
        {
            TempUpP = &_or.MemData.wData[Operands[4]._.Number];
        }
        else
        {
            TempUpP = &MemData.wData[Operands[4]._.Number];
        }

        //Разгон в минус
        if (Operands[5]._.Type == _SETPOINT)
        {
            TempUpM = &_or.MemData.wData[Operands[5]._.Number];
        }
        else
        {
            TempUpM = &MemData.wData[Operands[5]._.Number];
        }

        //Торможение в плюс
        if (Operands[6]._.Type == _SETPOINT)
        {
            TempDowP = &_or.MemData.wData[Operands[6]._.Number];
        }
        else
        {
            TempDowP = &MemData.wData[Operands[6]._.Number];
        }

        //Торможение в минус
        if (Operands[7]._.Type == _SETPOINT)
        {
            TempDowM = &_or.MemData.wData[Operands[7]._.Number];
        }
        else
        {
            TempDowM = &MemData.wData[Operands[7]._.Number];
        }

        //Параболический ЗИ
        if (Operands[8]._.Type == _SETPOINT)
        {
            TempParab = &_or.MemData.wData[Operands[8]._.Number];
        }
        else
        {
            TempParab = &MemData.wData[Operands[8]._.Number];
        }

        bx = timer1 ;               //_Sec(1.0)/2 для округления.
        ax = (w)( bx - ptr->time + (w)_Sec( 1.0 )/2) / (w)_Sec( 1.0 ) ; // Вычисление dT.
        ptr->time = bx ;  // запись момента текущей отработки ЗИ.

        if ( (sw)ziin != (sw)ptr->out_lin )
            {
                sign_lin = 0 ;
                // если вход и выход ЗИ положительны
                if ( (sw)ziin >= 0 && (sw)ptr->out_lin >= 0 )
                {

                    // если вход больше выхода ЗИ используется темп разгона в "+".
                    if ( (sw)ziin > (sw)ptr->out_lin )
                    {
                        bx = *TempUpP;
                        lbl = 1 ;
                    }

                    // если вход меньше выхода ЗИ используется темп торможения в "+".
                    else
                    {
                        bx = *TempDowP ;
                        lbl = 2 , sign_lin = 1 ;
                    }
                }

                // иначе если вход и выход ЗИ отрицательны
                else if ( (sw)ziin < 0 && (sw)ptr->out_lin <= 0 )
                {

                    // если вход меньше выхода ЗИ (по знаку) используется темп разгона в "-".
                    if ( (sw)ziin < (sw)ptr->out_lin )
                    {
                        bx = *TempUpM;
                        lbl = 2 , sign_lin = 1 ;
                    }

                // если вход болше выхода ЗИ (по знаку) используется темп торможения в "-".
                    else
                    {
                        bx = *TempDowM;
                        lbl = 1 ;
                    }
                }

                // если вход отрицательный а выход положительный
                                    //  используется темп торможения в "+".
                else if ( (sw)ziin < 0 && (sw)ptr->out_lin > 0 )
                    {
                        bx = *TempDowP ;
                        lbl = 3 , sign_lin = 1 ;
                    }

                // если вход положительный а выход отрицательный
                                    //  используется темп торможения в "-".
                else if ( (sw)ziin >= 0 && (sw)ptr->out_lin < 0 )
                    {
                        bx = *TempDowM ;
                        lbl = 4 ;
                    }

            //------- Рассчет интегратора N1 ( линейная часть ЗИ ) ---------------
                lax = ptr->drob_lin ;
                lax += ptr->out_lin << 16 ;
                if ( sign_lin == 1 ) lax -= (lw)bx * (lw)ax ;
                else                 lax += (lw)bx * (lw)ax ;
                ptr->drob_lin = (w) lax ;
                ptr->out_lin  = (w) ( lax >> 16 ) ;

            //--------------------------------------------------------------------

            //------------- Проверка конечных условий интегратора N1 -------------
                switch ( lbl )    //    out <?> in
                {
                    case 1:       //   + < +,  - < -
                            if ( (sw)ptr->out_lin > (sw)ziin )
                            {
                                    ptr->out_lin = ziin;
                                    ptr->drob_lin = 0 ;
                            }
                            //26.01.06 13:59cx = zip->in - zip->out_lin ; // вычисляем дельту межде соседними загибами.
                    break ;

                    case 2:       //   + > +,  - > -
                            if ( (sw)ptr->out_lin < (sw)ziin )
                            {
                                ptr->out_lin = ziin;
                                ptr->drob_lin = 0 ;
                            }
                            //26.01.06 13:59cx = zip->in - zip->out_lin ;
                    break ;

                    case 3:       //   + != -
                                // если адрес уставки и ее значение не равны нулю ,
                                // выполняется параболический ЗИ .
                            if ( (sw)ptr->out_lin < 0 )
                            {
                                ptr->out_lin = 0;
                                ptr->drob_lin = 0 ;
                            }
                    break ;

                    case 4:       //   - != +
                            if ( (sw)ptr->out_lin > 0 )
                            {
                                ptr->out_lin = 0;
                                ptr->drob_lin = 0 ;
                            }
                    break ;
                }
            //--------------------------------------------------------------------
            }



        //--------------------------------------------------------------------

            // В случае равенства задания (in) и линейного выхода (out_lin) на вход
            // второго интегратора должен подаваться нуль :
        else bx = 0 ;//26.01.06 14:07, cx = 0 ;

        //---               // сохраняем знак 'bx'
        if ( sign_lin == 1 )  ptr->in_2 = ~bx + 1 ;  // если знак "-" , инвертируем bx .
        else                  ptr->in_2 = bx ; // знаковый вход второго интегратора .

        //--------------------------------------------------------------------

                // если адрес уставки и ее значение не равны нулю ,
                // выполняется параболический ЗИ .
        if (( TempParab != 0) && ( *TempParab != 0 ))
        {
        //------- Рассчет интегратора N2 -------------------------------------

            if ( (sw)ptr->in_2 != (sw)ptr->out_2 || ptr->prz.all != 0 )
            {
                bx = *TempParab ;
                bx = (w)( (lw)*TempUpP * (lw)_fSec(1.00) / (lw)( bx * 2 ) ) ;  //2 - коэффициент закругленности параболы, при увеличении - закругленность увелич-ся.


                //----------------------------
                lax = ptr->drob_2;
                lax += ptr->out_2<< 16 ;

                //----- если в интервале линейного уч. изменится задание "zip->in_2" в противоположную сторону
                if (  ( ptr->prz._.trg_pl  == 1 ) && (sw)ptr->in_2 < 0 && (sw)ziin < (sw)ziout )  ptr->prz._.trg_pl  = 0 , ptr->prz._.trg_lin  = 0 ;
                if (  ( ptr->prz._.trg_min == 1 ) && (sw)ptr->in_2 > 0 && (sw)ziin > (sw)ziout )  ptr->prz._.trg_min = 0 , ptr->prz._.trg_lin  = 0 ;

                //------ если в интервале параболы2 изменится полярность задания "zip->in_2" в противоположную сторону
                if ( ( ptr->prz._.trg_min_end == 1 ) && (sw)ptr->in_2 < 0 && (sw)ziin < (sw)ziout )   ptr->prz._.trg_min_end = 0 ;
                if ( ( ptr->prz._.trg_pl_end  == 1 ) && (sw)ptr->in_2 > 0 && (sw)ziin > (sw)ziout )   ptr->prz._.trg_pl_end  = 0 ;


            //------- если в интервале параболы2 возрастет задание "zip->in" выше  "zip->out_lin"
                if ( ( ptr->prz._.trg_min_end == 1 ) && (sw)ptr->in_2 > 0 && (sw)ziin < (sw)ziout+ 2 )   ptr->prz._.trg_min_end = 0  ;
                if ( ( ptr->prz._.trg_pl_end  == 1 ) && (sw)ptr->in_2 < 0 && (sw)ziin > (sw)ziout- 2 )   ptr->prz._.trg_pl_end  = 0  ;


                // если вход больше выхода :
                if ( (sw)ptr->in_2 > (sw)ptr->out_2 || ptr->prz._.trg_pl == 1 || ptr->prz._.trg_pl_end == 1 )
                {
                if ( ptr->prz._.trg_min == 1 || ptr->prz._.trg_min_end == 1 ) goto _min ;

                if (ptr->prz._.trg_pl_end == 0 )  // если нет цикла второй парболы
                {

                    if ( ( ptr->prz._.trg_pl == 0 ) ) // если триггер в "плюс" не установлен
                    {
                        if ( ptr->in_2 != 0 )   // и "zi.in_2 != 0"
                        {
                            ptr->time_s = Timer1_fSec ; // фиксация времени для интервала параболы
                            ptr->prz._.trg_pl = 1 ;
                            ptr->in2_copy =  ptr->in_2 ; // сохранение копии "ptr->in_2"
                            ptr->outl_copy = ziout ; // ptr->outl_copy = ptr->out_lin ;
                        }
                    }
                    else
                    {
                        ptr->in_2 = ptr->in2_copy ;
                            // если на участке параболы осталось всего лишь половина пройденного пути (если дали малое задание)
                        if ( (sw)( ziout - ptr->outl_copy ) > (sw)( ziin - ziout ) && ptr->prz._.trg_lin == 0 )
                            {
                            goto _n1 ;  // минуем линейный участок
                            }
                    }



                    if ( (u)((w)(Timer1_fSec - ptr->time_s)) > (w)*TempParab  &&  ptr->prz._.trg_lin == 0 )  // интервал параболы завешен
                    {
                        ptr->prz._.trg_lin = 1 ; // начался линейный участок
                        ptr->out2_copy  = ptr->out_2 ;  // копия "out_2" для интегрирования в минус

                        ptr->out_2 = ptr->in2_copy  ;   // в "out_2" заносится копия "in2" для интервала линейного интегрирования
                        lax = ptr->drob_2 ;
                        lax += (lw)ptr->out_2 << 16 ;

                        ptr->outl_copy -= ziout  ;  // в переменную "outl_copy" добавляем текущее значение "ptr->out"
                    }


                    if (  ptr->prz._.trg_lin == 1  ) // линейный участок
                    {          // расчет точки для старта интервала парболы в "минус"
                        ptr->start_m = ziin + ptr->outl_copy ; // (перерасчет производится во время всего линейного участка т.к. "ptr->in" может меняться)

                        if ( (sw)ziout >= (sw)ptr->start_m )  // закончился интервал линейного интегрирования
                        {
                            ptr->out_2 = ptr->out2_copy ;  // в "out_2" заносится копия "in2" для интервала линейного интегрирования
                            lax = ptr->drob_2 ;
                            lax += (lw)ptr->out_2 << 16 ;
                        _n1:
                            ptr->prz._.trg_lin  = 0 ;
                            ptr->prz._.trg_pl   = 0 ;
                            ptr->prz._.trg_min_end  = 1 ;

                            ptr->start_m = ziin ; // сохраняем копию "ptr->in" для определения изменения "ptr->in" на интервале парболы в "минус"

                            goto _min ;
                        }
                    }
                }
                else
                {
                    // если уменьшилось задание "ptr->in" то сбрасаваем "prz._.trg_pl_end"
                    if ( ziin != ptr->start_p && (sw)ptr->in_2 < 0 )
                        {

                        if ( (sw)( ptr->out_lin - ziin ) > (sw)( ziout - ptr->out_lin ) )
                            {
                            ptr->prz._.trg_pl_end = 0 ;
                            ptr->out_2 = 0 ;
                            }
                        }
                    ptr->in_2 = 0 ;

                    // если итегратор out_2 дошел до "0", а триггер "trg_pl_end == 1" то принудительно сбрасываем trg_pl_end, иначе zi_out зависало
                    if ( ptr->out_2 == 0 )   ptr->prz._.trg_pl_end = 0 /*, ptr->out_lin = 0 */;
                }

                //------------------------------------

                lax +=  (lw)bx * (lw)ax ; // * (lw)ptr->K / (lw)256 ;
                ptr->drob_2 = (w) lax ;
                ptr->out_2  = (w) ( lax >> 16 ) ;
                if ( (sw)ptr->out_2 > (sw)ptr->in_2 ) ptr->out_2 = ptr->in_2, ptr->drob_2 = 0 ;
                }
                else // если вход меньше выхода :
                {
                _min:

                if ( ptr->prz._.trg_min_end == 0 )
                {
                    if ( ( ptr->prz._.trg_min == 0 ) ) // если триггер в "минус" не установлен
                    {
                    if ( ptr->in_2 != 0 )    // и "zi.in_2 != 0"
                        {
                            ptr->time_s = Timer1_fSec ; // фиксация времени для интервала параболы
                            ptr->prz._.trg_min = 1 ;
                            ptr->in2_copy  =  ptr->in_2 ; //
                            ptr->outl_copy = ziout ; // ptr->outl_copy = ptr->out_lin ;
                        }
                    }
                    else
                    {
                        ptr->in_2 = ptr->in2_copy ;

                        if ( (sw)( ziout - ptr->outl_copy ) < (sw)( ziin - ziout ) && ptr->prz._.trg_lin == 0 )
                            {
                            goto _n2 ;
                            }
                    }

                //------------------------------------

                    if ( (u)((w)(Timer1_fSec - ptr->time_s)) > (w)*TempParab && ptr->prz._.trg_lin == 0 )  // интервал параболы завешен
                    {
                        ptr->prz._.trg_lin = 1 ; // начался линейный участок
                        ptr->out2_copy  = ptr->out_2 ;  // копия "out_2" для интегрирования в минус

                        ptr->out_2 = ptr->in2_copy  ;   // в "out_2" заносится копия "in2" для интервала линейного интегрирования
                        lax = ptr->drob_2 ;
                        lax += (lw)ptr->out_2 << 16 ;

                        ptr->outl_copy -= ziout  ;
                        //ptr->start_p = ptr->in -  ptr->out + ptr->outl_copy ; // расчет точки для старта интервала парболы в "плюс"
                    }

                //------------------------------------


                    if ( ( ptr->prz._.trg_lin == 1 )  )      //  интервал линейного интегрирования
                    {
                    ptr->start_p = ziin + ptr->outl_copy ; // расчет точки для старта интервала парболы в "плюс"

                    if ( (sw)ziout <= (sw)ptr->start_p )   // закончился интервал линейного интегрирования
                        {
                        ptr->out_2 = ptr->out2_copy ;
                        lax = ptr->drob_2 ;
                        lax += (lw)ptr->out_2 << 16 ;
                    _n2:
                        ptr->prz._.trg_lin  = 0 ;
                        ptr->prz._.trg_min  = 0 ;
                        ptr->prz._.trg_pl_end = 1 ;

                        ptr->start_p = ziin ; // сохраняем копию "ptr->in" для определения изменения "ptr->in" на интервале парболы в "плюс"
                        }
                    }
                }
                else
                {
                    // если увеличилось задание "ptr->in" то сбрасаваем "prz._.trg_min_end"
                    if ( ziin != ptr->start_m && (sw)ptr->in_2 > 0 )
                        {
                        if ( (sw)( ziin - ptr->out_lin ) > (sw)( ptr->out_lin - ziout ) )
                            {
                            ptr->prz._.trg_min_end = 0 ;
                            ptr->out_2 = 0 ;
                            }
                        }
                    ptr->in_2 = 0 ;

                    // если итегратор out_2 дошел до "0", а триггер "trg_pl_end == 1" то принудительно сбрасываем trg_pl_end
                    if ( ptr->out_2 == 0 )   ptr->prz._.trg_min_end = 0 /*, ptr->out_lin = 0*/  ;
                }


                lax -=  (lw)bx * (lw)ax ; // * (lw)ptr->K / (lw)256 ;
                //lax -= ( (lw)bx * (lw)ax * ptr->K >> 8 );
                ptr->drob_2 = (w) lax ;
                ptr->out_2  = (w) ( lax >> 16 ) ;
                if ( (sw)ptr->out_2 < (sw)ptr->in_2 ) ptr->out_2 = ptr->in_2, ptr->drob_2 = 0 ;
                }
            }//26.01.06 14:11}

            // когда вход ЗИ равен выходу - почему-то in2 = out2 = +-temp;
            if ( ziin == ziout ) ptr->prz.all = 0 , ptr->in_2 = ptr->out_2 = 0 ;


        //--------------------------------------------------------------------

            //   Если команда (т.е. смена знака ptr->in2) на отработку нового
            // задания (ptr->in) пришла до того, как отработалось старое задание
            // и выход второго интегратора (ptr->out_2) все еще выполняет старое
            // задание --> принудительно обнуляем (ptr->out_2) , чтоб он интегрил
            // новое задание .

            if ( (sw)ptr->in_2 < 0 && (sw)ptr->out_2 > 0 )
            {
                if ( (sw)ziin < (sw)ziout )    ptr->out_2 = 0 ;
            }
            if ( (sw)ptr->in_2 > 0 && (sw)ptr->out_2 < 0 )
            {
                if ( (sw)ziin > (sw)ziout )    ptr->out_2 = 0 ;
            }
        //--------------------------------------------------------------------


            lax = ptr->drob ;
            lax += (lw)ziout << 16 ;

            bx = ptr->out_2 ;

            if ( (sw)ziin < (sw)ziout && (sw)bx > 0 )   bx = 0 ;
            if ( (sw)ziin > (sw)ziout && (sw)bx < 0 )   bx = 0 ;

            if ( bx == 0 )
            {    // дотяжка.
                if ( (sw)ziout > (sw)ziin ) bx = -1 ;
                else if ( (sw)ziout < (sw)ziin ) bx = +1 ;
            }
            // Если задание на интегратор bx = 0 (ptr->out_2), интегратор не работает
            if ( (sw)bx > 0 ) // Если задание положительное :
            {
                lax += (lw)bx * (lw)ax ;
                ptr->drob = (w) lax ;
                ziout  = (w) ( lax >> 16 ) ;
                // Срезаем выход ЗИ , если он наинтегрировался больше входа:
                if ( (sw)ziout > (sw)ziin ) ziout = ziin, ptr->drob = 0 ;
            }
            if ( (sw)bx < 0 ) // Если задание отрицательное :
            {
                bx = ~bx + 1 ;
                lax -= (lw)bx * (lw)ax ;
                ptr->drob = (w) lax ;
                ziout  = (w) ( lax >> 16 ) ;
                // Срезаем макс.отриц. выход ЗИ, если он наинтегрировался больше входа:
                if ( (sw)ziout < (sw)ziin ) ziout = ziin, ptr->drob = 0 ;
            }
        //--------------------------------------------------------------------
        }
            // если адрес уставки равен нулю , выполняется только линейный ЗИ :
        else ziout = ptr->out_lin ; // Выходу ЗИ присваеваем выход линейного ЗИ .
        MemData.wData[Operands[2]._.Number] = ziout;
  }
  return 0;
}
//--------------------------------
//L[0] - Номер функции
//L[1] - Номер блока
//L[2] - Выходная величина
//L[3] - Входная величина
//L[4] - значение инициализации выхода/выхода

word bini_ZI (union Operand *Operands)
{
   struct base_ZI * ptr = &base_ZIstr[Operands[1].all];

    //Вход и выход
    MemData.wData[Operands[2]._.Number]    = MemData.wData[Operands[4]._.Number] ;
    MemData.wData[Operands[3]._.Number]    = MemData.wData[Operands[4]._.Number] ;
    //обнуление внутренних переменных
    ptr->in_2  = 0 ;
    ptr->out_lin = MemData.wData[Operands[4]._.Number]  ;
    ptr->out_2 = 0 ;
    ptr->drob_lin = 0;
    ptr->drob_2 = 0;
    ptr->drob  = 0;
    ptr->prz.all = 0 ;
    ptr->time = timer1 ;

    return 0;
}
//--------------------------------
//L[0] - Номер функции
//L[1] - Номер блока
//L[2] - Выходная величина
//L[3] - Задание
//L[4] - Обратная связь
//L[5] - Пропорциональный коэффициент
//L[6] - Интегральный коэффициент 1 дискрета - 1 мсек
//L[7] - Ограничение выхода по максимуму
//L[8] - Ограничение выхода по минимуму
//L[9] - Разница между обратной связью и заданием, при котором достигается минимальное изменение выходной величины при значении Кр = 1, и Ti = 1;
//L[10] - минимальное изменение выходной величины регулятора, которого  требуется достичь при разнице между заданием и обратной связью, равной L[9],за время, равное Ti, или мгновенно, при Кр = 1;
//L[11] - Начальное значение интегратора
//L[12] - Структура конфигурирования регулятора:
//b0:
// = 0: увеличение величины ОС приводит к уменьшению выходной величины регулятора
//= 1: увеличение величины ОС приводит к увеличению выходной величины регулятора
//b1:
//= 0: регулятор отключён
//= 1: регулятор включён
word bPI_reg (union Operand *Operands)
{
    word ax, bx ;
    lword lax,lbx ;
    word *Kp_ex, *Ti_ex;
    word *min_lim, *max_lim;
    struct  bPI_reg_str *ptr;
    ptr = &bPI_str[Operands[1].all];

    if ( (ptr->first != 1) ||((MemData.bData[Operands[12]._.Number]& 0x1) == 0) )
    {
        ptr->first = 1;
        ptr->integrator = MemData.wData[Operands[11]._.Number];
        ptr->int_drob = 0;
        ptr->time = timer1;
        MemData.wData[Operands[2]._.Number] = 0;
        ptr->lims.all = 0;

    }
    else
    {
    //Коэффициценты могут быть как уставкой, так и переменной

        //Кп
        if (Operands[5]._.Type == _SETPOINT)
        {
            Kp_ex = &_or.MemData.wData[Operands[5]._.Number];
        }
        else
        {
            Kp_ex = &MemData.wData[Operands[5]._.Number];
        }

        //Ти
        if (Operands[6]._.Type == _SETPOINT)
        {
            Ti_ex = &_or.MemData.wData[Operands[6]._.Number];
        }
        else
        {
            Ti_ex = &MemData.wData[Operands[6]._.Number];
        }

        //Ограничение по максимуму
        if (Operands[7]._.Type == _SETPOINT)
        {
            max_lim = &_or.MemData.wData[Operands[7]._.Number];
        }
        else
        {
            max_lim = &MemData.wData[Operands[7]._.Number];
        }

        //Ограничение по минимуму
        if (Operands[8]._.Type == _SETPOINT)
        {
            min_lim = &_or.MemData.wData[Operands[8]._.Number];
        }
        else
        {
            min_lim = &MemData.wData[Operands[8]._.Number];
        }
            //  Вычисление отклонения от задания
        // Определяем заданный тип вычисления ошибки:
        // 0 - отрицательная обратная связь;
        // 1 - положительная обратная связь.
        if ( (MemData.bData[Operands[12]._.Number]& 0x2) == 0 )  ax = MemData.wData[Operands[3]._.Number] - MemData.wData[Operands[4]._.Number] ;
        else                               ax = MemData.wData[Operands[4]._.Number] - MemData.wData[Operands[3]._.Number] ;

        bx = timer1 - ptr->time;
        ptr->time = timer1;
    //ДДДДДДДДДДД Расчет интегратора.  ДДДДДДДДДДДДДД

    //   Проверка ограничений на возрастание или снижение интегратора.

        if ( (sw)ax >= 0 )
        {
            if ( ptr->lims._.ltd_int_p == 1 )  goto v4 ;
        }
        else
        {
            if ( ptr->lims._.ltd_int_m == 1 )  goto v4 ;
        }
        lax = *Ti_ex & 0x7ffful ;  // защита от "-" коэфф.

        if ( lax == 0)
        {
            ptr->integrator = MemData.wData[Operands[11]._.Number];
            goto v4;
        }
        else
        {
            lbx = (lw)MemData.wData[Operands[10]._.Number]*bx;
            lbx /=MemData.wData[Operands[9]._.Number];
            lax = (lbx<<16)/(lax*_MkSec(1000))  ;
        }

        bx = ax ;
        if ( (sw)bx < 0 )  bx = -bx ;
        if ( ((lw)bx >= (lw)0x7fffffff / lax) && (lax != 0))    // sravnivaem modul oshibki
        {                                        // s maksimalno dopustimoy
            if ( (sw)ax >= 0 ) lax = 0x7fffffff ;// pri vychislennom 'Ki',
            else               lax = 0x80000000 ;// dlya 32-bit setki oshibkoy.
        }
        else  lax = (slw)lax * (slw)(sw)ax ;


            //  Подготовка к контролю переполнения (без использ.'asm'):
        // если до сложения/вычитания операнды были одного знака, а результат
        // получился другого знака - значит произошло переполнения.
        bx = 2 ;
        if ( (slw)lax >= 0 ) // запоминаем сочетание знаков операндов.
        {
            if( (sw)ptr->integrator >= 0 ) bx = 0 ; // +/+
        }
        else if( (sw)ptr->integrator <  0 ) bx = 1 ; // -/-

        lax += (slw)(sw)ptr->integrator << 16 ;
        lax += (lw)(w)ptr->int_drob ;   // DROB IS'NT SIGNED !
                /* Проверка переполнений. */
                    //  переполнение в плюс?
            if     ( bx == 0 && (slw)lax <  0 ) goto v3 ;
                    //  переполнение в минус?
            else if( bx == 1 && (slw)lax >= 0 ) goto v2 ;
                    //  нет переполнения.

                /* Проверка ограничений. */

            if ( (slw)lax < ((slw)(sw)(*min_lim)<<16)  )
                {
        v2:       lax = (slw)(sw)(*min_lim)<<16 ;
                }
            else if ( (slw)lax >= ((slw)(sw)(*max_lim)<<16) )
                {
        v3:       lax = (slw)(sw)(*max_lim)<<16 ;
                }

            ptr->integrator = (slw)lax >> 16;
            ptr->int_drob = lax;
        v4:   ptr->lims._.ltd_int_p = 0 , ptr->lims._.ltd_int_m = 0 ;

    //ДДДДДД  Расчет пропорциональной составляющей и выхода регулятора. ДДДДДД
        lax = *Kp_ex;
        lax =( lax *  MemData.wData[Operands[10]._.Number]/ MemData.wData[Operands[9]._.Number]) << 16 ;

        lax &= 0x7ffffffful ;  //защита от "-" коэфф.
        //--- preventive overflow control.
        bx = ax ;
        if ( (sw)bx < 0 )  bx = -bx ;
        if ( ((lw)bx >= (lw)0x7fffffff / lax) &&(lax != 0))  //  sravnivaem modul oshibki
        {                                          // s maksimalno dopustimoy
            if ( (sw)ax >= 0 ) lax = 0x7fffffff ;// pri vychislennom 'Ki',
            else                 lax = 0x80000000 ;// dlya 32-bit setki oshibkoy.
        }
        else  lax = (slw)lax * (slw)(sw)ax ;

//        if ( (ptr->cfg._.pos_out == 1) && ((slw)lax < 0) ) lax = 0;

            //  Подготовка к контролю переполнения (без использ.'asm'):
        // если до сложения/вычитания операнды были одного знака, а результат
        // получился другого знака - значит произошло переполнения.
        bx = 2 ;
        if ( (slw)lax >= 0 ) // запоминаем сочетание знаков операндов.
        {
            if( (sw)ptr->integrator >= 0 ) bx = 0 ; // +/+
        }
        else if( (sw)ptr->integrator <  0 ) bx = 1 ; // -/-

        lax += (slw)(sw)ptr->integrator<<16 ;

                /* Проверка переполнений. */
                    //  переполнение в плюс?
            if     ( bx == 0 && (slw)lax <  0 ) goto p3 ;
                    //  переполнение в минус?
            else if( bx == 1 && (slw)lax >= 0 ) goto p2 ;
                    //  нет переполнения.

                /* Проверка ограничений. */
            if ( (slw)lax < (slw)(*min_lim)<<16 )
                {
        p2:       MemData.wData[Operands[2]._.Number] = (sw)(*min_lim) , ptr->lims._.ltd_int_m = 1 ;
                }
            else if ( (slw)lax >= (slw)(*max_lim)<<16 )
                {
        p3:       MemData.wData[Operands[2]._.Number] = (sw)(*max_lim) , ptr->lims._.ltd_int_p = 1 ;
                }
            else MemData.wData[Operands[2]._.Number] = (w)((slw)lax>>16) ;

    }
  return 0;

}

//--------------------------------
//L[0] - Номер функции
//L[1] - Номер блока
//L[2] - Выходная величина
//L[3] - Входная величина
//L[4] -Постоянная времени фильтра в fSec

word bFiltr (union Operand *Operands)
{
    struct  bfil_str *ptr;
    word  ax , bx , tim ;
    word *tau;
    sword  cx ;
    slword  lax;
    ptr = &bfilstr[Operands[1].all];

    if (ptr->first != 1)
    {
        ptr->first = 1;
        MemData.wData[Operands[2]._.Number] = MemData.wData[Operands[3]._.Number];
        ptr->time = Timer1_fSec ;
        ptr->drob = 0;
    }
    else
    {
    //тау может быть как уставкой, так и переменной

        if (Operands[4]._.Type == _SETPOINT)
        {
            tau = &_or.MemData.wData[Operands[4]._.Number];
        }
        else
        {
            tau = &MemData.wData[Operands[4]._.Number];
        }

        tim = Timer1_fSec ;
        ax = (w)( Timer1_fSec - ptr->time );
        if ( (u)ax != 0  )
        {
            ptr->time = tim ;
            bx = *tau + ax ;
            cx = MemData.wData[Operands[3]._.Number] - MemData.wData[Operands[2]._.Number] ; //Разность между входом и выходом фильтра
            lax = (w)ax;
            lax *= ((slw)(sw)cx<<16);
            lax /= (sw)bx ;
            if ( (slw)lax < (slw)(0xff800000) )
            {
                lax = 0x800000;
                ptr->drob = 0;
            }
            else if ( (slw)lax > (slw)0x7fffff )
            {
                lax = 0x7fff00;
                ptr->drob = 0;
            }
            lax += ((lw)(w)MemData.wData[Operands[2]._.Number]<<16);
            lax +=  (lw)(w)ptr->drob;
            ptr->drob = (w)lax;
            MemData.wData[Operands[2]._.Number] = (slw)lax>>16 ; //К выходу фильтра добавить целую часть от деления.
        }
    }
    return 0;

}

//--------------------------------
//L[0] - Номер функции
//L[1] - Номер блока
//L[2] - Выходная величина
//L[3] - Входная величина
//L[4] - Время, за которое производится усреднение
//L[5] -Биты конфигурации:
//b0 - усреднение по модулю

word bAverage (union Operand *Operands)
{
    struct  bAverage_str *ptr;
    word ax;
    word *dT_usr;
    lword lax;
    ptr = &bAveragestr[Operands[1]._.Number];

    if (ptr->first != 1)
    {
        ptr->first = 1;
        ptr->n = 0;
        ptr->time = Timer1_fSec;
        ptr->counter = 0;
        MemData.wData[Operands[2]._.Number] = MemData.wData[Operands[3]._.Number];
    }
    else
    {
    //dT может быть как уставкой, так и переменной

        if (Operands[4]._.Type == _SETPOINT)
        {
            dT_usr = &_or.MemData.wData[Operands[4]._.Number];
        }
        else
        {
            dT_usr = &MemData.wData[Operands[4]._.Number];
        }

        if ((u)((w)(Timer1_fSec - ptr->time))> *dT_usr )
        {
            if (ptr->n == 0 )
            {
                ptr->n = 1;
            }
            lax = (lw)ptr->n;
            MemData.wData[Operands[2]._.Number] = ((slw)ptr->counter)/(slw)lax;
            ptr->n = 0;
            ptr->counter = 0;
            ptr->time = Timer1_fSec;
        }
        else
        {
            if( ((MemData.bData[Operands[5]._.Number]&0x1) != 0 )&&((sw)MemData.wData[Operands[3]._.Number] < 0))
            {
                ax = ~MemData.wData[Operands[3]._.Number]+1;
            }
            else
            {
                ax = MemData.wData[Operands[3]._.Number];
            }
            ptr->counter = (slw)ptr->counter + (slw)(sw)ax ;
            ++ptr->n;
        }
    }
    return 0;
}


