#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Squally;

class SquallyRuneBehavior : public AttachedBehavior
{
public:
	static SquallyRuneBehavior* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyRuneBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~SquallyRuneBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	void saveState();

	Squally* squally;
};
