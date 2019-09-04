#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Squally;

class SquallyMovementBehavior : public AttachedBehavior
{
public:
	static SquallyMovementBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyMovementBehavior(GameObject* owner);
	~SquallyMovementBehavior();

	void update(float dt) override;
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	Squally* squally;

	bool isDisposing;
};
