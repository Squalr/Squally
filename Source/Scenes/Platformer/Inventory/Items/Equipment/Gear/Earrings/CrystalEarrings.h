#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Earrings/Earring.h"

class CrystalEarrings : public Earring
{
public:
	static CrystalEarrings* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	CrystalEarrings();
	virtual ~CrystalEarrings();

private:
	typedef Earring super;
};
