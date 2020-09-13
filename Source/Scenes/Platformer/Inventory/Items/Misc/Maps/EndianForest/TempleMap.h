#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Maps/DungeonMap.h"

class TempleMap : public DungeonMap
{
public:
	static TempleMap* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	TempleMap();
	virtual ~TempleMap();

private:
	typedef DungeonMap super;
};
