#pragma once
#include "cocos2d.h"
#include "Resources.h"
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
	void previewCard(Card* card);
	void doCoinFlipAnimation();
	void displayTurnBanner();
	void updateDisplayState(bool prePlayerDraw);
	void displayStatusBannerMessage(std::string message);

	GameState* gameState;

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

	LayerColor* playerDeckCardCountFrame;
	Label* playerDeckCardCountText;
	LayerColor* playerHandCardCountFrame;
	Label* playerHandCardCountText;
	Sprite* playerHandCardIcon;

	LayerColor* enemyDeckCardCountFrame;
	Label* enemyDeckCardCountText;
	LayerColor* enemyHandCardCountFrame;
	Label* enemyHandCardCountText;
	Sprite* enemyHandCardIcon;

	Label* enemyBinaryCardTotal;
	Label* enemyDecimalCardTotal;
	Label* enemyHexCardTotal;
	Label* playerBinaryCardTotal;
	Label* playerDecimalCardTotal;
	Label* playerHexCardTotal;

	Sprite* playerTotalFrame;
	Label* playerTotal;
	Sprite* playerLeaderEmblem;

	Sprite* enemyTotalFrame;
	Label* enemyTotal;
	Sprite* enemyLeaderEmblem;

	Card* currentPreviewCard;
	Node* previewPanel;

	Sprite* coin;
	Animation* skeletonInAnimation;
	Animation* skeletonOutAnimation;
	Animation* lionInAnimation;
	Animation* lionOutAnimation;
	Animation* neutralAnimation;

	LayerColor* statusBanner;
	Label* statusLabel;

	Sprite* gameBackground;
};
