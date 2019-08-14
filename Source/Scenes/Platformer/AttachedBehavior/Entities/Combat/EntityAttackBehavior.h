#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerAttack;
class PlatformerEntity;

class EntityAttackBehavior : public AttachedBehavior
{
public:
	static EntityAttackBehavior* create(GameObject* owner);

	std::vector<PlatformerAttack*> getAttacks();
	std::vector<PlatformerAttack*> getAvailableAttacks();
	void registerAttack(PlatformerAttack* attack);

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityAttackBehavior(GameObject* owner);
	~EntityAttackBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	void buildEquipmentAttacks();

	PlatformerEntity* entity;
	std::vector<PlatformerAttack*> registeredAttacks;
};
