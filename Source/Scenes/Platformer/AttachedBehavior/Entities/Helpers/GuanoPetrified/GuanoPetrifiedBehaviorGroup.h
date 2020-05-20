#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

class GuanoPetrifiedBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static GuanoPetrifiedBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GuanoPetrifiedBehaviorGroup(GameObject* owner);
	virtual ~GuanoPetrifiedBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
