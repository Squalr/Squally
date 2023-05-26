#pragma once

#include "Objects/Platformer/Combat/CombatObject.h"

class PlatformerAttack;
class PlatformerEntity;
class SmartAnimationSequenceNode;
class TimelineEntry;
class WorldSound;

class LavaAxe : public CombatObject
{
public:
	static LavaAxe* create(PlatformerEntity* caster, PlatformerEntity* target, std::function<void(int)> onImpact);

	void runLavaAxe(TimelineEntry* target);

	static const std::string HackIdentifierLavaAxe;
	
protected:
	LavaAxe(PlatformerEntity* caster, PlatformerEntity* target, std::function<void(int)> onImpact);
	virtual ~LavaAxe();

	void onEnter() override;
	void update(float dt) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef CombatObject super;

	void dealDamage(TimelineEntry* target);
	
	SmartAnimationSequenceNode* animationNode = nullptr;
	WorldSound* impactSound = nullptr;
	std::function<void(int)> onImpact = nullptr;
};
