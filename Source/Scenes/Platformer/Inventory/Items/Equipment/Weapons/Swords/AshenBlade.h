#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"

class AshenBlade : public Sword
{
public:
	static AshenBlade* create();

	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getSerializationKey() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	AshenBlade();
	virtual ~AshenBlade();

private:
	typedef Sword super;
};
