#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Squally;

class SquallySensingBehavior : public AttachedBehavior
{
public:
	static SquallySensingBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallySensingBehavior(GameObject* owner);
	~SquallySensingBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	void toggleSensing();

	Squally* squally;
};
