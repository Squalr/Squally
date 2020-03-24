#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class HackablePreview;
class PlatformerEntity;
class StoneSkinClippy;
class SmartParticles;
class WorldSound;

class StoneSkin : public Buff
{
public:
	static StoneSkin* create(PlatformerEntity* caster, PlatformerEntity* target);

	void enableClippy();

	static const std::string PropertyRestorePotionTutorial;
	static const std::string StoneSkinIdentifier;

protected:
	StoneSkin(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~StoneSkin();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onModifyTimelineSpeed(float* timelineSpeed, std::function<void()> handleCallback) override;

private:
	typedef Buff super;

	void applyStoneSkin();
	
	volatile float currentSpeed;
	
	StoneSkinClippy* clippy;
	SmartParticles* spellEffect;

	static const float MinSpeed;
	static const float DefaultSpeed;
	static const float MaxSpeed;
	static const float Duration;
};
