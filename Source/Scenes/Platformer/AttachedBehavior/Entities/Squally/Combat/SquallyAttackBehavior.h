#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerAttack;
class Squally;

class SquallyAttackBehavior : public AttachedBehavior
{
public:
	static SquallyAttackBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyAttackBehavior(GameObject* owner);
	~SquallyAttackBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	Squally* squally;
};
