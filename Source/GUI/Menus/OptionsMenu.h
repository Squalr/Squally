#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class OptionsMenu : public Scene
{
public:
	OptionsMenu();
	~OptionsMenu();

	void onEnter() override;

private:
	void InitializeListeners();
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void OnExitGame(Ref* pSender);

	MenuItemImage* closeItem;
};

