//   код       число       передаваемые         контр.
// команды     байт          байты              сумма
//  1 байт     2 байта       n - байт           1 байт
//|_______|   |__| |__|   |__| |__| |__|  ...  |______|

//старшая тетрада - коды команды
//младшая тетрада - количество пробелов перед параметром
#define cod_CRLF       0x00 //команда с переводом строки + возврат каретки
#define cod_Work       0x10 //команда без перевода строки + возврат каретки
#define cod_Razd       0x20 //разделитель
#define cod_End        0xF0 //конец передачи

#define mWait _Sec ( 0.5 )  //время ожидания ответа

//-------------------------------------------------------------
word LS ( const char *s )
{
  word dlina ;

  for ( dlina = 0 ; s [ dlina ] != '\0' ; dlina++ ) ;
  return dlina ;
}

//-------------------------------------------------------------
void OutPut_str(char const* str, word in_len, byte* sum)
{
    word ax;
    byte bh;
    bh = Hb ( in_len ) ;
    output_c ( bh ) ;
    *sum -= bh ;
    bh = Lb ( in_len ) ;
    output_c ( bh ) ;
    *sum -= bh ;
    output_s ( str ) ;
    for ( ax = 0 ; ax <= in_len ; ax++ ) *sum -= str[ax] ;
}

//-------------------------------------------------------------
void Read_Ust ( void )
{
  static byte count ;     //счетчик
  static byte crs   ; //контрольная сумма
  byte len ;
  static word tmp ;
#if defined( _NET_IRQ) && !defined(_VPCH_)
  char const* str;
#endif
  register word ax , bx , cx , ex, t_ax, t_bx ;
  double dax, dbx;
  byte sig_old ;
  register lword lax ;

  enum { m0,m1,m2,m200,m201,m3,m4,m5,m6,m600,m601,m602,m603,m7,m8,m9,m10,m11,m12,m13,m14,m15,m16,m17,m18,m19,
         m20,m21,m22,m23,m24,m25,m26,m27,m28,m29,m30,m31,m32,m33,m34,m35,m36,
         m37,m38,m39,m40,m41,m42,m43,m44,m45,m46,m47,m48,m49,m50,m51,m52,m53,m54,m55,m56,m57,m58,m59,
         m60,m61
    #ifdef _RES_I2C  //_BTE_NEW
        ,mr1,mr2,mr3,mr4,mr5,mr6,mr7,mr8,mr9,mr10,mr11,mr12
    #endif
    #ifdef _NET_IRQ
        ,mn1,mn2,mn3,mn4,mn5,mn6,mn7,mn8,mn9,mn10,mn11,mn12,mn13,mn14,mn15,mn16,mn17,mn18,mn19,mn20,mn21,mn22
    #endif
       } ;

  if ( M_FirstCall == 1 )
  {
    //быстрый вывод
    m_ext = Pult_Prog_Addr ;// сохраняем код команды чтобы его не перебил
    if ( Mon.Pult == 1 ) Speed_Pult ( ) ; //  "Speed_Pult () "
    Pult_Prog_Addr = m_ext ;
    //------
    M_FirstCall = 0 ;
    output_c ( '$' ) ;//выдать ключевой код готовности данного режима ввода/вывода
    Label = m0 ;
    count = 0 ;
    crs = 0 ;
    m_time = Timer1_Ovr ; //засечь время
    return ;
  }

  switch ( Label )
  {
    //Исходное состояние
    default: Label = m0 ;
    case m0:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ;
               if ( m_ch == Return )  //Выход из этого режима
               {
end:
                 output_c ( cod_End ) ;
                 Pult_Prog_Addr = _MainPultProg ;
                 M_FirstCall = 1 ;
                 return ;
               }
               else Label = m1 ;
             }
             break ;
    case m1:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //передача имени агрегата
               output_c ( cod_CRLF ) ;
               crs -= cod_CRLF ;
               m_ext = (w)( sizeof ( _Agr_ ) - 1 + sizeof ( _Device_Name_ ) - 1 ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( _Agr_ ) ;
               for ( count = 0 ; count < sizeof ( _Agr_ ) ; count++ ) crs -= _Agr_ [ count ] ;
               output_s ( _Device_Name_ ) ;
               for ( count = 0 ; count < sizeof ( _Device_Name_ ) ; count++ ) crs -= _Device_Name_ [ count ] ;
               output_c ( crs ) ; //передача контрольной суммы
               m_time = Timer1_Ovr ; //засечь время
               Label = m2 ;
             }
             break ;
    case m2:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
#ifdef _DECIMAL_
                    Label = m200 ;
#else
                    Label = m3 ;
#endif
               else goto end ;
             }
             break ;
#ifdef _DECIMAL_
    case m200:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //передача имени агрегата
               output_c ( cod_CRLF ) ;
               crs -= cod_CRLF ;
               m_ext = (w)( sizeof ( _DecNum_ ) - 1 + sizeof ( _DECIMAL_ ) - 1 ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( _DecNum_ ) ;
               for ( count = 0 ; count < sizeof ( _DecNum_ ) ; count++ ) crs -= _DecNum_ [ count ] ;
               output_s ( _DECIMAL_ ) ;
               for ( count = 0 ; count < sizeof ( _DECIMAL_ ) ; count++ ) crs -= _DECIMAL_ [ count ] ;
               output_c ( crs ) ; //передача контрольной суммы
               m_time = Timer1_Ovr ; //засечь время
               Label = m201 ;
             }
             break ;
    case m201:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs ) Label = m3 ;
               else goto end ;
             }
             break ;
#endif
    case m3:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //передача имени объекта
               output_c ( cod_CRLF ) ;
               crs -= cod_CRLF ;
               if( _kol_obl > 1 )
               {
                    if ( copy_code_rezerv != 0 )
                    {
                      m_addr = LS ( Tabl_name_ust [ copy_code_rezerv - 1 ] ) ;
                      m_ext = (w)( sizeof ( _Obj_ ) - 1 + m_addr ) ;
                      len = Hb ( m_ext ) ;
                      output_c ( len ) ;
                      crs -= len ;
                      len = Lb ( m_ext ) ;
                      output_c ( len ) ;
                      crs -= len ;
                      output_s ( _Obj_ ) ;
                      for ( count = 0 ; count < sizeof ( _Obj_ ) ; count++ ) crs -= _Obj_ [ count ] ;
                      output_s ( Tabl_name_ust [ copy_code_rezerv - 1 ] ) ;
                      for ( count = 0 ; count <= (b)m_addr  ; count++ ) crs -= Tabl_name_ust [ copy_code_rezerv - 1 ] [ count ] ;
                    }
                    else
                    {
                      m_ext = (w)( sizeof ( _Obj_ ) - 1 + sizeof ( _AgregatOut_txt ) - 1 ) ;
                      len = Hb ( m_ext ) ;
                      output_c ( len ) ;
                      crs -= len ;
                      len = Lb ( m_ext ) ;
                      output_c ( len ) ;
                      crs -= len ;
                      output_s ( _Obj_ ) ;
                      for ( count = 0 ; count < sizeof ( _Obj_ ) ; count++ ) crs -= _Obj_ [ count ] ;
                      output_s ( _AgregatOut_txt ) ;
                      for ( count = 0 ; count < sizeof ( _AgregatOut_txt ) ; count++ ) crs -= _AgregatOut_txt [ count ] ;
                    }
               }
               else
               {
                    m_addr = LS ( Tabl_name_ust [ 0 ] ) ;
                    m_ext = (w)( sizeof ( _Obj_ ) - 1 + m_addr ) ;
                    len = Hb ( m_ext ) ;
                    output_c ( len ) ;
                    crs -= len ;
                    len = Lb ( m_ext ) ;
                    output_c ( len ) ;
                    crs -= len ;
                    output_s ( _Obj_ ) ;
                    for ( count = 0 ; count < sizeof ( _Obj_ ) ; count++ ) crs -= _Obj_ [ count ] ;
                    output_s ( Tabl_name_ust [ 0 ] ) ;
                    for ( count = 0 ; count <= (b)m_addr  ; count++ ) crs -= Tabl_name_ust [ 0 ] [ count ] ;
               }
               output_c ( crs ) ; //передача контрольной суммы
               m_time = Timer1_Ovr ; //засечь время
               Label = m4 ;
             }
             break ;
    case m4:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
#ifdef _PROGRAM_
                  Label = m5 ;
#else
                  Label = m600 ;
#endif
               }
               else goto end ;
             }
             break ;
#ifdef _PROGRAM_
    case m5:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //передача даты компиляции
               output_c ( cod_CRLF ) ;
               crs -= cod_CRLF ;
               m_ext = (w)( sizeof ( _Prog_ ) - 1 + sizeof ( _PROGRAM_ ) - 1 ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( _Prog_ ) ;
               for ( count = 0 ; count < sizeof ( _Prog_ ) ; count++ ) crs -= _Prog_ [ count ] ;
               output_s ( _PROGRAM_ ) ;
               for ( count = 0 ; count < sizeof ( _PROGRAM_ ) ; count++ ) crs -= _PROGRAM_ [ count ] ;
               output_c ( crs ) ; //передача контрольной суммы
               m_time = Timer1_Ovr ; //засечь время
               Label = m6 ;
             }
             break ;
    case m6:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs ) Label = m600 ;
               else goto end ;
             }
             break ;
