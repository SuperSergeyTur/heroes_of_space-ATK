#ifndef  _NETPULT_H
  #define   _NETPULT_H


void NetIndicator_Drive ( void );
void NetSetab_Drive (char *numb, word kol);
void NetSetabBit_Drive (char *numb, word kol);


//----------------------------------------
#ifdef _NET_INCLUDE
//----------------------------------------

//----------------------------------------
#ifdef _NET_IRQ
//----------------------------------------
// Таблицы для сетевых плат
  //-----
  #ifndef _LANG_RU_
  //-----
_x_far const struct STB       stb_net1[ ] =
{
    { "Адреса     ", &_r.DP_addr          , 0               , 0x7f             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) }
};

_x_far const struct STB       stb_net2[ ] =
{
    { "IP-адреса 1", &_r.IP1_addr          , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "IP-адреса 2", &_r.IP2_addr          , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "IP-адреса 3", &_r.IP3_addr          , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "IP-адреса 4", &_r.IP4_addr          , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "IP-маска 1 ", &_r.IPM1_addr         , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "IP-маска 2 ", &_r.IPM2_addr         , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "IP-маска 3 ", &_r.IPM3_addr         , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "IP-маска 4 ", &_r.IPM4_addr         , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "IP-шлюз 1  ", &_r.DIP1_addr         , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "IP-шлюз 2  ", &_r.DIP2_addr         , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "IP-шлюз 3  ", &_r.DIP3_addr         , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "IP-шлюз 4  ", &_r.DIP4_addr         , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "EMAC-адр.1 ", &_r.EMAC1_addr        , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "EMAC-адр.2 ", &_r.EMAC2_addr        , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "EMAC-адр.3 ", &_r.EMAC3_addr        , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "EMAC-адр.4 ", &_r.EMAC4_addr        , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "EMAC-адр.5 ", &_r.EMAC5_addr        , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "EMAC-адр.6 ", &_r.EMAC6_addr        , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "Таймер WD  ", &_r.Net_LT            , 0               , 0xff             , 1            ,(w*)&_ind_Nom, 1              , 0xff, "мсек"  , _form(1,3,0,1) }
};

_x_far const struct STB       stb_net3[ ] =
{
    { "Адреса     ", &_r.RTU_addr          , 0               , 0xf7             , 1            ,(w*)&_ind_Nom, 1              , 0xff, "ед"  , _form(1,3,0,1) },
    { "Таймер WD  ", &_r.Net_LT            , 0               , 0xff             , 1            ,(w*)&_ind_Nom, 1              , 0xff, "мсек"  , _form(1,3,0,1) }
};

_x_far const struct STB       stb_net4[ ] =
{
    { "Nвх.парам. ", &_r.Num_RS485_In      , 0               , 0xff             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) },
    { "Nвих.парам.", &_r.Num_RS485_Out     , 0               , 0xff             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) },
    { "Таймер WD  ", &_r.Net_LT            , 0               , 0xff             , 1            ,(w*)&_ind_Nom, 1              , 0xff, "мсек"  , _form(1,3,0,1) }
};
  //-----
  #else //ifndef _LANG_RU_
  //-----
_x_far const struct STB       stb_net1[ ] =
{
    { "Адрес      ", &_r.DP_addr          , 0               , 0x7f             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) }
};

_x_far const struct STB       stb_net2[ ] =
{
    { "IP-адрес 1 ", &_r.IP1_addr          , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "IP-адрес 2 ", &_r.IP2_addr          , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "IP-адрес 3 ", &_r.IP3_addr          , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "IP-адрес 4 ", &_r.IP4_addr          , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "IP-маска 1 ", &_r.IPM1_addr         , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "IP-маска 2 ", &_r.IPM2_addr         , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "IP-маска 3 ", &_r.IPM3_addr         , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "IP-маска 4 ", &_r.IPM4_addr         , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "IP-шлюз 1  ", &_r.DIP1_addr         , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "IP-шлюз 2  ", &_r.DIP2_addr         , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "IP-шлюз 3  ", &_r.DIP3_addr         , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "IP-шлюз 4  ", &_r.DIP4_addr         , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "EMAC-адр.1 ", &_r.EMAC1_addr        , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "EMAC-адр.2 ", &_r.EMAC2_addr        , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "EMAC-адр.3 ", &_r.EMAC3_addr        , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "EMAC-адр.4 ", &_r.EMAC4_addr        , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "EMAC-адр.5 ", &_r.EMAC5_addr        , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "EMAC-адр.6 ", &_r.EMAC6_addr        , 0               , 0xfe             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) } ,
    { "Таймер WD  ", &_r.Net_LT            , 0               , 0xff             , 1            ,(w*)&_ind_Nom, 1              , 0xff, "мсек"  , _form(1,3,0,1) }
};

