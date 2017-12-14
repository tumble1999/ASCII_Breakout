#include "Menu.h"
#include "../../Core/Utils.h"

//TODO: Add comments to this file

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

//Sets up the menu with the MENU ITEMS
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


//sees if the menu items are in the right place
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


//puts the menu on the screen
void Menu::Render(ASCIIRenderer * pRenderer)
{
	for each (MenuItem* menuItem in m_menuItems)
	{
		menuItem->Render(pRenderer);
	}
}


//moves the selection up
void Menu::GoUp()
{
	m_selectedItem += m_menuItems.size();
	m_selectedItem++;
	m_selectedItem %= m_menuItems.size();
}

//moves the selection down
void Menu::GoDown()
{
	m_selectedItem += m_menuItems.size();
	m_selectedItem--;
	m_selectedItem %= m_menuItems.size();
}

//gets the id of the selected menu id
char* Menu::GetSelectedMenuItemID() const
{
	return m_menuItems[m_selectedItem]->GetId();
}


//sets the specific item as active
void Menu::SetActive(char* id)
{
	for (int i = 0; i < m_menuItems.size(); i++)
	{
		MenuItem* menuItem = m_menuItems[i];
		if (menuItem->GetId() == id)
		{
			m_selectedItem = i;
			return;
		}
	}
}
