#pragma once

#include "Engine/Components/ComponentGroup.h"

class ShopkeeperBehaviorGroup : public ComponentGroup
{
public:
	static ShopkeeperBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	ShopkeeperBehaviorGroup(GameObject* owner);
	virtual ~ShopkeeperBehaviorGroup();

	void onLoad() override;

private:
	typedef ComponentGroup super;
};
