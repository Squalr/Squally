#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;
class Squally;

class FollowMovementBehavior : public AttachedBehavior
{
public:
	static FollowMovementBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	FollowMovementBehavior(GameObject* owner);
	~FollowMovementBehavior();

	void onLoad() override;
	void update(float dt) override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
	Squally* squally;

	static const float StopFollowRangeX;
	static const float TryJumpRangeY;
	static const float ResetRangeX;
	static const float ResetRangeY;
};
