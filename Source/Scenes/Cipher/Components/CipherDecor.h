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
	CipherDecor();
	virtual ~CipherDecor();

	void onEnter() override;
	void initializePositions() override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;

	cocos2d::Sprite* furnace;
	cocos2d::Sprite* logo;
	cocos2d::Sprite* cipherLabel;
};
