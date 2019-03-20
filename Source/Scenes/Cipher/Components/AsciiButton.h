#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

class ClickableTextNode;

class AsciiButton : public CipherComponentBase
{
public:
	static AsciiButton* create();

protected:
	void onBeforeStateChange(CipherState* cipherState) override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;
	AsciiButton();
	~AsciiButton();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	ClickableTextNode* asciiButton;
};
