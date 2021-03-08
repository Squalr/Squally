#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class FountainRoomKey : public Key
{
public:
	static FountainRoomKey* create();

	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getSerializationKey() override;

	static const std::string SaveKey;

protected:
	FountainRoomKey();
	virtual ~FountainRoomKey();

private:
	typedef Key super;
};
