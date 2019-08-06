#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class EntityBehaviors : public AttachedBehaviorGroup
{
public:
	static EntityBehaviors* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityBehaviors(GameObject* owner, std::string attachedBehaviorArgs);
	~EntityBehaviors();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
