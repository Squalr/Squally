#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

class HelperBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static HelperBehaviorGroup* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	HelperBehaviorGroup(GameObject* owner);
	~HelperBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
