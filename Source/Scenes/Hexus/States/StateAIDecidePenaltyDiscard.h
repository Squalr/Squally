#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/States/StateBase.h"

using namespace cocos2d;

class StateAIDecidePenaltyDiscard : public StateBase
{
public:
	static StateAIDecidePenaltyDiscard * create();

protected:
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	StateAIDecidePenaltyDiscard();
	~StateAIDecidePenaltyDiscard();

	void replaceCard(Card* card, GameState* gameState);

	std::vector<Card*> removedCards;
};
