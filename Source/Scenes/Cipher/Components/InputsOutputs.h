#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

namespace cocos2d
{
	class Sprite;
}

class InputsOutputs : public CipherComponentBase
{
public:
	static InputsOutputs* create();
protected:
	void onBeforeStateChange(CipherState* cipherState) override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;
	InputsOutputs();
	~InputsOutputs();

	void onEnter() override;
	void initializePositions() override;
	void updateDisplayedLosses(CipherState* cipherState);

	cocos2d::Sprite* playerSocketA;
	cocos2d::Sprite* playerSocketB;
	cocos2d::Sprite* playerSkullA;
	cocos2d::Sprite* playerSkullB;
	cocos2d::Sprite* enemySocketA;
	cocos2d::Sprite* enemySocketB;
	cocos2d::Sprite* enemySkullA;
	cocos2d::Sprite* enemySkullB;
};
