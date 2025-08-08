#ifndef _MENU_H
#define _MENU_H
/*!
 * @file menu.h
 * @date  10 ���. 2023 �.
 * @authors Sergey Tur
 */
#include <types.h>
   
#ifndef _No_Items_Prompt

#define _No_Items_Prompt  "��� ��.����"

#endif

#ifndef _MenuMaxLevel
/*!
 *  @def  _MenuMaxLevel
 *  @brief ������� ����������� ����
 *  @date  06.03.2023
 *  @authors Sergey Tur
 */
#define _MenuMaxLevel 5

#endif   
   
/*!
 * @struct Def_menu_item
 * @brief  ���������� ���������, ����������� ����� ����
 */
typedef struct {
  char const *gruppa; //!<�������� ������
  void const * Item;  //!<��������� �� ��������� �������, ���� ������ ����, ������� ����� ���� ���� �����: ���� Def_menu_item, ���� UstUzm
  word type;          //!<�������� ���� ��������� Item : 0 - ����, 1 - ������ ������� ���� UstUzm� 2 - �������
} Def_menu_item;
/*!
 * @struct  Menu_items
 * @brief ��������� ��� ���������  ������������� ����
 */
typedef struct{
  char const  *Menu_Prompt; //!< ��������� ����       
  const Def_menu_item * items;    //!< ������, ���������� ������ ����
  word size;                //!< ����� ��������� �������   
} Menu_items;

/*!
 *  @struct  Menu_str
*  @brief   ���������, ���������� ����������� �������� ����������� ������� Menu::Menu_Item
 *  ���������� � �������� ����� ��� ������ ������������� ���� 
 *  @date  15.02.2023
 *  @authors Serhey
 */

typedef struct {
  word Label ;  //!< ����� ��� switch
  word index ;//!< ������, ���������� ����� ������� ������ ��������������
  word tst_output;   //!< ������, ��������� ����� ��������� ����� ����� ����������� ������� ���������, ���� �� ������ ������� ������ �� �������

} Menu_str;

typedef  word (*Prc_ptr) ( void const*, word * )  ;
/*!
 *  @class  Menu
 *  @brief  ����� ������������� ����
 *  @date  15.02.2023
 *  @authors Sergey Tur
 */

class Menu
{
private:
   ///��������� �� ��������� ��������� ����, ���������� �����
  //const Menu_items * Items;
  ///���� ��� ���������� ����, ������������ ������� ����������� �� ��������� = 5
  Menu_str Menu_Bufer[_MenuMaxLevel];
  ///������� ������� �����������
  word Menu_level;
  //��������� ����� ��� ���������� ���� �� ���������� ���������
  word CommWord;
  ///���������� ������ �� �������� ����
  bool  Item_set ;
 
  void  Out_Menu (const Menu_items * ptr);
  word Menu_Item(const Menu_items * ptr);
  ///��������� �� ������� ��������� ������ ������ ����
  Prc_ptr Item_prc ;
public:
  /*!
   * @brief  ����������� ������ Menu, ������ ��������� �������
   * @date 15.02.2023
   * @authors Sergey Tur
   */
  Menu()
  {
    int i;
    Item_set = false;
    Menu_level = -1;
    for (i= 0; i < _MenuMaxLevel ; ++ i)
    {
      Menu_Bufer[i].Label = 0;
      Menu_Bufer[i].index = 0;
      Menu_Bufer[i].tst_output = 0;      
    }
    
  }
  /*!
   * @brief  ������������� ������ Menu
   * @param ����� ��������� ���� Menu_items, ����������� �������� ���� 
   * @date 15.02.2023
   * @authors Segey Tur
   */
  
  void Set_Menu_items(Prc_ptr Prc)
  {
    //Items = ptr;    
    Item_set = true;
    Item_prc = Prc;
  }
  /*!
   * @brief  ��������� ������ ����
   * @date 15.02.2023
   * @authors Sergey Tur
   */ 
  void ItemsOut(const Menu_items * In);
//  {
//    Out_Menu (In);
//  }   
};

//extern Menu_str Menu_Bufer[];
//extern word Menu_level;
#endif