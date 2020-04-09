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
	virtual ~CipherComponentBase();

	void initializeListeners() override;
	virtual void onBeforeStateChange(CipherState* gameState);
	virtual void onBeforeAnyRequestStateChange(CipherState* gameState);
	virtual void onAnyRequestStateChange(CipherState* gameState);
	virtual void onAnyStateChange(CipherState* gameState);

private:
	typedef SmartNode super;
};
