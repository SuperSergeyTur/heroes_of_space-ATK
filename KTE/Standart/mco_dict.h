#ifndef  _MCO_DICT_H
  #define  _MCO_DICT_H

typedef struct  // тип данных 20h
{
	byte	num;
	lword	COBID;
	byte 	type;
	word	inhibit_time;
	byte	res;
	word	event_timer;
}TPDO_Parameter;

#ifdef _Union_FR
typedef union
{
	lword		element;
	struct
	{
		word	index;
		byte	subindex;
		byte	length;
	}_;
}TPDOmap_element;
#else
typedef union
{
	lword		element;
	struct
	{
		byte	length;
		byte	subindex;
		word	index;
	}_;
}TPDOmap_element;
#endif


typedef struct  // тип данных 21h
{
	byte				num;
	TPDOmap_element		object[4];
}TPDO_Mapping;

typedef struct  // тип данных 22h
{
	byte	num;
	lword	COBID_cs;
	lword	COBID_sc;
	byte	NodeID;
}TSDO_Parameter;

typedef struct  // тип данных 23h
{
	byte	num;
	lword	VendorID;
	lword	ProductCode;
	lword	RevisionNumber;
	lword	SerialNumber;
}TIdentity;

typedef struct  // тип данных 82h
{
	byte	num;
	lword	d_speed;
	short	d_time;
}Tvl_ramp;


//----- Классы в CANopen -----
#define  _NULL		0
#define  _DOMAIN	2
#define  _DEFTYPE	5
#define  _DEFSTUCT	6
#define  _VAR		7
#define  _ARRAY		8
#define  _RECORD	9

#define _READ_access		1
#define _READ_WRITE_access  2

#define _BEGIN_MVAR_TAB			(word)0x1000
#define _END_MVAR_TAB			(word)0x1FFF
#define _BEGIN_VAR1_TAB			(word)0x2000
#define _END_VAR1_TAB			(word)0x2FFF
#define _BEGIN_PVAR_TAB			(word)0x6000
#define _END_PVAR_TAB			(word)0x6FFF


#ifndef _Union_FR
typedef union
{
   lword	all;
   struct
   {
      union
      {
	      lword		b29		: 29;
	      struct
	      {
		     lword	b11		: 11;
		     lword	res 	: 18;
	      }_;
      }id;
      lword    	bit29	: 1;
      lword    	bit30	: 1;
      lword    	bit31	: 1;
   }_;
}TCOBID;

typedef union
{
   lword	all;
   struct
   {
     word		heartbeat;
     byte		node_id;
     byte		reserve;
   }_;
}TConsHbT;

#else

typedef union
{
   lword	all;
   struct
   {
      lword    	bit31	: 1;
      lword    	bit30	: 1;
      lword    	bit29	: 1;
      union
      {
	      lword		b29		: 29;
	      struct
	      {
		     lword	res 	: 18;
		     lword	b11		: 11;
	      }_;
      }id;
   }_;
}TCOBID;

typedef union
{
   lword	all;
   struct
   {
     word		heartbeat;
     byte		node_id;
     byte		reserve;
   }_;
}TConsHbT;

#endif


/*
typedef struct
{
  char *name;
  void *addr;
  unsigned int lon;
  char type;
  word  nom ;

  char  access ;
  word index;
  byte objcode;
  char dscr;
  word tag ;

}TNetNameVar;
*/
typedef const struct namevar TNetNameVar;
#define Timer1	Timer1_Ovr
#define TTimer	lword



#define  _rTypeDevice			0x1000
#define  _rRegError				0x1001
#define  _rManufStatus			0x1002
#define  _rPreDefError			0x1003
#define  _rCOBID_Sync			0x1005
#define  _rCommCycle			0x1006
#define  _rSynchWindow			0x1007
#define  _rManufDeviceName		0x1008
#define  _rManufHardware		0x1009
#define  _rManufSoftware		0x100A
#define  _rGuardTime			0x100C
#define  _rLifeTimeFactor		0x100D
#define  _rStoreParam			0x1010
#define  _rRestoreDefault		0x1011
#define  _rCOBID_TS				0x1012
#define  _rHighRes_TS			0x1013
#define  _rCOBID_Emerg			0x1014
#define  _rInhibitTimeEmerg	    0x1015
#define  _rConsumer_HbT			0x1016
#define  _rProducer_HbT			0x1017
#define  _rIdentObj				0x1018

