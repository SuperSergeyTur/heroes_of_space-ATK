
#include "pdf_drv.c"
word pdf ( word code , word num );

//  Настройки для ПДФов.

void pdf_init ( void )
{
  pdf_drv_init( 0 ) ;
  return ;
}
/*!
 * @brief  Функция обработки датчика измерения температуры со стандартной структурой PDF
 * @date 02.08.2023
 * @authors Tur Sergey    
 */
void pdf_input ( void )
{
  pdf ( 1 , 0, PDF ) ; 
  return ;
}

//Примерные эмпирические данные: дельта дельта в 12 Гр изменяет частоту на 2,4 кГц, следвательно 5 Гр/кГц
/*!
 * @brief  Функция обработки сигналов от ПДФ дачтчика температуры
 * @param code - статия работы программы, 0 - инициализация, 1 - работа
 * @param num - номер ПДФ
 * @param ptr - указатель на структуру типа PDF_data, определяющую текущие параметры измерения температуры
 * @return всегда возвращает 1
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
  case 0 :    // настройка EPA - передаем его условный номер.
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
          time23 = Timer1_fSec;// - _fSec(0.015); // Чтобы началось измерение сразу
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
            //Число импульсов за 100 мсек
            Time_Delta = _fSec(0.007);
            ptr->Fpdf =QEI_GetVelocityCap(num);
            QEI_Reset(0, QEI_RESET_POS);
            fax = (float)ptr->Fpdf;
            ptr->Freq = fax/(_ReloadValue_us*1e-3);// 1e-3 т.к. время в мксек, а частоту измеряем в кГц
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
//            //Если строб пропал, а мы не домеряли 
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
            //Температура из напряжения
            fax = fbx / *ptr->Temp ;            
            ptr->Out = fax + *ptr->T0Volt ;
            //Температура в целочисленном формате
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
//Прерывания по стробу - разрешаем измерения.
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
