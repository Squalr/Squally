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

	void resetLock();

protected:
	CipherLock();
	virtual ~CipherLock();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;

	std::vector<cocos2d::Sprite*> cipherPinholes;
	std::vector<cocos2d::Sprite*> cipherPins;

	cocos2d::ClippingNode* contentClip = nullptr;
	cocos2d::Sprite* background = nullptr;
	cocos2d::Sprite* steelGear = nullptr;
	cocos2d::Sprite* woodGearTop = nullptr;
	cocos2d::Sprite* woodGearBottom = nullptr;
	cocos2d::Sprite* shaft = nullptr;
	cocos2d::Sprite* pinboardBack = nullptr;
	cocos2d::Node* cipherPinsNode = nullptr;
	cocos2d::Sprite* stoppingBlock = nullptr;
	cocos2d::Sprite* pinboardFront = nullptr;
	Sound* gearTurnSound = nullptr;

	bool hasAnyPinFailed = false;

	static const float PinSpacing;
	static const float PinUnlockDistance;
};
