#ifndef _MENU_H_
#define _MENU_H_

#include "MenuItem.h"

class Menu
{
public:
	Menu();
	~Menu();

	void Initialise(Vector2 & pos, std::vector<MenuItem> menuItems);
	void Update();
	void Render(ASCIIRenderer *pRenderer);

private:
	Vector2& m_pos;
	std::vector<MenuItem> m_menuItems;
	int m_selectedItem;

	bool m_initialised;
};

#endif // !_MENU_H_
