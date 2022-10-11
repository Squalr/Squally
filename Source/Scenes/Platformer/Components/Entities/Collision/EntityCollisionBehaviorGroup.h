#pragma once

#include "Engine/Components/GameComponentGroup.h"

class EntityCollisionBehaviorGroup : public GameComponentGroup
{
public:
	static EntityCollisionBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EntityCollisionBehaviorGroup(GameObject* owner);
	virtual ~EntityCollisionBehaviorGroup();

	void onLoad() override;

private:
	typedef GameComponentGroup super;
};
