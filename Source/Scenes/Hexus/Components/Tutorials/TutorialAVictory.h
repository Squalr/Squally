#pragma once

#include "Scenes/Hexus/Components/Tutorials/TutorialBase.h"

class FocusTakeOver;
class HelpArrow;
class LocalizedLabel;
class TextMenuSprite;

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
	LocalizedLabel* lossDisplayTutorialLabel;
	TextMenuSprite* lossDisplayNextButton;
	HelpArrow* helpArrowLossDisplay;
};
