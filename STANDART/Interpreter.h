
#ifndef _interpreter_h
#define _interpreter_h

#include "functions.h"

//---------------���� ������----------------------------------

#define   _No_Link          0x01  //��� ���� � i2�
#define   _ErrCtrlCode      0x02  //����������� ����� �������� �� ��������� � �����������
#define   _VarQuantiy       0x03  //���������� ����������� ���������� ���������� ����������� ���������� ����������
#define   _SPQuantiy        0x04  //���������� ����������� ���������� ������� ����������� ���������� ����������
#define   _LenCode          0x05  //��������� ����� ����� ��������
#define   _CS_Programm      0x06  //������������ ����������� ����� ����� ��������
#define   _SP_Max           0x07  //����� ���������� ������� ��������� ����������� ����������
#define   _CS_SP            0x08  //������������ ����������� ����� ����� �������
#define   _SP_Max_Block     0x09  //����� ������� ��������� �� ������, ����������� �� ��������� ���������� �����
#define   _SP_No_Type       0x0A  //������������� ��� �������
#define   _ind_No_Type      0x0B  //������������� ��� ��� ���������
#define   _Ind_Max          0x0C  //��������� ����� ����� ���������� ��� ��������� ��������� ����������� ���������
#define   _CS_Ind           0x0D  //������������ ����������� ����� ����� ���������
#define   _Av_msg_max       0x0E  //��������� ����� ��������� ���������
#define   _CS_AvMsg         0x0F  //������������ ����������� ����� ����� ��������� ���������
#define   _Pr_msg_max       0x10  //��������� ����� ����������������� ���������
#define   _CS_PrMsg         0x11  //������������ ����������� ����� ����� ����������������� ���������
#define   _Srv_msg_max      0x12  //��������� ����� ��������� ���������
#define   _CS_SrvMsg        0x13  //������������ ����������� ����� ����� ��������� ���������
#define   _BVarQuantiy      0x14  //���������� ���������� ��������� ������� ����������
#define   _CS_Base          0x15  //������������ ����������� ����� ����� ������� ����������
#define   _Err_Base         0x16  //���������� ����� ������ ���������� ��� � �������
#define   _CS               0x17  //������������ ����������� ����� ����� ������������ �����
#define   _Num_Base_func    0x18  //���������� ������� ������� ������ ����������
#define   _Basef_load_err   0x19  //������ �������� ����� ������� �������
#define   _Err_Basef_Name   0x1A  //������������ ��� ������� �������
#define   _Err_Basef_nBlock 0x1B  //���������� ���������� ����� ������ ������� �������
#define   _CS_Basef         0x1C  //������������ ����������� ����� ����� ������� �������

#define   _Err_Comm         0x30  //�������� ��������
#define   _Oveflow          0x31  //������� �������� ����� �� ������� ����� ��������
#define   _Goto_Oveflow     0x32  //��������� �������� ��������� �� ������ �� ��������� ����� ��������
#define   _AvMsg_Oveflow    0x33  //����� ���������� ��������� ��������� ���������� ��������
#define   _PrMsg_Oveflow    0x34  //����� ������������������ ��������� ��������� ���������� ��������
#define   _SrvMsg_Oveflow   0x35  //����� ���������� ��������� ��������� ���������� ��������
#define   _Err_Oper         0x36  //������ � ���������
#define   _Stack_Oveflow    0x37  //������������ �����
#define   _Stack_Underflow  0x38  //C��� ����
#define   _Wrong_Base_func  0x39  //����� ��������� ����� ������� �������

#define   _End_programm     0xfff //�������� ���������� ���������� ���������

//------------------------------------------------------------

#define _MAX_NUM_OPER      16 // ������������ ���������� ��������� � ����� ��������
#define _MAX_NUM_BITS      511 // ������������ ��������� ���� ��� ������� ����������
#define _MAX_NUM_BYTE      511 // ������������ ����� ������������ ����������
#define _MAX_NUM_WORD      511 // ������������ ����� ������������ ����������
#define _MAX_NUM_LWORD     511 // ������������ ����� ��������������� ����������
#define _MAX_NUM_DOUBLE    511 // ������������ ����� ���������� � ��������� ������
#define _MAX_NUM_SP_BYTE   32
#define _MAX_NUM_SP_WORD   32
#define _MAX_NUM_SP_LWORD  32
#define _MAX_NUM_SP_DOUBLE 32
//����� �������� �������
#define _MAX_NUM_SETPOINTS   _MAX_NUM_SP_BYTE+_MAX_NUM_SP_WORD+_MAX_NUM_SP_LWORD+_MAX_NUM_SP_DOUBLE

