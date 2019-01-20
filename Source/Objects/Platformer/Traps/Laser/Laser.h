#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;
class SmartAnimationSequenceNode;

class Laser : public HackableObject
{
public:
	static Laser* create(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyLaser;

protected:
	Laser(cocos2d::ValueMap* initProperties);
	~Laser();

	cocos2d::Vec2 getButtonOffset() override;

private:
	typedef HackableObject super;
	void registerHackables();
	void onEnter() override;
	void update(float dt) override;
	void initializePositions() override;
	void updateLaser(float dt);

	cocos2d::Sprite* laserHeadTop;
	cocos2d::Sprite* laserHeadBottom;
	cocos2d::Sprite* laserWeak;
	cocos2d::Sprite* laserStrong;
	CollisionObject* laserCollision;

	float height;
	float currentLaserCountDown;
	float maxLaserCountDown;
	bool isRunningAnimation;
};
