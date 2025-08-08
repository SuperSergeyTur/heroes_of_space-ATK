#ifndef _MENU_H
#define _MENU_H
/*!
 * @file menu.h
 * @date  10 фев. 2023 г.
 * @authors Sergey Tur
 */
#include <types.h>
   
#ifndef _No_Items_Prompt

#define _No_Items_Prompt  "Нет эл.меню"

#endif

#ifndef _MenuMaxLevel
/*!
 *  @def  _MenuMaxLevel
 *  @brief Уровень вложенности меню
 *  @date  06.03.2023
 *  @authors Sergey Tur
 */
#define _MenuMaxLevel 5

#endif   
   
/*!
 * @struct Def_menu_item
 * @brief  Простейшая стурктура, описывающая пункт меню
 */
typedef struct {
  char const *gruppa; //!<Название пункта
  void const * Item;  //!<Указатель на структуру уставки, либо пункта меню, которая может быть двух типов: либо Def_menu_item, либо UstUzm
  word type;          //!<Описание типа структуры Item : 0 - меню, 1 - список уставок типа UstUzmб 2 - уставка
} Def_menu_item;
/*!
 * @struct  Menu_items
 * @brief Структура для программы  многоуровнего меню
 */
typedef struct{
  char const  *Menu_Prompt; //!< Назавание меню       
  const Def_menu_item * items;    //!< Массив, содержащий пункты меню
  word size;                //!< Число элементов массива   
} Menu_items;

/*!
 *  @struct  Menu_str
*  @brief   Структура, содержащая статические элементы рекурсивной функции Menu::Menu_Item
 *  необходима в качестве стека для вызова многоуровнего меню 
 *  @date  15.02.2023
 *  @authors Serhey
 */

typedef struct {
  word Label ;  //!< Метка для switch
  word index ;//!< индекс, определяет какой элемент сейчас обрабатывается
  word tst_output;   //!< тригер, взводится чтобы повторить вывод после отпускаения клавиши изменения, если не успели вывести символ до нажатия

} Menu_str;

typedef  word (*Prc_ptr) ( void const*, word * )  ;
/*!
 *  @class  Menu
 *  @brief  Класс многоуровнего меню
 *  @date  15.02.2023
 *  @authors Sergey Tur
 */

class Menu
{
private:
   ///Указатель на структуру элементов меню, передается извне
  //const Menu_items * Items;
  ///Стек для вложенного меню, максимальный уровень вложенности по умолчанию = 5
  Menu_str Menu_Bufer[_MenuMaxLevel];
  ///Текущий уровень вложенности
  word Menu_level;
  //Командное слово для управления меню из вызываемой программы
  word CommWord;
  ///Показывает заданы ли элементы меню
  bool  Item_set ;
 
  void  Out_Menu (const Menu_items * ptr);
  word Menu_Item(const Menu_items * ptr);
  ///Указатель на функцию обработки выбора пункта меню
  Prc_ptr Item_prc ;
public:
  /*!
   * @brief  Конструктор класса Menu, задаем начальные условия
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
   * @brief  Инициализация класса Menu
   * @param Адрес структуры типа Menu_items, описывающий элементы меню 
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
   * @brief  Программа вывода меню
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