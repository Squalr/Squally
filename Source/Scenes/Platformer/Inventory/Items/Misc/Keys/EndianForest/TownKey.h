#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class TownKey : public Key
{
public:
	static TownKey* create();

	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getSerializationKey() override;

	static const std::string SaveKey;

protected:
	TownKey();
	virtual ~TownKey();

private:
	typedef Key super;
};
