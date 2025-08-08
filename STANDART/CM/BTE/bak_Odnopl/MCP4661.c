// ������� ��� ������ � ���������� MCP4661




// ������������� ���� ��� ������ � RES
void MCP4661_Init( void )
{
          // ����� ����� ���� � ������� ����
	I2C_Init( RES_CH_I2C, RES_CLOCK_FREQ_I2C);

	  //(���������� ����� ���� � ������� ����� ��������, ����� � ������� �������� I2C, ��������� ������ ���� I2C ������� ������)
	I2C_Cmd( RES_CH_I2C, I2C_MASTER_MODE, ENABLE);

	return;
}


// ��������������� ���� ��� ������ � RES
void MCP4661_DeInit(void)
{
	  //������ ������ ���� ������� ������ I2C
	I2C_Cmd( RES_CH_I2C, I2C_MASTER_MODE, DISABLE);

	return;
}

///----------------------------------------------------------------------------------------------------------------------------///
///----------------------------------------------------------------------------------------------------------------------------///








  // �������� �� I2C ������ ��� ������
#define I2C_TRANSFER_OK         0
  // ��� �������� ������ �� I2C �������� ������
#define I2C_TRANSFER_FAIL       1
  // ������������ ����� ��� ���������� ������
#define ERR_LENGTH_DATA_0       2



// ����� I2C, ���������� ����� ��������� � �������� �������� ������, ���������� ����, ���� ������ ���������
//( uint32_t Res_add_I2C, uint8_t *Add_Start_Read, uint32_t rx_length_data, uint8_t *data )
  // ������� ������ ������� � ���������� �������
word GetData_fromAdd ( I2C_M_SETUP_Type *TransferCfg )
{

   if ( TransferCfg->rx_length == 0 || TransferCfg->tx_length == 0 ) return ERR_LENGTH_DATA_0 ;

     // ���� ���������� ������� ���������� � ���������� �� ������ ������� ���
   if ( TransferCfg->retransmissions_max == 0 ) TransferCfg->retransmissions_max = 3;

     // ���������� ������ �� I2C
   if ( I2C_MasterTransferData( RES_CH_I2C, TransferCfg, I2C_TRANSFER_POLLING ) == SUCCESS )
    {
     return I2C_TRANSFER_OK;
    }
   else
    {
     return I2C_TRANSFER_FAIL;
    }


}


  // ������� �������� ���������/����������� EEPROM ������� ��������� ��� ���������� � ������ � ���
  // (��������� ����� ������ ��� ������� ���������, ���������� ����� ���������� ������ �����. ������� ������)
uint32_t GetResistorSts( struct Res_Common *Res_chenel_in, uint8_t ResMemAdd_Read )
{

   I2C_M_SETUP_Type transferResStsReg;
   uint8_t ResStsReg_Adr_tx[1];
   uint8_t ResStsReg_Data_rx[2];
   word Ret = 0 ;

     // �������� ���������/����������� EEPROM ��� ���������� � ������ � ���
     // ���� ���������� � ������ �� EEPROM �������
   if ( ResMemAdd_Read == RES_WIPER_ROM || ResMemAdd_Read == RES_WIPER_EEP_COUNT_SAVE || ResMemAdd_Read == RES_WIPER_EEP_PAST_SAVE )
    {
       // ������� ���������� ����� ���������
     transferResStsReg.sl_addr7bit = MCP4661_adr | ((uint32_t)Res_chenel_in->ResConst.Add_channel & 0x07) ;
       // ������ ����� Status registra + ������� ������ �� ����
     ResStsReg_Adr_tx[0] = (uint8_t)(RES_STS_REG | RES_COMMAND_READ) ;
       // ��������� �������������� �������� ������ � �������
     transferResStsReg.tx_data = ResStsReg_Adr_tx ;
       // ���������� ������������ ���� � ������� � ������ ����������� (���������� ���� �� ��������� ������)
     transferResStsReg.tx_length = 1;
       // ��������� ���� ������ �������� ������
     transferResStsReg.rx_data = ResStsReg_Data_rx;
       // ���������� ����������� ���� � ������� � ������ ���������
     transferResStsReg.rx_length = 2;
       // ���������� ������� �������� ������
     transferResStsReg.retransmissions_max = 3;
       // ���������� ������ Status registra
    if ( GetData_fromAdd ( &transferResStsReg ) != I2C_TRANSFER_OK )
     {
        // ������ ���������� ������
        // ������ ������ I2C
 //     MCP4661_DeInit( );
      Ret = MCP4661_RETFUNC_FAILED ;
     }
    else
     {
      Res_chenel_in->Sts_Reg = (((w)ResStsReg_Data_rx[0] << 8) & 0x0100 ) | ((w)ResStsReg_Data_rx[1] & 0x00ff ) ;
        // �������� ������ �� ������� �����������/��������� EEPROM ���������
      if ( (Res_chenel_in->Sts_Reg & RES_EEPROM_BUSY) == 0 ) Ret = MCP4661_RET_EEPROM_OK ;
      else                                                   Ret = MCP4661_RET_EEPROM_BUSY;
     }
    }

return Ret ;

}



  // ������� �������� � ���������� ������
  // (��������� ����� ������ ��� ������� ���������, ���������� ����� ���������� ������ �����. ������� ������)
