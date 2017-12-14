#include "MenuItem.h"

//TODO: Add comments to this file

MenuItem::MenuItem()
{
	InitializeMemberVars();
}

MenuItem::MenuItem(char* text, Vector2 size, char* id)
{
	InitializeMemberVars();
	m_id = id;
	Initialize(text, size);
}

MenuItem::~MenuItem()
{
}



//set up the menu item
void MenuItem::Initialize(char* text, Vector2 size)
{
	
	Sprite::Initialise(text, FOREGROUND_WHITE, size);

	m_SELECTOR_L.Initialise(
		"######"
		"##    "
		"##    "
		"##    "
		"##    "
		"##    "
		"######"
		, FOREGROUND_WHITE, Vector2(6, 7));

	m_SELECTOR_R.Initialise(
		"######"
		"    ##"
		"    ##"
		"    ##"
		"    ##"
		"    ##"
		"######"
		, FOREGROUND_WHITE, Vector2(6, 7));

	SetPos(Vector2(10, 10));

	m_initialized = true;
}




void MenuItem::Update()
{
}


//Dispays the menu item on the screen
void MenuItem::Render(ASCIIRenderer * pRenderer)
{
	Sprite::Render(pRenderer);
	if (m_highlighted)
	{
		m_SELECTOR_L.Render(pRenderer);
		m_SELECTOR_R.Render(pRenderer);
	}
}

//returns the idetifing string that was soecialised when the item was created
char* MenuItem::GetId() const
{
	return m_id;
}


//updates the position of the menu item woth the new pos and the position of the hilighter '[]'s
void MenuItem::SetPos(Vector2 & position)
{
	m_SELECTOR_L.SetPosition(position);
	Sprite::SetPosition(position + Vector2(m_SELECTOR_L.GetSize().x + 1, 0));
	m_SELECTOR_R.SetPosition(Sprite::GetPosition() + Vector2(Sprite::GetSize().x + 1, 0));
}


//hilights the menu itsm (by)
// adding [...] arount it
void MenuItem::Select()
{
	m_highlighted = true;
}

//UnHighlights the item
void MenuItem::Deselect()
{
	m_highlighted = false;
}

void MenuItem::InitializeMemberVars()
{
	m_initialized = false;
	//m_text = "";
	m_highlighted = false;
	m_id = "";

	
}
