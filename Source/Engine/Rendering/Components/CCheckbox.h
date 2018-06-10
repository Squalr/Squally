#pragma once
#include "cocos2d.h"

#include "Resources.h"

#include "Mouse.h"
#include "MenuSprite.h"

using namespace cocos2d;

class CCheckbox : public Node
{
public:
	static CCheckbox * create(MenuSprite* uncheckedButton, MenuSprite* checkedButton, bool initialState, std::function<bool(CCheckbox*, bool)> callback);

protected:
	CCheckbox(MenuSprite* uncheckedButton, MenuSprite* checkedButton, bool initialState, std::function<bool(CCheckbox*, bool)> callback);
	~CCheckbox();

private:
	void initializeListeners();
	void onToggleClick(MenuSprite* menuSprite);
	void onMouseMove(EventMouse* event);

	MenuSprite* onSwitch;
	MenuSprite* offSwitch;

	bool isToggled;
	std::function<bool(CCheckbox*, bool)> toggleCallback;
	std::vector<MenuSprite*>* clickableMenus;
};

