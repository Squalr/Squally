#pragma once

#include "Engine/SmartNode.h"
#include "Scenes/Cipher/CipherState.h"

namespace cocos2d
{
	class EventCustom;
}

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
	void onRequestStateChangeEvent(cocos2d::EventCustom* eventCustom);
	void onBeforeStateChangeEvent(cocos2d::EventCustom* eventCustom);
	void onStateChangeEvent(cocos2d::EventCustom* eventCustom);

	CipherState::StateType stateType;
	float enterDelay;
};
