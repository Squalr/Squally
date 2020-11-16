#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

class SquallyBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static SquallyBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyBehaviorGroup(GameObject* owner);
	virtual ~SquallyBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
