#pragma once

#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"

class LocalizedString;
class Sound;

class FragGrenade : public Consumable
{
public:
	static FragGrenade* create();
	
	bool canUseOnTarget(PlatformerEntity* target) override;

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;
	static const int DamageMin;
	static const int DamageMax;

protected:
	FragGrenade();
	virtual ~FragGrenade();

	PlatformerAttack* createAssociatedAttack() override;

private:
	typedef Consumable super;
	
	Sound* outOfCombatSound = nullptr;
};
