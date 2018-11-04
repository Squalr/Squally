#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Sound/SoundManager.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/ComponentBase.h"

using namespace cocos2d;

class ScoreTotal : public ComponentBase
{
public:
	static ScoreTotal * create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	ScoreTotal();
	~ScoreTotal();

	void initializePositions() override;
	void updateTotals(GameState* gameState);

	Sprite* playerTotalFrame;
	Label* playerTotal;
	Sprite* playerLeaderEmblem;

	Sprite* enemyTotalFrame;
	Label* enemyTotal;
	Sprite* enemyLeaderEmblem;
};
