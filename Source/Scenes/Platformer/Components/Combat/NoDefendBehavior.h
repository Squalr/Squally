#pragma once

#include "Engine/Components/Component.h"

class PlatformerEntity;

class NoDefendBehavior : public Component
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
	typedef Component super;

	void runTutorial();

	PlatformerEntity* entity;
};