#define _MAX_NUM_IND    20   // ������������ ����� ����� ��� ���������
#define _SIZE_IND_TAB   1   // ������ ������� �������� ����� ���������� ��� ��������� � i2c
#define _MAX_SIZE_IND_TAB    _MAX_NUM_IND*_SIZE_IND_TAB
#define _MAX_NUM_ARG    16  //������������ ����� ���������� � �������
//------------------------------------------------------------
// ���� ���������
#define _VALUE       0x00 // ����������
#define _SETPOINT    0x01 // �������
#define _BASE        0x02 // ������� ���������� (�� �������� ��)
#define _CONST       0x03 // ���������
#define _ARGUMENT    0x04 // �������� �������

// ����������� ��������
#define _1BYTE       0x00 // ����� ����������� �������
#define _2BYTE       0x01 // ����� ����������� �������
#define _4BYTE       0x02 // ����� �������������� �������
#define _FLOAT       0x03 // �������������� ������� � ��������� ������
//#define _BIT         0x04 // ������� �������
#define _VOID        0x05 // ����������� (��� ����������� �������)

#define _STACK_SIZE  1500 //������ ����� � ������
#define _Tmp_Opers_max 64
//----------------------
#define _comp_Date  comp_date[0]
#define _comp_Month comp_date[1]
#define _comp_Year  comp_date[2]
#define _comp_Hour  comp_date[3]
#define _comp_Min   comp_date[4]
#define _comp_Sec   comp_date[5]

//---������� �������---

//������������ ������ ����� �������

#define _Max_Name_Func   12 //10 �������� + 0 + 1 ���� ������������

struct  Base_func_def
{
  const char*  Name; //��� �������
  word Numb_blocks;  //���������� ������������ ������
};

union Command
{
  word all;
  struct
  {
#ifdef _Union_FR   //�������������� ����� ������ ��� FR

    word Command  : 12; // ��� �������
    word Noperand : 4; // ���������� ���������
#else
    word Noperand : 4; // ���������� ���������
    word Command  : 12; // ��� �������
#endif
  }_;
};

/*------------------------------------------------------------
union bwlw
{
   lword  all;
   struct
   {
    word   h;
    word   l;
   }wrd;
   struct
   {
    byte   hh;
    byte   hl;
    byte   lh;
    byte   ll;
   }bt;
};
//------------------------------------------------------------
union str_word_byte
{
   word  all;
   struct
   {
    byte   h;
    byte   l;
   }_;
};*/
//--------------------------------------------------------------
struct Var_quant
{
   word    qByte;
   word    qWord;
   word    qLWord;
   word    qDouble;
};
//--------------------------------------------------------------
union FormatCode
{
  word all;
  struct
  {
#ifdef _Union_FR   //�������������� ����� ������ ��� FR
     word rezerv     : 1;
     word invert     : 1;  // ����������� ������� � ���� 1/x
     word print_type : 2;  // ����������� ������� � 16-���� ���� 0/1 - 10/16-������ ���
     word zapr       : 1;  // ��� ������������� � form2()-�������� �������
     word off_sign   : 1;  // '=1'- ������ ���������� �����
     word celoe      : 4;  // ���������� ���� ����� �����
     word drob       : 3;  // ���������� ���� ������� �����
     word type       : 3;  // ��� ����������: 0- double, 1-�����������, 2-�����������, 4-��������������, 7 - �������
#else
     word type       : 3;  // ��� ����������: 0- double, 1-�����������, 2-�����������, 4-��������������, 7 - �������
     word drob       : 3;  // ���������� ���� ������� �����
     word celoe      : 4;  // ���������� ���� ����� �����
     word off_sign   : 1;  // '=1'- ������ ���������� �����
     word zapr       : 1;  // ��� ������������� � form2()-�������� �������
     word print_type : 2;  // ����������� ������� � 16-���� ���� 0/1 - 10/16-������ ���
     word invert     : 1;  // ����������� ������� � ���� 1/x
     word rezerv     : 1;
#endif

  }_;
};
//------------------------------------------------------------

