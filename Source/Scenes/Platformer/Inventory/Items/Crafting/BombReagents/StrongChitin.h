#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class StrongChitin : public Crafting
{
public:
	static StrongChitin* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	StrongChitin();
	virtual ~StrongChitin();

private:
	typedef Crafting super;
};
