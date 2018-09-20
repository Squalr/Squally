#pragma once
#include "cocos2d.h"

#include "Events/NavigationEvents.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/UI/FadeScene.h"
#include "Engine/UI/FloatingSprite.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponents.h"
#include "Scenes/Menus/Minigames/Hexus/HexusOpponentFrame.h"

using namespace cocos2d;

class HexusMenu : public FadeScene
{
public:
	static HexusMenu * create();

protected:
	HexusMenu();
	~HexusMenu();

private:
	void loadOpponents();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onCloseClick(MenuSprite* menuSprite);
	void onMouseOver(HexusOpponentFrame* tutorialItem);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	ScrollPane* scrollPane;

	ParticleSystem* nether;
	ParticleSystem* swirl;

	std::vector<HexusOpponentFrame*>* hexusOpponents;
};

