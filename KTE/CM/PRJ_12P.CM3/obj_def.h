
//------- ФАЙЛ СО ВСЕМИ #DEFINE-ИМЕНАМИ ( кроме стандартных в INCLUDE.H ) :

//#define  _INTERPRETER    // Прекрасный язык программирования .

// Определить тип платы для автоматического определения аппаратной обвязки :
//#define  _CM3_ - определено в свойствах проекта .

#ifdef  _CM3_
  //#define _MAX_SPI   2
  #define _SPI0 // порт для S400, S500
  #define _SPI1 // порт для внешнего АЦП
  //#define _SPI2 // порт пока не используется
  //Свободная область в ЭОЗУ для размещения там своих переменных
  #define _free_Space_Reg 200
  #define _Hz_SPI0   500000
  #define _Hz_SPI1   20000000
  #define _ADC_SPI   LPC_SSP1
  #define _ADC_CS    LPC_GPIO3
  #define _CR0_SPI0  SSP_CR0_DSS(8) | SSP_CR0_FRF_SPI | SSP_CR0_CPOL_HI | SSP_CR0_CPHA_SECOND
  #define _CR0_SPI1  SSP_CR0_DSS(16) | SSP_CR0_FRF_SPI | SSP_CR0_CPOL_HI
  #define _SPP_S500  LPC_SSP0
  #define _ADC_12_         // 12-ти разрядный АЦП
  #define _PDF_FiltrNumb     0x100
  #define _PDF_FiltrNumbINX  0x100

//#define _Adc_Extend      // Дополнительный внешний мультиплексор АЦП .
//#define _Adc_Extend_Inv  // Инвертирование выборки для внешнего мультиплексора (например, если управление от Po0) .
//#define _Adc_Extend_Po0  // Дополнительный внешний мультиплексор АЦП на месте выходного Порта 0 .
//#define  Mux_Port LPC_GPIO2
//#define  Mux_Pins(data) (data&0x3f)<<24
//#define _Num_Mux     3   // Количество плат мультиплексированных каналов АЦП .
//#define _Ch13_Mux        // Мультиплексированный канал АЦП .
//#define _Ch14_Mux        // Мультиплексированный канал АЦП .
//#define _Ch15_Mux        // Мультиплексированный канал АЦП .
//#define _Dat_Temp_Max 24 // Для алгоритма аналогового измерения температуры каждого охладителя в каждом силовом шкафу .
  #define _MaxSaveSled   _SizeSledPole-1 // должно быть не больше , чем _SizeSledPole в INCLUDE.H .
  #define _SizeAddr_i2c_ 4
#else
  #define _SizeAddr_i2c_ 2
#endif

#define    _Monitor_start_page 0x8000  // Стартовая страница памяти для Монитора .
//---
#define    _SIFU2_         // 12-пульсная схема выпрямления .
//#define  _Gercon_APV     // АПВ Геркона чтобы не отключаться по сил.предохр.
#define    _POWER          // Наличие контроля Масленика .
//---
//#define  _SIFU_Syn2      // ЕСТЬ ЛИ ОТДЕЛЬНАЯ СИНХРОНИЗАЦИЯ ОТ МОСТА ДЛЯ СИФУ.
//#define  _KTE_5          // Управление Контактором от СУ (скорее всего переменного тока, а не ЛК) .
//#define  _KONTAKTOR_for_ProboyTir // Последний коммутационный аппарат - 3х фазный контактор , без включения которого нет силы на тиристорах
//#define  _Id_on_Itt_for_ProboyTir // ОС для РТ по Трансформаторам Тока , чтобы БЕЗ Шунта правильно работал тест Пробоя Тиристоров
//#define  _Synch_3f       // Трёхфазная синхронизация .
//---
#define    _AVTONASTR      // Автонастройка РТ
#define    _JOURNAL        // Наличие "журнала"
#define    _CombRedact     // Наличие пункта в меню "Комб.Редакт".
#define    _WatchDog       // Наличие таймера-сторожа
//---
// ЦАП PPG5 на порту P1.22 . Запайка #4 должна быть 2-3 .
//---
//#define  _CH5_PWM        // Если запайка #4:1-2 , то PPG5 для ЦАП на порту P2.2 . Суммой возбудителя порт быть не может .
//---
#define    _S500           // Наличие новой платы S500 (или S250) вместо S400 (или S200)
//---
//#define  _STOLB_1TIR     // Уставка на аварию охлаждения - до 3 сек .
//---
//#define  _SELS_NULL      // Установка нуля сельсина в "F2-Наладка."
//#define  _NARABOTKA      // подсчет наработки агрегата в часах .

