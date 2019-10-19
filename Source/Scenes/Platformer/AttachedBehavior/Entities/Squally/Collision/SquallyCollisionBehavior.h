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
	static SquallyCollisionBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyCollisionBehavior(GameObject* owner);
	~SquallyCollisionBehavior();

	void update(float dt) override;
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	float noCombatDuration;

	Squally* squally;

	static const float DefaultNoCombatDuration;
};
