#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEnemy;
class Squally;

class SquallyCollisionBehaviors : public AttachedBehavior
{
public:
	static SquallyCollisionBehaviors* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyCollisionBehaviors(GameObject* owner, std::string attachedBehaviorArgs);
	~SquallyCollisionBehaviors();

	void update(float dt) override;
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	void engageEnemy(PlatformerEnemy* enemy, bool firstStrike);

	float noCombatDuration;

	Squally* squally;
};
