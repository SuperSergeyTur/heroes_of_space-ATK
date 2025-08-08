//#define _Num_CAN_Ports	1
#include "Array.h"
#include <var_tab.h>
/*
TPDO_Parameter	TPDO[4], RPDO[4];
TPDO_Mapping	TPDOmap[4], RPDOmap[4];
TSDO_Parameter	SSDO, CSDO;
TIdentity		Ident;
word size_mvar_tab;
word size_var_tab1;
word size_pvar_tab;

extern byte flag_initmap;
extern TMCO_ust _mr;
extern TArray  HeartbeatCfg;
//extern TNetNameVar var_tab1[];
extern word status, control;

  */
//****************************   Область сетевых переменных 0x1000-0x1FFF   *********************************
//TNetNameVar mco_mvar_tab[] =
TNetNameVar mco_mvar_tab[] =
{
  { "DevTyp", (word*)&mco_ust.DeviceType,     4, _uLONG_type,       0, _READ_access,       0x1000, _VAR    },
  { "RegErr", (word*)&crezerv,                1, _uCHAR_type,       0, _READ_access,       0x1001, _VAR    },
  { "Status", (word*)&crezerv,                4, _uLONG_type,       0, _READ_access,       0x1002, _VAR    },
//{ "DefErr", (word*)&crezerv,                4, _uLONG_type,       0, _READ_access,       0x1003, _ARRAY  },
  { "SyncID", (lword*)&mco_ust.SyncObj.all,   4, _uLONG_type,       0, _READ_access,       0x1005, _VAR    },
  { "T_link", (lword*)&mco_ust.TimeCom,       4, _uLONG_type,       0, _READ_access,       0x1006, _VAR    },
  { "T_PDO",  (word*)&crezerv,                4, _uLONG_type,       0, _READ_access,       0x1007, _VAR    },
  { "Name",   (word*)&crezerv,                8, _STRING_type,      0, _READ_access,       0x1008, _VAR    },
  { "vHard",  (word*)&crezerv,                4, _STRING_type,      0, _READ_access,       0x1009, _VAR    },
  { "vSoft",  (word*)&crezerv,                4, _STRING_type,      0, _READ_access,       0x100a, _VAR    },
  { "T_wd",   (word*)&mco_ust.GuardTime,      2, _uSHORT_type,      0, _READ_WRITE_access, 0x100c, _VAR    },
  { "k_wd",   (byte*)&mco_ust.LifeTimeFactor, 1, _uCHAR_type,       0, _READ_WRITE_access, 0x100d, _VAR    },
//{ "SavPar", (word*)&crezerv,                4, _uLONG_type,       0, _READ_access,       0x1010, _ARRAY  },
//{ "RstPar", (word*)&crezerv,                4, _uLONG_type,       0, _READ_access,       0x1011, _ARRAY  },
  { "TimeID", (word*)&crezerv,                4, _uLONG_type,       0, _READ_WRITE_access, 0x1012, _VAR    },
  { "TimLab", (word*)&crezerv,                4, _uLONG_type,       0, _READ_WRITE_access, 0x1013, _VAR    },
  { "EmcyID", (word*)&crezerv,                4, _uLONG_type,       0, _READ_access,       0x1014, _VAR    },
  { "T_Emcy", (word*)&crezerv,                2, _uSHORT_type,      0, _READ_WRITE_access, 0x1015, _VAR    },
  { "WaitHB", (TArray*)&HeartbeatCfg,         4, _uLONG_type,       0, _READ_WRITE_access, 0x1016, _ARRAY  },
  { "T_HB",   (word*)&mco_ust.TimeProdHB,     2, _uSHORT_type,      0, _READ_WRITE_access, 0x1017, _VAR    },
  { "Object", (TIdentity*)&Ident,             4, _IDENTITY_type,    0, _READ_access,       0x1018, _RECORD },
  { "SSDO",   (TSDO_Parameter*)&SSDO,         4, _SDO_type,         0, _READ_access,       0x1200, _RECORD },
  { "CSDO",   (TSDO_Parameter*)&CSDO,         4, _SDO_type,         0, _READ_access,       0x1280, _RECORD },
  { "RPDO1",  (TPDO_Parameter*)&RPDO[0],      4, _PDO_type,         0, _READ_access,       0x1400, _RECORD },
  { "RPDO21", (TPDO_Parameter*)&RPDO[1],      4, _PDO_type,         0, _READ_access,       0x1414, _RECORD },
  { "RPDO22", (TPDO_Parameter*)&RPDO[2],      4, _PDO_type,         0, _READ_access,       0x1415, _RECORD },
  { "RPDO23", (TPDO_Parameter*)&RPDO[3],      4, _PDO_type,         0, _READ_access,       0x1416, _RECORD },
  { "Rmap1",  (TPDO_Mapping*)&RPDOmap[0],     4, _PDO_mapping_type, 0, _READ_WRITE_access, 0x1600, _RECORD },
  { "Rmap21", (TPDO_Mapping*)&RPDOmap[1],     4, _PDO_mapping_type, 0, _READ_WRITE_access, 0x1614, _RECORD },
  { "Rmap22", (TPDO_Mapping*)&RPDOmap[2],     4, _PDO_mapping_type, 0, _READ_WRITE_access, 0x1615, _RECORD },
  { "Rmap23", (TPDO_Mapping*)&RPDOmap[3],     4, _PDO_mapping_type, 0, _READ_WRITE_access, 0x1616, _RECORD },
  { "TPDO1",  (TPDO_Parameter*)&TPDO[0],      4, _PDO_type,         0, _READ_access,       0x1800, _RECORD },
  { "TPDO21", (TPDO_Parameter*)&TPDO[1],      4, _PDO_type,         0, _READ_access,       0x1814, _RECORD },
  { "TPDO22", (TPDO_Parameter*)&TPDO[2],      4, _PDO_type,         0, _READ_access,       0x1815, _RECORD },
  { "TPDO23", (TPDO_Parameter*)&TPDO[3],      4, _PDO_type,         0, _READ_access,       0x1816, _RECORD },
  { "Tmap1",  (TPDO_Mapping*)&TPDOmap[0],     4, _PDO_mapping_type, 0, _READ_WRITE_access, 0x1a00, _RECORD },
  { "Tmap21", (TPDO_Mapping*)&TPDOmap[1],     4, _PDO_mapping_type, 0, _READ_WRITE_access, 0x1a14, _RECORD },
  { "Tmap22", (TPDO_Mapping*)&TPDOmap[2],     4, _PDO_mapping_type, 0, _READ_WRITE_access, 0x1a15, _RECORD },
  { "Tmap23", (TPDO_Mapping*)&TPDOmap[3],     4, _PDO_mapping_type, 0, _READ_WRITE_access, 0x1a16, _RECORD }
};
//***********************************************************************************************************

