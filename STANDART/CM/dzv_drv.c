#ifndef _dzv_drv_c
#define _dzv_drv_c

void init_DZV(void)
{
  // ����� ���� .
  // DAN 25.05.2016 - �������������� ���������� ��� �� ��������� ������ , ����
  // ����������� ������� �������� ������� , � �� ������� ������ , ���� �����������
  // ������� �������� ������ .
  // ��� ������ , ��� � ���������� ����� �������� �� ��������� ������ � , �.�. �����������
  // ���� ������ , ���� ������� ������� �������� ��� , ��� ����� ��� ��������� ������ ��� .
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

  // ������ ���� .
  // DAN 24.05.2016 - �������������� ���������� ��� � �� ��������� , � �� ������� ������� .
  // ��� ������ , ��� � ���������� ����� �������� �� ����� ������� � , �.�. �����������
  // � ������ � ������� ������� �������� ��� , ��� ����� ��� ��������� ������ ��� .
  //����
    //GPIO_IntCmd( _DZVA_Port, _DZVA_Bit, 0); // Rising
    //GPIO_IntCmd( _DZVA_Port, _DZVA_Bit, 1); // Falling

  //����
    //GPIO_IntCmd( _DZVK_Port, _DZVK_Bit, 0); // Rising
    //GPIO_IntCmd( _DZVK_Port, _DZVK_Bit, 1); // Falling

    NVIC_SetPriority( GPIO_IRQn, IntPriority(3, 4));
    NVIC_EnableIRQ( GPIO_IRQn );

  Clr_DZV() ;
}
//***************

void init_DZV2(void)
{
  // ����� ���� .
  // DAN 25.05.2016 - �������������� ���������� ��� �� ��������� ������ , ����
  // ����������� ������� �������� ������� , � �� ������� ������ , ���� �����������
  // ������� �������� ������ .
  // ��� ������ , ��� � ���������� ����� �������� �� ��������� ������ � , �.�. �����������
  // ���� ������ , ���� ������� ������� �������� ��� , ��� ����� ��� ��������� ������ ��� .
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

  // ������ ���� .
  // DAN 24.05.2016 - �������������� ���������� ��� � �� ��������� , � �� ������� ������� .
  // ��� ������ , ��� � ���������� ����� �������� �� ����� ������� � , �.�. �����������
  // � ������ � ������� ������� �������� ��� , ��� ����� ��� ��������� ������ ��� .
  //����2
    //GPIO_IntCmd( _DZVA2_Port, _DZVA2_Bit, 0); // Rising
    //GPIO_IntCmd( _DZVA2_Port, _DZVA2_Bit, 1); // Falling

  //����2
    //GPIO_IntCmd( _DZVK2_Port, _DZVK2_Bit, 0); // Rising
    //GPIO_IntCmd( _DZVK2_Port, _DZVK2_Bit, 1); // Falling

    NVIC_SetPriority( GPIO_IRQn, IntPriority(3, 4));
    NVIC_EnableIRQ( GPIO_IRQn );

  Clr_DZV2() ;
}

