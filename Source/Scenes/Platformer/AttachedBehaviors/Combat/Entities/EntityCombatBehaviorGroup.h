#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class EntityCombatBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static EntityCombatBehaviorGroup* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityCombatBehaviorGroup(GameObject* owner, std::string attachedBehaviorArgs);
	~EntityCombatBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
