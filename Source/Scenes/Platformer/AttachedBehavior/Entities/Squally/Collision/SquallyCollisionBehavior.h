#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityCollisionBehaviorBase.h"

class Squally;

class SquallyCollisionBehavior : public EntityCollisionBehaviorBase
{
public:
	static SquallyCollisionBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyCollisionBehavior(GameObject* owner);
	~SquallyCollisionBehavior();

	void update(float dt) override;
	void onLoad() override;

private:
	typedef EntityCollisionBehaviorBase super;

	float noCombatDuration;

	Squally* squally;

	static const float DefaultNoCombatDuration;
};
