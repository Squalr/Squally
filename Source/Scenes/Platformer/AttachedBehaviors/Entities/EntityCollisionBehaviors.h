#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;

class EntityCollisionBehaviors : public AttachedBehavior
{
public:
	static EntityCollisionBehaviors* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityCollisionBehaviors(GameObject* owner, std::string attachedBehaviorArgs);
	~EntityCollisionBehaviors();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
