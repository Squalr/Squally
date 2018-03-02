#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "MiniGames/Hexium/Card.h"
#include "MiniGames/Hexium/Deck.h"
#include "MiniGames/Hexium/Hand.h"
#include "GUI/Components/FadeScene.h"
#include "GUI/Components/MenuSprite.h"

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

	enum Turn {
		Player,
		Enemy,
	};

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onClose(MenuSprite* menuSprite);
	void gameStart();
	void randomizeTurn();
	void drawCard();
	void yieldControl();
	void endTurn();

	// Game state
	bool allowControl;
	Turn turn;
	int playerLosses;
	int enemyLosses;

	// Images
	Sprite* emblem;

	Sprite* playerFrame;
	Sprite* playerSocketA;
	Sprite* playerSocketB;
	Sprite* playerSkullA;
	Sprite* playerSkullB;
	Sprite* playerPadDeck;
	Sprite* playerPadGrave;

	Sprite* enemyFrame;
	Sprite* enemySocketA;
	Sprite* enemySocketB;
	Sprite* enemySkullA;
	Sprite* enemySkullB;
	Sprite* enemyPadDeck;
	Sprite* enemyPadGrave;

	Deck* playerDeck;
	Hand* playerHand;
	Deck* playerGraveyard;
	Deck* enemyDeck;
	Hand* enemyHand;
	Deck* enemyGraveyard;

	LayerColor* playerDeckCardCountFrame;
	Label* playerDeckCardCountText;
	LayerColor* enemyDeckCardCountFrame;
	Label* enemyDeckCardCountText;
	LayerColor* playerHandCardCountFrame;
	Label* playerHandCardCountText;
	LayerColor* enemyHandCardCountFrame;
	Label* enemyHandCardCountText;

	Sprite* gameBackground;
};

