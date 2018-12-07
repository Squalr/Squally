#pragma once
#include "cocos2d.h"

#include "Events/NavigationEvents.h"
#include "Engine/SmartScene.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/FloatingSprite.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Menus/Minigames/Hexus/Puzzles/HexusPuzzleItem.h"
#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

class HexusPuzzlesMenu : public SmartScene
{
public:
	static HexusPuzzlesMenu * create();

protected:
	HexusPuzzlesMenu();
	~HexusPuzzlesMenu();

private:
	void loadLevels();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onCloseClick(MenuSprite* menuSprite);
	void onMouseOver(HexusPuzzleItem* tutorialItem);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	int currentPage;

	Sprite* tutorialWindow;
	Label* titleLabel;
	Sprite* descriptionBox;
	Label* description;
	MenuSprite* closeButton;

	ParticleSystem* nether;
	ParticleSystem* swirl;

	std::vector<HexusPuzzleItem*>* hexusOpponentItems;

	static const Color3B TitleColor;
	static const std::string StringKeyHexusPuzzles;
};

