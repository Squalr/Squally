#pragma once

#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorBase.h"

class OrcSwordsmanCombatBehavior : public EntityCombatBehaviorBase
{
public:
	static OrcSwordsmanCombatBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	OrcSwordsmanCombatBehavior(GameObject* owner);
	virtual ~OrcSwordsmanCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef EntityCombatBehaviorBase super;
};
