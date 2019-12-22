#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class HackablePreview;
class PlatformerEntity;
class RestoreHealthClippy;
class SmartAnimationSequenceNode;
class WorldSound;

class RestoreHealth : public Buff
{
public:
	static RestoreHealth* create(PlatformerEntity* caster, PlatformerEntity* target, int healAmount);

	void enableClippy();

	static const std::string MapKeyPropertyRestorePotionTutorial;
	static const std::string RestoreHealthIdentifier;
	static const float TimeBetweenTicks;
	static const int HackTicks;
	static const float StartDelay;

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
	
	RestoreHealthClippy* clippy;
	int healAmount;
	SmartAnimationSequenceNode* healEffect;
	WorldSound* impactSound;
	WorldSound* healSound;
};
