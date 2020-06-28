#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/Level/Combat/Attacks/AbilityType.h"

class PlatformerAttack;
class PlatformerEntity;

class EntityCombatBehaviorBase : public AttachedBehaviorGroup
{
public:
	void setTimelineSpeedBase(float timelineSpeed);
	float getTimelineSpeedBase();
	float getTimelineSpeed();

protected:
	EntityCombatBehaviorBase(GameObject* owner, std::vector<AttachedBehavior*> attachedBehavior = { });
	virtual ~EntityCombatBehaviorBase();
	
	void onLoad() override;
	void onDisable() override;

	PlatformerEntity* entity;

private:
	typedef AttachedBehaviorGroup super;
	
	virtual void onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing);
	virtual void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing);

	int bonusArmor;
	int bonusAttack;
	int bonusMagicAttack;
	float bonusSpeed;

	float timelineSpeed;
};
