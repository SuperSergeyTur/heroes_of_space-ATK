#ifndef _dzv_drv_c
#define _dzv_drv_c

void init_DZV(void)
{
  // Новая идея .
  // DAN 25.05.2016 - Инициализируем прерывание ДЗВ по переднему фронту , если
  // разрешающим уровнем является верхний , и по заднему фронту , если разрешающим
  // уровнем является нижний .
  // Это значит , что в прерывание будем заходить по заданному фронту и , т.о. отслеживать
  // либо нижний , либо верхний уровень сигналов ДЗВ , что нужно для алгоритма работы ДЗВ .
    if ( _DZVA_Ok_level == 1 )
	{
        GPIO_IntCmd( _DZVA_Port, _DZVA_Bit, 0); // Rising
		//dzva1 = 0;
    }
	else
	{
        GPIO_IntCmd( _DZVA_Port, _DZVA_Bit, 1); // Falling
		//dzva1 = 1;
	}
	if ( _DZVK_Ok_level == 1 )
	{
        GPIO_IntCmd( _DZVK_Port, _DZVK_Bit, 0); // Rising
	    //dzvk1 = 0;
	}
    else
	{
        GPIO_IntCmd( _DZVK_Port, _DZVK_Bit, 1); // Falling
	    //dzvk1 = 1;
	}

  // Старая идея .
  // DAN 24.05.2016 - Инициализируем прерывание ДЗВ и по переднему , и по заднему фронтам .
  // Это значит , что в прерывание будем заходить по обоим фронтам и , т.о. отслеживать
  // и нижний и верхний уровень сигналов ДЗВ , что нужно для алгоритма работы ДЗВ .
  //ДЗВА
    //GPIO_IntCmd( _DZVA_Port, _DZVA_Bit, 0); // Rising
    //GPIO_IntCmd( _DZVA_Port, _DZVA_Bit, 1); // Falling

  //ДЗВК
    //GPIO_IntCmd( _DZVK_Port, _DZVK_Bit, 0); // Rising
    //GPIO_IntCmd( _DZVK_Port, _DZVK_Bit, 1); // Falling

    NVIC_SetPriority( GPIO_IRQn, IntPriority(3, 4));
    NVIC_EnableIRQ( GPIO_IRQn );

  Clr_DZV() ;
}
//***************

void init_DZV2(void)
{
  // Новая идея .
  // DAN 25.05.2016 - Инициализируем прерывание ДЗВ по переднему фронту , если
  // разрешающим уровнем является верхний , и по заднему фронту , если разрешающим
  // уровнем является нижний .
  // Это значит , что в прерывание будем заходить по заданному фронту и , т.о. отслеживать
  // либо нижний , либо верхний уровень сигналов ДЗВ , что нужно для алгоритма работы ДЗВ .
    if ( _DZVA2_Ok_level == 1 )
	{
        GPIO_IntCmd( _DZVA2_Port, _DZVA2_Bit, 0); // Rising
    	//dzva2 = 0;
	}
    else
    {
		GPIO_IntCmd( _DZVA2_Port, _DZVA2_Bit, 1); // Falling
	    //dzva2 = 1;
	}
	if ( _DZVK2_Ok_level == 1 )
	{
        GPIO_IntCmd( _DZVK2_Port, _DZVK2_Bit, 0); // Rising
    	//dzvk2 = 0;
	}
	else
	{
        GPIO_IntCmd( _DZVK2_Port, _DZVK2_Bit, 1); // Falling
		//dzvk2 = 1;
	}

  // Старая идея .
  // DAN 24.05.2016 - Инициализируем прерывание ДЗВ и по переднему , и по заднему фронтам .
  // Это значит , что в прерывание будем заходить по обоим фронтам и , т.о. отслеживать
  // и нижний и верхний уровень сигналов ДЗВ , что нужно для алгоритма работы ДЗВ .
  //ДЗВА2
    //GPIO_IntCmd( _DZVA2_Port, _DZVA2_Bit, 0); // Rising
    //GPIO_IntCmd( _DZVA2_Port, _DZVA2_Bit, 1); // Falling

  //ДЗВК2
    //GPIO_IntCmd( _DZVK2_Port, _DZVK2_Bit, 0); // Rising
    //GPIO_IntCmd( _DZVK2_Port, _DZVK2_Bit, 1); // Falling

    NVIC_SetPriority( GPIO_IRQn, IntPriority(3, 4));
    NVIC_EnableIRQ( GPIO_IRQn );

  Clr_DZV2() ;
}

