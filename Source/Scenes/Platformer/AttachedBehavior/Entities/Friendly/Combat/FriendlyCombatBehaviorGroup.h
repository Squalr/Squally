#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

class FriendlyCombatBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static FriendlyCombatBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	FriendlyCombatBehaviorGroup(GameObject* owner);
	virtual ~FriendlyCombatBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
