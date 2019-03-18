#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;

class DisplayModeToggles : public CipherComponentBase
{
public:
	static DisplayModeToggles* create();
	
protected:
	void onBeforeStateChange(CipherState* cipherState) override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;
	DisplayModeToggles();
	~DisplayModeToggles();

	void onEnter() override;
	void initializePositions() override;

	ClickableNode* toggleButtonBin;
	ClickableNode* toggleButtonDec;
	ClickableNode* toggleButtonHex;
	ClickableNode* toggleButtonAscii;
};
