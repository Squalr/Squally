#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerAttack;
class PlatformerEntity;

class OrthrusCombatBehavior : public AttachedBehavior
{
public:
	static OrthrusCombatBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	OrthrusCombatBehavior(GameObject* owner);
	~OrthrusCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
