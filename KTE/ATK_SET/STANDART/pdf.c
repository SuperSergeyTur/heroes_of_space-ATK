
#include "pdf_drv.c"
word pdf ( word code , word num );

//  ��������� ��� �����.

void pdf_init ( void )
{
  pdf_drv_init( 0 ) ;
  return ;
}
/*!
 * @brief  ������� ��������� ������� ��������� ����������� �� ����������� ���������� PDF
 * @date 02.08.2023
 * @authors Tur Sergey    
 */
void pdf_input ( void )
{
  pdf ( 1 , 0, PDF ) ; 
  return ;
}

//��������� ������������ ������: ������ ������ � 12 �� �������� ������� �� 2,4 ���, ������������ 5 ��/���
/*!
 * @brief  ������� ��������� �������� �� ��� �������� �����������
 * @param code - ������ ������ ���������, 0 - �������������, 1 - ������
 * @param num - ����� ���
 * @param ptr - ��������� �� ��������� ���� PDF_data, ������������ ������� ��������� ��������� �����������
 * @return ������ ���������� 1
 * @date 02.08.2023
 * @authors Tur Sergey    
 */
word pdf ( word code , word num, PDF_data *ptr )
{
  float fax, fbx;
  static word time23, counter, LabelTemp = 0;
  static float Summ;
  switch ( code )
  {
  case 0 :    // ��������� EPA - �������� ��� �������� �����.
    ptr->Fpdf   = 0 ;
    ptr->Out   = 0;
    ptr->Bits.all   = 0;
    LabelTemp = 0;
    //---
    break;
    
  default:
    if (/*ptr->Bits._.Strob &&*/ ptr->Bits._.Count_Beg )
    {
      switch (LabelTemp)
      {
      case 0:
        
       // if ((u)((w)(Timer1_fSec - *ptr->TimeStrob)) > _fSec(0.01))
       // {
          ++LabelTemp;
          counter = 0;
          Summ = 0.0;
          time23 = Timer1_fSec;// - _fSec(0.015); // ����� �������� ��������� �����
          Time_Delta = _fSec(0.01);
          QEI_Reset(0, QEI_RESET_POS);
          //mUSEL_set();
        //}
        break;
      case 1:
        
        if ((u)((w)(Timer1_fSec - time23)) > Time_Delta)
        {
          //if (_StrobTempPin)
          //{
            //����� ��������� �� 100 ����
            Time_Delta = _fSec(0.007);
            ptr->Fpdf =QEI_GetVelocityCap(num);
            QEI_Reset(0, QEI_RESET_POS);
            fax = (float)ptr->Fpdf;
            ptr->Freq = fax/(_ReloadValue_us*1e-3);// 1e-3 �.�. ����� � �����, � ������� �������� � ���
            fbx = ptr->Freq * _Kvf;
            Summ += fbx;

            time23 = Timer1_fSec;
            Statistic_Data[counter] = fbx;
            
            if (++counter >= 3)
            {
              ++LabelTemp;
            }
//          }
//          else
//          {
//            //���� ����� ������, � �� �� �������� 
//            //++counter;
//            ++LabelTemp;
//          }
        }
        break;
      case 2:
        //mUSEL_clr();
        PDF[0].Bits._.Strob = 0;
        if (counter != 0)
        {
        fbx = Summ/counter;
          if (isnormal(fbx))
          {   
            ptr->V_Out = fbx;     
            //����������� �� ����������
            fax = fbx / *ptr->Temp ;            
            ptr->Out = fax + *ptr->T0Volt ;
            //����������� � ������������� �������
            ptr->I_Out = (sw)((ptr->Out+0.05)*10); 
          }
          else
          {
            ptr->Out = 300.0;
            ptr->I_Out = 3000;
            ptr->V_Out = 0.0;  
          } 
          //----    
          ptr->Bits._.Count_Beg = 0;
        }
        LabelTemp = 0;
      }
    }
    else
    {
      LabelTemp = 0;
      Time_IzmTemp = Timer1_fSec;
      if (PDF[0].Bits._.Strob)
      {
        PDF[0].Bits._.Strob = 0;
      }
    }
    break;
  }
  //------
  
  return 1 ;
}
//���������� �� ������ - ��������� ���������.
void PDF_Interrupt( void )
{
  if (!PDF[0].Bits._.Strob)
  {
    QEI_Reset(0, QEI_RESET_POS);
    PDF[0].Bits._.Strob = 1;
    //PDF[0].Bits._.Count_Beg = 1;
    Time_IzmTemp = Timer1_fSec;
  }
}
