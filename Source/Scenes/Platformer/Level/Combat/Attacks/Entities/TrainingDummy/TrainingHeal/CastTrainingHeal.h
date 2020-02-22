#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

namespace cocos2d
{
	class Sprite;
};

class WorldSound;

class CastTrainingHeal : public PlatformerAttack
{
public:
	static CastTrainingHeal* create(float attackDuration, float recoverDuration, float priority);

	LocalizedString* getString() override;
	std::string getAttackAnimation() override;

protected:
	CastTrainingHeal(float attackDuration, float recoverDuration, float priority);
	virtual ~CastTrainingHeal();

	void initializePositions() override;

	void performAttack(PlatformerEntity* owner, PlatformerEntity* target) override;
	void onCleanup() override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;
	
	cocos2d::Sprite* spellAura;
	WorldSound* healSound;
};
