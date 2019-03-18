#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;

class BlockBase : public CipherComponentBase
{
protected:
	BlockBase();
	~BlockBase();

	void initializeListeners() override;

private:
	typedef CipherComponentBase super;

	ClickableNode* blockFrameBinary;
	ClickableNode* blockFrameDecimal;
	ClickableNode* blockFrameHex;
	ClickableNode* blockFrameAscii;
};
