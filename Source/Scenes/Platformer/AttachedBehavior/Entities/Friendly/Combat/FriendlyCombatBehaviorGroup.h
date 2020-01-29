#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

class FriendlyCombatBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static FriendlyCombatBehaviorGroup* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	FriendlyCombatBehaviorGroup(GameObject* owner);
	virtual ~FriendlyCombatBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
