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

	///////////////

	void gameStart(Deck* startPlayerDeck, Deck* startEnemyDeck);
	void drawCard();
	void giveControl();
	void endTurn();
	void cancelCurrentAction(bool clearSelectedCard);
	void setCardPreviewCallback(std::function<void(Card*)> callback);
	void setUpdateStateCallback(std::function<void(bool)> callback);
	void setEndTurnCallback(std::function<void()> callback);
	void setRequestAiCallback(std::function<void(GameState*)> callback);

private:
	Hexium();
	~Hexium();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onClose(MenuSprite* menuSprite);

	/////////////////////

	void onCardMouseOver(Card* card);
	void onHandCardClick(Card* card);
	void onRowCardClick(Card* card);

	void updateState();
	void callEndTurn();
	void playSelectedCard(CardRow* cardRow);
	void stageSelectedSacrificeCard(Card* card);
	void selectCard(Card* card);
	void enableUserInteraction();
	void disableUserInteraction();

	///////////

	GameState* gameState;
	Sprite* gameBackground;

	// Components
	Avatars* avatars;
	Banners* banners;
	CardPreview* cardPreview;
	CoinFlip* coinFlip;
	ControlDraw* controlDraw;
	DeckCardCountDisplay* deckCardCountDisplay;
	HandCardCountDisplay* handCardCountDisplay;
	LossesDisplay* lossesDisplay;
	RowTotals* rowTotals;
	ScoreTotal* scoreTotal;
};
