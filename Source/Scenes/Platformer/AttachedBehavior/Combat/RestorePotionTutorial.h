#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class FlyBot;
class PlatformerEntity;

class RestorePotionTutorial : public AttachedBehavior
{
public:
	static RestorePotionTutorial* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	RestorePotionTutorial(GameObject* owner);
	~RestorePotionTutorial();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	void runTutorial();

	PlatformerEntity* entity;
	FlyBot* flyBot;

	bool hasTutorialRun;
};
