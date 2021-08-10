#pragma once

#include "Engine/Components/GameComponent.h"

class Squally;

class SquallyHackingBehavior : public GameComponent
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
	typedef GameComponent super;

	void toggleHackerMode();

	Squally* squally = nullptr;
};
