#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class PlatformerEntity;
class SmartParticles;

class SpellOfBinding : public Buff
{
public:
	static SpellOfBinding* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string SpellOfBindingIdentifier;
	static const std::string HackIdentifierSpellOfBinding;

protected:
	SpellOfBinding(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~SpellOfBinding();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onModifyTimelineSpeed(CombatEvents::ModifiableTimelineSpeedArgs* speed) override;

private:
	typedef Buff super;

	void applySpellOfBinding();
	
	SmartParticles* spellEffect = nullptr;
	cocos2d::Sprite* spellAura = nullptr;
	
	static volatile float currentSpeed;

	static const float MinSpeed;
	static const float DefaultSpeed;
	static const float DefaultHackSpeed;
	static const float MaxSpeed;
	static const float Duration;
};