// ��������� ������� ���������, ����������� �����
struct Ind_Table_Cod
{
  byte txt[ 16 ];  // ����� ��� ����������� ������������ ����������
  word num_var1; // ����� ��������� 1 � ������� ����������
  word num_var2; // ����� ��������� 2 � ������� ����������
  word nom1;              // ����������� �������� ��������� 1
  word nom2;              // ����������� �������� ��������� 2
  byte unit1[ 4]; // ����� ������� ��������� ��������� 1
  byte unit2[ 4]; // ����� ������� ��������� ��������� 2
  word abs_nom1;          // ����������� �������� ��������� 1 � ���������� ��������
  word abs_nom2;          // ����������� �������� ��������� 2 � ���������� ��������
  union FormatCode code1;  // ������ ��������� ��������� 1 �� ��������� ���������
  union FormatCode code2;  // ������ ��������� ��������� 1 �� ��������� ���������
};
      // ��������� ����� ������ ��� ���������� �������� ������� ����������.
struct Ind_obj {
             byte  *txt ;      //����� ��� ����������� ������������ ��������� ������� �������� �������
             void  *adr[2] ;      // ����� ������ ������ ��������������� ��������� ������� �������� �������
             word  nom[2] ;       // ����������� �������� ������� ��������� � ����������� ���������
             byte  *txt2[2] ;  // ����� ��� ����������� ���������� ��.�����. ������� �����.
             word  *abs_nom[2];   //����� ������ �������� � ���������� ��������
             union FormatCode code[2] ;
               } ;

//------------------------------------------------------------

// ������ ��������� �������, ������������ �����
struct Ust_Tab
{
  double dX;                  // ��� ��������� �������
  double typ;                 // ������� ��������
  double min;                 // ����������� �������� �������
  double max;                 // ������������ �������� �������
  word num_var;               // ����� ���������� � ������� �������
  word nom;                   // ����������� �������� ������� � ���������
  word abs_nom;               // ����������� �������� ������� � ���������� ��������
  union FormatCode code;
  byte text[ 16 ];            // ����� �������
  byte ch[ 4 ];               // ����� ������� ��������� �������
};
//��������� �������� ������� ��� �� ���������� �� ��������

struct Obj_STB {
            byte *text ;  // ����� ������ ������ ���������������� �������
            void *addr      ;  // ����� �������; ������� ����� ���� ������ �����������
            double  min     ;  // ����������� �������� ������� � ����������� ��������
            double  max     ;  // ������������ �������� �������� � ����������� ��������
            word  nom       ;  // ����������� �������� ������ ������� � ����������� ���������
            word  *abs_nom  ;  // ����������� �������� ������ ������� � ����������� ���������
            double  dX      ;  //
            byte  mask      ;  // ����� ������� - ���������� ���������� �� � ������� ��� ���
            byte *ch        ;  // ����� ������ ������ ���������������� �������
            union FormatCode code ;
 //           void * Type_Ust;        //����� �������� ��������
 //           void * Max_Dat;         //������������ �������� �������, ������ �� ���������� �������
 //   _x_far  char * Help_str;        //����� ������� ������� ������ Help ��� �������
        } ;

//------------------------------------------------------------
//����� �� ������
struct  Err_Rep
{
    word code;                          // ��� ������
    word Comm;                          //��� ������� � ������� ��������� ������
    word PC;                            //����������� �������
    word SP;                            //��������� �����
    word Oper[_Tmp_Opers_max+1];                      //����� ���������
};
// ��������� ������
struct MemoryData
{
 // byte   bitData [ _MAX_NUM_BITS ];
  byte   bData [ _MAX_NUM_BYTE   ];
  word   wData [ _MAX_NUM_WORD   ];
  lword  lwData[ _MAX_NUM_LWORD  ];
  double dData [ _MAX_NUM_DOUBLE ];
};
//������ � ��������
struct SetpointData
{
  byte   bData [ _MAX_NUM_SP_BYTE   ];
  word   wData [ _MAX_NUM_SP_WORD   ];
  lword  lwData[ _MAX_NUM_SP_LWORD  ];
  double dData [ _MAX_NUM_SP_DOUBLE ];
};


