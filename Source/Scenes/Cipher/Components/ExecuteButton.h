#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

class ClickableTextNode;

class ExecuteButton : public CipherComponentBase
{
public:
	static ExecuteButton* create();

protected:
	void onBeforeStateChange(CipherState* cipherState) override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;
	ExecuteButton();
	~ExecuteButton();

	void onEnter() override;
	void initializePositions() override;

	ClickableTextNode* executeButton;
};
