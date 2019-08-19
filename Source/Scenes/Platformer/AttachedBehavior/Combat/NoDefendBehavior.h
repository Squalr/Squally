#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;

class NoDefendBehavior : public AttachedBehavior
{
public:
	static NoDefendBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	NoDefendBehavior(GameObject* owner);
	~NoDefendBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	void runTutorial();

	PlatformerEntity* entity;
};
