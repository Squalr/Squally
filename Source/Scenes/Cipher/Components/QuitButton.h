#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

class ClickableTextNode;

class QuitButton : public CipherComponentBase
{
public:
	static QuitButton* create();

protected:
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;
	QuitButton();
	~QuitButton();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	ClickableTextNode* quitButton;
};
