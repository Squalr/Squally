#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class EntityRuneBehavior;
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

	Squally* squally;
	EntityRuneBehavior* entityRuneBehavior;
};
