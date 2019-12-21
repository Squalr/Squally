#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Misc.h"

class EssenceOfWind : public Misc
{
public:
	static EssenceOfWind* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyEssenceOfWind;

protected:
	EssenceOfWind();
	~EssenceOfWind();

private:
	typedef Misc super;
};
