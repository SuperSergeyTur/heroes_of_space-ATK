// Драйвер для работы с резистором MCP4661




// инициализация шины для работы с RES
void MCP4661_Init( void )
{
          // Задем номер шины и скорсть шины
	I2C_Init( RES_CH_I2C, RES_CLOCK_FREQ_I2C);

	  //(Аппаратный номер шины с которой будем работать, режим в котором работает I2C, разрешаем работу шины I2C данного канала)
	I2C_Cmd( RES_CH_I2C, I2C_MASTER_MODE, ENABLE);

	return;
}


// РЕинициализация шины для работы с RES
void MCP4661_DeInit(void)
{
	  //Запрет работы шины данного канала I2C
	I2C_Cmd( RES_CH_I2C, I2C_MASTER_MODE, DISABLE);

	return;
}

///----------------------------------------------------------------------------------------------------------------------------///
///----------------------------------------------------------------------------------------------------------------------------///








  // Передача по I2C прошла без ошибок
#define I2C_TRANSFER_OK         0
  // При передаче данных по I2C возникли ошибки
#define I2C_TRANSFER_FAIL       1
  // Недопустимая длина для считывания данных
#define ERR_LENGTH_DATA_0       2



// Адрес I2C, внутренний адрес резистора с которого начинаем читать, количистао байт, куда ложить считанное
//( uint32_t Res_add_I2C, uint8_t *Add_Start_Read, uint32_t rx_length_data, uint8_t *data )
  // Считать данные начиная с указанного адресса
word GetData_fromAdd ( I2C_M_SETUP_Type *TransferCfg )
{

   if ( TransferCfg->rx_length == 0 || TransferCfg->tx_length == 0 ) return ERR_LENGTH_DATA_0 ;

     // Если количиство попыток достучатся к устройству не задано задедим его
   if ( TransferCfg->retransmissions_max == 0 ) TransferCfg->retransmissions_max = 3;

     // Производим чтение по I2C
   if ( I2C_MasterTransferData( RES_CH_I2C, TransferCfg, I2C_TRANSFER_POLLING ) == SUCCESS )
    {
     return I2C_TRANSFER_OK;
    }
   else
    {
     return I2C_TRANSFER_FAIL;
    }


}


  // Функция проверки занятости/свободности EEPROM адресов резистора для считывания и записи в них
  // (структура общих данных для каждого резистора, внутренний адрес микросхемы откуда необх. считать данные)
uint32_t GetResistorSts( struct Res_Common *Res_chenel_in, uint8_t ResMemAdd_Read )
{

   I2C_M_SETUP_Type transferResStsReg;
   uint8_t ResStsReg_Adr_tx[1];
   uint8_t ResStsReg_Data_rx[2];
   word Ret = 0 ;

     // Проверка занятости/свободности EEPROM для считывания и записи в них
     // Если обратились к одному из EEPROM адресов
   if ( ResMemAdd_Read == RES_WIPER_ROM || ResMemAdd_Read == RES_WIPER_EEP_COUNT_SAVE || ResMemAdd_Read == RES_WIPER_EEP_PAST_SAVE )
    {
       // Зададим аппаратный адрес резистора
     transferResStsReg.sl_addr7bit = MCP4661_adr | ((uint32_t)Res_chenel_in->ResConst.Add_channel & 0x07) ;
       // Задали адрес Status registra + команда читать из него
     ResStsReg_Adr_tx[0] = (uint8_t)(RES_STS_REG | RES_COMMAND_READ) ;
       // переложим подготовленное значения адреса и команды
     transferResStsReg.tx_data = ResStsReg_Adr_tx ;
       // количество передаваемых байт в посылке в режиме передатчика (количество байт до поторного старта)
     transferResStsReg.tx_length = 1;
       // указатель куда ложить принятые данные
     transferResStsReg.rx_data = ResStsReg_Data_rx;
       // количество принимаемых байт в посылке в режиме приемника
     transferResStsReg.rx_length = 2;
       // количество попыток отослать данные
     transferResStsReg.retransmissions_max = 3;
       // Производим чтение Status registra
    if ( GetData_fromAdd ( &transferResStsReg ) != I2C_TRANSFER_OK )
     {
        // Просто возвращаем ошибку
        // Запрет работы I2C
 //     MCP4661_DeInit( );
      Ret = MCP4661_RETFUNC_FAILED ;
     }
    else
     {
      Res_chenel_in->Sts_Reg = (((w)ResStsReg_Data_rx[0] << 8) & 0x0100 ) | ((w)ResStsReg_Data_rx[1] & 0x00ff ) ;
        // проверим статус на предмет свободности/занятости EEPROM регистров
      if ( (Res_chenel_in->Sts_Reg & RES_EEPROM_BUSY) == 0 ) Ret = MCP4661_RET_EEPROM_OK ;
      else                                                   Ret = MCP4661_RET_EEPROM_BUSY;
     }
    }

return Ret ;

}



  // Считать значение с указанного адреса
  // (структура общих данных для каждого резистора, внутренний адрес микросхемы откуда необх. считать данные)
