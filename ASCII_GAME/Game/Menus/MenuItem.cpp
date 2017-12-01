#include "MenuItem.h"

MenuItem::MenuItem()
{
	InitializeMemberVars();
}

MenuItem::MenuItem(char* text, Vector2 size)
{
	InitializeMemberVars();
	Initialize(text, size);
}

MenuItem::~MenuItem()
{
}

void MenuItem::Initialize(char* text, Vector2 size)
{

	UpdateMenuItemSprite();
	
	Sprite::Initialise(text, FOREGROUND_WHITE, size);
	SetPosition(Vector2(10, 10));

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
		m_MenuItemSprite.push_back({ '[', BACKGROUND_BLACK | FOREGROUND_WHITE });
	}
	else
	{
		m_MenuItemSprite.push_back({ 0, BACKGROUND_BLACK | FOREGROUND_WHITE });
	}

	for (size_t i = 0; i < m_text.size(); i++)
	{
		WCHAR currentChar = m_text[i];
		m_MenuItemSprite.push_back({ currentChar, BACKGROUND_BLACK | FOREGROUND_WHITE });
	}
	if (m_highlighted)
	{
		m_MenuItemSprite.push_back({ ']', BACKGROUND_BLACK | FOREGROUND_WHITE });

	}
	else
	{
		m_MenuItemSprite.push_back({ 0, BACKGROUND_BLACK | FOREGROUND_WHITE });
	}
}

CHAR_INFO* MenuItem::GetMenuItemArray()
{
	return m_MenuItemSprite.data();
}
