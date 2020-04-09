#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

namespace cocos2d
{
	class Sprite;
}

class CipherBackground : public CipherComponentBase
{
public:
	static CipherBackground* create();

protected:
	CipherBackground();
	virtual ~CipherBackground();

	void onEnter() override;
	void initializePositions() override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;

	cocos2d::Sprite* cipherBackground;
};