word GetResistorValue( struct Res_Common *Res_chenel_in, uint8_t ResMemAdd_Read )
{
   I2C_M_SETUP_Type transferMCfg;

   uint8_t data_tx[1];
   uint8_t data_rx[2];

     // Разрешаем работу на I2C
   MCP4661_Init( );

       // Проверим занятое состояние для чтения/записи EEPROM (если занято выходим для попытки произвести считывание на след. цикле)
   Res_chenel_in->Res_Err_Ret = GetResistorSts( Res_chenel_in, ResMemAdd_Read ) ;
   if ( ( Res_chenel_in->Res_Err_Ret == MCP4661_RET_EEPROM_BUSY ) || ( Res_chenel_in->Res_Err_Ret == MCP4661_RETFUNC_FAILED ) )
    {
      // регистр памяти к которому идет обращение недоступен
        // Запрет работы I2C
      MCP4661_DeInit( );
      return (w)Res_chenel_in->Res_Err_Ret ;
    }


   // Подготовка данных для работы по I2C

     // Определим с каким 1-ым или 2-ым резистором надо работать (у каждого свои адреса в памяти)
   if ( Res_chenel_in->ResConst.Wiper_Num == 0 )
    {
       // С какой ячейкой памяти будем работать + команда читать из указанной ячейки
     data_tx[0] = (uint8_t)( ResMemAdd_Read | RES_COMMAND_READ );
    }
   else
    {
       // С какой ячейкой памяти будем работать + команда читать из указанной ячейки
     data_tx[0] = (uint8_t)(( ResMemAdd_Read + RES_MEM_ADD_WIPER1 ) | RES_COMMAND_READ) ;
   }

     // Зададим аппаратный адрес резистора
   transferMCfg.sl_addr7bit = MCP4661_adr | ((uint32_t)Res_chenel_in->ResConst.Add_channel & 0x07) ;
     // переложим подготовленное значения адреса и команды
   transferMCfg.tx_data = data_tx ;
     // количество передаваемых байт в посылке в режиме передатчика (количество байт до повторного старта)
   transferMCfg.tx_length = 1;

     // указатель куда ложить принятые данные
   transferMCfg.rx_data = data_rx;
     // количество принимаемых байт в посылке в режиме приемника
   transferMCfg.rx_length = 2;
     // количество попыток отослать данные
   transferMCfg.retransmissions_max = 3;

// Производим чтение по I2C
   if ( GetData_fromAdd ( &transferMCfg ) != I2C_TRANSFER_OK )
    {
       // Не перетираем значения резистора если прием не состоялся. Просто возвращаем ошибку
       // Запрет работы I2C
     MCP4661_DeInit( );
     return MCP4661_RETFUNC_FAILED ;
    }
   else
    {
        // Переложим принятые данные
      if      ( ResMemAdd_Read == RES_WIPER_RAM )            Res_chenel_in->ResMemory.Res_RAM =        (((w)data_rx[0] << 8) & 0x0100 ) |
                                                                                                        ((w)data_rx[1] & 0x00ff ) ;
      else if ( ResMemAdd_Read == RES_WIPER_ROM )            Res_chenel_in->ResMemory.Res_ROM =        (((w)data_rx[0] << 8) & 0x0100 ) |
                                                                                                        ((w)data_rx[1] & 0x00ff ) ;
      else if ( ResMemAdd_Read == RES_WIPER_EEP_COUNT_SAVE ) Res_chenel_in->ResMemory.Count_Save =     (((w)data_rx[0] << 8) & 0x0100 ) |
                                                                                                        ((w)data_rx[1] & 0x00ff ) ;
      else if ( ResMemAdd_Read == RES_WIPER_EEP_PAST_SAVE )  Res_chenel_in->ResMemory.Past_Save =      (((w)data_rx[0] << 8) & 0x0100 ) |
                                                                                                        ((w)data_rx[1] & 0x00ff ) ;



          // Запрет работы I2C
      MCP4661_DeInit( );
      return MCP4661_RETFUNC_OK;
     }


}








