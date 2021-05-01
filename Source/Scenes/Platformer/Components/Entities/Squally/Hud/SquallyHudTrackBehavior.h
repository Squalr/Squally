#pragma once

#include "Engine/Components/Component.h"

class Squally;

class SquallyHudTrackBehavior : public Component
{
public:
	static SquallyHudTrackBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyHudTrackBehavior(GameObject* owner);
	virtual ~SquallyHudTrackBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;

	Squally* squally;
};
