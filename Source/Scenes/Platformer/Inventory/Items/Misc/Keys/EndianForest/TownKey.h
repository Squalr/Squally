#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class TownKey : public Key
{
public:
	static TownKey* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	TownKey();
	virtual ~TownKey();

private:
	typedef Key super;
};
