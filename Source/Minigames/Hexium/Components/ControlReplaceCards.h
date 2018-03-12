#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "MiniGames/Hexium/Components/ComponentBase.h"
#include "GUI/Components/MenuSprite.h"
#include "Utils/StrUtils.h"

using namespace cocos2d;

class ControlReplaceCards : public ComponentBase
{
public:
	static ControlReplaceCards * create();

protected:
	void onStateChange(GameState* gameState) override;

private:
	ControlReplaceCards();
	~ControlReplaceCards();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void initializeCardReplace(GameState* gameState);
	void initializeCallbacks(GameState* gameState);
	void replaceCard(Card* card);

	int replaceCount;
	std::set<Card*>* replacedCards;
	LayerColor* bannerBackground;
	Label* bannerLabel;
	GameState* activeGameState;
};
