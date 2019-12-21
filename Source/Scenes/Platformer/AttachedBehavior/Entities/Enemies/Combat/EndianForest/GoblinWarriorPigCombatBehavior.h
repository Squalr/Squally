#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerAttack;
class PlatformerEntity;

class GoblinWarriorPigCombatBehavior : public AttachedBehavior
{
public:
	static GoblinWarriorPigCombatBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	GoblinWarriorPigCombatBehavior(GameObject* owner);
	~GoblinWarriorPigCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
