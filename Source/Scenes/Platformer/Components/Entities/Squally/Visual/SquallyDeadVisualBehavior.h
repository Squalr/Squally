#pragma once

#include "Engine/Components/Component.h"

class Squally;

class SquallyDeadVisualBehavior : public Component
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
	typedef Component super;

	Squally* squally;
};
