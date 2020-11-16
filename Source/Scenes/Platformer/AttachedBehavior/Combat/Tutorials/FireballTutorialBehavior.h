#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Scrappy;
class Squally;
class PlatformerEntity;

class FireballTutorialBehavior : public AttachedBehavior
{
public:
	static FireballTutorialBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	FireballTutorialBehavior(GameObject* owner);
	virtual ~FireballTutorialBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	void runTutorial();

	bool hasRunTutorial;
	bool tutorialInterrupt;

	PlatformerEntity* entity;
	Scrappy* scrappy;
	Squally* squally;
};
