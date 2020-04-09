#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;

class NoItemsBehavior : public AttachedBehavior
{
public:
	static NoItemsBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	NoItemsBehavior(GameObject* owner);
	virtual ~NoItemsBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	void runTutorial();

	PlatformerEntity* entity;
};
