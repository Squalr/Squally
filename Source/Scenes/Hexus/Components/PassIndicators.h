#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/ComponentBase.h"

using namespace cocos2d;

class PassIndicators : public ComponentBase
{
public:
	static PassIndicators * create();

protected:
	void onBeforeStateChange(GameState* gameState) override;
	void onStateChange(GameState* gameState) override;

private:
	PassIndicators();
	~PassIndicators();

	void initializePositions() override;

	Sprite* playerPassIndicator;
	Sprite* enemyPassIndicator;
};
