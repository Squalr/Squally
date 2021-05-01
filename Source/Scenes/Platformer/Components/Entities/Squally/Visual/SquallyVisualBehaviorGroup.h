#pragma once

#include "Engine/Components/ComponentGroup.h"

class SquallyVisualBehaviorGroup : public ComponentGroup
{
public:
	static SquallyVisualBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyVisualBehaviorGroup(GameObject* owner);
	virtual ~SquallyVisualBehaviorGroup();

	void onLoad() override;
	void onDisable() override;

private:
	typedef ComponentGroup super;
};
