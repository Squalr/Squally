#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class Jade : public Crafting
{
public:
	static Jade* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyJade;

protected:
	Jade();
	virtual ~Jade();

private:
	typedef Crafting super;
};
