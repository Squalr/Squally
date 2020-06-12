#pragma once

#include "Objects/Platformer/Combat/CombatObject.h"

class PlatformerAttack;
class PlatformerEntity;
class SmartAnimationSequenceNode;
class TimelineEntry;
class WorldSound;

class ArrowRain : public CombatObject
{
public:
	static ArrowRain* create(PlatformerEntity* caster, PlatformerEntity* target);

	void runArrowRain();

	static const std::string HackIdentifierArrowRainSpeed;
	static const int TickCount;
	static const int Damage;
	static const float TimeBetweenTicks;
	static const float StartDelay;

protected:
	ArrowRain(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~ArrowRain();

	void onEnter() override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef CombatObject super;

	void damageOtherTeam();
	void compareTeam(TimelineEntry* entry);

	volatile bool isOnPlayerTeam;
};
