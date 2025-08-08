word Virtual_canSlaveDrive( byte port );

/* ������� ������� ��� ������/������ � �����. ������� - �������� � c��������� VAR_MTAB.h
1. #define Addr    1 - �� ������������. ������ ������� �� �������, �� � ������������ ���� ���������. 
2. #define _WR_REGS     _W_Multiple_Registers   - ����� �������
   #define _RD_REGS     _R_Holding_Registers
3. 0x28 - ���. ����� ���������� � var_tab - "cId#P"
4. 0x02 - ���. ���������� �������� ���������� � ������ ����, �.�. "cId#P" � "cId#M"
5. 0x00 - �� ���. ��������� ����� � ������� ������.  
6. _MkSec(1*1000) - ���. �������� ����� ������� � ��������� ��������. �� ��������� 3.5 chara. �� ���� ����������. 
7. 0 - ����� ����� ������������� � ��������. ��������� 0

//----------------- ��������� � VAR_MTAB  -----------------------------
#define Addr         1  
#define _WR_REGS     _W_Multiple_Registers   
#define _RD_REGS     _R_Holding_Registers

TSettingModbusFrame  SetMBFrame[] = 
{
  { Addr1, _WR_REGS, 0x28/*40* / , 0x02, 0x00, _MkSec(1*1000)/*100* /, 0 },
  { Addr1, _RD_REGS, 0x28, 0x02, 0x00, _MkSec(1*1000), 0 }
};

word NumFrames = sizeof(SetMBFrame)/sizeof(TSettingModbusFrame);
//---------------------------------------------------------------------- */


struct CAN_slave_data  virtual_can_sd[ _Num_VirtualCAN_Ports]  ;
_x_far const struct SlaveVars  virtual_svar[_Num_VirtualCAN_Ports] =
{
  {
    sizeof(var_tab1)/sizeof(struct namevar), // ������ �������
    &var_tab1[0]                             // ����� �������
  },
} ;

