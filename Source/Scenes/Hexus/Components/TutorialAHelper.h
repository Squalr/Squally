#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/FocusTakeOver.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/ComponentBase.h"

using namespace cocos2d;

class TutorialAHelper : public ComponentBase
{
public:
	static TutorialAHelper * create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	TutorialAHelper();
	~TutorialAHelper();

	void onEnter() override;
	void initializePositions() override;
	void runTutorial(GameState* gameState);

	FocusTakeOver* focusTakeOver;
	Label* scoreTotalsTutorialLabel;
	Label* lossDisplayTutorialLabel;
	Label* rowTotalsTutorialLabel;
	Label* handCardsTutorialLabel;
};
