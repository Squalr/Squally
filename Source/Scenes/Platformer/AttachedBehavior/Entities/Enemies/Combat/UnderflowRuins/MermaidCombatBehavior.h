#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class MermaidCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static MermaidCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	MermaidCombatBehavior(GameObject* owner);
	virtual ~MermaidCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
