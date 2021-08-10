#pragma once

#include "Engine/Components/GameComponentGroup.h"

class ShopkeeperBehaviorGroup : public GameComponentGroup
{
public:
	static ShopkeeperBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	ShopkeeperBehaviorGroup(GameObject* owner);
	virtual ~ShopkeeperBehaviorGroup();

	void onLoad() override;

private:
	typedef GameComponentGroup super;
};
