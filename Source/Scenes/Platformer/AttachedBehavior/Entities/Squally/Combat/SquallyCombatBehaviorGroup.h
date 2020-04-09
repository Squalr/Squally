#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class SquallyCombatBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static SquallyCombatBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyCombatBehaviorGroup(GameObject* owner);
	virtual ~SquallyCombatBehaviorGroup();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehaviorGroup super;
};
