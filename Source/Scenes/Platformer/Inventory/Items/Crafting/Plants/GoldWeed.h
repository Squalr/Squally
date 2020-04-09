#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class GoldWeed : public Crafting
{
public:
	static GoldWeed* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	GoldWeed();
	virtual ~GoldWeed();

private:
	typedef Crafting super;
};
