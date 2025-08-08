//static word tx_ind;            `1
void Link_start(void)
{
  word i;
/* for(i = 0,j=0; i < (sizeof(SledPole));++i,++j)
  {
   if ( j >= 16 ) j = 0;
   SledPole[i] = j;
  }*/
 //  tmpcount = 0;
   P_Tab.numb = 0;
   L_sts.all = 0 ;

   TimeLanOsc = Timer1_fSec;
   for (i = 0; i < 36; ++i){
     LanOsclOut[i] = 0;
   }

   for (i = 0; i < 4; ++i){
     OscPtrs[i] = 0xff;
   }



}
//Програма включения линка из меню и начальной инициализации.
void Link(void)
{
    if ( M_FirstCall == 1 )  /*  Идентификация первого входа для задания  */
      {                      /* начального условия ...                    */
        M_FirstCall = 0 ;
        //Set_Uart_Speed (_High_UART_Speed);
        Mon.Pult = 0 ;
        numb_text = 0;
        numb_line[0] = 0;
        nuk = 0;
        nuk_max = 0;
        byte_ad = 0;
        Link_time = timer1;

        CW_count= 0;
        Comm_label = 0;
        //l_ret = 0;
        L_sts.all = 0;
        trg_time = 0;
        comm_word = 0;
        comm_word_old = 0;
        Tx_mem_label = 0;
        Write_Label = 0;
        feed_b = 0;
        sld_cw = 0;
         if (Size_bl == 0) Size_bl = 100;
         //По этому биту линк начинает работать
        L_sts._.run = 1;
        lpoint = 0;
        back_lab = 0;
        CW_time = Timer1_Ovr;
        sbh = 0;
      }
      else if ( !L_sts._.first_time  )
      {
        output_c ( 5 );
        Restart_Output ()  ;
        L_sts._.first_time = 1;
      }
      return ;
}
//Основная программа приема передачи работает в качестве диспетчера
// программ: принимает коммандное слово, и, в зависимости от его значени
//запускает нужную подпрограмму приема/передачи
void Link_txrx(void)
{
    byte bh;//, l_ret;
    word ax;
    //static byte sbh;

    if( !L_sts._.run)
    {
            CW_time = Timer1_Ovr;
            sbh = 0;
            return ;
    }

      if (  TestData_for_Input() )
      {
        //Обработка очереди байтов:
        // первый байт - коммандное слово, струтура его следующая:
        // Сташие четыре бита - код комманды, младшие - размер передаваемого массива данных
        // последующие байты - данные
        // последний байт - контрольная сумма
        // последовательность может состоять максимум из восьми байт + CW+CS, итого максимум 10 байт за раз
        // Отправлення комманда должна получить подтверждение принятия - код комманды с нулевой длинной данных
        // Если дополнительных данных с CW  не идет, то и контрольная сумма не приходит
        // Данные, полученные вместе с CW складываются в буферный массив comm_Par
        mInput_c ( bh ) ;
        CW_time = Timer1_Ovr;
        sbh = 0;
        switch ( Comm_label )
        {
          // Первый байт - CW
          default:
          case 0:
                  //Передали код ошибки, дожидаемся пока прийдет сигнал о том, что следующий байт - CW
                  // для этого мы должны получить код ошибки.
                  if ( trg_time != 2) trg_time = 0;
                  else if ( bh != Return)
                  {
                    //Приняли ошибку - преподключение
                    if (((bh >> 4) == _CW_Error) /*&& ((bh & 0x1) == 1)*/)
                    {
                        trg_time = 0;
                    }
                    break;
                  }
                  ccs = 0;
                  comm_word_old = comm_word;

                  //Пришел код Esc - выходим из программы

                  if(bh == Return)
                  {
                   comm_word = _CW_BREAK;
                   comm_len = 0;
                  }
                  else
                  {
                   comm_word = bh>>4;
                   comm_len = bh&0x0f;
                  }
                  // Длина не нулевая - продолжаем принимать данные
                  if ( comm_len != 0)
                  {
                    ccs -=bh;
                    Comm_label = 1;
                    comm_count = 0;
                    L_sts._.cw_all = 0;

                  }
                  else
                  {
                    // одиночная комманда конитрольная сумма не считается - преходим  сразу к отправке подтверждени
                    L_sts._.cw_all = 1;  // признак того, что приняли всю последовательность данных
                    // _CW_SYNCH и _CW_Error воспринимаются как ошибки и обрабатываются ниже
                    if (( comm_word != _CW_SYNCH)&&( comm_word != _CW_Error))
                    {
                        goto snd;
                    }
                  }
                  break;
          case 1:
                  //Складываем принятые байты в буфер
                  comm_Par[comm_count] = bh;
                  ccs -=bh;// подсчет контрольной суммы - вычитание принятого байта
                  //приняли всю последовательность - преходим к проверке контрольной суммы
                  if ( ++comm_count >= comm_len )
                  {
                    Comm_label = 2;
                  }
                  //CW_time = Timer1_Ovr;
                  break;
          case 2:
                  //CW_time = Timer1_Ovr;
                  //Контольная сумма не сошлась - выдаем код ошибки, и загружаем всю последовательнось заново
                  if ( bh != ccs )
                  {
                    bh =  (_CW_Error<<4)+2;
                    output_c ( bh );
                    Restart_Output ()  ;
                    Comm_label = 0;
                    trg_time = 2;
                   // Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                  //  L_sts._.run = 0;
                    //L_sts._.off_sled = 0;
                    return ;
                  }
                  else
                  {
                   //Все сошлось, если CW - _CW_SLED, то последующий байт определяет
                   // комманду работы со следом
                   if ( comm_word == _CW_SLED )
                   {
                    sld_cw = comm_Par[0];
                    feed_b = 0xb0;
                   }
                   // Признак, того, что последовательность получена
                   L_sts._.cw_all = 1;

          snd:
                   //Отправляем подтверждение - "последовательность принята" - CW в страших четырех битах, младшие = 0
                   bh =  comm_word<<4;
                   output_c ( bh );
                   Comm_label = 3 ;

                  }
                  goto next;
          case 3:
                  // Последовательность принята - теперь обрабатываем получение комманды выхода из Линка
                  //Будем висеть тут, пока программа обработки CW  не обнулит  Comm_label
                  if((bh == Return)|| (bh>>4 == _CW_BREAK))
                  {
                   comm_word = _CW_BREAK;
                   comm_len = 0;
                  }
                  else feed_b = bh;
                  //CW_time = Timer1_Ovr;
                  break;
        }
      }
next:

     if (L_sts._.cw_all)
     {
       // Последовательность приняли - приступаем к обработке полученных комманд
       switch ( comm_word )
       {
        default :
                            //comm_word = comm_word_old;
                            //break;
        case 0:
        case _CW_Read_Blok: //Несуществующие комманды, но, на всякий случай, оставил.
        case _CW_READ_TAB:              // обрабатываются как ошибка
                            bh =  (_CW_Error<<4)+3; //Несуществующее CW - код ошибки 3
                            output_c ( bh );
                            Comm_label = 0;
                            //L_sts._.trg_time = 0;
                            trg_time = 2; //Тоже ждем подтверждения принимающей стороны
                            //comm_word = _CW_BREAK;
                            L_sts._.cw_all = 0;
                            break;
        case _CW_BREAK:
                            //Комманда на выход
                            Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                          /*  if (sld_cw == _CW_Oscillat )
                            {
                              sl_d.Stop = 2;
                            }*/
                            Restart_Output ()  ;
                            L_sts._.off_sled = 0;
                            L_sts._.run = 0;
                           // Set_Uart_Speed (_Low_UART_Speed);
                            return ;
   /*                         comm_word = _CW_BREAK;
                            break;*/
        case _CW_READ_NUMB:
                            //Чтение номера переменной по её имени в таблице

                            back_lab = _CW_READ_NUMB;

                            ax = Write_Numb_By_Name( (b*)&feed_b);
                            // 0 - окончание передачи
                            // 2 - ошибка в процессе выполнени
                            if (ax == 0)
                            {
                              L_sts._.cw_all = 0;
                              Comm_label = 0;
                            }
                            else if (ax == 2)
                            {
                             comm_word = _CW_BREAK;
                            }
                            break;

        case _CW_READ_NAME:
                            //Чтение имени переменной по номеру
                            back_lab = _CW_READ_NAME;
                            ax = Write_Name_By_Numb((b*)&feed_b);
                            // 0 - окончание передачи
                            // 2 - ошибка в процессе выполнени
                            if (ax == 0)
                            {
                              L_sts._.cw_all = 0;
                              Comm_label = 0;
                            }
                            else if (ax == 2) comm_word = _CW_BREAK;
                            break;
        case _CW_READ:
                            //Выдача значения переменной или массива данных вовне
                            back_lab = _CW_READ;
                            ax = COMM_Write((b*)&feed_b) ;
                            // 0 - окончание передачи
                            // 2 - ошибка в процессе выполнени
                            if (ax == 0)
                            {
                              L_sts._.cw_all = 0;
                              Comm_label = 0;
                            }
                            else if (ax == 2) comm_word = _CW_BREAK;
                            break;
        case _CW_WRITE:
                            //Прием значения переменной или массива даных извне
                            back_lab = _CW_WRITE;

                            // 0 - окончание передачи
                            // 2 - ошибка в процессе выполнени

                            ax = COMM_Read((b*)&feed_b);
                            if (ax == 0)
                            {
                              L_sts._.cw_all = 0;
                              Comm_label = 0;
                            }
                            else if (ax == 2) comm_word = _CW_BREAK;
                            break;
        case _CW_SLED:
                            //Работа со следом
                            back_lab = _CW_SLED;

                            ax = UART_Sled();
                            //ax = Write_Sled_Tab();

                            // 0 - окончание передачи
                            // 2 - ошибка в процессе выполнени
                            if (ax == 0)
                            {
                              L_sts._.cw_all = 0;
                              Comm_label = 0;
                            }
                            else if (ax == 2)
                            {
                              comm_word = _CW_BREAK;
                            }
                            break;
        case _CW_SYNCH:
                          /*  bh = _CW_SYNCH<<4;
                            output_c ( bh );*/

        case _CW_Error:     //Пришла ошибка
                            feed_b = comm_word<<4;
                            comm_word = back_lab;
                            break;
       }
        CW_time = Timer1_Ovr;
     }
     else if ((u)((w)(Timer1_Ovr - CW_time)) >_Sec(0.5))
     {
        //Если в течении 500 мсек ничего не получаем, то потом
        //Каждые 100 мсек посылаем ошибку с кодом 1, пока не возобновится передача
        bh =  (_CW_Error<<4);
        if (trg_time == 0)
        {
            if ( ++sbh >= 10  )
            {
                sbh = 0;
                trg_time = 2;
               bh+=1;
                Comm_label = 0;
               // lpoint = 1;//sbh+1;
            }
          //CW_time = Timer1_Ovr;
        }
        else
        {
            bh += 5 ;
            Comm_label = 0;
        }
        CW_time = Timer1_Ovr;

        if ( bh != (_CW_Error<<4))
        {
          output_c ( bh);
        }


     }

     Restart_Output ()  ;

   return ;
}

