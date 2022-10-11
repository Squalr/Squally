#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;

class NoDefendBehavior : public GameComponent
{
public:
	static NoDefendBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	NoDefendBehavior(GameObject* owner);
	virtual ~NoDefendBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	void runTutorial();

	PlatformerEntity* entity = nullptr;
};
