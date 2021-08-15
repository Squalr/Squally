#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

class HackablePreview;
class PlatformerEntity;
class SmartParticles;

class Resurrection : public Buff
{
public:
	static Resurrection* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string ResurrectionIdentifier;

protected:
	Resurrection(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Resurrection();

	void onEnter() override;

private:
	typedef Buff super;

	void applyResurrection();
	
	SmartParticles* spellEffect = nullptr;
	cocos2d::Sprite* spellAura = nullptr;

	static const float Duration;
};
