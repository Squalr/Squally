#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

class DemonSwordsmanCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static DemonSwordsmanCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	DemonSwordsmanCombatBehavior(GameObject* owner);
	virtual ~DemonSwordsmanCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
