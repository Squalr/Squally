#pragma once

#include "Engine/Components/ComponentGroup.h"

class SquallyCollisionBehaviorGroup : public ComponentGroup
{
public:
	static SquallyCollisionBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyCollisionBehaviorGroup(GameObject* owner);
	virtual ~SquallyCollisionBehaviorGroup();

	void onLoad() override;

private:
	typedef ComponentGroup super;
};
