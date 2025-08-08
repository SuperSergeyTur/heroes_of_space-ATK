#ifndef _monitor_h
#define _monitor_h


#include <system.h>
#include <led_control.h>

//------------------------------------------

//Максимальный индекс тетрады адреса страницы для ввода адреса в мониторе

#ifdef _32_BITS_

#define _Page_shift  3

#else

#define _Page_shift  1

#endif

/*------------------------------------------------*/
#ifndef _MSG_INCLUDE
/*------------------------------------------------*/

  extern const char *const  c_Clock[];
  extern const char *const  u_Clock[];
  extern const char *const Day[];

  extern const char  _PasswordLtd_txt[] ;
  extern const char  _RightPassword_txt[] ;

  extern const char  _Dostup_Gotovn_txt[] ;
  extern const char  _Dostup_Rabota_txt[] ;
  extern const char  _Dostup_Ostanov_txt[];

/*------------------------------------------------*/
#endif

//------------------------------------------

    void  Start_RXD_TXD ( void )  ;
    void  Restart_Output ( void ) ;
    void  Monitor ( void )  ;
    void  output_ch ( void ) ;
    void  output_str ( void ) ;
    void  output_whex ( word );    // KVV_backup
    void  DecimalByte_print ( byte ) ;
    void  Speed_Pult ( void ) ;
    word  TestData_for_Input ( void ) ;
    word  TestCompleted_Output ( void ) ;
    void  UserCall ( void ) ;
    void  Restart_Output ( void ) ;
    void  Pult_Rabota ( void ) ;
    void  Pult_Ostanov ( void ) ;
    void  Monitor ( void )  ;
    void  PrintMessage ( void ) ;
    void  Setab_Bit_Drive (char *numb, word kol) ;
    void  SetabDrive (char *numb, word kol) ;
    void  Fazirovka ( void ) ;
    void  Fazirovka_V ( void ) ;
    void  Fazirovka_Us ( void ) ;
    void  Fazirovka_Is ( void ) ;
    void  output_ch ( void ) ;
    void  output_str ( void ) ;
    void  Speed_Pult ( void ) ;
    void  UstRam_in_Flash ( void )  ;
    void  ReadWrite_MemoryBlock ( void )  ;
    void  Vybor_Isp ( void )  ;
    void  Vybor_DAC_tabl ( void ) ;
    //void  Clock ( void ) ;
    //void  Clock_ust ( void ) ;

    void  Norton_Drive ( void )  ;
    void  TstADC_Drive ( void ) ;
    void  TstDAC_Drive ( void ) ;
    sword AutoOffsetADC ( word num );
    void  Indicator_Drive ( void ) ;
    void  IndicatorDP_Drive ( void ) ;
    void  TstInputPort_Drive ( void ) ;
    void  TstOutputPort_Drive ( void ) ;
    void  Pult_Dispetcher ( void )  ;
    void  Pult_Prog ( void )  ;

    void  Pult_Dispetcher ( void )  ;
    void  Pult_Prog ( void )  ;

    word  Chek_sum ( word n , byte *from ) ;
    void  Type_ustavki ( void ) ;
    word  Save_avar ( void ) ;
    void  ReLoad_sled ( void ) ;
    void  Test_i2c ( void ) ;
    void  load_obl_ust ( word num ) ;
    void  adr_obl_ust ( word num_obl );
    word  Perekl_rezerv ( word code, word code_rezerv ) ;
#ifndef _CM3_
    void  ReadWrite_i2c ( word flash_begin, word flash_end, byte flash_address );
    void  RW_Prog( word flash_begin, word flash_end, byte flash_address );
#else
#ifndef _EEPROM
    void  ReadWrite_i2c ( lword flash_begin, lword flash_end, byte flash_address );
#else
    void  ReadWrite_i2c ( word flash_begin, word flash_end, byte flash_address );
#endif
    void  RW_Prog( lword flash_begin, lword flash_end, byte flash_address );
#endif
    void  Read_Ust (void);

         // Очистка кодов из буфера с выдержкой времени.
    void  Test_Klav_buff( void ) ;

        //    Фиксация времени изменения количества сообщений дл
        //  распечатки его по "Enter" в режиме "A1".
    word  check_msg_time ( void ) ;
        // Вывод номера сообщения из отключенного второго регистра сообщений .
    void  Msg_notSupport ( byte num ) ;

    word  xSave_Ust ( byte code ) ;
    void  A1_A6_Switching ( void ) ;
    void  FA_Ostanov ( void ) ;
    void  About ( void ) ;
    void  RemoteTerminal ( word code )  ;
    void  Init_Stop_Point ( void ) ;

    word  Password_control ( word code ) ;

    void  SetF_AvarMsg ( void ) ;

    void comb_redact(void);

    void SendCommandToPult(byte Comand, byte *Params, byte NumbParams);
    void SendEasyCommandToPult(byte Comand);


/*--------  TXD  ---------------------------------------  */

             /* послать символ в буфер последовательного порта на вывод.  */
#define   mSymbol_in_Buff_TXD( symbol )  TxBuff[(w)InTxBuffCount] = (b)(symbol) , InTxBuffCount = ( InTxBuffCount + 1 ) & TxBuffSize

             /* прочитать символ из буфера последовательного порта на вывод.  */
#define   mSymbol_from_Buff_TXD( symbol )  OutTxBuffCount = ( OutTxBuffCount + 1 ) & TxBuffSize , symbol = TxBuff[(w)OutTxBuffCount]

         /* проверить: есть ли данные в буфере вывода последовательного порта.  */
#define   mTestYesData_in_Buff_TXD()   ( ((OutTxBuffCount + 1) & TxBuffSize) != InTxBuffCount )

         /* проверить: есть ли место под новые данные в буфере вывода последовательного порта.  */
#define   mTestYesRoom_in_Buff_TXD()   ( ((InTxBuffCount + 1) & TxBuffSize) != OutTxBuffCount )

/*--------  RXD  ---------------------------------------  */

             /* послать символ в буфер последовательного порта на вывод.  */
#define   mSymbol_in_Buff_RXD( symbol )  RxBuff[(w)InRxBuffCount] = (b)(symbol) , InRxBuffCount = ( InRxBuffCount + 1 ) & RxBuffSize

             /* прочитать символ из буфера последовательного порта на прием.  */
#define   mSymbol_from_Buff_RXD( symbol )    OutRxBuffCount = ( OutRxBuffCount + 1 ) & RxBuffSize , symbol = RxBuff[(w)OutRxBuffCount]
#define   mSeeSymbol_from_Buff_RXD( symbol ) symbol = RxBuff[(w)( OutRxBuffCount + 1 ) & RxBuffSize]

         /* проверить: есть ли данные в буфере ввода последовательного порта.  */
#define   mTestYesData_in_Buff_RXD()   ( ((OutRxBuffCount + 1) & RxBuffSize) != InRxBuffCount )

