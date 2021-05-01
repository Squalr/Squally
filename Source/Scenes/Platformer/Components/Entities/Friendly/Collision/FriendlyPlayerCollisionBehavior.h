#pragma once

#include "Engine/Components/Component.h"

class PlatformerEntity;

class FriendlyPlayerCollisionBehavior : public Component
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
	typedef Component super;

	PlatformerEntity* entity;
};
