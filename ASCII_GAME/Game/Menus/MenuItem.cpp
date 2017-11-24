#include "MenuItem.h"

MenuItem::MenuItem()
{
	m_initialised = false;
	m_text = "";
	m_highlighted = false;
}

MenuItem::MenuItem(std::string text)
{
	Initialise(text);
}

MenuItem::~MenuItem()
{
}

void MenuItem::Initialise(std::string text)
{
	m_text = text;

	UpdateMenuItemSprite();
	Sprite::Initialise(GetMenuItemArray(), Vector2(m_text.size(),1));

	m_initialised = true;
}



void MenuItem::Update()
{
}

void MenuItem::Render(ASCIIRenderer * pRenderer)
{
	Sprite::Render(pRenderer);
}

void MenuItem::UpdateMenuItemSprite()
{
	m_MenuItemSprite.clear();
	if (m_highlighted)
	{
		m_MenuItemSprite.push_back({ '[', BACKGROUND_WHITE });

	}
	for (int i = 0; i < m_text.size(); i++)
	{
		WCHAR currentChar = m_text[i];
		m_MenuItemSprite.push_back({ currentChar, BACKGROUND_WHITE });
	}
	if (m_highlighted)
	{
		m_MenuItemSprite.push_back({ ']', BACKGROUND_WHITE });

	}
}

CHAR_INFO * MenuItem::GetMenuItemArray()
{
	return m_MenuItemSprite.data();
}
