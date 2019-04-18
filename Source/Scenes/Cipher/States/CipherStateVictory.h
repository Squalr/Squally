#pragma once

#include "Scenes/Cipher/States/CipherStateBase.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
class ScrollPane;
class LocalizedLabel;

class CipherStateVictory : public CipherStateBase
{
public:
	static CipherStateVictory* create();

protected:
	void onBeforeStateEnter(CipherState* cipherState) override;
	void onStateEnter(CipherState* cipherState) override;
	void onStateReload(CipherState* cipherState) override;
	void onStateExit(CipherState* cipherState) override;

private:
	typedef CipherStateBase super;
	CipherStateVictory();
	~CipherStateVictory();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void giveRewards(CipherState* cipherState);

	CipherState* activeCipherState;
	cocos2d::Sprite* rewardsMenu;
	LocalizedLabel* titleLabel;
	ScrollPane* rewardsScroll;
	ClickableTextNode* okayButton;
};
