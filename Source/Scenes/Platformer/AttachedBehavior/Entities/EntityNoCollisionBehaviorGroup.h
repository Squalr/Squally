#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class EntityNoCollisionBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static EntityNoCollisionBehaviorGroup* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityNoCollisionBehaviorGroup(GameObject* owner);
	~EntityNoCollisionBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
