#pragma once

#include "Objects/Platformer/Combat/CombatObject.h"

namespace cocos2d
{
	class Sprite;
};

class PlatformerAttack;
class PlatformerEntity;
class SmartAnimationSequenceNode;
class TimelineEntry;
class WorldSound;

class LavaAxe : public CombatObject
{
public:
	static LavaAxe* create(PlatformerEntity* caster, PlatformerEntity* target);

	void runLavaAxe(TimelineEntry* target);

	static const std::string HackIdentifierLavaAxe;
	
protected:
	LavaAxe(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~LavaAxe();

	void onEnter() override;
	void elapse(float dt) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef CombatObject super;

	void rotateAxe(float dt);
	
	cocos2d::Sprite* axe = nullptr;
	WorldSound* impactSound = nullptr;
};
