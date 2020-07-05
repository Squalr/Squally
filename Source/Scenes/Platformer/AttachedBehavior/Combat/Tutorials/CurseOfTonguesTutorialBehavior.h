#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class Scrappy;
class Squally;
class PlatformerEntity;

class CurseOfTonguesTutorialBehavior : public AttachedBehavior
{
public:
	static CurseOfTonguesTutorialBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	CurseOfTonguesTutorialBehavior(GameObject* owner);
	virtual ~CurseOfTonguesTutorialBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
	Scrappy* scrappy;
	Squally* squally;
};
