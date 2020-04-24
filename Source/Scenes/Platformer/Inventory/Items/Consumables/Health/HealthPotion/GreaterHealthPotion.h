#pragma once

#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"

class LocalizedString;

class GreaterHealthPotion : public Consumable
{
public:
	static GreaterHealthPotion* create();
	
	void useOutOfCombat(PlatformerEntity* target) override;

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;
	static const float HealPercentage;

protected:
	GreaterHealthPotion();
	virtual ~GreaterHealthPotion();

	PlatformerAttack* createAssociatedAttack() override;

private:
	typedef Consumable super;
};
