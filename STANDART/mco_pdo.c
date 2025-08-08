#include "mco_pdo.h"
#include "mco_dict.h"

void PDO_Init( void )
{
  byte i;

  for ( i = 0; i < 4; i++ )
  {
	 TPDO[i].num = 5;
	 RPDO[i].num = 5;
  }
  TPDO[0].COBID = (_COBID_PDO1TX << 7) + _r.can[0].addr + 0x80000000;
  RPDO[0].COBID = (_COBID_PDO1RX << 7) + _r.can[0].addr + 0x80000000;
  TPDO[1].COBID = (_COBID_PDO2TX << 7) + _r.can[0].addr + 0x80000000;
  RPDO[1].COBID = (_COBID_PDO2RX << 7) + _r.can[0].addr + 0x80000000;
  TPDO[2].COBID = (_COBID_PDO3TX << 7) + _r.can[0].addr + 0x80000000;
  RPDO[2].COBID = (_COBID_PDO3RX << 7) + _r.can[0].addr + 0x80000000;
  TPDO[3].COBID = (_COBID_PDO4TX << 7) + _r.can[0].addr + 0x80000000;
  RPDO[3].COBID = (_COBID_PDO4RX << 7) + _r.can[0].addr + 0x80000000;
}

lword PDO_define( TNetNameVar *var_tab, word num, TPDOmap_element *obj, byte i, TPDO_msg *msg )
{
   Tvl_ramp* 			pRamp;

   (*msg).obj[i].type = var_tab[num].type;
   switch ( var_tab[num].objcode )
   {
   	  case _VAR :
		 switch ( var_tab[num].type )
		 {
		 	case _CHAR_type :
		 	case _uCHAR_type :
	 	  		(*msg).obj[i].addr = (byte*)var_tab[num].addr;
				break;
		 	case _SHORT_type :
		 	case _uSHORT_type :
	 	  		(*msg).obj[i].addr = (word*)var_tab[num].addr;
				break;
		 	case _LONG_type :
		 	case _uLONG_type :
	 	  		(*msg).obj[i].addr = (lword*)var_tab[num].addr;
				break;
		 }
		 break;
	  case _ARRAY :
		 switch ( var_tab[num].type )
		 {
		 	case _CHAR_type :
		 	case _uCHAR_type :
//	 	  		msg.obj.addr = ((byte*)var_tab[num].addr[]);
				break;
		 	case _SHORT_type :
		 	case _uSHORT_type :
//	 	  		msg.obj.addr = (word*)var_tab[num].addr;
				break;
		 	case _LONG_type :
		 	case _uLONG_type :
//	 	  		msg.obj.addr = (lword*)var_tab[num].addr;
				break;
		 }
	  	 break;
	  case _RECORD :
	  		switch ( var_tab[num].type )
	  		{
	  			case _RAMP_type :
	  				pRamp = (Tvl_ramp*)var_tab[num].addr;
	  				if ( (*obj)._.subindex == 1 )
	  					(*msg).obj[i].addr = &(pRamp->d_speed) ;
	  				else
						(*msg).obj[i].addr = &(pRamp->d_time) ;
	  				break;
	  			default:
	  				break;
     		}
			break;
   }
   return 1;
}



lword PDO_InitMapping( byte typePDO, byte numPDO )
{
	int num;
	byte i;
	TPDOmap_element  	pdo;
	TPDO_Mapping*	 	pMap;
	TPDO_msg*			pMsg;

	if ( typePDO == 0 )
	{
	   pMap = &TPDOmap[numPDO];
	   pMsg = &TPDOmsg[numPDO];
	}
	else
	{
	   pMap = &RPDOmap[numPDO];
	   pMsg = &RPDOmsg[numPDO];
	}
	pMsg->num = pMap->num;
	for ( i = 0; i < pMap->num; i++ )
	{
	    pdo.element = pMap->object[i].element;
	    num = Search_ObjDict( &var_tab1[0], size_var_tab1, pdo._.index, _BEGIN_VAR1_TAB, _END_VAR1_TAB );
	    if ( num != -1 )
	    {
		   PDO_define( &var_tab1[0], num, &pdo, i, pMsg );
		}
		else
		{
		   num = Search_ObjDict( &mco_pvar_tab[0], size_pvar_tab, pdo._.index, _BEGIN_PVAR_TAB, _END_PVAR_TAB );
	       if ( num != -1 )
	       {
		      PDO_define( &mco_pvar_tab[0], num, &pdo, i, pMsg );
		   }
                }
    }
    return  0;
}


