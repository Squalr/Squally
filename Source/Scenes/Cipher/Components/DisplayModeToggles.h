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
	static DisplayModeToggles* create(bool inAsciiMenu = false);
	
protected:
	DisplayModeToggles(bool inAsciiMenu = false);
	virtual ~DisplayModeToggles();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;

	bool inAsciiMenu;
	RadioButton* toggleButtonBin;
	RadioButton* toggleButtonDec;
	RadioButton* toggleButtonHex;
	RadioButton* toggleButtonAscii;

	static const int GroupIdDisplayModeToggles;
};
