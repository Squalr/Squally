#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class TrackingEye : public GameObject
{
public:
	static TrackingEye* create(cocos2d::ValueMap& properties);

	void pair(TrackingEye* pairedEye);

	static const std::string MapKey;

protected:
	TrackingEye(cocos2d::ValueMap& properties);
	virtual ~TrackingEye();

	void onEnter() override;
	void initializePositions() override;
	void update(float dt) override;

private:
	typedef GameObject super;

	void updateEyeTracking(float dt);

	cocos2d::Vec2 initialCoords = cocos2d::Vec2::ZERO;
	cocos2d::Vec2 eyeVector = cocos2d::Vec2::ZERO;

	TrackingEye* pairedEye = nullptr;

	std::vector<cocos2d::Sprite*> eyeParts;
	std::vector<float> leeway;
	
	cocos2d::Sprite* eyeBase = nullptr;
	cocos2d::Sprite* eyeInner = nullptr;
	cocos2d::Sprite* eyeRing = nullptr;
	cocos2d::Sprite* eyePupil = nullptr;

	Squally* squally = nullptr;
};
