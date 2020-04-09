#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class OrthrusCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static OrthrusCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	OrthrusCombatBehavior(GameObject* owner);
	virtual ~OrthrusCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
