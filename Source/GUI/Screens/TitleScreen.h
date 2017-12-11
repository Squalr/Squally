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
	void onEnter() override;
	void InitializeListeners();
	void OnMenuClick(MenuLabel* menuLabel);
	void OnMouseMove(EventMouse* event);

	Mouse* mouse;
	Sprite* background;

	MenuLabel* titleLabel;
	MenuLabel* storyModeLabel;
	MenuLabel* tutorialModeLabel;
	MenuLabel* optionsLabel;
	MenuLabel* exitLabel;

	std::vector<MenuLabel*>* clickableMenus;

	const float titleFontSize = 64.0f;
	const float menuFontSize = 48.0f;
	const float menuOffset = 128.0f;
	const float spacing = -96.0f;
};

