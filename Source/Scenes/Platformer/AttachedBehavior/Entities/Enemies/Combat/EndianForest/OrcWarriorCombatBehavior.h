#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerAttack;
class PlatformerEntity;

class OrcWarriorCombatBehavior : public AttachedBehavior
{
public:
	static OrcWarriorCombatBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	OrcWarriorCombatBehavior(GameObject* owner);
	~OrcWarriorCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
