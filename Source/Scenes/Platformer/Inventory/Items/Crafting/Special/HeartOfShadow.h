#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class HeartOfShadow : public Crafting
{
public:
	static HeartOfShadow* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	HeartOfShadow();
	virtual ~HeartOfShadow();

private:
	typedef Crafting super;
};
