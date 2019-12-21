#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

class ScrappyCombatBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static ScrappyCombatBehaviorGroup* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	ScrappyCombatBehaviorGroup(GameObject* owner);
	~ScrappyCombatBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