//****************************   Область сетевых переменных 0x6000-0x9FFF   *********************************
//****************************           Profile 402 (velocity)             *********************************
//TNetNameVar mco_pvar_tab[] =
TNetNameVar mco_pvar_tab[] =
{
  { "ErrCod", (word*)&crezerv,                2, _uSHORT_type,      0, _READ_access,       0x603f, _VAR    },
  { "Ctrlw",  (word*)&mco_control,            2, _uSHORT_type,      0, _READ_WRITE_access, 0x6040, _VAR    },
  { "Stsw",   (word*)&mco_status,             2, _uSHORT_type,      0, _READ_access,       0x6041, _VAR    },
  { "TarVel", (word*)&canr.N_zad,             2, _SHORT_type,       0, _READ_WRITE_access, 0x6042, _VAR    },
  { "VelDem", (word*)&ZISkor,                 2, _SHORT_type,       0, _READ_access,       0x6043, _VAR    },
  { "VelVal", (word*)&Skor,                   2, _SHORT_type,       0, _READ_access,       0x6044, _VAR    },
  { "VelAm",  (word*)&crezerv,                4, _uLONG_type,       0, _READ_WRITE_access, 0x6046, _ARRAY  },
  { "VelAcc", (word*)&crezerv,                4, _RAMP_type,        0, _READ_WRITE_access, 0x6048, _RECORD },
  { "VelDec", (word*)&crezerv,                4, _RAMP_type,        0, _READ_WRITE_access, 0x6049, _RECORD },
  { "Modes",  (word*)&crezerv,                1, _CHAR_type,        0, _READ_WRITE_access, 0x6060, _VAR    },
  { "ModDsp", (word*)&crezerv,                1, _CHAR_type,        0, _READ_access,       0x6061, _VAR    }
};
//***********************************************************************************************************

