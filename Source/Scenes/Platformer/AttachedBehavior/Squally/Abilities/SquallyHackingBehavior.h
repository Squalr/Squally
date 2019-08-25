#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class EntityRuneBehavior;
class Squally;

class SquallyHackingBehavior : public AttachedBehavior
{
public:
	static SquallyHackingBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyHackingBehavior(GameObject* owner);
	~SquallyHackingBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	Squally* squally;
	EntityRuneBehavior* entityRuneBehavior;
};