///----------------------------------------------------------------------------------------------------------------------------///
///----------------------------------------------------------------------------------------------------------------------------///
  // Записать значение в указанный адрес
  // (структура общих данных для каждого резистора, внутренний адрес микросхемы куда необх. записать данные)
word SetResistorValue(struct Res_Common *Res_chenel_in, uint8_t ResMemAdd_write   )
{

 //  uint8_t ResMemAdd[1] ;
   uint8_t data_write[2];
   I2C_M_SETUP_Type transferMCfg;

 //  I2C_M_SETUP_Type *TransferCfg;

    // Разрешаем работы I2C
   MCP4661_Init( );

     // Проверим занятое состояние для чтения/записи EEPROM (если занято выходим для попытки произвести считывание на след. цикле)
   Res_chenel_in->Res_Err_Ret = GetResistorSts( Res_chenel_in, ResMemAdd_write ) ;

   if ( ( Res_chenel_in->Res_Err_Ret == MCP4661_RET_EEPROM_BUSY ) || ( Res_chenel_in->Res_Err_Ret == MCP4661_RETFUNC_FAILED ) )
    {
        // регистр памяти к которому идет обращение недоступен
        // Запрет работы I2C
      MCP4661_DeInit( );
      return (w)Res_chenel_in->Res_Err_Ret ;
    }

      // Подготовка данных для записи данных в резистор


      // Подготовим передаваемые данные
    data_write[0] = (uint8_t)(( Res_chenel_in->Res_data_write >> 8 ) & 0x01) ;
    data_write[1] = (uint8_t)(  Res_chenel_in->Res_data_write & 0x00ff );

      // Определим в память какого резистора надо записывать
   if ( Res_chenel_in->ResConst.Wiper_Num == 0 )
    {
       // С какой ячейкой памяти будем работать + команда записать в указанную ячейку + в этом байте передается и 9 бит данных
     data_write[0] |= (uint8_t)( ResMemAdd_write | RES_COMMAND_WRITE ) ;
    }
   else
    {
       // С какой ячейкой памяти будем работать + команда записать в указанную ячейку + в этом байте передается и 9 бит данных
     data_write[0] |= (uint8_t)(( ResMemAdd_write + RES_MEM_ADD_WIPER1 ) | RES_COMMAND_WRITE );
    }

     // Зададим аппаратный адрес резистора
   transferMCfg.sl_addr7bit = MCP4661_adr | ((uint32_t)Res_chenel_in->ResConst.Add_channel & 0x07) ;
     // переложим подготовленное значения адреса, команды и 9-го бита данных
   transferMCfg.tx_data = data_write ;
     // количество передаваемых байт в посылке в режиме передатчика
   transferMCfg.tx_length = 2;

     // Нулевой указатель для отмены повторного старта I2C после записи
   transferMCfg.rx_data = NULL;
     // количество принимаемых байт в посылке
   transferMCfg.rx_length = 0;
     // количество попыток записать данные
   transferMCfg.retransmissions_max = 3;

  // Запишим данные в резистор, где
   // I2C_MasterTransferData( Аппаратный номер шины, данные, I2C_TRANSFER_POLLING: просто режим опроса без прерывания)

	if ( I2C_MasterTransferData( RES_CH_I2C, &transferMCfg, I2C_TRANSFER_POLLING ) == SUCCESS )
	{
            // Запрет работы I2C
          MCP4661_DeInit( );
          return MCP4661_RETFUNC_OK;
	}
	else
	{
            // Запрет работы I2C
          MCP4661_DeInit( );
	  return MCP4661_RETFUNC_FAILED;
	}

//return 0;

}





