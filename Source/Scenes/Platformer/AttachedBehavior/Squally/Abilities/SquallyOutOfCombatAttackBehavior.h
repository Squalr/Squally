#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Abilities/EntityOutOfCombatAttackBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class SquallyOutOfCombatAttackBehavior : public EntityOutOfCombatAttackBehavior
{
public:
	static SquallyOutOfCombatAttackBehavior* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyOutOfCombatAttackBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~SquallyOutOfCombatAttackBehavior();

	void onLoad() override;

private:
	typedef EntityOutOfCombatAttackBehavior super;
	
	std::string getOutOfCombatAttackAnimation();
	float getOutOfCombatAttackOnset();
	float getOutOfCombatAttackSustain();

	Squally* squally;
};
