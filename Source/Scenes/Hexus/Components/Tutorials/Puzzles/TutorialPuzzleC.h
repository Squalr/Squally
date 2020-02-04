#pragma once

#include "Scenes/Hexus/Components/Tutorials/TutorialBase.h"

class FocusTakeOver;
class HelpArrow;
class LocalizedLabel;
class ClickableTextNode;

class TutorialPuzzleC : public TutorialBase
{
public:
	static TutorialPuzzleC* create();

protected:
	TutorialPuzzleC();
	virtual ~TutorialPuzzleC();

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
	void runTutorialIntro(GameState* gameState);
\
	FocusTakeOver* focusTakeOver;
	LocalizedLabel* introTutorialLabel;
	ClickableTextNode* introNextButton;
};
