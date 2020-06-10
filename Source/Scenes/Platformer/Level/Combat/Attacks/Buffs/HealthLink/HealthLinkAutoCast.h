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

class HealthLinkAutoCast : public Buff
{
public:
	static HealthLinkAutoCast* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string HealthLinkAutoCastIdentifier;

protected:
	HealthLinkAutoCast(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~HealthLinkAutoCast();

	void onBeforeDamageTaken(volatile int* damageOrHealing, std::function<void()> handleCallback, PlatformerEntity* caster, PlatformerEntity* target) override;

private:
	typedef Buff super;

	bool hasAutoCasted;
};
