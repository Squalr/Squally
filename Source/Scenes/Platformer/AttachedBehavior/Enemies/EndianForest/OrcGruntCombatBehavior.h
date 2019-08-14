#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerAttack;
class PlatformerEnemy;

class OrcGruntCombatBehavior : public AttachedBehavior
{
public:
	static OrcGruntCombatBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	OrcGruntCombatBehavior(GameObject* owner);
	~OrcGruntCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEnemy* entity;
};
