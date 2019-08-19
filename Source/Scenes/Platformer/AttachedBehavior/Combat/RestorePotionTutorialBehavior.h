#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class Scrappy;
class PlatformerEntity;

class RestorePotionTutorialBehavior : public AttachedBehavior
{
public:
	static RestorePotionTutorialBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	RestorePotionTutorialBehavior(GameObject* owner);
	~RestorePotionTutorialBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	void runTutorial();

	PlatformerEntity* entity;
	Scrappy* scrappy;

	bool hasTutorialRun;
};
