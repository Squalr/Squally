#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Earrings/Earring.h"

class AquaMarineEarrings : public Earring
{
public:
	static AquaMarineEarrings* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	AquaMarineEarrings();
	virtual ~AquaMarineEarrings();

private:
	typedef Earring super;
};
