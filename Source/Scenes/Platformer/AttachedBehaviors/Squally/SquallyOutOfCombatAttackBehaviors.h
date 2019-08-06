#pragma once

#include "Scenes/Platformer/AttachedBehaviors/Entities/OutOfCombatAttackBehaviorBase.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class SquallyOutOfCombatAttackBehaviors : public OutOfCombatAttackBehaviorBase
{
public:
	static SquallyOutOfCombatAttackBehaviors* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyOutOfCombatAttackBehaviors(GameObject* owner, std::string attachedBehaviorArgs);
	~SquallyOutOfCombatAttackBehaviors();

	void onLoad() override;

private:
	typedef OutOfCombatAttackBehaviorBase super;
	
	std::string getOutOfCombatAttackAnimation();
	float getOutOfCombatAttackOnset();
	float getOutOfCombatAttackSustain();

	Squally* squally;
};
