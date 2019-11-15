#pragma once

#include "Scenes/Hexus/Components/Tutorials/TutorialBase.h"

class FocusTakeOver;
class HelpArrow;
class LocalizedLabel;
class ClickableTextNode;

class MarcelTutorialIntroSequence : public TutorialBase
{
public:
	static MarcelTutorialIntroSequence * create();

protected:
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef TutorialBase super;
	MarcelTutorialIntroSequence();
	~MarcelTutorialIntroSequence();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void initializeCallbacks(GameState* gameState);
	bool tryHijackState(GameState* gameState) override;
	void unHijackState(GameState* gameState) override;
	void runTutorialLossDisplay(GameState* gameState);

	FocusTakeOver* focusTakeOver;
	LocalizedLabel* lossDisplayTutorialLabel;
	ClickableTextNode* lossDisplayNextButton;
	HelpArrow* helpArrowLossDisplay;
};
