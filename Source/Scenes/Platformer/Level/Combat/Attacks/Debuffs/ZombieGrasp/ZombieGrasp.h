#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;

class ZombieGrasp : public Buff
{
public:
	static ZombieGrasp* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string ZombieGraspIdentifier;

protected:
	ZombieGrasp(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~ZombieGrasp();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing) override;

private:
	typedef Buff super;

	void applyZombieGrasp();
	
	SmartParticles* spellEffect = nullptr;
	cocos2d::Sprite* spellAura = nullptr;
	
	static const float Duration;
	static const int MaxMultiplier;
};
