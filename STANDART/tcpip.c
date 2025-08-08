/*-----------------30.08.2010 15:26-----------------
 *   Инициализация платы Modbus TCP/IP
 * --------------------------------------------------*/
#ifndef _CM3_

void Init_TCPIP( void )
{
   word i ;

   rmb.func  = 0 ;
   smb.func = 0 ;
   for ( i=0 ; i<MB_BUFFER; i++ )
   {
      rmb.data[i] = 0 ;
      smb.data[i] = 0 ;
   }

   flag_newdata = 0;

   WRITE_NET( DR_CR, DR_CR_SLAVE );
   WRITE_NET( DR_ETHADDR0, _r.EMAC1_addr );
   WRITE_NET( DR_ETHADDR1, _r.EMAC2_addr );
   WRITE_NET( DR_ETHADDR2, _r.EMAC3_addr );
   WRITE_NET( DR_ETHADDR3, _r.EMAC4_addr );
   WRITE_NET( DR_ETHADDR4, _r.EMAC5_addr );
   WRITE_NET( DR_ETHADDR5, _r.EMAC6_addr );
   WRITE_NET( DR_IPADDR0, _r.IP1_addr );
   WRITE_NET( DR_IPADDR1, _r.IP2_addr );
   WRITE_NET( DR_IPADDR2, _r.IP3_addr );
   WRITE_NET( DR_IPADDR3, _r.IP4_addr );
   WRITE_NET( DR_NETMASK0, _r.IPM1_addr );
   WRITE_NET( DR_NETMASK1, _r.IPM2_addr );
   WRITE_NET( DR_NETMASK2, _r.IPM3_addr );
   WRITE_NET( DR_NETMASK3, _r.IPM4_addr );
   WRITE_NET( DR_DRIPADDR0, _r.DIP1_addr );
   WRITE_NET( DR_DRIPADDR1, _r.DIP2_addr );
   WRITE_NET( DR_DRIPADDR2, _r.DIP3_addr );
   WRITE_NET( DR_DRIPADDR3, _r.DIP4_addr );



   WRITE_NET( DR_TLIFE, _r.Net_LT ); // 10 ms
//   инициализация прерывания
  ENIR_EN1 = 0;
  ELVR_LAB1 = Falling;
  EIRR_ER1 = 0;                         // 1111 1101
  ENIR_EN1 = 1;
  ICR01 = 24;

   WRITE_NET( DR_TLIFE, _r.Net_LT ); // 10 ms
   inet = (w)(DR_ISR_SF /*| DR_ISR_LT*/ | DR_ISR_ND) ;
   WRITE_NET( DR_IER,  inet );


//  WRITE_NET( DR_CR, DR_CR_START ) ;
  inet = (w)(DR_CR_START | DR_CR_LOAD) ;
  WRITE_NET( DR_CR, inet ) ;
}

/*-----------------30.08.2010 15:27-----------------
 * Обработчик рабочей программы Modbus TCP/IP
 * --------------------------------------------------*/
void Work_TCPIP( void )
{
   word length, i ;
   word ax ;

   if ( flag_newdata == 1 )
   {
      flag_newdata = 0;
      READ_NET( length, DR_DLI ) ;
      READ_NET( ax, DR_DI ) ;
      rmb.func = (b)ax ;
      for ( i = 2; i <= length; i = i+2 )
      {
         READ_NET( ax, DR_DI+i ) ;
         rmb.data[i-1] = (b)ax ;
         rmb.data[i-2] = (b)( ax >> 8 ) ;
      }
      WRITE_NET( DR_CR, DR_CR_CBI );

      length = modbus_slave( &rmb, &smb );

      WRITE_NET( DR_NDO, 1 ) ;
      length  += 2 ;
      WRITE_NET( DR_DLO , length ) ;
      ax = smb.func << 8 ;
      ax += smb.data[0] ;
      WRITE_NET( DR_DO, ax ) ;
      for ( i = 1; i < (length-1); i=i+2 )
      {
         ax  = smb.data[i] << 8 ;
         ax +=  smb.data[i+1] ;
         WRITE_NET( (DR_DO+i+1), ax ) ;
      }
      WRITE_NET( DR_CR, DR_CR_CBO );
   }

}

