#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;

class FriendlyPlayerCollisionBehavior : public GameComponent
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
	typedef GameComponent super;

	PlatformerEntity* entity = nullptr;
};
