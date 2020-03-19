#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class Scrappy;
class Squally;
class PlatformerEntity;

class IncrementHealthFlaskTutorialBehavior : public AttachedBehavior
{
public:
	static IncrementHealthFlaskTutorialBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	IncrementHealthFlaskTutorialBehavior(GameObject* owner);
	virtual ~IncrementHealthFlaskTutorialBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
