#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

class FriendlyNoCollisionBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static FriendlyNoCollisionBehaviorGroup* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	FriendlyNoCollisionBehaviorGroup(GameObject* owner);
	virtual ~FriendlyNoCollisionBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
