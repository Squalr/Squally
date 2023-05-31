#pragma once

#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"

class LocalizedString;
class Sound;

class SpikedBomb : public Consumable
{
public:
	static SpikedBomb* create();
	
	bool canUseOnTarget(PlatformerEntity* target) override;
	virtual LocalizedString* getDescription();
	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;
	static const int DamageMin;
	static const int DamageMax;

protected:
	SpikedBomb();
	virtual ~SpikedBomb();

	PlatformerAttack* createAssociatedAttack() override;

private:
	typedef Consumable super;
	
	Sound* outOfCombatSound = nullptr;
};
