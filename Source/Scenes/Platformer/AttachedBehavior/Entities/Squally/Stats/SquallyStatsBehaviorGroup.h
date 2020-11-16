#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

class SquallyStatsBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static SquallyStatsBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyStatsBehaviorGroup(GameObject* owner);
	virtual ~SquallyStatsBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
