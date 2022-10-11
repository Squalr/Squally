#pragma once

#include "Engine/Components/GameComponent.h"

class Squally;

class SquallyAnimationBehavior : public GameComponent
{
public:
	static SquallyAnimationBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyAnimationBehavior(GameObject* owner);
	virtual ~SquallyAnimationBehavior();

	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;

private:
	typedef GameComponent super;

	Squally* squally = nullptr;
};