void MCO_Dictionary_init( void )
{
   Ident.VendorID = mco_ust.VendorID;
   Ident.ProductCode = mco_ust.ProductCode;
   Ident.num = 4;

   size_mvar_tab = sizeof(mco_mvar_tab)/sizeof(struct namevar);
//   size_var_tab1 = sizeof(var_tab1)/sizeof(TNetNameVar);
   size_var_tab1 = size_vartab1/sizeof(struct namevar);
   size_pvar_tab = sizeof(mco_pvar_tab)/sizeof(struct namevar);

}



/*-----------------15.09.2011 9:52------------------
 * Поиск элемента по индексу
 * Диапазон таблицы указывается в indexlo и indexhi
 * Возвращает номер параметра в таблице
 * --------------------------------------------------*/
short Search_ObjDict( TNetNameVar *var_tab, word size, word index, word indexlo, word indexhi )
{
	word i = 0;

	if ( (index >= indexlo) && (index <= indexhi) )
	{
		while (i < size)
		{
			if ( index == var_tab[i].index )
			{
			   if ( i==0 )
			   {

			   }
			   return i;
			}
			i++;
		}
	}
	return -1;
}

/*-----------------15.09.2011 9:51------------------
 * Запись данных в таблицу объектного словаря
 * Возвращает номер ошибки
 * --------------------------------------------------*/
