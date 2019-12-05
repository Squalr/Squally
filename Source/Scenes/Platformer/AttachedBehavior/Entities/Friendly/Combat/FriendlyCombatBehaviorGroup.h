#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

class FriendlyCombatBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static FriendlyCombatBehaviorGroup* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	FriendlyCombatBehaviorGroup(GameObject* owner);
	~FriendlyCombatBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
