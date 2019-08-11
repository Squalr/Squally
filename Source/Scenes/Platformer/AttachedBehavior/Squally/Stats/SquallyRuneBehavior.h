#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityRuneBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class SquallyRuneBehavior : public EntityRuneBehavior
{
public:
	static SquallyRuneBehavior* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyRuneBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~SquallyRuneBehavior();

	void onLoad() override;

private:
	typedef EntityRuneBehavior super;

	void saveState();

	Squally* squally;
};
