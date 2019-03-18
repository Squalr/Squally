#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

class ClickableNode;
class LocalizedLabel;
class LocalizedString;

class BlockBase : public CipherComponentBase
{
protected:
	BlockBase(ClickableNode* block, LocalizedString* label);
	~BlockBase();

	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef CipherComponentBase super;

	ClickableNode* block;
	LocalizedLabel* label;
};
