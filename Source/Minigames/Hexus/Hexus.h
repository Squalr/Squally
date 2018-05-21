#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "MiniGames/Hexus/Components/Components.h"
#include "MiniGames/Hexus/GameState.h"
#include "GUI/Components/FadeScene.h"
#include "GUI/Components/MenuSprite.h"
#include "Events/NavigationEvents.h"
#include "Events/HexusEvents.h"
#include "Utils/StrUtils.h"

using namespace cocos2d;

class Hexus : public FadeScene
{
public:
	static Hexus * create();

	// Make this event public. Note that Game.h fires this event because this scene can't listen for events until it is created.
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
