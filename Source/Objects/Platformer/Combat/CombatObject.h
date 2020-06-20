#pragma once

#include "Engine/Hackables/HackableObject.h"
#include "Events/CombatEvents.h"

class PlatformerEntity;

class CombatObject : public HackableObject
{
public:
protected:
	CombatObject(PlatformerEntity* caster, PlatformerEntity* owner, bool onTimeline);
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

	PlatformerEntity* caster;
	PlatformerEntity* owner;
	bool canUpdate;
	bool onTimeline;
	bool timelinePaused;
	bool timelinePausedCinematic;

private:
	typedef HackableObject super;
	
	void updateObjectCanUpdate();
};
