#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;

class CannonBall : public HackableObject
{
public:
	static CannonBall* create(const cocos2d::ValueMap& properties, cocos2d::Vec2 velocity);

	static const std::string MapKeyCannonBall;

protected:
	CannonBall(const cocos2d::ValueMap& properties, cocos2d::Vec2 velocity);
	virtual ~CannonBall();

	void onEnter() override;
	void initializePositions() override;
	void update(float) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;

private:
	typedef HackableObject super;

	bool isAccelerating = true;
	cocos2d::Sprite* ball = nullptr;
	CollisionObject* ballCollision = nullptr;
	cocos2d::Vec2 velocity = cocos2d::Vec2::ZERO;
};
