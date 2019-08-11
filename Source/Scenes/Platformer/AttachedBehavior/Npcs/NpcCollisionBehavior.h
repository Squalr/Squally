#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class NpcBase;

class NpcCollisionBehavior : public AttachedBehavior
{
public:
	static NpcCollisionBehavior* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	NpcCollisionBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~NpcCollisionBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	NpcBase* npc;
};
