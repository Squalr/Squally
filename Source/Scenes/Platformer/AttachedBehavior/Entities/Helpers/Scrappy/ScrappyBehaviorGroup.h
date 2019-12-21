#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

class ScrappyBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static ScrappyBehaviorGroup* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	ScrappyBehaviorGroup(GameObject* owner);
	~ScrappyBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
