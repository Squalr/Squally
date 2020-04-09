#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class HackablePreview;
class PlatformerEntity;
class SiphonLifeClippy;
class SmartParticles;
class WorldSound;

class SiphonLife : public Buff
{
public:
	static SiphonLife* create(PlatformerEntity* caster, PlatformerEntity* target);

	void enableClippy();

	static const std::string PropertyRestorePotionTutorial;
	static const std::string SiphonLifeIdentifier;

protected:
	SiphonLife(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~SiphonLife();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onModifyTimelineSpeed(float* timelineSpeed, std::function<void()> handleCallback) override;

private:
	typedef Buff super;

	void applySiphonLife();
	
	volatile float currentSpeed;
	
	SiphonLifeClippy* clippy;
	SmartParticles* spellEffect;
	cocos2d::Sprite* spellAura;

	static const float MinSpeed;
	static const float DefaultSpeed;
	static const float MaxSpeed;
	static const float Duration;
};
