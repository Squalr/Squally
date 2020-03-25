#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class HackablePreview;
class PlatformerEntity;
class FortitudeClippy;
class SmartParticles;
class WorldSound;

class Fortitude : public Buff
{
public:
	static Fortitude* create(PlatformerEntity* caster, PlatformerEntity* target);

	void enableClippy();

	static const std::string PropertyRestorePotionTutorial;
	static const std::string FortitudeIdentifier;

protected:
	Fortitude(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Fortitude();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onBeforeDamageTaken(int* damageOrHealing, std::function<void()> handleCallback) override;

private:
	typedef Buff super;

	void applyFortitude();
	
	volatile int currentDamageTaken;
	
	FortitudeClippy* clippy;
	SmartParticles* spellEffect;
	
	static const int MaxMultiplier;
	static const float Duration;
};
