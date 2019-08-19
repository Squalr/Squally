#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;

class NoItemsBehavior : public AttachedBehavior
{
public:
	static NoItemsBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	NoItemsBehavior(GameObject* owner);
	~NoItemsBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	void runTutorial();

	PlatformerEntity* entity;
};
