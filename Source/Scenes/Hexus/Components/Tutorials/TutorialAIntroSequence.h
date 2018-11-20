#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/FocusTakeOver.h"
#include "Engine/UI/Controls/HelpArrow.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/Tutorials/TutorialBase.h"

using namespace cocos2d;

class TutorialAIntroSequence : public TutorialBase
{
public:
	static TutorialAIntroSequence * create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	TutorialAIntroSequence();
	~TutorialAIntroSequence();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void initializeCallbacks(GameState* gameState);
	bool tryHijackState(GameState* gameState) override;

	void runTutorialScoreTotal(GameState* gameState);
	void runTutorialLossDisplay(GameState* gameState);
	void runTutorialBinaryCards(GameState* gameState);
	void runTutorialDecimalCards(GameState* gameState);
	void runTutorialHexCards(GameState* gameState);
	void runTutorialRowTotals(GameState* gameState);
	void runTutorialHandCards(GameState* gameState);
	void concludeTutorial(GameState* gameState);

	FocusTakeOver* focusTakeOver;
	Label* scoreTotalsTutorialLabel;
	Label* lossDisplayTutorialLabel;
	Label* binaryCardsTutorialLabel;
	Label* decimalCardsTutorialLabel;
	Label* hexCardsTutorialLabel;
	Label* rowTotalsTutorialLabel;
	Label* handCardsTutorialLabel;
	TextMenuSprite* scoreTotalsNextButton;
	TextMenuSprite* lossDisplayNextButton;
	TextMenuSprite* binaryCardsNextButton;
	TextMenuSprite* decimalCardsNextButton;
	TextMenuSprite* hexCardsNextButton;
	TextMenuSprite* rowTotalsNextButton;
	TextMenuSprite* handCardsNextButton;

	HelpArrow* helpArrowScoreTotals;
	HelpArrow* helpArrowLossDisplay;
	HelpArrow* helpArrowRowTotals;
	HelpArrow* helpArrowHandCards;
};
