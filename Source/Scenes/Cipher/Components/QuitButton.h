#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

class ClickableTextNode;

class QuitButton : public CipherComponentBase
{
public:
	static QuitButton* create();

protected:
	QuitButton();
	virtual ~QuitButton();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;

	ClickableTextNode* quitButton;
};
