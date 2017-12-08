#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class TitleScreen : public Scene
{
public:
	TitleScreen(std::function<void()> gameStartCallback);
	~TitleScreen();

private:
	void InitializeListeners();
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
};

