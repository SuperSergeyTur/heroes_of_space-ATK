/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
      //   Переключение длины и скважности ИУ.
      //
void Short_ImpLong ( void )
{
  if( Id >= _r.Id_null )
  {
      //   При наличии тока ИУ задаются короткими с низкой скважностью.
    if ( _r_V_ImpLong != _r.V_ImpLong )
    {
      _r_V_ImpLong = _r.V_ImpLong ;
      mSet_Fzapoln( _FzapolnShort_Low, _FzapolnShort_High ) ;
  } }
  else
  {
      //   При отсутсвии тока ИУ задаются длинными с большой скважностью.
    if ( _r_V_ImpLong != _Grad(120)  )
    {
      _r_V_ImpLong = _Grad(120) ;
      mSet_Fzapoln( _FzapolnLong_Low, _FzapolnLong_High ) ;
  } }

  return ;
}

