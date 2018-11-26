#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/FocusTakeOver.h"
#include "Engine/UI/Controls/HelpArrow.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/Utils/StrUtils.h"

#include "Scenes/Hexus/Components/Tutorials/TutorialBase.h"

using namespace cocos2d;

class TutorialAWinningRound : public TutorialBase
{
public:
	static TutorialAWinningRound * create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	TutorialAWinningRound();
	~TutorialAWinningRound();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void initializeCallbacks(GameState* gameState);
	bool tryHijackState(GameState* gameState) override;

	void runTutorialScoreTotal(GameState* gameState);
	void concludeTutorial(GameState* gameState);

	FocusTakeOver* focusTakeOver;
	Label* scoreTotalsTutorialLabel;
	TextMenuSprite* scoreTotalsNextButton;
	HelpArrow* helpArrowScoreTotals;
};
