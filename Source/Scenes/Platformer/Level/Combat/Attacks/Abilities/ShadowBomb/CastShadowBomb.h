#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

namespace cocos2d
{
	class Sprite;
};

class WorldSound;

class CastShadowBomb : public PlatformerAttack
{
public:
	static CastShadowBomb* create(float attackDuration, float recoverDuration, Priority priority);
	
	LocalizedString* getString() override;
	std::string getAttackAnimation() override;

protected:
	CastShadowBomb(float attackDuration, float recoverDuration, Priority priority);
	virtual ~CastShadowBomb();

	void initializePositions() override;

	void performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets) override;
	void onCleanup() override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;
	
	WorldSound* castSound = nullptr;
};
