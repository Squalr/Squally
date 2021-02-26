#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class ShamanCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static ShamanCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	ShamanCombatBehavior(GameObject* owner);
	virtual ~ShamanCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
