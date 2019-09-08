#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;

class EntityNoCollisionBehavior : public AttachedBehavior
{
public:
	static EntityNoCollisionBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityNoCollisionBehavior(GameObject* owner);
	~EntityNoCollisionBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	void runTutorial();

	PlatformerEntity* entity;
};
