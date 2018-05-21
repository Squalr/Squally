#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "MiniGames/Hexus/Components/ComponentBase.h"
#include "GUI/Components/MenuSprite.h"
#include "Utils/StrUtils.h"

using namespace cocos2d;

class LossesDisplay : public ComponentBase
{
public:
	static LossesDisplay* create();
protected:
	void onStateChange(GameState* eventCustom) override;

private:
	LossesDisplay();
	~LossesDisplay();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void updateDisplayedLosses(GameState* gameState);

	Sprite* playerSocketA;
	Sprite* playerSocketB;
	Sprite* playerSkullA;
	Sprite* playerSkullB;
	Sprite* enemySocketA;
	Sprite* enemySocketB;
	Sprite* enemySkullA;
	Sprite* enemySkullB;
};