#endif
    case m600:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //передача даты компиляции
               output_c ( cod_CRLF ) ;
               crs -= cod_CRLF ;
             //m_ext = (w)( sizeof ( _DT_ ) - 1 + sizeof ( __DATETIME__ ) - 1 ) ; // 23.03.2015 DAN для CM3
               m_ext = (w)( strlen ( _DT_ ) + strlen ( __DATETIME__ )) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( _DT_ ) ;
             //for ( count = 0 ; count < sizeof ( _DT_ ) ; count++ ) crs -= _DT_ [ count ] ; // 23.03.2015 DAN для CM3
               for ( count = 0 ; count < strlen( _DT_ ) ; count++ ) crs -= _DT_ [ count ] ;
               output_s ( __DATETIME__ ) ;
             //for ( count = 0 ; count < sizeof ( __DATETIME__ ) ; count++ ) crs -= __DATETIME__ [ count ] ; // 23.03.2015 DAN для CM3
               for ( count = 0 ; count < strlen ( __DATETIME__ ) ; count++ ) crs -= __DATETIME__ [ count ] ;
               output_c ( crs ) ; //передача контрольной суммы
               m_time = Timer1_Ovr ; //засечь время
               Label = m601 ;
             }
             break ;
    case m601:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs ) Label = m602 ;
               else goto end ;
             }
             break ;
    case m602:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //передача объёма i2c
               output_c ( cod_CRLF ) ;
               crs -= cod_CRLF ;
               switch ( _i2c_end)
               {
                 case 0x1fff:
                          m_ext = (w)( sizeof ( _Size_i2c_ ) - 1 + sizeof ( _Size_8kb_ ) - 1 ) ;
                          break ;
                 case 0x7fff:
                          m_ext = (w)( sizeof ( _Size_i2c_ ) - 1 + sizeof ( _Size_32kb_ ) - 1 ) ;
                          break ;
                 case 0xffff:
                          m_ext = (w)( sizeof ( _Size_i2c_ ) - 1 + sizeof ( _Size_64kb_ ) - 1 ) ;
                          break ;
#ifdef _CM3_ // у Fujitsu эта переменная типа "word" :
                 case 0x7ffff:
                          m_ext = (w)( sizeof ( _Size_i2c_ ) - 1 + sizeof ( _Size_512kb_ ) - 1 ) ;
                          break ;
#endif
                 default:
                          m_ext = (w)( sizeof ( _Size_i2c_ ) - 1 + sizeof ( _Size_No_ ) - 1 ) ;
                          break ;
               }
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( _Size_i2c_ ) ;
               for ( count = 0 ; count < sizeof ( _Size_i2c_ ) ; count++ ) crs -= _Size_i2c_ [ count ] ;
               switch ( _i2c_end)
               {
                 case 0x1fff:
                          output_s ( _Size_8kb_ ) ;
                          for ( count = 0 ; count < sizeof ( _Size_8kb_ ) ; count++ ) crs -= _Size_8kb_ [ count ] ;
                          break ;
                 case 0x7fff:
                          output_s ( _Size_32kb_ ) ;
                          for ( count = 0 ; count < sizeof ( _Size_32kb_ ) ; count++ ) crs -= _Size_32kb_ [ count ] ;
                          break ;
                 case 0xffff:
                          output_s ( _Size_64kb_ ) ;
                          for ( count = 0 ; count < sizeof ( _Size_64kb_ ) ; count++ ) crs -= _Size_64kb_ [ count ] ;
                          break ;
#ifdef _CM3_ // у Fujitsu эта переменная типа "word" :
                 case 0x7ffff:
                          output_s ( _Size_512kb_ ) ;
                          for ( count = 0 ; count < sizeof ( _Size_512kb_ ) ; count++ ) crs -= _Size_512kb_ [ count ] ;
                          break ;
#endif
                 default:
                          output_s ( _Size_No_ ) ;
                          for ( count = 0 ; count < sizeof ( _Size_No_ ) ; count++ ) crs -= _Size_No_ [ count ] ;
                          break ;
               }
               output_c ( crs ) ; //передача контрольной суммы
               m_time = Timer1_Ovr ; //засечь время
               Label = m603 ;
             }
             break ;
    case m603:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                #ifndef _NET_IRQ
                     Label = m7 ;
                #else
                     Label = mn1 ;
                #endif

               }
               else goto end ;
             }
             break ;
#if defined( _NET_IRQ) && !defined(_VPCH_)
    case mn1:

             if ( TestCompleted_Output ( ) != 0 )
             {
               //output_c ( cod_Razd ) ;
               //передача текста "Уставки"
               output_c ( cod_CRLF ) ;
               crs -= cod_CRLF ;
               //передача типа сети
                switch ( TypeNet )
                {
                    case _ModbusRTU_ :
                        str = _NetModbusRTU_;
                        ax =  (w)(sizeof(_NetModbusRTU_)-1) ;
                        break;
                    case _ModbusTCPIP_ :
                        str = _NetModbusTCPIP_;
                        ax =  (w)(sizeof(_NetModbusTCPIP_)-1) ;
                        break;
                    case _CANopen_ :
                        str = _NetCANopen_;
                        ax =  (w)(sizeof(_NetCANopen_)-1) ;
                        break;
                    case _RS485FD_ :
                        str = _NetRS485FD_;
                        ax =  (w)(sizeof(_NetRS485FD_)-1) ;
                        break;
                    case _ProfibusDP_ :
                        str = _NetProfibusDP_;
                        ax =  (w)(sizeof(_NetProfibusDP_)-1) ;
                        break;
                    case _NotDefined_ :
                        str = _NetNotDefine_;
                        ax =  (w)(sizeof(_NetNotDefine_)-1) ;
                        break;
                }
                OutPut_str(str, ax , &crs);
                output_c ( crs ) ;
               m_time = Timer1_Ovr ; //засечь время
               Label = mn2 ;
             }
             break ;
    case mn2:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs ) Label = m7 ;
               else goto end ;
             }
             break ;
