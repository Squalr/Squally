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
	CipherFrame();
	virtual ~CipherFrame();

	void onEnter() override;
	void initializePositions() override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;

	cocos2d::Sprite* cipherFrame = nullptr;
	cocos2d::Sprite* furnace = nullptr;
};
