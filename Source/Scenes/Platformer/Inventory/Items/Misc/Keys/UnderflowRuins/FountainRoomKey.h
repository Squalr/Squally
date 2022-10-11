#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class FountainRoomKey : public Key
{
public:
	static FountainRoomKey* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	FountainRoomKey();
	virtual ~FountainRoomKey();

private:
	typedef Key super;
};
