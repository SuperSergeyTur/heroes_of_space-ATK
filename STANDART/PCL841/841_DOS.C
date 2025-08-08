  // Для совместимости отсчета задержки BorlandC c CBuilder.
void Sleep( short time )
{
  delay ( time ) ;
  return ;
}

//---------------------------------------------------------------------------

word canSend( byte  port, struct canMSG_hw *send_msg)
{
  MSG_STRUCT  msg_dos ;
  word i ;
         //  Приведение ID от общего вида к виду PCL841.
  msg_dos.id     = (w)(send_msg->id >> (5+16)) ;
  msg_dos.rtr    = 0 ; //22.04.03 11:39send_msg->cfg.dir ^ 1;
  msg_dos.dlen   = send_msg->cfg.dlen;
  for (i=0; i<8; i++) msg_dos.data[i] = send_msg->data[i];

  i = canSendMsg( port, msg_dos );
  if ( i == 0 )
  {
    can_dd[port].Error_send++ ;//06.01.05 10:37
    i = 1 ;
  }
  else  i = 0 ;

  return i;
}

//---------------------------------------------------------------------------
word canReceive( byte  port, struct canMSG_hw *rec_msg)
{
  MSG_STRUCT  msg_dos;
  word i, ax;

  ax = canReceiveMsg( port, &msg_dos);
  if ( ax == 1 )
  {
         //  Приведение ID от вида PCL841 к общему виду.
    rec_msg->id = (lw)msg_dos.id << (5+16) ;
    rec_msg->cfg.dlen =  msg_dos.dlen;
    //22.04.03 11:40rec_msg->cfg.dir  =  msg_dos.rtr ^ 0x01;
    for ( i = 0 ; i < 8 ; i++ ) rec_msg->data[i] = msg_dos.data[i];
  }

  return ax;
}