#endif
    case m7:
             if ( TestCompleted_Output ( ) != 0 )
             {
               output_c ( cod_Razd ) ;
               //передача текста "Уставки"
               output_c ( cod_CRLF ) ;
               crs -= cod_CRLF ;
               m_ext = (w)( sizeof ( _Ust_ ) - 1 ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( _Ust_ ) ;
               for ( count = 0 ; count < sizeof ( _Ust_ ) ; count++ ) crs -= _Ust_ [ count ] ;
               output_c ( crs ) ; //передача контрольной суммы
               m_time = Timer1_Ovr ; //засечь время
               Label = m8 ;
             }
             break ;
    case m8:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                 m_index = 0 ;
                 Label = m9 ;
               }
               else goto end ;
             }
             break ;
    case m9:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //имя группы уставок с новой строки и впереди текста 3 пробелов
               sig_old = cod_CRLF | 0x03 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;
               m_ext = (w)LS ( Ustav [ m_index ].gruppa ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( Ustav [ m_index ].gruppa ) ;
               for ( count = 0 ; count <= (b)m_ext ; count++ ) crs -= Ustav [ m_index ].gruppa [ count ] ;
               output_c ( crs ) ;
               Label = m10 ;
               m_time = Timer1_Ovr ; //засечь время
             }
             break ;
    case m10:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                 m_addr = 0 ;
                 Label = m11 ;
               }
               else goto end ;
             }
             break ;
    case m11:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //имя уставки с новой строки и впереди текста 7 пробелов
               sig_old = cod_Work | 0x07 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;
               m_ext = (w)LS ( Ustav [ m_index ].adr_Gruop [ m_addr ].text ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( Ustav [ m_index ].adr_Gruop [ m_addr ].text ) ;
               for ( count = 0 ; count <= (b)m_ext ; count++ ) crs -= Ustav [ m_index ].adr_Gruop [ m_addr ].text [ count ]  ;
               output_c ( crs ) ;
               Label = m12 ;
               m_time = Timer1_Ovr ; //засечь время
             }
             break ;
    case m12:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                 count = 0 ;
                 Label = m13 ;
               }
               else goto end ;
             }
             break ;
    case m13:
             //для 'word' все равно: со знаком или без
             if ( Ustav [ m_index ].adr_Gruop [ m_addr ].code._.type == 2 )  ax = *(w*)Ustav [ m_index ].adr_Gruop [ m_addr ].addr ;
             else if (Ustav [ m_index ].adr_Gruop [ m_addr ].code._.type == 0  )   // double
             {
               dax = *(d*)Ustav [ m_index ].adr_Gruop [ m_addr ].addr ;
             }
             else if (Ustav [ m_index ].adr_Gruop [ m_addr ].code._.type == 3  )   // float
             {
               dax = *(f*)Ustav [ m_index ].adr_Gruop [ m_addr ].addr ;
             }
             else
             { //для 'byte' не все равно: со знаком или без
               ax = *(sb*)Ustav [ m_index ].adr_Gruop [ m_addr ].addr ;
               if ( Ustav [ m_index ].adr_Gruop [ m_addr ].code._.off_sign == 1 ) ax &= 0x00FF ; // срезаем знаковое расширение
             }
             cx = *(w*)Ustav [ m_index ].adr_Gruop [ m_addr ].abs_nom ;
             bx = Ustav [ m_index ].adr_Gruop [ m_addr ].nom ;
             if ((Ustav [ m_index ].adr_Gruop [ m_addr ].code._.type == 0) || (Ustav [ m_index ].adr_Gruop [ m_addr ].code._.type == 3))
             {
                if ( (sw)dax >= 0 )    sig_old = '+' ;
                else   dax = abs(dax) , sig_old = '-' ;
                //приводим содержимое ячейки к его номиналам
                //для отображения уставок типа '1/x'
                if ( Ustav [ m_index ].adr_Gruop [ m_addr ].code._.invert == 1 )
                {  //меняем местами ax и bx для инверсного деления.
                    dbx = dax ;
                    dax = (d)bx ;
                }
                else
                {
                    dbx = (d)bx;
                }
                dax *= (d)cx;
                dax /=dbx;
                lax = (lw)dax;
                m_dax = dax - (d)lax;
             }
             else
             {
                if ( Ustav [ m_index ].adr_Gruop [ m_addr ].code._.off_sign == 0 )
                { //Если распечатка со знаком - выделяем знак и модуль
                    if ( (sw)ax >= 0 )    sig_old = '+' ;
                    else   ax = ~ax + 1 , sig_old = '-' ;
                }

                //приводим содержимое ячейки к его номиналам
                //для отображения уставок типа '1/x'
                if ( Ustav [ m_index ].adr_Gruop [ m_addr ].code._.invert == 1 )
                {  //меняем местами ax и bx для инверсного деления.
                    ex = ax , ax = bx , bx = ex ;
                }
                lax =  (lw)ax * (lw)cx ;
                m_time = lax % bx ;
                //*(w*)&m_buff [ 0 ] = bx ;
                tmp = bx ;
                lax /= bx ;
                if ( lax > 0xffffu ) lax = 0xffff ;
             }
            //распечатка целой части - максимум 5 символов
            ex = 5 - Ustav [ m_index ].adr_Gruop [ m_addr ].code._.celoe ; //сколько первых символов пропустить
            if ( ex == 5 ) ex = 2 ; // для совместимости - если заданы были нули то принимаем формат "3.2"
            else if ( (sw)ex < 0 ) ex = 0 ;
            for ( ax = 10000 , cx = 0 ; ax != 1 ; ax /= 10 )
            {
                bx = lax / ax ;
                lax %= ax ;
                //пока идут первые нули - не выводим их:
                if ( bx == 0 && cx == 0 )
                { //а пропускаем лишние нулевые символы,
                    if ( ex != 0 ) ex-- ;
                    //или заменяем пробелами.
                    else m_buff [ count++ ] = ' ' ;//output_c ( ' ' ) ;
                }
                else
                {
                    if ( cx == 0 )
                    {
                    //if ( ( Ustav [ m_index ].adr_Gruop [ m_addr ].code._.zapr == 1 ) && ( _Ne_Rabota == 0 ) ) output_c ( '#' ) ;
                    if ( ( Ustav [ m_index ].adr_Gruop [ m_addr ].code._.off_sign == 0 ) ) m_buff [ count++ ] = sig_old ;// output_c ( sig_old ) ;
                    cx = 1 ;
                    }
                    //первые нули закончились.
                    m_buff [ count++ ] = (b)bx + 0x30 ;//output_c ( (b)bx + 0x30 ) ;
                }
            }
            //распечатываем последнюю цифру
            if ( cx == 0 )
            {
                //if ( ( Ustav [ m_index ].adr_Gruop [ m_addr ].code._.zapr == 1 ) && ( _Ne_Rabota == 0 ) ) output_c ( '#' ) ;
                if ( ( Ustav [ m_index ].adr_Gruop [ m_addr ].code._.off_sign == 0 ) ) m_buff [ count++ ] = sig_old ;//output_c ( sig_old ) ;
            }
            m_buff [ count++ ] = (b)(w)lax + 0x30 ;//output_c ( (b)(w)lax + 0x30 ) ;

             Label = m14 ;
             break ;
    case m14:
             //распечатка дробной части
             if ( Ustav [ m_index ].adr_Gruop [ m_addr ].code._.celoe == 0 ) ex = 2 ;// по умолчанию.
             else ex = Ustav [ m_index ].adr_Gruop [ m_addr ].code._.drob ;
             if ( ex != 0 )
             {
               m_buff [ count++ ] = '.' ;//output_c ( '.' ) ;
               if (Ustav [ m_index ].adr_Gruop [ m_addr ].code._.type == 0 || Ustav [ m_index ].adr_Gruop [ m_addr ].code._.type == 3)
               {
                    for ( ; ex != 0 ; ex-- )
                    {
                        m_dax *=10;
                        ax = (w)m_dax ;
                        m_dax -= (d)ax;
                        m_buff [ count++ ] = (b)ax + 0x30 ;//output_c ( (b)ax + 0x30 ) ;
                    }

               }
               else
               {
                    //bx = *(w*)&m_buff [ 0 ] ;
                    bx = tmp ;
                    lax = m_time ; // восстанавливаем остаток.
                    for ( ; ex != 0 ; ex-- )
                    {
                        lax *= 10 ;
                        ax = lax / bx ;
                        lax %= bx ;
                        m_buff [ count++ ] = (b)ax + 0x30 ;//output_c ( (b)ax + 0x30 ) ;
                    }
               }
             }
             Label = m15 ;
             break ;
    case m15:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //значение уставки на текущей строке с 3 пробелами перед текстом
               sig_old = cod_Work | 0x03 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;
               len = 0 ;
               output_c ( len ) ;
               crs -= len ;
               output_c ( count ) ;
               crs -= count ;
               len = count ;
               for ( count = 0 ; count < len ; count++ )
               {
                 output_c ( m_buff [ count ] ) ;
                 crs -= m_buff [ count ] ;
               }
               output_c ( crs ) ;
               Label = m16 ;
               m_time = Timer1_Ovr ; //засечь время
             }
             break ;
    case m16:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs ) Label = m17 ;
               else goto end ;
             }
             break ;
    case m17:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //единицы измерения уставки на текущей строке с 1 пробелом перед текстом
               sig_old = cod_CRLF | 0x01 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;
               m_ext = (w)LS ( Ustav [ m_index ].adr_Gruop [ m_addr ].ch ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( Ustav [ m_index ].adr_Gruop [ m_addr ].ch ) ;
               for ( count = 0 ; count <= (b)m_ext ; count++ ) crs -= Ustav [ m_index ].adr_Gruop [ m_addr ].ch [ count ]  ;
               output_c ( crs ) ;
               Label = m18 ;
               m_time = Timer1_Ovr ; //засечь время
             }
             break ;
    case m18:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
          #ifdef _INTERPRETER
                if    ( Str_quant.SetPoint == 0 ) t_ax=_MaxNumUstav-1 ;
                else                              t_ax=_MaxNumUstav ;

                if ( m_index == _MaxNumUstav - 1) t_bx = Str_quant.SetPoint;
                else                              t_bx = Ustav[ m_index ].kol_vo;
          #else
                t_ax = _MaxNumUstav;

                t_bx = Ustav[ m_index ].kol_vo;
          #endif
                 if ( ++m_addr < t_bx ) Label = m11 ;
                 else if ( ++m_index < t_ax )
                 {
                   m_addr = 0 ;
                   Label = m9 ;
                 }
                 else Label = m19 ;
               }
               else goto end ;
             }
             break ;
    case m19:
             if ( TestCompleted_Output ( ) != 0 )
             {
               output_c ( cod_Razd ) ;
               //передача текста "Битовые уставки"
               output_c ( cod_CRLF ) ;
               crs -= cod_CRLF ;
               m_ext = (w)( sizeof ( _BitUst_ ) - 1 ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( _BitUst_ ) ;
               for ( count = 0 ; count < sizeof ( _BitUst_ ) ; count++ ) crs -= _BitUst_ [ count ] ;
               output_c ( crs ) ; //передача контрольной суммы
               m_time = Timer1_Ovr ; //засечь время
               Label = m20 ;
             }
             break ;
    case m20:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                 m_index = 0 ;
                 Label = m21 ;
               }
               else goto end ;
             }
             break ;
    case m21:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //имя группы уставок с новой строки и впереди текста 3 пробелов
               sig_old = cod_CRLF | 0x03 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;
               m_ext = (w)LS ( bts [ m_index ].text ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( bts [ m_index ].text ) ;
               for ( count = 0 ; count <= (b)m_ext ; count++ ) crs -= bts [ m_index ].text [ count ] ;
               output_c ( crs ) ;
               Label = m22 ;
               m_time = Timer1_Ovr ; //засечь время
             }
             break ;
    case m22:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                 m_addr = 0 ;
                 Label = m23 ;
               }
               else goto end ;
             }
             break ;
    case m23:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //имя уставки с новой строки и впереди текста 7 пробелов
               sig_old = cod_Work | 0x07 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;
               m_ext = (w)LS ( bts [ m_index ].bit [ m_addr ] ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( bts [ m_index ].bit [ m_addr ] ) ;
               for ( count = 0 ; count <= (b)m_ext ; count++ ) crs -= bts [ m_index ].bit [ m_addr ] [ count ]  ;
               output_c ( crs ) ;
               Label = m24 ;
               m_time = Timer1_Ovr ; //засечь время
             }
             break ;
    case m24:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs ) Label = m25 ;
               else goto end ;
             }
             break ;
    case m25:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //значение уставки на текущей строке с 1 пробелом перед текстом
               sig_old = cod_CRLF | 0x01 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;
               m_ext = (w)( sizeof ( "= " ) - 1 + 1 ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               if ( bts [ m_index ].code._.type == 1 ) ax = *(b*)bts [ m_index ].addr ;
               else  ax = *(w*)bts [ m_index ].addr ;
               output_s ( "= " ) ;
               crs -= '=' ;
               crs -= ' ' ;
               if ( ( ax & bts [ m_index ].msk [ m_addr ] ) == 0 )
               {
                 output_c ( '0' ) ;
                 crs -= '0' ;
               }
               else
               {
                 output_c ( '1' ) ;
                 crs -= '1' ;
               }
               output_c ( crs ) ;
               Label = m26 ;
               m_time = Timer1_Ovr ; //засечь время
             }
             break ;
    case m26:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                 if ( ++m_addr < bts [ m_index ].n ) Label = m23 ;
                 else if ( ++m_index < _MaxNumBUst )
                 {
                   m_addr = 0 ;
                   Label = m21 ;
                 }
                 else
                 {
#if defined( _NET_IRQ) && !defined(_VPCH_)
                    if (TypeNet != _NotDefined_)
                    {
                      Label = mn3 ;
                    }
                    else
                    {
#endif
                      Label = m27 ;
#if defined( _NET_IRQ) && !defined(_VPCH_)
                    }
#endif
                 }
               }
               else goto end ;
             }
             break ;