/*----------------------------------  */
/*#ifdef    _Terminal_196xRS232*/

    #define   mOutput_c( symbol )           mSymbol_in_Buff_TXD( symbol )

    #define   mTestFreeSpace_for_Output()   mTestYesRoom_in_Buff_TXD()

    #define   mTestCompleted_Output()       (!mTestYesData_in_Buff_TXD())

            /*   Макрос заменяющий способ передачи параметра в функцию вывода
             * строки текста: внешне - традиционно по правилам языка, а на самом
             * деле через зарезервированую ячейку, что избавляет от громоздких
             * операций со стеком.
             *   Внимание - функцией "output_str" содержимое "str_addr" модифи-
             * цируется.
             */
    #define   output_s( ptr )  str_addr = ptr, output_str()

    #define   output_c( sym )  m_ch = sym, output_ch()

    #define   mInput_c( symbol )            mSymbol_from_Buff_RXD( symbol )
    #define   mSeeInput_c( symbol )      mSeeSymbol_from_Buff_RXD( symbol )

    #define   mTestData_for_Input()         mTestYesData_in_Buff_RXD()

/*#endif*/
/*----------------------------------  */

     //  Делаем возможность работы с регистрами аварий в 2-х байтном исполнении для ModBus.
union  LW_Reg
{
    lword     lw_reg  ;
#ifndef   _Union_FR
    struct  { word l, h ; } w_reg ;
#else
    struct  { word h, l ; } w_reg ;
#endif
};
struct MSG_regs
{
  union   LW_Reg  avar_first;        /* Регистр первой аварии */
  union   LW_Reg  avar;              /* Регистр повторных аварий */
  union   LW_Reg  predupr;           /* Регистр предупреждений */
  union   LW_Reg  service;           /* Регистр служебных сообщений */
//------
  union   LW_Reg  avar_first2;       /* 2-й регистр первой аварии */
  union   LW_Reg  avar2;             /* 2-й регистр повторных аварий */
  union   LW_Reg  predupr2;          /* 2-й регистр предупреждений */
  union   LW_Reg  service2;          /* 2-й регистр служебных сообщений */
//------
#ifdef _TRETIY_REG
  union   LW_Reg  avar_first3;       /* 3-й регистр первой аварии */
  union   LW_Reg  avar3;             /* 3-й регистр повторных аварий */
  union   LW_Reg  predupr3;          /* 3-й регистр предупреждений */
  union   LW_Reg  service3;          /* 3-й регистр служебных сообщений */
#endif
//------
#ifdef _INTERPRETER
  union   LW_Reg  avar_first_obj;       /* Регистры для интерпретатора */
  union   LW_Reg  avar_obj;
  union   LW_Reg  predupr_obj;
  union   LW_Reg  service_obj;
#endif
//------
//  byte     check_sum ; // контрольная сумма сообщений для проверки появления новых сообщ.
};

struct MSG_reg
{
  I2C_time time ;      // Время регистрации аварии.
 /*                   D7...D4         D3...D0
          time.b[0]:   10 seconds       seconds      00-59
          time.b[1]:   10 minutes       minutes      00-59
          time.b[2]:   10 hours          hours      0-1/00-23
          time.b[3]:                     day         01-07
          time.b[4]:   10 date           date        01-31
          time.b[5]:   10 month          month       01-12
          time.b[6]:   10 years          years       00-99
  */
  struct MSG_regs  _ ;
};

void  print_message ( struct MSG_reg *ptr ) ;

struct Tabl_MSG
{
  char Avar[32][18]  ;
  char Predupr[32][18]  ;
  char Service[32][18]  ;
//------
#ifndef _ONE_REG
//------
  char Avar2[32][18]  ;
  char Predupr2[32][18]  ;
  char Service2[32][18]  ;
//------
#endif
//------
#ifdef _TRETIY_REG
//------
  char Avar3[32][18]  ;
  char Predupr3[32][18]  ;
  char Service3[32][18]  ;
//------
#endif
//------
} ;
extern const struct Tabl_MSG  Tabl_Msg ;

             // для совместимости с прежними программами.
             // ввели промежуточный буфер, т.к. CAN на прерываниях
             // выхватывал всякий мусор, когда влезал внутрь сборки
             // готовности между начальной очисткой регистров и завершением
             // их установки.
#define   Reg_AvarMsgFirst    msg_buf.avar_first.lw_reg
#define   Reg_AvarMsg         msg_buf.avar.lw_reg
#define   Reg_PreduprMsg      msg_buf.predupr.lw_reg
#define   Reg_ServiceMsg      msg_buf.service.lw_reg
//------
#define   Reg_AvarMsgFirst2   msg_buf.avar_first2.lw_reg
#define   Reg_AvarMsg2        msg_buf.avar2.lw_reg
#define   Reg_PreduprMsg2     msg_buf.predupr2.lw_reg
#define   Reg_ServiceMsg2     msg_buf.service2.lw_reg
//------
#ifdef _TRETIY_REG
//------
#define   Reg_AvarMsgFirst3   msg_buf.avar_first3.lw_reg
#define   Reg_AvarMsg3        msg_buf.avar3.lw_reg
#define   Reg_PreduprMsg3     msg_buf.predupr3.lw_reg
#define   Reg_ServiceMsg3     msg_buf.service3.lw_reg
//------
#else
//------
#define   Reg_AvarMsgFirst3   0
#define   Reg_AvarMsg3        0
#define   Reg_PreduprMsg3     0
#define   Reg_ServiceMsg3     0
//------
#endif
//------

//------    Регистры для интерпретатора

// Добавить их обнуление по старту

#define   Reg_AvarMsgFirst_obj   msg_buf.avar_first_obj.lw_reg
#define   Reg_AvarMsg_obj        msg_buf.avar_obj.lw_reg
#define   Reg_PreduprMsg_obj     msg_buf.predupr_obj.lw_reg
#define   Reg_ServiceMsg_obj     msg_buf.service_obj.lw_reg

//---------------------
struct DAC_output_tab1 {
         char const *txt ;
         struct DAC_data *p ;
         word setka ;
       } ;
struct DAC_output_tab2 {
         char const *txt ;
         word *addr ;
         word mashtab ;
       } ;

struct NCx {
         char const *txt ;
         word  cmd ;
         byte  Password;
       } ;

struct Stin {
         char const *txt ;
         byte *data ;
       } ;

struct StinL {
         char const *txt ;
         word *data ;
       } ;

struct Stout {
         char const *txt ;
         byte       *Px ;
         byte label ;
       } ;

struct StoutL {
         char const *txt ;
         word       *Px ;
         byte label ;
       } ;

