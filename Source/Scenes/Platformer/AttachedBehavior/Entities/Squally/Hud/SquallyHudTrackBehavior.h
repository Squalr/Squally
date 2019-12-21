#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Squally;

class SquallyHudTrackBehavior : public AttachedBehavior
{
public:
	static SquallyHudTrackBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyHudTrackBehavior(GameObject* owner);
	~SquallyHudTrackBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	Squally* squally;
};
