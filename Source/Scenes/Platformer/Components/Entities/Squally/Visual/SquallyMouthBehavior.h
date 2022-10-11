#pragma once

#include "Engine/Components/GameComponent.h"

class Squally;

class SquallyMouthBehavior : public GameComponent
{
public:
	static SquallyMouthBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyMouthBehavior(GameObject* owner);
	virtual ~SquallyMouthBehavior();

	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;

private:
	typedef GameComponent super;

	Squally* squally = nullptr;
};
