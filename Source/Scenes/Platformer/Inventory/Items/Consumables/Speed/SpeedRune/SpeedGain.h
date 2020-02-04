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

class SpeedGain : public Buff
{
public:
	static SpeedGain* create(PlatformerEntity* caster, PlatformerEntity* target, int healAmount);

	static const std::string MapKeyPropertyRestorePotionTutorial;
	static const std::string EventShowRestorePotionTutorial;
	static const std::string SpeedGainIdentifier;

protected:
	SpeedGain(PlatformerEntity* caster, PlatformerEntity* target, int healAmount);
	virtual ~SpeedGain();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void runSpeedGain();
	void runRestoreTick();

private:
	typedef Buff super;

	void incrementHeal();
	
	int healAmount;
	SmartAnimationSequenceNode* healEffect;
	WorldSound* impactSound;
	WorldSound* healSound;

	static const float TimeBetweenTicks;
};
