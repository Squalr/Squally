#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;
class LaserAnimation;
class SmartAnimationSequenceNode;

class Laser : public HackableObject
{
public:
	static Laser* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	Laser(cocos2d::ValueMap& properties);
	virtual ~Laser();

	void onEnter() override;
	void update(float dt) override;
	void initializePositions() override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef HackableObject super;
	void updateLaser(float dt);

	LaserAnimation* laserAnimation;
	CollisionObject* laserCollision;

	float currentLaserCountDown;
	float maxLaserCountDown;
	bool isRunningAnimation;
};
