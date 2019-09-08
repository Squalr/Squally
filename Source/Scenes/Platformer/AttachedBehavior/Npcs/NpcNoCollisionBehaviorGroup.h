#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class NpcNoCollisionBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static NpcNoCollisionBehaviorGroup* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	NpcNoCollisionBehaviorGroup(GameObject* owner);
	~NpcNoCollisionBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
