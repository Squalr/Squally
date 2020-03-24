#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class HackablePreview;
class PlatformerEntity;
class HasteClippy;
class SmartParticles;
class WorldSound;

class Haste : public Buff
{
public:
	static Haste* create(PlatformerEntity* caster, PlatformerEntity* target);

	void enableClippy();

	static const std::string PropertyRestorePotionTutorial;
	static const std::string HasteIdentifier;

protected:
	Haste(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Haste();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onModifyTimelineSpeed(float* timelineSpeed, std::function<void()> handleCallback) override;

private:
	typedef Buff super;

	void applyHaste();
	
	volatile float currentSpeed;
	
	HasteClippy* clippy;
	SmartParticles* spellEffect;

	static const float MinSpeed;
	static const float DefaultSpeed;
	static const float MaxSpeed;
};
