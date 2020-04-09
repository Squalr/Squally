#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;

class SpikedBall : public HackableObject
{
public:
	static SpikedBall* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	SpikedBall(cocos2d::ValueMap& properties);
	virtual ~SpikedBall();

	void onEnter() override;
	void initializePositions() override;
	void update(float) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;

private:
	typedef HackableObject super;

	cocos2d::Sprite* ball;
	CollisionObject* ballCollision;
};
