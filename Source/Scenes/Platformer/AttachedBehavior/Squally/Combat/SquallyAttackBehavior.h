#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerAttack;
class PlatformerEntity;

class SquallyAttackBehavior : public AttachedBehavior
{
public:
	static SquallyAttackBehavior* create(GameObject* owner, std::string attachedBehaviorArgs);

	std::vector<PlatformerAttack*> getAttacks();
	std::vector<PlatformerAttack*> getAvailableAttacks();
	std::vector<PlatformerAttack*> cloneAttacks();
	void registerAttack(PlatformerAttack* attack);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyAttackBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~SquallyAttackBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
	std::vector<PlatformerAttack*> attacks;
};
