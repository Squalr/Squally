#pragma once

#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"

class LocalizedString;
class Sound;

class ManaPotion : public Consumable
{
public:
	static ManaPotion* create();

	void useOutOfCombat(PlatformerEntity* target) override;
	bool canUseOnTarget(PlatformerEntity* target) override;
	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getSerializationKey() override;

	static const std::string SaveKey;
	static const float RestorePercentage;

protected:
	ManaPotion();
	virtual ~ManaPotion();

	PlatformerAttack* createAssociatedAttack() override;

private:
	typedef Consumable super;

	Sound* outOfCombatSound;
};
