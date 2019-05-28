#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class HackablePreview;
class PlatformerEntity;
class SmartAnimationSequenceNode;
class Sound;

class RestoreHealth : public Buff
{
public:
	static RestoreHealth* create(PlatformerEntity* caster, PlatformerEntity* target, int healAmount);

	static const std::string MapKeyPropertyRestorePotionTutorial;
	static const std::string EventShowRestorePotionTutorial;
	static const std::string RestoreHealthIdentifier;

protected:
	RestoreHealth(PlatformerEntity* caster, PlatformerEntity* target, int healAmount);
	~RestoreHealth();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void runRestoreHealth();
	void runRestoreTick();

private:
	typedef Buff super;

	void incrementHeal();
	
	int healAmount;
	SmartAnimationSequenceNode* healEffect;
	Sound* healSound;

	static const float TimeBetweenTicks;
};
