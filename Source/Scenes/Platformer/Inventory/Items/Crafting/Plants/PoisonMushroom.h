#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class PoisonMushroom : public Crafting
{
public:
	static PoisonMushroom* create();

	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getSerializationKey() override;

	static const std::string SaveKey;

protected:
	PoisonMushroom();
	virtual ~PoisonMushroom();

private:
	typedef Crafting super;
};
