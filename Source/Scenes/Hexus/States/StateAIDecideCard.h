#pragma once
#include "cocos2d.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"

#include "Scenes/Hexus/States/HexusAIHelper.h"
#include "Scenes/Hexus/States/StateBase.h"

using namespace cocos2d;

class StateAIDecideCard : public StateBase
{
public:
	static StateAIDecideCard * create();

protected:
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	StateAIDecideCard();
	~StateAIDecideCard();

	void decideCardRandom(GameState* gameState);
	void decideCardStrongestFirst(GameState* gameState);
	void decideCardWeakestFirst(GameState* gameState);
};
