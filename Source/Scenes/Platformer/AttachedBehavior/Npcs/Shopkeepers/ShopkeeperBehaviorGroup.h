#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

class PlatformerEntity;
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

	PlatformerEntity* entity;
};
