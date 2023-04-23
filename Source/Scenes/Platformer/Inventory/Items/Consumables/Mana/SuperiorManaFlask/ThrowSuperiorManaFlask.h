#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class WorldSound;

class ThrowSuperiorManaFlask : public PlatformerAttack
{
public:
	static ThrowSuperiorManaFlask* create(Priority priority);

	LocalizedString* getString() override;
	LocalizedString* getDescription() override;
	std::string getAttackAnimation() override;
	void onAttackTelegraphBegin() override;

protected:
	ThrowSuperiorManaFlask(Priority priority);
	virtual ~ThrowSuperiorManaFlask();

	void performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets) override;
	void onCleanup() override;

private:
	typedef PlatformerAttack super;

	PlatformerAttack* cloneInternal() override;

	WorldSound* throwSound = nullptr;
};
