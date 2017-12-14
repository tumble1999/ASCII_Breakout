#ifndef _MENU_ITEM_H_
#define _MENU_ITEM_H_

#include <string>
#include <functional>

#include "../GameObjects/GameObject.h"

/* The selector
###### ######
##         ##
##         ##
##         ##
##         ##
##         ##
###### ######
*/

class MenuItem: public GameObject
{
public:
	MenuItem();
	MenuItem(char* text, Vector2 size, char* id);
	virtual ~MenuItem();

	void Initialize(char* text, Vector2 size);
	void Update();
	void Render(ASCIIRenderer* pRenderer);

	char* GetId() const;

	void Select();
	void Deselect();

	void SetPos(Vector2& position);

private:
	char* m_id;
	//std::string m_text;

	Sprite m_SELECTOR_L;
	Sprite m_SELECTOR_R;

	bool m_highlighted;

	void InitializeMemberVars();

	bool m_initialized;
};

#endif // !_MENU_ITEM_H_
