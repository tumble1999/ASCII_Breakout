#include "MenuItem.h"

MenuItem::MenuItem()
{
	m_initialised = false;
	m_text = "";
}

MenuItem::~MenuItem()
{
}

void MenuItem::Initialise(std::string text)
{
	m_text = text;

	InitialiseMenuItemSprite();

	Sprite::Initialise(GetMenuItemArray(),);
}

void MenuItem::Update()
{
}

void MenuItem::Render(ASCIIRenderer * pRenderer)
{
}

void MenuItem::InitialiseMenuItemSprite()
{
}

CHAR_INFO * MenuItem::GetMenuItemArray()
{
	return nullptr;
}
