#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Earrings/Earring.h"

class SapphireEarrings : public Earring
{
public:
	static SapphireEarrings* create();

	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getSerializationKey() override;

	static const std::string SaveKey;

protected:
	SapphireEarrings();
	virtual ~SapphireEarrings();

private:
	typedef Earring super;
};
