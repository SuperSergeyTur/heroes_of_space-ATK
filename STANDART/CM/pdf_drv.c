//#ifndef _pdf_drv_c
//#define _pdf_drv_c

#include "lpc177x_8x_qei.c"

//Функция настройки ПДФ для процессора LPC178x|7x
//используются стандартные функции обработки QEI для NXP(содержатся в файле lpc177x_8x_qei.c,
//там же, перед каждой функцией дается описание ее параметров)

void pdf_drv_init( word num )
{
   QEI_CFG_Type QEIConfig;
   QEI_RELOADCFG_Type ReloadConfig;
   st_Qei_FilterCfg PDF_Filters;
   //Настройка канала ПДФ:
   //Режим Capture(4х умнижение, три импульса- F00, F90 и FZ)
   // Без инвертирования направления - это по желанию, может, надо будет менять этот бит в зависимости от установки ПДФ
   //Режим Signal - учетверение импульсов.
   //Сброс счетчика положения по каждому оборотному импульсу.
   QEIConfig.CaptureMode = QEI_CAPMODE_4X;
   QEIConfig.DirectionInvert = QEI_DIRINV_NONE;
   QEIConfig.InvertIndex = QEI_INVINX_NONE;
   QEIConfig.SignalMode =  QEI_SIGNALMODE_QUAD;
   QEIConfig.CRESPI     =  QEI_RESPI_EN;
   QEIConfig.INXGATE    =  0xf;
   PDF_Filters.PHA_FilterVal = _PDF_FiltrNumb;
   PDF_Filters.PHB_FilterVal = _PDF_FiltrNumb;
   PDF_Filters.INX_FilterVal = _PDF_FiltrNumbINX;
   //Функция загрузки полученной структуры в регистр QEI
    QEI_Init(num, &QEIConfig);
    QEI_SetDigiFilter(num ,PDF_Filters );

    // Загрузка регистра перезагрузки таймера - определяет период расчета скорости
    // ReloadOption  определяет в каких величинах задается период проверки:микросекунды
    // , или дискреты таймера (тики PCLK).
    //В нашем случае - в микросекундах
    ReloadConfig.ReloadOption = QEI_TIMERRELOAD_USVAL;
    ReloadConfig.ReloadValue = _PDF_PERIOD;

    QEI_SetTimerReload(num, &ReloadConfig);

    //Устанавливаем величину перезагрузки счетчика положения,
    //он загружает это значение при движении назад, когда переходит через ноль
    //при движении вперед счетчик положения обнуляется по достижению заданного значеня
    //короче сюда записывается учетверенное (в нашем случае) число импульсов ПДФ на оборот

    QEI_SetMaxPosition(num, 4*_r.PDF[num].imp);
    pdf_drv_data[num].Tpdf_time = timer1 ;
    pdf_drv_data[num].Tpdf      = _PDF_base_time * 5 ;
    pdf_drv_data[num].Scht_T    =  0 ;

    // Включение прерываний
    QEI_IntCmd(num, /*QEI_INTFLAG_INX_Int|*/QEI_INTFLAG_ENCLK_Int, ENABLE);

    NVIC_SetPriority(QEI_IRQn, IntPriority(2, 4));
    // Enable interrupt for QEI
	NVIC_EnableIRQ(QEI_IRQn);


  return ;
}
//-------------------
//Прерывание по ПДФ
extern "C" {
void QEI_IRQHandler(void)
{
 #ifdef _T_PDF
  word ax,bx;
    // Усредненный период для скорости вычисляется только в случае, когда период между предыдущим
    //и текущим импульсом меньше 50ms.
     bx = timer1;
     ax = bx - pdf_drv_data[0].Tpdf_time ; // расчет периода импульсов ПДФ .
     pdf_drv_data[0].Tpdf_time = bx ; // время предыдущего прихода импульса F00 .

    if ( PDF[0].flg._.t_ogr_pdf != 1 )
     {
       pdf_drv_data[0].Tpdf += ax ;  // сумма периодов импульсов ПДФ .
       pdf_drv_data[0].Scht_T++ ;    // счетчик периодов импульсов ПДФ .
     }

     PDF[0].flg._.t_ogr_pdf = 0 ; // сброс флага .

#endif

          F00_Oborot = QEI_GetPosition(QEI_0);
        // Reset Interrupt flag pending
        QEI_IntClear(QEI_0, QEI_INTFLAG_INX_Int|QEI_INTFLAG_ENCLK_Int);
}
//#endif
}
