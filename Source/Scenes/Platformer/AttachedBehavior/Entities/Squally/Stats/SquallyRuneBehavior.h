#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class EntityRuneBehavior;
class Squally;

class SquallyRuneBehavior : public AttachedBehavior
{
public:
	static SquallyRuneBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyRuneBehavior(GameObject* owner);
	virtual ~SquallyRuneBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	void saveState();

	Squally* squally;
	EntityRuneBehavior* entityRuneBehavior;
};
