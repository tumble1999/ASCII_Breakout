#include "Menu.h"

Menu::Menu()
{
	m_pos = Vector2(0,0);
	m_initialized = false;
}

Menu::~Menu()
{
}

void Menu::Initialize(Vector2& pos, std::vector<MenuItem>& menuItems)
{
	m_menuItems = menuItems;
	m_pos = pos;

	m_initialized = true;

	
	// 	calls this: std::vector<MenuItem,std::allocator<MenuItem> >::~vector<MenuItem,std::allocator<MenuItem> >()

}

void Menu::Update()
{
	for each (MenuItem menuItem in m_menuItems)
	{
		menuItem.Update();
	}
}

void Menu::Render(ASCIIRenderer * pRenderer)
{
	for each (MenuItem menuItem in m_menuItems)
	{
		menuItem.Render(pRenderer);
	}
}