#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "MiniGames/Hexus/Components/ComponentBase.h"
#include "GUI/Components/MenuSprite.h"
#include "Utils/StrUtils.h"

using namespace cocos2d;

class HandCardCountDisplay : public ComponentBase
{
public:
	static HandCardCountDisplay * create();

protected:
	void onStateChange(GameState* eventCustom) override;

private:
	HandCardCountDisplay();
	~HandCardCountDisplay();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void updateTotals(GameState* gameState);

	LayerColor* playerHandCardCountFrame;
	Label* playerHandCardCountText;
	Sprite* playerHandCardIcon;

	LayerColor* enemyHandCardCountFrame;
	Label* enemyHandCardCountText;
	Sprite* enemyHandCardIcon;
};
