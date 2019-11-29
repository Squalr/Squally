#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class CollisionObject;
class PlatformerEntity;

class EntityDisarmedBehavior : public AttachedBehavior
{
public:
	static EntityDisarmedBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityDisarmedBehavior(GameObject* owner);
	~EntityDisarmedBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
