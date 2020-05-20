#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;
class Squally;

class HelperFollowMovementBehavior : public AttachedBehavior
{
public:
	static HelperFollowMovementBehavior* create(GameObject* owner);

	void enableFollow();
	void disableFollow();

	static const std::string MapKey;

protected:
	HelperFollowMovementBehavior(GameObject* owner);
	virtual ~HelperFollowMovementBehavior();

	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
	Squally* squally;

	bool followEnabled;

	static const float StopFollowRangeX;
	static const float TryJumpRangeY;
	static const float ResetRangeX;
	static const float ResetRangeY;
};
