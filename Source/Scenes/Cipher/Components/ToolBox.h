#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

namespace cocos2d
{
	class Sprite;
}

class XorBlock;

class ToolBox : public CipherComponentBase
{
public:
	static ToolBox* create();
protected:
	void onBeforeStateChange(CipherState* cipherState) override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;
	ToolBox();
	~ToolBox();

	void onEnter() override;
	void initializePositions() override;

	XorBlock* xorBlock;
};
