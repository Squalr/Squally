#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

class ClickableTextNode;

class UnlockButton : public CipherComponentBase
{
public:
	static UnlockButton* create();

protected:
	UnlockButton();
	virtual ~UnlockButton();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;

	ClickableTextNode* unlockButton;
	CipherState* activeCipherState;
};
