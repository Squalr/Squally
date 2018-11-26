#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/FocusTakeOver.h"
#include "Engine/UI/Controls/HelpArrow.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Components/Tutorials/TutorialBase.h"

using namespace cocos2d;

class TutorialAVictory : public TutorialBase
{
public:
	static TutorialAVictory * create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	TutorialAVictory();
	~TutorialAVictory();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void initializeCallbacks(GameState* gameState);
	bool tryHijackState(GameState* gameState) override;

	void runTutorialLossDisplay(GameState* gameState);
	void concludeTutorial(GameState* gameState);

	FocusTakeOver* focusTakeOver;
	Label* lossDisplayTutorialLabel;
	TextMenuSprite* lossDisplayNextButton;
	HelpArrow* helpArrowLossDisplay;
};
