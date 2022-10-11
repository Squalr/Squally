#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Earrings/Earring.h"

class HeartEarrings : public Earring
{
public:
	static HeartEarrings* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	HeartEarrings();
	virtual ~HeartEarrings();

private:
	typedef Earring super;
};
