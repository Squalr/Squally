#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

class ClickableNode;

class AsciiTable : public CipherComponentBase
{
public:
	static AsciiTable* create();

protected:
	void onBeforeStateChange(CipherState* cipherState) override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;
	AsciiTable();
	~AsciiTable();

	void onEnter() override;
	void initializePositions() override;

	ClickableNode* viewAsciiTableButton;
};
