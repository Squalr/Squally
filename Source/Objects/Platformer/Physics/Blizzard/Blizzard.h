#pragma once
#include <set>

#include "Engine/Hackables/HackableObject.h"

class CollisionObject;
class HackableData;
class SmartParticles;

class Blizzard : public HackableObject
{
public:
	static Blizzard* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	Blizzard(cocos2d::ValueMap& properties);
	virtual ~Blizzard();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

	void applyBlizzardForce(CollisionObject* target, float dt);
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef HackableObject super;

	void updateBlizzard(float dt);

	cocos2d::Vec2 getButtonOffset() override;

	CollisionObject* blizzardForce = nullptr;
	HackableData* blizzardDataSpeedY = nullptr;
	SmartParticles* blizzardParticles = nullptr;
	cocos2d::CSize blizzardSize;
	cocos2d::Vec2 blizzardSpeedDefault;
	cocos2d::Vec2 blizzardSpeed;

	bool isUniform = false;

	static const float BaseBlizzardSpeed;
	static const std::string PropertyUniform;
	static const std::string PropertySpeedX;
	static const std::string PropertySpeedY;
};
