#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;

class CurseOfTongues : public Buff
{
public:
	static CurseOfTongues* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string CurseOfTonguesIdentifier;

protected:
	CurseOfTongues(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~CurseOfTongues();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onModifyTimelineSpeed(CombatEvents::ModifiableTimelineSpeedArgs* speed) override;

private:
	typedef Buff super;

	void applyCurseOfTongues();
	
	static volatile float currentSpeed;
	
	SmartParticles* spellEffect;
	cocos2d::Sprite* spellAura;

	static const float MinSpeed;
	static const float DefaultSpeed;
	static const float DefaultHackSpeed;
	static const float MaxSpeed;
	static const float Duration;
};
