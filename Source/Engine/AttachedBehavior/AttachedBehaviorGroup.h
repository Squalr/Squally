#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class AttachedBehavior;

class AttachedBehaviorGroup : public AttachedBehavior
{
public:

protected:
	AttachedBehaviorGroup(GameObject* owner, std::vector<AttachedBehavior*> attachedBehavior);
	~AttachedBehaviorGroup();

private:
	typedef AttachedBehavior super;
};

