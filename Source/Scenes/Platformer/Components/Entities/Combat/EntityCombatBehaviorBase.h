#pragma once

#include "Engine/Components/GameComponentGroup.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/Level/Combat/Attacks/AbilityType.h"

class PlatformerEntity;

class EntityCombatBehaviorBase : public GameComponentGroup
{
public:
	void setTimelineSpeedBase(float timelineSpeed);
	float getTimelineSpeedBase();
	float getTimelineSpeed();

protected:
	EntityCombatBehaviorBase(GameObject* owner, std::vector<GameComponent*> component = { });
	virtual ~EntityCombatBehaviorBase();
	
	void onLoad() override;
	void onDisable() override;

	PlatformerEntity* entity = nullptr;

private:
	typedef GameComponentGroup super;
	
	virtual void onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing);
	virtual void onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing);

	int bonusArmor = 0;
	int bonusAttack = 0;
	int bonusMagicAttack = 0;
	float bonusSpeed = 0.0f;
	float timelineSpeed = 1.0f;
};
