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
	virtual void onBeforeStateChange(CipherState* cipherState);
	virtual void onAnyRequestStateChange(CipherState* cipherState);
	virtual void onAnyStateChange(CipherState* cipherState);

private:
	typedef SmartNode super;
	void onRequestStateChangeEvent(cocos2d::EventCustom* eventCustom);
	void onBeforeStateChangeEvent(cocos2d::EventCustom* eventCustom);
	void onStateChangeEvent(cocos2d::EventCustom* eventCustom);
};
