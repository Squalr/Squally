#pragma once

#include "Engine/Components/Component.h"

class Squally;

class SquallyMouthBehavior : public Component
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
	typedef Component super;

	Squally* squally;
};