#if defined( _NET_IRQ) && !defined(_VPCH_)
    case mn3:
             if ( TestCompleted_Output ( ) != 0 )
             {
               output_c ( cod_Razd ) ;
               //передача текста "Уставки"
               output_c ( cod_CRLF ) ;
               crs -= cod_CRLF ;

               m_ext = (w)( sizeof ( _NetUst_ ) - 1 ) ;

               OutPut_str( _NetUst_, m_ext , &crs);

               output_c ( crs ) ; //передача контрольной суммы
               m_time = Timer1_Ovr ; //засечь время
               Label = mn4 ;
             }
             break ;
    case mn4:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                 m_index = 0 ;
                 Label = mn5 ;
               }
               else goto end ;
             }
             break ;
    case mn5:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //имя группы уставок с новой строки и впереди текста 3 пробелов
               sig_old = cod_CRLF | 0x03 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;
               m_ext = (w)LS ( NetUstav [ m_index ].gruppa ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( NetUstav[ m_index ].gruppa ) ;
               for ( count = 0 ; count <= (b)m_ext ; count++ ) crs -= NetUstav[ m_index ].gruppa [ count ] ;
               output_c ( crs ) ;
               Label = mn6 ;
               m_time = Timer1_Ovr ; //засечь время
             }
             break ;
    case mn6:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                 m_addr = 0 ;
                 Label = mn7 ;
               }
               else goto end ;
             }
             break ;
    case mn7:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //имя уставки с новой строки и впереди текста 7 пробелов
               sig_old = cod_Work | 0x07 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;
               m_ext = (w)LS ( NetUstav[ m_index ].adr_Gruop [ m_addr ].text ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( NetUstav[ m_index ].adr_Gruop [ m_addr ].text ) ;
               for ( count = 0 ; count <= (b)m_ext ; count++ ) crs -= NetUstav [ m_index ].adr_Gruop [ m_addr ].text [ count ]  ;
               output_c ( crs ) ;
               Label = mn8 ;
               m_time = Timer1_Ovr ; //засечь время
             }
             break ;
    case mn8:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                 count = 0 ;
                 Label = mn9 ;
               }
               else goto end ;
             }
             break ;
    case mn9:
             //для 'word' все равно: со знаком или без
             if ( NetUstav [ m_index ].adr_Gruop [ m_addr ].code._.type == 2 )  ax = *(w*)NetUstav [ m_index ].adr_Gruop [ m_addr ].addr ;
             else if (NetUstav [ m_index ].adr_Gruop [ m_addr ].code._.type == 0  )
             {
               dax = *(d*)NetUstav[ m_index ].adr_Gruop [ m_addr ].addr ;
             }
             else if (NetUstav [ m_index ].adr_Gruop [ m_addr ].code._.type == 3  )
             {
               dax = *(f*)NetUstav[ m_index ].adr_Gruop [ m_addr ].addr ;
             }
             else
             { //для 'byte' не все равно: со знаком или без
               ax = *(sb*)NetUstav[ m_index ].adr_Gruop [ m_addr ].addr ;
               if ( NetUstav[ m_index ].adr_Gruop [ m_addr ].code._.off_sign == 1 ) ax &= 0x00FF ; // срезаем знаковое расширение
             }
             cx = *(w*)NetUstav [ m_index ].adr_Gruop [ m_addr ].abs_nom ;
             bx = NetUstav[ m_index ].adr_Gruop [ m_addr ].nom ;
             if ((NetUstav [ m_index ].adr_Gruop [ m_addr ].code._.type == 0) || (NetUstav [ m_index ].adr_Gruop [ m_addr ].code._.type == 3))
             {
                if ( (sw)dax >= 0 )    sig_old = '+' ;
                else   dax = fabs(dax) , sig_old = '-' ;
                //приводим содержимое ячейки к его номиналам
                //для отображения уставок типа '1/x'
                if ( NetUstav[ m_index ].adr_Gruop [ m_addr ].code._.invert == 1 )
                {  //меняем местами ax и bx для инверсного деления.
                    dbx = dax ;
                    dax = (d)bx ;
                }
                else
                {
                    dbx = (d)bx;
                }
                dax *= (d)cx;
                dax /=dbx;
                lax = (lw)dax;
                m_dax = dax - (d)lax;
             }
             else
             {
                if ( NetUstav[ m_index ].adr_Gruop [ m_addr ].code._.off_sign == 0 )
                { //Если распечатка со знаком - выделяем знак и модуль
                    if ( (sw)ax >= 0 )    sig_old = '+' ;
                    else   ax = ~ax + 1 , sig_old = '-' ;
                }

                //приводим содержимое ячейки к его номиналам
                //для отображения уставок типа '1/x'
                if ( NetUstav[ m_index ].adr_Gruop [ m_addr ].code._.invert == 1 )
                {  //меняем местами ax и bx для инверсного деления.
                    ex = ax , ax = bx , bx = ex ;
                }
                lax =  (lw)ax * (lw)cx ;
                m_time = lax % bx ;
                //*(w*)&m_buff [ 0 ] = bx ;
                tmp = bx ;
                lax /= bx ;
                if ( lax > 0xffffu ) lax = 0xffff ;
             }
            //распечатка целой части - максимум 5 символов
            ex = 5 - NetUstav [ m_index ].adr_Gruop [ m_addr ].code._.celoe ; //сколько первых символов пропустить
            if ( ex == 5 ) ex = 2 ; // для совместимости - если заданы были нули то принимаем формат "3.2"
            else if ( (sw)ex < 0 ) ex = 0 ;
            for ( ax = 10000 , cx = 0 ; ax != 1 ; ax /= 10 )
            {
                bx = lax / ax ;
                lax %= ax ;
                //пока идут первые нули - не выводим их:
                if ( bx == 0 && cx == 0 )
                { //а пропускаем лишние нулевые символы,
                    if ( ex != 0 ) ex-- ;
                    //или заменяем пробелами.
                    else m_buff [ count++ ] = ' ' ;//output_c ( ' ' ) ;
                }
                else
                {
                    if ( cx == 0 )
                    {
                        if ( ( NetUstav[ m_index ].adr_Gruop [ m_addr ].code._.off_sign == 0 ) ) m_buff [ count++ ] = sig_old ;// output_c ( sig_old ) ;
                        cx = 1 ;
                    }
                    //первые нули закончились.
                    m_buff [ count++ ] = (b)bx + 0x30 ;//output_c ( (b)bx + 0x30 ) ;
                }
            }
            //распечатываем последнюю цифру
            if ( cx == 0 )
            {
                //if ( ( Ustav [ m_index ].adr_Gruop [ m_addr ].code._.zapr == 1 ) && ( _Ne_Rabota == 0 ) ) output_c ( '#' ) ;
                if ( ( NetUstav[ m_index ].adr_Gruop [ m_addr ].code._.off_sign == 0 ) ) m_buff [ count++ ] = sig_old ;//output_c ( sig_old ) ;
            }
            m_buff [ count++ ] = (b)(w)lax + 0x30 ;//output_c ( (b)(w)lax + 0x30 ) ;

             Label = mn10;
             break ;
    case mn10:
             //распечатка дробной части
             if ( NetUstav[ m_index ].adr_Gruop [ m_addr ].code._.celoe == 0 ) ex = 2 ;// по умолчанию.
             else ex = NetUstav[ m_index ].adr_Gruop [ m_addr ].code._.drob ;
             if ( ex != 0 )
             {
               m_buff [ count++ ] = '.' ;//output_c ( '.' ) ;
               if ((NetUstav [ m_index ].adr_Gruop [ m_addr ].code._.type == 0) || (NetUstav [ m_index ].adr_Gruop [ m_addr ].code._.type == 3))
               {
                    for ( ; ex != 0 ; ex-- )
                    {
                        m_dax *=10;
                        ax = (w)m_dax ;
                        m_buff [ count++ ] = (b)ax + 0x30 ;//output_c ( (b)ax + 0x30 ) ;
                    }

               }
               else
               {
                    //bx = *(w*)&m_buff [ 0 ] ;
                    bx = tmp ;
                    lax = m_time ; // восстанавливаем остаток.
                    for ( ; ex != 0 ; ex-- )
                    {
                        lax *= 10 ;
                        ax = lax / bx ;
                        lax %= bx ;
                        m_buff [ count++ ] = (b)ax + 0x30 ;//output_c ( (b)ax + 0x30 ) ;
                    }
               }
             }
             Label = mn11 ;
             break ;
    case mn11:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //значение уставки на текущей строке с 3 пробелами перед текстом
               sig_old = cod_Work | 0x03 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;
               len = 0 ;
               output_c ( len ) ;
               crs -= len ;
               output_c ( count ) ;
               crs -= count ;
               len = count ;
               for ( count = 0 ; count < len ; count++ )
               {
                 output_c ( m_buff [ count ] ) ;
                 crs -= m_buff [ count ] ;
               }
               output_c ( crs ) ;
               Label = mn12 ;
               m_time = Timer1_Ovr ; //засечь время
             }
             break ;
    case mn12:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs ) Label = mn13 ;
               else goto end ;
             }
             break ;
    case mn13:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //единицы измерения уставки на текущей строке с 1 пробелом перед текстом
               sig_old = cod_CRLF | 0x01 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;
               m_ext = (w)LS ( NetUstav[ m_index ].adr_Gruop [ m_addr ].ch ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( NetUstav[ m_index ].adr_Gruop [ m_addr ].ch ) ;
               for ( count = 0 ; count <= (b)m_ext ; count++ ) crs -= NetUstav[ m_index ].adr_Gruop [ m_addr ].ch [ count ]  ;
               output_c ( crs ) ;
               Label = mn14 ;
               m_time = Timer1_Ovr ; //засечь время
             }
             break ;
    case mn14:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                t_ax = NetNumUstav;

                t_bx = NetUstav[ m_index ].kol_vo;
                 if ( ++m_addr < t_bx ) Label = mn7 ;
                 else if ( ++m_index < t_ax )
                 {
                   m_addr = 0 ;
                   Label = mn5 ;
                 }
                 else Label = mn15 ;
               }
               else goto end ;
             }
             break ;
    case mn15:
             if ( TestCompleted_Output ( ) != 0 )
             {
               output_c ( cod_Razd ) ;
               //передача текста "Битовые уставки"
               output_c ( cod_CRLF ) ;
               crs -= cod_CRLF ;
               m_ext = (w)( sizeof ( _NetBitUst_ ) - 1 ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( _NetBitUst_ ) ;
               for ( count = 0 ; count < sizeof ( _NetBitUst_ ) ; count++ ) crs -= _NetBitUst_[ count ] ;
               output_c ( crs ) ; //передача контрольной суммы
               m_time = Timer1_Ovr ; //засечь время
               Label = mn16 ;
             }
             break ;
    case mn16:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                 m_index = 0 ;
                 Label = mn17 ;
               }
               else goto end ;
             }
             break ;
    case mn17:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //имя группы уставок с новой строки и впереди текста 3 пробелов
               sig_old = cod_CRLF | 0x03 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;
               m_ext = (w)LS ( Netbts[ m_index ].text ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( Netbts[ m_index ].text ) ;
               for ( count = 0 ; count <= (b)m_ext ; count++ ) crs -= Netbts[ m_index ].text [ count ] ;
               output_c ( crs ) ;
               Label = mn18 ;
               m_time = Timer1_Ovr ; //засечь время
             }
             break ;
    case mn18:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                 m_addr = 0 ;
                 Label = mn19 ;
               }
               else goto end ;
             }
             break ;
    case mn19:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //имя уставки с новой строки и впереди текста 7 пробелов
               sig_old = cod_Work | 0x07 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;
               m_ext = (w)LS ( Netbts[ m_index ].bit [ m_addr ] ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( Netbts[ m_index ].bit [ m_addr ] ) ;
               for ( count = 0 ; count <= (b)m_ext ; count++ ) crs -= Netbts[ m_index ].bit [ m_addr ] [ count ]  ;
               output_c ( crs ) ;
               Label = mn20 ;
               m_time = Timer1_Ovr ; //засечь время
             }
             break ;
    case mn20:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs ) Label = mn21 ;
               else goto end ;
             }
             break ;
    case mn21:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //значение уставки на текущей строке с 1 пробелом перед текстом
               sig_old = cod_CRLF | 0x01 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;
               m_ext = (w)( sizeof ( "= " ) - 1 + 1 ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               if ( Netbts [ m_index ].code._.type == 1 ) ax = *(b*)Netbts [ m_index ].addr ;
               else  ax = *(w*)Netbts [ m_index ].addr ;
               output_s ( "= " ) ;
               crs -= '=' ;
               crs -= ' ' ;
               if ( ( ax & Netbts[ m_index ].msk [ m_addr ] ) == 0 )
               {
                 output_c ( '0' ) ;
                 crs -= '0' ;
               }
               else
               {
                 output_c ( '1' ) ;
                 crs -= '1' ;
               }
               output_c ( crs ) ;
               Label = mn22 ;
               m_time = Timer1_Ovr ; //засечь время
             }
             break ;
    case mn22:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                 if ( ++m_addr < Netbts[ m_index ].n ) Label = mn19 ;
                 else if ( ++m_index < NetNumBUst )
                 {
                   m_addr = 0 ;
                   Label = mn17 ;
                 }
                 else Label = m27 ;
               }
               else goto end ;
             }
             break ;

