#ifndef _link_h
#define _link_h

/*#define  _CW_READ_NAME   1
#define  _CW_READ_NUMB   2
#define  _CW_BREAK       3
#define  _CW_WRITE_NUMB  4
#define  _CW_WRITE_NAME  5
#define  _CW_RETRY_BL    6
#define  _CW_READ_ADRR   7
#define  _CW_WRITE_ADRR  8
#define  _CW_READ_TAB    9
#define  _CW_SYNCH       10
#define  _CW_RETRY       11*/

  //Общие комманды

#define  _CW_READ_NUMB   1
#define  _CW_READ        2
#define  _CW_WRITE       3
#define  _CW_BREAK       5
#define  _CW_Possible    6
#define  _CW_READ_NAME   7
#define  _CW_READ_ADRR   8
#define  _CW_WRITE_ADRR  9
#define  _CW_READ_TAB    0x0a
#define  _CW_SYNCH       0x0b
#define  _CW_SLED        0x0c
#define  _CW_Error       0x0d
#define  _CW_Read_Blok   0x0e

 //Комманды для считывания следа и осциллаграфа

#define  _CW_Prepare_tab   1
#define  _CW_Load_tab      2
#define  _CW_Osc_tab       3
#define  _CW_Osc_adr       4
#define  _CW_Oscillat      5
#define  _CW_SLDStop       6

#define  _Low_UART_Speed   19200
#define  _High_UART_Speed  19200//56000

union  L_status
{
   word all;
   struct
   {
     word off_sled   :1;
     word cw_all     :1;
     word first_time :1;
     word Num_bl     :1;

     word Pr_Tabl    :1;
     word run        :1;
     word send       :1;
     word Av_up      :1;

     word trg_time   :2;
   }_;
};
//Структура состояния для программ подготовки таблиц, используемых
//и по CAN и по UART
struct PTAB
{
  union
  {
    byte all;
    struct
    {
  #ifndef  _Union_FR
      word En      :1;
      word One     :1;
      word Ld_Tab  :1;
      word Sv_Tab  :1;

      word LOsc_start :1; // Старт  LAN осциллогафа
      word LOsc_dataR :1; // Готовность данных для LAN осциллографа
  #else
      word         :2;
      word LOsc_dataR :1; // Готовность данных для LAN осциллографа
      word LOsc_start :1; // Старт  LAN осциллогафа

      word Sv_Tab  :1;
      word Ld_Tab  :1;
      word One     :1;
      word En      :1;
  #endif
    }_;
  }bits;
  byte numb; //номер параметра в таблице следа.
};
/*union  Link_addr
{
  lword addr;
  byte  ll[4];
};*/

struct Par
 {
    char txt1[12] ;  // текстовое наименование переменной
  #ifdef  _Union_FR

    byte addr_ll;
    byte addr_lh;
    byte addr_hl;
    byte addr_hh;

    byte form_l ;
    byte form_h ;

    byte nom_l;
    byte nom_h;

    byte abs_nom_l;
    byte abs_nom_h;

  #else

    lword addr;
    word form ;
    word nom;
    word abs_nom;

  #endif

    char txt2[6];
 } ;
/*struct Par
 {
    char txt1[12] ;  // текстовое наименование переменной
    word form_l ;
    //byte form_h ;
    word nom_l;
    //byte nom_h;
    //byte abs_nom_l;
    word abs_nom_h;
    char txt2[5];
 } ;*/
/*struct TR_MEM_BL
{
  byte* tx_addr;
  word  trans_blok;
  word  Len_blok;
};*/

struct SLED_TX
{
  #ifdef  _Union_FR

  byte  save_mem_l ; // объем памяти фрагмента следа сохраняемый в i2c после аварии.
  byte  save_mem_h ;

  byte  dt_scan_l ;
  byte  dt_scan_h ;

  byte  dt_stop_l ;
  byte  dt_stop_h ;

  byte  kratn_l ;
  byte  kratn_h ;

  byte  MSec_l ;
  byte  MSec_h ;

  byte  index_l;
  byte  index_h;

