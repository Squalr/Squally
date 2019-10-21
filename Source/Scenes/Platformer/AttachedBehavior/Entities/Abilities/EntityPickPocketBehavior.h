#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;

class EntityPickPocketBehavior : public AttachedBehavior
{
public:
	static EntityPickPocketBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityPickPocketBehavior(GameObject* owner);
	~EntityPickPocketBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
