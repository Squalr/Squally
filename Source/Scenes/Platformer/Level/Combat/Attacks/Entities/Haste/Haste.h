#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class HackablePreview;
class PlatformerEntity;
class HasteClippy;
class SmartAnimationSequenceNode;
class WorldSound;

class Haste : public Buff
{
public:
	static Haste* create(PlatformerEntity* caster, PlatformerEntity* target);

	void enableClippy();

	static const std::string MapKeyPropertyRestorePotionTutorial;
	static const std::string HasteIdentifier;
	static const float TimeBetweenTicks;
	static const int HackTicks;
	static const float StartDelay;

protected:
	Haste(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~Haste();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void onModifyTimelineSpeed(float* timelineSpeed, std::function<void()> handleCallback) override;
	float applyHaste(float currentSpeed);

private:
	typedef Buff super;

	void incrementHeal();
	
	HasteClippy* clippy;
	SmartAnimationSequenceNode* spellEffect;
};
