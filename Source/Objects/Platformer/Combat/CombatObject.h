#pragma once

#include "Engine/Hackables/HackableObject.h"
#include "Events/CombatEvents.h"

namespace cocos2d
{
	class Value;

	typedef std::map<std::string, Value> ValueMap;
}

class PlatformerEntity;

class CombatObject : public HackableObject
{
public:
protected:
	CombatObject(PlatformerEntity* caster, PlatformerEntity* owner, bool onTimeline, float duration = -1.0f);
	virtual ~CombatObject();

	void onEnter() override;
	void update(float dt) override;
	virtual void elapse(float dt);
	virtual void onModifyTimelineSpeed(CombatEvents::ModifiableTimelineSpeedArgs* speed);
	virtual void onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing);
	virtual void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing);
	virtual void onAfterDamageTaken(CombatEvents::DamageOrHealingArgs* damageOrHealing);
	virtual void onAfterDamageDealt(CombatEvents::DamageOrHealingArgs* damageOrHealing);
	virtual void onBeforeHealingTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing);
	virtual void onBeforeHealingDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing);
	virtual void onTimelineReset(CombatEvents::TimelineResetArgs* timelineReset);
	void enableUpdate();
	void disableUpdate();

	PlatformerEntity* caster = nullptr;
	PlatformerEntity* owner = nullptr;
	bool canUpdate = true;
	bool onTimeline = false;
	bool timelinePaused = false;
	bool timelinePausedCinematic = false;
	
	static cocos2d::ValueMap HackStateStorage;
	static const std::string HackStorageKeyDamage;

private:
	typedef HackableObject super;

	void updateDuration(float dt);

	float duration = 0.0f;
	float elapsedDuration = 0.0f;
	
	void updateObjectCanUpdate();
};
