#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Scrappy;
class Squally;
class PlatformerEntity;

class TrainingHealTutorialBehavior : public AttachedBehavior
{
public:
	static TrainingHealTutorialBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	TrainingHealTutorialBehavior(GameObject* owner);
	virtual ~TrainingHealTutorialBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	void runTutorial();

	int healCount;

	PlatformerEntity* entity;
	Scrappy* scrappy;
	Squally* squally;

	static const int HealsBeforeTutorial;
};