// состояние ДЗВ А
// если сработало ДЗВ, то сбрасываем флаг и возвращаем 1
byte DZVA_Ok(void)
{
  byte ah = 0;

/* DAN 24.05.2016 - Нулевая идея , так было неправильно .
  // если сработало ДЗВ, то сбрасываем флаг и возвращаем 1
  ah = (b)GPIO_GetIntStatus( _DZVA_Port, _DZVA_Bit, _DZVA_Ok_level);
  if ( ah ) GPIO_ClearInt( _DZVA_Port, _DZVA_Bit);
  NVIC_SetPriority( GPIO_IRQn , IntPriority(4, 1));
  NVIC_EnableIRQ( GPIO_IRQn  );
  return ah;*/

  // Старая идея .
  // DAN 24.05.2016 - Просто возвращаем значение , считанное по прерыванию по фронтам ,
  // это значение соответствует значению уровня
  // return dzva1;

  // Новая идея .
  // ВНИМАНИЕ ! Продумано только для разрешающего уровня "1" . Продумать, как будет при
  // разрешающем нулевом уровне .
  // DAN 25.05.2016 - Проверяем уровень , если он разрешающий , возвращаем "1" . Если же
  // он запрещающий , то возвращаем запомненное значение ДЗВ и сбрасываем ДЗВ .
  // Проверка уровня сделана на тот случай , если мы прочитаем ДЗВ , сбросим его , а при
  // следующем прочтении наколемся , т.к. прерывание реагирует только на фронты ,
  // а не на уровни...
 // if ( (LPC_GPIO0->PIN >> _DZVA_Bit) & 0x1)  ah = 1;
 // else ah = dzva1;
 // dzva1 = 0;
    if ( _DZVA_Ok_level == 1 )
    {
      if ((INTReg_GPIO_R[_DZVA_Port]&(0x1<<_DZVA_Bit))!= 0)
      {
        ah = 1;
      }
    }
    else
    {
      if ((INTReg_GPIO_F[_DZVA_Port]&(0x1<<_DZVA_Bit))!= 0)
      {
        ah = 1;
      }

    }

  return ah;
}

// состояние ДЗВ А2
// если сработало ДЗВ, то сбрасываем флаг и возвращаем 1
byte DZVA2_Ok(void)
{
  byte ah = 0;

/* DAN 24.05.2016 - Нулевая идея , так было неправильно .
  // если сработало ДЗВ, то сбрасываем флаг и возвращаем 1
  ah = (b)GPIO_GetIntStatus( _DZVA2_Port, _DZVA2_Bit, _DZVA2_Ok_level);
  if ( ah ) GPIO_ClearInt( _DZVA2_Port, _DZVA2_Bit);
  NVIC_SetPriority( GPIO_IRQn , IntPriority(4, 1));
  NVIC_EnableIRQ( GPIO_IRQn  );
  return ah;*/

  // Старая идея .
  // DAN 24.05.2016 - Просто возвращаем значение , считанное по прерыванию по фронтам ,
  // это значение соответствует значению уровня
  // return dzva2;

  // Новая идея .
  // ВНИМАНИЕ ! Продумано только для разрешающего уровня "1" . Продумать, как будет при
  // разрешающем нулевом уровне .
  // DAN 25.05.2016 - Проверяем уровень , если он разрешающий , возвращаем "1" . Если же
  // он запрещающий , то возвращаем запомненное значение ДЗВ и сбрасываем ДЗВ .
  // Проверка уровня сделана на тот случай , если мы прочитаем ДЗВ , сбросим его , а при
  // следующем прочтении наколемся , т.к. прерывание реагирует только на фронты ,
  // а не на уровни...
    if ( _DZVA2_Ok_level == 1 )
    {
      if ((INTReg_GPIO_R[_DZVA2_Port]&(0x1<<_DZVA2_Bit))!= 0)
      {
        ah = 1;
      }
    }
    else
    {
      if ((INTReg_GPIO_F[_DZVA2_Port]&(0x1<<_DZVA2_Bit))!= 0)
      {
        ah = 1;
      }

    }
  //if ( (LPC_GPIO2->PIN >> _DZVA2_Bit) & 0x1)  ah = 1;
  //else ah = dzva2;
  //dzva2 = 0;
  // mUSEL_clr();
  return ah;
}

