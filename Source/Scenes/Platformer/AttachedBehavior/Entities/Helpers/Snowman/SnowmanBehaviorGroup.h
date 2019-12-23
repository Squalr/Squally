#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

class SnowmanBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static SnowmanBehaviorGroup* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	SnowmanBehaviorGroup(GameObject* owner);
	~SnowmanBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