_x_far const struct STB       stb_net3[ ] =
{
    { "Адрес      ", &_r.RTU_addr          , 0               , 0xf7             , 1            ,(w*)&_ind_Nom, 1              , 0xff, "ед"  , _form(1,3,0,1) },
    { "Таймер WD  ", &_r.Net_LT            , 0               , 0xff             , 1            ,(w*)&_ind_Nom, 1              , 0xff, "мсек"  , _form(1,3,0,1) }
};

_x_far const struct STB       stb_net4[ ] =
{
    { "Nвх.парам. ", &_r.Num_RS485_In      , 0               , 0xff             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) },
    { "Nвых.парам.", &_r.Num_RS485_Out     , 0               , 0xff             , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,3,0,1) },
    { "Таймер WD  ", &_r.Net_LT            , 0               , 0xff             , 1            ,(w*)&_ind_Nom, 1              , 0xff, "мсек"  , _form(1,3,0,1) }
};
  //-----
  #endif //ifndef _LANG_RU_
  //-----


_x_far struct UstUzm   NetUstav1[] =
  {
    {"Profibus DP" ,sizeof(stb_net1   )/sizeof(struct STB) ,&stb_net1[0] }
  };

_x_far struct UstUzm   NetUstav2[] =
  {
    {"Modbus TCP " ,sizeof(stb_net2   )/sizeof(struct STB) ,&stb_net2[0] }
  };

_x_far struct UstUzm   NetUstav3[] =
  {
    {"Modbus RTU " ,sizeof(stb_net3   )/sizeof(struct STB) ,&stb_net3[0] }
  };

_x_far struct UstUzm   NetUstav4[] =
  {
    {"RS485FD    " ,sizeof(stb_net4   )/sizeof(struct STB) ,&stb_net4[0] }
  };


struct UstUzm   *NetUstav ;
word NetNumUstav ;


  //-----
  #ifndef _LANG_RU_
  //-----
_x_far struct Bits    Netbts1[] =
    { "Конфiг.    " , &_r.net_setting.all,  1 ,
                               {
                                 "Увiм.обмiн  "
                               },
      { _net_cfg_vkl },
      (w*)&_Msk,1
    }  ;

_x_far struct Bits    Netbts2[] =
{
    { "Конфiг.    " , &_r.net_setting.all,  4 ,
                               {
                                 "Увiм.обмiн  " ,
                                 "Вкл пар/неп." ,
                                 "Пар/непарн  " ,
                                 "Стоп-бiт    "
                               },
      { _net_cfg_vkl, _net_cfg_par1, _net_cfg_par2, _net_cfg_stop },
      (w*)&_Msk,1
    },
    { "Скорость   " , &_r.net_spd.all,  8 ,
                               {
                                 "1200 бiт/с  " ,
                                 "2400 бiт/с  " ,
                                 "4800 бiт/с  " ,
                                 "9600 бiт/с  " ,
                                 "19200 бiт/с " ,
                                 "38400 бiт/с " ,
                                 "56800 бiт/с " ,
                                 "115200 бiт/c"
                               },
      { _net_spd_1, _net_spd_2, _net_spd_4, _net_spd_9, _net_spd_19,
        _net_spd_38, _net_spd_56, _net_spd_115 },
      (w*)&_Msk,1
    }
  } ;
  //-----
  #else //ifndef _LANG_RU_
  //-----
_x_far struct Bits    Netbts1[] =
    { "Конфиг.    " , &_r.net_setting.all,  1 ,
                               {
                                 "Вкл.обмен   "
                               },
      { _net_cfg_vkl },
      (w*)&_Msk,1
    }  ;

