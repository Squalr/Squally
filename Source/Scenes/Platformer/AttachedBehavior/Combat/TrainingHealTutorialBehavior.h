#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class Scrappy;
class Squally;
class PlatformerEntity;

class TrainingHealTutorialBehavior : public AttachedBehavior
{
public:
	static TrainingHealTutorialBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

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
