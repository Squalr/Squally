#pragma once

#include "Objects/Platformer/Combat/CombatObject.h"

class PlatformerAttack;
class PlatformerEntity;
class SmartAnimationSequenceNode;
class TimelineEntry;
class WorldSound;

class FogOfWar : public CombatObject
{
public:
	static FogOfWar* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string HackIdentifierFogOfWarTeamCompare;

protected:
	FogOfWar(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~FogOfWar();

	void onEnter() override;
	void update(float dt) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef CombatObject super;

	cocos2d::Vec3 getRandomSpawnPosition();

	struct Fog
	{
		cocos2d::Sprite* sprite;
		float speed;
		cocos2d::Vec3 spawnPosition;

		Fog(cocos2d::Sprite* sprite, float speed, cocos2d::Vec3 spawnPosition) : sprite(sprite), speed(speed), spawnPosition(spawnPosition) { }
	};

	void updateAnimation(float dt);
	void increaseDamage();

	std::vector<Fog> fog;
};
