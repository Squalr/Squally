#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerAttack;
class PlatformerEntity;

class OrcSwordsmanCombatBehavior : public AttachedBehavior
{
public:
	static OrcSwordsmanCombatBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	OrcSwordsmanCombatBehavior(GameObject* owner);
	virtual ~OrcSwordsmanCombatBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
