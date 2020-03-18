#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class Adamantite : public Crafting
{
public:
	static Adamantite* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyAdamantite;

protected:
	Adamantite();
	virtual ~Adamantite();

private:
	typedef Crafting super;
};
