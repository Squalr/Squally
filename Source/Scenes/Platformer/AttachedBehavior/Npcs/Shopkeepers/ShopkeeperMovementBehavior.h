#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerFriendly;
class Squally;

class ShopkeeperMovementBehavior : public AttachedBehavior
{
public:
	static ShopkeeperMovementBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	ShopkeeperMovementBehavior(GameObject* owner);
	~ShopkeeperMovementBehavior();

	void onLoad() override;
	void update(float dt) override;

private:
	typedef AttachedBehavior super;

	PlatformerFriendly* npc;
	Squally* squally;
};
