#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;

class FriendlyPlayerCollisionBehavior : public AttachedBehavior
{
public:
	static FriendlyPlayerCollisionBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	FriendlyPlayerCollisionBehavior(GameObject* owner);
	virtual ~FriendlyPlayerCollisionBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
