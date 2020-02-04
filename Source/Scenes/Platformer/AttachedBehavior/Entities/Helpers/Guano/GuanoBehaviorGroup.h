#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

class GuanoBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static GuanoBehaviorGroup* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	GuanoBehaviorGroup(GameObject* owner);
	virtual ~GuanoBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
