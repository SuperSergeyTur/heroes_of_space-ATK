void Alarm_start(void)
{
#ifndef _ALARM_FZ
  ACSR = 0x62; //01100010

  ICR44 = 19;
#endif
}
__interrupt void Alarm_interrupt(void)
{

#ifndef _ALARM_FZ
  // На аналоговый компаратор ALARM заведен контроль P24 :
  Av._.P24 = 1;
#else
  // Для RCP вход ПДФ FZ заведен на аналоговый компаратор ALARM :

#endif

  //Чтобы не было зависаний,компаратор включается при выдаче предупреждений
  Alarm_off();

  ACSR_IRQ = 0;
}