//Программа передачи коммандного слова с проверкой контрольной суммы
//при наличии аргументов. Принимает : command - код команды
// length - число параметров в команде(не более 8)
// param - массив с  параметрами
// feed_back - обратная связь: параметр, который получаем в ходе передачи от принимающей стороны
// Используется внутри программ связи, возвращаемые параметры:
// 1 - идет передача
// 0 - все передал
// 3 - ошибка передачи
word SendCommWord(byte command, byte length, byte param[8],byte* feed_back )
{
   byte bh, i;
   word ax = 1;
  // byte c_s = 0;
   enum { s0, s1, s2, s3};
   switch (Write_Label  )
   {
    case s0:
            ccs = 0;
            bh = (command<<4)+ length;
            output_c ( bh );
            Restart_Output ()  ;
            //Если параметров нет, то заканчиваем передачу
            if (length != 0)
            {
              ccs -=bh;//контрольная сумма
              // До трех байт отправляем за раз с кодом комманды и контрольной суммы
              for (i= 0;(i<length)&&(i<3);++i)
              {
                output_c (param[i]);
                ccs -=param[i];
                Restart_Output ()  ;
              }
              ++Write_Label;
              if ( length < 3)
              {
                output_c (ccs);//Контрольная сумма
                goto end;
              }
            }
            else goto end;
             break;
    case s1://Предаем 4-7 байты
            for (i= 3;(i<length)&&(i<7);++i)
            {
              output_c (param[i]);
              ccs -=param[i];
              Restart_Output ()  ;
            }
            if ( length < 7)
            {
              output_c (ccs);
              goto end;
            }
            ++Write_Label;
            break;
    case s2://последний байт
            for (i= 7;i<length;++i)
            {
              output_c (param[i]);
              ccs -=param[i];
              Restart_Output ()  ;
            }
            output_c (ccs); //Контрольная сумма
        end:
            Write_Label = s3;
            *feed_back = 0;
            break;
    case s3: //Все передали, ожидаем подтверждения приема
             ax = *feed_back>>4;
             if ( ax == command)
             { //Получили подтверждение
               ax = 0;
               Write_Label = 0;
             }
             else if (ax == _CW_Error  )
             { //Ошибка, пробуем послать еще раз
               Write_Label = 0;
               if (++CW_count > 5)
               {
                 //Больше пяти попыток - полный алес капут
                 ax = 3;
               }
               else ax = 1;
             }
             else ax = 1;
             break;
   }
    Restart_Output ()  ;

   return ax;
}

