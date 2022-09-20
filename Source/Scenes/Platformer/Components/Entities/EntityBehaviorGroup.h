#pragma once

#include "Engine/Components/GameComponentGroup.h"

class EntityBehaviorGroup : public GameComponentGroup
{
public:
	static EntityBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EntityBehaviorGroup(GameObject* owner);
	virtual ~EntityBehaviorGroup();

	void onLoad() override;

private:
	typedef GameComponentGroup super;
};
