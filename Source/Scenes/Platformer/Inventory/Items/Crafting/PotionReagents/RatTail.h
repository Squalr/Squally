#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class RatTail : public Crafting
{
public:
	static RatTail* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	RatTail();
	virtual ~RatTail();

private:
	typedef Crafting super;
};
