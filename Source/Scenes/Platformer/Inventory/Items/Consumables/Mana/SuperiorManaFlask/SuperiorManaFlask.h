#pragma once

#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"

class LocalizedString;
class Sound;

class SuperiorManaFlask : public Consumable
{
public:
	static SuperiorManaFlask* create();

	void useOutOfCombat(PlatformerEntity* target) override;
	bool canUseOnTarget(PlatformerEntity* target) override;
	virtual LocalizedString* getDescription();
	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;
	static const float RestorePercentage;

protected:
	SuperiorManaFlask();
	virtual ~SuperiorManaFlask();

	PlatformerAttack* createAssociatedAttack() override;

private:
	typedef Consumable super;

	Sound* outOfCombatSound = nullptr;
};
