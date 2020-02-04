#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class Sound;

class StateRoundStart : public StateBase
{
public:
	static StateRoundStart* create();

protected:
	StateRoundStart();
	virtual ~StateRoundStart();
	
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	typedef StateBase super;

	Sound* roundStartSound;
};
