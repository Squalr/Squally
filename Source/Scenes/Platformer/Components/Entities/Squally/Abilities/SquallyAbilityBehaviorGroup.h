#pragma once

#include "Engine/Components/ComponentGroup.h"

class Squally;

class SquallyAbilityBehaviorGroup : public ComponentGroup
{
public:
	static SquallyAbilityBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyAbilityBehaviorGroup(GameObject* owner);
	virtual ~SquallyAbilityBehaviorGroup();

	void onLoad() override;

private:
	typedef ComponentGroup super;
};