//Считывание параметров переменной по имени
// Имя переменной: 8 байт в массиве  comm_Par
word Write_Numb_By_Name(byte* feed_back)
{
  word i;
  static byte Sendlength, SendCommand;
  //byte bh;
  enum {a0,a1,a2,a3};
  byte *pt1, *pt2;

  switch (Tx_mem_label )
  {
    case a0:
              trans_blok = 0;
              ++Tx_mem_label;
    case a1:
                // Поиск имени: сравенение полученного с именами в таблице
                // Чтобы поиск не вызывал зависаний фоновой программы
                // обрабатывается зараз не более 10 имен
              for(i = 0; i < 2; ++i)
              {
                pt1 = (b*)var_tab1[trans_blok].name;
                pt2 = comm_Par;

                while ( *pt1 == *pt2 )//Символы имени совпали
                {

                  if ( *pt2 == 0 )//Совпало все им
                  {
                    //goto send;
                    comm_Par[0] = trans_blok;
                    comm_Par[1] = var_tab1[trans_blok].access;
                    comm_Par[2] = var_tab1[trans_blok].type;
#ifdef _CM3_
                    comm_Par[5] = var_tab1[trans_blok].lon>>24;
                    comm_Par[6] = var_tab1[trans_blok].lon>>16;
#endif
                    comm_Par[3] = var_tab1[trans_blok].lon>>8;
                    comm_Par[4] = (b)var_tab1[trans_blok].lon;


                    SendCommand = _CW_READ_NUMB;
#ifdef  _CM3_
                    Sendlength = 7;
#else
                    Sendlength = 5;

#endif

                    //++Tx_mem_label;
                    //SendCommWord(_CW_READ_NUMB, 5, comm_Par);
                    ++Tx_mem_label;
                   // return 1;
                    goto send;
                  }

                  pt1++,pt2++;//Следующий смвол
                }
                //Прошли всю таблицу, и ничего похожего не нашли
                if ( ++trans_blok >= svar[_CAN0_Port].size )
                { //Выдаем ошибку с кодом _Err_DESCRIPT
                  comm_Par[0] = _Err_DESCRIPT;
                  SendCommand = _CW_Error;
                  Sendlength = 1;
                 // SendCommWord(_CW_Error, 1, comm_Par);
                  ++Tx_mem_label;
                  break;
                 // return 2 ;
                }
              }
              break;
    case a2:
    send:     //Опознание прошло, выдаем CW с результатами
              i = SendCommWord(SendCommand, Sendlength, comm_Par,feed_back);
              //Проверка на oшибки передачи
              if ( i == 0 )
              {
                Tx_mem_label = 0;

                if (comm_Par[6] == _CW_Error)  return 2;
                else return 0;
              }
              else if ( i != 1 ) return 2;
              break;
  }
  *feed_back = 0;
  return 1;

}
//Выдача имени переменной по номеру дискриптора
// Номер хранится в нулевом байте массива comm_Par
word Write_Name_By_Numb(byte* feed_back)
{
  word i;
 // byte bh;
  enum {a0,a00,a1};
  len_trans = comm_Par[0];

  //Если номер больше, чем элементов в таблице - однозначно ошибка
  if ( len_trans >= svar[_CAN0_Port].size )
  {
    comm_Par[0] = _Err_NAME;
    SendCommWord(_CW_Error, 1, comm_Par, feed_back);
    Write_Label = 0;
    L_sts._.cw_all = 0;
    return 2;

  }
  else
  {
    switch ( Tx_mem_label )
    {
      case a0:  //Загрузка имени переменной в буфер
                for(i=0;i<8;++i)
                {
                  comm_Par[i] = *(var_tab1[len_trans].name+i);
                  if(comm_Par[i] == 0) break;
                }
                trans_blok = i;
                //SendCommWord(_CW_READ_NAME, trans_blok, comm_Par);
                ++Tx_mem_label;
                break;
      case a00:
                //Передача CW с именем
                i = SendCommWord(_CW_READ_NAME, trans_blok, comm_Par,feed_back);
                if (i == 0)
                {
                  Tx_mem_label = 0;
                  return 0;
                }
                else if ( i != 1 ) return 2;
                break;
    }
  }
  *feed_back = 0;
  return 1;

}