_x_far struct Bits    Netbts2[] =
{
    { "Конфиг.    " , &_r.net_setting.all,  4 ,
                               {
                                 "Вкл.обмен   " ,
                                 "Вкл чет/неч." ,
                                 "Чет/нечет   " ,
                                 "Стоп-бит    "
                               },
      { _net_cfg_vkl, _net_cfg_par1, _net_cfg_par2, _net_cfg_stop },
      (w*)&_Msk,1
    },
    { "Скорость   " , &_r.net_spd.all,  8 ,
                               {
                                 "1200 бит/с  " ,
                                 "2400 бит/с  " ,
                                 "4800 бит/с  " ,
                                 "9600 бит/с  " ,
                                 "19200 бит/с " ,
                                 "38400 бит/с " ,
                                 "56800 бит/с " ,
                                 "115200 бит/c"
                               },
      { _net_spd_1, _net_spd_2, _net_spd_4, _net_spd_9, _net_spd_19,
        _net_spd_38, _net_spd_56, _net_spd_115 },
      (w*)&_Msk,1
    }
  } ;
  //-----
  #endif //ifndef _LANG_RU_
  //-----

    struct Bits *Netbts ;
    word NetNumBUst ;


_x_far /*const*/ struct Ind  ind_net1[] =
  {
         { "In1   ,In2    ", { &Profi_dp.In_PPO[0]   ,&Profi_dp.In_PPO[1]}   ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "In3   ,In4    ", { &Profi_dp.In_PPO[2]   ,&Profi_dp.In_PPO[3]}   ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "In5   ,In6    ", { &Profi_dp.In_PPO[4]   ,&Profi_dp.In_PPO[5]}   ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "In7   ,In8    ", { &Profi_dp.In_PPO[6]   ,&Profi_dp.In_PPO[7]}   ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "In9   ,In10   ", { &Profi_dp.In_PPO[8]   ,&Profi_dp.In_PPO[9]}   ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "In11  ,In12   ", { &Profi_dp.In_PPO[10]  ,&Profi_dp.In_PPO[11]}  ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "In13  ,In14   ", { &Profi_dp.In_PPO[12]  ,&Profi_dp.In_PPO[13]}  ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "In15  ,In16   ", { &Profi_dp.In_PPO[14]  ,&Profi_dp.In_PPO[15]}  ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "Out1  ,Out2   ", { &Profi_dp.Out_PPO[0]  ,&Profi_dp.Out_PPO[1]}  ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "Out3  ,Out4   ", { &Profi_dp.Out_PPO[2]  ,&Profi_dp.Out_PPO[3]}  ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "Out5  ,Out6   ", { &Profi_dp.Out_PPO[4]  ,&Profi_dp.Out_PPO[5]}  ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "Out7  ,Out8   ", { &Profi_dp.Out_PPO[6]  ,&Profi_dp.Out_PPO[7]}  ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "Out9  ,Out10  ", { &Profi_dp.Out_PPO[8]  ,&Profi_dp.Out_PPO[9]}  ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "Out11 ,Out12  ", { &Profi_dp.Out_PPO[10] ,&Profi_dp.Out_PPO[11]} ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "Out13 ,Out14  ", { &Profi_dp.Out_PPO[12] ,&Profi_dp.Out_PPO[13]} ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "Out15 ,Out16  ", { &Profi_dp.Out_PPO[14] ,&Profi_dp.Out_PPO[15]} ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "CfgI1 ,CfgI2  ", { &Profi_dp.Prm_Data[0] ,&Profi_dp.Prm_Data[1]} ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,3,0,1)}},
         { "CfgI3 ,CfgI4  ", { &Profi_dp.Prm_Data[2] ,&Profi_dp.Prm_Data[3]} ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,3,0,1)}},
         { "CfgI5 ,CfgI6  ", { &Profi_dp.Prm_Data[4] ,&Profi_dp.Prm_Data[5]} ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,3,0,1)}},
         { "CfgI7 ,CfgI8  ", { &Profi_dp.Prm_Data[6] ,&Profi_dp.Prm_Data[7]} ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,3,0,1)}},
         { "CfgI9 ,CfgI10 ", { &Profi_dp.Prm_Data[8] ,&Profi_dp.Prm_Data[9]} ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,3,0,1)}},
         { "CfgI11,CfgI12 ", { &Profi_dp.Prm_Data[10],&Profi_dp.Prm_Data[11]},{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,3,0,1)}},
         { "CfgI13,CfgI14 ", { &Profi_dp.Prm_Data[12],&Profi_dp.Prm_Data[13]},{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,3,0,1)}},
         { "CfgI15,CfgI16 ", { &Profi_dp.Prm_Data[14],&Profi_dp.Prm_Data[15]},{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,3,0,1)}},
         { "CfgO1 ,CfgO2  ", { &Profi_dp.Prm_Data[16],&Profi_dp.Prm_Data[17]},{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,3,0,1)}},
         { "CfgO3 ,CfgO4  ", { &Profi_dp.Prm_Data[18],&Profi_dp.Prm_Data[19]},{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,3,0,1)}},
         { "CfgO5 ,CfgO6  ", { &Profi_dp.Prm_Data[20],&Profi_dp.Prm_Data[21]},{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,3,0,1)}},
         { "CfgO7 ,CfgO8  ", { &Profi_dp.Prm_Data[22],&Profi_dp.Prm_Data[23]},{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,3,0,1)}},
         { "CfgO9 ,CfgO10 ", { &Profi_dp.Prm_Data[24],&Profi_dp.Prm_Data[25]},{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,3,0,1)}},
         { "CfgO11,CfgO12 ", { &Profi_dp.Prm_Data[26],&Profi_dp.Prm_Data[27]},{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,3,0,1)}},
         { "CfgO13,CfgO14 ", { &Profi_dp.Prm_Data[28],&Profi_dp.Prm_Data[29]},{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,3,0,1)}},
         { "CfgO15,CfgO16 ", { &Profi_dp.Prm_Data[30],&Profi_dp.Prm_Data[31]},{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,3,0,1)}},
         { "CfgVar,Code   ", { &Profi_dp.Prm_Data[32],&Profi_dp.Op          },{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,3,0,1)}},
         { "Group ,Number ", { &Profi_dp.Gr          ,&Profi_dp.var2        },{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,5,0,2)}},
         { "Var_h  ,Var_l ", { &Profi_dp.var3._.high ,&Profi_dp.var3._.low  },{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "Error         ", { &Profi_dp.err                                },{1,1},{"   "    },{(w*)&_ind_Nom              },{_form(1,2,0,1)               }}
  };

