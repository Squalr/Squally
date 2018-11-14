#pragma once
#include "cocos2d.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/ComponentBase.h"

using namespace cocos2d;

class LossesDisplay : public ComponentBase
{
public:
	static LossesDisplay* create();
protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	LossesDisplay();
	~LossesDisplay();

	void onEnter() override;
	void initializePositions() override;
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
