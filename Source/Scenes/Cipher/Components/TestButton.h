#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

class ClickableTextNode;

class TestButton : public CipherComponentBase
{
public:
	static TestButton* create();

protected:
	void onBeforeStateChange(CipherState* cipherState) override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;
	TestButton();
	~TestButton();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	ClickableTextNode* testButton;
	CipherState* activeCipherState;
};
