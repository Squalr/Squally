#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Misc.h"

class FountainRoomKey : public Misc
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
	typedef Misc super;
};
