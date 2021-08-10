#pragma once

#include "Engine/Components/GameComponent.h"

class Squally;

class SquallyDisableHackFxBehavior : public GameComponent
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
	typedef GameComponent super;

	void toggleHackerMode();

	Squally* squally = nullptr;
};
