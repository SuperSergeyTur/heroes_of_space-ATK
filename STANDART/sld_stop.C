//Остановка следа
void Cond_Sled_Stop (void)
{
  if (Sled_Cond_cont(&_r.Stop_cond) == 1 )
  { //Домножаем на _fSec(0.001)  чтобы получить значение в милисекундах, т.к. надо передавать
    //значение уставки в Link, то лучше ее нормировать тут, а не передавать нормировку по UART
    if ( (u)((w)(Timer1_fSec - TimeFiltr_Stop)) > (_r.FiltrTime_Stop*_fSec(0.001)) )
    {
        sl_cond_old |= 0x1;
    }
  }
  else
  {
    TimeFiltr_Stop = Timer1_fSec;
  }

  if (( sl_cond_old & 0x1 ) != 0)
  {
    if ((u)((w)(Timer1_fSec -  TimeDelay_Stop)) > (_r.DelayTime_Stop*_fSec(0.001)) )
    {
        Prg._.Sled = 0 ; //sl_d.Stop = 2; //Для возможности запуска из линка.
        sl_cond_old &= 0xfffe;
    }
  }
  else
  {
    TimeDelay_Stop = Timer1_fSec;
  }
  return ;
}
//Пуск следа
void Cond_Sled_Start (void)
{
  if ( Sled_Cond_cont(&_r.Start_cond) == 1 )
  {
    if ( (u)((w)(Timer1_fSec - TimeFiltr_Start)) > (_r.FiltrTime_Start*_fSec(0.001)) )
    {
        sl_cond_old |= 0x2;
    }

  }
  else
  {
    TimeFiltr_Start = Timer1_fSec;
  }

    if ( ( sl_cond_old & 0x2 ) != 0)
    {
        if ((u)((w)(Timer1_fSec -  TimeDelay_Start)) > (_r.DelayTime_Start*_fSec(0.001)) )
        {
            Prg._.Sled = 1 ; //sl_d.Stop = 0;
            sl_cond_old &= 0xfffd;
        }
    }
    else
    {
        TimeDelay_Start = Timer1_fSec;
    }
  return ;
}
//Подпрограмма определения выполнения условий, заданных структурой sled_cond
word Sled_Cond_cont (struct sled_cond* in)
{
    word ax, bx ;

    bx = 0;

    if ( !in->bits._.enable) return bx;
    if (FullSledTab[in->numb].code._.off_sign ) ax = *(w*)FullSledTab[in->numb].addr;
    else ax = (sw)(*(w*)FullSledTab[in->numb].addr);

    //Если задана битовая переменная - выделяем бит
    if (in->bits._.type ) ax = (ax>>in->bits._.bit)&0x01;
    switch (in->bits._.cond )
    {
        case 0: //равно
                 if (ax ==  in->mean) bx  = 1;
                 break;
        case 1: //меньше
                if (FullSledTab[in->numb].code._.off_sign )
                {
                 if ((w)ax <  (w)in->mean) bx  = 1;
                }
                else if ((sw)ax <  (sw)in->mean) bx  = 1;

                 break;
        case 2: //больше
                if (FullSledTab[in->numb].code._.off_sign )
                {
                   if ((w)ax >  (w)in->mean) bx  = 1;
                }
                else if ((sw)ax >  (sw)in->mean) bx  = 1;
                 break;
    }
return bx;

}
//Задание условий пуска/остановки следа с пультика
void Sled_Cond_sel (void)
{
   byte aaa_sig;

   word ax, bx, cx, ex;

   lword lax;
   enum {k0, k1, k2, k3, k4, k5, k6,k63, k65, k7,k73, k75, k8,k83, k85, k9,k93, k95, k10, k101, k105,
         k11,k113, k115, k12, k123, k125, k13, k133, k135  };


              //  Контроль пароля: Полный запрет входа.

      if ( Password_control ( 2 ) == 0 )  return   ;
              //---


    if ( M_FirstCall == 1 )  /*  Идентификация первого входа для задания  */
    {                      /* начального условия ...                    */
        M_FirstCall = 0 ;
        Label = k0 ;
        m_index = 0 ;
        m_addr  = 0 ;
        output_s ( _Scond_prompt ) ;
        output_c ( '\n' ) ;
        //Label = k1;
        return ;
    }

    switch (Label )
    {
       case k0:
              if (  TestCompleted_Output() )
                {
      case k3:    output_c( '\r');
                  output_s( AWelcome );
                  output_s (Sld_Start_Stop[m_index]  ) ;
                  Label = k2 ;
                  break ;
                }
       case k2:
                if (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return)
                  {
                      output_c ( '\n' ) ;
                      Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                      return ;   // добавить еще какую-то иниц.
                  }
                  else if ( m_ch == Down)
                  {
                    if ( ++m_index > 1) m_index = 0;
                    Label = k3;
                  }
                  else if ( m_ch == Up)
                  {
                    if ( (sw)(--m_index) < (sw)0) m_index = 1;
                    Label = k3;
                  }
                  else if (m_ch == Enter )
                  {
                     if ( m_index == 0)
                     {
                        adr_m_tmp   = &_r.Stop_cond ;
                        adr_t_delay = &_r.DelayTime_Stop;
                        adr_f_delay = &_r.FiltrTime_Stop;

                     }
                     else
                     {
                        adr_m_tmp   = &_r.Start_cond ;
                        adr_t_delay = &_r.DelayTime_Start;
                        adr_f_delay = &_r.FiltrTime_Start;
                     }
                     output_c ( '\n' ) ;
                    output_c( '\r');
                    output_s( AWelcome );
                    output_s (Sld_Name[m_addr]) ;
                    Label = k5 ;
                  }
                  else
                  {
                     Klav_Buff = m_ch;
                  }

                }
                if ( AWelcome != AWell_old )
                {
                  AWell_old = AWelcome;
                  Label = k1;
                }
                break;
       case k4:
              if (  TestCompleted_Output() )
                {
                  output_c( '\r');
                  output_s( AWelcome );
                  output_s (Sld_Name[m_addr]) ;
                  Label = k5 ;
                  break ;
                }
       case k5:
                if (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return)
                  {
                      output_s ( _Scond_prompt ) ;
                      output_c ( '\n' ) ;
                      m_addr = 0;
                      Label = k3;
                  }
                  else if ( m_ch == Down)
                  {
                    if ( ++m_addr > 7) m_addr = 0;
                    if (adr_m_tmp->bits._.type )
                    {
                        if ( m_addr == 3) m_addr = 4;
                    }
                    else if (m_addr == 2 ) m_addr = 3;
                    Label = k4;
                  }
                  else if ( m_ch == Up)
                  {
                    if ( (sw)(--m_addr) < (sw)0) m_addr = 7;
                    if (adr_m_tmp->bits._.type )
                    {
                        if ( m_addr == 3) m_addr = 2;
                    }
                    else if (m_addr == 2 ) m_addr = 1;
                    Label = k4;
                  }
                  else if (m_ch == Enter )
                  {
                    output_c ( '\n' ) ;
                    switch (m_addr )
                    {
                        case 0:
                               m_ext = adr_m_tmp->numb;
                               Label = k63;

                               break;
                        case 1:
                               m_ext = adr_m_tmp->bits._.type;
                               Label = k73;
                               break;
                        case 2:
                               m_ext = adr_m_tmp->bits._.bit;
                               Label = k83;
                               break;
                        case 3:
                               m_ext = adr_m_tmp->bits._.cond;
                               Label = k93;
                               break;

                        case 4:
                               m_ext = adr_m_tmp->mean;
                               if (adr_m_tmp->bits._.type == 0 )
                               {

                                if (FullSledTab[adr_m_tmp->numb].code._.drob == 0 )
                                {
                                    ax = FullSledTab[adr_m_tmp->numb].nom / *FullSledTab[adr_m_tmp->numb].abs_nom;
                                }
                                else
                                {
                                    ax = FullSledTab[adr_m_tmp->numb].nom ;
                                    for (bx=0;bx< FullSledTab[adr_m_tmp->numb].code._.drob; ++bx )
                                    {
                                        ax/=10;
                                    }
                                    ax /= *FullSledTab[adr_m_tmp->numb].abs_nom;
                                }

                                if ( ax == 0 ) m_time = 1;
                                else m_time = ax;
                                if (FullSledTab[adr_m_tmp->numb].code._.type == 0 )
                                {
                                    if (FullSledTab[adr_m_tmp->numb].code._.off_sign == 0 )
                                    {
                                        sld_max = 0x7f;
                                        sld_min = 0x80;
                                    }
                                    else
                                    {
                                        sld_max = 0xff;
                                        sld_min = 0;
                                    }
                                }
                                else
                                {
                                    if (FullSledTab[adr_m_tmp->numb].code._.off_sign == 0 )
                                    {
                                        sld_max = 0x7fff;
                                        sld_min = 0x8000;
                                    }
                                    else
                                    {
                                        sld_max = 0xffff;
                                        sld_min = 0;
                                    }
                                }
                               }
                               else
                               {
                                 m_time = 1;
                                 sld_max = 1;
                                 sld_min = 0;
                                 if (m_ext > 1) m_ext = 1;
                               }
                               Label = k10;
                               break;

                        case 5:
                               adr_delay = adr_t_delay;
                               m_ext =  *adr_delay;
                               Label = k12;
                               break;
                        case 6:
                               adr_delay = adr_f_delay;
                               m_ext =  *adr_delay;
                               Label = k12;
                               break;
                        case 7:
                               m_ext = adr_m_tmp->bits._.enable;
                               Label = k113;
                               break;
                    }


                  }
                  else
                  {
                     Klav_Buff = m_ch;
                  }

                }
                if ( AWelcome != AWell_old )
                {
                  AWell_old = AWelcome;
                  Label = k4;
                }
                break;

       case k6:   //Выбор переменной
              if (  TestCompleted_Output() )
                {
       case k63 :
                  output_c( '\r');
                  output_s( AWelcome );
                  output_s (FullSledTab[m_ext].txt) ;
                  Label = k65 ;
                  break ;
                }
       case k65 :
                 ax = Key_tst(0, FullSledTab_size, k6, 1);

                 if (ax != 0 )
                 {
                   if ( ax == 1) adr_m_tmp->numb = m_ext;

                   output_c ( '\n' ) ;
                   output_c( '\r');
                   output_s (Sld_Start_Stop[m_index]  ) ;
                   output_c ( '\n' ) ;
                   Label = k4;

                 }
                break;

       case k7:  //Выбор типа переменной
              if (  TestCompleted_Output() )
                {
       case k73:
                  output_c( '\r');
                  output_s( AWelcome );
                  output_s (Sld_type[m_ext]) ;
                  Label = k75 ;
                  break ;
                }
       case k75:
                 ax = Key_tst(0, 2, k7, 1);

                 if (ax != 0 )
                 {
                   if ( ax == 1)
                   {
                    if (m_ext == 1) adr_m_tmp->bits._.cond = 0;
                    adr_m_tmp->bits._.type = m_ext;
                   }
                   output_c ( '\n' ) ;
                   output_c( '\r');
                   output_s (Sld_Start_Stop[m_index]  ) ;

                   output_c ( '\n' ) ;


                   Label = k4;

                 }
                break;
       case k8:  //Номер бита
              if (  TestCompleted_Output() )
                {
       case k83 :
                  output_c( '\r');
                  output_s( AWelcome );
                  ax = m_ext/10;
                  if ( ax == 0 ) output_c(' ');
                  else  output_c ( (b)ax + 0x30 ) ;
                  ax = m_ext%10;
                  output_c ( (b)ax + 0x30 ) ;
                  Label = k85;
                  break ;
                }
       case k85:
                 if (FullSledTab[adr_m_tmp->numb].code._.type == 1 )  ax = Key_tst(0, 8, k8, 0);
                 else ax = Key_tst(0, 16, k8, 0);

                 if (ax != 0 )
                 {
                   if ( ax == 1) adr_m_tmp->bits._.bit = m_ext;

                   output_c ( '\n' ) ;
                   output_c( '\r');
                   output_s (Sld_Start_Stop[m_index]  ) ;
                   output_c ( '\n' ) ;
                   Label = k4;

                 }
                break;
       case k9: //Условия пуска(остановки)
              if (  TestCompleted_Output() )
                {
       case k93 :
                  output_c( '\r');
                  output_s( AWelcome );
                  output_s (Sld_cond[m_ext]) ;
                  Label = k95 ;
                  break ;
                }
       case k95:
                 ax = Key_tst(0, 3, k9, 1);

                 if (ax != 0 )
                 {
                   if ( ax == 1) adr_m_tmp->bits._.cond = m_ext;

                   output_c ( '\n' ) ;
                   output_c( '\r');
                   output_s (Sld_Start_Stop[m_index]  ) ;
                   output_c ( '\n' ) ;
                   Label = k4;

                 }
                break;
       case k101 :
              if (  TestCompleted_Output() )
                {
       case k10: //значение условия.

                  output_c( '\r');
                  output_s( AWelcome );
                  ax = m_ext;
                  aaa_sig = '+' ;
                  if ( FullSledTab[adr_m_tmp->numb].code._.off_sign == 0 )
                  {
                    if ( (sw)ax < 0 )  ax = ~ax + 1 , aaa_sig = '-' ;
                  }

                  bx = FullSledTab[adr_m_tmp->numb].nom;
                  lax = *FullSledTab[adr_m_tmp->numb].abs_nom;
                  lax *= ax;
                  *(w*)&m_buff[3] = lax%bx  ;    //сохраняем остаток.
                  *(w*)&m_buff[0] = bx;
                   lax /= bx;

                  if (FullSledTab[adr_m_tmp->numb].code._.type == 1 )
                  {
                    if ( lax > 0xff) lax = 0xff;
                  }
                  else if (lax > 0xffff) lax = 0xffff;

                  ex = 5 - FullSledTab[adr_m_tmp->numb].code._.celoe ; //сколько первых символов пропустить
                  if ( ex == 5 ) ex = 2 ; // для совместимости - если заданы были нули то принимаем формат "3.2".
                  else if ( (sw)ex < 0 ) ex = 0 ;

                  for ( ax = 10000, cx = 0 ; ax != 1 ; ax /= 10 )
                    {
                        bx =  lax/ax  ;
                        lax %=ax ;
                            // пока идут первые нули - не выводим их:
                        if ( bx == 0 && cx == 0 )
                        {     // а пропускаем лишние нулевые символы,
                            if ( ex != 0 ) ex-- ;
                                // или заменяем пробелами.
                            else  output_c (' ') ;
                        }
                        else
                        {
                            if ((cx == 0) && ( FullSledTab[adr_m_tmp->numb].code._.off_sign == 0 )  )   output_c ( aaa_sig ) ;
                            cx = 1 ; // первые нули закончились.
                            output_c ( (b)bx + 0x30 ) ;
                        }
                    }

                    if ((cx == 0) && (FullSledTab[adr_m_tmp->numb].code._.off_sign == 0  )  )   output_c ( aaa_sig ) ;
                    // распечатываем последнюю цифру.
                    output_c ( (b)(w)lax + 0x30 ) ;
                    // распечатка дробной части
                    if  (FullSledTab[adr_m_tmp->numb].code._.celoe == 0)
                    {
                        ex = 2 ;
                    }
                    else ex = FullSledTab[adr_m_tmp->numb].code._.drob ;
                    if (adr_m_tmp->bits._.type ) ex = 0;
                    if ( ex != 0 )
                    {
                        output_c ( '.' ) ;
                        bx = *(w*)&m_buff[0] ;
                        lax =*(w*)&m_buff[3]  ; // восстанавливаем остаток.
                        for ( ; ex != 0 ; ex-- )
                        {
                            ax = lax*10  ;
                            lax = ax % bx         ;
                            ax /= bx;
                            output_c ( (b)(w)ax + 0x30 ) ;
                        }
                    }
                   output_c ( ' ') ;
                   output_s ( FullSledTab[adr_m_tmp->numb].txt2 ) ;
                   Label = k105;
                   break;
                }
       case k105:
                if (  TestData_for_Input() )
                {
                    mInput_c ( m_ch ) ;
                    if ( m_ch == Return)
                    {
                        output_c ( '\n' ) ;
                        output_c( '\r');
                        output_s (Sld_Start_Stop[m_index]  ) ;
                        output_c ( '\n' ) ;
                        Label = k4;
                    }
                    else if ( m_ch == Down)
                    {
                        cx = m_ext;
                        m_ext -= m_time;

                        if (FullSledTab[adr_m_tmp->numb].code._.off_sign == 0 )
                        {
                          if ( (sw)m_ext > (sw)cx) m_ext = sld_min;
                          if ( (sw)m_ext < (sw)sld_min) m_ext = sld_min;
                        }
                        else
                        {
                          if ( (w)m_ext > (w)cx) m_ext = sld_min;
                          if ( (w)m_ext < (w)sld_min) m_ext = sld_min;
                        }

                        Label = k101;
                    }
                    else if ( m_ch == Up)
                    {
                        cx = m_ext;
                        m_ext += m_time;

                        if (FullSledTab[adr_m_tmp->numb].code._.off_sign == 0 )
                        {
                          if ( (sw)m_ext < (sw)cx) m_ext = sld_max;
                          if ( (sw)m_ext > (sw)sld_max) m_ext = sld_max;
                        }
                        else
                        {
                          if ( (w)m_ext < (w)cx) m_ext = sld_max;
                          if ( (w)m_ext > (w)sld_max) m_ext = sld_max;
                        }
                        Label = k101;
                    }
                    else if (m_ch == Enter )
                    {

                        adr_m_tmp->mean = m_ext;

                        output_c ( '\n' ) ;
                        output_c( '\r');
                        output_s (Sld_Start_Stop[m_index]  ) ;
                        output_c ( '\n' ) ;
                        Label = k4;
                    }
                    else
                    {
                        Klav_Buff = m_ch;
                    }

                }
                if ( AWelcome != AWell_old )
                {
                    AWell_old = AWelcome;
                    Label = k101;
                }
                break;
       case k11 : //включение, выключение условия.
              if (  TestCompleted_Output() )
                {
       case k113:
                  output_c( '\r');
                  output_s( AWelcome );
                  output_s (Sld_en[m_ext]) ;
                  Label = k115 ;
                  break;
                }
       case k115:
                 ax = Key_tst(0, 2, k11, 1);

                 if (ax != 0 )
                 {
                   if ( ax == 1) adr_m_tmp->bits._.enable = m_ext;
                   output_c( '\n' ) ;
                   output_c( '\r' );
                   output_s (Sld_Start_Stop[m_index]  ) ;
                   output_c ( '\n' ) ;
                   Label = k4;

                 }
                break;
       case k123 :
              if (  TestCompleted_Output() )
                {
       case k12: //значение условия.

                  output_c( '\r');
                  output_s( AWelcome );
                  lax = m_ext;

               //   bx = FullSledTab[adr_m_tmp->numb].nom;
               //   lax = *FullSledTab[adr_m_tmp->numb].abs_nom;
               //   lax *= ax;

                  ex = 0 ; // для совместимости - если заданы были нули то принимаем формат "3.2".

                  for ( ax = 10000, cx = 0 ; ax != 1 ; ax /= 10 )
                    {
                        bx =  lax/ax  ;
                        lax %=ax ;
                            // пока идут первые нули - не выводим их:
                        if ( bx == 0 && cx == 0 )
                        {     // а пропускаем лишние нулевые символы,
                            if ( ex != 0 ) ex-- ;
                                // или заменяем пробелами.
                            else  output_c (' ') ;
                        }
                        else
                        {
                            cx = 1 ; // первые нули закончились.
                            output_c ( (b)bx + 0x30 ) ;
                        }
                    }

                    // распечатываем последнюю цифру.
                   output_c ( (b)(w)lax + 0x30 ) ;
                   output_c ( ' ') ;
                   output_s ( "мсек" ) ;
                   Label = k125;
                   break;
                }
       case k125:
                if (  TestData_for_Input() )
                {
                    mInput_c ( m_ch ) ;
                    if ( m_ch == Return)
                    {
                        output_c ( '\n' ) ;
                        output_c( '\r');
                        output_s (Sld_Start_Stop[m_index]  ) ;
                        output_c ( '\n' ) ;
                        Label = k4;
                    }
                    else if ( m_ch == Down)
                    {
                        m_ext -= 1;
                        if ((sw)m_ext < 0 )
                        {
                           m_ext = 0;
                        }
                        Label = k123;
                    }
                    else if ( m_ch == Up)
                    {
                        m_ext += 1;
                        if ( m_ext > 100 )
                        {
                           m_ext = 100;
                        }
                        Label = k123;
                    }
                    else if (m_ch == Enter )
                    {

                        *adr_delay = m_ext;
                        output_c ( '\n' ) ;
                        output_c( '\r');
                        output_s (Sld_Start_Stop[m_index]  ) ;
                        output_c ( '\n' ) ;
                        Label = k4;
                    }
                    else
                    {
                        Klav_Buff = m_ch;
                    }

                }
                if ( AWelcome != AWell_old )
                {
                    AWell_old = AWelcome;
                    Label = k123;
                }
                break;

    }

}

word Key_tst(word min, word max, word lab, word inv)
{
    if (  TestData_for_Input() )
    {
        mInput_c ( m_ch ) ;
        if ( m_ch == Return) return 2;
        else if ( m_ch == Down)
        {
            if ( inv == 1)
            {
                 if ( ++m_ext >= max) m_ext = min;
            }
            else if ( (sw)(--m_ext) < (sw)min ) m_ext = max-1;
            Label = lab;
        }
        else if ( m_ch == Up)
        {
            if ( inv == 1)
            {
                 if ( (sw)(--m_ext) < (sw)min ) m_ext = max-1;
            }
            else if ( ++m_ext >= max) m_ext = min;
            Label = lab;
        }
        else if (m_ch == Enter ) return 1;
        else
        {
            Klav_Buff = m_ch;
        }

    }
    if ( AWelcome != AWell_old )
    {
        AWell_old = AWelcome;
        Label = lab;
    }
    return 0;
}
