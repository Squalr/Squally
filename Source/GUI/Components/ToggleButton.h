#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Components/Mouse.h"
#include "GUI/Components/MenuSprite.h"

using namespace cocos2d;

class ToggleButton : public Node
{
public:
	static ToggleButton * create(bool initialState, std::function<void(bool)> callback);

protected:
	ToggleButton(bool initialState, std::function<void(bool)> callback);
	~ToggleButton();

private:
	void InitializeListeners();
	void OnToggleClick(MenuSprite* menuSprite);
	void OnMouseMove(EventMouse* event);

	MenuSprite* onSwitch;
	MenuSprite* offSwitch;

	bool isToggled;
	std::function<void(bool)> toggleCallback;
	std::vector<MenuSprite*>* clickableMenus;
};

