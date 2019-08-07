#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class EntityCollisionBehaviors : public AttachedBehaviorGroup
{
public:
	static EntityCollisionBehaviors* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityCollisionBehaviors(GameObject* owner, std::string attachedBehaviorArgs);
	~EntityCollisionBehaviors();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
