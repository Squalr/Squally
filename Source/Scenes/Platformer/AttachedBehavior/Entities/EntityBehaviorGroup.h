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
	static EntityBehaviorGroup* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityBehaviorGroup(GameObject* owner);
	virtual ~EntityBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
