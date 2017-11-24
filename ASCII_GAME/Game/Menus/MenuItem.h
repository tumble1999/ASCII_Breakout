#ifndef _MENU_ITEM_H_
#define _MENU_ITEM_H_

#include <string>

#include "../GameObjects/GameObject.h"

class MenuItem:GameObject
{
public:
	MenuItem();
	MenuItem(std::string text);
	~MenuItem();

	void Initialise(std::string text);
	void Update();
	void Render(ASCIIRenderer* pRenderer);

private:
	std::string m_text;
	std::vector<CHAR_INFO> m_MenuItemSprite;
	bool m_highlighted;


	void UpdateMenuItemSprite();
	CHAR_INFO* GetMenuItemArray();

	bool m_initialised;
};

#endif // !_MENU_ITEM_H_
