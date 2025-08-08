//Программа усреднения измеренного значения
void Usrednitel( Usrednit_Str  *usr, byte label)
{
  enum {i0,i1, i2};
  word ax;
  switch ( label )
  {
    case i0 :
              //Запускаем измерения
              usr->in = _AD_BUSY;
              mAD_Izm (  *usr->ach  , &usr->in ) ;
              //usr->label = i2;
              break;
    case i1:
              //Измеренные значения суммируются
              while (usr->in == _AD_BUSY);

                ax = timer1 - usr->time1;
                if ((u)ax > _MkSec(2000)  )
                {
                  usr->time1 += _MkSec(2000);
                  ax = 0;
                  mIzmData_Conversion ( usr->in , ax  , *usr->ach  ) ;
                  //Если задано усреднение модуля
                  if ( usr->mod == 1 )
                  {
                    if ( (sw)ax < 0 )  ax = ~ax+1;
                  }
                  usr->sum +=(sw)ax;
                  ++usr->n;
                  //usr->label = i1;
                }
              break;
    case i2 :
             // mUSEL_clr() ;

              while (usr->in == _AD_BUSY);

              //mUSEL_set() ;

              //Измеренные значения суммируются
             /* if ( usr->in != _AD_BUSY)
              {
                ax = timer1 - usr->time1;
                if ((u)ax > _MkSec(2000)  )
                {
                  usr->time1 = timer1;
                  ax = 0;*/
                  mIzmData_Conversion ( usr->in , ax  , *usr->ach  ) ;
                  //Если задано усреднение модуля
                  if ( usr->mod == 1 )
                  {
                    if ( (sw)ax < 0 )  ax = ~ax+1;
                  }
                  usr->sum +=(sw)ax;
                  ++usr->n;
                 // usr->label = i1;
                //}
              //}
              //Запускаем измерения
              usr->in = _AD_BUSY;
              mAD_Izm (  *usr->ach  , &usr->in ) ;
              break;
  }

  ax = timer1 - usr->time;

  //По истечении заданного промежутка вычисляем усредненное значение
  //т.е делим сумму на число измерений
  if ((u)ax>= usr->dT )
  {
    usr->time = timer1;
    usr->time1 = usr->n;
    if ( usr->n == 0 ) ax = 1;
    else ax = usr->n;
    *usr->out = (slw)usr->sum/(sw)ax;
    usr->sum = 0;
    usr->n = 0;
  }

}
