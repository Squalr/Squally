#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

class FriendlyStaticBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static FriendlyStaticBehaviorGroup* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	FriendlyStaticBehaviorGroup(GameObject* owner);
	~FriendlyStaticBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
