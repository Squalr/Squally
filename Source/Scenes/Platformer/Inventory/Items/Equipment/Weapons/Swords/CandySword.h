#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"

class CandySword : public Sword
{
public:
	static CandySword* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	CandySword();
	virtual ~CandySword();

private:
	typedef Sword super;
};
