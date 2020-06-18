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
	static ArrowRain* create(PlatformerEntity* caster, PlatformerEntity* target, std::string arrowResource);

	void runArrowRain();

	static const std::string HackIdentifierArrowRainTeamCompare;
	static const int TickCount;
	static const int Damage;
	static const float TimeBetweenTicks;
	static const float StartDelay;

protected:
	ArrowRain(PlatformerEntity* caster, PlatformerEntity* target, std::string arrowResource);
	virtual ~ArrowRain();

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

	std::vector<cocos2d::Sprite*> arrowPool;
	std::vector<float> arrowCooldowns;

	std::string arrowResource;
	static volatile bool isOnPlayerTeam;
};
