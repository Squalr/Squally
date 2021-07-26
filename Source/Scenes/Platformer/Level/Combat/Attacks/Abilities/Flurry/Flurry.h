#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class WorldSound;

class Flurry : public PlatformerAttack
{
public:
	static Flurry* create(float attackDuration, float recoverDuration, Priority priority);

	LocalizedString* getString() override;
	std::string getAttackAnimation() override;
	void onAttackTelegraphBegin() override;

protected:
	Flurry(float attackDuration, float recoverDuration, Priority priority);
	virtual ~Flurry();

	void registerHackables() override;
	void performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets) override;
	void doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target) override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;
	void setRandomHits();

	int hits;

	std::vector<WorldSound*> slashSounds;
	std::vector<WorldSound*> hitSounds;

	static const int LowerBoundHits;
	static const int MinHits;
	static const int MaxHits;
};
