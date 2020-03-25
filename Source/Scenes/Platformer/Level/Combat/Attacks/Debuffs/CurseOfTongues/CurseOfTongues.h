#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class HackablePreview;
class PlatformerEntity;
class CurseOfTonguesClippy;
class SmartParticles;
class WorldSound;

class CurseOfTongues : public Buff
{
public:
	static CurseOfTongues* create(PlatformerEntity* caster, PlatformerEntity* target);

	void enableClippy();

	static const std::string PropertyRestorePotionTutorial;
	static const std::string CurseOfTonguesIdentifier;

protected:
	CurseOfTongues(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~CurseOfTongues();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onModifyTimelineSpeed(float* timelineSpeed, std::function<void()> handleCallback) override;

private:
	typedef Buff super;

	void applyCurseOfTongues();
	
	volatile float currentSpeed;
	
	CurseOfTonguesClippy* clippy;
	SmartParticles* spellEffect;

	static const float MinSpeed;
	static const float DefaultSpeed;
	static const float MaxSpeed;
	static const float Duration;
};
