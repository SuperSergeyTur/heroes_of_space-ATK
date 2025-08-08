#include "common_include.h"
#include <wg.h>
//--------------------------------------------------------
//     НАСТРОЙКИ  ГЕНЕРАТОРА ПЕРИОДИЧЕСКОГО СИГНАЛА.

void Start_wg ( void )
{
 // word ax;
  lword lax;
  fr4 = 0;
 

  //Аппаратная инициализаци
  MCPWM_Init(LPC_MCPWM);
  mOtkl_imp();
  Fsin_d = 0 ;
  Fwg = _r.wg_Fwg;
  sdvig = 120 ;
  lax = PeripheralClock/_r.wg_Fwg;

   channelsetup[0].channelType = MCPWM_CHANNEL_CENTER_MODE;
   channelsetup[1].channelType = MCPWM_CHANNEL_CENTER_MODE;
   channelsetup[2].channelType = MCPWM_CHANNEL_CENTER_MODE;
   channelsetup[0].channelDeadtimeEnable = ENABLE;
   channelsetup[1].channelDeadtimeEnable = DISABLE;
   channelsetup[2].channelDeadtimeEnable = DISABLE;
   channelsetup[0].channelDeadtimeValue = _r.wg_dead_time;
   channelsetup[0].channelUpdateEnable = ENABLE;
   channelsetup[1].channelUpdateEnable = ENABLE;
   channelsetup[2].channelUpdateEnable = ENABLE;
   channelsetup[0].channelTimercounterValue = 0;
   //Половина потому, что у нас центрированная ШИМ.Период будет в два раза больше,
   //чем максимальное значение таймера
   channelsetup[0].channelPeriodValue = lax/2;
   //половина периода - нулевое значение выходного напряжения
   channelsetup[0].channelPulsewidthValue = channelsetup[0].channelPeriodValue/2;



   channelsetup[1].channelTimercounterValue = 0;
   channelsetup[1].channelPulsewidthValue = lax/4; //половина периода
   channelsetup[1].channelPeriodValue = lax/2;     //Половина потому, что у нас центрированная ШИМ
                                                   //Период будет в два раза больше,
                                                   //чем максимальное значение таймера
   channelsetup[2].channelTimercounterValue = 0;
   channelsetup[2].channelPulsewidthValue = lax/4; //половина периода
   channelsetup[2].channelPeriodValue = lax/2;     //Половина потому, что у нас центрированная ШИМ
                                                   //Период будет в два раза больше,
                                                   //чем максимальное значение таймера

#if _Pulse_Polarity == 0
    channelsetup[0].channelPolarity = MCPWM_CHANNEL_PASSIVE_HI;
    channelsetup[1].channelPolarity = MCPWM_CHANNEL_PASSIVE_HI;
    channelsetup[2].channelPolarity = MCPWM_CHANNEL_PASSIVE_HI;
#else
    channelsetup[0].channelPolarity = MCPWM_CHANNEL_PASSIVE_LO;
    channelsetup[1].channelPolarity = MCPWM_CHANNEL_PASSIVE_LO;
    channelsetup[2].channelPolarity = MCPWM_CHANNEL_PASSIVE_LO;
#endif
//    LPC_GPIO1->SET = _PIN_NOT_PULSES;
     PINSEL_ConfigPin (1, 19, 4);
     PINSEL_ConfigPin (1, 22, 4);
     PINSEL_ConfigPin (1, 25, 4);
     PINSEL_ConfigPin (1, 26, 4);
     PINSEL_ConfigPin (1, 28, 4);
     PINSEL_ConfigPin (1, 29, 4);                      

    LPC_GPIO1->SET = _PIN_NOT_PULSES| _PIN_PULSES;

    MCPWM_ConfigChannel(LPC_MCPWM, MCPWM_CHANNEL_0, &channelsetup[0]);
    MCPWM_ConfigChannel(LPC_MCPWM, MCPWM_CHANNEL_1, &channelsetup[1]);
    MCPWM_ConfigChannel(LPC_MCPWM, MCPWM_CHANNEL_2, &channelsetup[2]);
    
//Включаем прерывание по достижении максимума счетчиком (LIM0)
    MCPWM_IntConfig(LPC_MCPWM, MCPWM_INTFLAG_LIM0, ENABLE);
    NVIC_EnableIRQ(MCPWM_IRQn);
    //MC_1A Ч Motor control PWM channel 1
  //МСPWM AC mode режим, в котором частота переключения всех каналов и мертвое
  //время задается каналом 0, каналы "В" будут инверсными каналам "А"
    MCPWM_ACMode(LPC_MCPWM, ENABLE);
    MCPWM_Start(LPC_MCPWM, ENABLE,ENABLE, ENABLE);
   // LPC_GPIO2->CLR = 0x4; 
//Настройка Динамического тормоза
    Init_DT ();

 return ;
}
//----------------------------------------------
extern "C" {
void MCPWM_IRQHandler ( void )
{
  if ( MCPWM_GetIntStatus(LPC_MCPWM, MCPWM_INTFLAG_LIM0) == SET)
  {
    wg_interrupt();//24 mks
    MCPWM_IntClear(LPC_MCPWM, MCPWM_INTFLAG_LIM0);
  }
  else
  {
    MCPWM_IntClear(LPC_MCPWM, (MCPWM_INTFLAG_MAT0 | MCPWM_INTFLAG_CAP0
                              |MCPWM_INTFLAG_LIM1 |MCPWM_INTFLAG_MAT1 | MCPWM_INTFLAG_CAP1
                              |MCPWM_INTFLAG_LIM2 |MCPWM_INTFLAG_MAT2 | MCPWM_INTFLAG_CAP2
                                ));
  }
  return;
}
} //extern "C"
//Программа раздачи задания на длительность импульсов ШИМ
void wg_interrupt(void)
{
  float ax;
  fr1 = timer1;
 // slword lax ;
      asm_ei();
              //   Очередное приращение угла формируемой синусоиды.
            //   угол: старший байт целый, младший - дробный.
            // Lsin += 360грд/(Fwg/(Fsin/_HzSin_Nom)) ;

     ax =  (d)(Fwg*_HzSin_Nom)/Fsin_d ;
     ax = 360/ax;
     if ((ax == INFINITY)||(ax == NAN))
     {
       //неопределенное значение - все равно прирост 0
       ax = 0;
     }

     Lsin_z +=  ax ;

     if (Lsin_z >= 360)
     {
       Lsin_z -= 360;
     }
     Lsin_z_i = (w)(Lsin_z*182.0);
#ifdef _Synchr
     Lsin_z = Corr_phase(Lsin_z,  pSyn );
#endif
     /*
     ax = (Lsin_z*_PI)/180;
     ax = cosf(ax);
     //Umsin_d должно иметть значение в пределах 0 - channelsetup[0].channelPeriodValue/2
     lax = (slw)(ax *(d)Umsin_d);
     //Нулевой канал для всех т.к. используется AC MODE
     if ((slw)lax > (slw)channelsetup[0].channelPeriodValue/2)
     {
       lax = channelsetup[0].channelPeriodValue/2;
     }
     else if((slw)lax < -(slw)(channelsetup[0].channelPeriodValue/2))
     {
       lax = -(slw)(channelsetup[0].channelPeriodValue/2);
     }

     channelsetup[0].channelPulsewidthValue = channelsetup[0].channelPeriodValue/2 - lax ;
     */
     channelsetup[0].channelPulsewidthValue = Set_PulseWidth ( Lsin_z, Umsin_d , channelsetup[0].channelPeriodValue/2);
             //  Задание на угол для следующей, фазы она смещена на угол = -sdvig
     //Фаза В - знак переменной sdvig определяет напрявление вращения пол
     ax = Lsin_z- sdvig ;
 /*    if (ax < 0)
     {
       ax += 360 ;
     }
     //Проверка нужна т.к. sdvig может быть отрицательным
     else if (ax > 360)
     {
       ax -= 360;
     }
     ax = (ax*_PI)/180;
     ax = cosf(ax);
     //Umsin_d должно иметть значение в пределах 0 - channelsetup[0].channelPeriodValue/2
     lax = (slw)(ax *(d)Umsin_d);
     //Нулевой канал для всех т.к. используется AC MODE
     if ((slw)lax > (slw)channelsetup[0].channelPeriodValue/2)
     {
       lax = channelsetup[0].channelPeriodValue/2;
     }
     else if((slw)lax < -(slw)(channelsetup[0].channelPeriodValue/2))
     {
       lax = -(slw)(channelsetup[0].channelPeriodValue/2);
     }*/
     channelsetup[1].channelPulsewidthValue = Set_PulseWidth ( ax , Umsin_d , channelsetup[0].channelPeriodValue/2);;
     //Фаза С - знак переменной sdvig определяет напрявление вращения пол

     ax = Lsin_z + sdvig ;
     /*//Проверка нужна т.к. sdvig может быть отрицательным
     if (ax < 0)
     {
       ax += 360 ;
     }
     else if (ax > 360)
     {
       ax -= 360;
     }
     ax = (ax*_PI)/180;
     ax = cosf(ax);
     //Umsin_d должно иметть значение в пределах 0 - channelsetup[0].channelPeriodValue/2
     lax = (slw)(ax *(d)Umsin_d);
     //Нулевой канал для всех т.к. используется AC MODE
     if ((slw)lax > (slw)channelsetup[0].channelPeriodValue/2)
     {
       lax = channelsetup[0].channelPeriodValue/2;
     }
     else if((slw)lax < -(slw)(channelsetup[0].channelPeriodValue/2))
     {
       lax = -(slw)(channelsetup[0].channelPeriodValue/2);
     }*/
     channelsetup[2].channelPulsewidthValue = Set_PulseWidth ( ax , Umsin_d , channelsetup[0].channelPeriodValue/2);;

     MCPWM_WriteToShadow(LPC_MCPWM, MCPWM_CHANNEL_0, &channelsetup[0]);
     MCPWM_WriteToShadow(LPC_MCPWM, MCPWM_CHANNEL_1, &channelsetup[1]);
     MCPWM_WriteToShadow(LPC_MCPWM, MCPWM_CHANNEL_2, &channelsetup[2]);
  /*   if (Otkl_imp != 0)
     {
      // MCPWM_Stop(LPC_MCPWM, ENABLE,ENABLE,ENABLE);
              
     }
 //    else
 //    {
 //      MCPWM_Start(LPC_MCPWM, ENABLE,ENABLE,ENABLE);       
 //    }

*/
     fr3 = timer1 - fr1;
     if (fr4 < fr3) 
     {
       fr4 = fr3;
     }
   return ;
}
//Расчет длительности импульса исходя из угла, амплитуды и периода
lword Set_PulseWidth ( float alfa, word Um,  uint32_t PeriodValue)
{
  float ax;
  slword lax;
     //Проверка на требуемые услови
   if (alfa < 0)
   {
     ax = alfa + 360 ;
   }
   else if (alfa > 360)
   {
     ax =alfa - 360;
   }
   else
   {
     ax = alfa;
   }
   ax = (ax*_PI)/180;
   //форма выходного напряжения: либо Um*cos(wt), либо Um*cos(wt)+(Um/6)*cos(3*wt)
   if(Prg._.Trap == 0)                                          
   {                                                                                          
     ax = cosf(ax);
   }                                                            
   else
   {
     ax = cosf(ax)-(cosf(3*ax)/6);
   }

   
   //Umsin_d должно иметть значение в пределах 0 - channelsetup[0].channelPeriodValue/2
   lax = (slw)(ax *(d)(sw)Um*_Sin_Polarity);
   //Нулевой канал для всех т.к. используется AC MODE
   if ((slw)lax > (slw)PeriodValue)
   {
     lax = PeriodValue;
   }
   else if((slw)lax < -(slw)PeriodValue)
   {
     lax = -(slw)PeriodValue;
   }
   return (PeriodValue - lax);
}
/*
void mVkl_imp(void)
{
  PINSEL_ConfigPin (1, 19, 4);
  PINSEL_ConfigPin (1, 22, 4);
  PINSEL_ConfigPin (1, 25, 4);
  PINSEL_ConfigPin (1, 26, 4);
  PINSEL_ConfigPin (1, 28, 4);
  PINSEL_ConfigPin (1, 29, 4);                      
  MCPWM_Start(LPC_MCPWM, ENABLE,ENABLE,ENABLE);//LPC_GPIO2->CLR = 0x4  //Подача импульсов(включение регистра)
}
void mOtkl_imp(void)
{
  MCPWM_Stop(LPC_MCPWM, ENABLE,ENABLE,ENABLE);
  PINSEL_ConfigPin (1, 19, 0);
  PINSEL_ConfigPin (1, 22, 0);  
  PINSEL_ConfigPin (1, 25, 0);  
  PINSEL_ConfigPin (1, 26, 0);  
  PINSEL_ConfigPin (1, 28, 0);  
  PINSEL_ConfigPin (1, 29, 0);
  LPC_GPIO1->SET = _PIN_NOT_PULSES| _PIN_PULSES;  
}
*/