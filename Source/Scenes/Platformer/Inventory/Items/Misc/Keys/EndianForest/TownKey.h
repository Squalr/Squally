#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Misc.h"

class TownKey : public Misc
{
public:
	static TownKey* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyTownKey;

protected:
	TownKey();
	virtual ~TownKey();

private:
	typedef Misc super;
};
