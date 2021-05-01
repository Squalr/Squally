#pragma once

#include "Engine/Components/ComponentGroup.h"

class GeckyBehaviorGroup : public ComponentGroup
{
public:
	static GeckyBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GeckyBehaviorGroup(GameObject* owner);
	virtual ~GeckyBehaviorGroup();

	void onLoad() override;

private:
	typedef ComponentGroup super;
};
