#pragma once

#include "Engine/Components/GameComponent.h"

class Squally;

class SquallyFloatBehavior : public GameComponent
{
public:
	static SquallyFloatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyFloatBehavior(GameObject* owner);
	virtual ~SquallyFloatBehavior();

	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;

private:
	typedef GameComponent super;

	Squally* squally;

	float elapsed;
};
