#pragma once
#include <algorithm>
#include <string>

#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/Sound/SoundManager.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/UI/Mouse.h"
#include "Engine/UI/HUD/Hud.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/NavigationEvents.h"

using namespace cocos2d;

class MinigamesMenu : public Hud
{
public:
	static MinigamesMenu * create();

protected:
	MinigamesMenu();
	~MinigamesMenu();

private:
	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onBackClick(MenuSprite* menuSprite);
	void onHexusClick(MenuSprite* menuSprite);
	void onHexusPuzzlesClick(MenuSprite* menuSprite);
	TextMenuSprite* createComingSoonButton();

	ScrollPane* scrollPane;
	TextMenuSprite* hexusButton;
	TextMenuSprite* hexusPuzzlesButton;
	TextMenuSprite* comingSoonButton1;
	TextMenuSprite* comingSoonButton2;
	TextMenuSprite* comingSoonButton3;
	TextMenuSprite* comingSoonButton4;
	TextMenuSprite* comingSoonButton5;
	TextMenuSprite* comingSoonButton6;
	TextMenuSprite* backButton;

	static const std::string StringKeyHexus;
	static const std::string StringKeyHexusPuzzles;
	static const std::string StringKeyComingSoon;

	static const float titleFontSize;
	static const float menuFontSize;
	static const float menuOffset;
	static const float spacing;
};