//Программа приема данных по UARTу по нескольким дискрипторам
//порядок приема следующий:
//1.В первом ком. слове принимаем дискрипторы.
//2.Передаем в ответ значения переменных ком. словом, причем,
// если данные не влазят в 8 байт, то передается столько ком. слов,
// чтобы данные влезли(каждое последующее ком. слово передаетс
//в следующий цикл - надо учитывать: больше 8 байт за раз не передается)
//3.дожидаемся подтверждения - если пришла ошибка - загружаем слово заново.

word COMM_Write(byte* feed_back)
{
  word i, ax;
  lword lax;
  //byte bh;
  enum {a0, a1, a11, a2,a3};

  switch ( Tx_mem_label )
  {
    case a0:

            len_trans = 0;
            len_blok  = 0;
            wr_Diskr = 0;
            block_count = 0;
            //Расчитываем сколько байт нам надо передать
            for (i=0;i< comm_len; ++i )
            {
              Dis_Buff[i] = comm_Par[i] ;
              len_trans += var_tab1[Dis_Buff[i]].lon;
            }
            trans_blok = comm_len;
            ++Tx_mem_label;

    case a1:
             nuk = 0;
             block_count_old = block_count;
             len_blok_old = len_blok;
             link_stop_point = wr_Diskr;
             //Заполняем буфер
             while ( block_count < trans_blok )
             {
               switch (var_tab1[Dis_Buff[block_count]].type )//Выбирается тип данных
               {
                default:
                         block_count = trans_blok;
                         break;

                case _CHAR_type:
                case _uCHAR_type:
                                  lax = *((b*)var_tab1[Dis_Buff[block_count]].addr);
                                  goto prbr;
                                  /*comm_Par[i] =*(b*)(var_tab1[Dis_Buff[block_count]].addr);
                                  ++i;
                                  ++block_count;
                                  break;*/
                case _INT_type  :
                case _uSHORT_type:
                case _SHORT_type:
                                  lax = *((w*)var_tab1[Dis_Buff[block_count]].addr);
                                  goto prbr;
                                 /* lax = *(w*)(var_tab1[Dis_Buff[block_count]].addr);
                                  comm_Par[i] = (b)lax;
                                  ++i;
                                  comm_Par[i] = (b)(lax>>8);
                                  ++i;
                                  ++block_count;
                                  break;*/

                case _LONG_type:
                case _uLONG_type :

                                  lax = *((lw*)var_tab1[Dis_Buff[block_count]].addr);
                             prbr:      // Загрузка буфера, если пременная состоит из одного элемента
                                        // может быть максимум четыре байта один дискриптор
                                  while (len_blok < var_tab1[Dis_Buff[block_count]].lon)
                                  {
                                    comm_Par[nuk] = (b)(lax>>(len_blok*8));

                                    ++len_blok;
                                    if ( ++nuk >= 8 )  // nuk - счетчик для разделения всего массива на пакеты по 8 байт
                                                       // если размер массива больше.
                                    {
                                      goto send;
                                    }
                                  }
                                  ++block_count;
                                  len_blok  = 0;

                                  break;

                case _CHAR_array_type   :
                case _uCHAR_array_type  ://Массив байт
                                  while (len_blok < var_tab1[Dis_Buff[block_count]].lon)
                                  {
                                    lax = *((b*)var_tab1[Dis_Buff[block_count]].addr+len_blok);
                                    comm_Par[nuk] = (b)lax;
                                    ++len_blok;
                                    //Либо сам закончится, либо восемь байт заполнили
                                    if ((++nuk >= 8)&& (len_blok < var_tab1[Dis_Buff[block_count]].lon ) )
                                    {
                                      goto send;
                                    }
                                  }

                                  len_blok  = 0;
                                  ++block_count;
                                  break;

                case _SHORT_array_type  :
                case _SHORT2_array_type :
                case _uSHORT_array_type : // Массив слов, каждый элемент занимает 2 места в буфере
                                  while (len_blok < var_tab1[Dis_Buff[block_count]].lon)
                                  {

                                    lax = *((w*)var_tab1[Dis_Buff[block_count]].addr+len_blok);
                                    while (wr_Diskr < 2)
                                    {
                                      comm_Par[nuk] = (b)(lax>>(wr_Diskr*8));
                                      ++wr_Diskr;
                                      if ( (++nuk >= 8)&&((len_blok+wr_Diskr-1) < var_tab1[Dis_Buff[block_count]].lon ) )
                                      {
                                        goto send;
                                      }
                                    }
                                    len_blok += 2;
                                    wr_Diskr = 0;
                                  }
                                  len_blok  = 0;
                                  ++block_count;
                                  break;

                case _LONG_array_type   :
                case _uLONG_array_type  ://Массив длинных слов - 4 места на элемент
                                  while (len_blok < var_tab1[Dis_Buff[block_count]].lon)
                                  {

                                    lax = (lw)(*((w*)var_tab1[Dis_Buff[block_count]].addr+len_blok));
                                    while (wr_Diskr < 4)
                                    {
                                      comm_Par[nuk] = (b)(lax>>(wr_Diskr*8));
                                      ++wr_Diskr;
                                      if ( (++nuk >= 8)&&((len_blok+wr_Diskr-1) < var_tab1[Dis_Buff[block_count]].lon )  )
                                      {
                                        goto send;
                                      }
                                    }
                                    len_blok += 4;
                                    wr_Diskr = 0;
                                  }
                                  len_blok  = 0;
                                  ++block_count;
                                  break;
               }
             }
    /*         i = 0;
             block_count_old = block_count;
             len_blok_old = len_blok;
             link_stop_point = wr_Diskr;
             while ( block_count < trans_blok )
             {
               for(;len_blok < var_tab1[Dis_Buff[block_count]].lon;++len_blok, ++i )
               {
                 comm_Par[i] =*((char*)(var_tab1[Dis_Buff[block_count]].addr)+len_blok);
                 if ((++wr_Diskr>=len_trans )||(i>=7) )
                 {
                  ++len_blok;
                  goto send ;
                 }
               }
               len_blok = 0;
               ++block_count;

             }*/
       send: CW_count = 0;
             ++Tx_mem_label;
    case a11: //Отправляем заполненый буфер
             ax = SendCommWord(_CW_READ, nuk, comm_Par,feed_back);
             if ( ax == 0 )
             {
              if (block_count < trans_blok )
              {
                Tx_mem_label = a1;
              }
              else
              {
                Tx_mem_label = 0;
                return 0;
                //++Tx_mem_label;
              }

             }
             else if ( ax != 1 )
             {
              Tx_mem_label = 0;
              return 2;
             }

             break;
  }

  return 1;
}
// Программа чтения извне данных, дискрипторы которых указаны в строке коммандного слова
word COMM_Read( byte* feed_back )
{
  word i, ax = 1;
  lword lax,lbx;
  enum {a0,a1, a2,a3};
    i = 0;
  switch ( Tx_mem_label )
  {
    case a0:
            len_trans = 0;
            len_blok  = 0;
            wr_Diskr = 0;
            block_count = 0;
            *feed_back = 0;
            len_trans = comm_Par[0];
            i= 1;

            ++Tx_mem_label;
    case a1:
              ++Tx_mem_label;
              //На случай обрыва связи переподключение
              if ( *feed_back == _CW_SYNCH<<4 )
              {
                Tx_mem_label = 0;
                output_c ( 5 );
                Restart_Output ()  ;
                ax = 0;
                break;
              }
              //i = 0;
              //Разбираем дискрипторы
              for ( ;i < comm_len;++i )
              {
                // Номер больше размера таблицы - выдаем ошибку
                if (len_trans >= svar[_CAN0_Port].size )
                {
                  L_sts._.Av_up = 1;
                  comm_Par[6] =_CW_Error ;
                  comm_Par[7] = 1;
                  comm_Par[0] =_Err_DESCRIPT;
                  goto end;
                }
                //Нет доступа к переменной - выдаем ошибку и дискриптор, к которому нет доступа
                if (var_tab1[len_trans].access != _READ_WRITE_access )
                {
                  L_sts._.Av_up = 1;
                  comm_Par[6] =_CW_Error ;
                  comm_Par[7] = 2;
                  comm_Par[0] =_Err_ACCESS;
                  comm_Par[1] =len_trans;
                  goto end;
                }
                 //Загружаем данные из буфера в зависимости от их типа
                 switch (var_tab1[len_trans].type )
                 {
                  default:
                           break;

                  case _CHAR_type:
                  case _uCHAR_type:
                                    *((b*)var_tab1[len_trans].addr) = comm_Par[i];
                                    break;
                  case _INT_type  :
                  case _uSHORT_type:
                  case _SHORT_type:
                                    Dis_Buff[block_count] = comm_Par[i];
                                    if ( ++block_count >= 2 )
                                    {
                                      lax = Dis_Buff[0]+((w)Dis_Buff[1]<<8);
                                      *((w*)var_tab1[len_trans].addr) = (w)lax;

                                      block_count = 0;
                                    }
                                    break;

                  case _LONG_type:
                  case _uLONG_type :
                                    Dis_Buff[block_count] = comm_Par[i];
                                    if ( ++block_count >= 4 )
                                    {
                                      lax = Dis_Buff[0]+((lw)Dis_Buff[1]<<8);
                                      lax += ((lw)Dis_Buff[2]<<16)+((lw)Dis_Buff[3]<<24);
                                      *((lw*)var_tab1[len_trans].addr) = lax;
                                      block_count = 0;
                                    }
                                    break;

                  case _CHAR_array_type   :
                  case _uCHAR_array_type  :

                                        *((b*)(var_tab1[len_trans].addr)+len_blok) = comm_Par[i];
                                        break;

                  case _SHORT_array_type  :
                  case _SHORT2_array_type :
                  case _uSHORT_array_type :

                                        Dis_Buff[block_count] = comm_Par[i];
                                        if ( ++block_count >= 2 )
                                        {
                                          lax = Dis_Buff[0]+((w)Dis_Buff[1]<<8);
                          #if defined (_24_BITS_) ||  defined (_32_BITS_)
                                          lbx = (lw)var_tab1[len_trans].addr+len_blok-1;
                                          *((w*)lbx) = (w)lax;
                          #else
                                          lbx = (lw)(w)var_tab1[len_trans].addr+len_blok-1;
                                          *((w*)(w)lbx) = (w)lax;
                          #endif
                                          block_count = 0;
                                        }
                                        break;

                  case _LONG_array_type   :
                  case _uLONG_array_type  :
                                        Dis_Buff[block_count] = comm_Par[i];
                                        if ( ++block_count >= 4 )
                                        {
                                          lax = Dis_Buff[0]+((lw)Dis_Buff[1]<<8);
                                          lax += ((lw)Dis_Buff[2]<<16)+((lw)Dis_Buff[3]<<24);
                          #if defined (_24_BITS_) ||  defined (_32_BITS_)
                                          lbx = (lw)var_tab1[len_trans].addr+len_blok-3;
                                          *((lw*)lbx) = lax;
                          #else
                                          lbx = (lw)(w)var_tab1[len_trans].addr+len_blok-3;
                                          *((lw*)(w)lbx) = lax;
                          #endif
                                          block_count = 0;
                                        }
                                        break;
                 }



                if (++len_blok >= var_tab1[len_trans].lon  )
                {
                  ++i;
                  len_trans = comm_Par[i];
                  len_blok = 0;
                }

              }
              //Если все нормально загружаем в буфер код команды как подтверждение приема
              comm_Par[6] =_CW_WRITE ;
              comm_Par[7] = 0;
              L_sts._.Av_up = 0;
    //   end:

             break;
    case a2:
       end: //Оправляем подтверждение, или ошибку приема
            i = SendCommWord(comm_Par[6], comm_Par[7], comm_Par,feed_back);
            if ( i == 0 )
            { //Если был сбой, то L_sts._.Av_up = 1
              if (L_sts._.Av_up == 0 )
              {
                --Tx_mem_label;
                L_sts._.cw_all = 0;//чтобы дождаться следующего командного слова
                Comm_label = 0;
               // ax = 1;
              }
              else
              {
                Tx_mem_label = 0;
                ax = 2;
              }

            }
            else if ( i != 1 )
            {
              Tx_mem_label = 0;
              ax = 2;
            }
            break;

  }
  *feed_back = 0;
  return ax;
}
//Подготовка в памяти таблиц для передачи по UART

