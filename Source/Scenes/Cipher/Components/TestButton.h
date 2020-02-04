#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

class ClickableTextNode;

class TestButton : public CipherComponentBase
{
public:
	static TestButton* create();

protected:
	TestButton();
	virtual ~TestButton();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;

	ClickableTextNode* testButton;
	CipherState* activeCipherState;
};
