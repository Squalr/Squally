#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Squally;

class SquallyCameraFollowBehavior : public AttachedBehavior
{
public:
	static SquallyCameraFollowBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyCameraFollowBehavior(GameObject* owner);
	~SquallyCameraFollowBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	Squally* squally;
};