#else // _CM3_

//#include "lpc177x_8x_exti.h"
#include "net.h"
void Init_TCPIP( void )
{
  word i;
  byte *ptr = (b*)NetRam ;

  rmb.func  = 0 ;
   smb.func = 0 ;
   for ( i=0 ; i<MB_BUFFER; i++ )
   {
      rmb.data[i] = 0 ;
      smb.data[i] = 0 ;
   }
   LPC_GPIO1->CLR  = _DP_RESET;
   for(i=0; i < sizeof (TECRRegs);++i)
    {
      *ptr = 0;
      ++ptr;
    }



   //flag_newdata = 0;

  // word i ;
  //TECRRegs NetRamTMP = NetRam;
  //word *i;
   //EXTI_InitTypeDef eint_cfg;
  //i = NetRam->EthConfig.IpAddress;
  NetRam->EthConfig.IpAddress[0] = _r.IP1_addr; 
  NetRam->EthConfig.IpAddress[1] = _r.IP2_addr; 
  NetRam->EthConfig.IpAddress[2] = _r.IP3_addr; 
  NetRam->EthConfig.IpAddress[3] = _r.IP4_addr; 
 
      
  NetRam->EthConfig.IpMask[0] = _r.IPM2_addr;
  NetRam->EthConfig.IpMask[1] = _r.IPM2_addr;
  NetRam->EthConfig.IpMask[2] = _r.IPM3_addr;
  NetRam->EthConfig.IpMask[3] = _r.IPM4_addr;
   
  NetRam->EthConfig.IpGate[0] = _r.DIP1_addr;
  NetRam->EthConfig.IpGate[1] = _r.DIP2_addr;
  NetRam->EthConfig.IpGate[2] = _r.DIP3_addr;
  NetRam->EthConfig.IpGate[3] = _r.DIP4_addr;
   
  NetRam->EthConfig.MacAddress[0] = _r.EMAC1_addr;
  NetRam->EthConfig.MacAddress[1] = _r.EMAC2_addr;
  NetRam->EthConfig.MacAddress[2] = _r.EMAC3_addr;
  NetRam->EthConfig.MacAddress[3] = _r.EMAC4_addr;
  NetRam->EthConfig.MacAddress[4] = _r.EMAC5_addr;
  NetRam->EthConfig.MacAddress[5] = _r.EMAC6_addr;

//-----------------------------------
/* Прерывания при работе с Net-CM3 не используются
//    Настраиваем прерывания
 eint_cfg.EXTI_Line = EXTI_EINT2;
 eint_cfg.EXTI_Mode = EXTI_MODE_EDGE_SENSITIVE;
 eint_cfg.EXTI_polarity = EXTI_POLARITY_LOW_ACTIVE_OR_FALLING_EDGE;
 
 EXTI_Config(&eint_cfg);
 NVIC_SetPriority( EINT2_IRQn, IntPriority(1, 3));
 NVIC_EnableIRQ( EINT2_IRQn );*/
 NetRam->TimerWD = _r.Net_LT;
 NetRam->EthConfig.On = _r.net_setting._.vkl;
 
 LPC_GPIO1->SET  = _DP_RESET;

}
//--------------------------------------------
void Work_TCPIP( void )
{
  word i;
  
   NetRam->EthConfig.On = _r.net_setting._.vkl;

  if (NetRam->TcpRequestF != 0)
  {  
     rmb.func = NetRam->eth_data[0] ;
     if (NetRam->eth_length < ((sizeof (Tmodbus_packet)/2))-1)
     {
       for (i = 1; i<= NetRam->eth_length; ++i)
       {
         rmb.data[i-1] = NetRam->eth_data[i];
       }
     }
     
     NetRam->TcpReadyF = 0;
     NetRam->TcpRequestF = 0;
      
     i = modbus_slave( &rmb, &smb );
     NetRam->eth_length = i;
     NetRam->eth_data[0] = smb.func;
     NetRam->eth_data[1] = smb.data[0];
     for ( i = 2; i <= NetRam->eth_length; ++i )
     {
       NetRam->eth_data[i] = smb.data[i-1];
     }
     NetRam->eth_length++;     
     NetRam->TcpReadyF = 0xff;     
  }
}

#endif // _CM3_
