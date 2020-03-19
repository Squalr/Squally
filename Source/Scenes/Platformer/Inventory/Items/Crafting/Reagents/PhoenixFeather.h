#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class PhoenixFeather : public Crafting
{
public:
	static PhoenixFeather* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	PhoenixFeather();
	virtual ~PhoenixFeather();

private:
	typedef Crafting super;
};
