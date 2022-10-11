#pragma once

#include "Objects/Platformer/Combat/CombatObject.h"

class PlatformerAttack;
class PlatformerEntity;
class SmartAnimationSequenceNode;
class TimelineEntry;
class WorldSound;

class RockSlide : public CombatObject
{
public:
	static RockSlide* create(PlatformerEntity* caster, PlatformerEntity* target, std::string rockResource);

	void runRockSlide();

	static const std::string HackIdentifierRockSlideTeamCompare;
	static const int TickCount;
	static const int MaxDamage;
	static const float TimeBetweenTicks;
	static const float StartDelay;

protected:
	RockSlide(PlatformerEntity* caster, PlatformerEntity* target, std::string rockResource);
	virtual ~RockSlide();

	void onEnter() override;
	void update(float dt) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef CombatObject super;

	void updateAnimation(float dt);
	void damagePlayerEntities();
	void damagePlayerEntity(PlatformerEntity* entity);

	std::vector<cocos2d::Sprite*> rockPool;
	std::vector<float> rockCooldowns;

	std::string rockResource;
	static const std::string StateKeyIsCasterOnEnemyTeam;
};
