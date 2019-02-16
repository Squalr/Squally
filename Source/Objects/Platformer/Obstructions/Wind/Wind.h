#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class ParticleSystem;
}

class CollisionObject;
class HackableData;

class Wind : public HackableObject
{
public:
	static Wind* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyWind;

protected:
	void registerHackables() override;

private:
	typedef HackableObject super;
	Wind(cocos2d::ValueMap& initProperties);
	virtual ~Wind() = default;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;
	void updateWind(float dt);

	cocos2d::Vec2 getButtonOffset() override;

	CollisionObject* windForce;
	HackableData* windDataSpeedY;
	cocos2d::ParticleSystem* windParticles;
	cocos2d::Size windSize;
	cocos2d::Vec2 windSpeedDefault;
	cocos2d::Vec2 windSpeed;
};
