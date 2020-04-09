#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

class ClickableTextNode;

class AsciiButton : public CipherComponentBase
{
public:
	static AsciiButton* create();

protected:
	AsciiButton();
	virtual ~AsciiButton();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;

	ClickableTextNode* asciiButton;
};
