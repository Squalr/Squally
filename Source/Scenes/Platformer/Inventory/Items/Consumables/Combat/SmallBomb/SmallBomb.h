#pragma once

#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"

class LocalizedString;
class Sound;

class SmallBomb : public Consumable
{
public:
	static SmallBomb* create();
	
	bool canUseOnTarget(PlatformerEntity* target) override;

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;
	static const int DamageMin;
	static const int DamageMax;

protected:
	SmallBomb();
	virtual ~SmallBomb();

	PlatformerAttack* createAssociatedAttack() override;

private:
	typedef Consumable super;
	
	Sound* outOfCombatSound = nullptr;
};
