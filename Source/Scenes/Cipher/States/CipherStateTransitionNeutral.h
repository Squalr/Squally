#pragma once

#include "Scenes/Cipher/States/CipherStateBase.h"

namespace cocos2d
{
	class ClippingNode;
	class Sprite;
}

class BlockBase;

class CipherStateTransitionNeutral : public CipherStateBase
{
public:
	static CipherStateTransitionNeutral* create();

protected:
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onBeforeStateEnter(CipherState* cipherState) override;
	void onStateEnter(CipherState* cipherState) override;
	void onStateReload(CipherState* cipherState) override;
	void onStateExit(CipherState* cipherState) override;

private:
	typedef CipherStateBase super;
	CipherStateTransitionNeutral();
	~CipherStateTransitionNeutral();

	cocos2d::ClippingNode* contentClip;
	cocos2d::Sprite* transitionPanel;
};
