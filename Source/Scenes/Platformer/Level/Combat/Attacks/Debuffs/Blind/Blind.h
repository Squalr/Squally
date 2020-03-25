#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class HackablePreview;
class PlatformerEntity;
class BlindClippy;
class SmartParticles;
class WorldSound;

class Blind : public Buff
{
public:
	static Blind* create(PlatformerEntity* caster, PlatformerEntity* target);

	void enableClippy();

	static const std::string PropertyRestorePotionTutorial;
	static const std::string BlindIdentifier;

protected:
	Blind(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Blind();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onModifyTimelineSpeed(float* timelineSpeed, std::function<void()> handleCallback) override;

private:
	typedef Buff super;

	void applyBlind();
	
	volatile float currentSpeed;
	
	BlindClippy* clippy;
	SmartParticles* spellEffect;

	static const float MinSpeed;
	static const float DefaultSpeed;
	static const float MaxSpeed;
	static const float Duration;
};
