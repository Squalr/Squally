#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartParticles;

class Rabies : public Buff
{
public:
	static Rabies* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string RabiesIdentifier;
	static const std::string HackIdentifierRabies;

protected:
	Rabies(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Rabies();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onModifyTimelineSpeed(CombatEvents::ModifiableTimelineSpeedArgs* speed) override;

private:
	typedef Buff super;

	void applyRabies();
	
	SmartParticles* spellEffect = nullptr;
	cocos2d::Sprite* spellAura = nullptr;
	
	static volatile float currentSpeed;

	static const float MinSpeed;
	static const float DefaultSpeed;
	static const float DefaultHackSpeed;
	static const float MaxSpeed;
	static const float Duration;
};