lword WriteOD( TNetNameVar *var_tab, byte datatype, lword num, byte subindex, byte *data )
{
   TLWord temp;
   TPDO_Parameter*	pPDOtype;
   TPDO_Mapping*	pPDOmaptype;
   TSDO_Parameter*	pSDOtype;
   Tvl_ramp*		pRAMPtype;
   TArray*			pArray;

   switch ( var_tab[num].objcode )
   {
   		case _VAR :
		    if ( subindex == 0 )
		    {
			   	if ( var_tab[num].access == _READ_WRITE_access )
			   	{
			     	switch ( var_tab[num].type )
				    {
						case _CHAR_type :
							*(char*)var_tab[num].addr = (char)data[0];
							break;
//						case _INT_type :
						case _SHORT_type :
							*(short*)var_tab[num].addr = (short)data[0] + ((short)data[1] << 8);
							break;
						case _LONG_type :
							*(long*)var_tab[num].addr = (long)data[0]        + ((long)data[1] << 8 ) +
													   ((long)data[2] << 16) + ((long)data[3] << 24);
							break;
						case _uCHAR_type :
							*(byte*)var_tab[num].addr = (byte)data[0];
							break;
						case _uSHORT_type :
							*(word*)var_tab[num].addr = (word)data[0] + ((word)data[1] << 8);
							break;
						case _uLONG_type :
							*(lword*)var_tab[num].addr = (lword)data[0]        + ((lword)data[1] << 8 ) +
														((lword)data[2] << 16) + ((lword)data[3] << 24);
							break;
						case _STRING_type :

							break;
						case _DOUBLE_type :

							break;
					}
				}
				else
			   		if ( datatype == _SDO_type )
						return _ERR_SDO_read_only;
					else
						return _EMCY_Monitor_protocol;
		  	}
			else
 		       return _ERR_SDO_subindex;
			break;
		case _ARRAY :
		    if ( subindex != 0 )
		    {
			   	if ( var_tab[num].access == _READ_WRITE_access )
			   	{
					pArray = (TArray*)var_tab[num].addr;
			     	switch ( var_tab[num].type )
				    {
						case _CHAR_type :
							if ( subindex <= pArray->count )
							{
								temp.b.b1 = data[0];
								ArrayWriteValue( (TArray*)var_tab[num].addr, subindex, temp.lw );
							}
							break;
//						case _INT_type :
						case _SHORT_type :
							if ( subindex <= pArray->count )
							{
								temp.b.b1 = data[0];
								temp.b.b2 = data[1];
								ArrayWriteValue( (TArray*)var_tab[num].addr, subindex, temp.lw );
							}
							break;
						case _LONG_type :
							if ( subindex <= pArray->count )
							{
								temp.b.b1 = data[0];
								temp.b.b2 = data[1];
								temp.b.b3 = data[2];
								temp.b.b4 = data[3];
								ArrayWriteValue( (TArray*)var_tab[num].addr, subindex, temp.lw );
							}
							break;
						case _uCHAR_type :
							if ( subindex <= pArray->count )
							{
								temp.b.b1 = data[0];
								ArrayWriteValue( (TArray*)var_tab[num].addr, subindex, temp.lw );
							}
							break;
						case _uSHORT_type :
							if ( subindex <= pArray->count )
							{
								temp.b.b1 = data[0];
								temp.b.b2 = data[1];
								ArrayWriteValue( (TArray*)var_tab[num].addr, subindex, temp.lw );
							}
							break;
						case _uLONG_type :
							if ( subindex <= pArray->count )
							{
								temp.b.b1 = data[0];
								temp.b.b2 = data[1];
								temp.b.b3 = data[2];
								temp.b.b4 = data[3];
								ArrayWriteValue( (TArray*)var_tab[num].addr, subindex, temp.lw );
							}
							break;
					}
				}
				else
			   		if ( datatype == _SDO_type )
						return _ERR_SDO_read_only;
					else
						return _EMCY_Monitor_protocol;
			}
			else
 		       return _ERR_SDO_subindex;
			break;
		case _RECORD :
			   switch ( var_tab[num].type )
			   {
				  case _PDO_type :
					if ( subindex != 0 )
					{
		   			pPDOtype = (TPDO_Parameter*)var_tab[num].addr;
					if ( subindex <= pPDOtype->num )
					{
						switch ( subindex )
						{
							case 1 :
			        			pPDOtype->COBID = (lword)data[0]         + ((lword)data[1] << 8)
											  	+ ((lword)data[2] << 16) + ((lword)data[3] << 24);
									  if  (num==20)  flag_set_rpdo = 1;
									  if  (num==21)  flag_set_rpdo = 2;
									  if  (num==22)  flag_set_rpdo = 3;
									  if  (num==23)  flag_set_rpdo = 4;
								break;
							case 2 :
			        			pPDOtype->type = (byte)data[0];
								break;
							case 3 :
			        			pPDOtype->inhibit_time = (word)data[0] + ((word)data[1] << 8);
								break;
							case 5 :
			        			pPDOtype->event_timer = (byte)data[0];
								break;
							default:
 		       					return _ERR_SDO_subindex;
								break;
						}
					}
					else
					   return _ERR_SDO_parameter_limit;
					}
					else
 		       			return _ERR_SDO_subindex;
					break;
				  case _PDO_mapping_type :
			   		pPDOmaptype = (TPDO_Mapping*)var_tab[num].addr;
					if ( subindex == 0 )
					{
						pPDOmaptype->num = (byte)data[0];
		   				switch (num)
						{
							case 24: flag_initmap |= 1;break;
							case 25: flag_initmap |= 1<<1;break;
							case 26: flag_initmap |= 1<<2;break;
							case 27: flag_initmap |= 1<<3;break;
							case 32: flag_initmap |= 1<<4;break;
							case 33: flag_initmap |= 1<<5;break;
							case 34: flag_initmap |= 1<<6;break;
							case 35: flag_initmap |= 1<<7;break;
						}
					}
					else
					{
						pPDOmaptype->object[subindex-1].element = (lword)data[0]        + ((lword)data[1] << 8)
												       		   + ((lword)data[2] << 16) + ((lword)data[3] << 24);
					}
					break;
				  case _SDO_type :
			   		pSDOtype = (TSDO_Parameter*)var_tab[num].addr;
					if ( subindex <= pSDOtype->num )
					{
						switch ( subindex )
						{
							case 1 :
			        			pSDOtype->COBID_cs = (lword)data[0]        + ((lword)data[1] << 8)
								 		          + ((lword)data[2] << 16) + ((lword)data[3] << 24);
								break;
							case 2 :
			        			pSDOtype->COBID_sc = (lword)data[0]        + ((lword)data[1] << 8)
												  + ((lword)data[2] << 16) + ((lword)data[3] << 24);
								break;
							case 3 :
			        			pSDOtype->NodeID = (byte)data[0];
								break;
							default:
 		       					return _ERR_SDO_subindex;
								break;
						}
					}
					else
					   return _ERR_SDO_parameter_limit;
					break;
				  case _IDENTITY_type :
					return _ERR_SDO_read_only;
					break;
				  case _RAMP_type :
					if ( subindex != 0 )
					{
					pRAMPtype = (Tvl_ramp*)var_tab[num].addr;
					if ( subindex <= pRAMPtype->num )
					{
					   if ( subindex == 1 )
					   {
	        			  pRAMPtype->d_speed = (lword)data[0]        + ((lword)data[1] << 8)
						  		            + ((lword)data[2] << 16) + ((lword)data[3] << 24);
					   }
					   else
					   {
			        	  pRAMPtype->d_time = (short)data[0] + ((short)data[1] << 8);
					   }
					}
					else
					   return _ERR_SDO_parameter_limit;
					}
					else
 		       			return _ERR_SDO_subindex;
					break;
			   }
		    break;
   }
   return 0;
}