//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//




        //4. Если выход произвели через Enter:
        //   4.1 оставляем в RAM установленное значение
        //   4.2 считуем с ROM текущее значение и записуем его в EEPROM в адрес "Предыдущая настройка" проверяем что записали
        //   4.3 записуем в ROM выставленное значение в RAM
        //   4.4 перепроверяем что значения в RAM и ROM одинаковые
        //   4.5 считаем значение из счетчика если оно >= 0xff записываем в него 0x01 иначе просто инкримент
        //   4.6 запишем и сверим, что записано в счетчике с тем, что хотели записать


// Функция реализующая выход из меню настр. резистора по Enter с сохранением данных в память резистора

word SetResVal_Enter(struct Res_Common *Res_chenel_in )
{
                      // 0,  1,  2,   3,   4,   5,  6,    7,   8,   9,  10
           enum    { L0 = 0, L3, L5, L10, L12, L20, L22, L30, L32, L40, L42 };

  static   word    time ;
  static   word    Res_Label ;
  static   word    count_pov ;

             // проинициализируем перем, котор будем возвращать по return, значением незаконченного цикла записи в данной функции
             // ниже если ее никто не перетер значит ошибок для прекращения работы функции нет но она еще не закончена
  register  word    Ret = MCP4661_RET_RECORD_NO_FINISH ;
  //         word    ax ;




  switch ( Res_Label )
    {
      default: Res_Label = L0 ;

      case L0:
        count_pov = 0 ;

//--------------------------------------------------------------------------------------------------------------------//
      case L3:

  //   4.2.1 считуем с ROM текущее значение

               Res_chenel_in->Res_Err_Ret = GetResistorValue( Res_chenel_in, RES_WIPER_ROM );
               Ret = (w)Res_chenel_in->Res_Err_Ret ;
               time = timer1 ;
             ++count_pov ;
               Res_Label = L5 ;

       case L5:
         // Проверка на ошибки или занятость резистора для чтения/записи данных
               if ( Ret != ( MCP4661_RETFUNC_OK || MCP4661_RET_EEPROM_OK) )
                {
                  if ( Ret == MCP4661_RET_EEPROM_BUSY )
                   {
                     // если резистор занят произведем повторные попытки считать данные
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
                         // попытки достучатся к резистору исчерпаны
                       Ret = MCP4661_RET_CONNECT_OVERFLOW ;
                       break ;
                      }
                     }
                   }
                  else  // ошибка по которой нет смысла идти дальше
                   {
                    Res_Label = L0 ;
                    break ;
                   }
               }


  // 4.2.2  записуем его в EEPROM в адрес "Предыдущая настройка" проверяем что записали
       case L10:
                 // Подготовим данные для записи в указанный адрес
               Res_chenel_in->Res_data_write = Res_chenel_in->ResMemory.Res_ROM ;

                 // Запишем данные
               Res_chenel_in->Res_Err_Ret = SetResistorValue( Res_chenel_in, RES_WIPER_EEP_PAST_SAVE );
               Ret = (w)Res_chenel_in->Res_Err_Ret ;
                 // проверка на ошибку по которой нет смысла идти дальше
               if ( Ret == MCP4661_RETFUNC_FAILED )
                {
                 Res_Label = L0 ;
                 break ;
                }

               time = timer1 ;
               count_pov = 0 ;
               Res_Label = L12 ;
                 // запись в резистор длится 5-10 мс поэтому выходим. Подготовим возвращаемое значение - не закон цикл записи
               Ret = MCP4661_RET_RECORD_NO_FINISH ;
               break ;


        case L12:
                    // не закидуем запросы на считывание данных. В течении 5 мс это бесполезно не тратим врем
                if ( (u)(w)( timer1 - time ) <= _MkSec( 7*1000 ) )
                 {
                    // не прошло время торебуемое для записи
                  break ;
                 }
                else
                 {

  // 4.2.3 считуем и проверяем что записали в адрес "Предыдущая настройка"
                   Res_chenel_in->Res_Err_Ret = GetResistorValue( Res_chenel_in, RES_WIPER_EEP_PAST_SAVE ) ;
                   Ret = (w)Res_chenel_in->Res_Err_Ret ;

                   if ( ( Ret == MCP4661_RET_EEPROM_BUSY ) || ( Ret == MCP4661_RETFUNC_FAILED  ) )
                    {
                        // если резистор занят произведем повторные попытки считать данные
                      time = timer1 ;
                      if ( ++count_pov > 3 )
                       {
                        Res_Label = L0 ;
                          // попытки достучатся к резистору исчерпаны
                        Ret = MCP4661_RET_CONNECT_OVERFLOW ;
                        break ;
                       }
                    }
                 }

 // 4.2.4 Сврерим ячейки памяти ROM и EEPROM выделенную под "Предыдущую настройку"
                  // В данном месте ROM и данные запис. в EEPROM "Пред. зап." должны быть равны проверим это
                if ( Res_chenel_in->ResMemory.Past_Save == Res_chenel_in->ResMemory.Res_ROM )
                 {
                  Res_Label = L20 ;
                  // Данные не потерялись.  Перед выходом подготовим возвращаемое значение - не закон цикл записи
                  Ret = MCP4661_RET_RECORD_NO_FINISH ;
                  break ;
                 }
                else
                 {
                    // выявленна ошибка в записанных данных дальше нет смысла идти
                  Ret = MCP4661_RET_DATA_FAILED ;
                  Res_Label = L0 ;
                  break ;
                 }


         case L20:

