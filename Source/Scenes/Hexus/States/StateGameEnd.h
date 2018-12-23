#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class MenuSprite;
class TextMenuSprite;

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
	StateGameEnd();
	~StateGameEnd();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onBackClick(MenuSprite* menuSprite, GameState* gameState);

	TextMenuSprite* backButton;
};
