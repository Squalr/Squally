#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Earrings/Earring.h"

class AquaMarineEarrings : public Earring
{
public:
	static AquaMarineEarrings* create();

	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getSerializationKey() override;

	static const std::string SaveKey;

protected:
	AquaMarineEarrings();
	virtual ~AquaMarineEarrings();

private:
	typedef Earring super;
};
