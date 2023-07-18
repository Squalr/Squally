#pragma once

#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"

class LocalizedString;
class Sound;

class IncrementManaFlask : public Consumable
{
public:
	static IncrementManaFlask* create();
	
	void useOutOfCombat(PlatformerEntity* target) override;
	bool canUseOnTarget(PlatformerEntity* target) override;
	LocalizedString* getDescription() override;
	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;
	static const int HealTicks;

protected:
	IncrementManaFlask();
	virtual ~IncrementManaFlask();

	PlatformerAttack* createAssociatedAttack() override;

private:
	typedef Consumable super;

	Sound* outOfCombatSound = nullptr;
};
