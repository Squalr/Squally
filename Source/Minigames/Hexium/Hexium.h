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
		int temp;

		HexiumGameEventArgs(int temp) : temp(temp)
		{
		}
	};

	void startGame(Deck* playerDeckStart, Deck* enemyDeckStart);

private:
	Hexium();
	~Hexium();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onClose(MenuSprite* menuSprite);

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

	Sprite* gameBackground;
};

