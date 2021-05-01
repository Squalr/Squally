#pragma once

#include "Engine/Components/Component.h"

class Squally;

class SquallyFloatBehavior : public Component
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
	typedef Component super;

	Squally* squally;

	float elapsed;
};