// ��������� ��� �
// ���� ��������� ���, �� ���������� ���� � ���������� 1
byte DZVA_Ok(void)
{
  byte ah = 0;

/* DAN 24.05.2016 - ������� ���� , ��� ���� ����������� .
  // ���� ��������� ���, �� ���������� ���� � ���������� 1
  ah = (b)GPIO_GetIntStatus( _DZVA_Port, _DZVA_Bit, _DZVA_Ok_level);
  if ( ah ) GPIO_ClearInt( _DZVA_Port, _DZVA_Bit);
  NVIC_SetPriority( GPIO_IRQn , IntPriority(4, 1));
  NVIC_EnableIRQ( GPIO_IRQn  );
  return ah;*/

  // ������ ���� .
  // DAN 24.05.2016 - ������ ���������� �������� , ��������� �� ���������� �� ������� ,
  // ��� �������� ������������� �������� ������
  // return dzva1;

  // ����� ���� .
  // �������� ! ��������� ������ ��� ������������ ������ "1" . ���������, ��� ����� ���
  // ����������� ������� ������ .
  // DAN 25.05.2016 - ��������� ������� , ���� �� ����������� , ���������� "1" . ���� ��
  // �� ����������� , �� ���������� ����������� �������� ��� � ���������� ��� .
  // �������� ������ ������� �� ��� ������ , ���� �� ��������� ��� , ������� ��� , � ���
  // ��������� ��������� ��������� , �.�. ���������� ��������� ������ �� ������ ,
  // � �� �� ������...
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

// ��������� ��� �2
// ���� ��������� ���, �� ���������� ���� � ���������� 1
byte DZVA2_Ok(void)
{
  byte ah = 0;

/* DAN 24.05.2016 - ������� ���� , ��� ���� ����������� .
  // ���� ��������� ���, �� ���������� ���� � ���������� 1
  ah = (b)GPIO_GetIntStatus( _DZVA2_Port, _DZVA2_Bit, _DZVA2_Ok_level);
  if ( ah ) GPIO_ClearInt( _DZVA2_Port, _DZVA2_Bit);
  NVIC_SetPriority( GPIO_IRQn , IntPriority(4, 1));
  NVIC_EnableIRQ( GPIO_IRQn  );
  return ah;*/

  // ������ ���� .
  // DAN 24.05.2016 - ������ ���������� �������� , ��������� �� ���������� �� ������� ,
  // ��� �������� ������������� �������� ������
  // return dzva2;

  // ����� ���� .
  // �������� ! ��������� ������ ��� ������������ ������ "1" . ���������, ��� ����� ���
  // ����������� ������� ������ .
  // DAN 25.05.2016 - ��������� ������� , ���� �� ����������� , ���������� "1" . ���� ��
  // �� ����������� , �� ���������� ����������� �������� ��� � ���������� ��� .
  // �������� ������ ������� �� ��� ������ , ���� �� ��������� ��� , ������� ��� , � ���
  // ��������� ��������� ��������� , �.�. ���������� ��������� ������ �� ������ ,
  // � �� �� ������...
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

// ��������� ��� �
// ���� ��������� ���, �� ���������� ���� � ���������� 1
byte DZVK_Ok(void)
{
  byte ah = 0 ;

/* DAN 24.05.2016 - ������� ���� , ��� ���� ����������� .
  // ���� ��������� ���, �� ���������� ���� � ���������� 1
  ah = (b)GPIO_GetIntStatus( _DZVK_Port, _DZVK_Bit, _DZVK_Ok_level);
  if ( ah ) GPIO_ClearInt( _DZVK_Port, _DZVK_Bit);
  return ah;*/

  // ������ ���� .
  // DAN 24.05.2016 - ������ ���������� �������� , ��������� �� ���������� �� ������� ,
  // ��� �������� ������������� �������� ������
  // return dzvk1;

  // ����� ���� .
  // �������� ! ��������� ������ ��� ������������ ������ "1" . ���������, ��� ����� ���
  // ����������� ������� ������ .
  // DAN 25.05.2016 - ��������� ������� , ���� �� ����������� , ���������� "1" . ���� ��
  // �� ����������� , �� ���������� ����������� �������� ��� � ���������� ��� .
  // �������� ������ ������� �� ��� ������ , ���� �� ��������� ��� , ������� ��� , � ���
  // ��������� ��������� ��������� , �.�. ���������� ��������� ������ �� ������ ,
  // � �� �� ������...

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

// ��������� ��� �2
// ���� ��������� ���, �� ���������� ���� � ���������� 1
byte DZVK2_Ok(void)
{
  byte ah = 0;

/* DAN 24.05.2016 - ������� ���� , ��� ���� ����������� .
  // ���� ��������� ���, �� ���������� ���� � ���������� 1
  ah = (b)GPIO_GetIntStatus( _DZVK2_Port, _DZVK2_Bit, _DZVK2_Ok_level);
  if ( ah ) GPIO_ClearInt( _DZVK2_Port, _DZVK2_Bit);
  return ah;*/

  // ������ ���� .
  // DAN 24.05.2016 - ������ ���������� �������� , ��������� �� ���������� �� ������� ,
  // ��� �������� ������������� �������� ������
  // return dzvk1;

  // ����� ���� .
  // �������� ! ��������� ������ ��� ������������ ������ "1" . ���������, ��� ����� ���
  // ����������� ������� ������ .
  // DAN 25.05.2016 - ��������� ������� , ���� �� ����������� , ���������� "1" . ���� ��
  // �� ����������� , �� ���������� ����������� �������� ��� � ���������� ��� .
  // �������� ������ ������� �� ��� ������ , ���� �� ��������� ��� , ������� ��� , � ���
  // ��������� ��������� ��������� , �.�. ���������� ��������� ������ �� ������ ,
  // � �� �� ������...
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

// ����� ���� ���
void Clr_DZV(void)
{
  lword lax, lbx;
  //��������� ������� ��� ��������� �������: ���� ���������� ����, � 
  //������� ��� � ��������������� ���� ����� ���, �� ������ ������� ���
  //������������, ���� �� ������� ������ �� ��� ��������, �� ��������������� 
  //��� �������� �������� � 1
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
  //��������� ������� ��� ��������� �������: ���� ���������� ����, � 
  //������� ��� � ��������������� ���� ����� ���, �� ������ ������� ���
  //������������, ���� �� ������� ������ �� ��� ��������, �� ��������������� 
  //��� �������� �������� � 1
  
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

// ����� ��� �
void Clr_DZVA(void)   { 
  lword lax;
  //��������� ������� ��� ��������� �������: ���� ���������� ����, � 
  //������� ��� � ��������������� ���� ����� ���, �� ������ ������� ���
  //������������, ���� �� ������� ������ �� ��� ��������, �� ��������������� 
  //��� �������� �������� � 1
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
  //��������� ������� ��� ��������� �������: ���� ���������� ����, � 
  //������� ��� � ��������������� ���� ����� ���, �� ������ ������� ���
  //������������, ���� �� ������� ������ �� ��� ��������, �� ��������������� 
  //��� �������� �������� � 1
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

// ����� ��� �
void Clr_DZVK(void)   { 
  lword lax;
  //��������� ������� ��� ��������� �������: ���� ���������� ����, � 
  //������� ��� � ��������������� ���� ����� ���, �� ������ ������� ���
  //������������, ���� �� ������� ������ �� ��� ��������, �� ��������������� 
  //��� �������� �������� � 1
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
  //��������� ������� ��� ��������� �������: ���� ���������� ����, � 
  //������� ��� � ��������������� ���� ����� ���, �� ������ ������� ���
  //������������, ���� �� ������� ������ �� ��� ��������, �� ��������������� 
  //��� �������� �������� � 1
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
