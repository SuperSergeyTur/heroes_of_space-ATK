

      //   Если надо настроить capture-EPA под какую-то новуюфункцию.
      //  то следует добавить в этот файл новую функцию со своим именем и
      //  соответствующими настройками.

      //   Настройка заданного канала capture-EPA под прием
      //  синхронизации.
word init_syn_epa( word channel )
{
  if     ( channel == _ICS0 ) ICS01 = _CAP0_NEG_EDGE ;
  else if( channel == _ICS1 ) ICS01 = _CAP1_NEG_EDGE ;
  else if( channel == _ICS2 ) ICS23 = _CAP2_NEG_EDGE ;
  else if( channel == _ICS3 ) ICS23 = _CAP3_NEG_EDGE ;
  return 0;
}
