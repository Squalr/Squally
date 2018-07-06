#pragma once
#include "cocos2d.h"

#include "Engine/Rendering/Components/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"

#include "ComponentBase.h"

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
	void updateBanner();

	int replaceCount;
	std::set<Card*>* replacedCards;
	LayerColor* bannerBackground;
	Label* bannerLabel;
	GameState* activeGameState;
};
