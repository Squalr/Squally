#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class StoryMap : public Scene
{
public:
	StoryMap();
	~StoryMap();

private:
	void InitializeListeners();
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
};

