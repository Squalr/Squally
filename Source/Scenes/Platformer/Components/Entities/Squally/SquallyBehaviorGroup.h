#pragma once

#include "Engine/Components/ComponentGroup.h"

class SquallyBehaviorGroup : public ComponentGroup
{
public:
	static SquallyBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyBehaviorGroup(GameObject* owner);
	virtual ~SquallyBehaviorGroup();

	void onLoad() override;

private:
	typedef ComponentGroup super;
};
