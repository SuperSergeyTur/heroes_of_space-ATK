
#ifndef _journal
#define _journal
/*�����������������������������������������������*/

// ��������� �������
void Journal ( byte );    // ���������� ��� ������
void SetJrnTab ( void );  // ��������� �������
void JrnPrint ( void );   // ����� ������� �� �������
word TestJrnTab ( byte );
word Save_jrn ( void );   // ���������� ������ ������� � i2c

#ifndef    _Journal_Version
  #define  _Journal_Version   0x01
#endif

#ifndef _CM3_

#define  _AdrSize 2

#else

#define  _AdrSize (4)

#endif

#define  _i2c_jrn_page   ( sizeof( struct MSG_JRN ) ) // ������ �������� �������

#define _MaxJrnCount 0x7u //������ ������ ������� � ���


        // ������� �����-��������� �������
        // ������ ��������� ������ �����, ����� ��� �� ����� ������� ���������
        // ���� ������ 0 ���������� - ������ �� ��������
#define bi_JrnStop  ( ( JrnData.Stop != 0 ) || ( TabJrn.n_kanal == 0 ) ) //|| L_sts._.off_jrn == 1 )


#define _BRV 0x00 // >=
#define _MRV 0x01 // <=
#define _RVN 0x02 // ==
#define _NRV 0x03 // !=
#define _BOL 0x04 // >
#define _MEN 0x05 // <

#define _Gisterezis   5  // ���������� �� 5%
#define _CntrCode     ((w)0x1234)  // ����������� ��� ��� ���������� ������ ������� �� ������

#define _VarNameSize  15  // 14 - ����� ����� + 1 - ����� ������

// ������� ����� ����������
struct TAB_VAR
{
  char name[ _VarNameSize ];  // ��������� ������������ ����������
  byte uslovie; // ������� ��������� ������ � ������ ��� ���������� ����������
  word etalon;  // �������� �������, � ������� ������������ ���������� ����������,
                // ��� ����� ���� ��� ���������� ����������
};

// ������������ ���������� ����������, ��������� � ������
#ifndef  _MaxNumVarJrn
  #define  _MaxNumVarJrn  ( 40 )
#endif

// ������� ������� � ��� � ����
struct TAB_JRN
{
  byte  version;  // ������ �������
  byte  n_kanal;  // ����� ����� ����������
  word  dt_scan;  // �������� ������� ������������
  struct TAB_VAR TabVar[ _MaxNumVarJrn ];
  byte  check_sum; // ����������� ����� ��� ����
};

// �������� �������-��������� ���������� ��� �������
struct VAR_JRN
{
  char name[ _VarNameSize ];    // ��� ����������
  void       *addr;    // ����� ����������
  word       min;      // ����������� �������� ���������� � ����������� ��������� ��� ���������� ���������� ���
                       // ���������� ����� ���� ��� ���������� ����������
  word       max;      // ������������ �������� ���������� � ����������� ��������� ��� ���������� ���������� ���
                       // ���������� ����� ���� ��� ���������� ����������
  word       nom;      // ����������� �������� ���������� � ����������� ��������� ��� ���������� ���������� ���
                       // ����� ���� ��� ���������� ���������� ���
                       // ����� ��� ���������� ����������, �������������� �������� ������
  word       *abs_nom; // ����� ������ �������� � ���������� ��������
  word       dX;       // ��� ���������
  char const *ch;      // ����� ������ ��������� ����������
  union
  {
    word all;
#ifndef   _Union_FR
    struct
    {
      word type     : 2;  // ��� ����������: 1-byte, 2-word
      word drob     : 2;  // ���������� ���� �����.�����
      word celoe    : 3;  // ���������� ���� ����� �����
      word off_sign : 1;  // '=1'- �����������

      word ad       : 2;  // 0-���������� ����������, 1-����������, 2 - ������������ �������� ������
      word rezerv   : 6;  // ������
    } _ ;
#else
    struct
    {
      word rezerv   : 6;  // ������
      word ad       : 2;  // 0-���������� ����������, 1-����������, 2 - ������������ �������� ������

      word off_sign : 1;  // '=1'- �����������
      word celoe    : 3;  // ���������� ���� ����� �����
      word drob     : 2;  // ���������� ���� �����.�����
      word type     : 2;  // ��� ����������: 1-byte, 2-word
    } _ ;
#endif
  } code;
} ;


// 1. ���������� ���������� ����� ���� ������ "word" ��� ������������ �������� ������.
// 2. ���������� ���������� ����� ���� "byte", "word".

// ������� ���� ������� ����������� ����������
// type  -  1,2 - ��� ����������: 1 - �����������, 2 - �����������
// drob  -  0...3 - ���������� �������� ����� ������� (������� �����)
// celoe -  1...5 - ���������� �������� �� ������� (����� �����)
// off_sign  -  1 - �� ���������� ���� (���������� ������������) ��� ������� ������� ��� hex
// ad -  0-���������� ����������, 1-����������, 2 - ������������ �������� ������
#define  _jrn_form(ad,off_sign,celoe,drob,type)\
                                                (( type )|\
                                                 ( drob << 2 )|\
                                                 ( celoe << 4 )|\
                                                 ( off_sign << 7 )|\
                                                 ( ad << 8 ))