// Создание шаблона-структуры блока данных закрепляемого за каждой уставкой.
    struct STB {
           char const *text ;  // адрес строки текста соответствующего уставке
                 void *addr      ;  // адрес уставки; уставка может быть только двухбайтной
//#ifdef _INTERPRETER
                double min       ;  // минимальное значение вличины в программных единицах
                double max       ;  // максимальное значение величины в программных единицах
/*#else
                sword  min       ;
                sword  max       ;
#endif*/
                 word  nom       ;  // номинальное значение данной уставки в программных дискретах
                 word  *abs_nom  ;  // номинальное значение данной уставки в программных дискретах

//#ifdef _INTERPRETER
                 double dX       ;  //
//#else
//                 word   dX       ;
//#endif
                 byte  mask      ;  // Маска уставки - определяет показывать ее в таблице или нет
           char const *ch        ;  // адрес строки текста соответствующего уставке
                 union
                 {
                   word all ;
            #ifndef   _Union_FR
                   struct  // для компилятора распологающего битовое поле
                   {     // от младшего бита к старшему.
                     word  type     :3 ;  /* тип уставки: 0-double, 1-однобайтная, 2-двухбайтная, 3 - float, 4-четырехбайтная  */
                     word  drob     :3 ;  /* количество цифр дробной части */

                     word  celoe    :4 ;  /* количество цифр целой части */
                     word  off_sign :1 ;  /* '=1'- отмена распечатки знака */

                     word  zapr     :1 ;  /* разрешение изменения уставки только в режиме "Работа"*/
                     word  print_type:2;  /* отображение уставок в 16-ричн виде*/
                     word  invert   :1 ;  /* отображение уставок в виде 1/x */
                   } _ ;
            #else
                   struct  // для компилятора распологающего битовое поле
                   {     // от старшего бита к младшему.
                     word  rezerv   :1 ;
                     word  invert   :1 ;  /* отображение уставок в виде 1/x */
                     word  print_type:2;  /* отображение уставок в 16-ричн виде*/
                     word  zapr     :1 ;  /* разрешение изменения уставки только в режиме "Работа"*/

                     word  off_sign :1 ;  /* '=1'- отмена распечатки знака */
                     word  celoe    :4 ;  /* количество цифр целой части */

                     word  drob     :3 ;  /* количество цифр дробной части */
                     word  type     :3 ;  /* тип уставки: 0-double, 1-однобайтная, 2-двухбайтная, 3 - float, 4-четырехбайтная  */
                   } _ ;
            #endif
                 } code ;
               } ;

                /* задание кода формата отображения переменной для режима  */
               /* редактирования уставок (по вышеописанному битовому полю):  */
               /* print_type -  0/1 - 10/16-ричный вид  */
               /* sign  -  1 - не отображать знак  */
               /* celoe -  1...10 - количество символов до запятой (целая часть)  */
               /* drob  -  0...3 - количество символов после запятой (дробная часть)  */
               /* type  -  1,2,4 - тип переменной: 1 - однобайтная, 2 - двухбайтная, 4 - четырехбайтная.  */
               /*   Задание "celoe=0" эквивалентно "celoe=3, drob=2" - для  */
               /* совместимости с уже сформированными таблицами переменных.  */

#define  _format(print_type,zapr,sign,celoe,drob,type) \
                                                    (( print_type << 12 )| \
                                                     ( zapr <<11 )|   \
                                                     ( sign << 10 )|   \
                                                     ( celoe<< 6 )|   \
                                                     ( drob << 3 )|   \
                                                     ( type ))
     //  формат общий и для А7 и для А6, и распределение битов одинаковое.
#define  _form(sign,celoe,drob,type)       _format(0,   0,sign,celoe,drob,type)
#define  _form1(zapr,sign,celoe,drob,type) _format(0,zapr,sign,celoe,drob,type)
          // big - 0/1 маленькие/большие буквы.
#define  _formh(big,type)                  _format(1,   0, big,    0,   0,type)

//Структура для разбиения уставок на группы
struct UstUzm
{
    char const *gruppa;// Название группы уставок
    word kol_vo; // Количество уставок в группе
    _x_far const struct STB *adr_Gruop;
};

/* Создание шаблона-структуры блока данных закрепляемого за каждой уставкой. */
    struct Bits {
           char const *text ;  /* адрес строки текста соответствующего уставке   */
                 void *addr ;  /* адрес побитовой уставки; уставка может быть только однобайтной */
                 byte n ;      /* кол-во битов в уставке                         */
           char const *bit[16]; /* табл. адресов строк-наименований битов уставки */
                 word msk[16] ; /* табл. масок битов в уставке                    */
                 word *mask1  ;  /* адрес маски для скрытия некоторых битов в уставке                    */
            union
            {
              word all ;
          #ifndef   _Union_FR
              struct  // для компилятора распологающего битовое поле
              {     // от младшего бита к старшему.
                word  type     :2 ;  /* тип уставки: 1-однобайтная, 2-двухбайтная  */
              } _ ;
          #else
              struct  // для компилятора распологающего битовое поле
              {     // от старшего бита к младшему.
                word  rezerv   :14 ;

                word  type     :2 ;  /* тип уставки: 1-однобайтная, 2-двухбайтная  */
              } _ ;
          #endif
            } code;
               } ;

      /* Структура блока данных для отдельного элемента таблицы параметров.  */
struct Ind {
        char const *text ;  /* текст для отображения наименования параметра данного элемента таблицы  */
             void  *adr[2] ;  /* адрес ячейки памяти соответствующей параметру данного элемента таблицы  */
             word  nom[2] ;  /* номинальное значение данного параметра в программных дискретах  */
        char const *txt2[2] ;  /* текст для отображения физической ед.измер. данного парам.  */
             word  *abs_nom[2];/*адрес ячейки номинала в абсолютных единицах  */
        union
        {
          word all ;
      #ifndef   _Union_FR
          struct  // для компилятора распологающего битовое поле
          {     // от младшего бита к старшему.
            word  type     :3 ;  /* тип параметра: 0-double, 1-однобайтная, 2-двухбайтная, 3- float, 4-четырехбайтная  */
            word  drob     :3 ;  /* количество цифр дробной части */

            word  celoe    :4 ;  /* количество цифр целой части */
            word  off_sign :1 ;  /* '=1'- отмена распечатки знака */

            word  zapr     :1 ;  /* разрешение изменения уставки только в режиме "Работа"*/
            word  print_type:2;  /* отображение уставок в 16-ричн виде*/
            word  invert   :1 ;  /* отображение уставок в виде 1/x */
          } _ ;
      #else
          struct  // для компилятора распологающего битовое поле
          {     // от старшего бита к младшему.
            word  rezerv   :1 ;
            word  invert   :1 ;  /* отображение уставок в виде 1/x */
            word  print_type:2;  /* отображение уставок в 16-ричн виде*/
            word  zapr     :1 ;  /* разрешение изменения уставки только в режиме "Работа"*/

            word  off_sign :1 ;  /* '=1'- отмена распечатки знака */
            word  celoe    :4 ;  /* количество цифр целой части */

