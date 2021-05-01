#pragma once

#include "Engine/Components/Component.h"

class EntityRuneBehavior;
class Squally;

class SquallyRuneBehavior : public Component
{
public:
	static SquallyRuneBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyRuneBehavior(GameObject* owner);
	virtual ~SquallyRuneBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;

	void saveState();

	Squally* squally;
	EntityRuneBehavior* entityRuneBehavior;
};
