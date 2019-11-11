#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Misc.h"

class EssenceOfFrost : public Misc
{
public:
	static EssenceOfFrost* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyEssenceOfFrost;

protected:
	EssenceOfFrost();
	~EssenceOfFrost();

private:
	typedef Misc super;
};
