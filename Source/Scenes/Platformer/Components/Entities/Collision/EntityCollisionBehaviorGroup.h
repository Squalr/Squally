#pragma once

#include "Engine/Components/ComponentGroup.h"

class EntityCollisionBehaviorGroup : public ComponentGroup
{
public:
	static EntityCollisionBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EntityCollisionBehaviorGroup(GameObject* owner);
	virtual ~EntityCollisionBehaviorGroup();

	void onLoad() override;

private:
	typedef ComponentGroup super;
};