//void modbus_slave( void )
word modbus_slave( Tmodbus_packet *Receive, Tmodbus_packet *Send )
{
  word start_addr, quantity, ByteCount;
  word length, i, j;
  byte ErrorCode = 0;
  int index;
//  static byte Symb_old;
//  static lword Symb_count;

  lword pAddr;
  lword arrayStartIndex, arraySize;

//
//   Atention!!!
//  If set breakpoint inside this function and stop at it
//  then Tcp-adapter will not wait and automaticaly response to client
//  the same frame which received!!!

  union
  {
    word  slovo;
    struct
    {
#ifdef _Union_FR
      byte b1;
      byte b2;
#else
      byte b2;
      byte b1;
#endif
    } _;
  } DATA;

  start_addr = (w)( Receive->data[0] ) ;
  start_addr = ( start_addr << 8 ) + (w)Receive->data[1] ;
  quantity   = (w)( Receive->data[2] ) ;
  quantity   = ( quantity << 8 ) + (w)Receive->data[3] ;
  Send->func = Receive->func ;

  switch ( Receive->func )
  {
    case _R_Coils :
        ErrorCode = _Code_Not_Support ;
/*                      if ( ( quantity >= 1 ) && ( quantity <= 0x07D0 ) )
                        {
                          if ( ( ( start_addr/8 ) <= kol_var ) &&
                               ( ( start_addr + quantity/8) <= kol_var ) )
                          {
//                           ����� ��������� ������, � ������
                             Send->data = ( quantity + 7 ) / 8 ;

                             for ( i = 0 ; i <= s_mbf.data[0] ; i++ )
                             {
                                Send.data++;
                                Send->data[1+i] = tabl_var_tab[0][start_addr+i] ;
                             }
                             quantity = quantity - ( s_mbf.data[0] - 1 ) * 8 ;
                             Send->data[1+i] &= ~( 0xFF << quantity ) ;
//                           ������� ����� ������� Modbus
                             length = 3 + s_mbf.data[0];
                          }
                          else
                            ErrorCode = _Address_Not_Support ;
                        }
                        else
                          ErrorCode = _Out_Of_Quantity ;
  */
        break ;

    case _R_Discrete_Inputs :
        ErrorCode = _Code_Not_Support ;
/*                      if ( ( quantity >= 1 ) && ( quantity <= 0x07D0 ) )
                        {
                          if ( ( ( start_addr/8 ) <= kol_var ) &&
                               ( ( start_addr + quantity/8) <= kol_var ) )
                          {
//                           ����� ��������� ������, � ������
                             s_mbf.data[0] = ( quantity + 7 ) / 8 ;

                             for ( i = 0 ; i <= s_mbf.data[0] ; i++ )
                             {
                                s_mbf.data[1+i] = tabl_var_tab[0][start_addr+i] ;
                             }
                             quantity = quantity - ( s_mbf.data[0] - 1 ) * 8 ;
                             s_mbf.data[1+i] &= ~( 0xFF << quantity ) ;
//                           ������� ����� ������� Modbus
                             length = 3 + s_mbf.data[0];
                          }
                          else
                            ErrorCode = _Address_Not_Support ;
                        }
                        else
                          ErrorCode = _Out_Of_Quantity ;
  */
        break;

    case _R_Holding_Registers :
        if ( ( quantity >= 1 ) && ( quantity <= 0x07D ) )
        {
          if ( ( ( start_addr ) <= kol_var ) &&
               ( ( start_addr + quantity) <= kol_var ) )
          {
// ����� ��������� ������, � ������
               length = quantity ;
// ������� ����� ������� Modbus
               for ( i = 0, j = 1 ; i < length ; i++, j = j+2 )
               {
				      DATA.slovo = *((w*)var_tab1[start_addr+i].addr) ;
                                                    // �������� �������� �� ������ 
                  Send->data[j+1] = (w)DATA._.b2;   // �������� ����
                  if (var_tab1[start_addr+i].type != _CHAR_type)
                  {
                    Send->data[j]   = (w)DATA._.b1; // ������ ����
                  }
                  else
                  {
                    Send->data[j] = 0;
                  }
/*                  if (DATA._.b2 == Symb_old)
                  {
                    if (++Symb_count > 3) 
                    {
                      Tx_Tmp_buf[TxBuf_index-3] =Tx_Tmp_buf[TxBuf_index-2];
                      Tx_Tmp_buf[TxBuf_index-2] =Tx_Tmp_buf[TxBuf_index-1];
                      Tx_Tmp_buf[TxBuf_index-1] =Tx_Tmp_buf[TxBuf_index];        
                    }                    
                    
                  }
                  else
                  {
                    Symb_old = DATA._.b2;
                    Symb_count = 0;
                  }
                  Tx_Tmp_buf[TxBuf_index] = UartCAN_Tx.all;
                  if (Symb_count < 3)
                  {                  
                    if (++TxBuf_index >= 1000)
                    {
                      TxBuf_index = 0;
                    }
                  }
*/
               }
               length = length * 2 ;    
               Send->data[0] = (w)length ;
               length++;
          }
          else
            ErrorCode = _Address_Not_Support ;
        }
        else
          ErrorCode = _Out_Of_Quantity ;

        break;

    case _R_Input_Register :
        ErrorCode = _Code_Not_Support ;
        break;

    case _W_Single_Coils :
        ErrorCode = _Code_Not_Support ;
        break;

    case _W_Single_Register :

      if ( start_addr <= kol_var )
          {
             DATA._.b1 = Receive->data[2];
             DATA._.b2 = Receive->data[3];
             if ( var_tab1[start_addr].access == _READ_WRITE_access )
             {
               if (var_tab1[start_addr].type != _CHAR_type){
                 *((w*) var_tab1[start_addr].addr) = DATA.slovo ;
               }
               else
               {
                  *((b*) var_tab1[start_addr].addr) = DATA._.b2 ;
               }
             }
             else
             {
                 ErrorCode = _Address_Not_Support ;
                 break;
             }

//      ����� ��������� ������, � ������
               Send->data[0] = Receive->data[0];
               Send->data[1] = Receive->data[1];
               Send->data[2] = Receive->data[2];
               Send->data[3] = Receive->data[3];

               length = 4 ;
          }
          else
            ErrorCode = _Address_Not_Support ;
        break;

    case _R_Exception_Status :
        ErrorCode = _Code_Not_Support ;
        break;

    case _Diagnostic :
        ErrorCode = _Code_Not_Support ;
        break;

    case _Get_Com_Event_Counter :
        ErrorCode = _Code_Not_Support ;
        break;
 
    case _Get_Com_Event_Log :
        ErrorCode = _Code_Not_Support ;
        break;

    case _W_Multiple_Coils :
        ErrorCode = _Code_Not_Support ;
        break;

    case _W_Multiple_Registers :
        ByteCount = Receive->data[4] ;
        if ( ( ( quantity >= 1 ) && ( quantity <= 0x07B ) ) && ( ByteCount == ( quantity * 2 ) ) )
        {
          if ( ( ( start_addr ) <= kol_var ) &&
               ( ( start_addr + quantity ) <= kol_var ) )
          {
               length = quantity ;

               for ( i = 0, j = 5 ; i < length ; i++, j = j+2 )
               {
                  DATA._.b1 = Receive->data[j];
                  DATA._.b2 = Receive->data[j+1];
                  index = start_addr + i;
                     if ( var_tab1[index].access == _READ_WRITE_access )
                     {
                       if (var_tab1[index].type != _CHAR_type){
                          *((w*) var_tab1[index].addr) = DATA.slovo ;
                       }            
                       else
                       {
                          *((b*) var_tab1[index].addr) = DATA._.b2 ;
                       }                        
                     }
                     else
                     {
                         ErrorCode = _Address_Not_Support ;
                         break;
                     }
               }
//      ����� ��������� ������, � ������
               Send->data[0] = Receive->data[0];
               Send->data[1] = Receive->data[1];
               Send->data[2] = Receive->data[2];
               Send->data[3] = Receive->data[3];

               length = 4 ;
          }
          else
            ErrorCode = _Address_Not_Support ;
        }
        else
          ErrorCode = _Out_Of_Quantity ;

        break;

    case _Report_Slave_ID :
        ErrorCode = _Code_Not_Support ;
        break;

    case _R_File_Record :
        ErrorCode = _Code_Not_Support ;
        break;

    case _W_File_Record :
        ErrorCode = _Code_Not_Support ;
        break;

    case _Mask_Write_Register :
        ErrorCode = _Code_Not_Support ;
        break;

    case _RW_Multiple_Registers :
        ErrorCode = _Code_Not_Support ;
        break;

    case _R_FIFO_Queue :
        ErrorCode = _Code_Not_Support ;
        break;

    case _R_Device_Ident :
        ErrorCode = _Code_Not_Support ;
        break;

    case _CAN_Frame :
  		virtual_can_sd[_ModbusOverCAN_port].rmsg.cfg.dlen =  Receive->data[0] - 2 ; // ����� ������ = ID(2 �����) + Data
// ID ��� �� ����� (������������ ������ ��� �����)
		Send->data[1] = Receive->data[1];  // CAN ID
		Send->data[2] = Receive->data[2];  // CAN ID
		for ( i = 0; i < 8; i++ )
		{
		   virtual_can_sd[_ModbusOverCAN_port].rmsg.data[i] = Receive->data[i+3];
		}

		Virtual_canSlaveDrive( _ModbusOverCAN_port );

  		Send->data[0] = virtual_can_sd[_ModbusOverCAN_port].smsg.cfg.dlen + 2; // ����� ������ = ID(2 �����) + Data
		for ( i = 0; i < Send->data[0]; i++ )
		{
		   Send->data[i+3] = virtual_can_sd[_ModbusOverCAN_port].smsg.data[i] ;
		}
		length = Send->data[0] + 1;

//		if ( error )
//		{
//		   ErrorCode =
//		}
        break;


    // 2021-02-08 ��� ������ � ��� :
    // - ������ ��������� � �������� ������ 65536 ����� � 4-� ������� �������
	case _R_StructL :
          if (  start_addr  <= kol_var )
		  {
		     if ( ( var_tab1[start_addr].type == _CHAR_array_type ) || ( var_tab1[start_addr].type == _uCHAR_array_type ) )
			 {
                  // 23-03-2020 ��� - ��������� ����� Host ��� �� ���� ������ ������� ������ �� ��� �����:
                  // - ��������� ����� ������ ���������� ������ �� ������� ������������� �� "0"
                  // - ���� Host �������� ������ ��� ������ ������� �� ��������� �� ������� �������
                  //   �� ������������ ����������� ���������� ������
                  // - ���� Host �������� ������ ��� ������ ������� ��������� �� ������� �������,
                  //   �� ��������� ����� �� ��������� �� ������� ������� �� ������������ ���������� ������
                  //   �� ���������� ������ �� ����� �������, �.�. ������ ��� ���� ���������
                  //   ������ ��� ���� �� ����������
                  // - ���� Host �������� ������ ��� ������ ������� ��������� �� ������� �������
                  //   �� ��������� ����� ��������� �� 1 �� ������� �������, �.�. ������
                  //   �� ������������ ������ � ����� _End_Of_Quantity
                  // - ���� Host �������� ��������� ����� ��������� ����� ��� �� 1 �� ������� �������
                  //   �� ������������ ������ � ����� _Out_Of_Quantity

                  arrayStartIndex = (lw)( Receive->data[2]<< 24 ) + ((lw)Receive->data[3]<<16)+((lw)Receive->data[4]<<8 ) + (lw)Receive->data[5] ;
                  arraySize = var_tab1[start_addr].lon;// / sizeof(char);
                  quantity   = ((w) Receive->data[6]<< 8 ) + (w)Receive->data[7] ;
                  if ( arrayStartIndex < arraySize )
				  {
                      if( arrayStartIndex + quantity > arraySize ) quantity = arraySize - arrayStartIndex;

                      Send->data[0] = (quantity & 0xFF00) >> 8;
                      Send->data[1] = quantity & 0x00FF;

				      pAddr = (lword)(var_tab1[start_addr].addr);
                      pAddr = pAddr + arrayStartIndex;
                      for ( i = 2 ; i < quantity+2 ; i++ )
                      {
                        Send->data[i] = *((b*)pAddr) ;
						(b*)pAddr++;
                      }
					  length = quantity + 2; // +length
                  }
                  else  if ( arrayStartIndex == arraySize )  ErrorCode = _End_Of_Quantity; // 0x02

				  else
					ErrorCode = _Out_Of_Quantity; // 0x02
			 }
			 else
				 ErrorCode = _Param_Not_Support; // 0x03;
		  }
		  else
			  ErrorCode = _Address_Not_Support; // 0x1
		  break;

    // 2021-02-08 ��� ������ � ��� :
    // - ������ ��������� � �������� ������ 65536 ����� � 4-� ������� �������
	case _W_StructL :
          if (  start_addr  <= kol_var )
		  {
		     if ( ( var_tab1[start_addr].type == _CHAR_array_type ) || ( var_tab1[start_addr].type == _uCHAR_array_type ) )
			 {
                  // 05-05-2020 ��� - ��������� ����� Host ��� �� ���� ������� ������� ������ �� ��� �����:
                  arrayStartIndex   = (lw)( Receive->data[2]<< 24 ) + ((lw)Receive->data[3]<<16)+((lw)Receive->data[4]<<8 ) + (lw)Receive->data[5] ;
                  arraySize = var_tab1[start_addr].lon;// / sizeof(char);
                  quantity   = ((w) Receive->data[6]<< 8 ) + (w)Receive->data[7] ;
                  if ( arrayStartIndex < arraySize )
                  {   //  �������� ������� ������� ���������� ������ ���� � ������
                      if( arrayStartIndex + quantity > arraySize ) quantity = arraySize - arrayStartIndex;

                      //  ��� 2021-02-09 - ����� ��� ���������� � ������� �������
                      //Send->data[0] = Receive->data[0] ;
                      //Send->data[1] = Receive->data[1] ;
                      //Send->data[2] = Receive->data[2] ;
                      //Send->data[3] = Receive->data[3] ;
                      //Send->data[4] = Receive->data[4] ;
                      //Send->data[5] = Receive->data[5] ;
                      //Send->data[6] =(quantity & 0xFF00) >> 8;
                      //Send->data[7] = quantity & 0x00FF;
                      Send->data[0] =(quantity & 0xFF00) >> 8;
                      Send->data[1] = quantity & 0x00FF;


				      pAddr = (lword)(var_tab1[start_addr].addr);
                      pAddr = pAddr + arrayStartIndex;

					  for ( i = 8 ; i < quantity+8 ; i++ )
                      {
                        *((b*)pAddr) = Receive->data[i];
						(b*)pAddr++;
                      }

                      length = 2; //8  // +length

                  }
                  else  if ( arrayStartIndex == arraySize )  ErrorCode = _End_Of_Quantity; // 0x02

				  else
					ErrorCode = _Out_Of_Quantity; // 0x02
			 }
			 else
				 ErrorCode = _Param_Not_Support; // 0x03;
		  }
		  else
			  ErrorCode = _Address_Not_Support; // 0x1

		  break;

    default:
        ErrorCode = _Code_Not_Support ;
        break;
  }
  if ( ErrorCode != 0 )
  {
    length = 1;
    Send->data[0] = ErrorCode;
    Send->func = Send->func | 0x80;
  }
  return length;
}

