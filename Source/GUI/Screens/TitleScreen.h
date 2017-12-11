#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "StoryMap.h"
#include "TutorialMap.h"
#include "GUI/Menus/OptionsMenu.h"
#include "GUI/MenuLabel.h"
#include "GUI/Mouse.h"

using namespace cocos2d;

class TitleScreen : public Scene
{
public:
	TitleScreen();
	~TitleScreen();

private:
	void OnMenuClick(MenuLabel* menuLabel);

	void InitializeListeners();
	void OnMouseMove(EventMouse* event);

	Mouse* mouse;
	Sprite* background;

	MenuLabel* titleLabel;
	MenuLabel* storyModeLabel;
	MenuLabel* tutorialModeLabel;
	MenuLabel* optionsLabel;
	MenuLabel* exitLabel;

	std::vector<MenuLabel*>* clickableMenus;

	const float titleFontSize = 48.0f;
	const float menuFontSize = 32.0f;
	const float menuOffset = 64.0f;
	const float spacing = -40.0f;
};

