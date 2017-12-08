#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class PauseMenu : public Scene
{
public:
	PauseMenu();
	~PauseMenu();

private:
	void InitializeListeners();
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void OnExitGame(Ref* pSender);
};

