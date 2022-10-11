#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Earrings/Earring.h"

class CrystalEarrings : public Earring
{
public:
	static CrystalEarrings* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	CrystalEarrings();
	virtual ~CrystalEarrings();

private:
	typedef Earring super;
};
