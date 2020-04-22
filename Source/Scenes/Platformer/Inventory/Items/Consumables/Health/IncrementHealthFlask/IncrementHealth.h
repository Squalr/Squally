#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class HackablePreview;
class PlatformerEntity;
class SmartAnimationSequenceNode;
class WorldSound;

class IncrementHealth : public Buff
{
public:
	static IncrementHealth* create(PlatformerEntity* caster, PlatformerEntity* target, int healAmount);

	static const std::string PropertyIncrementHealthTutorial;
	static const std::string IncrementHealthIdentifier;
	static const float TimeBetweenTicks;
	static const int HackTicks;
	static const float StartDelay;

protected:
	IncrementHealth(PlatformerEntity* caster, PlatformerEntity* target, int healAmount);
	virtual ~IncrementHealth();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void runIncrementHealth();
	void runRestoreTick();

private:
	typedef Buff super;

	void incrementHeal();
	
	int healAmount;
	SmartAnimationSequenceNode* healEffect;
	WorldSound* impactSound;
	WorldSound* healSound;
};
