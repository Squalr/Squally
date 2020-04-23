#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Earrings/Earring.h"

class SapphireEarrings : public Earring
{
public:
	static SapphireEarrings* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	SapphireEarrings();
	virtual ~SapphireEarrings();

private:
	typedef Earring super;
};
