#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "StoryMap.h"
#include "TutorialMap.h"
#include "Utils/Utils.h"
#include "GUI/Menus/OptionsMenu.h"
#include "GUI/MenuLabel.h"
#include "GUI/MenuSprite.h"
#include "GUI/Mouse.h"

using namespace cocos2d;

class TitleScreen : public Scene
{
public:
	TitleScreen();
	~TitleScreen();

private:
	void onEnter() override;
	void update(float) override;
	void InitializeListeners();
	void OnTutorialClick(MenuSprite* menuSprite);
	void OnMenuClick(MenuLabel* menuLabel);
	void OnMouseMove(EventMouse* event);

	Mouse* mouse;
	Sprite* background;
	MenuSprite* monitor;

	Label* hackerModeLabel;

	MenuLabel* titleLabel;
	MenuLabel* storyModeLabel;
	MenuLabel* optionsLabel;
	MenuLabel* exitLabel;

	std::vector<MenuLabel*>* clickableMenus;

	static int hackerMode;

	const float titleFontSize = 64.0f;
	const float menuFontSize = 48.0f;
	const float menuOffset = 128.0f;
	const float spacing = -96.0f;
};