/*-----------------15.09.2011 9:51------------------
 * Чтения данных из таблицы объектного словаря
 * Возвращает номер ошибки
 * --------------------------------------------------*/
lword ReadOD( TNetNameVar *var_tab, lword *num, byte subindex, byte *data )
{
   TLWord  temp;
   TPDO_Parameter*	pPDOtype;
   TPDO_Mapping*	pPDOmaptype;
   TSDO_Parameter*	pSDOtype;
   TIdentity*		pIdent;
   Tvl_ramp*		pRAMPtype;

   switch ( var_tab[*num].objcode )
   {
   		case _VAR :
		    if ( subindex == 0 )
		    {

			     	switch ( var_tab[*num].type )
				    {
						case _CHAR_type :
							data[0] = *(char*)var_tab[*num].addr;
							*num = 1;
							break;
//						case _INT_type :
						case _SHORT_type :
							temp.w.w1 = *(short*)var_tab[*num].addr;
							data[0] = temp.b.b1;
							data[1] = temp.b.b2;
							*num = 2;
							break;
						case _LONG_type :
							temp.lw = *(long*)var_tab[*num].addr;
							data[0] = temp.b.b1;
							data[1] = temp.b.b2;
							data[2] = temp.b.b3;
							data[3] = temp.b.b4;
							*num = 4;
							break;
						case _uCHAR_type :
							data[0] = *(byte*)var_tab[*num].addr;
							*num = 1;
							break;
						case _uSHORT_type :
							temp.w.w1 = *(word*)var_tab[*num].addr;
							data[0] = temp.b.b1;
							data[1] = temp.b.b2;
							*num = 2;
							break;
						case _uLONG_type :
							temp.lw = *(lword*)var_tab[*num].addr;
							data[0] = temp.b.b1;
							data[1] = temp.b.b2;
							data[2] = temp.b.b3;
							data[3] = temp.b.b4;
							*num = 4;
							break;
						case _STRING_type :

							break;
						case _DOUBLE_type :

							break;
					}

		  	}
			else
 		       return _ERR_SDO_subindex;
			break;
		case _ARRAY :
		    if ( subindex != 0 )
		    {
			     	switch ( var_tab[*num].type )
				    {
						case _CHAR_type :
							if ( subindex <= sizeof(*(byte*)var_tab[*num].addr) )
							{
								ArrayReadValue( (TArray*)var_tab[*num].addr, subindex, &temp.lw );
								data[0] = temp.b.b1;
							}
							*num = 1;
							break;
//						case _INT_type :
						case _SHORT_type :
							if ( subindex <= (sizeof(*(byte*)var_tab[*num].addr))/2 )
							{
								ArrayReadValue( (TArray*)var_tab[*num].addr, subindex, &temp.lw );
								data[0] = temp.b.b1;
								data[1] = temp.b.b2;
							}
							*num = 2;
							break;
						case _LONG_type :
							if ( subindex <= (sizeof(*(byte*)var_tab[*num].addr))/4 )
							{
								ArrayReadValue( (TArray*)var_tab[*num].addr, subindex, &temp.lw );
								data[0] = temp.b.b1;
								data[1] = temp.b.b2;
								data[2] = temp.b.b3;
								data[3] = temp.b.b4;
							}
							*num = 4;
							break;
						case _uCHAR_type :
							if ( subindex <= sizeof(*(byte*)var_tab[*num].addr) )
							{
								ArrayReadValue( (TArray*)var_tab[*num].addr, subindex, &temp.lw );
								data[0] = temp.b.b1;
							}
							*num = 1;
							break;
						case _uSHORT_type :
							if ( subindex <= (sizeof(*(byte*)var_tab[*num].addr))/2 )
							{
								ArrayReadValue( (TArray*)var_tab[*num].addr, subindex, &temp.lw );
								data[0] = temp.b.b1;
								data[1] = temp.b.b2;
							}
							*num = 2;
							break;
						case _uLONG_type :
							if ( subindex <= (sizeof(*(byte*)var_tab[*num].addr))/4 )
							{
								ArrayReadValue( (TArray*)var_tab[*num].addr, subindex, &temp.lw );
								data[0] = temp.b.b1;
								data[1] = temp.b.b2;
								data[2] = temp.b.b3;
								data[3] = temp.b.b4;
							}
							*num = 4;
							break;
					}
			}
			else
 		       return _ERR_SDO_subindex;
			break;
		case _RECORD :
			   switch ( var_tab[*num].type )
			   {
				  case _PDO_type :
					pPDOtype = (TPDO_Parameter*)var_tab[*num].addr;
					if ( subindex <= pPDOtype->num )
					{
						switch ( subindex )
						{
							case 0 :
			        			data[0] = pPDOtype->num;
							    *num = 1;
								break;
							case 1 :
								temp.lw = pPDOtype->COBID;
								data[0] = temp.b.b1;
								data[1] = temp.b.b2;
								data[2] = temp.b.b3;
								data[3] = temp.b.b4;
							    *num = 4;
								break;
							case 2 :
			        			data[0] = pPDOtype->type;
							    *num = 1;
								break;
							case 3 :
								temp.w.w1 = pPDOtype->inhibit_time;
								data[0] = temp.b.b1;
								data[1] = temp.b.b2;
							    *num = 2;
								break;
							case 5 :
			        			data[0] = pPDOtype->event_timer;
							    *num = 1;
								break;
							default:
 		       					return _ERR_SDO_subindex;
								break;
						}
					}
					else
					   return _ERR_SDO_parameter_limit;
					break;
				  case _PDO_mapping_type :
					pPDOmaptype = (TPDO_Mapping*)var_tab[*num].addr;
					if ( subindex <= pPDOmaptype->num )
					{
						if ( subindex == 0 )
						{
						 	data[0] = pPDOmaptype->num;
							*num = 1;
						}
						else
						{
						 	temp.lw = pPDOmaptype->object[subindex-1].element;
						 	data[0] = temp.b.b1;
						 	data[1] = temp.b.b2;
						 	data[2] = temp.b.b3;
						 	data[3] = temp.b.b4;
							*num = 4;
						}
					}
					else
					   return _ERR_SDO_parameter_limit;
					break;
				  case _SDO_type :
					pSDOtype = (TSDO_Parameter*)var_tab[*num].addr;
					if ( subindex <= pSDOtype->num )
					{
						switch ( subindex )
						{
							case 0 :
						 	    data[0] = pSDOtype->num;
							    *num = 1;
								break;
							case 1 :
						 		temp.lw = pSDOtype->COBID_cs;
						 		data[0] = temp.b.b1;
						 		data[1] = temp.b.b2;
						 		data[2] = temp.b.b3;
						 		data[3] = temp.b.b4;
							    *num = 4;
								break;
							case 2 :
						 		temp.lw = pSDOtype->COBID_sc;
						 		data[0] = temp.b.b1;
						 		data[1] = temp.b.b2;
						 		data[2] = temp.b.b3;
						 		data[3] = temp.b.b4;
							    *num = 4;
								break;
							case 3 :
						 	    data[0] = pSDOtype->NodeID;
							    *num = 1;
								break;
							default:
 		       					return _ERR_SDO_subindex;
								break;
						}
					}
					else
					   return _ERR_SDO_parameter_limit;
					break;
				  case _IDENTITY_type :
					pIdent = (TIdentity*)var_tab[*num].addr;
					if ( subindex <= pIdent->num )
					{
 					   switch ( subindex )
					   {
					     	case 0 :
						       data[0] = pIdent->num;
						       *num = 1;
						   	   break;
							case 1 :
						 		temp.lw = pIdent->VendorID;
						 		data[0] = temp.b.b1;
						 		data[1] = temp.b.b2;
						 		data[2] = temp.b.b3;
						 		data[3] = temp.b.b4;
							    *num = 4;
								break;
							case 2 :
						 		temp.lw = pIdent->ProductCode;
						 		data[0] = temp.b.b1;
						 		data[1] = temp.b.b2;
						 		data[2] = temp.b.b3;
						 		data[3] = temp.b.b4;
							    *num = 4;
								break;
							case 3 :
						 		temp.lw = pIdent->RevisionNumber;
						 		data[0] = temp.b.b1;
						 		data[1] = temp.b.b2;
						 		data[2] = temp.b.b3;
						 		data[3] = temp.b.b4;
							    *num = 4;
								break;
							case 4 :
						 		temp.lw = pIdent->SerialNumber;
						 		data[0] = temp.b.b1;
						 		data[1] = temp.b.b2;
						 		data[2] = temp.b.b3;
						 		data[3] = temp.b.b4;
							    *num = 4;
								break;
							default:

 		       					return _ERR_SDO_subindex;
								break;
					   }
					}
					else
						   return _ERR_SDO_parameter_limit;
					break;
				  case _RAMP_type :
					pRAMPtype = (Tvl_ramp*)var_tab[*num].addr;
					if ( subindex <= pRAMPtype->num )
					{
						if ( subindex == 0 )
						{
						   data[0] = 2;
						   *num = 1;
						}
						else
						{
					   		if ( subindex == 1 )
					   		{
						 		temp.lw = pRAMPtype->d_speed;
						 		data[0] = temp.b.b1;
						 		data[1] = temp.b.b2;
						 		data[2] = temp.b.b3;
						 		data[3] = temp.b.b4;
							    *num = 4;
					   		}
					   		else
					   		{
								temp.w.w1 = pRAMPtype->d_time;
								data[0] = temp.b.b1;
								data[1] = temp.b.b2;
							    *num = 2;
					   		}
						}
					}
					else
					   return _ERR_SDO_parameter_limit;
					break;
			   }
		    break;
   }
   return 0;
}


