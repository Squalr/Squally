#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class TigerManCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static TigerManCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	TigerManCombatBehavior(GameObject* owner);
	virtual ~TigerManCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
