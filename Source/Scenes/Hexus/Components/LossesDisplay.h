#pragma once

#include "Scenes/Hexus/Components/ComponentBase.h"

namespace cocos2d
{
	class Sprite;
}

class LossesDisplay : public ComponentBase
{
public:
	static LossesDisplay* create();
protected:
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef ComponentBase super;
	LossesDisplay();
	~LossesDisplay();

	void onEnter() override;
	void initializePositions() override;
	void updateDisplayedLosses(GameState* gameState);

	cocos2d::Sprite* playerSocketA;
	cocos2d::Sprite* playerSocketB;
	cocos2d::Sprite* playerSkullA;
	cocos2d::Sprite* playerSkullB;
	cocos2d::Sprite* enemySocketA;
	cocos2d::Sprite* enemySocketB;
	cocos2d::Sprite* enemySkullA;
	cocos2d::Sprite* enemySkullB;
};
