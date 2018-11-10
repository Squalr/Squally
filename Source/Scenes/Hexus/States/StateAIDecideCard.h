#pragma once
#include "cocos2d.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
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

	int getBaseCardsInHandCount(GameState* gameState);
	int getPlayerHandCount(GameState* gameState);
	int getEnemyHandCount(GameState* gameState);
	int getPlayerCardsOnFieldCount(GameState* gameState);
	int getEnemyCardsOnFieldCount(GameState* gameState);
	int getCardsStrongerThanAttackCount(CardRow* row, int attack);
	int getCardsWeakerThanAttackCount(CardRow* row, int attack);
	unsigned int getStrongestEnemyCardOnField(GameState* gameState);
	unsigned int getWeakestEnemyCardOnField(GameState* gameState);
	unsigned int getStrongestPlayerCardOnField(GameState* gameState);
	unsigned int getWeakestPlayerCardOnField(GameState* gameState);
};