            word  drob     :3 ;  /* количество цифр дробной части */
            word  type     :3 ;  /* тип параметра: 0-double, 1-однобайтная, 2-двухбайтная, 3- float, 4-четырехбайтная  */
          } _ ;
      #endif
        } code[2] ;
       } ;
 //Структура для разбиения индикации на группы
struct IndUzm
{
    char const *gruppa;// Название группы уставок
    word kol_vo; // Количество уставок в группе
    _x_far const struct Ind *adr_Gruop;
};

struct Stx {
         char const *txt ;
         struct Channel_AD  *ach ;
/*         word   koef ;  */
       } ;

struct VUP
{
  char const *txt;
  const struct UProgramm *source;
};

struct Ck {
         char const *txt ;
         word  min ;
         word  max ;
         word  nom ;
         word  dK ;
       } ;

struct Vybor {
         char const *txt ;
         byte label ;
       } ;

struct COMB_MENU
{
     /*  УСТАВКА  */
     char const *txt; // адрес строки текста вида "Уставка      Инд".

     void *addr;        // адрес уставки; уставка может быть только двухбайтной
     double min;        // минимальное значение вличины в программных единицах
     double max;        // максимальное значение величины в программных единицах
     word nom_ust;      // номинальное значение данной уставки в программных дискретах
     word *abs_nom_ust; // номинальное значение данной уставки в программных дискретах
     double dX;
     char const *ch; // адрес строки текста соответствующего уставке
     union {
          word all;
          struct              // для компилятора распологающего битовое поле
          {                   // от младшего бита к старшему.
               word type : 3; /* тип уставки: 0-double, 1-однобайтная, 2-двухбайтная, 4-четырехбайтная  */
               word drob : 3; /* количество цифр дробной части */

               word celoe : 4;    /* количество цифр целой части */
               word off_sign : 1; /* '=1'- отмена распечатки знака */

               word zapr : 1;       /* разрешение изменения уставки только в режиме "Работа"*/
               word print_type : 2; /* отображение уставок в 16-ричн виде*/
               word invert : 1;     /* отображение уставок в виде 1/x */
          } _;
     } code_ust;

     /*  ИНДИКАЦИЯ  */
     void *adr;         /* адрес ячейки памяти соответствующей параметру данного элемента таблицы  */
     word nom_ind;      /* номинальное значение данного параметра в программных дискретах  */
     char const *txt2;  /* текст для отображения физической ед.измер. данного парам.  */
     word *abs_nom_ind; /*адрес ячейки номинала в абсолютных единицах  */
     union {
          word all;
          struct              // для компилятора распологающего битовое поле
          {                   // от младшего бита к старшему.
               word type : 3; /* тип параметра: 0-double, 1-однобайтная, 2-двухбайтная, 4-четырехбайтная  */
               word drob : 3; /* количество цифр дробной части */

               word celoe : 4;    /* количество цифр целой части */
               word off_sign : 1; /* '=1'- отмена распечатки знака */

               word zapr : 1;       /* разрешение изменения уставки только в режиме "Работа"*/
               word print_type : 2; /* отображение уставок в 16-ричн виде*/
               word invert : 1;     /* отображение уставок в виде 1/x */
          } _;
     } code_ind;
}; //структура комбинированого меню

//    Команды на запись уставок.
//
#define   _CAN_Wr_ust      0x01
#define   _Link_Wr_ust     0x02
#define   _Pult_Wr_ust     0x04
#define   _Pult_BackUp_ust 0x08         // KVV
#define   _Error_Wr_ust    0x80

/*------------------------------------------------*/
#ifndef _MAIN_INCLUDE
/*------------------------------------------------*/

//extern const word _Num_dacs ;
//extern const struct DACS_N dac_tab[] ;
/*
extern const word  _Nin ;
extern const struct Stin Nstin [] ;

extern const word  _Nout  ;
extern const struct Stout Nstout [] ;

extern const word _Nm ;
extern _x_far const struct Stx Nstx [] ;

extern const word _MaxNumBUst ;
extern _x_far const struct Bits  bts[] ;

extern const word _MaxNumUstav ;
extern const struct STB  stb[];
extern const struct UstUzm  Ustav[] ;
extern _x_far const struct IndUzm  Indicat[] ;
extern const word _Nc ;
extern _x_far const struct NCx NC [] ;
  */

#endif
//------------------------------------------------------------------------------------------
//#ifndef _CM3_

// Смещение адреса при переходе к другой области
#ifdef _JOURNAL
    #define  _sm_obl_ust  (_v_r+_v_or+_v_TablSled+_v_Func+_v_Stat+_v_TablJrn)
#else
    #define  _sm_obl_ust  (_v_r+_v_or+_v_TablSled+_v_Func+_v_Stat)
#endif

//------------------------------------------------------------------------------------------
// Начальные и конечные адреса в i2c различных областей:
//------------------------------------------------------------------------------------------

// KVV_backup  07.2019
// Добавлена область BackUp-уставок
// Изменениям подверглись только файлы monitor.h и #ust_i2c.c
// Все внесенные изменения отмечены в комментариях меткой  "KVV_backup"
// Для СМ-3 ТурСА сделал свой файл #ust_i2c.c, поэтому его надо унифицировать с этим файлом через драйвера.
// Разъяснения:
// - область предназначена для сохранения в ней запасной версии наладочных уставок (АЕ-ЗаписьУставок)
//   для того чтобы сохранять в ней "рабочий" вариант уставок перед переналадкой агрегата
//   для возможности откатиться к ним при неуспешности переналадки вместо отката до F9-ТиповыхУставок
// - второе назначение области - восстановить рабочие наладочные уставки елс Заказчик испортил их
// - работа областей в комплексе:
//   -  все прежние области уставок работают как и ранее ( при подаче питания, смене областей уставок, востановлении типовых)
//   -  по команде АЕ предлагается выбрать область записи уставок: Наладочные или BackUp, где
//      наладочные эквивалентны прежней записи уставок АЕ
//   -  по команде F9 предлагается выбрать область из которой будут восстановлены уставки: Типовые или BackUp, где
//      типовые эквивалентны прежнему восстановлению уставок F9
//   -  размер области  BackUp-уставок включает все уставки (_r, _or, _ar и т.д.)
//   -  для агрегатов с несколькими областями уставок:
//      -  создается соотв. столько же областей BackUp-уставок
//      -  по командам АЕ и F9 запись-чтение уставок происходит в выбранную в настоящее время область
//   - в памяти область BackUp-уставок размещается между рабочими уставками и аварийным следом

// ----------------Вариант 1----------------
// 1. Область рабочих-уставок начинается с аналоговых уставок и начала i2c
// _free_Space_Reg  - размер области для переменных в ЭОЗУ(задается в obj_def.h, если не нужен(для fujitsu), то ставится 0) TSA 23.07.19

#define  _ust_beg_adr_i2c   _i2c_beg+_free_Space_Reg

