#pragma once

#include "Engine/Components/Component.h"

class Squally;

class SquallyEqBehavior : public Component
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
	typedef Component super;

	Squally* squally;
};
