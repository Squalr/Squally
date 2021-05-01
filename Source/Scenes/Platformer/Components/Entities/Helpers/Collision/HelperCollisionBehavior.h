#pragma once

#include "Scenes/Platformer/Components/Entities/Collision/EntityCollisionBehaviorBase.h"

class HelperCollisionBehavior : public EntityCollisionBehaviorBase
{
public:
	static HelperCollisionBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	HelperCollisionBehavior(GameObject* owner);
	virtual ~HelperCollisionBehavior();
	
	void onEntityCollisionCreated() override;
	void onDisable() override;

private:
	typedef EntityCollisionBehaviorBase super;
};
