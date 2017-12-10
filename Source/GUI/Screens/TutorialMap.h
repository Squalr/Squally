#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class TutorialMap : public Scene
{
public:
	TutorialMap();
	~TutorialMap();

private:
	void InitializeListeners();
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
};

