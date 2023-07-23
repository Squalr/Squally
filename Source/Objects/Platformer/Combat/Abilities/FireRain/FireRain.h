#pragma once

#include "Objects/Platformer/Combat/CombatObject.h"

class PlatformerAttack;
class PlatformerEntity;
class SmartAnimationSequenceNode;
class TimelineEntry;
class WorldSound;

class FireRain : public CombatObject
{
public:
	static FireRain* create(PlatformerEntity* caster, PlatformerEntity* target);

	void runFireRain();

	static const std::string HackIdentifierFireRainTeamCompare;
	static const int TickCount;
	static const int Damage;
	static const float TimeBetweenTicks;
	static const float StartDelay;

protected:
	FireRain(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~FireRain();

	void onEnter() override;
	void update(float dt) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef CombatObject super;

	void updateAnimation(float dt);
	void damageOtherTeam();
	void compareTeam(TimelineEntry* entry);

	std::vector<SmartAnimationSequenceNode*> meteorPool;
	std::vector<float> meteorCooldowns;
	WorldSound* impactSfxA = nullptr;
	WorldSound* impactSfxB = nullptr;

	static const std::string StateKeyIsCasterOnEnemyTeam;
};