word Write_Sled_Tab( byte Numb )
{
  word ax;
  ax = 1;
  if ( !L_sts._.Pr_Tabl )
  {
    P_Tab.numb = Numb;
    P_Tab.bits._.En = 1;
    L_sts._.Pr_Tabl = 1;
  }
  else if ( !P_Tab.bits._.En )
  {
    ax = _CW_SLED<<4;

    output_c ( ax );
    L_sts._.Pr_Tabl = 0;
    ax = 0;
  }
//  PrepareTab();

  return ax;
}

//Программа - диспетчер комманд для работы со следом по СОМ порту
// Комманды по обработке следа идут в следующем байте после слова _CW_SLED
word UART_Sled( void )
{
  word ax;
  switch ( sld_cw )
  {
    default:
    case 0:                //Получили что-то непонятное - выдаем ошибку
                          #if defined (_24_BITS_) ||  defined (_32_BITS_)
                            SendCommWord(_CW_Error, 0 , (b*)(lw)0, (b*)&feed_b);
                          #else
                            SendCommWord(_CW_Error, 0 , NULL, (b*)&feed_b);
                          #endif
                            Write_Label = 0;
                            ax = 2;
                            break;
    case _CW_Prepare_tab: //Подготовить таблицы следа для передачи
                            ax = Write_Sled_Tab(comm_Par[1]);
                            break;

    case _CW_Load_tab:     //Загрузить список переменных следа
      if (!P_Tab.bits._.Ld_Tab){
        P_Tab.bits._.Ld_Tab = 1;
        P_Tab.bits._.Sv_Tab = 0;
        ax = 1;
      }
      else{
        if (!P_Tab.bits._.Sv_Tab){
          ax = 1;
        }
        else{
          output_c(5);
          P_Tab.bits._.Ld_Tab = 0;
          P_Tab.bits._.Sv_Tab = 0;
          ax = 0;          
        }
      }
                            
                            break;
    case _CW_Osc_tab:
    case _CW_Osc_adr:       //Задание переменных для отображения в осциллографе
                            ax = RD_addr();
                            break;
    case _CW_Oscillat:      //Осциллограф
                            ax = Oscillator();
                            break;
  }
  return ax;
}
//Загрузка переменных следа с компа.
word Load_Sled_Tab( void)
{
  word ax;
  enum {a0,a1, a2,a3};
  if (P_Tab.bits._.Ld_Tab && !P_Tab.bits._.Sv_Tab){
    
     switch ( Tx_mem_label )
     {
       case a0:
                L_sts._.off_sled = 1;                
                len_blok = 0;
                ++Tx_mem_label;
       case a1:
                 if ( bo_SledActiv == 0 )
                 {
                   ++Tx_mem_label;
       #ifdef _Union_FR
     
     
                   sled.kratn   = s_tx.kratn_l+((w)s_tx.kratn_h<<8)  ;
     
       #else
     
                   sled.kratn   = s_tx.kratn  ;
     
       #endif
                   sled.n_kanal = s_tx.n_kanal;
                 }
     
                 break;
       case a2:
                 sl_d.tab[len_blok] = s_tx.ptr[len_blok];
                 for( ax=0; ax < _NameSize; ++ax)
                 {
                   sled.tab[len_blok].txt[ax] = FullSledTab[sl_d.tab[len_blok]].txt[ax];
                 }
                 if ( ++len_blok >= s_tx.n_kanal ) ++Tx_mem_label;
                 break;
       case a3:
              //   SendCommWord(_CW_SLED, 0 , NULL, NULL);
                // output_c(5);
                 Write_Label = 0;
                 Tx_mem_label = 0;
                 L_sts._.off_sled = 0;
                 //P_Tab.bits._.Ld_Tab = 0;
                 P_Tab.bits._.Sv_Tab = 1;
                 return 0;
     
     }
  }
  return 1;
}

