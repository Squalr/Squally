#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"

class MithrilSword : public Sword
{
public:
	static MithrilSword* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	MithrilSword();
	virtual ~MithrilSword();

private:
	typedef Sword super;
};
