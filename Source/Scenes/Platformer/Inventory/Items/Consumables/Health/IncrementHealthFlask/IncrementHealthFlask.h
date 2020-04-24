#pragma once

#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"

class LocalizedString;
class Sound;

class IncrementHealthFlask : public Consumable
{
public:
	static IncrementHealthFlask* create();
	
	void useOutOfCombat(PlatformerEntity* target) override;
	bool canUseOnTarget(PlatformerEntity* target) override;
	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;
	static const int HealTicks;

protected:
	IncrementHealthFlask();
	virtual ~IncrementHealthFlask();

	PlatformerAttack* createAssociatedAttack() override;

private:
	typedef Consumable super;

	Sound* outOfCombatSound;
};
