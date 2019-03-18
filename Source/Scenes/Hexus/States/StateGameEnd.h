#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class ClickableNode;
class ClickableTextNode;

class StateGameEnd : public StateBase
{
public:
	static StateGameEnd* create();

protected:
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	typedef StateBase super;
	StateGameEnd();
	~StateGameEnd();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onBackClick(GameState* gameState);

	ClickableTextNode* backButton;
};
