#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class Scrappy;
class Squally;
class PlatformerEntity;

class RestorePotionTutorialBehavior : public AttachedBehavior
{
public:
	static RestorePotionTutorialBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	RestorePotionTutorialBehavior(GameObject* owner);
	virtual ~RestorePotionTutorialBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