// ��� ���������
struct CodeData
{
  word Size;  //������ ������������ �����.
  word ProgrammCounter;       // ����� �������� ����� ������������ ��� ������� ����� �� "Prog"
  word Prog[ _MAX_LEN_CODE/2 ]; // ���� ����������� ��� ��������� �� i2c  ������ ����� � ������,
                                //� ������ �� ���� �������, �� ����� ����� �� 2
};
//���������, ������������ ������� �������� ��������� � ���������.
union Prg_cfg
{
 word all;
 struct
 {
#ifdef _Union_FR   //�������������� ����� ������ ��� FR

    word res_h    :8;    //������

    word res      :1;
    word func     :1;  //��������� �������
    word base     :1;  //����������� ����������
    word srv_msg  :1;  //��������� ���������

    word pr_msg   :1;  //����������������� ���������
    word av_msg   :1;  //��������� ���������
    word ind      :1;  //������� ���������� ��� ���������
    word ust      :1;  //������� �������
#else

    word ust      :1;  //������� �������
    word ind      :1;  //������� ���������� ��� ���������
    word av_msg   :1;  //��������� ���������
    word pr_msg   :1;  //����������������� ���������

    word srv_msg  :1;  //��������� ���������
    word base     :1;  //����������� ����������
    word func     :1;  //��������� �������
    word res      :1;

    word res_h    :8;    //������

#endif
 }_;
};
//���������, ������������ ���������� ���������, ��������� � �.�.
 struct quantity
 {
    word Function;
    word SetPoint;
    word VarInd;
    word VarBase;
    word Av_Msg;
    word Pr_Msg;
    word Srv_Msg;

 };
//��������� �������� ���������� ���� ����������
 struct arg_data
 {
   word quant; //���������� ���������� ������� ����
   word Arg[_MAX_NUM_ARG]; //���� ������������ �������� ����������

 };
 struct  arg_data_full
 {
    struct arg_data   byte_arg     ;  //�����������
    struct arg_data   word_arg     ;  //�����������
    struct arg_data   lword_arg    ;  //��������������
    struct arg_data   double_arg   ;  //double
 };

struct  Stack_str
{
    word Stack_Pointer; //��������� �����
    union
    {
        word Stack[_STACK_SIZE]; //���� ���  �������� �� ������������
        union Operand oStack[_STACK_SIZE]; //���� � ���� ���������
    } body;
} ;

union  ObjPrg_Srv_bit
{
   word all;
   struct
   {
      word Avar   :1;
      word InWork :1;
   }_;

};
word Interpreter ( byte code );
double Double_Move( double in) ;


word PUSH(byte*in, word size);
word POP (byte*in, word size);


//byte ExtractFromMemory(union Operand *Operands, union bwlw *Output, byte Counter);
//void LoadToMemory     (union Operand Operands, union bwlw *Input);

#ifdef _INT_MEM_INCLUDE

struct CodeData       ObjPrgData;

#else

extern struct CodeData       ObjPrgData;

#endif

#ifdef _INTERPRETER_INCLUDE

const struct  Base_func_def  Basef_def[] =
{
    "bSin",     _Numb_blocks_bSin,
    "bCos",     _Numb_blocks_bCos,
    "bTan",     _Numb_blocks_bTan,
    "bAsin",    _Numb_blocks_bAsin,
    "bAcos",    _Numb_blocks_bAcos,
    "bAtan",    _Numb_blocks_bAtan,
    "bSqr",     _Numb_blocks_bSqr,
    "bAbs_d",   _Numb_blocks_bAbsD,
    "bAbs_i",   _Numb_blocks_bAbsI,
    "bLim_d",   _Numb_blocks_bLimD,
    "bLim_i",   _Numb_blocks_bLimI,
    "bIZU_d",   _Numb_blocks_bIZUD,
    "bIZU_i",   _Numb_blocks_bIZUI,
    "bZI"  ,    _Numb_blocks_bZI,
    "bInitZi",  _Numb_blocks_bini_ZI,
    "bPI_reg",  _Numb_blocks_bPI_reg,
    "bFiltr",   _Numb_blocks_bFiltr,
    "bAverage", _Numb_blocks_bAverage
};

