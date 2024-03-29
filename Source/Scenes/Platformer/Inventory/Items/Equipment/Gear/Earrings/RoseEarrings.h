#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Earrings/Earring.h"

class RoseEarrings : public Earring
{
public:
	static RoseEarrings* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	RoseEarrings();
	virtual ~RoseEarrings();

private:
	typedef Earring super;
};