#endif
    case m27:
             if ( TestCompleted_Output ( ) != 0 )
             {
               output_c ( cod_Razd ) ;
               //передача текста "Тест АЦП"
               output_c ( cod_CRLF ) ;
               crs -= cod_CRLF ;
               m_ext = (w)( sizeof ( _TstADC_ ) - 1 ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( _TstADC_ ) ;
               for ( count = 0 ; count < sizeof ( _TstADC_ ) ; count++ ) crs -= _TstADC_ [ count ] ;
               output_c ( crs ) ; //передача контрольной суммы
               m_time = Timer1_Ovr ; //засечь время
               Label = m28 ;
             }
             break ;
    case m28:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                 m_index = 0 ;
                 Label = m29 ;
               }
               else goto end ;
             }
             break ;
    case m29:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //имя аналогового входа с новой строки и впереди текста 3 пробелов
               sig_old = cod_Work | 0x03 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;
               m_ext = (w)LS ( Nstx [ m_index ].txt ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( Nstx [ m_index ].txt ) ;
               for ( count = 0 ; count <= (b)m_ext ; count++ ) crs -= Nstx [ m_index ].txt [ count ] ;
               output_c ( crs ) ; //передача контрольной суммы
               m_time = Timer1_Ovr ; //засечь время
               Label = m30 ;
             }
             break ;
    case m30:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs ) Label = m31 ;
               else goto end ;
             }
             break ;
    case m31:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //значение смещения на текущей строке с 2 пробелом перед текстом
               sig_old = cod_Work | 0x02 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;
               m_ext = (w)( sizeof ( _Smech_ ) - 1 + 1 + 1 + 1 + 1 + 1 ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( _Smech_ ) ;
               for ( count = 0 ; count < sizeof ( _Smech_ ) ; count++ ) crs -= _Smech_ [ count ] ;
  #ifndef _BTE_NEW
               ax = Nstx [ m_index ].ach->offset * 2 ;
  #else
                    // В BTE_NEW с 0 по 7  канал имеем смещение и знак относительно смещения + полный уровень АЦП =0...5 В. Измерять физич.
                    // единицы в вольтах есть возможность только на АЦП и уже смещенный сигнал
                    //           С 8 по 13 канал нет смещения и уровень АЦП по внутр пинанию контроллера +3,3 В
                  ax = Nstx[ m_index ].ach->offset ;
  #endif

               m_ch = ax / _AD_VOLT + 0x30 , ax %= _AD_VOLT ;
               output_c ( m_ch ) ;
               crs -= m_ch ;
               output_c ( '.' ) ;
               crs -= '.' ;
               ax *= 10 , m_ch = ax / _AD_VOLT + 0x30 , ax %= _AD_VOLT ;
               output_c ( m_ch ) ;
               crs -= m_ch ;
               ax *= 10 , m_ch = ax / _AD_VOLT + 0x30 , ax %= _AD_VOLT ;
               output_c ( m_ch ) ;
               crs -= m_ch ;
               ax *= 10 , m_ch = ax / _AD_VOLT + 0x30 ;
               output_c ( m_ch ) ;
               crs -= m_ch ;
               output_c ( crs ) ; //передача контрольной суммы
               m_time = Timer1_Ovr ; //засечь время
               Label = m32 ;
             }
             break ;
    case m32:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                 //Mon.Otkl_InOut = 1 ;
                 m_ext = _AD_BUSY ;
                 AD_Izm ( *Nstx [ m_index ].ach , &m_ext ) ;
                 Label = m33 ;
               }
               else goto end ;
             }
             break ;
    case m33:
             if ( m_ext == _AD_BUSY ) break ; // ожидание готовности измерения.
             //Преобразование рез.изм. в знаковое со смещением.
             mIzmData_Conversion ( m_ext , ax , *Nstx [ m_index ].ach ) ;
             if ( TestCompleted_Output ( ) != 0 )
             {
               //значение смещения на текущей строке с 2 пробелом перед текстом
               sig_old = cod_CRLF | 0x02 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;
               m_ext = (w)( sizeof ( _Up_ ) - 1 + 1 + 1 + 1 + 1 + 1 ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               //Вывод знака.
               if ( (sw)ax >= 0 )
               {
                 output_s ( _Up_ ) ;
                 for ( count = 0 ; count < sizeof ( _Up_ ) ; count++ ) crs -= _Up_ [ count ] ;
               }
               else
               {
                 output_s ( _Um_ ) ;
                 for ( count = 0 ; count < sizeof ( _Um_ ) ; count++ ) crs -= _Um_ [ count ] ;
                 ax = ~ax + 1 ;
               }
               //Приведение полученного измерения к масштабу
               // напряжения на входе платы ввода/вывода.
               // 205 - значение соотв. одному вольту в дискретах АЦП.
// 28.12.2023 В "obj_def.h" задаются двуполярные каналы из таблицы Nstx: "#define _Bipolar_Chanels_ADC(chanel) if(chanel== 1)".
// Аналогично ранее заданному "_BTE_NEW". Актуально для новых плат .050, .051.
#ifndef _Bipolar_Chanels_ADC
    #ifndef _BTE_NEW
               ax *= 2 ;
    #else
                    // В BTE_NEW с 0 по 7  канал имеем смещение и знак относительно смещения + полный уровень АЦП =0...5 В. Измерять физич.
                    // единицы в вольтах есть возможность только на АЦП и уже смещенный сигнал
                    //           С 8 по 13 канал нет смещения и уровень АЦП по внутр пинанию контроллера +3,3 В
               if (m_index >= 8 ) ax *= 2 ;
    #endif
#else
               _Bipolar_Chanels_ADC( m_index ) ax *= 2 ;
#endif      // _Bipolar_Chanels_ADC

               //Вывод целой части: при 205-ти 'ax' - не выйдет за 9.98
               m_ch = ax / _AD_VOLT + 0x30 , ax %= _AD_VOLT ;
               output_c ( m_ch ) ;
               crs -= m_ch ;
               output_c ( '.' ) ;
               crs -= '.' ;
               //Вывод дробной части: достаточно 2-знака, т.к.
               //дискрета АЦП приведенная ко входу ячейки ввода/вывода равна +-10мВ.
               ax *= 10 , m_ch = ax / _AD_VOLT + 0x30 , ax %= _AD_VOLT ;
               output_c ( m_ch ) ;
               crs -= m_ch ;
               ax *= 10 , m_ch = ax / _AD_VOLT + 0x30 , ax %= _AD_VOLT ;
               output_c ( m_ch ) ;
               crs -= m_ch ;
               ax *= 10 , m_ch = ax / _AD_VOLT + 0x30 ;
               output_c ( m_ch ) ;
               crs -= m_ch ;
               output_c ( crs ) ; //передача контрольной суммы
               m_time = Timer1_Ovr ; //засечь время
               Label = m34 ;
             }
             break ;
    case m34:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                 if ( ++m_index < _Nm ) Label = m29 ;
                 else
                 {
#ifndef _NO_DAC
                   //Mon.Otkl_InOut = 0 ;
                   Label = m35 ;
#else
   #ifndef _NO_LINK
                   Label = m46 ;
   #else
        #ifdef _JOURNAL
                   Label = m50 ;
        #else
                   goto end ;
        #endif
   #endif
#endif
                 }
               }
               else goto end ;
             }
             break ;
