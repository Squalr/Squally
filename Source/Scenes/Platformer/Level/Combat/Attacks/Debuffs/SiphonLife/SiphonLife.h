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

class SiphonLife : public Buff
{
public:
	static SiphonLife* create(PlatformerEntity* caster, PlatformerEntity* target);

	static const std::string SiphonLifeIdentifier;
	static const int HealAmount;
	static const float TimeBetweenTicks;
	static const int HackTicks;
	static const float StartDelay;

protected:
	SiphonLife(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~SiphonLife();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void runSiphonLife();
	void runRestoreTick();

private:
	typedef Buff super;

	void incrementHeal();

	int healAmount;
	SmartAnimationSequenceNode* healEffect;
	WorldSound* impactSound;
	WorldSound* healSound;
};
