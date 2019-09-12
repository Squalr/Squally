#pragma once

#include "Engine/SmartNode.h"
#include "Scenes/Cipher/CipherState.h"

class CipherState;

class CipherStateBase : public SmartNode
{
protected:
	CipherStateBase(CipherState::StateType stateType);
	~CipherStateBase();

	void initializeListeners() override;
	virtual void onAnyStateChange(CipherState* cipherState);
	virtual void onAnyRequestStateChange(CipherState* cipherState);
	virtual void onBeforeStateEnter(CipherState* cipherState);
	virtual void onStateEnter(CipherState* cipherState);
	virtual void onStateReload(CipherState* cipherState);
	virtual void onStateExit(CipherState* cipherState);

private:
	typedef SmartNode super;

	CipherState::StateType stateType;
	float enterDelay;
};
