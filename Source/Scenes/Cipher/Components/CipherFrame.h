#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

namespace cocos2d
{
	class Sprite;
}

class CipherFrame : public CipherComponentBase
{
public:
	static CipherFrame* create();

protected:
	void onBeforeStateChange(CipherState* cipherState) override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;
	CipherFrame();
	~CipherFrame();

	void onEnter() override;
	void initializePositions() override;

	cocos2d::Sprite* cipherFrame;
	cocos2d::Sprite* furnace;
};