// состояние ДЗВ К
// если сработало ДЗВ, то сбрасываем флаг и возвращаем 1
byte DZVK_Ok(void)
{
  byte ah = 0 ;

/* DAN 24.05.2016 - Нулевая идея , так было неправильно .
  // если сработало ДЗВ, то сбрасываем флаг и возвращаем 1
  ah = (b)GPIO_GetIntStatus( _DZVK_Port, _DZVK_Bit, _DZVK_Ok_level);
  if ( ah ) GPIO_ClearInt( _DZVK_Port, _DZVK_Bit);
  return ah;*/

  // Старая идея .
  // DAN 24.05.2016 - Просто возвращаем значение , считанное по прерыванию по фронтам ,
  // это значение соответствует значению уровня
  // return dzvk1;

  // Новая идея .
  // ВНИМАНИЕ ! Продумано только для разрешающего уровня "1" . Продумать, как будет при
  // разрешающем нулевом уровне .
  // DAN 25.05.2016 - Проверяем уровень , если он разрешающий , возвращаем "1" . Если же
  // он запрещающий , то возвращаем запомненное значение ДЗВ и сбрасываем ДЗВ .
  // Проверка уровня сделана на тот случай , если мы прочитаем ДЗВ , сбросим его , а при
  // следующем прочтении наколемся , т.к. прерывание реагирует только на фронты ,
  // а не на уровни...

    if ( _DZVK_Ok_level == 1 )
    {
      if ((INTReg_GPIO_R[_DZVK_Port]&(0x1<<_DZVK_Bit))!= 0)
      {
        ah = 1;
      }
    }
    else
    {
      if ((INTReg_GPIO_F[_DZVK_Port]&(0x1<<_DZVK_Bit))!= 0)
      {
        ah = 1;
      }
      
    }
  //if ( (LPC_GPIO0->PIN >> _DZVK_Bit) & 0x1)  ah = 1;
  //else ah = dzvk1;
  //dzvk1 = 0;
  
  return ah;
}

// состояние ДЗВ К2
// если сработало ДЗВ, то сбрасываем флаг и возвращаем 1
byte DZVK2_Ok(void)
{
  byte ah = 0;

/* DAN 24.05.2016 - Нулевая идея , так было неправильно .
  // если сработало ДЗВ, то сбрасываем флаг и возвращаем 1
  ah = (b)GPIO_GetIntStatus( _DZVK2_Port, _DZVK2_Bit, _DZVK2_Ok_level);
  if ( ah ) GPIO_ClearInt( _DZVK2_Port, _DZVK2_Bit);
  return ah;*/

  // Старая идея .
  // DAN 24.05.2016 - Просто возвращаем значение , считанное по прерыванию по фронтам ,
  // это значение соответствует значению уровня
  // return dzvk1;

  // Новая идея .
  // ВНИМАНИЕ ! Продумано только для разрешающего уровня "1" . Продумать, как будет при
  // разрешающем нулевом уровне .
  // DAN 25.05.2016 - Проверяем уровень , если он разрешающий , возвращаем "1" . Если же
  // он запрещающий , то возвращаем запомненное значение ДЗВ и сбрасываем ДЗВ .
  // Проверка уровня сделана на тот случай , если мы прочитаем ДЗВ , сбросим его , а при
  // следующем прочтении наколемся , т.к. прерывание реагирует только на фронты ,
  // а не на уровни...
  //if ( (LPC_GPIO2->PIN >> _DZVK2_Bit) & 0x1)  ah = 1;
  //else ah = dzvk2;
  //dzvk2 = 0;
    if ( _DZVK2_Ok_level == 1 )
    {
      if ((INTReg_GPIO_R[_DZVK2_Port]&(0x1<<_DZVK2_Bit))!= 0)
      {
        ah = 1;
      }
    }
    else
    {
      if ((INTReg_GPIO_F[_DZVK2_Port]&(0x1<<_DZVK2_Bit))!= 0)
      {
        ah = 1;
      }
      
    }
 
  return ah;
}