// ��������� ��� �������� ��������� �������
// �� ���� ������ - 58 ����
struct MSG_JRN
{
  char name[ _VarNameSize ];  // ��������� ������������ ����������
  byte uslovie; // ������� ��������� ������ � ������
  word value;   // �������� ���������� byte, word
  struct MSG_reg time_msg;
  //  struct I2C_time time;      // ����� �����������
  //  {                   D7...D4         D3...D0
  //        time.b[0]:   10 seconds       seconds      00-59
  //        time.b[1]:   10 minutes       minutes      00-59
  //        time.b[2]:   10 hours          hours      0-1/00-23
  //        time.b[3]:                     day         01-07
  //        time.b[4]:   10 date           date        01-31
  //        time.b[5]:   10 month          month       01-12
  //        time.b[6]:   10 years          years       00-99
  //        time.b[7]:   Control Byte  - ���� ����� ����������� ��� ��� ���������� ������ ������� �� ������
  //  },
  //  struct MSG_regs  _ ;    // ����� ��� ����� ������� ���������.
  //  {
  //    lword    avar_first;        // ������� ������ ������
  //    lword    avar;              // ������� ��������� ������
  //    lword    predupr;           // ������� ��������������
  //    lword    service;           // ������� ��������� ���������
  //------
  //    lword    avar_first2;       // 2-� ������� ������ ������
  //    lword    avar2;             // 2-� ������� ��������� ������
  //    lword    predupr2;          // 2-� ������� ��������������
  //    lword    service2;          // 2-� ������� ��������� ���������
  //  }
};

struct JRN_DATA
{
  word time;
  byte tab[ _MaxNumVarJrn ];  // ��������� �� ��������������� ������ � ������� �������
  byte flag[ _MaxNumVarJrn ]; // ������� ��������� ����������
  byte number; // ����� ����������, ��������� �� i2c
  byte label; // ����� ��� ��������� TestJrnTab()
  byte activ, Stop; // ������� ���������/������� �����.
};

struct MENU
{
  char const *txt; // ����� ����
  byte label;      // �����
};

union BIT_JRN
{
  byte all;
  struct
  {
    word tst_msg_jrn : 2;
    word tst_new_msg : 1;
    word first       : 1;
    word rezerv      : 4;
  }_;
};

/*struct BIT_PORT
{
  char name[ _VarNameSize ];  // ��� ����� ���������� ��������
  void       *addr;    // ����� ����� ���������� ��������
};*/

/*�����������������������������������������������*/
#ifdef _JOURNAL_INCLUDE
/*�����������������������������������������������*/

// ������� ������� � ���
struct TAB_JRN TabJrn;

// ����� ������� � ���
struct MSG_JRN MsgJrn[ _MaxJrnCount + 1 ];

// ����� ������� � ��� ��� ���������� �� i2c � ����������
struct MSG_JRN MsgJrnPrint;

byte InJrnPtr;  // ���������, ����������� �� ��������� (������) ������ �������
byte OutJrnPtr; // ���������, ����������� �� ��������� (���������� � i2c) ������ �������.
                // ������ ������ ��������� �� 1 �� InJrnPtr

struct JRN_DATA JrnData;

const struct MENU Menu1[ ] =
{
  { _jrnMultiplicity, 10 },
  { _jrnQuantity    , 20 },
  { _jrnList        , 30 }
};

const word Menu1_size = sizeof( Menu1 )/sizeof( struct MENU );

const struct MENU Menu2[ ] =
{
  { _jrnNewChannel, 40 },
  { _jrnCondition , 50 },
  { _jrnLevel     , 60 }
};

const word Menu2_size = sizeof( Menu2 )/sizeof( struct MENU );

const struct MENU Menu3[ ] =
{
  { " '>='", _BRV },
  { " '<='", _MRV },
  { " '=' ", _RVN },
  { " '!='", _NRV },
  { " '>' ", _BOL },
  { " '<' ", _MEN }
};

const word Menu3_size = sizeof( Menu3 )/sizeof( struct MENU );

_x_far const struct VAR_JRN *dptr;
union BIT_JRN  BitJrn;
byte i2c_jrn_label, *jrn_adr_data;
#ifndef _CM3_

word i2c_jrn_addr;

#else

lword i2c_jrn_addr;

#endif
const char *const DayJrn[ 7 ] = { "��,","��,","��,","��,","��,","��,","��," };
word Tjrn, Tckl_jrn;
#ifdef _CM3_

lword j_ext ;

#endif
/*�����������������������������������������������*/
#else
/*�����������������������������������������������*/

extern struct TAB_JRN TabJrn;
extern struct MSG_JRN MsgJrn[];
extern byte InJrnPtr;
extern byte OutJrnPtr;
extern struct JRN_DATA JrnData;
extern const struct MENU Menu1[];
extern const struct MENU Menu2[];
extern const struct MENU Menu3[];
extern const word Menu1_size;
extern const word Menu2_size;
extern const word Menu3_size;
extern _x_far const struct VAR_JRN *dptr;
extern struct MSG_JRN MsgJrnPrint;
extern union BIT_JRN  BitJrn;
extern byte i2c_jrn_label, *jrn_adr_data;
#ifndef _CM3_

extern word i2c_jrn_addr;

#else

extern lword i2c_jrn_addr;

#endif
extern const char *const DayJrn[];
extern word Tjrn, Tckl_jrn;
#ifdef _CM3_

extern lword j_ext ;

#endif

/*�����������������������������������������������*/
#endif
/*�����������������������������������������������*/
#endif
