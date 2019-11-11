#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Misc.h"

class EssenceOfNature : public Misc
{
public:
	static EssenceOfNature* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyEssenceOfNature;

protected:
	EssenceOfNature();
	~EssenceOfNature();

private:
	typedef Misc super;
};
