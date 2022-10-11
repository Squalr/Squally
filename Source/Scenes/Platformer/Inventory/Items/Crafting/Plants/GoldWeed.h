#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class GoldWeed : public Crafting
{
public:
	static GoldWeed* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	GoldWeed();
	virtual ~GoldWeed();

private:
	typedef Crafting super;
};