//������� � ������� ������������ ������� �������, ������������ � ���������
// struct  Base_func_def Basef_block[_Numb_Basef];

//������ ��� �������� �� ���������� ������ ������� ������� � ���������� ���������
word Base_func_decoding[_Numb_Basef];

byte comp_date[6];


//struct Tabl_Obj_MSG   TablObjMSG;
//struct MSG_Obj_regs   MSGObjregs;
struct MemoryData     MemData;  // ��� ������ ��������������
struct Stack_str      Stack;  //����
//struct AgrData ObjArgData;      //��������� ���������� �� ��������� �������
union  Prg_cfg  Cfg_str;
struct quantity Str_quant;
struct Var_quant PVar_quant;
struct Var_quant SVar_quant;

//struct MemoryArgData    MemArgData; //����� ���������� �����������
union  ObjPrg_Srv_bit   ObjSrv_bit;
const char CtrlCode[9] = "PComplex";
//word  addr_Ctrl;
byte CtrlTmp[8];
//word fr1,fr2;
lword fr3;
lword fr4;//, fr5;
word *fr5[4];
double fr6, fr7;
//������� ������� ������� ��������� ��� ��������� ������������� ������� �������
word obj_FirstPrg;
//������ ������� �� �������� ���������
//word Shifts[1000];
const word SizeMemData = sizeof ( struct MemoryData ); // ������ ��� ������ ��������������

union Operand  Operand_Tmp[_Tmp_Opers_max+1]; //��������� ��������� ���������
//����� ����������� ���������� � var_tab
//word   Std_Vars[(size_vartab1/sizeof(struct namevar))] ;
struct Ind_obj  Ind_Obj_Prg[_MAX_NUM_IND];
struct Ind_Table_Cod  Ind_Obj_Load[_MAX_NUM_IND];
struct Ust_Tab        Ust_Obj_Load[_MAX_NUM_SETPOINTS];
struct Obj_STB        Ust_Obj_Prg [_MAX_NUM_SETPOINTS];
union Command  Com;
//union bwlw  long_tmp;
struct  Err_Rep  ErrRep;
byte ObjVarPar[5];
//������� �������� �������
struct SetpointData   Type_SetPoints;
//struct SetpointData   _opr;
#else

extern const struct  Base_func_def Basef_def[];

extern byte comp_date[6];

extern word Base_func_decoding[];

//extern struct Tabl_Obj_MSG   TablObjMSG;
//extern struct MSG_Obj_regs   MSGObjregs;
//extern struct AgrData        ObjArgData;
extern union  Prg_cfg  Cfg_str;
extern struct quantity Str_quant;
extern struct Var_quant PVar_quant;
extern struct Var_quant SVar_quant;
extern struct MemoryData     MemData;
//extern struct MemoryArgData    MemArgData;
//extern word   Shifts[1000];
extern struct Stack_str Stack;
extern union  Operand Operand_Tmp[];
extern struct Ind_obj        Ind_Obj_Prg[_MAX_NUM_IND];
extern struct Ind_Table_Cod  Ind_Obj_Load[_MAX_NUM_IND];
extern struct Ust_Tab        Ust_Obj_Load[_MAX_NUM_SETPOINTS];
extern struct Obj_STB        Ust_Obj_Prg [_MAX_NUM_SETPOINTS];
//extern word   Std_Vars[] ;
extern union Command  Com;
//extern union bwlw  long_tmp;
extern const word SizeMemData;
extern union  ObjPrg_Srv_bit   ObjSrv_bit;
extern const char CtrlCode[];
extern word obj_FirstPrg;
//extern word  addr_Ctrl;
extern byte CtrlTmp[8];
extern word fr1, fr2;
extern double fr6, fr7;
extern struct  Err_Rep  ErrRep;
extern byte ObjVarPar[5];
extern struct SetpointData   Type_SetPoints;
//extern struct SetpointData   _opr;

#endif

#endif  // _interpreter_h
