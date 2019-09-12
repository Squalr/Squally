#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

namespace cocos2d
{
	class Sprite;
}

class CipherDecor : public CipherComponentBase
{
public:
	static CipherDecor* create();

protected:
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;
	CipherDecor();
	~CipherDecor();

	void onEnter() override;
	void initializePositions() override;

	cocos2d::Sprite* furnace;
	cocos2d::Sprite* logo;
	cocos2d::Sprite* cipherLabel;
};
