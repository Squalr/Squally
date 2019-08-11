#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class EntityCollisionBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static EntityCollisionBehaviorGroup* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityCollisionBehaviorGroup(GameObject* owner, std::string attachedBehaviorArgs);
	~EntityCollisionBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