//Программа осциллографа
// За раз передаются:
//1.Значения переменных, адреса которых хранятся в массиве tx_addr[ax]
//2.значение текущего времени, для определиня dT  - итого до 6 байт
// число переменных, отбражаемых осциллографом определяетя в nuk_max
word Oscillator( void)
{
  word ax, bx, cx, dx;
  byte bh;
  //ax = Timer1_Ovr -Link_time;
  do { ax = Timer1_Ovr , bx = timer1 ; } while ( ax != Timer1_Ovr ) ;
  ax <<= 8 ;      //  Из четырехбайтного полного значения времени
  ax  += (bx>>8); // для работы берутся средние два байта прини-
                  // мающие значения в диапазоне 0.25мсек-12.0сек.

  dx = ax - Link_time;

 // if(((u)dx < _r.dt_Osc)&&(feed_b != 0xb0)) return 1;     // выдаются значения раз в 40 мсек
  if(/*(u)dx < _fSec(0.04)||*/(feed_b != 0xb0)) return 1;     // выдаются значения раз в 40 мсек
  feed_b = 0;
  Link_time = ax;
  //mUSEL_not() ;

  for ( ax = 0, bx = 0; ax <nuk_max;++ax )
  {
    cx = *(w*)tx_addr[ax];
    bh = cx>>8;
    comm_Par[bx] = bh;
    ++bx;
    bh = (b)cx;
    comm_Par[bx] = bh;
    ++bx;
  }
  /*lax = (lw)Link_time*0x100;
  ax = lax/TickD;//L_Tmp1;*/
  ax = Link_time;///_fSec(0.01);
  comm_Par[bx++] = ax>>8;
  comm_Par[bx] = ax;
  ax = 0;
  cx = nuk_max*2+2;
  //Выдача переменных
  bh = (_CW_SYNCH<<4)+cx;
  output_c ( bh );
  Restart_Output ()  ;
  ax -=bh;
  for (bx= 0;bx<cx;++bx)
  {
    output_c (comm_Par[bx]);
    ax -=comm_Par[bx];
    Restart_Output ()  ;
  }
  output_c (ax);
  Restart_Output ()  ;

  return 1;
}
// Задание переменных для отображения в осциллографе
//Задать переменные можно либо адресом, либо дискриптором
//Если идет переменная по адресу, то предварительно с компа заполняется
//структура s_short, определяющая тип переменной, формат и ее адрес
word RD_addr(void)
{
  byte bh;
  word ax;

  if ( sld_cw == _CW_Osc_tab )
  { //Адрес переменной берется из таблицы, последний байт должен быть = 0xff
    // так мы определяем количество отображаемых переменных, дискриптор передается в буфере
      bh = comm_Par[1];
      ax = 1;
    while (bh != 0xff)
    {
      tx_addr[nuk] = (b*)FullSledTab[bh].addr;
      //tx_addr[nuk] = (b*)&fr2;
      if ( ++nuk >= 2 )
      {
        nuk = 0;
        nuk_max = 2;
      }
      else nuk_max = nuk;

      if ( ++ax < 8 )
      {
        bh = comm_Par[ax];
      }
      else bh = 0xff;
    }
  }
  else
  {
    // Задание адреса - данные берутся из s_short
    #ifdef _Union_FR
    //Для FR приходится формировать из-за того, что там по идиотски располагаются байты в структуре
    lword lax = s_short[nuk].addr_ll+(lw)s_short[nuk].addr_lh<<8
    +(lw)s_short[nuk].addr_hl<<16+(lw)s_short[nuk].addr_hh<<24;
    tx_addr[nuk] = (b*)lax;

    #else
      #if defined (_24_BITS_) ||  defined (_32_BITS_)
        tx_addr[nuk] = (b*)s_short[nuk].addr;
      #else
        tx_addr[nuk] = (b*)(w)s_short[nuk].addr;
      #endif
    #endif

    if ( ++nuk >= 2 )
    {
      nuk = 0;
      nuk_max = 2;
    }
    else nuk_max = nuk;
  }
  //Высылаем подтверждение получения
#if defined (_24_BITS_) ||  defined (_32_BITS_)
  SendCommWord(_CW_SLED, 0 , (b*)(lw)0,(b*)&feed_b);
#else
  SendCommWord(_CW_SLED, 0 , NULL,(b*)&feed_b);
#endif
  Write_Label = 0;

  return 0;

}
//Подготовка таблиц для следа.Универсальная программа для использования и по UART
// и по CAN, запускается установлением бита En, признак того, что таблица
//сформирована - обнуление этого бита.Заполняет два вида таблиц - таблицу
//состояния следа и таблицу параметров определенной переменной в таблице, то,
//какую таблицу заполнять определяет значение Numb в структуре P_Tab, если оно
// равняется: 255 - то заполняется таблица состояния следа, любой другой номер -
// заполняются параметры переменной под заданным номером
//Для FR приходится заполнять таблицы побайтно из-за особенности расположения данных в памяти
void PrepareTab(void)
{
  word ax;

  if ( P_Tab.bits._.En )
  {
    if ( (sb)P_Tab.numb != -1 )
    {
      for ( ax =0;ax < 12;++ax )
      {
        s_short[0].txt1[ax] = FullSledTab[P_Tab.numb].txt[ax];
      }
      #ifdef _Union_FR

      s_short[0].form_h = FullSledTab[P_Tab.numb].code.all>>8;
      s_short[0].form_l =(b)FullSledTab[P_Tab.numb].code.all;
      s_short[0].nom_h = FullSledTab[P_Tab.numb].nom>>8;
      s_short[0].nom_l = (b)FullSledTab[P_Tab.numb].nom;
      ax = *FullSledTab[P_Tab.numb].abs_nom;
      s_short[0].abs_nom_h = ax>>8;
      s_short[0].abs_nom_l = (b)ax;

      s_short[0].addr_ll =  (b)(lw)FullSledTab[P_Tab.numb].addr;
      s_short[0].addr_lh =  (b)((lw)FullSledTab[P_Tab.numb].addr>>8);
      s_short[0].addr_hl =  (b)((lw)FullSledTab[P_Tab.numb].addr>>16);
      s_short[0].addr_hh =  (b)((lw)FullSledTab[P_Tab.numb].addr>>24);

      #else
      s_short[0].form = FullSledTab[P_Tab.numb].code.all;
      s_short[0].nom = FullSledTab[P_Tab.numb].nom;
      s_short[0].abs_nom = *FullSledTab[P_Tab.numb].abs_nom;
        #if defined (_24_BITS_) ||  defined (_32_BITS_)
          s_short[0].addr =  (lw)FullSledTab[P_Tab.numb].addr;
        #else
          s_short[0].addr =  (lw)(w)FullSledTab[P_Tab.numb].addr;
        #endif
      #endif
      for ( ax =0;ax < 5;++ax )
      {
        s_short[0].txt2[ax] = FullSledTab[P_Tab.numb].txt2[ax];
      }
      //P_Tab.bits._.En = 0;

    }
    else
    {
      #ifdef _Union_FR

      s_tx.save_mem_l = (b)sl_d.print_size;
      s_tx.save_mem_h = sl_d.print_size>>8;
      s_tx.dt_scan_l  = (b)sled.dt_scan;
      s_tx.dt_scan_h  = sled.dt_scan>>8;
      s_tx.dt_stop_l  = (b)sled.dt_stop;
      s_tx.dt_stop_h  = sled.dt_stop>>8;
      s_tx.kratn_l    = (b)sled.kratn;
      s_tx.kratn_h    = sled.kratn>>8;
      s_tx.index_l    = (b)sl_d.index;
      s_tx.index_h    = sl_d.index>>8;
      s_tx.MSec_l     = (b)_MkSec(1000);
      s_tx.MSec_h     = _MkSec(1000)>>8;
      s_tx.size_l     = (b)sizeof(SledPole);
      s_tx.size_h     = sizeof(SledPole)>>8;

      #else

      s_tx.save_mem = sl_d.print_size;
      s_tx.dt_scan = sled.dt_scan;
      s_tx.dt_stop = sled.dt_stop;
      s_tx.kratn = sled.kratn;
      s_tx.index  = sl_d.index;
      s_tx.MSec = _MkSec(1000);
      s_tx.size = sizeof(SledPole);

      #endif

      s_tx.numb = FullSledTab_size;
      s_tx.n_kanal = sled.n_kanal;
      s_tx.type     = sled.type;

      for(ax = 0; ax < sled.n_kanal; ++ax)
      {
        s_tx.ptr[ax] = sl_d.tab[ax];
      }
    }
      P_Tab.bits._.En = 0;
  }
  return ;
}
void Wait_Time( void)
{
 /* word ax;
  ax = Timer1_Ovr - CW_time;
  if ( (u)ax > _Sec(0.1) ) L_sts._.send = 1;
  if ( L_sts._.send == 1)
  {
    if ( ++CW_count < 8 ) output_c ( 0xff );
    else
    {
      L_sts._.send = 0;
      CW_time = Timer1_Ovr;
      CW_count = 0;
    }
  }*/
  return ;
}
void LanOscl(void )
{
  word i, j, time;
  //double *tst =  &fr1;
  if (UartCAN_Rx._.LOsc_start != 0)
  {
    if (!UartCAN_Rx._.LOsc_dataR)
    {
      
      //Загружаем переменные в зависимости от их типа
      for (i = 0, j = 0; i < 4; ++ i){
        if (OscPtrs[i] < FullSledTab_size){
          
          switch(FullSledTab[OscPtrs[i]].code._.type){
            case 1:     //byte
              LanOsclOut[j]   = *(b*)FullSledTab[OscPtrs[i]].addr;
              j += 8;              
                                   
              break;               
            case  2:   //word            
              LanOsclOut[j]   = *(b*)FullSledTab[OscPtrs[i]].addr;
              LanOsclOut[++j] = *((b*)(FullSledTab[OscPtrs[i]].addr)+1);
              j += 7;              
              break;               
            case 4 :   //long         
              LanOsclOut[j]   = *(b*)FullSledTab[OscPtrs[i]].addr;
              LanOsclOut[++j] = *((b*)FullSledTab[OscPtrs[i]].addr+1);
              LanOsclOut[++j] = *((b*)FullSledTab[OscPtrs[i]].addr+2);
              LanOsclOut[++j] = *((b*)FullSledTab[OscPtrs[i]].addr+3);
              j += 5;              
              break;               
            case 0:    //float  
              LanOsclOut[j]   = *(b*)FullSledTab[OscPtrs[i]].addr;
              LanOsclOut[++j] = *((b*)FullSledTab[OscPtrs[i]].addr+1);
              LanOsclOut[++j] = *((b*)FullSledTab[OscPtrs[i]].addr+2);
              LanOsclOut[++j] = *((b*)FullSledTab[OscPtrs[i]].addr+3);
              j+= 5;            
              break;            
                                
            case 3:  //double
              LanOsclOut[j]   = *(b*)FullSledTab[OscPtrs[i]].addr;
              LanOsclOut[++j] = *((b*)FullSledTab[OscPtrs[i]].addr+1);
              LanOsclOut[++j] = *((b*)FullSledTab[OscPtrs[i]].addr+2);
              LanOsclOut[++j] = *((b*)FullSledTab[OscPtrs[i]].addr+3);
              LanOsclOut[++j] = *((b*)FullSledTab[OscPtrs[i]].addr+4);
              LanOsclOut[++j] = *((b*)FullSledTab[OscPtrs[i]].addr+5);
              LanOsclOut[++j] = *((b*)FullSledTab[OscPtrs[i]].addr+6);
              LanOsclOut[++j] = *((b*)FullSledTab[OscPtrs[i]].addr+7);
              ++j;
              break;
          }
        }
        else{
          j+=8;
        }
      }
      time = timer1;
      LanOsclOut[j] = (b)(Timer1_fSec&0xff);
      LanOsclOut[++j] = (b)(Timer1_fSec>>8);
      LanOsclOut[++j] = (b)(_fSec(1)&0xff);
      LanOsclOut[++j] = (b)(_fSec(1)>>8);
      LanOsclOut[++j] = (b)(UartCAN_Tx.all&0xff);
      LanOsclOut[++j] = (b)(UartCAN_Tx.all>>8);
      
      Per_Osc = (float)(w)((u)(timer1 - TimeLanOsc))/(float)_MkSec(1000);
      TimeLanOsc = timer1;
      UartCAN_Rx._.LOsc_dataR = 1;
    }
 /*   else
    {
      TimeLanOsc = timer1;
    }*/
  }
  else
  {
       TimeLanOsc = timer1;
       UartCAN_Rx._.LOsc_dataR = 0;
       for (i = 0; i < 36; ++i){
         LanOsclOut[i] = 0;
       }

  }
}