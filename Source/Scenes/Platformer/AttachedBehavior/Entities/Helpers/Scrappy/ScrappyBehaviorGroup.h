#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

class ScrappyBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static ScrappyBehaviorGroup* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	ScrappyBehaviorGroup(GameObject* owner);
	virtual ~ScrappyBehaviorGroup();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehaviorGroup super;
};
