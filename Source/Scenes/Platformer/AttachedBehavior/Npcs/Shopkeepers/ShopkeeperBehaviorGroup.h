#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class ShopkeeperBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static ShopkeeperBehaviorGroup* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	ShopkeeperBehaviorGroup(GameObject* owner);
	~ShopkeeperBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
