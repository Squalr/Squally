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
	static NpcCollisionBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	NpcCollisionBehavior(GameObject* owner);
	~NpcCollisionBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	NpcBase* npc;
};
