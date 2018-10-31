#pragma once
#include "cocos2d.h"

#include "Engine/SmartNode.h"
#include "Engine/UI/Mouse.h"
#include "Engine/UI/Controls/MenuSprite.h"

using namespace cocos2d;

class CCheckbox : public SmartNode
{
public:
	static CCheckbox * create(MenuSprite* uncheckedButton, MenuSprite* checkedButton, bool initialState, std::function<bool(CCheckbox*, bool)> callback = nullptr);

	void setCallback(std::function<bool(CCheckbox*, bool)> callback);
	void setToggled(bool isToggled);
	bool getToggled();

protected:
	CCheckbox(MenuSprite* uncheckedButton, MenuSprite* checkedButton, bool initialState, std::function<bool(CCheckbox*, bool)> callback);
	~CCheckbox();

private:
	void onToggle();
	void onUntoggle();
	void updateVisuals();

	MenuSprite* onSwitch;
	MenuSprite* offSwitch;

	bool isToggled;
	std::function<bool(CCheckbox*, bool)> toggleCallback;
	std::vector<MenuSprite*>* clickableMenus;
};

