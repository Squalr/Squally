#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class AttachedBehavior;

class AttachedBehaviorGroup : public AttachedBehavior
{
public:

protected:
	AttachedBehaviorGroup(GameObject* owner, std::string attachedBehaviorArgs, std::vector<AttachedBehavior*> attachedBehaviors);
	~AttachedBehaviorGroup();

private:
	typedef AttachedBehavior super;
};

