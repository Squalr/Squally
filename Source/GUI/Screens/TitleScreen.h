#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/MenuLabel.h"
#include "GUI/Mouse.h"

using namespace cocos2d;

class TitleScreen : public Scene
{
public:
	TitleScreen(std::function<void()> gameStartCallback);
	~TitleScreen();

private:
	void InitializeListeners();
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void OnMouseMove(EventMouse* event);

	Mouse* mouse;
	function<void()> theGameStartCallback;
	Sprite* background;

	MenuLabel* titleLabel;
	MenuLabel* storyModeLabel;
	MenuLabel* tutorialModeLabel;
	MenuLabel* optionsLabel;
	MenuLabel* exitLabel;
};

