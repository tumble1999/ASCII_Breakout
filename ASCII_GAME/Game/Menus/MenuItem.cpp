#include "MenuItem.h"



MenuItem::MenuItem()
{
	InitializeMemberVars();
}

MenuItem::MenuItem(char* text, Vector2 size)
{
	InitializeMemberVars();
	m_id = id;
	Initialize(text, size);
}

MenuItem::~MenuItem()
{
}

void MenuItem::Initialize(char* text, Vector2 size, std::string id)
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

void MenuItem::Render(ASCIIRenderer * pRenderer)
{
	Sprite::Render(pRenderer);
	if (m_highlighted)
	{
		m_SELECTOR_L.Render(pRenderer);
		m_SELECTOR_R.Render(pRenderer);
	}
}



void MenuItem::SetPos(Vector2 & position)
{
	m_SELECTOR_L.SetPosition(position);
	Sprite::SetPosition(position + Vector2(m_SELECTOR_L.GetSize().x + 1, 0));
	m_SELECTOR_R.SetPosition(Sprite::GetPosition() + Vector2(Sprite::GetSize().x + 1, 0));
}

void MenuItem::Select()
{
	m_highlighted = true;
}

void MenuItem::Deselect()
{
	m_highlighted = false;
}

void MenuItem::InitializeMemberVars()
{
	m_initialized = false;
	m_text = "";
	m_highlighted = false;

	
}
