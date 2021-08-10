#pragma once

#include "Engine/Components/GameComponent.h"

class Squally;

class SquallyEqBehavior : public GameComponent
{
public:
	static SquallyEqBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyEqBehavior(GameObject* owner);
	virtual ~SquallyEqBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	Squally* squally = nullptr;
};
