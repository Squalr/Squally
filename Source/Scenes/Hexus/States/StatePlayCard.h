#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class CardRow;
class Sound;

class StatePlayCard : public StateBase
{
public:
	static StatePlayCard* create();

	static void DoNextTransition(GameState* gameState, bool enterPeekState = false);

protected:
	StatePlayCard();
	virtual ~StatePlayCard();
	
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	typedef StateBase super;

	bool tryAbsorb(GameState* gameState, CardRow* cardRow);
	void passFromError(GameState* gameState);

	// This may seem like a violation of responsibilities (ie the card should play the sound), but this falls apart for rows, as
	// this pattern would mean all cards in the row would play the same sound and it would be terrible
	// Controlling this behavior in this class is the solution
	Sound* movementSound = nullptr;
	Sound* shlSound = nullptr;
	Sound* shrSound = nullptr;
	Sound* flip1Sound = nullptr;
	Sound* flip2Sound = nullptr;
	Sound* flip3Sound = nullptr;
	Sound* flip4Sound = nullptr;
	Sound* movSound = nullptr;
	Sound* andSound = nullptr;
	Sound* orSound = nullptr;
	Sound* xorSound = nullptr;
	Sound* addSound = nullptr;
	Sound* subSound = nullptr;
	Sound* rolSound = nullptr;
	Sound* rorSound = nullptr;
	Sound* notSound = nullptr;
	Sound* killSound = nullptr;
	Sound* returnToHandSound = nullptr;
	Sound* stealSound = nullptr;
	Sound* sheepSound = nullptr;
};
