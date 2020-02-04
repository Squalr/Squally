#pragma once

#include "Scenes/Hexus/Components/ComponentBase.h"

namespace cocos2d
{
	class Sprite;
}

class ConstantString;
class LocalizedLabel;

class ScoreTotal : public ComponentBase
{
public:
	static ScoreTotal* create();

protected:
	ScoreTotal();
	virtual ~ScoreTotal();

	void onEnter() override;
	void initializePositions() override;
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef ComponentBase super;
	void updateTotals(GameState* gameState);

	cocos2d::Sprite* playerTotalFrame;
	ConstantString* playerTotalStr;
	LocalizedLabel* playerTotalLabel;
	cocos2d::Sprite* playerLeaderEmblem;

	cocos2d::Sprite* enemyTotalFrame;
	ConstantString* enemyTotalStr;
	LocalizedLabel* enemyTotalLabel;
	cocos2d::Sprite* enemyLeaderEmblem;
};
