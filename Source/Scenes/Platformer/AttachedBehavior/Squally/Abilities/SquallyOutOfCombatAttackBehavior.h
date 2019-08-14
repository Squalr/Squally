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
	static SquallyOutOfCombatAttackBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyOutOfCombatAttackBehavior(GameObject* owner);
	~SquallyOutOfCombatAttackBehavior();

	void onLoad() override;

private:
	typedef EntityOutOfCombatAttackBehavior super;
	
	std::string getOutOfCombatAttackAnimation();
	float getOutOfCombatAttackOnset();
	float getOutOfCombatAttackSustain();

	Squally* squally;
};