//#define  _AF_Otkl_Q1     // Отключение Q1 в мощных агрегатах и то по особой договоренности .
//---
//#define  _CANOPEN
//#define  _CAN_MASTER     // По крайней мере один порт CAN настраивается на работу как мастер
//#define  _CAN_MASTER_PORT  _CAN0_Port // Определение CAN0-порта как мастера
//#define  _CAN_MASTER_PORT  _CAN1_Port // Определение CAN1-порта как мастера
//---
#define    _NET_IRQ        // ia????N ?N?Noл? »?a?? ?aN?n??мa
#define    _DMA_RS485_     // включение ДМА на RS485 для уменьшения времени фона при передаче
//---
//#define  _AZIMUT         // Сельсин от 0 до 360грд .
//---
//#define  _REG_POL        // Регулятор положения
//#define  _RP_OS_S0_      // Обратная связь для РП по Сельсину 0
//#define  _RP_OS_S1_      // Обратная связь для РП по Сельсину 1
//#define  _RP_OS_PDF_     // Обратная связь для РП по ПДФ
//#define  _RP_ZIS         // Подключение выхода РП на вход ЗИС
//---
//#define  _ONE_REG        // Один регистр сообщений
//#define  _TRETIY_REG     // Третий регистр сообщений
#define    _Sld_cond       // Остановка Следа по условию
//---
//#define  _Rev_Pola       // Реверс поля.
//#define  _RS_10ms_       // Период выполнения РС раз в 3 пульса.
//---
#define    _Po0_INVERT     // Имеется возможность инверсии выходных сигналов .
//#define  _AsPo_INVERT    // Имеется возможность инверсии выходных сигналов портов платы S400/S500 или S200/S250 .
//---
#define    _DST            // Включение Датчика Статического Тока .
//#define  _RDN            // Включение Регулятора Деления Нагрузки .
//#define  _RRS            // Включение ЛЫЖИ : Регулятора Рассогласования Скорости .
//#define  _BUKSOVKA       // Контроль буксовки ( срыва тока ) .
//#define  _RVId           // Включение Регулятора выравнивания токов якоря
//---
//#define  _Obj_Id_izm     // Объектное измерение мгновенного тока Id .
//#define  _Obj_Id_conv    // Объектное преобразование измеренного тока Id .
//#define  _Obj_Id_Max     // Объектное вычисление аварии по току Id .
//---
//#define  _Obj_Id2_izm    // Объектное измерение и преобразование мгновенного тока Id2 .
//---
//#define  _ZI_4TEMPA      // ЗИС с 4-мя темпами : на разгон и торможение обоими мостами .
//#define  _ZI_30min       // ЗИ до 30 минут .
//---
//#define  _Perecl_DS      // При неисправности ДС переключаемся на ЭДС без аварии .
#define     bi_xQ1  ( bi_AK1 == 1 || bi_AK2 == 1 ) // Отключение Q1 , когда его б/к включен .
#define     bi_xQ2  1 //( bi_VAT == 1 ) //( bi_Vkl_Q2 == 1 && bi_Otkl_Q2 == 0 ) // Отключение Q2 , когда его б/к включен .
//---
//#define  _T_PDF          // Включение на ОС по периоду при небольших скоростях
//#define  _USEL_obj       // Объектное управление USEL . Иначе он показывает работу, готовность, аварию .
//---
//--- Входные и выходные порты :
//----------------
#define    _Po0_
//----------------
//#define  _AsPo0_
//#define  _AsPo1_
//#define  _AsPo2_
//#define  _AsPo3_
//#define  _AsPo4_
//#define  _AsPo5_
//#define  _AsPo6_
//#define  _AsPo7_
//----------------
#define    _Pi1_
//----------------
#define    _AsPi0_
#define    _AsPi1_
//#define  _AsPi2_
//#define  _AsPi3_
//#define  _AsPi4_
//#define  _AsPi5_
//#define  _AsPi6_
//#define  _AsPi7_
//#define  _AsPi8_
//#define  _AsPi9_
//#define  _AsPi10_
//#define  _AsPi11_
//#define  _AsPi12_
//#define  _AsPi13_
//#define  _AsPi14_
//#define  _AsPi15_
//----------------
#ifdef     _Adc_Extend_Po0      // Дополнительный внешний мультиплексор АЦП на месте выходного Порта 0 .
#define    _AsPo_Av_Pr_Got_  1  // Номер порта , в котором находятся Авария , Готовность , Предупреждение .
#endif