#ifndef _NO_DAC
    case m35:
             if ( TestCompleted_Output ( ) != 0 )
             {
               output_c ( cod_Razd ) ;
               //передача текста "Вывод на ЦАП"
               output_c ( cod_CRLF ) ;
               crs -= cod_CRLF ;
               m_ext = (w)( sizeof ( _VivDAC_ ) - 1 ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( _VivDAC_ ) ;
               for ( count = 0 ; count < sizeof ( _VivDAC_ ) ; count++ ) crs -= _VivDAC_ [ count ] ;
               output_c ( crs ) ; //передача контрольной суммы
               m_time = Timer1_Ovr ; //засечь время
               Label = m36 ;
             }
             break ;
    case m36:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                 m_index = 0 ;
                 Label = m37 ;
               }
               else goto end ;
             }
             break ;
    case m37:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //с новой строки и впереди текста 3 пробелов
               sig_old = cod_CRLF | 0x03 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;
               m_ext = (w)( LS ( DAC_tab1 [ m_index ].txt ) + sizeof ( _Pusto_ ) - 1  + LS ( DAC_tab2 [ DAC_tab1 [ m_index ].p->var_num ].txt ) ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( DAC_tab1 [ m_index ].txt ) ;
               for ( count = 0 ; count <= (b)LS ( DAC_tab1 [ m_index ].txt ) ; count++ ) crs -= DAC_tab1 [ m_index ].txt [ count ] ;
               output_s ( _Pusto_ ) ;
               for ( count = 0 ; count < sizeof ( _Pusto_ ) ; count++ ) crs -= _Pusto_ [ count ] ;
               output_s ( DAC_tab2 [ DAC_tab1 [ m_index ].p->var_num ].txt ) ;
               for ( count = 0 ; count <= (b)LS ( DAC_tab2 [ DAC_tab1 [ m_index ].p->var_num ].txt ) ; count++ ) crs -= DAC_tab2 [ DAC_tab1 [ m_index ].p->var_num ].txt [ count ] ;
               output_c ( crs ) ; //передача контрольной суммы
               m_time = Timer1_Ovr ; //засечь время
               Label = m38 ;
             }
             break ;
    case m38:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                 if ( ++m_index < _DAC_Ntab1 ) Label = m37 ;
                 else
                 {
   #ifdef _DAC_OFFSET
                   Label = m39 ;
   #else
      #ifndef _NO_LINK
                   Label = m46 ;
      #else
         #ifdef _JOURNAL
                   Label = m50 ;
         #else
                   goto end ;
         #endif
      #endif
   #endif
                 }
               }
               else goto end ;
             }
             break ;
   #ifdef _DAC_OFFSET
    case m39:
             if ( TestCompleted_Output ( ) != 0 )
             {
               output_c ( cod_Razd ) ;
               //передача текста "Смещение ЦАП"
               output_c ( cod_CRLF ) ;
               crs -= cod_CRLF ;
               m_ext = (w)( sizeof ( _SmDAC_ ) - 1 ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( _SmDAC_ ) ;
               for ( count = 0 ; count < sizeof ( _SmDAC_ ) ; count++ ) crs -= _SmDAC_ [ count ] ;
               output_c ( crs ) ; //передача контрольной суммы
               m_time = Timer1_Ovr ; //засечь время
               Label = m40 ;
             }
             break ;
    case m40:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                 m_index = 0 ;
                 Label = m41 ;
               }
               else goto end ;
             }
             break ;
    case m41:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //с новой строки и впереди текста 3 пробелов
               sig_old = cod_Work | 0x03 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;
               m_ext = (w)LS ( DAC_tab1 [ m_index ].txt ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( DAC_tab1 [ m_index ].txt ) ;
               for ( count = 0 ; count <= (b)LS ( DAC_tab1 [ m_index ].txt ) ; count++ ) crs -= DAC_tab1 [ m_index ].txt [ count ] ;
               output_c ( crs ) ; //передача контрольной суммы
               m_time = Timer1_Ovr ; //засечь время
               Label = m42 ;
             }
             break ;
    case m42:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                 count = 0 ;
                 Label = m43 ;
               }
               else goto end ;
             }
             break ;
    case m43:
             // знаковое смещение в дискретах :
             ax = DAC_tab1 [ m_index ].p->offset ;
             // Определение знака :
             if ( (sw)ax >= 0 )  m_buff [ count++ ] = '+' ;//output_s ( " См = +" ) ;
             else
             {
               m_buff [ count++ ] = '-' ;//output_s ( " См = -" ) ;
               ax = ~ax + 1 ;
             }
             bx = _DAC_setka_max / 100 ;  // дискрет/процент - 1 единица .
             cx = ax % bx ; // остаток от деления уставки в дискретах
                            // на 1 единицу ( дискрет/процент ) .
             ax /= bx ;     // перевод из дискрет в проценты .
             m_ch = ax / 100 + 0x30 ;
             ax %= 100 ;
             m_buff [ count++ ] = m_ch ;//  output_c ( m_ch ) ;       // вывод первой цифры - сотен .
             m_ch = ax / 10 + 0x30  ;
             ax %= 10 ;
             m_buff [ count++ ] = m_ch ;//  output_c ( m_ch ) ;       // вывод второй цифры - десятков .
             m_buff [ count++ ] = ax + 0x30 ;//  output_c ( ax + 0x30 ) ;  // вывод третьей цифры - единиц .
             m_buff [ count++ ] = '.' ;//  output_c ( '.' ) ;
             cx *= 10 ;
             m_ch = cx / bx ;
             m_buff [ count++ ] = m_ch + 0x30 ;//  output_c ( m_ch + 0x30 ) ; // вывод дробной части .
             m_buff [ count++ ] = '%' ;//  output_s ( "% " ) ;
             Label = m44 ;
             break ;
    case m44:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //значение уставки на текущей строке с 3 пробелами перед текстом
               sig_old = cod_CRLF | 0x03 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;
               len = 0 ;
               output_c ( len ) ;
               crs -= len ;
               output_c ( count ) ;
               crs -= count ;
               len = count ;
               for ( count = 0 ; count < len ; count++ )
               {
                 output_c ( m_buff [ count ] ) ;
                 crs -= m_buff [ count ] ;
               }
               output_c ( crs ) ;
               Label = m45 ;
               m_time = Timer1_Ovr ; //засечь время
             }
             break ;
    case m45:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                 if ( ++m_index < _DAC_Ntab1 ) Label = m41 ;
      #ifndef _NO_LINK
                 else Label = m46 ;
      #else
        #ifdef _JOURNAL
                 else Label = m50 ;
        #else
                 else goto end ;
        #endif
      #endif
               }
               else goto end ;
             }
             break ;
   #endif
