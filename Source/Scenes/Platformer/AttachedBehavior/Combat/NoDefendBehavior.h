#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;

class NoDefendBehavior : public AttachedBehavior
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
	typedef AttachedBehavior super;

	void runTutorial();

	PlatformerEntity* entity;
};
