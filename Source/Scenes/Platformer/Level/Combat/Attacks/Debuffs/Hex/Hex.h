#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;

class Hex : public Buff
{
public:
	static Hex* create(PlatformerEntity* caster, PlatformerEntity* target);
	
	static const std::string HexIdentifier;

protected:
	Hex(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Hex();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onModifyTimelineSpeed(CombatEvents::ModifiableTimelineSpeedArgs* speed) override;

private:
	typedef Buff super;

	void applyHex();
	
	SmartParticles* spellEffect = nullptr;
	cocos2d::Sprite* spellAura = nullptr;
	
	static volatile float currentSpeed;

	static const float MinSpeed;
	static const float DefaultSpeed;
	static const float DefaultHackSpeed;
	static const float MaxSpeed;
	static const float Duration;
};
