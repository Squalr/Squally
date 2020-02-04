#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;

class FriendlyPlayerCollisionBehavior : public AttachedBehavior
{
public:
	static FriendlyPlayerCollisionBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	FriendlyPlayerCollisionBehavior(GameObject* owner);
	virtual ~FriendlyPlayerCollisionBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
