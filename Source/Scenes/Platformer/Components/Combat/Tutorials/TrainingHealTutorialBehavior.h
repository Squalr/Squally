#pragma once

#include "Engine/Components/GameComponent.h"

class Scrappy;
class Squally;
class PlatformerEntity;

class TrainingHealTutorialBehavior : public GameComponent
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
	typedef GameComponent super;

	void runTutorial();

	int healCount;

	PlatformerEntity* entity;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;

	static const int HealsBeforeTutorial;
};