// 1.1 Область backup-уставок начинается после всех областей рабочих уставок
// KVV_backup: Вставка между рабочими уставками и аварийным следом Области BackUp-уставок

#define  _ust_beg_adr_i2c_backup ((_ust_beg_adr_i2c+_v_ar)+(_sm_obl_ust*_kol_obl)+1)

//----
// 2. Область аварийного следа начинается после всех областей backup- уставок
// KVV_backup #define  _i2c_av_beg   ((_ar_adr_i2c+_v_ar)+(_sm_obl_ust*_kol_obl)+1)
#ifndef _SD_Card_

#define _Av_index_addr _i2c_av_beg

#define  _i2c_av_beg   ((_ust_beg_adr_i2c_backup+_v_ar)+(_sm_obl_ust*_kol_obl)+1)

#ifdef _JOURNAL
    // -------------------------------------------------------
    //                   Для FR
    // При распределении i2c между следом и журналом 3/4 имеем:
    // -------------------------------------------------------
    // интерпретатор | журнал | следов | записей журнала
    // --------------|--------|--------|----------------------
    //      +        |   +    |   10   |      122
    // --------------|--------|--------|----------------------
    //      +        |   -    |   15   |       -
    // --------------|--------|--------|----------------------
    //      -        |   +    |   11   |      157
    // --------------|--------|--------|----------------------
    //      -        |   -    |   17   |       -
    // --------------|--------|--------|----------------------

// 08.03.2024 на 16-ти разрядном 590-ом на F16K при умножении на 3 результат умножения "срезался" c lword до word
// и получалось 2 следа и 408 записей журнала. При правильном вычислении получилось 9 следов и 125 записей журнала.
// Выявилось на проекте гр.36 КТЕ5-МС-100/230 для ДСС.
//    #define  _i2c_av_end  (_i2c_av_beg + (((_i2c_jrn_end - _i2c_av_beg)*3)/4))
      #define  _i2c_av_end  (_i2c_av_beg + (lw)(_i2c_jrn_end - _i2c_av_beg)*3/4)

#else
    #ifdef _INTERPRETER
        #define  _i2c_av_end   (_i2c_code_beg-1) // Конец следа в i2c при отсутствии _JOURNAL и наличии _INTERPRETER
    #else
        #define  _i2c_av_end   _i2c_end // Конец следа в i2c при отсутствии _JOURNAL и _INTERPRETER
    #endif
#endif
//----
// 3. Область записей журнала
#ifdef _JOURNAL
    #define  _i2c_jrn_beg    ( _i2c_av_end+1 )  // Начало журнала в i2c - после следа

    #ifdef _INTERPRETER
        #define  _i2c_jrn_end    (_i2c_code_beg-1) // Конец журнала в i2c при наличии _INTERPRETER
    #else
        #define  _i2c_jrn_end    _i2c_end         // Конец журнала в i2c при отсутствии _INTERPRETER
    #endif
#endif
//----
// 4. Область кода программы
#ifdef _INTERPRETER
    #ifndef _MAX_LEN_CODE
        #define _MAX_LEN_CODE  (0x0800) // Максимальный размер зашивочного файла 2048 байт
    #endif
    #define _i2c_code_beg  (_i2c_end-_MAX_LEN_CODE+1)  // Начало кода программы в i2c
    #define _i2c_code_end  _i2c_end  // Конец кода программы в i2c
#endif

#endif //_SD_Card_

/*
#else   //_CM3_
 //Аналоговые уставки не изменяются в зависимости от области
 #define  _ar_adr_i2c   ((lw)&_f_ar - _flash_beg)

#ifdef _JOURNAL

 #define _i2c_jrn_beg   ((lw)&_f_ - _flash_beg)
 #define _i2c_jrn_end   ( _SIZE_JRN_OBL + _flash_beg)

#endif

#ifdef _INTERPRETER

 #define _i2c_code_beg ((lw)obj_prg_obl - _flash_beg)
 #define _i2c_code_end  (_i2c_code_beg + _MAX_LEN_CODE)
*/
/*
#else  //_CM3_

#ifdef _INTERPRETER
    #ifndef _MAX_LEN_CODE
        #define _MAX_LEN_CODE  (0x0800) // Максимальный размер зашивочного файла 2048 байт
    #endif
#endif

#endif  //_CM3_
*/
//------------------------------------------------------------------------------------------

/*
// ----------------Вариант 2----------------
// 1. Область кода программы
#ifdef _INTERPRETER
    #ifndef _MAX_LEN_CODE
        #define _MAX_LEN_CODE  ((w)0x0800) // Максимальный размер зашивочного файла 2048 байт
    #endif
    #define _i2c_code_beg  _i2c_beg  // Начало кода программы в i2c
    #define _i2c_code_end  ((w)(_i2c_beg+_MAX_LEN_CODE-1)) // Конец кода программы в i2c
#endif
//----
// 2. Область уставок начинается с аналоговых уставок
#ifdef _INTERPRETER
    #define  _ar_adr_i2c   ((w)(_i2c_code_end+1))
#else
    #define  _ar_adr_i2c   _i2c_beg
#endif
//----
// 3. Область аварийного следа
//    в "obj.h" #define  _kol_obl    ( 1 ) // Количество областей уставок
#define  _i2c_av_beg   ((_ar_adr_i2c+_v_ar)+(_sm_obl_ust*_kol_obl)+1)
#ifdef _JOURNAL
    // -------------------------------------------------------
    //                   Для FR
    // При распределении i2c между следом и журналом 3/4 имеем:
    // -------------------------------------------------------
    // интерпретатор | журнал | следов | записей журнала
    // --------------|--------|--------|----------------------
    //      +        |   +    |    9   |      149
    // --------------|--------|--------|----------------------
    //      +        |   -    |   15   |       -
    // --------------|--------|--------|----------------------
    //      -        |   +    |   11   |      157
    // --------------|--------|--------|----------------------
    //      -        |   -    |   17   |       -
    // --------------|--------|--------|----------------------
    #define  _i2c_av_end  ((w)((lw)((lw)(w)(_i2c_jrn_end - _i2c_av_beg)*(lw)3)/(w)4))
#else
    #define  _i2c_av_end   _i2c_end // При отсутствии журнала под след отводится вся свободная область
#endif
//----
// 4. Область записей журнала
#ifdef _JOURNAL
    #define  _i2c_jrn_beg    ((w)(_i2c_av_end+1))  // Начало журнала в i2c - после следа
    #define  _i2c_jrn_end    _i2c_end         // Конец журнала в i2c
#endif
*/
//------------------------------------------------------------------------------------------

#ifdef _MAIN_INCLUDE
#ifdef _CM3_
#ifndef _SD_Card_

lword _r_adr_i2c;
lword _ar_adr_i2c;
lword _or_adr_i2c;
lword _sr_adr_i2c;
lword _TablSled_adr_i2c;

