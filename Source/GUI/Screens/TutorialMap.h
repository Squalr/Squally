#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Mouse.h"
#include "GUI/MenuLabel.h"

using namespace cocos2d;

class TutorialMap : public Scene
{
public:
	TutorialMap();
	~TutorialMap();

private:
	void InitializeListeners();
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	Mouse* mouse;

	Sprite* background;
	MenuLabel* titleLabel;
	MenuLabel* infoLabel;

	const float titleFontSize = 48.0f;
	const float infoFontSize = 32.0f;
};