  byte  size_l;
  byte  size_h;

  #else

  lword  save_mem ; // объем памяти фрагмента следа сохраняемый в i2c после аварии.
  word  dt_scan ;
  word  dt_stop ;
  word  kratn ;
  word  MSec ;
  lword  index;
  lword  size;

  #endif

  byte  n_kanal ;
  byte  type   ;
  byte  numb;
  byte  ptr [ _SledTabSizeMax ] ;

};



void Link_start(void);
void Link(void);
word trans_mem_blok(byte* addr, word len_bl,word length, byte* feed_back);
word SendCommWord(byte command, byte length, byte param[8],byte* feed_back );
word SendTabl( byte* feed_back);
word Write_Numb_By_Name(byte* feed_back);
word Write_Name_By_Numb(byte* feed_back);
word COMM_Write(byte* feed_back);
word COMM_Read(byte* feed_back);
word Write_Sled_Tab( byte Numb );
word UART_Sled( void );
word Load_Sled_Tab( void);
word RD_addr(void);
word Oscillator( void);
void PrepareTab(void);
void Link_txrx(void);
void Wait_Time( void);
void LanOscl(void );
#define TickD  (w)((d)_TimerDiscreta * (d)256)

#ifdef _LINK_INCLUDE


#ifdef  _Sld_cond

/* #ifndef _CM3_
const byte L_Ver = 7;
 #else*/
const byte L_Ver = 10;
 //#endif

#else

const byte L_Ver = 5;

#endif
//union tst tstttt;
word Size_bl;
word Comm_label, numb_text,  Link_time, back_lab;
word Tx_mem_label, Write_Label;
word numb_line[2];
word link_contr_summ,  link_stop_point, trans_blok;
lword len_blok ,len_trans;
word comm_word, comm_word_old, sld_cw;
byte nuk, byte_ad;
word wr_Diskr, len_blok_old;
byte nuk_max;
byte *tx_addr[2];
byte *tx_addr_beg;
byte feed_b;
byte comm_len, comm_count, ccs, block_count, block_count_old;
byte Dis_Buff[8];
byte trg_time;
//lword test_sl[5];// = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
byte comm_Par[8];
byte LanOsclOut[38]; // 4 переменных для Double - по 8 байт+2 байта для dt+2байта номинал времени
byte OscPtrs[4];   //перечень переменных для осциллографа из таблицы следа
word TimeLanOsc;
float Per_Osc;
//union Link_addr  Link_a;
//word fr2;
//lword fr1;
struct SLED_TX   s_tx;
union  L_status  L_sts;
struct Par s_short[2];
struct PTAB  P_Tab;
word TX_size;//,tmpcount;
word CW_time,CW_count;
//byte tmptx[1000];
word lpoint;
//byte tmprx[1000];
byte sbh;

#else

//extern byte tmptx[1000];
//extern byte tmprx[1000];
extern byte sbh;

extern const byte L_Ver;
extern word Size_bl;
extern word Comm_label, numb_text,  Link_time, back_lab;
extern word Tx_mem_label, Write_Label;
extern word numb_line[];
extern word link_contr_summ, len_trans, link_stop_point, trans_blok;
extern word comm_word, comm_word_old, sld_cw;
extern byte nuk, byte_ad;
extern word len_blok, wr_Diskr, len_blok_old;
extern byte nuk_max;
extern byte *tx_addr[];
extern byte *tx_addr_beg;
extern byte feed_b;
extern byte comm_len, comm_count, ccs, block_count, block_count_old;
extern byte Dis_Buff[];
//lword test_sl[5];// = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
extern byte comm_Par[];
extern byte LanOsclOut[38];
extern byte OscPtrs[];
extern word TimeLanOsc;
//union Link_addr  Link_a;
//extern word  fr2 ;
//extern lword fr1;
extern struct SLED_TX   s_tx;
extern union  L_status  L_sts;
extern struct Par s_short[2];
extern word TX_size;//,tmpcount;
extern word CW_time,CW_count;
extern word lpoint;
extern byte trg_time;

extern struct PTAB  P_Tab;

#endif
#endif

