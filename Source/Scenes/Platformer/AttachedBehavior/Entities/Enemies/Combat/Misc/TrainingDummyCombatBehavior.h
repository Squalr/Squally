#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerAttack;
class PlatformerEntity;

class TrainingDummyCombatBehavior : public AttachedBehavior
{
public:
	static TrainingDummyCombatBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	TrainingDummyCombatBehavior(GameObject* owner);
	virtual ~TrainingDummyCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
