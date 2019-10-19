#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerAttack;
class PlatformerEnemy;

class OrcSwordsmanCombatBehavior : public AttachedBehavior
{
public:
	static OrcSwordsmanCombatBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	OrcSwordsmanCombatBehavior(GameObject* owner);
	~OrcSwordsmanCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEnemy* entity;
};
