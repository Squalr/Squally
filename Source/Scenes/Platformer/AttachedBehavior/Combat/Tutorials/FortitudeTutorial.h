#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class Scrappy;
class Squally;
class PlatformerEntity;

class FortitudeTutorial : public AttachedBehavior
{
public:
	static FortitudeTutorial* create(GameObject* owner);

	static const std::string MapKey;

protected:
	FortitudeTutorial(GameObject* owner);
	virtual ~FortitudeTutorial();

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
