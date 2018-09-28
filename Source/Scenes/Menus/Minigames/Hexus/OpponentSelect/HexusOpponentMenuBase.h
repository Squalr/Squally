#pragma once
#include "cocos2d.h"

#include "Events/NavigationEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/UI/FadeScene.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponents.h"
#include "Scenes/Menus/Minigames/Hexus/OpponentSelect/HexusOpponentPreview.h"

using namespace cocos2d;

class HexusOpponentMenuBase : public FadeScene
{
protected:
	HexusOpponentMenuBase(std::string progressSaveStringKey);
	~HexusOpponentMenuBase();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void loadProgress();
	void onCloseClick(MenuSprite* menuSprite);
	void onDeckManagementClick(MenuSprite* menuSprite);
	void onMouseOver(HexusOpponentPreview* opponent);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onGameEndCallback(HexusEvents::HexusGameResultEventArgs args);

	ScrollPane* scrollPane;
	std::vector<HexusOpponentPreview*> opponents;

	std::string progressSaveStringKey;
	Sprite* background;
	TextMenuSprite* deckManagementButton;
	Label* opponentSelectLabel;
};