/*-----------------15.09.2011 9:49------------------
 * Функция записи данных в Объектный словарь
 * Возвращает номер ошибки
 * --------------------------------------------------*/
lword Write_ObjDict( word index, byte subindex, byte datatype, byte *data, lword *num )
{
  int n;
//  word size;

    if ( datatype != _PDO_type )
    {
	  n = Search_ObjDict( &mco_mvar_tab[0], size_mvar_tab, index, _BEGIN_MVAR_TAB, _END_MVAR_TAB );
	  if ( n != -1 )
	  {
	   	*num = (lword)n;
		return WriteOD( &mco_mvar_tab[0], datatype, *num, subindex, data);
	  }
    }
	n = Search_ObjDict( &var_tab1[0], size_var_tab1, index, _BEGIN_VAR1_TAB, _END_VAR1_TAB );
	if ( n != -1 )
	{
		*num = (lword)n;
		return WriteOD( &var_tab1[0], datatype, *num, subindex, data);
	}
	n = Search_ObjDict( &mco_pvar_tab[0], size_pvar_tab, index, _BEGIN_PVAR_TAB, _END_PVAR_TAB );
	if ( n != -1 )
	{
		*num = (lword)n;
		return WriteOD( &mco_pvar_tab[0], datatype, *num, subindex, data);
	}

  return _ERR_SDO_object;
}

