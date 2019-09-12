#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class EventCustom;
}

class CipherState;

class CipherComponentBase : public SmartNode
{
protected:
	CipherComponentBase();
	~CipherComponentBase();

	void initializeListeners() override;
	virtual void onAnyStateChange(CipherState* cipherState);
	virtual void onAnyRequestStateChange(CipherState* cipherState);
	virtual void onBeforeStateEnter(CipherState* cipherState);
	virtual void onStateEnter(CipherState* cipherState);
	virtual void onStateReload(CipherState* cipherState);
	virtual void onStateExit(CipherState* cipherState);

private:
	typedef SmartNode super;
};
