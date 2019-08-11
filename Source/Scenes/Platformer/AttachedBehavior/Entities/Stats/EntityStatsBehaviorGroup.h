#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class EntityStatsBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static EntityStatsBehaviorGroup* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityStatsBehaviorGroup(GameObject* owner, std::string attachedBehaviorArgs);
	~EntityStatsBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
