#include "functions.c"


word Interpreter ( byte code )
{
  word ax, cx,dx, i;
#ifndef _CM3_
  word bx;
#else

  lword bx;

#endif

  //union str_word_byte cs_byte;
  byte tmp_txt[_Max_Name_Func];
 // lword lax;
  //byte  tmp_std_var[sizeof(var_tab1)/sizeof(struct namevar)][10];
  byte *pt1, *pt2;
 // byte tmp_ind[_MAX_SIZE_IND_TAB], bh;//Таблица переменных для индикации, извлекаемая из i2c
  word/* n_ind, j, */cs, cs_small;
  word err_code;
  byte tmp_func[sizeof( Basef_def ) ];
  err_code = 0;
  if ( code == 0 ) // инициализация
  {
    cs = 0xfcd8;//0x6a6c; //Контрольная сумма кодового слова - константа
    cs_small = 0;
   // addr_Ctrl = _i2c_end;
    fr1 = 0;
    ObjSrv_bit.all = 0;
    Stack.Stack_Pointer = 0;
    ObjPrgData.Size = 0;
    //ObjSrv_bit._.InWork = 0;
    fr5[0] = (w*)MemData.bData;
    fr5[1] = MemData.wData;
    fr5[2] = (w*)MemData.lwData;
    fr5[3] = (w*)MemData.dData;
    //Если не будет уставок чтобы не показывать мусор
    ax = sizeof (Ust_Obj_Prg);
    pt1 = (b*)Ust_Obj_Prg;
    for (i = 0; i < ax; ++i )
    {
      *pt1 = 0;
      ++pt1;
    }
    //[0].mask = 0;
   // Oprg = long_arch_command;
    //Проверочный код
    ax  = Load_from_i2c ( 8 ,  _ExtPrg_adr_i2c, (b*)CtrlTmp , _Adr_Flash_i2c ) ;
    if ( ax != 0 )
    {
not_i2c:
        mSet_ServiceMsg2( _Srv2_NoReadObj_i2c ) ;
        err_code =  _No_Link;
        goto Prg_End;
    }
    else
    {
        bx =_ExtPrg_adr_i2c+8;

        for (i=0; i<8;++i )
        {

            if (CtrlTmp[i] != CtrlCode[i]) goto  Prg_End;
        }
        //if ( err_code != 0)

        //Слово состава блока
        ax  = Load_from_i2c ( 2 ,   bx ,  (b*)&cx , _Adr_Flash_i2c ) ;
        if ( ax != 0 ) goto not_i2c;
#ifdef _Union_FR   //переворачиваем байты только для FR
        cx = (((cx&0x00ff)<<8)|((cx&0xff00)>>8));
#endif
        cs -= cx&0xff;
        cs -=cx>>8;
        bx += 2;

        Cfg_str.all = cx;

        //Количество перменных
        ax  = Load_from_i2c ( 8 ,   bx ,  (b*)&PVar_quant , _Adr_Flash_i2c ) ;
        if ( ax != 0 ) goto not_i2c;
#ifdef _Union_FR  //переворачиваем байты только для FR

        PVar_quant.qByte = (((PVar_quant.qByte&0x00ff)<<8)|((PVar_quant.qByte&0xff00)>>8));
        PVar_quant.qWord = (((PVar_quant.qWord&0x00ff)<<8)|((PVar_quant.qWord&0xff00)>>8));
        PVar_quant.qLWord = (((PVar_quant.qLWord&0x00ff)<<8)|((PVar_quant.qLWord&0xff00)>>8));
        PVar_quant.qDouble = (((PVar_quant.qDouble&0x00ff)<<8)|((PVar_quant.qDouble&0xff00)>>8));
#endif
        cs -= PVar_quant.qByte&0xff;
        cs -= PVar_quant.qByte>>8;
        cs -= PVar_quant.qWord&0xff;
        cs -= PVar_quant.qWord>>8;
        cs -= PVar_quant.qLWord&0xff;
        cs -= PVar_quant.qLWord>>8;
        cs -= PVar_quant.qDouble&0xff;
        cs -= PVar_quant.qDouble>>8;
        bx += 8;
        if ((PVar_quant.qByte> _MAX_NUM_BYTE)||(PVar_quant.qWord> _MAX_NUM_WORD)
          ||(PVar_quant.qLWord> _MAX_NUM_LWORD)||(PVar_quant.qDouble > _MAX_NUM_DOUBLE) )
        {
            err_code =  _VarQuantiy;
            goto Prg_End;
        }
        //Количество уставок
        ax  = Load_from_i2c ( 8 ,   bx ,  (b*)&SVar_quant , _Adr_Flash_i2c ) ;
        if ( ax != 0 ) goto not_i2c;
#ifdef _Union_FR  //переворачиваем байты только для FR

        SVar_quant.qByte = (((SVar_quant.qByte&0x00ff)<<8)|((SVar_quant.qByte&0xff00)>>8));
        SVar_quant.qWord = (((SVar_quant.qWord&0x00ff)<<8)|((SVar_quant.qWord&0xff00)>>8));
        SVar_quant.qLWord = (((SVar_quant.qLWord&0x00ff)<<8)|((SVar_quant.qLWord&0xff00)>>8));
        SVar_quant.qDouble = (((SVar_quant.qDouble&0x00ff)<<8)|((SVar_quant.qDouble&0xff00)>>8));

#endif
        cs -= SVar_quant.qByte&0xff;
        cs -= SVar_quant.qByte>>8;
        cs -= SVar_quant.qWord&0xff;
        cs -= SVar_quant.qWord>>8;
        cs -= SVar_quant.qLWord&0xff;
        cs -= SVar_quant.qLWord>>8;
        cs -= SVar_quant.qDouble&0xff;
        cs -= SVar_quant.qDouble>>8;
        bx += 8;
        if ((SVar_quant.qByte> _MAX_NUM_SP_BYTE)||(SVar_quant.qWord> _MAX_NUM_SP_WORD)
          ||(SVar_quant.qLWord> _MAX_NUM_SP_LWORD)||(SVar_quant.qDouble > _MAX_NUM_SP_DOUBLE) )
        {
            err_code =  _SPQuantiy;
            goto Prg_End;
        }

        //Размер блока программ
        ax  = Load_from_i2c ( 2 ,   bx ,  (b*)&cx , _Adr_Flash_i2c ) ;
        if ( ax != 0 ) goto not_i2c;
        //bh = cx>>8;
#ifdef _Union_FR  //переворачиваем байты только для FR
        cx = (((cx&0x00ff)<<8)|((cx&0xff00)>>8));
#endif
        cs_small -= cx&0xff;
        cs_small -= cx>>8;

    //    cs -=cx;
        bx += 2;
        //cx -= 10; //вычитаем 8 байт - слово, 2 байта - размер.

        //Превышение размера блока программ
        if ( cx > _MAX_LEN_CODE)
        {
            err_code =  _LenCode;
            goto Prg_End;
        }

        ObjPrgData.Size = cx/2;

        //Сам блок программ
        pt1 = (b*)ObjPrgData.Prog;
        ax  = Load_from_i2c ( cx ,   bx ,  pt1 , _Adr_Flash_i2c ) ;
        if ( ax != 0 ) goto not_i2c;
        //Переставляем байты под FR, заодно и расчитываем контрольную сумму.
        for ( i=0; i< cx/2; ++i)
        {
#ifdef _Union_FR  //переворачиваем байты только для FR
            ObjPrgData.Prog[i] = (((ObjPrgData.Prog[i]&0x00ff)<<8)|((ObjPrgData.Prog[i]&0xff00)>>8));
#endif
            cs_small -=ObjPrgData.Prog[i]>>8;
            cs_small -=ObjPrgData.Prog[i]&0x00ff;
        }
        bx +=cx;

        //Контрольная сумма
        ax  = Load_from_i2c ( 2 ,   bx ,  (b*)&cx , _Adr_Flash_i2c ) ;
        if ( ax != 0 ) goto not_i2c;
        bx += 2;
#ifdef _Union_FR  //переворачиваем байты только для FR
        cx = (((cx&0x00ff)<<8)|((cx&0xff00)>>8));
#endif
        if ( cs_small != cx)
        {
            err_code =  _CS_Programm;
            Com.all = cs_small;
            ObjPrgData.ProgrammCounter = cx;
            goto Prg_End;
        }
        cs += cs_small;
        cs -= cx&0xff;
        cs -=cx>>8;
        cs_small = 0;

        if (Cfg_str._.ust )
        {
            //Размер блока
            ax  = Load_from_i2c ( 2 ,   bx , (b*)&cx , _Adr_Flash_i2c ) ;
            if ( ax != 0 ) goto not_i2c;
            bx += 2;
#ifdef _Union_FR  //переворачиваем байты только для FR
            cx = (((cx&0x00ff)<<8)|((cx&0xff00)>>8));
#endif
            cs_small -= cx&0xff;
            cs_small -= cx>>8;
            //вычитаем два байта на количество уставок.
            cx -=2;
            //Количество уставок
            ax  = Load_from_i2c ( 2 ,   bx , (b*)&i , _Adr_Flash_i2c ) ;
            if ( ax != 0 ) goto not_i2c;
            bx += 2;
#ifdef _Union_FR  //переворачиваем байты только для FR
            i = (((i&0x00ff)<<8)|((i&0xff00)>>8));
#endif
            cs_small -= i&0xff;
            cs_small -= i>>8;

            //Превышение количества строк.

            if (i >= _MAX_NUM_SETPOINTS)
            {
                err_code =  _SP_Max;
                goto Prg_End;

            }
            Str_quant.SetPoint = i;
            //Сам блок
            ax  = Load_from_i2c ( cx ,   bx , (b*)Ust_Obj_Load , _Adr_Flash_i2c ) ;
            if ( ax != 0 ) goto not_i2c;
            bx+= cx;
            //Расчет контрольной суммы
            for(ax = 0; ax < cx; ++ax)  cs_small -= *((b*)Ust_Obj_Load+ax);
            //Считывание контрольной суммы
            ax  = Load_from_i2c ( 2 ,   bx ,  (b*)&cx , _Adr_Flash_i2c ) ;
            if ( ax != 0 ) goto not_i2c;

            bx += 2;
#ifdef _Union_FR  //переворачиваем байты только для FR
            cx = (((cx&0x00ff)<<8)|((cx&0xff00)>>8));
#endif
            if ( cs_small != cx)
            {
                err_code =  _CS_SP;
                Com.all = cs_small;
                ObjPrgData.ProgrammCounter = cx;
                goto Prg_End;
            }
            cs += cs_small;
            cs -= cx&0xff;
            cs -=cx>>8;
            cs_small = 0;
            //Переставляем байты
            for (i=0; i< Str_quant.SetPoint; ++i)
            {
#ifdef _Union_FR  //переворачиваем байты только для FR
               Ust_Obj_Load[i].num_var  =  (((Ust_Obj_Load[i].num_var&0x00ff) <<8) | ((Ust_Obj_Load[i].num_var&0xff00)>>8));
               Ust_Obj_Load[i].nom      =  (((Ust_Obj_Load[i].nom&0x00ff)     <<8) | ((Ust_Obj_Load[i].nom&0xff00)>>8));
               Ust_Obj_Load[i].abs_nom  =  (((Ust_Obj_Load[i].abs_nom&0x00ff) <<8) | ((Ust_Obj_Load[i].abs_nom&0xff00)>>8));
               Ust_Obj_Load[i].code.all =  (((Ust_Obj_Load[i].code.all&0x00ff)<<8) | ((Ust_Obj_Load[i].code.all&0xff00)>>8));

               Ust_Obj_Load[i].typ = Double_Move( Ust_Obj_Load[i].typ);
               Ust_Obj_Load[i].min = Double_Move( Ust_Obj_Load[i].min);
               Ust_Obj_Load[i].max = Double_Move( Ust_Obj_Load[i].max);
               Ust_Obj_Load[i].dX  = Double_Move( Ust_Obj_Load[i].dX );
#endif
               if (Ust_Obj_Load[i].num_var >= _MAX_NUM_SETPOINTS)
               {
                    err_code =  _SP_Max_Block;
                    Com.all = Ust_Obj_Load[i].num_var;
                    ObjPrgData.ProgrammCounter = i;
                    Stack.Stack_Pointer =   _MAX_NUM_SETPOINTS;
                    goto Prg_End;
               }
               Ust_Obj_Prg[i].text     = Ust_Obj_Load[i].text;
               Ust_Obj_Prg[i].min      = Ust_Obj_Load[i].min;
               Ust_Obj_Prg[i].max      = Ust_Obj_Load[i].max;
               Ust_Obj_Prg[i].dX       = Ust_Obj_Load[i].dX;
               Ust_Obj_Prg[i].nom      = Ust_Obj_Load[i].nom;
               Ust_Obj_Prg[i].abs_nom  = &Ust_Obj_Load[i].abs_nom ;
               Ust_Obj_Prg[i].mask     = 0xff;
               Ust_Obj_Prg[i].ch       = Ust_Obj_Load[i].ch;
               Ust_Obj_Prg[i].code.all = Ust_Obj_Load[i].code.all;

               switch (Ust_Obj_Load[i].code._.type )
               {
                    case 0:

                        if (Ust_Obj_Load[i].num_var >= SVar_quant.qDouble)
                        {
                                err_code =  _SP_Max_Block;
                                Com.all = Ust_Obj_Load[i].num_var;
                                ObjPrgData.ProgrammCounter = i;
                                Stack.Stack_Pointer =  SVar_quant.qDouble ;
                                goto Prg_End;
                        }
                        //передаем в таблицу адрес уставки
                        Ust_Obj_Prg [i].addr = &_or.MemData.dData[Ust_Obj_Load[i].num_var];
                        //Структура типовых значений
                        Type_SetPoints.dData[Ust_Obj_Load[i].num_var] = Ust_Obj_Load[i].typ;
                        break;

                    case 1:

                        if (Ust_Obj_Load[i].num_var >= SVar_quant.qByte)
                        {
                                err_code =  _SP_Max_Block;
                                Com.all = Ust_Obj_Load[i].num_var;
                                ObjPrgData.ProgrammCounter = i;
                                Stack.Stack_Pointer =  SVar_quant.qByte   ;
                                goto Prg_End;
                        }
                        //передаем в таблицу адрес уставки
                        Ust_Obj_Prg [i].addr = &_or.MemData.bData[Ust_Obj_Load[i].num_var];
                        //Структура типовых значений
                        if (!Ust_Obj_Load[i].code._.off_sign )
                        {
                             Type_SetPoints.bData[Ust_Obj_Load[i].num_var] = (sb)Ust_Obj_Load[i].typ;
                        }
                        else Type_SetPoints.bData[Ust_Obj_Load[i].num_var] = (b)Ust_Obj_Load[i].typ;
                        break;

                    case 2:

                        if (Ust_Obj_Load[i].num_var >= SVar_quant.qWord)
                        {
                                err_code =  _SP_Max_Block;
                                Com.all = Ust_Obj_Load[i].num_var;
                                ObjPrgData.ProgrammCounter = i;
                                Stack.Stack_Pointer =  SVar_quant.qWord   ;
                                goto Prg_End;
                        }
                        //передаем в таблицу адрес уставки
                        Ust_Obj_Prg [i].addr = &_or.MemData.wData[Ust_Obj_Load[i].num_var];
                        //Структура типовых значений
                        if (!Ust_Obj_Load[i].code._.off_sign )
                        {
                             Type_SetPoints.wData[Ust_Obj_Load[i].num_var] = (sw)Ust_Obj_Load[i].typ;
                        }
                        else Type_SetPoints.wData[Ust_Obj_Load[i].num_var] = (w)Ust_Obj_Load[i].typ;
                        break;

                    case 4:

                        if (Ust_Obj_Load[i].num_var >= SVar_quant.qLWord)
                        {
                                err_code =  _SP_Max_Block;
                                Com.all = Ust_Obj_Load[i].num_var;
                                ObjPrgData.ProgrammCounter = i;
                                Stack.Stack_Pointer =  SVar_quant.qLWord   ;
                                goto Prg_End;
                        }
                        //передаем в таблицу адрес уставки
                        Ust_Obj_Prg [i].addr = &_or.MemData.lwData[Ust_Obj_Load[i].num_var];
                        //Структура типовых значений
                        if (!Ust_Obj_Load[i].code._.off_sign )
                        {
                             Type_SetPoints.lwData[Ust_Obj_Load[i].num_var] = (slw)Ust_Obj_Load[i].typ;
                        }
                        else Type_SetPoints.lwData[Ust_Obj_Load[i].num_var] = (lw)Ust_Obj_Load[i].typ;
                        break;

                    default:
                        err_code =  _SP_No_Type;
                        goto Prg_End;
               }

            }

        }

        if (Cfg_str._.ind )
        {
            //Размер блока
            ax  = Load_from_i2c ( 2 ,   bx , (b*)&cx , _Adr_Flash_i2c ) ;
            if ( ax != 0 ) goto not_i2c;
            bx += 2;
#ifdef _Union_FR  //переворачиваем байты только для FR

            cx = (((cx&0x00ff)<<8)|((cx&0xff00)>>8));
#endif
            cs_small -= cx&0xff;
            cs_small -= cx>>8;
            //вычитаем два байта на количество строк индикации.
            cx -=2;
            //Количество строк
            ax  = Load_from_i2c ( 2 ,   bx , (b*)&i , _Adr_Flash_i2c ) ;
            if ( ax != 0 ) goto not_i2c;
            bx += 2;
#ifdef _Union_FR  //переворачиваем байты только для FR
            i = (((i&0x00ff)<<8)|((i&0xff00)>>8));
#endif
            cs_small -= i&0xff;
            cs_small -= i>>8;

            //Превышение количества строк.

            if (i >= _MAX_NUM_IND)
            {
                err_code =  _Ind_Max;
                goto Prg_End;

            }
            Str_quant.VarInd = i;
            //Сам блок
            ax  = Load_from_i2c ( cx ,   bx , (b*)Ind_Obj_Load , _Adr_Flash_i2c ) ;
            if ( ax != 0 ) goto not_i2c;
            bx+= cx;
            //Расчет контрольной суммы
            for(ax = 0; ax < cx; ++ax)  cs_small -= *((b*)Ind_Obj_Load+ax);
            //Считывание контрольной суммы
            ax  = Load_from_i2c ( 2 ,   bx ,  (b*)&cx , _Adr_Flash_i2c ) ;
            if ( ax != 0 ) goto not_i2c;
            bx += 2;
#ifdef _Union_FR  //переворачиваем байты только для FR
            cx = (((cx&0x00ff)<<8)|((cx&0xff00)>>8));
#endif
            if ( cs_small != cx)
            {
                err_code =  _CS_Ind;
                Com.all = cs_small;
                ObjPrgData.ProgrammCounter = cx;
                goto Prg_End;
            }
            cs += cs_small;
            cs -= cx&0xff;
            cs -=cx>>8;
            cs_small = 0;
            //Переставляем байты и заполняем таблицу.
#ifdef _Union_FR  //переворачиваем байты только для FR
            for (i=0; i< Str_quant.VarInd; ++i)
            {
               Ind_Obj_Load[i].num_var1  =  (((Ind_Obj_Load[i].num_var1&0x00ff)<<8)  | ((Ind_Obj_Load[i].num_var1&0xff00)>>8));
               Ind_Obj_Load[i].num_var2  =  (((Ind_Obj_Load[i].num_var2&0x00ff)<<8)  | ((Ind_Obj_Load[i].num_var2&0xff00)>>8));
               Ind_Obj_Load[i].nom1      =  (((Ind_Obj_Load[i].nom1&0x00ff)<<8)      | ((Ind_Obj_Load[i].nom1&0xff00)>>8));
               Ind_Obj_Load[i].nom2      =  (((Ind_Obj_Load[i].nom2&0x00ff)<<8)      | ((Ind_Obj_Load[i].nom2&0xff00)>>8));
               Ind_Obj_Load[i].abs_nom1  =  (((Ind_Obj_Load[i].abs_nom1&0x00ff)<<8)  | ((Ind_Obj_Load[i].abs_nom1&0xff00)>>8));
               Ind_Obj_Load[i].abs_nom2  =  (((Ind_Obj_Load[i].abs_nom2&0x00ff)<<8)  | ((Ind_Obj_Load[i].abs_nom2&0xff00)>>8));
               Ind_Obj_Load[i].code1.all =  (((Ind_Obj_Load[i].code1.all&0x00ff)<<8) | ((Ind_Obj_Load[i].code1.all&0xff00)>>8));
               Ind_Obj_Load[i].code2.all =  (((Ind_Obj_Load[i].code2.all&0x00ff)<<8) | ((Ind_Obj_Load[i].code2.all&0xff00)>>8));
               //fr5[i] = (w*)&Ind_Obj_Load[i];
            }
#endif
        }

        if (Cfg_str._.av_msg )
        {
            //Размер блока
            ax  = Load_from_i2c ( 2 ,   bx , (b*)&cx , _Adr_Flash_i2c ) ;
            if ( ax != 0 ) goto not_i2c;
            bx += 2;
#ifdef _Union_FR  //переворачиваем байты только для FR
            cx = (((cx&0x00ff)<<8)|((cx&0xff00)>>8));
#endif
            cs_small -= cx&0xff;
            cs_small -= cx>>8;
            //вычитаем два байта на количество сообщений.
            cx -=2;
            //Количество
            ax  = Load_from_i2c ( 2 ,   bx , (b*)&i , _Adr_Flash_i2c ) ;
            if ( ax != 0 ) goto not_i2c;
            bx += 2;
#ifdef _Union_FR  //переворачиваем байты только для FR
            i = (((i&0x00ff)<<8)|((i&0xff00)>>8));
#endif
            cs_small -= i&0xff;
            cs_small -= i>>8;
            if (i >= 32)
            {
                err_code =  _Av_msg_max;
                goto Prg_End;

            }
            Str_quant.Av_Msg = i;
            //Сам блок
            ax  = Load_from_i2c ( cx ,   bx , (b*)Tabl_Msg_obj.Avar , _Adr_Flash_i2c ) ;
            if ( ax != 0 ) goto not_i2c;
            bx+= cx;
            //Расчет контрольной суммы
            for(ax = 0; ax < cx; ++ax)  cs_small -= *((b*)Tabl_Msg_obj.Avar+ax);
            //Считывание контрольной суммы
            ax  = Load_from_i2c ( 2 ,   bx ,  (b*)&cx , _Adr_Flash_i2c ) ;
            if ( ax != 0 ) goto not_i2c;
            bx += 2;
#ifdef _Union_FR  //переворачиваем байты только для FR
            cx = (((cx&0x00ff)<<8)|((cx&0xff00)>>8));
#endif
            if ( cs_small != cx)
            {
                err_code =  _CS_AvMsg;
                Com.all = cs_small;
                ObjPrgData.ProgrammCounter = cx;
                goto Prg_End;
            }
            cs += cs_small;
            cs -= cx&0xff;
            cs -=cx>>8;
            cs_small = 0;
        }

        if (Cfg_str._.pr_msg )
        {
            //Размер блока
            ax  = Load_from_i2c ( 2 ,   bx , (b*)&cx , _Adr_Flash_i2c ) ;
            if ( ax != 0 ) goto not_i2c;
            bx += 2;
#ifdef _Union_FR  //переворачиваем байты только для FR
            cx = (((cx&0x00ff)<<8)|((cx&0xff00)>>8));
#endif
            cs_small -= cx&0xff;
            cs_small -= cx>>8;
            //вычитаем два байта на количество сообщений.
            cx -=2;

            //Количество
            ax  = Load_from_i2c ( 2 ,   bx , (b*)&i , _Adr_Flash_i2c ) ;
            if ( ax != 0 ) goto not_i2c;
            bx += 2;
#ifdef _Union_FR  //переворачиваем байты только для FR
            i = (((i&0x00ff)<<8)|((i&0xff00)>>8));
#endif
            cs_small -= i&0xff;
            cs_small -= i>>8;
            if (i >= 32)
            {
                err_code =  _Pr_msg_max;
                goto Prg_End;

            }
            Str_quant.Pr_Msg = i;
            //Сам блок
            ax  = Load_from_i2c ( cx ,   bx , (b*)Tabl_Msg_obj.Predupr , _Adr_Flash_i2c ) ;
            if ( ax != 0 ) goto not_i2c;
            bx+= cx;
            //Расчет контрольной суммы
            for(ax = 0; ax < cx; ++ax)  cs_small -= *((b*)Tabl_Msg_obj.Predupr+ax);
            //Считывание контрольной суммы
            ax  = Load_from_i2c ( 2 ,   bx ,  (b*)&cx , _Adr_Flash_i2c ) ;
            if ( ax != 0 ) goto not_i2c;
            bx += 2;
#ifdef _Union_FR  //переворачиваем байты только для FR
            cx = (((cx&0x00ff)<<8)|((cx&0xff00)>>8));
#endif
            if ( cs_small != cx)
            {
                err_code =  _CS_PrMsg;
                Com.all = cs_small;
                ObjPrgData.ProgrammCounter = cx;
                goto Prg_End;
            }
            cs += cs_small;
            cs -= cx&0xff;
            cs -=cx>>8;
            cs_small = 0;

        }

        if (Cfg_str._.srv_msg )
        {
            //Размер блока
            ax  = Load_from_i2c ( 2 ,   bx , (b*)&cx , _Adr_Flash_i2c ) ;
            if ( ax != 0 ) goto not_i2c;
            bx += 2;
#ifdef _Union_FR  //переворачиваем байты только для FR
            cx = (((cx&0x00ff)<<8)|((cx&0xff00)>>8));
#endif
            cs_small -= cx&0xff;
            cs_small -= cx>>8;
            //вычитаем два байта на количество сообщений.
            cx -=2;

            //Количество
            ax  = Load_from_i2c ( 2 ,   bx , (b*)&i , _Adr_Flash_i2c ) ;
            if ( ax != 0 ) goto not_i2c;
            bx += 2;
#ifdef _Union_FR  //переворачиваем байты только для FR
            i = (((i&0x00ff)<<8)|((i&0xff00)>>8));
#endif
            cs_small -= i&0xff;
            cs_small -= i>>8;
            if (i >= 32)
            {
                err_code =  _Srv_msg_max;
                goto Prg_End;

            }
            Str_quant.Srv_Msg = i;
            //Сам блок
            ax  = Load_from_i2c ( cx ,   bx , (b*)Tabl_Msg_obj.Service , _Adr_Flash_i2c ) ;
            if ( ax != 0 ) goto not_i2c;
            bx+= cx;
            //Расчет контрольной суммы
            for(ax = 0; ax < cx; ++ax)  cs_small -= *((b*)Tabl_Msg_obj.Service+ax);
            //Считывание контрольной суммы
            ax  = Load_from_i2c ( 2 ,   bx ,  (b*)&cx , _Adr_Flash_i2c ) ;
            if ( ax != 0 ) goto not_i2c;
            bx += 2;
#ifdef _Union_FR  //переворачиваем байты только для FR
            cx = (((cx&0x00ff)<<8)|((cx&0xff00)>>8));
#endif
            if ( cs_small != cx)
            {
                err_code =  _CS_SrvMsg;
                Com.all = cs_small;
                ObjPrgData.ProgrammCounter = cx;
                goto Prg_End;
            }
            cs += cs_small;
            cs -= cx&0xff;
            cs -=cx>>8;
            cs_small = 0;

        }

        if (Cfg_str._.base )
        {
            //Размер блока имен стандартных переменных
            ax  = Load_from_i2c ( 2 ,   bx , (b*)&cx , _Adr_Flash_i2c ) ;
            if ( ax != 0 ) goto not_i2c;
            bx += 2;
#ifdef _Union_FR  //переворачиваем байты только для FR
            cx = (((cx&0x00ff)<<8)|((cx&0xff00)>>8));
#endif
            cs_small -= cx&0xff;
            cs_small -= cx>>8;
            //вычитаем два байта на количество сообщений.
            cx -=2;

            //Количество стандартных переменных
            ax  = Load_from_i2c ( 2 ,   bx , (b*)&i , _Adr_Flash_i2c ) ;
            if ( ax != 0 ) goto not_i2c;
            bx += 2;
#ifdef _Union_FR  //переворачиваем байты только для FR

            i = (((i&0x00ff)<<8)|((i&0xff00)>>8));
#endif
            cs_small -= i&0xff;
            cs_small -= i>>8;

            Str_quant.VarBase = i;

            //Превышение количества
            if (Str_quant.VarBase > svar[0].size)
            {
                err_code =  _BVarQuantiy;
                goto Prg_End;
            }
            i = size_vartab1/sizeof(struct namevar);
            for (ax = 0; ax < i; ++ax )
            {
               tmp_std_var[ax][0] = 0;
            }

            //Блок имен стандартных переменных
            ax  = Load_from_i2c ( cx ,   bx , (b*)tmp_std_var , _Adr_Flash_i2c ) ;
            if ( ax != 0 ) goto not_i2c;
            bx += cx;

            //Расчет контрольной суммы
            for(ax = 0; ax < cx; ++ax)  cs_small -= *((b*)tmp_std_var+ax);

            //Контрольная сумма
            ax  = Load_from_i2c ( 2 ,   bx ,  (b*)&cx , _Adr_Flash_i2c ) ;
            if ( ax != 0 ) goto not_i2c;
            bx+=2;
#ifdef _Union_FR  //переворачиваем байты только для FR

            cx = (((cx&0x00ff)<<8)|((cx&0xff00)>>8));
#endif
            if ( cs_small != cx)
            {
                err_code =  _CS_Base;
                Com.all = cs_small;
                ObjPrgData.ProgrammCounter = cx;
                goto Prg_End;
            }
            cs += cs_small;
            cs -= cx&0xff;
            cs -=cx>>8;

            cs_small = 0;

            for ( ax = 0; tmp_std_var[ax][0] != 0; ++ax)
            {
                Std_Vars[ax] = 0xffff;
                for(i = 0; i < svar[_CAN0_Port].size; ++i)
                {
                    pt1 = (b*)var_tab1[i].name;
                    pt2 = tmp_std_var[ax];

                    while ( *pt1 == *pt2 )//Символы имени совпали
                    {

                        if ( *pt2 == 0 )//Совпало все имя
                        {
                            Std_Vars[ax] = i;
                        }

                        pt1++,pt2++;//Следующий смвол
                    }
                    if (Std_Vars[ax] != 0xffff ) break;
                }

                if (i >= svar[_CAN0_Port].size )
                {
                    err_code = _Err_Base;
                    Com.all = *pt2;
                    ObjPrgData.ProgrammCounter = i;
                    goto Prg_End;
                }
            }

        }
        if (Cfg_str._.func )
        {
            //Размер блока функций
            ax  = Load_from_i2c ( 2 ,   bx , (b*)&cx , _Adr_Flash_i2c ) ;
            if ( ax != 0 ) goto not_i2c;
            bx += 2;
#ifdef _Union_FR  //переворачиваем байты только для FR
            cx = (((cx&0x00ff)<<8)|((cx&0xff00)>>8));
#endif
            cs_small -= cx&0xff;
            cs_small -= cx>>8;
            //вычитаем два байта на количество .
            cx -=2;
            //Количество функций
            ax  = Load_from_i2c ( 2 ,   bx , (b*)&i , _Adr_Flash_i2c ) ;
            if ( ax != 0 ) goto not_i2c;
            bx += 2;
#ifdef _Union_FR  //переворачиваем байты только для FR

            i = (((i&0x00ff)<<8)|((i&0xff00)>>8));
#endif
            cs_small -= i&0xff;
            cs_small -= i>>8;
            Str_quant.Function = i;
            if (i > _Numb_Basef)
            {
                err_code =  _Num_Base_func;
                goto Prg_End;
            }

            //Блок функций

            ax  = Load_from_i2c ( cx ,   bx , tmp_func, _Adr_Flash_i2c ) ;
            if ( ax != 0 ) goto not_i2c;
            bx += cx;
            i= 0;
            //Заполнение таблицы функций.Заодно и расчет контрольной суммы.
            dx = 0;

            while( ax < cx)
            {
                for ( i= 0; i < _Max_Name_Func; ++i)
                {
                   cs_small -=tmp_func[ax];
                   tmp_txt[i] = tmp_func[ax];
                   if (++ax >= cx)
                   {
                        err_code =  _Basef_load_err;
                        goto Prg_End;
                   }
                }

                //Поиск имени базовой функции в таблице

                Base_func_decoding[ dx ]= _Numb_Basef+1;

                for(i = 0; i < _Numb_Basef; ++i)
                {
                    pt1 = (b*)Basef_def[i].Name;
                    pt2 = tmp_txt;

                    while ( *pt1 == *pt2 )//Символы имени совпали
                    {

                        if ( *pt2 == 0 )//Совпало все имя
                        {
                            Base_func_decoding[ dx ]= i;
                        }

                        pt1++,pt2++;//Следующий смвол
                    }
                }
                //Не нашли такого имени - выдаем ошибку
                if ( Base_func_decoding[ dx ] >=  _Numb_Basef)
                {
                    err_code = _Err_Basef_Name;
                    Com.all = ax;
                    ObjPrgData.ProgrammCounter = dx;
                    for (i= 0; i < _Max_Name_Func; ++i )
                    {
                       Operand_Tmp[i].all = tmp_txt[i];
                    }
                    goto Prg_End;
                }
                //Смотрим количество блоков
                cs_small -=tmp_func[ax];
                cs_small -=tmp_func[ax+1];

                i = ((w)tmp_func[ax+1]<<8)+(tmp_func[ax]);
                if (i > Basef_def[Base_func_decoding[ dx ]].Numb_blocks )
                {
                    err_code = _Err_Basef_nBlock;
                    ObjPrgData.ProgrammCounter = i;
                    Stack.Stack_Pointer = dx;
                    goto Prg_End;
                }

                ax +=2;

                if (ax > cx)
                {
                    err_code =  _Basef_load_err;
                    goto Prg_End;
                }
                ++dx;
            }

            //Контрольная сумма
            ax  = Load_from_i2c ( 2 ,   bx ,  (b*)&cx , _Adr_Flash_i2c ) ;
            if ( ax != 0 ) goto not_i2c;
            bx+=2;
#ifdef _Union_FR  //переворачиваем байты только для FR

            cx = (((cx&0x00ff)<<8)|((cx&0xff00)>>8));
#endif
            if ( cs_small != cx)
            {
                err_code =  _CS_Basef;
                Com.all = cs_small;
                ObjPrgData.ProgrammCounter = cx;
                goto Prg_End;
            }
            cs += cs_small;
            cs -= cx&0xff;
            cs -=cx>>8;
            cs_small = 0;

            //Начальная инициализация функций
            for ( i=0; i < _Numb_blocks_bIZUD;++i)
            {
               b_timeIZUd[i].first = 0;
            }

            for ( i=0; i < _Numb_blocks_bIZUI;++i)
            {
               b_timeIZUi[i].first = 0;
            }

            for ( i=0; i < _Numb_blocks_bZI;++i)
            {
               base_ZIstr[i].first = 0;
            }

            for ( i=0; i < _Numb_blocks_bPI_reg;++i)
            {
               bPI_str[i].first = 0;
            }

            for ( i=0; i < _Numb_blocks_bFiltr;++i)
            {
               bfilstr[i].first = 0;
            }
        }
        //Считывание даты/времени компиляции
        ax  = Load_from_i2c ( 6 ,   bx , (b*)comp_date , _Adr_Flash_i2c ) ;
        if ( ax != 0 ) goto not_i2c;
        bx += 6;

        //Расчет контрольной суммы
        for(ax = 0; ax < 6; ++ax)  cs -= comp_date[ax];

        //Считывание общей контрольной суммы
        ax  = Load_from_i2c ( 2 ,   bx ,  (b*)&cx , _Adr_Flash_i2c ) ;
        if ( ax != 0 ) goto not_i2c;
        bx += 2;
#ifdef _Union_FR  //переворачиваем байты только для FR
        cx = (((cx&0x00ff)<<8)|((cx&0xff00)>>8));
#endif
        if ( cs != cx)
        {
            err_code =  _CS;
            Com.all = cs;
            ObjPrgData.ProgrammCounter = cx;
            goto Prg_End;
        }
       // addr_Ctrl = bx;
        ax  = Load_from_i2c ( 2 ,   bx ,  (b*)&cx , _Adr_Flash_i2c ) ;
        if ( ax != 0 ) goto not_i2c;

        //Проверяем первую загрузку программы
        if ( (cx != 0x1234)||(( _r.Begin_Code &0x8000)!=0))
        {
            if (Cfg_str._.ust != 0)
            {
                _or.MemData =  Type_SetPoints;
                if (  (_r.Begin_Code &0x8000)==0)
                {
                    Chek_sum ( sizeof( struct oBlok_Ustavok ) , (b*)&_or ) ;
                    ax= Save_into_i2c ( sizeof( struct oBlok_Ustavok ) , (b*)&_or ,  _or_adr_i2c,_Adr_Flash_i2c  ) ;

                }
                else ax = 0;
            }
            cx = 0x1234;
            ax += Save_into_i2c ( 2 , (b*)&cx , bx, _Adr_Flash_i2c );
            if ( ax != 0 ) goto not_i2c;
        }
        //Заполняем таблицу для индикации именно тут, потому что в индикации могут быть базовые переменные,
        //и нам нужна заполненная таблица базовых переменных
        for (i=0; i< Str_quant.VarInd; ++i)
        {

            Ind_Obj_Prg[i].code[0].all = Ind_Obj_Load[i].code1.all;
            Ind_Obj_Prg[i].code[1].all = Ind_Obj_Load[i].code2.all;
            Ind_Obj_Prg[i].txt         = Ind_Obj_Load[i].txt;
            Ind_Obj_Prg[i].txt2[0]     = Ind_Obj_Load[i].unit1;
            //Если  code2.all = 0, то второй переменной нет
            if (Ind_Obj_Load[i].code2.all == 0 ) Ind_Obj_Prg[i].txt2[1] =  0 ;
            else  Ind_Obj_Prg[i].txt2[1]     = Ind_Obj_Load[i].unit2;

            Ind_Obj_Prg[i].nom[0]      = Ind_Obj_Load[i].nom1;
            Ind_Obj_Prg[i].nom[1]      = Ind_Obj_Load[i].nom2;
            Ind_Obj_Prg[i].abs_nom[0]  = &Ind_Obj_Load[i].abs_nom1;
            Ind_Obj_Prg[i].abs_nom[1]  = &Ind_Obj_Load[i].abs_nom2;
            //Передаем адреса переменных в зависимости от их типа
            switch (Ind_Obj_Load[i].code1._.type )
            {

                case  0 :   //Double
                            Ind_Obj_Prg[i].adr[0] = &MemData.dData[Ind_Obj_Load[i].num_var1];
                            break;
                case  1 :   //Byte
                            Ind_Obj_Prg[i].adr[0] = &MemData.bData[Ind_Obj_Load[i].num_var1];
                            break;
                case  2 :   //Word
                            Ind_Obj_Prg[i].adr[0] = &MemData.wData[Ind_Obj_Load[i].num_var1];
                            break;
                case  4 :   //Long
                            Ind_Obj_Prg[i].adr[0] = &MemData.lwData[Ind_Obj_Load[i].num_var1];
                            break;
                case  7 :   //Базовые
                            Ind_Obj_Prg[i].adr[0] = var_tab1[Std_Vars[Ind_Obj_Load[i].num_var1]].addr;
                            switch (var_tab1[Std_Vars[Ind_Obj_Load[i].num_var1]].type )
                            {
                                case  1 :
                                          Ind_Obj_Prg[i].code[0]._.type = 1;
                                          break;
                                default:
                                case  2 :
                                case  3 :
                                          Ind_Obj_Prg[i].code[0]._.type = 2;
                                          break;
                                case  4 :
                                          Ind_Obj_Prg[i].code[0]._.type = 4;
                                          break;
                                case  6 :
                                          Ind_Obj_Prg[i].code[0]._.type = 0;
                                          break;
                            }

                            break;
                default:
                    err_code =  _ind_No_Type;
                    goto Prg_End;

            }

            switch (Ind_Obj_Load[i].code2._.type )
            {
                case  0 :
                            Ind_Obj_Prg[i].adr[1] = &MemData.dData[Ind_Obj_Load[i].num_var2];
                            break;
                case  1 :
                            Ind_Obj_Prg[i].adr[1] = &MemData.bData[Ind_Obj_Load[i].num_var2];
                            break;
                case  2 :
                            Ind_Obj_Prg[i].adr[1] = &MemData.wData[Ind_Obj_Load[i].num_var2];
                            break;
                case  4 :
                            Ind_Obj_Prg[i].adr[1] = &MemData.lwData[Ind_Obj_Load[i].num_var2];
                            break;
                case  7 :
                            Ind_Obj_Prg[i].adr[1] = var_tab1[Std_Vars[Ind_Obj_Load[i].num_var2]].addr;
                            switch (var_tab1[Std_Vars[Ind_Obj_Load[i].num_var2]].type )
                            {
                                case  1 :
                                          Ind_Obj_Prg[i].code[1]._.type = 1;
                                          break;
                                default:
                                case  2 :
                                case  3 :
                                          Ind_Obj_Prg[i].code[1]._.type = 2;
                                          break;
                                case  4 :
                                          Ind_Obj_Prg[i].code[1]._.type = 4;
                                          break;
                                case  6 :
                                          Ind_Obj_Prg[i].code[1]._.type = 0;
                                          break;
                            }
                            break;
                default:
                    err_code =  _ind_No_Type;
                    goto Prg_End;

            }

        }


    }
    //long_tmp.all = 0;

    Reg_AvarMsgFirst_obj = 0 ;
    Reg_AvarMsg_obj      = 0 ;
    Reg_PreduprMsg_obj   = 0 ;
    Reg_ServiceMsg_obj   = 0 ;
    // _End_programm - загрузка прошла нормально
    err_code = _End_programm;
  }
  else
  {
    ObjPrgData.ProgrammCounter = 0;
    Stack.Stack_Pointer = 0;
    //ObjArgData.counter = 0;
    //ObjArgData.ret_point = 0;
    cx = 0;
    Com.all = 0;
  //  mUSEL_clr() ;
    while ((err_code == 0)&&(++cx < fr1))
    {
        //Получаем  код команды
        Com.all = ObjPrgData.Prog[ObjPrgData.ProgrammCounter];
        ++ObjPrgData.ProgrammCounter;
        //Пришла команда окончания, выдаем код завершения
        if ( Com._.Command == 0 ) err_code = _End_programm;
        else
        {
            if (Com._.Command >= _Max_Func  )
            {
              err_code = _Err_Comm;
            }
            else
            {
                Operand_Tmp[0].all = 0xffff;
                if (Com._.Noperand == 0x0f )
                {
                    ax = ObjPrgData.Prog[ObjPrgData.ProgrammCounter];
                    ++ObjPrgData.ProgrammCounter;
                }
                else
                {
                    ax =  Com._.Noperand;
                }

                //Выбираем операнды
                for (i=0; i< ax; ++i)
                {
                    Operand_Tmp[i].all = ObjPrgData.Prog[ObjPrgData.ProgrammCounter];
                    ++ObjPrgData.ProgrammCounter;
                }
                Operand_Tmp[_Tmp_Opers_max].all = ax;
                err_code = (*Oprg[Com._.Command])( Operand_Tmp );
                if (ObjPrgData.ProgrammCounter > ObjPrgData.Size)  err_code = _Oveflow;
                //fr2 = Stack.Stack_Pointer;
              //  ++cx;
            }
        }

    }
  //  mUSEL_set() ;

    if (err_code == 0)
    {
       err_code = _End_programm ;
    }
  }
Prg_End:
/*  if ( ax !=0)
  { */
    ErrRep.code = err_code|(code<<12);
    if ( err_code != _End_programm)
    {
        ErrRep.Comm = Com.all;
        ErrRep.PC   = ObjPrgData.ProgrammCounter;
        ErrRep.SP   = Stack.Stack_Pointer ;
        for ( i = 0; i< _Tmp_Opers_max; ++i)
        {
            ErrRep.Oper[i] =  Operand_Tmp[i].all ;
        }
        ObjSrv_bit._.InWork  = 0 ;

    }
    else
    {
        ObjSrv_bit._.InWork  = 1 ;
        err_code = 0;
    }
 // }
  return err_code;
}
#ifdef _Union_FR  //переворачиваем байты только для FR

//--------------------------------
double Double_Move( double in)
{
    union str_double d_lax, d_lbx;
    d_lax.all =  in;

    d_lbx.bt[0] = d_lax.bt[7] ;
    d_lbx.bt[1] = d_lax.bt[6] ;
    d_lbx.bt[2] = d_lax.bt[5] ;
    d_lbx.bt[3] = d_lax.bt[4] ;
    d_lbx.bt[4] = d_lax.bt[3] ;
    d_lbx.bt[5] = d_lax.bt[2] ;
    d_lbx.bt[6] = d_lax.bt[1] ;
    d_lbx.bt[7] = d_lax.bt[0] ;
    return d_lbx.all;
}

#endif
