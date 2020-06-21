#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Earrings/Earring.h"

class RoseEarrings : public Earring
{
public:
	static RoseEarrings* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	RoseEarrings();
	virtual ~RoseEarrings();

private:
	typedef Earring super;
};
