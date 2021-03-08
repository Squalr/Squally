#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Maps/DungeonMap.h"

class TempleMap : public DungeonMap
{
public:
	static TempleMap* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	TempleMap();
	virtual ~TempleMap();

private:
	typedef DungeonMap super;
};
