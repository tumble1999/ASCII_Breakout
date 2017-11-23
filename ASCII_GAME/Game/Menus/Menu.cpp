#include "Menu.h"

Menu::Menu()
{
	m_pos = Vector2(0,0);
	m_initialised = false;
}

Menu::~Menu()
{
}

void Menu::Initialise(Vector2& pos, std::vector<MenuItem> menuItems)
{
	m_menuItems = menuItems;
	m_pos = pos;

	m_initialised = true;

}

void Menu::Update()
{
	for (int i = 0; i < m_menuItems.size(); i++)
	{
		m_menuItems[i].Update();
	}
}

void Menu::Render(ASCIIRenderer * pRenderer)
{
	for (int i = 0; i < m_menuItems.size(); i++)
	{
		m_menuItems[i].Render(pRenderer);
	}
}
