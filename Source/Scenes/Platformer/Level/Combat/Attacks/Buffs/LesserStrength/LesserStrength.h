#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class HackablePreview;
class PlatformerEntity;
class LesserStrengthClippy;
class SmartParticles;
class WorldSound;

class LesserStrength : public Buff
{
public:
	static LesserStrength* create(PlatformerEntity* caster, PlatformerEntity* target);

	void enableClippy();

	static const std::string PropertyRestorePotionTutorial;
	static const std::string LesserStrengthIdentifier;

protected:
	LesserStrength(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~LesserStrength();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onModifyTimelineSpeed(float* timelineSpeed, std::function<void()> handleCallback) override;

private:
	typedef Buff super;

	void applyLesserStrength();
	
	volatile float currentSpeed;
	
	LesserStrengthClippy* clippy;
	SmartParticles* spellEffect;

	static const float MinSpeed;
	static const float DefaultSpeed;
	static const float MaxSpeed;
	static const float Duration;
};
