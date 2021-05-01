#pragma once

#include "Engine/Components/Component.h"

class Squally;

class SquallyHackingBehavior : public Component
{
public:
	static SquallyHackingBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyHackingBehavior(GameObject* owner);
	virtual ~SquallyHackingBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;

	void toggleHackerMode();

	Squally* squally;
};
