#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class EntityBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static EntityBehaviorGroup* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityBehaviorGroup(GameObject* owner, std::string attachedBehaviorArgs);
	~EntityBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
