#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerAttack;
class PlatformerEntity;

class GuanoCombatBehavior : public AttachedBehavior
{
public:
	static GuanoCombatBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	GuanoCombatBehavior(GameObject* owner);
	~GuanoCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
