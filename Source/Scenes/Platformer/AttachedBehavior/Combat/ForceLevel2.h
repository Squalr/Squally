#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;

class ForceLevel2 : public AttachedBehavior
{
public:
	static ForceLevel2* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	ForceLevel2(GameObject* owner);
	~ForceLevel2();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	void runTutorial();

	PlatformerEntity* entity;
};
