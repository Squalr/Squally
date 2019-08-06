#pragma once

#include "Scenes/Platformer/AttachedBehaviors/Entities/EntityMovementBehaviorBase.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class SquallyMovementBehaviors : public EntityMovementBehaviorBase
{
public:
	static SquallyMovementBehaviors* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyMovementBehaviors(GameObject* owner, std::string attachedBehaviorArgs);
	~SquallyMovementBehaviors();

	void update(float dt) override;
	void onLoad() override;

private:
	typedef EntityMovementBehaviorBase super;

	Squally* squally;
};
