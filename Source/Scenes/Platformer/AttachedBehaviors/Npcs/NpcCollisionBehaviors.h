#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class NpcBase;

class NpcCollisionBehaviors : public AttachedBehavior
{
public:
	static NpcCollisionBehaviors* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	NpcCollisionBehaviors(GameObject* owner, std::string attachedBehaviorArgs);
	~NpcCollisionBehaviors();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	NpcBase* npc;
};
