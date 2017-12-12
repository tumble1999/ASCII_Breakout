#ifndef _MENU_H_
#define _MENU_H_

#include "MenuItem.h"

class Menu
{
public:
	Menu();
	~Menu();

	void Initialize(Vector2 & pos, std::vector<MenuItem*>& menuItems);
	void Update();
	void Render(ASCIIRenderer *pRenderer);

	void GoUp();
	void GoDown();
	char* GetSelectedMenuItemID() const;

	void SetActive(char * id);

private:
	Vector2 m_pos;
	std::vector<MenuItem*> m_menuItems;
	int m_selectedItem;

	bool m_initialized;
};

#endif // !_MENU_H_
