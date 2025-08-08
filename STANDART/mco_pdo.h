#ifndef  _MCO_PDO_H
  #define  _MCO_PDO_H

typedef struct
{
	byte num;
	struct
	{
		void* 	addr;
		byte	type;
	}obj[4];
}TPDO_msg;

void PDO_Init( void );
lword PDO_InitMapping( byte count, byte numPDO );
byte PDO_Read( byte numPDO, TMCO_msg *msg );
void PDO_Write( byte numPDO, TMCO_msg *msg );

#ifdef _CANOPEN_INCLUDE

TPDO_msg TPDOmsg[4], RPDOmsg[4];

#else

extern  TPDO_msg TPDOmsg[], RPDOmsg[];

#endif




#endif // _PDO_H