#ifdef _ModbusMaster   
/*------------------------------------------------------------------------------
 * ������� ������� ������� SAP Modbus RTU Master.
 * word frameCount      - ����� ������
 * Tmodbus_packet *Send - ��������� ��� ���������� ������ Modbus ��� ��������
 * ���������� ����� ������
 * --------------------------------------------------*/
word modbusMasterSend( word frameCount, Tmodbus_packet *Send )
{
  // ������ ������� 
  word start_addr, quantity,source_addr;
  word length = 0, i;//, j;
  byte func, ErrorCode = 0;
  
  func = SetMBFrame[frameCount].Func;        // �������� ����� �������
  quantity = SetMBFrame[frameCount].Count;   // ���-�� ����������
  start_addr = SetMBFrame[frameCount].StartSlave; 
  source_addr = SetMBFrame[frameCount].Start ; // ����� ���������� � �������
   union // ����������� ��� ���������� ���������� ���������, � ����������� �� ��� ����
  {
    word  slovo;
    struct
    {
#ifdef _Union_FR
      byte b1;
      byte b2;
#else
      byte b2;
      byte b1;
#endif
    } _;
  } DATA;
  
  switch ( func ) 
  {
    case _R_Holding_Registers :
    case _R_Input_Register :     // ��������� � ������ ��� ������
 /*-----------------------------------------------------------------------------
 * ������-������
 * = 0 - ������
 * = 4 - ������ �������, ������ 4 �����
 * --------------------------------------------------*/
      if ( (quantity < 1) || (quantity > 0x7D) ) length = 0/*return 0*/;   
      else
      {
      // ������ ������� � ���������� ����������
        Send -> data[0] = ((start_addr >> 8) & 0xFF);   //  out[0] = (byte)((start >> 8) & 0xFF);
        Send -> data[1] = (start_addr & 0xFF);          //  out[1] = (byte)(start & 0xFF);
        Send -> data[2] = ((quantity >> 8) & 0xFF);     //  out[2] = (byte)((count >> 8) & 0xFF);
        Send -> data[3] = (quantity & 0xFF);            //  out[3] = (byte)(count & 0xFF);
        length = 4;                                     //  return 4;
      }
 //-----------------------------------------------------------------------------
		break;
    case _W_Single_Register :

		break;
    case _W_Multiple_Registers :
/*------------------------------------------------------------------------------
 * ������-������
 * ���������� ���������� ����
 * = 0 - ������
 * --------------------------------------------------*/
      if ( (quantity < 1) || (quantity > 0x7D) ) length = 0/*return 0*/;
      else
      {
        Send -> data[0] = (byte)((start_addr >> 8) & 0xFF);
        Send -> data[1] = (byte)(start_addr & 0xFF);
        Send -> data[2] = (byte)((quantity >> 8) & 0xFF);
        Send -> data[3] = (byte)(quantity & 0xFF);
        Send -> data[4] = quantity*2;
        for (  i=0; i < quantity; i++ )
        {
          DATA.slovo = *((w*)var_tab1[source_addr+i].addr) ;
          // �������� ����������  
          Send -> data[2*i+6] = (w)DATA._.b2;                     //(byte)((*in[i])>>8);  �������� ����
          if (var_tab1[source_addr+i].type != _CHAR_type){
            Send->data[2*i+5]   = (w)DATA._.b1;                   // ������� ����  (byte) (*in[i]);
          }
          else{
            Send->data[2*i+5] = 0;
          }
        }
        length = 5+quantity*2;                                    // return 5+count*2;      
      }
//------------------------------------------------------------------------------
		break;
   }
   Send -> func = func;                                          // (*mbfOut).Func = func;
   if ( ErrorCode != 0 )
   {
     length = 1;
     //Send->data[0] = ErrorCode;
     //Send->func = Send->func | 0x80;
     return length;
   } 
   return length;
   //return ++length;
}


