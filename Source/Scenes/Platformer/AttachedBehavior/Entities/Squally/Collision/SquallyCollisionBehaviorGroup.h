#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

class SquallyCollisionBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static SquallyCollisionBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyCollisionBehaviorGroup(GameObject* owner);
	virtual ~SquallyCollisionBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
