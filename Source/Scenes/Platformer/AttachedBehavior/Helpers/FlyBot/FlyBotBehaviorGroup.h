#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class FlyBotBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static FlyBotBehaviorGroup* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	FlyBotBehaviorGroup(GameObject* owner);
	~FlyBotBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