// сброс всех ДЗВ
void Clr_DZV(void)
{
  lword lax, lbx;
  //Очищается регистр ДЗВ следующим образом: Если прерывание было, и 
  //сигнала ДЗВ в соответствующем бите порта нет, то Сигнал наличия ДЗВ
  //сбрасывается, если же активнй сигнал от ДЗВ приходит, то соответствующий 
  //бит регистра остается в 1
  if (_DZVA_Port == 0)
  {
    lax = LPC_GPIO0->PIN &(0x1<<_DZVA_Bit);
  }
  else
  {
    lax = LPC_GPIO2->PIN &(0x1<<_DZVA_Bit);    
  }
  
  if (_DZVK_Port == 0)
  {
    lbx = LPC_GPIO0->PIN &(0x1<<_DZVK_Bit);
  }
  else
  {
    lbx = LPC_GPIO2->PIN &(0x1<<_DZVK_Bit);    
  }
  
  if (lax != 0)
  {
    INTReg_GPIO_R[_DZVA_Port] |=   (0x1<<_DZVA_Bit);
    INTReg_GPIO_F[_DZVA_Port] &= (~(0x1<<_DZVA_Bit));    
  }
  else
  {
    INTReg_GPIO_R[_DZVA_Port] &= (~(0x1<<_DZVA_Bit));
    INTReg_GPIO_F[_DZVA_Port] |=   (0x1<<_DZVA_Bit);    
  }  
  
  if (lbx != 0)
  {
    INTReg_GPIO_R[_DZVK_Port] |=   (0x1<<_DZVK_Bit);
    INTReg_GPIO_F[_DZVK_Port] &= (~(0x1<<_DZVK_Bit));    
  }
  else
  {
    INTReg_GPIO_R[_DZVK_Port] &= (~(0x1<<_DZVK_Bit));
    INTReg_GPIO_F[_DZVK_Port] |=   (0x1<<_DZVK_Bit);    
  }  
}

void Clr_DZV2(void)
{
  lword lax, lbx;
  //Очищается регистр ДЗВ следующим образом: Если прерывание было, и 
  //сигнала ДЗВ в соответствующем бите порта нет, то Сигнал наличия ДЗВ
  //сбрасывается, если же активнй сигнал от ДЗВ приходит, то соответствующий 
  //бит регистра остается в 1
  
  if (_DZVA2_Port == 0)
  {
    lax = LPC_GPIO0->PIN &(0x1<<_DZVA2_Bit);
  }
  else
  {
    lax = LPC_GPIO2->PIN &(0x1<<_DZVA2_Bit);    
  }
  
  if (_DZVK2_Port == 0)
  {
    lbx = LPC_GPIO0->PIN &(0x1<<_DZVK2_Bit);
  }
  else
  {
    lbx = LPC_GPIO2->PIN &(0x1<<_DZVK2_Bit);    
  }
  
  if (lax != 0)
  {
    INTReg_GPIO_R[_DZVA2_Port] |=   (0x1<<_DZVA2_Bit);
    INTReg_GPIO_F[_DZVA2_Port] &= (~(0x1<<_DZVA2_Bit));    
  }
  else
  {
    INTReg_GPIO_R[_DZVA2_Port] &= (~(0x1<<_DZVA2_Bit));
    INTReg_GPIO_F[_DZVA2_Port] |=   (0x1<<_DZVA2_Bit);    
  }  
  
  if (lbx != 0)
  {
    INTReg_GPIO_R[_DZVK2_Port] |=   (0x1<<_DZVK2_Bit);
    INTReg_GPIO_F[_DZVK2_Port] &= (~(0x1<<_DZVK2_Bit));    
  }
  else
  {
    INTReg_GPIO_R[_DZVK2_Port] &= (~(0x1<<_DZVK2_Bit));
    INTReg_GPIO_F[_DZVK2_Port] |=   (0x1<<_DZVK2_Bit);    
  }  
}