//------------------------------------------------------------------------------------------------------------------------------//
  // 4.3 Значение из RAM записуем в ROM
                  // В переменной ResMemory.Res_RAM данного резистора уже лежит желаемое значение для записи в ROM
                  // произведем запись с проверкой

                  // Опрос статус регистра (на предмет занятого состояния ROM ячеек памяти)  нет смысла делать его сделали выше

  // 4.3.1 Подготовим данные для записи в указанный адрес
                Res_chenel_in->Res_data_write = Res_chenel_in->ResMemory.Res_RAM ;

                  // Запишем данные
                Res_chenel_in->Res_Err_Ret = SetResistorValue( Res_chenel_in, RES_WIPER_ROM );
                Ret = (w)Res_chenel_in->Res_Err_Ret ;
                  // проверка на ошибку по которой нет смысла идти дальше
                if ( Ret == MCP4661_RETFUNC_FAILED )
                 {
                  Res_Label = L0 ;
                  break ;
                 }
                  //
                time = timer1 ;
                count_pov = 0 ;
                Res_Label = L22 ;
                 // запись в резистор длится 5-10 мс поэтому выходим. Подготовим возвращаемое значение - не закон цикл записи
                Ret = MCP4661_RET_RECORD_NO_FINISH ;
                break ;


         case L22:
                    // не закидуем запросы на считывание данных. В течении 5 мс это бесполезно не тратим врем
                if ( (u)(w)( timer1 - time ) <= _MkSec( 7*1000 ) )
                 {
                    // не прошло время торебуемое для записи
                  break ;
                 }
                else
                 {

  // 4.3.2 считуем данные из ROM
                   Res_chenel_in->Res_Err_Ret = GetResistorValue( Res_chenel_in, RES_WIPER_ROM ) ;
                   Ret = (w)Res_chenel_in->Res_Err_Ret ;

                   if ( ( Ret == MCP4661_RET_EEPROM_BUSY ) || ( Ret == MCP4661_RETFUNC_FAILED  ) )
                    {
                        // если резистор занят произведем повторные попытки считать данные
                      time = timer1 ;
                      if ( ++count_pov > 3 )
                       {
                        Res_Label = L0 ;
                          // попытки достучатся к резистору исчерпаны
                        Ret = MCP4661_RET_CONNECT_OVERFLOW ;
                        break ;
                       }
                    }
                 }

  // 4.4 перепроверяем что значения в RAM и ROM одинаковые
                if ( Res_chenel_in->ResMemory.Res_RAM == Res_chenel_in->ResMemory.Res_ROM )
                 {
                  Res_Label = L30 ;
                  count_pov = 0 ;
                    // Данные не потерялись. Перед выходом подготовим возвращаемое значение - не закон цикл записи
                  Ret = MCP4661_RET_RECORD_NO_FINISH ;
                  break ;
                 }
                else
                 {
                    // выявленна ошибка в записанных данных дальше нет смысла идти
                  Ret = MCP4661_RET_DATA_FAILED ;
                  Res_Label = L0 ;
                  break ;
                 }

 //------------------------------------------------------------------------------------------------------------------------------//

           case L30:
  // 4.5 считаем значение из счетчика если оно >= 0xff записываем в него 0x01 иначе просто инкримент

                // Предвварительный опрос статус регистра (на предмет занятого состояния ROM ячеек памяти)  нет смысла делать его сделали выше

                Res_chenel_in->Res_Err_Ret = GetResistorValue( Res_chenel_in, RES_WIPER_EEP_COUNT_SAVE );
                Ret = (w)Res_chenel_in->Res_Err_Ret ;
                time = timer1 ;
                Res_Label = L32 ;


           case L32:

                  // Проверка на и ошибки или занятость резистора для чтени
                if ( Ret != ( MCP4661_RETFUNC_OK || MCP4661_RET_EEPROM_OK) )
                 {
                   if ( Ret == MCP4661_RET_EEPROM_BUSY )
                    {
                      // если резистор занят произведем повторные попытки считать данные
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
                          // попытки достучатся к резистору исчерпаны
                        Ret = MCP4661_RET_CONNECT_OVERFLOW ;
                        break ;
                       }
                      }
                    }
                   else  // ошибка по которой нет смысла идти дальше
                    {
                     Res_Label = L0 ;
                     break ;
                    }
                }
                  // из-за того что в EEPROM до первой записи хранится 0x00FF, а сетка _RES_setka_max = 0x0100
                  // чтоб при первой записи в данную ячейку записать 1 приходится делаать ( _RES_setka_max - 1 )
                if ( Res_chenel_in->ResMemory.Count_Save >= ( _RES_setka_max - 1 )  )
                     Res_chenel_in->ResMemory.Count_Save = 1 ;
                  // переполнения не будет
                else Res_chenel_in->ResMemory.Count_Save++  ;

                Res_Label = L40 ;

                  // Перед выходом подготовим возвращаемое значение - не закончен цикл записи
                Ret = MCP4661_RET_RECORD_NO_FINISH ;
                break ;


           case L40:

             //------------------------------------------------------------------------------------------------------------------------------//
  // 4.6 Запишем и сверим, что записано в счетчике с тем, что хотели записать
                  // В переменной ResMemory.Count_Save данного резистора уже лежит желаемое значение для записи в Count_Save
                  // произведем запись с проверкой

  // 4.6.1 Подготовим данные для записи в адрес счетчика
                Res_chenel_in->Res_data_write = Res_chenel_in->ResMemory.Count_Save ;

                  // Запишем данные
                Res_chenel_in->Res_Err_Ret = SetResistorValue( Res_chenel_in, RES_WIPER_EEP_COUNT_SAVE );
                Ret = (w)Res_chenel_in->Res_Err_Ret ;
                  // проверка на ошибку по которой нет смысла идти дальше
                if ( Ret == MCP4661_RETFUNC_FAILED )
                 {
                  Res_Label = L0 ;
                  break ;
                 }
                  //
                time = timer1 ;
                count_pov = 0 ;
                Res_Label = L42 ;
                  // запись в резистор длится 5-10 мс поэтому выходим
                  // Перед выходом подготовим возвращаемое значение - не закон цикл записи
                Ret = MCP4661_RET_RECORD_NO_FINISH ;
                break ;


         case L42:
                    // не закидуем запросы на считывание данных. В течении 5-10 мс это бесполезно не тратим врем
                if ( (u)(w)( timer1 - time ) <= _MkSec( 7*1000 ) )
                 {
                    // не прошло время торебуемое для записи
                  break ;
                 }
                else
                 {

  // 4.6.2 считуем данные из Count_Save
                   Res_chenel_in->Res_Err_Ret = GetResistorValue( Res_chenel_in, RES_WIPER_EEP_COUNT_SAVE ) ;
                   Ret = (w)Res_chenel_in->Res_Err_Ret ;

                   if ( ( Ret == MCP4661_RET_EEPROM_BUSY ) || ( Ret == MCP4661_RETFUNC_FAILED  ) )
                    {
                        // если резистор занят произведем повторные попытки считать данные
                      time = timer1 ;
                      if ( ++count_pov > 3 )
                       {
                        Res_Label = L0 ;
                          // попытки достучатся к резистору исчерпаны
                        Ret = MCP4661_RET_CONNECT_OVERFLOW ;
                        break ;
                       }
                    }
                 }

  // 4.6.3 перепроверяем что значения по адресу Count_Saveи равны с тем что хотели записать
                if ( Res_chenel_in->ResMemory.Count_Save == Res_chenel_in->Res_data_write )
                 {
                    // УСПЕШНЫЙ КОНЕЦ
                  Ret = MCP4661_RET_DATA_OK ;
                  Res_Label = L0 ;
                  count_pov = 0 ;
                  break ;
                 }
                else
                 {
                    // выявленна ошибка в записанных данных дальше нет смысла идти
                  Ret = MCP4661_RET_DATA_FAILED ;
                  Res_Label = L0 ;
                  break ;
                 }

    }



  // если не вышли по ошибке
