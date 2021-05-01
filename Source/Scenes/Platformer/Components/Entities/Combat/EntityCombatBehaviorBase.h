#pragma once

#include "Engine/Components/ComponentGroup.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/Level/Combat/Attacks/AbilityType.h"

class PlatformerEntity;

class EntityCombatBehaviorBase : public ComponentGroup
{
public:
	void setTimelineSpeedBase(float timelineSpeed);
	float getTimelineSpeedBase();
	float getTimelineSpeed();

protected:
	EntityCombatBehaviorBase(GameObject* owner, std::vector<Component*> component = { });
	virtual ~EntityCombatBehaviorBase();
	
	void onLoad() override;
	void onDisable() override;

	PlatformerEntity* entity;

private:
	typedef ComponentGroup super;
	
	virtual void onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing);
	virtual void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing);

	int bonusArmor;
	int bonusAttack;
	int bonusMagicAttack;
	float bonusSpeed;

	float timelineSpeed;
};
