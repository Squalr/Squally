#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

class ScrappyCombatBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static ScrappyCombatBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	ScrappyCombatBehaviorGroup(GameObject* owner);
	virtual ~ScrappyCombatBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
