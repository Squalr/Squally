#pragma once

#include "Objects/Platformer/Combat/CombatObject.h"

class PlatformerAttack;
class PlatformerEntity;
class SmartAnimationSequenceNode;
class TimelineEntry;
class WorldSound;

class ShadowBomb : public CombatObject
{
public:
	static ShadowBomb* create(PlatformerEntity* caster, PlatformerEntity* target);

	void runShadowBomb(TimelineEntry* target);

	static const std::string HackIdentifierShadowBomb;
	
protected:
	ShadowBomb(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~ShadowBomb();

	void onEnter() override;
	void update(float dt) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef CombatObject super;

	void dealDamage(TimelineEntry* target);

	SmartAnimationSequenceNode* animationNode = nullptr;
};
