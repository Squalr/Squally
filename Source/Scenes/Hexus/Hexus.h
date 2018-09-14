#pragma once
#include "cocos2d.h"
#include "Resources.h"

#include "Events/NavigationEvents.h"
#include "Events/HexusEvents.h"
#include "Engine/Rendering/Components/FadeScene.h"
#include "Engine/Rendering/Components/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"

#include "Components/Components.h"
#include "GameState.h"

using namespace cocos2d;

class Hexus : public FadeScene
{
public:
	static Hexus * create();

	void onGameStart(EventCustom* eventCustom);

private:
	Hexus();
	~Hexus();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onClose(MenuSprite* menuSprite);

	GameState* gameState;
	Sprite* gameBackground;

	// Components
	Avatars* avatars;
	Banners* banners;
	CardPreview* cardPreview;
	CoinFlip* coinFlip;
	ControlDraw* controlDraw;
	ControlNeutral* controlNeutral;
	ControlEndTurn* controlEndTurn;
	ControlSacrificeStaged* controlSacrificeStaged;
	ControlSelectionStaged* controlSelectionStaged;
	ControlReplaceCards* controlReplaceCards;
	DeckCardCountDisplay* deckCardCountDisplay;
	HandCardCountDisplay* handCardCountDisplay;
	LossesDisplay* lossesDisplay;
	RowTotals* rowTotals;
	ScoreTotal* scoreTotal;
};
