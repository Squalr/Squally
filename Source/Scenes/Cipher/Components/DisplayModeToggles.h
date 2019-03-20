#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class RadioButton;

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
	void initializeListeners() override;

	RadioButton* toggleButtonBin;
	RadioButton* toggleButtonDec;
	RadioButton* toggleButtonHex;
	RadioButton* toggleButtonAscii;

	static const int GroupIdDisplayModeToggles;
};
