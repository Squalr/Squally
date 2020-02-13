#pragma once
#include <set>

#include "Engine/Hackables/HackableObject.h"

class CollisionObject;
class HackableData;
class SmartParticles;
class WindClippy;

class Wind : public HackableObject
{
public:
	static Wind* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyWind;

protected:
	Wind(cocos2d::ValueMap& properties);
	virtual ~Wind();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

	void applyWindForce(CollisionObject* target, float dt);
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef HackableObject super;

	void updateWind(float dt);

	cocos2d::Vec2 getButtonOffset() override;

	CollisionObject* windForce;
	HackableData* windDataSpeedY;
	SmartParticles* windParticles;
	cocos2d::Size windSize;
	cocos2d::Vec2 windSpeedDefault;
	cocos2d::Vec2 windSpeed;

	WindClippy* windClippy;

	bool isUniform;

	static const float BaseWindSpeed;
	static const std::string MapPropertyUniform;
	static const std::string MapPropertySpeedX;
	static const std::string MapPropertySpeedY;
};