word GetResistorValue( struct Res_Common *Res_chenel_in, uint8_t ResMemAdd_Read )
{
   I2C_M_SETUP_Type transferMCfg;

   uint8_t data_tx[1];
   uint8_t data_rx[2];

     // ��������� ������ �� I2C
   MCP4661_Init( );

       // �������� ������� ��������� ��� ������/������ EEPROM (���� ������ ������� ��� ������� ���������� ���������� �� ����. �����)
   Res_chenel_in->Res_Err_Ret = GetResistorSts( Res_chenel_in, ResMemAdd_Read ) ;
   if ( ( Res_chenel_in->Res_Err_Ret == MCP4661_RET_EEPROM_BUSY ) || ( Res_chenel_in->Res_Err_Ret == MCP4661_RETFUNC_FAILED ) )
    {
      // ������� ������ � �������� ���� ��������� ����������
        // ������ ������ I2C
      MCP4661_DeInit( );
      return (w)Res_chenel_in->Res_Err_Ret ;
    }


   // ���������� ������ ��� ������ �� I2C

     // ��������� � ����� 1-�� ��� 2-�� ���������� ���� �������� (� ������� ���� ������ � ������)
   if ( Res_chenel_in->ResConst.Wiper_Num == 0 )
    {
       // � ����� ������� ������ ����� �������� + ������� ������ �� ��������� ������
     data_tx[0] = (uint8_t)( ResMemAdd_Read | RES_COMMAND_READ );
    }
   else
    {
       // � ����� ������� ������ ����� �������� + ������� ������ �� ��������� ������
     data_tx[0] = (uint8_t)(( ResMemAdd_Read + RES_MEM_ADD_WIPER1 ) | RES_COMMAND_READ) ;
   }

     // ������� ���������� ����� ���������
   transferMCfg.sl_addr7bit = MCP4661_adr | ((uint32_t)Res_chenel_in->ResConst.Add_channel & 0x07) ;
     // ��������� �������������� �������� ������ � �������
   transferMCfg.tx_data = data_tx ;
     // ���������� ������������ ���� � ������� � ������ ����������� (���������� ���� �� ���������� ������)
   transferMCfg.tx_length = 1;

     // ��������� ���� ������ �������� ������
   transferMCfg.rx_data = data_rx;
     // ���������� ����������� ���� � ������� � ������ ���������
   transferMCfg.rx_length = 2;
     // ���������� ������� �������� ������
   transferMCfg.retransmissions_max = 3;

// ���������� ������ �� I2C
   if ( GetData_fromAdd ( &transferMCfg ) != I2C_TRANSFER_OK )
    {
       // �� ���������� �������� ��������� ���� ����� �� ���������. ������ ���������� ������
       // ������ ������ I2C
     MCP4661_DeInit( );
     return MCP4661_RETFUNC_FAILED ;
    }
   else
    {
        // ��������� �������� ������
      if      ( ResMemAdd_Read == RES_WIPER_RAM )            Res_chenel_in->ResMemory.Res_RAM =        (((w)data_rx[0] << 8) & 0x0100 ) |
                                                                                                        ((w)data_rx[1] & 0x00ff ) ;
      else if ( ResMemAdd_Read == RES_WIPER_ROM )            Res_chenel_in->ResMemory.Res_ROM =        (((w)data_rx[0] << 8) & 0x0100 ) |
                                                                                                        ((w)data_rx[1] & 0x00ff ) ;
      else if ( ResMemAdd_Read == RES_WIPER_EEP_COUNT_SAVE ) Res_chenel_in->ResMemory.Count_Save =     (((w)data_rx[0] << 8) & 0x0100 ) |
                                                                                                        ((w)data_rx[1] & 0x00ff ) ;
      else if ( ResMemAdd_Read == RES_WIPER_EEP_PAST_SAVE )  Res_chenel_in->ResMemory.Past_Save =      (((w)data_rx[0] << 8) & 0x0100 ) |
                                                                                                        ((w)data_rx[1] & 0x00ff ) ;



          // ������ ������ I2C
      MCP4661_DeInit( );
      return MCP4661_RETFUNC_OK;
     }


}








