#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class CastShadowBolt : public PlatformerAttack
{
public:
	static CastShadowBolt* create(float attackDuration, float recoverDuration, Priority priority, int damageMin = 4, int damageMax = 6);

	LocalizedString* getString() override;
	std::string getAttackAnimation() override;

protected:
	CastShadowBolt(float attackDuration, float recoverDuration, Priority priority, int damageMin, int damageMax);
	virtual ~CastShadowBolt();

	void performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets) override;
	void onCleanup() override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;
};
