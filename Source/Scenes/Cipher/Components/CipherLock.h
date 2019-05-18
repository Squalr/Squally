#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

namespace cocos2d
{
	class ClippingNode;
	class Sprite;
}

class Sound;

class CipherLock : public CipherComponentBase
{
public:
	static CipherLock* create();

protected:
	void onBeforeStateChange(CipherState* cipherState) override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;
	CipherLock();
	~CipherLock();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	std::vector<cocos2d::Sprite*> cipherPinholes;
	std::vector<cocos2d::Sprite*> cipherPins;

	cocos2d::ClippingNode* contentClip;
	cocos2d::Sprite* background;
	cocos2d::Sprite* steelGear;
	cocos2d::Sprite* woodGearTop;
	cocos2d::Sprite* woodGearBottom;
	cocos2d::Sprite* shaft;
	cocos2d::Sprite* pinboardBack;
	cocos2d::Node* cipherPinsNode;
	cocos2d::Sprite* stoppingBlock;
	cocos2d::Sprite* pinboardFront;

	Sound* gearTurnSound;

	bool hasAnyPinFailed;

	static const int PinSpacing;
	static const int PinUnlockDistance;
};
