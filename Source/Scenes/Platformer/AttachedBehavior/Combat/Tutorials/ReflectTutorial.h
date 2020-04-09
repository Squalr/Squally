#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class Scrappy;
class Squally;
class PlatformerEntity;

class ReflectTutorial : public AttachedBehavior
{
public:
	static ReflectTutorial* create(GameObject* owner);

	static const std::string MapKey;

protected:
	ReflectTutorial(GameObject* owner);
	virtual ~ReflectTutorial();

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
