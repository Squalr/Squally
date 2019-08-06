#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;

class OutOfCombatAttackBehaviorBase : public AttachedBehavior
{
protected:
	OutOfCombatAttackBehaviorBase(GameObject* owner, std::string attachedBehaviorArgs);
	~OutOfCombatAttackBehaviorBase();

	void initializePositions() override;
	void onDeveloperModeEnable() override;
	void onDeveloperModeDisable() override;
	void onLoad() override;
	void doOutOfCombatAttack(std::string attackAnimation, float onset, float sustain);

private:
	typedef AttachedBehavior super;

	bool isPerformingOutOfCombatAttack;

	PlatformerEntity* entity;
	cocos2d::Sprite* outOfCombatAttackDebug;
};
