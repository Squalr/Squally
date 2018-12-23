#pragma once

#include "Scenes/Hexus/Components/Tutorials/TutorialBase.h"

class FocusTakeOver;
class HelpArrow;
class LocalizedLabel;
class TextMenuSprite;

class TutorialDIntroSequence : public TutorialBase
{
public:
	static TutorialDIntroSequence* create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	TutorialDIntroSequence();
	~TutorialDIntroSequence();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void initializeCallbacks(GameState* gameState);
	bool tryHijackState(GameState* gameState) override;

	void runTutorialHandCards(GameState* gameState);
	void concludeTutorial(GameState* gameState);

	FocusTakeOver* focusTakeOver;
	LocalizedLabel* handCardsTutorialLabel;
	TextMenuSprite* handCardsNextButton;
	HelpArrow* helpArrowHandCards;
};