/*------------------------------------------------------------------------------
 * ������� ��������� ������ ������ SAP Modbus RTU Master.
 * word frameCount      - ����� ������
 * Tmodbus_packet *Send - ��������� ��� ���������� ������ Modbus ��� ��������
 * ���������� ����� ������
 * --------------------------------------------------*/
word modbusMasterReceive( word frameCount, Tmodbus_packet *Receive )
{
   // ������ ������� 
  word start_addr, quantity;//, ByteCount;
  word length = 0, i;//, j;
  byte ErrorCode = 0;
  int index;
  word count;
//  Atention!!!
//  If set breakpoint inside this function and stop at it
//  then Tcp-adapter will not wait and automaticaly response to client
//  the same frame which received!!!
  union
  {
    word  slovo;
    struct
    {
#ifdef _Union_FR
      byte b1;
      byte b2;
#else
      byte b2;
      byte b1;
#endif
    } _;
  } DATA;

  //-----------------------------------????----------
  //func, ������ �� �������� �������� ��� �� ������, ���� ������� �� ��������
  word func = Receive -> func;        //(*mbfIn).Func; 
  //func = SetMBFrame[frameCount].Func;           // �������� ����� �������
  //--------------------------------------------------
  quantity = SetMBFrame[frameCount].Count;        // ���-�� ����������
  start_addr = SetMBFrame[frameCount].Start;      // ����� ���������� � �������
  
  //word length = 0;

  if ( (func & 0x80) != 0)  
  {
  //--------------------?????--------------------------------------------  
  //���� ������ ���������� � func, �� ��� �������� � ����� ��� ��� ������ ????
    //**data = (*mbfIn).data[0] ; old variant
    //    =   Receive -> data[0]; new variant    
    //-------------------------------------------------------------------
  }
  switch ( func )
  {
    case _R_Holding_Registers :
    case _R_Input_Register :
/*------------------------------------------------------------------------------
 * ������-�����
 * ���������� ���������� ����:
 * = 0 - ������
 * --------------------------------------------------*/
      length = Receive -> data[0];//*in;  //�������� ���� ���������
      count = 0;
      if ( length == 0 ) length = 0; // return 0;
      else {
        for ( i = 0; i < (length/2); i++ ){
        //*out[count] = ((word)in[2*i+1] << 8) + in[2*i+2] ;
          DATA._.b1 = Receive->data[2*i+1];
          DATA._.b2 = Receive->data[2*i+2];
          index = start_addr + count;
          if ( var_tab1[index].access == _READ_WRITE_access )
          {
            if (var_tab1[index].type != _CHAR_type){
              *((w*) var_tab1[index].addr) = DATA.slovo ;
            }            
            else
            {
              *((b*) var_tab1[index].addr) = DATA._.b2 ;
            }                        
          }
          else
          {
            ErrorCode = _Address_Not_Support ;
            break;
          }
          count++;        
        }
        length = count;//return count;
      }
      break;
    case _W_Single_Register :

      break;
    case _W_Multiple_Registers :
/*------------------------------------------------------------------------------
 * ������-�����. ���� ����� ���������� � ������� ������, �� ��� ��.
 * ���������� ���������� ���������� ����:
 * = 0 - ������
 * = 4 - ������ �������, ������ 4 �����
 * --------------------------------------------------*/
      word st, ct;
      st = (((word)Receive->data[0])<<8) + (word)Receive->data[1];//st = (((word)in[0])<<8) + (word)in[1]; //77777777777777777
      ct = (((word)Receive->data[2])<<8) + (word)Receive->data[3];//ct = (((word)in[2])<<8) + (word)in[3]; //7777777777777777
      if ( (st == start_addr) && (ct == quantity) ) length = 4;   //return 4;
      else                                          length = 0;   // return 0;
      break;
  }
  
 if ( ErrorCode != 0 )
  {
    length = 1;
    //--------??????????-----------------------------------
    //Send->data[0] = ErrorCode;
    //Send->func = Send->func | 0x80;
    //-----------------------------------------------------
    return length;  
  }
  return length;  
}
//--------
#endif

