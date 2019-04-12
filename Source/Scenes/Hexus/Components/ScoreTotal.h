#pragma once

#include "Scenes/Hexus/Components/ComponentBase.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;

class ScoreTotal : public ComponentBase
{
public:
	static ScoreTotal* create();

protected:
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef ComponentBase super;
	ScoreTotal();
	~ScoreTotal();

	void onEnter() override;
	void initializePositions() override;
	void updateTotals(GameState* gameState);

	cocos2d::Sprite* playerTotalFrame;
	LocalizedLabel* playerTotal;
	cocos2d::Sprite* playerLeaderEmblem;

	cocos2d::Sprite* enemyTotalFrame;
	LocalizedLabel* enemyTotal;
	cocos2d::Sprite* enemyLeaderEmblem;
};
