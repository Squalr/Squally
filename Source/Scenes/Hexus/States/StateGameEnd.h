#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class ClickableTextNode;
class Sound;

class StateGameEnd : public StateBase
{
public:
	static StateGameEnd* create();

protected:
	StateGameEnd();
	virtual ~StateGameEnd();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	typedef StateBase super;
	void onBackClick(GameState* gameState);

	ClickableTextNode* backButton;
	Sound* defeatSound;
	Sound* victorySound;
};
