#include "MenuItem.h"

MenuItem::MenuItem()
{
	m_initialised = false;
	m_text = "";
	m_highlighted = false;
}

MenuItem::~MenuItem()
{
}

MenuItem MenuItem::Initialise(std::string text)
{
	m_text = text;

	UpdateMenuItemSprite(" " + text + " ");
	Sprite::Initialise(GetMenuItemArray(),text.length+2);

	m_initialised = true;
	return *this;
}

void MenuItem::Update()
{
}

void MenuItem::Render(ASCIIRenderer * pRenderer)
{
	Sprite::Render(pRenderer);
}

void MenuItem::UpdateMenuItemSprite(std::string text)
{
	m_MenuItemSprite.clear();
	for (int i = 0; i < text.length; i++)
	{
		WCHAR hello = text.c_str()[i];
		m_MenuItemSprite.push_back({ hello, BACKGROUND_WHITE });
	}
}

CHAR_INFO * MenuItem::GetMenuItemArray()
{
	return m_MenuItemSprite.data();
}
