#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Misc.h"

class EssenceOfUndeath : public Misc
{
public:
	static EssenceOfUndeath* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyEssenceOfUndeath;

protected:
	EssenceOfUndeath();
	~EssenceOfUndeath();

private:
	typedef Misc super;
};
