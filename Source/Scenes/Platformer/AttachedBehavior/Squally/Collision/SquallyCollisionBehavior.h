#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEnemy;
class Squally;

class SquallyCollisionBehavior : public AttachedBehavior
{
public:
	static SquallyCollisionBehavior* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyCollisionBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~SquallyCollisionBehavior();

	void update(float dt) override;
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	float noCombatDuration;

	Squally* squally;

	static const float DefaultNoCombatDuration;
};
