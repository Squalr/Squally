#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class FountainRoomKey : public Key
{
public:
	static FountainRoomKey* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	FountainRoomKey();
	virtual ~FountainRoomKey();

private:
	typedef Key super;
};
