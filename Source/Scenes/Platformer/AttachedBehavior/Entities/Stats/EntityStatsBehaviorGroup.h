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
	static EntityStatsBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EntityStatsBehaviorGroup(GameObject* owner);
	virtual ~EntityStatsBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