#ifdef _INTERPRETER

lword _i2c_code_beg, _i2c_code_end;

#endif
//word _Ivz_adr_i2c;
lword  _TabFunc_adr_i2c;
#ifdef _JOURNAL
  lword  _TablJrn_adr_i2c; //адрес в i2c уставок журнала
#endif

#ifdef _INTERPRETER
  lword  _ExtPrg_adr_i2c; //адрес в i2c блока объектной программы
#endif

#else //SD_Card

SD_Addr _r_adr_i2c;
SD_Addr _ar_adr_i2c;
SD_Addr _or_adr_i2c;
SD_Addr _sr_adr_i2c;
SD_Addr _TablSled_adr_i2c;

#ifdef _INTERPRETER

SD_Addr _i2c_code_beg, _i2c_code_end;

#endif
//word _Ivz_adr_i2c;
SD_Addr  _TabFunc_adr_i2c;
#ifdef _JOURNAL
SD_Addr  _TablJrn_adr_i2c; //адрес в i2c уставок журнала
#endif

#ifdef _INTERPRETER
  SD_Addr  _ExtPrg_adr_i2c; //адрес в i2c блока объектной программы
#endif

#endif
#ifdef _JOURNAL

//lword _i2c_jrn_beg, _i2c_jrn_end;

#endif

#else  //_CM3_

word _r_adr_i2c;
word _ar_adr_i2c;
word _or_adr_i2c;
word _sr_adr_i2c;
word _TablSled_adr_i2c;//word _Ivz_adr_i2c;
word  _TabFunc_adr_i2c;

#ifdef _JOURNAL
  word  _TablJrn_adr_i2c; //адрес в i2c уставок журнала
#endif

#ifdef _INTERPRETER
  word  _ExtPrg_adr_i2c; //адрес в i2c блока объектной программы
#endif

#endif
#else
#ifdef _CM3_

#ifndef _SD_Card_
extern lword _r_adr_i2c;
extern lword _ar_adr_i2c;
extern lword _or_adr_i2c;
extern lword _sr_adr_i2c;
extern lword _TablSled_adr_i2c;
#ifdef _INTERPRETER

extern lword _i2c_code_beg, _i2c_code_end;

#endif
//extern word _Ivz_adr_i2c;
extern lword  _TabFunc_adr_i2c;
#ifdef _JOURNAL
  extern lword  _TablJrn_adr_i2c;
#endif

#ifdef _INTERPRETER
  extern lword  _ExtPrg_adr_i2c;
#endif

#else

extern SD_Addr _r_adr_i2c;
extern SD_Addr _ar_adr_i2c;
extern SD_Addr _or_adr_i2c;
extern SD_Addr _sr_adr_i2c;
extern SD_Addr _TablSled_adr_i2c;

#ifdef _INTERPRETER

extern SD_Addr _i2c_code_beg, _i2c_code_end;

#endif
//extern word _Ivz_adr_i2c;
extern SD_Addr  _TabFunc_adr_i2c;

#ifdef _JOURNAL
  extern SD_Addr  _TablJrn_adr_i2c;
#endif

#ifdef _INTERPRETER
  extern SD_Addr  _ExtPrg_adr_i2c;
#endif

#endif
#ifdef _JOURNAL

//extern lword _i2c_jrn_beg, _i2c_jrn_end;

#endif

#else  //_CM3_

extern word _r_adr_i2c;
extern word _ar_adr_i2c;
extern word _or_adr_i2c;
extern word _sr_adr_i2c;
extern word _TablSled_adr_i2c;
//extern word _Ivz_adr_i2c;
extern word  _TabFunc_adr_i2c;
#ifdef _JOURNAL
  extern word  _TablJrn_adr_i2c;
#endif

#ifdef _INTERPRETER
  extern word  _ExtPrg_adr_i2c;
#endif

#endif
#endif


/*---------    Для монитора    ------------*/
#ifdef _CM3_

#define TxBuffSize          ((w) 0x007Fu) /* все мл.разряды в указателе
                                           * размера должны быть запол-
                                           * нены единицами    */
#define RxBuffSize          ((w) 0x007Fu) /* все мл.разряды в указателе
                                           * размера должны быть запол-
                                           * нены единицами    */
#else

#define TxBuffSize          ((w) 0x003Fu) /* все мл.разряды в указателе
                                           * размера должны быть запол-
                                           * нены единицами    */
#define RxBuffSize          ((w) 0x001Fu) /* все мл.разряды в указателе
                                           * размера должны быть запол-
                                           * нены единицами    */

#endif
/*ДДДДДД-  Длп  паогаамм аабовл б пглмвом  ДДДДДДДДД  */

  #define   BckSp         0x08u

  #define   FrvdSp        0x0cu

  #define   Enter         0x0Du

  #define   Shift_Enter   'x'

  #define   Esc           0x1Bu

  #define   Shift_Esc     'y'

  #define   Up            '+'

  #define   Down          '-'

  #define   Shift_Up      '='

  #define   Shift_Down    '_'

  #define   CR            0x0Du

  #define   LF            0x0Au

  #define   Return        Esc

  #define   _Stop         '*'

  #define   _Start        'p'

  #define   _Shift_Start  'P'

  #define   _Reset        '@'

  #define   _ComPref      0x1f //Преффикс для перевода терминала в режим ввода комманды

  #define   _Cursor_Home  0x01 // Kурсор в левый верхний угол

  #define  _Set_Cursor    0x02 //Команда установки курсора в определенную позицию
                                       //(адрес определяется в следующем байте ), формат: 0x00-0x3f - Верхняя строка
                                       //                                                 0x40-0x7f - Нижняя строка
  #define   _Cursor_On    0x03 // Включить курсор

  #define   _Cursor_Off   0x04 // Выключить курсор

  #define  _PultikSwet   0x00 //24.02.09 15:27 для вкл.подсветки пультика

  #define  _ClrDisplay    0x05 //Команда очистки диспле


  //Пароль для доступа ко всем пунктам меню
  #define   _PassW          1
  //Пароль доступа к служебным программам
  #define   _PassWS         3

  //#define   _N_prog         1
         /*  Пультовая программа исходного состояния пульта.  */
  #ifndef   _MainPultProg
    #define   _MainPultProg  _Case (  0  ,  0  )
  #endif
         /*  Код пультовой программы - Norton.  */
  #define   _NortonPultProg  _Case (  'A',  0  )

          /* паузы между символами в режиме бегущей строки в
           * дискретах переполнений "TIMER1"  */
  #define   _SymbolPauza       ( _Sec(0.140) )

          /* пауза между отдельными сообщениями в любом режиме
           * в дискретах переполнений "TIMER1" */
  #define   _SoobPauza         ( _Sec(2.0) ) //1.2

          /* пауза, после которой ( при отсутствии нажатий на клавиатуре )
           * монитор приводится в исходное состояние
           * ( в дискретах переполнений "TIMER1" ) */
  #define   _TimeDoGasheniya   ( _Sec(100) )

          /* пауза между выводом приглашений монитором, после того как тот
           * ( при отсутствии нажатий на клавиатуре ) был приведен в исходное
           * состояние ( в дискретах переполнений "TIMER1" ) */
  #define   _MAvtoPovtor       ( _Sec(1.66) )

          /* Для А8: величина ограничения вывода имени бита на экран:
               Ограничиваем вывод имени бита на 14-ти символах для возможности
             указания в таблице А8 адресов строк сообщений из "А1-Сообщения" и чтобы
             символы не выезжали за экран, т.к. сообщения 16-ти символьные -
             понадобилось для СВТГ для масок переходов между СВ1 и СВ2 по авариям.
           */
  #define   _A8_bit_txt_size    14

    /*--------  Флаги для монитора  ---------  */
 struct Monitor_Flags {
                 word   UartCAN_Connect : 1 ;
                 word   FirstCall  : 1 ;  /* для пультовых программ признак первого входа в п/п для инициализации.  */
                 word   i2c_busy   : 1 ;
                 word   RXBuffOverflow   : 1 ; //24.02.09 15:27 используем для вкл.подсветки пультика

                 word   Pult       : 1 ;
                 word   NewCiklMsg : 1 ;
                 word EnableSrvMsg : 1 ;
                 word   RX_Data_ok : 1 ;

                 word   Password_Ok: 1 ;

                 word   FirstCallFazir    : 1;   // 21.05.2020
                 word   FirstCallFazir_Is : 1;   // 22.05.2020
                 word   FirstCallFazir_Us : 1;   // 22.05.2020
        } ;