/*-----------------15.09.2011 9:49------------------
 * Функция чтения данных из Объектный словарь
 * Возвращает номер ошибки
 * --------------------------------------------------*/
lword Read_ObjDict( word index, byte subindex, byte datatype, byte *data, lword *num )
{
  int n;
//  word size;

    if ( datatype != _PDO_type )
    {
	  n = Search_ObjDict( &mco_mvar_tab[0], size_mvar_tab, index, _BEGIN_MVAR_TAB, _END_MVAR_TAB );
	  if ( n != -1 )
	  {
		*num = (lword)n;
		return ReadOD( &mco_mvar_tab[0], num, subindex, data);
	  }
	  return 0;
    }
	n = Search_ObjDict( &var_tab1[0], size_var_tab1, index, _BEGIN_VAR1_TAB, _END_VAR1_TAB );
	if ( n != -1 )
	{
		*num = (lword)n;
		return ReadOD( &var_tab1[0], num, subindex, data);
	}
	n = Search_ObjDict( &mco_pvar_tab[0], size_pvar_tab, index, _BEGIN_PVAR_TAB, _END_PVAR_TAB );
	if ( n != -1 )
	{
		*num = (lword)n;
		return ReadOD( &mco_pvar_tab[0], num, subindex, data);
	}

  return _ERR_SDO_object;
}