///----------------------------------------------------------------------------------------------------------------------------///
///----------------------------------------------------------------------------------------------------------------------------///
  // �������� �������� � ��������� �����
  // (��������� ����� ������ ��� ������� ���������, ���������� ����� ���������� ���� �����. �������� ������)
word SetResistorValue(struct Res_Common *Res_chenel_in, uint8_t ResMemAdd_write   )
{

 //  uint8_t ResMemAdd[1] ;
   uint8_t data_write[2];
   I2C_M_SETUP_Type transferMCfg;

 //  I2C_M_SETUP_Type *TransferCfg;

    // ��������� ������ I2C
   MCP4661_Init( );

     // �������� ������� ��������� ��� ������/������ EEPROM (���� ������ ������� ��� ������� ���������� ���������� �� ����. �����)
   Res_chenel_in->Res_Err_Ret = GetResistorSts( Res_chenel_in, ResMemAdd_write ) ;

   if ( ( Res_chenel_in->Res_Err_Ret == MCP4661_RET_EEPROM_BUSY ) || ( Res_chenel_in->Res_Err_Ret == MCP4661_RETFUNC_FAILED ) )
    {
        // ������� ������ � �������� ���� ��������� ����������
        // ������ ������ I2C
      MCP4661_DeInit( );
      return (w)Res_chenel_in->Res_Err_Ret ;
    }

      // ���������� ������ ��� ������ ������ � ��������


      // ���������� ������������ ������
    data_write[0] = (uint8_t)(( Res_chenel_in->Res_data_write >> 8 ) & 0x01) ;
    data_write[1] = (uint8_t)(  Res_chenel_in->Res_data_write & 0x00ff );

      // ��������� � ������ ������ ��������� ���� ����������
   if ( Res_chenel_in->ResConst.Wiper_Num == 0 )
    {
       // � ����� ������� ������ ����� �������� + ������� �������� � ��������� ������ + � ���� ����� ���������� � 9 ��� ������
     data_write[0] |= (uint8_t)( ResMemAdd_write | RES_COMMAND_WRITE ) ;
    }
   else
    {
       // � ����� ������� ������ ����� �������� + ������� �������� � ��������� ������ + � ���� ����� ���������� � 9 ��� ������
     data_write[0] |= (uint8_t)(( ResMemAdd_write + RES_MEM_ADD_WIPER1 ) | RES_COMMAND_WRITE );
    }

     // ������� ���������� ����� ���������
   transferMCfg.sl_addr7bit = MCP4661_adr | ((uint32_t)Res_chenel_in->ResConst.Add_channel & 0x07) ;
     // ��������� �������������� �������� ������, ������� � 9-�� ���� ������
   transferMCfg.tx_data = data_write ;
     // ���������� ������������ ���� � ������� � ������ �����������
   transferMCfg.tx_length = 2;

     // ������� ��������� ��� ������ ���������� ������ I2C ����� ������
   transferMCfg.rx_data = NULL;
     // ���������� ����������� ���� � �������
   transferMCfg.rx_length = 0;
     // ���������� ������� �������� ������
   transferMCfg.retransmissions_max = 3;

  // ������� ������ � ��������, ���
   // I2C_MasterTransferData( ���������� ����� ����, ������, I2C_TRANSFER_POLLING: ������ ����� ������ ��� ����������)

	if ( I2C_MasterTransferData( RES_CH_I2C, &transferMCfg, I2C_TRANSFER_POLLING ) == SUCCESS )
	{
            // ������ ������ I2C
          MCP4661_DeInit( );
          return MCP4661_RETFUNC_OK;
	}
	else
	{
            // ������ ������ I2C
          MCP4661_DeInit( );
	  return MCP4661_RETFUNC_FAILED;
	}

//return 0;

}





