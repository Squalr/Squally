#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class HackablePreview;
class PlatformerEntity;
class StrengthClippy;
class SmartParticles;
class WorldSound;

class Strength : public Buff
{
public:
	static Strength* create(PlatformerEntity* caster, PlatformerEntity* target);

	void enableClippy();

	static const std::string PropertyRestorePotionTutorial;
	static const std::string StrengthIdentifier;

protected:
	Strength(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Strength();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageDelt(int* damageOrHealing, std::function<void()> handleCallback) override;

private:
	typedef Buff super;

	void applyStrength();
	
	volatile int currentDamageDelt;
	
	StrengthClippy* clippy;
	SmartParticles* spellEffect;
	
	static const int MaxMultiplier;
	static const float Duration;
};
