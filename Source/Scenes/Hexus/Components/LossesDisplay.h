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
	LossesDisplay();
	virtual ~LossesDisplay();

	void onEnter() override;
	void initializePositions() override;
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef ComponentBase super;

	void updateDisplayedLosses(GameState* gameState);

	cocos2d::Sprite* playerSocketA = nullptr;
	cocos2d::Sprite* playerSocketB = nullptr;
	cocos2d::Sprite* playerSkullA = nullptr;
	cocos2d::Sprite* playerSkullB = nullptr;
	cocos2d::Sprite* enemySocketA = nullptr;
	cocos2d::Sprite* enemySocketB = nullptr;
	cocos2d::Sprite* enemySkullA = nullptr;
	cocos2d::Sprite* enemySkullB = nullptr;
};
