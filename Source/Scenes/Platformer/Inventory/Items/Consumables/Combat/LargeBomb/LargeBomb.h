#pragma once

#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"

class LocalizedString;
class Sound;

class LargeBomb : public Consumable
{
public:
	static LargeBomb* create();
	
	bool canUseOnTarget(PlatformerEntity* target) override;
	LocalizedString* getDescription() override;
	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;
	static const int DamageMin;
	static const int DamageMax;

protected:
	LargeBomb();
	virtual ~LargeBomb();

	PlatformerAttack* createAssociatedAttack() override;

private:
	typedef Consumable super;
	
	Sound* outOfCombatSound = nullptr;
};
