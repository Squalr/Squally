#pragma once

#include "Engine/Components/Component.h"

class Squally;

class SquallyDisableHackFxBehavior : public Component
{
public:
	static SquallyDisableHackFxBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyDisableHackFxBehavior(GameObject* owner);
	virtual ~SquallyDisableHackFxBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;

	void toggleHackerMode();

	Squally* squally;
};
