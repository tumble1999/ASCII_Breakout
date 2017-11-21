#ifndef _MENU_H_
#define _MENU_H_

#include "MenuItem.h"

class Menu
{
public:
	Menu();
	~Menu();

private:
	std::vector<MenuItem> m_menuItems;
	int m_selectedItem;
};

#endif // !_MENU_H_
