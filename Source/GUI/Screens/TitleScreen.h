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
	void OnMenuClick(MenuLabel* menuLabel);

	void InitializeListeners();
	void OnMouseMove(EventMouse* event);

	Mouse* mouse;
	function<void()> theGameStartCallback;
	Sprite* background;

	MenuLabel* titleLabel;
	MenuLabel* storyModeLabel;
	MenuLabel* tutorialModeLabel;
	MenuLabel* optionsLabel;
	MenuLabel* exitLabel;

	std::vector<MenuLabel*>* clickableMenus;
};

