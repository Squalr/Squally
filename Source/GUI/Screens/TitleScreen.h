#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "StoryMap.h"
#include "TutorialMap.h"
#include "Utils/Utils.h"
#include "Utils/InfiniteParallaxNode.h"
#include "GUI/Menus/OptionsMenu.h"
#include "GUI/MenuLabel.h"
#include "GUI/MenuSprite.h"
#include "GUI/Mouse.h"
#include "audio/include/SimpleAudioEngine.h"
#include <algorithm>
#include <string>

using namespace cocos2d;
using namespace CocosDenshion;

class TitleScreen : public Scene
{
public:
	TitleScreen();
	~TitleScreen();

private:
	void onEnter() override;
	void update(float) override;
	void InitializeListeners();
	void InitializeMovement();
	void OnTutorialClick(MenuSprite* menuSprite);
	void OnMenuClick(MenuLabel* menuLabel);
	void OnMouseMove(EventMouse* event);

	Mouse* mouse;
	Sprite* squally;
	Sprite* background;
	Sprite* backgroundVines;
	Sprite* backgroundTrees;
	Sprite* midgroundTrees;
	Sprite* tree;
	Sprite* foregroundVines;
	InfiniteParallaxNode* fog;
	Sprite* foregroundGrassBottom;
	Sprite* foregroundGrassTop;
	Sprite* foregroundLight;
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

