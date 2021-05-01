#pragma once

#include "Engine/Components/Component.h"

class Scrappy;
class Squally;
class PlatformerEntity;

class TrainingHealTutorialBehavior : public Component
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
	typedef Component super;

	void runTutorial();

	int healCount;

	PlatformerEntity* entity;
	Scrappy* scrappy;
	Squally* squally;

	static const int HealsBeforeTutorial;
};
