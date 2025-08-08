#ifndef  _MCO_NMT_H
  #define  _MCO_NMT_H

#define  Num_Producer_HbT		1


#define NMTMSG_OP 1
#define NMTMSG_STOP 2
#define NMTMSG_PREOP 128
#define NMTMSG_RESETAPP 129
#define NMTMSG_RESETCOM 130

#define NMTSTATE_BOOT 0
#define NMTSTATE_STOP 4
#define NMTSTATE_OP 5
#define NMTSTATE_PREOP 127

#ifndef _Union_FR

typedef struct
{
   union
   {
        byte		d[2];
		struct
		{
		   union
		   {
		   	  byte		all;
			  struct
			  {
				 byte   s : 7;
				 byte	t : 1;
			  }_;
		   }cmd;
		   byte		id;
		}_;
   }data;
   byte 	dlen;
}TNMT_Service	;

#else

typedef struct
{
   union
   {
        byte		d[2];
		struct
		{
		   union
		   {
		   	  byte		all;
			  struct
			  {
				 byte	t : 1;
				 byte   s : 7;
			  }_;
		   }cmd;
		   byte		id;
		}_;
   }data;
   byte 	dlen;
}TNMT_Service	;

#endif


void NMT_Init( void );
byte NMT_mc_service( TNMT_Service *msg );
byte NMT_lg_service( TNMT_Service *msg, byte state );
byte NMT_hb_service( byte id,  byte *state );
byte NMT_check_heartbeat( void );
byte NMT_check_lifeguard( void );
void NMT_HB_Producer( byte state );
void NMT_Bootup( void );

#ifdef _CANOPEN_INCLUDE

lword  Timer_NMT_LG;
lword  Timer_NMT_HBp;
TArray Time_NMT_HB;
TArray HeartbeatCfg;

#else

extern lword  Timer_NMT_LG;
extern lword  Timer_NMT_HBp;
extern TArray Time_NMT_HB;
extern TArray HeartbeatCfg;

#endif

#endif  // _NMT_H
