#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

class EntityCollisionBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static EntityCollisionBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EntityCollisionBehaviorGroup(GameObject* owner);
	virtual ~EntityCollisionBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
