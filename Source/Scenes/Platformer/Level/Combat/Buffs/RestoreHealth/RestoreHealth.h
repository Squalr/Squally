#pragma once

#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

namespace cocos2d
{
	class Sprite;
}

class HackablePreview;
class PlatformerEntity;
class SmartAnimationSequenceNode;

class RestoreHealth : public Buff
{
public:
	static RestoreHealth* create(PlatformerEntity* caster, PlatformerEntity* target, int healAmount);

protected:
	RestoreHealth(PlatformerEntity* caster, PlatformerEntity* target, int healAmount);
	~RestoreHealth();

	void onEnter() override;
	void initializePositions() override;
	void registerHackables() override;
	void runRestoreTick();

private:
	typedef Buff super;

	void incrementHeal();

	int healAmount;
	SmartAnimationSequenceNode* healEffect;

	static const std::string RestoreHealthIdentifier;
	static const float TimeBetweenTicks;
};