void PDO_Write( byte numPDO, TMCO_msg *msg )
{
   byte i;

   for ( i = 0; i < RPDOmsg[numPDO].num; i++ )
   {
	   switch ( RPDOmsg[numPDO].obj[i].type )
	   {
			case _CHAR_type :
				*(char*)RPDOmsg[numPDO].obj[i].addr = (char)msg->data[i];
				break;
//			case _INT_type :
			case _SHORT_type :
				*(short*)RPDOmsg[numPDO].obj[i].addr = (short)msg->data[2*i] + ((short)msg->data[2*i+1] << 8);
				break;
			case _LONG_type :
				*(long*)RPDOmsg[numPDO].obj[i].addr = (long)msg->data[4*i]     + ((long)msg->data[4*i+1] << 8 ) +
								   			    ((long)msg->data[4*i+2] << 16) + ((long)msg->data[4*i+3] << 24);
				break;
			case _uCHAR_type :
				*(byte*)RPDOmsg[numPDO].obj[i].addr = (byte)msg->data[i];
				break;
			case _uSHORT_type :
				*(word*)RPDOmsg[numPDO].obj[i].addr = (word)msg->data[2*i] + ((word)msg->data[2*i+1] << 8);
				break;
			case _uLONG_type :
				*(lword*)RPDOmsg[numPDO].obj[i].addr = (lword)msg->data[4*i] + ((lword)msg->data[4*i+1] << 8 ) +
												 ((lword)msg->data[4*i+2] << 16) + ((lword)msg->data[4*i+3] << 24);
				break;
	   }
   }
   return ;
}

byte PDO_Read( byte numPDO, TMCO_msg *msg )
{
  byte i;
  byte size = 0;
  TLWord temp;

   for ( i = 0; i < TPDOmsg[numPDO].num; i++ )
   {
	   switch ( TPDOmsg[numPDO].obj[i].type )
	   {
	   	  case _CHAR_type :
			msg->data[size++] = *(char*)TPDOmsg[numPDO].obj[i].addr;
			break;
//		  case _INT_type :
		  case _SHORT_type :
			temp.w.w1 = *(short*)TPDOmsg[numPDO].obj[i].addr;
			msg->data[size++] = temp.b.b1;
			msg->data[size++] = temp.b.b2;
			break;
		 case _LONG_type :
			temp.lw = *(long*)TPDOmsg[numPDO].obj[i].addr;
			msg->data[size++] = temp.b.b1;
			msg->data[size++] = temp.b.b2;
			msg->data[size++] = temp.b.b1;
			msg->data[size++] = temp.b.b2;
			break;
		 case _uCHAR_type :
			msg->data[size++] = *(byte*)TPDOmsg[numPDO].obj[i].addr;
			break;
		 case _uSHORT_type :
			temp.w.w1 = *(word*)TPDOmsg[numPDO].obj[i].addr;
			msg->data[size++] = temp.b.b1;
			msg->data[size++] = temp.b.b2;
			break;
		 case _uLONG_type :
			temp.lw = *(lword*)TPDOmsg[numPDO].obj[i].addr;
			msg->data[size++] = temp.b.b1;
			msg->data[size++] = temp.b.b2;
			msg->data[size++] = temp.b.b1;
			msg->data[size++] = temp.b.b2;
			break;
	   }
   }
   return size;
}

