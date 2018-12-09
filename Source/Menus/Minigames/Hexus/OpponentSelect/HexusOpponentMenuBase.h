#pragma once
#include "cocos2d.h"

#include "Analytics/AnalyticsCategories.h"
#include "Engine/Analytics/Analytics.h"
#include "Engine/GlobalScene.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/NavigationEvents.h"
#include "Menus/Minigames/Hexus/OpponentSelect/HexusOpponentPreview.h"

using namespace cocos2d;

class HexusOpponentMenuBase : public GlobalScene
{
protected:
	HexusOpponentMenuBase(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter chapter, std::string chapterProgressSaveKey);
	~HexusOpponentMenuBase();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void loadProgress();
	void onBackClick(MenuSprite* menuSprite);
	void onDeckManagementClick(MenuSprite* menuSprite);
	void onShopClick(MenuSprite* menuSprite);
	void onMouseOver(HexusOpponentPreview* opponent);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter chapter;

	ScrollPane* scrollPane;
	std::vector<HexusOpponentPreview*> opponents;
	std::map<HexusOpponentPreview*, HexusOpponentPreview*> dependencies;

	std::string chapterProgressSaveKey;
	Sprite* background;
	TextMenuSprite* deckManagementButton;
	TextMenuSprite* shopButton;
	Label* opponentSelectLabel;
	TextMenuSprite* backButton;
};

