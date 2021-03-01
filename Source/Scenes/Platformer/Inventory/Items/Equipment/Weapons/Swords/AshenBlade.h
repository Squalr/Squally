#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"

class AshenBlade : public Sword
{
public:
	static AshenBlade* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	AshenBlade();
	virtual ~AshenBlade();

private:
	typedef Sword super;
};
