#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

class FriendlyBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static FriendlyBehaviorGroup* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	FriendlyBehaviorGroup(GameObject* owner);
	~FriendlyBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
