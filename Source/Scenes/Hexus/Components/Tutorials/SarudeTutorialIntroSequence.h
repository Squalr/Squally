#pragma once

#include "Scenes/Hexus/Components/Tutorials/TutorialBase.h"

class FocusTakeOver;
class HelpArrow;
class LocalizedLabel;
class ClickableTextNode;

class SarudeTutorialIntroSequence : public TutorialBase
{
public:
	static SarudeTutorialIntroSequence * create();

protected:
	SarudeTutorialIntroSequence();
	virtual ~SarudeTutorialIntroSequence();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;
	bool tryHijackState(GameState* gameState) override;
	void unHijackState(GameState* gameState) override;

private:
	typedef TutorialBase super;

	void initializeCallbacks(GameState* gameState);
	void runTutorialLossDisplay(GameState* gameState);

	FocusTakeOver* focusTakeOver;
	LocalizedLabel* lossDisplayTutorialLabel;
	ClickableTextNode* lossDisplayNextButton;
	HelpArrow* helpArrowLossDisplay;
};
