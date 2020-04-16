#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

class KingGroggBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static KingGroggBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	KingGroggBehaviorGroup(GameObject* owner);
	virtual ~KingGroggBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
