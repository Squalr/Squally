#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

class GeckyBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static GeckyBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GeckyBehaviorGroup(GameObject* owner);
	virtual ~GeckyBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
