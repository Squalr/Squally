#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

namespace cocos2d
{
	class Sprite;
}

class BlockBase : public CipherComponentBase
{
protected:
	BlockBase();
	~BlockBase();

	void initializeListeners() override;

private:
	typedef CipherComponentBase super;

	cocos2d::Sprite* blockFrame;
	cocos2d::Sprite* blockFill;
};
