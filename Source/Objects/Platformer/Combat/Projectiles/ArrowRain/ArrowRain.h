#pragma once

#include "Objects/Platformer/Combat/CombatObject.h"

class PlatformerAttack;
class PlatformerEntity;
class SmartAnimationSequenceNode;
class WorldSound;

class ArrowRain : public CombatObject
{
public:
	static ArrowRain* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string HackIdentifierArrowRainSpeed;

protected:
	ArrowRain(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~ArrowRain();

	void update(float dt) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef CombatObject super;

	void setArrowRainSpeed();
};
