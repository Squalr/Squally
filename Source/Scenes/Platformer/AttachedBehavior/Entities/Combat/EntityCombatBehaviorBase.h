#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerAttack;
class PlatformerEntity;

class EntityCombatBehaviorBase : public AttachedBehavior
{
public:
	void setTimelineSpeed(float timelineSpeed);
	float getTimelineSpeed();

protected:
	EntityCombatBehaviorBase(GameObject* owner);
	virtual ~EntityCombatBehaviorBase();
	
	void onLoad() override;

	PlatformerEntity* entity;

private:
	typedef AttachedBehavior super;
	
	virtual void onBeforeDamageTaken(int* damageOrHealing, bool* blocked, std::function<void()> handleCallback);
	virtual void onBeforeDamageDelt(int* damageOrHealing, std::function<void()> handleCallback);

	int bonusArmor;
	int bonusAttack;
	float bonusSpeed;

	float timelineSpeed;
};
