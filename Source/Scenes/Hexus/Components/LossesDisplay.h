#pragma once
#include "cocos2d.h"

#include "Engine/Rendering/Components/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"

#include "ComponentBase.h"

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
