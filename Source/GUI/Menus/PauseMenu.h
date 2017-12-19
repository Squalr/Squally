#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class PauseMenu : public Scene
{
public:
	static PauseMenu * create();

protected:
	PauseMenu();
	~PauseMenu();

private:
	void onEnter() override;
	void InitializeListeners();
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void OnExitGame(Ref* pSender);

	MenuItemImage* closeItem;
};

