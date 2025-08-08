#ifndef _CM3_

void Init_RS( void )
{

   word speed = 0, mode = 0;

   flag_newdata = 0;

   In_RS485 = 0;
   Out_RS485 = 0;

   speed = _r.net_spd.all;
   mode  = _r.net_setting.all;

   WRITE_NET( DR_CR, DR_CR_SLAVE );
   WRITE_NET( DR_SPEED, speed );
   WRITE_NET( DR_MODE, mode );

   WRITE_NET( DR_TLIFE, _r.Net_LT ); // 10 ms

//   инициализация прерывания
   ENIR_EN1 = 0;
   ELVR_LAB1 = Low;//Falling;
   EIRR_ER1 = 0;                         // 1111 1101
   ENIR_EN1 = 1;
   ICR01 = 24;


   WRITE_NET( DR_TLIFE, _r.Net_LT ); // 10 ms
   inet = (w)(/*DR_ISR_SF | DR_ISR_LT |*/ DR_ISR_ND) ;
   WRITE_NET( DR_IER,  inet );

  inet = (w)(DR_CR_START | DR_CR_LOAD) ;
  WRITE_NET( DR_CR, inet ) ;
  Timer_Rec1 = timer1;
  Timer_Send1 = 0;
}


word Work_RS( byte flag )
{
   word length, err;

  if ( flag_newdata == 1 )
  {
	  Timer_Rec = Timer_Rec1 - timer1;
	  Timer_Rec1 = timer1;
	  flag_newdata = 0;
// Читаем данные
//      READ_NET( length, DR_DLI ) ;

      READ_NET( In_RS485, DR_DI ) ;
	  *(w*)var_tab1[_r.Num_RS485_In].addr = In_RS485 ;

      WRITE_NET( DR_CR, DR_CR_CBI );
  }

//  length = modbus_slave( rmb, &smb );

  if ( flag == _FLAGNET_SEND )
  {
// Записываем данные
	  flag = _FLAGNET_NO ;
      length  = 1 ;
//      WRITE_NET( DR_DLO , length ) ;

	  Out_RS485 = *(w*)var_tab1[_r.Num_RS485_Out].addr ;
      WRITE_NET( DR_DO, Out_RS485 ) ;

      WRITE_NET( DR_CR, DR_CR_CBO );
  }

  READ_NET( err, DR_ERROR);
  return err;
}

#else // _CM3_

void Init_RS( void )
{
}

word Work_RS( byte flag )
{
  return 0;
}

#endif // _CM3_

