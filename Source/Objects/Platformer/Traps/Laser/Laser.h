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
	static Laser* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyLaser;

protected:
	Laser(cocos2d::ValueMap& initProperties);
	~Laser();

	cocos2d::Vec2 getButtonOffset() override;

private:
	typedef HackableObject super;
	void registerHackables();
	void onEnter() override;
	void update(float dt) override;
	void initializePositions() override;
	void updateLaser(float dt);

	LaserAnimation* laserAnimation;
	CollisionObject* laserCollision;

	float currentLaserCountDown;
	float maxLaserCountDown;
	bool isRunningAnimation;
};
