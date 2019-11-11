#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Misc.h"

class EssenceOfShadow : public Misc
{
public:
	static EssenceOfShadow* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyEssenceOfShadow;

protected:
	EssenceOfShadow();
	~EssenceOfShadow();

private:
	typedef Misc super;
};
