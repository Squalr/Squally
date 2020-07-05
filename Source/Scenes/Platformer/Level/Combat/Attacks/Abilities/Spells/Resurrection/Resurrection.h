#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class HackablePreview;
class PlatformerEntity;
class SmartParticles;
class WorldSound;

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
	
	SmartParticles* spellEffect;
	cocos2d::Sprite* spellAura;

	static const float Duration;
};
