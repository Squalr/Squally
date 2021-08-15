#pragma once

#include "Engine/Components/GameComponent.h"

class EntityRuneBehavior;
class Squally;

class SquallyRuneBehavior : public GameComponent
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
	typedef GameComponent super;

	void saveState();

	Squally* squally = nullptr;
	EntityRuneBehavior* entityRuneBehavior = nullptr;
};
