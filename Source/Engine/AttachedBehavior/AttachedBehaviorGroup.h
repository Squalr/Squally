#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class AttachedBehaviorGroup : public AttachedBehavior
{
public:

protected:
	AttachedBehaviorGroup(GameObject* owner, std::vector<AttachedBehavior*> attachedBehavior);
	virtual ~AttachedBehaviorGroup();

private:
	typedef AttachedBehavior super;
};

