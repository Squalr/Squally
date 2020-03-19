#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

class ShopkeeperBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static ShopkeeperBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	ShopkeeperBehaviorGroup(GameObject* owner);
	virtual ~ShopkeeperBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
