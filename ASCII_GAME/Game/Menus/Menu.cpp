#include "Menu.h"
#include "../../Core/Utils.h"

Menu::Menu()
{
	m_pos = Vector2(0,0);
	m_initialized = false;
	m_selectedItem = 0;
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
		menuItems[i]->SetPos(pos + Vector2(0, i * (7+3)));
		m_menuItems.push_back(menuItems[i]);
	}
	
	m_pos = pos;

	m_initialized = true;

	
	// 	calls this: std::vector<MenuItem,std::allocator<MenuItem> >::~vector<MenuItem,std::allocator<MenuItem> >()

}

void Menu::Update()
{
	for (int i = 0; i < m_menuItems.size(); i++)
	{
		MenuItem* menuItem = m_menuItems[i];
		menuItem->Update();

		if (m_selectedItem == i)
		{
			menuItem->Select();
		}
		else
		{
			menuItem->Deselect();
		}
	}
}

void Menu::Render(ASCIIRenderer * pRenderer)
{
	for each (MenuItem* menuItem in m_menuItems)
	{
		menuItem->Render(pRenderer);
	}
}

void Menu::GoUp()
{
	m_selectedItem += m_menuItems.size();
	m_selectedItem++;
	m_selectedItem %= m_menuItems.size();
}

void Menu::GoDown()
{
	m_selectedItem += m_menuItems.size();
	m_selectedItem--;
	m_selectedItem %= m_menuItems.size();
}

void Menu::RunSelected()
{

}
