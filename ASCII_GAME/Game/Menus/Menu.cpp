#include "Menu.h"
#include "../../Core/Utils.h"

Menu::Menu()
{
	m_pos = Vector2(0,0);
	m_initialized = false;
}

Menu::~Menu()
{
	for (int i = 0; i < m_menuItems.size(); i++)
	{
		SAFE_DELETE_PTR(m_menuItems[i]);
	}
}

void Menu::Initialize(Vector2& pos, std::vector<MenuItem*>& menuItems)
{
	for (int i = 0; i < menuItems.size(); i++)
	{
		m_menuItems.push_back(menuItems[i]);
	}
	
	m_pos = pos;

	m_initialized = true;

	
	// 	calls this: std::vector<MenuItem,std::allocator<MenuItem> >::~vector<MenuItem,std::allocator<MenuItem> >()

}

void Menu::Update()
{
	for each (MenuItem* menuItem in m_menuItems)
	{
		menuItem->Update();
	}
}

void Menu::Render(ASCIIRenderer * pRenderer)
{
	for each (MenuItem* menuItem in m_menuItems)
	{
		menuItem->Render(pRenderer);
	}
}