_x_far /*const*/ struct Ind  ind_net2[] =
  {
         { "Function - In ", { &rmb.func                      } ,{ 1 },{"  "     },{(w*)&_ind_Nom              },{_form(1,5,0,2)               }},
         { "In1    ,In2   ", { &rmb.data[0]    ,&rmb.data[1]  } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "In3    ,In4   ", { &rmb.data[2]    ,&rmb.data[3]  } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "In5    ,In6   ", { &rmb.data[4]    ,&rmb.data[5]  } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "In7    ,In8   ", { &rmb.data[6]    ,&rmb.data[7]  } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "In9    ,In10  ", { &rmb.data[8]    ,&rmb.data[9]  } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "In11   ,In12  ", { &rmb.data[10]   ,&rmb.data[11] } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "In13   ,In14  ", { &rmb.data[12]   ,&rmb.data[13] } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "In15   ,In16  ", { &rmb.data[14]   ,&rmb.data[15] } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "In17   ,In18  ", { &rmb.data[16]   ,&rmb.data[17] } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "In19   ,In20  ", { &rmb.data[18]   ,&rmb.data[19] } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "In21   ,In22  ", { &rmb.data[20]   ,&rmb.data[21] } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "In23   ,In24  ", { &rmb.data[22]   ,&rmb.data[23] } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "In25   ,In26  ", { &rmb.data[24]   ,&rmb.data[25] } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "In27   ,In28  ", { &rmb.data[26]   ,&rmb.data[27] } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "In29   ,In30  ", { &rmb.data[28]   ,&rmb.data[29] } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "In31   ,In32  ", { &rmb.data[30]   ,&rmb.data[31] } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "Function - Out", { &smb.func                      } ,{ 1 },{"  "     },{(w*)&_ind_Nom              },{_form(1,5,0,2)               }},
         { "Out1   ,Out2  ", { &smb.data[0]    ,&smb.data[1]  } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "Out3   ,Out4  ", { &smb.data[2]    ,&smb.data[3]  } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "Out5   ,Out6  ", { &smb.data[4]    ,&smb.data[5]  } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "Out7   ,Out8  ", { &smb.data[6]    ,&smb.data[7]  } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "Out9   ,Out10 ", { &smb.data[8]    ,&smb.data[9]  } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "Out11  ,Out12 ", { &smb.data[10]   ,&smb.data[11] } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "Out13  ,Out14 ", { &smb.data[12]   ,&smb.data[13] } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "Out15  ,Out16 ", { &smb.data[14]   ,&smb.data[15] } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "Out17  ,Out18 ", { &smb.data[16]   ,&smb.data[17] } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "Out19  ,Out20 ", { &smb.data[18]   ,&smb.data[19] } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "Out21  ,Out22 ", { &smb.data[20]   ,&smb.data[21] } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "Out23  ,Out24 ", { &smb.data[22]   ,&smb.data[23] } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "Out25  ,Out26 ", { &smb.data[24]   ,&smb.data[25] } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "Out27  ,Out28 ", { &smb.data[26]   ,&smb.data[27] } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "Out29  ,Out30 ", { &smb.data[28]   ,&smb.data[29] } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
         { "Out31  ,Out32 ", { &smb.data[30]   ,&smb.data[31] } ,{1,1},{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}}
  } ;

_x_far /*const*/ struct Ind  ind_net3[] =
  {
         { "In    ,Out    ", { &In_RS485   ,&Out_RS485 }   ,{ 1, 1 }    ,{" , "," "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,5,0,2)}},
  //-----
  #ifndef _LANG_RU_
  //-----
         { "Помилка мереж ", { &ErrorNet             }     ,{ 1  }      ,{" "      },{(w*)&_ind_Nom           }   ,{_form(1,5,0,2)                }}
  //-----
  #else //ifndef _LANG_RU_
  //-----
         { "Ошибки сети   ", { &ErrorNet             }     ,{ 1  }      ,{" "      },{(w*)&_ind_Nom           }   ,{_form(1,5,0,2)                }}
  //-----
  #endif //ifndef _LANG_RU_
  //-----
  };