//--------
word Virtual_canSlaveDrive( byte port )
{

  word    ax, bx, cx ;
  byte    ah , r_dlen , s_dlen ;
  lword lax;
  static   byte    count[_Num_VirtualCAN_Ports] ;
  void   *ptr ;
  struct  CAN_slave_data  *dptr ;
  _x_far const struct namevar  *vptr ;

   //   ��������� ��� �������������� ��������� ���� � �����,
   // � ������� ����� � ��������.
  union lax_ax_b  buff ;

  //*tds canFromTxBuffMsg( port ) ;
        //   ��� ���������� ������ �������� ������� ���������
        // ����� ����� ������.
  dptr = &virtual_can_sd[port] ;
  vptr = virtual_svar[port].tab ;

            // ��������: �� ������� �� ����� �������� �� ������������� �����
          // ������� ������.
          //   ���� ���-�� ����� ���� � �� ���������� � ���� ����� N-������
          // ���� �������������� ��� ������ ���������.
        if ( dptr->long_io.size != 0 ) // ����� �� ����?
        {
          if ( (u)((w)(Timer1_Ovr-dptr->long_io.time)) > _TimeOut_long_io ) dptr->long_io.size=0 ;
        }

//----------------------------------------------------------------------------

         // ��������� �� ����� ������?
  count[port] = 0 ;
  //*tds  while ( canFromSlvBuffReceiveMsg( port, &dptr->rmsg ) != 0 )
  {
         //04.11.04 15:04
     //ax = canFromSlvBuffReceiveMsg( port, &dptr->rmsg )  ;
     //if ( ax == 0 ) return 1 ;

//----------------------------------------------------------------------------

        // ��������� ��� ������������� ���� ������� � ���������� ������� �������.
     dptr->cmd.all = dptr->rmsg.data[0] ;
     dptr->cmd._.rqst = 0 ;// ���������� ��� �������, �� ������ ������ ������-�������.
     r_dlen  = dptr->rmsg.cfg.dlen ;
             // ����� ���������� 'id' � �������� ���������,
            // �.�. ��������� ������� dptr->rmsg' ����� ����������.
     dptr->smsg.id = dptr->rmsg.id ;
     switch ( dptr->cmd._.cmd )
     {
       default:  dptr->smsg.data[1]  = _Err_COMMAND ; //����������� ������.
               goto err;

 //  ����������� ������/������ �� ������������� �������
       case _Continue_OpCode:
                       //  ���� ���� ��������, ������ ������� "�����������
                      // ������" �� �������������� ���. "������ ������".
                   if ( dptr->long_io.size == 0 )
                   {
                     dptr->smsg.data[1] = _Err_CONTINUE ;
                      goto err;
                   }
                   else  // ���� ������� ������ �����: ����� ���� ��
                   {     // �������� ?
                     if ( dptr->long_io.id == dptr->rmsg.id )
                     {     // ���������/�������������� ��������� ��������� ������ ������.
                       for ( bx = 1 ; bx < 8 && dptr->long_io.size > 0; bx++ )
                       {
                         dptr->long_io.size-- ;
                         switch ( dptr->long_io.cmd )
                         {
                           case _Read_OpCode:
                               dptr->smsg.data[bx] = *(dptr->long_io.addr++) ;
                             break;

                           case _Write_OpCode:
                               *(dptr->long_io.addr++) = dptr->rmsg.data[bx] ;
                             break;
                         }
                       }
                       if ( dptr->long_io.size == 0 )
                       {  // �������� � ������ ���������� ����� �������,
                         dptr->cmd._.cmd = dptr->long_io.cmd ; // ��������� � ���� ��� ��������.
                       }
                       else dptr->cmd._.cmd = _Continue_OpCode ;

                       //dptr->smsg.data[0] = dptr->cmd.all  ;
                       s_dlen = bx ;
                      //--  �������� ������� time-out �� ������������� ����� ������� ������.
                       dptr->long_io.time = Timer1_Ovr ;
                     }
                     else
                     {   // ���� ����� - ������� ������� ��������� ������.
                       dptr->smsg.data[1]  = _Err_WAIT ;
                       goto err;
                     }
                   }
         break;

 //  ������ ����������� ��������   //------------
       case _Descript_OpCode: //������ ����������� �� �����.
       case _Descript_OpCodeL:

            ax = dptr->rmsg.data[1] ;
               // �� ������� �� ���������� �� ������ 6-�� ��������.
            if ( ax > _canName_max_size )
            {
              dptr->smsg.data[1] = _Err_NAME_SIZE ; //����������� ������.
              goto err;
            }
              dptr->canName_buff[ax] = 0 ; // ��������� ����� ������� �����.
            for ( ax-- ; (sw)ax >= 0 ; ax-- )// �������� ��� � �����, ����� ��� ���-�� �� �����.
            {
              dptr->canName_buff[ax] = dptr->rmsg.data[2+ax]  ;
            }
                  //dptr->rmsg.data[2+ax] = 0 ;// ��������� ����� ������� �����.
            ax = seek_index( port, dptr->canName_buff ) ;
               // ��� �� �������.
            if ( (sw)ax == -1 )
            {
              dptr->smsg.data[1] = _Err_NAME ; //����������� ������.
        err:
                 // �������� � ������ ���������� ����� �������,
              dptr->cmd._.cmd = _Error_OpCode ; // ��������� � ���� ��� ������.
              //dptr->smsg.data[0] = dptr->cmd.all  ;
              s_dlen = 2 ;
            }
            else
            {
              //dptr->smsg.data[0] =dptr->rmsg.data[0] ;
              dptr->smsg.data[1] = ax;
              dptr->smsg.data[2] = vptr[ax].access;
              dptr->smsg.data[3] = vptr[ax].type;
              lax = vptr[ax].lon;
              dptr->smsg.data[4] = (b)lax;
              dptr->smsg.data[5] = (b)((lw)lax>>8);
              if (dptr->cmd._.cmd == _Descript_OpCodeL)
              {
                dptr->smsg.data[6] = (b)((lw)lax>>16);
                dptr->smsg.data[7] = (b)((lw)lax>>24);
                dptr->smsg.data[8] = (w)vptr[ax].nom;
                dptr->smsg.data[9] = (w)vptr[ax].nom>>8;
                s_dlen = 10 ;
              }
              else
              {
                dptr->smsg.data[6] = (w)vptr[ax].nom;
                dptr->smsg.data[7] = (w)vptr[ax].nom>>8;
                s_dlen = 8 ;
              }

            }
       break;
 //  ������ ����� ���������� �������� //------------
       case _VarName_OpCode: //������ ����� �� �����������.

               // �� ������� �� ���������� �� ������ �������.
            if ( dptr->rmsg.data[1] >= svar[port].size )
            {
              dptr->smsg.data[1]  = _Err_DESCRIPT ; //����������� ������.
              goto err;
            }
               // ����������� ��� ���������� � ������ ���������.
            for ( ax = 2, bx = 0 ;  ; ax++, bx++ )
            {  //  ������ �� ��� � ��������� - �������� 6 ��������..
              if ( ax > 8 )// " > 8 " �.�. ����� ��� ���� ������ �����,
              {            // ����� ��������� ����� ������.
                dptr->smsg.data[1] = _Err_NAME_SIZE ; //����������� ������.
                goto err;
              }
              ah = vptr[dptr->rmsg.data[1]].name[bx] ;
              if ( ah != 0 ) dptr->smsg.data[ax] = ah ;// ��������� ����� �����.
              else  break ;                            // NULL Vit-07.12.07 14:17
            }
            dptr->smsg.data[1] = bx;
            s_dlen = ax ;

       break;
 // ������ ������ ��������   //------------
       case _Read_OpCode: //������ �� �����������.

          for ( cx = 1, bx = 1 ; cx < r_dlen ; )
          {      // ���������� i-���� �����������.
            ax = dptr->rmsg.data[cx++] ;
               // �� ������� �� ���������� �� ������ �������.
            //if ( (sw)ax >= _SizeVarTable )
            if ( ax >= svar[port].size )
            {
              dptr->smsg.data[1]  = _Err_DESCRIPT ; //����������� ������.
              goto err;
         len: dptr->smsg.data[1]  = _Err_DATA_LENGHT ; //����������� ������.
              goto err;
            }
            else
            {     // ������������ ������ ��� ��������� ���������?
              if (( vptr[ax].type & _Indirect_type) != 0 )
                     ptr = *(void **)vptr[ax].addr ;// ��������� ���������.
              else   ptr =  vptr[ax].addr ;
              switch ( vptr[ax].type & ~_Indirect_type )
              {
               case _CHAR_type :
                   if ( bx+1 > 8 ) goto len ;
                   dptr->smsg.data[bx+0] = *(b*)ptr;
                   bx += 1 ;
                   break;

               case _SHORT_type:
               case _INT_type:
                   if ( bx+2 > 8 ) goto len ;
                   buff.ax = *(w*)ptr ;
                   dptr->smsg.data[bx+0] = buff.ax      ;
                   dptr->smsg.data[bx+1] = buff.ax >> 8 ;
                   bx += 2 ;
                   break;

               case _LONG_type :
                   if ( bx+4 > 8 ) goto len ;
                   buff.lax = *(lw*)ptr ;
                   dptr->smsg.data[bx+0] = buff.lax      ;
                   dptr->smsg.data[bx+1] = buff.lax >> 8 ;
                   dptr->smsg.data[bx+2] = buff.lax >>16 ;
                   dptr->smsg.data[bx+3] = buff.lax >>24 ;
                   bx += 4 ;
                   break;

            #ifdef   _CAN_FLOAT_VAR
               case _FLOAT_type :
                   if ( bx+4 > 8 ) goto len ;
                   buff.flt = *(float*)ptr ;
                   dptr->smsg.data[bx+0] = buff.lax      ;
                   dptr->smsg.data[bx+1] = buff.lax >> 8 ;
                   dptr->smsg.data[bx+2] = buff.lax >>16 ;
                   dptr->smsg.data[bx+3] = buff.lax >>24 ;
                   bx += 4 ;
                   break;
            #endif

               case _CHAR_array_type :
                      // ���� ������� ������ ��������.
                   if ( dptr->long_io.size == 0 )
                   {    // � �������� ����� ������������ � ��������
                       // ������������ ������ ������� ��� �����������
                       // ����������� ������ � ���� �� ����� ��� ���� ��������.
                     buff.ax = 0 ;

                     if ( r_dlen > 2 )
                     {
                       buff.ax = (w)dptr->rmsg.data[2] +
                                ((w)dptr->rmsg.data[3] << 8) ;
                         // �� ������� ������ �� ��������.
                       if ( vptr[ax].lon < buff.ax )
                       {
                         dptr->smsg.data[1]  = _Err_DATA_LENGHT ;
                         goto err;
                       }
                     }
                     cx = r_dlen ;// ����� ����� ������� ����.

                      // ������ ��������� ��������� �����
                      // ������������ ������ ��� ��������� ���������?
              if (( vptr[ax].type & _Indirect_type) != 0 )
#if defined (_24_BITS_) ||  defined (_32_BITS_)
                   dptr->long_io.addr = (b*)((lw)*(void **)vptr[ax].addr+buff.ax) ;   // ��������� ���������.
              else dptr->long_io.addr = (b*)((lw)vptr[ax].addr+buff.ax) ;
#else
                   dptr->long_io.addr = (b*)((w)*(void **)vptr[ax].addr+buff.ax) ;   // ��������� ���������.
              else dptr->long_io.addr = (b*)((w)vptr[ax].addr+buff.ax) ;
#endif
                     dptr->long_io.size = vptr[ax].lon-buff.ax ;
                     dptr->long_io.id   = dptr->rmsg.id ;
                     dptr->long_io.cmd  = _Read_OpCode ;

                       // �������� ������ ������������� �������.
                     dptr->smsg.data[bx+0] = dptr->long_io.size;
                     dptr->smsg.data[bx+1] = dptr->long_io.size>>8;
                     bx += 2 ;

                      // �������� � ������ ���������� ����� �������,
                     // ��������� � ���� ��� �������.
                     dptr->cmd._.cmd = _Continue_OpCode ;

                     //--  �������� ������� time-out �� ������������� ����� ������� ������.
                     dptr->long_io.time = Timer1_Ovr ;

                   }   // ���� ������� ������ �����, ����� ���� ��
                      // �������� � �� ����� �� �����������.
                   else
                   {   // ���� ����� - ������� ������� ��������� ������.
                     dptr->smsg.data[1]  = _Err_WAIT ;
                     goto err;
                   }
                   break;
                //======================

               default:  dptr->smsg.data[1]  = _Err_TYPE ; //����������� ������.
                         goto err;
             }
           }
         }
        // dptr->smsg.data[0] = dptr->cmd.all  ;
         s_dlen = bx ;
       break;
         //------------
 // ������ ������ ��������   //------------
       case _QuickWrite_OpCode: //������ �� ����������� ��� ��������������� ������.
       case _Write_OpCode: //������ �� �����������.

         for ( cx = 1, bx=1 ; cx < r_dlen ; )
         {     // ���������� i-���� �����������.
           ax = dptr->rmsg.data[cx++] ;

              // �� ������� �� ���������� �� ������ �������.
           //if ( (sw)ax >= _SizeVarTable )
           if ( ax >= svar[port].size )
           {
             dptr->smsg.data[1]  = _Err_DESCRIPT ; //����������� ������.
             goto err;
       len1: dptr->smsg.data[1]  = _Err_DATA_LENGHT ; //����������� ������.
             goto err;
           }
           else
           {
               //  �������� �� ������ �� ������ ��� ������ ����������.
             if ( vptr[ax].access != _READ_WRITE_access )
             {
               dptr->smsg.data[1]  = _Err_ACCESS ;
               goto err;
             }
                  // ������������� ���������� ���������� � ���������.
                 // ������������ ������ ��� ��������� ���������?
             if (( vptr[ax].type & _Indirect_type) != 0 )
                    ptr = *(void **)vptr[ax].addr ;// ��������� ���������.
             else   ptr =  vptr[ax].addr ;
             switch ( vptr[ax].type & ~_Indirect_type )
             {
              case _CHAR_type :
                   if ( cx+1 > r_dlen ) goto len1 ;
                 *(b*)ptr = dptr->rmsg.data[cx+0] ;
                   cx += 1 ;
                 break;

              case _SHORT_type:
              case _INT_type:
                   if ( cx+2 > r_dlen ) goto len1 ;
                 buff.ax = (w)dptr->rmsg.data[cx+0] +
                          ((w)dptr->rmsg.data[cx+1] << 8) ;
                 *(w*)ptr = buff.ax ;
                   cx += 2 ;
                 break;

              case _LONG_type :
                   if ( cx+4 > r_dlen ) goto len1 ;
                 buff.lax = (lw)(w)dptr->rmsg.data[cx+0]       +
                           ((lw)(w)dptr->rmsg.data[cx+1] << 8) +
                           ((lw)(w)dptr->rmsg.data[cx+2] <<16) +
                           ((lw)(w)dptr->rmsg.data[cx+3] <<24) ;
                 *(lw*)ptr = buff.lax ;
                   cx += 4 ;
                 break;

          #ifdef   _CAN_FLOAT_VAR
              case _FLOAT_type :
                   if ( cx+4 > r_dlen ) goto len1 ;
                 buff.flt = (lw)(w)dptr->rmsg.data[cx+0]       +
                           ((lw)(w)dptr->rmsg.data[cx+1] << 8) +
                           ((lw)(w)dptr->rmsg.data[cx+2] <<16) +
                           ((lw)(w)dptr->rmsg.data[cx+3] <<24) ;
                 *(float*)ptr = buff.flt ;
                   cx += 4 ;
                 break;
          #endif

               case _CHAR_array_type :
                      // ���� ������� ������ ��������.
                   if ( dptr->long_io.size == 0 )
                   {    // � �������� ����� ������������ � ��������
                       // ������������ ������ ������� ��� �����������
                       // ����������� ������ � ���� �� ����� ��� ���� ��������.
                     buff.ax = 0 ;

                     if ( r_dlen > 2 )
                     {
                       buff.ax = (w)dptr->rmsg.data[2] +
                                ((w)dptr->rmsg.data[3] << 8) ;
                         // �� ������� ������ �� ��������.
                       if ( vptr[ax].lon < buff.ax )
                       {
                         dptr->smsg.data[1]  = _Err_DATA_LENGHT ;
                         goto err;
                       }
                     }
                     cx = r_dlen ;// ����� ����� ������� ����.

                      // ������ ��������� ��������� �����
                      // ������������ ������ ��� ��������� ���������?
              if (( vptr[ax].type & _Indirect_type) != 0 )
#if defined (_24_BITS_) ||  defined (_32_BITS_)
                   dptr->long_io.addr = (b*)((lw)*(void **)vptr[ax].addr+buff.ax) ;   // ��������� ���������.
              else dptr->long_io.addr = (b*)((lw)vptr[ax].addr+buff.ax) ;
#else
                   dptr->long_io.addr = (b*)((w)*(void **)vptr[ax].addr+buff.ax) ;   // ��������� ���������.
              else dptr->long_io.addr = (b*)((w)vptr[ax].addr+buff.ax) ;
#endif
                     dptr->long_io.size = vptr[ax].lon-buff.ax ;
                     dptr->long_io.id   = dptr->rmsg.id ;
                     dptr->long_io.cmd  = _Write_OpCode ;

                       // �������� ������ ������������� �������.
                     dptr->smsg.data[bx+0] = dptr->long_io.size;
                     dptr->smsg.data[bx+1] = dptr->long_io.size>>8;
                     bx += 2 ; // ����������� ����� �������.

                      // �������� � ������ ���������� ����� �������,
                     // ��������� � ���� ��� �������.
                     dptr->cmd._.cmd = _Continue_OpCode ;

                     //--  �������� ������� time-out �� ������������� ����� ������� ������.
                     dptr->long_io.time = Timer1_Ovr ;

                   }   // ���� ������� ������ �����, ����� ���� ��
                      // �������� � �� ����� �� �����������.
                   else
                   {   // ���� ����� - ������� ������� ��������� ������.
                     dptr->smsg.data[1]  = _Err_WAIT ;
                     goto err;
                   }
                   break;
                //======================

               default:  dptr->smsg.data[1]  = _Err_TYPE ; //����������� ������.
                         goto err;
             }
           }
         }
       //  dptr->smsg.data[0] = dptr->rmsg.data[0] ;
         s_dlen = bx ;
       break;
         //------------
       case _Version_OpCode: //������ ������������ ��������.

         dptr->smsg.data[1] = _Version_code;
         dptr->smsg.data[2] = svar[port].size ;
         s_dlen = 3 ;
       break;
         //------------
       case _Break_OpCode: //���������� ��������.

         switch ( dptr->rmsg.data[1] )
         {
           default: ; //���������� �������� �������.
           case _Break_array :  dptr->long_io.size = 0 ;
         }
         s_dlen = 1 ;
       break;
     } //end switch

         // ��� ������ ��� ������ �� �������� �����.
          // ��������� �������� ��� �������
    if ((*(union MSG_CMD*)(b*)&(dptr->rmsg.data[0]))._.cmd != _QuickWrite_OpCode)
    {
      dptr->smsg.data[0] = dptr->cmd.all  ;
    //dptr->smsg.id = dptr->rmsg.id ;   // ���������� � ������ �������.
    //11.04.03 13:30dptr->smsg.cfg.dir = 1 ;
      dptr->smsg.cfg.dlen = s_dlen ;

//*tds       canInTxBuffMsg( port, &dptr->smsg ) ;
//*tds       canFromTxBuffMsg( port ) ;
    }
    //--------
        // ����� �� ������ ����� ���������� ��� ������� ������ ������.
//*tds    if ( ++count[port] >= 3 ) break ;
  }        //------------

               //���� NewDat ����� ����������, - �������� ����
               //��������� ������ � ����� ����������
               // if ((can_msg15con1 & 0x03) == 0x02 ) goto povtor_read_MO15;
   return 0 ;
}
