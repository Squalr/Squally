#pragma once

#include "Engine/Components/ComponentGroup.h"

class GuanoPetrifiedBehaviorGroup : public ComponentGroup
{
public:
	static GuanoPetrifiedBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GuanoPetrifiedBehaviorGroup(GameObject* owner);
	virtual ~GuanoPetrifiedBehaviorGroup();

	void onLoad() override;

private:
	typedef ComponentGroup super;
};
