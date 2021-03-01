#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"

class GoldenSword : public Sword
{
public:
	static GoldenSword* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	GoldenSword();
	virtual ~GoldenSword();

private:
	typedef Sword super;
};
