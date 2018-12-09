#pragma once
#include <functional>
#include <vector>

#include "Engine/SmartNode.h"

class MenuSprite;

class CCheckbox : public SmartNode
{
public:
	static CCheckbox * create(MenuSprite* uncheckedButton, MenuSprite* checkedButton, bool initialState,
			std::function<bool(CCheckbox*, bool)> callback = nullptr);

	void setCallback(std::function<bool(CCheckbox*, bool)> callback);
	void setToggled(bool isToggled);
	bool getToggled();

protected:
	CCheckbox(MenuSprite* uncheckedButton, MenuSprite* checkedButton, bool initialState,
			std::function<bool(CCheckbox*, bool)> callback);
	virtual ~CCheckbox();

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