#endif
#ifndef _NO_LINK
    case m46:
             if ( TestCompleted_Output ( ) != 0 )
             {
               output_c ( cod_Razd ) ;
               //передача текста "Переменные следа"
               output_c ( cod_CRLF ) ;
               crs -= cod_CRLF ;
               m_ext = (w)( sizeof ( _VarSled_ ) - 1 ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( _VarSled_ ) ;
               for ( count = 0 ; count < sizeof ( _VarSled_ ) ; count++ ) crs -= _VarSled_ [ count ] ;
               output_c ( crs ) ; //передача контрольной суммы
               m_time = Timer1_Ovr ; //засечь время
               Label = m47 ;
             }
             break ;
    case m47:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                 m_index = 0 ;
                 Label = m48 ;
               }
               else goto end ;
             }
             break ;
    case m48:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //с новой строки и впереди текста 3 пробелов
               sig_old = cod_CRLF | 0x03 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;
               m_ext = (w)( LS ( sled.tab [ m_index ].txt ) ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( sled.tab [ m_index ].txt ) ;
               for ( count = 0 ; count <= (b)LS ( sled.tab [ m_index ].txt ) ; count++ ) crs -= sled.tab [ m_index ].txt [ count ] ;
               output_c ( crs ) ; //передача контрольной суммы
               m_time = Timer1_Ovr ; //засечь время
               Label = m49 ;
             }
             break ;
    case m49:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                 if ( ++m_index < sled.n_kanal ) Label = m48 ;
           #ifdef _JOURNAL
                 else Label = m50 ;
           #else
                 else goto end ;
           #endif
               }
               else goto end ;
             }
             break ;
#endif

#ifdef _JOURNAL
    case m50:
             if ( TestCompleted_Output ( ) != 0 )
             {
               output_c ( cod_Razd ) ;
               //передача текста "Переменные журнала"
               output_c ( cod_CRLF ) ;
               crs -= cod_CRLF ;
               m_ext = (w)( sizeof ( _VarJrn_ ) - 1 ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( _VarJrn_ ) ;
               for ( count = 0 ; count < sizeof ( _VarJrn_ ) ; count++ ) crs -= _VarJrn_ [ count ] ;
               output_c ( crs ) ; //передача контрольной суммы
               m_time = Timer1_Ovr ; //засечь время
               Label = m51 ;
             }
             break ;
    case m51:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                 m_index = 0 ;
                 Label = m52 ;
               }
               else goto end ;
             }
             break ;
    case m52:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //с новой строки и впереди текста 3 пробелов
               // 22.10.2012 13:38 Проверка на случай, если имя переменной из таблицы уставок журнала отсутствует
               // в полной таблице журнала
               if( TabJrn.TabVar [ m_index ].name[ 0 ] == '?' ) sig_old = cod_CRLF | 0x03 ;
               else sig_old = cod_Work | 0x03 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;
               m_ext = (w)( LS ( TabJrn.TabVar [ m_index ].name ) ) ; // имя переменной журнала
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( TabJrn.TabVar [ m_index ].name ) ;
               for ( count = 0 ; count <= (b)LS ( TabJrn.TabVar [ m_index ].name ) ; count++ ) crs -= TabJrn.TabVar [ m_index ].name [ count ] ;
               output_c ( crs ) ; //передача контрольной суммы
               m_time = Timer1_Ovr ; //засечь время
               Label = m53 ;
             }
             break ;
    case m53:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {                                                   // 22.10.2012 13:54
                 if( TabJrn.TabVar [ m_index ].name[ 0 ] == '?' )  // если такой переменной в полной таблице нет, то чтобы
                 {                                                 // не выводился в отчет по уставкам мусор и не затиралась
                   if ( ++m_index < TabJrn.n_kanal ) Label = m52 ; // память (как оказалось в зашивке Xарьковского возб.-ля
                   else goto end ;                                 // "замирал" вывод, а может и ещё что-то похуже), выводим
                 }                                                 // только имя переменной (отсутствующей в полной таблице)
                 else Label = m54 ;
               }
               else goto end ;
             }
             break ;
    case m54:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //условие на текущей строке с 2 пробелами перед текстом
               sig_old = cod_Work | 0x02 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;

               dptr = &FullJrnTab[ JrnData.tab[ m_index ] ];

               // переменная аналоговая или сформиравана битовыми полями
               if ( dptr->code._.ad == 0 || dptr->code._.ad == 2 )  //аналоговая переменная
               {
                 for ( ax = 0; ax < Menu3_size; ax++ ) //поиск текста условия
                 {
                   if ( TabJrn.TabVar [ m_index ].uslovie == Menu3[ ax ].label )  break;
                 }
                 m_ext = (w)( LS ( Menu3[ ax ].txt ) ) ; // имя переменной журнала
                 len = Hb ( m_ext ) ;
                 output_c ( len ) ;
                 crs -= len ;
                 len = Lb ( m_ext ) ;
                 output_c ( len ) ;
                 crs -= len ;
                 output_s ( Menu3[ ax ].txt ) ;
                 for ( count = 0 ; count <= (b)LS ( Menu3[ ax ].txt ) ; count++ ) crs -= Menu3[ ax ].txt [ count ] ;
               }
               else  //дискретная переменная
               {
                 m_ext = (w)( LS ( _Bit_ ) ) ; // имя переменной журнала
                 len = Hb ( m_ext ) ;
                 output_c ( len ) ;
                 crs -= len ;
                 len = Lb ( m_ext ) ;
                 output_c ( len ) ;
                 crs -= len ;
                 output_s ( _Bit_ ) ;
                 for ( count = 0 ; count <= (b)LS ( _Bit_ ) ; count++ ) crs -= _Bit_ [ count ] ;
               }
               output_c ( crs ) ;
               Label = m55 ;
               m_time = Timer1_Ovr ; //засечь время
             }
             break ;
    case m55:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                 count = 0;
                 Label = m56 ;
               }
               else goto end ;
             }
             break ;
    case m56:

            ax = TabJrn.TabVar[ m_index ].etalon;

            //Распечатка в 10-тичном виде
            if ( dptr->code._.ad == 2 || dptr->code._.ad == 1 ) bx = 1; // аналоговая переменная, сформированная битовыми полями или дисретная переменная 25.04.2012 10:49
            else bx = dptr->nom;
            cx = *(w*)dptr->abs_nom;
            if ( dptr->code._.off_sign == 0 )
            {    //Если распечатка со знаком - выделяем знак и модуль
              if ( (sw)ax >= 0 )   sig_old = '+';
              else   ax = ~ax + 1, sig_old = '-';
            }

            //приводим содержимое ячейки к его номиналам
            lax = (lw)ax * (lw)cx;
            m_addr = lax % bx;
            lax /= bx;
            if ( lax > 0xffffu) lax = 0xffff;

            //распечатка целой части - максимум 5 символов
            ex = 5 - dptr->code._.celoe; //сколько первых символов пропустить
            if ( ex == 5 ) ex = 2; //для совместимости - если заданы были нули то принимаем формат "3.2".
            else if ( (sw)ex < 0 ) ex = 0;
            for ( ax = 10000, cx = 0; ax != 1; ax /= 10 )
            {
              bx = lax / ax;
              lax %= ax;
              //пока идут первые нули - не выводим их:
              if ( bx == 0 && cx == 0 )
              {     //а пропускаем лишние нулевые символы,
                if ( ex != 0 ) ex--;
                //или заменяем пробелами
                else m_buff [ count++ ] = ' ' ;//output_c ( ' ' ) ;
              }
              else
              {
                if ( cx == 0 )
                {
                  if ( dptr->code._.off_sign == 0 ) m_buff [ count++ ] = sig_old; //output_c ( sig_old );
                  cx = 1;
                }
                //первые нули закончились
                m_buff [ count++ ] = (b)bx + 0x30; //output_c ( (b)bx + 0x30 );
              }
            }   //распечатываем последнюю цифру
            if ( cx == 0 )
            {
              if ( dptr->code._.off_sign == 0 ) m_buff [ count++ ] = sig_old; //output_c ( sig_old );
            }
            m_buff [ count++ ] = (b)(w)lax + 0x30; //output_c ( (b)(w)lax + 0x30 );
            Label = m57;
          break;

    case m57:    //распечатка дробной части
            if ( dptr->code._.celoe == 0 ) ex = 2;// по умолчанию.
            else ex = dptr->code._.drob;
            if ( ex != 0 )
            {
              m_buff [ count++ ] = '.'; //output_c ( '.' );
              bx = dptr->nom;
              lax = m_addr; //восстанавливаем остаток
              for ( ; ex != 0 ; ex-- )
              {
                lax *= 10;
                ax = lax / bx;
                lax %= bx;
                m_buff [ count++ ] = (b)ax + 0x30; //output_c ( (b)ax + 0x30 );
              }
            }
            Label = m58;
          break;

    case m58:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //значение уставки на текущей строке с 3 пробелами перед текстом
               sig_old = cod_Work | 0x03 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;
               len = 0 ;
               output_c ( len ) ;
               crs -= len ;
               output_c ( count ) ;
               crs -= count ;
               len = count ;
               for ( count = 0 ; count < len ; count++ )
               {
                 output_c ( m_buff [ count ] ) ;
                 crs -= m_buff [ count ] ;
               }
               output_c ( crs ) ;
               Label = m59 ;
               m_time = Timer1_Ovr ; //засечь время
             }
             break ;
    case m59:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs ) Label = m60 ;
               else goto end ;
             }
             break ;
    case m60:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //единицы измерения уставки на текущей строке с 1 пробелом перед текстом
               sig_old = cod_CRLF | 0x01 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;
               m_ext = (w)LS ( dptr->ch ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( dptr->ch ) ;
               for ( count = 0 ; count <= (b)m_ext ; count++ ) crs -= dptr->ch[ count ]  ;
               output_c ( crs ) ;
               Label = m61 ;
               m_time = Timer1_Ovr ; //засечь время
             }
             break ;
    case m61:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                 if ( ++m_index < TabJrn.n_kanal ) Label = m52 ;
           #ifdef _RES_I2C  //_BTE_NEW
                 else Label = mr1 ;
           #else
                 else goto end ;
           #endif
               }
               else goto end ;
             }
             break ;
