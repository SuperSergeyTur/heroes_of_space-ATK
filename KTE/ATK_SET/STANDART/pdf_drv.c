//#ifndef _pdf_drv_c
//#define _pdf_drv_c

#include "lpc177x_8x_qei.c"

//������� ��������� ��� ��� ���������� LPC178x|7x
//������������ ����������� ������� ��������� QEI ��� NXP(���������� � ����� lpc177x_8x_qei.c,
//��� ��, ����� ������ �������� ������ �������� �� ����������)

void pdf_drv_init( word num )
{
   QEI_CFG_Type QEIConfig;
   QEI_RELOADCFG_Type ReloadConfig;
   st_Qei_FilterCfg PDF_Filters;
   //��������� ������ ���:
   //����� Capture(4� ���������, ��� ��������- F00, F90 � FZ)
   // ��� �������������� ����������� - ��� �� �������, �����, ���� ����� ������ ���� ��� � ����������� �� ��������� ���
   //����� Signal - ����������� ���������.
   //����� �������� ��������� �� ������� ���������� ��������.
   QEIConfig.CaptureMode = QEI_CAPMODE_2X;
   QEIConfig.DirectionInvert = QEI_DIRINV_NONE;
   QEIConfig.InvertIndex = QEI_INVINX_NONE;
   QEIConfig.SignalMode =  QEI_SIGNALMODE_CLKDIR;
   QEIConfig.CRESPI     =  QEI_RESPI_EN;
   QEIConfig.INXGATE    =  0xf;
   PDF_Filters.PHA_FilterVal = _PDF_FiltrNumb;
   PDF_Filters.PHB_FilterVal = _PDF_FiltrNumb;
   PDF_Filters.INX_FilterVal = _PDF_FiltrNumbINX;
   //������� �������� ���������� ��������� � ������� QEI
    QEI_Init(num, &QEIConfig);
    QEI_SetDigiFilter(num ,PDF_Filters );

    // �������� �������� ������������ ������� - ���������� ������ ������� ��������
    // ReloadOption  ���������� � ����� ��������� �������� ������ ��������:������������
    // , ��� �������� ������� (���� PCLK).
    //� ����� ������ - � �������������
    ReloadConfig.ReloadOption = QEI_TIMERRELOAD_USVAL;
    ReloadConfig.ReloadValue = _ReloadValue_us;

    QEI_SetTimerReload(num, &ReloadConfig);

    //������������� �������� ������������ �������� ���������,
    //�� ��������� ��� �������� ��� �������� �����, ����� ��������� ����� ����
    //��� �������� ������ ������� ��������� ���������� �� ���������� ��������� �������
    //������ ���� ������������ ������������ (� ����� ������) ����� ��������� ��� �� ������

    QEI_SetMaxPosition(num, 40000 );
//    pdf_drv_data[num].Tpdf_time = timer1 ;
//    pdf_drv_data[num].Tpdf      = _PDF_base_time * 5 ;
    pdf_drv_data[num].Scht_T    =  0 ;

    // ��������� ����������
   // QEI_IntCmd(num, QEI_INTFLAG_INX_Int, ENABLE);
    QEI_IntCmd(num, QEI_INTFLAG_INX_Int, ENABLE);
    NVIC_SetPriority(QEI_IRQn, IntPriority(2, 4));
    // Enable interrupt for QEI
	NVIC_EnableIRQ(QEI_IRQn);


  return ;
}
//-------------------
//���������� �� ���
extern "C" {
void QEI_IRQHandler(void)
{

         // F00_Oborot = QEI_GetPosition(QEI_0);
          
          PDF_Interrupt();
        // Reset Interrupt flag pending
        QEI_IntClear(QEI_0, QEI_INTFLAG_INX_Int|QEI_INTFLAG_ENCLK_Int);
}
//#endif
}
