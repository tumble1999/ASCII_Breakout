#include "MenuItem.h"

MenuItem::MenuItem()
{
	InitializeMemberVars();
}

MenuItem::MenuItem(std::string text)
{
	InitializeMemberVars();
	Initialize(text);
}

MenuItem::~MenuItem()
{
}

void MenuItem::Initialize(std::string text)
{
	m_text = text;

	UpdateMenuItemSprite();
	Sprite::Initialise(GetMenuItemArray(), Vector2(m_text.size(),1));

	m_initialized = true;
}



void MenuItem::Update()
{
}

void MenuItem::Render(ASCIIRenderer * pRenderer)
{
	Sprite::Render(pRenderer);
}

void MenuItem::InitializeMemberVars()
{
	m_initialized = false;
	m_text = "";
	m_highlighted = false;
}

void MenuItem::UpdateMenuItemSprite()
{
	m_MenuItemSprite.clear();

	if (m_highlighted)
	{
		m_MenuItemSprite.push_back({ '[', BACKGROUND_BLACK });
	}
	else
	{
		m_MenuItemSprite.push_back({ 0, BACKGROUND_BLACK });
	}

	for (size_t i = 0; i < m_text.size(); i++)
	{
		WCHAR currentChar = m_text[i];
		m_MenuItemSprite.push_back({ currentChar, BACKGROUND_BLACK });
	}
	if (m_highlighted)
	{
		m_MenuItemSprite.push_back({ ']', BACKGROUND_BLACK });

	}
	else
	{
		m_MenuItemSprite.push_back({ 0, BACKGROUND_BLACK });
	}
}

CHAR_INFO* MenuItem::GetMenuItemArray()
{
	return m_MenuItemSprite.data();
}
