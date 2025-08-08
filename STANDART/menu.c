/*!
* @file Menu.c
* @date  10.02.2023
* @authors Serhey Tur
*/
#include <menu.h>

/*!
*@brief ������� ������� ������� ���� � ��������� � ���� ��������� ������� �����������
*@param ptr - ��������� ���� Menu_items, ����������� �������� ����
*@date 13.02.2023
*@authors Serhey Tur   
*/

void  Menu::ItemsOut (const Menu_items * ptr)
{
  static word m_Level; // ������� �����������
  static byte tst_output ;  
  
  word i;
  enum{k0, k1, k2 , k3, k4 };
  if ( M_FirstCall == 1 )  //  ������������� ������� ����� ��� �������  
  {                        // ���������� ������� ...                    
    M_FirstCall = 0 ;    
    if(Item_set)
    {
      
      m_Level = 0;
      tst_output = 0 ;
      m_index = 0;
      Menu_level = -1; //��� ����, ����� ������ ������� ��� 0
      if ( Mon.Password_Ok == 0 )  Label = k0 ;  // ���� � ��������������� � ������.
      else                         Label = k2 ;  // ������� ����.
      
      for (i= 0; i < _MenuMaxLevel ; ++ i)
      {
        Menu_Bufer[i].Label = 0;
        Menu_Bufer[i].index = 0;
        Menu_Bufer[i].tst_output = 0;      
      }
    }
    else
    {
      Label = k3 ; //�� ������ �������� ����
    }
    return ;
  }
  switch ( Label )
  {
  default:
  case k0:
    output_s ( _PasswordLtd_txt ) ;
    m_time = Timer1_Ovr ;
    Label = k1 ;
    
  case k1:
    if ( (u)(w)(Timer1_Ovr - m_time) < _Time_Password_txt )  
    {
      break   ;
    }
  case k2:    //  ������� ����. 
    if (Menu_Item(ptr) == 0) 
    {
      Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;                      
    }
    break;
  case k3:
    output_s ("\r\n");
    output_s ( _PasswordLtd_txt ) ;
    m_time = Timer1_Ovr;
    Label = k4;
    break;
  case k4:
    if ( (u)((w)(Timer1_Ovr - m_time)) < _Sec(2) )  
    {
      Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;                         
    }
    break;    
    
  }
  
  
}
/*!
* @brief  ����������� ������� ��������� ������ ���� ���������� ���� ����� ����, ���� �������
* @param ��������� ���� ���� Menu_items, ����������� ������ ������ ���� 
* @return ����� ������ ������� 0 - ��������� ������, 1 - � ������
* @date 13.02.2023
* @authors Serhey Tur   
*/
word Menu::Menu_Item( const Menu_items * ptr )
{
  enum {k0, k00, k1,k2, k3, k4, k5};
  //static word IM_Label = k0, IM_index = 0,  tst_output = 0, out = 1, Code_in ;  
  word out = 1;
  //Menu_str * Tst_str;
  //����������� ������� �����������
  if (++Menu_level >= _MenuMaxLevel)
  {
    out = 0;
  }
  else
  {
    switch (Menu_Bufer[Menu_level].Label)
    {
    case k0:
      Menu_Bufer[Menu_level].index = 0;
    case k00:
      output_s ( "\r" ) ;    
      output_s ( ptr->Menu_Prompt ) ;
      output_c ( 0 );
      output_c ( '\n' ) ;    
      Menu_Bufer[Menu_level].Label = k1 ;
      break;
    case k1:
      if( TestCompleted_Output() )
      {
      case k2:
        
        output_c ( '\r' ) ;
        output_s( AWelcome );
        output_s ( ptr->items[Menu_Bufer[Menu_level].index].gruppa ) ;
        Menu_Bufer[Menu_level].tst_output = 0 ;     //����, ��� �������, �� �������� ������� ��������� ��������, ��
      }                       // ������� ������, ����� ��������� ����� ����� ����������� ������� ���������
      else  Menu_Bufer[Menu_level].tst_output = 1 ;
      
      Menu_Bufer[Menu_level].Label = k3 ;
      break ;
      //---
      //  ���������  ������
    case k3:
      while (  TestData_for_Input() )
      {
        
        mInput_c ( m_ch ) ;
        if ( m_ch == Return )
        {
          out = 0;
          Menu_Bufer[Menu_level].Label = k0;
          break;
        }
        else if ( m_ch == Down ) // ������� � ������� ������ ����.
        {
          if ( ++Menu_Bufer[Menu_level].index >= ptr->size ) Menu_Bufer[Menu_level].index = 0 ;
          
          Menu_Bufer[Menu_level].Label = k1 ;
        }
        else if ( m_ch == Up ) // ������� � ������� ������ ����.
        {
          if ( Menu_Bufer[Menu_level].index-- == 0 ) Menu_Bufer[Menu_level].index = ptr->size - 1  ;
          Menu_Bufer[Menu_level].Label = k1 ;
        }
        else if ( m_ch == Enter ) // ������� � ����� ��������� �������
        {
          output_c ( '\n' ) ;
          Menu_Bufer[Menu_level].Label = k4 ;
          break ;
        }
        else
        {
          Klav_Buff = m_ch;
        }
      }
      
      if ( Menu_Bufer[Menu_level].tst_output == 1 )  Menu_Bufer[Menu_level].Label = k1 ;
      
      if ( AWelcome != AWell_old )
      {
        AWell_old = AWelcome;
        Menu_Bufer[Menu_level].Label = k00;
      }
      
      break ;
    case k4:
      if (ptr->items[Menu_Bufer[Menu_level].index].type == 0) 
      { 
        if (Menu_Item((Menu_items *)ptr->items[Menu_Bufer[Menu_level].index].Item ) == 0)
        {
          Menu_Bufer[Menu_level].Label = k00;
        }
      }
      else
      {
       if ( (*Item_prc)(&ptr->items[Menu_Bufer[Menu_level].index],&CommWord)== 0)
       {
         Menu_Bufer[Menu_level].Label = k00;
       }
      }
      break;
      
    }
  }
  //������� �� ����� ����: ������� ����������� ���������
  --Menu_level;
  return out;
  
}


