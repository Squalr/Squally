#pragma once

#include "Engine/Components/ComponentGroup.h"

class FriendlyCombatBehaviorGroup : public ComponentGroup
{
public:
	static FriendlyCombatBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	FriendlyCombatBehaviorGroup(GameObject* owner);
	virtual ~FriendlyCombatBehaviorGroup();

	void onLoad() override;

private:
	typedef ComponentGroup super;
};
