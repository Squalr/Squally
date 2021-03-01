#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"

class MithrilSword : public Sword
{
public:
	static MithrilSword* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	MithrilSword();
	virtual ~MithrilSword();

private:
	typedef Sword super;
};
