#pragma once

#include "Engine/Components/ComponentGroup.h"

class ScrappyCombatBehaviorGroup : public ComponentGroup
{
public:
	static ScrappyCombatBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	ScrappyCombatBehaviorGroup(GameObject* owner);
	virtual ~ScrappyCombatBehaviorGroup();

	void onLoad() override;

private:
	typedef ComponentGroup super;
};