#define  M_FirstCall   Mon.FirstCall

#define  M_FirstCallFazir    Mon.FirstCallFazir      // 21.05.2020
#define  M_FirstCallFazir_Is Mon.FirstCallFazir_Is   // 22.05.2020
#define  M_FirstCallFazir_Us Mon.FirstCallFazir_Us   // 22.05.2020

#define  point( kod ) stop_point1 = kod
#define  p( kod )     stop_point1 = kod
#define  pS( kod )    stop_pointS1 = kod
#define  pV( kod )    stop_pointV1 = kod
#define  pP( kod )    stop_pointP1 = kod
#define  pD( kod )    stop_pointD1 = kod
#define  pR( kod )    stop_pointR1 = kod

#ifdef _NARABOTKA
  struct T_Rab
    {
      word  hou ; // часы              , 0 - 60000
      byte  min ; // минуты            , 0 - 59
      byte  sec ; // секуднды          , 0 - 59
      byte  ovr ; // переполнения часов, 0 - 200     Всего 1369 лет... Должно хватить...
#ifdef _OBJ_Narabotka
      Obj_Narabotka_struct ;
#endif
#ifdef _BTE
#ifdef _MAX_LIM_PUSK
      word cntLimitPusk;                 // счетчик пусков
      word cntMinNextPusk[_MAX_LIM_PUSK]; // день недели сброса счетчика пусков
      word checkDayPusk;                 // день пуска в году
#endif

    struct { word Id_z_Scan ;
             word Qr_z_Scan ;
             word Us_z_Scan ;
             word Cos_z_Scan ;
             word Contrl_sum ; } Start_z ;
#endif
    }   ;

    union flgRAB
    {
      word all ;
      struct
        {
          word  rab_rd    : 1  ;
          word  rab_wr    : 1  ;
          word  rab_beg   : 1  ;
          word  new_sec   : 1  ;

          word  load_ok   : 1  ;
          word  null_all  : 1  ;
          word  rezerv    : 10 ;
        } _ ;
    } ;
#endif


union UART_CAN
{
  word all ;
#ifndef   _Union_FR
  struct
  {
    word Symbol  : 8 ;

    word Connect    : 1 ;
    word LOsc_dataR : 1 ;  //21.10.21 - добавка для осциллографа по Modbus используется в Link
    word LOsc_start : 1 ;  //21.10.21 - добавка для осциллографа по Modbus используется в Link
    word tx_array   : 1 ;
    word rx_num     : 2 ;
    word tx_num     : 2 ;
  } _ ;
#else
  struct
  {
    word tx_num  : 2 ;
    word rx_num  : 2 ;
    word tx_array: 1 ;
    word rezerv  : 2 ;
    word Connect : 1 ;

    word Symbol  : 8 ;
  } _ ;
#endif
} ;

#define _UartCAN_Tx_Size 32

union UART_CANtx
{
   word all ;
   byte symbols[_UartCAN_Tx_Size] ;

#ifndef   _Union_FR
  struct
  {
    word Symbol  : 8 ;

    word Connect    : 1 ;
    word LOsc_dataR : 1 ;  //21.10.21 - добавка для осциллографа по Modbus используется в Link
    word LOsc_start : 1 ;  //21.10.21 - добавка для осциллографа по Modbus используется в Link
    word rezerv     : 1 ;
    word rx_num     : 2 ;
    word tx_num     : 2 ;
  } _ ;
#else
  struct
  {
    word tx_num  : 2 ;
    word rx_num  : 2 ;
    word rezerv  : 3 ;
    word Connect : 1 ;

    word Symbol  : 8 ;
  } _ ;
#endif
} ;


struct AboutMenu
{
  char const *txt1;
  char const *txt2;
  word label;
};

/*------------------------------------------------*/
#ifdef _MAIN_INCLUDE
/*------------------------------------------------*/

byte Write_ust ;
word time_Svet;

                 // Структура штатных сообщений.

struct MSG_regs  msg_buf ;  // буфер для сбора текущих сообщений.

struct MSG_reg   msg_reg ;
                 // Структура восстановленных аварийных сообщений.
struct MSG_reg   msg_av ;

lword   mask_service, mask_service2 ;

#ifdef _TRETIY_REG
lword   mask_service3 ;
#endif

_register word    m_index ;
_register word    m_time  ;
_register word    m_addr  ;
_register word    m_ext   ;
_register double  m_dax, m_dbx ;
#ifdef _CM3_
lword m_lext;
#else
word m_lext;
#endif
_register word    m_old;
char    m_buff[16] ;  /* размер должен быть 8,16,32 для п/п "RW_I2C".  */
word t_clock, n_clock, clock_max;
byte clock_ed;

byte Klav_Buff , S_break ;
const char* DWell_old;

const char* AWell_old;

_register byte     InRxBuffCount ;
_register byte    OutRxBuffCount ;

_register byte    InTxBuffCount  ;

_register byte    OutTxBuffCount  ;

_register byte    m_ch ;

_register byte   Label ;   /*  всеобщий указатель для переключателей в  */
                             /*  программах работы с терминалом  */
_register byte   LabelFazir ;      // 21.05.2020

_register byte   LabelFazir_Is ;   // 21.05.2020

