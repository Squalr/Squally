#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "MiniGames/Hexium/Components/Components.h"
#include "MiniGames/Hexium/GameState.h"
#include "MiniGames/Hexium/Ai.h"
#include "GUI/Components/FadeScene.h"
#include "GUI/Components/MenuSprite.h"
#include "Utils/StrUtils.h"

using namespace cocos2d;

class Hexium : public FadeScene
{
public:
	static Hexium * create();

	static const std::string HexiumGameStartEvent;
	static const std::string HexiumGameEndEvent;

	struct HexiumGameEventArgs
	{
		Deck* playerDeck;
		Deck* enemyDeck;

		HexiumGameEventArgs(Deck* playerDeck, Deck* enemyDeck) : playerDeck(playerDeck), enemyDeck(enemyDeck)
		{
		}
	};

	// Make this event public. Note that Game.h fires this event because this scene can't listen for events until it is created.
	void onGameStart(EventCustom* eventCustom);

private:
	Hexium();
	~Hexium();

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
	DeckCardCountDisplay* deckCardCountDisplay;
	HandCardCountDisplay* handCardCountDisplay;
	LossesDisplay* lossesDisplay;
	RowTotals* rowTotals;
	ScoreTotal* scoreTotal;
};
