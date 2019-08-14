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
	static EntityCombatBehaviorGroup* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityCombatBehaviorGroup(GameObject* owner);
	~EntityCombatBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
