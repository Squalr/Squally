#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class TrackingEye : public SmartNode
{
public:
	static TrackingEye* create();

	void pair(TrackingEye* pairedEye);

	static const std::string MapKey;

protected:
	TrackingEye();
	virtual ~TrackingEye();

	void onEnter() override;
	void initializePositions() override;
	void update(float dt) override;

private:
	typedef SmartNode super;

	void updateEyeTracking(float dt);

	cocos2d::Vec2 eyeVector;

	TrackingEye* pairedEye;

	std::vector<cocos2d::Sprite*> eyeParts;
	std::vector<float> leeway;
	
	cocos2d::Sprite* eyeBase;
	cocos2d::Sprite* eyeInner;
	cocos2d::Sprite* eyeRing;
	cocos2d::Sprite* eyePupil;

	Squally* squally;
};