_register byte   LabelFazir_Us ;   // 21.05.2020

         word     Pult_Prog_Addr ;
byte ListIndic;
     /*--- Счетчик переполнений "Timer1" ----*/
#ifndef _CM3_
volatile _register word    Timer1_Ovr ;
#else
volatile _register word    Timer1_Ovr @ "RAM_region" ;  // для проверки внешнего ОЗУ кладём во внутреннее .
#endif
_register word    Timer1_fSec ;

          /* счетчик отсчета паузы между символами в режиме бегущей строки в
           * дискретах переполнений "TIMER1"  */
        byte     Count_SymbolPauza ;

struct Monitor_Flags   Mon;

           /* указатель на адрес текста приглашения-готовности монитора  */
      char const* MWelcome ;

           /* указатель на адрес текста приглашения-готовности монитора  */
      char const* DWelcome ;
      char const* AWelcome ;

           /*   указатель на адрес текста передаваемого в качестве параметра  */
           /* в функцию вывода строки текста.  */
_register  char const*  str_addr ;

         /* буфер на выдачу данных в последовательный порт */
        byte     TxBuff[TxBuffSize+1]  ;      /* static */
        byte     RxBuff[RxBuffSize+1]  ;      /* static */
        byte      Nort_Password;

//word  Sch_Byte  ;

byte  *from_i2c;
word  into_i2c ;
byte  i2c_label1, i2c_label ;
         byte    i2c_buff[3] ;  /* такой размер нужен для п/п ReadWrite_MemBlock.  */

byte  i2c_av_label , *av_adr_data  ;

#ifndef _CM3_
word  i2c_av_addr ;
#else
lword  i2c_av_addr ;
#endif

word i2c_tim;
byte Wr_label;
//  KVV_backup:
byte Backup_label;
_register byte stop_point ;    /*  control of stop processor.  */
          byte stop_point1 ;
byte  stop_pointS , stop_pointS1 ; // стоповая точка прерывания СИФУ .
byte  stop_pointV , stop_pointV1 ; // стоповая точка прерывания СИФУВ .
byte  stop_pointP , stop_pointP1 ; // стоповая точка прерывания ПДФ .
byte  stop_pointD , stop_pointD1 ; // стоповая точка прерывания DP .
byte  stop_pointR , stop_pointR1 ; // стоповая точка прерывания Реверс .
byte _N_prog;
word APV_mask;

#ifdef _NARABOTKA
 struct T_Rab NARAB;
 #ifndef _CM3_
   struct T_Rab NARAB_buff ;
 #else
  /*__no_init */ struct T_Rab NARAB_buff ; // 17.10.19 FAA вернульсь на сохранение по станд. с i2c
 #endif
//#ifndef _CM3_ // 17.10.19 FAA вернульсь на сохранение по станд. с i2c
 struct rld_i2c RAB ;
//#endif
 union  flgRAB  narab ;
 byte   i2c_lab ;
 byte   Nsec ;
 byte   old_sec ;
#endif

//Переменная для занесения значений при тестировании DACов
word T_DAC;

union UART_CANtx UartCAN_Tx;
union UART_CAN UartCAN_Rx;

byte copy_code_rezerv;
/*------------------------------------------------*/
#else
/*------------------------------------------------*/
extern union UART_CAN UartCAN_Tx;
extern union UART_CAN UartCAN_Rx;

extern byte copy_code_rezerv;

extern byte Write_ust ;
extern word time_Svet;

extern struct MSG_regs  msg_buf ;
extern struct MSG_reg   msg_reg ;
extern struct MSG_reg   msg_av ;
extern lword   mask_service, mask_service2 ;

#ifdef _TRETIY_REG
extern lword   mask_service3 ;
#endif

extern _register word    m_index ;
extern _register word    m_time  ;
extern _register word    m_addr  ;
extern _register word    m_ext   ;
extern _register word    m_old;

#ifdef _CM3_
extern lword m_lext;
#else
extern word m_lext;
#endif

extern _register double  m_dax, m_dbx ;
extern          char    m_buff[16] ;
extern  const char*  DWell_old;

extern  const char*  AWell_old;

extern _register byte     InRxBuffCount ;
extern _register byte    OutRxBuffCount ;

extern _register byte    InTxBuffCount  ;

extern _register byte    OutTxBuffCount  ;

extern _register byte    m_ch ;

extern          struct Monitor_Flags   Mon;

extern _register byte   Label ;

extern _register byte   LabelFazir ;      // 21.05.2020

extern _register byte   LabelFazir_Is ;   // 21.05.2020

extern _register byte   LabelFazir_Us ;   // 21.05.2020

extern          word     Pult_Prog_Addr ;

extern  byte ListIndic;

extern volatile _register word     Timer1_Ovr ;
extern _register word     Timer1_fSec ;

extern          byte     Count_SymbolPauza ;

extern     char const*   MWelcome ;

extern     char const*   DWelcome ;

extern     char const*   AWelcome ;

extern  _register char const*   str_addr ;

extern          byte     TxBuff[]  ;

extern          byte     RxBuff[]  ;

extern          byte      Nort_Password;

//extern          word  Sch_Byte  ;

extern   byte *from_i2c ;
extern   word  into_i2c ;
extern   byte  i2c_label1, i2c_label ;
extern   byte  i2c_buff[] ;

#ifndef _CM3_
extern word  i2c_av_addr ;
#else
extern lword  i2c_av_addr ;
#endif

extern   word i2c_tim;
extern   byte  i2c_av_label , *av_adr_data  ;
extern   word  t_clock, n_clock, c_max;
extern   byte  clock_ed ;
extern   byte Klav_Buff , S_break ;
extern   byte Wr_label;
//  KVV_backup:
extern   byte Backup_label;

//extern   byte PTS_cont_old;
extern   byte _N_prog;

extern word APV_mask;

#ifdef _NARABOTKA
 extern struct T_Rab NARAB;
 #ifndef _CM3_
   extern struct T_Rab NARAB_buff ;
 #else
  extern __no_init  struct T_Rab NARAB_buff ;
 #endif
#ifndef _CM3_
 extern struct rld_i2c RAB ;
#endif
 extern union  flgRAB  narab ;
 extern byte   i2c_lab ;
 extern byte   Nsec ;
 extern byte   old_sec ;
#endif

extern _register byte stop_point ;
extern           byte stop_point1 ;
extern   byte  stop_pointS , stop_pointS1 ; // стоповая точка прерывания СИФУ .
extern   byte  stop_pointV , stop_pointV1 ; // стоповая точка прерывания СИФУВ .
extern   byte  stop_pointP , stop_pointP1 ; // стоповая точка прерывания ПДФ .
extern   byte  stop_pointD , stop_pointD1 ; // стоповая точка прерывания DP .
extern   byte  stop_pointR , stop_pointR1 ; // стоповая точка прерывания Реверс .
extern word T_DAC;

/*------------------------------------------------*/

#endif
#endif
