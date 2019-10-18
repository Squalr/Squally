#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerAttack;
class PlatformerEnemy;

class KingGroggCombatBehavior : public AttachedBehavior
{
public:
	static KingGroggCombatBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	KingGroggCombatBehavior(GameObject* owner);
	~KingGroggCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEnemy* entity;
};