#define  _rRPDO1				0x1400
#define  _rRPDO2				0x1414
#define  _rRPDO3				0x1415
#define  _rRPDO4				0x1416
#define  _rRPDOmap1				0x1600
#define  _rRPDOmap2 			0x1614
#define  _rRPDOmap3				0x1615
#define  _rRPDOmap4	   			0x1616
#define  _rTPDO1				0x1800
#define  _rTPDO2				0x1814
#define  _rTPDO3				0x1815
#define  _rTPDO4				0x1816
#define  _rTPDOmap1				0x1A00
#define  _rTPDOmap2 			0x1A14
#define  _rTPDOmap3				0x1A15
#define  _rTPDOmap4				0x1A16




//#define _OD_DEVICE_TYPE   	 	0x00020192 // 0x0002 - Servo Drive, 0x0192 = 402 - Drive & Motion Control Profile
//#define _OD_VENDOR_ID     		0x0000115C
//#define _OD_PRODUCT_CODE  		0x00000001
#define _OD_DEVICE_TYPE   	 	0x92010200 // 0x0002 - Servo Drive, 0x0192 = 402 - Drive & Motion Control Profile
#define _OD_VENDOR_ID     		0x5C110000
#define _OD_PRODUCT_CODE  		0x01000000
#define _OD_REVISION      		0x20000100
#define Node_ID_default			1

union mco_config
{
    byte all;
	struct
	{
	   byte		_20k	: 1 ;
	   byte		_62_5k	: 1 ;
	   byte		_125k	: 1 ;
	   byte		_250k	: 1 ;

	   byte		_500k	: 1 ;
	   byte		_800k	: 1 ;
	   byte		_1000k	: 1 ;
	   byte		vkl		: 1 ;
	}_;
};


#define  _mco_cfg_vkl		0x01
#define  _mco_cfg_1000k		0x02
#define  _mco_cfg_800k		0x04
#define  _mco_cfg_500k		0x08

#define  _mco_cfg_250k		0x10
#define  _mco_cfg_125k		0x20
#define  _mco_cfg_62_5k		0x40
#define  _mco_cfg_20k		0x80


typedef struct
{
	union  mco_config   config;
	word				baudrate;
	byte				NodeID;
	lword 				DeviceType;
	lword				VendorID;
	lword				ProductCode;
	TCOBID				SyncObj;                        // ID SYNC-объекта
	lword				TimeCom;   						// в мксек
	word  				GuardTime;
	byte 				LifeTimeFactor;
	lword  				TimeConsHB;
	word 				TimeProdHB;
	TCOBID				EmcyID;
	lword				InhibitTime;
}TMCO_ust;

short Search_ObjDict( TNetNameVar *var_tab, word size, word index, word indexlo, word indexhi );
lword Write_ObjDict( word index, byte subindex, byte datatype, byte *data, lword *num );
lword Read_ObjDict( word index, byte subindex, byte datatype, byte *data, lword *num );
void MCO_Dictionary_init( void );

#ifdef _CANOPEN_INCLUDE

TPDO_Parameter	TPDO[4], RPDO[4];
TPDO_Mapping	TPDOmap[4], RPDOmap[4];
TSDO_Parameter	SSDO, CSDO;
TIdentity		Ident;
word size_mvar_tab;
word size_var_tab1;
word size_pvar_tab;
word mco_control, mco_status;


#else

extern TPDO_Parameter	TPDO[], RPDO[];
extern TPDO_Mapping		TPDOmap[], RPDOmap[];
extern TSDO_Parameter	SSDO, CSDO;
extern TIdentity		Ident;
extern word size_mvar_tab;
extern word size_var_tab1;
extern word size_pvar_tab;
extern word mco_control, mco_status;

#endif



#endif  //  _MCO_DICT_H
