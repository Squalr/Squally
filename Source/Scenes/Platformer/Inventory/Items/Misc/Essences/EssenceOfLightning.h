#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Misc.h"

class EssenceOfLightning : public Misc
{
public:
	static EssenceOfLightning* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyEssenceOfLightning;

protected:
	EssenceOfLightning();
	~EssenceOfLightning();

private:
	typedef Misc super;
};
