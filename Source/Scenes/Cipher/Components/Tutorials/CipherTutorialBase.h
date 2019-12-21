#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"
#include "Scenes/Cipher/CipherState.h"

class CipherTutorialBase : public CipherComponentBase
{
protected:
	CipherTutorialBase(CipherState::StateType stateToHijack);
	virtual ~CipherTutorialBase();

	void onEnter() override;
	void onBeforeAnyRequestStateChange(CipherState* gameState) override;
	void onAnyRequestStateChange(CipherState* gameState) override;
	virtual bool tryHijackState(CipherState* gameState) = 0;
	void tryUnHijackState(CipherState* gameState, bool updateState = true);
	virtual void unHijackState(CipherState* gameState) = 0;

	bool tutorialShown;
	CipherState::StateType cachedPreviousState;
	CipherState::StateType stateToHijack;

private:
	typedef CipherComponentBase super;

	bool isHijacking;
};
