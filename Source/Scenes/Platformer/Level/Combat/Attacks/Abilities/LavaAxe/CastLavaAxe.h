#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

namespace cocos2d
{
	class Sprite;
};

class WorldSound;

class CastLavaAxe : public PlatformerAttack
{
public:
	static CastLavaAxe* create(float attackDuration, float recoverDuration, Priority priority);
	
	LocalizedString* getString() override;
	std::string getAttackAnimation() override;

protected:
	CastLavaAxe(float attackDuration, float recoverDuration, Priority priority);
	virtual ~CastLavaAxe();

	void initializePositions() override;

	void performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets) override;
	void onCleanup() override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;
	
	WorldSound* castSound = nullptr;
};
