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

	float timelineSpeed;
};
