#pragma once

#include "Engine/Components/GameComponent.h"

class Squally;

class SquallyHudTrackBehavior : public GameComponent
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
	typedef GameComponent super;

	Squally* squally = nullptr;
};
