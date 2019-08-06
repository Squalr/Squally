#pragma once

#include "Scenes/Platformer/AttachedBehaviors/Entities/EntityOutOfCombatAttackBehaviorBase.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class SquallyOutOfCombatAttackBehaviors : public EntityOutOfCombatAttackBehaviorBase
{
public:
	static SquallyOutOfCombatAttackBehaviors* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyOutOfCombatAttackBehaviors(GameObject* owner, std::string attachedBehaviorArgs);
	~SquallyOutOfCombatAttackBehaviors();

	void onLoad() override;

private:
	typedef EntityOutOfCombatAttackBehaviorBase super;
	
	std::string getOutOfCombatAttackAnimation();
	float getOutOfCombatAttackOnset();
	float getOutOfCombatAttackSustain();

	Squally* squally;
};