#endif


#ifdef _RES_I2C  //_BTE_NEW
    case mr1:
             if ( TestCompleted_Output ( ) != 0 )
             {
               output_c ( cod_Razd ) ;
               //передача текста "Настройка резисторов:"
               output_c ( cod_CRLF ) ;
               crs -= cod_CRLF ;
               m_ext = (w)( sizeof ( _NAST_RES_ ) - 1 ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( _NAST_RES_ ) ;
               for ( count = 0 ; count < sizeof ( _NAST_RES_ ) ; count++ ) crs -= _NAST_RES_ [ count ] ;
               output_c ( crs ) ; //передача контрольной суммы
               m_time = Timer1_Ovr ; //засечь время
               Label = mr2 ;
             }
             break ;
    case mr2:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                 m_index = 0 ;
                 Label = mr3 ;
               }
               else goto end ;
             }
             break ;
    case mr3:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //передачем текс с номер резистора и его привязкой с новой строки и впереди текста 3 пробелов
               sig_old = cod_Work | 0x03 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;
               m_ext = (w)LS ( RES_com_tab[ m_index ].RES_tab.txt ) ; // Nstx [ m_index ].txt ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( RES_com_tab[ m_index ].RES_tab.txt /*  Nstx [ m_index ].txt */) ;
               for ( count = 0 ; count <= (b)m_ext ; count++ ) crs -= RES_com_tab[ m_index ].RES_tab.txt[ count ] ;  //Nstx [ m_index ].txt [ count ] ;
               output_c ( crs ) ; //передача контрольной суммы
               m_time = Timer1_Ovr ; //засечь время
               Label = mr4 ;
             }
             break ;
    case mr4:

             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                 Label = mr5 ;
               }
               else goto end ;
             }
             break ;
    case mr5:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //значение текущего сопротивления на текущей строке с 1 пробелом перед текстом
               sig_old = cod_Work | 0x01 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;
               m_ext = (w)( sizeof ( _R_ZAD_ ) - 1 + 1 + 1 + 1 + 1 + 1 + 1 ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( _R_ZAD_ ) ;
               for ( count = 0 ; count < sizeof ( _R_ZAD_ ) ; count++ ) crs -= _R_ZAD_ [ count ] ;


         #ifdef _RES_IND_INVERT
                  lax = ResCommon[ m_index ].ResConst.mashtab -
                        (lw)(( (lw)ResCommon[ m_index ].ResMemory.Res_RAM * ResCommon[ m_index ].ResConst.mashtab ) >> 8) ;
         #else
                  lax = (lw)(( (lw)ResCommon[ m_index ].ResMemory.Res_RAM * ResCommon[ m_index ].ResConst.mashtab ) >> 8) ;
         #endif
               m_ch = lax / 100000 + 0x30  ;
               lax %= 100000 ;
               output_c ( m_ch ) ;
               crs -= m_ch ;

               m_ch = lax / 10000 + 0x30  ;
               lax %= 10000 ;
               output_c ( m_ch ) ;
               crs -= m_ch ;

               m_ch = lax / 1000 + 0x30  ;
               lax %= 1000 ;
               output_c ( m_ch ) ;
               crs -= m_ch ;

               m_ch = lax / 100 + 0x30  ;
               lax %= 100 ;
               output_c ( m_ch ) ;
               crs -= m_ch ;

               m_ch = lax / 10 + 0x30  ;
               lax %= 10 ;
               output_c ( m_ch ) ;
               crs -= m_ch ;


               m_ch = lax + 0x30 ;
               output_c ( m_ch ) ;
               crs -= m_ch ;

               output_c ( crs ) ; //передача контрольной суммы
               m_time = Timer1_Ovr ; //засечь время
               Label = mr6 ;
             }
             break ;
    case mr6:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                 Label = mr7 ;
               }
               else goto end ;
             }
             break ;
    case mr7:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //значение прошлой установки сопротивления на текущей строке с 1 пробелом перед текстом
               sig_old = cod_Work | 0x01 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;
               m_ext = (w)( sizeof ( _R_ZAD_PRED_ ) - 1 + 1 + 1 + 1 + 1 + 1 + 1 ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( _R_ZAD_PRED_ ) ;
               for ( count = 0 ; count < sizeof ( _R_ZAD_PRED_ ) ; count++ ) crs -= _R_ZAD_PRED_ [ count ] ;

        #ifdef _RES_IND_INVERT
               lax = ResCommon[ m_index ].ResConst.mashtab -
                     (lw)(( (lw)ResCommon[ m_index ].ResMemory.Past_Save * ResCommon[ m_index ].ResConst.mashtab ) >> 8) ;
        #else
               lax = (lw)(( (lw)ResCommon[ m_index ].ResMemory.Past_Save * ResCommon[ m_index ].ResConst.mashtab ) >> 8) ;
        #endif

               m_ch = lax / 100000 + 0x30  ;
               lax %= 100000 ;
               output_c ( m_ch ) ;
               crs -= m_ch ;

               m_ch = lax / 10000 + 0x30  ;
               lax %= 10000 ;
               output_c ( m_ch ) ;
               crs -= m_ch ;

               m_ch = lax / 1000 + 0x30  ;
               lax %= 1000 ;
               output_c ( m_ch ) ;
               crs -= m_ch ;

               m_ch = lax / 100 + 0x30  ;
               lax %= 100 ;
               output_c ( m_ch ) ;
               crs -= m_ch ;

               m_ch = lax / 10 + 0x30  ;
               lax %= 10 ;
               output_c ( m_ch ) ;
               crs -= m_ch ;

               m_ch = lax + 0x30 ;
               output_c ( m_ch ) ;
               crs -= m_ch ;

               output_c ( crs ) ; //передача контрольной суммы
               m_time = Timer1_Ovr ; //засечь время
               Label = mr8 ;
             }
             break ;
    case mr8:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs ) Label = mr9 ;
               else goto end ;
             }
             break ;
    case mr9:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //Количество внесенных изменений настройки резистора на текущей строке с 1 пробелом перед текстом
               sig_old = cod_Work | 0x01 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;
               m_ext = (w)( sizeof ( _N_IZM_R_ ) - 1 + 1 + 1 + 1 ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( _N_IZM_R_ ) ;
               for ( count = 0 ; count < sizeof ( _N_IZM_R_ ) ; count++ ) crs -= _N_IZM_R_ [ count ] ;

               ax = ResCommon[ m_index ].ResMemory.Count_Save ;

               m_ch = ax / 100 + 0x30  ;
               ax %= 100 ;
               output_c ( m_ch ) ;
               crs -= m_ch ;

               m_ch = ax / 10 + 0x30  ;
               ax %= 10 ;
               output_c ( m_ch ) ;
               crs -= m_ch ;

               m_ch = ax + 0x30  ;
               output_c ( m_ch ) ;

               crs -= m_ch ;
               output_c ( crs ) ; //передача контрольной суммы
               m_time = Timer1_Ovr ; //засечь время
               Label = mr10 ;
             }
             break ;
     case mr10:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs ) Label = mr11 ;
               else goto end ;
             }
             break ;
     case mr11:
             if ( TestCompleted_Output ( ) != 0 )
             {
               //Предаем текст "(раз.)" - еденицы измерения прошлого вывода, на текущей строке с 1 пробелом перед текстом
               sig_old = cod_CRLF | 0x01 ;
               output_c ( sig_old ) ;
               crs -= sig_old ;
               m_ext = (w)( sizeof ( _IZM_RAZ_ ) - 1 ) ;
               len = Hb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               len = Lb ( m_ext ) ;
               output_c ( len ) ;
               crs -= len ;
               output_s ( _IZM_RAZ_ ) ;
               for ( count = 0 ; count < sizeof ( _IZM_RAZ_ ) ; count++ ) crs -= _IZM_RAZ_ [ count ] ;
                output_c ( crs ) ; //передача контрольной суммы
               m_time = Timer1_Ovr ; //засечь время
               Label = mr12 ;
             }
             break ;
    case mr12:
             //если за 0.5с ничего не поступило в приёмный буфер
             if ( (u)((w)( Timer1_Ovr - m_time )) > mWait ) goto end ;
             //выборка данных из буфера приёма до его опустошения
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( m_ch ) ; //получена контрольная сумма
               if ( m_ch == crs )
               {
                 if ( ++m_index < _RES_Ntab ) Label = mr3 ;
                 else
                 {
                   goto end ;
                 }
               }
               else goto end ;
             }
             break ;
#endif

  }
  Restart_Output ( ) ;

  return ;
}