//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//




        //4. ���� ����� ��������� ����� Enter:
        //   4.1 ��������� � RAM ������������� ��������
        //   4.2 ������� � ROM ������� �������� � �������� ��� � EEPROM � ����� "���������� ���������" ��������� ��� ��������
        //   4.3 �������� � ROM ������������ �������� � RAM
        //   4.4 ������������� ��� �������� � RAM � ROM ����������
        //   4.5 ������� �������� �� �������� ���� ��� >= 0xff ���������� � ���� 0x01 ����� ������ ���������
        //   4.6 ������� � ������, ��� �������� � �������� � ���, ��� ������ ��������


// ������� ����������� ����� �� ���� �����. ��������� �� Enter � ����������� ������ � ������ ���������

word SetResVal_Enter(struct Res_Common *Res_chenel_in )
{
                      // 0,  1,  2,   3,   4,   5,  6,    7,   8,   9,  10
           enum    { L0 = 0, L3, L5, L10, L12, L20, L22, L30, L32, L40, L42 };

  static   word    time ;
  static   word    Res_Label ;
  static   word    count_pov ;

             // ����������������� �����, ����� ����� ���������� �� return, ��������� �������������� ����� ������ � ������ �������
             // ���� ���� �� ����� �� ������� ������ ������ ��� ����������� ������ ������� ��� �� ��� ��� �� ���������
  register  word    Ret = MCP4661_RET_RECORD_NO_FINISH ;
  //         word    ax ;




  switch ( Res_Label )
    {
      default: Res_Label = L0 ;

      case L0:
        count_pov = 0 ;

//--------------------------------------------------------------------------------------------------------------------//
      case L3:

  //   4.2.1 ������� � ROM ������� ��������

               Res_chenel_in->Res_Err_Ret = GetResistorValue( Res_chenel_in, RES_WIPER_ROM );
               Ret = (w)Res_chenel_in->Res_Err_Ret ;
               time = timer1 ;
             ++count_pov ;
               Res_Label = L5 ;

       case L5:
         // �������� �� ������ ��� ��������� ��������� ��� ������/������ ������
               if ( Ret != ( MCP4661_RETFUNC_OK || MCP4661_RET_EEPROM_OK) )
                {
                  if ( Ret == MCP4661_RET_EEPROM_BUSY )
                   {
                     // ���� �������� ����� ���������� ��������� ������� ������� ������
                    if ( (u)(w)( timer1 - time ) <= _MkSec( 7*1000 ) )
                     {
                      break ;
                     }
                    else
                     {
                      Res_Label = L3 ;
                      if ( count_pov > 3 )
                      {
                       Res_Label = L0 ;
                         // ������� ���������� � ��������� ���������
                       Ret = MCP4661_RET_CONNECT_OVERFLOW ;
                       break ;
                      }
                     }
                   }
                  else  // ������ �� ������� ��� ������ ���� ������
                   {
                    Res_Label = L0 ;
                    break ;
                   }
               }


  // 4.2.2  �������� ��� � EEPROM � ����� "���������� ���������" ��������� ��� ��������
       case L10:
                 // ���������� ������ ��� ������ � ��������� �����
               Res_chenel_in->Res_data_write = Res_chenel_in->ResMemory.Res_ROM ;

                 // ������� ������
               Res_chenel_in->Res_Err_Ret = SetResistorValue( Res_chenel_in, RES_WIPER_EEP_PAST_SAVE );
               Ret = (w)Res_chenel_in->Res_Err_Ret ;
                 // �������� �� ������ �� ������� ��� ������ ���� ������
               if ( Ret == MCP4661_RETFUNC_FAILED )
                {
                 Res_Label = L0 ;
                 break ;
                }

               time = timer1 ;
               count_pov = 0 ;
               Res_Label = L12 ;
                 // ������ � �������� ������ 5-10 �� ������� �������. ���������� ������������ �������� - �� ����� ���� ������
               Ret = MCP4661_RET_RECORD_NO_FINISH ;
               break ;


        case L12:
                    // �� �������� ������� �� ���������� ������. � ������� 5 �� ��� ���������� �� ������ ����
                if ( (u)(w)( timer1 - time ) <= _MkSec( 7*1000 ) )
                 {
                    // �� ������ ����� ���������� ��� ������
                  break ;
                 }
                else
                 {

  // 4.2.3 ������� � ��������� ��� �������� � ����� "���������� ���������"
                   Res_chenel_in->Res_Err_Ret = GetResistorValue( Res_chenel_in, RES_WIPER_EEP_PAST_SAVE ) ;
                   Ret = (w)Res_chenel_in->Res_Err_Ret ;

                   if ( ( Ret == MCP4661_RET_EEPROM_BUSY ) || ( Ret == MCP4661_RETFUNC_FAILED  ) )
                    {
                        // ���� �������� ����� ���������� ��������� ������� ������� ������
                      time = timer1 ;
                      if ( ++count_pov > 3 )
                       {
                        Res_Label = L0 ;
                          // ������� ���������� � ��������� ���������
                        Ret = MCP4661_RET_CONNECT_OVERFLOW ;
                        break ;
                       }
                    }
                 }

 // 4.2.4 ������� ������ ������ ROM � EEPROM ���������� ��� "���������� ���������"
                  // � ������ ����� ROM � ������ �����. � EEPROM "����. ���." ������ ���� ����� �������� ���
                if ( Res_chenel_in->ResMemory.Past_Save == Res_chenel_in->ResMemory.Res_ROM )
                 {
                  Res_Label = L20 ;
                  // ������ �� ����������.  ����� ������� ���������� ������������ �������� - �� ����� ���� ������
                  Ret = MCP4661_RET_RECORD_NO_FINISH ;
                  break ;
                 }
                else
                 {
                    // ��������� ������ � ���������� ������ ������ ��� ������ ����
                  Ret = MCP4661_RET_DATA_FAILED ;
                  Res_Label = L0 ;
                  break ;
                 }


         case L20:

//------------------------------------------------------------------------------------------------------------------------------//
  // 4.3 �������� �� RAM �������� � ROM
                  // � ���������� ResMemory.Res_RAM ������� ��������� ��� ����� �������� �������� ��� ������ � ROM
                  // ���������� ������ � ���������

                  // ����� ������ �������� (�� ������� �������� ��������� ROM ����� ������)  ��� ������ ������ ��� ������� ����

  // 4.3.1 ���������� ������ ��� ������ � ��������� �����
                Res_chenel_in->Res_data_write = Res_chenel_in->ResMemory.Res_RAM ;

                  // ������� ������
                Res_chenel_in->Res_Err_Ret = SetResistorValue( Res_chenel_in, RES_WIPER_ROM );
                Ret = (w)Res_chenel_in->Res_Err_Ret ;
                  // �������� �� ������ �� ������� ��� ������ ���� ������
                if ( Ret == MCP4661_RETFUNC_FAILED )
                 {
                  Res_Label = L0 ;
                  break ;
                 }
                  //
                time = timer1 ;
                count_pov = 0 ;
                Res_Label = L22 ;
                 // ������ � �������� ������ 5-10 �� ������� �������. ���������� ������������ �������� - �� ����� ���� ������
                Ret = MCP4661_RET_RECORD_NO_FINISH ;
                break ;


         case L22:
                    // �� �������� ������� �� ���������� ������. � ������� 5 �� ��� ���������� �� ������ ����
                if ( (u)(w)( timer1 - time ) <= _MkSec( 7*1000 ) )
                 {
                    // �� ������ ����� ���������� ��� ������
                  break ;
                 }
                else
                 {

  // 4.3.2 ������� ������ �� ROM
                   Res_chenel_in->Res_Err_Ret = GetResistorValue( Res_chenel_in, RES_WIPER_ROM ) ;
                   Ret = (w)Res_chenel_in->Res_Err_Ret ;

                   if ( ( Ret == MCP4661_RET_EEPROM_BUSY ) || ( Ret == MCP4661_RETFUNC_FAILED  ) )
                    {
                        // ���� �������� ����� ���������� ��������� ������� ������� ������
                      time = timer1 ;
                      if ( ++count_pov > 3 )
                       {
                        Res_Label = L0 ;
                          // ������� ���������� � ��������� ���������
                        Ret = MCP4661_RET_CONNECT_OVERFLOW ;
                        break ;
                       }
                    }
                 }

  // 4.4 ������������� ��� �������� � RAM � ROM ����������
                if ( Res_chenel_in->ResMemory.Res_RAM == Res_chenel_in->ResMemory.Res_ROM )
                 {
                  Res_Label = L30 ;
                  count_pov = 0 ;
                    // ������ �� ����������. ����� ������� ���������� ������������ �������� - �� ����� ���� ������
                  Ret = MCP4661_RET_RECORD_NO_FINISH ;
                  break ;
                 }
                else
                 {
                    // ��������� ������ � ���������� ������ ������ ��� ������ ����
                  Ret = MCP4661_RET_DATA_FAILED ;
                  Res_Label = L0 ;
                  break ;
                 }

 //------------------------------------------------------------------------------------------------------------------------------//

           case L30:
  // 4.5 ������� �������� �� �������� ���� ��� >= 0xff ���������� � ���� 0x01 ����� ������ ���������

                // ���������������� ����� ������ �������� (�� ������� �������� ��������� ROM ����� ������)  ��� ������ ������ ��� ������� ����

                Res_chenel_in->Res_Err_Ret = GetResistorValue( Res_chenel_in, RES_WIPER_EEP_COUNT_SAVE );
                Ret = (w)Res_chenel_in->Res_Err_Ret ;
                time = timer1 ;
                Res_Label = L32 ;


           case L32:

                  // �������� �� � ������ ��� ��������� ��������� ��� �����
                if ( Ret != ( MCP4661_RETFUNC_OK || MCP4661_RET_EEPROM_OK) )
                 {
                   if ( Ret == MCP4661_RET_EEPROM_BUSY )
                    {
                      // ���� �������� ����� ���������� ��������� ������� ������� ������
                     if ( (u)(w)( timer1 - time ) <= _MkSec( 7*1000 ) )
                      {
                       break ;
                      }
                     else
                      {
                       Res_Label = L30 ;
                       if ( ++count_pov > 3 )
                       {
                        Res_Label = L0 ;
                          // ������� ���������� � ��������� ���������
                        Ret = MCP4661_RET_CONNECT_OVERFLOW ;
                        break ;
                       }
                      }
                    }
                   else  // ������ �� ������� ��� ������ ���� ������
                    {
                     Res_Label = L0 ;
                     break ;
                    }
                }
                  // ��-�� ���� ��� � EEPROM �� ������ ������ �������� 0x00FF, � ����� _RES_setka_max = 0x0100
                  // ���� ��� ������ ������ � ������ ������ �������� 1 ���������� ������� ( _RES_setka_max - 1 )
                if ( Res_chenel_in->ResMemory.Count_Save >= ( _RES_setka_max - 1 )  )
                     Res_chenel_in->ResMemory.Count_Save = 1 ;
                  // ������������ �� �����
                else Res_chenel_in->ResMemory.Count_Save++  ;

                Res_Label = L40 ;

                  // ����� ������� ���������� ������������ �������� - �� �������� ���� ������
                Ret = MCP4661_RET_RECORD_NO_FINISH ;
                break ;


           case L40:

             //------------------------------------------------------------------------------------------------------------------------------//
  // 4.6 ������� � ������, ��� �������� � �������� � ���, ��� ������ ��������
                  // � ���������� ResMemory.Count_Save ������� ��������� ��� ����� �������� �������� ��� ������ � Count_Save
                  // ���������� ������ � ���������

  // 4.6.1 ���������� ������ ��� ������ � ����� ��������
                Res_chenel_in->Res_data_write = Res_chenel_in->ResMemory.Count_Save ;

                  // ������� ������
                Res_chenel_in->Res_Err_Ret = SetResistorValue( Res_chenel_in, RES_WIPER_EEP_COUNT_SAVE );
                Ret = (w)Res_chenel_in->Res_Err_Ret ;
                  // �������� �� ������ �� ������� ��� ������ ���� ������
                if ( Ret == MCP4661_RETFUNC_FAILED )
                 {
                  Res_Label = L0 ;
                  break ;
                 }
                  //
                time = timer1 ;
                count_pov = 0 ;
                Res_Label = L42 ;
                  // ������ � �������� ������ 5-10 �� ������� �������
                  // ����� ������� ���������� ������������ �������� - �� ����� ���� ������
                Ret = MCP4661_RET_RECORD_NO_FINISH ;
                break ;


         case L42:
                    // �� �������� ������� �� ���������� ������. � ������� 5-10 �� ��� ���������� �� ������ ����
                if ( (u)(w)( timer1 - time ) <= _MkSec( 7*1000 ) )
                 {
                    // �� ������ ����� ���������� ��� ������
                  break ;
                 }
                else
                 {

  // 4.6.2 ������� ������ �� Count_Save
                   Res_chenel_in->Res_Err_Ret = GetResistorValue( Res_chenel_in, RES_WIPER_EEP_COUNT_SAVE ) ;
                   Ret = (w)Res_chenel_in->Res_Err_Ret ;

                   if ( ( Ret == MCP4661_RET_EEPROM_BUSY ) || ( Ret == MCP4661_RETFUNC_FAILED  ) )
                    {
                        // ���� �������� ����� ���������� ��������� ������� ������� ������
                      time = timer1 ;
                      if ( ++count_pov > 3 )
                       {
                        Res_Label = L0 ;
                          // ������� ���������� � ��������� ���������
                        Ret = MCP4661_RET_CONNECT_OVERFLOW ;
                        break ;
                       }
                    }
                 }

  // 4.6.3 ������������� ��� �������� �� ������ Count_Save� ����� � ��� ��� ������ ��������
                if ( Res_chenel_in->ResMemory.Count_Save == Res_chenel_in->Res_data_write )
                 {
                    // �������� �����
                  Ret = MCP4661_RET_DATA_OK ;
                  Res_Label = L0 ;
                  count_pov = 0 ;
                  break ;
                 }
                else
                 {
                    // ��������� ������ � ���������� ������ ������ ��� ������ ����
                  Ret = MCP4661_RET_DATA_FAILED ;
                  Res_Label = L0 ;
                  break ;
                 }

    }



  // ���� �� ����� �� ������
return Ret ;

}




