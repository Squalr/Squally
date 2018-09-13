#pragma once
#include "cocos2d.h"

#include "Events/NavigationEvents.h"
#include "Engine/Rendering/Components/FadeScene.h"
#include "Engine/Rendering/Components/FloatingSprite.h"
#include "Engine/Rendering/Components/MenuSprite.h"
#include "Engine/Rendering/Components/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"

#include "HexusPuzzlesMenu.h"
#include "HexusOpponentItem.h"

using namespace cocos2d;

class HexusPuzzlesMenu : public FadeScene
{
public:
	static HexusPuzzlesMenu * create();

protected:
	HexusPuzzlesMenu();
	~HexusPuzzlesMenu();

private:
	void loadLevels();
	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void onCloseClick(MenuSprite* menuSprite);
	void onMouseOver(HexusOpponentItem* tutorialItem);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	int currentPage;

	Sprite* tutorialWindow;
	Label* titleLabel;
	Sprite* descriptionBox;
	Label* description;
	MenuSprite* closeButton;

	ParticleSystem* nether;
	ParticleSystem* swirl;

	std::vector<HexusOpponentItem*>* hexusOpponentItems;

	static const Color3B TitleColor;
	static const std::string StringKeyHexusPuzzles;
};

