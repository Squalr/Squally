#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Maps/DungeonMap.h"

class TempleMap : public DungeonMap
{
public:
	static TempleMap* create();

	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getSerializationKey() override;

	static const std::string SaveKey;

protected:
	TempleMap();
	virtual ~TempleMap();

private:
	typedef DungeonMap super;
};