// ������� ����������� ����������� ���������� ������ � ��������� ��� ������ � ����, ���� �� ����������� ����� ��� ��� ���� 
//         ��������� �������� � I2C � �� �� ������ � while �� ��������� ������� � ustavki.c

word GetResVal_Start(struct Res_Common *Res_chenel_in, word num )
{
                      // 0,  1,  2,   3   
           enum    { L0 = 0, L3, L5, L10 };

  static   word    time ;
  static   word    Res_Label ;
  static   word    count_pov ;
  static   word    count_mem ;
  static   word    ax ;
  static   word    Start_FirstCall ;

             // ����������������� �����, ����� ����� ���������� �� return, ��������� �������������� ����� ������ � ������ �������
             // ���� ���� �� ����� �� ������� ������ ������ ��� ����������� ������ ������� ��� �� ��� ��� �� ���������
  register  word    Ret = MCP4661_RET_RECORD_NO_FINISH ;


  if ( num == 0 )
   {
     Start_FirstCall = 0 ;
     count_mem = 0 ;
     Res_Label = 0  ;
     ax = 0 ;
     return 0;
   }


 if ( Start_FirstCall == 0 )
 {

  switch ( Res_Label )
    {
      default: Res_Label = L0 ;

      case L0:
        count_pov = 0 ;

//--------------------------------------------------------------------------------------------------------------------//
      case L3:

        //   ������� �� ������� � ������������ ��� 4-�� ����� ������ �������� ��� ������� ���������: RAM, ROM, EEPROM ������� ���., EEPROM ����. ���������)
               if      ( count_mem == 0 ) Res_chenel_in[ ax ].Res_Err_Ret = GetResistorValue( &Res_chenel_in[ ax ], RES_WIPER_RAM );
               else if ( count_mem == 1 ) Res_chenel_in[ ax ].Res_Err_Ret = GetResistorValue( &Res_chenel_in[ ax ], RES_WIPER_ROM );
               else if ( count_mem == 2 ) Res_chenel_in[ ax ].Res_Err_Ret = GetResistorValue( &Res_chenel_in[ ax ], RES_WIPER_EEP_COUNT_SAVE );
               else if ( count_mem == 3 ) Res_chenel_in[ ax ].Res_Err_Ret = GetResistorValue( &Res_chenel_in[ ax ], RES_WIPER_EEP_PAST_SAVE );

               Ret = (w)Res_chenel_in->Res_Err_Ret ;
               time = timer1 ;
             ++count_pov ;
               Res_Label = L5 ;

       case L5:
         // �������� �� ������ ��� ��������� ��������� ��� ������/������ ������
              if ( Ret != ( MCP4661_RETFUNC_OK || MCP4661_RET_EEPROM_OK) )
               {
                 // ���� �������� ����� ��� �� ���������� ���������� ��������� ������� ������� ������
                if ( (u)(w)( timer1 - time ) <= _MkSec( 7*1000 ) )
                 {
                  break ;
                 }
                else
                 {

                  if ( count_pov > 3 )
                   {
                      // ������� ���������� � ������� ������ ������ ��������� ���������
                    Ret = MCP4661_RET_CONNECT_OVERFLOW ;
                    mSet_ServiceMsg2 ( _Srv2_FailReadRes ) ;
                       // �� ������� ����� ��������� �������� ��������� ������ ������ �������� ��������� 
                    if ( ++count_mem >= 4 )
                     {
                        // �������� � ������ ���������� ���������
                      ++ax ;
                      count_mem = 0 ;
                     }
                    
                    Res_Label = L0 ;
                    
                   }
                  else Res_Label = L3 ;
                  
                  break ;
                 }
               }
              else
               {
                if ( ++count_mem >= 4 )
                 {
                  ++ax ;
                  count_mem = 0 ;
                 }
                
                Res_Label = L0 ;
                break ;
               }

              break ;

    }

 }
  // ����� ���������� ������. ��������� ����������� ������ ���������� ������ � ����������.
if ( ax >= _RES_Ntab ) Start_FirstCall = 1 , ax = 0 ;

  // ���� �� ����� �� ������
return Ret ;

}