return Ret ;

}




// Функция реализующая одноразовое считывание данных с резистора при старте в ФОНЕ, чтоб не задерживать старт при АПВ если 
//         появились проблемы с I2C и мы не сидели в while на повторных опросах в ustavki.c

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

             // проинициализируем перем, котор будем возвращать по return, значением незаконченного цикла записи в данной функции
             // ниже если ее никто не перетер значит ошибок для прекращения работы функции нет но она еще не закончена
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

        //   Считуем по очереди с интересующих нас 4-ех ячеек памяти значения для каждого резистора: RAM, ROM, EEPROM счетчик изм., EEPROM пред. настройка)
               if      ( count_mem == 0 ) Res_chenel_in[ ax ].Res_Err_Ret = GetResistorValue( &Res_chenel_in[ ax ], RES_WIPER_RAM );
               else if ( count_mem == 1 ) Res_chenel_in[ ax ].Res_Err_Ret = GetResistorValue( &Res_chenel_in[ ax ], RES_WIPER_ROM );
               else if ( count_mem == 2 ) Res_chenel_in[ ax ].Res_Err_Ret = GetResistorValue( &Res_chenel_in[ ax ], RES_WIPER_EEP_COUNT_SAVE );
               else if ( count_mem == 3 ) Res_chenel_in[ ax ].Res_Err_Ret = GetResistorValue( &Res_chenel_in[ ax ], RES_WIPER_EEP_PAST_SAVE );

               Ret = (w)Res_chenel_in->Res_Err_Ret ;
               time = timer1 ;
             ++count_pov ;
               Res_Label = L5 ;

       case L5:
         // Проверка на ошибки или занятость резистора для чтения/записи данных
              if ( Ret != ( MCP4661_RETFUNC_OK || MCP4661_RET_EEPROM_OK) )
               {
                 // если резистор занят или не отзывается произведем повторные попытки считать данные
                if ( (u)(w)( timer1 - time ) <= _MkSec( 7*1000 ) )
                 {
                  break ;
                 }
                else
                 {

                  if ( count_pov > 3 )
                   {
                      // Попытки достучатся к текущей ячейке памяти резистора исчерпаны
                    Ret = MCP4661_RET_CONNECT_OVERFLOW ;
                    mSet_ServiceMsg2 ( _Srv2_FailReadRes ) ;
                       // Не выходим сразу попробуем опросить следующую ячейку памяти текущего резистора 
                    if ( ++count_mem >= 4 )
                     {
                        // Перейдем к опросу следующего резистора
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
  // Конец считывания данных. Блокируем последующие опросы считывания данных с резисторов.
if ( ax >= _RES_Ntab ) Start_FirstCall = 1 , ax = 0 ;

  // если не вышли по ошибке
return Ret ;

}







