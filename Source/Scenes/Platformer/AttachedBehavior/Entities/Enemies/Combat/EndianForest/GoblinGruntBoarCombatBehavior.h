#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerAttack;
class PlatformerEntity;

class GoblinGruntBoarCombatBehavior : public AttachedBehavior
{
public:
	static GoblinGruntBoarCombatBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	GoblinGruntBoarCombatBehavior(GameObject* owner);
	~GoblinGruntBoarCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
