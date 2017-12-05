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
	
	Sprite::Initialise(text, FOREGROUND_WHITE, size);
	SetPosition(Vector2(10, 10));

	m_SELECTOR_L.Initialise(
		"######"
		"##    "
		"##    "
		"##    "
		"##    "
		"##    "
		"######"
		,FOREGROUND_WHITE , Vector2(6, 7));

		m_SELECTOR_R.Initialise(
			"######"
			"    ##"
			"    ##"
			"    ##"
			"    ##"
			"    ##"
			"######"
			, FOREGROUND_WHITE, Vector2(6, 7));

	m_initialized = true;
}

void MenuItem::SetPos(Vector2 & position)
{
	Sprite::SetPosition(position);

	m_SELECTOR_L.SetPosition(Sprite::GetPosition() - Vector2(m_SELECTOR_L.GetPosition().x + 1, 0));
	m_SELECTOR_R.SetPosition(Sprite::GetPosition() + Vector2(Sprite::GetSize().x + m_SELECTOR_L.GetPosition().x + 1, 0));




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
