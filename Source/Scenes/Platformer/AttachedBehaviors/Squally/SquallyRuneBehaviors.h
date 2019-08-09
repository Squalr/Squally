#pragma once

#include "Scenes/Platformer/AttachedBehaviors/Entities/Stats/EntityRuneBehaviorBase.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class SquallyRuneBehaviors : public EntityRuneBehaviorBase
{
public:
	static SquallyRuneBehaviors* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyRuneBehaviors(GameObject* owner, std::string attachedBehaviorArgs);
	~SquallyRuneBehaviors();

	void onLoad() override;

private:
	typedef EntityRuneBehaviorBase super;

	void saveState();

	Squally* squally;
};
