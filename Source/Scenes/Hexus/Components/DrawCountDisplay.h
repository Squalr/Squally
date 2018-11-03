#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Sound/SoundManager.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/ComponentBase.h"

using namespace cocos2d;

class DrawCountDisplay : public ComponentBase
{
public:
	static DrawCountDisplay * create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onStateChange(GameState* eventCustom) override;

private:
	DrawCountDisplay();
	~DrawCountDisplay();

	void initializePositions() override;

	Sprite* drawCountSprite;
	Label* drawCountLabel;

	Sprite* enemyDrawCountSprite;
	Label* enemyDrawCountLabel;
};