// сброс ДЗВ А
void Clr_DZVA(void)   { 
  lword lax;
  //Очищается регистр ДЗВ следующим образом: Если прерывание было, и 
  //сигнала ДЗВ в соответствующем бите порта нет, то Сигнал наличия ДЗВ
  //сбрасывается, если же активнй сигнал от ДЗВ приходит, то соответствующий 
  //бит регистра остается в 1
  if (_DZVA_Port == 0)
  {
    lax = LPC_GPIO0->PIN &(~(0x1<<_DZVA_Bit));
  }
  else
  {
    lax = LPC_GPIO2->PIN &(~(0x1<<_DZVA_Bit));    
  }
  
  if (lax != 0)
  {
    INTReg_GPIO_R[_DZVA_Port] |=   (0x1<<_DZVA_Bit);
    INTReg_GPIO_F[_DZVA_Port] &= (~(0x1<<_DZVA_Bit));    
  }
  else
  {
    INTReg_GPIO_R[_DZVA_Port] &= (~(0x1<<_DZVA_Bit));
    INTReg_GPIO_F[_DZVA_Port] |=   (0x1<<_DZVA_Bit);    
  }  
                        
}
void Clr_DZVA2(void)  { 
  lword lax;
  //Очищается регистр ДЗВ следующим образом: Если прерывание было, и 
  //сигнала ДЗВ в соответствующем бите порта нет, то Сигнал наличия ДЗВ
  //сбрасывается, если же активнй сигнал от ДЗВ приходит, то соответствующий 
  //бит регистра остается в 1
  if (_DZVA2_Port == 0)
  {
    lax = LPC_GPIO0->PIN &(~(0x1<<_DZVA2_Bit));
  }
  else
  {
    lax = LPC_GPIO2->PIN &(~(0x1<<_DZVA2_Bit));    
  }
  
  if (lax != 0)
  {
    INTReg_GPIO_R[_DZVA2_Port] |=   (0x1<<_DZVA2_Bit);
    INTReg_GPIO_F[_DZVA2_Port] &= (~(0x1<<_DZVA2_Bit));    
  }
  else
  {
    INTReg_GPIO_R[_DZVA2_Port] &= (~(0x1<<_DZVA2_Bit));
    INTReg_GPIO_F[_DZVA2_Port] |=   (0x1<<_DZVA2_Bit);    
  }  
}

// сброс ДЗВ К
void Clr_DZVK(void)   { 
  lword lax;
  //Очищается регистр ДЗВ следующим образом: Если прерывание было, и 
  //сигнала ДЗВ в соответствующем бите порта нет, то Сигнал наличия ДЗВ
  //сбрасывается, если же активнй сигнал от ДЗВ приходит, то соответствующий 
  //бит регистра остается в 1
  if (_DZVK_Port == 0)
  {
    lax = LPC_GPIO0->PIN &(~(0x1<<_DZVK_Bit));
  }
  else
  {
    lax = LPC_GPIO2->PIN &(~(0x1<<_DZVK_Bit));    
  }
  
  if (lax != 0)
  {
    INTReg_GPIO_R[_DZVK_Port] |=   (0x1<<_DZVK_Bit);
    INTReg_GPIO_F[_DZVK_Port] &= (~(0x1<<_DZVK_Bit));    
  }
  else
  {
    INTReg_GPIO_R[_DZVK_Port] &= (~(0x1<<_DZVK_Bit));
    INTReg_GPIO_F[_DZVK_Port] |=   (0x1<<_DZVK_Bit);    
  }  
}
void Clr_DZVK2(void)  { 
  lword lax;
  //Очищается регистр ДЗВ следующим образом: Если прерывание было, и 
  //сигнала ДЗВ в соответствующем бите порта нет, то Сигнал наличия ДЗВ
  //сбрасывается, если же активнй сигнал от ДЗВ приходит, то соответствующий 
  //бит регистра остается в 1
  if (_DZVK2_Port == 0)
  {
    lax = LPC_GPIO0->PIN &(~(0x1<<_DZVK2_Bit));
  }
  else
  {
    lax = LPC_GPIO2->PIN &(~(0x1<<_DZVK2_Bit));    
  }
  
  if (lax != 0)
  {
    INTReg_GPIO_R[_DZVK2_Port] |=   (0x1<<_DZVK2_Bit);
    INTReg_GPIO_F[_DZVK2_Port] &= (~(0x1<<_DZVK2_Bit));    
  }
  else
  {
    INTReg_GPIO_R[_DZVK2_Port] &= (~(0x1<<_DZVK2_Bit));
    INTReg_GPIO_F[_DZVK2_Port] |=   (0x1<<_DZVK2_Bit);    
  }  
}

#endif
