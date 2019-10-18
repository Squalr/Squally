#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerAttack;
class PlatformerEnemy;

class OrcBomberCombatBehavior : public AttachedBehavior
{
public:
	static OrcBomberCombatBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	OrcBomberCombatBehavior(GameObject* owner);
	~OrcBomberCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEnemy* entity;
};