_x_far struct IndUzm NetIndicat1[]=
{
    {"Profibus DP" ,sizeof(ind_net1)/sizeof(struct Ind) ,&ind_net1[0] }
};
_x_far struct IndUzm NetIndicat2[]=
{
    {"Modbus     " ,sizeof(ind_net2)/sizeof(struct Ind) ,&ind_net2[0] }
};

_x_far struct IndUzm NetIndicat3[]=
{
    {"RS485FD    " ,sizeof(ind_net3)/sizeof(struct Ind) ,&ind_net3[0] }
};

struct IndUzm  *NetIndicat ;
word NetNumInd;

//----------------------------------------
#endif // _NET_IRQ
//----------------------------------------

//----------------------------------------
#else // _NET_INCLUDE
//----------------------------------------

//----------------------------------------
#ifdef _NET_IRQ
//----------------------------------------

extern struct IndUzm  *NetIndicat ;
extern word NetNumInd;
extern struct UstUzm   *NetUstav ;
extern word NetNumUstav ;
extern struct Bits *Netbts ;
extern word NetNumBUst ;
extern _x_far const struct STB       stb_net1[];
extern _x_far const struct STB       stb_net2[];
extern _x_far const struct STB       stb_net3[];
extern _x_far const struct STB       stb_net4[];
extern _x_far struct UstUzm   NetUstav1[];
extern _x_far struct UstUzm   NetUstav2[];
extern _x_far struct UstUzm   NetUstav3[];
extern _x_far struct UstUzm   NetUstav4[];
extern _x_far struct IndUzm NetIndicat1[];
extern _x_far struct IndUzm NetIndicat2[];
extern _x_far struct IndUzm NetIndicat3[];
extern _x_far const struct Ind  ind_net1[];
extern _x_far const struct Ind  ind_net2[];
extern _x_far const struct Ind  ind_net3[];
extern _x_far struct Bits    Netbts1[];
extern _x_far struct Bits    Netbts2[];

//----------------------------------------
#endif // _NET_IRQ
//----------------------------------------

//----------------------------------------
#endif // _NET_INCLUDE
//----------------------------------------


#endif


