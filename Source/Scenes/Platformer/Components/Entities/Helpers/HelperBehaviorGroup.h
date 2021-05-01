#pragma once

#include "Engine/Components/ComponentGroup.h"

class HelperBehaviorGroup : public ComponentGroup
{
public:
	static HelperBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	HelperBehaviorGroup(GameObject* owner);
	virtual ~HelperBehaviorGroup();

	void onLoad() override;
	void onDisable() override;

private:
	typedef ComponentGroup super;
};
