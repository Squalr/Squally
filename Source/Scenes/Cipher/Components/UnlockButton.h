#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

class ClickableTextNode;

class UnlockButton : public CipherComponentBase
{
public:
	static UnlockButton* create();

protected:
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;
	UnlockButton();
	~UnlockButton();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	ClickableTextNode* unlockButton;
	CipherState* activeCipherState;
};
