#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerAttack;
class PlatformerEnemy;

class OgreCombatBehavior : public AttachedBehavior
{
public:
	static OgreCombatBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	OgreCombatBehavior(GameObject* owner);
	~OgreCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEnemy* entity;
};
