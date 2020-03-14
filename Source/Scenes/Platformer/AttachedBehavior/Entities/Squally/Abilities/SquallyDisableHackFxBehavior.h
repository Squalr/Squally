#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Squally;

class SquallyDisableHackFxBehavior : public AttachedBehavior
{
public:
	static SquallyDisableHackFxBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyDisableHackFxBehavior(GameObject* owner);
	virtual ~SquallyDisableHackFxBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	void toggleHackerMode();

	Squally* squally;
};
