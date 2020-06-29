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

class TrainingHeal : public Buff
{
public:
	static TrainingHeal* create(PlatformerEntity* caster, PlatformerEntity* target, int healAmount);
	
	static const std::string TrainingHealIdentifier;
	static const float TimeBetweenTicks;
	static const int HackTicks;
	static const float StartDelay;

protected:
	TrainingHeal(PlatformerEntity* caster, PlatformerEntity* target, int healAmount);
	virtual ~TrainingHeal();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void runTrainingHeal();
	void runRestoreTick();

private:
	typedef Buff super;

	void incrementHeal();
	
	int healAmount;
	SmartAnimationSequenceNode* healEffect;
	WorldSound* healSound;
	cocos2d::Sprite* spellAura;
};
