#pragma once

#include "Engine/Components/GameComponent.h"

class Squally;

class SquallyDeadVisualBehavior : public GameComponent
{
public:
	static SquallyDeadVisualBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyDeadVisualBehavior(GameObject* owner);
	virtual ~SquallyDeadVisualBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	Squally* squally = nullptr;
};
