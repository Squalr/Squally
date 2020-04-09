#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class Sound;

class StateTurnEnd : public StateBase
{
public:
	static StateTurnEnd* create();

protected:
	StateTurnEnd();
	virtual ~StateTurnEnd();
	
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	typedef StateBase super;

	void runIncrementHex0Effect(GameState* gameState);

	Sound* increment0Sound;
};
