#pragma once

#include "Engine/Components/Component.h"

class Squally;

class SquallyAnimationBehavior : public Component
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
	typedef Component super;

	Squally* squally;
};
